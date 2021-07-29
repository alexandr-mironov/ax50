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
#ifndef __DLTX_FW_DATA_STRUCTURE_BE_H_
#define __DLTX_FW_DATA_STRUCTURE_BE_H_

typedef struct {

	unsigned int packet_pointer;

	unsigned int rsvd0:16;
	unsigned int fragment_length:16;

	unsigned int rsvd1;

	unsigned int rsvd2;

	unsigned int rsvd3;

	unsigned int rsvd4;

	unsigned int payload_len:16;
	unsigned int flags:8;
	unsigned int endpoint_id:8;

	unsigned int rsvd5:16;
	unsigned int control_bytes_1:8;
	unsigned int control_bytes_2:8;

	unsigned int rsvd6:1;
	unsigned int chk_sum:2;
	unsigned int mib:1;
	unsigned int postponed:1;
	unsigned int ext_tid:5;
	unsigned int vdec_id:6;
	unsigned int pkt_type:3;
	unsigned int pkt_subtype:5;
	unsigned int msg_type:8;

	unsigned int pb_pointer:16;
	unsigned int length:16;

	unsigned int frag_desc_pointer;

	unsigned int peer_id;

} dltx_msg_header_t;

typedef struct {

	unsigned int rsvd9:3;
	unsigned int tunnel_id:4;
	unsigned int flow_id:8;
	unsigned int eth_type:2;
	unsigned int dest_sub_if_id:15;

	unsigned int session_id:12;
	unsigned int tcp_err:1;
	unsigned int nat:1;
	unsigned int dec:1;
	unsigned int enc:1;
	unsigned int mpe2:1;
	unsigned int mpe1:1;
	unsigned int color:2;
	unsigned int ep:4;
	unsigned int res:4;
	unsigned int class:4;

	unsigned int dram_address;

	unsigned int own:1;
	unsigned int c_bit:1;
	unsigned int sop:1;
	unsigned int eop:1;
	unsigned int dic:1;
	unsigned int pdu_type:1;
	unsigned int byte_offset:3;
	unsigned int rsvd10:7;
	unsigned int data_length:16;

} dltx_dma_rx_desc_t;

typedef struct {

	unsigned int source_buffer_pointer;

	unsigned int meta_data:14;
	unsigned int byte_swap:1;
	unsigned int gather:1;
	unsigned int source_buffer_length:16;

} dltx_ce4des_format_t;

typedef struct {

	unsigned int ce4_write_index;

} dltx_ce4_write_index_track_t;

typedef struct {

	unsigned int packet_id;

} dltx_circular_list_t;

typedef struct {

	unsigned int pointer_address;

} dltx_buffer_pointer_table_t;

typedef struct {

	unsigned int rsvd11:15;
	unsigned int frag_len:17;

	unsigned int payloadlen:16;
	unsigned int flags:8;
	unsigned int endpointid:8;

	unsigned int rsvd12:16;
	unsigned int controlbyte1:8;
	unsigned int controlbyte2:8;

	unsigned int rsvd13:1;
	unsigned int chksum:2;
	unsigned int mib:1;
	unsigned int postponed:1;
	unsigned int exttid:5;
	unsigned int vdevid:6;
	unsigned int pkttype:3;
	unsigned int pktsubtype:5;
	unsigned int msgtype:8;

	unsigned int packet_id:16;
	unsigned int length:16;

	unsigned int _dw_res0[3];

} htt_tx_des_t;

typedef struct {

	unsigned int qca_vap_id;

} dltx_qca_vap_id_map_t;

typedef struct {

	unsigned int txpdu_low;

	unsigned int txpdu_high;

	unsigned int txbytes_low;

	unsigned int txbytes_high;

	unsigned int txdrop_low;

	unsigned int txdrop_high;

	unsigned int _dw_res0[10];

} dltx_vap_data_mib_t;

typedef struct {

	unsigned int cpu_ce4_msg_low;

	unsigned int cpu_ce4_msg_high;

	unsigned int cpu_ce4_bytes_low;

	unsigned int cpu_ce4_bytes_high;

	unsigned int _dw_res0[4];

} dltx_data_mib_t;

typedef struct {

	unsigned int cfg_badr_ce4buf;

	unsigned int cfg_num_ce4buf;

	unsigned int cfg_ce4_read_index_addr;

	unsigned int cfg_ce4_write_index_addr;

	unsigned int local_ce4_read_index;

	unsigned int local_ce4_write_index;

	unsigned int load_ce4_read_index_req;

	unsigned int cfg_ce4des_low;

	unsigned int cfg_ce4_des_full;

	unsigned int _dw_res0[7];

} dltx_cfg_ctxt_ce4buf_t;

typedef struct {

	unsigned int circular_list_badr;

	unsigned int circular_list_num;

	unsigned int circular_list_read_index;

	unsigned int circular_list_write_index;

	unsigned int consumed_pkt_ids;

	unsigned int _dw_res0[3];

} dltx_cfg_ctxt_circular_list_t;

typedef struct {

	unsigned int buffer_pointer_badr;

	unsigned int buffer_pointer_num;

	unsigned int _dw_res0[2];

} dltx_cfg_ctxt_buffer_pointer_table_t;

typedef struct {

	unsigned int write_index_track_badr;

	unsigned int write_index_track_num;

	unsigned int _dw_res0[2];

} dltx_cfg_ctxt_ce4_write_index_track_t;

typedef struct {

	unsigned int cfg_size_tx_header;

	unsigned int _dw_res0[3];

} dltx_cfg_ctxt_tx_msg_t;

