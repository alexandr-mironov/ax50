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
#include <linux/moduleparam.h>
#include <linux/init.h>
#include <linux/stat.h>
#include "../include/dlrx_fw_def.h"
#include "../include/dlrx_fw_internal_def.h"
#include "../include/dlrx_dre_api.h"
#include "../include/dlrx_fw_version.h"
#include "../include/dlrx_fw_data_structure_macro.h"

/* #include "../include/cycle_counter.h" */
#include <linux/interrupt.h>
#include <lantiq_soc.h>
#include <asm/gic.h>


#define DLRX_SRAM_PHY_ADDR      0x1F107400

#define DMA_BASE		0xBE104100
#define DMA_CS			(volatile u32 *)(DMA_BASE + 0x18)
#define DMA_CCTRL		(volatile u32 *)(DMA_BASE + 0x1C)
#define DMA_CDBA		(volatile u32 *)(DMA_BASE + 0x20)
#define DMA_CDLEN		(volatile u32 *)(DMA_BASE + 0x24)
#define DMA_CIS			(volatile u32 *)(DMA_BASE + 0x28)
#define DMA_CIE			(volatile u32 *)(DMA_BASE + 0x2C)
#define PPE_TX_CH_NO	3
/* Global variables */
unsigned int global_debug_flag;
/* unsigned int global_debug_print; */
unsigned int g_cfg_badr_ce5buf;
unsigned int g_cfg_badr_ce5des;
unsigned int g_cfg_badr_rxpb_ptr_ring;
unsigned int g_cfg_badr_ro_linklist;
unsigned int g_cfg_badr_ro_mainlist;

unsigned int g_qca_hw;
unsigned int g_ce5_offset;
unsigned int g_qca_hw_sub_type;

unsigned int g_congestion_timeout_num;
unsigned int g_congestion_drop_flag;
unsigned int dl_kseg0;
unsigned int dl_kseg1;

extern int dlrx_main(void);

#if defined(CONFIG_ACCL_11AC_CS2)
static void dlrx_tasklet(unsigned long data)
{
	dlrx_main();
	return;
}
DECLARE_TASKLET(dl_linux_tasklet, &dlrx_tasklet, 0);

