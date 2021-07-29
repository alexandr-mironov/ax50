/*
* Copyright (c) 2014 Lantiq Corporation
*
* Permission to use, copy, modify, and/or distribute this software for any
* purpose with or without fee is hereby granted, provided that the above
* copyright notice and this permission notice appear in all copies.
*
* THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
* WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
* MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY
* SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
* WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN ACTION
* OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF OR IN
* CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
*/


/*
 * ####################################
 *              Head File
 * ####################################
 */

/*
 *  Common Head File
 */
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/version.h>
#include <linux/types.h>
#include <linux/ctype.h>
#include <linux/fs.h>
#include <linux/proc_fs.h>
#include <linux/miscdevice.h>
#include <linux/init.h>
#include <linux/etherdevice.h>  /*  eth_type_trans  */
#include <linux/ethtool.h>      /*  ethtool_cmd     */
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
#include <net/directconnect_dp_api.h>
#include <net/ppa_api.h>
#include <net/ppa_stack_al.h>
#include <net/ppa_api_directpath.h>
#include <net/datapath_api.h>
#include <net/directconnect_dp_api.h>
#include <net/dc_ep.h>

#include "new_feature.h"
#include "datapath.h"
#include "../ltqmips_hal.h"
#include "eth1_qos_data_structure.h"


#define DSL_PORT 7
#define     MAX_DIRECTPATH_NUM      5
extern struct ppe_directpath_data g_ppe_directpath_data[MAX_DIRECTPATH_NUM];
extern int (*g_smartphy_push_fn)(struct sk_buff *, struct flag_header *, unsigned int);

#define DP_PORT_ID_TO_PORT_IDX(port_id) (port_id - 3)
char *dp_dbg_flag_str[] = {
	"dbg",			/*DP_DBG_FLAG_DBG */

	"rx",			/*DP_DBG_FLAG_DUMP_RX */
	"rx_data",		/*DP_DBG_FLAG_DUMP_RX_DATA*/

	"tx",			/*DP_DBG_FLAG_DUMP_TX */
	"tx_data",		/*DP_DBG_FLAG_DUMP_TX_DATA */

	/*the last one*/
	"err"
};


unsigned int dp_dbg_flag_list[] = {
	DP_DBG_FLAG_DBG,

	DP_DBG_FLAG_DUMP_RX,
	DP_DBG_FLAG_DUMP_RX_DATA,

	DP_DBG_FLAG_DUMP_TX,
	DP_DBG_FLAG_DUMP_TX_DATA,

};

#undef DP_F_ENUM_OR_STRING
#define DP_F_ENUM_OR_STRING(name,value, short_name) short_name
char *dp_port_type_str[] = {
	DP_F_FLAG_LIST
};
#undef DP_F_ENUM_OR_STRING

#undef DP_F_ENUM_OR_STRING
#define DP_F_ENUM_OR_STRING(name,value, short_name) value
uint32_t dp_port_flag[] = {
	DP_F_FLAG_LIST
};
#undef DP_F_ENUM_OR_STRING

char *dp_subif_status_str[] = {
	"SUBIF_FREE",
	"SUBIF_REGISTERED",
	"Invalid"
};

char *dp_port_status_str[] = {
	"PORT_NOT_READY",
	"PORT_FREE",
	"PORT_ALLOCATED",
	"PORT_DEV_REGISTERED",
	"PORT_SUBIF_REGISTERED",
	"Invalid"
};

static int32_t dp_init_ok;
spinlock_t dp_lock;
unsigned int dp_dbg_flag = 0;
struct dc_dp_res g_dcdp_resources[MAX_DIRECTPATH_NUM];
/*port 0 is reserved and never assigned to any one */
struct pmac_port_info dp_port_info[DP_MAX_PORT_IDX];

/***********Support functions***********/
int get_dp_port_type_str_size(void)
{
	return ARRAY_SIZE(dp_port_type_str);
}

int get_dp_dbg_flag_str_size()
{
	return ARRAY_SIZE(dp_dbg_flag_str);
}

int get_dp_port_status_str_size()
{
	return ARRAY_SIZE(dp_port_status_str);
}

int get_dp_subif_status_str_size()
{
	return ARRAY_SIZE(dp_subif_status_str);
}

static int dsl_push(struct sk_buff *skb, struct flag_header *header, unsigned int ifid)
{
	int sub_if;
	/* printk("%s: skb[%p]header[%p]ifid[%d]", __func__, skb, header, ifid); */
    if ( ifid == 6 /* IPoA/PPPoA */ || ifid == 7 /* EoA */ )
    {
    	uint32_t port_idx = DP_PORT_ID_TO_PORT_IDX(DSL_PORT);
    	if(skb->cb[13] == 0x5A)
    		sub_if=skb->cb[15];
    	else
    		sub_if =0;

    	if (g_ppe_directpath_data[port_idx].callback.rx_fn) {
    		g_ppe_directpath_data[port_idx].callback.rx_fn(
    			dp_port_info[port_idx].subif_info[sub_if].netif,
				NULL,
				skb,
				skb->len);
    	}
        return 0;
    }
    else{
        dev_kfree_skb_any(skb);
        return -EINVAL;
    }
}

static void dp_private_resource_save(int port_id, struct dc_dp_res *dcdp_res) {
	/* printk("%s: port_id[%d]\n\n", __func__, port_id); */
	memcpy(&g_dcdp_resources[DP_PORT_ID_TO_PORT_IDX(port_id)],
		dcdp_res,
		sizeof(struct dc_dp_res));
	dbg_pool_check(__func__);
}
static void dp_private_resource_free(int port_id) {
	struct dc_dp_res *dcdp_res = &g_dcdp_resources[DP_PORT_ID_TO_PORT_IDX(port_id)];
	struct dc_dp_buf_pool *pool;
	int i;
	pool = dcdp_res->buflist;
	/* printk("%s: dcdp_res->buflist[%p]dcdp_res->num_bufpools[%d]\n",
		__func__, dcdp_res->buflist, dcdp_res->num_bufpools); */
	if (pool) {
		for (i = 0; i < dcdp_res->num_bufpools; i++) {
			BUG_ON(!pool->pool);
			dc_dp_free_dma(pool->pool);
			pool++;
		}
	}
	if (dcdp_res->buflist)
		kfree(dcdp_res->buflist);
	pool = dcdp_res->tx_buflist;
	/* printk("%s: dcdp_res->tx_buflist[%p]dcdp_res->tx_num_bufpools[%d]\n",
		__func__, dcdp_res->tx_buflist, dcdp_res->tx_num_bufpools); */
	if (pool) {
		for (i = 0; i < dcdp_res->tx_num_bufpools; i++) {
			BUG_ON(!pool->pool);
			dc_dp_free_dma(pool->pool);
			pool++;
		}
	}
	if(dcdp_res->tx_buflist)
		kfree(dcdp_res->tx_buflist);
	dbg_pool_check(__func__);
}

