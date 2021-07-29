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
#ifndef __DLRX_FW_DEF_H__
#define __DLRX_FW_DEF_H__
/* In DDR */
#include <linux/io.h>
#include <linux/kernel.h>

#define OPTIMIZE_PERF 1
extern unsigned int *ddr_base, *pcie_base, *cfg_ctxt_base;
extern unsigned int dl_kseg0, dl_kseg1;

#define DLRX_GRX330_BOARD_CFG 0

#if (defined(DLRX_GRX330_BOARD_CFG) && (DLRX_GRX330_BOARD_CFG == 1))
	/* 1 x 12 dwords */
	#define DLRX_MSG_MIB_BASE                               \
			(unsigned int *)(ddr_base)

	/* 1 x 32 dwords */
	#define DLRX_DATA_MIB_BASE                              \
			(unsigned int *)(ddr_base + 0x0C)

	/* 132 x 1 dwords i.e 528 x 1 bytes - - Location moved below due
	to increase in number of peer id's */
	/*#define DLRX_CFG_PEER_ID_TO_PEER_MAP_BASE(i)            \
			(unsigned int *)(ddr_base + 0x2C  + i)
			*/

	/* 128x 1 dwords i.e 528 peers x 4 bytes */
	#define DLRX_CFG_PEER_TO_VAP_PN_BASE(i)                 \
			(unsigned int *)(ddr_base + 0xB0 + i)

	/* 1 x 1 dword */
	#define DLRX_CFG_PEER_RESET_BASE                        \
			(unsigned int *)(ddr_base + 0x130)

	/* 1 x 1 dword */
	#define DLRX_CFG_INVALID_TID_BASE                       \
			(unsigned int *)(ddr_base + 0x131)

	/* 1 x 1 dword */
	#define DLRX_CFG_MIB_RESET_BASE                         \
			(unsigned int *)(ddr_base + 0x132)

	/* 1 x 1 dword */
	#define DLRX_CFG_VAP2INT_MAP1_BASE                      \
			(unsigned int *)(ddr_base + 0x133)

	/* 1 x 1 dword */
	#define DLRX_CFG_VAP2INT_MAP2_BASE                      \
			(unsigned int *)(ddr_base + 0x134)

	/* 1x16 dword */
	#define DLRX_MISC_MIB_BASE                              \
			(unsigned int *)(ddr_base + 0x140)

	/* 1X4 dword */
	#define DLRX_SKB_POOL_CTXT                              \
			(unsigned int *)(ddr_base + 0x150)

	/* total_size for ddr_base: 0x150 dwords */

	/* 32 x 16 dwords i.e 16 x 128 bytes Note: this is in SB,
		sharing with DLRX TX!!
		*/
	#define DLRX_VAP_MIB_BASE(i)                            \
			(unsigned int *)(ddr_base + 0x200 + ((i)*32))

	/* 32 x 16 dwords */
	#define DLRX_VAP_MIB_MISC_BASE(i)                       \
			(unsigned int *)(ddr_base + 0x400 + ((i)*32))

	/* 255 * 2 DWORDS  move to SRAM */
	/*#define DLRX_DDR_GSWIP_DMA_DESC_BASE                    \
			(volatile unsigned int *)( ddr_base + 0x500 )
			*/

	/*255 * 2 DWORDS */
	#define DLRX_DDR_PROTO_DMA_DESC_BASE                    \
			(unsigned int *)(ddr_base + 0x700)

	/* 128 * 2 DWORDS */
	#define DLRX_DDR_RX_PKT_BUF_REL_MSG_BASE                \
			(unsigned int *)(ddr_base + 0x900)

	/* 4096 * 1 DWORDS */
	#define DLRX_DDR_RX_PKT_BUF_RING_BASE                   \
			(unsigned int *)(ddr_base + 0xa00)

	/* 2048 * (64 + 4) DWORDS */
	#define DLRX_DDR_RO_MAINLIST_BASE                       \
			(unsigned int *)(ddr_base + 0x1a00)

	/* 4096 * 6 DWORDS */
	#define DLRX_DDR_RO_LINKLIST_BASE                       \
			(unsigned int *)(ddr_base + 0x23a00)

	/* 2 * (1 * 8) DWORDS */
	#define DLRX_DDR_CPU_CE5_DESC_BASE                      \
			(unsigned int *)(ddr_base + 0x29a00)

	/* 2048 * 2 DWORDS (shift to SRAM) */
	/*#define DLRX_DDR_CE5DESC_BASE                         \
			(volatile unsigned int *)(ddr_base + 0x2a000)
			*/

	/* 264 x 1 dwords i.e 1056 x 1 bytes */
	#define DLRX_CFG_PEER_ID_TO_PEER_MAP_BASE(i)            \
			(unsigned int *)(ddr_base + 0x2a000 + i)

	/* 2048 * 512 Bytes (2e000 -*/
	#define DLRX_DDR_CE5BUF_BASE                            \
			(unsigned int *)(ddr_base + 0x2e000)

	/* 128*16 Dword */
	#define DLRX_DDR_SEQ_MASK_BASE                          \
			(unsigned int *)(ddr_base + 0x6e000)


	/*dword? */

	#define DLRX_TARGET_CE5_PEREGRINE                       0x00058800
	#define DLRX_TARGET_CE5_BEELINER                        0x0004B400

	#define DLRX_TARGET_CE5_READ_INDEX(base)                \
			(volatile unsigned int *)(pcie_base + ((base+0x48)>>2))

	/* 1 dword? */
	#define DLRX_TARGET_CE5_WRITE_INDEX(base)               \
			(volatile unsigned int *)(pcie_base + ((base+0x40)>>2))

	/* 4 dword */
	#define DLRX_CFG_CTXT_GSWIP_DMA_BASE                    \
			(unsigned int *)(cfg_ctxt_base)

	/* 4 dword */
	#define DLRX_CFG_CTXT_WLAN_DMA_BASE                     \
			(unsigned int *)(cfg_ctxt_base + 0x04)

	/* 4 dword */
	#define DLRX_CFG_CTXT_PROT_DMA_BASE                     \
			(unsigned int *)(cfg_ctxt_base + 0x08)

	/* 1 x 12 dwords */
	#define DLRX_CFG_CTXT_CE5BUF_BASE                       \
			(unsigned int *)(cfg_ctxt_base + 0x0C)

	/* 1 x 4 dwords */
	#define DLRX_CFG_CTXT_CE5DES_BASE                       \
			(unsigned int *)(cfg_ctxt_base + 0x18)

	/* 1 x 8 dword */
	#define DLRX_CFG_CTXT_CPU_CE5DES_BASE                   \
			(unsigned int *)(cfg_ctxt_base + 0x1C)

	/* 1 x 8 dwords */
	#define DLRX_CFG_CTXT_RXPB_PTR_RING_BASE                \
			(unsigned int *)(cfg_ctxt_base + 0x24)
	/*#define DLRX_CFG_CTXT_RXPB_PTR_RING_BASE               \
			(unsigned int *)(ddr_base + 0x158)
			*/

	/* 1 x 4 dwords */
	#define DLRX_CFG_CTXT_RXPB_BASE                         \
			(unsigned int *)(cfg_ctxt_base + 0x2C)

	/* 1 x 16 dwords */
	#define DLRX_CFG_CTXT_RO_LINKLIST_BASE                  \
			(unsigned int *)(cfg_ctxt_base + 0x30)

	/* 1 x 8 dword */
	#define DLRX_CFG_CTXT_RO_MAINLIST_BASE                  \
			(unsigned int *)(cfg_ctxt_base + 0x40)

	/* 1 x 48 dwords */
	#define DLRX_CTXT_MSG_BASE                              \
			(unsigned int *)(cfg_ctxt_base + 0x48)

	/* 1 x 4 dwords */
	#define DLRX_CFG_CTXT_RXPB_PTR_REL_MSGBUF_BASE          \
			(unsigned int *)(cfg_ctxt_base + 0x78)

	/* 1 x 8 dwords */
	#define DLRX_CFG_GLOBAL_BASE                            \
			(unsigned int *)(cfg_ctxt_base + 0x80)

	/* 128 x 2 dwords i.e. 128 peers x 2 dwords */
	#define DLRX_CFG_CTXT_PEER_HANDLER_BASE(i)              \
			(unsigned int *)(cfg_ctxt_base + 0x90 + (i) * 2)

	/* 4 x 1 dwords */
	#define DLRX_CFG_CTXT_PEER_BITMAP_BASE(i)               \
			(unsigned int *)(cfg_ctxt_base + 0x190 + i)

	/* 255 * 2 DWORDS */
	#define DLRX_DDR_GSWIP_DMA_DESC_BASE                    \
			(volatile unsigned int *)(cfg_ctxt_base + 0x200)

	/* 512 * 2 DWORDS (shift from  SRAM) */
	#define DLRX_DDR_CE5DESC_BASE                           \
			(volatile unsigned int *)(cfg_ctxt_base + 0x400)

	/* total size for cfg_ctxt_base allocation: 8kbyte */
