/* nf_nat_helper.c - generic support functions for NAT helpers
 *
 * (C) 2000-2002 Harald Welte <laforge@netfilter.org>
 * (C) 2003-2006 Netfilter Core Team <coreteam@netfilter.org>
 * (C) 2007-2012 Patrick McHardy <kaber@trash.net>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */
#include <linux/module.h>
#include <linux/gfp.h>
#include <linux/types.h>
#include <linux/skbuff.h>
#include <linux/tcp.h>
#include <linux/udp.h>
#include <net/tcp.h>

#include <net/netfilter/nf_conntrack.h>
#include <net/netfilter/nf_conntrack_helper.h>
#include <net/netfilter/nf_conntrack_ecache.h>
#include <net/netfilter/nf_conntrack_expect.h>
#include <net/netfilter/nf_nat.h>
#include <net/netfilter/nf_nat_l3proto.h>
#include <net/netfilter/nf_nat_l4proto.h>
#include <net/netfilter/nf_nat_core.h>
#include <net/netfilter/nf_nat_helper.h>

#ifdef CONFIG_LANTIQ_ALG_QOS
#if 0
#define DEBUGP printk
#define DUMP_OFFSET(x)	printk("offset_before=%d, offset_after=%d, correction_pos=%u\n", x->offset_before, x->offset_after, x->correction_pos);
#else
#define DEBUGP(format, args...)
#define DUMP_OFFSET(x)
#endif
#endif

#define DUMP_OFFSET(x) \
	pr_debug("offset_before=%d, offset_after=%d, correction_pos=%u\n", \
		 x->offset_before, x->offset_after, x->correction_pos);

static DEFINE_SPINLOCK(nf_nat_seqofs_lock);

/* Setup TCP sequence correction given this change at this sequence */
static inline void
adjust_tcp_sequence(u32 seq,
		    int sizediff,
		    struct nf_conn *ct,
		    enum ip_conntrack_info ctinfo)
{
	enum ip_conntrack_dir dir = CTINFO2DIR(ctinfo);
	struct nf_conn_nat *nat = nfct_nat(ct);
	struct nf_nat_seq *this_way = NULL;

	if(nat != NULL)
		this_way = &nat->seq[dir];

	if(this_way == NULL) {
		return;
	}
	pr_debug("adjust_tcp_sequence: seq = %u, sizediff = %d\n",
		 seq, sizediff);

	pr_debug("adjust_tcp_sequence: Seq_offset before: ");
	DUMP_OFFSET(this_way);

	spin_lock_bh(&nf_nat_seqofs_lock);

	/* SYN adjust. If it's uninitialized, or this is after last
	 * correction, record it: we don't handle more than one
	 * adjustment in the window, but do deal with common case of a
	 * retransmit */
	if (this_way->offset_before == this_way->offset_after ||
	    before(this_way->correction_pos, seq)) {
		this_way->correction_pos = seq;
		this_way->offset_before = this_way->offset_after;
		this_way->offset_after += sizediff;
	}
	spin_unlock_bh(&nf_nat_seqofs_lock);

	pr_debug("adjust_tcp_sequence: Seq_offset after: ");
	DUMP_OFFSET(this_way);
}

/* Get the offset value, for conntrack */
s16 nf_nat_get_offset(const struct nf_conn *ct,
		      enum ip_conntrack_dir dir,
		      u32 seq)
{
	struct nf_conn_nat *nat = nfct_nat(ct);
	struct nf_nat_seq *this_way;
	s16 offset;

	if (!nat)
		return 0;

	this_way = &nat->seq[dir];
	if(this_way == NULL) {
		return 0;
	}
	spin_lock_bh(&nf_nat_seqofs_lock);
	offset = after(seq, this_way->correction_pos)
		 ? this_way->offset_after : this_way->offset_before;
	spin_unlock_bh(&nf_nat_seqofs_lock);

	return offset;
}

