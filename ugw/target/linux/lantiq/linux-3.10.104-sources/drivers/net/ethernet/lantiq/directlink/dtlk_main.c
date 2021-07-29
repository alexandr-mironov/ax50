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
/*####################################
 *				Head File
 * ####################################
 */

/*Common Head File
 */
#include <linux/module.h>
#include <linux/moduleparam.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/version.h>
#include <linux/types.h>
#include <linux/ctype.h>
#include <linux/fs.h>
#include <linux/proc_fs.h>
#include <linux/miscdevice.h>
#include <linux/etherdevice.h>
#include <linux/ethtool.h>
#include <linux/if_ether.h>
#include <linux/if_arp.h>
#include <asm/uaccess.h>
#include <asm/unistd.h>
#include <asm/irq.h>
#include <asm/delay.h>
#include <asm/addrspace.h>
#include <asm/io.h>
#include <linux/netdevice.h>
#include <net/ppa_ppe_hal.h>
#include <linux/list.h>
#include <linux/delay.h>
#include <net/ppa_stack_al.h>
#include <net/ppa_api_directpath.h>
#include <net/ppa_api.h>
#include <net/datapath_api.h>
#include <net/ltq_mpe_api.h>
#include <linux/dma-mapping.h>
#include <xway/switch-api/lantiq_gsw_api.h>
#include <linux/pci.h>
#include <net/ltq_mpe_hal.h>
#include <net/ltq_mpe_hal.h>
#include <net/lantiq_cbm.h>
#include <net/lantiq_cbm_api.h>

#include "./include/11ac_acc_data_structure_tx_be.h"
#include "./include/dlrx_drv.h"
#include "./include/dlrx_fw_data_structure_be.h"
#include "./include/dltx_fw_data_structure_be.h"
#include "./include/dlrx_fw_def.h"
#include "./include/Dltx_fw_def.h"
#include "./include/dlrx_wlan_api.h"
#include "./include/dlrx_dre_api.h"
#include "./include/dlrx_memory_lyt.h"
#include "./include/dlrx_fw_version.h"
#include "./include/directlink_tx_cfg.h"
#include "./include/ltqmips_hal.h"
#include "./include/dltx_fw_comm_buf_data_structure_be.h"


#if defined(CONFIG_LANTIQ_MCAST_HELPER_MODULE) || defined(CONFIG_LANTIQ_MCAST_HELPER)
#include "../../../../net/lantiq_ppa/ppa_api/ppa_api_core.h"
#endif

#include <xway/switch-api/lantiq_gsw_api.h>
#include <xway/switch-api/lantiq_gsw_flow.h>



#define	MAX_DIRECTPATH_NUM	5
#define MAX_DIRECTLINK_NUM 16
struct ppe_directpath_data g_ppe_directpath_data[MAX_DIRECTPATH_NUM];
struct dl_drv_address_map g_dl_drv_address;
struct dl_buf_info g_dl_buf_info;

#define MAX_TX_DESCRIPTOR 2496

/*****************************************************
 *	 Macro definition
 *****************************************************/
#define MOD_AUTHOR			"Zhu YiXin, Ho Nghia Duc"
#define MOD_DESCRIPTION		"Accelerate QCA 11AC TX RX Traffic"
#define MOD_LICENCE			"GPL"
#define DRV_MAJOR		0
#define DRV_MID		2
#define DRV_MINOR		0xA
#define DRV_VERSION	((DRV_MAJOR << 24) | (DRV_MID << 16) | DRV_MINOR)

#define INLINE				inline
#define DIRECTLINK_PROC_DIR	"dl"

#define DLTX_DRV_TO_EXIT 1
#define DLTX_DRV_TO_DEBUG 2


#define NUM_ENTITY(x)		(sizeof(x) / sizeof(*(x)))

typedef dma_addr_t ce_addr_t;

struct ce_src_desc {
	ce_addr_t src_ptr;
	u_int32_t	meta_data:12,
				target_int_disable:1,
				host_int_disable:1,
				byte_swap:1,
				gather:1,
				nbytes:16;
};

int dl_param_tx_descriptor = MAX_TX_DESCRIPTOR;

module_param(dl_param_tx_descriptor, int, S_IWUSR | S_IWGRP);
MODULE_PARM_DESC(dl_param_tx_descriptor, "Establish number of TX DESCRIPTOR");

int dl_param_tx_pflow_mode = DL_TX_MODE_PUSH_NO_CLASSIFY;

module_param(dl_param_tx_pflow_mode, int, S_IWUSR | S_IWGRP);
MODULE_PARM_DESC(dl_param_tx_pflow_mode, "Set TX Mode");

/*****************************************************
 *	External functions
 *****************************************************/
extern int mpe_hal_dl_alloc_resouce(uint32_t mem_size,
	uint32_t *mem_addr,
	uint32_t flags);

/*****************************************************
 *	Global Parameter
 *****************************************************/
uint32_t g_ce5_desc_ring_num = CE5_DEST_DESC_RING_NUM;
uint32_t g_ce5_buf_ptr_ring_num = RX_PKT_BUF_PTR_RING_NUM;
u32 g11ACWirelessCardID = PEREGRINE_BOARD;
u32 g11ACWirelessCardID_SUBTYPE = SUBTYPE_NONE_BOARD;
struct device *g_mpe_dev;
uint32_t g_mpe_dltx_tc;
/**************************************/

/*
 * !!! These three base address must be
* initialized before access any FW structure
* */
unsigned int *ddr_base;
unsigned int *ddr_mpe_base;
unsigned int *ddr_mpe_comp_base;
unsigned int *cfg_ctxt_base;
unsigned int *pcie_base;

extern dre_regfn_set_t g_dre_fnset;
extern uint32_t g_dlrx_max_inv_header_len;
extern uint32_t g_dlrx_cfg_offset_atten;

/* QCA cards information */
#define PCI_VENDOR_ATHEROS 0x168C
#define PCI_ATH_DEV_PEREGRINE 0x003C
#define PCI_ATH_DEV_BEELINER 0x0040
#define PCI_ATH_DEV_BEELINER_CASCADE 0x0046
#define PCI_ATH_DEV_BEELINER_BESRA 0x0056

#define MAX_DTLK_NUM	16
#define MAX_RADIO_NUM	1
/* can extend to 8 */
#define MAX_TX_COMP_MAX 4
static DEFINE_SPINLOCK(g_ppe_dtlk_spinlock);
static struct ppe_radio_map	g_ppe_radio[MAX_RADIO_NUM];
#define DTLK_RX_ADDR(offset) (ddr_base + offset)
#define DTLK_RX_CTXT_ADDR(offset) (cfg_ctxt_base + offset)
#define MPE_TX_ADDR(offset) (ddr_mpe_base + offset)
#define MPE_TX_COML_ADDR(offset) (ddr_mpe_comp_base + offset)

extern int (*datapath_dtlk_switch_parser)(void);
extern int (*datapath_dtlk_register_fn)(PPA_SUBIF *sub_if, PPA_DTLK_T *dtlk);

#if defined(CONFIG_ACCL_11AC_CS2)
extern uint8_t g_peerid;
extern int32_t (*dl_get_subifid_fn)(struct net_device *netif,
	struct sk_buff *skb,
	void *subif_data,
	uint8_t dst_mac[MAX_ETH_ALEN],
	dp_subif_t *subif,
	uint32_t flags
	);
#endif

void (*set_vap_itf_tbl_fn)(uint32_t, uint32_t) = NULL;
EXPORT_SYMBOL(set_vap_itf_tbl_fn);
int dl_m2c_remove_peer(
	uint32_t *mac_addr,
	uint16_t peer_id,
	uint16_t vap_id,
	uint16_t extension
	);
int dl_m2c_find_peer(
	unsigned char *peer_mac,
	unsigned int extension,
	unsigned int b_get_wds_index
	);
/*****************************************************
 *	Internal Variables
 *****************************************************/
static struct proc_dir_entry *g_dtlk_proc_dir;

struct dtlk_dgb_info {
	char *cmd;
	char *description;
	uint32_t flag;
};

PPA_SUBIF g_quick_ref_sub_if_from_vap_id[MAX_DTLK_NUM];


static struct dtlk_dgb_info dtlk_dbg_enable_mask_str[] = {
	{"err",		"error print",		DBG_ERR},
	{"init",	"init print",		DBG_INIT},
	{"rx",		"rx path print",	DBG_RX},
	{"tx",		"tx path print",	DBG_TX},
	{"cpu",		"cpu path print",	DBG_CPU},
	{"proc",	"proc print",		DBG_PROC},
	{"print",	"message print",	DBG_PRINT},
	/* the last one */
	{"all",		"enable all debug",	-1}
};
uint32_t g_dtlk_dbg_enable = DTLK_DBG_ENA;


/*****************************************************
 *	Internal functions
 *****************************************************/
static GSW_API_HANDLE gswr;
static GSW_register_t old_pce_ctrl;
static GSW_register_t old_pce_IGPTRM;

/* Function: gsw_enable_ingress_port_remove
* Purpose: In order to send the forward packet: wlan -> wlan client
* 	We have to enable the ingress feature in switch.
* Argument:
*		portnum : switch port number
* Return: < 0 : error
*/
static int gsw_enable_ingress_port_remove(int portnum)
{
	GSW_register_t regr;
	int result = 0;
	gswr = gsw_api_kopen("/dev/switch_api/1");
	if (gswr == 0) {
		dtlk_debug(DBG_ERR, "%s: Open SWAPI device FAILED !!\n",
			__func__);
		return -EIO;
	}
	dtlk_debug(DBG_INIT, "%s: enable ingress at port [%d]\n",
		__func__, portnum);
	/*PCE Control register*/
	old_pce_ctrl.nRegAddr = (0x483 + (0xA * portnum));
	if (gsw_api_kioctl(gswr, GSW_REGISTER_GET,
		(unsigned int)&old_pce_ctrl) < 0) {
		dtlk_debug(DBG_ERR, "ERROR");
		result = -EIO;
		goto error;
	}
	dtlk_debug(DBG_INIT, "regr.nRegAddr:0x%08x, regr.nData=0x%08x\n",
		old_pce_ctrl.nRegAddr, old_pce_ctrl.nData);
	regr.nData = old_pce_ctrl.nData;
	regr.nRegAddr = (0x483 + (0xA * portnum));
	regr.nData |= (0x4000);
	if (gsw_api_kioctl(gswr, GSW_REGISTER_SET, (unsigned int)&regr) < 0) {
		dtlk_debug(DBG_ERR, "ERROR");
		result = -EIO;
		goto error;
	}
	/*IGPTRM register*/
	regr.nRegAddr = (0x544 + (0x10 * portnum));
	if (gsw_api_kioctl(gswr, GSW_REGISTER_GET,
		(unsigned int)&old_pce_IGPTRM) < 0) {
		dtlk_debug(DBG_ERR, "ERROR");
		result = -EIO;
		goto error;
	}
	dtlk_debug(DBG_INIT, "regr.nRegAddr:0x%08x, regr.nData=0x%08x\n",
		old_pce_IGPTRM.nRegAddr, old_pce_IGPTRM.nData);
	regr.nRegAddr = (0x544 + (0x10 * portnum));
	regr.nData = old_pce_IGPTRM.nData;
	regr.nData |= (0xffff);
	if (gsw_api_kioctl(gswr, GSW_REGISTER_SET, (unsigned int)&regr) < 0) {
		dtlk_debug(DBG_ERR, "ERROR");
		result = -EIO;
		goto error;
	}
error:
	gsw_api_kclose(gswr);
	return result;
}

/* Function: dlrx_init_buf_size
* Purpose: Initilize DLRX FW Buffer
* Argument:
*		dlrx_bufnum : dlrx_bufsize_t
* Return: none
*/
static void dlrx_init_buf_size(
	dlrx_bufsize_t *dlrx_bufnum
	)
{
	/* Initializing the Length of data structure */
	dlrx_bufnum->wlan_desc_num				= WLAN_DESC_NUM;
	dlrx_bufnum->proto_desc_num				= PROTO_DESC_NUM;
	dlrx_bufnum->cpu_ce5_desc_ring_num		= CPU_CE5_DESC_RING_NUM;
	dlrx_bufnum->rx_pkt_buf_rel_msg_num		= RX_PKT_BUF_REL_MSG_NUM;
	dlrx_bufnum->ce5_dest_desc_ring_num		= g_ce5_desc_ring_num;
	dlrx_bufnum->ce5_dest_msg_buf_num		= g_ce5_desc_ring_num;
	dlrx_bufnum->rx_pkt_buf_ptr_ring_num	= g_ce5_buf_ptr_ring_num;
	dlrx_bufnum->rx_reorder_main_num		= RX_REORDER_MAIN_NUM;
	dlrx_bufnum->rx_reorder_desc_link_num	= RX_REORDER_DESC_LINK_NUM;

	return;
}

/** Function: ppa_dl_detect_11ac_card
* Purpose: detect wireless card. Peregrine or Beeliner.
* Argument: none
* Return: card type.
*/
u32 ppa_dl_detect_11ac_card(void)
{
	dtlk_debug(DBG_INIT, "%s:g11ACWirelessCardID[%d] subtype[%d]\n",
		__func__,
		g11ACWirelessCardID,
		g11ACWirelessCardID_SUBTYPE);
	return g11ACWirelessCardID;
}

/** Function: dtlk_dev_from_vapid
* Purpose: Get net device of given VAP.
* Argument: vap_id: VAP id
* Return: dev pointer
* 	NULL: cannot find
*/
struct net_device *dtlk_dev_from_vapid(
	uint32_t vap_id
	)
{
	struct net_device *dev = NULL;
	int i;

	if (vap_id >= MAX_DTLK_NUM)
		dtlk_debug(DBG_ERR,
			"VAP id [%d] is larger than the MAX DTLK NUM [%d]\n",
			vap_id,
			MAX_DTLK_NUM
		);

	spin_lock_bh(&g_ppe_dtlk_spinlock);
	for (i = 0; i < MAX_DTLK_NUM; i++)
		if (g_ppe_radio[0].g_ppe_dtlk_data[i].flags & PPE_DTLK_VALID)
			if (g_ppe_radio[0].g_ppe_dtlk_data[i].vap_id == vap_id)
				dev = (struct net_device *)g_ppe_radio[0].g_ppe_dtlk_data[i].dev;
	spin_unlock_bh(&g_ppe_dtlk_spinlock);

	return dev;
}
EXPORT_SYMBOL(dtlk_dev_from_vapid);

/** Function: wlan_detect_ath_card
* Purpose: detect 11 QCA wireless card.
* Argument: None
* Return : None. The type of card will be saved to global variable named
* g11ACWirelessCardID.
*/
static void wlan_detect_ath_card(void)
{
	int index = 0;
	int ath_dev_id = PCI_ATH_DEV_PEREGRINE;
	int found = 0;
	struct pci_dev *dev_tel = NULL;

	for (index = 0; index < 4; index++) {
		dev_tel = pci_get_subsys(PCI_VENDOR_ATHEROS,
				ath_dev_id,
				PCI_ANY_ID,
				PCI_ANY_ID,
				NULL);
		if (dev_tel)
			found = 1;
		if (found)
			break;
		else {
			switch (ath_dev_id) {
			case PCI_ATH_DEV_PEREGRINE:
				ath_dev_id = PCI_ATH_DEV_BEELINER;
			break;
			case PCI_ATH_DEV_BEELINER:
				ath_dev_id = PCI_ATH_DEV_BEELINER_CASCADE;
				break;
			case PCI_ATH_DEV_BEELINER_CASCADE:
				ath_dev_id = PCI_ATH_DEV_BEELINER_BESRA;
				break;
			default:
				break;
			}
		}
	}
	if (!found)	{
		dtlk_debug(DBG_ERR, "Can not found any Atheros card\n");
		return;
	}
	g11ACWirelessCardID_SUBTYPE = SUBTYPE_NONE_BOARD;
	if (ath_dev_id == PCI_ATH_DEV_PEREGRINE) {
		dtlk_debug(DBG_INIT, "Found PEREGRINE_BOARD card\n");
		g11ACWirelessCardID = PEREGRINE_BOARD;
	} else if (ath_dev_id == PCI_ATH_DEV_BEELINER) {
		dtlk_debug(DBG_INIT, "Found BEELINER_BOARD card\n");
		g11ACWirelessCardID = BEELINER_BOARD;
		/* changed in firmware, using 4 instead of 1 */
	} else if (ath_dev_id == PCI_ATH_DEV_BEELINER_CASCADE) {
		dtlk_debug(DBG_INIT, "Found CASCADE_BOARD card\n");
		g11ACWirelessCardID = BEELINER_BOARD;
		g11ACWirelessCardID_SUBTYPE = SUBTYPE_BEELINER_CASCADE_BOARD;
		/* changed in firmware, using 4 instead of 1 */
	} else if (ath_dev_id == PCI_ATH_DEV_BEELINER_BESRA) {
		dtlk_debug(DBG_INIT, "Found BESRA_BOARD card\n");
		g11ACWirelessCardID = BEELINER_BOARD;
		g11ACWirelessCardID_SUBTYPE = SUBTYPE_BEELINER_CASCADE_BOARD;
		/* changed in firmware, using 4 instead of 1 */
	}
}

/* * Function: dtlk_mem_base_get
 * Purpose: Return the address of DTLK TX and DTLK RX.
 *	  These value should get from MPE HAL
 * Argument:
 *	  dltx_base : uint32_t, contains DTLK TX base.
 *	  dlrx_base : uint32_t, contains DTLK RX base.
 * Return : None
 */
void dtlk_mem_base_get(
	uint32_t *dltx_base,
	uint32_t *dlrx_base
	)
{
	if (dltx_base) {
		/* *dltx_base = NULL; */
		*dltx_base = g_dl_buf_info.tx_cfg_ctxt_buf_base;
		dtlk_debug(DBG_INIT, "DTLK TX base :0x%x\n", *dltx_base);
	}
	if (dlrx_base) {
		/* *dlrx_base = NULL; */
		*dlrx_base = g_dl_buf_info.rx_msgbuf_base;
		dtlk_debug(DBG_INIT, "DTLK RX base :0x%x\n", *dlrx_base);
	}
	return;
}
EXPORT_SYMBOL(dtlk_mem_base_get);

void dtlk_mem_comm_base_get(
	uint32_t *dltx_comm_base
	)
{
	if (dltx_comm_base)
		*dltx_comm_base = g_dl_buf_info.comm_buf_base;

	return;
}
EXPORT_SYMBOL(dtlk_mem_comm_base_get);
void dtlk_get_bank_base(
	uint32_t *dltx_bank_base
	)
{
	if (dltx_bank_base) {
		dma_addr_t phy_addr;
		uint32_t fragment =
			(uint32_t)MPE_TX_ADDR(DLTX_FRAG_DATA_OFFSET);
		phy_addr = dma_map_single(
			g_mpe_dev,
			(void *)fragment,
			4096 * 16 * 4,
			DMA_FROM_DEVICE
		);
		if (unlikely(dma_mapping_error(g_mpe_dev, phy_addr)))
			dtlk_debug(DBG_ERR, "DMA error");

		dtlk_debug(DBG_INIT,
			"%s: vir[0x%x] return[0x%x]\n",
			__func__, fragment, phy_addr);
		*dltx_bank_base = phy_addr;
	}
	return;
}
EXPORT_SYMBOL(dtlk_get_bank_base);

/* * Function: dtlk_mem_base_get
 * Purpose: Return the address of DTLK TX and DTLK RX.
 *	  These value should get from MPE HAL
 * Argument:
 *	  dtlk_ctxt : uint32_t, contains DTLK FW
 * Return : None
 */
void dtlk_mem_sram_base_get(
	uint32_t *dtlk_sram
	)
{
	/* *dtlk_sram = NULL; */
	*dtlk_sram = g_dl_buf_info.rx_cfg_ctxt_buf_base;
}

/* BEELINERTODO */
#define  SIZE_BEELINER_MSDU_ID		1424
#define  SIZE_BEELINER_FRAG_DESC	64
static inline uint32_t __bswap32(
	u_int32_t _x)
{
	return (u_int32_t)(
		(((const u_int8_t *)(&_x))[0]) |
		(((const u_int8_t *)(&_x))[1] << 8) |
		(((const u_int8_t *)(&_x))[2] << 16) |
		(((const u_int8_t *)(&_x))[3] << 24));
}

/** Function: ppa_dl_qca_h2t_ring_init
* Purpose: This function is called QCA driver to initialize H2T Ring buffer
* Argument:
* Return:
*/
#define __CE4SRC_BEELINER_HI			0x4
#define __CE4SRC_MISC_IE_BEELINER_LOW	0xb034

#define __CE4SRC_TARGET_WR_PTR_BEELINER_LOW		0xb03c
#define __CE4SRC_TARGET_RD_PTR_BEELINER_LOW		0xb044

uint32_t ppa_dl_qca_get_peer_map_base(
	uint32_t max_peer,
	uint32_t flags)
{
#if defined(CONFIG_ACCL_11AC_CS2)
	struct _dl_ce4_pflow_control *dl_pflow_control;
	pr_info("%s: Max peer[%d]\n", __func__, max_peer);
	dl_pflow_control =
		(struct _dl_ce4_pflow_control *)MPE_TX_ADDR(DLTX_CFG_CTXT_CE4_PFLOW_CTRL);
	if (max_peer == 0)
		max_peer = 532;
	dl_pflow_control->pflow_max_peer = max_peer;


	return (uint32_t)(MPE_TX_ADDR(DLTX_PEER_MAP_TABLE));
#else
	return 0;
#endif
}
EXPORT_SYMBOL(ppa_dl_qca_get_peer_map_base);

