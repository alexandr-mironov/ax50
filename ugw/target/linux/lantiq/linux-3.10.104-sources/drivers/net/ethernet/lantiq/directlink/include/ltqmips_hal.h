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
#ifndef LTQMIPS_HAL_H
#define LTQMIPS_HAL_H
struct ppe_dtlk_map{
	uint32_t	vap_id;
	struct PPA_NETIF *dev;
	uint32_t	flags;
	uint32_t	dl_rx_pkts; /* receive from WIFI HW */
	uint32_t	dl_tx_pkts; /* send to WIFI HW */
	uint32_t	dl_rx_drop_pkts;
	uint32_t	dl_tx_drop_pkts;
	PPA_SUBIF	dl_sub_if;
	struct module	*owner;
};

struct ppe_radio_map{
	uint32_t	flags;
	PPA_SUBIF	dl_sub_if;
	struct ppe_dtlk_map g_ppe_dtlk_data[16];
};


#define __DIRLINK_ENABLE 0x5E00
#define PHYADDR_MASK 0x1FFFFFFF

#define __D6_RX_MIB_SIZE	__D6_SUPPORT_VAP_NUM
#define __D6_RX_MIB_BASE	__D6_PER_VAP_MIB_BASE

#define SIZE_CE4DES	8
#define SIZE_CPUSRCDES	64
#define SIZE_HTT_TXDES	16
#define LEN_HTT_TXDES	32
#define NUM_HTT_TXDES	8
#define SIZE_TXPB	2048
#define NUM_TXPB	4096
#define RESERVED_TXPB	8
/* 8 DWORD, DWORD0 pkt buffer address, DWORD1 pkt len, not inited, DWORD2 0 */
#define PBPTR_TXPB	32
/* point to packet addr */
#define PBADDR_TXPB 64
#define SIZE_TXDES 24
#define SIZE_TXHEADER 44
#define LOW_MARK 0x200
#define HIGH_MARK 2
#define DMA_RX_CH7_DESC_BASE DTLK_RX_ADDR(__D6_RXDMA7_DES_BASE)
#define DMA_RX_CH7_DESC_NUM 8


struct offload_tx_release_t {
	uint8_t reserved1;
	uint8_t num_msdus;
	uint16_t reserved0;
	uint16_t msdu_ids[__D6_TXPB_MSG0_SIZE*2];
};

typedef struct {
	uint32_t rx_mpdu_ok;
	uint32_t rx_msdu_ok;
	uint32_t rx_mpdu_err2;
	uint32_t rx_msdu_err2;
	uint32_t rx_mpdu_err3;
	uint32_t rx_msdu_err3;
	uint32_t rx_mpdu_err4;
	uint32_t rx_msdu_err4;
	uint32_t rx_mpdu_err5;
	uint32_t rx_msdu_err5;
	uint32_t rx_mpdu_err6;
	uint32_t rx_msdu_err6;
	uint32_t rx_mpdu_err7;
	uint32_t rx_msdu_err7;
	uint32_t rx_mpdu_err8;
	uint32_t rx_msdu_err8;
	uint32_t rx_mpdu_err9;
	uint32_t rx_msdu_err9;
	uint32_t rx_mpdu_errA;
	uint32_t rx_msdu_errA;
} PPA_WLAN_Rx_MPDU_MSDU_Stats_t;
#endif
