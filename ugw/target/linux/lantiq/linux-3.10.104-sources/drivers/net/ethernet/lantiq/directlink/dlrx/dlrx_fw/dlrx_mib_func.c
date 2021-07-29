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

void mib_clear(int vap);
void msg_mib_inc(unsigned int msg_type);
void struct_val_set(void *struct_addr, int val, unsigned int struct_size);

/*************************************************************************
Module:          struct_val_set
Description:     set value for every byte of a data structure
Parameters:      struct_addr, val, struct_size
Return value :   struct_addr
Functions called by this module:
	None
Notes        :   None
*************************************************************************/
void struct_val_set(void *struct_addr, int val, unsigned int struct_size)
{
	uint8_t *struct_addr_byte_ptr = struct_addr;

	while (struct_size--)
		*struct_addr_byte_ptr++ = val;
}

/*************************************************************************
Module:          mib_clear
Description:     Clear all mibs (including vap mibs, data mibs and
	message mibs)or mib of a particular vap. Vap mib
	structure is shared between directlink rx and tx.
Parameters:      vap (set to vap value if mib_reset_vapreq is set
	or -1 if mib_reset_allreq is set)
Return value :   None
Functions called by this module:
	struct_val_set()
Notes        :   None
*************************************************************************/
void mib_clear(int vap)
{
	int k = 0;

	if (vap == -1) {
		/* Clear vap mib's for all 16 vaps */
		for (k = 0; k < 16; k++) {
			struct_val_set((void *)DLRX_VAP_MIB_BASE(k),
				       0,
				       sizeof(vap_data_mib_t));
			struct_val_set((void *)DLRX_VAP_MIB_MISC_BASE(k),
				       0,
				       sizeof(vap_data_misc_mib_t));
		}

		/* Clear data mib's */
		struct_val_set((void *)DLRX_DATA_MIB_BASE,
			       0,
			       sizeof(dlrx_data_mib_t));
		/* Clear message mib's */
		struct_val_set((void *)DLRX_MSG_MIB_BASE,
			       0,
			       sizeof(dlrx_msg_mib_t));
		/* Clear misc mib's */
		struct_val_set((void *)DLRX_MISC_MIB_BASE,
			       0,
			       sizeof(dlrx_misc_mib_t));
	} else {
		struct_val_set((void *)DLRX_VAP_MIB_BASE(vap),
			       0,
			       sizeof(vap_data_mib_t));
		struct_val_set((void *)DLRX_VAP_MIB_MISC_BASE(vap),
			       0,
			       sizeof(vap_data_misc_mib_t));
	}

	return;
}