uint32_t ppa_dl_qca_h2t_ring_init(
	uint32_t h2t_ring_size,
	uint32_t entry_size,
	uint32_t src_ring_base,
	uint32_t pcie_base,
	uint32_t flags)
{
	int i;
	char *bufptr;
	uint32_t BADR_TXPB;
	uint32_t BADR_CE4DES;
	uint16_t NUM_CE4DES;
	uint32_t BADR_PCIEMEM;
	uint32_t BADR_HTT_TXDES;
	dltx_cfg_ctxt_ce4buf_t *dltx_cfg_txt;
	dltx_cfg_ctxt_circular_list_t *dltx_cfg_ctxt_circular;
	dltx_circular_list_t *dltx_circular;
	dltx_cfg_ctxt_qca_vap_id_map_t *dltx_cfg_ctxt_qca_vap_id_map;
	dltx_cfg_ctxt_buffer_pointer_table_t *dltx_cfg_ctxt_buffer_pointer_table;
	dltx_cfg_ctxt_ce4_write_index_track_t *dltx_cfg_ctxt_ce4_write_index_track;
	dltx_cfg_ctxt_cpu_ce4des_t *dltx_cfg_ctxt_cpu_ce4des;
	dltx_cfg_ctxt_comm_buff_t *dltx_cfg_ctxt_comm_buff;
	dltx_cfg_ctxt_frag_data_t *dltx_cfg_ctxt_frag_data;
	dltx_cfg_ctxt_tx_msg_t *dltx_cfg_ctxt_tx_msg;
	unsigned char offload_tx_desc_t[] = {
	0X00, 0X42, 0X00, 0X01, /* DW0 */
	0X00, 0X00, 0X00, 0X00, /* DW1 */
	0X07, 0XC0, 0X40, 0X01, /* DW2 */
	0X00, 0X01, 0X05, 0XEA, /* DW3 */
	0X00, 0X00, 0X00, 0X00, /* DW4 byte swap */
	0XFF, 0XFF, 0X00, 0X00 /* DW5 byte swap */
	};

	unsigned char offload_tx_src_ring_desc_t[] = {
	0X00, 0X00, 0X00, 0X00, /* DW0 */
	0X00, 0X04, 0X04, 0X04, /* DW1 */
	/* metadata 14b =1, ByteSwapEN 1b=0, Gather 1b=0,
	* SourceBufferLen 16b=68
	* */
	};

	if ((h2t_ring_size == 0x0) ||
		(entry_size == 0x0) ||
		(src_ring_base == 0x0) ||
		(pcie_base == 0x0))
		return PPA_FAILURE;

	BADR_CE4DES = src_ring_base;

	/* NUM_CE4DES = src_ring_size; */
	NUM_CE4DES = h2t_ring_size;

	dtlk_mem_base_get(&BADR_TXPB, NULL);
	BADR_PCIEMEM = 0xf0000000 | pcie_base;
	/* TODO: GRX500 get TX from HAL layer, need to align with  MPE FW TX */
	/* initialize CE4 List handling */
	dltx_cfg_txt =
		(dltx_cfg_ctxt_ce4buf_t *)MPE_TX_ADDR(DLTX_CFG_CTXT_CE4BUF_OFFSET);
	dltx_cfg_txt->cfg_badr_ce4buf = BADR_CE4DES;
	dltx_cfg_txt->cfg_ce4des_low = LOW_MARK;
	dltx_cfg_txt->cfg_ce4_des_full = HIGH_MARK;
	dltx_cfg_txt->cfg_ce4_read_index_addr =
		BADR_PCIEMEM + (__CE4SRC_BEELINER_HI << 16) +
		__CE4SRC_TARGET_RD_PTR_BEELINER_LOW;
	dltx_cfg_txt->cfg_ce4_write_index_addr =
		BADR_PCIEMEM + (__CE4SRC_BEELINER_HI << 16) +
		__CE4SRC_TARGET_WR_PTR_BEELINER_LOW;
	dltx_cfg_txt->cfg_num_ce4buf = NUM_CE4DES;
	dltx_cfg_txt->load_ce4_read_index_req = 0x0;
	dltx_cfg_txt->local_ce4_read_index = 0x0;
	dltx_cfg_txt->local_ce4_write_index = 0x0;
	dltx_cfg_txt->_dw_res0[0] = BADR_PCIEMEM;

	/* initialize circular list */
	dltx_cfg_ctxt_circular =
		(dltx_cfg_ctxt_circular_list_t *)MPE_TX_ADDR(DLTX_CFG_CTXT_CIRCULAR_LIST_OFFSET);

	dtlk_debug(DBG_INIT, "%s: dltx_cfg_ctxt_circular[%p]\n", __func__,
		(void *)dltx_cfg_ctxt_circular);
	dltx_cfg_ctxt_circular->circular_list_badr =
		(unsigned int)(MPE_TX_ADDR(DLTX_CIRCULAR_LIST_OFFSET));
	dtlk_debug(DBG_INIT,
		"%s: dltx_cfg_ctxt_circular->circular_list_badr[0x%x]\n",
		__func__, dltx_cfg_ctxt_circular->circular_list_badr);

	dltx_cfg_ctxt_circular->circular_list_num = dl_param_tx_descriptor;

	dltx_cfg_ctxt_circular->circular_list_read_index = 0;
	dltx_cfg_ctxt_circular->circular_list_write_index = 0;
	dltx_cfg_ctxt_circular->consumed_pkt_ids = 0;
	dltx_circular =
		(dltx_circular_list_t *)dltx_cfg_ctxt_circular->circular_list_badr;
	dtlk_debug(DBG_INIT, "%s: dltx_circular[%p] %d\n", __func__,
		(void *)dltx_circular,
		dltx_cfg_ctxt_circular->circular_list_num);
	for (i = 0; i < dltx_cfg_ctxt_circular->circular_list_num; i++) {
		dltx_circular->packet_id = i + 1;
		dltx_circular++;
	}

	/* Configure context QCA VAP ID */
	dltx_cfg_ctxt_qca_vap_id_map =
		(dltx_cfg_ctxt_qca_vap_id_map_t *)MPE_TX_ADDR(DLTX_CFG_CTXT_QCA_VAP_ID_MAP_OFFSET);
	dltx_cfg_ctxt_qca_vap_id_map->qca_vap_id_map_badr =
		(unsigned int)MPE_TX_ADDR(DLTX_QCA_VAP_ID_MAP_OFFSET);
	dltx_cfg_ctxt_qca_vap_id_map->qca_vap_id_map_num = MAX_DTLK_NUM;

	/* Buffer pointer */
	dltx_cfg_ctxt_buffer_pointer_table =
		(dltx_cfg_ctxt_buffer_pointer_table_t *)MPE_TX_ADDR(DLTX_CFG_CTXT_BUFFER_POINTER_TABLE_OFFSET);
	dltx_cfg_ctxt_buffer_pointer_table->buffer_pointer_badr =
		(unsigned int)MPE_TX_ADDR(DLTX_BUFFER_POINTER_TABLE_OFFSET);
	dltx_cfg_ctxt_buffer_pointer_table->buffer_pointer_num = NUM_CE4DES;

	/* Write CE4 Write index track */
	dltx_cfg_ctxt_ce4_write_index_track =
		(dltx_cfg_ctxt_ce4_write_index_track_t *)MPE_TX_ADDR(DLTX_CFG_CTXT_CE4_WRITE_INDEX_TRACK_OFFSET);
	dltx_cfg_ctxt_ce4_write_index_track->write_index_track_badr =
		(unsigned int)MPE_TX_ADDR(DLTX_CE4_WRITE_INDEX_TRACK_OFFSET);
	dltx_cfg_ctxt_ce4_write_index_track->write_index_track_num = NUM_CE4DES;

	/* Comm CPU CE4 */
	dltx_cfg_ctxt_cpu_ce4des =
		(dltx_cfg_ctxt_cpu_ce4des_t *)MPE_TX_COML_ADDR(DLTX_CFG_CTXT_CPU_CE4DES_OFFSET);
	dltx_cfg_ctxt_cpu_ce4des->cfg_badr_cpu_ce4 =
		(unsigned int)MPE_TX_COML_ADDR(DLTX_CPU_CE4DES_FORMAT_OFFSET);
	dltx_cfg_ctxt_cpu_ce4des->cfg_num_cpu_ce4 = 64;
	dltx_cfg_ctxt_cpu_ce4des->cpu_ce4_read_index = 0;
	dltx_cfg_ctxt_cpu_ce4des->cpu_ce4_write_index = 0;
	dltx_cfg_ctxt_cpu_ce4des->cpu_ce4_ppe_read_index = 0;
	dltx_cfg_ctxt_cpu_ce4des->cpu_ce4_msg_done = 0;

	/* Comm TX Completion */
	dltx_cfg_ctxt_comm_buff =
		(dltx_cfg_ctxt_comm_buff_t *)MPE_TX_COML_ADDR(DLTX_CFG_CTXT_COMM_BUFF_OFFSET);
	dltx_cfg_ctxt_comm_buff->cfg_badr_tx_cmpl_flag =
		(unsigned int)MPE_TX_COML_ADDR(DLTX_TX_CMPL_FLAG_OFFSET);
	dltx_cfg_ctxt_comm_buff->cfg_badr_tx_cmpl_buf =
		(unsigned int)MPE_TX_COML_ADDR(DLTX_TX_CMPL_MSG_OFFSET);
	dltx_cfg_ctxt_comm_buff->cfg_num_tx_cmpl_buf = MAX_TX_COMP_MAX;

	/* Reset statictisc MIB */
	memset((void *)MPE_TX_ADDR(DLTX_DATA_MIB_OFFSET),
		0x0,
		sizeof(dltx_data_mib_t));
	/* Reset VAP MIB */
	memset((void *)MPE_TX_ADDR(DLTX_VAP_DATA_MIB_OFFSET(0)),
		0x0,
		sizeof(dltx_vap_data_mib_t) * MAX_DTLK_NUM);

	dltx_cfg_ctxt_frag_data =
		(dltx_cfg_ctxt_frag_data_t *)MPE_TX_ADDR(DLTX_CFG_CTXT_FRAG_DATA_OFFSET);
	dltx_cfg_ctxt_frag_data->frag_data_badr =
		(unsigned int)MPE_TX_ADDR(DLTX_FRAG_DATA_OFFSET);
	dltx_cfg_ctxt_frag_data->frag_data_num = 4096;

	dltx_cfg_ctxt_tx_msg =
		(dltx_cfg_ctxt_tx_msg_t *)MPE_TX_ADDR(DLTX_CFG_CTXT_TX_MSG_OFFSET);
	dltx_cfg_ctxt_tx_msg->cfg_size_tx_header = SIZE_TXHEADER;

	/*GRX350: the header for transmit should be intialized by MPE FW TX itself
	* becase packet will be get from CBM, driver does not pre-allocate buffer
	*/

	/* HTT_TXDES defined in PPE spec
	 * 5 HTT_TXDES template. each for one VAP (equal vdev_id ??)
	 * HTT_TXDES has 8 DWORD. DWORD0 is 0x0, DWORD1 DWORD2 DWORD3 DWORD4
	 * SIZE_HTT_TXDES info in DWORD1 DWORD2 DWORD3 DWORD4
	 */
	BADR_HTT_TXDES = (uint32_t)MPE_TX_ADDR(HTT_TX_DES_OFFSET(0));

	for (i = 0; i < NUM_HTT_TXDES; i++) {
		/* 32 or 16 <by default> */
		bufptr = (char *)(BADR_HTT_TXDES + (i * LEN_HTT_TXDES));
		memset(bufptr, 0x0, 4);
		memcpy(bufptr + 4, offload_tx_desc_t, SIZE_HTT_TXDES);
	}
	/* 512 or 4096 */
	for (i = 0; i < NUM_CE4DES; i++) {
		bufptr = (char *)(BADR_CE4DES + (i * SIZE_CE4DES));
		memcpy(bufptr, offload_tx_src_ring_desc_t, SIZE_CE4DES);
	}

	return (uint32_t)BADR_CE4DES;
}
EXPORT_SYMBOL(ppa_dl_qca_h2t_ring_init);
#if defined(CONFIG_ACCL_11AC_CS2)

uint8_t default_dscp_tid_map[WMI_DSCP_MAP_MAX] = {
	0, 0, 0, 0, 0, 0, 0, 0,
	1, 1, 1, 1, 1, 1, 1, 1,
	2, 2, 2, 2, 2, 2, 2, 2,
	3, 3, 3, 3, 3, 3, 3, 3,
	4, 4, 4, 4, 4, 4, 4, 4,
	5, 5, 5, 5, 5, 5, 5, 5,
	6, 6, 6, 6, 6, 6, 6, 6,
	7, 7, 7, 7, 7, 7, 7, 7,
};
#endif
uint32_t ppa_dl_qca_cpu_h2t_ring_init(uint32_t h2t_cpu_msg_ring_size,
	uint32_t entry_size,
	uint32_t flags
#if defined(CONFIG_ACCL_11AC_CS2)
	, uint32_t irq_base
#endif
	)
{
	dma_addr_t phy_addr;
	dltx_cpu_ce4des_format_t *dltx_cpu_ce4des_format;
	dltx_cfg_ctxt_cpu_ce4des_t *dltx_cfg_ctxt_cpu_ce4des;
#if defined(CONFIG_ACCL_11AC_CS2)
	struct _dl_ce5_resource *dl_ce5_resource;
	struct _dl_ce4_pflow_control *dl_pflow_control;
#endif
	dtlk_debug(DBG_INIT, "%s: ringsize[%d] entrysize[%d] irq[%d]\n",
		__func__, h2t_cpu_msg_ring_size, entry_size
#if defined(CONFIG_ACCL_11AC_CS2)
		, irq_base
#else
		, flags
#endif
		);
	if ((h2t_cpu_msg_ring_size == 0x0) || (entry_size == 0x0))
		return PPA_FAILURE;
	if (h2t_cpu_msg_ring_size > 128)
		return PPA_FAILURE;
	dltx_cpu_ce4des_format =
		(dltx_cpu_ce4des_format_t *)MPE_TX_COML_ADDR(DLTX_CPU_CE4DES_FORMAT_OFFSET);

	dltx_cfg_ctxt_cpu_ce4des =
		(dltx_cfg_ctxt_cpu_ce4des_t *)MPE_TX_COML_ADDR(DLTX_CFG_CTXT_CPU_CE4DES_OFFSET);
	dltx_cfg_ctxt_cpu_ce4des->cfg_num_cpu_ce4 = h2t_cpu_msg_ring_size;
	phy_addr = dma_map_single(
		g_mpe_dev,
		(void *)dltx_cpu_ce4des_format,
		128 * 2 * 4,
		DMA_FROM_DEVICE
	);
	if (unlikely(dma_mapping_error(g_mpe_dev, phy_addr)))
		dtlk_debug(DBG_ERR, "%s: DMA error", __func__);
#if defined(CONFIG_ACCL_11AC_CS2)
	dl_ce5_resource =
	(struct _dl_ce5_resource *)(DLRX_CE5_RESOURCES_BASE);
	dl_ce5_resource->dl_msi_irq = (irq_base - 8) + 6;
	dtlk_debug(DBG_INIT, "\tIRQ number: %d",
		dl_ce5_resource->dl_msi_irq);
	/* Init peer flow control */
	dl_pflow_control =
		(struct _dl_ce4_pflow_control *)MPE_TX_ADDR(DLTX_CFG_CTXT_CE4_PFLOW_CTRL);
	dl_pflow_control->pflow_ctrl_mode = dl_param_tx_pflow_mode;
	dl_pflow_control->pflow_msdu_default_ttl =
		DL_MSDU_DEFAULT_TTL;
	dl_pflow_control->pflow_cong_ctrl_timer_interval =
		DL_TX_PFLOW_CTRL_ROT_TIMER_MS;
	dl_pflow_control->pflow_ctl_stats_timer_interval =
		DL_TX_PFLOW_CTRL_STATS_TIMER_MS;
	dl_pflow_control->pflow_ctl_min_threshold =
		DL_TX_PFLOW_CTRL_MIN_THRESHOLD;
	dl_pflow_control->pmap_qdepth_flush_interval =
		DL_TX_PFLOW_CTRL_QDEPTH_FLUSH_INTERVAL;
	dl_pflow_control->pflow_ctl_min_queue_len =
		DL_TX_PFLOW_CTRL_MIN_QUEUE_LEN;
	dl_pflow_control->pflow_ctl_max_queue_len =
		DL_TX_PFLOW_CTRL_MAX_QUEUE_LEN;
	/* setting default dscp table */
	memcpy(
		MPE_TX_ADDR(DLTX_PFLOW_DSCP_TID_TABLE),
		default_dscp_tid_map,
		WMI_DSCP_MAP_MAX
	);
#endif
	dtlk_debug(DBG_INIT, "%s: return 0x%x %p ring_size[%d]\n",
		__func__,
		phy_addr,
		dltx_cpu_ce4des_format,
		h2t_cpu_msg_ring_size);
	return phy_addr;
}
EXPORT_SYMBOL(ppa_dl_qca_cpu_h2t_ring_init);

/** Function: ppa_dl_qca_cpu_h2t_ring_get_write_idx
* Purpose: Get write index of MPE FW TX
* Argument:
*	 flags - unit32_t, not use
* Return: None
*/
int32_t ppa_dl_qca_cpu_h2t_ring_get_write_idx(
	uint32_t flags
	)
{
	dltx_cfg_ctxt_cpu_ce4des_t *dltx_cfg_ctxt_cpu_ce4des
		= (dltx_cfg_ctxt_cpu_ce4des_t *)MPE_TX_COML_ADDR(DLTX_CFG_CTXT_CPU_CE4DES_OFFSET);
	return dltx_cfg_ctxt_cpu_ce4des->cpu_ce4_write_index;
}
EXPORT_SYMBOL(ppa_dl_qca_cpu_h2t_ring_get_write_idx);

/** Function: ppa_dl_qca_cpu_h2t_ring_write_msg
* Purpose: Write message from CPU to MPE FW TX buffer
* Argument:
* Return: Current MPE FW TX write index.
*/
int32_t ppa_dl_qca_cpu_h2t_ring_write_msg(
	uint32_t write_index,
	uint32_t *msg_ptr,
	uint32_t msg_len,
	uint32_t next_write_index,
	uint32_t flags)
{
	dltx_cpu_ce4des_format_t *bufptr;
	struct ce_src_desc *src_desc;
	dltx_cpu_ce4des_format_t *dltx_cpu_ce4des_format;
	dltx_cfg_ctxt_cpu_ce4des_t *dltx_cfg_ctxt_cpu_ce4des =
		(dltx_cfg_ctxt_cpu_ce4des_t *)MPE_TX_COML_ADDR(DLTX_CFG_CTXT_CPU_CE4DES_OFFSET);
	dltx_cpu_ce4des_format =
		(dltx_cpu_ce4des_format_t *)MPE_TX_COML_ADDR(DLTX_CPU_CE4DES_FORMAT_OFFSET);
	if ((msg_ptr == NULL) || (msg_len == 0x0))
		return PPA_FAILURE;
	src_desc = (struct ce_src_desc *)msg_ptr;
	bufptr = dltx_cpu_ce4des_format + write_index;
	dtlk_debug(DBG_CPU,
		"write_index[%d] bufprt[0x%p] msg_len[%d]\n",
		write_index, bufptr, msg_len);
	/* descriptor is 2 DWs */
	memcpy((char *)bufptr, (char *)msg_ptr, msg_len);
	dltx_cfg_ctxt_cpu_ce4des->cpu_ce4_write_index = next_write_index;
	ppa_dl_dre_dma_writeback((unsigned int)bufptr, msg_len);
	ppa_dl_dre_dma_writeback(
		KSEG0 | (0x0fffffff & src_desc->src_ptr),
		src_desc->nbytes);
	return write_index;
}
EXPORT_SYMBOL(ppa_dl_qca_cpu_h2t_ring_write_msg);

struct qca_offload_tx_release_t {
	uint8_t reserved1;
	uint8_t num_msdus;
	uint16_t reserved0;
	uint16_t msdu_ids[129*2];
};

