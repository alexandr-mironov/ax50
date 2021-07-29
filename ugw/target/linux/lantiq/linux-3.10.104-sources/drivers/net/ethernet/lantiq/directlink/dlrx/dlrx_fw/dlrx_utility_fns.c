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
#include "../include/dlrx_fw_macro_adaptor.h"
#include "../include/dlrx_inl_fns.h"

/**************************************************************************************
//      Function name: dlrx_add_outgoing_data_to_rxpb_buffer
//      Description  : Add data to the outgoing packet buffer based on the switch value
//      Parameters   : *rxpb_buf_ptr : rx packet buffer pointer
//                     outgoing_header_switch: Switch value to decide the type of data
//                     to be added to the rx packet buffer
//      Return value : None
//      Functions called by this module:
//                     dlrx_get_interface_data_from_vap
//      Notes        : Make sure the vap, discard, forward, inspect, cfg_size_rxpktdes and
//                     mpdu_status data is set to the correct value in the context structure
//                     before calling this function. Check the notes of functions called for
//                     complete list to be set in the context.
**************************************************************************************/
void dlrx_add_outgoing_data_to_rxpb_buffer(unsigned int *rxpb_buf_ptr, rx_outgoing_header_switch outgoing_header_switch)
{
	unsigned int pmac_header_data = 0;
	unsigned int vap;
	unsigned int forward;
	unsigned int discard;
	unsigned int interface;
	unsigned int inspect;
	unsigned int mpdu_status;
	unsigned int fw_rx_desc_byte;
	unsigned int *pmac_data_ptr;
	unsigned int padding_bytes = 0; /* Must initialize to zero */
	unsigned int pmac_ptr_offset;

	vap = DLRX_CTXT_MSG_vap_get_indirect(DLRX_CTXT_MSG_BASE, 0);
	/* TODO: Handle error case for interface */
	interface = dlrx_get_interface_data_from_vap(vap);
	discard = DLRX_CTXT_MSG_discard_get_indirect(DLRX_CTXT_MSG_BASE, 0);
	forward = DLRX_CTXT_MSG_forward_get_indirect(DLRX_CTXT_MSG_BASE, 0);
	inspect = DLRX_CTXT_MSG_inspect_get_indirect(DLRX_CTXT_MSG_BASE, 0);

	if (g_qca_hw == BEELINER_BOARD)
		padding_bytes = DLRX_RXPB_HDR_BEELINER_l3_header_padding_get_indirect(rxpb_buf_ptr, CFG_OFFSET_ATTEN_IN_DWORDS);

	switch (outgoing_header_switch) {
	case INSPECT_BIT_DATA:
		mpdu_status = DLRX_CTXT_MSG_mpdu_status_get_indirect(DLRX_CTXT_MSG_BASE, 0);
		fw_rx_desc_byte = ((inspect << B_FW_RX_DESC_BYTE_inspect_msdu0) | (forward << B_FW_RX_DESC_BYTE_forward_msdu0) | discard);

		pmac_header_data = ((mpdu_status << B_DLRX_RXPB_WLAN_DRV_HDR_mpdu_status) | fw_rx_desc_byte);
		*rxpb_buf_ptr = pmac_header_data;
		break;

	case ONE_PMAC_DATA:
		if (interface == 15) {
			/* The value of 3 is set as the interface value to prevent passing invalid interface value to the switch during the */
			/* playout process. The value could be any value between 3 to 7. Only condition is source and destination interface */
			/* value should be same */
			interface = VALID_INTERFACE_NUMBER;
		}

		pmac_header_data = ((interface << B_DLRX_RXPB_PMAC_HDR_src_int) | (interface << B_DLRX_RXPB_PMAC_HDR_dest_int) | (forward << B_DLRX_RXPB_PMAC_HDR_fwd1) | \
				    (vap << B_DLRX_RXPB_PMAC_HDR_vap) | (discard << B_DLRX_RXPB_PMAC_HDR_discard) | forward);
		pmac_data_ptr = (unsigned int *)((uint8_t *)rxpb_buf_ptr + GET_RXPKT_DESC_SIZE + padding_bytes);

		if ((padding_bytes % 4) == 0) {
			pmac_data_ptr--;
			*pmac_data_ptr = pmac_header_data;
		} else {
			uint8_t *temp_pmac_ptr;
			pmac_ptr_offset = 4;
			temp_pmac_ptr = dlrx_get_pmac_data_ptr(pmac_data_ptr, pmac_ptr_offset);
			memcpy((void *)temp_pmac_ptr, (void *)&pmac_header_data, 4);
		}

		break;

	case TWO_PMAC_DATA:
		if (interface == 15) {
			/* The value of 3 is set as the interface value to prevent passing invalid interface value to the switch during the */
			/* playout process. The value could be any value between 3 to 7. Only condition is source and destination interface */
			/* value should be same */
			pmac_header_data = ((VALID_INTERFACE_NUMBER << B_DLRX_RXPB_PMAC_HDR_src_int) | (VALID_INTERFACE_NUMBER << B_DLRX_RXPB_PMAC_HDR_dest_int) | \
					    (forward << B_DLRX_RXPB_PMAC_HDR_fwd1) | (vap << B_DLRX_RXPB_PMAC_HDR_vap) | (discard << B_DLRX_RXPB_PMAC_HDR_discard) | forward);
		} else {
			pmac_header_data = ((interface << B_DLRX_RXPB_PMAC_HDR_src_int) | (interface << B_DLRX_RXPB_PMAC_HDR_dest_int) | (forward << B_DLRX_RXPB_PMAC_HDR_fwd1) | \
					    (vap << B_DLRX_RXPB_PMAC_HDR_vap) | (discard << B_DLRX_RXPB_PMAC_HDR_discard) | forward | (1 << B_DLRX_RXPB_PMAC_HDR_rsvd1));
		}

		pmac_data_ptr = (unsigned int *)((uint8_t *)rxpb_buf_ptr + GET_RXPKT_DESC_SIZE + padding_bytes);

		if ((padding_bytes % 4) == 0) {
			pmac_data_ptr--;
			*pmac_data_ptr = pmac_header_data;
		} else {
			uint8_t *temp_pmac_ptr;
			pmac_ptr_offset = 4;
			temp_pmac_ptr = dlrx_get_pmac_data_ptr(pmac_data_ptr, pmac_ptr_offset);
			memcpy((void *)temp_pmac_ptr, (void *)&pmac_header_data, 4);
		}

		pmac_header_data = 0;
		pmac_header_data = ((interface << B_DLRX_RXPB_PMAC_HDR_src_int) | (interface << B_DLRX_RXPB_PMAC_HDR_dest_int));

		if ((padding_bytes % 4) == 0) {
			pmac_data_ptr--;
			*pmac_data_ptr = pmac_header_data;
		} else {
			uint8_t *temp_pmac_ptr;
			pmac_ptr_offset = 8;
			temp_pmac_ptr = dlrx_get_pmac_data_ptr(pmac_data_ptr, pmac_ptr_offset);
			memcpy((void *)temp_pmac_ptr, (void *)&pmac_header_data, 4);
		}

		break;

	default:
		/* Should not reach here */
		break;
	}
}

