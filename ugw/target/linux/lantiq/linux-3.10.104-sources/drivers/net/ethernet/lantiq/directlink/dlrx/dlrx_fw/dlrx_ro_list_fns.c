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
#include <linux/kernel.h>
#include <linux/module.h>

#include "../include/dlrx_fw_def.h"
#include "../include/dlrx_fw_data_structure.h"
#include "../include/dlrx_fw_data_structure_macro.h"
#include "../include/dlrx_fw_internal_def.h"
#include "../include/dlrx_dre_api.h"
#include "../include/dlrx_fw_macro_adaptor.h"

/**********************************************************************************
//      Function name: ro_list_add_data
//      Description  : Add the data to the ro main and link list
//      Parameters   : ce5_buf_ptr : Message buffer pointer
//                     rxpb_buf_ptr : packet buffer pointer  ( Virtual address)
//      Return value : None
//      Functions called by this module:
//                     dlrx_get_cfg_offset_atten_in_dwords
//                     ro_linklist_get_free_ro_desc
//
//      Notes        : Make sure the cfg_badr_ro_linklist, peer, seq_id, ext_tid,
//                     msdu_mpdu_index, prev_ro_des_index, discard, forward and inspect
//                     data is set to the correct value in the context structure before
//                     calling this function. Check the notes of functions called
//                     for complete list to be set in the context.
**********************************************************************************/
unsigned int ro_list_add_data(unsigned int *ce5_buf_ptr, unsigned int *rxpb_buf_ptr)
{
	unsigned int temp_cur_ro_des_index;
	unsigned int *temp_linklist_data_ptr;
	unsigned int *temp_mainlist_data_ptr;
	unsigned int temp_prev_ro_des_index;
	unsigned int peer;
	unsigned int seq_id;
	unsigned int msdu_mpdu_index;
	unsigned int ext_tid;
	unsigned int msdu_length;
	unsigned int pn_dw0;
	unsigned int pn_dw1;
	unsigned int pn_dw2;
	unsigned int pn_dw3;
	unsigned int discard;
	unsigned int forward;
	unsigned int inspect;
	unsigned int mcast_bcast;
	unsigned int sec_type;

	/*step 21 in Page no. 23 of CPU_11AC_ACC_DES.pdf*/
	temp_cur_ro_des_index = ro_linklist_get_free_ro_desc();

	if (temp_cur_ro_des_index == NULL_PTR)
		return 0;

	DLRX_CFG_CTXT_RO_LINKLIST_cur_ro_des_index_set_indirect(DLRX_CFG_CTXT_RO_LINKLIST_BASE, 0, temp_cur_ro_des_index);
	sec_type = DLRX_CTXT_MSG_sec_type_get_indirect(DLRX_CTXT_MSG_BASE, 0);
	temp_linklist_data_ptr = (unsigned int *)((dlrx_ro_linklist_t *)g_cfg_badr_ro_linklist + temp_cur_ro_des_index);

	if (sec_type != SEC_TYPE_DISABLE) { /* Step 5, In spec present in wrong place should be between step 7 and 8*/
		pn_dw0      = DLRX_RXPB_HDR_pn_31_0_get_indirect(rxpb_buf_ptr, CFG_OFFSET_ATTEN_IN_DWORDS);
		pn_dw1      = (DLRX_RXPB_HDR_pn_63_48_get_indirect(rxpb_buf_ptr, CFG_OFFSET_ATTEN_IN_DWORDS) << B_DLRX_RXPB_HDR_pn_63_48) | \
			      DLRX_RXPB_HDR_pn_47_32_get_indirect(rxpb_buf_ptr, CFG_OFFSET_ATTEN_IN_DWORDS);
		pn_dw2      = DLRX_RXPB_HDR_pn_95_64_get_indirect(rxpb_buf_ptr, CFG_OFFSET_ATTEN_IN_DWORDS);
		pn_dw3      = DLRX_RXPB_HDR_pn_127_96_get_indirect(rxpb_buf_ptr, CFG_OFFSET_ATTEN_IN_DWORDS);
		DLRX_RO_LINKLIST_pn_dw0_set_indirect(temp_linklist_data_ptr, 0, pn_dw0);
		DLRX_RO_LINKLIST_pn_dw1_set_indirect(temp_linklist_data_ptr, 0, pn_dw1);
		DLRX_RO_LINKLIST_pn_dw2_set_indirect(temp_linklist_data_ptr, 0, pn_dw2);
		DLRX_RO_LINKLIST_pn_dw3_set_indirect(temp_linklist_data_ptr, 0, pn_dw3);
	}

	/* TODO: To optimize further*/
	msdu_length = DLRX_RXPB_HDR_msdu_len_get_indirect(rxpb_buf_ptr, CFG_OFFSET_ATTEN_IN_DWORDS);
	mcast_bcast = DLRX_RXPB_HDR_mcast_bcast_get_indirect(rxpb_buf_ptr, CFG_OFFSET_ATTEN_IN_DWORDS);
	discard     = DLRX_CTXT_MSG_discard_get_indirect(DLRX_CTXT_MSG_BASE, 0);

	forward     = DLRX_CTXT_MSG_forward_get_indirect(DLRX_CTXT_MSG_BASE, 0);
	inspect     = DLRX_CTXT_MSG_inspect_get_indirect(DLRX_CTXT_MSG_BASE, 0);
	DLRX_RO_LINKLIST_discard_set_indirect(temp_linklist_data_ptr, 0, discard);
	DLRX_RO_LINKLIST_fwd_set_indirect(temp_linklist_data_ptr, 0, forward);
	DLRX_RO_LINKLIST_inspect_set_indirect(temp_linklist_data_ptr, 0, inspect);
	DLRX_RO_LINKLIST_msdu_len_set_indirect(temp_linklist_data_ptr, 0, msdu_length);
	DLRX_RO_LINKLIST_rxpb_ptr_set_indirect(temp_linklist_data_ptr, 0, (unsigned int)rxpb_buf_ptr);
	DLRX_RO_LINKLIST_next_ptr_set_indirect(temp_linklist_data_ptr, 0, NULL_PTR);

	/* TODO: Change all the fixed values to be read in higher level function and passed as a parameter to this function*/
	peer = DLRX_CTXT_MSG_peer_get_indirect(DLRX_CTXT_MSG_BASE, 0);
	seq_id = DLRX_CTXT_MSG_seqid_get_indirect(DLRX_CTXT_MSG_BASE, 0);
	ext_tid = DLRX_CTXT_MSG_ext_tid_get_indirect(DLRX_CTXT_MSG_BASE, 0);
	msdu_mpdu_index = DLRX_CTXT_MSG_msdu_mpdu_index_get_indirect(DLRX_CTXT_MSG_BASE, 0);

	if (msdu_mpdu_index == 0) { /* Step 22 in Page no. 23 of CPU_11AC_ACC_DES.pdf*/
		unsigned int original_1st_des_idx;

		temp_mainlist_data_ptr = (unsigned int *)(((dlrx_ro_mainlist_t *)g_cfg_badr_ro_mainlist) + ((peer * NUM_TID) + ext_tid)); /* Offset into the required mainlist entry*/

		original_1st_des_idx = DLRX_RO_MAINLIST_first_ptr_get_indirect(temp_mainlist_data_ptr, seq_id);  /* First pointer data*/

		if (original_1st_des_idx != NULL_PTR) {
			dre_print("original link list not empty temp_mainlist_data_ptr=0x%x original_1st_des_idx=0x%x", temp_mainlist_data_ptr, original_1st_des_idx);
			ro_list_reset_a_tid_seqid(peer, ext_tid, seq_id, RECYCLE_RXPB);
		}

		DLRX_RO_MAINLIST_first_ptr_set_indirect(temp_mainlist_data_ptr, seq_id, temp_cur_ro_des_index);    /* First pointer data*/
		DLRX_RO_MAINLIST_mcast_bcast_set_indirect(temp_mainlist_data_ptr, seq_id, mcast_bcast);    /* mcast bcast data*/
		DLRX_CFG_CTXT_RO_LINKLIST_prev_ro_des_index_set_indirect(DLRX_CFG_CTXT_RO_LINKLIST_BASE, 0, temp_cur_ro_des_index);
	} else { /* Step 23 in Page no. 23 of CPU_11AC_ACC_DES.pdf*/
		temp_prev_ro_des_index = DLRX_CFG_CTXT_RO_LINKLIST_prev_ro_des_index_get_indirect(DLRX_CFG_CTXT_RO_LINKLIST_BASE, 0);
		temp_linklist_data_ptr = (unsigned int *)((dlrx_ro_linklist_t *)g_cfg_badr_ro_linklist + temp_prev_ro_des_index);  /* Offset into the required linklist entry*/

		DLRX_RO_LINKLIST_next_ptr_set_indirect(temp_linklist_data_ptr, 0, temp_cur_ro_des_index);
		DLRX_CFG_CTXT_RO_LINKLIST_prev_ro_des_index_set_indirect(DLRX_CFG_CTXT_RO_LINKLIST_BASE, 0, temp_cur_ro_des_index);
	}

	return 1;
}

