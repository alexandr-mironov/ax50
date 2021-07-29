/*******************************************************************************

  Intel DirectLink driver
  Copyright(c) 2016 Intel Corporation.

  This program is free software; you can redistribute it and/or modify it
  under the terms and conditions of the GNU General Public License,
  version 2, as published by the Free Software Foundation.

  This program is distributed in the hope it will be useful, but WITHOUT
  ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
  FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
  more details.

  You should have received a copy of the GNU General Public License along with
  this program; if not, write to the Free Software Foundation, Inc.,
  51 Franklin St - Fifth Floor, Boston, MA 02110-1301 USA.

  The full GNU General Public License is included in this distribution in
  the file called "COPYING".

*******************************************************************************/
#include "../include/dlrx_fw_def.h"
#include "../include/dlrx_fw_data_structure_macro.h"
#include "../include/dlrx_fw_data_structure.h"
#include "../include/dlrx_fw_internal_def.h"
#include "../include/dlrx_dre_api.h"
#include "../include/dlrx_inl_fns.h"

/*#include "../include/cycle_counter.h" */
void dlrx_ind_msg_process(unsigned int *ce5buf_ptr);
void dlrx_ind_rel_flush_process(unsigned int *ce5buf_ptr);
unsigned int peer_vld_check(unsigned int peer_id);

extern void msg_mib_inc(unsigned int msg_type);
extern void dlrx_reorder_buffering_process(unsigned int *ce5_buf_ptr);
extern void dlrx_playout_process(unsigned int ce5_buf_ptr);
extern void ro_list_reset(unsigned int peer);
extern int ppa_dl_dre_wlan_msg_send(unsigned int msg_type, unsigned int msg_ptr, unsigned int msg_len,
				    unsigned int flags);

/*************************************************************************
// Module:          dlrx_ind_msg_process
// Description:     RX Indication Message Processing, based on validity of
//                  peer, continue processing or send the whole message to
//                  wlan driver
// Parameters:      ce5buf_ptr
// Return value :   None
// Functions called by this module:
//                  peer_vld_check()
//                  dlrx_reorder_buffering_process()
//                  dlrx_ind_rel_flush_process()
// Notes        :   rxpb_ptr_read_index should be set correctly by firmware
//                  when dlrx_main was called previously,
//                  cfg_num_rxpb_ptr_ring should be set correctly by driver
//                  . Check the notes of functions called for complete list
//                  to be set in the context.
*************************************************************************/
void dlrx_ind_msg_process(unsigned int *ce5buf_ptr)
{
	unsigned int peer_id, peer_vld, acc_dis;
	unsigned int var_size_rx_desc_byte, variable_size, total_msdu, ext_tid;

/*    CycleCounter_Start(function1_cycles); */

	/*Increment message mib for RX Indication Message */
	mib_update_rx_ind_msg();

	peer_id = DLRX_IND_MSG_peer_id_get_indirect(ce5buf_ptr, 0);

	/*peer_vld is set if peer_id is within valid range and valid */
	peer_vld = peer_vld_check(peer_id);
	/*acc_dis is set by peer_vld_check() */
	/*When peer_vid !=0, acc_dis is not correct value. */
	acc_dis = DLRX_CTXT_MSG_acc_dis_get_indirect(DLRX_CTXT_MSG_BASE, 0);

	total_msdu = DLRX_IND_MSG_fw_rx_desc_byte_num_get_indirect(ce5buf_ptr, 0);

	DLRX_CTXT_MSG_total_msdu_set_indirect(DLRX_CTXT_MSG_BASE, 0, total_msdu);

	/*variable_size (dw) = roundup(total_msdu/4) + number of mpdu_ranges */
	var_size_rx_desc_byte = total_msdu >> 2;

	if (total_msdu % 4)
		var_size_rx_desc_byte++;

	variable_size  = var_size_rx_desc_byte + DLRX_IND_MSG_mpdu_ranges_num_get_indirect(ce5buf_ptr, 0);

	/*Get ext_tid and save to FW context */
	ext_tid = DLRX_IND_MSG_ext_tid_get_indirect(ce5buf_ptr, 0);
	DLRX_CTXT_MSG_ext_tid_set_indirect(DLRX_CTXT_MSG_BASE, 0, ext_tid);

	if (peer_vld && acc_dis) {
		/*For peer valid but acceleration is disabled */
		unsigned int msg_type;
		unsigned int msg_len;

		/*RX indication Message to wlan */
		unsigned int *buf_end_ptr = ce5buf_ptr + (sizeof(dlrx_ind_msg_t) / 4) + variable_size;

		/*Increment message mib for RX Indication Message to WLAN */
		msg_mib_inc(HTT_RX_IND_MSG_WLAN);

		/*Write rxpb_ptr_read_index to end of message */

		*buf_end_ptr = DLRX_CFG_CTXT_RXPB_PTR_RING_rxpb_ptr_read_index_get_indirect((unsigned int *)UNCACHE_ADDR(DLRX_CFG_CTXT_RXPB_PTR_RING_BASE), 0);

		/*cpu_ce5des_enq(); */

		msg_type = DLRX_IND_MSG_msg_type_get_indirect(ce5buf_ptr, 0);
		msg_len = DLRX_CFG_CTXT_CE5DES_msg_len_get_indirect(DLRX_CFG_CTXT_CE5DES_BASE, 0);

		/*call driver API to send message to wlan driver */
		ppa_dl_dre_wlan_msg_send(msg_type, (unsigned int)ce5buf_ptr, msg_len, 0);
	} else {
		/*For peer valid and acceleration enabled/ peer invalid */
		/* Control can reach here when the peer is not valid however the function */
		/* dlrx_reorder_buffering_process handles this condition */
		if ((g_qca_hw == BEELINER_BOARD) || total_msdu)
			dlrx_reorder_buffering_process(ce5buf_ptr);

		if (!global_debug_flag)
			dlrx_ind_rel_flush_process(ce5buf_ptr);

	}

	/*  CycleCounter_End(function1_cycles); */
	return;
}