#else

	#define RX_CFG_CTXT_BUF_BASE                            cfg_ctxt_base
	#define RX_MSG_BUF_BASE                                 ddr_base

	/* 1 x 12 dwords */
	#define DLRX_MSG_MIB_BASE                               \
			(unsigned int *)(RX_CFG_CTXT_BUF_BASE)

	/* 1 x 32 dwords */
	#define DLRX_DATA_MIB_BASE                              \
			(unsigned int *)(RX_CFG_CTXT_BUF_BASE + 0x0C)

	/* 128x 1 dwords i.e 528 peers x 4 bytes */
	#define DLRX_CFG_PEER_TO_VAP_PN_BASE(i)                 \
			(unsigned int *)(RX_CFG_CTXT_BUF_BASE + 0x2C + i)

	/* 1 x 1 dword */
	#define DLRX_CFG_PEER_RESET_BASE                        \
			(unsigned int *)(RX_CFG_CTXT_BUF_BASE + 0xB0)

	/* 1 x 1 dword */
	#define DLRX_CFG_INVALID_TID_BASE                       \
			(unsigned int *)(RX_CFG_CTXT_BUF_BASE + 0xB1)

	/* 1 x 1 dword */
	#define DLRX_CFG_MIB_RESET_BASE                         \
			(unsigned int *)(RX_CFG_CTXT_BUF_BASE + 0xB2)

	/* 1 x 1 dword */
	#define DLRX_CFG_VAP2INT_MAP1_BASE                      \
			(unsigned int *)(RX_CFG_CTXT_BUF_BASE + 0xB3)

	/* 1 x 1 dword */
	#define DLRX_CFG_VAP2INT_MAP2_BASE                      \
			(unsigned int *)(RX_CFG_CTXT_BUF_BASE + 0xB4)

	/* 1x16 dword */
	#define DLRX_MISC_MIB_BASE                              \
			(unsigned int *)(RX_CFG_CTXT_BUF_BASE + 0xC0)

	/* 1X4 dword */
	#define DLRX_SKB_POOL_CTXT                              \
			(unsigned int *)(RX_CFG_CTXT_BUF_BASE + 0xD0)

	/* 32 x 16 dwords i.e 16 x 128 bytes Note: this is in SB, sharing
		with DLRX TX!!
		*/
	#define DLRX_VAP_MIB_BASE(i)                            \
		(unsigned int *)(RX_CFG_CTXT_BUF_BASE + 0xE0 + ((i)*32))

	/* 32 x 16 dwords */
	#define DLRX_VAP_MIB_MISC_BASE(i)                       \
			(unsigned int *)(RX_CFG_CTXT_BUF_BASE + 0x2E0 + \
							((i)*32))

	/* 255 * 2 DWORDS */
	#define DLRX_DDR_PROTO_DMA_DESC_BASE                    \
			(unsigned int *)(RX_CFG_CTXT_BUF_BASE + 0x500)

	/* 128 * 2 DWORDS */
	#define DLRX_DDR_RX_PKT_BUF_REL_MSG_BASE                \
			(unsigned int *)(RX_CFG_CTXT_BUF_BASE + 0x700)

	/* 4096 * 1 DWORDS */
	/* TODO: Need to define this as a seperate address as
	 KSEG1 address is not guaranteed
	 */
	#define DLRX_DDR_RX_PKT_BUF_RING_BASE                   \
			(unsigned int *)(RX_CFG_CTXT_BUF_BASE + 0x800)

	/* (128 * 16=tid + 128*16) 2048 * (64 + 4) DWORDS  */
	#define DLRX_DDR_RO_MAINLIST_BASE                       \
			(unsigned int *)(RX_CFG_CTXT_BUF_BASE + 0x1800)

	/* 4096 * 6 DWORDS */
	#define DLRX_DDR_RO_LINKLIST_BASE                       \
			(unsigned int *)(RX_CFG_CTXT_BUF_BASE + 0x23800 + 0x22000)

	/* 2 * (1 * 8) DWORDS */
	#define DLRX_DDR_CPU_CE5_DESC_BASE                      \
			(unsigned int *)(RX_CFG_CTXT_BUF_BASE + 0x29800 + 0x22000)

	/* 264 x 1 dwords i.e 1056 x 1 bytes */
	#define DLRX_CFG_PEER_ID_TO_PEER_MAP_BASE(i)            \
			(unsigned int *)(RX_CFG_CTXT_BUF_BASE + 0x2a000 + i  + 0x22000)

	/* 128*(16 + 16) Dword */
	#define DLRX_DDR_SEQ_MASK_BASE                          \
			(unsigned int *)(RX_CFG_CTXT_BUF_BASE + 0x2a200 + 0x22000)

	/* 4 dword */
	#define DLRX_CFG_CTXT_GSWIP_DMA_BASE                    \
			(unsigned int *)(RX_CFG_CTXT_BUF_BASE + 0x2aa00 + 0x22000 + 0x800)

	/* 4 dword */
	#define DLRX_CFG_CTXT_WLAN_DMA_BASE                     \
			(unsigned int *)(RX_CFG_CTXT_BUF_BASE + 0x2aa04 + 0x22000 + 0x800)

	/* 4 dword */
	#define DLRX_CFG_CTXT_PROT_DMA_BASE                     \
			(unsigned int *)(RX_CFG_CTXT_BUF_BASE + 0x2aa08 + 0x22000 + 0x800)

	/* 1 x 12 dwords */
	#define DLRX_CFG_CTXT_CE5BUF_BASE                       \
			(unsigned int *)(RX_CFG_CTXT_BUF_BASE + 0x2aa0C + 0x22000 + 0x800)

	/* 1 x 4 dwords */
	#define DLRX_CFG_CTXT_CE5DES_BASE                       \
			(unsigned int *)(RX_CFG_CTXT_BUF_BASE + 0x2aa18 + 0x22000 + 0x800)

	/* 1 x 8 dword */
	#define DLRX_CFG_CTXT_CPU_CE5DES_BASE                   \
			(unsigned int *)(RX_CFG_CTXT_BUF_BASE + 0x2aa1C + 0x22000 + 0x800)

	/* 1 x 8 dwords */
	#define DLRX_CFG_CTXT_RXPB_PTR_RING_BASE                \
			(unsigned int *)(RX_CFG_CTXT_BUF_BASE + 0x2aa24 + 0x22000 + 0x800)

	/* 1 x 4 dwords */
	#define DLRX_CFG_CTXT_RXPB_BASE                         \
			(unsigned int *)(RX_CFG_CTXT_BUF_BASE + 0x2aa2C + 0x22000 + 0x800)

	/* 1 x 16 dwords + 16*/
	#define DLRX_CFG_CTXT_RO_LINKLIST_BASE                  \
			(unsigned int *)(RX_CFG_CTXT_BUF_BASE + 0x2aa30 + 0x22000 + 0x800)

	/* 1 x 8 dword */
	#define DLRX_CFG_CTXT_RO_MAINLIST_BASE                  \
			(unsigned int *)(RX_CFG_CTXT_BUF_BASE + 0x2aa40 + 0x22000 + 0x800 + 0x10)

	/* 1 x 48 dwords */
	#define DLRX_CTXT_MSG_BASE                              \
			(unsigned int *)(RX_CFG_CTXT_BUF_BASE + 0x2aa48 + 0x22000 + 0x800 + 0x10)

	/* 1 x 4 dwords */
	#define DLRX_CFG_CTXT_RXPB_PTR_REL_MSGBUF_BASE          \
			(unsigned int *)(RX_CFG_CTXT_BUF_BASE + 0x2aa78 + 0x22000 + 0x800 + 0x10)

	/* 1 x 8 dwords */
	#define DLRX_CFG_GLOBAL_BASE                            \
			(unsigned int *)(RX_CFG_CTXT_BUF_BASE + 0x2aa80 + 0x22000 + 0x800 + 0x10)

	/* 128 x 2 dwords i.e. 128 peers x 2 dwords */
	#define DLRX_CFG_CTXT_PEER_HANDLER_BASE(i)              \
			(unsigned int *)(RX_CFG_CTXT_BUF_BASE + 0x2aa90 + \
							(i) * 2 + 0x22000 + 0x800 + 0x10)

	/* 4 x 1 dwords */
	#define DLRX_CFG_CTXT_PEER_BITMAP_BASE(i)               \
			(unsigned int *)(RX_CFG_CTXT_BUF_BASE + 0x2ab90 + i + 0x22000 + 0x800 + 0x10)

	/* 255 * 2 DWORDS  */
	#define DLRX_DDR_GSWIP_DMA_DESC_BASE                    \
		(volatile unsigned int *)(RX_CFG_CTXT_BUF_BASE + 0x2ac00 + 0x22000 + 0x800 + 0x10)


