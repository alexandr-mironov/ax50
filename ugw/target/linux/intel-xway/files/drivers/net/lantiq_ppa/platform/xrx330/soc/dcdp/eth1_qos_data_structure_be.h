
#ifndef __ETH1_QOS_DATA_STRUCTURE_BE_H_
#define __ETH1_QOS_DATA_STRUCTURE_BE_H_

	typedef struct {

		unsigned int time_tick:16;
		unsigned int overhd_bytes:8;
		unsigned int eth1_eg_qnum:4;
		unsigned int _res0:1;
		unsigned int eth1_qss:1;
		unsigned int shape_en:1;
		unsigned int wfq_en:1;

	} tx_qos_cfg_t;

	typedef struct {

		unsigned int threshold:8;
		unsigned int desc_num:8;
		unsigned int base_adr:16;

		unsigned int rd_ptr:16;
		unsigned int wr_ptr:16;

	} eth1_qos_q_des_cfg_t;

	typedef struct {

		unsigned int own:1;
		unsigned int c:1;
		unsigned int sop:1;
		unsigned int eop:1;
		unsigned int byte_off:5;
		unsigned int qos:4;
		unsigned int res:2;
		unsigned int small:1;
		unsigned int data_len:16;

		unsigned int _res0:3;
		unsigned int data_ptr:29;

	} tx_descriptor_t;

	typedef struct {

		unsigned int own:1;
		unsigned int c:1;
		unsigned int sop:1;
		unsigned int eop:1;
		unsigned int dic:1;
		unsigned int pdu_type:1;
		unsigned int byte_off:3;
		unsigned int qos:4;
		unsigned int mpoa_pt:1;
		unsigned int mpoa_type:2;
		unsigned int data_len:16;

		unsigned int data_ptr:32;

	} unified_tx_descriptor_t;

	typedef struct {

		unsigned int own:1;
		unsigned int c:1;
		unsigned int sop:1;
		unsigned int eop:1;
		unsigned int dic:1;
		unsigned int pdu_type:1;
		unsigned int byte_off:3;
		unsigned int qos:4;
		unsigned int mpoa_pt:1;
		unsigned int mpoa_type:2;
		unsigned int data_len:16;

		unsigned int data_ptr:32;

	} unified_rx_descriptor_t;

	typedef struct {

		unsigned int des_in_own_val:1;
		unsigned int enabled:1;
		unsigned int fpq_shutdown:1;
		unsigned int swap_en:1;
		unsigned int _res0:12;
		unsigned int cdma_des_num:8;
		unsigned int vrx218_syncdes_num:8;

		unsigned int cdma_des_base:16;
		unsigned int cdma_idx:16;

		unsigned int vrx218_syncdes_base:16;
		unsigned int vrx218_idx:16;

		unsigned int us_fpq_rx_cnt;

		unsigned int us_fpq_swap_drop_cnt;

		unsigned int us_fpq_shutdown_drop_cnt;

		unsigned int res1;

		unsigned int res2;

	} us_fpq_swap_cfg_ctxt_t;

	typedef struct {

		unsigned int t:8;
		unsigned int w:24;

		unsigned int s:16;
		unsigned int r:16;

		unsigned int _res0:8;
		unsigned int d:24;

		unsigned int _res1:8;
		unsigned int tick_cnt:8;
		unsigned int b:16;

	} eth1_shaping_scheduling_cfg_t;

	typedef struct {

		unsigned int total_rx_pkt;

		unsigned int total_rx_bytes;

		unsigned int total_tx_pkt;

		unsigned int total_tx_bytes;

		unsigned int cpu_path_small_pkt_drop_cnt;

		unsigned int cpu_path_total_pkt_drop_cnt;

		unsigned int fast_path_small_pkt_drop_cnt;

		unsigned int fast_path_total_pkt_drop_cnt;

	} eth1_shaping_scheduling_mib_t;

	typedef struct {

		unsigned int large_frame_drop_th:16;
		unsigned int large_frame_size:16;

	} tx_qosq_bandwidth_ctrl_t;

	typedef struct {

		unsigned int _res0:14;
		unsigned int byte_off:2;
		unsigned int data_len:16;

	} cfg_std_data_len_t;

	typedef struct {

		unsigned int own:1;
		unsigned int c:1;
		unsigned int sop:1;
		unsigned int eop:1;
		unsigned int _res0:3;
		unsigned int byte_off:2;
		unsigned int _res1:7;
		unsigned int data_len:16;

		unsigned int _res2:3;
		unsigned int data_ptr:29;

	} rx_descriptor_t;

	typedef struct {

		unsigned int _res0:14;
		unsigned int byte_off:2;
		unsigned int data_len:16;

	} std_des_cfg_t;

	typedef struct {

		unsigned int des_in_own_val:1;
		unsigned int fast_path:1;
		unsigned int mbox_int_en:1;
		unsigned int des_sync_needed:1;
		unsigned int _res0:1;
		unsigned int gif_id:3;
		unsigned int des_num:8;
		unsigned int des_base_addr:16;

		unsigned int mbox_int_cfg_ptr:16;
		unsigned int bp_des_base_addr:16;

		unsigned int deq_idx:16;
		unsigned int enq_idx:16;

		unsigned int _dw_res0;

		unsigned int enq_pkt_cnt;

		unsigned int enq_byte_cnt;

		unsigned int deq_pkt_cnt;

		unsigned int deq_byte_cnt;

	} desq_cfg_ctxt_t;

#endif

