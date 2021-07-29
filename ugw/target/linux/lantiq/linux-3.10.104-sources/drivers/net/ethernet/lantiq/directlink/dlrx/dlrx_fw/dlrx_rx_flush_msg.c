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
#include "../include/dlrx_inl_fns.h"
void dlrx_rx_flush_msg_process(unsigned int *ce5buf_ptr);

extern void msg_mib_inc(unsigned int msg_type);
extern unsigned int peer_vld_check(unsigned int peer_id);
extern void dlrx_playout_process(unsigned int ce5_buf_ptr);
extern void ro_list_reset(unsigned int peer);
extern int ppa_dl_dre_wlan_msg_send(unsigned int msg_type, unsigned int msg_ptr, unsigned int msg_len, unsigned int flags);

/*************************************************************************
// Module:          dlrx_rx_flush_msg_process
// Description:     RX Flush Message Processing.
//                  If ext_tid is invalid, set invalid_tid_peer and
//                  invalid_tid_req; otherwise check fv and rv flag
//                  to perform RX Playout Process accordingly.
// Parameters:      ce5buf_ptr
// Return value :   None
// Functions called by this module:
//                  msg_mib_inc()
//                  ro_list_reset()
//                  rx_playout_process()
// Notes        :   Make sure peer_vld and peer is saved
//                  to message context prior this function is called.
//                  Check the notes of functions called for
//                  complete list to be set in the context.
*************************************************************************/

void dlrx_rx_flush_msg_process(unsigned int *ce5buf_ptr)
{
	unsigned int peer_id, peer_vld, acc_dis;
	unsigned int ext_tid, peer;

	/*Increment message mib for RX Flush Message */
	msg_mib_inc(HTT_RX_FLUSH_MSG);

	peer_id = DLRX_FLUSH_MSG_peer_id_get_indirect(ce5buf_ptr, 0);

	/*peer_vld is set if peer_id is within valid range and valid */
	peer_vld = peer_vld_check(peer_id);

	/*peer, acc_dis and vap are set by peer_vld_check() */
	/*When peer_vid !=0, acc_dis is not correct value. */
	acc_dis = DLRX_CTXT_MSG_acc_dis_get_indirect(DLRX_CTXT_MSG_BASE, 0);

	if (peer_vld && (!acc_dis)) {
		ext_tid = DLRX_FLUSH_MSG_ext_tid_get_indirect(ce5buf_ptr, 0);
		DLRX_CTXT_MSG_ext_tid_set_indirect(DLRX_CTXT_MSG_BASE, 0, ext_tid);

		peer    = DLRX_CTXT_MSG_peer_get_indirect(DLRX_CTXT_MSG_BASE, 0);

		if (ext_tid == INVALID_TID) {
			/*Scan RO_mainlist and RO_linklist of all TID and seqid of this peer. */
			/*Free all valid packet buffer pointer used. Free used RO_linklist entry. */
			ro_list_reset(peer);
			msg_mib_inc(HTT_RX_INVALID_TID);
		} else {
			unsigned int start_seqid, end_seqid, total_seqid;
			unsigned int seq_mask = dlrx_get_seq_mask(peer, ext_tid);
			unsigned int seq_num = seq_mask + 1;
			start_seqid = DLRX_FLUSH_MSG_flush_start_seqid_get_indirect(ce5buf_ptr, 0);
			end_seqid =  DLRX_FLUSH_MSG_flush_end_seqid_get_indirect(ce5buf_ptr, 0);
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
	} else {
		unsigned int msg_type;
		unsigned int msg_len;

		msg_type = DLRX_IND_MSG_msg_type_get_indirect(ce5buf_ptr, 0);
		msg_len = DLRX_CFG_CTXT_CE5DES_msg_len_get_indirect(DLRX_CFG_CTXT_CE5DES_BASE, 0);

		/*Increment message mib for CPU_CE5 */
		msg_mib_inc(HTT_RX_FLUSH_MSG_WLAN);

		/*call driver API to send message to wlan driver */
		ppa_dl_dre_wlan_msg_send(msg_type, (unsigned int)ce5buf_ptr, msg_len, 0);
	}
}

