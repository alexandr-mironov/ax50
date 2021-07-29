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
#include<linux/kernel.h>
#include "../include/dlrx_fw_def.h"
#include "../include/dlrx_fw_data_structure.h"
#include "../include/dlrx_fw_data_structure_macro.h"
#include "../include/dlrx_fw_internal_def.h"
#include "../include/dlrx_inl_fns.h"
#include "../include/dlrx_dre_api.h"

extern int ppa_dl_dre_wlan_pkt_send(unsigned int rxpb_ptr, unsigned int data_len, unsigned int pktstatus,
				    unsigned int msg_ptr, unsigned int vap_id, unsigned int flags);
extern int ppa_dl_dre_ps_send(unsigned int rxpb_ptr, unsigned int data_ptr, unsigned int data_len,
			      unsigned int vap_id);

extern int ppa_dl_dre_gswip_dma_send(unsigned int vap_id, unsigned int rxpb_ptr, unsigned int data_ptr, unsigned int data_len,
				     unsigned int release_flag, unsigned int pmac_hdr_ptr, unsigned int unmap_type);

/******************************************************************************
//      Function name: dlrx_playout_process
//      Description  : Playout process function
//      Parameters   : None
//      Return value : None
//      Functions called by this module:
//                     ro_list_release_data
//      Notes        : Make sure the start_seqid and total_seqid is set to the
//                     correct value in the context structure before calling this
//                     function. Check the notes of functions called for complete
//                     list to be set in the context.
******************************************************************************/

void dlrx_playout_process(unsigned int ce5_buf_ptr)
{
	unsigned int mpdu_index;
	unsigned int start_seq_id;
	unsigned int total_seq_id;
	unsigned int peer = DLRX_CTXT_MSG_peer_get_indirect(DLRX_CTXT_MSG_BASE, 0);
	unsigned int ext_tid = DLRX_CTXT_MSG_ext_tid_get_indirect(DLRX_CTXT_MSG_BASE, 0);
	unsigned int seq_mask = dlrx_get_seq_mask(peer, ext_tid);

	start_seq_id = DLRX_CTXT_MSG_start_seqid_get_indirect(DLRX_CTXT_MSG_BASE, 0);
	total_seq_id = DLRX_CTXT_MSG_total_seqid_get_indirect(DLRX_CTXT_MSG_BASE, 0);
	start_seq_id &= seq_mask;
	/* Step 27 , Step 28 */
	for (mpdu_index = 0; mpdu_index < total_seq_id; mpdu_index++) {
		DLRX_CTXT_MSG_mpdu_index_set_indirect(DLRX_CTXT_MSG_BASE, 0, start_seq_id);
		ro_list_release_data(ce5_buf_ptr);

		start_seq_id++;
		start_seq_id &= seq_mask;   /* Check wrap around condition */
	}
}

