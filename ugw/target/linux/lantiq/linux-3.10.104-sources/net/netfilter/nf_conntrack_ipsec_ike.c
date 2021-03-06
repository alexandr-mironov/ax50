/******************************************************************************
**
** FILE NAME    : nf_contrack_ipsec.c
**
** DATE         : 22 Nov 2010
** AUTHOR       : Manamohan Shetty 
** DESCRIPTION  : IPSec IKE extension for connection tracking.
** COPYRIGHT    :       Copyright (c) 2009
**                      Lantiq Deutschland GmbH
**                      Am Campeon 3, 85579 Neubiberg, Germany
**
**    This program is free software; you can redistribute it and/or modify
**    it under the terms of the GNU General Public License as published by
**    the Free Software Foundation; either version 2 of the License, or
**    (at your option) any later version.
**
** HISTORY
** $Date        $Author         	$Comment
** 22 Nov,2010  Manamohan Shetty    	First release
** 19 Sep,2015  $Tapan/Radhakrishna     Ported to 6.1.1_3.10.69
*******************************************************************************/

#include <linux/module.h>
#include <linux/moduleparam.h>
#include <linux/netfilter.h>
#include <linux/ip.h>
#include <linux/ipv6.h>
#include <linux/ctype.h>
#include <linux/inet.h>
#include <net/checksum.h>
#include <net/udp.h>
#include <linux/slab.h>
#include <net/tcp.h>

#include <net/netfilter/nf_conntrack.h>
#include <net/netfilter/nf_conntrack_expect.h>
#include <net/netfilter/nf_conntrack_ecache.h>
#include <net/netfilter/nf_conntrack_helper.h>

#include <linux/netfilter/nf_conntrack_ipsec_ike.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Manamohan Shetty <Manamohan.Shetty@lantiq.com>");
MODULE_DESCRIPTION("IPSec IKEY connection tracking helper");

static bool loose;
module_param(loose, bool, 0600);

static DEFINE_SPINLOCK(nf_ipsec_ike_lock);

#define MAX_PORTS 8
static u_int16_t ports[MAX_PORTS];
static unsigned int ports_c;

#if 0
#define DEBUGP printk
#else
#define DEBUGP(format, args...)
#endif

#if 0
void ipsec_ike_match(void)
{
	printk("\nIPSec IKE Expectation matched successfully\n");

}
#endif