#define USING_BBCPU_SRAM 1
#ifdef USING_BBCPU_SRAM
	/* 512 * 2 DWORDS (shift from  SRAM) */
	#define BBCPU_SRAM_ADDR 0xb4000000
	#define DLRX_DDR_CE5DESC_BASE                           \
		(unsigned int *)(BBCPU_SRAM_ADDR)
	#define DLRX_BBCPU_CE5_CTXT_RD_IDX_BASE                           \
		(unsigned int *)(BBCPU_SRAM_ADDR + (1024*2*4))
	#define DLRX_BBCPU_CE5_CTXT_WRAPAROUND_IDX_BASE                           \
		(unsigned int *)(BBCPU_SRAM_ADDR + (1024*2*4) + 4)
	#define DLRX_BBCPU_CE5_CTXT_QCA_RD_IDX_BASE                           \
		(unsigned int *)(BBCPU_SRAM_ADDR + (1024*2*4) + 8)
#else
	#define DLRX_DDR_CE5DESC_BASE                           \
		(unsigned int *)(RX_CFG_CTXT_BUF_BASE + 0x2ae00 + 0x22000 + 0x800 + 0x10)
#endif
#if defined(CONFIG_ACCL_11AC_CS2)
	/* 16 dwords */
	#define DLRX_CE5_RESOURCES_BASE                         \
		(unsigned int *)(RX_CFG_CTXT_BUF_BASE + 0x2b200 + 0x22000 + 0x800 + 0x10)