/* Frobs data inside this packet, which is linear. */
static void mangle_contents(struct sk_buff *skb,
			    unsigned int dataoff,
			    unsigned int match_offset,
			    unsigned int match_len,
			    const char *rep_buffer,
			    unsigned int rep_len)
{
	unsigned char *data;

	BUG_ON(skb_is_nonlinear(skb));
	data = skb_network_header(skb) + dataoff;

	/* move post-replacement */
	memmove(data + match_offset + rep_len,
		data + match_offset + match_len,
		skb->tail - (skb->network_header + dataoff +
			     match_offset + match_len));

	/* insert data from buffer */
	memcpy(data + match_offset, rep_buffer, rep_len);

	/* update skb info */
	if (rep_len > match_len) {
		pr_debug("nf_nat_mangle_packet: Extending packet by "
			 "%u from %u bytes\n", rep_len - match_len, skb->len);
		skb_put(skb, rep_len - match_len);
	} else {
		pr_debug("nf_nat_mangle_packet: Shrinking packet from "
			 "%u from %u bytes\n", match_len - rep_len, skb->len);
		__skb_trim(skb, skb->len + rep_len - match_len);
	}

	if (nf_ct_l3num((struct nf_conn *)skb->nfct) == NFPROTO_IPV4) {
		/* fix IP hdr checksum information */
		ip_hdr(skb)->tot_len = htons(skb->len);
		ip_send_check(ip_hdr(skb));
	} else
		ipv6_hdr(skb)->payload_len =
			htons(skb->len - sizeof(struct ipv6hdr));
}

/* Unusual, but possible case. */
static int enlarge_skb(struct sk_buff *skb, unsigned int extra)
{
	if (skb->len + extra > 65535)
		return 0;

	if (pskb_expand_head(skb, 0, extra - skb_tailroom(skb), GFP_ATOMIC))
		return 0;

	return 1;
}

void nf_nat_set_seq_adjust(struct nf_conn *ct, enum ip_conntrack_info ctinfo,
			   __be32 seq, s16 off)
{
	if (!off)
		return;
	set_bit(IPS_SEQ_ADJUST_BIT, &ct->status);
	adjust_tcp_sequence(ntohl(seq), off, ct, ctinfo);
	nf_conntrack_event_cache(IPCT_NATSEQADJ, ct);
}
EXPORT_SYMBOL_GPL(nf_nat_set_seq_adjust);

void nf_nat_tcp_seq_adjust(struct sk_buff *skb, struct nf_conn *ct,
			   u32 ctinfo, int off)
{
	const struct tcphdr *th;

	if (nf_ct_protonum(ct) != IPPROTO_TCP)
		return;

	th = (struct tcphdr *)(skb_network_header(skb)+ ip_hdrlen(skb));
	nf_nat_set_seq_adjust(ct, ctinfo, th->seq, off);
}
EXPORT_SYMBOL_GPL(nf_nat_tcp_seq_adjust);

/* Generic function for mangling variable-length address changes inside
 * NATed TCP connections (like the PORT XXX,XXX,XXX,XXX,XXX,XXX
 * command in FTP).
 *
 * Takes care about all the nasty sequence number changes, checksumming,
 * skb enlargement, ...
 *
 * */
int __nf_nat_mangle_tcp_packet(struct sk_buff *skb,
			       struct nf_conn *ct,
			       enum ip_conntrack_info ctinfo,
			       unsigned int protoff,
			       unsigned int match_offset,
			       unsigned int match_len,
			       const char *rep_buffer,
			       unsigned int rep_len, bool adjust)
{
	const struct nf_nat_l3proto *l3proto;
	struct tcphdr *tcph;
	int oldlen, datalen;

	if (!skb_make_writable(skb, skb->len))
		return 0;

	if (rep_len > match_len &&
	    rep_len - match_len > skb_tailroom(skb) &&
	    !enlarge_skb(skb, rep_len - match_len))
		return 0;

	SKB_LINEAR_ASSERT(skb);

	tcph = (void *)skb->data + protoff;

	oldlen = skb->len - protoff;
	mangle_contents(skb, protoff + tcph->doff*4,
			match_offset, match_len, rep_buffer, rep_len);

	datalen = skb->len - protoff;

	l3proto = __nf_nat_l3proto_find(nf_ct_l3num(ct));
	l3proto->csum_recalc(skb, IPPROTO_TCP, tcph, &tcph->check,
			     datalen, oldlen);

	if (adjust && rep_len != match_len)
		nf_nat_set_seq_adjust(ct, ctinfo, tcph->seq,
				      (int)rep_len - (int)match_len);

	return 1;
}
EXPORT_SYMBOL(__nf_nat_mangle_tcp_packet);

/* Generic function for mangling variable-length address changes inside
 * NATed UDP connections (like the CONNECT DATA XXXXX MESG XXXXX INDEX XXXXX
 * command in the Amanda protocol)
 *
 * Takes care about all the nasty sequence number changes, checksumming,
 * skb enlargement, ...
 *
 * XXX - This function could be merged with nf_nat_mangle_tcp_packet which
 *       should be fairly easy to do.
 */
