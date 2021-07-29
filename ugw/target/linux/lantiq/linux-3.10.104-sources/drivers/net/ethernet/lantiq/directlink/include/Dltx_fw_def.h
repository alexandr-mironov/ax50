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
#ifndef __DLTX_FW_DEF_H__
#define __DLTX_FW_DEF_H__

/*extern struct genconf gc;*/

#define dl_kseg0 KSEG0
#define dl_kseg1 KSEG1

#define DL_TX_MODE_PUSH_NO_CLASSIFY	0
#define DL_TX_MODE_PUSH_PULL 		1

#if defined(CONFIG_ACCL_11AC_CS2)
#define DL_TX_PFLOW_CTRL_MIN_THRESHOLD          256
#define DL_TX_PFLOW_CTRL_MAX_BUF_GLOBAL         (32*1024)
#define DL_TX_PFLOW_CTRL_MAX_QUEUE_LEN          (4*1024)
#define DL_TX_PFLOW_CTRL_MIN_QUEUE_LEN          256
#define DL_TX_PFLOW_CTRL_QDEPTH_FLUSH_INTERVAL  256
#define DL_TX_PFLOW_CTRL_CONG_CTRL_TIMER_MS     1000
#define DL_TX_PFLOW_CTRL_STATS_TIMER_MS         1000
#define DL_TX_PFLOW_CTRL_ROT_TIMER_MS           2
#define DL_MSDU_DEFAULT_TTL                     10000
#define WMI_DSCP_MAP_MAX 64
#endif

/*#define TX_CFG_CTXT_BUF_BASE                            gc.dl_buffer_info.tx_cfg_ctxt_buf_base*/


#define DLTX_CE4_WRITE_INDEX_TRACK_OFFSET			0  /*4096 dwords*/

#define DLTX_CIRCULAR_LIST_OFFSET					0x1000 /*Byte offset: 0x4000    4096 dwords*/

#define DLTX_BUFFER_POINTER_TABLE_OFFSET			0x2000 /*Byte offset: 0x8000    4096 dwords*/

#define HTT_TX_DES_OFFSET(vap)						(0x3000 + (vap * (8)))  /*Byte offset: 0xC000   16*8 = 128 dwords*/

#define DLTX_QCA_VAP_ID_MAP_OFFSET					0x3080  /*Byte offset: 0xC200 16 dwords*/

#define DLTX_VAP_DATA_MIB_OFFSET(vap)				(0x3090 + (vap * (16))) /*Byte offset: 0xC240   16*16 = 256 dwords*/

#define DLTX_DATA_MIB_OFFSET						0x3190 /*Byte offset: 0xC640   8 dwords*/

#define DLTX_CFG_CTXT_CE4BUF_OFFSET					0x3198 /*Byte offset: 0xC660  16 dwords*/

#define DLTX_CFG_CTXT_CIRCULAR_LIST_OFFSET			0x31A8 /*Byte offset: 0xC6A0   8 dwords*/

#define DLTX_CFG_CTXT_BUFFER_POINTER_TABLE_OFFSET	0x31B0 /*Byte offset: 0xC6C0  4 dwords*/

#define DLTX_CFG_CTXT_CE4_WRITE_INDEX_TRACK_OFFSET	0x31B4 /*Byte offset: 0xC6D0  4 dwords*/

#define DLTX_CFG_CTXT_TX_MSG_OFFSET				    0x31B8 /*Byte offset: 0xC6E0  4 dwords*/

#define DLTX_CFG_CTXT_QCA_VAP_ID_MAP_OFFSET			0x31BC /*Byte offset: 0xC6F0  4 dwords*/

#define DLTX_CTXT_MSG_OFFSET						0x31C0 /*Byte offset: 0xC700  24 dwords*/

#define DLTX_CFG_GLOBAL_OFFSET						0x31D8 /*Byte offset: 0xC760 16 dwords*/

#define DLTX_CFG_CTXT_CIRCULAR_LIST_LINUX_OFFSET	0x31E8 /*Byte offset: 0xC7a0 16 dwords*/

#define DLTX_FRAG_DATA_OFFSET                       0x3200 /*Byte offset: 0xC800  16 * 4096 = 65536 dwords*/

#define DLTX_CFG_CTXT_FRAG_DATA_OFFSET              0x13200 /*Byte offset: 0x4C7A0  4 dwords*/

