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
#ifndef __DLRX_INL_FNS_H__
#define __DLRX_INL_FNS_H__

#include "dlrx_fw_data_structure_macro.h"
#include "dlrx_fw_internal_def.h"


/*************************************************************************
Module:           mib_update_success_status_counters
Description: Increment the success status counters
Parameters: switch_value : Used to determine if msdu or mpdu counters need to
	be updated.
Return value :   None
Functions called by this module: None
Notes        : This function is made as a seperate
			inline function to improve performance
*************************************************************************/
extern inline void mib_update_success_status_counters(
	mib_msdu_mpdu_update_switch switch_value)
{
	unsigned int counter_value;
	if (switch_value == UPDATE_MSDU_MIB) {
		counter_value = DLRX_DATA_MIB_rx_success_msdu_get_indirect(DLRX_DATA_MIB_BASE, 0);
		counter_value++;
		DLRX_DATA_MIB_rx_success_msdu_set_indirect(DLRX_DATA_MIB_BASE, 0, counter_value);
	} else if (switch_value == UPDATE_MPDU_MIB) {
		counter_value = DLRX_DATA_MIB_rx_success_mpdu_get_indirect(DLRX_DATA_MIB_BASE, 0);
		counter_value++;
		DLRX_DATA_MIB_rx_success_mpdu_set_indirect(DLRX_DATA_MIB_BASE, 0, counter_value);
	}
}

/*************************************************************************
Module:          mib_update_rx_ind_msg
Description:     Increment the rx indication message mib
Parameters:      None
Return value :   None
Functions called by this module: None
Notes        :   This function is made as a seperate inline
			function to improve performance
************************************************************************/
extern inline void mib_update_rx_ind_msg(void)
{
	unsigned int msg_mib;
	msg_mib = DLRX_MSG_MIB_total_rx_ind_msg_get_indirect(DLRX_MSG_MIB_BASE, 0) + 1;
	DLRX_MSG_MIB_total_rx_ind_msg_set_indirect(DLRX_MSG_MIB_BASE, 0, msg_mib);
}

/*************************************************************************
Module:           mib_update_chained_mpdu
Description:     Increment the total chained mpdu counters
Parameters:     offset : Offset value into the structure
Return value :   None
Functions called by this module: None
Notes:  None
*************************************************************************/
extern inline void mib_update_chained_mpdu(unsigned int offset)
{
	unsigned int mib_value;
	mib_value = DLRX_MISC_MIB_total_chained_mpdu_get_indirect(DLRX_MISC_MIB_BASE, offset);
	mib_value++;
	DLRX_MISC_MIB_total_chained_mpdu_set_indirect(DLRX_MISC_MIB_BASE, offset, mib_value);
}

/******************************************************************************
Function name: mib_update_vap_gswip_data
Description  : Update the mib VAP GSWIP data
Parameters   : msdu_length : msdu length
Return value : None
Functions called by this module:
	None
	Notes        : Make sure the vap is set to the correct value in the context
	structure before calling this function. Check the notes of functions called
	for complete list to be set in the context.
******************************************************************************/
extern inline void mib_update_vap_gswip_data(unsigned int msdu_length)
{
	unsigned int vap;
	unsigned long long msb_byte;
	unsigned long long lsb_byte;
	unsigned long long pdu_data;
	unsigned long long num_bytes_data;

	vap = DLRX_CTXT_MSG_vap_get_indirect(DLRX_CTXT_MSG_BASE, 0);

	lsb_byte = VAP_DATA_MISC_MIB_rx_gswip_packets_low_get_indirect(DLRX_VAP_MIB_MISC_BASE(vap), 0);
	msb_byte = VAP_DATA_MISC_MIB_rx_gswip_packets_high_get_indirect(DLRX_VAP_MIB_MISC_BASE(vap), 0);
	msb_byte = msb_byte << W_VAP_DATA_MISC_MIB_rx_gswip_packets_high;
	pdu_data = (msb_byte | lsb_byte);
	pdu_data++;
	VAP_DATA_MISC_MIB_rx_gswip_packets_low_set_indirect(DLRX_VAP_MIB_MISC_BASE(vap), 0, (pdu_data & M_VAP_DATA_MISC_MIB_rx_gswip_packets_low));
	VAP_DATA_MISC_MIB_rx_gswip_packets_high_set_indirect(DLRX_VAP_MIB_MISC_BASE(vap), 0, ((pdu_data >> W_VAP_DATA_MISC_MIB_rx_gswip_packets_high) \
		& M_VAP_DATA_MISC_MIB_rx_gswip_packets_high));

	lsb_byte = VAP_DATA_MISC_MIB_rx_gswip_bytes_low_get_indirect(DLRX_VAP_MIB_MISC_BASE(vap), 0);
	msb_byte = VAP_DATA_MISC_MIB_rx_gswip_bytes_high_get_indirect(DLRX_VAP_MIB_MISC_BASE(vap), 0);
	msb_byte = msb_byte << W_VAP_DATA_MISC_MIB_rx_gswip_bytes_high;
	num_bytes_data = (msb_byte | lsb_byte);
	num_bytes_data += msdu_length;
	VAP_DATA_MISC_MIB_rx_gswip_bytes_low_set_indirect(DLRX_VAP_MIB_MISC_BASE(vap), 0, (num_bytes_data & M_VAP_DATA_MISC_MIB_rx_gswip_bytes_low));
	VAP_DATA_MISC_MIB_rx_gswip_bytes_high_set_indirect(DLRX_VAP_MIB_MISC_BASE(vap), 0, ((num_bytes_data >> W_VAP_DATA_MISC_MIB_rx_gswip_bytes_high) \
		& M_VAP_DATA_MISC_MIB_rx_gswip_bytes_high));
}