/*************************************************************************
Module:          msg_mib_inc
Description:     Increment message mib according to message type.
Parameters:      msg_type
Return value :   None
Functions called by this module:
	None
Notes        :   None
*************************************************************************/
void msg_mib_inc(unsigned int msg_type)
{
	unsigned int msg_mib = 0;

	/* printk("msg_mib_inc = %d\n", msg_type); */
	/* reduce CPU load for critical path */
	if (msg_type == HTT_RX_IND_MSG) {
		msg_mib = DLRX_MSG_MIB_total_rx_ind_msg_get_indirect(DLRX_MSG_MIB_BASE, 0) + 1;
		DLRX_MSG_MIB_total_rx_ind_msg_set_indirect(DLRX_MSG_MIB_BASE, 0, msg_mib);
		return;
	}

	switch (msg_type) {
	case HTT_RX_CPU_CE4:
		msg_mib = DLRX_MSG_MIB_total_ce4_cpu_msg_get_indirect(DLRX_MSG_MIB_BASE, 0) + 1;
		DLRX_MSG_MIB_total_ce4_cpu_msg_set_indirect(DLRX_MSG_MIB_BASE, 0, msg_mib);
		break;

	case HTT_RX_CPU_CE5:
		msg_mib = DLRX_MSG_MIB_total_ce5_cpu_msg_get_indirect(DLRX_MSG_MIB_BASE, 0) + 1;
		DLRX_MSG_MIB_total_ce5_cpu_msg_set_indirect(DLRX_MSG_MIB_BASE, 0, msg_mib);
		break;

	case HTT_RX_FLUSH_MSG:
		msg_mib = DLRX_MSG_MIB_total_rx_flush_msg_get_indirect(DLRX_MSG_MIB_BASE, 0) + 1;
		DLRX_MSG_MIB_total_rx_flush_msg_set_indirect(DLRX_MSG_MIB_BASE, 0, msg_mib);
		break;

	case HTT_TX_CMP_MSG:
		msg_mib = DLRX_MSG_MIB_total_tx_cmp_msg_get_indirect(DLRX_MSG_MIB_BASE, 0) + 1;
		DLRX_MSG_MIB_total_tx_cmp_msg_set_indirect(DLRX_MSG_MIB_BASE, 0, msg_mib);
		break;

	case HTT_RX_IND_MSG_WLAN:
		msg_mib = DLRX_MSG_MIB_total_rx_ind_wlan_msg_get_indirect(DLRX_MSG_MIB_BASE, 0) + 1;
		DLRX_MSG_MIB_total_rx_ind_wlan_msg_set_indirect(DLRX_MSG_MIB_BASE, 0, msg_mib);
		break;

	case HTT_RX_FLUSH_MSG_WLAN:
		msg_mib = DLRX_MSG_MIB_total_rx_flush_wlan_msg_get_indirect(DLRX_MSG_MIB_BASE, 0) + 1;
		DLRX_MSG_MIB_total_rx_flush_wlan_msg_set_indirect(DLRX_MSG_MIB_BASE, 0, msg_mib);
		break;

	case HTT_RX_FRAG_IND_MSG:
		msg_mib = DLRX_MSG_MIB_total_rx_frag_ind_msg_get_indirect(DLRX_MSG_MIB_BASE, 0) + 1;
		DLRX_MSG_MIB_total_rx_frag_ind_msg_set_indirect(DLRX_MSG_MIB_BASE, 0, msg_mib);
		break;

	case HTT_RX_INVALID_TID:
		msg_mib = DLRX_MSG_MIB_total_rx_invalid_tid_msg_get_indirect(DLRX_MSG_MIB_BASE, 0) + 1;
		DLRX_MSG_MIB_total_rx_invalid_tid_msg_set_indirect(DLRX_MSG_MIB_BASE, 0, msg_mib);
		break;

	default:
		break;
	}

	return;
}

