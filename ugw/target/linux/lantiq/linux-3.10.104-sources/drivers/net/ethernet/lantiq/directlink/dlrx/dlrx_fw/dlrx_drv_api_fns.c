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

extern void mib_clear(int vap);

/******************************************************************************
Function name: dlrx_drv_get_revision
Description  : Get the firmware version id
Parameters   : None
Return value : Firmware version id
Functions called by this module:
	None
	Notes        : Make sure the fw_ver_id is set to the correct value in
	the context structure before calling this function. Check the
	notes of functions called for complete list to be set in the context.
******************************************************************************/
unsigned int dlrx_drv_get_revision(void)
{
	return DLRX_CFG_GLOBAL_fw_ver_id_get_indirect(DLRX_CFG_GLOBAL_BASE, 0);
}

/***************************************************************************
Function name: dlrx_drv_reset
Description  : Reset the peer or the mib depending on the input
Parameters   : reset_type - Indicates if the reset is for peer or mib
	id_num - Indicates the peer or the vap_id depending on the reset_type
Return value : None
Functions called by this module:
		ro_list_reset
		mib_clear
Notes        : Check the notes of functions called for list of values
		to be set in the context.
**************************************************************************/
void dlrx_drv_reset(unsigned int reset_type, unsigned int id_num)
{
	switch (reset_type) {
	case DRE_RESET_MIB:

		/* Case to reset mib */
		if (id_num == 0xFF)
			mib_clear(-1);
		else if (id_num < NUM_TID)
			mib_clear(id_num);

		break;

	case DRE_RESET_PEER:

		/* case to reset the peer */
		if (id_num < NUM_PEER) {
			DLRX_CFG_PEER_RESET_req_set_indirect(DLRX_CFG_PEER_RESET_BASE, 0, 1);
			DLRX_CFG_PEER_RESET_peer_set_indirect(DLRX_CFG_PEER_RESET_BASE, 0, id_num);
			/*
			Scan RO_mainlist and RO_linklist of all TID and seqid of this peer.
			Free all valid packet buffer pointer used. Free used RO_linklist entry.
			ro_list_reset(id_num);
			*/
		}

		break;

	default:
		break;
	}
}

/******************************************************************************
Function name: dlrx_drv_get_mib_data
Description  : Get the mib data
Parameters   : mib_type - Indicates if the type of mib requested by the driver
	vap_id - Indicates the vap_id if the request mib is vap mib
Return value : Pointer to the location of the mib data
	Functions called by this module:
	None
Notes        : None
******************************************************************************/
unsigned int *dlrx_drv_get_mib_data(unsigned int mib_type, unsigned int vap_id)
{
	switch (mib_type) {
	case DRE_MSG_MIB:
		/* Case to get msg mib */
		return (unsigned int *)DLRX_MSG_MIB_BASE;
		break;

	case DRE_VAP_MIB:

		/* Case to get vap mib */
		if (vap_id == 0xFF)
			return NULL;
		else
			return (unsigned int *)DLRX_VAP_MIB_BASE(vap_id);

		break;

	case DRE_DATA_MIB:
		/* Case to get data mib */
		return (unsigned int *)DLRX_DATA_MIB_BASE;
		break;

	default:
		return NULL;
		break;
	}
}

