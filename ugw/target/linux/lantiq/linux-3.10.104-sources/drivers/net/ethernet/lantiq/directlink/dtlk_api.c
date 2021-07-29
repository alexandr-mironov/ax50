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
/*************************************************
 *	This file provide all the APIs that need export to DLRX_FW or 11AC driver
 *************************************************/

/*************************************************
 *			Head File
 *************************************************/
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/version.h>
#include <linux/types.h>
#include <linux/ctype.h>
#include <linux/fs.h>
#include <linux/proc_fs.h>
#include <linux/miscdevice.h>
#include <linux/init.h>
#include <linux/etherdevice.h>
#include <linux/ethtool.h>
#include <linux/if_ether.h>
#include <linux/if_arp.h>
#include <asm/uaccess.h>
#include <asm/unistd.h>
#include <asm/irq.h>
#include <asm/delay.h>
#include <asm/io.h>
#include <asm/gic.h>
#include <linux/skbuff.h>
#include <linux/dma-mapping.h>
#include <linux/list.h>
#include <net/lantiq_cbm.h>
#include <net/lantiq_cbm_api.h>
#include <net/ppa_ppe_hal.h>
#include <net/ppa_stack_al.h>
#include <linux/dma-mapping.h>

/* FW header files */
#include "./include/11ac_acc_data_structure_tx_be.h"
#include "./include/dlrx_fw_data_structure_be.h"
#include "./include/dlrx_fw_def.h"
#include "./include/dlrx_fw_version.h"
/*DLRX driver header files */
#include "./include/dlrx_drv.h"
#include "./include/dlrx_memory_lyt.h"
#include "./include/dlrx_dre_api.h"
#include "./include/dlrx_wlan_api.h"

#include "./include/directlink_tx_cfg.h"
#include "./include/ltqmips_hal.h"
#include <net/ltq_mpe_api.h>
#include <net/ppa_stack_al.h>
#include <net/ppa_api.h>
#include <net/ppa_api_directpath.h>
#include <net/ppa_hook.h>
#include <net/ppa_ppe_hal.h>

#include "./include/dltx_fw_data_structure_be.h"
#include "./include/Dltx_fw_def.h"
#include "../cbm/cbm.h"

#include <net/datapath_api.h>

#include <xway/switch-api/lantiq_gsw_api.h>
#include <xway/switch-api/lantiq_gsw_flow.h>
#define dl_kseg0 KSEG0
#define dl_kseg1 KSEG1

/*************************************************
 *			Definition
 *************************************************/

/*************************************************
 *			Global Variable
 *************************************************/
uint32_t g_dlrx_max_inv_header_len;
uint32_t g_dlrx_cfg_offset_atten;
void *g_dlrx_handle;
PPA_QCA_DL_RX_CB g_dlrx_qca_cb = {0};
dre_regfn_set_t g_dre_fnset    = {0};
spinlock_t g_vap2int_tbl_lock;
spinlock_t g_prid2pr_tbl_lock;
spinlock_t g_pr2vap_tbl_lock;
spinlock_t g_pr2handler_tbl_lock;

extern PPA_SUBIF g_quick_ref_sub_if_from_vap_id[];
extern struct device *g_mpe_dev;
extern struct dl_buf_info g_dl_buf_info;


extern int dtlk_get_subif_from_vap_id(
	PPA_SUBIF *sub_if, int vap_id
	);

struct dma_rx_desc_1 dma_rx_desc_mask1;
struct dma_rx_desc_3 dma_rx_desc_mask3;
struct dma_rx_desc_0 dma_tx_desc_mask0;
struct dma_rx_desc_1 dma_tx_desc_mask1;
#define DTLK_SET_PMAC_SUBIF(pmac, subif) do {;\
	pmac->src_sub_inf_id2 = (subif) & 0xff; \
	pmac->src_sub_inf_id =  ((subif) >> 8) & 0x1f; } \
	while (0)
#define DTLK_SET_PMAC_PORTMAP(pmac, port_id) do { if (port_id <= 7)\
			pmac->port_map2 = 1 << (port_id); \
			else \
				pmac->port_map = (1 << (port_id-8)); } \
			while (0)

extern int cbm_setup_desc(struct cbm_desc *desc, uint32_t data_ptr, uint32_t data_len,
uint32_t DW0, uint32_t DW1);
extern int cbm_cpu_enqueue(uint32_t pid, struct cbm_desc *desc);
extern int cbm_cpu_enqueue_dl(uint32_t pid, struct cbm_desc *desc);


#ifdef PROFILING
extern void *CycleCounter_Create(char *);
extern void CycleCounter_Start(void *);
extern void CycleCounter_End(void *);
void *profiling_alloc;
void *profiling_enqueue;
void *profiling_writeback;
void *profiling_cmb_alloc;
void *profiling_cmb_enqueue;

void initProfiling()
{
	dtlk_debug(DBG_INIT, "%s: Init profiling\n", __func__);
	profiling_alloc = CycleCounter_Create("Allocation");
	profiling_enqueue = CycleCounter_Create("Enqueue");
	profiling_writeback = CycleCounter_Create("Writeback");
	profiling_cmb_alloc = CycleCounter_Create("CBM Allocation");
	profiling_cmb_enqueue = CycleCounter_Create("CBM Enqueue");
}
#endif


int set_peer_id_to_peer_table(
	uint32_t dlrx_peer_reg_handle,
	uint32_t peer_id,
	uint32_t *peer,
	unsigned int vap_id,
	unsigned int pn_chk_type
	);
int remove_peer_id_from_table(
	uint32_t peer,
	uint32_t peer_id
	);
int remove_peer_from_table(
	uint32_t peer,
	uint32_t peer_id
	);
int get_handler_index(
	uint32_t index
	);
int get_free_peer_number(
	unsigned int *peer
	);

/*************************************************
 *			Static functions
 *************************************************/
/*
* Function: alloc_skb_tx
* Purpose: alloc CBM skb buffer
*/
#define RX_RESERVE_BYTES 128

void dealloc_skb_tx(struct sk_buff *skb)
{
	cbm_buffer_free(smp_processor_id(), (uint32_t)skb, 0);
}

static struct sk_buff *alloc_skb_tx(
	int len
	)
{
	void *buf = NULL;
#ifdef PROFILING
	CycleCounter_Start(profiling_cmb_alloc);
#endif
	buf = cbm_buffer_alloc(smp_processor_id(), CBM_PORT_F_STANDARD_BUF);
#ifdef PROFILING
	CycleCounter_End(profiling_cmb_alloc);
#endif
	return buf;
}


/*
*  Get the DRE FW API pointer
*/
static void *dlrx_get_dre_fn(
	unsigned int fntype
	)
{
	switch (fntype) {
	case DRE_MAIN_FN:
		return g_dre_fnset.dre_dl_main_fn;
	case DRE_GET_VERSION_FN:
		return g_dre_fnset.dre_dl_getver_fn;
	case DRE_RESET_FN:
		return g_dre_fnset.dre_dl_reset_fn;
	case DRE_GET_MIB_FN:
		return g_dre_fnset.dre_dl_getmib_fn;
	case DRE_GET_CURMSDU_FN:
		return g_dre_fnset.dre_dl_getmsdu_fn;
	case DRE_SET_MEMBASE_FN:
		return g_dre_fnset.dre_dl_set_membase_fn;
	case DRE_SET_RXPN_FN:
		return g_dre_fnset.dre_dl_set_rxpn_fn;
	case DRE_SET_DLRX_UNLOAD:
		return g_dre_fnset.dre_dl_set_dlrx_unload_t;
	default:
		return NULL;
	}

	return NULL;

}

/*
 *	Extract and Setup the skb structure
 */
static struct sk_buff *dlrx_skb_setup(
	unsigned int rxpb_ptr,
	unsigned int data_ptr,
	unsigned int data_len
	)
{
	struct sk_buff *skb;
	int header_len = data_ptr - rxpb_ptr;
	ppa_dl_dre_dma_invalidate(rxpb_ptr , header_len + data_len);
	skb = dev_alloc_skb(header_len + data_len);
	if (skb == NULL) {
		dtlk_debug(DBG_ERR, "Can not allocate memory for DLRX\n");
		return NULL;
	}
	memcpy(skb_put(skb, header_len + data_len),
		(void *)rxpb_ptr, header_len + data_len);
	skb_pull(skb, header_len);
	/* free old cbm */
	cbm_buffer_free(smp_processor_id(), rxpb_ptr, 0);
	return skb;
}

static void dump_skb(
	struct sk_buff *skb,
	uint32_t len,
	char *title
	)
{
	int i;

	if (skb->len < len)
		len = skb->len;

	if (len > DTLK_PACKET_SIZE) {
		dtlk_debug(DBG_ERR, "Too big:skb=%08x,skb->data=%08x,skb->len=%d\n",
			(u32)skb, (u32)skb->data, skb->len);
		return;
	}

	dtlk_debug(DBG_RX, "%s\n", title);
	dtlk_debug(DBG_RX, "skb=0x%x,skb->data=%08X,skb->tail=%08X,skb->len=%d\n",
		(u32)skb, (u32)skb->data, (u32)skb->tail, (int)skb->len);
	for (i = 1; i <= len; i++) {
		if ((i % 16) == 1)
			dtlk_debug(DBG_RX, "  %4d:", i - 1);
		dtlk_debug(DBG_RX, " %02X", (int)(*((char *)skb->data + i - 1) & 0xFF));
		if ((i % 16) == 0)
			dtlk_debug(DBG_RX, "\n");
	}
	if (((i - 1) % 16) != 0)
		dtlk_debug(DBG_RX, "\n");
}

void skb_list_replenish(
	struct list_head *head
	)
{

}

/*
* Free all skb buffers in the recycle list
*/
void skb_list_exhaust(
	struct list_head *head
	)
{
	struct list_head *pos, *q;
	int count = 0;
	list_for_each_safe(pos, q, head) {
		list_del(pos);
		if (pos) {
			struct sk_buff *buff = (struct sk_buff *)pos;
			if (buff != NULL) {
				dtlk_debug(DBG_ERR,
				"%s: %p shoudl be the same %x\n",
				__func__, buff,
				(unsigned int)(*((u32 *)buff->data - 1))
				);
				/* free the data */
				dealloc_skb_tx(buff);
				count++;
			}
		}
	}
	dtlk_debug(DBG_RX,
		"%s: release %d in list\n", __func__, count);
}

/*************************************************
 *			Global Functions
 *************************************************/