void dp_dump_raw_data(char *buf, int len, char *prefix_str)
{
	int i;
	int r;
	int line_num = 32;
	unsigned char *p = (unsigned char *)buf;

	if (!p) {
		DP_ERROR("dp_dump_raw_data: p NULL ?\n");
		return ;
	}

	DP_INFO("%s in hex at 0x%p\n", prefix_str ? (char *)prefix_str : "Data", p);

	for (i = 0; i < len; i++) {
		r = i % line_num;

		if (r == 0)
			DP_INFO(" %04d: ", i);
		else if (r == (line_num / 2))
			DP_INFO(" "); /*inser seperator*/

		DP_INFO("%02x ", p[i]);

		if (r == (line_num - 1))
			DP_INFO("\n"); /*insert new line */
	}

	DP_INFO("\n");
}
EXPORT_SYMBOL(dp_dump_raw_data);

struct pmac_port_info *get_port_info(int index)
{
	if (index < DP_MAX_PORT_IDX)
		return &dp_port_info[index];

	return NULL;
}

struct pmac_port_info *get_port_info_via_dp_port(int dp_port)
{
	int i;

	for (i = 0; i < DP_MAX_PORT_IDX; i++) {
		if ((dp_port_info[i].status >= PORT_DEV_REGISTERED) &&
		    (dp_port_info[i].port_id == dp_port))
			return &dp_port_info[i];
	}

	return NULL;
}

struct pmac_port_info *get_port_info_via_dp_name(struct net_device *dev)
{
	int i;

	for (i = 0; i < DP_MAX_PORT_IDX; i++) {
		if ((dp_port_info[i].status >= PORT_DEV_REGISTERED) &&
		    (dp_port_info[i].dev == dev))
			return &dp_port_info[i];
	}

	return NULL;
}

static int dp_get_index_via_module_dev_port_priv(struct module *owner,
		struct net_device *dev,
		uint32_t dev_port)
{
	int i;

	for (i = 0; i < DP_MAX_PORT_IDX; i++) {
		if (dp_port_info[i].status >= PORT_DEV_REGISTERED) {
			if ((dp_port_info[i].owner == owner) &&
			    (dp_port_info[i].dev_port == dev_port))
				return i;
		}
	}

	return -1;
}

static int32_t dp_port_get_free(int32_t port_id, int32_t flags)
{
	int i;

	if (flags & DP_F_FAST_DSL || flags & DP_F_FAST_WLAN) { //TODO: why use wlan
		return DSL_PORT;
	} else {
		for (i = 0; i < DP_MAX_PORT_IDX; i++) {
			if (dp_port_info[i].status != PORT_FREE)
				continue;
			return i + 3;
		}
	}

	return DP_FAILURE;
}

static uint32_t
dp_subif_expand(struct net_device *netif, dp_subif_t *subif_id, dp_subif_t *res)
{
	if (!subif_id && !netif)
		return DP_FAILURE;

	if (!subif_id) {
		if (dp_get_port_subitf_via_dev(netif, res))
			return DP_FAILURE;
	} else {
		res->port_id = subif_id->port_id;
		res->subif = subif_id->subif;
	}

	if (res->port_id <= 0 || res->port_id >= DP_MAX_PORTS)
		return DP_FAILURE;

	return DP_SUCCESS;
}




/***************Datapath functions*****************/
/*note: dev can be NULL */
static int32_t dp_alloc_port_private(struct module *owner,
				     struct net_device *dev,
				     uint32_t dev_port, int32_t port_id,
				     dp_pmac_cfg_t *pmac_cfg, uint32_t flags)
{
	int i;

	if (!owner) {
		DP_ERROR("Allocate port failed for owner NULL\n");
		return DP_FAILURE;
	}

	if (port_id >= DP_MAX_PORTS || port_id < 0) {
		DP_DEBUG_ASSERT((port_id >= DP_MAX_PORTS),
				"port_id(%d) >= DP_MAX_PORTS(%d)", port_id,
				DP_MAX_PORTS);
		DP_DEBUG_ASSERT((port_id < 0), "port_id(%d) < 0", port_id);
		return DP_FAILURE;
	}

	DP_DBG("Flags=");

	for (i = 0; i < get_dp_port_type_str_size(); i++) {
		if (flags & dp_port_flag[i])
			DP_DBG("%s ", dp_port_type_str[i]);
	}

	DP_DBG("\n");

	if (flags & DP_F_DEREGISTER) {	/*De-register */
		if (dp_port_info[port_id].status != PORT_ALLOCATED) {
			DP_ERROR("No Deallocate for module %s w/o deregistered\n",
				owner->name);
			return DP_FAILURE;
		}

		DP_DBG("de-alloc port %d\n", port_id);

		memset(&dp_port_info[port_id], 0, sizeof(dp_port_info[port_id]));

		dp_port_info[port_id].status = PORT_FREE;

		return DP_SUCCESS;
	}

	/*sanity check here: "onwner + dev_port" should be unique  */
	i = dp_get_index_via_module_dev_port_priv(owner, dev, dev_port);

	if (i > 0) {
		DP_DEBUG_ASSERT(i > 0, "module %s(dev_port %d)already alloc %d\n",
				owner->name, dev_port,
				dp_port_info[i].port_id);
		return DP_FAILURE;
	}

	if (port_id) {		/*with specified port_id */
		if (dp_port_info[port_id].status != PORT_FREE) {
			DP_DEBUG_ASSERT(i > 0, "module %s (dev_port %d) failed to allocate port %d used by %s %d\n",
					owner->name, dev_port, port_id,
					dp_port_info[i].owner->name,
					dp_port_info[i].dev_port);
			return DP_FAILURE;
		}
	}

	if (!port_id)
		port_id = dp_port_get_free(port_id, flags);

	if (port_id <= 0) {
		DP_ERROR("dp_port_alloc allocation failed for module %s with dev_port %d\n",
			owner->name, dev_port);
		return DP_FAILURE;
	}
	if (g_ppe_directpath_data[DP_PORT_ID_TO_PORT_IDX(port_id)].flags & 0x80000000) {
		printk("%s: DSL port is already in use [%x]\n", __func__, flags);
		return -1;
	}
	g_ppe_directpath_data[DP_PORT_ID_TO_PORT_IDX(DSL_PORT)].flags = (0x80000000 | flags);
	dp_port_info[DP_PORT_ID_TO_PORT_IDX(port_id)].owner = owner;
	dp_port_info[DP_PORT_ID_TO_PORT_IDX(port_id)].dev = dev;
	dp_port_info[DP_PORT_ID_TO_PORT_IDX(port_id)].dev_port = dev_port;
	dp_port_info[DP_PORT_ID_TO_PORT_IDX(port_id)].port_id = DSL_PORT;
	dp_port_info[DP_PORT_ID_TO_PORT_IDX(port_id)].alloc_flags = flags;
	dp_port_info[DP_PORT_ID_TO_PORT_IDX(port_id)].status = PORT_ALLOCATED;
	/* only DCDP call this, return DSL port */



	DP_DBG("Port %d allocation succeed for module %s with dev_port %d\n",
		 port_id, owner->name, dev_port);

	return port_id;
}
int32_t dp_alloc_port(struct module *owner, struct net_device *dev,
		      uint32_t dev_port, int32_t port_id,
		      dp_pmac_cfg_t *pmac_cfg, uint32_t flags)
{
	int32_t res;
	printk("%s: flags[%x]\n", __func__, flags);

	if (unlikely(!dp_init_ok)) {
		DP_ERROR("dp_alloc_port failed for datapath not init yet\n");
		return DP_FAILURE;
	}

	DP_LIB_LOCK(&dp_lock);
	res = dp_alloc_port_private(owner, dev, dev_port, port_id, pmac_cfg ,flags);
	DP_LIB_UNLOCK(&dp_lock);

	return res;
}
EXPORT_SYMBOL(dp_alloc_port);