int
nf_nat_mangle_udp_packet(struct sk_buff *skb,
			 struct nf_conn *ct,
			 enum ip_conntrack_info ctinfo,
			 unsigned int protoff,
			 unsigned int match_offset,
			 unsigned int match_len,
			 const char *rep_buffer,
			 unsigned int rep_len)
{
	const struct nf_nat_l3proto *l3proto;
	struct udphdr *udph;
	int datalen, oldlen;

	if (!skb_make_writable(skb, skb->len))
		return 0;

	if (rep_len > match_len &&
	    rep_len - match_len > skb_tailroom(skb) &&
	    !enlarge_skb(skb, rep_len - match_len))
		return 0;

	udph = (void *)skb->data + protoff;

	oldlen = skb->len - protoff;
	mangle_contents(skb, protoff + sizeof(*udph),
			match_offset, match_len, rep_buffer, rep_len);

	/* update the length of the UDP packet */
	datalen = skb->len - protoff;
	udph->len = htons(datalen);

	/* fix udp checksum if udp checksum was previously calculated */
	if (!udph->check && skb->ip_summed != CHECKSUM_PARTIAL)
		return 1;

	l3proto = __nf_nat_l3proto_find(nf_ct_l3num(ct));
	l3proto->csum_recalc(skb, IPPROTO_UDP, udph, &udph->check,
			     datalen, oldlen);

	return 1;
}
EXPORT_SYMBOL(nf_nat_mangle_udp_packet);

/* Adjust one found SACK option including checksum correction */
static void
sack_adjust(struct sk_buff *skb,
	    struct tcphdr *tcph,
	    unsigned int sackoff,
	    unsigned int sackend,
	    struct nf_nat_seq *natseq)
{
	while (sackoff < sackend) {
		struct tcp_sack_block_wire *sack;
		__be32 new_start_seq, new_end_seq;

		sack = (void *)skb->data + sackoff;
		if (after(ntohl(sack->start_seq) - natseq->offset_before,
			  natseq->correction_pos))
			new_start_seq = htonl(ntohl(sack->start_seq)
					- natseq->offset_after);
		else
			new_start_seq = htonl(ntohl(sack->start_seq)
					- natseq->offset_before);

		if (after(ntohl(sack->end_seq) - natseq->offset_before,
			  natseq->correction_pos))
			new_end_seq = htonl(ntohl(sack->end_seq)
				      - natseq->offset_after);
		else
			new_end_seq = htonl(ntohl(sack->end_seq)
				      - natseq->offset_before);

		pr_debug("sack_adjust: start_seq: %d->%d, end_seq: %d->%d\n",
			 ntohl(sack->start_seq), new_start_seq,
			 ntohl(sack->end_seq), new_end_seq);

		inet_proto_csum_replace4(&tcph->check, skb,
					 sack->start_seq, new_start_seq, 0);
		inet_proto_csum_replace4(&tcph->check, skb,
					 sack->end_seq, new_end_seq, 0);
		sack->start_seq = new_start_seq;
		sack->end_seq = new_end_seq;
		sackoff += sizeof(*sack);
	}
}

/* TCP SACK sequence number adjustment */
static inline unsigned int
nf_nat_sack_adjust(struct sk_buff *skb,
		   unsigned int protoff,
		   struct tcphdr *tcph,
		   struct nf_conn *ct,
		   enum ip_conntrack_info ctinfo)
{
	unsigned int dir, optoff, optend;
	struct nf_conn_nat *nat = nfct_nat(ct);

	optoff = protoff + sizeof(struct tcphdr);
	optend = protoff + tcph->doff * 4;

	if (!skb_make_writable(skb, optend))
		return 0;

	dir = CTINFO2DIR(ctinfo);

	while (optoff < optend) {
		/* Usually: option, length. */
		unsigned char *op = skb->data + optoff;

		switch (op[0]) {
		case TCPOPT_EOL:
			return 1;
		case TCPOPT_NOP:
			optoff++;
			continue;
		default:
			/* no partial options */
			if (optoff + 1 == optend ||
			    optoff + op[1] > optend ||
			    op[1] < 2)
				return 0;
			if (op[0] == TCPOPT_SACK &&
			    op[1] >= 2+TCPOLEN_SACK_PERBLOCK &&
			    ((op[1] - 2) % TCPOLEN_SACK_PERBLOCK) == 0)
				sack_adjust(skb, tcph, optoff+2,
					    optoff+op[1], &nat->seq[!dir]);
			optoff += op[1];
		}
	}
	return 1;
}