/** Function: ppa_dl_dre_txpkt_buf_release
* Purpose: DLRX FW release buffer to PPE FW after receive
*	 the TX complete message.
* Not use anymore, TX will do it.
*/
int32_t ppa_dl_dre_txpkt_buf_release (
	uint32_t num_msdus,
	uint32_t *msg,
	uint32_t flags
	)
{
	int i;
	struct qca_offload_tx_release_t *offload_tx;
	dltx_tx_cmpl_msg_t *dltx_tx_cmpl_msg;
	dltx_tx_cmpl_flag_t *dltx_tx_cmpl_flag;
	/* sanity check */
	if (msg == NULL || !num_msdus) {
		dtlk_debug(DBG_ERR,
			"--Invalid argument for releasing [0x%p] [%d]--\n",
			msg, num_msdus);
		return PPA_FAILURE;
	}
	if (num_msdus > 64) {
		dtlk_debug(DBG_ERR,
			"--Number of msdus is too big [0x%p] msdus[%d]--\n",
			msg, num_msdus);
		num_msdus = 64;
	}
	/* find free slot */
	offload_tx = (struct qca_offload_tx_release_t *)msg;
	/* sanity check */
	if (offload_tx == NULL)
		return PPA_FAILURE;

	dltx_tx_cmpl_flag =
		(dltx_tx_cmpl_flag_t *)(MPE_TX_COML_ADDR(DLTX_TX_CMPL_FLAG_OFFSET));
	dltx_tx_cmpl_msg =
		(dltx_tx_cmpl_msg_t *)(MPE_TX_COML_ADDR(DLTX_TX_CMPL_MSG_OFFSET));
	if (num_msdus) {
		int current_write_index;
		int old_write_index;
		int numberOfFree = 0;
		int previous_release = 0;
		dltx_cfg_ctxt_circular_list_t *dltx_cfg_ctxt_circular_list
			= (dltx_cfg_ctxt_circular_list_t *)MPE_TX_ADDR(DLTX_CFG_CTXT_CIRCULAR_LIST_LINUX_OFFSET);
		dltx_circular_list_t *dltx_circular_list
			= (dltx_circular_list_t *)MPE_TX_ADDR(DLTX_CIRCULAR_LIST_OFFSET);
		struct qca_offload_tx_release_t *qca_tx_completion;
		dltx_buffer_pointer_table_t *tx_pointer_table =
			(dltx_buffer_pointer_table_t *)MPE_TX_ADDR(DLTX_BUFFER_POINTER_TABLE_OFFSET);
		current_write_index = dltx_cfg_ctxt_circular_list->circular_list_write_index;
		old_write_index = current_write_index;
		previous_release = dltx_cfg_ctxt_circular_list->_dw_res0[0];
		qca_tx_completion = (struct qca_offload_tx_release_t *)msg;

		for (i = 0; i < num_msdus; i++) {
			dltx_buffer_pointer_table_t *tx_pointer_table_temp = NULL;
			dltx_circular_list_t *dltx_circular_list_temp = NULL;
			int tx_id = 0;
			if ((i % 2) == 0)
				tx_id = qca_tx_completion->msdu_ids[i+1];
			else
				tx_id = qca_tx_completion->msdu_ids[i-1];
			/*get buffer pointer*/
			tx_pointer_table_temp = tx_pointer_table;
			tx_pointer_table_temp += (tx_id - 1);
			tx_pointer_table_temp =
				(dltx_buffer_pointer_table_t *)(tx_pointer_table_temp);

			if (tx_pointer_table_temp->pointer_address) {
				/*free buffer first*/
				if (cbm_buffer_free(
					smp_processor_id(),
					tx_pointer_table_temp->pointer_address,
					0) == -1)
					dtlk_debug(DBG_ERR,
						"CMB Pointer: [0x%08x] at id[%d] failed!Num[%d]\n",
						tx_pointer_table_temp->pointer_address,
						tx_id,
						num_msdus);

				/*update free packet index to circular list*/
				dltx_circular_list_temp = dltx_circular_list;
				dltx_circular_list_temp += current_write_index;
				dltx_circular_list_temp =
					(dltx_circular_list_t *)(dltx_circular_list_temp);

				dltx_circular_list_temp->packet_id = tx_id;
				dltx_circular_list_temp =
					(dltx_circular_list_t *)CACHE_ADDR(dltx_circular_list_temp);
				dltx_circular_list_temp->packet_id = tx_id;
				/*update write index*/
				current_write_index++;
				if (current_write_index >= dl_param_tx_descriptor)
					current_write_index = 0;
				/*update consume index*/
				numberOfFree++;
			} else
				dtlk_debug(DBG_ERR,
					"%s: NULL at [%d] num_msdus[%d]\n",
					__func__, tx_id, num_msdus);
		}
		if (dltx_cfg_ctxt_circular_list->_dw_res0[1]
			> previous_release)
			dtlk_debug(DBG_ERR,
				"%s: %x %x %x MEMORY CORRUPTION\n",
				__func__,
				previous_release,
				dltx_cfg_ctxt_circular_list->_dw_res0[1],
				numberOfFree);
		dltx_cfg_ctxt_circular_list->_dw_res0[1] =
			previous_release;
		dltx_cfg_ctxt_circular_list->_dw_res0[2] =
			numberOfFree;
		dltx_cfg_ctxt_circular_list->_dw_res0[0] =
			previous_release + numberOfFree;
		dltx_cfg_ctxt_circular_list->circular_list_write_index =
			current_write_index;
	}
	return PPA_SUCCESS;
}
EXPORT_SYMBOL(ppa_dl_dre_txpkt_buf_release);


/** Function: ppa_dl_qca_get_vap_stats
* Purpose: Get the VAP status
* Argument:
* Return: PPA_FAILURE or PPA_SUCCESS
*/
uint32_t ppa_dl_qca_get_vap_stats(
	uint32_t vapId,
	PPA_WLAN_VAP_Stats_t *vap_stats,
	uint32_t flags
	)
{
	/* TODO : should get from DRLX buffer */
	dtlk_debug(DBG_CPU, "%s: vapId[%d] [%p]\n", __func__, vapId, ddr_base);
	if ((vap_stats == NULL)
		|| (vapId > MAX_VAPID)
		) {
		dtlk_debug(DBG_ERR, "Invalid vap_id[%d]\n", vapId);
		return PPA_FAILURE;
	} else {
		dltx_vap_data_mib_t *vap_mib_tx =
				(dltx_vap_data_mib_t *)MPE_TX_ADDR(DLTX_VAP_DATA_MIB_OFFSET(vapId));

		volatile vap_data_mib_t *vap_mib_rx =
				(vap_data_mib_t *)DLRX_VAP_MIB_BASE(vapId);
		uint64_t rxpdu = (uint64_t)vap_mib_rx->rx_rcv_pdu_low +
			(((uint64_t)vap_mib_rx->rx_rcv_pdu_high) << 32);
		uint64_t rxbytes = (uint64_t)vap_mib_rx->rx_rcv_bytes_low +
			(((uint64_t)vap_mib_rx->rx_rcv_bytes_high) << 32);

		uint64_t txpdu = (uint64_t)vap_mib_tx->txpdu_low +
			(((uint64_t)vap_mib_tx->txpdu_high) << 32);
		uint64_t txbytes = (uint64_t)vap_mib_tx->txbytes_low +
			(((uint64_t)vap_mib_tx->txbytes_high) << 32);
		vap_stats->txdrop = vap_mib_tx->txdrop_low;
		dtlk_debug(DBG_CPU, "%s: RX [%llu]\n", __func__, rxbytes);
		/* get tx vap mib */
		vap_stats->txpdu = txpdu;
		vap_stats->txbytes = txbytes;
		/* get rx vap mib */
		vap_stats->rx_rcv_pdu = rxpdu;
		vap_stats->rx_rcv_bytes = rxbytes;
		vap_stats->rx_discard_pdu = vap_mib_rx->rx_discard_pdu_low;
		vap_stats->rx_discard_bytes = vap_mib_rx->rx_discard_bytes_low;
		vap_stats->rx_fwd_pdu = vap_mib_rx->rx_fwd_pdu_low;
		vap_stats->rx_fwd_bytes = vap_mib_rx->rx_fwd_bytes_low;
		vap_stats->rx_inspect_pdu = vap_mib_rx->rx_inspect_pdu_low;
		vap_stats->rx_inspect_bytes = vap_mib_rx->rx_inspect_bytes_low;
		vap_stats->rx_pn_pdu = vap_mib_rx->rx_pn_pdu_low;
		vap_stats->rx_pn_bytes = vap_mib_rx->rx_pn_bytes_low;
		vap_stats->rx_drop_pdu = vap_mib_rx->rx_drop_pdu_low;
		vap_stats->rx_drop_bytes = vap_mib_rx->rx_drop_bytes_low;

		dtlk_debug(DBG_CPU, "%s: vapId[%d] data returned:\n",
			__func__,
			vapId);
		dtlk_debug(DBG_CPU, "RX[%llu] TX[%llu]\n",
			vap_stats->rx_rcv_bytes,
			vap_stats->txbytes);


		return PPA_SUCCESS;
	}
	return PPA_FAILURE;
}
EXPORT_SYMBOL(ppa_dl_qca_get_vap_stats);
/** Funtion: dtlk_id_from_subif
* Purpose: Get
*/
int dtlk_get_radio_id_from_subif(
	PPA_SUBIF *sub_if
	)
{
	int i;
	/* sanity check */
	if (!sub_if)
		return -1;
	for (i = 0; i < MAX_RADIO_NUM; i++) {
		if ((g_ppe_radio[i].flags & PPE_DTLK_VALID)
				&& (g_ppe_radio[i].dl_sub_if.port_id ==
					sub_if->port_id))
				return i;
	}
	dtlk_debug(DBG_ERR, "Cannot find sub_if->port_id[%d] in\n",
		sub_if->port_id);
	dtlk_debug(DBG_ERR, "\tradio[%d]\n",
		g_ppe_radio[0].dl_sub_if.port_id);
	return -1;
}

unsigned int ppa_dl_dre_get_sram_addr(void)
{
	return (unsigned int)cfg_ctxt_base;
}
EXPORT_SYMBOL(ppa_dl_dre_get_sram_addr);

unsigned int ppa_dl_dre_get_kseg0(void)
{
	return KSEG0;
}
EXPORT_SYMBOL(ppa_dl_dre_get_kseg0);

unsigned int ppa_dl_dre_get_kseg1(void)
{
	return KSEG1;
}
EXPORT_SYMBOL(ppa_dl_dre_get_kseg1);


void ppa_dl_dre_dma_invalidate(
	unsigned int startAddr,
	unsigned int size
	)
{
	dma_addr_t phy_addr;
	if (!startAddr) {
		dtlk_debug(DBG_ERR, "%s: rxpb_ptr is NULL\n", __func__);
		return ;
	}
	if (g_mpe_dev) {
		phy_addr = dma_map_single(g_mpe_dev,
			(void *)startAddr,
			size,
			DMA_FROM_DEVICE
			);
		/*
		dtlk_debug(DBG_RX, "%s:phy 0x%x\n", __func__, phy_addr); */
		if (unlikely(dma_mapping_error(g_mpe_dev, phy_addr))) {
			dtlk_debug(DBG_ERR,
				"ERROR:[0x%x] size: %d, dir: %d\n",
				(u32)startAddr, size, DMA_FROM_DEVICE);
			BUG();
		}
	}
}
EXPORT_SYMBOL(ppa_dl_dre_dma_invalidate);

inline void ppa_dl_dre_dma_writeback(
	unsigned int startAddr,
	unsigned int size
	)
{
	dma_addr_t phy_addr;
	if (startAddr < KSEG0) {
		startAddr = KSEG1ADDR(startAddr);
	}

	if (!startAddr) {
		dtlk_debug(DBG_ERR, "%s: rxpb_ptr is NULL\n", __func__);
		return ;
	}
	if (g_mpe_dev) {
		phy_addr = dma_map_single(g_mpe_dev,
			(void *)startAddr,
			size,
			DMA_TO_DEVICE
			);
		/* dtlk_debug(DBG_RX, "%s:phy 0x%x\n", __func__, phy_addr); */
		if (unlikely(dma_mapping_error(g_mpe_dev, phy_addr))) {
			dtlk_debug(DBG_ERR,
			"ERROR: buf[0x%x] size: %d dir: %d\n",
			startAddr, size, DMA_FROM_DEVICE);
			BUG();
		}
	}
}
EXPORT_SYMBOL(ppa_dl_dre_dma_writeback);


inline void ppa_dl_dre_dma_wback_inv(
	unsigned int startAddr,
	unsigned int size
	)
{
	dma_addr_t phy_addr;
	if (startAddr < KSEG0) {
		startAddr = KSEG1ADDR(startAddr);
	}
	if (!startAddr) {
		dtlk_debug(DBG_ERR, "%s: rxpb_ptr is NULL\n", __func__);
		return ;
	}
	if (g_mpe_dev) {
		phy_addr = dma_map_single(g_mpe_dev,
			(void *)startAddr,
			size,
			DMA_TO_DEVICE
			);
		/* dtlk_debug(DBG_RX, "%s:phy 0x%x\n", __func__, phy_addr); */
		if (unlikely(dma_mapping_error(g_mpe_dev, phy_addr))) {
			dtlk_debug(DBG_ERR,
				"error: [0x%x] size: %d dir: %d\n",
			startAddr, size, DMA_FROM_DEVICE);
			BUG();
		}
	}
}
EXPORT_SYMBOL(ppa_dl_dre_dma_wback_inv);


/** Funtion: dtlk_id_from_subif
* Purpose: Get
*/
int dtlk_get_id_from_subif(
	PPA_SUBIF *sub_if
	)
{
	int i;
	int radio;
	struct ppe_radio_map ppe;
	/* sanity check */
	if (!sub_if)
		return -1;
	radio = dtlk_get_radio_id_from_subif(sub_if);
	if (radio < 0 || radio >= MAX_RADIO_NUM) {
		dtlk_debug(DBG_ERR, "%s:invalid id! if_id: %d",
			__func__,
			radio);
		return -1;
	}
	ppe = g_ppe_radio[radio];
	for (i = 0; i < MAX_DTLK_NUM; i++)
		if ((ppe.g_ppe_dtlk_data[i].flags & PPE_DTLK_VALID)
			&& (ppe.g_ppe_dtlk_data[i].dl_sub_if.port_id
			== sub_if->port_id)
			&& (ppe.g_ppe_dtlk_data[i].dl_sub_if.subif
			== sub_if->subif))
			return i;

	return -1;
}
inline int dtlk_get_subif_from_vap_id(
	PPA_SUBIF *sub_if, int vap_id
	)
{
	int radio;
	/* sanity check */
	if (!sub_if)
		return -1;
	radio = dtlk_get_radio_id_from_subif(sub_if);
	if (radio < 0 || radio >= MAX_RADIO_NUM) {
		dtlk_debug(DBG_ERR, "invalid radio: %d", radio);
		return -1;
	}
	if (vap_id < 0 || vap_id >= MAX_DTLK_NUM) {
		dtlk_debug(DBG_ERR, "Invalid VAP ID %d\n", vap_id);
		return -1;
	}
	/*
	dtlk_debug(DBG_INIT, "%s: vap_id[%d] port[%d] subif[%d]\n",
		__func__,
		vap_id,
		g_quick_ref_sub_if_from_vap_id[vap_id].port_id,
		g_quick_ref_sub_if_from_vap_id[vap_id].subif
		); */
	sub_if->port_id = g_quick_ref_sub_if_from_vap_id[vap_id].port_id;
	sub_if->subif = g_quick_ref_sub_if_from_vap_id[vap_id].subif;
	return 0;
}

/** Function: dltk_remove_quickrefsub
* Purpose: remove sub interface entry in quick reference sub interface table
* Argument: sub interface
* Return: none. The entry in
*/
void dltk_remove_quickrefsub(PPA_SUBIF *sub_if)
{
	int i = 0;
	for (i = 0; i < MAX_DTLK_NUM; i++) {
		if (g_quick_ref_sub_if_from_vap_id[i].port_id == sub_if->port_id &&
			g_quick_ref_sub_if_from_vap_id[i].subif == sub_if->subif) {
			g_quick_ref_sub_if_from_vap_id[i].port_id = -1;
			g_quick_ref_sub_if_from_vap_id[i].subif = -1;
		}
	}
}

/** Function: dltk_update_radio
* Purpose: update radio to datapath port(aka EP, aka port_id, aka pmac)
*
*/
void dltk_update_radio_datapath_port(
	unsigned radio_id,
	unsigned vap_id,
	PPA_SUBIF *subif,
	unsigned int flag
	)
{
	uint32_t *dltx_ep_radio_id
		= (uint32_t *)g_dl_drv_address.dl_ep_2radio_addr;
	dltx_qca_vap_id_map_t *dltx_qca_vap_id_map
		= (dltx_qca_vap_id_map_t *)MPE_TX_ADDR(DLTX_QCA_VAP_ID_MAP_OFFSET);
	dltx_ep_radio_id = dltx_ep_radio_id + subif->port_id;

	dtlk_debug(DBG_INIT,
		"%s: radio_id[%d] vap[%d] port[%d] subif[%d]\n",
		__func__, radio_id, vap_id, subif->port_id, subif->subif);
	/* update subif to vap_id mapping */
	dltx_qca_vap_id_map = dltx_qca_vap_id_map +
		subif->subif;
	/* update port id */
	if (flag & PPE_F_DTLK_DP_REGISTER) {
		dtlk_debug(DBG_INIT, "%s: register\n", __func__);
		*(dltx_ep_radio_id + radio_id) = radio_id;
		dltx_qca_vap_id_map->qca_vap_id = vap_id;
	} else {
		dtlk_debug(DBG_INIT, "%s: deregister\n", __func__);
		*(dltx_ep_radio_id + radio_id) = 0;
		dltx_qca_vap_id_map->qca_vap_id = 0;
	}
}


#if defined(CONFIG_LANTIQ_MCAST_HELPER_MODULE) || defined(CONFIG_LANTIQ_MCAST_HELPER)
typedef void (*Mcast_module_callback_t)(unsigned int grpidx,
	struct net_device *netdev,
	void *mc_stream,
	unsigned int flag
	);

#endif
#if defined(CONFIG_ACCL_11AC_CS2)
static unsigned int dl_tx_get_peer_id_from_peer_idx(uint32_t peer_index)
{
	unsigned int *dl_tx_fw_peer_map_tbl =
		(unsigned int *)MPE_TX_ADDR(DLTX_CE5_PEER_MAP_TO_PEER_ID);
	dl_tx_fw_peer_map_tbl += peer_index;
	return *dl_tx_fw_peer_map_tbl;
}
#endif
int dl_m2c_add_peer(
	uint32_t *mac_addr,
	uint16_t peer_id,
	uint16_t vap_id,
	uint16_t extension
	)
{
	char *temp, *tempDL;
	struct _dl_peer_mac_mapping_table *dl_m2c_table;
	if (extension == 0)
		dl_m2c_table =
			(struct _dl_peer_mac_mapping_table *)MPE_TX_ADDR(DLTX_CFG_CTXT_M2C_PEER_TABLE);
	else if (extension == 1)
		dl_m2c_table =
			(struct _dl_peer_mac_mapping_table *)MPE_TX_ADDR(DLTX_CFG_CTXT_M2C_PEER_EXT_TABLE);
	else
		dl_m2c_table =
#if defined(CONFIG_ACCL_11AC_CS2)
		(struct _dl_peer_mac_mapping_table *)MPE_TX_ADDR(DLTX_WDS_CLIENT_PEER_TABLE);
#else
		(struct _dl_peer_mac_mapping_table *)MPE_TX_ADDR(DLTX_CFG_CTXT_M2C_PEER_EXT_TABLE);
#endif
	dtlk_debug(DBG_INIT,
		"======ADD: %d %d [%02x:%02x:%02x:%02x:%02x:%02x]\n",
		peer_id, vap_id,
		*((uint8_t *)mac_addr),
		*((uint8_t *)mac_addr + 1),
		*((uint8_t *)mac_addr + 2),
		*((uint8_t *)mac_addr + 3),
		*((uint8_t *)mac_addr + 4),
		*((uint8_t *)mac_addr + 5)
		);
	if (peer_id >= MAX_PEER_NUM) {
		dtlk_debug(DBG_ERR, "peer id is out of range %d\n", peer_id);
		return DTLK_FAILURE;
	}
	if (mac_addr) {
		int tmp_peer_idx = -1;
		tmp_peer_idx = dl_m2c_find_peer((char *)mac_addr, extension, 0);
		/* check for existing entry */
		if (tmp_peer_idx > -1) {
			dtlk_debug(DBG_ERR, "Peer %d is in system\n", peer_id);
			/* remove */
#if defined(CONFIG_ACCL_11AC_CS2)
			dl_m2c_remove_peer(mac_addr,
				dl_tx_get_peer_id_from_peer_idx(tmp_peer_idx),
				0,
				extension
			);
#endif
		}
		if (extension == 0) {
			spin_lock_bh(&g_ppe_dtlk_spinlock);
			dl_m2c_table = (dl_m2c_table + peer_id);
			temp = (char *)(mac_addr);
			tempDL = (char *)dl_m2c_table + 2;
			memcpy((char *)tempDL, temp, 6);
			dl_m2c_table->valid = 1;
			dl_m2c_table->res = peer_id;
			dl_m2c_table->vap_id = vap_id;
			spin_unlock_bh(&g_ppe_dtlk_spinlock);
			return DTLK_SUCCESS;
		} else {
			/* find free slot -> peer id */
			int free_peer_id = 0;
			struct _dl_peer_mac_mapping_table *dl_m2c_table_temp;
			int max_peer;
			if (extension == 1)
				max_peer = MAX_PEER_NUM;
			else
				max_peer = MAX_WDS_PEER_NUM;
			while (free_peer_id < max_peer) {
				dl_m2c_table_temp = (dl_m2c_table + free_peer_id);
				if (dl_m2c_table_temp->valid == 0) {
					dtlk_debug(DBG_ERR, "\tAdding [%d] to [%d]\n", tmp_peer_idx, free_peer_id);
					spin_lock_bh(&g_ppe_dtlk_spinlock);
					temp = (char *)(mac_addr);
					tempDL = (char *)dl_m2c_table_temp + 2;
					memcpy((char *)tempDL, temp, 6);
					dl_m2c_table_temp->valid = 1;
					dl_m2c_table_temp->vap_id = vap_id;
					dl_m2c_table_temp->res = peer_id;
					spin_unlock_bh(&g_ppe_dtlk_spinlock);
					return free_peer_id;
				}
				free_peer_id++;
			}
		}
	}
	dtlk_debug(DBG_ERR, "Invalid data %d\n", peer_id);
	return DTLK_FAILURE;
}