int32_t dp_register_dev(struct module *owner, uint32_t port_id,
			dp_cb_t *dp_cb, uint32_t flags)
{
	int32_t res = DP_FAILURE;
	int32_t port_idx;

	if (unlikely(!dp_init_ok)) {
		DP_ERROR("dp_register_dev failed for datapath not init yet\n");
		return DP_FAILURE;
	}

	if (!port_id || !owner) {
		if (!owner)
			DP_DBG("owner NULL\n");
		else
			DP_DBG("Wrong port_id:%d\n", port_id);

		return DP_FAILURE;
	}
	port_idx = DP_PORT_ID_TO_PORT_IDX(port_id);
	if (flags & DP_F_DEREGISTER) {	/*de-register */
		DP_LIB_LOCK(&dp_lock);

		if (dp_port_info[port_idx].status != PORT_DEV_REGISTERED) {
			DP_DBG("No or %s to de-register for num_subif=%d\n",
			       owner->name, dp_port_info[port_idx].num_subif);
		} else if (dp_port_info[port_idx].status == PORT_DEV_REGISTERED) {
			dp_port_info[port_idx].status = PORT_ALLOCATED;
			res = DP_SUCCESS;
		} else {
			DP_DBG("No for %s to de-register for unknown status:%d\n",
			 owner->name, dp_port_info[port_idx].status);
		}
		g_smartphy_push_fn = NULL;
		DP_LIB_UNLOCK(&dp_lock);
		/* There is no TC, reset PPE FW */
		dc_dp_ppe_518_path_enable(0);
		dp_private_resource_free(port_id);
		return res;
	}

	DP_LIB_LOCK(&dp_lock);

	/*register a device */
	if (dp_port_info[port_idx].status != PORT_ALLOCATED) {
		DP_DBG("No de-register for %s for unknown status:%d\n",
		       owner->name, dp_port_info[port_idx].status);
		DP_LIB_UNLOCK(&dp_lock);
		return DP_FAILURE;
	}

	if (dp_port_info[port_idx].owner != owner) {
		DP_DBG("No matched owner(%s):%p->%p\n", owner->name, owner,
		       dp_port_info[port_id].owner);
		DP_LIB_UNLOCK(&dp_lock);
		return res;
	}

	dp_port_info[port_idx].status = PORT_DEV_REGISTERED;
	dp_port_info[port_idx].port_id = port_id;

	if (dp_cb) {
		dp_port_info[port_idx].cb = *dp_cb;
		g_ppe_directpath_data[port_idx].callback.rx_fn = dp_cb->rx_fn;
		g_ppe_directpath_data[port_idx].callback.stop_tx_fn = dp_cb->stop_fn;
		g_ppe_directpath_data[port_idx].callback.start_tx_fn = dp_cb->restart_fn;
	}
	g_smartphy_push_fn = dsl_push;
	//currently, only 518 uses DCDP to register to datapath
	dsl_chipset_type_set(DSL_518);
	dc_dp_ppe_518_path_enable(1);
	DP_LIB_UNLOCK(&dp_lock);
	return DP_SUCCESS;
}
EXPORT_SYMBOL(dp_register_dev);