/***************************************************************************
Function name: dlrx_drv_get_cur_rxpb_ptr
Description  : Get the current rxpb pointer and the data length
Parameters   : rxpb_ptr - Location passed by the driver to store the rxpb pointer
	data_len - Location passed by the driver to store the data length
	flags - For Beeliner or Cascade, there are padding bytes.
Return value : -1 - Read index is equal to write index
	0 - Success status
Functions called by this module:
	None
Notes        : Make sure the rxpb_ptr_read_index,  rxpb_ptr_write_index,
	cfg_badr_rxpb_ptr_ring and cfg_num_rxpb_ptr_ring is set to the correct
	value in the context structure before calling this function. Check the
	notes of functions called for complete list to be set in the context.
******************************************************************************/
int dlrx_drv_get_cur_rxpb_ptr(unsigned int *rxpb_ptr,
	unsigned int *data_len,
	unsigned int *flags)
{
	unsigned int rxpb_ptr_read_index;
	unsigned int rxpb_ptr_write_index;
	unsigned int rxpb_ptr_ring_badr;
	unsigned int *tmp_rxpb_ptr;
	unsigned int padding_bytes = 0;

	rxpb_ptr_read_index = DLRX_CFG_CTXT_RXPB_PTR_RING_rxpb_ptr_read_index_get_indirect((unsigned int *)UNCACHE_ADDR(DLRX_CFG_CTXT_RXPB_PTR_RING_BASE), 0);
	rxpb_ptr_write_index = DLRX_CFG_CTXT_RXPB_PTR_RING_rxpb_ptr_write_index_get_indirect((unsigned int *)UNCACHE_ADDR(DLRX_CFG_CTXT_RXPB_PTR_RING_BASE), 0);

	if (rxpb_ptr_read_index == rxpb_ptr_write_index)
		return -1;

	rxpb_ptr_ring_badr = UNCACHE_ADDR(g_cfg_badr_rxpb_ptr_ring);

	tmp_rxpb_ptr = (unsigned int *)CACHE_ADDR(DLRX_RXPB_PTR_RING_rxpb_ptr_get_indirect((unsigned int *)rxpb_ptr_ring_badr, rxpb_ptr_read_index));
	dre_dma_unmap((unsigned int)(tmp_rxpb_ptr), (HTT_RX_BUF_SIZE));
	*rxpb_ptr = (unsigned int)tmp_rxpb_ptr;

	*data_len = DLRX_RXPB_HDR_msdu_len_get_indirect((unsigned int *)(*rxpb_ptr), CFG_OFFSET_ATTEN_IN_DWORDS);
	if (g_qca_hw == BEELINER_BOARD)
		padding_bytes = DLRX_RXPB_HDR_BEELINER_l3_header_padding_get_indirect((unsigned int *)*rxpb_ptr, CFG_OFFSET_ATTEN_IN_DWORDS);
	*flags = ((padding_bytes << 16) | 1);
	/* pr_info("skb :0x%x  read index: %u  write index: %u rxpb_ptr 0x%x, rxpb_ptr_ptr 0x%x rxpb_ptr_ring_badr 0x%x \n",
		 *(tmp_rxpb_ptr-1), rxpb_ptr_read_index, rxpb_ptr_write_index,
		 (unsigned int)*rxpb_ptr, (unsigned int)rxpb_ptr, (unsigned int)rxpb_ptr_ring_badr);
	*/
	/* pr_info("pkt_buffer is 0x%x,0x%x,0x%x,0x%x  0ff13 0x%x \n",*tmp_rxpb_ptr,*(tmp_rxpb_ptr+1),*(tmp_rxpb_ptr+2),*(tmp_rxpb_ptr+3),*(tmp_rxpb_ptr+13)); */
	/* Increment rxpb_ptr_read_index and check for wraparound */
	rxpb_ptr_read_index = (rxpb_ptr_read_index + 1) % GET_NUM_RXPB_PTR_RING;
	DLRX_CFG_CTXT_RXPB_PTR_RING_rxpb_ptr_read_index_set_indirect((unsigned int *)UNCACHE_ADDR(DLRX_CFG_CTXT_RXPB_PTR_RING_BASE), 0, rxpb_ptr_read_index);

	rxpb_write_free_buffer_to_rxpb_ptr_ring(NEW_RXPB_PTR);
	return 0;
}

/******************************************************************************
Function name: dlrx_dre_replenish_rxpb_ptr
Description  : Replenish the rxpb pointer ring with new rxpb pointers
Parameters   : None
Return value : None
Functions called by this module:
	rxpb_write_free_buffer_to_rxpb_ptr_ring
Notes        : Check the notes of functions called for list of values to be
	set in the context.
******************************************************************************/
void dlrx_drv_replenish_rxpb_ptr(void)
{
	rxpb_write_free_buffer_to_rxpb_ptr_ring(NEW_RXPB_PTR);
}