static int help(struct sk_buff *skb, unsigned int protoff, struct nf_conn *ct, enum ip_conntrack_info ctinfo)
{
	unsigned int dataoff = 0, datalen = 0;
	struct iphdr *iph = NULL;
	struct udphdr *udph = NULL;
	char *fb_ptr = NULL;
	char *data_ptr = NULL;
	int ret = 0;
	int dir = CTINFO2DIR(ctinfo);
	struct nf_conntrack_expect *exp;

	uint64_t vendor_Id = 0;
	u32 vendor_payload_len = 0;
	u_int16_t port = 0;
	struct ike_secassoci_hdr *ike_secassoci_ptr = NULL;
	union nf_inet_addr *daddr;
	struct nf_conntrack_man cmd = { };

	spin_lock_bh(&nf_ipsec_ike_lock);

	/* iph = (*pskb)->nh.iph; */
	iph = ip_hdr(skb);
	udph = (void *)iph + iph->ihl * 4;

	ike_secassoci_ptr = (void *)udph + 8;
	fb_ptr = (char *)udph + 8;

	dataoff = protoff + 8;
	/* No data? */
	if (dataoff >= (skb)->len) {
		DEBUGP("IPSEC IKY: dataoff(%u) >= skblen(%u)\n", dataoff, (skb)->len);

		spin_unlock_bh(&nf_ipsec_ike_lock);
		return NF_ACCEPT;
	}
	datalen = (skb)->len - dataoff;

	DEBUGP("IPSec IKY: datalen=%d\n", datalen);
#if 0
	th = skb_header_pointer(*pskb, protoff, sizeof(_udph), &_udph);
	if (th == NULL)
		return NF_ACCEPT;
#endif
	if ((ntohs(udph->dest) != IPSEC_IKEY_PORT)) {
		DEBUGP("Returned from 1\n");
		spin_unlock_bh(&nf_ipsec_ike_lock);
		return NF_ACCEPT;
	}

	DEBUGP("IPSec IKY: udph->dest=%d\n", udph->dest);

/*Check for the Initiator Cookie and Responder cookie */
	if (!((ike_secassoci_ptr->init_cookie != 0x0) && (ike_secassoci_ptr->resp_cookie == 0x0))) {
		DEBUGP("Returned from 2\n");
		spin_unlock_bh(&nf_ipsec_ike_lock);
		return NF_ACCEPT;
	}

/* Security Association Payload,check for the Vendor Id   */

	DEBUGP("IPSec IKY:fb_ptr + IKE_VENDORID_OFFSET =0x%x\n", *(fb_ptr + IKE_VENDORID_OFFSET));

#if 1
	if (*(fb_ptr + IKE_VENDORID_OFFSET) == VENDORID) {
//#ifdef CONFIG_CPU_BIG_ENDIAN
#if 0
		DEBUGP("IPSec IKY:BIG ENDIAN\n");
		vendor_payload_len = le32_to_cpu(*(u32 *) (fb_ptr + IKE_SAP_LENGTH_OFFSET));
#else
		vendor_payload_len = *(u32 *) (fb_ptr + IKE_SAP_LENGTH_OFFSET);
#endif
		DEBUGP("IPSec IKY: vendor_payload_len=0x%x\n", vendor_payload_len);

		vendor_payload_len = (vendor_payload_len >> 8) & 0xFFFFFF;

		DEBUGP("IPSec IKY: After 8 bit shift vendor_payload_len=0x%x\n", vendor_payload_len);
		if (vendor_payload_len > datalen) {
			DEBUGP("IPSec IKY:Initial payloadlen is greater than datalen \n");
			spin_unlock_bh(&nf_ipsec_ike_lock);
			return NF_ACCEPT;
		}

		data_ptr = (fb_ptr + IKE_VENDORID_OFFSET + vendor_payload_len + 1);

//#ifdef CONFIG_CPU_BIG_ENDIAN
#if 0
		vendor_payload_len = le32_to_cpu(*(u32 *) (data_ptr));
#else
		vendor_payload_len = *(u32 *) (data_ptr);
#endif
		DEBUGP("IPSec IKY:Next vendor_payload_len=0x%x\n", vendor_payload_len);
		vendor_payload_len = (vendor_payload_len >> 8) & 0xFFFFFF;

		DEBUGP("IPSec IKY: Next vendor_payload_len after 8 bit shift=0x%x\n", vendor_payload_len);

		if (vendor_payload_len > datalen) {
			DEBUGP("IPSec IKY:Next payloadlen is greater than datalen \n");
			spin_unlock_bh(&nf_ipsec_ike_lock);
			return NF_ACCEPT;
		}
//#ifdef CONFIG_CPU_BIG_ENDIAN
#if 0
		vendor_Id = le64_to_cpu(*(uint64_t *) (data_ptr + 3));
#else
		vendor_Id = *(uint64_t *) (data_ptr + 3);
#endif
		DEBUGP("IPSec IKY: Actual Vendor Id=%llu\n", vendor_Id);
#if 0
		vendor_payload_len = 12;
		*(data_ptr + 3) = 'B';
		*(data_ptr + 4) = 'N';
		*(data_ptr + 5) = 'E';
		*(data_ptr + 6) = 'C';
		*(data_ptr + 7) = 0x0;
		*(data_ptr + 8) = 0x0;
		*(data_ptr + 9) = 0x0;
		*(data_ptr + 10) = 0x04;

		vendor_payload_len = 30;
		*(data_ptr + 3) = 'N';
		*(data_ptr + 4) = 'a';
		*(data_ptr + 5) = 'T';
		*(data_ptr + 6) = '-';
		*(data_ptr + 7) = 'S';
		*(data_ptr + 8) = 'I';
#endif
		if (vendor_payload_len == 12) {
			if (vendor_Id == UNKNOWN_VENDORID_BNEC) {
				DEBUGP("IPSec IKY: Entered BNEC \n");
				port = IPSEC_IKEY_DATA_PORT_SHASTA;
			} else
				port = IPSEC_IKEY_DATA_PORT;
		} else if (vendor_payload_len == 30) {
			if (strncmp(data_ptr + 3, "NaT-SI", 6) == 0) {
				DEBUGP("IPSec IKY: Entered NAT-SI \n");
				port = IPSEC_IKEY_DATA_PORT_SHASTA;
			} else
				port = IPSEC_IKEY_DATA_PORT;
		} else
			port = IPSEC_IKEY_DATA_PORT;
	} else {
		DEBUGP("IPSec IKY: payload doesn't contain Vendor Id 0xC\n");
		spin_unlock_bh(&nf_ipsec_ike_lock);
		//port = IPSEC_IKEY_DATA_PORT;
		return NF_ACCEPT;
	}
#endif

#if 0
	DEBUGP("\nPayload dump:\n");
	for (i = 0; i < datalen; i++) {
		DEBUGP("0x%2.2x ", (u8) * (fb_ptr + i));
		if (i % 16 == 15)
			DEBUGP("\n");
	}
	DEBUGP("\n");
#endif
	DEBUGP("IPSec IKY: Port=%d\n", port);
	/* exp = nf_conntrack_expect_alloc(ct); */
	exp = nf_ct_expect_alloc(ct);

	if (exp == NULL) {
		spin_unlock_bh(&nf_ipsec_ike_lock);
		DEBUGP("IPSec IKY: nf_conntrack_expect_alloc failed\n");
		return NF_DROP;
	}

	cmd.l3num = nf_ct_l3num(ct);

	/* We refer to the reverse direction ("!dir") tuples here,
	 * because we're expecting something in the other direction.
	 * Doesn't matter unless NAT is happening.  */
	daddr = &ct->tuplehash[!dir].tuple.dst.u3;

	/* Update the ftp info */
	if ((cmd.l3num == nf_ct_l3num(ct)) && memcmp(&cmd.u3.all, &ct->tuplehash[dir].tuple.src.u3.all, sizeof(cmd.u3.all))) {
		/* Enrico Scholz's passive FTP to partially RNAT'd ftp
		   server: it really wants us to connect to a
		   different IP address.  Simply don't record it for
		   NAT. */
		if (cmd.l3num == PF_INET) {
			pr_debug("conntrack_ftp: NOT RECORDING: %pI4 != %pI4\n", &cmd.u3.ip, &ct->tuplehash[dir].tuple.src.u3.ip);
		} else {
			pr_debug("conntrack_ftp: NOT RECORDING: %pI6 != %pI6\n", cmd.u3.ip6, ct->tuplehash[dir].tuple.src.u3.ip6);
		}

		/* Thanks to Cristiano Lincoln Mattos
		   <lincoln@cesar.org.br> for reporting this potential
		   problem (DMZ machines opening holes to internal
		   networks, or the packet filter itself). */
		if (!loose) {
			ret = NF_ACCEPT;
			goto out_put_expect;
		}
		daddr = &cmd.u3;
	}

	nf_ct_expect_init(exp, NF_CT_EXPECT_CLASS_DEFAULT, cmd.l3num, &ct->tuplehash[!dir].tuple.src.u3, daddr, IPPROTO_TCP, NULL, &cmd.u.tcp.port);

#if 0
	exp->mask = (struct nf_conntrack_tuple) {
		.src = {
			.l3num = 0xFFFF,
#ifdef CONFIG_IFX_NF_FIXES
			    .u = {
				.udp = {
			.port = 0}},
#else
			    .u = {
				.udp = {
			0}},
#endif
		},.dst = {
			.protonum = 0xFF,
#ifdef CONFIG_IFX_NF_FIXES
			    .u = {
				.udp = {
			.port = __constant_htons(0xFFFF)}},
#else
			    .u = {
				.udp = {
			__constant_htons(0xFFFF)}},
#endif
	},};
#endif
	exp->mask = (struct nf_conntrack_tuple_mask) {
		.src = {
#ifdef CONFIG_IFX_NF_FIXES
			.u = {
				.udp = {
			.port = 0}},
#else
			.u = {
				.udp = {
			0}},
#endif
		}
	};

	if (ct->tuplehash[dir].tuple.src.l3num == PF_INET) {
		exp->mask.src.u3.ip = htonl(0xFFFFFFFF);
		//exp->mask.dst.u3.ip = htonl(0xFFFFFFFF);
	} else {
		memset(exp->mask.src.u3.ip6, 0xFF, sizeof(exp->mask.src.u3.ip6));
		//memset(exp->mask.dst.u3.ip6, 0xFF, sizeof(exp->mask.src.u3.ip6));
	}

	DEBUGP("IPSec IKY: DST PORT %d", exp->tuple.dst.u.udp.port);
	exp->expectfn = NULL;
	exp->flags = 0;
#if 0
	DEBUGP("\nIPSec IKY expect:\n");
	NF_CT_DUMP_TUPLE(&exp->tuple);
	NF_CT_DUMP_TUPLE(&exp->mask);
#endif
	if (nf_ct_expect_related(exp) != 0) {
		ret = NF_DROP;
		DEBUGP("nf_conntrack_expect_related failed \n");
		nf_ct_expect_put(exp);
		spin_unlock_bh(&nf_ipsec_ike_lock);
		return ret;
	} else
		ret = NF_ACCEPT;

	DEBUGP("IPSec IKY: Expectation registered successfully\n");

 out_put_expect:
	nf_ct_expect_put(exp);
	spin_unlock_bh(&nf_ipsec_ike_lock);
	return ret;
}