/******************************************************************************
Function name: mib_update_vap_dlrx_data
Description  : Update the mib VAP data
Parameters   : msdu_length : msdu length
	packet_drop_reason: Used to find if packet is dropped or not and
	update the corresponding counters.
Return value : None
Functions called by this module:
	None
Notes        : Make sure the vap, discard, forward, inspect is set to the
	correct value in the context structure before calling this
	function. Check the notes of functions called for
	complete list to be set in the context.
******************************************************************************/
void mib_update_vap_dlrx_data(
	unsigned int msdu_length,
	dlrx_packet_drop_reason packet_drop_reason)
{
	unsigned int vap;
	unsigned int discard;
	unsigned int forward;
	unsigned int inspect;
	unsigned long long msb_byte;
	unsigned long long lsb_byte;
	unsigned long long pdu_data;
	unsigned long long num_bytes_data;

	vap = DLRX_CTXT_MSG_vap_get_indirect(DLRX_CTXT_MSG_BASE, 0);

	if (!packet_drop_reason) {
		discard = DLRX_CTXT_MSG_discard_get_indirect(DLRX_CTXT_MSG_BASE, 0);
		forward = DLRX_CTXT_MSG_forward_get_indirect(DLRX_CTXT_MSG_BASE, 0);
		inspect = DLRX_CTXT_MSG_inspect_get_indirect(DLRX_CTXT_MSG_BASE, 0);

		if (!discard) {
			lsb_byte = VAP_DATA_MIB_rx_rcv_pdu_low_get_indirect(DLRX_VAP_MIB_BASE(vap), 0);
			msb_byte = VAP_DATA_MIB_rx_rcv_pdu_high_get_indirect(DLRX_VAP_MIB_BASE(vap), 0);
			msb_byte = msb_byte << W_VAP_DATA_MIB_rx_rcv_pdu_high;
			pdu_data = (msb_byte | lsb_byte);
			pdu_data++;
			VAP_DATA_MIB_rx_rcv_pdu_low_set_indirect(DLRX_VAP_MIB_BASE(vap), 0, (pdu_data & M_VAP_DATA_MIB_rx_rcv_pdu_low));
			VAP_DATA_MIB_rx_rcv_pdu_high_set_indirect(DLRX_VAP_MIB_BASE(vap), 0, ((pdu_data >> W_VAP_DATA_MIB_rx_rcv_pdu_high) \
					& M_VAP_DATA_MIB_rx_rcv_pdu_high));
			lsb_byte = VAP_DATA_MIB_rx_rcv_bytes_low_get_indirect(DLRX_VAP_MIB_BASE(vap), 0);
			msb_byte = VAP_DATA_MIB_rx_rcv_bytes_high_get_indirect(DLRX_VAP_MIB_BASE(vap), 0);
			msb_byte = msb_byte << W_VAP_DATA_MIB_rx_rcv_bytes_high;
			num_bytes_data = (msb_byte | lsb_byte);
			num_bytes_data += msdu_length;
			VAP_DATA_MIB_rx_rcv_bytes_low_set_indirect(DLRX_VAP_MIB_BASE(vap), 0, (num_bytes_data & M_VAP_DATA_MIB_rx_rcv_bytes_low));
			VAP_DATA_MIB_rx_rcv_bytes_high_set_indirect(DLRX_VAP_MIB_BASE(vap), 0, ((num_bytes_data >> W_VAP_DATA_MIB_rx_rcv_bytes_high) \
					& M_VAP_DATA_MIB_rx_rcv_bytes_high));
		} else {
			lsb_byte = VAP_DATA_MIB_rx_discard_pdu_low_get_indirect(DLRX_VAP_MIB_BASE(vap), 0);
			msb_byte = VAP_DATA_MIB_rx_discard_pdu_high_get_indirect(DLRX_VAP_MIB_BASE(vap), 0);
			msb_byte = msb_byte << W_VAP_DATA_MIB_rx_discard_pdu_high;
			pdu_data = (msb_byte | lsb_byte);
			pdu_data++;
			VAP_DATA_MIB_rx_discard_pdu_low_set_indirect(DLRX_VAP_MIB_BASE(vap), 0, (pdu_data & M_VAP_DATA_MIB_rx_discard_pdu_low));
			VAP_DATA_MIB_rx_discard_pdu_high_set_indirect(DLRX_VAP_MIB_BASE(vap), 0, ((pdu_data >> W_VAP_DATA_MIB_rx_discard_pdu_high) \
					& M_VAP_DATA_MIB_rx_discard_pdu_high));

			lsb_byte = VAP_DATA_MIB_rx_discard_bytes_low_get_indirect(DLRX_VAP_MIB_BASE(vap), 0);
			msb_byte = VAP_DATA_MIB_rx_discard_bytes_high_get_indirect(DLRX_VAP_MIB_BASE(vap), 0);
			msb_byte = msb_byte << W_VAP_DATA_MIB_rx_discard_bytes_high;
			num_bytes_data = (msb_byte | lsb_byte);
			num_bytes_data += msdu_length;
			VAP_DATA_MIB_rx_discard_bytes_low_set_indirect(DLRX_VAP_MIB_BASE(vap), 0, (num_bytes_data & M_VAP_DATA_MIB_rx_discard_bytes_low));
			VAP_DATA_MIB_rx_discard_bytes_high_set_indirect(DLRX_VAP_MIB_BASE(vap), 0, ((num_bytes_data >> W_VAP_DATA_MIB_rx_discard_bytes_high) \
					& M_VAP_DATA_MIB_rx_discard_bytes_high));
		}

		if (forward) {
			lsb_byte = VAP_DATA_MIB_rx_fwd_pdu_low_get_indirect(DLRX_VAP_MIB_BASE(vap), 0);
			msb_byte = VAP_DATA_MIB_rx_fwd_pdu_high_get_indirect(DLRX_VAP_MIB_BASE(vap), 0);
			msb_byte = msb_byte << W_VAP_DATA_MIB_rx_fwd_pdu_high;
			pdu_data = (msb_byte | lsb_byte);
			pdu_data++;
			VAP_DATA_MIB_rx_fwd_pdu_low_set_indirect(DLRX_VAP_MIB_BASE(vap), 0, (pdu_data & M_VAP_DATA_MIB_rx_fwd_pdu_low));
			VAP_DATA_MIB_rx_fwd_pdu_high_set_indirect(DLRX_VAP_MIB_BASE(vap), 0, ((pdu_data >> W_VAP_DATA_MIB_rx_fwd_pdu_high) \
					& M_VAP_DATA_MIB_rx_fwd_pdu_high));

			lsb_byte = VAP_DATA_MIB_rx_fwd_bytes_low_get_indirect(DLRX_VAP_MIB_BASE(vap), 0);
			msb_byte = VAP_DATA_MIB_rx_fwd_bytes_high_get_indirect(DLRX_VAP_MIB_BASE(vap), 0);
			msb_byte = msb_byte << W_VAP_DATA_MIB_rx_fwd_bytes_high;
			num_bytes_data = (msb_byte | lsb_byte);
			num_bytes_data += msdu_length;
			VAP_DATA_MIB_rx_fwd_bytes_low_set_indirect(DLRX_VAP_MIB_BASE(vap), 0, (num_bytes_data & M_VAP_DATA_MIB_rx_fwd_bytes_low));
			VAP_DATA_MIB_rx_fwd_bytes_high_set_indirect(DLRX_VAP_MIB_BASE(vap), 0, ((num_bytes_data >> W_VAP_DATA_MIB_rx_fwd_bytes_high) \
					& M_VAP_DATA_MIB_rx_fwd_bytes_high));
		}

		if (inspect) {

			lsb_byte = VAP_DATA_MIB_rx_inspect_pdu_low_get_indirect(DLRX_VAP_MIB_BASE(vap), 0);
			msb_byte = VAP_DATA_MIB_rx_inspect_pdu_high_get_indirect(DLRX_VAP_MIB_BASE(vap), 0);
			msb_byte = msb_byte << W_VAP_DATA_MIB_rx_inspect_pdu_high;
			pdu_data = (msb_byte | lsb_byte);
			pdu_data++;
			VAP_DATA_MIB_rx_inspect_pdu_low_set_indirect(DLRX_VAP_MIB_BASE(vap), 0, (pdu_data & M_VAP_DATA_MIB_rx_inspect_pdu_low));
			VAP_DATA_MIB_rx_inspect_pdu_high_set_indirect(DLRX_VAP_MIB_BASE(vap), 0, ((pdu_data >> W_VAP_DATA_MIB_rx_inspect_pdu_high) \
					& M_VAP_DATA_MIB_rx_inspect_pdu_high));

			lsb_byte = VAP_DATA_MIB_rx_inspect_bytes_low_get_indirect(DLRX_VAP_MIB_BASE(vap), 0);
			msb_byte = VAP_DATA_MIB_rx_inspect_bytes_high_get_indirect(DLRX_VAP_MIB_BASE(vap), 0);
			msb_byte = msb_byte << W_VAP_DATA_MIB_rx_inspect_bytes_high;
			num_bytes_data = (msb_byte | lsb_byte);
			num_bytes_data += msdu_length;
			VAP_DATA_MIB_rx_inspect_bytes_low_set_indirect(DLRX_VAP_MIB_BASE(vap), 0, (num_bytes_data & M_VAP_DATA_MIB_rx_inspect_bytes_low));
			VAP_DATA_MIB_rx_inspect_bytes_high_set_indirect(DLRX_VAP_MIB_BASE(vap), 0, ((num_bytes_data >> W_VAP_DATA_MIB_rx_inspect_bytes_high) \
					& M_VAP_DATA_MIB_rx_inspect_bytes_high));
		}
	}

	if (packet_drop_reason == WRONG_PN_SEQUENCE) {
		lsb_byte = VAP_DATA_MIB_rx_pn_pdu_low_get_indirect(DLRX_VAP_MIB_BASE(vap), 0);
		msb_byte = VAP_DATA_MIB_rx_pn_pdu_high_get_indirect(DLRX_VAP_MIB_BASE(vap), 0);
		msb_byte = msb_byte << W_VAP_DATA_MIB_rx_pn_pdu_high;
		pdu_data = (msb_byte | lsb_byte);
		pdu_data++;
		VAP_DATA_MIB_rx_pn_pdu_low_set_indirect(DLRX_VAP_MIB_BASE(vap), 0, (pdu_data & M_VAP_DATA_MIB_rx_pn_pdu_low));
		VAP_DATA_MIB_rx_pn_pdu_high_set_indirect(DLRX_VAP_MIB_BASE(vap), 0, ((pdu_data >> W_VAP_DATA_MIB_rx_pn_pdu_high) \
				& M_VAP_DATA_MIB_rx_pn_pdu_high));

		lsb_byte = VAP_DATA_MIB_rx_pn_bytes_low_get_indirect(DLRX_VAP_MIB_BASE(vap), 0);
		msb_byte = VAP_DATA_MIB_rx_pn_bytes_high_get_indirect(DLRX_VAP_MIB_BASE(vap), 0);
		msb_byte = msb_byte << W_VAP_DATA_MIB_rx_pn_bytes_high;
		num_bytes_data = (msb_byte | lsb_byte);
		num_bytes_data += msdu_length;
		VAP_DATA_MIB_rx_pn_bytes_low_set_indirect(DLRX_VAP_MIB_BASE(vap), 0, (num_bytes_data & M_VAP_DATA_MIB_rx_pn_bytes_low));
		VAP_DATA_MIB_rx_pn_bytes_high_set_indirect(DLRX_VAP_MIB_BASE(vap), 0, ((num_bytes_data >> W_VAP_DATA_MIB_rx_pn_bytes_high) \
				& M_VAP_DATA_MIB_rx_pn_bytes_high));
	} else if (packet_drop_reason == DMA_TX_CHANNEL_FULL) {
		lsb_byte = VAP_DATA_MIB_rx_drop_pdu_low_get_indirect(DLRX_VAP_MIB_BASE(vap), 0);
		msb_byte = VAP_DATA_MIB_rx_drop_pdu_high_get_indirect(DLRX_VAP_MIB_BASE(vap), 0);
		msb_byte = msb_byte << W_VAP_DATA_MIB_rx_drop_pdu_high;
		pdu_data = (msb_byte | lsb_byte);
		pdu_data++;
		VAP_DATA_MIB_rx_drop_pdu_low_set_indirect(DLRX_VAP_MIB_BASE(vap), 0, (pdu_data & M_VAP_DATA_MIB_rx_drop_pdu_low));
		VAP_DATA_MIB_rx_drop_pdu_high_set_indirect(DLRX_VAP_MIB_BASE(vap), 0, ((pdu_data >> W_VAP_DATA_MIB_rx_drop_pdu_high) \
				& M_VAP_DATA_MIB_rx_drop_pdu_high));

		lsb_byte = VAP_DATA_MIB_rx_drop_bytes_low_get_indirect(DLRX_VAP_MIB_BASE(vap), 0);
		msb_byte = VAP_DATA_MIB_rx_drop_bytes_high_get_indirect(DLRX_VAP_MIB_BASE(vap), 0);
		msb_byte = msb_byte << W_VAP_DATA_MIB_rx_drop_bytes_high;
		num_bytes_data = (msb_byte | lsb_byte);
		num_bytes_data += msdu_length;
		VAP_DATA_MIB_rx_drop_bytes_low_set_indirect(DLRX_VAP_MIB_BASE(vap), 0, (num_bytes_data & M_VAP_DATA_MIB_rx_drop_bytes_low));
		VAP_DATA_MIB_rx_drop_bytes_high_set_indirect(DLRX_VAP_MIB_BASE(vap), 0, ((num_bytes_data >> W_VAP_DATA_MIB_rx_drop_bytes_high) \
				& M_VAP_DATA_MIB_rx_drop_bytes_high));
	}
}