/**************************************************************************************
//      Function name: dlrx_get_interface_data_from_vap
//      Description  : Get the interface value for the vap
//      Parameters   : None
//      Return value : Interface value for the vap
//      Functions called by this module:
//                     None
//      Notes        : Make sure the vap 0 to vap 15 is set to the correct value in the
//                     context structure before calling this function. Check the notes
//                     of functions called for complete list to be set in the context.
**************************************************************************************/
unsigned int dlrx_get_interface_data_from_vap(unsigned int vap)
{
	return ppa_dl_dre_itf_from_vapid(vap);
}

/**************************************************************************************
//      Function name: dlrx_get_current_rxpb_buf_ptr
//      Description  : Get the current rx packet buffer pointer  ( Physical address returned)
//      Parameters   : None
//      Return value : Current rx packet buffer pointer
//      Functions called by this module:
//                     None
//      Notes        : Make sure the cfg_badr_rxpb_ptr_ring and rxpb_ptr_read_index is
//                     set to the correct value in the context structure before calling
//                     this function. Check the notes of functions called for complete
//                     list to be set in the context.
**************************************************************************************/
unsigned int dlrx_get_current_rxpb_buf_ptr(void)
{
	unsigned int rxpb_ring_base_address;
	unsigned int rxpb_ptr_read_index;

	/* Get RXPB ring data */
	rxpb_ring_base_address = UNCACHE_ADDR(DLRX_CFG_CTXT_RXPB_PTR_RING_cfg_badr_rxpb_ptr_ring_get_indirect((unsigned int *)UNCACHE_ADDR(DLRX_CFG_CTXT_RXPB_PTR_RING_BASE), 0));
	rxpb_ptr_read_index = DLRX_CFG_CTXT_RXPB_PTR_RING_rxpb_ptr_read_index_get_indirect((unsigned int *)UNCACHE_ADDR(DLRX_CFG_CTXT_RXPB_PTR_RING_BASE), 0);

	return DLRX_RXPB_PTR_RING_rxpb_ptr_get_indirect((unsigned int *)rxpb_ring_base_address, rxpb_ptr_read_index);
}

