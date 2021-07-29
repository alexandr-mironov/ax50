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
#include "../include/dlrx_fw_data_structure_macro.h"
#include "../include/dlrx_fw_data_structure.h"
#include "../include/dlrx_fw_internal_def.h"
#include "../include/dlrx_dre_api.h"

int dlrx_main(void);
void peer_reset_check(void);
void peer_reset(unsigned int *ptr);
void mib_reset_check(void);
extern void mib_clear(int vap);
void ce5_write_index_update(unsigned int *ce5_parsing_index_ptr);

extern void dlrx_rx_flush_msg_process(unsigned int *ce5buf_ptr);
extern void dlrx_rx_frag_ind_msg_process(unsigned int *ce5buf_ptr);

extern void dlrx_tx_cmpl_msg_process(unsigned int *ce5buf_ptr);

extern void dlrx_tx_cmp_msg_process(unsigned int *ce5buf_ptr);
extern void dlrx_ind_msg_process(unsigned int *ce5buf_ptr);
extern void msg_mib_inc(unsigned int msg_type);
extern void ro_list_reset(unsigned int peer);
extern int ppa_dl_dre_wlan_msg_send(unsigned int msg_type,
				    unsigned int msg_ptr,
				    unsigned int msg_len,
				    unsigned int flags);

unsigned int *ddr_base, *pcie_base, *cfg_ctxt_base;
unsigned int *congestion_register_addr;