/***********************************************************************************
//      Function name: dlrx_send_packet_to_dma_descriptor
//      Description  : Send the packet to corresponding dma descriptor based
//                     on the comditions
//      Parameters   : None
//      Return value : None
//      Functions called by this module:
//                     dlrx_get_interface_data_from_vap
//                     mib_update_vap_dlrx_data
//                     rxpb_write_free_buffer_to_rxpb_ptr_ring
//      Notes        : Make sure the cur_ro_des_ptr and vap is set to the correct value
//                     in the context structure before calling this function. Check
//                     the notes of functions called for complete list to be set
//                     in the context.
************************************************************************************/
void dlrx_send_packet_to_dma_descriptor(unsigned int ce5_buf_ptr)
{
	unsigned int forward, discard, inspect;
	unsigned int *linklist_data_ptr;
	unsigned int vap, vap2int;
	unsigned int msdu_length;
	unsigned int rxpb_buf_ptr, data_ptr;
	int driver_status = -2;
	unsigned int padding_bytes = 0; /* Must initialize to zero */

	linklist_data_ptr = (unsigned int *)DLRX_CFG_CTXT_RO_LINKLIST_cur_ro_des_ptr_get_indirect(DLRX_CFG_CTXT_RO_LINKLIST_BASE, 0);

	forward = DLRX_RO_LINKLIST_fwd_get_indirect(linklist_data_ptr, 0);
	inspect = DLRX_RO_LINKLIST_inspect_get_indirect(linklist_data_ptr, 0);
	discard = DLRX_RO_LINKLIST_discard_get_indirect(linklist_data_ptr, 0);
	vap = DLRX_CTXT_MSG_vap_get_indirect(DLRX_CTXT_MSG_BASE, 0);

	vap2int = dlrx_get_interface_data_from_vap(vap);

	msdu_length = DLRX_RO_LINKLIST_msdu_len_get_indirect(linklist_data_ptr, 0);
	rxpb_buf_ptr = DLRX_RO_LINKLIST_rxpb_ptr_get_indirect(linklist_data_ptr, 0);

	if (g_qca_hw == BEELINER_BOARD)
		padding_bytes = DLRX_RXPB_HDR_BEELINER_l3_header_padding_get_indirect((unsigned int *)rxpb_buf_ptr, CFG_OFFSET_ATTEN_IN_DWORDS);

	data_ptr = (unsigned int)((uint8_t *)rxpb_buf_ptr + GET_RXPKT_DESC_SIZE + padding_bytes);

	if (inspect == 1) { /* Step 12 */
		unsigned int mpdu_status;
		unsigned int *temp_rxpb_ptr;
		unsigned int flags = 0;

		temp_rxpb_ptr = (unsigned int *)rxpb_buf_ptr;
		mpdu_status = ((*temp_rxpb_ptr) >> B_DLRX_RXPB_WLAN_DRV_HDR_mpdu_status);

		dre_dma_unmap((unsigned int)(rxpb_buf_ptr + MAX_INV_HEADER_LEN), HTT_RX_BUF_SIZE - MAX_INV_HEADER_LEN);

		flags = ((padding_bytes << 16) | 1);   /* Store the padding bytes value in the upper 16 bits for driver usage and last bit to indicate if inspect is 1 or 0 */
		/* call driver API to send packet to wlan dma */
		driver_status = ppa_dl_dre_wlan_pkt_send(rxpb_buf_ptr, msdu_length, WLAN_INSPECT_TYPE , ce5_buf_ptr, vap, flags);   /*Step 14 */
		mib_update_vap_wlan_data(msdu_length);
	} else { /* The flow in the else part is not defined in the specification */
		unsigned int pmac_hdr_ptr;
		unsigned int release_bit;
		unsigned int temp_switch = 0;

		if ((discard == 0) && (forward == 1)) {
			release_bit = 0;
			mib_update_vap_forward_data(msdu_length);
			/* call driver API to send packet to gswip dma */
			dre_dma_unmap((unsigned int)(rxpb_buf_ptr + MAX_INV_HEADER_LEN), HTT_RX_BUF_SIZE - MAX_INV_HEADER_LEN);
		} else
			release_bit = 1;

		if (forward == 1) {
			pmac_hdr_ptr = (unsigned int)(((uint8_t *)data_ptr) - 4);

			driver_status = ppa_dl_dre_gswip_dma_send(vap, rxpb_buf_ptr, data_ptr, msdu_length, release_bit, pmac_hdr_ptr, 1);
			mib_update_vap_gswip_data(msdu_length);
			release_bit = 1;
			temp_switch = 1;
		}

		if (discard == 0) {
#if (defined (DLRX_GRX330_BOARD_CFG) && (DLRX_GRX330_BOARD_CFG == 1))
			if (vap2int == 15) {
				if (release_bit == 1)
					dre_dma_unmap((unsigned int)(rxpb_buf_ptr + MAX_INV_HEADER_LEN), HTT_RX_BUF_SIZE - MAX_INV_HEADER_LEN);

				/* call driver API to send packet to protocol stack dma */

				driver_status = ppa_dl_dre_ps_send(rxpb_buf_ptr, data_ptr, msdu_length, vap);
				mib_update_vap_protocol_stack_data(msdu_length);
			} else
#endif
			{
				if (temp_switch == 1)
					pmac_hdr_ptr = (unsigned int)(((uint8_t *)data_ptr) - 8);
				else
					pmac_hdr_ptr = (unsigned int)(((uint8_t *)data_ptr) - 4);
				/* call driver API to send packet to gswip dma */
				if (forward == 0)
					driver_status = ppa_dl_dre_gswip_dma_send(vap, rxpb_buf_ptr, data_ptr, msdu_length, release_bit, pmac_hdr_ptr , 0);
				else /* already unmapped */
					driver_status = ppa_dl_dre_gswip_dma_send(vap, rxpb_buf_ptr, data_ptr, msdu_length, release_bit, pmac_hdr_ptr, 1);

				mib_update_vap_gswip_data(msdu_length);
			}
		}
	}

	if (driver_status == -1) {   /* Step 13, Step 17, Step 19, Step 21 */
		/* update drop mib counter */
		mib_update_vap_dlrx_data(msdu_length, DMA_TX_CHANNEL_FULL);
	}

	/* Step 24 */
	rxpb_write_free_buffer_to_rxpb_ptr_ring(NEW_RXPB_PTR);
}

