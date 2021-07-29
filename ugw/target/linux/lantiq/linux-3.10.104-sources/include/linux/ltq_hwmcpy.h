/******************************************************************************
 *
 *                        Copyright (c) 2012, 2014, 2015
 *                           Lantiq Deutschland GmbH
 *
 *  For licensing information, see the file 'LICENSE' in the root folder of
 *  this software module.
 *  
 ******************************************************************************/

#ifndef __LTQ_HWMCPY_H__
#define __LTQ_HWMCPY_H__

enum {
	HWMCPY_F_PRIO_LOW	= 0x0,
	HWMCPY_F_PRIO_HIGH	= 0x1,
	HWMCPY_F_IPC		= 0x2,
	HWMCPY_F_CHKSZ_1	= 0x4,
	HWMCPY_F_CHKSZ_2	= 0x8,
	HWMCPY_F_CHKSZ_3	= 0xC,
	HWMCPY_F_CHKSZ_4	= 0x10,
/*Trunk size support from 0 to 0x7(512B,1KB to 64KB),
 start from bit 2, len 3 bits, max 0x1C */
	HWMCPY_F_RESERVED	= 0x20,
	HWMCPY_F_CHKSZ_SET	= 0x40,
	HWMCPY_F_LAST		= 0x80,

};

enum mcpy_type {
	MCPY_PHY_TO_PHY = 0,
	MCPY_PHY_TO_IOCU,
	MCPY_IOCU_TO_PHY,
	MCPY_IOCU_TO_IOCU,
	MCPY_SW_CPY,
};

struct mcpy_frag {
	void *ptr;
	u16 offset;
	u16 size;
};

enum umt_mode {
	UMT_SELFCNT_MODE = 0,
	UMT_USER_MODE    = 1,
	UMT_MODE_MAX,
};
enum umt_msg_mode {
	UMT_NO_MSG    = 0,
	UMT_MSG0_ONLY = 1,
	UMT_MSG1_ONLY = 2,
	UMT_MSG0_MSG1 = 3,
	UMT_MSG_MAX,
};

enum umt_status {
	UMT_DISABLE = 0,
	UMT_ENABLE  = 1,
	UMT_STATUS_MAX,
	UMT_BROKEN,
};

extern void *ltq_hwmemcpy(void *dst, const void *src, u32 len,
				u32 portid, enum mcpy_type mode, u32 flags);
extern int ltq_hwmcpy_sg(void *dst, const struct mcpy_frag *src, u32 frag_num,
				u32 portid, enum mcpy_type mode, u32 flags);
extern int ltq_mcpy_reserve(void);
extern void ltq_mcpy_release(u32);

#ifdef CONFIG_LTQ_UMT_LEGACY_MODE
extern int ltq_umt_enable(u32 enable);
extern int ltq_umt_set_mode(u32 umt_mode, u32 msg_mode,
				u32 phy_dst, u32 period, u32 enable);
extern int ltq_umt_set_period(u32 period);
#else
int ltq_umt_set_period(u32 umt_id, u32 ep_id, u32 period);
int ltq_umt_set_mode(u32 umt_id, u32 ep_id, u32 umt_mode, u32 msg_mode,
			u32 phy_dst, u32 period, u32 enable);
int ltq_umt_enable(u32 umt_id, u32 ep_id, u32 enable);
int ltq_umt_request(u32 ep_id, u32 cbm_pid,
		u32 *dma_ctrlid, u32 *dma_cid, u32 *umt_id);
int ltq_umt_release(u32 umt_id, u32 ep_id);
int ltq_umt_suspend(u32 umt_id, u32 ep_id, u32 enable);
#ifdef CONFIG_LTQ_UMT_SW_MODE
int umt_reset_port_dq_idx(u32 cbm_id);
#endif

#endif

#ifdef CONFIG_LTQ_UMT_518_FW_SG
#define MIPS_TC_DMA0_CS_REG 0xb6e00018
#define MIPS_TC_DMA_CDPTNRD_REG 0xb6e00034
#define MIPS_TC_OPTIMIZE 1