/*************************************************************************
// Module:          peer_vld_check
// Description:     Check peer_id range and peer_id_vld to determine whether
//                  the peer is valid or not; also get vap, sec_type
//                  and acc_dis for this peer.
// Parameters:      ce5buf_ptr
// Return value :   peer_vld
// Functions called by this module:
//                  None
// Notes        :   dlrx_cfg_peer_id_to_peer_map and dlrx_cfg_peer_to_vap
//                  should be configured by driver prior this function is
//                  called.
*************************************************************************/
unsigned int peer_vld_check(unsigned int peer_id)
{
	unsigned int peer, vap, sec_type, acc_dis, peer_id_vld;
	unsigned int peer_vld = 0;

	peer_id_vld = ppa_dl_dre_peer_from_peerid(peer_id, &peer);

	if (peer_id_vld) {
		ppa_dl_dre_vapinfo_from_peer(peer, &vap, &sec_type, &acc_dis);

		DLRX_CTXT_MSG_peer_set_indirect(DLRX_CTXT_MSG_BASE, 0, peer);
		DLRX_CTXT_MSG_vap_set_indirect(DLRX_CTXT_MSG_BASE, 0, vap);
		DLRX_CTXT_MSG_sec_type_set_indirect(DLRX_CTXT_MSG_BASE, 0, sec_type);
		DLRX_CTXT_MSG_acc_dis_set_indirect(DLRX_CTXT_MSG_BASE, 0, acc_dis);

		if (peer_id < MAX_PEERID_NUM)
			peer_vld = 1;
	}

	DLRX_CTXT_MSG_peer_vld_set_indirect(DLRX_CTXT_MSG_BASE, 0, peer_vld);

	return peer_vld;

}