/**********************************************************************************
//      Function name: ro_linklist_get_free_ro_desc
//      Description  : Get a free reorder linklist pointer
//      Parameters   : None
//      Functions called by this module:
//                     None
//      Return value : Free reorder linklist pointer
//      Notes        : Make sure the ro_des_free_head_index, free_num_ro_linklist,
//                     cfg_badr_ro_linklist data is set to the correct value in the
//                     context structure before calling this function. Check the notes
//                     of functions called for complete list to be set in the context.
**********************************************************************************/
unsigned int ro_linklist_get_free_ro_desc(void)
{
	unsigned int ro_des_free_index;
	unsigned int *temp_linklist_data_ptr;
	unsigned int temp_next_free_head_index;
	unsigned int free_num_ro_linklist;

	free_num_ro_linklist = DLRX_CFG_CTXT_RO_LINKLIST_free_num_ro_linklist_get_indirect(DLRX_CFG_CTXT_RO_LINKLIST_BASE, 0);

	if (free_num_ro_linklist == 0) {
		return NULL_PTR;   /* No free reorder descriptor*/
	}

	ro_des_free_index = DLRX_CFG_CTXT_RO_LINKLIST_ro_des_free_head_index_get_indirect(DLRX_CFG_CTXT_RO_LINKLIST_BASE, 0);

	temp_linklist_data_ptr = (unsigned int *)((dlrx_ro_linklist_t *)g_cfg_badr_ro_linklist + ro_des_free_index);  /* Offset into the required linklist entry*/

	temp_next_free_head_index = DLRX_RO_LINKLIST_next_ptr_get_indirect(temp_linklist_data_ptr, 0);
	DLRX_CFG_CTXT_RO_LINKLIST_ro_des_free_head_index_set_indirect(DLRX_CFG_CTXT_RO_LINKLIST_BASE, 0, temp_next_free_head_index);

	/* Reduce the number of free linklist*/
	free_num_ro_linklist--;
	DLRX_CFG_CTXT_RO_LINKLIST_free_num_ro_linklist_set_indirect(DLRX_CFG_CTXT_RO_LINKLIST_BASE, 0, free_num_ro_linklist);

	return ro_des_free_index;
}