/******************************************************************************
Function name: mib_update_vap_wlan_data
Description  : Update the mib VAP WLAN data
Parameters   : msdu_length : msdu length
Return value : None
Functions called by this module: None
Notes        : Make sure the vap is set to the correct value in the context
	structure before calling this function. Check the notes of functions
	called for complete list to be set in the context.
******************************************************************************/
extern inline void mib_update_vap_wlan_data(unsigned int msdu_length)
{
	unsigned int vap;
	unsigned long long msb_byte;
	unsigned long long lsb_byte;
	unsigned long long pdu_data;
	unsigned long long num_bytes_data;

	vap = DLRX_CTXT_MSG_vap_get_indirect(DLRX_CTXT_MSG_BASE, 0);

	lsb_byte = VAP_DATA_MISC_MIB_rx_wlan_packets_low_get_indirect(DLRX_VAP_MIB_MISC_BASE(vap), 0);
	msb_byte = VAP_DATA_MISC_MIB_rx_wlan_packets_high_get_indirect(DLRX_VAP_MIB_MISC_BASE(vap), 0);
	msb_byte = msb_byte << W_VAP_DATA_MISC_MIB_rx_wlan_packets_high;
	pdu_data = (msb_byte | lsb_byte);
	pdu_data++;
	VAP_DATA_MISC_MIB_rx_wlan_packets_low_set_indirect(DLRX_VAP_MIB_MISC_BASE(vap), 0, (pdu_data & M_VAP_DATA_MISC_MIB_rx_wlan_packets_low));
	VAP_DATA_MISC_MIB_rx_wlan_packets_high_set_indirect(DLRX_VAP_MIB_MISC_BASE(vap), 0, ((pdu_data >> W_VAP_DATA_MISC_MIB_rx_wlan_packets_high) \
														& M_VAP_DATA_MISC_MIB_rx_wlan_packets_high));

	lsb_byte = VAP_DATA_MISC_MIB_rx_wlan_bytes_low_get_indirect(DLRX_VAP_MIB_MISC_BASE(vap), 0);
	msb_byte = VAP_DATA_MISC_MIB_rx_wlan_bytes_high_get_indirect(DLRX_VAP_MIB_MISC_BASE(vap), 0);
	msb_byte = msb_byte << W_VAP_DATA_MISC_MIB_rx_wlan_bytes_high;
	num_bytes_data = (msb_byte | lsb_byte);
	num_bytes_data += msdu_length;
	VAP_DATA_MISC_MIB_rx_wlan_bytes_low_set_indirect(DLRX_VAP_MIB_MISC_BASE(vap), 0, (num_bytes_data & M_VAP_DATA_MISC_MIB_rx_wlan_bytes_low));
	VAP_DATA_MISC_MIB_rx_wlan_bytes_high_set_indirect(DLRX_VAP_MIB_MISC_BASE(vap), 0, ((num_bytes_data >> W_VAP_DATA_MISC_MIB_rx_wlan_bytes_high) \
	   & M_VAP_DATA_MISC_MIB_rx_wlan_bytes_high));
}