/*************************************************************************
// Module:          dlrx_ind_rel_flush_process
// Description:     RX Indication Message Release or Flush Processing.
//                  If ext_tid is invalid, set invalid_tid_peer and
//                  invalid_tid_req; otherwise check fv and rv flag
//                  to perform RX Playout Process accordingly.
// Parameters:      ce5buf_ptr
// Return value :   None
// Functions called by this module:
//                  msg_mib_inc()
//                  ro_list_reset()
//                  rx_playout_process()
// Notes        :   Make sure ext_tid and peer is saved to message context
//                  prior this function is called. Check the notes of
//                  functions called for complete list to be set in the
//                  context.
*************************************************************************/
void dlrx_ind_rel_flush_process(unsigned int *ce5buf_ptr)
{
	unsigned int ext_tid, peer;
	unsigned int fv = 0, rv = 0;
	unsigned int start_seqid, end_seqid, total_seqid;

	ext_tid = DLRX_CTXT_MSG_ext_tid_get_indirect(DLRX_CTXT_MSG_BASE, 0);
	peer    = DLRX_CTXT_MSG_peer_get_indirect(DLRX_CTXT_MSG_BASE, 0);

	if (ext_tid == INVALID_TID) {
		DLRX_CFG_INVALID_TID_peer_set_indirect(DLRX_CFG_INVALID_TID_BASE, 0, peer);
		DLRX_CFG_INVALID_TID_req_set_indirect(DLRX_CFG_INVALID_TID_BASE, 0, 1);

		/*Scan RO_mainlist and RO_linklist of all TID and seqid of this peer. */
		/*Free all valid packet buffer pointer used. Free used RO_linklist entry. */
		ro_list_reset(peer);
		msg_mib_inc(HTT_RX_INVALID_TID);
	} else {
		fv = DLRX_IND_MSG_fv_get_indirect(ce5buf_ptr, 0);
		rv = DLRX_IND_MSG_rv_get_indirect(ce5buf_ptr, 0);

		/*It is possible to have both fv and rv set, in this case, */
		/*perform flush first and followed by release */
		if (fv) {
			unsigned int seq_mask = dlrx_get_seq_mask(peer, ext_tid);
			unsigned int seq_num = seq_mask + 1;
			start_seqid = DLRX_IND_MSG_flush_start_seqid_get_indirect(ce5buf_ptr, 0);
			end_seqid =  DLRX_IND_MSG_flush_end_seqid_get_indirect(ce5buf_ptr, 0);
			start_seqid &= seq_mask;
			end_seqid &= seq_mask;
			/*Note: end_seqid is the sequence number one larger */
			/*than the sequence number of the last MPDU to check to flush */
			if (end_seqid > start_seqid)
				total_seqid = end_seqid - start_seqid;
			else if (end_seqid == start_seqid)
				total_seqid = seq_num;
			else
				total_seqid = end_seqid + seq_num - start_seqid;

			DLRX_CTXT_MSG_start_seqid_set_indirect(DLRX_CTXT_MSG_BASE, 0, start_seqid);
			DLRX_CTXT_MSG_total_seqid_set_indirect(DLRX_CTXT_MSG_BASE, 0, total_seqid);

			/* ce5buf_ptr is passed here for usage by the driver API */
			dlrx_playout_process((unsigned int) ce5buf_ptr);
		}

		if (rv) {
			unsigned int seq_mask = dlrx_get_seq_mask(peer, ext_tid);
			unsigned int seq_num = seq_mask + 1;
			start_seqid = DLRX_IND_MSG_release_start_seqid_get_indirect(ce5buf_ptr, 0);
			end_seqid =  DLRX_IND_MSG_release_end_seqid_get_indirect(ce5buf_ptr, 0);
			start_seqid &= seq_mask;
			end_seqid &= seq_mask;
			/*Note: end_seqid is the sequence number one larger */
			/*than the sequence number of the last MPDU to check to release */
			if (end_seqid > start_seqid)
				total_seqid = end_seqid - start_seqid;
			else if (end_seqid == start_seqid)
				total_seqid = seq_num;
			else
				total_seqid = end_seqid + seq_num - start_seqid;

			DLRX_CTXT_MSG_start_seqid_set_indirect(DLRX_CTXT_MSG_BASE, 0, start_seqid);
			DLRX_CTXT_MSG_total_seqid_set_indirect(DLRX_CTXT_MSG_BASE, 0, total_seqid);

			/* ce5buf_ptr is passed here for usage by the driver API */
			dlrx_playout_process((unsigned int) ce5buf_ptr);
		}
	}

	return;
}
