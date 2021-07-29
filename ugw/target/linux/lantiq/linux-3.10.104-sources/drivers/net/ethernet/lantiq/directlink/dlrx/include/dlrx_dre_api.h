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
#ifndef __DLRX_DRE_API_H__
#define __DLRX_DRE_API_H__

enum {
	DRE_MAIN_FN = 0,
	DRE_GET_VERSION_FN,
	DRE_RESET_FN,
	DRE_GET_MIB_FN,
	DRE_GET_CURMSDU_FN,
	DRE_SET_MEMBASE_FN,
	DRE_SET_RXPN_FN,
	DRE_SET_DLRX_UNLOAD,
	DRE_MAX_FN
};

enum {
	DRE_RESET_MIB,
	DRE_RESET_PEER,
};

enum {
	DRE_MSG_MIB,
	DRE_VAP_MIB,
	DRE_DATA_MIB,
};

enum {
	MIN_PEERID = 0,
	MAX_PEERID = 127
};

enum {
	MIN_VAPID = 0,
	MAX_VAPID = 15
};

enum {
	PEER_INVALID = 0,
	PEER_VALID	 = 1,
};

enum {
	INVALIDATE_HEADER = 0,
	INVALIDATE_FULL
};

enum {
	PEREGRINE_BOARD = 0,
	BEELINER_BOARD
};

enum {
	SUBTYPE_NONE_BOARD = 0,
	SUBTYPE_BEELINER_CASCADE_BOARD
};

enum {
	LOAD_QCA = 0,
	UNLOAD_QCA = 1
};


#define RESET_ALLVAP	0xFF
#define MAX_PEERID_NUM	1056
#define MAX_PEER_NUM	128
#define MAX_VAP_NUM		16
#define MAX_INV_PEREGRINE_HEADER_LEN	256
#define MAX_INV_BEELINER_HEADER_LEN		320
#define MAX_INV_CASCADE_HEADER_LEN		324

#define QCA_PEREGRINE_11AC_CFG_OFFSET_ATTEN   248
#define QCA_BEELINER_11AC_CFG_OFFSET_ATTEN	 296
#define QCA_CASCADE_11AC_CFG_OFFSET_ATTEN	 300

#define DTLK_INVALID_ITFID	0xF

typedef struct dre_register_func_set {
	void *dre_dl_main_fn;
	void *dre_dl_getver_fn;
	void *dre_dl_reset_fn;
	void *dre_dl_getmib_fn;
	void *dre_dl_getmsdu_fn;
	void *dre_dl_set_membase_fn;
	void *dre_dl_set_rxpn_fn;
	void *dre_dl_set_dlrx_unload_t;
} dre_regfn_set_t;

typedef int (*dre_dl_main_fn_t)(void);
typedef unsigned int (*dre_dl_getver_fn_t)(void);
/* reset type, vap id(0-15)/peer id(0-127) */
typedef void (*dre_dl_reset_fn_t)(
			unsigned int reset_type,
			unsigned int id_num
			);
typedef unsigned int (*dre_dl_getmib_fn_t)(
			unsigned int mib_type,
			unsigned int vapid
			);
/* return base addr and data len */
typedef int (*dre_dl_getmsdu_fn_t)(
			unsigned int *rxpb_ptr,
			unsigned int *data_len,
			unsigned int *flags
			);
/* configure the base address */
typedef int (*dre_dl_set_membase_fn_t)(
			unsigned int ddr_membase,
			unsigned int cfg_ctxt_membase,
			unsigned int pcie_membase
			);
/* set rxpn */
typedef int (*dre_dl_set_rxpn_fn_t)(
			unsigned int peer,
			unsigned int *rxpn
			);
typedef void (*dre_dl_set_dlrx_unload_t)(void);


/* API to support dre to send pkt to switch via dma */
extern int ppa_dl_dre_gswip_dma_send(
	unsigned int vap_id,
	unsigned int rxpb_ptr,
	unsigned int data_ptr,
	unsigned int data_len,
	unsigned int release_flag,
	unsigned int pmac_hdr_ptr,
	unsigned int unmap_type
	);

/* API to support dre to send pkt to protocol stack*/
extern int ppa_dl_dre_ps_send(
	unsigned int rxpb_ptr,
	unsigned int data_ptr,
	unsigned int data_len,
	unsigned int vap_id
	);

/* API to support dre to send pkt to wlan driver */
extern int ppa_dl_dre_wlan_pkt_send(
	unsigned int rxpb_ptr,
	unsigned int data_len,
	unsigned int pktstatus,
	unsigned int msg_ptr,
	unsigned int vap_id,
	unsigned int flags
	);

/* API to support dre to send message to wlan driver */
extern int ppa_dl_dre_wlan_msg_send(
	unsigned int msg_type,
	unsigned int msg_ptr,
	unsigned int msg_len,
	unsigned int flags
	);

/* API to support dre to release buff after receive the TX complete message */
extern int ppa_dl_dre_txpkt_buf_release(
	unsigned int num_msdus,
	unsigned int *msg,
	unsigned int flags
	);

/* API to support dre to register callback functons */
extern int ppa_dl_dre_fn_register(
	unsigned int regno,
	void *func
	);

/* API to get peer via peer id */
extern int ppa_dl_dre_peer_from_peerid(
	unsigned int peerid,
	unsigned int *peer
	);

/* API to get vap info via peer */
extern int ppa_dl_dre_vapinfo_from_peer(
	unsigned int peer,
	unsigned int *vapid,
	unsigned int *sec_type,
	unsigned int *acc_dis
	);

/* API to get interface id via vap id */
extern unsigned int ppa_dl_dre_itf_from_vapid(
	unsigned int vap_id
	);

/*API to set the vapinfo */
extern int ppa_dl_dre_vapinfo_set(
	unsigned int peer,
	unsigned int vapid,
	unsigned int sec_type,
	unsigned int acc_dis
	);


/* API to allocate a rxpb pkt buffer to FW */
extern unsigned int dlrx_dl_dre_rxpb_buf_alloc(void);

/*API to free the rxpb buffer*/
extern int ppa_dl_dre_rxpb_buf_free(
	unsigned int rxpb_ptr
	);

extern unsigned int ppa_dl_dre_get_sram_addr(void);

extern void ppa_dl_dre_dma_invalidate(
		unsigned int startAddr,
		unsigned int size
		);

extern void ppa_dl_dre_dma_writeback(
		unsigned int startAddr,
		unsigned int size
		);

extern void ppa_dl_dre_dma_wback_inv(
		unsigned int startAddr,
		unsigned int size
		);

extern unsigned int ppa_dl_dre_get_kseg0(void);

extern unsigned int ppa_dl_dre_get_kseg1(void);

extern void ppa_dl_dre_peer_act_fn(unsigned int peer_id);

#endif