typedef struct {

	unsigned int qca_vap_id_map_badr;

	unsigned int qca_vap_id_map_num;

	unsigned int _dw_res0[2];

} dltx_cfg_ctxt_qca_vap_id_map_t;

typedef struct {

	unsigned int ext_tid;

	unsigned int pkt_type;

	unsigned int pkt_subtype;

	unsigned int msg_type;

	unsigned int pb_pointer;

	unsigned int pb_length;

	unsigned int peer_id;

	unsigned int vap;

	unsigned int radio_id;

	unsigned int _dw_res0[15];

} dltx_ctxt_msg_t;

typedef struct {

	unsigned int dltx_enable;

	unsigned int dltx_base_address;

	unsigned int fw_ver_id;

	unsigned int fw_feature;

	unsigned int debug_print_enable;

	unsigned int switch_parser_flag;

	unsigned int qca_support_cs2;

	unsigned int _dw_res0[8];

} dltx_cfg_global_t;

typedef struct {

	unsigned int fragment_ptr[16];

} dltx_frag_data_t;

typedef struct {

	unsigned int frag_data_badr;

	unsigned int frag_data_num;

	unsigned int _dw_res0[2];

} dltx_cfg_ctxt_frag_data_t;

struct _dl_mcast_group_table {
	/* first dw */
	unsigned int valid:1;
	unsigned int res:23;
	unsigned int grpIdx:8;
	/* Bit map */
	unsigned int bitmap[4];
};

struct _dl_peer_mac_mapping_table {
	/* first dw */
	unsigned int valid:1;
	unsigned int vap_id:4;
	unsigned int res:11;
	unsigned int mac5:8;
	unsigned int mac4:8;
	/* second dw */
	unsigned int mac3:8;
	unsigned int mac2:8;
	unsigned int mac1:8;
	unsigned int mac0:8;
};

#if defined(CONFIG_ACCL_11AC_CS2)
struct _dl_ce5_resource {
	/* QCA target */
	unsigned int qca_target_ce5_read_index_ptr;
	unsigned int qca_target_ce5_write_index_ptr;
	unsigned int qca_target_ce5_is_host_ptr;
	/* CE5 resources */
	unsigned int ce5_numb;
	unsigned int ce5_ctxt_ce5des_base;
	unsigned int ce5_ctxt_ce5buf_base;
	/* MSI Interrupt */
	uint32_t dl_msi_irq;
	uint32_t bbcpu_dltx_rd_idx_base;
	uint32_t bbcpu_dltx_wraparnd_cnt_base;
	uint32_t bbcpu_qca_rd_idx_base;
	uint32_t peer_id_mapping_base;
};
struct dl_dma_desc_ctrl {
	int _head_idx:16;
	int _tail_idx:16;
};
struct dl_prio_queue {
	uint32_t pending_cnt;
	uint32_t deq_cnt;
	uint32_t enq_cnt;
	uint32_t timeout_cnt;
	uint32_t drop_overflow_cnt;
	uint32_t byte_cnt;
	/* This should be dynamically allocated by MPE HAL to size of dma desc len */
	uint32_t discard_cnt;
	uint32_t resv1[1];
	struct dl_dma_desc_ctrl desc_ctrl;
};

struct _dl_ce4_pflow_control {
    uint32_t pmap_qdepth_flush_interval;
    uint32_t pmap_qdepth_flush_count;
    uint32_t pmap_rotting_timer_interval;
    uint32_t pflow_ctrl_stats_enable;
    uint32_t pflow_ctrl_mode:8;
    uint32_t pflow_ctrl_low_latency_mode:8;
    uint32_t pflow_tidq_map:8;
    uint32_t pflow_hostq_dump:8;
    uint32_t pflow_max_peer;
    uint32_t resv[1];
    uint32_t pflow_msdu_default_ttl;
    uint32_t pflow_ctl_min_threshold;
    uint32_t pflow_ctl_desc_count;
    uint32_t pflow_cong_ctrl_timer_interval;
    uint32_t pflow_ctl_stats_timer_interval;
    uint32_t pflow_ctl_global_queue_cnt;
    uint32_t pflow_ctl_min_queue_len;
    uint32_t pflow_ctl_max_queue_len;
    uint32_t pflow_ctl_max_buf_global;
    uint32_t pflow_ctl_total_dequeue_cnt;
    uint32_t pflow_ctl_total_dequeue_byte_cnt;
    uint32_t pflow_ctl_total_enqueue_cnt;
    uint32_t pflow_ctl_total_enqueue_byte_cnt;
    uint32_t *pflow_ctl_queue_max_len;/* an 128 dword array to set length for each queue*/
};

#define DL_TXRX_MAX_PEER_IDS		532
#define NUM_PEER_BYTE_CNTS_IN_WORD	4
#define MAX_PEER_MAP_WORD 			((DL_TXRX_MAX_PEER_IDS) / 32 + 1)

#define DL_TX_PFLOW_CTRL_MAX_TIDS	8

struct peermap_t {
	uint32_t byte_cnt[DL_TX_PFLOW_CTRL_MAX_TIDS][DL_TXRX_MAX_PEER_IDS / NUM_PEER_BYTE_CNTS_IN_WORD];
	uint32_t tid_peermap[DL_TX_PFLOW_CTRL_MAX_TIDS][MAX_PEER_MAP_WORD];
	uint32_t seq;
};
#endif /* SUPPORT_CS2 */

#endif

