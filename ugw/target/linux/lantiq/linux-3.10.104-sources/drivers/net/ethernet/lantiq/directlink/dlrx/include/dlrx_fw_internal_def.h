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
#ifndef __DLRX_FW_INTERNAL_H__
#define __DLRX_FW_INTERNAL_H__


/*      defines      */
#define uint8_t  unsigned char
#define uint16_t unsigned short
#define uint32_t unsigned int

#if defined(CONFIG_ACCL_11AC_CS2)
/* 125 + 8 for linux */
#define DL_LI_IPI_NO		133
#endif
/* The value of 3 is set as the interface value to prevent passing
* invalid interface value to the switch during the playout process.
* The value could be any value between 3 to 7. Only condition is
* source and destination interface value should be same
*/
#define VALID_INTERFACE_NUMBER     3
#define CFG_OFFSET_ATTEN_IN_DWORDS 1

#define CONGESTION_REG_MASK        0x40

typedef enum {
	UPDATE_MSDU_MIB,
	UPDATE_MPDU_MIB
} mib_msdu_mpdu_update_switch;

typedef enum {
	INSPECT_BIT_DATA,
	ONE_PMAC_DATA,
	TWO_PMAC_DATA
} rx_outgoing_header_switch;

typedef enum {
	RECYCLE_RXPB_PTR,
	NEW_RXPB_PTR,
	RECYCLE_LL_RXPB_PTR
} rxpb_free_ptr_type;

typedef enum {
	WRONG_PN_SEQUENCE = 1,
	DMA_TX_CHANNEL_FULL
} dlrx_packet_drop_reason;

typedef enum {
	RECYCLE_RXPB,
	RELEASE_RXPB
} dlrx_rxpb_release_type;

/* Hardware Specific defines */
#define B_DLRX_RXPB_HDR_pn_63_48  \
	((g_qca_hw == BEELINER_BOARD) ? B_DLRX_RXPB_HDR_BEELINER_pn_63_48 : \
	B_DLRX_RXPB_HDR_PEREGRINE_pn_63_48)

#define MAX_INV_HEADER_LEN ((g_qca_hw == BEELINER_BOARD) ? \
		((g_qca_hw_sub_type == SUBTYPE_NONE_BOARD) ? \
		MAX_INV_BEELINER_HEADER_LEN : \
		MAX_INV_CASCADE_HEADER_LEN) : \
		MAX_INV_PEREGRINE_HEADER_LEN)

/* Variable Definition */
extern unsigned int global_debug_flag;
extern unsigned int global_debug_print;
extern unsigned int g_cfg_badr_ce5buf;
extern unsigned int g_cfg_badr_ce5des;
extern unsigned int g_cfg_badr_rxpb_ptr_ring;
extern unsigned int g_cfg_badr_ro_linklist;
extern unsigned int g_cfg_badr_ro_mainlist;

extern unsigned int g_qca_hw;
extern unsigned int g_qca_hw_sub_type;
extern unsigned int g_ce5_offset;
extern unsigned int g_congestion_timeout_num;
extern unsigned int g_congestion_drop_flag;
extern unsigned int *congestion_register_addr;



/* 2 NOTE: Make sure the values set here are same as
* the ones set by driver in the cfg ctxt structure
*/
#if	DLRX_GRX330_BOARD_CFG
#define GET_NUM_CE5BUF			(512)
#define GET_CE5BUF_SIZE_SHIFT	(9)
#define GET_NUM_RXPB_PTR_RING   (1024)
#else
//#define GET_NUM_CE5BUF			(512)
#define GET_NUM_CE5BUF			(1024)
#define GET_CE5BUF_SIZE_SHIFT	(9)
#define GET_NUM_RXPB_PTR_RING	 (1024)
#endif
#define GET_RXPKT_DESC_SIZE ((g_qca_hw == BEELINER_BOARD) ? \
			((g_qca_hw_sub_type == SUBTYPE_NONE_BOARD) ? \
			QCA_BEELINER_11AC_CFG_OFFSET_ATTEN : \
			QCA_CASCADE_11AC_CFG_OFFSET_ATTEN) : \
			QCA_PEREGRINE_11AC_CFG_OFFSET_ATTEN)
#define GET_OFFSET_ATTEN (4)

/* Function Definition */
/* Functions defined in DLRX_reorder_buffering_process.c */
void dlrx_reorder_buffering_process(unsigned int *ce5_buf_ptr);

/* Functions defined in DLRX_utility_fns.c */
void dlrx_add_outgoing_data_to_rxpb_buffer(unsigned int *rxpb_buf_ptr,
		rx_outgoing_header_switch outgoing_header_switch);
unsigned int dlrx_get_interface_data_from_vap(unsigned int vap);
unsigned int dlrx_get_current_rxpb_buf_ptr(void);
unsigned int dlrx_get_ind_msg_mpdu_data_offset(unsigned int *ce5_buf_ptr);
void dlrx_get_fw_rx_desc_byte_data(unsigned int *ce5_buf_ptr);
void dlrx_copy_last_pn_to_mainlist(void);
unsigned int dlrx_is_pn_check_fail(void);
unsigned int dlrx_get_ro_ll_rxpb_ptr(void);
unsigned int dlrx_check_congestion_status(void);
void dlrx_generate_debug(unsigned int);
void dlrx_print_rolist_debug_data(void);
void dlrx_unregister_driver_fns(void);

/* Functions defined in RO_list_fns.c */
unsigned int ro_list_add_data(unsigned int *ce5_buf_ptr,
		unsigned int *rxpb_buf_ptr);
unsigned int ro_linklist_get_free_ro_desc(void);
void ro_list_release_data(unsigned int ce5_buf_ptr);
unsigned int ro_linklist_return_free_ptr(unsigned int ro_des_free_ptr);
void ro_list_reset(unsigned int peer);
void ro_list_reset_a_tid_seqid(unsigned int peer,
		unsigned int ext_tid,
		unsigned int mpdu_index,
		unsigned int rxpb_release_type
		);
void ro_list_clear(void);

/* Functions defined in RXPB_fns.c */
void rxpb_write_free_buffer_to_rxpb_ptr_ring(rxpb_free_ptr_type free_ptr_type);
void rxpb_find_duplicate_ptr_value(void);
void rxpb_free_buffers_on_unload(void);

/* Functions defined in MIB_data_update.c */
void mib_update_status_counters(mib_msdu_mpdu_update_switch switch_value,
		unsigned int status_value);
void mib_update_vap_dlrx_data(unsigned int msdu_length,
		dlrx_packet_drop_reason packet_drop_reason);

/* Functions defined in dlrx_playout_process.c */
void dlrx_playout_process(unsigned int ce5_buf_ptr);
void dlrx_send_packet_to_dma_descriptor(unsigned int ce5_buf_ptr);

/* Functions defined in dlrx_drv_api_fns.c */
unsigned int dlrx_drv_get_revision(void);
void dlrx_drv_reset(unsigned int reset_type, unsigned int id_num);
unsigned int *dlrx_drv_get_mib_data(unsigned int mib_type,
		unsigned int vap_id);
int dlrx_drv_get_cur_rxpb_ptr(unsigned int *rxpb_ptr,
	unsigned int *data_len,
	unsigned int *flags);
/* void dlrx_drv_replenish_rxpb_ptr(void); */
/* configure the base address */
int dlrx_drv_set_mem_base(unsigned int ddr_membase,
		unsigned int cfg_ctxt_membase,
		unsigned int pcie_membase);
int dlrx_drv_set_wapi_rxpn(unsigned int peer, unsigned int *rxpn);
void dre_drv_set_dlrx_unload(void);
#endif