/**************************************************************************************
//      Function name: ro_list_release_data
//      Description  : Release data from the RO link list
//      Parameters   : None
//      Return value : None
//      Functions called by this module:
//                     dlrx_is_pn_check_fail
//                     dlrx_send_packet_to_dma_descriptor
//                     dlrx_copy_last_pn_to_mainlist
//                     ro_linklist_return_free_ptr
//      Notes        : Make sure the peer, ext_tid, mpdu_index, cfg_badr_ro_mainlist,
//                     cfg_badr_ro_linklist , sec_type and pn_pass
//                     is set to the correct value in the context structure before
//                     calling this function. Check the notes of functions called
//                     for complete list to be set in the context.
**************************************************************************************/
void ro_list_release_data(unsigned int ce5_buf_ptr)
{
	unsigned int *temp_mainlist_data_ptr = 0;
	unsigned int *temp_linklist_data_ptr = 0;
	unsigned int temp_cur_ro_desc_index = 0;
	unsigned int mpdu_index;
	unsigned int first_msdu = 1;    /* Step 1*/
	unsigned int msdu_length;
	unsigned int sec_type;
	unsigned int next_ptr_index_to_process = NULL_PTR;

	mpdu_index = DLRX_CTXT_MSG_mpdu_index_get_indirect(DLRX_CTXT_MSG_BASE, 0);

	while (1) {
		/* Step 2*/
		if (first_msdu) {
			unsigned int peer;
			unsigned int ext_tid;

			peer = DLRX_CTXT_MSG_peer_get_indirect(DLRX_CTXT_MSG_BASE, 0);
			ext_tid = DLRX_CTXT_MSG_ext_tid_get_indirect(DLRX_CTXT_MSG_BASE, 0);
			temp_mainlist_data_ptr = (unsigned int *)(((dlrx_ro_mainlist_t *)g_cfg_badr_ro_mainlist) + ((peer * NUM_TID) + ext_tid)); /* Offset into the required mainlist entry*/
			temp_cur_ro_desc_index = DLRX_RO_MAINLIST_first_ptr_get_indirect(temp_mainlist_data_ptr, mpdu_index);
			DLRX_CFG_CTXT_RO_MAINLIST_ro_mainlist_ptr_set_indirect(DLRX_CFG_CTXT_RO_MAINLIST_BASE, 0, (unsigned int)temp_mainlist_data_ptr);
		} else /* Step 3*/
			temp_cur_ro_desc_index = next_ptr_index_to_process;

		/* Step 4*/
		if (temp_cur_ro_desc_index == NULL_PTR)  /* if current ro descriptor pointer in NULL*/
			break;

		DLRX_CFG_CTXT_RO_LINKLIST_cur_ro_des_index_set_indirect(DLRX_CFG_CTXT_RO_LINKLIST_BASE, 0, temp_cur_ro_desc_index);

		temp_linklist_data_ptr = (unsigned int *)((dlrx_ro_linklist_t *)g_cfg_badr_ro_linklist + temp_cur_ro_desc_index);
		DLRX_CFG_CTXT_RO_LINKLIST_cur_ro_des_ptr_set_indirect(DLRX_CFG_CTXT_RO_LINKLIST_BASE, 0, (unsigned int)temp_linklist_data_ptr);

		/* TODO: Change all the fixed values to be read in higher level function and passed as a parameter to this function*/
		sec_type = DLRX_CTXT_MSG_sec_type_get_indirect(DLRX_CTXT_MSG_BASE, 0);
		msdu_length = DLRX_RO_LINKLIST_msdu_len_get_indirect(temp_linklist_data_ptr, 0);

		if (first_msdu) {
			if (sec_type == SEC_TYPE_DISABLE) { /* Step 5, In spec present in wrong place should be between step 7 and 8*/
				DLRX_CTXT_MSG_pn_pass_set_indirect(DLRX_CTXT_MSG_BASE, 0, 1);
				/* Call function to step 12*/
				dlrx_send_packet_to_dma_descriptor(ce5_buf_ptr);
			} else {
				if (dlrx_is_pn_check_fail()) {   /* Step 8*/
					DLRX_CTXT_MSG_pn_pass_set_indirect(DLRX_CTXT_MSG_BASE, 0, 0);
					/* Step 23*/
					mib_update_vap_dlrx_data(msdu_length, WRONG_PN_SEQUENCE);
					/* Step 24*/
					rxpb_write_free_buffer_to_rxpb_ptr_ring(RECYCLE_LL_RXPB_PTR);
				} else {
					unsigned int mcast_bcast;

					mcast_bcast = DLRX_RO_MAINLIST_mcast_bcast_get_indirect(temp_mainlist_data_ptr, mpdu_index);;

					if (mcast_bcast == 0) {
						unsigned int pn_last_bit;

						/*Unicast*/
						pn_last_bit = (DLRX_RO_LINKLIST_pn_dw0_get_indirect(temp_linklist_data_ptr, 0) & 0x01);

						if ((sec_type == SEC_TYPE_PN_48) || \
						    ((sec_type == SEC_TYPE_PN_128_EVEN)  && (!pn_last_bit)) || \
						    ((sec_type == SEC_TYPE_PN_128_ODD)  && pn_last_bit)) {    /* Step 9 and step 10*/
							/* step 11*/
							DLRX_CTXT_MSG_pn_pass_set_indirect(DLRX_CTXT_MSG_BASE, 0, 1);
							dlrx_copy_last_pn_to_mainlist();
							/* call function to step 12*/
							dlrx_send_packet_to_dma_descriptor(ce5_buf_ptr);
						} else {
							DLRX_CTXT_MSG_pn_pass_set_indirect(DLRX_CTXT_MSG_BASE, 0, 0);
							/* Step 23*/
							mib_update_vap_dlrx_data(msdu_length, WRONG_PN_SEQUENCE);
							/* Step 24*/
							rxpb_write_free_buffer_to_rxpb_ptr_ring(RECYCLE_LL_RXPB_PTR);
						}
					} else { /* Not defined in spec*/
						DLRX_CTXT_MSG_pn_pass_set_indirect(DLRX_CTXT_MSG_BASE, 0, 1);
						dlrx_copy_last_pn_to_mainlist();
						/* call function to step 12*/
						dlrx_send_packet_to_dma_descriptor(ce5_buf_ptr);
					}
				}
			}
		} else {
			/* Step 6*/
			if (DLRX_CTXT_MSG_pn_pass_get_indirect(DLRX_CTXT_MSG_BASE, 0)) {
				/* Call function to step 12*/
				dlrx_send_packet_to_dma_descriptor(ce5_buf_ptr);
			} else { /* step 7*/
				/* Step 23*/
				mib_update_vap_dlrx_data(msdu_length, WRONG_PN_SEQUENCE);
				rxpb_write_free_buffer_to_rxpb_ptr_ring(RECYCLE_LL_RXPB_PTR);
			}
		}

		/* Step 25*/
		next_ptr_index_to_process = ro_linklist_return_free_ptr(temp_cur_ro_desc_index);
		/* Add cur_ro_desc_index as prev_ro_des_index in cfg ctxt for debug purposes*/
		DLRX_CFG_CTXT_RO_LINKLIST_prev_ro_des_index_set_indirect(DLRX_CFG_CTXT_RO_LINKLIST_BASE, 0, temp_cur_ro_desc_index);
		/* Step 3*/
		first_msdu = 0;
	}

	/* Step 26*/
	DLRX_RO_MAINLIST_first_ptr_set_indirect(temp_mainlist_data_ptr, mpdu_index, NULL_PTR);
	/* Not defined in spec.*/
	DLRX_RO_MAINLIST_msdu_num_set_indirect(temp_mainlist_data_ptr, mpdu_index, 0);    /* Reset the number of MSDU data*/
	DLRX_RO_MAINLIST_mcast_bcast_set_indirect(temp_mainlist_data_ptr, mpdu_index, 0);    /* Reset the mcast bcast data*/
}