#ifdef  MIPS_TC_OPTIMIZE
struct mips_tc_q_cfg_ctxt {
		u32 des_in_own_val;
		u32 _res0;
		u32 des_num;
		
		u32 des_base_addr;

		u32 rd_idx;
		u32 wr_idx;

		u32 _dw_res0;
		
		u32 rd_frag_cnt;
		
		u32 _dw_res1;

		u32 wr_frag_cnt;
		
		u32 _dw_res2;

		u32 rd_pkt_cnt;

		u32 rd_byte_cnt;

		u32 wr_pkt_cnt;

		u32 wr_byte_cnt;

};

struct mips_tc_fw_memcpy_ctxt_t {
		u32 _res0;
		u32 sop;
		u32 eop;
		u32 byte_off;
		u32 src_data_ptr;
		u32 dst_data_ptr;
		u32 data_len;

};

struct mips_tc_fw_pp_ctxt_t {
		u32 split_error;
		u32 status;
		u32 rx_in_hd_accum;
		u32 _res0;
		u32 sop;
		u32 eop;
		u32 byte_off;
		u32 _res1;
		u32 src_data_ptr;
		u32 dst_data_ptr;
		u32 data_len;
		u32 pkt_data_len;
		u32 prev_dma_tx_ptr;
		u32 prev_dma_rx_ptr;
		u32 _res2;
		u32 _res3;

};


struct mips_tc_metadata {
		u32 sop_frag;
		u32 eop_frag;
		u32 _res0;
		u32 _res1;
		u32 byte_off;
		u32 data_len;
		u32 src_data_ptr;
		u32 dst_data_ptr;

};

struct mips_tc_rxout_dst_cache_ctxt {
		u32 data_ptr;
};



#else /* MIPS_TC_OPTIMIZE */
/* Define DMA descriptors */
struct mips_tc_q_cfg_ctxt {
		u32 des_in_own_val:1;
		u32 _res0:15;
		u32 des_num:16;
		
		u32 des_base_addr;

		u32 rd_idx:16;
		u32 wr_idx:16;

		u32 _dw_res0;
		
		u32 rd_frag_cnt;
		
		u32 _dw_res1;

		u32 wr_frag_cnt;
		
		u32 _dw_res2;

		u32 rd_pkt_cnt;

		u32 rd_byte_cnt;

		u32 wr_pkt_cnt;

		u32 wr_byte_cnt;

};

struct mips_tc_fw_memcpy_ctxt_t {
		u32 _res0:30;
		u32 sop:1;
		u32 eop:1;
		u32 byte_off;
		u32 src_data_ptr;
		u32 dst_data_ptr;
		u32 data_len;

};

struct mips_tc_fw_pp_ctxt_t {
		u32 split_error:12;
		u32 status:4;
		u32 rx_in_hd_accum:12;
		u32 _res0:2;
		u32 sop:1;
		u32 eop:1;
		u32 byte_off;
		u32 src_data_ptr;
		u32 dst_data_ptr;
		u32 data_len;
		u32 pkt_data_len;

};

struct mips_tc_metadata{
	
		u32 sop_frag:1;
		u32 eop_frag:1;
		u32 _res0:14;
		u32 data_len:16;

};

struct mips_tc_rxout_dst_cache_ctxt {
		u32 data_ptr;
};



#endif /* MIPS_TC_OPTIMIZE */


struct mips_tc_tx_descriptor{

		u32 own:1;
		u32 c:1;
		u32 sop:1;
		u32 eop:1;
		u32 dic:1;
		u32 pdu_type:1;
		u32 byte_off:3;
		u32 qos:4;
		u32 mpoa_pt:1;
		//u32 mpoa_type:2;
		//u32 sop_frag:1;
		//u32 eop_frag:1;

		u32 sop_frag:1;
		u32 eop_frag:1;
		u32 data_len:16;
		u32 data_ptr:32;
};

struct mips_tc_rx_descriptor{