/******************************************************************************
Function name: mib_update_vap_protocol_stack_data
Description  : Update the mib VAP protocol stack data
Parameters   : msdu_length : msdu length
Return value : None
Functions called by this module: None
Notes        : Make sure the vap is set to the correct value in the context
	structure before calling this function. Check the notes of functions
	called for complete list to be set in the context.
******************************************************************************/
extern inline void mib_update_vap_protocol_stack_data(unsigned int msdu_length)
{
	unsigned int vap;
	unsigned long long msb_byte;
	unsigned long long lsb_byte;
	unsigned long long pdu_data;
	unsigned long long num_bytes_data;

	vap = DLRX_CTXT_MSG_vap_get_indirect(DLRX_CTXT_MSG_BASE, 0);

	lsb_byte = VAP_DATA_MISC_MIB_rx_protocol_stack_packets_low_get_indirect(DLRX_VAP_MIB_MISC_BASE(vap), 0);
	msb_byte = VAP_DATA_MISC_MIB_rx_protocol_stack_packets_high_get_indirect(DLRX_VAP_MIB_MISC_BASE(vap), 0);
	msb_byte = msb_byte << W_VAP_DATA_MISC_MIB_rx_protocol_stack_packets_high;
	pdu_data = (msb_byte | lsb_byte);
	pdu_data++;
	VAP_DATA_MISC_MIB_rx_protocol_stack_packets_low_set_indirect(DLRX_VAP_MIB_MISC_BASE(vap), 0, (pdu_data & M_VAP_DATA_MISC_MIB_rx_protocol_stack_packets_low));
	VAP_DATA_MISC_MIB_rx_protocol_stack_packets_high_set_indirect(DLRX_VAP_MIB_MISC_BASE(vap), 0, ((pdu_data >> W_VAP_DATA_MISC_MIB_rx_protocol_stack_packets_high) \
			& M_VAP_DATA_MISC_MIB_rx_protocol_stack_packets_high));

	lsb_byte = VAP_DATA_MISC_MIB_rx_protocol_stack_bytes_low_get_indirect(DLRX_VAP_MIB_MISC_BASE(vap), 0);
	msb_byte = VAP_DATA_MISC_MIB_rx_protocol_stack_bytes_high_get_indirect(DLRX_VAP_MIB_MISC_BASE(vap), 0);
	msb_byte = msb_byte << W_VAP_DATA_MISC_MIB_rx_protocol_stack_bytes_high;
	num_bytes_data = (msb_byte | lsb_byte);
	num_bytes_data += msdu_length;
	VAP_DATA_MISC_MIB_rx_protocol_stack_bytes_low_set_indirect(DLRX_VAP_MIB_MISC_BASE(vap), 0, (num_bytes_data & M_VAP_DATA_MISC_MIB_rx_protocol_stack_bytes_low));
	VAP_DATA_MISC_MIB_rx_protocol_stack_bytes_high_set_indirect(DLRX_VAP_MIB_MISC_BASE(vap), 0, ((num_bytes_data >> W_VAP_DATA_MISC_MIB_rx_protocol_stack_bytes_high) \
			& M_VAP_DATA_MISC_MIB_rx_protocol_stack_bytes_high));
}

/****************************************************************************
Function name: mib_update_vap_forward_data
Description  : Update the mib VAP forward data
Parameters   : msdu_length : msdu length
Return value : None
Functions called by this module:
	None
Notes        : Make sure the vap is set to the correct value in the context
	structure before calling this function. Check the notes of functions
	called for complete list to be set in the context.
****************************************************************************/
extern inline void mib_update_vap_forward_data(unsigned int msdu_length)
{
	unsigned int vap;
	unsigned long long msb_byte;
	unsigned long long lsb_byte;
	unsigned long long pdu_data;
	unsigned long long num_bytes_data;

	vap = DLRX_CTXT_MSG_vap_get_indirect(DLRX_CTXT_MSG_BASE, 0);

	lsb_byte = VAP_DATA_MISC_MIB_rx_forward_packets_low_get_indirect(DLRX_VAP_MIB_MISC_BASE(vap), 0);
	msb_byte = VAP_DATA_MISC_MIB_rx_forward_packets_high_get_indirect(DLRX_VAP_MIB_MISC_BASE(vap), 0);
	msb_byte = msb_byte << W_VAP_DATA_MISC_MIB_rx_forward_packets_high;
	pdu_data = (msb_byte | lsb_byte);
	pdu_data++;
	VAP_DATA_MISC_MIB_rx_forward_packets_low_set_indirect(DLRX_VAP_MIB_MISC_BASE(vap), 0, (pdu_data & M_VAP_DATA_MISC_MIB_rx_forward_packets_low));
	VAP_DATA_MISC_MIB_rx_forward_packets_high_set_indirect(DLRX_VAP_MIB_MISC_BASE(vap), 0, ((pdu_data >> W_VAP_DATA_MISC_MIB_rx_forward_packets_high) \
		& M_VAP_DATA_MISC_MIB_rx_forward_packets_high));

	lsb_byte = VAP_DATA_MISC_MIB_rx_forward_bytes_low_get_indirect(DLRX_VAP_MIB_MISC_BASE(vap), 0);
	msb_byte = VAP_DATA_MISC_MIB_rx_forward_bytes_high_get_indirect(DLRX_VAP_MIB_MISC_BASE(vap), 0);
	msb_byte = msb_byte << W_VAP_DATA_MISC_MIB_rx_forward_bytes_high;
	num_bytes_data = (msb_byte | lsb_byte);
	num_bytes_data += msdu_length;
	VAP_DATA_MISC_MIB_rx_forward_bytes_low_set_indirect(DLRX_VAP_MIB_MISC_BASE(vap), 0, (num_bytes_data & M_VAP_DATA_MISC_MIB_rx_forward_bytes_low));
	VAP_DATA_MISC_MIB_rx_forward_bytes_high_set_indirect(DLRX_VAP_MIB_MISC_BASE(vap), 0, ((num_bytes_data >> W_VAP_DATA_MISC_MIB_rx_forward_bytes_high) \
		 & M_VAP_DATA_MISC_MIB_rx_forward_bytes_high));
}