/*******************************************************************************
//      Function name: ro_linklist_return_free_ptr
//      Description  : Free a reorder linklist pointer
//      Parameters   : ro_des_free_ptr - Free pointer to be released
//      Return value : Next free pointer to process
//      Functions called by this module:
//                     None
//      Notes        : 1. Make sure the ro_des_free_tail_index free_num_ro_linklist and
//                     cfg_badr_ro_linklist is set to the correct value in the context
//                     structure before calling this function. Check the notes of functions
//                     called for complete list to be set in the context.
//                    2. The pointer to be freed is added as the head in this function to increase the cache hits.
//                        The spec however defines the pointer to be freed to be added to the tail
*******************************************************************************/
unsigned int ro_linklist_return_free_ptr(unsigned int ro_des_free_ptr)
{
	unsigned int temp_free_head_index;
	unsigned int *temp_linklist_data_ptr;
	unsigned int free_num_ro_linklist;
	unsigned int next_ptr_index_to_process;

	temp_free_head_index = DLRX_CFG_CTXT_RO_LINKLIST_ro_des_free_head_index_get_indirect(DLRX_CFG_CTXT_RO_LINKLIST_BASE, 0);
	free_num_ro_linklist = DLRX_CFG_CTXT_RO_LINKLIST_free_num_ro_linklist_get_indirect(DLRX_CFG_CTXT_RO_LINKLIST_BASE, 0);

	temp_linklist_data_ptr = (unsigned int *)((dlrx_ro_linklist_t *)g_cfg_badr_ro_linklist + ro_des_free_ptr);  /* Offset into the required linklist entry*/
	next_ptr_index_to_process = DLRX_RO_LINKLIST_next_ptr_get_indirect(temp_linklist_data_ptr, 0);

	DLRX_RO_LINKLIST_next_ptr_set_indirect(temp_linklist_data_ptr, 0, temp_free_head_index);
	DLRX_CFG_CTXT_RO_LINKLIST_ro_des_free_head_index_set_indirect(DLRX_CFG_CTXT_RO_LINKLIST_BASE, 0, ro_des_free_ptr);

	/* Increase the number of free linklist*/
	free_num_ro_linklist++;
	DLRX_CFG_CTXT_RO_LINKLIST_free_num_ro_linklist_set_indirect(DLRX_CFG_CTXT_RO_LINKLIST_BASE, 0, free_num_ro_linklist);
	return next_ptr_index_to_process;
}