#endif
	/* 2048 * 512 Bytes (2e000 -*/
	#define DLRX_DDR_CE5BUF_BASE                            \
			(unsigned int *)(RX_MSG_BUF_BASE)


	#define DLRX_TARGET_CE5_PEREGRINE                       0x00058800
	#define DLRX_TARGET_CE5_BEELINER                        0x0004B400

#ifdef USING_BBCPU_SRAM
	#define DLRX_TARGET_CE5_READ_INDEX(base)                \
		(unsigned int *)(DLRX_BBCPU_CE5_CTXT_RD_IDX_BASE)
	#define DLRX_QCA_TARGET_CE5_READ_INDEX(base)                \
		(unsigned int *)(pcie_base + ((base+0x48)>>2))
#else
	#define DLRX_TARGET_CE5_READ_INDEX(base)                \
		(unsigned int *)(pcie_base + ((base+0x48)>>2))
#endif

	/* 1 dword? */
	#define DLRX_TARGET_CE5_WRITE_INDEX(base)               \
		(unsigned int *)(pcie_base + ((base+0x40)>>2))

	#define DLRX_TARGET_CE5_IS_HOST_INDEX(base)               \
		(unsigned int *)(pcie_base + ((base+0x30)>>2))
#endif

/* Message type */
#define HTT_RX_IND_MSG                                  0x1
#define HTT_RX_FLUSH_MSG                                0x2
#define HTT_RX_FRAG_IND_MSG                             0xA
#define HTT_TX_CMP_MSG                                  0x7

