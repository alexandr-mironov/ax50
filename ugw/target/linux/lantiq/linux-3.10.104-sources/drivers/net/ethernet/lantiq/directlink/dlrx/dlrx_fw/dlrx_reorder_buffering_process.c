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
#include <asm/addrspace.h>
#include <linux/kernel.h>
#include "../include/dlrx_fw_def.h"
#include "../include/dlrx_fw_data_structure.h"
#include "../include/dlrx_fw_data_structure_macro.h"
#include "../include/dlrx_fw_internal_def.h"
#include "../include/dlrx_dre_api.h"
#include "../include/dlrx_inl_fns.h"
#include "../include/dlrx_fw_macro_adaptor.h"

extern int ppa_dl_dre_wlan_pkt_send(unsigned int rxpb_ptr, unsigned int data_len, unsigned int pktstatus,
				    unsigned int msg_ptr, unsigned int vap_id, unsigned int flags);

/********************************************************************************
//      Function name: dlrx_reorder_buffering_process
//      Description  : Perform the dlrx reorder buffering process
//      Parameters   : ce5_buf_ptr : Message buffer pointer
//      Return value : None
//      Functions called by this module:
//                     dlrx_get_ind_msg_mpdu_data_offset
//                     dlrx_get_cfg_offset_atten_in_dwords
//                     dlrx_get_current_rxpb_buf_ptr
//                     dlrx_get_fw_rx_desc_byte_data
//                     mib_update_mpdu_msdu_counters
//                     mib_update_vap_dlrx_data
//                     dlrx_add_outgoing_data_to_rxpb_buffer
//                     ro_list_add_data
//                     rxpb_write_free_buffer_to_rxpb_ptr_ring
//
//      Notes        : Make sure the peer, ext_tid, peer_vld,rxpb_ptr_read_index
//                     cfg_num_rxpb_ptr_ring, is set to the correct value in the
//                     context structure before calling this function. Check the
//                     notes of functions called for complete list to be set
//                     in the context.
********************************************************************************/
void dlrx_reorder_buffering_process(unsigned int *ce5_buf_ptr)
{
	/* Step 6 */
	unsigned int msdu_index = 0;  /* This should to initialized to zero here */
	/* Step 7 */
	unsigned int msdu_mpdu_index = 0; /* This should to initialized to zero here */
	unsigned int mpdu_data_offset, mpdu_range_index, mpdu_range_num;
	unsigned int peer, ext_tid, seq_id = 0, peer_vld;
	unsigned int rxpb_ptr_read_index;
	unsigned int *base_ptr, *rxpb_buf_ptr = NULL;
	unsigned int total_msdus, last_msdu = 0, msdu_number_debug_count = 0;
	unsigned int msdu_chained = 0;
	unsigned int seq_id_mask;

	mpdu_data_offset = dlrx_get_ind_msg_mpdu_data_offset(ce5_buf_ptr);

	mpdu_range_num = DLRX_IND_MSG_mpdu_ranges_num_get_indirect(ce5_buf_ptr, 0);
	peer = DLRX_CTXT_MSG_peer_get_indirect(DLRX_CTXT_MSG_BASE, 0);
	ext_tid = DLRX_CTXT_MSG_ext_tid_get_indirect(DLRX_CTXT_MSG_BASE, 0);
	peer_vld = DLRX_CTXT_MSG_peer_vld_get_indirect(DLRX_CTXT_MSG_BASE, 0);
	rxpb_ptr_read_index = DLRX_CFG_CTXT_RXPB_PTR_RING_rxpb_ptr_read_index_get_indirect((unsigned int *)UNCACHE_ADDR(DLRX_CFG_CTXT_RXPB_PTR_RING_BASE), 0);

	seq_id_mask = dlrx_get_seq_mask(peer, ext_tid);

	DLRX_CTXT_MSG_msdu_index_set_indirect(DLRX_CTXT_MSG_BASE, 0, msdu_index);
	total_msdus = DLRX_IND_MSG_fw_rx_desc_byte_num_get_indirect(ce5_buf_ptr, 0);

	base_ptr = (unsigned int *)((uint8_t *)ce5_buf_ptr + sizeof(dlrx_ind_msg_t) + mpdu_data_offset);

	/* Step 5 , step 30 and step 31 */
	for (mpdu_range_index = 0; mpdu_range_index < mpdu_range_num; mpdu_range_index++) {
		unsigned int *temp_ptr;
		unsigned int mpdu_status;
		unsigned int mpdu_index;

		unsigned int mpdu_cnt = 0;

		/* Step 9 : Get MPDU status and MPDU count */
		temp_ptr = base_ptr + mpdu_range_index;
		mpdu_cnt = CTXT_MPDU_mpdu_cnt_mpdu_range0_get_indirect(temp_ptr, 0);
		mpdu_status = CTXT_MPDU_mpdu_status_mpdu_range0_get_indirect(temp_ptr, 0);

		DLRX_CTXT_MSG_mpdu_cnt_set_indirect(DLRX_CTXT_MSG_BASE, 0, mpdu_cnt);
		DLRX_CTXT_MSG_mpdu_status_set_indirect(DLRX_CTXT_MSG_BASE, 0, mpdu_status);

		if ((mpdu_status == MPDU_STATUS_SUCCESS) && peer) {
			unsigned int peer_id;
			peer_id = DLRX_IND_MSG_peer_id_get_indirect(ce5_buf_ptr, 0);
			ppa_dl_dre_peer_act_fn(peer_id);
		}
		/* Step 8 , Step 28 and Step 29 */
		for (mpdu_index = 0; mpdu_index < mpdu_cnt; mpdu_index++) {
			unsigned int msdu_length = 0;
			unsigned int first_msdu = 0;
			unsigned int msdu_chain_num;

			msdu_mpdu_index = 0;  /* Reset msdu_mpdu_index (step 28) */
			msdu_chain_num = 0;
			msdu_chained = 0;

			while (1) {
				rxpb_buf_ptr = (unsigned int *)(dlrx_get_current_rxpb_buf_ptr());
				rxpb_buf_ptr = (unsigned int *)CACHE_ADDR((unsigned int)rxpb_buf_ptr);
				if (DLRX_CFG_GLOBAL_dlrx_enable_get_indirect(DLRX_CFG_GLOBAL_BASE, 0) == 0xf)
					pr_err("ce5buf 0x%x RXPB ADD 0x%x  mpdu_status : 0x%x  mpdu_cnt :0x%x    peer : 0x%x  peer_id : 0x%x  peer_vld:0x%x  \n",
					       (unsigned int)ce5_buf_ptr, (unsigned int)rxpb_buf_ptr,
						   mpdu_status, mpdu_cnt, peer,
						   DLRX_IND_MSG_peer_id_get_indirect(ce5_buf_ptr, 0),
						   peer_vld);

				dre_dma_unmap((unsigned int)rxpb_buf_ptr, MAX_INV_HEADER_LEN);

				if (msdu_chain_num == 0) {
					unsigned int time_out_index;

					for (time_out_index = 0; time_out_index < 0x8000000; time_out_index++)
						if (DLRX_RXPB_HDR_msdu_load_status_get_indirect(rxpb_buf_ptr, CFG_OFFSET_ATTEN_IN_DWORDS))
							break;

					if (time_out_index) {
						unsigned int rxpb_ptr_write_index;

						rxpb_ptr_write_index = DLRX_CFG_CTXT_RXPB_PTR_RING_rxpb_ptr_write_index_get_indirect((unsigned int *)UNCACHE_ADDR(DLRX_CFG_CTXT_RXPB_PTR_RING_BASE), 0);
						pr_err("Time out index value: %u  ce5_buf_ptr: 0x%x rxpb_buf_ptr: 0x%x (Read_idx *4): 0x%x (write_idx *4): 0x%x\n", \
						       time_out_index, (unsigned int)ce5_buf_ptr, (unsigned int)rxpb_buf_ptr, (rxpb_ptr_read_index * 4), (rxpb_ptr_write_index * 4));
						global_debug_flag = 1;
#if defined(DRE_DBG_PRINT_ENABLE) && DRE_DBG_PRINT_ENABLE

						dlrx_generate_debug(1);
#endif
						return;
					}

					/*clear msdu_done */
					DLRX_RXPB_HDR_msdu_load_status_clear_indirect(rxpb_buf_ptr, CFG_OFFSET_ATTEN_IN_DWORDS);

					msdu_length = DLRX_RXPB_HDR_msdu_len_get_indirect(rxpb_buf_ptr, CFG_OFFSET_ATTEN_IN_DWORDS);
					first_msdu = DLRX_RXPB_HDR_first_msdu_get_indirect(rxpb_buf_ptr, CFG_OFFSET_ATTEN_IN_DWORDS);
					last_msdu = DLRX_RXPB_HDR_last_msdu_get_indirect(rxpb_buf_ptr, CFG_OFFSET_ATTEN_IN_DWORDS);
					msdu_chain_num = DLRX_RXPB_HDR_msdu_chain_num_get_indirect(rxpb_buf_ptr, CFG_OFFSET_ATTEN_IN_DWORDS);

					if (msdu_chain_num) {
						msdu_number_debug_count++;
						msdu_chain_num++;
						/* TODO: Add code to count this status in the MIB */
						mpdu_status = MSDU_STATUS_CHAIN_MSDU_DROP;
						DLRX_CTXT_MSG_mpdu_status_set_indirect(DLRX_CTXT_MSG_BASE, 0, mpdu_status);
						msdu_chained = 1;

						mib_update_chained_mpdu(0);
					}
				}

				if (first_msdu) {
					unsigned int seq_mask = dlrx_get_seq_mask(peer, ext_tid);
					/* Setting seq_id here as it is valid when it is the first msdu */
					seq_id = (DLRX_RXPB_HDR_seqid_get_indirect(rxpb_buf_ptr, CFG_OFFSET_ATTEN_IN_DWORDS)) & seq_id_mask;   /* Since seqid is between 0-63 , AND with the value of seq_id_mask */
					seq_id &= seq_mask;
					DLRX_CTXT_MSG_seqid_set_indirect(DLRX_CTXT_MSG_BASE, 0, seq_id);

					/* Step 10 */
					mib_update_status_counters(UPDATE_MPDU_MIB, mpdu_status);
					first_msdu = 0;  /* Need to set this to zero here to handle the case where first msdu is a part of a chain */
				}

				DLRX_CTXT_MSG_msdu_mpdu_index_set_indirect(DLRX_CTXT_MSG_BASE, 0, msdu_mpdu_index);

				if ((mpdu_status != MPDU_STATUS_INVALID_PEER) && (mpdu_status != MPDU_STATUS_TKIP_MIB_ERROR) \
				    && peer_vld) {
					if ((mpdu_status == MPDU_STATUS_SUCCESS) && (ext_tid < NUM_TID)) {

						unsigned int discard, forward, inspect;

						dlrx_get_fw_rx_desc_byte_data(ce5_buf_ptr);
						discard = DLRX_CTXT_MSG_discard_get_indirect(DLRX_CTXT_MSG_BASE, 0);
						forward = DLRX_CTXT_MSG_forward_get_indirect(DLRX_CTXT_MSG_BASE, 0);
						inspect = DLRX_CTXT_MSG_inspect_get_indirect(DLRX_CTXT_MSG_BASE, 0);

						mib_update_success_status_counters(UPDATE_MSDU_MIB);
						/* Step 13 to 16 */
						mib_update_vap_dlrx_data(msdu_length, 0);

						if (inspect) {
							/*Step 19 */
							ro_list_prepare_rxpb_buf_and_add_to_ro_list(ce5_buf_ptr, rxpb_buf_ptr, INSPECT_BIT_DATA);
						} else if ((discard && forward) || (!discard && !forward)) {
							/*Step 18 */
							ro_list_prepare_rxpb_buf_and_add_to_ro_list(ce5_buf_ptr, rxpb_buf_ptr, ONE_PMAC_DATA);
						} else if (discard && !forward) {
							/* Not defined in spec flowchart */
							rxpb_write_free_buffer_to_rxpb_ptr_ring(RECYCLE_RXPB_PTR);
							mib_update_chained_mpdu(2);
						} else if (!discard && forward) {
							/* step 17 */
							ro_list_prepare_rxpb_buf_and_add_to_ro_list(ce5_buf_ptr, rxpb_buf_ptr, TWO_PMAC_DATA);
						}
					} else {
						/* Step 11 */
						mib_update_status_counters(UPDATE_MSDU_MIB, mpdu_status);

						/* Step 20 */
						rxpb_write_free_buffer_to_rxpb_ptr_ring(RECYCLE_RXPB_PTR);

						mib_update_chained_mpdu(4);
					}
				} else {
					/* Step 11 */
					mib_update_status_counters(UPDATE_MSDU_MIB, mpdu_status);

					if (!peer_vld) {
						/* Not defined in spec. */
#if 0
						rxpb_write_free_buffer_to_rxpb_ptr_ring(RECYCLE_RXPB_PTR);
						mib_update_chained_mpdu(6);
#else

						if (mpdu_status == MPDU_STATUS_INVALID_PEER) {
							int driver_status;
							unsigned int vap;
							unsigned int flags = 0;
							unsigned int padding_bytes = 0;

							vap = DLRX_CTXT_MSG_vap_get_indirect(DLRX_CTXT_MSG_BASE, 0);

							/* Step 12 here */
							dlrx_add_outgoing_data_to_rxpb_buffer(rxpb_buf_ptr, INSPECT_BIT_DATA);

							if (g_qca_hw == BEELINER_BOARD)
								padding_bytes = DLRX_RXPB_HDR_BEELINER_l3_header_padding_get_indirect((unsigned int *)rxpb_buf_ptr, CFG_OFFSET_ATTEN_IN_DWORDS);

							flags = ((padding_bytes << 16) | 0);   /* Store the padding bytes value in the upper 16 bits for driver usage and last bit to indicate if inspect is 1 or 0 */

							/*call driver API to send packet to wlan dma */
							driver_status = ppa_dl_dre_wlan_pkt_send((unsigned int)rxpb_buf_ptr, msdu_length, mpdu_status, (unsigned int)ce5_buf_ptr, vap, flags);

							if (driver_status == -1) { /*DMA descriptor is full */
								/* Case when DMA descriptor is full */
								mib_update_vap_dlrx_data(msdu_length, DMA_TX_CHANNEL_FULL);
								mib_update_status_counters(0, MSDU_STATUS_ERROR_5_DROP);
							}

							rxpb_write_free_buffer_to_rxpb_ptr_ring(NEW_RXPB_PTR);
						} else {
							rxpb_write_free_buffer_to_rxpb_ptr_ring(RECYCLE_RXPB_PTR);
							mib_update_chained_mpdu(6);
						}

#endif
					} else {
						int driver_status;
						unsigned int vap;
						unsigned int flags = 0;
						unsigned int padding_bytes = 0;

						vap = DLRX_CTXT_MSG_vap_get_indirect(DLRX_CTXT_MSG_BASE, 0);

						/* Step 12 here */
						dlrx_add_outgoing_data_to_rxpb_buffer(rxpb_buf_ptr, INSPECT_BIT_DATA);

						if (g_qca_hw == BEELINER_BOARD)
							padding_bytes = DLRX_RXPB_HDR_BEELINER_l3_header_padding_get_indirect((unsigned int *)rxpb_buf_ptr, CFG_OFFSET_ATTEN_IN_DWORDS);

						flags = ((padding_bytes << 16) | 0);   /* Store the padding bytes value in the upper 16 bits for driver usage and last bit to indicate if inspect is 1 or 0 */

						/*call driver API to send packet to wlan dma */
						driver_status = ppa_dl_dre_wlan_pkt_send((unsigned int)rxpb_buf_ptr, msdu_length, mpdu_status, (unsigned int)ce5_buf_ptr, vap, flags);

						if (driver_status == -1) { /*DMA descriptor is full */
							/* Case when DMA descriptor is full */
							mib_update_vap_dlrx_data(msdu_length, DMA_TX_CHANNEL_FULL);

							if (mpdu_status == MPDU_STATUS_INVALID_PEER)
								mib_update_status_counters(0, MSDU_STATUS_ERROR_5_DROP);

							printk("%s : %d : LTQ11ACOL OFFLOAD - DMA descriptor full: mpdu_status = %d\n", __func__, __LINE__, mpdu_status);
						}

						rxpb_write_free_buffer_to_rxpb_ptr_ring(NEW_RXPB_PTR);
					}
				}

				*(rxpb_buf_ptr - 2) = (unsigned int)ce5_buf_ptr;

				/* Step 24 */
				msdu_index++;
				DLRX_CTXT_MSG_msdu_index_set_indirect(DLRX_CTXT_MSG_BASE, 0, msdu_index);
				/* Step 25 */
				rxpb_ptr_read_index++;
				rxpb_ptr_read_index = (rxpb_ptr_read_index % GET_NUM_RXPB_PTR_RING);    /* Wrap around to zero if max number reached */
				DLRX_CFG_CTXT_RXPB_PTR_RING_rxpb_ptr_read_index_set_indirect((unsigned int *)UNCACHE_ADDR(DLRX_CFG_CTXT_RXPB_PTR_RING_BASE), 0, rxpb_ptr_read_index);

				/* Step 26 */
				if (!msdu_chain_num) {
					msdu_mpdu_index++; /* No need to set context here as it will be set if the loop is continued */
					msdu_number_debug_count++;
				} else {
					msdu_chain_num--;

					if (!msdu_chain_num) { /* Restore back the original MPDU status */
						mpdu_status = CTXT_MPDU_mpdu_status_mpdu_range0_get_indirect(temp_ptr, 0);
						DLRX_CTXT_MSG_mpdu_status_set_indirect(DLRX_CTXT_MSG_BASE, 0, mpdu_status);
					}
				}

				/* Step 27 */
				if (last_msdu == 1) {
					if (msdu_chain_num == 0) { /* Add the number of msdu to the reorder mainlist only if msdu_mpdu_index is not 0. */
						if (msdu_mpdu_index) {
							unsigned int *temp_mainlist_data_ptr;
							/* Update the number of MSDU for this sequence ID : Not defined in new spec */
							temp_mainlist_data_ptr = (unsigned int *)(((dlrx_ro_mainlist_t *)g_cfg_badr_ro_mainlist) + ((peer * NUM_TID) + ext_tid)); /* Offset into the required mainlist entry */
							DLRX_RO_MAINLIST_msdu_num_set_indirect(temp_mainlist_data_ptr, seq_id, (msdu_mpdu_index));   /* Number of MSDU data */
						}

						if (msdu_chained) {
							dre_print("msdu_chained : seq_Id=0x%x  msdu_mpdu_index=0x%x", seq_id, msdu_mpdu_index);
							ro_list_reset_a_tid_seqid(peer, ext_tid, seq_id, RECYCLE_RXPB);
						}

						break;
					}
				}
			}
		}
	}
}