int dl_m2c_remove_peer(
	uint32_t *mac_addr,
	uint16_t peer_id,
	uint16_t vap_id,
	uint16_t extension
	)
{
	struct _dl_peer_mac_mapping_table *dl_m2c_table;
	int peer_idx = 0;
	unsigned int b_get_wds_index = 0;
	if (extension == 0)
		dl_m2c_table =
			(struct _dl_peer_mac_mapping_table *)MPE_TX_ADDR(DLTX_CFG_CTXT_M2C_PEER_TABLE);
	else if (extension == 1)
		dl_m2c_table =
			(struct _dl_peer_mac_mapping_table *)MPE_TX_ADDR(DLTX_CFG_CTXT_M2C_PEER_EXT_TABLE);
	else {
		dl_m2c_table =
#if defined(CONFIG_ACCL_11AC_CS2)
			(struct _dl_peer_mac_mapping_table *)MPE_TX_ADDR(DLTX_WDS_CLIENT_PEER_TABLE);
		b_get_wds_index = 1;
#else
			(struct _dl_peer_mac_mapping_table *)MPE_TX_ADDR(DLTX_CFG_CTXT_M2C_PEER_EXT_TABLE);
		b_get_wds_index = 0;
#endif
	}

	peer_idx = dl_m2c_find_peer((unsigned char *)mac_addr, extension, b_get_wds_index);
	dtlk_debug(DBG_INIT,
		"======REMOVE: %d %d [%02x:%02x:%02x:%02x:%02x:%02x] from[%d]idx[%d]\n",
		peer_id, vap_id,
		*((uint8_t *)mac_addr),
		*((uint8_t *)mac_addr + 1),
		*((uint8_t *)mac_addr + 2),
		*((uint8_t *)mac_addr + 3),
		*((uint8_t *)mac_addr + 4),
		*((uint8_t *)mac_addr + 5),
		extension,
		peer_idx
		);
	if (peer_idx > -1) {
		dl_m2c_table = (dl_m2c_table + peer_idx);
		if (peer_idx != peer_id)
			dtlk_debug(DBG_ERR, "REMOVE peer index[%d]#id[%d]\n",
				peer_idx,
				peer_id);
	} else {
		dtlk_debug(DBG_ERR, "Can not find peer id\n");
		return DTLK_FAILURE;
	}
	spin_lock_bh(&g_ppe_dtlk_spinlock);
	if (dl_m2c_table->valid) {
		dl_m2c_table->valid = 0;
		spin_unlock_bh(&g_ppe_dtlk_spinlock);
		return DTLK_SUCCESS;
	} else
		dtlk_debug(DBG_ERR, "Peer is not valid %d\n", peer_id);
	spin_unlock_bh(&g_ppe_dtlk_spinlock);
	return DTLK_FAILURE;
}

int dl_m2c_find_peer(
	unsigned char *peer_mac,
	unsigned int extension,
	unsigned int b_get_wds_index
	)
{
	dtlk_debug(DBG_INIT, "Arguments: 0x%p ext[%d] b[%d]\n",
				peer_mac,
				extension,
				b_get_wds_index
				);
	if (peer_mac) {
		struct _dl_peer_mac_mapping_table *dl_m2c_table;
		int i = 0;
		uint32_t max_peer;
		char *temp = NULL;
		dtlk_debug(DBG_INIT, "MAC - %x:%x:%x:%x:%x:%x\n",
			*peer_mac,
			*(peer_mac + 1),
			*(peer_mac + 2),
			*(peer_mac + 3),
			*(peer_mac + 4),
			*(peer_mac + 5)
			);
		if (extension == 0)
			dl_m2c_table =
				(struct _dl_peer_mac_mapping_table *)MPE_TX_ADDR(DLTX_CFG_CTXT_M2C_PEER_TABLE);
		else if (extension == 1)
			dl_m2c_table =
				(struct _dl_peer_mac_mapping_table *)MPE_TX_ADDR(DLTX_CFG_CTXT_M2C_PEER_EXT_TABLE);
		else
			dl_m2c_table =
#if defined(CONFIG_ACCL_11AC_CS2)
			(struct _dl_peer_mac_mapping_table *)MPE_TX_ADDR(DLTX_WDS_CLIENT_PEER_TABLE);
#else
			(struct _dl_peer_mac_mapping_table *)MPE_TX_ADDR(DLTX_CFG_CTXT_M2C_PEER_EXT_TABLE);
#endif
		if (extension == 2)
			max_peer = MAX_WDS_PEER_NUM;
		else
			max_peer = MAX_PEER_NUM;
		for (i = 0; i < max_peer; i++) {
			if (dl_m2c_table->valid) {
				temp = (char *)dl_m2c_table + 2;
				if (!memcmp(peer_mac, temp, 6)) {
					/* return peer id */
					if (extension != 2)
						return i;
					else {
						if (b_get_wds_index)
							return i;
						else
							return dl_m2c_table->res;
					}
				}
			}
			dl_m2c_table++;
		}
		dtlk_debug(DBG_ERR,
			"Can not find peer in %s table for %x:%x:%x:%x:%x:%x\n",
			extension == 0 ? "main" : "extension",
			*peer_mac,
			*(peer_mac + 1),
			*(peer_mac + 2),
			*(peer_mac + 3),
			*(peer_mac + 4),
			*(peer_mac + 5)
			);
	} else
		dtlk_debug(DBG_ERR, "Invalid peer MAC\n");

	return -1;
}
void dl_dp_mcast_group_modify_bitmap(
	unsigned int grpidx,
	unsigned int peer_id,
	unsigned int b_set,
	unsigned int extension
	)
{
	dtlk_debug(DBG_INIT,
		"%s: Start 1 grpidx[%d] peer_id[%d] b_set[%d]\n",
		__func__, grpidx, peer_id, b_set);
	if (grpidx < MAX_MCAST_GROUP &&
		peer_id < MAX_PEER_NUM) {
		int dword_offset = peer_id / 32;
		int bitmap_offset = peer_id % 32;
		struct _dl_mcast_group_table *dl_mcast_group_table;
		if (extension == 0)
			dl_mcast_group_table =
				(struct _dl_mcast_group_table *)MPE_TX_ADDR(DLTX_CFG_CTXT_M2C_GROUP_TABLE);
		else
			dl_mcast_group_table =
				(struct _dl_mcast_group_table *)MPE_TX_ADDR(DLTX_CFG_CTXT_M2C_GROUP_EXT_TABLE);
		dl_mcast_group_table += grpidx;
		if (b_set) {
			if ((dl_mcast_group_table->bitmap[dword_offset]
				& (1 << bitmap_offset)) == 0) {
				dl_mcast_group_table->bitmap[dword_offset] =
					dl_mcast_group_table->bitmap[dword_offset]
					| (1 << bitmap_offset);
				dl_mcast_group_table->grpIdx++;
				dl_mcast_group_table->valid = 1;
			} else
				dtlk_debug(DBG_INIT,
					"%s:peer id[%d] is already in group[%d]\n",
					__func__, peer_id, grpidx);
		} else {
			dl_mcast_group_table->bitmap[dword_offset] =
				dl_mcast_group_table->bitmap[dword_offset]
				& (~(1 << bitmap_offset));
			if (dl_mcast_group_table->grpIdx > 0)
				dl_mcast_group_table->grpIdx--;
			if (dl_mcast_group_table->grpIdx == 0)
				dl_mcast_group_table->valid = 0;
		}
	} else
		dtlk_debug(DBG_ERR,
			"Invalid group index %d peer [%d]\n",
			grpidx, peer_id);
	return;
}

int dl_dp_mcast_join(
	unsigned int grpidx,
	unsigned int peer_id,
	unsigned int bJoin,
	unsigned int extension
	)
{
	dtlk_debug(DBG_INIT,
		"%s: Start grpidx[%d] peer_id[%d] bJoin[%d]\n",
		__func__, grpidx, peer_id, bJoin);
	if (grpidx < MAX_MCAST_GROUP) {
		struct _dl_mcast_group_table *dl_mcast_group_table;
		if (extension == 0)
			dl_mcast_group_table =
				(struct _dl_mcast_group_table *)MPE_TX_ADDR(DLTX_CFG_CTXT_M2C_GROUP_TABLE);
		else
			dl_mcast_group_table =
				(struct _dl_mcast_group_table *)MPE_TX_ADDR(DLTX_CFG_CTXT_M2C_GROUP_EXT_TABLE);
		dl_mcast_group_table += grpidx;
		if (bJoin) {
			dl_mcast_group_table->valid = 1;
			dl_dp_mcast_group_modify_bitmap(
				grpidx, peer_id, 1, extension);
		} else
			dl_dp_mcast_group_modify_bitmap(
				grpidx, peer_id, 0, extension);
	} else
		dtlk_debug(DBG_ERR, "Invalid group index %d\n", grpidx);
	return -1;
}
static INLINE int stricmp(
	const char *p1,
	const char *p2
	)
{
	int c1, c2;

	while (*p1 && *p2) {
		c1 = *p1 >= 'A' && *p1 <= 'Z' ? *p1 + 'a' - 'A' : *p1;
		c2 = *p2 >= 'A' && *p2 <= 'Z' ? *p2 + 'a' - 'A' : *p2;
		c1 -= c2;
		if (c1)
			return c1;
		p1++;
		p2++;
	}

	return *p1 - *p2;
}
/** Function: dtlk_dev_from_vapid
* Purpose: Get net device of given VAP.
* Argument dev
*/
int dtlk_vapid_from_dev(
		struct net_device *dev
	)
{
	int i;

	if (!dev) {
		dtlk_debug(DBG_ERR, "%s: invalid dev\n",
				__func__
				);
		return -1;
	}
	pr_info("%s: dev [%s]\n", __func__, dev->name);
	for (i = 0; i < MAX_DTLK_NUM; i++)
		if (g_ppe_radio[0].g_ppe_dtlk_data[i].flags & PPE_DTLK_VALID) {
			PPA_NETIF *tempDev =
				(PPA_NETIF *)(g_ppe_radio[0].g_ppe_dtlk_data[i].dev);
			if (tempDev) {
				pr_info("\t[%d]:[%s]\n", i, tempDev->name);
				if (stricmp(tempDev->name,
					dev->name) == 0)
					return g_ppe_radio[0].g_ppe_dtlk_data[i].vap_id;
			}
	   }

	return -1;
}
void dl_dp_mcast_cb(unsigned int grpidx,
	struct net_device *netdev,
	void *mc,
	unsigned int flag
	)
{
	int peer_id;
	dtlk_debug(DBG_INIT,
		"%s: Start grpidx[%d] netdev[%s] flag[%d]\n",
		__func__, grpidx, netdev->name, flag);
	if (mc) {
		mcast_stream_t *mc_stream = (mcast_stream_t *)mc;
		if (mc_stream->rx_dev && mc_stream->rx_dev->name)
			dtlk_debug(DBG_INIT, "\tdev[%s]\n",
			mc_stream->rx_dev->name);
		dtlk_debug(DBG_INIT,
			"\tDest:[%x][%x][%x][%x][%x][%x]\n",
			mc_stream->macaddr[0],
			mc_stream->macaddr[1],
			mc_stream->macaddr[2],
			mc_stream->macaddr[3],
			mc_stream->macaddr[4],
			mc_stream->macaddr[5]
			);
		dtlk_debug(DBG_INIT,
			"\tSrc[%x][%x][%x][%x][%x][%x]\n",
			mc_stream->src_mac[0],
			mc_stream->src_mac[1],
			mc_stream->src_mac[2],
			mc_stream->src_mac[3],
			mc_stream->src_mac[4],
			mc_stream->src_mac[5]
			);
		peer_id = dl_m2c_find_peer(mc_stream->macaddr,
			DRE_DIRECT_CLIENT_TABLE,
			0
		);
		switch (flag) {
		case 1:
			if (peer_id != -1)
				dl_dp_mcast_join(grpidx, peer_id, 1, 0);
			break;
		case 2:
			if (peer_id != -1)
				dl_dp_mcast_join(grpidx, peer_id, 0, 0);
			break;
		default:
			break;
		}
		if (peer_id == -1) {
			peer_id = dl_m2c_find_peer(mc_stream->macaddr,
				DRE_DIRECT_CLIENT_EXT_TABLE,
				0);
			switch (flag) {
			case 1:
				if (peer_id != -1)
					dl_dp_mcast_join(grpidx, peer_id, 1, 1);
				else {
					int vap_id = dtlk_vapid_from_dev(netdev);
					if (vap_id > -1) {
						/* find the peer idx from */
						peer_id = dl_m2c_find_peer(mc_stream->macaddr,
							DRE_DIRECT_CLIENT_WDS_TABLE,
							0
							);
						pr_info("<%s>Found WDS Client Peer Idx [%d]for M2C\n",
							__func__,
							peer_id
							);
						/* add new peer to extension table */
						peer_id = dl_m2c_add_peer(
							(uint32_t *)mc_stream->macaddr,
							peer_id,
							(uint16_t)vap_id,
							DRE_DIRECT_CLIENT_EXT_TABLE);
						if (peer_id >= 0)
							dl_dp_mcast_join(grpidx, peer_id, 1, 1);
						else
							pr_err("[%s:%d] Failed to add entry [%s].\n",
								__func__, __LINE__, netdev->name);
					}
				}
				break;
			case 2:
				if (peer_id != -1) {
					/* remove new peer to extension table */
					dl_m2c_remove_peer(
						(uint32_t *)mc_stream->macaddr,
						0,
						0,
						DRE_DIRECT_CLIENT_EXT_TABLE
					);
					dl_dp_mcast_join(grpidx, peer_id, 0, 1);
				}
				break;
			default:
				break;
			}
		}
	}
}


int32_t dl_dp_register_mcast_module(
	struct net_device *dev,
	struct module *owner,
	Mcast_module_callback_t cb,
	unsigned int flags
	)
{
	pr_info("[%s:%d] Entry [%s] [%d].\n",
		__func__, __LINE__, dev->name, flags);
#if defined(CONFIG_LANTIQ_MCAST_HELPER_MODULE) || defined(CONFIG_LANTIQ_MCAST_HELPER)
	mcast_helper_register_module(dev,
		owner, "DirectLink", (int32_t *)cb, flags);
    pr_info("[%s:%d] Exit, returned 0.\n", __func__, __LINE__);
	return DP_SUCCESS;
#else
    pr_info("[%s:%d] Exit, returned -1.\n", __func__, __LINE__);
	return DP_FAILURE;
#endif /* #else */
}

int datapath_dtlk_register(
	PPA_SUBIF *sub_if,
	PPA_DTLK_T *dtlk)
{
	int i;
	int j;
	int radio = -1;
	struct ppe_radio_map *ppe_radio;

	/* sanity check */
	if (sub_if == NULL || dtlk == NULL) {
		dtlk_debug(DBG_ERR, "%s: invalid subif\n", __func__);
		return PPA_EINVAL;
	}
	if (sub_if->subif == -1) {
		dtlk_debug(DBG_ERR, "%s: invalid subif value\n", __func__);
		return PPA_EINVAL;
	}
	dtlk_debug(DBG_INIT,
		"%s: sub_if->port_id[%d] sub_if->subif[%d]\n",
		__func__, sub_if->port_id, sub_if->subif);
	spin_lock_bh(&g_ppe_dtlk_spinlock);
	/*if (dtlk->flags & PPE_F_DTLK_REGISTER) {*/
	if (dtlk->flags & PPE_F_DTLK_DP_REGISTER) {
		dtlk_debug(DBG_INIT, "%s: Register\n", __func__);
		/* looking for free or right radio */
		for (i = 0; i < MAX_RADIO_NUM; i++) {
			if ((g_ppe_radio[i].flags & PPE_DTLK_VALID)
				&& (g_ppe_radio[i].dl_sub_if.port_id
				== sub_if->port_id)) {
				ppe_radio = &g_ppe_radio[i];
				for (j = 0; j < MAX_DTLK_NUM; j++)
					if (ppe_radio->g_ppe_dtlk_data[j].dl_sub_if.subif ==
						sub_if->subif) {
						dtlk_debug(DBG_ERR,
							"Duplicate wifi device: %s",
							dtlk->dev->name);
						goto err_exit;
					}

				radio = i;
				dtlk_debug(DBG_INIT,
				"Register radio[%d] port[%d]\n",
				radio,
				g_ppe_radio[i].dl_sub_if.port_id);
			}
			if (radio == -1 &&
				((g_ppe_radio[0].flags &
					PPE_DTLK_VALID) == 0)) {
				dtlk_debug(DBG_INIT,
				"Register: find free radio[%d]\n",
				 i);
				radio = i;
			}
		}
		/* no free or don't match with existing datapath port */
		if (radio == -1) {
			dtlk_debug(DBG_ERR, "Register Fail, no more ports\n");
			goto err_exit;
		}
		g_ppe_radio[radio].flags |= PPE_DTLK_VALID;
		g_ppe_radio[radio].dl_sub_if.port_id = sub_if->port_id;
		dtlk_debug(DBG_INIT,
			"Register: free radio[%d] with port[%d]\n",
			radio,
			g_ppe_radio[radio].dl_sub_if.port_id
			);
		ppe_radio = &(g_ppe_radio[radio]);
		/* looking for free sub interface */
		for (j = 0; j < MAX_DTLK_NUM; j++) {
			if (ppe_radio->g_ppe_dtlk_data[j].dl_sub_if.subif ==
				-1) {
				dltx_vap_data_mib_t *vap_mib_tx =
					(dltx_vap_data_mib_t *)MPE_TX_ADDR(DLTX_VAP_DATA_MIB_OFFSET(j));
				dtlk_debug(DBG_INIT,
					"Register: radio[%d] sub[%d]\n",
					radio,
					j);
				if (dtlk->dev)
					g_ppe_radio[radio].g_ppe_dtlk_data[j].dev = (struct PPA_NETIF *)dtlk->dev;
				else
					dtlk_debug(DBG_ERR,
					"DEV is NULL\n");
				g_ppe_radio[radio].g_ppe_dtlk_data[j].vap_id
					= dtlk->vap_id;
				ppe_radio->g_ppe_dtlk_data[j].dl_sub_if.port_id
					= sub_if->port_id;
				ppe_radio->g_ppe_dtlk_data[j].dl_sub_if.subif
					= sub_if->subif;
				/* update quick reference table */
				g_quick_ref_sub_if_from_vap_id[dtlk->vap_id].port_id
					= sub_if->port_id;
				g_quick_ref_sub_if_from_vap_id[dtlk->vap_id].subif
					= sub_if->subif;
				g_ppe_radio[radio].g_ppe_dtlk_data[j].flags
					|= PPE_DTLK_VALID;
				/* clear MIB information */
				memset((void *)vap_mib_tx,
					0,
					sizeof(dltx_vap_data_mib_t));
				break;
			}
		 }
		dltk_update_radio_datapath_port(radio,
			dtlk->vap_id,
			&(g_quick_ref_sub_if_from_vap_id[dtlk->vap_id]),
			PPE_F_DTLK_DP_REGISTER);
		if (dtlk->dev)
			dtlk_debug(DBG_INIT,
				"%s: dtlk->dev->name[%s]\n",
				__func__, dtlk->dev->name);
		else
			dtlk_debug(DBG_ERR,
				"%s: wrong dtlk->dev is NULL\n",
				__func__);
		if (set_vap_itf_tbl_fn)
			set_vap_itf_tbl_fn(dtlk->vap_id, sub_if->subif);
		/* switch setting */
		gsw_enable_ingress_port_remove(sub_if->port_id);
#if defined(CONFIG_LANTIQ_MCAST_HELPER_MODULE) || defined(CONFIG_LANTIQ_MCAST_HELPER)
		/* register to mcast helper */
		dl_dp_register_mcast_module(dtlk->dev,
			 THIS_MODULE,
			 dl_dp_mcast_cb,
			 MC_F_REGISTER);
#endif
	} else {
		/*looking for right radio with respective datapath port*/
		dtlk_debug(DBG_INIT, "%s: DeRegister\n", __func__);
		for (i = 0; i < MAX_RADIO_NUM; i++)
			if ((g_ppe_radio[i].flags & PPE_DTLK_VALID)
				&& (g_ppe_radio[i].dl_sub_if.port_id
				== sub_if->port_id))
				radio = i;

		if (radio == -1) {
			dtlk_debug(DBG_ERR, "No record, deregistration failed\n");
			goto err_exit;
		}
		ppe_radio = &g_ppe_radio[radio];
		/* deregister VAP device */
		for (j = 0; j < MAX_DTLK_NUM; j++) {
			if (ppe_radio->g_ppe_dtlk_data[j].dl_sub_if.subif ==
				sub_if->subif) {
				ppe_radio->g_ppe_dtlk_data[j].dev = NULL;
				ppe_radio->g_ppe_dtlk_data[j].vap_id = -1;
				ppe_radio->g_ppe_dtlk_data[j].flags
					&= (~PPE_DTLK_VALID);
				ppe_radio->g_ppe_dtlk_data[j].dl_sub_if.port_id = -1;
				ppe_radio->g_ppe_dtlk_data[j].dl_sub_if.subif = -1;
				/* update quick reference table */
				dltk_remove_quickrefsub(sub_if);
				break;
			}
		}
		dltk_update_radio_datapath_port(radio,
			dtlk->vap_id,
			&(g_quick_ref_sub_if_from_vap_id[dtlk->vap_id]),
			PPE_F_DTLK_DEREGISTER);
		if (set_vap_itf_tbl_fn)
			set_vap_itf_tbl_fn(dtlk->vap_id, 0xF);
#if defined(CONFIG_LANTIQ_MCAST_HELPER_MODULE) || defined(CONFIG_LANTIQ_MCAST_HELPER)
		/* register to mcast helper */
		dl_dp_register_mcast_module(dtlk->dev,
			 THIS_MODULE,
			 dl_dp_mcast_cb,
			 MC_F_DEREGISTER);
#endif
	}
	spin_unlock_bh(&g_ppe_dtlk_spinlock);

	return PPA_SUCCESS;

err_exit:
	spin_unlock_bh(&g_ppe_dtlk_spinlock);

	return PPA_EINVAL;
}
EXPORT_SYMBOL(datapath_dtlk_register);