/***********************************************************************
Function name:   dlrx_main
Description:     Check message type and call corresponding function for
	processing each type of message
Parameters:      None
Return value :   0
Functions called by this module:
	peer_reset_check()
	mib_reset_check()
	dlrx_ind_msg_process()
	dlrx_flush_msg_process()
	dlrx_frag_ind_msg_process()
	dlrx_cmp_msg_process()
Notes:           cfg_badr_ce5des, cfg_badr_ce5buf and cfg_size_ce5buf
	should be set to the correct value by driver in the
	context structure before calling this function. Check
	the notes of functions called for complete list to be
	set in the context.
************************************************************************/
int dlrx_main(void)
{
	unsigned int ce5_parsing_index;
	unsigned int ptr_in_ce5_ring;
	/* printk("dlrx_main_called\n"); */
	if (DLRX_CFG_GLOBAL_dlrx_enable_get_indirect(DLRX_CFG_GLOBAL_BASE, 0)) {
		ce5_parsing_index = DLRX_CFG_CTXT_CE5BUF_local_ce5_parsing_index_get_indirect(DLRX_CFG_CTXT_CE5BUF_BASE, 0);
		/* Check CE5 message status */
		/* Read unload from memory during every iteration */
		while (((*DLRX_TARGET_CE5_READ_INDEX(g_ce5_offset))
				!= ce5_parsing_index)
			&& !global_debug_flag
			&& !(DLRX_CFG_GLOBAL_dlrx_cfg_unload_get_indirect(DLRX_CFG_GLOBAL_BASE, 0))) {
			unsigned int *ce5buf_ptr;
			unsigned int *ce5des_ptr;
			unsigned int msg_len;
			unsigned int msg_type = 0;

			/* Check if the consumed segments in the
			switch buffer is below threshold.
			If not wait for the value to come below threshold
			If timeout occurs return
			*/
#ifdef USING_BBCPU_SRAM
			ce5des_ptr = ((unsigned int *)(g_cfg_badr_ce5des)
							      + (ce5_parsing_index << 1));
#else
			ce5des_ptr = ((unsigned int *)UNCACHE_ADDR(g_cfg_badr_ce5des)
				      + (ce5_parsing_index << 1));
#endif
			msg_len = DLRX_CE5DES_FORMAT_nbytes_get_indirect(ce5des_ptr, 0);
			ptr_in_ce5_ring = DLRX_CE5DES_FORMAT_dest_ptr_get_indirect(ce5des_ptr, 0);

			DLRX_CFG_CTXT_CE5DES_msg_len_set_indirect(DLRX_CFG_CTXT_CE5DES_BASE, 0, msg_len);

			/* Note: cfg_size_ce5buf is the number of bytes in power of 2 */
			ce5buf_ptr = (unsigned int *)((uint8_t *)g_cfg_badr_ce5buf
						      + (ce5_parsing_index << GET_CE5BUF_SIZE_SHIFT));
			/*
			printk("ce5des_ptr=0x%x, msg_len=0x%x\n",
				ce5des_ptr, msg_len);*/

			if (msg_len) {
				/* TODO: remove */
#if !defined(CONFIG_ACCL_11AC_CS2)
				dre_dma_unmap((unsigned int)ce5buf_ptr, msg_len + 4);
#endif
				msg_type = DLRX_IND_MSG_msg_type_get_indirect(ce5buf_ptr, 0);

				if (DLRX_CFG_GLOBAL_dlrx_enable_get_indirect(DLRX_CFG_GLOBAL_BASE, 0) == 0xf)
					pr_info("ce5des_ptr=0x%p, msg_type= 0x%x ,msg_len=0x%x\n",
						ce5des_ptr, msg_type, msg_len);

				if ((ptr_in_ce5_ring != ((unsigned int)VIR_TO_PHY(ce5buf_ptr)))
				    || ((msg_type == 0xFF) && (msg_len))) {
					pr_info("ptr_in_ce5_ring: 0x%x ce5buf_ptr: 0x%x\n",
						ptr_in_ce5_ring,
						((unsigned int)VIR_TO_PHY(ce5buf_ptr)));
					pr_info("Msg type: 0x%x msg_len: %u\n",
						msg_type,
						msg_len);
					global_debug_flag = 1;
					break;
				}
				/*
				pr_err("Msg type: 0x%x msg_len: %u\n",
										msg_type,
										msg_len);*/
				DLRX_CFG_CTXT_CE5BUF_ce5_msg_type_set_indirect(DLRX_CFG_CTXT_CE5BUF_BASE, 0, msg_type);

				/* TODO: DEBUG */
				if (DLRX_CFG_GLOBAL_dltx_enable_get_indirect(DLRX_CFG_GLOBAL_BASE, 0)) {
					switch (msg_type) {
					case HTT_RX_IND_MSG:
						g_congestion_timeout_num = 0;
						g_congestion_drop_flag = 0;
						dlrx_ind_msg_process(ce5buf_ptr);
						break;

					case HTT_RX_FLUSH_MSG:
						dlrx_rx_flush_msg_process(ce5buf_ptr);
						break;

					case HTT_RX_FRAG_IND_MSG:
						dlrx_rx_frag_ind_msg_process(ce5buf_ptr);
						break;

					case HTT_TX_CMP_MSG:
#if defined(CONFIG_ACCL_11AC_CS2)
						break;
#else
						dlrx_tx_cmpl_msg_process(ce5buf_ptr);
						break;
#endif
#if defined(CONFIG_ACCL_11AC_CS2)
					case HTT_TX_T2H_MSG_TYPE_TX_INSPECT_IND:
					case HTT_TX_T2H_MSG_TYPE_TX_FETCH_CONF:
					case HTT_TX_T2H_MSG_TYPE_TX_MODE_SWITCH_IND:
						break;
#endif
					default:
						/*Increment message mib for WLAN
						(Not TX complete, not RX indication,
						not RX fragment indication, not RX flush)
						*/
						msg_mib_inc(HTT_RX_CPU_CE5);
						/* call driver API to send message to wlan driver */
						ppa_dl_dre_wlan_msg_send(msg_type,
									 (unsigned int)ce5buf_ptr,
									 msg_len,
									 0);
						break;
					}
				} else if (msg_type == HTT_TX_CMP_MSG) {/* always send to QCA */
#if !defined(CONFIG_ACCL_11AC_CS2)
					dlrx_tx_cmpl_msg_process(ce5buf_ptr);
#endif
				}
				else
					ppa_dl_dre_wlan_msg_send(msg_type,
								 (unsigned int)ce5buf_ptr,
								 msg_len,
								 0);

#if defined(CONFIG_ACCL_11AC_CS2)
				if (msg_type != HTT_TX_CMP_MSG)
					dre_dma_wback_invalidate((unsigned int)ce5buf_ptr, msg_len + 4);
#else
				dre_dma_wback_invalidate((unsigned int)ce5buf_ptr, msg_len + 4);
#endif
			} 	else { /* if(msg_len) */
				/* this may be the TX Completion */
				ce5_write_index_update(&ce5_parsing_index);
				continue;
			}


#if defined(CONFIG_ACCL_11AC_CS2)
			if (msg_type != HTT_TX_CMP_MSG
					&& msg_type != HTT_TX_T2H_MSG_TYPE_TX_INSPECT_IND
					&& msg_type != HTT_TX_T2H_MSG_TYPE_TX_FETCH_CONF
					&& msg_type != HTT_TX_T2H_MSG_TYPE_TX_MODE_SWITCH_IND)
				DLRX_IND_MSG_msg_type_set_indirect((unsigned int *)UNCACHE_ADDR(ce5buf_ptr), 0, 0xFF);
#else
			DLRX_IND_MSG_msg_type_set_indirect((unsigned int *)UNCACHE_ADDR(ce5buf_ptr), 0, 0xFF);
#endif

#if defined(CONFIG_ACCL_11AC_CS2)
			if (msg_type != HTT_TX_CMP_MSG
					&& msg_type != HTT_TX_T2H_MSG_TYPE_TX_INSPECT_IND
					&& msg_type != HTT_TX_T2H_MSG_TYPE_TX_FETCH_CONF
					&& msg_type != HTT_TX_T2H_MSG_TYPE_TX_MODE_SWITCH_IND)
				DLRX_CE5DES_FORMAT_nbytes_set_indirect(ce5des_ptr, 0, 0);
#else
			DLRX_CE5DES_FORMAT_nbytes_set_indirect(ce5des_ptr, 0, 0);
#endif
			ce5_write_index_update(&ce5_parsing_index);
		}

		if (DLRX_CFG_GLOBAL_debug_print_enable_get_indirect(DLRX_CFG_GLOBAL_BASE, 0)) {
#if defined(DRE_DBG_PRINT_ENABLE) && DRE_DBG_PRINT_ENABLE
			dlrx_generate_debug(0);
#endif
			DLRX_CFG_GLOBAL_debug_print_enable_set_indirect(DLRX_CFG_GLOBAL_BASE, 0, 0);
		}

		peer_reset_check();

		mib_reset_check();
	} /* if(DLRX_ENABLE) */

	return 0;
}