int32_t dp_register_subif(struct module *owner, struct net_device *dev,
			  char *subif_name, dp_subif_t *subif_id,
			  uint32_t flags)
{
	int32_t res = DP_FAILURE;
	int i, port_id, port_idx, start, end;
	if (unlikely(!dp_init_ok)) {
		DP_ERROR("dp_register_subif failed for datapath not init yet\n");
		return DP_FAILURE;
	}
	printk("to cha no: ownner[%x]dev[%x]subif_id[%x]\n", owner, dev, subif_id);
	/* printk("%s:owner=%s dev=%s port_id=%d subif=%d(%s)\n",
		 (flags & DP_F_DEREGISTER) ? "unregister subif:" : "register subif",
		 owner ? owner->name : "NULL",
		 dev ? dev->name : "NULL",
		 subif_id->port_id,
		 subif_id->subif,
		 (subif_id->subif < 0) ? "dynamic" : "fixed");*/

	if ((!subif_id) || (!subif_id->port_id) || (!owner) ||
	    (subif_id->port_id >= DP_MAX_PORTS)
	    || subif_id->port_id <= 0) {
		DP_ERROR("%s: port_id[%d] > MAX_PORT[%d]\n", __func__,
				subif_id->port_id, DP_MAX_PORTS);
		if (!owner)
			DP_ERROR("Unregister subif failed for owner NULL\n");
		else if (!subif_id)
			DP_ERROR("Unregister subif failed for NULL subif_id\n");
		else
			DP_ERROR("Unregister subif failed port_id=%d or others\n",
			 subif_id->port_id);

		return DP_FAILURE;
	}

	port_id = subif_id->port_id;
	port_idx = DP_PORT_ID_TO_PORT_IDX(port_id);
#if 0
	if (((!dev) && !(dp_port_info[port_idx].alloc_flags & (DP_F_FAST_DSL || DP_F_FAST_WLAN))) ||
	    !subif_name) {
		DP_ERROR("Wrong dev=%p, subif_name=%p\n", dev, subif_name);
		return DP_FAILURE;
	}
#endif
	DP_LIB_LOCK(&dp_lock);

	/*register a device */
	if (dp_port_info[port_idx].owner != owner) {
		pr_err("Unregister subif failed:Not matching:%p(%s)->%p(%s)\n",
		 owner, owner->name, dp_port_info[port_idx].owner,
		 dp_port_info[port_idx].owner->name);
		DP_LIB_UNLOCK(&dp_lock);
		return res;
	}

	if (flags & DP_F_DEREGISTER) {	/*de-register */
		DP_DBG("Try to unregister subif=%s with dp_port=%d subif=%d\n",
			 dev ? dev->name : "NULL", subif_id->port_id, subif_id->subif);

		if (dp_port_info[port_idx].status != PORT_SUBIF_REGISTERED) {
			DP_ERROR("Unregister failed:%s not registered subif!\n",
			       dev ? dev->name : "NULL");
			DP_LIB_UNLOCK(&dp_lock);
			return DP_FAILURE;
		}

		for (i = 0; i < MAX_SUBIF_PER_PORT; i++) {
			if (dp_port_info[port_idx].subif_info[i].subif ==
			    get_vap(subif_id->subif)) {

				//dp_dev_pp_exit(dp_port_info[port_idx].subif_info[i].netif);

				memset(&dp_port_info[port_idx].subif_info[i],
				       0,
				       sizeof(dp_port_info[port_idx].
					      subif_info[i]));
				dp_port_info[port_idx].num_subif--;

				/*last subif deregistered */
				if (dp_port_info[port_idx].num_subif == 0)
					dp_port_info[port_idx].status = PORT_DEV_REGISTERED;

				pr_info("Found matched subif: %d_%d!\n",
					 subif_id->port_id, subif_id->subif);
				break;
			}
		}

		if (i < MAX_SUBIF_PER_PORT) {
			pr_info("  dp_port=%d subif=%d\n",
				 subif_id->port_id, subif_id->subif);
			res = DP_SUCCESS;
		}

		DP_LIB_UNLOCK(&dp_lock);
		return res;
	}

	/*Register subif */
	if (dp_port_info[port_idx].status < PORT_DEV_REGISTERED) {
		pr_err("Register subif failed:%s is not a registered dev!\n",
		 dev ? dev->name : "NULL");
		DP_LIB_UNLOCK(&dp_lock);
		return res;
	}

	if (subif_id->subif < 0) { /*dynamic mode*/
		start = 0;
		end = MAX_SUBIF_PER_PORT;
	} else { /*caller provided the vap. Try to get its vap value as start*/
		start = get_vap(subif_id->subif);
		end = start + 1;
	}

	DP_INFO("search range: start=%d end=%d\n",start, end);
	/*allocate a free subif */
	for (i = start; i < end; i++) {
		uint32_t subif;
		if (dp_port_info[port_idx].subif_info[i].flags != SUBIF_FREE)
			continue;

		/*free */
		dp_port_info[port_idx].subif_info[i].netif = dev;
		dp_port_info[port_idx].port_id = port_id;

		if (subif_id->subif < 0) /*dynamic */
			dp_port_info[port_idx].subif_info[i].subif = i;
		else /*provided by caller*/
			dp_port_info[port_idx].subif_info[i].subif =
				get_vap(subif_id->subif);

		strcpy(dp_port_info[port_idx].subif_info[i].
		       device_name, dev ? dev->name : "NULL");
		dp_port_info[port_idx].subif_info[i].flags = SUBIF_REGISTERED;
		dp_port_info[port_idx].status = PORT_SUBIF_REGISTERED;
		subif_id->port_id = port_id;
		set_vap(&subif, i);
		subif_id->subif = subif;
		dp_port_info[port_idx].num_subif++;

		break;
	}

	if (i < end)
		res = DP_SUCCESS;
	else
		printk("register subif failed\n");

	DP_LIB_UNLOCK(&dp_lock);
	return res;
}
EXPORT_SYMBOL(dp_register_subif);