/**************************************************************************************
//      Function name: dlrx_get_ind_msg_mpdu_data_offset
//      Description  : Get the dword offset to the mpdu data
//      Parameters   : *ce5_buf_ptr : ce5 buffer pointer
//      Return value : Byte data offset to reach to get the MPDU status and MPDU count
//      Functions called by this module:
//                     None
//      Notes        : None
**************************************************************************************/
unsigned int dlrx_get_ind_msg_mpdu_data_offset(unsigned int *ce5_buf_ptr)
{
	unsigned int num_rx_desc_bytes;

	num_rx_desc_bytes = DLRX_IND_MSG_fw_rx_desc_byte_num_get_indirect(ce5_buf_ptr, 0);

	return ((num_rx_desc_bytes + 3) >> 2) << 2;
}

/**************************************************************************************
//      Function name: dlrx_get_fw_rx_desc_byte_data
//      Description  : Get the fw_rx_dwsc_byte for the corresponding msdu
//      Parameters   : *ce5_buf_ptr : ce5 buffer pointer
//      Return value : None
//      Functions called by this module:
//                     None
//      Notes        : Make sure the msdu_index is set to the correct value in the
//                     context structure before calling this function. Check the notes of
//                     functions called for complete list to be set in the context.
**************************************************************************************/
void dlrx_get_fw_rx_desc_byte_data(unsigned int *ce5_buf_ptr)
{
	unsigned int msdu_dword_offset;
	unsigned int *fw_rx_desc_data_base_addr;
	unsigned int msdu_switch_value;
	unsigned int msdu_index;
	unsigned int discard = 0;
	unsigned int forward = 0;
	unsigned int inspect = 0;
	unsigned int total_msdu;

	total_msdu = DLRX_CTXT_MSG_total_msdu_get_indirect(DLRX_CTXT_MSG_BASE, 0);
	msdu_index = DLRX_CTXT_MSG_msdu_index_get_indirect(DLRX_CTXT_MSG_BASE, 0);
	msdu_dword_offset = msdu_index >> 2;
	fw_rx_desc_data_base_addr = (unsigned int *)((uint8_t *)ce5_buf_ptr + sizeof(dlrx_ind_msg_t));
	msdu_switch_value = msdu_index % 4;

	switch (msdu_switch_value) {
	case 0:
		discard = FW_RX_DESC_BYTE_discard_msdu0_get_indirect(fw_rx_desc_data_base_addr, msdu_dword_offset);
		forward = FW_RX_DESC_BYTE_forward_msdu0_get_indirect(fw_rx_desc_data_base_addr, msdu_dword_offset);
		inspect = FW_RX_DESC_BYTE_inspect_msdu0_get_indirect(fw_rx_desc_data_base_addr, msdu_dword_offset);
		break;

	case 1:
		discard = FW_RX_DESC_BYTE_discard_msdu1_get_indirect(fw_rx_desc_data_base_addr, msdu_dword_offset);
		forward = FW_RX_DESC_BYTE_forward_msdu1_get_indirect(fw_rx_desc_data_base_addr, msdu_dword_offset);
		inspect = FW_RX_DESC_BYTE_inspect_msdu1_get_indirect(fw_rx_desc_data_base_addr, msdu_dword_offset);
		break;

	case 2:
		discard = FW_RX_DESC_BYTE_discard_msdu2_get_indirect(fw_rx_desc_data_base_addr, msdu_dword_offset);
		forward = FW_RX_DESC_BYTE_forward_msdu2_get_indirect(fw_rx_desc_data_base_addr, msdu_dword_offset);
		inspect = FW_RX_DESC_BYTE_inspect_msdu2_get_indirect(fw_rx_desc_data_base_addr, msdu_dword_offset);
		break;

	case 3:
		discard = FW_RX_DESC_BYTE_discard_msdu3_get_indirect(fw_rx_desc_data_base_addr, msdu_dword_offset);
		forward = FW_RX_DESC_BYTE_forward_msdu3_get_indirect(fw_rx_desc_data_base_addr, msdu_dword_offset);
		inspect = FW_RX_DESC_BYTE_inspect_msdu3_get_indirect(fw_rx_desc_data_base_addr, msdu_dword_offset);
		break;

	default:
		/* Should not reach here */
		break;
	}

	if (g_congestion_drop_flag) {
		if (inspect != 1) {
			discard = 1;
			forward = 0;
			inspect = 0;
			mib_update_congestion_drop_packets();
		}
	} else if (msdu_index >= total_msdu) {
		discard = 0;
		forward = 0;
		inspect = 0;
	}

	DLRX_CTXT_MSG_discard_set_indirect(DLRX_CTXT_MSG_BASE, 0, discard);
	/* TODO: DEBUG remove forword */
#if 0	  /*temp disable forwarding for GRX350_DL_TEST */
	forward = 0;
#endif
	DLRX_CTXT_MSG_forward_set_indirect(DLRX_CTXT_MSG_BASE, 0, forward);

	DLRX_CTXT_MSG_inspect_set_indirect(DLRX_CTXT_MSG_BASE, 0, inspect);

}