static const struct nf_conntrack_expect_policy ipsec_ike_exp_policy = {
	.max_expected = 1,
	.timeout = 5 * 60,
};

static struct nf_conntrack_helper ipsec_ike[MAX_PORTS];
static char ipsec_ike_names[MAX_PORTS][sizeof("ipsec_ike-65535")];

static void nf_conntrack_ipsec_ike_fini(void)
{
	int i;
	for (i = 0; i < ports_c; i++) {
		if (ipsec_ike[i].me == NULL)
			continue;

		DEBUGP("nf_ct_ipsec_ike: unregistering helper for pf: %d " "port: %d\n", ipsec_ike[i].tuple.src.l3num, ports[i]);
		nf_conntrack_helper_unregister(&ipsec_ike[i]);
	}
}

static int __init nf_conntrack_ipsec_ike_init(void)
{
	int i, ret = 0;
	char *tmpname;

	if (ports_c == 0)
		ports[ports_c++] = IPSEC_IKEY_PORT;

	for (i = 0; i < ports_c; i++) {
		ipsec_ike[i].tuple.src.l3num = PF_INET;
		ipsec_ike[i].tuple.src.u.udp.port = htons(ports[i]);
		ipsec_ike[i].tuple.dst.protonum = IPPROTO_UDP;
#if 0
		ipsec_ike[i].mask.src.l3num = 0xFFFF;
		ipsec_ike[i].mask.src.u.udp.port = htons(0xFFFF);
		ipsec_ike[i].mask.dst.protonum = 0xFF;
#endif

		ipsec_ike[i].expect_policy = &ipsec_ike_exp_policy;
#if 0
		ipsec_ike[i].max_expected = 1;
		ipsec_ike[i].timeout = 5 * 60;	/* 5 Minutes */
#endif

		ipsec_ike[i].me = THIS_MODULE;
		ipsec_ike[i].help = help;
		tmpname = &ipsec_ike_names[i][0];
		if (ports[i] == IPSEC_IKEY_PORT)
			sprintf(tmpname, "ipsec_ike");
		else
			sprintf(tmpname, "ipsec_ike-%d", ports[i]);
		snprintf(ipsec_ike[i].name, NF_CT_HELPER_NAME_LEN, "%s", tmpname);
		printk("nf_ct_ipsec_ike: registering helper for pf: %d " "port: %d\n", ipsec_ike[i].tuple.src.l3num, ports[i]);
		ret = nf_conntrack_helper_register(&ipsec_ike[i]);
		if (ret) {
			printk("nf_ct_ipsec_ike: failed to register helper " " for pf: %d port: %d\n", ipsec_ike[i].tuple.src.l3num, ports[i]);
			nf_conntrack_ipsec_ike_fini();
			return ret;
		}
	}
	return 0;
}

module_init(nf_conntrack_ipsec_ike_init);
module_exit(nf_conntrack_ipsec_ike_fini);