/**********************************************************************
Module:           mib_update_chained_mpdu
Description:     Increment the total chained mpdu counters
Parameters:     offset : Offset value into the structure
Return value :   None
Functions called by this module: None
Notes:  None
**********************************************************************/
extern inline void mib_update_congestion_drop_packets(void)
{
	unsigned int mib_value;
	mib_value = DLRX_DATA_MIB_rx_drop_congestion_packets_get_indirect(DLRX_DATA_MIB_BASE, 0);
	mib_value++;
	DLRX_DATA_MIB_rx_drop_congestion_packets_set_indirect(DLRX_DATA_MIB_BASE, 0, mib_value);
}

/*****************************************************************************
Function name: ro_list_prepare_rxpb_buf_and_add_to_ro_list
Description  : Prepare the rxpb data and add to ro list
Parameters   : ce5_bufptr, rxpb_buf_ptr, header_switch
Return value : None
Functions called by this module:
	dlrx_add_outgoing_data_to_rxpb_buffer, ro_list_add_data
	rxpb_write_free_buffer_to_rxpb_ptr_ring, mib_update_status_counters
	Notes        : None
****************************************************************************/
extern inline void ro_list_prepare_rxpb_buf_and_add_to_ro_list(
		unsigned int *ce5_buf_ptr,
		unsigned int *rxpb_buf_ptr,
		rx_outgoing_header_switch header_switch
		)
{
	dlrx_add_outgoing_data_to_rxpb_buffer(rxpb_buf_ptr, header_switch);
	if (!(ro_list_add_data(ce5_buf_ptr, rxpb_buf_ptr))) {
		/* Drop the packet due to non availability of linklist ptr */
		/* Not defined in spec flowchart */
		rxpb_write_free_buffer_to_rxpb_ptr_ring(RECYCLE_RXPB_PTR);
		mib_update_status_counters(0, MSDU_STATUS_RO_LINKLIST_DROP);
		pr_info("Insert to ro linklist failed: Header_Switch %u\n",
			header_switch);
	}
}

extern inline uint8_t *dlrx_get_pmac_data_ptr(unsigned int *pmac_data_ptr, unsigned int pmac_ptr_offset)
{
	uint8_t *temp_pmac_ptr;
	temp_pmac_ptr = (uint8_t *)pmac_data_ptr;
	while (pmac_ptr_offset != 0) {
		temp_pmac_ptr--;
		pmac_ptr_offset--;
	}
	return temp_pmac_ptr;
}
extern inline unsigned int dlrx_get_seq_mask(unsigned int peer, unsigned int ext_tid)
{
	unsigned int seq_id_mask;
	unsigned int *seq_mask_base = DLRX_DDR_SEQ_MASK_BASE;
	seq_id_mask = seq_mask_base[(peer * NUM_TID) + ext_tid];

	if ((seq_id_mask == 0) || (seq_id_mask > NUM_SEQ_ID)) {
		if (seq_id_mask != 0)
			pr_err("<%s>: seq_id_mask trouble[%x]peer[%d]ext_tid[%d]\n", __func__,
				seq_id_mask,
				peer,
				ext_tid);
		else if (ext_tid) {
			/* get the first tid */
			seq_id_mask = seq_mask_base[(peer * NUM_TID)];
		}
		if ((seq_id_mask == 0) || (seq_id_mask > NUM_SEQ_ID))
			seq_id_mask = NUM_SEQ_ID;
	}

	seq_id_mask--;
	return seq_id_mask;
}
#endif