/*****************************************************************************************
//      Function name: dlrx_copy_last_pn_to_mainlist
//      Description  : Copy the last PN value from the linklist to the mainlist
//      Parameters   : None
//      Return value : None
//      Functions called by this module:
//                     None
//      Notes        : Make sure the cur_ro_des_ptr and ro_mainlist_ptr is set to the
//                     correct value in the context structure before calling this function.
//                     Check the notes of functions called for complete list to be set
//                     in the context.
*****************************************************************************************/
void dlrx_copy_last_pn_to_mainlist(void)
{
	unsigned int *linklist_data_ptr;
	unsigned int *mainlist_data_ptr;
	unsigned int pn_data;

	linklist_data_ptr = (unsigned int *)DLRX_CFG_CTXT_RO_LINKLIST_cur_ro_des_ptr_get_indirect(DLRX_CFG_CTXT_RO_LINKLIST_BASE, 0);
	mainlist_data_ptr = (unsigned int *)DLRX_CFG_CTXT_RO_MAINLIST_ro_mainlist_ptr_get_indirect(DLRX_CFG_CTXT_RO_MAINLIST_BASE, 0);

	pn_data = DLRX_RO_LINKLIST_pn_dw0_get_indirect(linklist_data_ptr, 0);
	DLRX_RO_MAINLIST_last_pn_dw0_set_indirect(mainlist_data_ptr, 0, pn_data);

	pn_data = DLRX_RO_LINKLIST_pn_dw1_get_indirect(linklist_data_ptr, 0);
	DLRX_RO_MAINLIST_last_pn_dw1_set_indirect(mainlist_data_ptr, 0, pn_data);

	pn_data = DLRX_RO_LINKLIST_pn_dw2_get_indirect(linklist_data_ptr, 0);
	DLRX_RO_MAINLIST_last_pn_dw2_set_indirect(mainlist_data_ptr, 0, pn_data);

	pn_data = DLRX_RO_LINKLIST_pn_dw3_get_indirect(linklist_data_ptr, 0);
	DLRX_RO_MAINLIST_last_pn_dw3_set_indirect(mainlist_data_ptr, 0, pn_data);
}