/* configure the base address */
int dlrx_drv_set_mem_base(unsigned int ddr_membase,
			  unsigned int cfg_ctxt_membase,
			  unsigned int pcie_membase
			 )
{
#ifdef CONFIG_ACCL_11AC_CS2
	dlrx_cfg_ctxt_ce5_resource_t ce5_resource;
#endif
	ddr_base = (unsigned int *)ddr_membase;
	pcie_base = (unsigned int *)pcie_membase;
	cfg_ctxt_base = (unsigned int *)cfg_ctxt_membase;

	DLRX_CFG_GLOBAL_dlrx_cfg_ctxt_base_set_indirect(DLRX_CFG_GLOBAL_BASE, 0, cfg_ctxt_membase);
	DLRX_CFG_GLOBAL_dlrx_ddr_base_set_indirect(DLRX_CFG_GLOBAL_BASE, 0, ddr_membase);
	DLRX_CFG_GLOBAL_dlrx_pcie_base_set_indirect(DLRX_CFG_GLOBAL_BASE, 0, pcie_membase);
#ifdef CONFIG_ACCL_11AC_CS2
	ce5_resource.qca_target_ce5_read_index_ptr =
		(uint32_t)DLRX_QCA_TARGET_CE5_READ_INDEX(g_ce5_offset);
	ce5_resource.qca_target_ce5_write_index_ptr =
			(uint32_t)DLRX_TARGET_CE5_WRITE_INDEX(g_ce5_offset);
	ce5_resource.qca_target_ce5_is_host_ptr =
			(uint32_t)DLRX_TARGET_CE5_IS_HOST_INDEX(g_ce5_offset);
	ce5_resource.ce5_numb = GET_NUM_CE5BUF;
	ce5_resource.ce5_ctxt_ce5des_base =
		g_cfg_badr_ce5des;
	ce5_resource.ce5_ctxt_ce5buf_base =
		g_cfg_badr_ce5buf;
	memcpy((void *)DLRX_CE5_RESOURCES_BASE,
		(void *)&ce5_resource,
		sizeof(dlrx_cfg_ctxt_ce5_resource_t));
#endif
	return 0;
}
int dlrx_drv_set_wapi_rxpn(unsigned int peer, unsigned int *rxpn)
{
	unsigned int ext_tid;
	unsigned int *mainlist_data_ptr;

	for (ext_tid = 0; ext_tid < NUM_TID; ext_tid++) {
		/* Offset into the required mainlist entry */
		mainlist_data_ptr = (unsigned int *)(((dlrx_ro_mainlist_t *)g_cfg_badr_ro_mainlist) + ((peer * NUM_TID) + ext_tid));
		/* update pn_dw */
		DLRX_RO_LINKLIST_pn_dw0_set_indirect(mainlist_data_ptr, 0, *rxpn);
		/* update pn_dw */
		DLRX_RO_LINKLIST_pn_dw1_set_indirect(mainlist_data_ptr, 0, *(rxpn + 1));
		/* update pn_dw */
		DLRX_RO_LINKLIST_pn_dw2_set_indirect(mainlist_data_ptr, 0, *(rxpn + 2));
		/* update pn_dw */
		DLRX_RO_LINKLIST_pn_dw3_set_indirect(mainlist_data_ptr, 0, *(rxpn + 3));
	}

	return 0;
}

/******************************************************************************
Function name: dre_dl_set_dlrx_unload_t
Description  : Set Flag indicating the unload of the dlrx module
Parameters   : None
Return value : None
Functions called by this module: None
Notes        : None
******************************************************************************/
void dre_drv_set_dlrx_unload(void)
{
	DLRX_CFG_GLOBAL_dlrx_cfg_unload_set_indirect(DLRX_CFG_GLOBAL_BASE, 0, 1);
}
