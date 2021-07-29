#ifndef DATAPATH_H
#define DATAPATH_H

#include <linux/skbuff.h>

#define DRV_MODULE_VERSION          "1.3.1"

#define DP_ERROR(fmt, args...) pr_err("DP [%s:%d] " fmt, __func__, __LINE__, ##args)
#define DP_INFO(fmt, args...) pr_info("DP [%s:%d] " fmt, __func__, __LINE__, ##args)
#define CONFIG_LTQ_DATAPATH_DBG 1
#if defined(CONFIG_LTQ_DATAPATH_DBG) && CONFIG_LTQ_DATAPATH_DBG
	#define DP_DEBUG(flags, fmt, args...) \
		do { \
			if ((dp_dbg_flag & flags)) { \
				pr_info("DP [%s:%d] " fmt, __func__, __LINE__, ##args); \
			} \
		} while (0)
#else /* #if defined(CONFIG_LTQ_DATAPATH_DBG) && CONFIG_LTQ_DATAPATH_DBG */
	#define DP_DEBUG(level, fmt, args...)
#endif /* #if defined(CONFIG_LTQ_DATAPATH_DBG) && CONFIG_LTQ_DATAPATH_DBG */

#define DP_DEBUG_ASSERT(expr, fmt, arg...)  do { if (expr) \
		DP_ERROR(fmt, ##arg); }   \
		while (0)

#define DP_DBG(fmt, args...) \
	do { \
		DP_DEBUG(DP_DBG_FLAG_DBG, fmt, ##args); \
	} while (0)

#define IFNAMSIZ 16

#define DP_LIB_LOCK    spin_lock_bh
#define DP_LIB_UNLOCK  spin_unlock_bh

#define MAX_SUBIF_PER_PORT 16

#define CHECK_BIT(var, pos) (((var) & (1<<(pos))) ? 1 : 0)

#define VAP_OFFSET 8
#define VAP_MASK  0xF
#define VAP_DSL_OFFSET 3

#define DP_MAX_PORT_IDX  5
#define DP_MAX_PORTS  8
#define MAX_PID       32
#define MAX_VPID      51

#define DP_STATS_CPU    0x00000001
#define DP_STATS_ACCEL  0x00000002
#define DP_STATS_ALL    (DP_STATS_CPU | DP_STATS_ACCEL)
#define DP_XMIT_F_FORCE        0x00000001

#define __ETH1_TX_DES_ADDR 0x3ac0
/*! D5 new resources for 518 */
/* include resource from D5 */
#define	__VRX218_SYNC_DES_LIST_BASE		0x3820	/*0x3820-0x385F	32	x	2	=	64*/
#define	__VRX218_SYNC_DES_LIST_SIZE		64
#define	__VRX218_SYNC_DES_LIST_NUM		32
#define	__VRX218_SYNC_DES_LIST_GUARD	31

#define	__STD_DES_CFG					0x20A6

#define	__SOC_ACA_CFG_CTXT				0x2030	/*0x2030-0x203F		16	x	1	=	16*/

#define	__SOC_TX_IN_DESQ_CFG_CTXT		0x37D8	/*0x37D8-0x37DF		8	x	1	=	8*/
#define	__SOC_RX_IN_DESQ_CFG_CTXT		0x3A60	/*0x3A60-0x3A67		8	x	1	=	8*/

#define	__SOC_TX_IN_DES_LIST_BASE		__ETH1_TX_DES_ADDR
#define	__SOC_TX_IN_DES_LIST_SIZE		64
#define	__SOC_TX_IN_DES_LIST_NUM		32
#define	__SOC_TX_IN_DES_LIST_NUM_MASK	0x1F
#define	__SOC_TX_IN_DES_LIST_GUARD		31

#define	__SOC_TX_OUT_DES_LIST_BASE		0x26C0	/*0x26C0-0x273F	64	x	2	=	128*/
#define	__SOC_TX_OUT_DES_LIST_SIZE		128
#define	__SOC_TX_OUT_DES_LIST_NUM		64
#define	__SOC_TX_OUT_DES_LIST_GUARD		63

#define	__SOC_RX_IN_DES_LIST_BASE		0x5600	/*0x5600-0x57FD		255 x 2=	510*/
#define	__SOC_RX_IN_DES_LIST_SIZE		510
#define	__SOC_RX_IN_DES_LIST_NUM		255
#define	__SOC_RX_IN_DES_LIST_NUM_MASK	0xFF
#define	__SOC_RX_IN_DES_LIST_GUARD		254

#define	__SOC_RX_OUT_DES_LIST_BASE		0x57FE	/*0x57FE-0x59FB		255 x 2=	510*/
#define	__SOC_RX_OUT_DES_LIST_SIZE		510
#define	__SOC_RX_OUT_DES_LIST_NUM		255
#define	__SOC_RX_OUT_DES_LIST_GUARD		254

#define	__TOTAL_SOC_ACA_CNT_BASE		0x3BF8	/*0x3BF8-0x3BFB	4 x 1 = 4*/

#define	__TOTAL_DEV_ACA_CNT_LE_BASE		0x20B0	/*0x20B0-0x20B3	4 x 1 = 4*/
#define	__TOTAL_DEV_ACA_CNT_BE_BASE		0x20B4	/*0x20B4-0x20B7	4 x 1 = 4*/

#define	__TOTAL_DEV_ACA_CNT_BASE		__TOTAL_DEV_ACA_CNT_BE_BASE//0x3BFC

#define	__MAX_TX_IN_HD_DES_NUM			32

#define	__MAX_RX_IN_HD_DES_NUM			32

#define	__IS_VRX518						0x3439

#define	__DSL_CPU_DES_LIST_BASE			0x2FA0	/*0x2FA0-0x2FDF	32	x	2	=	64*/
#define	__DSL_CPU_DES_LIST_SIZE			64
#define	__DSL_CPU_DES_LIST_NUM			32
#define	__DSL_CPU_DES_LIST_GUARD		31

//CPU path descriptor read pointer
#define __CPU_IN_DESC_RDPTR		0x328E
//fast path descriptor read pointer
#define __FP_IN_DESC_RDPTR		0x328D
//outq write pointer
#define __ETH1_TX_WRPTR			0x328C
//WAN Mode switching Configuration
#define __SOC_MODE_SWITCH		0x2F14
#define	__DSL_QOS_VALID			0x2F17
// bit[0:3] qid for PVC0, bit[4:7] qid for PVC1,
// bit[8:11]qid for PVC2, bit[12:15] qid for PVC3
// bit[16:19] qid for PVC4, bit[20:23] qid for PVC5,
// bit[24:27]qid for PVC6, bit[28:31] qid for PVC7
#define	__DSLQID2ETHQID_MAP0					0x2F18

// bit[0:3] qid for PVC8, bit[4:7] qid for PVC9,
// bit[8:11]qid for PVC10, bit[12:15] qid for PVC11
// bit[16:19] qid for PVC12, bit[20:23] qid for PVC13,
// bit[24:27]qid for PVC14, bit[28:31] qid for PVC15
#define	__DSLQID2ETHQID_MAP1					0x2F19

/*! dp subif flag */
enum SUBIF_FLAG {
	SUBIF_FREE,		/*! The subif is free */
	SUBIF_REGISTERED,	/*! The subif is registered */
};

/*! dp subif flag */
enum DSL_CHIPSET {
	DSL_UNKNOWN = -1,
	DSL_318,
	DSL_518,
};

/*! dp port flag */
enum PORT_FLAG {
	PORT_NOT_READY,		/*! The port is not ready to be allocated yet */
	PORT_FREE,		/*! The port is free */
	PORT_ALLOCATED,		/*! the port is already allocated to some driver,
					but not registered or no need to register at all.\n
					for example, LRO/CAPWA, only need to allocate,
					but no need to register
					*/
	PORT_DEV_REGISTERED,	/*! dev Registered already. */
	PORT_SUBIF_REGISTERED,	/*! subif Registered already. */


	PORT_FLAG_NO_VALID	/*! Not valid flag */
};

/*! Sub interface detail information */
struct dp_subif_info {
	enum SUBIF_FLAG flags;
	uint32_t subif:15;
	struct net_device *netif;	/*! pointer to  net_device */
	char device_name[IFNAMSIZ];	/*! devide name, like wlan0, */
	struct rtnl_link_stats64 if_stats;    /* slowpath stats */
	//AVALANCHE_PP_VPID_STATS_t stats_delta; /* acceleration stats (for clearing vpid stats) */
};

struct pmac_port_info {
	enum PORT_FLAG status;	/*! port status */
	int alloc_flags;	/* the flags saved when calling dp_port_alloc */
	struct dp_cb cb;	/*! Callback Pointer to DIRECTPATH_CB */
	struct module *owner;
	struct net_device *dev;
	uint32_t dev_port;
	uint32_t num_subif;
	int32_t port_id;
	struct dp_subif_info subif_info[MAX_SUBIF_PER_PORT];
	uint32_t tx_err_drop;
	uint32_t rx_err_drop;

};


extern struct pmac_port_info dp_port_info[DP_MAX_PORT_IDX];/*port 0 is reserved */
extern void dp_init();
extern void dp_exit();

extern struct proc_dir_entry *dp_proc_install(struct proc_dir_entry *);
extern void dp_proc_remove(void);
extern char *dp_dbg_flag_str[];
extern unsigned int dp_dbg_flag_list[];
extern uint32_t dp_port_flag[];
extern char *dp_port_type_str[];
extern char *dp_port_status_str[];
extern char *dp_subif_status_str[];



extern int get_dp_dbg_flag_str_size(void);
extern int get_dp_port_status_str_size(void);
extern int get_dp_subif_status_str_size(void);
extern int get_dp_port_type_str_size(void);

ssize_t proc_print_mode_write(struct file *file, const char *buf, size_t count,
		       loff_t *ppos);
void proc_print_mode_read(struct seq_file *s);

struct pmac_port_info *get_port_info_via_dp_name(struct net_device *dev);

static inline unsigned int get_vap(uint32_t subif)
{
	return ((subif >> 8) & 0xf);
}

static inline void set_vap(uint32_t *subif, uint32_t value)
{
	*subif = ~(0xf << 8) & *subif;
	*subif = *subif | ((value  & 0xf) << 8);
}

extern int dc_dp_ppe_start_xmit(struct sk_buff *skb, dp_subif_t *rx_subif, struct net_device *dev, uint32_t flags);
extern void dsl_chipset_type_set(enum DSL_CHIPSET type);
extern int dsl_chipset_type_get();
extern int dc_dp_ppe_518_path_enable(int);
struct sk_buff * dc_dp_alloc_dma(int len);
extern void dc_dp_free_dma(unsigned int dataptr);
extern void dbg_pool_check(char *str);
#endif				/*DATAPATH_H */