struct sk_buff *alloc_skb_rx(void)
{
	struct sk_buff *result;
#ifdef PROFILING
	CycleCounter_Start(profiling_alloc);
#endif
	result = alloc_skb_tx(DTLK_PACKET_SIZE);
#ifdef PROFILING
	CycleCounter_End(profiling_alloc);
#endif
	return result;
}

/*
* This function is called when DTLK driver is unloaded.
*/
void dtlk_rx_api_exit(void)
{
	*DLRX_SKB_POOL_CTXT = 0;
}

void dtlk_rx_api_init(void)
{
	spin_lock_init(&g_vap2int_tbl_lock);
	spin_lock_init(&g_prid2pr_tbl_lock);
	spin_lock_init(&g_pr2vap_tbl_lock);
	spin_lock_init(&g_pr2handler_tbl_lock);

	return;
}

/*************************************************
 *			APIs for DLRX FW
 *************************************************/
/*
 * Function: dlrx_dl_dre_rxpb_buf_alloc
 * Purpose: Allocate a new rxpb ring pkt buffer for DLRX FW
 * Return: return skb->data pointer. DLRX FW from this pointer
 *     can get original skb pointer.
 */
unsigned int dlrx_dl_dre_rxpb_buf_alloc(void)
{
	struct sk_buff *skb;

	skb = alloc_skb_rx();
	if (!skb) {
		dtlk_debug(DBG_ERR, "%s:It's realy bad SKB fail!!!\n", __func__);
		return 0;
	}
	return (unsigned int)((unsigned char *)skb + RX_RESERVE_BYTES);
}
EXPORT_SYMBOL(dlrx_dl_dre_rxpb_buf_alloc);


/*
 * Free a  rxpb ring pkt buffer,called by DLRX firmware.
 */
int ppa_dl_dre_rxpb_buf_free(
	unsigned int rxpb_ptr
	)
{
	struct sk_buff *skb;

	/* sanity check */

	dtlk_debug(DBG_RX, "%s: going to free 0x%x\n",
		__func__,
		rxpb_ptr
		);
	if (rxpb_ptr < KSEG0)
		rxpb_ptr = 	CACHE_ADDR(rxpb_ptr);

	if (!rxpb_ptr) {
		dtlk_debug(DBG_ERR, "%s: rxpb_ptr is NULL\n", __func__);
		return DTLK_FAILURE;
	}
	rxpb_ptr = 	CACHE_ADDR(rxpb_ptr);
	skb = (struct sk_buff *)rxpb_ptr;
	if (!skb) {
		dtlk_debug(DBG_ERR, "%s: freed by replenish or invalid\n",
			__func__);
		return DTLK_ERROR;
	}
	/*
	* dtlk_debug(DBG_RX,
	* 	"%s: rxpb[%x] skb[%x] cbm[%x]\n",
	* 	__func__, rxpb_ptr, skb, skb->head);
	*/
	/* free the cbm */
	dealloc_skb_tx(skb);
	return DTLK_SUCCESS;
}
EXPORT_SYMBOL(ppa_dl_dre_rxpb_buf_free);

inline int32_t
dl_cbm_cpu_pkt_tx_no_skb(
	int data_len,
	int ep,
	int subif,
	unsigned int rxpb_ptr,
	unsigned int pmac_header_ptr,
	int flags
	)
{
	struct cbm_desc desc;
	uint32_t tmp_data_ptr;
	unsigned int txLen = data_len + 8;
	unsigned int sub_if = (subif << 8);
	struct pmac_tx_hdr *pmac = NULL;
	struct dma_tx_desc_0 desc_0;
	struct dma_tx_desc_1 desc_1;
	/*
	dtlk_debug(DBG_TX, "<%s>: ep[%d] subif[%d] [%x] rxpb_ptr[0x%x] pmac_header_ptr[0x%x]\n",
	__func__, ep, subif, sub_if, rxpb_ptr, pmac_header_ptr);
	*/
	tmp_data_ptr = pmac_header_ptr;
	pmac = (struct pmac_tx_hdr *)pmac_header_ptr;
	memset(pmac, 0, sizeof(struct pmac_tx_hdr));
	/* step1 : set pmac */
	if (flags == 0) {
		/*pmac->port_map_en = 0;*/
		pmac->port_map = 0xff;
		pmac->port_map2 = 0xff;
		pmac->sppid = ep;

		DTLK_SET_PMAC_SUBIF(pmac, sub_if);
	} else {
		pmac->port_map_en = 1;
		DTLK_SET_PMAC_PORTMAP(pmac, (ep));
		pmac->sppid = PMAC_CPU_ID;
		DTLK_SET_PMAC_SUBIF(pmac, sub_if);
	}
	/* step 2: set DMA */
	desc_1.all &=  dma_tx_desc_mask1.all;
	if (flags == 0) {
		desc_1.field.enc = 1;
		desc_1.field.dec = 1;
	}
	desc_1.field.ep = ep;
	desc_0.all = sub_if;
	ppa_dl_dre_dma_writeback(rxpb_ptr, (pmac_header_ptr - rxpb_ptr) + 8);

	if (cbm_setup_desc ((struct cbm_desc *) &desc, tmp_data_ptr,
			(txLen < (ETH_ZLEN + 8)) ? (ETH_ZLEN + 8) : txLen,
			desc_1.all, desc_0.all)) {
		dtlk_debug(DBG_ERR, "cbm setup desc failed..\n");
		dealloc_skb_tx((struct sk_buff *)rxpb_ptr);
		return -1;
	}
	if (1) {
		uint32_t data_pointer, pointer_to_wb;
		pointer_to_wb = desc.desc2 & 0xfffff800;
		data_pointer = ((pointer_to_wb & 0x0fffffff) | 0x20000000);
		data_pointer += desc.desc2 - pointer_to_wb;
#ifdef PROFILING
		CycleCounter_Start(profiling_cmb_enqueue);
#endif
		if (cbm_cpu_enqueue_hw(smp_processor_id(),
			(struct cbm_desc *)&desc, (void *)data_pointer, 0)
			== CBM_FAILURE) {
			dtlk_debug(DBG_ERR, "cpu enqueue failed..\n");
			dealloc_skb_tx((struct sk_buff *)rxpb_ptr);
			return -1;
		}
#ifdef PROFILING
		CycleCounter_End(profiling_cmb_enqueue);
#endif
	}
	return 0;
}


int ppa_dl_dre_gswip_dma_send(
	unsigned int vap_id,
	unsigned int rxpb_ptr,
	unsigned int data_ptr,
	unsigned int data_len,
	unsigned int release_flag,
	unsigned int pmac_hdr_ptr,
	unsigned int unmap_type
	)
{
	PPA_SUBIF dp_sub_if;
	struct net_device *dev;
	int32_t res = 0;
	uint32_t flags = 0;

	int header_len;

#ifdef PROFILING
	CycleCounter_Start(profiling_enqueue);
#endif
	/* get Datapath sub interface for this VAP ID */
	dp_sub_if = g_quick_ref_sub_if_from_vap_id[vap_id & 0xffff];
	header_len = data_ptr - rxpb_ptr;
	vap_id = vap_id & 0xffff;
	if (!dtlk_get_subif_from_vap_id(&dp_sub_if, vap_id)) {
		if (release_flag) {
			/*direct enqueue to CBM buffer*/
			if (dl_cbm_cpu_pkt_tx_no_skb(data_len,
				dp_sub_if.port_id,
				dp_sub_if.subif,
				rxpb_ptr,
				data_ptr - 8,
				flags) == -1) {
				dtlk_debug(
				DBG_ERR,
				"dl_cbm_cpu_pkt_tx_no_skb: failed\n"
				);
				return DTLK_FAILURE;
			}
		} else {
			/* create new skb data */
			unsigned char *skb_data;
			struct sk_buff *skb2;
			dev = dtlk_dev_from_vapid(vap_id & 0xffff);
			if (!dev)
				dtlk_debug(DBG_ERR,
					"Invalid device: vap[%u]\n",
					vap_id);
			else {
				skb2 = dev_alloc_skb(data_len);
				if (!skb2) {
					dtlk_debug(DBG_ERR,
						"alloc_skb_rx failed");
					return DTLK_FAILURE;
				}
				skb_data = skb_put(skb2, data_len);
				memset(skb_data, 0, data_len);
				memcpy(skb_data,
					(void *)data_ptr, data_len);
				skb2->dev = dev;
				res = ppa_hook_directpath_ex_send_fn(
					&dp_sub_if, skb2, data_len, 1);
			}
		}

		if (res == DP_SUCCESS) {
		} else {
			dtlk_debug(DBG_ERR, "Cannot send to Datapath");
			return DTLK_FAILURE;
		}
	} else {
		dtlk_debug(DBG_ERR,
			"Cannot get sub interface of VAP[%d]\n", vap_id);
		return DTLK_FAILURE;
	}
#ifdef PROFILING
	CycleCounter_End(profiling_enqueue);
#endif
	return DTLK_SUCCESS;
}
EXPORT_SYMBOL(ppa_dl_dre_gswip_dma_send);

int ppa_dl_dre_ps_send(
	unsigned int rxpb_ptr,
	unsigned int data_ptr,
	unsigned int data_len,
	unsigned int vap_id
	)
{
	struct sk_buff *skb;
	struct net_device *dev;
	skb = dlrx_skb_setup(rxpb_ptr, data_ptr, data_len);

	if (!skb)
		return DTLK_FAILURE;

	dev = dtlk_dev_from_vapid((uint32_t)vap_id);
	/* sanity check */
	if (!dev) {
		dtlk_debug(DBG_ERR, "No valid device pointer!!!\n");
		dev_kfree_skb_any(skb);
		return DTLK_FAILURE;
	}
	skb->protocol = eth_type_trans(skb, dev);
	dtlk_debug(DBG_RX,
		"%s - skb: 0x%x, dev_name: %s, rxpb_ptr: 0x%x,",
		__func__, (uint32_t)skb, dev->name, rxpb_ptr);

	dtlk_debug(DBG_RX,
		" data_ptr: 0x%x, len: 0x%x, vap_id: 0x%x, protocol: %d\n",
		(uint32_t)skb->data, skb->len, vap_id, skb->protocol);

	dump_skb(skb, skb->len, "Send To Protocol Stack");
	if (netif_rx(skb) == NET_RX_DROP) {
		dtlk_debug(DBG_ERR, "Cannot send to Protocol Stack\n");
		dev_kfree_skb_any(skb);
		return DTLK_FAILURE;
	}

	return DTLK_SUCCESS;
}
EXPORT_SYMBOL(ppa_dl_dre_ps_send);