int32_t dp_get_netif_subifid(struct net_device *netif, struct sk_buff *skb,
			     void *subif_data,
			     uint8_t dst_mac[MAX_ETH_ALEN],
			     dp_subif_t *subif, uint32_t flags)
{
	int32_t res = -1;
	int i, k;
	int port_id = -1, port_idx;
	int dst_subifid = -1;
	dp_get_netif_subifid_fn_t subifid_fn_t;

	if (!netif && !subif_data) {
		DP_DBG("dp_get_netif_subifid failed: netif=%p subif_data=%p\n", netif, subif_data);
		return res;
	}

	if (!subif) {
		DP_DBG("dp_get_netif_subifid failed:subif=%p\n", subif);
		return res;
	}

	if (subif->port_id >= DP_MAX_PORTS) {
		DP_DBG("dp_get_netif_subifid wrong port_id: %d\n",
		       subif->port_id);
		return res;
	}

	//DP_LIB_LOCK(&dp_lock);

	for (k = 0; k < DP_MAX_PORT_IDX; k++) {
		if (dp_port_info[k].status != PORT_SUBIF_REGISTERED)
			continue;

		/*Workaround for VRX318 */
		if (subif_data && (dp_port_info[k].alloc_flags & DP_F_FAST_DSL)) {
			/*VRX318 should overwritten them later if necessary */
			port_id = k;
			dst_subifid = 0;
			break;
		}

		/*search sub-interfaces */
		for (i = 0; i < MAX_SUBIF_PER_PORT; i++) {
			if (dp_port_info[k].subif_info[i].flags == SUBIF_FREE)
				continue;

			if (dp_port_info[k].subif_info[i].netif == netif) {
				if ((subif->port_id > 0) &&	/*specified port */
				    (subif->port_id != k)) {	/*not match */
					DP_DBG("dp_get_netif_subifid portid not match\n");
				} else {
					port_id = k;
					dst_subifid =
						dp_port_info[k].
						subif_info[i].subif;
				}

				break;
			}
		}
	}

	//DP_LIB_UNLOCK(&dp_lock);

	if ((dst_subifid < 0) || (port_id < 0)) {
		if (subif_data)
			DP_DBG("dp_get_netif_subifid failed with subif_data %p\n",
			       subif_data);
		else /*netif must should be valid */
			DP_DBG("dp_get_netif_subifid failed: %s\n",
			       netif->name);

		return res;
	}

	subif->port_id = port_id;
	port_idx = DP_PORT_ID_TO_PORT_IDX(port_id);
	subifid_fn_t = dp_port_info[port_idx].cb.get_subifid_fn;

	if (subifid_fn_t && !(flags & DP_F_SUBIF_LOGICAL)) {
		/*subif->subif will be set by callback api itself */
		res = subifid_fn_t(netif, skb, subif_data, dst_mac, subif, flags);

		if (res != 0)
			DP_DBG("get_netif_subifid callback failed\n");

		return res;

	} else
		subif->subif = dst_subifid;

	res = 0;
	return res;
}
EXPORT_SYMBOL(dp_get_netif_subifid);

/* return DP_SUCESS -- found
   return DP_FAILURE -- not found
*/
int dp_get_port_subitf_via_dev_private(struct net_device *dev,
				       dp_subif_t *subif)
{
	int i, j;

	for (i = 0; i < DP_MAX_PORT_IDX; i++)
		for (j = 0; j < MAX_SUBIF_PER_PORT; j++) {
			if (dp_port_info[i].subif_info[j].netif == dev) {
				subif->port_id = dp_port_info[i].port_id;
				subif->subif = j << VAP_OFFSET;
				return DP_SUCCESS;
			}
		}

	return DP_FAILURE;
}

int dp_get_port_subitf_via_dev(struct net_device *dev, dp_subif_t *subif)
{
	int res;

	DP_LIB_LOCK(&dp_lock);
	res = dp_get_port_subitf_via_dev_private(dev, subif);
	DP_LIB_UNLOCK(&dp_lock);
	return res;
}
EXPORT_SYMBOL(dp_get_port_subitf_via_dev);

int dp_get_port_subitf_via_ifname_private(char *ifname, dp_subif_t *subif)
{
	int i, j;

	for (i = 0; i < DP_MAX_PORT_IDX; i++) {
		for (j = 0; j < MAX_SUBIF_PER_PORT; j++) {
			if (strcmp
			    (dp_port_info[i].subif_info[j].device_name,
			     ifname) == 0) {
				subif->port_id = dp_port_info[i].port_id;
				subif->subif = j << VAP_OFFSET;
				return DP_SUCCESS;
			}
		}
	}

	return DP_FAILURE;
}

int dp_get_port_subitf_via_ifname(char *ifname, dp_subif_t *subif)
{
	int res;

	DP_LIB_LOCK(&dp_lock);
	res = dp_get_port_subitf_via_ifname_private(ifname, subif);
	DP_LIB_UNLOCK(&dp_lock);
	return res;
}
EXPORT_SYMBOL(dp_get_port_subitf_via_ifname);

int32_t dp_check_if_netif_fastpath_fn(struct net_device *netif,
				      dp_subif_t *subif, char *ifname,
				      uint32_t flags)
{

	int32_t res = 1;
	int32_t port_idx = 0;
	dp_subif_t tmp_subif = { 0 };
	DP_LIB_LOCK(&dp_lock);

	if (unlikely(!dp_init_ok)) {
		DP_ERROR("dp_check_if_netif_fastpath_fn failed for datapath not init yet\n");
		DP_LIB_UNLOCK(&dp_lock);
		return DP_FAILURE;
	}

	if (subif)
		tmp_subif = *subif;
	else if (netif)
		dp_get_port_subitf_via_dev_private(netif, &tmp_subif);
	else if (ifname)
		dp_get_port_subitf_via_ifname_private(ifname, &tmp_subif);

	if (tmp_subif.port_id <= 0 && tmp_subif.port_id >= DP_MAX_PORTS)
		res = 0;
	else if (!
		 (dp_port_info[DP_PORT_ID_TO_PORT_IDX(tmp_subif.port_id)].alloc_flags &
		  (DP_F_FAST_DSL | DP_F_FAST_ETH_LAN | DP_F_FAST_ETH_WAN |
		   DP_F_FAST_WLAN)))
		res = 0;

	DP_LIB_UNLOCK(&dp_lock);
	return res;
}
EXPORT_SYMBOL(dp_check_if_netif_fastpath_fn);

struct module *dp_get_module_owner(int ep)
{
	int ep_idx;
	if (unlikely(!dp_init_ok)) {
		DP_ERROR("dp_get_module_owner failed for datapath not init yet\n");
		return NULL;
	}
	ep_idx = DP_PORT_ID_TO_PORT_IDX(ep);
	if ((ep_idx >= 0) && (ep_idx < DP_MAX_PORT_IDX))
		return  dp_port_info[ep_idx].owner;

	return NULL;
}
EXPORT_SYMBOL(dp_get_module_owner);

void set_dp_dbg_flag(uint32_t flags)
{
	dp_dbg_flag = flags;
}

uint32_t get_dp_dbg_flag(void)
{
	return dp_dbg_flag;
}				/* DP_TEST_EXAMPLE */


static int32_t
dp_set_psi(struct sk_buff *skb, struct net_device *dev, dp_subif_t *tx_subif)
{
	int32_t ret = DP_SUCCESS;
	dp_subif_t subif;
#if defined(CONFIG_LTQ_PPA_API) || defined(CONFIG_LTQ_PPA_API_MODULE)
        PPA_VCC *vcc = NULL;
#endif
	if (dp_subif_expand(dev, tx_subif, &subif)) {
		DP_ERROR("subif not found for %s\n", dev ? dev->name : "unknown");
		return DP_FAILURE;
	}

	DP_LIB_LOCK(&dp_lock);

#if defined(CONFIG_LTQ_PPA_API) || defined(CONFIG_LTQ_PPA_API_MODULE)
    ppa_br2684_get_vcc(dev,&vcc);
	if (vcc !=NULL) {
		if(dp_get_netif_subifid(dev, skb,
                             	(void *)vcc,
                             	NULL,
                             	&subif, 0) != DP_SUCCESS)
			ret = DP_FAILURE;
		goto done;
	}
#endif

done:
	DP_LIB_UNLOCK(&dp_lock);
	return ret;

}

