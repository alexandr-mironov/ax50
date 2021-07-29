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

/**************************************************************************************
//      Function name: rxpb_write_free_buffer_to_rxpb_ptr_ring
//      Description  : Write a free buffer to the end of the rx packet buffer
//                     pointer ring
//      Parameters   : ce5_buf_ptr : Message buffer pointer
//      Return value : None
//      Functions called by this module:
//                     dlrx_get_current_rxpb_buf_ptr
//                     dlrx_get_ro_ll_rxpb_ptr
//      Notes        : Make sure the cfg_badr_rxpb_ptr_ring, rxpb_ptr_write_index,
//                     cfg_badr_rel_msgbuf,pb_ptr_rel_num, cfg_num_rxpb_ptr_ring
//                     is set to the correct value in the context structure before
//                     calling this function. Check the notes of functions called
//                     for complete list to be set in the context.
**************************************************************************************/
void rxpb_write_free_buffer_to_rxpb_ptr_ring(rxpb_free_ptr_type free_ptr_type)
{
	unsigned int rxpb_buf_ptr = 0;
	unsigned int rxpb_ptr_write_index;
	unsigned int rxpb_ring_base_address;
	unsigned int va_rxpb_buf_ptr;
	unsigned int *tmp_buf_ptr;

	unsigned int rxpb_ptr_read_index;
	rxpb_ring_base_address = UNCACHE_ADDR(DLRX_CFG_CTXT_RXPB_PTR_RING_cfg_badr_rxpb_ptr_ring_get_indirect((unsigned int *)UNCACHE_ADDR(DLRX_CFG_CTXT_RXPB_PTR_RING_BASE), 0));
	rxpb_ptr_write_index = DLRX_CFG_CTXT_RXPB_PTR_RING_rxpb_ptr_write_index_get_indirect((unsigned int *)UNCACHE_ADDR(DLRX_CFG_CTXT_RXPB_PTR_RING_BASE), 0);

	switch (free_ptr_type) {
	case RECYCLE_RXPB_PTR:
		rxpb_buf_ptr = dlrx_get_current_rxpb_buf_ptr();
		break;

	case NEW_RXPB_PTR:
		rxpb_buf_ptr = VIR_TO_PHY(dlrx_dl_dre_rxpb_buf_alloc());
		break;

	case RECYCLE_LL_RXPB_PTR:
		rxpb_buf_ptr = VIR_TO_PHY(dlrx_get_ro_ll_rxpb_ptr());
		break;

	default:
		/* Should not reach here */
		break;
	}

	if (!rxpb_buf_ptr)
		return;

	va_rxpb_buf_ptr = CACHE_ADDR(rxpb_buf_ptr);

	rxpb_ptr_read_index = DLRX_CFG_CTXT_RXPB_PTR_RING_rxpb_ptr_read_index_get_indirect((unsigned int *)UNCACHE_ADDR(DLRX_CFG_CTXT_RXPB_PTR_RING_BASE), 0);

	DLRX_RXPB_HDR_msdu_load_status_clear_indirect((unsigned int *)va_rxpb_buf_ptr, CFG_OFFSET_ATTEN_IN_DWORDS);
	/* TODO: */
	dre_dma_map(CACHE_ADDR(rxpb_buf_ptr), MAX_INV_HEADER_LEN);

	tmp_buf_ptr = (unsigned int *)CACHE_ADDR(rxpb_buf_ptr);

/*    printk("rxpb_ptr_write_index 0x%x, read_idx 0x%x free_type %u,rxpb_buf_ptr 0x%x skb 0x%x\n",rxpb_ptr_write_index,rxpb_ptr_read_index,free_ptr_type,(unsigned int)rxpb_buf_ptr,*((unsigned int *)va_rxpb_buf_ptr-1)); */
	DLRX_RXPB_PTR_RING_rxpb_ptr_set_indirect((unsigned int *)rxpb_ring_base_address, rxpb_ptr_write_index, rxpb_buf_ptr);
	rxpb_ptr_write_index++;
	rxpb_ptr_write_index = (rxpb_ptr_write_index % GET_NUM_RXPB_PTR_RING);    /* Wrap around to zero if max number reached */

	tmp_buf_ptr = (unsigned int *)UNCACHE_ADDR(DLRX_CFG_CTXT_RXPB_PTR_RING_BASE);
	DLRX_CFG_CTXT_RXPB_PTR_RING_rxpb_ptr_write_index_set_indirect(tmp_buf_ptr, 0, rxpb_ptr_write_index);
}