/*
 *	DLRX FW send pkt to WLAN driver
 */
int ppa_dl_dre_wlan_pkt_send(
	unsigned int rxpb_ptr,
	unsigned int data_len,
	unsigned int pkt_status,
	unsigned int msg_ptr,
	unsigned int vap_id,
	unsigned int flags
	)
{
	struct sk_buff *skb;
	int ret = DTLK_FAILURE;
	unsigned padding = (flags >> 16);
	skb = dlrx_skb_setup(rxpb_ptr,
			rxpb_ptr + padding,
			data_len + g_dlrx_cfg_offset_atten
			);
	if (!skb)
		return DTLK_FAILURE;
	ppa_dl_dre_dma_invalidate((u32)skb->data, data_len);

	dtlk_debug(DBG_CPU,
		"%s, rxpb_ptr: 0x%x, data_len: 0x%x,",
		__func__, rxpb_ptr, data_len);
	dtlk_debug(DBG_CPU,
		" pkt_status: 0x%x, msg_ptr: 0x%x, flags: 0x%x\n",
		pkt_status, msg_ptr, flags);
	/* QCA will consume the CBM skb */
	if (likely(g_dlrx_qca_cb.rx_splpkt_fn))
		ret = g_dlrx_qca_cb.rx_splpkt_fn(g_dlrx_handle,
			pkt_status,
			data_len,
			skb,
			(uint32_t *)msg_ptr,
			flags
			);
	else {
		dtlk_debug(DBG_ERR, "No Special PKT fn handler!");
		dev_kfree_skb_any(skb);
	}
	/*
	   * The QCA does not pass the packet to protocol stack.
	   * DTLK will create new skb buffer for good packet
	   * and send it to protocol stack.
	   */
	if (flags) {
		/* Get the data pointer */
		unsigned int data_ptr = rxpb_ptr + g_dlrx_cfg_offset_atten;
		struct net_device *dev;
		struct sk_buff *skb3 = dev_alloc_skb(data_len + 32);

		data_ptr += padding;

		if (skb3 == NULL)
			dtlk_debug(DBG_ERR, "%s: Cannot alloc [%d]\n",
				__func__,
				data_len + 32);
		else {
			dev = dtlk_dev_from_vapid((uint32_t)vap_id);
			if (dev) {
				memcpy(skb_put(skb3, data_len),
					(void *)data_ptr,
					data_len);
				skb3->dev = dev;
				skb3->protocol = eth_type_trans(skb3, dev);
				skb3->ip_summed = CHECKSUM_UNNECESSARY;
				if (netif_rx(skb3) != NET_RX_DROP)
					dtlk_debug(
					DBG_CPU,
					"%s: Send PS successfully\n",
					__func__
					);
				else {
					dev_kfree_skb_any(skb3);
					dtlk_debug(DBG_ERR, "%s: Cannot send to PS\n",
						__func__);
				}
			}
		}
	}
	return ret;
}
EXPORT_SYMBOL(ppa_dl_dre_wlan_pkt_send);

/*
 *	DLRX FW send msg to WLAN driver
 */
int ppa_dl_dre_wlan_msg_send(
	unsigned int msg_type,
	unsigned int msg_ptr,
	unsigned int msg_len,
	unsigned int flags
	)
{
	int ret = DTLK_FAILURE;
	if (likely(g_dlrx_qca_cb.rx_msg_fn)) {
		/*
		* dtlk_debug(DBG_CPU, "%s, msg_type: %d,",
		* __func__, msg_type);
		* dtlk_debug(DBG_CPU,
		* " msg_len: %d, msg_ptr: 0x%x, flags: 0x%x\n",
		* msg_len, msg_ptr, flags);
		**/
		ret = g_dlrx_qca_cb.rx_msg_fn(g_dlrx_handle,
				msg_type,
				msg_len,
				(uint32_t *)msg_ptr,
				flags
				);
	} else
		dtlk_debug(DBG_ERR, "No Message fn handler!");

	return ret;
}
EXPORT_SYMBOL(ppa_dl_dre_wlan_msg_send);

void ppa_dl_dre_peer_act_fn(unsigned int peer_id)
{
	if (g_dlrx_qca_cb.peer_act_fn)
		g_dlrx_qca_cb.peer_act_fn(g_dlrx_handle, peer_id);
}
EXPORT_SYMBOL(ppa_dl_dre_peer_act_fn);

/*
*  DLRX register function
*/
int ppa_dl_dre_fn_register(unsigned int fntype, void *func)
{
	switch (fntype) {
	case DRE_MAIN_FN:
		g_dre_fnset.dre_dl_main_fn = func;
		break;

	case DRE_GET_VERSION_FN:
		g_dre_fnset.dre_dl_getver_fn = func;
		break;

	case DRE_RESET_FN:
		g_dre_fnset.dre_dl_reset_fn = func;
		break;

	case DRE_GET_MIB_FN:
		g_dre_fnset.dre_dl_getmib_fn = func;
		break;

	case DRE_GET_CURMSDU_FN:
		g_dre_fnset.dre_dl_getmsdu_fn = func;
		break;

	case DRE_SET_MEMBASE_FN:
		g_dre_fnset.dre_dl_set_membase_fn = func;
		break;

	case DRE_SET_RXPN_FN:
		g_dre_fnset.dre_dl_set_rxpn_fn = func;
		break;

	case DRE_SET_DLRX_UNLOAD:
		g_dre_fnset.dre_dl_set_dlrx_unload_t = func;
		break;
	case DRE_MAX_FN:
	default:
		dtlk_debug(DBG_ERR, "Register NO is Not valid:%d", fntype);
		return DTLK_FAILURE;
	}
	return DTLK_SUCCESS;
}
EXPORT_SYMBOL(ppa_dl_dre_fn_register);

/*
 * Get Peer value from PeerID
 * Return Peer Valid
 */
int ppa_dl_dre_peer_from_peerid(
	unsigned int peerid,
	unsigned int *peer
	)
{
	unsigned int *pid2p_tbl = DLRX_CFG_PEER_ID_TO_PEER_MAP_BASE(0);
	unsigned int idx = peerid >> 2;
	unsigned int offset = peerid % 4;
	unsigned int peer_val;
	int result;

	if (peerid >= MAX_PEERID_NUM)
		return PEER_INVALID;

	spin_lock_bh(&g_prid2pr_tbl_lock);
	peer_val = *(pid2p_tbl + idx);
	spin_unlock_bh(&g_prid2pr_tbl_lock);

	peer_val = (peer_val >> (offset << 3));
	*peer = peer_val & 0x7F;
	result = ((peer_val >> 7) & 0x1);
	return result;
}
EXPORT_SYMBOL(ppa_dl_dre_peer_from_peerid);

extern void mpe_hal_dl_enable_gic(int irq_no);

void ppa_dl_qca_ipi_interrupt(void)
{
	/*
	 dtlk_debug(DBG_TX,
	 "%s:ipi irq [%d]\n", __func__, g_dl_buf_info.DlCommmIpi);
	 */
	mpe_hal_dl_enable_gic(g_dl_buf_info.DlCommmIpi);

}
EXPORT_SYMBOL(ppa_dl_qca_ipi_interrupt);

int32_t ppa_dl_qca_clear_stats(
	uint32_t vapId,
	uint32_t flags
	)
{
	dre_dl_reset_fn_t dre_dl_reset_fn;
	dre_dl_reset_fn = dlrx_get_dre_fn(DRE_RESET_FN);
	return DTLK_FAILURE;
}
EXPORT_SYMBOL(ppa_dl_qca_clear_stats);

/*
 * Set VAP info
 * Return -1 if peer or vapid out of range
 */
int ppa_dl_dre_vapinfo_set(
	unsigned int peer,
	unsigned int vapid,
	unsigned int sec_type,
	unsigned int acc_dis
	)
{
	unsigned int *vapinfo_tbl = DLRX_CFG_PEER_TO_VAP_PN_BASE(0);
	unsigned int vapinfo;

	if (vapid >= MAX_VAP_NUM || peer >= MAX_PEER_NUM)
		return DTLK_FAILURE;

	vapinfo = ((acc_dis & 0x1) << 6) |
				((sec_type & 0x3) << 4) |
				(vapid & 0xF);
	spin_lock_bh(&g_pr2vap_tbl_lock);
	*(vapinfo_tbl + peer) = vapinfo;
	spin_unlock_bh(&g_pr2vap_tbl_lock);

	return DTLK_SUCCESS;
}
EXPORT_SYMBOL(ppa_dl_dre_vapinfo_set);


/*
 *	Get VAP info from Peer
 *	Return -1 if peer or vap id out of range
 */
int ppa_dl_dre_vapinfo_from_peer(
	unsigned int peer,
	unsigned int *vapid,
	unsigned int *sec_type,
	unsigned int *acc_dis
	)
{
	unsigned int *vapinfo_tbl = DLRX_CFG_PEER_TO_VAP_PN_BASE(0);
	unsigned int vapinfo;

	if (peer >= MAX_PEER_NUM)
		return DTLK_FAILURE;

	spin_lock_bh(&g_pr2vap_tbl_lock);
	vapinfo = *(vapinfo_tbl + peer);
	spin_unlock_bh(&g_pr2vap_tbl_lock);

	*vapid	  = vapinfo & 0xf;
	*sec_type = (vapinfo >> 4) & 0x3;
	*acc_dis  = (vapinfo >> 6) & 0x1;

	return DTLK_SUCCESS;
}
EXPORT_SYMBOL(ppa_dl_dre_vapinfo_from_peer);

/*
 * Get interface id from VAP id
 */
unsigned int ppa_dl_dre_itf_from_vapid(
	unsigned int vap_id
	)
{
	unsigned int *itf_tbl;
	unsigned int itf_id;

	if (vap_id >= MAX_VAP_NUM)
		return DTLK_INVALID_ITFID;
	/* Range is defined in the spec */
	if (vap_id <= 7)
		itf_tbl = DLRX_CFG_VAP2INT_MAP1_BASE;
	else
		itf_tbl = DLRX_CFG_VAP2INT_MAP2_BASE;

	vap_id = vap_id % 8;
	spin_lock_bh(&g_vap2int_tbl_lock);
	itf_id = (*itf_tbl >> (vap_id<<2)) & 0xF;
	spin_unlock_bh(&g_vap2int_tbl_lock);

	return itf_id;

}
EXPORT_SYMBOL(ppa_dl_dre_itf_from_vapid);