/*****************************************************************************************
//      Function name: dlrx_is_pn_check_fail
//      Description  : Compare the current PN in the linklist with the last PN value in the
//                     mainlist
//      Parameters   : None
//      Return value : TRUE : Current PN is less than or equal to last PN (PN check failed)
//                     FALSE : Current PN is greater than the last PN (PN check passed)
//      Functions called by this module:
//                     None
//      Notes        : Make sure the sec_type, cur_ro_des_ptr and ro_mainlist_ptr is set to
//                     the correct value in the context structure before calling this
//                     function. Check the notes of functions called for complete list to
//                     be set in the context.
*****************************************************************************************/
unsigned int dlrx_is_pn_check_fail(void)
{
	unsigned int sec_type;
	unsigned int cur_pn[4];
	unsigned int last_pn[4];
	unsigned int loop_count;
	unsigned int i;
	unsigned int *linklist_data_ptr;
	unsigned int *mainlist_data_ptr;

	linklist_data_ptr = (unsigned int *)DLRX_CFG_CTXT_RO_LINKLIST_cur_ro_des_ptr_get_indirect(DLRX_CFG_CTXT_RO_LINKLIST_BASE, 0);
	mainlist_data_ptr = (unsigned int *)DLRX_CFG_CTXT_RO_MAINLIST_ro_mainlist_ptr_get_indirect(DLRX_CFG_CTXT_RO_MAINLIST_BASE, 0);
	sec_type = DLRX_CTXT_MSG_sec_type_get_indirect(DLRX_CTXT_MSG_BASE, 0);

	cur_pn[0] = DLRX_RO_LINKLIST_pn_dw0_get_indirect(linklist_data_ptr, 0);
	cur_pn[1] = DLRX_RO_LINKLIST_pn_dw1_get_indirect(linklist_data_ptr, 0);
	cur_pn[2] = DLRX_RO_LINKLIST_pn_dw2_get_indirect(linklist_data_ptr, 0);
	cur_pn[3] = DLRX_RO_LINKLIST_pn_dw3_get_indirect(linklist_data_ptr, 0);

	last_pn[0] = DLRX_RO_MAINLIST_last_pn_dw0_get_indirect(mainlist_data_ptr, 0);
	last_pn[1] = DLRX_RO_MAINLIST_last_pn_dw1_get_indirect(mainlist_data_ptr, 0);
	last_pn[2] = DLRX_RO_MAINLIST_last_pn_dw2_get_indirect(mainlist_data_ptr, 0);
	last_pn[3] = DLRX_RO_MAINLIST_last_pn_dw3_get_indirect(mainlist_data_ptr, 0);

	if (sec_type == SEC_TYPE_PN_48) {
		/* Compare only 48 bits */
		cur_pn[1] = (cur_pn[1] & 0xFFFF);
		last_pn[1] = (last_pn[1] & 0xFFFF);
		loop_count = 2;
	} else
		loop_count = 4;

	for (i = loop_count; i > 0; i--) {
		if (cur_pn[i - 1] < last_pn[i - 1])
			return 1;
		else if (cur_pn[i - 1] > last_pn[i - 1])
			return 0;
	}

	return 1; /* This return is for the last case when cur_pn[0] == last_pn[0] */
}

/*****************************************************************************************
//      Function name: dlrx_get_ro_ll_rxpb_ptr
//      Description  : Get the vap to int value based on the vap
//      Parameters   : None
//      Return value : Vap to int value
//      Functions called by this module:
//                     None
//      Notes        : Make sure the cur_ro_des_ptr is set to the correct value in the
//                     context structure before calling this function. Check the notes of
//                     functions called for complete list to be set in the context.
*****************************************************************************************/
unsigned int dlrx_get_ro_ll_rxpb_ptr(void)
{
	unsigned int *linklist_data_ptr;

	linklist_data_ptr = (unsigned int *)DLRX_CFG_CTXT_RO_LINKLIST_cur_ro_des_ptr_get_indirect(DLRX_CFG_CTXT_RO_LINKLIST_BASE, 0);
	return DLRX_RO_LINKLIST_rxpb_ptr_get_indirect(linklist_data_ptr, 0);
}