		u32 own:1;
		u32 c:1;
		u32 sop:1;
		u32 eop:1;
		u32 dic:1;
		u32 pdu_type:1;
		u32 byte_off:3;
		u32 qos:4;
		u32 mpoa_pt:1;
		//u32 mpoa_type:2;
		u32 sop_frag:1;
		u32 eop_frag:1;
		u32 data_len:16;
		
		u32 data_ptr:32;

};


/* Section 1: Define MIPS TC control & debug structure */
#define MIPS_TC_DEBUG_MSG_LEN 256
#define MIPS_TC_DEBUG_MSG_ARRAY_LEN 4
struct mips_tc_msg_param {
	u32 flags;
	char message[MIPS_TC_DEBUG_MSG_LEN];
};
enum {
	MIPS_TC_C_STOP	= 0x0,
	MIPS_TC_C_RUN	= 0x1,
};

struct mips_tc_ctrl_dbg {
	u32 mips_tc_control;
	u32 dbg_flags;
	u32 ver_major:8;
	u32 ver_mid:8;
	u32 ver_minor:8;
	u32 ver_reserved:8;
	u32 priv_data_vir;
	u32 priv_data_phy;
	u32 priv_data_len;
	u32 ctrl_max_process_pkt;
	u32 reserved[16];
	u32 msg_cur_idx;
	struct mips_tc_msg_param msgs[MIPS_TC_DEBUG_MSG_ARRAY_LEN];
};

struct mips_tc_tx_des_soc{

		u32 dword0;
		
		u32 dword1;
		
		struct mips_tc_tx_descriptor dword2_3;

};

struct mips_tc_rx_des_soc{

		u32 dword0;
		
		u32 dword1;
		
		struct mips_tc_rx_descriptor dword2_3;

}; 

/* Section 2: Memory configuration */
struct mips_tc_mem_conf {
	/* Sec1: memory configure context */
	struct mips_tc_q_cfg_ctxt soc_rx_out_src_ctxt;
	struct mips_tc_q_cfg_ctxt soc_sg_dma_tx_ctxt;
	struct mips_tc_q_cfg_ctxt soc_sg_dma_rx_ctxt;
	struct mips_tc_q_cfg_ctxt soc_rx_out_dst_ctxt;
	/* Sec2: Current context */
	struct mips_tc_fw_memcpy_ctxt_t fw_memcpy_ctxt;
	struct mips_tc_fw_pp_ctxt_t fw_pp_ctxt;
	/* Sec3: control variable */
	u32 aca_hw_rxin_hd_acc_addr;
	u32 tc_mode_bonding;
	u32 reserved[16];
	struct mips_tc_rxout_dst_cache_ctxt *cache_rxout_ptr;
};
/* Section 3: MIPS TC Info */
enum {
	MIPS_TC_S_ERROR	= -1,
	MIPS_TC_S_IDLE	= 0x0,
	MIPS_TC_S_RUNNING = 0x1,
	MIPS_TC_S_BUSY = 0x2,
};
struct mips_tc_mib {
	u32 jobs;
	u32 reserved[32];
};
struct mips_tc_info {
	u32 state;
	struct mips_tc_mib mib;
};
/* Define shared memory: note that new field
* should be added to the tail of the structure.
* The layout:
*   - Control and debug structure ( 518 <-> SoC): mips_tc_ctrl_dbg
*   - Memory configuration(518 -> SoC): mips_tc_mem_conf
* 		+ Memory configure context.
*	- MIPS TC information (SoC -> 518): mips_tc_info
*		+ State machine, mib
*	- Others
*/
struct mips_tc_sg_mem {
	struct mips_tc_ctrl_dbg ctrl;
	struct mips_tc_mem_conf conf;
	struct mips_tc_info mib;
};
extern int mips_tc_get_shared_mem(struct mips_tc_sg_mem **shared_mem);
#endif /* CONFIG_LTQ_UMT_518_FW_SG */

#endif /* __LTQ_HWMCPY_H__ */