/*************************************************
 *			APIs for 11AC Driver
 *************************************************/
void ppa_dl_qca_register(
	void *dl_rx_handle,
	PPA_QCA_DL_RX_CB *dl_qca_rxcb,
	uint32_t flags
	)
{
	ASSERT((dl_rx_handle != NULL && dl_qca_rxcb != NULL),
		"dl_rx_handle or dl_qca_rxcb is NULL");
	ASSERT((flags == PPA_F_REGISTER) || (flags == PPA_F_DEREGISTER),
		"flag is not expected: %d\n",
		flags);
	dtlk_debug(DBG_INIT, "%s, dl_rx_handle: 0x%x,",
		__func__, (uint32_t)dl_rx_handle);
	dtlk_debug(DBG_INIT, "dl_qca_rxcb: 0x%x, flags: 0x%d\n",
		(uint32_t)dl_qca_rxcb, flags);
	g_dlrx_handle = dl_rx_handle;
	/* Fix Klockwork's check */
	if (dl_qca_rxcb == NULL)
		return;
	switch (flags) {
	case PPA_F_REGISTER:
		{
		dre_dl_set_dlrx_unload_t dre_dl_set_dlrx_unload_fn;
		dre_dl_set_dlrx_unload_fn =
			g_dre_fnset.dre_dl_set_dlrx_unload_t;
		ASSERT((dl_rx_handle != NULL &&  dl_qca_rxcb != NULL),
			"dl_rx_handle or dl_qca_rxcb is NULL");
		g_dlrx_handle = dl_rx_handle;
		g_dlrx_qca_cb.rx_msg_fn	=
			dl_qca_rxcb->rx_msg_fn;
		g_dlrx_qca_cb.rx_splpkt_fn =
			dl_qca_rxcb->rx_splpkt_fn;
		g_dlrx_qca_cb.vap_stats_fn =
			dl_qca_rxcb->vap_stats_fn;
		g_dlrx_qca_cb.peer_act_fn =
			dl_qca_rxcb->peer_act_fn;
		}
		break;
	case PPA_F_DEREGISTER:
		{
			dre_dl_set_dlrx_unload_t dre_dl_set_dlrx_unload_fn;
			dtlk_debug(DBG_INIT, "%s: deregister from QCA\n",
				__func__);
			dre_dl_set_dlrx_unload_fn =
				g_dre_fnset.dre_dl_set_dlrx_unload_t;
			/* we stop dlrx firmware here */
			if (likely(dre_dl_set_dlrx_unload_fn)) {
				dtlk_debug(DBG_INIT, "%s: inform DRE to stop\n",
					__func__);
				dre_dl_set_dlrx_unload_fn();
			}
		}
		break;
	default:
		break;
	}
	return;
}
EXPORT_SYMBOL(ppa_dl_qca_register);

/*
* These functions need to merge with DL TX
* QCA Name: "QCA-11AC"
*/
void ppa_directlink_manage(
	char *name,
	uint32_t flags
	)
{
	/* Update the global structure cfg_global */
	dlrx_cfg_global_t *dlrx_global =
		(dlrx_cfg_global_t *)DLRX_CFG_GLOBAL_BASE;

	if (flags == PPA_F_INIT) {
		dlrx_global->dlrx_enable = TRUE;
		dlrx_global->dltx_enable = TRUE;
	} else if (flags == PPA_F_UNINIT) {
		dlrx_global->dlrx_enable = FALSE;
		dlrx_global->dltx_enable = FALSE;
	}

	/* ppa_directlink_enable(flags); */

	return;
}
EXPORT_SYMBOL(ppa_directlink_manage);

/*API to get 11AC wireless card type */
extern int ppa_dl_detect_11ac_card(void);


#if defined(CONFIG_ACCL_11AC_CS2)
extern unsigned int *ddr_mpe_base;
#define MPE_TX_ADDR(offset) (ddr_mpe_base + offset)
#endif
/*
* This function initializes Target-to-Host (t2h) CE-5 Destination Ring
* in Direct Link between Target WLAN and PPE.
*/
void ppa_dl_qca_t2h_ring_init(
	uint32_t *t2h_ring_sz,
	uint32_t *dst_ring_base,
	uint32_t pcie_baddr,
	uint32_t flags
	)
{
	dre_dl_set_membase_fn_t  dre_dl_set_mb_fn;
	dlrx_cfg_ctxt_ce5des_t *dlrx_cfg_ctxt_ce5des_ptr;
	dlrx_cfg_ctxt_ce5buf_t *dlrx_cfg_ctxt_ce5buf_ptr;
	dlrx_cfg_global_t *dlrx_cfg_global_ptr;

	dtlk_debug(DBG_INIT,
		"%s:ddr base:0x%08x,cfg_ctxt_base:0x%x,pcie base:0x%08x\n",
		 __func__,
		 (uint32_t)ddr_base,
		 (uint32_t)cfg_ctxt_base,
		 (uint32_t)pcie_baddr
		 );
	pcie_base = (unsigned int *)(0xF0000000 | pcie_baddr);
	dtlk_debug(DBG_INIT,
		"pcie base(virtual): 0x%x\n", (unsigned int)pcie_base);
	dtlk_debug(DBG_INIT,
		"pcie base(virtual): 0x%p\n",
		(unsigned int *)KSEG1ADDR(pcie_baddr));
	dlrx_cfg_global_ptr = (dlrx_cfg_global_t *)DLRX_CFG_GLOBAL_BASE;
	dlrx_cfg_global_ptr->dlrx_pcie_base = (unsigned int)pcie_base;

	dlrx_cfg_ctxt_ce5des_ptr =
		(dlrx_cfg_ctxt_ce5des_t *)DLRX_CFG_CTXT_CE5DES_BASE;
#ifdef USING_BBCPU_SRAM
	*dst_ring_base =
		(dlrx_cfg_ctxt_ce5des_ptr->cfg_badr_ce5des & 0x0fffffff)
		| 0x10000000;
#else
	*dst_ring_base = dma_map_single(
				g_mpe_dev,
				(void *)dlrx_cfg_ctxt_ce5des_ptr->cfg_badr_ce5des,
				512 * 2 * 4,
				DMA_FROM_DEVICE
				);
	if (unlikely(dma_mapping_error(g_mpe_dev, (u64)*dst_ring_base))) {
		dtlk_debug(DBG_ERR, "DMA error");
	}
#endif
	*t2h_ring_sz = dlrx_cfg_ctxt_ce5des_ptr->cfg_num_ce5des;
	dtlk_debug(DBG_INIT, "dst_ring_base: 0x%x\n", *dst_ring_base);
	dtlk_debug(DBG_INIT, "t2h_ring_sz: 0x%x\n", *t2h_ring_sz);

	/*
	QCA will update the HW register
	*/
	dlrx_cfg_ctxt_ce5buf_ptr =
		(dlrx_cfg_ctxt_ce5buf_t *)DLRX_CFG_CTXT_CE5BUF_BASE;

	if (ppa_dl_detect_11ac_card() == PEREGRINE_BOARD) {
		dtlk_debug(DBG_INIT, "%s: PEREGRINE_BOARD\n", __func__);
		dlrx_cfg_ctxt_ce5buf_ptr->cfg_badr_target_ce5_read_index =
			(unsigned int)DLRX_TARGET_CE5_READ_INDEX(DLRX_TARGET_CE5_PEREGRINE);
		dlrx_cfg_ctxt_ce5buf_ptr->cfg_badr_target_ce5_write_index =
			(unsigned int)DLRX_TARGET_CE5_WRITE_INDEX(DLRX_TARGET_CE5_PEREGRINE);
	} else {
		dtlk_debug(DBG_INIT, "%s: BEELINER_BOARD\n", __func__);
		dlrx_cfg_ctxt_ce5buf_ptr->cfg_badr_target_ce5_read_index =
			(unsigned int)DLRX_TARGET_CE5_READ_INDEX(DLRX_TARGET_CE5_BEELINER);
		dlrx_cfg_ctxt_ce5buf_ptr->cfg_badr_target_ce5_write_index =
			(unsigned int)DLRX_TARGET_CE5_WRITE_INDEX(DLRX_TARGET_CE5_BEELINER);
	}
	dtlk_debug(DBG_INIT, "%s: ce5 read 0x%x\n",
		__func__,
		dlrx_cfg_ctxt_ce5buf_ptr->cfg_badr_target_ce5_read_index);
	dtlk_debug(DBG_INIT, "%s: ce5 write 0x%x\n",
		__func__,
		dlrx_cfg_ctxt_ce5buf_ptr->cfg_badr_target_ce5_write_index);
	dlrx_cfg_ctxt_ce5buf_ptr->local_ce5_parsing_index = 0;
	dlrx_cfg_ctxt_ce5buf_ptr->local_ce5_read_index = 0;

	dre_dl_set_mb_fn = dlrx_get_dre_fn(DRE_SET_MEMBASE_FN);
	if (dre_dl_set_mb_fn) {
#if defined(CONFIG_ACCL_11AC_CS2)
		struct _dl_ce5_resource *dl_ce5_resource;
		struct _dl_ce4_pflow_control *dl_ce4_pflow_control;
		dltx_cfg_global_t *mpe_dl_tx_cfg_global;
#endif
		dre_dl_set_mb_fn((unsigned int)ddr_base,
			(unsigned int)cfg_ctxt_base,
			(unsigned int)pcie_base
			);
#if defined(CONFIG_ACCL_11AC_CS2)
		dl_ce5_resource =
			(struct _dl_ce5_resource *)MPE_TX_ADDR(DLTX_CFG_CTXT_CE5_RESOURCE);
		mpe_dl_tx_cfg_global =
			(dltx_cfg_global_t *)MPE_TX_ADDR(DLTX_CFG_GLOBAL_OFFSET);

		/* copy from rx to tx */
		pr_info("%s: support CS2\n", __func__);
		memcpy(dl_ce5_resource,
			DLRX_CE5_RESOURCES_BASE,
			sizeof(struct _dl_ce5_resource));
		dl_ce5_resource->peer_id_mapping_base =
			(uint32_t)DLRX_CFG_PEER_ID_TO_PEER_MAP_BASE();
		mpe_dl_tx_cfg_global->qca_support_cs2 = 1;
#ifdef USING_BBCPU_SRAM
		dl_ce5_resource->bbcpu_dltx_rd_idx_base =
			(uint32_t)DLRX_BBCPU_CE5_CTXT_RD_IDX_BASE;
		dl_ce5_resource->bbcpu_dltx_wraparnd_cnt_base =
			(uint32_t)DLRX_BBCPU_CE5_CTXT_WRAPAROUND_IDX_BASE;
		dl_ce5_resource->bbcpu_qca_rd_idx_base =
			(uint32_t)DLRX_BBCPU_CE5_CTXT_QCA_RD_IDX_BASE;
		*DLRX_TARGET_CE5_READ_INDEX(0) =
			*DLRX_QCA_TARGET_CE5_READ_INDEX(0);
#endif
		/* init flow control */
		dl_ce4_pflow_control =
			(struct _dl_ce4_pflow_control *)MPE_TX_ADDR(DLTX_CFG_CTXT_CE5_PFLOW_CTRL);
		dl_ce4_pflow_control->pflow_msdu_default_ttl = DL_MSDU_DEFAULT_TTL;
		dl_ce4_pflow_control->pflow_cong_ctrl_timer_interval = DL_TX_PFLOW_CTRL_CONG_CTRL_TIMER_MS;
		dl_ce4_pflow_control->pflow_ctl_min_threshold = DL_TX_PFLOW_CTRL_MIN_THRESHOLD;
		dl_ce4_pflow_control->pmap_qdepth_flush_interval = DL_TX_PFLOW_CTRL_QDEPTH_FLUSH_INTERVAL;
		dl_ce4_pflow_control->pmap_rotting_timer_interval = DL_TX_PFLOW_CTRL_ROT_TIMER_MS;
#endif
	} else
		dtlk_debug(DBG_ERR, "Not register function: set membase!!!");

	return;
}
EXPORT_SYMBOL(ppa_dl_qca_t2h_ring_init);