#if DLRX_GRX330_BOARD_CFG
/*****************************************************************************************
//      Function name: dlrx_check_congestion_status
//      Description  : Check the congestion bit status
//      Parameters   : None
//      Return value : Congestion status
//      Functions called by this module:
//                     None
//      Notes        : Make sure the congestion_bit_timeout is set to the correct value in the
//                     context structure before calling this function. Check the notes of
//                     functions called for complete list to be set in the context.
*****************************************************************************************/
unsigned int dlrx_check_congestion_status(void)
{
	unsigned int loop_val = DLRX_CFG_GLOBAL_dlrx_congestion_bit_timeout_get_indirect(DLRX_CFG_GLOBAL_BASE, 0);
	unsigned int loop_count = 0;

	if ((*congestion_register_addr & CONGESTION_REG_MASK)) {
		for (loop_count = 0; loop_count < loop_val; loop_count++) {
			if (((*congestion_register_addr) & CONGESTION_REG_MASK) == 0)
				break;
		}
	}

	if (loop_count == loop_val)
		return 0;
	else
		return 1;
}
#endif

void dlrx_generate_debug(unsigned int stop_flag)
{
	unsigned int rxpb_ptr_read_index;
	unsigned int *rxpb_buf_ptr;
	unsigned int rxpb_ptr_write_index;
	unsigned int idx, i;
	unsigned int *ce5buf_ptr;
	unsigned int first_msdu = 0;
	unsigned int last_msdu = 0;
	unsigned int msdu_chain_num, msdu_length, seq_id;
	unsigned int peer_id, peer, total_msdu, ext_tid, msg_type;
	unsigned int iden_id;

	if (stop_flag) {
		*DLRX_TARGET_CE5_WRITE_INDEX(g_ce5_offset) = ((*DLRX_TARGET_CE5_READ_INDEX(g_ce5_offset)) + 64) % GET_NUM_CE5BUF;

		/*delay some time */
		for (i = 0; i < 0xffffff ; i++)
			idx = 0;
	}

	rxpb_ptr_write_index = DLRX_CFG_CTXT_RXPB_PTR_RING_rxpb_ptr_write_index_get_indirect(DLRX_CFG_CTXT_RXPB_PTR_RING_BASE, 0);
	rxpb_ptr_read_index = DLRX_CFG_CTXT_RXPB_PTR_RING_rxpb_ptr_read_index_get_indirect(DLRX_CFG_CTXT_RXPB_PTR_RING_BASE, 0);

	printk("\n\n");
	printk("rxpb_parse_idex=0x%x, write_idx=0x%x \n", rxpb_ptr_read_index, rxpb_ptr_write_index);
	printk(" rxpb_idx, seq_id,skb, msdu_length,first_msdu,last_msdu,msdu_chained_num,ce5_buf_ptr,total_msdu,peer_id,ext_tid,msg_type,iden_id\n");

	for (idx = 0; idx < GET_NUM_RXPB_PTR_RING; idx++) {
		rxpb_buf_ptr = (unsigned int *)UNCACHE_ADDR(DLRX_RXPB_PTR_RING_rxpb_ptr_get_indirect((unsigned int *)g_cfg_badr_rxpb_ptr_ring, idx));
		msdu_length = DLRX_RXPB_HDR_msdu_len_get_indirect(rxpb_buf_ptr, CFG_OFFSET_ATTEN_IN_DWORDS);
		first_msdu = DLRX_RXPB_HDR_first_msdu_get_indirect(rxpb_buf_ptr, CFG_OFFSET_ATTEN_IN_DWORDS);
		last_msdu = DLRX_RXPB_HDR_last_msdu_get_indirect(rxpb_buf_ptr, CFG_OFFSET_ATTEN_IN_DWORDS);
		msdu_chain_num = DLRX_RXPB_HDR_msdu_chain_num_get_indirect(rxpb_buf_ptr, CFG_OFFSET_ATTEN_IN_DWORDS);

		if (first_msdu)
			seq_id = DLRX_RXPB_HDR_seqid_get_indirect(rxpb_buf_ptr, CFG_OFFSET_ATTEN_IN_DWORDS);
		else
			seq_id = 0xfff;

		ce5buf_ptr = (unsigned int *) *(rxpb_buf_ptr - 2) ;

		if (idx == 0x3ff)
			printk("rxpb_buf_ptr 0x%x,ce5buf_ptr0x%x \n ", (unsigned int)rxpb_buf_ptr, (unsigned int)ce5buf_ptr);

		if (((unsigned  int)ce5buf_ptr & 0xF0000000) ==  0x80000000) {
			peer_id = DLRX_IND_MSG_peer_id_get_indirect(ce5buf_ptr, 0);
			ppa_dl_dre_peer_from_peerid(peer_id, &peer);

			total_msdu = DLRX_IND_MSG_fw_rx_desc_byte_num_get_indirect(ce5buf_ptr, 0);

			/*Get ext_tid and save to FW context */
			ext_tid = DLRX_IND_MSG_ext_tid_get_indirect(ce5buf_ptr, 0);
			msg_type = DLRX_IND_MSG_msg_type_get_indirect(ce5buf_ptr, 0);
		} else {
			peer = 0;
			total_msdu = 0;
			ext_tid = 0;
			msg_type = 0;
		}

		if (DLRX_RXPB_HDR_msdu_load_status_get_indirect(rxpb_buf_ptr, CFG_OFFSET_ATTEN_IN_DWORDS))   /*msdu_done set */
			printk("MSDU_DONE     ") ;
		else
			printk("MSDU_NOT_DONE ");

		iden_id = *(rxpb_buf_ptr + 66);
		printk(" 0x%x,0x%x, 0x%x,0x%x 0x%x,0x%x,%u,%u,%u,0x%x,0x%x,0x%x,0x%x,0x%x \n", idx, iden_id, (unsigned int) *(rxpb_buf_ptr - 1), (unsigned int)rxpb_buf_ptr, (unsigned int)seq_id, msdu_length, first_msdu, last_msdu, msdu_chain_num, (unsigned int)ce5buf_ptr, total_msdu, peer, ext_tid, msg_type);
#if 1

		if ((unsigned int) *(rxpb_buf_ptr - 1) == 0x6e746400) {
			for (i = 32; i > 0 ; i--)
				printk("0x%x", (unsigned int) *(rxpb_buf_ptr - i));

			printk("\n");
		}

#endif

		for (i = 0; i < GET_NUM_RXPB_PTR_RING; i++) {
			unsigned int *tmp_ptr;

			if (i == idx)
				continue;

			tmp_ptr = (unsigned int *)UNCACHE_ADDR(DLRX_RXPB_PTR_RING_rxpb_ptr_get_indirect((unsigned int *)g_cfg_badr_rxpb_ptr_ring, i));

			if ((unsigned int)tmp_ptr == (unsigned int)rxpb_buf_ptr) {
				if (DLRX_RXPB_HDR_msdu_load_status_get_indirect(rxpb_buf_ptr, CFG_OFFSET_ATTEN_IN_DWORDS))
					printk(" Same buffer : 0x%x for index(msdu_done set) 0x%x  and (msdu_done set) 0x%x \n", (unsigned int)tmp_ptr, idx, i);
				else
					printk(" Same buffer : 0x%x for index(msdu_done set) 0x%x  and  free 0x%x \n", (unsigned int)tmp_ptr, idx, i);
			}
		}

	}

	/* Ro list debug data */
/*   dlrx_print_rolist_debug_data( ); */
#if 0
	{
		int index;
		unsigned int *dma_desc;
		dma_desc = DLRX_DDR_GSWIP_DMA_DESC_BASE;
		printk("index  Des_ptr, Iden_id  \n");

		for (index = 0 ;  index < 127;   index++) {
			unsigned int   *tmp_ptr;
			tmp_ptr = (unsigned int *) *(dma_desc + 1) + 0xa0000000;

			if ((index % 2) == 0)
				printk(" 0x%x  ", index);

			printk("0x%x , 0x%x   ", tmp_ptr, *(tmp_ptr + 10));
			dma_desc += 4;

			if ((index % 2) == 1)
				printk(" \n");
		}
	}
#endif
}