static irqreturn_t dl_linux_handler(int irq, void *data)
{
	tasklet_schedule(&dl_linux_tasklet);
	return IRQ_HANDLED;	
}
#endif
static int __init dlrx_fw_init(void)
{
	/* #if DLRX_GRX330_BOARD_CFG */
	unsigned int loop_index;
	unsigned int write_index_address;
	/* #else */
	unsigned int sram_phy_addr;
	/* #endif */
#if defined(CONFIG_ACCL_11AC_CS2)
	int err = 0;
#endif

#if DLRX_GRX330_BOARD_CFG
	cfg_ctxt_base = (unsigned int *)CACHE_ADDR(DLRX_SRAM_PHY_ADDR);
#else
	sram_phy_addr = ppa_dl_dre_get_sram_addr();
	dl_kseg0 = ppa_dl_dre_get_kseg0();
	dl_kseg1 = ppa_dl_dre_get_kseg1();

	cfg_ctxt_base = (unsigned int *)CACHE_ADDR(sram_phy_addr);
#endif

	DLRX_CFG_GLOBAL_fw_ver_id_set_indirect(DLRX_CFG_GLOBAL_BASE, 0, DRE_FW_VERSION);
	DLRX_CFG_GLOBAL_fw_feature_set_indirect(DLRX_CFG_GLOBAL_BASE, 0, DRE_FW_FEATURE);

	ppa_dl_dre_fn_register(DRE_MAIN_FN, dlrx_main);
	ppa_dl_dre_fn_register(DRE_GET_VERSION_FN, dlrx_drv_get_revision);
	ppa_dl_dre_fn_register(DRE_RESET_FN, dlrx_drv_reset);
	ppa_dl_dre_fn_register(DRE_GET_MIB_FN, dlrx_drv_get_mib_data);
	ppa_dl_dre_fn_register(DRE_GET_CURMSDU_FN, dlrx_drv_get_cur_rxpb_ptr);
	ppa_dl_dre_fn_register(DRE_SET_MEMBASE_FN, dlrx_drv_set_mem_base);
	ppa_dl_dre_fn_register(DRE_SET_RXPN_FN, dlrx_drv_set_wapi_rxpn);
	ppa_dl_dre_fn_register(DRE_SET_DLRX_UNLOAD, dre_drv_set_dlrx_unload);

	pr_info("DRE_Version is 0x%x, DRE_Feature is 0x%x \n",
		DRE_FW_VERSION,
		DRE_FW_FEATURE);
#ifdef CONFIG_ACCL_11AC_CS2
	pr_info("QCA CS2 Support 4\n");
#endif
	global_debug_flag = 0;
	/* global_debug_print = 1; */
	g_cfg_badr_ce5buf = DLRX_CFG_CTXT_CE5BUF_cfg_badr_ce5buf_get_indirect(DLRX_CFG_CTXT_CE5BUF_BASE, 0);
	g_cfg_badr_ce5des = DLRX_CFG_CTXT_CE5DES_cfg_badr_ce5des_get_indirect(DLRX_CFG_CTXT_CE5DES_BASE, 0);

#if DLRX_GRX330_BOARD_CFG
	/* TODO : debug */
	ddr_base = (unsigned int *)0x8f200000;
#endif
#if 0
	DLRX_CFG_GLOBAL_dlrx_congestion_bit_timeout_set_indirect(DLRX_CFG_GLOBAL_BASE, 0, 0x4000);
	DLRX_CFG_GLOBAL_dlrx_timout_count_th_set_indirect(DLRX_CFG_GLOBAL_BASE, 0, 0x0A);
#endif
	g_congestion_timeout_num = 0;

	g_cfg_badr_rxpb_ptr_ring = DLRX_CFG_CTXT_RXPB_PTR_RING_cfg_badr_rxpb_ptr_ring_get_indirect(DLRX_CFG_CTXT_RXPB_PTR_RING_BASE, 0);
	g_cfg_badr_ro_linklist = DLRX_CFG_CTXT_RO_LINKLIST_cfg_badr_ro_linklist_get_indirect(DLRX_CFG_CTXT_RO_LINKLIST_BASE, 0);
	g_cfg_badr_ro_mainlist = DLRX_CFG_CTXT_RO_MAINLIST_cfg_badr_ro_mainlist_get_indirect(DLRX_CFG_CTXT_RO_MAINLIST_BASE, 0);

	g_qca_hw = DLRX_CFG_GLOBAL_dlrx_qca_hw_get_indirect(DLRX_CFG_GLOBAL_BASE, 0);
	g_qca_hw_sub_type = DLRX_CFG_GLOBAL_dlrx_qca_hw_sub_type_get_indirect(DLRX_CFG_GLOBAL_BASE, 0);

	if (g_qca_hw == BEELINER_BOARD) {
		g_ce5_offset = DLRX_TARGET_CE5_BEELINER;

		if (g_qca_hw_sub_type == SUBTYPE_NONE_BOARD)
			pr_info("DLRX FW: Beeliner board detected\n");
		else
			pr_info("DLRX FW: Beeliner Cascade board detected\n");
	} else {
		g_ce5_offset = DLRX_TARGET_CE5_PEREGRINE;
		pr_info("DLRX FW: Peregrine board detected\n");
	}

	/* #if DLRX_GRX330_BOARD_CFG */
	/* Each entry in the rxpb ptr ring is one dword,
	Multiply GET_NUM_RXPB_PTR_RING by 4 to convert to bytes
	*/
	dre_dma_map(g_cfg_badr_rxpb_ptr_ring, (GET_NUM_RXPB_PTR_RING * 4));
	/* Each entry in the ce5 des ring is two dwords,
	Multiply GET_NUM_CE5BUF by 8 to convert to bytes
	*/
#ifdef USING_BBCPU_SRAM
#else
	dre_dma_map(g_cfg_badr_ce5des, (GET_NUM_CE5BUF * 2) * 4);
#endif
	/* Each entry in the ce5 buffer is 512 bytes
	Multiply GET_NUM_CE5BUF by 512
	*/
	dre_dma_map(g_cfg_badr_ce5buf, ((GET_NUM_CE5BUF) * (1 << GET_CE5BUF_SIZE_SHIFT)));

	for (loop_index = 0; loop_index < GET_NUM_RXPB_PTR_RING; loop_index++) {
		unsigned int rxpb_ptr;
		rxpb_ptr = CACHE_ADDR(DLRX_RXPB_PTR_RING_rxpb_ptr_get_indirect((unsigned int *)g_cfg_badr_rxpb_ptr_ring, loop_index));
		dre_dma_map(rxpb_ptr, HTT_RX_BUF_SIZE);
	}

	/* 2 is offset for the write index */
	write_index_address = (unsigned int)((unsigned int *)CACHE_ADDR(DLRX_CFG_CTXT_RXPB_PTR_RING_BASE) + 2);

	dre_dma_map(write_index_address, 4);
	/* function1_cycles  = CycleCounter_Create("Rx Ind : Overall"); */
#if DLRX_GRX330_BOARD_CFG
	*DMA_CS 	= 7;
	*DMA_CCTRL	= 0x30102;

	*DMA_CS 	= 7;
	*DMA_CCTRL	= 0x30101;
#endif
#ifdef CONFIG_ACCL_11AC_CS2
	pr_info("register irq for DL IPI\n");

	err = request_irq(DL_LI_IPI_NO,
			dl_linux_handler, IRQF_DISABLED, "DL_LI", NULL);
	if (err)
		pr_err("request_irq for IRQ DL to Linux = %d failed !!! \n",
			DL_LI_IPI_NO);
#endif
	return 0;
}

static void __exit dlrx_fw_exit(void)
{
	/* Find duplicate pointer values in the rxpb
	ring ans set to 0 if duplicate is found
	*/
	rxpb_find_duplicate_ptr_value();
	/* Release of the rxpb buffers between
	read and write pointer
	*/
	rxpb_free_buffers_on_unload();
	/* Clear the RO list */
	pr_info("%s: clear RO list\n", __func__);
	ro_list_clear();
	/* Unregister functions that are already registered with the driver */
	dlrx_unregister_driver_fns();
#ifdef CONFIG_ACCL_11AC_CS2
	pr_info("Deregister irq\n");
	free_irq(DL_LI_IPI_NO,
		NULL);
#endif
}

module_init(dlrx_fw_init);
module_exit(dlrx_fw_exit);
MODULE_AUTHOR("LANTIQ");
MODULE_DESCRIPTION("DRE FW");
MODULE_LICENSE("GPL");
