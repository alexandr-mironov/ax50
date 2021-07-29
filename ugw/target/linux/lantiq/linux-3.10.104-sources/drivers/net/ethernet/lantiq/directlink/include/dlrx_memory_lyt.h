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
#ifndef __DLRX_MEMORY_LYT_H_
#define __DLRX_MEMORY_LYT_H_

/* The maximum size is fixed for DLRX FW as 4Kbyte */
#define DLRX_CFG_CTXT_MAX_SIZE	0x2000

/* Definition of length for each Data Structure */
#define GSWIP_DESC_NUM				254
#define WLAN_DESC_NUM				254
#define PROTO_DESC_NUM				254

#define CPU_CE5_DESC_RING_NUM		2
#define RX_PKT_BUF_REL_MSG_NUM		2
#define CE5_DEST_DESC_RING_NUM		1024
#define CE5_DEST_MSG_BUF_NUM		CE5_DEST_DESC_RING_NUM
/* Must >= desc ring num  */
/* this value should be 2^n */
#define RX_PKT_BUF_PTR_RING_NUM		1024
#define RX_PKT_BUF_PTR_RING_ALLOC_NUM	1024
#define RX_REORDER_MAIN_NUM			(128 * 31)
#define RX_REORDER_DESC_LINK_NUM	4095

#define RX_PEER_ID_PEER_MAP			132
#define RX_PEER_TO_VAP_PN			128
#define RX_PEER_RESET				1
#define RX_VAP2INT_MAP1				1
#define RX_VAP2INT_MAP2				1

#define DLRX_CE5_DEST_BUF_SIZE	512


#define TRUE 1
#define FALSE 0

#define ZERO 0
#define ONE 1

#define VALID 1

/* DMA	Related Definition */
#define DMA_BASE			0xBE104100
#define DMA_CS				(volatile u32*)(DMA_BASE + 0x18)
#define DMA_CCTRL			(volatile u32*)(DMA_BASE + 0x1C)
#define DMA_CDBA			(volatile u32*)(DMA_BASE + 0x20)
#define DMA_CDLEN			(volatile u32*)(DMA_BASE + 0x24)
#define DMA_CIS				(volatile u32*)(DMA_BASE + 0x28)
#define DMA_CIE				(volatile u32*)(DMA_BASE + 0x2C)
#define PPE_TX_CH_NO		3

typedef struct {
	uint32_t gswip_desc_num;
	uint32_t wlan_desc_num;
	uint32_t proto_desc_num;
	uint32_t cpu_ce5_desc_ring_num;
	uint32_t rx_pkt_buf_rel_msg_num;
	uint32_t ce5_dest_desc_ring_num;
	uint32_t ce5_dest_msg_buf_num;
	uint32_t rx_pkt_buf_ptr_ring_num;
	uint32_t rx_reorder_main_num;
	uint32_t rx_reorder_desc_link_num;
} dlrx_bufsize_t;


#endif