/** Function: dltx_data_structure_init
* Purpose: Init DLTX data structure
* Argument: None
* Return: None.
*	List of initialization: TX free buffer management.
*
*/
int dltx_data_structure_init(void)
{
	memset((void *)g_dl_buf_info.tx_cfg_ctxt_buf_base,
		0,
		g_dl_buf_info.tx_cfg_ctxt_buf_size
		);
	/* init comm buffer */
	memset((void *)g_dl_buf_info.comm_buf_base,
		0,
		g_dl_buf_info.comm_buf_size);
	return DTLK_SUCCESS;
}

int dlrx_data_structure_init(void)
{
	unsigned int index;
	struct sk_buff *new_skb;
	unsigned int seqid;
	unsigned int temp_ce5_buf_size;
	unsigned int shift_size = 0;
	dlrx_bufsize_t dlrx_bufnum;
	/**************************************/
	/* Pointer to various data structures with respect to config context
	 * dlrx_cfg_ctxt_dma_t *dlrx_cfg_ctxt_dma_des_wlan_ptr;
	 * */
	/* dlrx_cfg_ctxt_dma_t *dlrx_cfg_ctxt_dma_des_gswip_ptr; */



	dlrx_cfg_ctxt_cpu_ce5des_t *dlrx_cfg_ctxt_cpu_ce5des_ptr;
	dlrx_ce5des_format_t *dlrx_ce5des_format_ptr;

	dlrx_cfg_ctxt_ce5des_t *dlrx_cfg_ctxt_ce5des_ptr;
	dlrx_cfg_ctxt_ce5buf_t *dlrx_cfg_ctxt_ce5buf_ptr;

	dlrx_cfg_ctxt_rxpb_ptr_ring_t *dlrx_cfg_ctxt_rxpb_ptr_ring_ptr;

	dlrx_cfg_ctxt_ro_mainlist_t *dlrx_cfg_ctxt_ro_mainlist_ptr;
	dlrx_cfg_ctxt_ro_linklist_t *dlrx_cfg_ctxt_ro_linklist_ptr;

	dlrx_cfg_ctxt_rxpb_ptr_rel_msgbuf_t *dlrx_cfg_ctxt_rxpb_ptr_rel_msgbuf_ptr;
	dlrx_cfg_global_t *dlrx_cfg_global_ptr;

	/** This is the reorder main list in DDR memory
	* The starting of this	base address is stored in
	* "dlrx_cfg_ctxt_ro_mainlist_t" structure. */
	dlrx_ro_mainlist_t *dlrx_ro_mainlist_ptr;
	dlrx_ro_linklist_t *dlrx_ro_linklist_ptr;

	dlrx_rxpb_ptr_ring_t *dlrx_rxpb_ring_ptr;
	dlrx_cfg_vap2int_map1_t *dlrx_cfg_vap2int_map1_ptr;
	dlrx_cfg_vap2int_map2_t *dlrx_cfg_vap2int_map2_ptr;
	dlrx_cfg_ctxt_rxpb_t *dlrx_cfg_ctxt_rxpb_ptr;

	uint32_t *msg_buf_base;

	/* The below base addresses will be used by FW */
	dtlk_mem_base_get(NULL, (uint32_t *)&ddr_base);
	if (!ddr_base) {
		dtlk_debug(DBG_ERR, "No memory for DLRX\n");
		return DTLK_FAILURE;
	}
	dtlk_mem_sram_base_get((uint32_t *)&cfg_ctxt_base);
	if (!cfg_ctxt_base) {
		ddr_base = 0;
		dtlk_debug(DBG_ERR, "No memory for DLRX Context base\n");
		return DTLK_FAILURE;
	}
	/* Set the memory range to 0 */
	memset((void *)ddr_base, 0, g_dl_buf_info.rx_msgbuf_size);
	memset((void *)cfg_ctxt_base, 0, g_dl_buf_info.rx_cfg_ctxt_buf_size);

	if (ppa_dl_detect_11ac_card() ==  PEREGRINE_BOARD) {
		g_dlrx_max_inv_header_len = MAX_INV_PEREGRINE_HEADER_LEN;
		g_dlrx_cfg_offset_atten = QCA_PEREGRINE_11AC_CFG_OFFSET_ATTEN;
	} else {
		if (g11ACWirelessCardID_SUBTYPE == SUBTYPE_NONE_BOARD) {
			g_dlrx_max_inv_header_len = MAX_INV_BEELINER_HEADER_LEN;
			g_dlrx_cfg_offset_atten = QCA_BEELINER_11AC_CFG_OFFSET_ATTEN;
		} else {
			g_dlrx_max_inv_header_len = MAX_INV_CASCADE_HEADER_LEN;
			g_dlrx_cfg_offset_atten = QCA_CASCADE_11AC_CFG_OFFSET_ATTEN;
		}
	}
	/* Initializing the Length of data structure */
	dlrx_init_buf_size(&dlrx_bufnum);
	dlrx_cfg_ctxt_cpu_ce5des_ptr =
		(dlrx_cfg_ctxt_cpu_ce5des_t *)DLRX_CFG_CTXT_CPU_CE5DES_BASE;
	/* Initializing CPU CE5 Destination Ring Pointers
	* ==> 2 * (1 * 8) DWORDS ( this CPU_CE5DES is in SB )
	*/
	dlrx_cfg_ctxt_cpu_ce5des_ptr->cfg_badr_cpu_ce5 =
		(unsigned int)DLRX_DDR_CPU_CE5_DESC_BASE;
	dlrx_cfg_ctxt_cpu_ce5des_ptr->cfg_num_cpu_ce5 =
		dlrx_bufnum.cpu_ce5_desc_ring_num;
	dlrx_cfg_ctxt_cpu_ce5des_ptr->cpu_ce5_read_index = 0;
	dlrx_cfg_ctxt_cpu_ce5des_ptr->cpu_ce5_write_index = 1;
	dlrx_cfg_ctxt_cpu_ce5des_ptr->cpu_ce5_msg_done = 1;

	dlrx_cfg_ctxt_rxpb_ptr_rel_msgbuf_ptr =
		(dlrx_cfg_ctxt_rxpb_ptr_rel_msgbuf_t *)DLRX_CFG_CTXT_RXPB_PTR_REL_MSGBUF_BASE;
	/* Initializing RX PB Release Message Buffer
	* ==> 2 * (2 * 128) DWORDS
	* */
	dlrx_cfg_ctxt_rxpb_ptr_rel_msgbuf_ptr->cfg_badr_rel_msgbuf =
		(unsigned int)DLRX_DDR_RX_PKT_BUF_REL_MSG_BASE;
	dlrx_cfg_ctxt_rxpb_ptr_rel_msgbuf_ptr->cfg_num_rel_msgbuf =
		dlrx_bufnum.rx_pkt_buf_rel_msg_num;

	dlrx_cfg_ctxt_rxpb_ptr =
		(dlrx_cfg_ctxt_rxpb_t *)DLRX_CFG_CTXT_RXPB_BASE;
	dlrx_cfg_ctxt_rxpb_ptr->cfg_offset_atten = 4;
	dlrx_cfg_ctxt_rxpb_ptr->cfg_size_rxpktdes = g_dlrx_cfg_offset_atten;

	dlrx_cfg_ctxt_rxpb_ptr_ring_ptr =
		(dlrx_cfg_ctxt_rxpb_ptr_ring_t *)DLRX_CFG_CTXT_RXPB_PTR_RING_BASE;

	/* Initializing RX PB Ring Ptr ===> 256 * (1 * 8) DWORDS */
	dlrx_cfg_ctxt_rxpb_ptr_ring_ptr->cfg_badr_rxpb_ptr_ring =
		(unsigned int)DLRX_DDR_RX_PKT_BUF_RING_BASE;
	dlrx_cfg_ctxt_rxpb_ptr_ring_ptr->cfg_num_rxpb_ptr_ring =
		dlrx_bufnum.rx_pkt_buf_ptr_ring_num;
	dlrx_cfg_ctxt_rxpb_ptr_ring_ptr->rxpb_ptr_read_index = 0;
	dlrx_cfg_ctxt_rxpb_ptr_ring_ptr->rxpb_ptr_write_index =
		RX_PKT_BUF_PTR_RING_ALLOC_NUM - 1;
	dlrx_rxpb_ring_ptr =
		(dlrx_rxpb_ptr_ring_t *)DLRX_DDR_RX_PKT_BUF_RING_BASE;
	/* initial 1024 -1 */
	for (index = 0;
		index < RX_PKT_BUF_PTR_RING_ALLOC_NUM - 1;
		index++) {
		/* Initializing RX PB PTR ==> 4096 * (1 * 4) DWORDS */
		new_skb = alloc_skb_rx();
		if (new_skb == NULL)
			return DTLK_FAILURE;
		else {
			dma_addr_t phy_addr;
			phy_addr = dma_map_single(
				g_mpe_dev,
				(void *) ((unsigned char *)new_skb + 128),
				1920,
				DMA_FROM_DEVICE
				);
			if (unlikely(dma_mapping_error(g_mpe_dev, phy_addr)))
				dtlk_debug(DBG_ERR, "%s: DMA error\n", __func__);
			dlrx_rxpb_ring_ptr->rxpb_ptr = phy_addr;
			/* dtlk_debug(DBG_INIT, "%s: %x\n",__func__,new_skb); */
			dlrx_rxpb_ring_ptr++;
		}
	}
	/* This is message ring initialization */
	dlrx_cfg_ctxt_ce5buf_ptr =
		(dlrx_cfg_ctxt_ce5buf_t *)DLRX_CFG_CTXT_CE5BUF_BASE;
	/* Initializing CE5 Buffers and Buffer format pointers
	* ====> 4096 * 512 Bytes */
	dlrx_cfg_ctxt_ce5buf_ptr->cfg_badr_ce5buf =
		(unsigned int)DLRX_DDR_CE5BUF_BASE;
	dlrx_cfg_ctxt_ce5buf_ptr->cfg_num_ce5buf =
		dlrx_bufnum.ce5_dest_msg_buf_num;
	dlrx_cfg_ctxt_ce5buf_ptr->cfg_size_ce5buf =
		DLRX_CE5_DEST_BUF_SIZE;
	temp_ce5_buf_size = DLRX_CE5_DEST_BUF_SIZE;

	while (temp_ce5_buf_size != 1) {
		shift_size++;
		temp_ce5_buf_size >>= 1;
	}
	dlrx_cfg_ctxt_ce5buf_ptr->cfg_size_shift_ce5buf = shift_size;

	/* initial msg buf type to 0xFF */
	msg_buf_base = (uint32_t *)DLRX_DDR_CE5BUF_BASE;
	for (index = 0;
		index < dlrx_bufnum.ce5_dest_msg_buf_num;
		index++) {
		*(msg_buf_base + index * 512 / 4 + 2) = 0xFF;
	}
	/* Initializing Actual CE5 Descriptors format ====>4096 * 2 DWORDS */
	/* This is ce5 descriptor initialization */
	dlrx_ce5des_format_ptr = (dlrx_ce5des_format_t *)DLRX_DDR_CE5DESC_BASE;
	for (index = 0; index < dlrx_bufnum.ce5_dest_msg_buf_num; index++) {
		dlrx_ce5des_format_ptr->dest_ptr =
			dma_map_single(
			g_mpe_dev,
			(void *)dlrx_cfg_ctxt_ce5buf_ptr->cfg_badr_ce5buf +
			 (index << dlrx_cfg_ctxt_ce5buf_ptr->cfg_size_shift_ce5buf),
			512,
			DMA_FROM_DEVICE
			);
		if (unlikely(dma_mapping_error(g_mpe_dev, dlrx_ce5des_format_ptr->dest_ptr)))
			dtlk_debug(DBG_ERR, "%s: DMA error", __func__);

		dlrx_ce5des_format_ptr->meta_data = 0;
		dlrx_ce5des_format_ptr->nbytes	= 0;
		dlrx_ce5des_format_ptr++;
	}
	dlrx_cfg_ctxt_ce5des_ptr =
		(dlrx_cfg_ctxt_ce5des_t *)DLRX_CFG_CTXT_CE5DES_BASE;
	/* Initializing General Configuration of CE5
	* Destination Descriptors ===>  1 * 4 DWORDS
	* (only used by driver)
	* */
	dlrx_cfg_ctxt_ce5des_ptr->cfg_badr_ce5des =
		(unsigned int)(DLRX_DDR_CE5DESC_BASE);
	dlrx_cfg_ctxt_ce5des_ptr->cfg_num_ce5des =
		dlrx_bufnum.ce5_dest_desc_ring_num;
	dtlk_debug(DBG_INIT,
		"%s: cfg_num_ce5des[%d]\n",
		__func__,
		dlrx_cfg_ctxt_ce5des_ptr->cfg_num_ce5des
		);

	dlrx_cfg_ctxt_ro_mainlist_ptr =
		(dlrx_cfg_ctxt_ro_mainlist_t *)DLRX_CFG_CTXT_RO_MAINLIST_BASE;
	/* Initializing RX REORDER Mainlist Ptr
	* ===> 128 * 16 = 2048 domains
	* ==> Each domain == 64 + 4 DWORDS
	* */
	dlrx_cfg_ctxt_ro_mainlist_ptr->cfg_badr_ro_mainlist =
		(unsigned int)DLRX_DDR_RO_MAINLIST_BASE;
	dlrx_cfg_ctxt_ro_mainlist_ptr->cfg_num_ro_mainlist =
		dlrx_bufnum.rx_reorder_main_num;
	dlrx_cfg_ctxt_ro_mainlist_ptr->ro_mainlist_ptr = NULL_PTR;

	dlrx_ro_mainlist_ptr = (dlrx_ro_mainlist_t *)DLRX_DDR_RO_MAINLIST_BASE;
	for (index = 0; index < dlrx_bufnum.rx_reorder_main_num; index++) {
		dlrx_ro_mainlist_ptr->first_ptr = NULL_PTR;
		for (seqid = 1; seqid < 64; seqid++)
			dlrx_ro_mainlist_ptr->_dw_res0[seqid-1] = NULL_PTR;
		dlrx_ro_mainlist_ptr++;
	}

	dlrx_cfg_ctxt_ro_linklist_ptr =
		(dlrx_cfg_ctxt_ro_linklist_t *) DLRX_CFG_CTXT_RO_LINKLIST_BASE;
	/* Initializing RX REORDER Linklist Ptr
	* ===> 4095 Desc ==> Each Desc == 6 DWORDS */
	dlrx_cfg_ctxt_ro_linklist_ptr->cfg_badr_ro_linklist =
		(unsigned int)DLRX_DDR_RO_LINKLIST_BASE;
	dlrx_cfg_ctxt_ro_linklist_ptr->cfg_num_ro_linklist =
		dlrx_bufnum.rx_reorder_desc_link_num;
	dlrx_cfg_ctxt_ro_linklist_ptr->free_num_ro_linklist =
		dlrx_cfg_ctxt_ro_linklist_ptr->cfg_num_ro_linklist - 1;
	dlrx_cfg_ctxt_ro_linklist_ptr->ro_des_free_head_index = 0;
	dlrx_cfg_ctxt_ro_linklist_ptr->ro_des_free_tail_index =
		dlrx_cfg_ctxt_ro_linklist_ptr->cfg_num_ro_linklist - 1;

	dlrx_ro_linklist_ptr = (dlrx_ro_linklist_t *)DLRX_DDR_RO_LINKLIST_BASE;
	for (index = 0; index < dlrx_bufnum.rx_reorder_desc_link_num;
		index++) {
		dlrx_ro_linklist_ptr->next_ptr = index + 1;
		dlrx_ro_linklist_ptr++;
	}
	dlrx_cfg_global_ptr = (dlrx_cfg_global_t *)DLRX_CFG_GLOBAL_BASE;
	/* Initializing GLOBAL CONFIGURATION STRUCTURE */
	dlrx_cfg_global_ptr->dltx_enable = 0;
	dlrx_cfg_global_ptr->dlrx_enable = 0;
	dlrx_cfg_global_ptr->dlrx_pcie_base = (unsigned int)pcie_base;
	dlrx_cfg_global_ptr->dlrx_ddr_base = (unsigned int)ddr_base;
	dlrx_cfg_global_ptr->dlrx_cfg_ctxt_base = (unsigned int)cfg_ctxt_base;
	dlrx_cfg_global_ptr->dlrx_cfg_ctxt_max_size = DLRX_CFG_CTXT_MAX_SIZE;
	dlrx_cfg_global_ptr->dlrx_cfg_unload = 0;
	dlrx_cfg_global_ptr->dlrx_qca_hw = ppa_dl_detect_11ac_card();
	dlrx_cfg_global_ptr->dlrx_qca_hw_sub_type =
		g11ACWirelessCardID_SUBTYPE;
	dlrx_cfg_vap2int_map1_ptr =
		(dlrx_cfg_vap2int_map1_t *) DLRX_CFG_VAP2INT_MAP1_BASE;
	dlrx_cfg_vap2int_map2_ptr =
		(dlrx_cfg_vap2int_map2_t *) DLRX_CFG_VAP2INT_MAP2_BASE;
	dlrx_cfg_vap2int_map1_ptr->vap0 = 0xF;
	dlrx_cfg_vap2int_map1_ptr->vap1 = 0xF;
	dlrx_cfg_vap2int_map1_ptr->vap2 = 0xF;
	dlrx_cfg_vap2int_map1_ptr->vap3 = 0xF;
	dlrx_cfg_vap2int_map1_ptr->vap4 = 0xF;
	dlrx_cfg_vap2int_map1_ptr->vap5 = 0xF;
	dlrx_cfg_vap2int_map1_ptr->vap6 = 0xF;
	dlrx_cfg_vap2int_map1_ptr->vap7 = 0xF;
	dlrx_cfg_vap2int_map2_ptr->vap8 = 0xF;
	dlrx_cfg_vap2int_map2_ptr->vap9 = 0xF;
	dlrx_cfg_vap2int_map2_ptr->vap10 = 0xF;
	dlrx_cfg_vap2int_map2_ptr->vap11 = 0xF;
	dlrx_cfg_vap2int_map2_ptr->vap12 = 0xF;
	dlrx_cfg_vap2int_map2_ptr->vap13 = 0xF;
	dlrx_cfg_vap2int_map2_ptr->vap14 = 0xF;
	dlrx_cfg_vap2int_map2_ptr->vap15 = 0xF;

	return DTLK_SUCCESS;
}


/** Function: get_next_argument.
 * Description: Get the next valid argument from given string, ignore space
 * Argument: pSrc [IN]: source pointer
 * Return: pSrc[OUT]: new pointer points to the starting of valid argument
 *			  len[OUT]: the len of ignorance space.
*/
static char *get_next_argument(
	char *ptr_src,
	int *len
	)
{
	char *ptr_temp = ptr_src;
	if (ptr_temp == NULL) {
		*len = 0;
		return NULL;
	}

	while (ptr_temp != NULL && *ptr_temp == ' ') {
		ptr_temp++;
	}

	return ptr_temp;

}
/** Function: Compare strings follow by given number of length,
 * ignore case senstive.
 * Description: Compare two strings, ignore the case sensitive
 * Argument: p1 [IN]: source pointer 1
 *				   p2 [IN]: source pointer 2
 *				   n [IN]: length of string to compare.
 * Return:0: identical
 *			 other: not match
*/
static INLINE int strincmp(
	const char *p1,
	const char *p2, int n
	)
{
	int c1 = 0, c2;

	while (n && *p1 && *p2)	{
		c1 = *p1 >= 'A' && *p1 <= 'Z' ? *p1 + 'a' - 'A' : *p1;
		c2 = *p2 >= 'A' && *p2 <= 'Z' ? *p2 + 'a' - 'A' : *p2;
		c1 -= c2;
		if (c1)
			return c1;
		p1++;
		p2++;
		n--;
	}

	return n ? *p1 - *p2 : c1;
}

/**	Proc struct def
 */