int32_t dp_xmit(struct net_device *rx_if, dp_subif_t *rx_subif,
		struct sk_buff *skb, int32_t len, uint32_t flags)
{

	int ret;
	dp_subif_t subif;
	struct dp_subif_info *subif_info;
	struct pmac_port_info *port;
#if defined(CONFIG_LTQ_PPA_API) || defined(CONFIG_LTQ_PPA_API_MODULE)
        PPA_VCC *vcc = NULL;
#endif
	if (unlikely(in_irq()))
		pr_err_ratelimited("Not allowed to call dp_xmit in interrupt context\n");
	/* pointers for easy access */
#if defined(CONFIG_LTQ_PPA_API) || defined(CONFIG_LTQ_PPA_API_MODULE)
	ppa_br2684_get_vcc(rx_if, &vcc);
	if (vcc !=NULL) {
		/*
		psi = pdp_skb_get_psi(skb);
		memset(psi, 0, sizeof(*psi));
		psi->wifi_session_info = cpu_to_be16((uint16_t)subif.subif);
        	goto __skip_psi;
        	*/
	}
#endif
__skip_psi:

	//TODO: call datapath'x hard_xmit
	dc_dp_ppe_start_xmit(skb, rx_subif, rx_if, flags);

	if (ret) {
		subif_info->if_stats.tx_dropped++;
	} else {
		subif_info->if_stats.tx_packets++;
		subif_info->if_stats.tx_bytes += skb->len;
	}

	return DP_SUCCESS;

discard:
	dev_kfree_skb_any(skb);
	return DP_SUCCESS;
}
EXPORT_SYMBOL(dp_xmit);

int32_t dp_rx(struct sk_buff *skb, uint32_t flags)
{
	struct dp_subif_info *subif_info;
	struct net_device *dev;
	struct pmac_port_info *port;
	//struct wifi_proxy_psi_t *psi;
	dp_rx_fn_t rx_fn;
	int32_t ret;

//	struct dma_rx_desc_0 *desc_0 = (struct dma_rx_desc_0 *)&skb->DW0;
	struct dma_rx_desc_1 *desc_1 = (struct dma_rx_desc_1 *)&skb->DW1;
//	struct dma_rx_desc_2 *desc_2 = (struct dma_rx_desc_2 *)&skb->DW2;
//	struct dma_rx_desc_3 *desc_3 = (struct dma_rx_desc_3 *)&skb->DW3;

	//psi = pdp_skb_get_psi(skb);

	/* pointers for easy access */
	port = &dp_port_info[DP_PORT_ID_TO_PORT_IDX(desc_1->field.ep)];
	subif_info = &port->subif_info[0];//TODO: get_vap(be16_to_cpu(psi->wifi_session_info))

	DP_LIB_LOCK(&dp_lock);

	rx_fn = port->cb.rx_fn;
	dev = subif_info->netif;

	if (!rx_fn || !dev || subif_info->flags == SUBIF_FREE) {
		port->rx_err_drop++;
		goto discard_unlock;
	}

	if (!netif_running(dev)) {
		subif_info->if_stats.rx_dropped++;
		goto discard_unlock;
	}

	skb->dev = dev;

	DP_LIB_UNLOCK(&dp_lock);

	ret = rx_fn(dev, NULL, skb, skb->len);

	if (ret) {
		subif_info->if_stats.rx_dropped++;
	} else {
		subif_info->if_stats.rx_packets++;
		subif_info->if_stats.rx_bytes += skb->len;
	}


	return DP_SUCCESS;

discard_unlock:
	DP_LIB_UNLOCK(&dp_lock);

	dev_kfree_skb_any(skb);
	return DP_FAILURE;
}

int32_t
dp_get_netif_stats(struct net_device *netif, dp_subif_t *subif_id,
			struct rtnl_link_stats64 *path_stats, uint32_t flags)
{

	uint32_t vap;
	dp_subif_t subif;
	struct rtnl_link_stats64 cpu = {0}, accel = {0};

	if (dp_subif_expand(netif, subif_id, &subif))
		return DP_FAILURE;

	vap = get_vap(subif.subif);

	if ((flags & DP_STATS_CPU))
	    //TODO: dp_get_netif_stats_cpu(subif.port_id, vap, &cpu))
		return DP_FAILURE;

	if ((flags & DP_STATS_ACCEL))
	    //TODO: dp_get_netif_stats_accel(subif.port_id, vap, &accel))
		return DP_FAILURE;

	//dp_netif_stats_add(path_stats, &cpu, &accel);
	return DP_SUCCESS;
}
EXPORT_SYMBOL(dp_get_netif_stats);

int32_t
dp_clear_netif_stats(struct net_device *netif, dp_subif_t *subif_id,
			uint32_t flags)
{
	uint32_t vap;
	dp_subif_t subif;

	if (dp_subif_expand(netif, subif_id, &subif))
		return DP_FAILURE;

	vap = get_vap(subif.subif);

	if ((flags & DP_STATS_CPU))
	    //dp_clear_netif_stats_cpu(subif.port_id, vap))
		return DP_FAILURE;

	if ((flags & DP_STATS_ACCEL))
	    //dp_clear_netif_stats_accel(subif.port_id, vap))
		return DP_FAILURE;

	return DP_SUCCESS;
}
EXPORT_SYMBOL(dp_clear_netif_stats);

