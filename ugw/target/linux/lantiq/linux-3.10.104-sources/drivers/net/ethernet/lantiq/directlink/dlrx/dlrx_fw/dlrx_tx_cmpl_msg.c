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
#include "../include/dlrx_fw_def.h"
#include "../include/dlrx_fw_data_structure_macro.h"
#include "../include/dlrx_fw_data_structure.h"
#include "../include/dlrx_fw_internal_def.h"

#define HTT_TX_COMPL_CTXT_SZ                sizeof(A_UINT16)
#define HTT_TX_COMPL_CTXT_NUM(_bytes)       ((_bytes) >> 1)

#define HTT_TX_COMPL_INV_MSDU_ID            0xffff

#define HTT_TX_COMPL_IND_STAT_OK            0
#define HTT_TX_COMPL_IND_STAT_DISCARD       1
#define HTT_TX_COMPL_IND_STAT_NO_ACK        2
#define HTT_TX_COMPL_IND_STAT_POSTPONE      3
#define HTT_HOST_ONLY_STATUS_CODE_START     128

#define MAX_TX_CMPL_NUM                     1
struct htt_tx_compl_ind_base {
	uint32_t hdr;
	uint16_t payload[MAX_TX_CMPL_NUM];
};

enum htt_tx_status {
	/* ok - successfully sent + acked */
	htt_tx_status_ok = HTT_TX_COMPL_IND_STAT_OK,

	/* discard - not sent (congestion control) */
	htt_tx_status_discard = HTT_TX_COMPL_IND_STAT_DISCARD,

	/* no_ack - sent, but no ack */
	htt_tx_status_no_ack = HTT_TX_COMPL_IND_STAT_NO_ACK,

	/* download_fail - the host could not deliver the tx frame to the target */
	htt_tx_status_download_fail = HTT_HOST_ONLY_STATUS_CODE_START,
};

struct offload_tx_release_t {
	uint8_t reserved1;
	uint8_t num_msdus;
	uint16_t reserved0;
	uint16_t msdu_ids[129 * 2];
};
struct offload_tx_release_t offload_tx_release_data;

void dlrx_tx_cmpl_msg_process(unsigned int *ce5buf_ptr);
void ol_tx_completion_handler_ltq(
	int num_msdus,
	enum htt_tx_status status,
	void *tx_desc_id_iterator);

extern void msg_mib_inc(unsigned int msg_type);
extern uint32_t ppa_dl_dre_txpkt_buf_release(uint32_t num_msdus, uint32_t *msg, uint32_t flags);

/*extern unsigned int peer_vld_check(unsigned int peer_id); */
/*extern void dlrx_playout_process(void); */
/*extern void ro_list_reset(unsigned int peer); */

/*************************************************************************
// Module:          dlrx_tx_cmpl_msg_process
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

void dlrx_tx_cmpl_msg_process(unsigned int *ce5buf_ptr)
{
	int num_msdus;
	enum htt_tx_status status;

	/*Increment message mib for RX Fragment Indication Message */
	msg_mib_inc(HTT_TX_CMP_MSG);

	/* status - no enum translation needed */
	status = DLRX_TX_CMPL_MSG_status_get_indirect(ce5buf_ptr, 0);
	num_msdus = DLRX_TX_CMPL_MSG_pb_ptr_rel_num_get_indirect(ce5buf_ptr, 0);

	if (num_msdus & 0x1) {
		struct htt_tx_compl_ind_base *compl = (struct htt_tx_compl_ind_base *)(ce5buf_ptr + O_DLRX_TX_CMPL_MSG_free_txpb_ptr - 1);

		/*
		       * Host CPU endianness can be different from FW CPU. This
		       * can result in even and odd MSDU IDs being switched. If
		       * this happens, copy the switched final odd MSDU ID from
		       * location payload[size], to location payload[size-1],
		       * where the message handler function expects to find it
		       */
		if (compl->payload[num_msdus] != HTT_TX_COMPL_INV_MSDU_ID) {
			compl->payload[num_msdus - 1] =
				compl->payload[num_msdus];
		}
	}

	ol_tx_completion_handler_ltq(num_msdus, status, ce5buf_ptr + O_DLRX_TX_CMPL_MSG_free_txpb_ptr);

}

void ol_tx_completion_handler_ltq(
	int num_msdus,
	enum htt_tx_status status,
	void *tx_desc_id_iterator)
{
	int i;
	uint16_t *desc_ids = (uint16_t *)tx_desc_id_iterator;
	uint16_t tx_desc_id;

	offload_tx_release_data.num_msdus = (uint8_t)num_msdus;

	for (i = 0; i < num_msdus; i++) {
		tx_desc_id = desc_ids[i];

		if ((i % 2) == 0)
			offload_tx_release_data.msdu_ids[i + 1] = tx_desc_id;
		else
			offload_tx_release_data.msdu_ids[i - 1] = tx_desc_id;
	}

	if (ppa_dl_dre_txpkt_buf_release(num_msdus, (unsigned int *)&offload_tx_release_data, 0))
		pr_err("%s : %d : failed num_msdus: %d\n",
			__func__, __LINE__, num_msdus);

}