#define DLTX_CFG_CTXT_M2C_PEER_TABLE                0x13204 /*Byte offset: 0x4C810  128(peer) * 2 dwords*/

#define DLTX_CFG_CTXT_M2C_GROUP_TABLE               0x13304 /*Byte offset: 0x4CC10  64(group) * 5 dwords*/

#define DLTX_CFG_CTXT_M2C_PEER_EXT_TABLE            0x13450 /*Byte offset: 0x4D140  128(peer) * 2 dwords*/

#define DLTX_CFG_CTXT_M2C_GROUP_EXT_TABLE           0x13550 /*Byte offset: 0x4D540  64(group) * 5 dwords*/

#if defined(CONFIG_ACCL_11AC_CS2)

#define DLTX_CFG_CTXT_CE5_RESOURCE	                0x13750 /*Byte offset: 0x4dd40  4 dwords*/

#define DLTX_CFG_CTXT_CE5_PFLOW_CTRL                0x13760 /*Byte offset: 0x4dd80  12 dwords*/

#define DLTX_CFG_CTXT_CE5_PEER_FLOW_CTRL        	0x13790 /*Byte offset: 0x4de40  16 dwords*/

#define DLTX_BUFFER_ID_TABLE_OFFSET(packet_id)		(0x14000 + (packet_id)) /* Byte offset: 0x50000    4096 dwords - DLTX_BUFFER_POINTER_TABLE_OFFSET */

#define DLTX_CFG_CTXT_CE4_PFLOW_CTRL                0x13760 /*Byte offset: 0x4dd80  16 dwords*/

#define DLTX_PFLOW_DSCP_TID_TABLE		            0x13780 /*Byte offset: 0x4ddd0  16 dwords*/

#define DL_DMA_PEER_NUM 16
#define DL_DMA_TID_NUM 9
#define PRIO_Q_SIZE		(DL_DMA_PEER_NUM * DL_DMA_TID_NUM)

#define DLTX_PRIO_SOFT_QUEUE_DMA_DESC_CTXT			0x15400 /* byte offset:0x55000 (128 * 8)(queues) * 12 dword */

/* 128 dword, one word for one qca peer id */
#define DLTX_CE5_PEER_MAP_TO_PEER_ID				0x18A00	/* byte offset:0x62800 */

#define DLTX_PEER_MAP_TABLE							0x18A80 /* Byte offset: 0x62a00 , reseved 4k dword*/

#define DLTX_FETCH_RESP_ID_TABLE					0x19A80 /* byte offset:0x66a00, 1k dword */

#define DLTX_WDS_CLIENT_PEER_TABLE					0x19E80 /* byte offset:0x67a00, 128*128*2 dword */

#endif
#define DLTX_PACKET_ID_TRACE_CIRCULAR_LIST_OFFSET	0x21e80 /* Byte offset: 1(tx) + 1(tx_ptr) + 1(completion) + 1(comple_ptr) + 64(dwords) x1000    4096 dwords */

/*Structure offsets for communication buffer structures*/

#define DLTX_TX_CMPL_FLAG_OFFSET					0	  /*2*8 = 16 dwords*/

#define DLTX_TX_CMPL_MSG_OFFSET						0x10  /* Byte offset: 0x40    8* 129 = 1032 dwords*/

#define DLTX_CFG_CTXT_CPU_CE4DES_OFFSET				0x418  /*Byte offset: 0x1060  8 dwords*/

#define DLTX_CPU_CE4DES_FORMAT_OFFSET				0x420  /*Byte offset: 0x1080  128 * 2 = 256 dwords*/

#define DLTX_CFG_CTXT_COMM_BUFF_OFFSET				0x520 /*Byte offset: 0x1480    8 dwords*/

#define DLTX_DRV_MSG_OFFSET							0x528 /*Byte offset: 0x14A0  64 dwords*/


/*Hardware addresses*/

/*address in QCA 11ac target*/
/*CE4 base address*/
#define CE4SRC_BEELINER_HI                          0x4
#define CE4SRC_MISC_IE_BEELINER_LOW                 0xB034

/*CE4 read and write index*/
#define CE4SRC_TARGET_WR_PTR_BEELINER_LOW           0xB03C
#define CE4SRC_TARGET_RD_PTR_BEELINER_LOW           0xB044


#endif