/*************************************************************************
Function name:   peer_reset_check
Description:     Check whether need to execute peer_reset or
	invalid tid reset
Parameters:      None
Return value :   None
Functions called by this module:
	peer_reset()
Notes        :   req and peer should be configured by driver in the event
	of peer_reset and by firmware in the event of invalid
	peer.
*************************************************************************/
void peer_reset_check(void)
{
	/*If peer reset or invalid TI
	Scan reorder main list and reorder link list of
	all TID of this peer. Free all valid packet buffer
	pointer used. Free used reorder link list entry.
	*/
	if (DLRX_CFG_PEER_RESET_req_get_indirect(DLRX_CFG_PEER_RESET_BASE, 0))
		peer_reset((unsigned int *)DLRX_CFG_PEER_RESET_BASE);
	else if (DLRX_CFG_INVALID_TID_req_get_indirect(DLRX_CFG_INVALID_TID_BASE, 0)) {
		peer_reset((unsigned int *)DLRX_CFG_INVALID_TID_BASE);
		msg_mib_inc(HTT_RX_INVALID_TID);
	}

	return;
}

/*************************************************************************
Function name:   mib_reset_check
Description:     Check whether need to execute mib_reset
Parameters:      None
Return value :   None
Functions called by this module:
	mib_clear()
Notes        :   allreq or vapreq and vap should be configured by driver
	in the event of requesting to reset the mib
*************************************************************************/
void mib_reset_check(void)
{
	if (DLRX_CFG_MIB_RESET_allreq_get_indirect(DLRX_CFG_MIB_RESET_BASE, 0)) {
		mib_clear(-1);
		/* Clear all mib reset request */
		DLRX_CFG_MIB_RESET_allreq_clear_indirect(DLRX_CFG_MIB_RESET_BASE, 0);
	} else if (DLRX_CFG_MIB_RESET_vapreq_get_indirect(DLRX_CFG_MIB_RESET_BASE, 0)) {
		unsigned int vap;
		/* Clear VAP MIB */
		vap = DLRX_CFG_MIB_RESET_vap_get_indirect(DLRX_CFG_MIB_RESET_BASE, 0);
		mib_clear(vap);
		/* Clear VAP mib reset request */
		DLRX_CFG_MIB_RESET_vapreq_clear_indirect(DLRX_CFG_MIB_RESET_BASE, 0);
	}

	return;
}

/*************************************************************************
Function name:    peer_reset
Description:      peer reset when peer_reset_req is set or
	invalid_tid_req is set
Parameters:       ptr (point to DLRX_CFG_PEER_RESET_BASE or
	DLRX_CFG_INVALID_TID_BASE)
Return value :    None
Functions called by this module:
	ro_list_reset()
Notes        :    None
*************************************************************************/
void peer_reset(unsigned int *ptr)
{
	unsigned int peer;

	peer = DLRX_CFG_PEER_RESET_peer_get_indirect(ptr, 0);

	/* Scan RO_mainlist and RO_linklist of all TID and seqid of this peer.
	Free all valid packet buffer pointer used.
	Free used RO_linklist entry.
	*/
	ro_list_reset(peer);
	/* Clear req bit */
	DLRX_CFG_PEER_RESET_req_clear_indirect(ptr, 0);
}

/*************************************************************************
Function name:    ce5_write_index_update
Description:      write local_ce5_parsing_index to target's
	ce5_write_index and increment local_ce5_parsing_index
Parameters:       ce5_parsing_index_ptr
Return value :    None
Functions called by this module:
	None
Notes        :    cfg_num_ce5buf should be configured by driver prior
	this function is called
*************************************************************************/
void ce5_write_index_update(unsigned int *ce5_parsing_index_ptr)
{
	if (!global_debug_flag)
		*DLRX_TARGET_CE5_WRITE_INDEX(g_ce5_offset) = *ce5_parsing_index_ptr;
	else
		*DLRX_TARGET_CE5_WRITE_INDEX(g_ce5_offset) = ((*DLRX_TARGET_CE5_READ_INDEX(g_ce5_offset)) + 64) % GET_NUM_CE5BUF;

	*ce5_parsing_index_ptr = *ce5_parsing_index_ptr + 1;
	*ce5_parsing_index_ptr = (*ce5_parsing_index_ptr) % GET_NUM_CE5BUF;
	DLRX_CFG_CTXT_CE5BUF_local_ce5_parsing_index_set_indirect(DLRX_CFG_CTXT_CE5BUF_BASE, 0, *ce5_parsing_index_ptr);

	return;
}