int32_t
dp_port_id_to_pid(int32_t port_id)
{
	int32_t pid;

	if (port_id >= DP_MAX_PORTS || port_id < 0) {
		DP_ERROR("invalid port_id %d\n", port_id);
		return DP_FAILURE;
	}

	DP_LIB_LOCK(&dp_lock);
	if (dp_port_info[DP_PORT_ID_TO_PORT_IDX(port_id)].status <= PORT_FREE) {
		DP_LIB_UNLOCK(&dp_lock);
		DP_ERROR("invalid status %d for port_id %d\n",
		    dp_port_info[DP_PORT_ID_TO_PORT_IDX(port_id)].status, port_id);
		return DP_FAILURE;
	}

	//BUG_ON(!dp_port_info[port_id - DSL_PORT].cppi.cppi_dev);

	pid = dp_port_info[DP_PORT_ID_TO_PORT_IDX(port_id)].port_id;
	DP_LIB_UNLOCK(&dp_lock);

	return pid;
}
EXPORT_SYMBOL(dp_port_id_to_pid);
static void inline dc_dp_dump_dccntr(struct dc_dp_dccntr *dccntr)
{
	printk("soc2dev_enq_phys_base      [0x%pK]\n", dccntr->soc2dev_enq_phys_base);
	printk("soc2dev_enq_base           [0x%pK]\n", dccntr->soc2dev_enq_base);
	printk("soc2dev_enq_dccntr_len     [%d]\n", dccntr->soc2dev_enq_dccntr_len);
	printk("soc2dev_ret_deq_phys_base  [0x%pK]\n", dccntr->soc2dev_ret_deq_phys_base);
	printk("soc2dev_ret_deq_base       [0x%pK]\n", dccntr->soc2dev_ret_deq_base);
	printk("soc2dev_ret_deq_dccntr_len [%d]\n", dccntr->soc2dev_ret_deq_dccntr_len);
	printk("dev2soc_deq_phys_base      [0x%pK]\n", dccntr->dev2soc_deq_phys_base);
	printk("dev2soc_deq_base           [0x%pK]\n", dccntr->dev2soc_deq_base);
	printk("dev2soc_deq_dccntr_len     [%d]\n", dccntr->dev2soc_deq_dccntr_len);
	printk("dev2soc_ret_enq_phys_base  [0x%pK]\n", dccntr->dev2soc_ret_enq_phys_base);
	printk("dev2soc_ret_enq_base       [0x%pK]\n", dccntr->dev2soc_ret_enq_base);
	printk("dev2soc_ret_enq_dccntr_len [%d]\n", dccntr->dev2soc_ret_enq_dccntr_len);
	printk("soc2dev_deq_phys_base      [0x%pK]\n", dccntr->soc2dev_deq_phys_base);
	printk("soc2dev_deq_base           [0x%pK]\n", dccntr->soc2dev_deq_base);
	printk("soc2dev_deq_dccntr_len     [%d]\n", dccntr->soc2dev_deq_dccntr_len);
	printk("soc2dev_ret_enq_phys_base  [0x%pK]\n", dccntr->soc2dev_ret_enq_phys_base);
	printk("soc2dev_ret_enq_base       [0x%pK]\n", dccntr->soc2dev_ret_enq_base);
	printk("soc2dev_ret_enq_dccntr_len [%d]\n", dccntr->soc2dev_ret_enq_dccntr_len);
	printk("dev2soc_enq_phys_base      [0x%pK]\n", dccntr->dev2soc_enq_phys_base);
	printk("dev2soc_enq_base           [0x%pK]\n", dccntr->dev2soc_enq_base);
	printk("dev2soc_enq_dccntr_len     [%d]\n", dccntr->dev2soc_enq_dccntr_len);
	printk("dev2soc_ret_deq_phys_base  [0x%pK]\n", dccntr->dev2soc_ret_deq_phys_base);
	printk("dev2soc_ret_deq_base       [0x%pK]\n", dccntr->dev2soc_ret_deq_base);
	printk("dev2soc_ret_deq_dccntr_len [%d]\n", dccntr->dev2soc_ret_deq_dccntr_len);
	printk("flags                      [0x%x]\n", dccntr->flags);
}

#define PP_BUFFER_HEADROOM		128
#define DC_DP_TOTAL_BUF_SIZE		2048
#define DC_DP_REAL_BUF_SIZE \
	(DC_DP_TOTAL_BUF_SIZE - PP_BUFFER_HEADROOM)