/*
* This function gets called from QCA driver
* to initialize or free the Rx packet buffers pool.
*/
void ppa_dl_qca_t2h_pktbuf_pool_manage(
	uint32_t *alloc_idx_ptr,
	uint32_t *t2h_rxpb_ring_sz,
	uint32_t *rxpb_ring_base,
	uint32_t flags
	)
{
	dlrx_cfg_ctxt_rxpb_ptr_ring_t *dlrx_cfg_rxpb_ring;
	dlrx_cfg_rxpb_ring =
		(dlrx_cfg_ctxt_rxpb_ptr_ring_t *)DLRX_CFG_CTXT_RXPB_PTR_RING_BASE;

	if (flags == PPA_F_INIT) {
		*alloc_idx_ptr =
			(uint32_t)((unsigned int)&dlrx_cfg_rxpb_ring->rxpb_ptr_write_index | 0x20000000);
		*t2h_rxpb_ring_sz =
			dlrx_cfg_rxpb_ring->cfg_num_rxpb_ptr_ring;
		*rxpb_ring_base = dma_map_single(
			g_mpe_dev,
			(void *)dlrx_cfg_rxpb_ring->cfg_badr_rxpb_ptr_ring,
			4096 * 4,
			DMA_FROM_DEVICE
			);
		if (unlikely(dma_mapping_error(g_mpe_dev,
			(u64)*rxpb_ring_base)))
			dtlk_debug(DBG_ERR, "DMA error");

		dtlk_debug(DBG_INIT,
			"%s: return to QCA:\nalloc_idx_ptr[%x]\n",
			__func__,
			*alloc_idx_ptr);
		dtlk_debug(DBG_INIT,
			"t2h_rxpb_ring_sz[%d] rxpb_ring_base[0x%x]\n",
			*t2h_rxpb_ring_sz,
			*rxpb_ring_base);
	}

	return;
}
EXPORT_SYMBOL(ppa_dl_qca_t2h_pktbuf_pool_manage);

#if defined(CONFIG_ACCL_11AC_CS2)

uint8_t g_peerid;

static int32_t dl_ltq_try_gswapi_kioctl(uint32_t command, uint32_t arg)
{
    uint16_t retry_conf;
    int32_t ret;
    GSW_API_HANDLE gswr;
    retry_conf = 0;
    gswr = gsw_api_kopen("/dev/switch_api/1");

    if (gswr == 0) {
		pr_err("%s: Open SWAPI device FAILED !!\n", __func__);
		return PPA_FAILURE;
    }

retry_config:
	ret = gsw_api_kioctl(gswr, command, arg);
	if (ret < GSW_statusOk) {
		if (ret == GSW_statusLock_Failed) {
			retry_conf++;
			if (retry_conf < 8)
				goto retry_config;
		}
	}

	gsw_api_kclose(gswr);
	return ret;
}


int32_t dl_update_bridging_entry(GSW_MAC_tableRead_t *mac_entry)
{
	int ret;
	GSW_MAC_tableAdd_t entry = {0};

	entry.nFId = mac_entry->nFId;
	entry.nPortId = mac_entry->nPortId;
	entry.nSubIfId = mac_entry->nSubIfId;
	entry.bStaticEntry = mac_entry->bStaticEntry;
	entry.nAgeTimer = mac_entry->nAgeTimer;

	memcpy(entry.nMAC, mac_entry->nMAC, sizeof(uint8_t)*PPA_ETH_ALEN);

	if (!dp_get_port_info_via_allocflags(entry.nPortId, DP_F_DIRECTLINK)) {
		pr_err("add_bridging_entry returned failure\n");
		return -1;
	}
	ret = dl_ltq_try_gswapi_kioctl(
		GSW_MAC_TABLE_ENTRY_ADD,
		(unsigned int)&entry
	);
	if (ret < GSW_statusOk) {
		pr_err("add_bridging_entry returned failure\n");
		ret = -1;
	}

	pr_info("\n:::::: Updating_bridging_entry :::::::: \n src_mac=%02x:%02x:%02x:%02x:%02x:%02x\n port=%0x\n subifid=%0x fid=%x\n static=%d\n",
		entry.nMAC[0], entry.nMAC[1], entry.nMAC[2],
		entry.nMAC[3], entry.nMAC[4], entry.nMAC[5],
		entry.nPortId, entry.nSubIfId, entry.nFId, entry.bStaticEntry
	);
	return ret;
}

int32_t update_bridging_entry(uint8_t  mac[PPA_ETH_ALEN], uint16_t peer_id)
{
	GSW_MAC_tableRead_t mac_entry = {0};
	int32_t ret;
	memset(&mac_entry, 0x00, sizeof(mac_entry));

	mac_entry.bInitial = 1;

	for (;;) {
		ret = dl_ltq_try_gswapi_kioctl(
			GSW_MAC_TABLE_ENTRY_READ,
			(unsigned int)&mac_entry
		);
		if (ret < GSW_statusOk) {
			pr_err("get_bridging_entry returned failure\n");
			return -1;
		}

		pr_info("\nBridging_entry got\n src_mac=%02x:%02x:%02x:%02x:%02x:%02x\n port=%0x\n subifid=%0x fid=%x\n static=%d\n",
			mac_entry.nMAC[0], mac_entry.nMAC[1], mac_entry.nMAC[2],
			mac_entry.nMAC[3], mac_entry.nMAC[4], mac_entry.nMAC[5],
			mac_entry.nPortId, mac_entry.nSubIfId, mac_entry.nFId,
			mac_entry.bStaticEntry);

		if (!memcmp(mac, mac_entry.nMAC, sizeof(uint8_t)*PPA_ETH_ALEN)) {
			mac_entry.nSubIfId = ((mac_entry.nSubIfId && 0x00) | peer_id);
			dl_update_bridging_entry(&mac_entry);
			return 1;
		}
		if (mac_entry.bLast == 1)
			break;
	}

	return ret;
}

#endif


