
#ifndef __NEW_FEATURE_LE_H_
#define __NEW_FEATURE_LE_H_

	typedef struct {

		unsigned int psave_en:1;
		unsigned int asc_mode:1;
		unsigned int ssc_mode:1;
		unsigned int class_en:1;
		unsigned int session_mib_unit:1;
		unsigned int app4_fast_path_en:1;
		unsigned int vrx218_en:1;
		unsigned int vrx218_atm:1;
		unsigned int _res0:8;
		unsigned int time_tick:16;

	} new_feature_cfg_t;

	typedef struct {

		unsigned int capwap_itf_bmap:8;
		unsigned int _res0:24;

	} capwap_config_t;

	typedef struct {

		unsigned int acc_en:1;
		unsigned int is_ipv4header:1;
		unsigned int _res0:2;
		unsigned int qid:4;
		unsigned int us_dest_lit:8;
		unsigned int us_max_frag_size:16;

		unsigned int rsvd_1;

		unsigned int rsvd_2;

		unsigned int ds_mib;

		unsigned int us_mib;

		unsigned int da_hi;

		unsigned int da_lo_sa_hi;

		unsigned int sa_lo;

		unsigned int tos:8;
		unsigned int head_len:4;
		unsigned int version:4;
		unsigned int eth_type:16;

		unsigned int identifier:16;
		unsigned int total_len:16;

		unsigned int protocol:8;
		unsigned int ttl:8;
		unsigned int ip_frag_off:13;
		unsigned int ip_flags:3;

		unsigned int sa_ip:16;
		unsigned int ip_checksum:16;

		unsigned int sa_ip_da_ip;

		unsigned int src_port:16;
		unsigned int da_ip_lo:16;

		unsigned int udp_ttl_len:16;
		unsigned int dst_port:16;

		unsigned int rid_hi:3;
		unsigned int hlen:5;
		unsigned int preamble:8;
		unsigned int udp_checksum:16;

		unsigned int frag_id:16;
		unsigned int flags:3;
		unsigned int k_flag:1;
		unsigned int m_flag:1;
		unsigned int w_flag:1;
		unsigned int l_flag:1;
		unsigned int f_flag:1;
		unsigned int t_flag:1;
		unsigned int wbid:5;
		unsigned int rid_lo:2;

		unsigned int payload:16;
		unsigned int capwap_rsv:3;
		unsigned int frag_off:13;

	} capwap_table_config_t;

	typedef struct {

		unsigned int tx_in_aca_msg_ptr;

		unsigned int tx_out_aca_msg_ptr;

		unsigned int rx_in_aca_msg_ptr;

		unsigned int rx_out_aca_msg_ptr;

		unsigned int tx_in_wr_ptr;

		unsigned int tx_out_rd_ptr;

		unsigned int rx_in_wr_ptr;

		unsigned int rx_out_rd_ptr;

		unsigned int tx_in_fw_cnt;

		unsigned int tx_out_fw_cnt;

		unsigned int rx_in_fw_cnt;

		unsigned int rx_out_fw_cnt;

		unsigned int tx_in_pend_fw_cnt;

		unsigned int _dw_res0[3];

	} soc_aca_cfg_ctxt_t;

	typedef struct {

		unsigned int tx_in_enq_cnt;

		unsigned int tx_out_deq_cnt;

		unsigned int rx_in_enq_cnt;

		unsigned int rx_out_deq_cnt;

	} total_soc_aca_cnt_t;

	typedef struct {

		unsigned int tx_in_deq_cnt;

		unsigned int tx_out_enq_cnt;

		unsigned int rx_in_deq_cnt;

		unsigned int rx_out_enq_cnt;

	} total_dev_aca_cnt_t;

#endif