void dlrx_print_rolist_debug_data(void)
{
	unsigned int peer_num;
	unsigned int tid_num;
	unsigned int seqid_num;
	unsigned int *temp_mainlist_data_ptr;
	unsigned int *temp_linklist_data_ptr;
	unsigned int first_ptr;
	unsigned int next_ptr;
	unsigned int count_num = 0;
	unsigned int msdu_num;

	/*re-order list */
	printk("Reorder Link list context \n");
	printk("Head = %u Tail = %u Free = %u cur_ptr = 0x%x  cur_index = %u\n\n",
	       DLRX_CFG_CTXT_RO_LINKLIST_ro_des_free_head_index_get_indirect(DLRX_CFG_CTXT_RO_LINKLIST_BASE, 0),
	       DLRX_CFG_CTXT_RO_LINKLIST_ro_des_free_tail_index_get_indirect(DLRX_CFG_CTXT_RO_LINKLIST_BASE, 0),
	       DLRX_CFG_CTXT_RO_LINKLIST_free_num_ro_linklist_get_indirect(DLRX_CFG_CTXT_RO_LINKLIST_BASE, 0),
	       DLRX_CFG_CTXT_RO_LINKLIST_cur_ro_des_ptr_get_indirect(DLRX_CFG_CTXT_RO_LINKLIST_BASE, 0),
	       DLRX_CFG_CTXT_RO_LINKLIST_cur_ro_des_index_get_indirect(DLRX_CFG_CTXT_RO_LINKLIST_BASE, 0));

	printk("Main list Data \n");
	printk("Peer  Tid  seqid  Linked ro link list\n");

	for (peer_num = 0; peer_num < 128; peer_num++) {
		for (tid_num = 0; tid_num < 16; tid_num++) {
			temp_mainlist_data_ptr = (unsigned int *)(((dlrx_ro_mainlist_t *)g_cfg_badr_ro_mainlist) + ((peer_num * NUM_TID) + tid_num)); /* Offset into the required mainlist entry */

			for (seqid_num = 0; seqid_num < 64; seqid_num++) {
				first_ptr = DLRX_RO_MAINLIST_first_ptr_get_indirect(temp_mainlist_data_ptr, seqid_num);
				msdu_num = DLRX_RO_MAINLIST_msdu_num_get_indirect(temp_mainlist_data_ptr, seqid_num);

				if (first_ptr == NULL_PTR)
					continue;

				temp_linklist_data_ptr = (unsigned int *)((dlrx_ro_linklist_t *)g_cfg_badr_ro_linklist + first_ptr);   /* Offset into the required linklist entry */
				printk("%u    %u    %u   ", peer_num, tid_num, seqid_num);
				printk("%u  ", first_ptr);
				count_num++;
				next_ptr = DLRX_RO_LINKLIST_next_ptr_get_indirect(temp_linklist_data_ptr, 0);

				while (next_ptr != NULL_PTR) {
					count_num++;
					printk("%u  ", next_ptr);
					temp_linklist_data_ptr = (unsigned int *)((dlrx_ro_linklist_t *)g_cfg_badr_ro_linklist + next_ptr);   /* Offset into the required linklist entry */
					next_ptr = DLRX_RO_LINKLIST_next_ptr_get_indirect(temp_linklist_data_ptr, 0);
				}

				if (count_num == msdu_num)
					printk("LL_MATCH\n");
				else
					printk("LL_MISMATCH Count_num = %u msdu_num = %u\n", count_num, msdu_num);

				count_num = 0;
			}
		}
	}

	printk("--------------------------------------------------------\n");
}

/*****************************************************************************************
//      Function name: dlrx_unregister_driver_fns
//      Description  : Unregister the functions registered with the driver
//      Parameters   : None
//      Return value : None
//      Functions called by this module: ppa_dl_dre_fn_register
//      Notes        : None
*****************************************************************************************/
void dlrx_unregister_driver_fns(void)
{
	ppa_dl_dre_fn_register(DRE_MAIN_FN, NULL);
	ppa_dl_dre_fn_register(DRE_GET_VERSION_FN, NULL);
	ppa_dl_dre_fn_register(DRE_RESET_FN, NULL);
	ppa_dl_dre_fn_register(DRE_GET_MIB_FN, NULL);
	ppa_dl_dre_fn_register(DRE_GET_CURMSDU_FN, NULL);
	ppa_dl_dre_fn_register(DRE_SET_MEMBASE_FN , NULL);
	ppa_dl_dre_fn_register(DRE_SET_RXPN_FN , NULL);
	ppa_dl_dre_fn_register(DRE_SET_DLRX_UNLOAD, NULL);
}