/**************************************************************************************
Function name: mib_update_status_counters
Description  : Update the mib status counters
Parameters   : switch_value : Used to determine if msdu or mpdu counters need to
be updated.
status_value : Used to update the corresponding status counters
Return value : None
Functions called by this module:
None
Notes        : None
***************************************************************************************/
void mib_update_status_counters(mib_msdu_mpdu_update_switch switch_value, unsigned int status_value)
{
	unsigned int counter_value;

	switch (status_value) {
	case MPDU_STATUS_SUCCESS:
		if (switch_value == UPDATE_MSDU_MIB) {
			counter_value = DLRX_DATA_MIB_rx_success_msdu_get_indirect(DLRX_DATA_MIB_BASE, 0);
			counter_value++;
			DLRX_DATA_MIB_rx_success_msdu_set_indirect(DLRX_DATA_MIB_BASE, 0, counter_value);
		} else if (switch_value == UPDATE_MPDU_MIB) {
			counter_value = DLRX_DATA_MIB_rx_success_mpdu_get_indirect(DLRX_DATA_MIB_BASE, 0);
			counter_value++;
			DLRX_DATA_MIB_rx_success_mpdu_set_indirect(DLRX_DATA_MIB_BASE, 0, counter_value);
		}

		break;

	case MPDU_STATUS_FCS_ERROR:
		if (switch_value == UPDATE_MSDU_MIB) {
			counter_value = DLRX_DATA_MIB_rx_error2_msdu_get_indirect(DLRX_DATA_MIB_BASE, 0);
			counter_value++;
			DLRX_DATA_MIB_rx_error2_msdu_set_indirect(DLRX_DATA_MIB_BASE, 0, counter_value);
		} else if (switch_value == UPDATE_MPDU_MIB) {
			counter_value = DLRX_DATA_MIB_rx_error2_mpdu_get_indirect(DLRX_DATA_MIB_BASE, 0);
			counter_value++;
			DLRX_DATA_MIB_rx_error2_mpdu_set_indirect(DLRX_DATA_MIB_BASE, 0, counter_value);
		}

		break;

	case MPDU_STATUS_DUPLICATE_ERROR:
		if (switch_value == UPDATE_MSDU_MIB) {
			counter_value = DLRX_DATA_MIB_rx_error3_msdu_get_indirect(DLRX_DATA_MIB_BASE, 0);
			counter_value++;
			DLRX_DATA_MIB_rx_error3_msdu_set_indirect(DLRX_DATA_MIB_BASE, 0, counter_value);
		} else if (switch_value == UPDATE_MPDU_MIB) {
			counter_value = DLRX_DATA_MIB_rx_error3_mpdu_get_indirect(DLRX_DATA_MIB_BASE, 0);
			counter_value++;
			DLRX_DATA_MIB_rx_error3_mpdu_set_indirect(DLRX_DATA_MIB_BASE, 0, counter_value);
		}

		break;

	case MPDU_STATUS_REPLAY_ERROR:
		if (switch_value == UPDATE_MSDU_MIB) {
			counter_value = DLRX_DATA_MIB_rx_error4_msdu_get_indirect(DLRX_DATA_MIB_BASE, 0);
			counter_value++;
			DLRX_DATA_MIB_rx_error4_msdu_set_indirect(DLRX_DATA_MIB_BASE, 0, counter_value);
		} else if (switch_value == UPDATE_MPDU_MIB) {
			counter_value = DLRX_DATA_MIB_rx_error4_mpdu_get_indirect(DLRX_DATA_MIB_BASE, 0);
			counter_value++;
			DLRX_DATA_MIB_rx_error4_mpdu_set_indirect(DLRX_DATA_MIB_BASE, 0, counter_value);
		}

		break;

	case MPDU_STATUS_INVALID_PEER:
		if (switch_value == UPDATE_MSDU_MIB) {
			counter_value = DLRX_DATA_MIB_rx_error5_msdu_get_indirect(DLRX_DATA_MIB_BASE, 0);
			counter_value++;
			DLRX_DATA_MIB_rx_error5_msdu_set_indirect(DLRX_DATA_MIB_BASE, 0, counter_value);
		} else if (switch_value == UPDATE_MPDU_MIB) {
			counter_value = DLRX_DATA_MIB_rx_error5_mpdu_get_indirect(DLRX_DATA_MIB_BASE, 0);
			counter_value++;
			DLRX_DATA_MIB_rx_error5_mpdu_set_indirect(DLRX_DATA_MIB_BASE, 0, counter_value);
		}

		break;

	case MPDU_STATUS_UNAUTHORIZED_PEER:
		if (switch_value == UPDATE_MSDU_MIB) {
			counter_value = DLRX_DATA_MIB_rx_error6_msdu_get_indirect(DLRX_DATA_MIB_BASE, 0);
			counter_value++;
			DLRX_DATA_MIB_rx_error6_msdu_set_indirect(DLRX_DATA_MIB_BASE, 0, counter_value);
		} else if (switch_value == UPDATE_MPDU_MIB) {
			counter_value = DLRX_DATA_MIB_rx_error6_mpdu_get_indirect(DLRX_DATA_MIB_BASE, 0);
			counter_value++;
			DLRX_DATA_MIB_rx_error6_mpdu_set_indirect(DLRX_DATA_MIB_BASE, 0, counter_value);
		}

		break;

	case MPDU_STATUS_OUT_OF_SYNC_PEER:
		if (switch_value == UPDATE_MSDU_MIB) {
			counter_value = DLRX_DATA_MIB_rx_error7_msdu_get_indirect(DLRX_DATA_MIB_BASE, 0);
			counter_value++;
			DLRX_DATA_MIB_rx_error7_msdu_set_indirect(DLRX_DATA_MIB_BASE, 0, counter_value);
		} else if (switch_value == UPDATE_MPDU_MIB) {
			counter_value = DLRX_DATA_MIB_rx_error7_mpdu_get_indirect(DLRX_DATA_MIB_BASE, 0);
			counter_value++;
			DLRX_DATA_MIB_rx_error7_mpdu_set_indirect(DLRX_DATA_MIB_BASE, 0, counter_value);
		}

		break;

	case MPDU_STATUS_MANAGEMENT_CONTROL:
		if (switch_value == UPDATE_MSDU_MIB) {
			counter_value = DLRX_DATA_MIB_rx_error8_msdu_get_indirect(DLRX_DATA_MIB_BASE, 0);
			counter_value++;
			DLRX_DATA_MIB_rx_error8_msdu_set_indirect(DLRX_DATA_MIB_BASE, 0, counter_value);
		} else if (switch_value == UPDATE_MPDU_MIB) {
			counter_value = DLRX_DATA_MIB_rx_error8_mpdu_get_indirect(DLRX_DATA_MIB_BASE, 0);
			counter_value++;
			DLRX_DATA_MIB_rx_error8_mpdu_set_indirect(DLRX_DATA_MIB_BASE, 0, counter_value);
		}

		break;

	case MPDU_STATUS_TKIP_MIB_ERROR:
		if (switch_value == UPDATE_MSDU_MIB) {
			counter_value = DLRX_DATA_MIB_rx_error9_msdu_get_indirect(DLRX_DATA_MIB_BASE, 0);
			counter_value++;
			DLRX_DATA_MIB_rx_error9_msdu_set_indirect(DLRX_DATA_MIB_BASE, 0, counter_value);
		} else if (switch_value == UPDATE_MPDU_MIB) {
			counter_value = DLRX_DATA_MIB_rx_error9_mpdu_get_indirect(DLRX_DATA_MIB_BASE, 0);
			counter_value++;
			DLRX_DATA_MIB_rx_error9_mpdu_set_indirect(DLRX_DATA_MIB_BASE, 0, counter_value);
		}

		break;

	case MPDU_STATUS_DECRYPT_ERROR:
		if (switch_value == UPDATE_MSDU_MIB) {
			counter_value = DLRX_DATA_MIB_rx_errora_msdu_get_indirect(DLRX_DATA_MIB_BASE, 0);
			counter_value++;
			DLRX_DATA_MIB_rx_errora_msdu_set_indirect(DLRX_DATA_MIB_BASE, 0, counter_value);
		} else if (switch_value == UPDATE_MPDU_MIB) {
			counter_value = DLRX_DATA_MIB_rx_errora_mpdu_get_indirect(DLRX_DATA_MIB_BASE, 0);
			counter_value++;
			DLRX_DATA_MIB_rx_errora_mpdu_set_indirect(DLRX_DATA_MIB_BASE, 0, counter_value);
		}

		break;

	case MSDU_STATUS_ERROR_5_DROP:
		counter_value = DLRX_DATA_MIB_rx_drop_error5_get_indirect(DLRX_DATA_MIB_BASE, 0);
		counter_value++;
		DLRX_DATA_MIB_rx_drop_error5_set_indirect(DLRX_DATA_MIB_BASE, 0, counter_value);
		break;

	case MSDU_STATUS_RO_LINKLIST_DROP:
		counter_value = DLRX_DATA_MIB_rx_drop_ro_linklist_get_indirect(DLRX_DATA_MIB_BASE, 0);
		counter_value++;
		DLRX_DATA_MIB_rx_drop_ro_linklist_set_indirect(DLRX_DATA_MIB_BASE, 0, counter_value);
		break;

	default:
		/* Should not reach here */
		break;
	}
}