/* Not actual message type, defined to identify message being sent
	to wlan driver/cpu_ce5/cpu_ce4/invalid_tid
	*/
#define HTT_RX_CPU_CE4                                  0xB
#define HTT_RX_CPU_CE5                                  0xC
#define HTT_RX_IND_MSG_WLAN                             0xD
#define HTT_RX_FLUSH_MSG_WLAN                           0xE
#define HTT_RX_INVALID_TID                              0xF


/* MPDU status */
#define MPDU_STATUS_SUCCESS                             0x1
#define MPDU_STATUS_FCS_ERROR                           0x2
#define MPDU_STATUS_DUPLICATE_ERROR                     0x3
#define MPDU_STATUS_REPLAY_ERROR                        0x4
#define MPDU_STATUS_INVALID_PEER                        0x5
#define MPDU_STATUS_UNAUTHORIZED_PEER                   0x6
#define MPDU_STATUS_OUT_OF_SYNC_PEER                    0x7
#define MPDU_STATUS_MANAGEMENT_CONTROL                  0x8
#define MPDU_STATUS_TKIP_MIB_ERROR                      0x9
#define MPDU_STATUS_DECRYPT_ERROR                       0xA
#define MSDU_STATUS_ERROR_5_DROP                        0xB
#define MSDU_STATUS_RO_LINKLIST_DROP                    0xC
#define MSDU_STATUS_CHAIN_MSDU_DROP                     0xD