int32_t ppa_dl_qca_set_wds_peer_cfg(
	uint32_t *dlrx_peer_reg_handle,
	uint16_t peer_id,
	uint16_t vap_id,
	PPA_QCA_PEER_ADD_REMOVE_FLAG_Type_t flags,
    uint8_t *mac_addr
	)
{
	struct _dl_peer_mac_mapping_table dl_peer_mac_mapping;
	uint32_t peer_idx;
	char *temp, *tempDL;

	dtlk_debug(DBG_RX, "peer handler: 0x%x, peer id: %d, flags: %d\n",
		(unsigned int)dlrx_peer_reg_handle,
		peer_id,
		flags
		);
	temp = mac_addr;
	tempDL = (char *)&dl_peer_mac_mapping + 2;
	dl_peer_mac_mapping.mac5 = 0;
	dl_peer_mac_mapping.mac4 = 0;
	dl_peer_mac_mapping.mac3 = 0;
	dl_peer_mac_mapping.mac2 = 0;
	dl_peer_mac_mapping.mac1 = 0;
	dl_peer_mac_mapping.mac0 = 0;
	memcpy((char *)tempDL, temp, 6);
	dl_peer_mac_mapping.valid = 1;
	dl_peer_mac_mapping.vap_id = vap_id;
	dtlk_debug(DBG_INIT,
		"%s: %d %x:%x:%x:%x:%x:%x\n",
		__func__,
		dl_peer_mac_mapping.vap_id,
		dl_peer_mac_mapping.mac5,
		dl_peer_mac_mapping.mac4,
		dl_peer_mac_mapping.mac3,
		dl_peer_mac_mapping.mac2,
		dl_peer_mac_mapping.mac1,
		dl_peer_mac_mapping.mac0
	);
	/* get peer idx from peer id */
	switch (flags) {
	case PPA_WLAN_ADD_PEER_ID:
		/* Set peer ID to peer */
		if (vap_id >= MAX_VAP_NUM)
			return DTLK_FAILURE;
		if (!ppa_dl_dre_peer_from_peerid(peer_id, &peer_idx)) {
			dtlk_debug(DBG_ERR,
				"Peer does not exist: peer_id: %d, vap_id %d\n",
				peer_id, vap_id);
			return DTLK_FAILURE;
		}
		dl_m2c_add_peer((unsigned int *)mac_addr,
			peer_idx,
			vap_id,
			DRE_DIRECT_CLIENT_WDS_TABLE
		);
		dtlk_debug(DBG_ERR,
			"Add wds peer idx: %d, peer_id: %d, vap_id %d\n",
			peer_idx,
			peer_id, vap_id);
#if defined(CONFIG_ACCL_11AC_CS2)
		update_bridging_entry(mac_addr, peer_idx);
#endif
	break;
	case PPA_WLAN_REMOVE_PEER:
		dtlk_debug(DBG_ERR, "Remove wds peer: peer_id: %d, vap_id %d\n",
			peer_id, vap_id);
		dl_m2c_remove_peer(
			(unsigned int *)mac_addr,
			peer_id + 1,
			vap_id,
			DRE_DIRECT_CLIENT_WDS_TABLE);
		break;
	default:
		dtlk_debug(DBG_ERR,
			"Don't support: peer_id: %d, vap_id %d, flags[%d]\n",
			peer_id,
			vap_id,
			flags
		);
		break;
	}
	return DTLK_SUCCESS;
}
EXPORT_SYMBOL(ppa_dl_qca_set_wds_peer_cfg);
/*
* This hook function is invoked by QCA WLAN
* Driver for addition or deletion of peer.
*/
int32_t ppa_dl_qca_set_peer_cfg(
	uint32_t *dlrx_peer_reg_handle,
	uint16_t peer_id,
	uint16_t vap_id,
	PPA_WLAN_PN_CHECK_Type_t pn_chk_type,
	uint32_t *rxpn,
	uint32_t flags,
	uint8_t *mac_addr
	)
{
	/* Each Peer_id can have 8 peer values */
	unsigned int peer;
	unsigned int temp_acc_dis;
	unsigned int temp_vap_id;
	unsigned int temp_sec_type;
	dre_dl_set_rxpn_fn_t dre_dl_set_rxpn_fn;
	struct _dl_peer_mac_mapping_table dl_peer_mac_mapping;
	char *temp, *tempDL;

	dtlk_debug(DBG_RX, "peer handler: 0x%x, peer id: %d, flags: %d\n",
		(unsigned int)dlrx_peer_reg_handle,
		peer_id,
		flags
		);
	temp = mac_addr;
	tempDL = (char *)&dl_peer_mac_mapping + 2;
	dl_peer_mac_mapping.mac5 = 0;
	dl_peer_mac_mapping.mac4 = 0;
	dl_peer_mac_mapping.mac3 = 0;
	dl_peer_mac_mapping.mac2 = 0;
	dl_peer_mac_mapping.mac1 = 0;
	dl_peer_mac_mapping.mac0 = 0;
	memcpy((char *)tempDL, temp, 6);
	dl_peer_mac_mapping.valid = 1;
	dl_peer_mac_mapping.vap_id = vap_id;
	dtlk_debug(DBG_INIT,
		"%s: %d %x:%x:%x:%x:%x:%x\n",
		__func__,
		dl_peer_mac_mapping.vap_id,
		dl_peer_mac_mapping.mac5,
		dl_peer_mac_mapping.mac4,
		dl_peer_mac_mapping.mac3,
		dl_peer_mac_mapping.mac2,
		dl_peer_mac_mapping.mac1,
		dl_peer_mac_mapping.mac0
		);
	switch (flags) {
	case PPA_WLAN_ADD_PEER_ID:
		/* Set peer ID to peer */
		if (vap_id >= MAX_VAP_NUM)
			return DTLK_FAILURE;

		if (set_peer_id_to_peer_table(
				(uint32_t)dlrx_peer_reg_handle,
				peer_id,
				&peer,
				(unsigned int)vap_id,
				(unsigned int)pn_chk_type
				) != DTLK_SUCCESS)
			return DTLK_FAILURE;

		dtlk_debug(DBG_ERR,
			"peer: %d, peer_id: %d, vap_id %d, pn_chk_type: %d\n",
			peer,
			peer_id, vap_id, pn_chk_type);
		dl_m2c_add_peer((unsigned int *)mac_addr,
			peer,
			vap_id,
			DRE_DIRECT_CLIENT_TABLE
		);

#if defined(CONFIG_ACCL_11AC_CS2)
		g_peerid = peer_id;
		update_bridging_entry(mac_addr, peer);
#endif
	break;

	case PPA_WLAN_REMOVE_PEER:/* FOR DELETE PEER */
		if (remove_peer_from_table(
				(uint32_t)dlrx_peer_reg_handle,
				(uint32_t)peer_id) != DTLK_SUCCESS)
			return DTLK_FAILURE;
		dtlk_debug(DBG_ERR, "remove peer: peer_id: %d, vap_id %d\n",
			peer_id, vap_id);
		dl_m2c_remove_peer(
			(unsigned int *)mac_addr,
			peer_id + 1,
			vap_id,
			DRE_DIRECT_CLIENT_TABLE);
	break;

	case PPA_WLAN_REMOVE_PEER_ID:/* For Delete PEER_ID */
		dtlk_debug(DBG_ERR, "remove peer_id: peer_id: %d, vap_id %d\n",
			peer_id, vap_id);
		if (remove_peer_id_from_table(
			(uint32_t)dlrx_peer_reg_handle,
			(uint32_t)peer_id) != DTLK_SUCCESS)
			return DTLK_FAILURE;
	break;

	case PPA_WLAN_SET_PN_CHECK:/* To Update PN SEC TYPE */
		peer = get_handler_index(
			(uint32_t)dlrx_peer_reg_handle
			);
		if (peer == HANDLER_NOT_FOUND)
			return DTLK_FAILURE;

		ppa_dl_dre_vapinfo_from_peer(
			peer,
			&temp_vap_id,
			&temp_sec_type,
			&temp_acc_dis
			);
		if (ppa_dl_dre_vapinfo_set(
				peer,
				temp_vap_id,
				(unsigned int)pn_chk_type,
				temp_acc_dis) == DTLK_SUCCESS) {
			/*
			* Peer may still store old information
			* from previous connection.
			* Reset Peer information as well as PNs value.
			*/
			dlrx_ro_mainlist_t *dlrx_ro_mainlist_ptr;
			int seqid = 0;
			int tid = 0;
			dlrx_ro_mainlist_ptr =
				(dlrx_ro_mainlist_t *)DLRX_DDR_RO_MAINLIST_BASE;
			dlrx_ro_mainlist_ptr += (peer*NUM_TID);
			for (tid = 0; tid < NUM_TID; tid++) {
				dlrx_ro_mainlist_ptr->last_pn_dw0 = 0;
				dlrx_ro_mainlist_ptr->last_pn_dw1 = 0;
				dlrx_ro_mainlist_ptr->last_pn_dw2 = 0;
				dlrx_ro_mainlist_ptr->last_pn_dw3 = 0;
				dlrx_ro_mainlist_ptr->first_ptr = NULL_PTR;
				for (seqid = 1; seqid < 64; seqid++)
					dlrx_ro_mainlist_ptr->_dw_res0[seqid-1] = NULL_PTR;
				dlrx_ro_mainlist_ptr++;
			}
		}
		dtlk_debug(DBG_RX,
			"peer:%d,peer_id:%d,vap_id:%d,",
			peer,
			peer_id,
			temp_vap_id
			);
		dtlk_debug(DBG_RX,
			"sec_type:%d,acc_dis:%d\n",
			pn_chk_type,
			temp_acc_dis
			);
	break;

	case PPA_WLAN_SET_PN_CHECK_WITH_RXPN:
		peer = get_handler_index(
			(uint32_t)dlrx_peer_reg_handle
			);
		if (peer == HANDLER_NOT_FOUND) {
			dtlk_debug(DBG_ERR, "Invalid peer");
			return DTLK_FAILURE;
		}
		ppa_dl_dre_vapinfo_from_peer(
			peer,
			&temp_vap_id,
			&temp_sec_type,
			&temp_acc_dis
			);
		ppa_dl_dre_vapinfo_set(
			peer,
			temp_vap_id,
			(unsigned int)pn_chk_type,
			temp_acc_dis
			);
		dtlk_debug(DBG_RX,
			"SET PN:peer:%d,peer_id:%d,vap_id:%d,",
			peer,
			peer_id,
			temp_vap_id
			);
		dtlk_debug(DBG_RX,
			"sec_type:%d,acc_dis:%d,rxpn:0x%x\n",
			pn_chk_type,
			temp_acc_dis,
			(uint32_t)rxpn
			);
		dre_dl_set_rxpn_fn = dlrx_get_dre_fn(DRE_SET_RXPN_FN);
		if (likely(dre_dl_set_rxpn_fn))
			dre_dl_set_rxpn_fn(peer, rxpn);
		else
			dtlk_debug(
				DBG_ERR,
				"Function set_rxpn is not registered!"
			);

	break;
	}

	return DTLK_SUCCESS;
}
EXPORT_SYMBOL(ppa_dl_qca_set_peer_cfg);
#if defined(CONFIG_ACCL_11AC_CS2)
static void dl_tx_mpe_fw_update_peer_map(uint32_t peer_index,
	uint32_t peer_id)
{
	unsigned int *dl_tx_fw_peer_map_tbl =
		(unsigned int *)MPE_TX_ADDR(DLTX_CE5_PEER_MAP_TO_PEER_ID);
	dl_tx_fw_peer_map_tbl += peer_index;
	*dl_tx_fw_peer_map_tbl = peer_id;
}
unsigned int dl_tx_get_peer_id_from_peer_idx(uint32_t peer_index)
{
	unsigned int *dl_tx_fw_peer_map_tbl =
		(unsigned int *)MPE_TX_ADDR(DLTX_CE5_PEER_MAP_TO_PEER_ID);
	dl_tx_fw_peer_map_tbl += peer_index;
	return *dl_tx_fw_peer_map_tbl;
}
extern int32_t dl_set_dscp_tid(void *cfg);
int32_t ppa_dl_qca_set_dscp_tid_map (
	uint32_t *dscp_tid_map_ptr,
	uint32_t vap_id,
	uint32_t flags
)
{
	uint8_t *dscp_tables;
	int i = 0;
	pr_info("<%s>: [0x%p]vapid[%d]flags[%d]\n",
		__func__,
		dscp_tid_map_ptr,
		vap_id,
		flags
		);
	/* copy dscp table from user setting */
	dscp_tables = (uint8_t *)MPE_TX_ADDR(DLTX_PFLOW_DSCP_TID_TABLE);
	for (i = 0; i < WMI_DSCP_MAP_MAX; i++)
		*(dscp_tables + i) = (uint8_t)(*(dscp_tid_map_ptr + i));

	dl_set_dscp_tid((void *)(dscp_tables));
	return 0;
}
EXPORT_SYMBOL(ppa_dl_qca_set_dscp_tid_map);