int32_t dp_create_dcdp_res(uint32_t port_id, struct dc_dp_res *dcdp_res)
{
	total_dev_aca_cnt_t dev_aca_cnt, *ptr_dev_aca_cnt_le, *ptr_dev_aca_cnt_be;
	total_soc_aca_cnt_t *ptr_soc_aca_cnt;
	struct dc_dp_dccntr *dccntr;
	struct dc_dp_ring *ring;
	soc_aca_cfg_ctxt_t *soc_cfg_ctxt = (soc_aca_cfg_ctxt_t *)SB_BUFFER(__SOC_ACA_CFG_CTXT);
	desq_cfg_ctxt_t *desq_cfg_ctxt;
	struct dc_dp_buf_pool *pool;
	int i;
	dccntr = dcdp_res->dccntr;
	/* update SB UMT addresses to 518 */
	dev_aca_cnt.tx_in_deq_cnt = SB_BUFFER(__TOTAL_DEV_ACA_CNT_BASE);
	dev_aca_cnt.tx_out_enq_cnt = SB_BUFFER(__TOTAL_DEV_ACA_CNT_BASE + 1);
	dev_aca_cnt.rx_in_deq_cnt = SB_BUFFER(__TOTAL_DEV_ACA_CNT_BASE + 2);
	dev_aca_cnt.rx_out_enq_cnt = SB_BUFFER(__TOTAL_DEV_ACA_CNT_BASE + 3);
	dccntr->soc2dev_deq_phys_base = CPHYSADDR(dev_aca_cnt.tx_in_deq_cnt);
	dccntr->soc2dev_deq_base = dev_aca_cnt.tx_in_deq_cnt;
	dccntr->soc2dev_ret_enq_phys_base = CPHYSADDR(dev_aca_cnt.tx_out_enq_cnt);
	dccntr->soc2dev_ret_enq_base = dev_aca_cnt.tx_out_enq_cnt;
	dccntr->dev2soc_enq_phys_base = CPHYSADDR(dev_aca_cnt.rx_out_enq_cnt);
	dccntr->dev2soc_enq_base = dev_aca_cnt.rx_out_enq_cnt;
	dccntr->dev2soc_ret_deq_phys_base = CPHYSADDR(dev_aca_cnt.rx_in_deq_cnt);
	dccntr->dev2soc_ret_deq_base = dev_aca_cnt.rx_in_deq_cnt;
	/* update 518 UMT addresses to D5 firmware */
	memset(soc_cfg_ctxt, 0, sizeof(soc_aca_cfg_ctxt_t));
	soc_cfg_ctxt->tx_in_aca_msg_ptr = CPHYSADDR(dccntr->soc2dev_enq_base);
	soc_cfg_ctxt->tx_out_aca_msg_ptr = CPHYSADDR(dccntr->soc2dev_ret_deq_base);
	soc_cfg_ctxt->rx_in_aca_msg_ptr = CPHYSADDR(dccntr->dev2soc_ret_enq_base);
	soc_cfg_ctxt->rx_out_aca_msg_ptr = CPHYSADDR(dccntr->dev2soc_deq_base);
	/* dc_dp_dump_dccntr(dccntr); */
	/* initialize rings */
	ring = &(dcdp_res->rings.soc2dev);
	ring->base = SB_BUFFER(__SOC_TX_IN_DES_LIST_BASE);
	ring->phys_base = CPHYSADDR((SB_BUFFER(__SOC_TX_IN_DES_LIST_BASE)));
	ring->size = __SOC_TX_IN_DES_LIST_NUM;
	ring->desc_dwsz = 2;

	ring = &(dcdp_res->rings.soc2dev_ret);
	ring->base = SB_BUFFER(__SOC_TX_OUT_DES_LIST_BASE);
	ring->phys_base = CPHYSADDR(SB_BUFFER(__SOC_TX_OUT_DES_LIST_BASE));
	ring->size = __SOC_TX_OUT_DES_LIST_NUM;
	ring->desc_dwsz = 2;

	ring = &(dcdp_res->rings.dev2soc);
	ring->base = SB_BUFFER(__SOC_RX_OUT_DES_LIST_BASE);
	ring->phys_base = CPHYSADDR(SB_BUFFER(__SOC_RX_OUT_DES_LIST_BASE));
	ring->size = __SOC_RX_OUT_DES_LIST_NUM;
	ring->desc_dwsz = 2;

	ring = &(dcdp_res->rings.dev2soc_ret);
	ring->base = SB_BUFFER(__SOC_RX_IN_DES_LIST_BASE);
	ring->phys_base = CPHYSADDR(SB_BUFFER(__SOC_RX_IN_DES_LIST_BASE));
	ring->size = __SOC_RX_IN_DES_LIST_NUM;
	ring->desc_dwsz = 2;
	/* initilize TXIN descriptors */
	desq_cfg_ctxt = (desq_cfg_ctxt_t *)(SB_BUFFER(__SOC_TX_IN_DESQ_CFG_CTXT));
	memset((void *)desq_cfg_ctxt, 0, sizeof(desq_cfg_ctxt_t));
	desq_cfg_ctxt->des_in_own_val = 0;
	desq_cfg_ctxt->des_num = __SOC_TX_IN_DES_LIST_NUM;
	desq_cfg_ctxt->des_base_addr = __SOC_TX_IN_DES_LIST_BASE;
	/* initilize RXIN descriptors */
	desq_cfg_ctxt = (desq_cfg_ctxt_t *)(SB_BUFFER(__SOC_RX_IN_DESQ_CFG_CTXT));
	memset((void *)desq_cfg_ctxt, 0, sizeof(desq_cfg_ctxt_t));
	desq_cfg_ctxt->des_in_own_val = 0;
	desq_cfg_ctxt->des_num = __SOC_RX_IN_DES_LIST_NUM;
	desq_cfg_ctxt->des_base_addr = __SOC_RX_IN_DES_LIST_BASE;
	/* init aca counters */
	ptr_soc_aca_cnt = (total_soc_aca_cnt_t *)(SB_BUFFER(__TOTAL_SOC_ACA_CNT_BASE));
	ptr_soc_aca_cnt->tx_in_enq_cnt = 0;
	ptr_soc_aca_cnt->tx_out_deq_cnt = 0;
	ptr_soc_aca_cnt->rx_in_enq_cnt = 0;
	ptr_soc_aca_cnt->rx_out_deq_cnt = 0;
	ptr_dev_aca_cnt_le = (total_dev_aca_cnt_t *)(SB_BUFFER(__TOTAL_DEV_ACA_CNT_LE_BASE));
	ptr_dev_aca_cnt_le->tx_in_deq_cnt = 0;
	ptr_dev_aca_cnt_le->tx_out_enq_cnt = 0;
	ptr_dev_aca_cnt_le->rx_in_deq_cnt = 0;
	ptr_dev_aca_cnt_le->rx_out_enq_cnt = 0;
	ptr_dev_aca_cnt_be = (total_dev_aca_cnt_t *)(SB_BUFFER(__TOTAL_DEV_ACA_CNT_BE_BASE));
	ptr_dev_aca_cnt_be->tx_in_deq_cnt = 0;
	ptr_dev_aca_cnt_be->tx_out_enq_cnt = 0;
	ptr_dev_aca_cnt_be->rx_in_deq_cnt = 0;
	ptr_dev_aca_cnt_be->rx_out_enq_cnt = 0;
	*SB_BUFFER(__CPU_IN_DESC_RDPTR) = 0;
	*SB_BUFFER(__FP_IN_DESC_RDPTR) = 0;
	*SB_BUFFER(__ETH1_TX_WRPTR) = 0;
	dbg_pool_check(__func__);
	if (!dcdp_res->num_bufpools)
		dcdp_res->num_bufpools = dcdp_res->num_bufs_req;

	dp_private_resource_save(port_id, dcdp_res);

	return 0;
}
EXPORT_SYMBOL(dp_create_dcdp_res);

/****************System functions***************/
void dp_init()
{
	int i;
	spin_lock_init(&dp_lock);
	DP_LIB_LOCK(&dp_lock);
	memset(dp_port_info, 0, sizeof(dp_port_info));
	DP_LIB_UNLOCK(&dp_lock);
	for (i = 0; i < DP_MAX_PORT_IDX; i++)
		dp_port_info[i].status = PORT_FREE;
	/* printk("================%s+++++++++++++++\n", __func__); */
	dp_init_ok = 1;

}
EXPORT_SYMBOL(dp_init);
void dp_exit()
{
	DP_LIB_LOCK(&dp_lock);
	memset(dp_port_info, 0, sizeof(dp_port_info));
	DP_LIB_UNLOCK(&dp_lock);
	/* printk("================%s+++++++++++++++\n", __func__); */
	dp_init_ok = 0;
}
EXPORT_SYMBOL(dp_exit);
