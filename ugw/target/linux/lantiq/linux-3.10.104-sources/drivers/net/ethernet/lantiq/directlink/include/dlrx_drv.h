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
#ifndef __DLRX_DRV_H__
#define __DLRX_DRV_H__
#include <linux/klogging.h>

/****************************************************
 *	Extern Variable Declaration
 ****************************************************/
extern uint32_t g_dtlk_dbg_enable;

/****************************************************
 *	Extern Variable Declaration
 ****************************************************/
extern struct sk_buff *alloc_skb_rx(void);
extern struct net_device *dtlk_dev_from_vapid(
	uint32_t
	);
extern void dtlk_rx_api_init(void);
extern void dtlk_rx_api_exit(void);
extern void set_vap_itf_tbl(
	uint32_t vap_id,
	uint32_t itf_id
	);

/****************************************************
 *	Macro Definition
 ****************************************************/
#define DTLK_PACKET_SIZE		2048
#define DTLK_ALIGNMENT			32
#define DMA_CPU_OWNBIT			0

#define DTLK_SUCCESS			0
#define DTLK_FAILURE			-1
#define DTLK_ERROR				-2

#define HANDLER_FOUND			0
#define HANDLER_NOT_FOUND		-1
#define PEER_FIRST				1

#define DTLK_DBG				1
#define ENABLE_DTLK_DBG			1

#define MAX_MCAST_GROUP 64

/*#define PROFILING 1*/
#define USING_BBCPU_SRAM 1
#ifdef USING_BBCPU_SRAM
#define BBCPU_SRAM_ADDR 0xb4000000
#endif

#ifdef PROFILING
extern void	initProfiling(void);
#endif


#define ASSERT(cond, fmt, arg...) do { if (!(cond)) LOGF_KLOG_ERR_RATELIMITED("%s:%d:%s: " fmt "\n", __FILE__, __LINE__, __func__, ##arg); } while (0)

/*
 *	Debug Print Mask
 *	Note, once you add a new DBG_ macro,
 * don't forget to add it in DBG_ENABLE_MASK_ALL also !!!!
 */
#define DBG_ERR		BIT(0)
#define DBG_INIT	BIT(1)
#define DBG_RX		BIT(2)
#define DBG_TX		BIT(3)
#define DBG_CPU		BIT(4)
#define DBG_PROC	BIT(5)
#define DBG_PRINT	BIT(6)







#define DTLK_DBG_ENA (DBG_ERR | DBG_INIT | DBG_PRINT)
#define DTLK_DBG_ENABLE_MASK_ALL (DBG_RX | DBG_TX | DBG_CPU | DBG_PROC)

#define dtlk_debug(dbg_level, fmt, arg...) \
	do { \
		if ((g_dtlk_dbg_enable & dbg_level)) { \
			if (dbg_level & DBG_ERR) { \
				LOGF_KLOG_ERR_RATELIMITED(fmt, ##arg); \
			} else if ((dbg_level & DBG_PRINT) || \
					(dbg_level & DBG_INIT)) { \
				LOGF_KLOG_INFO_RATELIMITED(fmt, ##arg); \
			} else { \
				LOGF_KLOG_DEBUG_RATELIMITED(fmt, ##arg); \
			} \
		} \
	} \
	while (0)

#endif /* __DLRX_DRV_H__ */