#endif
int set_peer_id_to_peer_table(
	uint32_t dlrx_peer_reg_handle,
	uint32_t peer_id,
	uint32_t *peer,
	unsigned int vap_id,
	unsigned int pn_chk_type
	)
{
	unsigned int vld;
	unsigned int peer_val;
	unsigned int peer_index;
	unsigned int peer_offset;
	unsigned int mask_value;
	unsigned int peerinfo;
	unsigned int temp_peerinfo;
	int handler_index;
	unsigned int *pid2p_tbl =
		DLRX_CFG_PEER_ID_TO_PEER_MAP_BASE(0);
	dlrx_cfg_ctxt_peer_handler_t *peer_handler_tbl = NULL;

	handler_index = get_handler_index(dlrx_peer_reg_handle);
	dtlk_debug(DBG_RX,
		"%s: peer: %d, peer_id:%d\n",
		__func__,
		handler_index,
		peer_id
		);

	if (handler_index == HANDLER_NOT_FOUND) {
		if (get_free_peer_number(&peer_val) == DTLK_FAILURE)
			return DTLK_FAILURE;

		/* Get the handler index address by using the base address */
		peer_handler_tbl =
			(dlrx_cfg_ctxt_peer_handler_t *)DLRX_CFG_CTXT_PEER_HANDLER_BASE(peer_val);
		/* Send the handler table data */
		peer_handler_tbl->cfg_peer_count++;
		peer_handler_tbl->cfg_peer_handler = dlrx_peer_reg_handle;
	} else {
		/* Get the handler index address by using the base address */
		peer_handler_tbl =
			(dlrx_cfg_ctxt_peer_handler_t *)DLRX_CFG_CTXT_PEER_HANDLER_BASE(handler_index);
		peer_handler_tbl->cfg_peer_count++;
		peer_val = (unsigned int)handler_index;
	}

	ppa_dl_dre_vapinfo_set(peer_val, vap_id, pn_chk_type, 0);

	vld = VALID;
	peerinfo = ((vld << 7) | (peer_val & 0x7F));

	peer_index = peer_id >> 2;
	peer_offset = peer_id % 4;

	mask_value = ~(0xFF << (peer_offset * 8));

	spin_lock_bh(&g_prid2pr_tbl_lock);
	temp_peerinfo = *(pid2p_tbl + peer_index);
	temp_peerinfo &= mask_value;
	*(pid2p_tbl + peer_index) =
		(temp_peerinfo | (peerinfo << (peer_offset << 3)));
	spin_unlock_bh(&g_prid2pr_tbl_lock);

	*peer = peer_val;
#if defined(CONFIG_ACCL_11AC_CS2)
	dl_tx_mpe_fw_update_peer_map(peer_val, peer_id);
#endif
	return DTLK_SUCCESS;
}

int remove_peer_from_table(
	uint32_t dlrx_peer_reg_handle,
	uint32_t peer_id
	)
{
	int handler_index;
	unsigned int peer;
	unsigned int loop_index_1;
	unsigned int loop_index_2;
	unsigned int peer_id_loop_num;
	unsigned int temp_peerinfo;
	unsigned int peerinfo;
	unsigned int temp_peer;
	unsigned int temp_peer_vld;
	unsigned int mask_value;
	dlrx_cfg_ctxt_peer_handler_t *peer_handler_tbl = NULL;
	unsigned int *pid2p_tbl = DLRX_CFG_PEER_ID_TO_PEER_MAP_BASE(0);
	dre_dl_reset_fn_t dre_dl_reset_fn;
	unsigned int *peer_bit_field;
	unsigned int peer_bit_field_offset;
	unsigned int peer_bit_field_index;

	peer_bit_field = (unsigned int *)DLRX_CFG_CTXT_PEER_BITMAP_BASE(0);
	/* have 4 element */

	handler_index = get_handler_index(dlrx_peer_reg_handle);

	if (handler_index == HANDLER_NOT_FOUND)
		return DTLK_FAILURE;
	else {
		peer = (unsigned int)handler_index;
		/* Get the handler index address by using the base address */
		peer_handler_tbl =
			(dlrx_cfg_ctxt_peer_handler_t *)DLRX_CFG_CTXT_PEER_HANDLER_BASE(peer);
		/* Send the handler table data */
		peer_handler_tbl->cfg_peer_handler = 0;

		peer_id_loop_num = MAX_PEERID_NUM >> 2;

		if (peer_handler_tbl->cfg_peer_count) {
			spin_lock_bh(&g_prid2pr_tbl_lock);
			for (loop_index_1 = 0;
					loop_index_1 < peer_id_loop_num;
					loop_index_1++) {
				temp_peerinfo = *(pid2p_tbl + loop_index_1);
				for (loop_index_2 = 0;
					loop_index_2 < 4;
					loop_index_2++) {
					mask_value =
						(0xFF << (loop_index_2 << 3));
					peerinfo =
						(temp_peerinfo & mask_value) >>
						(loop_index_2 << 3);
					temp_peer = peerinfo & 0x7F;
					temp_peer_vld = (peerinfo & 0x80) >> 7;
					if ((temp_peer_vld == 1) &&
						(temp_peer == peer)) {
						peerinfo = 0;
						mask_value = ~mask_value;
						temp_peerinfo &= mask_value;
						*(pid2p_tbl + loop_index_1) =
							temp_peerinfo;
					}
				}
			}
			spin_unlock_bh(&g_prid2pr_tbl_lock);
		}
		peer_handler_tbl->cfg_peer_count = 0;

		dtlk_debug(DBG_RX,
			"%s: reset_peer, peer: %d\n", __func__, peer);
		dre_dl_reset_fn = dlrx_get_dre_fn(DRE_RESET_FN);
		if (likely(dre_dl_reset_fn))
			dre_dl_reset_fn(DRE_RESET_PEER, peer);
		else
			dtlk_debug(DBG_ERR,
				"Function DRE_RESET_PEER is not registered!");

		ppa_dl_dre_vapinfo_set(peer, 0, 0, 0);

		/* Set the corresponding peer bit field value to 0 */
		peer_bit_field_offset = peer >> 5;/* Divide by 32 */
		peer_bit_field_index = peer % 32;
		/* Calculate the mask value
		* to set the corresponding peer bit to zero */
		mask_value = ~(1 << peer_bit_field_index);
		peer_bit_field[peer_bit_field_offset] &= mask_value;
	}
	return DTLK_SUCCESS;
}


/*
* Remove peer ID PEER table
*/
int remove_peer_id_from_table(
	uint32_t dlrx_peer_reg_handle,
	uint32_t peer_id
	)
{
	unsigned int handler_index;
	unsigned int peer_index;
	unsigned int peer_offset;
	unsigned int peer;
	unsigned int temp_peerinfo;
	unsigned int mask_value;
	dlrx_cfg_ctxt_peer_handler_t *peer_handler_tbl = NULL;
	unsigned int *pid2p_tbl = DLRX_CFG_PEER_ID_TO_PEER_MAP_BASE(0);

	handler_index = get_handler_index(dlrx_peer_reg_handle);

	dtlk_debug(DBG_RX, "%s: peer: %d\n", __func__, handler_index);
	if (handler_index == HANDLER_NOT_FOUND)
		return DTLK_FAILURE;
	else {
		peer_index = peer_id >> 2;
		peer_offset = peer_id % 4;
		peer = (unsigned int)handler_index;
		/* Get the handler index address by using the base address */
		peer_handler_tbl =
			(dlrx_cfg_ctxt_peer_handler_t *)DLRX_CFG_CTXT_PEER_HANDLER_BASE(peer);
		/* Send the handler table data */
		peer_handler_tbl->cfg_peer_count--;
		mask_value = ~(0xFF << (peer_offset * 8));
		spin_lock_bh(&g_prid2pr_tbl_lock);
		temp_peerinfo = *(pid2p_tbl + peer_index);
		temp_peerinfo &= mask_value;
		*(pid2p_tbl + peer_index) = temp_peerinfo;
		spin_unlock_bh(&g_prid2pr_tbl_lock);
	}

	return DTLK_SUCCESS;
}

int get_handler_index(
	uint32_t dlrx_peer_reg_handle
	)
{
	int index;
	int handler_index = HANDLER_NOT_FOUND;
	dlrx_cfg_ctxt_peer_handler_t *peer_handler_tbl = NULL;

	for (index = 0; index < MAX_PEER_NUM; index++) {
		peer_handler_tbl =
			(dlrx_cfg_ctxt_peer_handler_t *)DLRX_CFG_CTXT_PEER_HANDLER_BASE(index);
		if (peer_handler_tbl->cfg_peer_handler ==
			dlrx_peer_reg_handle)
			return index;
	}
	return handler_index;
}

int get_free_peer_number(
	unsigned int *peer_val
	)
{
	unsigned int index;
	unsigned int temp_bit_field;
	unsigned int free_peer_num = 0;
	unsigned int *peer_bit_field;

	/* To store handler value and number
	* of peer count for each handler
	* NOTE : MAXIMUM SUPPORTED
	* HANDLER VALUE IS 128
	*/
	/* have 4 element */
	peer_bit_field = (unsigned int *)DLRX_CFG_CTXT_PEER_BITMAP_BASE(0);
	for (index = 0; index < 4; index++) {
		temp_bit_field = peer_bit_field[index];
		/* No free peer in this Dword */
		if (temp_bit_field == 0xFFFFFFFF) {
			free_peer_num += 32;
			continue;
		}
		while (temp_bit_field & 1) {
			temp_bit_field >>= 1;
			free_peer_num++;
		}
		break;
	}
	if (index >= 4)
		return DTLK_FAILURE;

	*peer_val = free_peer_num;
	peer_bit_field[index] =
		(peer_bit_field[index] | (1 << (*peer_val % 32)));

	return DTLK_SUCCESS;
}


/* This function transfers control for DirectLink in CE-5 Rx in system.
* The function gets called by QCA WLAN driver as part of handling
* legacy interrupt when CE-5 handling is made.
* Flags -- This is used for future use
*/
int32_t ppa_hook_dl_qca_rx_offload(
	uint32_t flags
	)
{
#if defined(CONFIG_ACCL_11AC_CS2)
	return DTLK_SUCCESS;
#else
	int ret = DTLK_FAILURE;
	dre_dl_main_fn_t dre_dl_main_fn;
	/*dtlk_debug(DBG_RX, "%s\n", __func__);*/
	dre_dl_main_fn = dlrx_get_dre_fn(DRE_MAIN_FN);
	if (likely(dre_dl_main_fn))
		ret = dre_dl_main_fn();
	else
		dtlk_debug(
			DBG_ERR,
			"FW Callback: dre_main is not registered"
			);

	return (int32_t)ret;
#endif
}
EXPORT_SYMBOL(ppa_hook_dl_qca_rx_offload);