/* Functions and structure support proc/dl/peer_to_vap */
static int proc_read_dtlk_peer_to_vap(
	struct seq_file *seq,
	void *v
	)
{
	int i = 0;
	seq_printf(seq, "\n");
	seq_printf(seq, "Peer to VAP and PN Configuration table: \n");
	seq_printf(seq,	"PN type: 0-no PN check,1-48 bit PB,2-128");
	seq_printf(seq,	" bit PB Even,3-128 bit PB Odd\n");
	seq_printf(seq, "\n");
	seq_printf(seq, "[ ID:Acc:PN:Vap] [ ID:Acc:PN:Vap]\n");
	for (i = 0; i < MAX_PEER_NUM; i += 2) {
		uint32_t peer0 = 0, peer1 = 0;
		peer0 = *(uint32_t *)DLRX_CFG_PEER_TO_VAP_PN_BASE(i);
		peer1 = *(uint32_t *)DLRX_CFG_PEER_TO_VAP_PN_BASE(i + 1);
		seq_printf(seq, "[%3d:%3d:%2d:%3d] [%3d:%3d:%2d:%3d]\n",
			i,
			(peer0 & 0x40),
			(peer0 & 0x30),
			(peer0 & 0xF),
			i + 1,
			(peer1 & 0x40),
			(peer1 & 0x30),
			(peer1 & 0xF)
			);
	}
	seq_printf(seq, "\n");
	return 0;
}
/* Functions and structure support proc/dl/peer_id */
static int proc_read_dtlk_peer_id(
	struct seq_file *seq,
	void *v
	)
{
	int i = 0;
	seq_printf(seq, "\n");
	seq_printf(seq, "Peer ID to peer table address: %p\n",
		DLRX_CFG_PEER_ID_TO_PEER_MAP_BASE(0));
	seq_printf(seq, "\n");
	seq_printf(seq, "Valid Peer ID table:\n");
	seq_printf(seq, "  [ ID:   Peer]\n");
	for (i = 0; i < MAX_PEERID_NUM/4; i++) {
		uint32_t regs = 0;
		uint8_t peerid0 = 0, peerid1 = 0, peerid2 = 0, peerid3 = 0;
		regs = *(uint32_t *)DLRX_CFG_PEER_ID_TO_PEER_MAP_BASE(i);
		peerid0 = ((regs) & 0xff);
		peerid1 = ((regs >>  8) & 0xff);
		peerid2 = ((regs >> 16) & 0xff);
		peerid3 = ((regs >> 24) & 0xff);
		if ((peerid0 >> 7) & 1)
			seq_printf(seq,
			"  [%3d:%7d]\n", i * 4, (peerid0 & 0x7f));

		if ((peerid1 >> 7) & 1)
			seq_printf(seq,
			"  [%3d:%7d]\n", i * 4 + 1, (peerid1 & 0x7f));

		if ((peerid2 >> 7) & 1)
			seq_printf(seq,
			"  [%3d:%7d]\n", i * 4 + 2, (peerid2 & 0x7f));

		if ((peerid3 >> 7) & 1)
			seq_printf(seq,
			"  [%3d:%7d]\n", i * 4 + 3, (peerid3 & 0x7f));

	}
	seq_printf(seq, "\n");

	return 0;
}
/* Functions and structure support proc/dl/wifi_port */
static int proc_read_dtlk_wifi_port(
	struct seq_file *seq,
	void *v
	)
{
	int i = 0;
	int radio = 0;
	if (g_ppe_radio[0].flags | PPE_DTLK_VALID) {
		seq_printf(seq, "Radio [%d]: data port [%d]\n",
			radio,
			g_ppe_radio[0].dl_sub_if.port_id);
	for (i = 0; i < MAX_VAP_NUM; i++) {
		struct net_device *vap_dev = dtlk_dev_from_vapid(i);
		if (vap_dev) {
			int directpath_id = 0;
			uint32_t vap2int;
			if (i < MAX_VAP_NUM / 2)
				vap2int = *(uint32_t *)DLRX_CFG_VAP2INT_MAP1_BASE;
			else
				vap2int = *(uint32_t *)DLRX_CFG_VAP2INT_MAP2_BASE;

			directpath_id = (vap2int >> i*4) & 0xf;
			seq_printf(seq,
				"  [%d]: Sub interface: %d, VAP id: %d, wifi dev: %s\n",
				i,
				directpath_id,
				i,
				vap_dev->name
				);
		} else
			seq_printf(seq, "  [%d]: Invalid\n", i);
	}
	} else
		seq_printf(seq, "Radio [%d]: Invalid data port\n", radio);


	return 0;
}

static int proc_read_dtlk_peer_to_vap_seq_open(
	struct inode *inode,
	struct file *file
	)
{
	return single_open(file, proc_read_dtlk_peer_to_vap, NULL);
}

static int proc_read_dtlk_peer_id_seq_open(
	struct inode *inode,
	struct file *file
	)
{
	return single_open(file, proc_read_dtlk_peer_id, NULL);
}

static int proc_read_dtlk_wifi_port_seq_open(
	struct inode *inode,
	struct file *file
	)
{
	return single_open(file, proc_read_dtlk_wifi_port, NULL);
}

static struct file_operations g_proc_file_peer_to_vap_seq_fops = {
	.owner		= THIS_MODULE,
	.open		= proc_read_dtlk_peer_to_vap_seq_open,
	.read		= seq_read,
	.llseek 	= seq_lseek,
	.release	= single_release
};

static struct file_operations g_proc_file_peer_id_seq_fops = {
	.owner		= THIS_MODULE,
	.open		= proc_read_dtlk_peer_id_seq_open,
	.read		= seq_read,
	.llseek 	= seq_lseek,
	.release	= single_release
};

static struct file_operations g_proc_file_wifi_port_seq_fops = {
	.owner		= THIS_MODULE,
	.open		= proc_read_dtlk_wifi_port_seq_open,
	.read		= seq_read,
	.llseek 	= seq_lseek,
	.release	= single_release
};

static int proc_read_mem(
	struct seq_file *seq,
	void *v
	)
{
	return 0;
}
static int proc_read_mem_seq_open(
	struct inode *inode,
	struct file *file
	)
{
	return single_open(file, proc_read_mem, NULL);
}
static INLINE int get_token(
	char **p1,
	char **p2,
	int *len,
	int *colon
	) {
	int tlen = 0;
	while (*len && !((**p1 >= 'A' && **p1 <= 'Z') ||
		(**p1 >= 'a' && **p1 <= 'z') ||
		(**p1 >= '0' && **p1 <= '9'))) {
		(*p1)++;
		(*len)--;
	}
	if (!*len)
		return 0;

	if  (*colon) {
		*colon = 0;
		*p2 = *p1;
		while (*len && **p2 > ' ' && **p2 != ',') {
			if (**p2 == ':') {
				*colon = 1;
				break;
			}
			(*p2)++;
			(*len)--;
			tlen++;
		}
		**p2 = 0;
	} else {
		*p2 = *p1;
		while (*len && **p2 > ' ' && **p2 != ',') {
			(*p2)++;
			(*len)--;
			tlen++;
		}
		**p2 = 0;
	}

	return tlen;
}

static INLINE void ignore_space(
	char **p,
	int *len
	)
{
	while (*len && (**p <= ' ' || **p == ':' ||
		**p == '.' || **p == ',')) {
		(*p)++;
		(*len)--;
	}
}

static INLINE int get_number(
	char **p,
	int *len,
	int is_hex
	)
{
	int ret = 0;
	int n = 0;

	if ((*p)[0] == '0' && (*p)[1] == 'x') {
		is_hex = 1;
		(*p) += 2;
		(*len) -= 2;
	}

	if (is_hex) {
		while (*len && ((**p >= '0' && **p <= '9') ||
			(**p >= 'a' && **p <= 'f') ||
			(**p >= 'A' && **p <= 'F'))) {
			if (**p >= '0' && **p <= '9')
				n = **p - '0';
			else if (**p >= 'a' && **p <= 'f')
			   n = **p - 'a' + 10;
			else if (**p >= 'A' && **p <= 'F')
				n = **p - 'A' + 10;
			ret = (ret << 4) | n;
			(*p)++;
			(*len)--;
		}
	} else {
		while (*len && **p >= '0' && **p <= '9') {
			n = **p - '0';
			ret = ret * 10 + n;
			(*p)++;
			(*len)--;
		}
	}

	return ret;
}

static ssize_t proc_write_mem(
	struct file *file,
	const char __user *buf,
	size_t count,
	loff_t *data
	)
{
	char *p1, *p2;
	int len;
	int colon;
	unsigned long *p = NULL;
	unsigned long dword;
	char local_buf[900];
	int i, n, l;


	len = sizeof(local_buf) < count ? sizeof(local_buf) - 1 : count;
	len = len - copy_from_user(local_buf, buf, len);
	local_buf[len] = 0;

	p1 = local_buf;
	p2 = NULL;
	colon = 1;
	while (get_token(&p1, &p2, &len, &colon)) {
		if (stricmp(p1, "w") == 0 ||
			stricmp(p1, "write") == 0 ||
			stricmp(p1, "r") == 0 ||
			stricmp(p1, "read") == 0)
			break;

		p1 = p2;
		colon = 1;
	}

	if (*p1 == 'w') {
		ignore_space(&p2, &len);
		if (p2[0] == 's' && p2[1] == 'w' &&
			(p2[2] == ' ' || p2[2] == '\t')) {
		} else
			p = (unsigned long *)get_number(&p2, &len, 1);

		if ((u32)p >= KSEG0)
			while (1) {
				ignore_space(&p2, &len);
				if (!len || !((*p2 >= '0' && *p2 <= '9') ||
					(*p2 >= 'a' && *p2 <= 'f') ||
					(*p2 >= 'A' && *p2 <= 'F')))
					break;

				*p++ = (u32)get_number(&p2, &len, 1);
			}
	} else if (*p1 == 'r')	{
		ignore_space(&p2, &len);
		if (p2[0] == 's' && p2[1] == 'w' &&
			(p2[2] == ' ' || p2[2] == '\t')) {
			/* do nothing */
		} else
			p = (unsigned long *)get_number(&p2, &len, 1);

		if ((u32)p >= KSEG0) {
			ignore_space(&p2, &len);
			n = (int)get_number(&p2, &len, 0);
			if (n) {
				char str[32] = {0};
				char *pch = str;
				int k;
				char c;

				n += (l = ((int)p >> 2) & 0x03);
				p = (unsigned long *)((u32)p & ~0x0F);
				for (i = 0; i < n; i++) {
					if ((i & 0x03) == 0) {
						printk("%08X:", (u32)p);
						pch = str;
					}
					if (i < l) {
						printk("		 ");
						sprintf(pch, "	  ");
					} else {
						dword = *p;
						printk(" %08X", (u32)dword);
						for (k = 0; k < 4; k++) {
							c = ((char *)&dword)[k];
							pch[k] = c < ' ' ? '.' : c;
						}
					}
					p++;
					pch += 4;
					if ((i & 0x03) == 0x03) {
						pch[0] = 0;
						printk(" ; %s\n", str);
					}
				}
				if ((n & 0x03) != 0x00) {
					for (k = 4 - (n & 0x03); k > 0; k--)
						printk("		 ");
					pch[0] = 0;
					printk(" ; %s\n", str);
				}
			}
		}
	}
	return count;
}

static struct file_operations g_proc_file_mem_seq_fops = {
	.owner	= THIS_MODULE,
	.open	= proc_read_mem_seq_open,
	.read	= seq_read,
	.write	= proc_write_mem,
	.llseek	= seq_lseek,
	.release	= single_release,
};

#if defined(CONFIG_ACCL_11AC_CS2)
static int proc_read_pflow(
	struct seq_file *seq,
	void *v
	)
{
	int i = 0;
	struct dl_prio_queue *prio_queue;
	struct _dl_ce4_pflow_control *ctrl;
	ctrl = (struct _dl_ce4_pflow_control *)
		MPE_TX_ADDR(DLTX_CFG_CTXT_CE4_PFLOW_CTRL);
	seq_printf(seq, "General Information\n");
	seq_printf(seq, "Current Mode[%s]\n",
		ctrl->pflow_ctrl_mode == 0 ? "PUSH mode" : "PULL mode");
	if (ctrl->pflow_ctrl_mode) {
		seq_printf(seq, "\tQDepth Flush Interval[%d]\n",
			ctrl->pmap_qdepth_flush_interval);
		seq_printf(seq, "\tRotting Interval[%d]\n",
			ctrl->pmap_rotting_timer_interval);
		seq_printf(seq, "\tCongestion Timer Interval [%d]\n",
			ctrl->pflow_cong_ctrl_timer_interval);
		seq_printf(seq, "\tTTL Default[%d]\n",
			ctrl->pflow_msdu_default_ttl);
		seq_printf(seq, "\tControl Min Threshold[%d]\n",
			ctrl->pflow_ctl_min_threshold);
	}
	prio_queue = (struct dl_prio_queue *)
		MPE_TX_ADDR(DLTX_PRIO_SOFT_QUEUE_DMA_DESC_CTXT);
	seq_printf(seq, "Active Peer Flow MIB Information\n");
	for (i = 0; i < PRIO_Q_SIZE; i++) {
		if (prio_queue->enq_cnt) {
			seq_printf(seq, "\tPeer [%d] Tid[%d]:", i / DL_DMA_TID_NUM, i % DL_DMA_TID_NUM);
			seq_printf(seq, " Enqueue: %u;", prio_queue->enq_cnt);
			seq_printf(seq, " Dequeue: %u;", prio_queue->deq_cnt);
			seq_printf(seq, " Timeout: %u;", prio_queue->timeout_cnt);
			seq_printf(seq, " Discard: %u;", prio_queue->discard_cnt);
			seq_printf(seq, " Overflow: %u\n", prio_queue->drop_overflow_cnt);
		}
		prio_queue++;
	}
	return 0;
}

static int proc_read_uptime(
	struct seq_file *seq,
	void *v
	)
{
	u32 jiffies, days, sec, min, hr;

	jiffies = mpe_hal_get_jiffies();

	sec = jiffies / 1000;

	if (sec >= 60) {
		min = sec / 60;
		sec = sec - (min * 60);
	} else
		min = 0;

	if (min >= 60) {
		hr = min / 60;
		min = min - (hr * 60);
	} else
		hr = 0;

	if (hr >= 24) {
		days = hr / 24;
		hr = hr - (days * 24);
	} else
		days = 0;
	seq_printf(seq, "Jiffies        : %08d\n", jiffies);
	seq_printf(seq, "Uptime(d:h:m:s): %02d:%02d:%02d:%02d\n", days,
		hr, min, sec);

	return 0;
}

static int proc_read_uptime_seq_open(
	struct inode *inode,
	struct file *file
	)
{
	return single_open(file, proc_read_uptime, NULL);
}

static struct file_operations g_proc_file_uptime_seq_fops = {
	.owner	= THIS_MODULE,
	.open	= proc_read_uptime_seq_open,
	.read	= seq_read,
	.write	= NULL,
	.llseek	= seq_lseek,
	.release	= single_release,
};

static int proc_read_pflow_seq_open(
	struct inode *inode,
	struct file *file
	)
{
	return single_open(file, proc_read_pflow, NULL);
}
extern int32_t update_bridging_entry(uint8_t mac[PPA_ETH_ALEN], uint16_t peer_id);
static void pflow_reset_mib_queue(struct dl_prio_queue *prio_queue)
{
	if (!prio_queue)
		return;
	prio_queue->enq_cnt = 0;
	prio_queue->deq_cnt = 0;
	prio_queue->timeout_cnt = 0;
	prio_queue->discard_cnt = 0;
	prio_queue->drop_overflow_cnt = 0;
}
static void pflow_reset_mib(int peer_id, int tid)
{
	int i = 0;
	struct dl_prio_queue *prio_queue;
	if (peer_id == -1) {
		prio_queue = (struct dl_prio_queue *)
			MPE_TX_ADDR(DLTX_PRIO_SOFT_QUEUE_DMA_DESC_CTXT);
		for (i = 0; i < PRIO_Q_SIZE; i++) {
			pflow_reset_mib_queue(prio_queue);
			prio_queue++;
		}
	} else {
		prio_queue = (struct dl_prio_queue *)
			MPE_TX_ADDR(DLTX_PRIO_SOFT_QUEUE_DMA_DESC_CTXT);
		prio_queue += (peer_id * DL_DMA_TID_NUM);
		if (tid == -1) {
			for (i = 0; i < DL_DMA_TID_NUM; i++) {
				pflow_reset_mib_queue(prio_queue);
				prio_queue++;
			}
		} else {
			prio_queue += tid;
			pflow_reset_mib_queue(prio_queue);
		}
	}
}
static ssize_t proc_write_pflow(
	struct file *file,
	const char __user *buf,
	size_t count,
	loff_t *data
	)
{
	char *p1, *p2;
	int len;
	int colon;
	unsigned long *p = NULL;
	char local_buf[900];


	len = sizeof(local_buf) < count ? sizeof(local_buf) - 1 : count;
	len = len - copy_from_user(local_buf, buf, len);
	local_buf[len] = 0;

	p1 = local_buf;
	p2 = NULL;
	colon = 1;
	while (get_token(&p1, &p2, &len, &colon)) {
		if (stricmp(p1, "mode") == 0)
			break;
		if (stricmp(p1, "mac") == 0)
			break;
		if (stricmp(p1, "reset") == 0)
			break;
		if (stricmp(p1, "peer_map") == 0)
			break;
		p1 = p2;
		colon = 1;
	}
	/* set WDS MAC or DirectLink working mode */
	if (*p1 == 'm') {
		if (*(p1+1) == 'o') {
			struct _dl_ce4_pflow_control *ctrl;
			ctrl = (struct _dl_ce4_pflow_control *)
				MPE_TX_ADDR(DLTX_CFG_CTXT_CE4_PFLOW_CTRL);
			ignore_space(&p2, &len);
			if (p2[0] == 's' && p2[1] == 'w' &&
				(p2[2] == ' ' || p2[2] == '\t')) {
			} else
				p = (unsigned long *)get_number(&p2, &len, 1);

			if (p == 0) {
				pr_info("Set mode to PUSH mode\n");
				ctrl->pflow_ctrl_mode = DL_TX_MODE_PUSH_NO_CLASSIFY;
			} else {
				pr_info("Set mode to PULL mode\n");
				ctrl->pflow_ctrl_mode = DL_TX_MODE_PUSH_PULL;
			}
		} else if (*(p1 + 1) == 'a') {
			uint8_t mac_addr[PPA_ETH_ALEN];
			uint16_t id, j;
			ignore_space(&p2, &len);
			memset(mac_addr, 0, PPA_ETH_ALEN);
			for (j = 0; j < 6; j++) {
				int temp_len = 2;
				mac_addr[j] = (uint8_t)get_number(
					&p2,
					&temp_len,
					1);
				p2 += 1;
			}
			ignore_space(&p2, &len);
			id = (uint16_t)get_number(&p2, &len, 1);
			ppa_dl_qca_set_wds_peer_cfg(NULL, id, 0, PPA_WLAN_ADD_PEER_ID, mac_addr);
			update_bridging_entry(mac_addr, id);
		}
	}
	/* print out peer map */
	if (*p1 == 'p') {
		struct peermap_t *pmap;
		int i, j;
		pmap = (struct peermap_t *)
			MPE_TX_ADDR(DLTX_PEER_MAP_TABLE);
		/* Print out the peer map table */
		pr_info("Byte control address[0x%p]\n",
			&pmap->byte_cnt[0]);
		pr_info("TID address[0x%p]\n",
					&pmap->tid_peermap[0]);

		pr_info("Sequence number[%x]\n", pmap->seq);
		for (j = 0; j < DL_TX_PFLOW_CTRL_MAX_TIDS; j++) {
			pr_info("\tTID[%d]\n", j);
			for (i = 0; i < MAX_PEER_MAP_WORD; i++) {
				int dword_index = i / 32;
				int dword_offset = i % 32;
				if ((pmap->tid_peermap[j][dword_index] >> dword_offset) & 0x1) {
					unsigned char *byte_count;
					int dindex = i / NUM_PEER_BYTE_CNTS_IN_WORD;
					int doffset = 3 - i % NUM_PEER_BYTE_CNTS_IN_WORD;
					byte_count =
						(unsigned char *)(&pmap->byte_cnt[j][dindex])
						+ doffset;

					pr_info("\t\tPeer[%d]: [%d]\n",
						i,
						*byte_count);
				}
			}
		}
	}
	/* reset mib */
	if (*p1 == 'r') {
		int peer_id = -1;
		int tid = -1;
		/* get peer id */
		ignore_space(&p2, &len);
		if (p2) {
			peer_id = get_number(&p2, &len, 0);
			/* get tid */
			ignore_space(&p2, &len);
			if (p2)
				tid = get_number(&p2, &len, 0);
		}
		pflow_reset_mib(peer_id, tid);
	}

	return count;
}
static struct file_operations g_proc_file_pflow_seq_fops = {
	.owner	= THIS_MODULE,
	.open	= proc_read_pflow_seq_open,
	.read	= seq_read,
	.write	= proc_write_pflow,
	.llseek	= seq_lseek,
	.release	= single_release,
};
#endif
int dtlk_switch_parser(void)
{
	dltx_cfg_global_t *mpe_dl_tx_cfg_global =
		(dltx_cfg_global_t *)MPE_TX_ADDR(DLTX_CFG_GLOBAL_OFFSET);
	return mpe_dl_tx_cfg_global->switch_parser_flag;
}