/**************************************************************************************
//      Function name: rxpb_find_duplicate_ptr_value
//      Description  : Find duplicate pointer values in the rxpb ring ans set to 0 if duplicate is found
//      Parameters   : None
//      Return value : None
//      Functions called by this module:
//      Notes        : Make sure the cfg_badr_rxpb_ptr_ring, rxpb_ptr_write_index,
//                         rxpb_ptr_read_index is set to the correct value in the context
//                         structure before calling this function. Check the notes of functions
//                         called for complete list to be set in the context.
**************************************************************************************/
void rxpb_find_duplicate_ptr_value(void)
{
	unsigned int loop_index_1;
	unsigned int loop_index_2;
	unsigned int rxpb_ptr;
	unsigned int temp_rxpb_ptr;
	unsigned int rxpb_ring_base_address;
	unsigned int rxpb_write_index;
	unsigned int rxpb_read_index;
	unsigned int loop_count;
	unsigned int rxpb_idx;
	unsigned int temp_rxpb_idx;

	rxpb_write_index = DLRX_CFG_CTXT_RXPB_PTR_RING_rxpb_ptr_write_index_get_indirect((unsigned int *)UNCACHE_ADDR(DLRX_CFG_CTXT_RXPB_PTR_RING_BASE), 0);
	rxpb_read_index = DLRX_CFG_CTXT_RXPB_PTR_RING_rxpb_ptr_read_index_get_indirect((unsigned int *)UNCACHE_ADDR(DLRX_CFG_CTXT_RXPB_PTR_RING_BASE), 0);
	rxpb_ring_base_address = UNCACHE_ADDR(DLRX_CFG_CTXT_RXPB_PTR_RING_cfg_badr_rxpb_ptr_ring_get_indirect((unsigned int *)UNCACHE_ADDR(DLRX_CFG_CTXT_RXPB_PTR_RING_BASE), 0));

	printk("dlrx_fw_exit : Read index %u  Write index %u\n",rxpb_read_index,rxpb_write_index);
	if (rxpb_write_index < rxpb_read_index)
		loop_count = (GET_NUM_RXPB_PTR_RING + rxpb_write_index) - rxpb_read_index;
	else
		loop_count = rxpb_write_index - rxpb_read_index;

	/* Find duplicate pointer values in the rxpb ring ans set to 0 if duplicate is found */
	for (loop_index_1 = 0; loop_index_1 < loop_count; loop_index_1++) {
		rxpb_idx = (rxpb_read_index + loop_index_1) % GET_NUM_RXPB_PTR_RING;
		rxpb_ptr = DLRX_RXPB_PTR_RING_rxpb_ptr_get_indirect((unsigned int *)rxpb_ring_base_address, rxpb_idx);

		for (loop_index_2 = 0; loop_index_2 < loop_count; loop_index_2++) {
			temp_rxpb_idx = (rxpb_read_index + loop_index_2) % GET_NUM_RXPB_PTR_RING;

			if (temp_rxpb_idx == rxpb_idx)
				continue;

			temp_rxpb_ptr = DLRX_RXPB_PTR_RING_rxpb_ptr_get_indirect((unsigned int *)rxpb_ring_base_address, temp_rxpb_idx);

			if (temp_rxpb_ptr == rxpb_ptr) {
				printk("Duplicate ptr value found in index %u and %u . Ptr value = 0x%x\n", rxpb_idx,temp_rxpb_idx, rxpb_ptr);
				DLRX_RXPB_PTR_RING_rxpb_ptr_set_indirect((unsigned int *)rxpb_ring_base_address, loop_index_2, 0);
			}
		}
	}

}
/**************************************************************************************
//      Function name: rxpb_free_buffers_on_unload
//      Description  : Release the rxpb buffers between the read pointer and write pointer
//      Parameters   : None
//      Return value : None
//      Functions called by this module:
//      Notes        : Make sure the cfg_badr_rxpb_ptr_ring, rxpb_ptr_write_index,
//                         rxpb_ptr_read_index is set to the correct value in the context
//                         structure before calling this function. Check the notes of functions
//                         called for complete list to be set in the context.
**************************************************************************************/
void rxpb_free_buffers_on_unload(void)
{
	unsigned int rxpb_write_index;
	unsigned int rxpb_read_index;
	unsigned int loop_count;
	unsigned int loop_index;
	unsigned int rxpb_ring_base_address;

	rxpb_write_index = DLRX_CFG_CTXT_RXPB_PTR_RING_rxpb_ptr_write_index_get_indirect((unsigned int *)UNCACHE_ADDR(DLRX_CFG_CTXT_RXPB_PTR_RING_BASE), 0);
	rxpb_read_index = DLRX_CFG_CTXT_RXPB_PTR_RING_rxpb_ptr_read_index_get_indirect((unsigned int *)UNCACHE_ADDR(DLRX_CFG_CTXT_RXPB_PTR_RING_BASE), 0);
	rxpb_ring_base_address = UNCACHE_ADDR(DLRX_CFG_CTXT_RXPB_PTR_RING_cfg_badr_rxpb_ptr_ring_get_indirect((unsigned int *)UNCACHE_ADDR(DLRX_CFG_CTXT_RXPB_PTR_RING_BASE), 0));
	if (rxpb_write_index < rxpb_read_index)
		loop_count = (GET_NUM_RXPB_PTR_RING + rxpb_write_index) - rxpb_read_index;
	else
		loop_count = rxpb_write_index - rxpb_read_index;

	/* Release rxpb buffer */
	for (loop_index = 0; loop_index < loop_count; loop_index++) {
		unsigned int rxpb_ptr;
		unsigned int rxpb_idx;

		rxpb_idx = (rxpb_read_index + loop_index) % GET_NUM_RXPB_PTR_RING;
		rxpb_ptr = DLRX_RXPB_PTR_RING_rxpb_ptr_get_indirect((unsigned int *)rxpb_ring_base_address, rxpb_idx);
		ppa_dl_dre_rxpb_buf_free(rxpb_ptr);
	}
}