/*
* This function picks a corresponding network packet buffer
* for previous handed over message in callback. The function
* gets called by QCA WLAN driver after its PPA_QCA_DL_RX_MSG_FN
* callback gets a message of type RX_IND or RX_FRAG_IND to it.
* This network buffer should be getting freed
* inside QCA driver or somewhere in the path of protocol stack.
*/
int32_t ppa_dl_qca_get_rx_net_buf(
	struct sk_buff **rx_skb,
	uint32_t flags
	)
{
	int ret = DTLK_SUCCESS;
	dre_dl_getmsdu_fn_t dre_dl_getmsdu_fn;
	unsigned int rx_pb, data_len;
	unsigned int padding_flags;
	unsigned int padding_bytes;
	/* dtlk_debug(DBG_RX, "%s: -\n", __func__); */
	*rx_skb = NULL;
	dre_dl_getmsdu_fn = dlrx_get_dre_fn(DRE_GET_CURMSDU_FN);
	if (likely(dre_dl_getmsdu_fn)) {
		ret = dre_dl_getmsdu_fn(&rx_pb, &data_len, &padding_flags);
		if (ret != DTLK_SUCCESS)
			return (int32_t)ret;
	} else {
		dtlk_debug(DBG_ERR,
			"FW CallBack: get_curmsdu is not registered!");
		return (int32_t)ret;
	}
	dtlk_debug(DBG_RX,
		"%s: rx_pb[0x%x] len[%d] flags[%x]\n",
		__func__,
		rx_pb,
		data_len,
		padding_flags
		);

	padding_bytes = (padding_flags >> 16);
	*rx_skb =
		dlrx_skb_setup(
			rx_pb,
			rx_pb,
			data_len + g_dlrx_cfg_offset_atten + padding_bytes
			);

	return DTLK_SUCCESS;
}
EXPORT_SYMBOL(ppa_dl_qca_get_rx_net_buf);

/* Return MIB information to QCA driver */
int32_t ppa_dl_qca_get_msg_mdu_stats(
	PPA_DL_WLAN_MSG_STATS_t *msg_stats,
	PPA_DL_WLAN_RX_MPDU_MSDU_STATS_t *mdu_stats,
	uint32_t flags
	)
{
	dlrx_data_mib_t *wlan_mdu_stats =
		(dlrx_data_mib_t *)DLRX_DATA_MIB_BASE;
	dlrx_msg_mib_t *wlan_msg_stats =
		(dlrx_msg_mib_t *)DLRX_MSG_MIB_BASE;

	msg_stats->ce4_cpu_msgs = wlan_msg_stats->total_ce4_cpu_msg;
	msg_stats->ce5_cpu_msgs = wlan_msg_stats->total_ce5_cpu_msg;
	msg_stats->rx_ind_msgs = wlan_msg_stats->total_rx_ind_msg;
	msg_stats->rx_flush_msgs = wlan_msg_stats->total_rx_flush_msg;
	msg_stats->tx_comp_msgs = wlan_msg_stats->total_tx_cmp_msg;
	msg_stats->rx_ind_wl_msgs = wlan_msg_stats->total_rx_ind_wlan_msg;
	msg_stats->rx_flush_wl_msgs = wlan_msg_stats->total_rx_flush_wlan_msg;
	msg_stats->rx_frag_msgs = wlan_msg_stats->total_rx_frag_ind_msg;

	mdu_stats->rx_mpdu_ok = wlan_mdu_stats->rx_success_mpdu;
	mdu_stats->rx_msdu_ok = wlan_mdu_stats->rx_success_msdu;
	mdu_stats->rx_mpdu_err2 = wlan_mdu_stats->rx_error2_mpdu;
	mdu_stats->rx_msdu_err2 = wlan_mdu_stats->rx_error2_msdu;
	mdu_stats->rx_mpdu_err3 = wlan_mdu_stats->rx_error3_mpdu;
	mdu_stats->rx_msdu_err3 = wlan_mdu_stats->rx_error3_msdu;
	mdu_stats->rx_mpdu_err4 = wlan_mdu_stats->rx_error4_mpdu;
	mdu_stats->rx_msdu_err4 = wlan_mdu_stats->rx_error4_msdu;
	mdu_stats->rx_mpdu_err5 = wlan_mdu_stats->rx_error5_mpdu;
	mdu_stats->rx_msdu_err5 = wlan_mdu_stats->rx_error5_msdu;
	mdu_stats->rx_mpdu_err6 = wlan_mdu_stats->rx_error6_mpdu;
	mdu_stats->rx_msdu_err6 = wlan_mdu_stats->rx_error6_msdu;
	mdu_stats->rx_mpdu_err7 = wlan_mdu_stats->rx_error7_mpdu;
	mdu_stats->rx_msdu_err7 = wlan_mdu_stats->rx_error7_msdu;
	mdu_stats->rx_mpdu_err8 = wlan_mdu_stats->rx_error8_mpdu;
	mdu_stats->rx_msdu_err8 = wlan_mdu_stats->rx_error8_msdu;
	mdu_stats->rx_mpdu_err9 = wlan_mdu_stats->rx_error9_mpdu;
	mdu_stats->rx_msdu_err9 = wlan_mdu_stats->rx_error9_msdu;
	mdu_stats->rx_mpdu_errA = wlan_mdu_stats->rx_errora_mpdu;
	mdu_stats->rx_msdu_errA = wlan_mdu_stats->rx_errora_msdu;

	return DTLK_SUCCESS;
}
EXPORT_SYMBOL(ppa_dl_qca_get_msg_mdu_stats);

int32_t ppa_dl_qca_set_seq_mask(
	uint32_t *dlrx_peer_reg_handle,
	uint32_t ex_tid,
	uint32_t seq_mask,
	uint32_t flags
	)
{
	int peer;
	uint32_t *seq_mask_base = DLRX_DDR_SEQ_MASK_BASE;

	if (unlikely(!dlrx_peer_reg_handle))
		return DTLK_FAILURE;

	peer = get_handler_index((uint32_t)dlrx_peer_reg_handle);
	if (unlikely(peer == HANDLER_NOT_FOUND))
		return DTLK_FAILURE;


	seq_mask_base[(peer * (NUM_TID + 1)) + ex_tid] = seq_mask;

	return DTLK_SUCCESS;
}
EXPORT_SYMBOL(ppa_dl_qca_set_seq_mask);

#if defined(CONFIG_ACCL_11AC_CS2)
int32_t ppa_dl_qca_set_pflow_cfg (
    PFLOW_CFG_TYPE pflow_cfg_type,
    uint32_t  peer_id,   /* peer id ,  set to   0xffff => for all peer Id*/
    uint32_t tid,
    uint32_t cfg_value
)
{
	struct _dl_ce4_pflow_control *dl_pflow_control;
	dl_pflow_control =
		(struct _dl_ce4_pflow_control *)MPE_TX_ADDR(DLTX_CFG_CTXT_CE4_PFLOW_CTRL);
	switch (pflow_cfg_type)	{
	case PFLOW_CFG_TYPE_CTRL_MIN_THRESHOLD:
		dl_pflow_control->pflow_ctl_min_threshold = cfg_value;
		break;
	case PFLOW_CFG_TYPE_CTRL_MAX_BUF_GLOBAL:
		dl_pflow_control->pflow_ctl_max_buf_global = cfg_value;
		break;
	case PFLOW_CFG_TYPE_CTRL_MAX_QUEUE_LEN:
		dl_pflow_control->pflow_ctl_max_queue_len = cfg_value;
		break;
	case PFLOW_CFG_TYPE_CTRL_MIN_QUEUE_LEN:
		dl_pflow_control->pflow_ctl_min_queue_len = cfg_value;
		break;
	case PFLOW_CFG_TYPE_CTRL_QDEPTH_FLUSH_INTERVAL:
		dl_pflow_control->pmap_qdepth_flush_interval = cfg_value;
		break;
	case PFLOW_CFG_TYPE_CTRL_CONG_CTRL_TIMER_MS:
		dl_pflow_control->pflow_cong_ctrl_timer_interval = cfg_value;
		break;
	case PFLOW_CFG_TYPE_CTRL_STATS_TIMER_MS:
		dl_pflow_control->pflow_ctl_stats_timer_interval = cfg_value;
		break;
	case PFLOW_CFG_TYPE_CTRL_ROT_TIMER_MS:
		dl_pflow_control->pmap_rotting_timer_interval = cfg_value;
		break;
	case PFLOW_CFG_TYPE_CTRL_DEQUEUE_TIMER_MS:
		break;
	case PFLOW_CFG_TYPE_MSDU_DEFAULT_TTL:
		dl_pflow_control->pflow_msdu_default_ttl = cfg_value;
		break;
	default:
		break;
	}
	return DTLK_SUCCESS;
}
EXPORT_SYMBOL(ppa_dl_qca_set_pflow_cfg);
#endif
/*************************************************
 *		   Functions called by datapath driver
 *************************************************/
void set_vap_itf_tbl(
	uint32_t vap_id,
	uint32_t fid
	)
{
	unsigned int *itf_tbl;
	unsigned int itf_id;
	dtlk_debug(DBG_RX, "%s: vap_id[%d] fid[%d]\n", __func__, vap_id, fid);
	if (vap_id >= MAX_VAP_NUM)
		return;
	/* Range is defined in the spec */
	if (vap_id <= 7)
		itf_tbl = DLRX_CFG_VAP2INT_MAP1_BASE;
	else
		itf_tbl = DLRX_CFG_VAP2INT_MAP2_BASE;


	vap_id = vap_id % 8;
	spin_lock_bh(&g_vap2int_tbl_lock);
	itf_id = *(itf_tbl);
	dtlk_debug(
		DBG_RX,
		"%s: itf_tbl[0x%p] itf_id[%x]\n",
		__func__, itf_tbl, itf_id
	);
	*(itf_tbl) =
		(itf_id & ~(0xF << (vap_id * 4))) |
		((fid & 0xF) << (vap_id * 4));
	dtlk_debug(
		DBG_RX,
		"%s: itf_tbl[%p] value[%x]\n",
		__func__, itf_tbl, *itf_tbl
	);
	spin_unlock_bh(&g_vap2int_tbl_lock);

	return;
}


/*************************************************
 *			Export Functions
 *************************************************/