/* Security Type */
#define SEC_TYPE_DISABLE                                0x0
#define SEC_TYPE_PN_48                                  0x1
#define SEC_TYPE_PN_128_EVEN                            0x2
#define SEC_TYPE_PN_128_ODD                             0x3

#define NUM_PEER                                        128
#define NUM_TID                                         31
#define NUM_SEQ_ID                                      64

/* Need to define a value for NULL_PTR as 0 is also a valid pointer */
/* Set to 0xFFF as the next_ptr value in dlrx_ro_linklist_t is 12 bits length*/
#define NULL_PTR                                        0xFFF

#define INVALID_TID                                     31

#define HTT_INVALID_PEER                                0xFFFF
#define PHY_ADDR_MASK                                   0x1FFFFFFF
/*
    This is the enumeration for Special Received MPDU Status. Used by
    \ref PPA_QCA_DL_RX_SPL_PKT_FN.
*/

/* Inspect Flag Set Rx Packet */
#define WLAN_INSPECT_TYPE		0x1
#define DRE_DBG_PRINT_ENABLE	1

/*#define DBG_CACHED_ADDR		1*/
#define HTT_RX_BUF_SIZE			1920
#define HTT_MSG_BUF_SIZE		512
extern void  dre_dma_map(unsigned int addr, unsigned int size);
extern void dre_dma_unmap(unsigned int  addr, unsigned int size);

#define dre_dma_map(addr, size) ppa_dl_dre_dma_writeback(addr, size)
#define dre_dma_unmap(addr, size) ppa_dl_dre_dma_invalidate(addr, size)
#define dre_dma_wback_invalidate(addr, size) \
	ppa_dl_dre_dma_wback_inv(addr, size)

#if (defined(DLRX_GRX330_BOARD_CFG) && (DLRX_GRX330_BOARD_CFG == 1))
#define VIR_TO_PHY(addr) CPHYSADDR(addr)
#define UNCACHE_ADDR(addr) KSEG1ADDR(addr)
#define CACHE_ADDR(addr)  KSEG0ADDR(addr)
#else
#define VIR_TO_PHY(addr) ((((unsigned int)addr)  & 0x0FFFFFFF) | 0x20000000)
#define PHY_TO_VIRT(addr) ((addr & 0x0fffffff) | dl_kseg0)
#define VIRT_TO_IOCU(addr) (((addr) & 0x1fffffff) | 0xC0000000)
#define UNCACHE_ADDR(addr)  ((((uint32_t)addr) & (0x0FFFFFFF)) | dl_kseg1)
#define CACHE_ADDR(addr)  ((((uint32_t)addr) & (0x0FFFFFFF)) | dl_kseg0)
#endif

#if defined(DBG_CACHED_ADDR) && DBG_CACHED_ADDR
#define dre_print(fmt, arg...)  do { printk(KERN_WARNING ":%d:%s: " \
				fmt "\n", __LINE__, __func__, ##arg); } \
				while (0)
#else
#define dre_print(fmt, arg...)
#endif

#endif