static int proc_read_parser(
	struct seq_file *seq,
	void *v
	)
{
	dltx_cfg_global_t *mpe_dl_tx_cfg_global =
		(dltx_cfg_global_t *)MPE_TX_ADDR(DLTX_CFG_GLOBAL_OFFSET);
	seq_printf(seq,
		"Switch flag[%d]\n", mpe_dl_tx_cfg_global->switch_parser_flag);
	seq_printf(seq, "Current switch parser: %s\n",
		mpe_dl_tx_cfg_global->switch_parser_flag
		== 1 ? "Enable" : "Disable");
	return 0;
}
static int proc_read_parser_seq_open(
	struct inode *inode,
	struct file *file
	)
{
	return single_open(file, proc_read_parser, NULL);
}

static ssize_t proc_write_parser(
	 struct file *file,
	 const char __user *buf,
	 size_t count,
	 loff_t *data
	 )
{
	char *p1, *p2;
	int len;
	int colon;
	char local_buf[900];

	dltx_cfg_global_t *mpe_dl_tx_cfg_global =
			(dltx_cfg_global_t *)MPE_TX_ADDR(DLTX_CFG_GLOBAL_OFFSET);
	len = sizeof(local_buf) < count ? sizeof(local_buf) - 1 : count;
	len = len - copy_from_user(local_buf, buf, len);
	local_buf[len] = 0;
	p1 = local_buf;
	p2 = NULL;
	colon = 1;
	while (get_token(&p1, &p2, &len, &colon)) {
		if (stricmp(p1, "disable") == 0 ||
			stricmp(p1, "enable") == 0)
			break;
		p1 = p2;
		colon = 1;
	}

	if (*p1 == 'd') {
		printk("%s: Disable switch parser\n", __func__);
		mpe_dl_tx_cfg_global->switch_parser_flag = 0;
	} else {
		printk("%s: Enable switch parser\n", __func__);
		mpe_dl_tx_cfg_global->switch_parser_flag = 1;
	}
	return count;
}

static struct file_operations g_proc_file_parser_seq_fops = {
	.owner  = THIS_MODULE,
	.open	 = proc_read_parser_seq_open,
	.read	 = seq_read,
	.write  = proc_write_parser,
	.llseek = seq_lseek,
	.release	 = single_release,
};




 /* Functions and structure support proc/dtlk/reg */
static int proc_read_dtlk_reg(
	struct seq_file *seq,
	void *v
	)
{
	volatile dlrx_cfg_vap2int_map1_t *vap2int_map1 =
		(dlrx_cfg_vap2int_map1_t *)DLRX_CFG_VAP2INT_MAP1_BASE;
	volatile dlrx_cfg_vap2int_map2_t *vap2int_map2 =
		(dlrx_cfg_vap2int_map2_t *)DLRX_CFG_VAP2INT_MAP2_BASE;
	seq_printf(seq, "Firmware registers information\n");
	seq_printf(seq, "			CFG_VAP2INT_MAP1: %p\n", vap2int_map1);
	seq_printf(seq, "	VAP0: %d\n", vap2int_map1->vap0);
	seq_printf(seq, "	VAP1: %d\n", vap2int_map1->vap1);
	seq_printf(seq, "	VAP2: %d\n", vap2int_map1->vap2);
	seq_printf(seq, "	VAP3: %d\n", vap2int_map1->vap3);
	seq_printf(seq, "	VAP4: %d\n", vap2int_map1->vap4);
	seq_printf(seq, "	VAP5: %d\n", vap2int_map1->vap5);
	seq_printf(seq, "	VAP6: %d\n", vap2int_map1->vap6);
	seq_printf(seq, "	VAP7: %d\n", vap2int_map1->vap7);
	seq_printf(seq, "			CFG_VAP2INT_MAP2: %p\n", vap2int_map2);
	seq_printf(seq, "	VAP8: %d\n", vap2int_map2->vap8);
	seq_printf(seq, "	VAP9: %d\n", vap2int_map2->vap9);
	seq_printf(seq, "	VAP10: %d\n", vap2int_map2->vap10);
	seq_printf(seq, "	VAP11: %d\n", vap2int_map2->vap11);
	seq_printf(seq, "	VAP12: %d\n", vap2int_map2->vap12);
	seq_printf(seq, "	VAP13: %d\n", vap2int_map2->vap13);
	seq_printf(seq, "	VAP14: %d\n", vap2int_map2->vap14);
	seq_printf(seq, "	VAP15: %d\n", vap2int_map2->vap15);

	return 0;
}

static int proc_read_dtlk_reg_seq_open(
	struct inode *inode,
	struct file *file
	)
{
	return single_open(file, proc_read_dtlk_reg, NULL);
}



static struct file_operations g_proc_file_reg_seq_fops = {
.owner = THIS_MODULE,
.open = proc_read_dtlk_reg_seq_open,
.read = seq_read,
.llseek = seq_lseek,
.release = single_release
};

 /* Functions and structure support proc/dtlk/ver */
static int proc_read_dtlk_ver(
	struct seq_file *seq,
	void *v
	)
{
	dltx_cfg_global_t *mpe_dl_tx_cfg_global =
				(dltx_cfg_global_t *)MPE_TX_ADDR(DLTX_CFG_GLOBAL_OFFSET);

	seq_printf(seq, "DirectLink driver information: \n");
	seq_printf(seq, "	 Version: %d.%d.%d\n",
		DRV_MAJOR,
		DRV_MID,
		DRV_MINOR
		);
	seq_printf(seq, "DLRX Firmware information: \n");
	seq_printf(seq, "    Version:%08x\n", DRE_FW_VERSION);
	seq_printf(seq, "    Feature:%08x\n", DRE_FW_FEATURE);
	seq_printf(seq, "DLTX Firmware information: \n");
	seq_printf(seq, "	 Version:%08x\n", mpe_dl_tx_cfg_global->fw_ver_id);
	seq_printf(seq, "	 Feature:%08x\n", mpe_dl_tx_cfg_global->fw_feature);
#if defined(CONFIG_ACCL_11AC_CS2)
	seq_printf(seq, "Support CS2\n");
#endif
	return 0;
}

static int proc_read_dtlk_ver_seq_open(
	struct inode *inode,
	struct file *file
	)
{
	return single_open(file, proc_read_dtlk_ver, NULL);
}



static struct file_operations g_proc_file_ver_seq_fops = {
	.owner		= THIS_MODULE,
	.open		= proc_read_dtlk_ver_seq_open,
	.read		= seq_read,
	.llseek 	= seq_lseek,
	.release	= single_release
};
/* Functions and structure support proc/dtlk/mib */
static int proc_read_dtlk_mib(struct seq_file *seq, void *v)
{
	int i = 0;
	uint64_t general_rx_drops = 0;
	uint64_t general_rx_errors = 0;
	uint64_t general_tx_drops = 0;

	for (i = 0; i < MAX_DTLK_NUM; i++) {
		struct net_device *vap_dev = dtlk_dev_from_vapid(i);
		if (vap_dev) {
			/* TODO: implement function to get mib from vap */
			volatile vap_data_mib_t *vap_mib_rx =
				(vap_data_mib_t *)DLRX_VAP_MIB_BASE(i);
			dltx_vap_data_mib_t *vap_mib_tx =
				(dltx_vap_data_mib_t *)MPE_TX_ADDR(DLTX_VAP_DATA_MIB_OFFSET(i));
			uint64_t rxpdu =
				(uint64_t)vap_mib_rx->rx_rcv_pdu_low +
				(((uint64_t)vap_mib_rx->rx_rcv_pdu_high) << 32);
			uint64_t rxbytes =
				(uint64_t)vap_mib_rx->rx_rcv_bytes_low +
				(((uint64_t)vap_mib_rx->rx_rcv_bytes_high) << 32);
			uint64_t txdrops =
				(uint64_t)vap_mib_tx->txdrop_low +
				(((uint64_t)vap_mib_tx->txdrop_high) << 32);
			uint64_t rxerros =
				((uint64_t)vap_mib_rx->rx_pn_bytes_low +
				(((uint64_t)vap_mib_rx->rx_pn_bytes_high) << 32)) +
				((uint64_t)vap_mib_rx->rx_discard_pdu_low +
				(((uint64_t)vap_mib_rx->rx_discard_pdu_high) << 32));
			uint64_t rxdrops = (uint64_t)vap_mib_rx->rx_drop_pdu_low +
				(((uint64_t)vap_mib_rx->rx_drop_pdu_high) << 32);
			uint64_t txpdu = (uint64_t)vap_mib_tx->txpdu_low +
				(((uint64_t)vap_mib_tx->txpdu_high) << 32);
			uint64_t txbytes = (uint64_t)vap_mib_tx->txbytes_low +
				(((uint64_t)vap_mib_tx->txbytes_high) << 32);
			seq_printf(seq, "VAP-Id = %d\n", i);
			seq_printf(seq, "  VAP-Name = %s\n", vap_dev->name);
			seq_printf(seq, "   tx_pkts    = %llu\n", txpdu);
			seq_printf(seq, "   tx_bytes   = %llu\n", txbytes);
			seq_printf(seq, "   tx_drops   = %llu\n", txdrops);
			seq_printf(seq, "   rx_pkts    = %llu\n", rxpdu);
			seq_printf(seq, "   rx_bytes   = %llu\n", rxbytes);
			seq_printf(seq, "   rx_error_pkts = %llu\n", rxerros);
			seq_printf(seq, "   rx_drops_pkts = %llu\n", rxdrops);
			seq_printf(seq, "\n");
			general_tx_drops += txdrops;
			general_rx_drops += rxdrops;
			general_rx_errors += rxerros;
		} else {
			seq_printf(seq, "VAP-Id = %d\n", i);
			seq_printf(seq, "  VAP-Name = Unassigned\n");
		}
	}
	seq_printf(seq, "\n");
	seq_printf(seq, "General RX Drops = %10llu General RX Errors = %10llu\n",
		general_rx_drops,
		general_rx_errors
		);
	seq_printf(seq, "General TX Drops = %10llu\n", general_tx_drops);
	return 0;
}

static int proc_read_dtlk_mib_seq_open(
	struct inode *inode,
	struct file *file
	)
{
	return single_open(file, proc_read_dtlk_mib, NULL);
}

static ssize_t proc_write_dtlk_mib_seq(
	struct file *file,
	const char __user *buf,
	size_t count,
	loff_t *data
	)
{
	int len;
	char str[64];
	char *p;
	int space_len = 0;
	int i;
	uint32_t vap_mask = 0;

	memset(str, 0, 64);
	len = min(count, (size_t)((unsigned long)sizeof(str) - 1));
	len -= copy_from_user(str, buf, len);
	while (len && str[len - 1] <= ' ')
		len--;
	str[len] = 0;
	for (p = str; *p && *p <= ' '; p++, len--)
		;
	if (!*p)
		return count;
	/* first, looking for VAP from user input  */

	p = get_next_argument(p, &space_len);
	len -= space_len;
	if (p == NULL) {
		dtlk_debug(
		DBG_PROC,
		"%s: Invalid input\n",
		__func__
		);
		return count;
	}
	/* get vap id */
	if (strincmp(p, "reset", strlen("reset")) == 0) {
		p += strlen("reset");
		len -= strlen("reset");

		while (p && *p) {
			int vap_id = 0;
			p = get_next_argument(p, &space_len);
			if (!p)
				break;

			len -= space_len;
			if (strincmp(p, "all", strlen("all")) == 0) {
				/* mask all */
				vap_mask = 0xff;
				break;
			} else {
				if (*p >= '0' && *p <= '9') {
					sscanf(p, "%d", &vap_id);
					if (vap_id >= MAX_VAP_NUM) {
						dtlk_debug(
							DBG_PROC,
							"%s: invalid VAP id [%d]\n",
							__func__,
							vap_id);
						break;/* while */
					}
					vap_mask |= 1 << vap_id;
					if (vap_id > 9) {
						len -= 2;
						p += 2;
					} else {
						len -= 1;
						p += 1;
					}
				} else
					break;
			}
			if (!p)
				break;
			p += 1;
			len -= 1;
		}
	} else if (strincmp(p, "help", 4) == 0 || *p == '?') {
		dtlk_debug(DBG_PROC, "echo reset <0 1 2 ...> > /proc/%s/wifi_mib\n",
			DIRECTLINK_PROC_DIR);
		dtlk_debug(DBG_PROC, "echo reset all > /proc/%s/wifi_mib\n",
			DIRECTLINK_PROC_DIR);
		return count;
	}

	dtlk_debug(
		DBG_PROC,
		"%s: Going to clear: 0x%08x\n",
		__func__,
		vap_mask
		);
	/* secondly, clear vap mib counter */
	if (vap_mask == 0xffffffff) {
		dre_dl_reset_fn_t dre_dl_reset_fn;
		uint32_t *ptrTxMib = (void *)DTLK_RX_ADDR(__D6_PER_VAP_MIB_BASE);
		/* clear rx mib counter
		* resetMib->allreq = 1;
		* clear tx mib counter
		*/
		memset(ptrTxMib, 0x0, sizeof(mib_table_t)*MAX_VAP_NUM);
		dre_dl_reset_fn = g_dre_fnset.dre_dl_reset_fn;
		if (likely(dre_dl_reset_fn))
			dre_dl_reset_fn(DRE_RESET_MIB, 0xff);
		else
			dtlk_debug(DBG_ERR, "%s: Function DRE_RESET_MIB is not registered!\n", __func__);
	} else {
		dre_dl_reset_fn_t dre_dl_reset_fn;
		dre_dl_reset_fn = g_dre_fnset.dre_dl_reset_fn;
		for (i = 0; i < MAX_VAP_NUM; i++) {
			if ((1 << i) & vap_mask) {
				uint32_t *ptr_tx_mib =
					(void *)DTLK_RX_ADDR(__D6_PER_VAP_MIB_BASE) +
					i*sizeof(mib_table_t);
				dltx_vap_data_mib_t *vap_mib_tx =
					(dltx_vap_data_mib_t *)MPE_TX_ADDR(DLTX_VAP_DATA_MIB_OFFSET(i));
				memset(ptr_tx_mib, 0x0, sizeof(mib_table_t));
				if (likely(dre_dl_reset_fn))
					dre_dl_reset_fn(DRE_RESET_MIB, i);
				else
					dtlk_debug(DBG_ERR, "%s:DRE_RESET_MIB is not registered!\n",
						__func__
						);
				memset((void *)vap_mib_tx,
					0,
					sizeof(dltx_vap_data_mib_t)
				);
			}
		}
	}
	return count;

}


static struct file_operations g_proc_file_mib_seq_fops = {
.owner = THIS_MODULE,
.open = proc_read_dtlk_mib_seq_open,
.read = seq_read,
.write = proc_write_dtlk_mib_seq,
.llseek = seq_lseek,
.release = single_release
};
/** ####################################
 *			  Local Function
 * ####################################
 */

/* Functions and structure support proc/dtlk/dbg*/
static int proc_read_dtlk_dbg(
	struct seq_file *seq,
	void *v
	)
{
	int i;
	/* skip -1 */
	for (i = 0; i < NUM_ENTITY(dtlk_dbg_enable_mask_str) - 1; i++)
		seq_printf(seq, "%-10s(%-40s):		  %-5s\n",
			dtlk_dbg_enable_mask_str[i].cmd,
			dtlk_dbg_enable_mask_str[i].description,
			(g_dtlk_dbg_enable & dtlk_dbg_enable_mask_str[i].flag) ? "enabled" : "disabled"
			);

	return 0;

}

static int proc_read_dtlk_dbg_seq_open(
	struct inode *inode,
	struct file *file
	)
{
	return single_open(file, proc_read_dtlk_dbg, NULL);
}

static ssize_t proc_write_dtlk_dbg_seq(
	struct file *file,
	const char __user *buf,
	size_t count, loff_t *data
	)
{
	int len;
	char str[64];
	char *p;
	int f_enable = 0;
	int f_dtlk = 0;
	int i;
	int space_len = 0;
	dltx_cfg_global_t *dltx_cfg_global =
		(dltx_cfg_global_t *)MPE_TX_ADDR(DLTX_CFG_GLOBAL_OFFSET);
	memset(str, 0, 64);
	len = min(count, (size_t)((unsigned long)sizeof(str) - 1));
	len -= copy_from_user(str, buf, len);
	while (len && str[len - 1] <= ' ')
		len--;
	str[len] = 0;
	for (p = str; *p && *p <= ' '; p++, len--)
		;
	if (!*p)
		return count;

	if (strincmp(p, "dltx", 4) == 0) {
		p += 4;
		len -= 4;
		f_dtlk = 1;
	} else if (strincmp(p, "enable", 6) == 0) {
		p += 6;
		len -= 6;
		f_enable = 1;
	} else if (strincmp(p, "disable", 7) == 0) {
		p += 7;
		len -= 7;
		f_enable = -1;
	} else if (strincmp(p, "help", 4) == 0 || *p == '?') {
		dtlk_debug(DBG_PRINT, "echo <enable/disable/dltx> [");
		for (i = 0; i < NUM_ENTITY(dtlk_dbg_enable_mask_str); i++)
			dtlk_debug(DBG_PRINT,
				"%s/", dtlk_dbg_enable_mask_str[i].cmd);
		dtlk_debug(DBG_PRINT,
			"] > /proc/%s/dbg\n", DIRECTLINK_PROC_DIR);
		return count;
	}

	p = get_next_argument(p, &space_len);
	if (p == NULL) {
		dtlk_debug(DBG_ERR, "NULL pointer\n");
		return count;
	}
	len -= space_len;

	if (f_enable) {
		if ((len <= 0) || (p[0] >= '0' && p[1] <= '9')) {
			if (f_enable > 0)
				g_dtlk_dbg_enable |= (~DTLK_DBG_ENA);
			else
				g_dtlk_dbg_enable &= DTLK_DBG_ENA;
		} else {
			do {
				for (i = 0; i < NUM_ENTITY(dtlk_dbg_enable_mask_str); i++) {
					if (dtlk_dbg_enable_mask_str[i].cmd == NULL)
						break;
					if (strlen(p) < strlen(dtlk_dbg_enable_mask_str[i].cmd))
						continue;
					if (strincmp(p,
						dtlk_dbg_enable_mask_str[i].cmd,
						strlen(dtlk_dbg_enable_mask_str[i].cmd)) == 0) {
						if (f_enable > 0)
							g_dtlk_dbg_enable |= dtlk_dbg_enable_mask_str[i].flag;
						else
							g_dtlk_dbg_enable &= ~dtlk_dbg_enable_mask_str[i].flag;
						/* skip one blank */
						p += strlen(dtlk_dbg_enable_mask_str[i].cmd);
						p = get_next_argument(p, &space_len);
						if (p == NULL)
							break;

						/*skip one blank. len maybe negative
						* now if there is no other parameters
						*/
						len -= strlen(dtlk_dbg_enable_mask_str[i].cmd) + space_len;
						break;
					}
				}
			} while (i < NUM_ENTITY(dtlk_dbg_enable_mask_str) && p);
		}
	}
	if (f_dtlk) {
		/* enable debug in DLTX */
		dtlk_debug(DBG_PROC, "DEBUG: enable DLTX debug\n");
		dltx_cfg_global->debug_print_enable = 1;
	} else {
		dtlk_debug(DBG_PROC, "DEBUG: disable DLTX debug\n");
		dltx_cfg_global->debug_print_enable = 0;
	}

	return count;

}


static struct file_operations g_proc_file_dbg_seq_fops = {
	.owner		= THIS_MODULE,
	.open		= proc_read_dtlk_dbg_seq_open,
	.read		= seq_read,
	.write		= proc_write_dtlk_dbg_seq,
	.llseek 	= seq_lseek,
	.release	= single_release
};
static void print_m2c(struct seq_file *seq, unsigned int extension)
{
	struct _dl_mcast_group_table *dl_m2c_group_tbl;
	int i, j;
	if (extension == 0)
		dl_m2c_group_tbl =
			(struct _dl_mcast_group_table *)MPE_TX_ADDR(DLTX_CFG_CTXT_M2C_GROUP_TABLE);
	else
		dl_m2c_group_tbl =
			(struct _dl_mcast_group_table *)MPE_TX_ADDR(DLTX_CFG_CTXT_M2C_GROUP_EXT_TABLE);
	dtlk_debug(DBG_PROC, "%s\n", __func__);
	for (i = 0; i < MAX_MCAST_GROUP; i++) {
		if (dl_m2c_group_tbl->valid) {
			seq_printf(seq, "Group: %d\n", i);
			for (j = 0; j < MAX_PEER_NUM; j++) {
			int byte_off = j / 32;
			int bit_off = j % 32;
			if (dl_m2c_group_tbl->bitmap[byte_off] & (1 << bit_off)) {
				struct _dl_peer_mac_mapping_table *dl_m2c_peer_tbl;
				if (extension == 0)
					dl_m2c_peer_tbl = (struct _dl_peer_mac_mapping_table *)MPE_TX_ADDR(DLTX_CFG_CTXT_M2C_PEER_TABLE);
				else
					dl_m2c_peer_tbl = (struct _dl_peer_mac_mapping_table *)MPE_TX_ADDR(DLTX_CFG_CTXT_M2C_PEER_EXT_TABLE);
				dl_m2c_peer_tbl += j;
				seq_printf(seq,	"\tPeer: %d[%x:%x:%x:%x:%x:%x]\n", i,
					dl_m2c_peer_tbl->mac5,
					dl_m2c_peer_tbl->mac4,
					dl_m2c_peer_tbl->mac3,
					dl_m2c_peer_tbl->mac2,
					dl_m2c_peer_tbl->mac1,
					dl_m2c_peer_tbl->mac0
					);
			}
			}
		}
		dl_m2c_group_tbl++;
	}
}
static int proc_read_m2c(
	struct seq_file *seq,
	void *v
	)
{
	print_m2c(seq, 0);
	print_m2c(seq, 1);
	return 0;
}
static int proc_read_m2c_seq_open(
	struct inode *inode,
	struct file *file
	)
{
	return single_open(file, proc_read_m2c, NULL);
}

