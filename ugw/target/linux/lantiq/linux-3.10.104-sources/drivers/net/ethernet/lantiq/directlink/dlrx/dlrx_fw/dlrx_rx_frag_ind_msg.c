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
#include "../include/dlrx_fw_internal_def.h"
#include "../include/dlrx_fw_data_structure_macro.h"
#include "../include/dlrx_fw_data_structure.h"
#include "../include/dlrx_dre_api.h"

void dlrx_rx_frag_ind_msg_process(unsigned int *ce5buf_ptr);

extern void msg_mib_inc(unsigned int msg_type);
extern unsigned int peer_vld_check(unsigned int peer_id);
extern void dlrx_playout_process(unsigned int ce5_buf_ptr);
extern void ro_list_reset(unsigned int peer);
extern int ppa_dl_dre_wlan_msg_send(unsigned int msg_type, unsigned int msg_ptr, unsigned int msg_len, unsigned int flags);

/*************************************************************************
// Module:          dlrx_rx_frag_ind_msg_process
// Description:     RX Fragment Indication Message Processing.
//                  If peer is valid and acc is enabled, reset this peer;
//                  pass this message to WLAN driver
// Parameters:      ce5buf_ptr
// Return value :   None
// Functions called by this module:
//                  msg_mib_inc()
//                  peer_vld_check()
//                  ro_list_reset()
// Notes        :   Check the notes of functions called for
//                  complete list to be set in the context.
*************************************************************************/

void dlrx_rx_frag_ind_msg_process(unsigned int *ce5buf_ptr)
{
	unsigned int peer_id, peer_vld, acc_dis, vap, sec_type, temp_acc_dis;
	unsigned int peer;
	unsigned int rxpb_ptr_read_index;
	unsigned int msg_type;
	unsigned int msg_len;

	/*Increment message mib for RX Fragment Indication Message */
	msg_mib_inc(HTT_RX_FRAG_IND_MSG);

	peer_id = DLRX_FRAG_IND_MSG_peer_id_get_indirect(ce5buf_ptr, 0);

	/*peer_vld is set if peer_id is within valid range and valid */
	peer_vld = peer_vld_check(peer_id);

	/*peer, acc_dis and vap are set by peer_vld_check() */
	/*When peer_vid !=0, acc_dis is not correct value. */
	acc_dis = DLRX_CTXT_MSG_acc_dis_get_indirect(DLRX_CTXT_MSG_BASE, 0);

	if (peer_vld && (!acc_dis)) {
		peer    = DLRX_CTXT_MSG_peer_get_indirect(DLRX_CTXT_MSG_BASE, 0);
		/*Set acc_dis for this peer */
		ppa_dl_dre_vapinfo_from_peer(peer, &vap, &sec_type, &temp_acc_dis);
		ppa_dl_dre_vapinfo_set(peer, vap, sec_type, 1);
		DLRX_CTXT_MSG_acc_dis_set_indirect(DLRX_CTXT_MSG_BASE, 0, 1);

		/*Scan RO_mainlist and RO_linklist of all TID and seqid of this peer. */
		/*Free all valid packet buffer pointer used. Free used RO_linklist entry. */
		ro_list_reset(peer);

	}

	rxpb_ptr_read_index = DLRX_CFG_CTXT_RXPB_PTR_RING_rxpb_ptr_read_index_get_indirect((unsigned int *)UNCACHE_ADDR(DLRX_CFG_CTXT_RXPB_PTR_RING_BASE), 0);

	/*Write rxpb_ptr_read_index to the end of message */
	DLRX_FRAG_IND_MSG_rxpb_ptr_read_index_set_indirect(ce5buf_ptr, 0, rxpb_ptr_read_index);

	/*Increment rxpb_ptr_read_index and check for wraparound */
	/*Note: number of msdu is always 1 for RX Fragment Indication Message */
	/*  rxpb_ptr_read_index = (rxpb_ptr_read_index + 1) % GET_NUM_RXPB_PTR_RING; */

	/* DLRX_CFG_CTXT_RXPB_PTR_RING_rxpb_ptr_read_index_set_indirect((unsigned int*)UNCACHE_ADDR(DLRX_CFG_CTXT_RXPB_PTR_RING_BASE), 0, rxpb_ptr_read_index); */

	msg_type = DLRX_IND_MSG_msg_type_get_indirect(ce5buf_ptr, 0);
	msg_len = DLRX_CFG_CTXT_CE5DES_msg_len_get_indirect(DLRX_CFG_CTXT_CE5DES_BASE, 0);

	/*call driver API to send message to wlan driver */
	ppa_dl_dre_wlan_msg_send(msg_type, (unsigned int)ce5buf_ptr, msg_len, 0);

}