/**************************************************************************************
//      Function name: ro_list_reset
//      Description  : Reset RO_mainlist and RO_linklist for a particular peer.
//                     Scan RO_mainlist and RO_linklist of
//                     all TID and seqid of this peer. Free all valid packet buffer
//                     pointer used. Free used RO_linklist entry.
//      Parameters   : peer
//      Return value : None
//      Functions called by this module:
//                     ro_list_reset_a_tid_seqid
//      Notes        : Check the notes of functions called
//                     for complete list to be set in the context.
**************************************************************************************/
void ro_list_reset(unsigned int peer)
{
	unsigned int ext_tid = 0;
	unsigned int mpdu_index = 0;

	for (ext_tid = 0; ext_tid < NUM_TID; ext_tid++) {
		for (mpdu_index = 0; mpdu_index < NUM_SEQ_ID; mpdu_index++) {
			dre_print("ro_list_reset  mpdu_index=0x%x", mpdu_index);
			ro_list_reset_a_tid_seqid(peer, ext_tid, mpdu_index, RECYCLE_RXPB);
		}
	}

}

/**************************************************************************************
//      Function name: ro_list_reset_a_tid_seqid
//      Description  : Reset RO_mainlist and RO_linklist for a particular
//                     ext_tid and mpdu_index (seqid).
//                     Free all valid packet buffer pointer used.
//                     Free used RO_linklist entry.
//      Parameters   : peer, ext_tid, mpdu_index
//      Return value : None
//      Functions called by this module:
//                     rxpb_write_free_buffer_to_rxpb_ptr_ring
//                     ro_linklist_return_free_ptr
//      Notes        : Make sure the cfg_badr_ro_mainlist and cfg_badr_ro_linklist
//                     is set to the correct value in the context structure before
//                     calling this function. Check the notes of functions called
//                     for complete list to be set in the context.
**************************************************************************************/
void ro_list_reset_a_tid_seqid(unsigned int peer, unsigned int ext_tid, unsigned int mpdu_index, unsigned int rxpb_release_type)
{
	unsigned int *temp_mainlist_data_ptr = 0;
	unsigned int *temp_linklist_data_ptr = 0;
	unsigned int temp_cur_ro_desc_index = 0;
	unsigned int first_msdu = 1;    /* Step 1*/
	unsigned int next_ptr_index_to_process = NULL_PTR;

	while (1) {
		/* Step 2*/
		if (first_msdu) {
			temp_mainlist_data_ptr = (unsigned int *)(((dlrx_ro_mainlist_t *)g_cfg_badr_ro_mainlist) + ((peer * NUM_TID) + ext_tid)); /* Offset into the required mainlist entry*/
			temp_cur_ro_desc_index = DLRX_RO_MAINLIST_first_ptr_get_indirect(temp_mainlist_data_ptr, mpdu_index);
			DLRX_CFG_CTXT_RO_MAINLIST_ro_mainlist_ptr_set_indirect(DLRX_CFG_CTXT_RO_MAINLIST_BASE, 0, (unsigned int)temp_mainlist_data_ptr);
		} else /* Step 3*/
			temp_cur_ro_desc_index = next_ptr_index_to_process;

		/* Step 4*/
		if (temp_cur_ro_desc_index == NULL_PTR)  /* if current ro descriptor pointer in NULL*/
			break;

		DLRX_CFG_CTXT_RO_LINKLIST_cur_ro_des_index_set_indirect(DLRX_CFG_CTXT_RO_LINKLIST_BASE, 0, temp_cur_ro_desc_index);

		temp_linklist_data_ptr = (unsigned int *)((dlrx_ro_linklist_t *)g_cfg_badr_ro_linklist + temp_cur_ro_desc_index);
		DLRX_CFG_CTXT_RO_LINKLIST_cur_ro_des_ptr_set_indirect(DLRX_CFG_CTXT_RO_LINKLIST_BASE, 0, (unsigned int)temp_linklist_data_ptr);

		if (rxpb_release_type == RECYCLE_RXPB)
			rxpb_write_free_buffer_to_rxpb_ptr_ring(RECYCLE_LL_RXPB_PTR);
		else {
			unsigned int rxpb_buf_ptr;
			rxpb_buf_ptr = VIR_TO_PHY(dlrx_get_ro_ll_rxpb_ptr());
			ppa_dl_dre_rxpb_buf_free(rxpb_buf_ptr);
		}

		/* Step 25*/
		next_ptr_index_to_process = ro_linklist_return_free_ptr(temp_cur_ro_desc_index);
		/* Add cur_ro_desc_index as prev_ro_des_index in cfg ctxt for debug purposes*/
		DLRX_CFG_CTXT_RO_LINKLIST_prev_ro_des_index_set_indirect(DLRX_CFG_CTXT_RO_LINKLIST_BASE, 0, temp_cur_ro_desc_index);
		/* Step 3*/
		first_msdu = 0;
	}

	/* Step 26*/
	DLRX_RO_MAINLIST_first_ptr_set_indirect(temp_mainlist_data_ptr, mpdu_index, NULL_PTR);
	/* Not defined in spec.*/
	DLRX_RO_MAINLIST_msdu_num_set_indirect(temp_mainlist_data_ptr, mpdu_index, 0);    /* Reset the number of MSDU data*/
	DLRX_RO_MAINLIST_mcast_bcast_set_indirect(temp_mainlist_data_ptr, mpdu_index, 0);    /* Reset the mcast bcast data*/
}

/**************************************************************************************
//      Function name: ro_list_clear
//      Description  : Clear the RO list data
//      Parameters   : None
//      Return value : None
//      Functions called by this module:
//                     ro_list_reset_a_tid_seqid
//      Notes        : None
**************************************************************************************/
void ro_list_clear(void)
{
	unsigned int peer;
	unsigned int ext_tid;
	unsigned int mpdu_index;

	for (peer = 0; peer < NUM_PEER; peer++) {
		for (ext_tid = 0; ext_tid < NUM_TID; ext_tid++) {
			for (mpdu_index = 0; mpdu_index < NUM_SEQ_ID; mpdu_index++)
				ro_list_reset_a_tid_seqid(peer, ext_tid, mpdu_index, RELEASE_RXPB);
		}
	}
}