static ssize_t proc_write_m2c(
	 struct file *file,
	 const char __user *buf,
	 size_t count,
	 loff_t *data
	 )
{
	return count;
}

static struct file_operations g_proc_file_m2c_seq_fops = {
	.owner  = THIS_MODULE,
	.open	 = proc_read_m2c_seq_open,
	.read	 = seq_read,
	.write  = proc_write_m2c,
	.llseek = seq_lseek,
	.release	 = single_release,
};

/**
  * proc_file_create - Create proc files for driver
  *
  *
  * All proc files will be located in /proc/dtlk. Called by
  * dlrx_drv_init
  * Return: 0 : success. Others: fail
  */
static INLINE int proc_file_create(void)
{
	struct proc_dir_entry *res;
	int ret = 0;

	if (g_dtlk_proc_dir) {
		dtlk_debug(DBG_ERR, "More than one DirectLink device found!\n");
		return -EEXIST;
	}

	/* create parent proc directory */
	g_dtlk_proc_dir = proc_mkdir(DIRECTLINK_PROC_DIR, NULL);
	/* create mib */
	res  = proc_create("wifi_mib",
		S_IRUGO|S_IWUSR,
		g_dtlk_proc_dir,
		&g_proc_file_mib_seq_fops
		);

	if (!res) {
		dtlk_debug(DBG_ERR, "Failed to create mib\n");
		return -ENODEV;
	}

	/* create wifi_port */
	res = proc_create("wifi_port",
		S_IRUGO,
		g_dtlk_proc_dir,
		&g_proc_file_wifi_port_seq_fops
		);

	if (!res) {
		dtlk_debug(DBG_ERR, "Failed to create wifi_port\n");
		return -ENODEV;
	}

	/* create peer_id */
	res  = proc_create("peer_id",
		S_IRUGO,
		g_dtlk_proc_dir,
		&g_proc_file_peer_id_seq_fops
		);

	if (!res) {
		dtlk_debug(DBG_ERR, "Failed to create peer_id\n");
		return -ENODEV;
	}

	/* create peer_to_vap */
	res = proc_create("peer_to_vap",
		S_IRUGO,
		g_dtlk_proc_dir,
		&g_proc_file_peer_to_vap_seq_fops
		);

	if (!res) {
		dtlk_debug(DBG_ERR, "Failed to create peer_to_vap\n");
		return -ENODEV;
	}
#if defined(CONFIG_ACCL_11AC_CS2)
	/* create peer_to_vap */
	res = proc_create("pflow",
		S_IRUGO,
		g_dtlk_proc_dir,
		&g_proc_file_pflow_seq_fops
		);

	if (!res) {
		dtlk_debug(DBG_ERR, "Failed to create pflow\n");
		return -ENODEV;
	}
	/* create peer_to_vap */
	res = proc_create("uptime",
		S_IRUGO,
		g_dtlk_proc_dir,
		&g_proc_file_uptime_seq_fops
		);

	if (!res) {
		dtlk_debug(DBG_ERR, "Failed to create uptime\n");
		return -ENODEV;
	}
#endif

	/* create dbg */
	res = proc_create("dbg",
		S_IRUGO|S_IWUSR,
		g_dtlk_proc_dir,
		&g_proc_file_dbg_seq_fops
		);

	if (!res) {
		dtlk_debug(DBG_ERR, "Failed to create dbg\n");
		ret = -ENODEV;
	}
	/* create mem */
	res = proc_create("mem",
		S_IRUGO|S_IWUSR,
		g_dtlk_proc_dir,
		&g_proc_file_mem_seq_fops
		);

	if (!res) {
		dtlk_debug(DBG_ERR, "Failed to create dbg\n");
		ret = -ENODEV;
	}

	/* create ver */
	res  = proc_create("ver",
		S_IRUGO,
		g_dtlk_proc_dir,
		&g_proc_file_ver_seq_fops
		);

	if (!res) {
		dtlk_debug(DBG_ERR, "Failed to create version\n");
		ret = -ENODEV;
	}

	/* create reg */
	res  = proc_create("reg",
		S_IRUGO,
		g_dtlk_proc_dir,
		&g_proc_file_reg_seq_fops
		);

	if (!res) {
		dtlk_debug(DBG_ERR, "Failed to create register\n");
		ret = -ENODEV;
	}

	/* create parser */
	res  = proc_create("parser",
		S_IRUGO,
		g_dtlk_proc_dir,
		&g_proc_file_parser_seq_fops
	);

	if (!res) {
		dtlk_debug(DBG_ERR, "Failed to create register\n");
		ret = -ENODEV;
	}

	/* create parser */
	res  = proc_create("m2c",
		S_IRUGO,
		g_dtlk_proc_dir,
		&g_proc_file_m2c_seq_fops
	);

	if (!res) {
		dtlk_debug(DBG_ERR, "Failed to create register\n");
		ret = -ENODEV;
	}

	return ret;
}

/**
  * proc_file_create - Delete all proc files created by this driver
  *
  *
  * Delete all proc files in /proc/dtlk.
  * Called by dlrx_drv_exit.
  */
static INLINE void proc_file_delete(void)
{
	/* delete reg  entry */
	remove_proc_entry("reg", g_dtlk_proc_dir);
	/* delete ver  entry */
	remove_proc_entry("ver", g_dtlk_proc_dir);
	/* delete mib entry */
	remove_proc_entry("wifi_mib", g_dtlk_proc_dir);
	/* delete dbg */
	remove_proc_entry("dbg", g_dtlk_proc_dir);

	/* delete wifi_port */
	remove_proc_entry("wifi_port", g_dtlk_proc_dir);

	/* delete peer_id */
	remove_proc_entry("peer_id", g_dtlk_proc_dir);

	/* delete peer_to_vap */
	remove_proc_entry("peer_to_vap", g_dtlk_proc_dir);
#if defined(CONFIG_ACCL_11AC_CS2)
	/* delete pflow */
	remove_proc_entry("pflow", g_dtlk_proc_dir);
	/* delete uptime */
	remove_proc_entry("uptime", g_dtlk_proc_dir);
#endif
	/* delete mem */
	remove_proc_entry("mem", g_dtlk_proc_dir);

	/* delete parser */
	remove_proc_entry("parser", g_dtlk_proc_dir);
	/* delete m2c */
	remove_proc_entry("m2c", g_dtlk_proc_dir);

	/* delete parent proc directory */
	remove_proc_entry(DIRECTLINK_PROC_DIR, NULL);

	g_dtlk_proc_dir = NULL;
}
/**
  * dtlk_variables_api_init - Module entry function
  * Init control resources
  **/
void dtlk_variables_api_init(void){
	int i, j;
	for (i = 0; i < MAX_RADIO_NUM; i++) {
		struct ppe_radio_map *radio = &g_ppe_radio[i];
		radio->flags = 0;
		radio->dl_sub_if.port_id = -1;
		radio->dl_sub_if.subif = -1;
		for (j = 0; j < MAX_DTLK_NUM; j++) {
			struct ppe_dtlk_map *dtlk =
				&(radio->g_ppe_dtlk_data[j]);
			memset(&radio->g_ppe_dtlk_data[j],
				0,
				sizeof(struct ppe_dtlk_map));
			dtlk->dev = NULL;
			dtlk->dl_sub_if.port_id = -1;
			dtlk->dl_sub_if.subif = -1;
			dtlk->owner = NULL;
			dtlk->vap_id = -1;
		}
	}
}
/**
  * dl_init_dltx_memory - Reset DLTX CE4 memory to zero
  * These memories are used by MPE TX FW
  **/
static void dl_init_dltx_memory(struct dl_buf_info dl_mem)
{
#if defined(CONFIG_ACCL_11AC_CS2)
	int i = 0;
#endif
	if (dl_mem.tx_cfg_ctxt_buf_size && dl_mem.tx_cfg_ctxt_buf_base) {
		memset((void *)(dl_mem.tx_cfg_ctxt_buf_base),
			0, dl_mem.tx_cfg_ctxt_buf_size);
		ppa_dl_dre_dma_writeback(dl_mem.tx_cfg_ctxt_buf_base,
			dl_mem.tx_cfg_ctxt_buf_size);
	}
	if (dl_mem.rx_cfg_ctxt_buf_size && dl_mem.rx_cfg_ctxt_buf_base) {
		memset((void *)(dl_mem.rx_cfg_ctxt_buf_base),
			0, dl_mem.rx_cfg_ctxt_buf_size);
		ppa_dl_dre_dma_writeback(dl_mem.rx_cfg_ctxt_buf_base,
			dl_mem.rx_cfg_ctxt_buf_size);
	}
	if (dl_mem.rx_msgbuf_size && dl_mem.rx_msgbuf_base) {
		memset((void *)(dl_mem.rx_msgbuf_base),
			0, dl_mem.rx_msgbuf_size);
		ppa_dl_dre_dma_writeback(dl_mem.rx_msgbuf_base,
			dl_mem.rx_msgbuf_size);
	}
	if (dl_mem.uncached_addr_size && dl_mem.uncached_addr_base) {
		memset((void *)dl_mem.uncached_addr_base,
			0, dl_mem.uncached_addr_size);
		ppa_dl_dre_dma_writeback(dl_mem.uncached_addr_base,
			dl_mem.uncached_addr_size);
	}
	if (dl_mem.comm_buf_size && dl_mem.comm_buf_base) {
		memset((void *)(dl_mem.comm_buf_base),
			0, dl_mem.comm_buf_size);
		ppa_dl_dre_dma_writeback(dl_mem.comm_buf_base,
			dl_mem.comm_buf_size);
	}
#if defined(CONFIG_ACCL_11AC_CS2)
	if (dl_mem.comm_buf_size && dl_mem.dl_dma_queue_base) {
		memset((void *)(dl_mem.dl_dma_queue_base),
			0, dl_mem.dl_dma_queue_size);
		ppa_dl_dre_dma_writeback(dl_mem.dl_dma_queue_base,
			dl_mem.dl_dma_queue_size);
	}
	for (i = 0; i < DL_CS2_BUFFER_CHUNK_NUM; i++) {
		if (dl_mem.DlBufManPtrs[i])
			memset((void *)dl_mem.DlBufManPtrs[i],
				0,
			DL_CS2_BUFFER_CHUNK_SIZE);
	}
#endif
}



#if defined(CONFIG_ACCL_11AC_CS2)
int32_t dl_set_dscp_tid(void *cfg);
int32_t dl_get_dscp_tid(void);


int32_t dl_set_dscp_tid(void *cfg)
{
	GSW_API_HANDLE gswl_handle = 0;
	GSW_QoS_DSCP_ClassCfg_t *qos_dscp_class_set;

	int32_t ret = 0;

	gswl_handle = gsw_api_kopen("/dev/switch_api/1");

	qos_dscp_class_set = (GSW_QoS_DSCP_ClassCfg_t *)cfg;
	ret = gsw_api_kioctl(gswl_handle,
		GSW_QOS_DSCP_CLASS_SET,
		(u32)qos_dscp_class_set
	);

	return ret;
}



int32_t dl_get_dscp_tid()
{

	GSW_QoS_DSCP_ClassCfg_t DSCP_ClassCfg;
	int i;
	int32_t ret = 0;
	GSW_API_HANDLE gswl_handle = 0;

	gswl_handle = gsw_api_kopen("/dev/switch_api/1");

	memset(&DSCP_ClassCfg, 0x00, sizeof(DSCP_ClassCfg));

	ret = gsw_api_kioctl(
		gswl_handle,
		GSW_QOS_DSCP_CLASS_GET,
		(u32)&DSCP_ClassCfg
	);

	for (i = 0; i < 64; i++)
		pr_info("\tnTrafficClass[%d] = %d\n",
			i,
			DSCP_ClassCfg.nTrafficClass[i]
		);

	return ret;

}



int32_t dl_get_subifid(struct net_device *netif,
	struct sk_buff *skb,
	void *subif_data,
	uint8_t dst_mac[MAX_ETH_ALEN],
	dp_subif_t *subif,
	uint32_t flags)
{
	int peer_id;
	if (!dst_mac) {
		dtlk_debug(DBG_ERR, "Invalid argument\n");
		return 0;
	}

	peer_id = dl_m2c_find_peer(dst_mac,
		DRE_DIRECT_CLIENT_TABLE,
		0);
	if (peer_id != -1) {
		subif->subif |= peer_id;
		return 0;
	} else {
		/* find in the WDS client list */
		peer_id = dl_m2c_find_peer(dst_mac,
			DRE_DIRECT_CLIENT_WDS_TABLE, 0);/* get peer idx */
		if (peer_id != -1) {
			subif->subif |= peer_id;
			return 0;
		} else
			pr_err("<%s>: cannot find peer from[%x:%x:%x:%x:%x:%x]\n",
			__func__,
			dst_mac[0],
			dst_mac[1],
			dst_mac[2],
			dst_mac[3],
			dst_mac[4],
			dst_mac[5]);
	}
	return 1;
}
EXPORT_SYMBOL(dl_get_subifid);
#endif

/**
  * dlrx_drv_init - Module entry function
  * Initialize basic resources for:
  * - DLRX (in Linux kernel)
  * - DLTX (MPE TX FW).
  **/
int __init dlrx_drv_init(void)
{
	struct dl_drv_address_map dl_resource;
	if (g_ce5_desc_ring_num >= CE5_DEST_DESC_RING_NUM)
		g_ce5_desc_ring_num = CE5_DEST_DESC_RING_NUM;

	if (g_ce5_buf_ptr_ring_num < g_ce5_desc_ring_num)
		g_ce5_buf_ptr_ring_num = g_ce5_desc_ring_num;
	dtlk_debug(DBG_INIT, "DirectLink's parameters\n");
	dtlk_debug(DBG_INIT,
		"\tNumber of TX DESCRIPTOR: %d\n",
		dl_param_tx_descriptor);
#ifdef PROFILING
	initProfiling();
#endif
	wlan_detect_ath_card();

	datapath_dtlk_register_fn = datapath_dtlk_register;
#if defined(CONFIG_ACCL_11AC_CS2)
	dl_get_subifid_fn = dl_get_subifid;
#endif

	/* Get DirectLink resource from MPE HAL */
	g_mpe_dev = mpe_hal_dl_get_dev();

	if (mpe_hal_dl_alloc_resource(0, (uint32_t *)&dl_resource, 0) < 0) {
		dtlk_debug(DBG_ERR, "Can not get DL BUF INFO resource\n");
		return -1;
	}
	datapath_dtlk_switch_parser = dtlk_switch_parser;

	dtlk_debug(DBG_INIT, "%s: 0x%x 0x%x\n",
		__func__,
		dl_resource.dl_buf_info_addr,
		dl_resource.dl_ep_2radio_addr
		);
	memcpy(&g_dl_buf_info,
		(struct dl_buf_info *)dl_resource.dl_buf_info_addr,
		sizeof(g_dl_buf_info)
		);
	dl_init_dltx_memory(g_dl_buf_info);
	g_dl_drv_address.dl_buf_info_addr = dl_resource.dl_buf_info_addr;
	g_dl_drv_address.dl_ep_2radio_addr = dl_resource.dl_ep_2radio_addr;

	dtlk_debug(DBG_INIT, "DirectLink resource from MPE HAL\n");
	dtlk_debug(DBG_INIT, "\tCOMM base[%x]\n",
		g_dl_buf_info.comm_buf_base);
	dtlk_debug(DBG_INIT, "\tCOMM size[%d]\n",
		g_dl_buf_info.comm_buf_size);
	dtlk_debug(DBG_INIT, "\tRX CFG context base[%x]\n",
		g_dl_buf_info.rx_cfg_ctxt_buf_base);
	dtlk_debug(DBG_INIT, "\tRX CFG context size[%d]\n",
		g_dl_buf_info.rx_cfg_ctxt_buf_size);
	dtlk_debug(DBG_INIT, "\tRX Message base[%x]\n",
		g_dl_buf_info.rx_msgbuf_base);
	dtlk_debug(DBG_INIT, "\tRX Message size[%d]\n",
		g_dl_buf_info.rx_msgbuf_size);
	dtlk_debug(DBG_INIT, "\tTX CFG context base[%x]\n",
		g_dl_buf_info.tx_cfg_ctxt_buf_base);
	dtlk_debug(DBG_INIT, "\tTX CFG context size[%d]\n",
		g_dl_buf_info.tx_cfg_ctxt_buf_size);
	dtlk_debug(DBG_INIT, "\tUncached context base[%x]\n",
		g_dl_buf_info.uncached_addr_base);
	dtlk_debug(DBG_INIT, "\tUncached context size[%d]\n",
		g_dl_buf_info.uncached_addr_size);
	if (g_mpe_dev) {
		dtlk_debug(DBG_INIT,
		"\tCOMM base[%x] KSEG0[0x%x] KSEG1[0x%x] [0x%x]\n",
		g_dl_buf_info.comm_buf_base,
		KSEG0,
		KSEG1,
		(unsigned int)CPHYSADDR(g_dl_buf_info.comm_buf_base));
		} else
			dtlk_debug(DBG_ERR, "%s: device is null\n", __func__);
	/* Memory resources */
	ddr_mpe_base = (unsigned int *)(g_dl_buf_info.tx_cfg_ctxt_buf_base);
	ddr_mpe_comp_base = (unsigned int *)(g_dl_buf_info.comm_buf_base);
	/* Initialize data structure */
	if (dlrx_data_structure_init() == DTLK_SUCCESS)
		dtlk_rx_api_init();
	if (dltx_data_structure_init() != DTLK_SUCCESS)
		dtlk_debug(DBG_ERR, "%s:cannot initialize DLTX\n", __func__);

	dtlk_variables_api_init();
	set_vap_itf_tbl_fn = set_vap_itf_tbl;
	dtlk_debug(DBG_INIT, "%s: before create proc\n", __func__);
	proc_file_create();

	dtlk_debug(DBG_INIT, "DLRX driver init successfully!\n");
	dtlk_debug(DBG_INIT, "DLRX driver version: 0x%x\n",
		DRV_VERSION);
	/*Configure MPE DL TX*/
	if (ddr_mpe_base) {
		dltx_cfg_global_t *mpe_dl_tx_cfg_global =
			(dltx_cfg_global_t *)MPE_TX_ADDR(DLTX_CFG_GLOBAL_OFFSET);
		mpe_dl_tx_cfg_global->dltx_enable = 1;
		mpe_dl_tx_cfg_global->dltx_base_address =
			(unsigned int)ddr_mpe_base;
		mpe_dl_tx_cfg_global->switch_parser_flag = 0;
	}
	/* start MPE DL TX,assume we are running one radio */
	mpe_hal_feature_start(DL_TX_1, 0, NULL, F_FEATURE_START);


	return 0;

}
/**
  * dltx_stop - Using logic control variable in shared memory
  * to stop MPE FW
  * - first step: fill in command to shared memory
  * - second step: send IPI message to MPE FW. MPE FW will
  * check the control variable and exit.
  **/
static void dltx_stop(void)
{
	dltx_drv_msg_t *dltx_cfg_ctxt_drv_msg;
	dltx_cfg_ctxt_drv_msg =
		(dltx_drv_msg_t *)MPE_TX_COML_ADDR(DLTX_DRV_MSG_OFFSET);
	dltx_cfg_ctxt_drv_msg->valid = 1;
	dltx_cfg_ctxt_drv_msg->action_type = DLTX_DRV_TO_EXIT;
	ppa_dl_qca_ipi_interrupt();
}
/**
  * dlrx_drv_exit - Exit module
  * It will stop:
  * - DLRX
  * - MPE TX FW
  * then clean all the resources
  **/
static void __exit dlrx_drv_exit(void)
{
	int retries = 3;
	dltx_cfg_global_t *mpe_dl_tx_cfg_global =
		(dltx_cfg_global_t *)MPE_TX_ADDR(DLTX_CFG_GLOBAL_OFFSET);

	/*
	 * check for all activities and stop them
	 */
	datapath_dtlk_register_fn = NULL;
	datapath_dtlk_switch_parser = NULL;
#if defined(CONFIG_ACCL_11AC_CS2)
	dl_get_subifid_fn = NULL;
#endif
	/* clean proc */
	proc_file_delete();
	dtlk_debug(DBG_INIT, "After proc delete\n");
	dtlk_debug(DBG_INIT,
		"%s: Try to free all buffer in replenish list\n",
		__func__
	);
	dtlk_rx_api_exit();
	/*Stop MPE DL TX*/
	dltx_stop();
	while (mpe_dl_tx_cfg_global->dltx_enable && retries) {
		msleep(1000);
		retries--;
		dtlk_debug(DBG_INIT, "Try again\n");
	}

	dtlk_debug(DBG_INIT, "After dtlk_rx_api_exit\n");
	mpe_hal_feature_start(DL_TX_1, 0, NULL, F_FEATURE_STOP);

	return;
}


/* Module Definitions */
module_init(dlrx_drv_init);
module_exit(dlrx_drv_exit);

MODULE_AUTHOR(MOD_AUTHOR);
MODULE_DESCRIPTION(MOD_DESCRIPTION);
MODULE_LICENSE(MOD_LICENCE);