/* TCP sequence number adjustment.  Returns 1 on success, 0 on failure */
int
nf_nat_seq_adjust(struct sk_buff *skb,
		  struct nf_conn *ct,
		  enum ip_conntrack_info ctinfo,
		  unsigned int protoff)
{
	struct tcphdr *tcph;
	int dir;
	__be32 newseq, newack;
	s16 seqoff, ackoff;
	struct nf_conn_nat *nat = nfct_nat(ct);
	struct nf_nat_seq *this_way, *other_way;

	dir = CTINFO2DIR(ctinfo);

	this_way = &nat->seq[dir];
	other_way = &nat->seq[!dir];

	if (!skb_make_writable(skb, protoff + sizeof(*tcph)))
		return 0;

	tcph = (void *)skb->data + protoff;
	if (after(ntohl(tcph->seq), this_way->correction_pos))
		seqoff = this_way->offset_after;
	else
		seqoff = this_way->offset_before;

	if (after(ntohl(tcph->ack_seq) - other_way->offset_before,
		  other_way->correction_pos))
		ackoff = other_way->offset_after;
	else
		ackoff = other_way->offset_before;

	newseq = htonl(ntohl(tcph->seq) + seqoff);
	newack = htonl(ntohl(tcph->ack_seq) - ackoff);

	inet_proto_csum_replace4(&tcph->check, skb, tcph->seq, newseq, 0);
	inet_proto_csum_replace4(&tcph->check, skb, tcph->ack_seq, newack, 0);

	pr_debug("Adjusting sequence number from %u->%u, ack from %u->%u\n",
		 ntohl(tcph->seq), ntohl(newseq), ntohl(tcph->ack_seq),
		 ntohl(newack));

	tcph->seq = newseq;
	tcph->ack_seq = newack;

	return nf_nat_sack_adjust(skb, protoff, tcph, ct, ctinfo);
}

/* Setup NAT on this expected conntrack so it follows master. */
/* If we fail to get a free NAT slot, we'll get dropped on confirm */
void nf_nat_follow_master(struct nf_conn *ct,
			  struct nf_conntrack_expect *exp)
{
	struct nf_nat_range range;

#ifdef CONFIG_LANTIQ_ALG_QOS
	if(exp->master->rtcp_expect_registered == 1) { 
		DEBUGP("\nMaster conntracker lantiq_alg_qos_mark is : %x \n",ct->lantiq_alg_qos_mark );
		ct->lantiq_alg_qos_mark = LANTIQ_ALG_APP_FTP | LANTIQ_ALG_PROTO_DATA;
		DEBUGP("\n Marked the Child conntrackeri with value: %x !!! \n",ct->lantiq_alg_qos_mark );
	}
	 
	else if(exp->master->rtcp_expect_registered == 2 ) {
		DEBUGP("\nMaster conntracker lantiq_alg_qos_mark(RTSP) is : %x \n",ct->lantiq_alg_qos_mark ); 
		ct->lantiq_alg_qos_mark = LANTIQ_ALG_APP_RTSP | LANTIQ_ALG_PROTO_RTP;
	}
	
	else if (exp->master->rtcp_expect_registered == 3 ) {
		ct->lantiq_alg_qos_mark = LANTIQ_ALG_APP_H323 | LANTIQ_ALG_PROTO_RTP;
	}
		
	else if (exp->master->rtcp_expect_registered == 4 ) {
		ct->lantiq_alg_qos_mark = LANTIQ_ALG_APP_H323 | LANTIQ_ALG_PROTO_RTCP;
	}
				   
	else if (exp->master->rtcp_expect_registered == 5 ) {
		ct->lantiq_alg_qos_mark = LANTIQ_ALG_APP_H323;
	}
#endif

	/* This must be a fresh one. */
	BUG_ON(ct->status & IPS_NAT_DONE_MASK);

	/* Change src to where master sends to */
	range.flags = NF_NAT_RANGE_MAP_IPS;
	range.min_addr = range.max_addr
		= ct->master->tuplehash[!exp->dir].tuple.dst.u3;
	nf_nat_setup_info(ct, &range, NF_NAT_MANIP_SRC);

	/* For DST manip, map port here to where it's expected. */
	range.flags = (NF_NAT_RANGE_MAP_IPS | NF_NAT_RANGE_PROTO_SPECIFIED);
	range.min_proto = range.max_proto = exp->saved_proto;
	range.min_addr = range.max_addr
		= ct->master->tuplehash[!exp->dir].tuple.src.u3;
	nf_nat_setup_info(ct, &range, NF_NAT_MANIP_DST);
}
EXPORT_SYMBOL(nf_nat_follow_master);
