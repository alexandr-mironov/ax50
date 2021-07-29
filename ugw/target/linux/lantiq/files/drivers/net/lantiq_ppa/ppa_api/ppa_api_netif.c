/*******************************************************************************
 **
 ** FILE NAME    : ppa_api_netif.c
 ** PROJECT      : PPA
 ** MODULES      : PPA API (Routing/Bridging Acceleration APIs)
 **
 ** DATE         : 3 NOV 2008
 ** AUTHOR       : Xu Liang
 ** DESCRIPTION  : PPA Protocol Stack Hook API Network Interface Functions
 ** COPYRIGHT    :              Copyright (c) 2009
 **                          Lantiq Deutschland GmbH
 **                   Am Campeon 3; 85579 Neubiberg, Germany
 **
 **   For licensing information, see the file 'LICENSE' in the root folder of
 **   this software module.
 **
 ** HISTORY
 ** $Date        $Author         $Comment
 ** 03 NOV 2008  Xu Liang        Initiate Version
 *******************************************************************************
 */

/* ####################################
 *              Head File
 * ####################################
 */

/*  Common Head File
 */
#include <linux/version.h>
#include <generated/autoconf.h>

/*  PPA Specific Head File
 */
#include "ppa_api.h"
#if defined(CONFIG_LTQ_DATAPATH) && CONFIG_LTQ_DATAPATH
#include <net/datapath_api.h>
#endif
#include <net/ppa_ppe_hal.h>
#include "ppa_api_netif.h"
#include "ppa_api_misc.h"
#include "ppe_drv_wrapper.h"
#include "ppa_api_session.h"
#include "ppa_datapath_wrapper.h"
#include "ppa_hal_wrapper.h"
#include "ppa_api_tools.h"
#include "ppa_api_core.h"

#ifdef CONFIG_LTQ_ETHSW_API
#include <xway/switch-api/lantiq_gsw_api.h>
#endif

/* ####################################
 *              Definition
 * ####################################
 */


/* ####################################
 *              Data Type
 * ####################################
 */


/* ####################################
 *             Declaration
 * ####################################
 */

/*  implemented in PPA PPE Low Level Driver (Data Path)
 */


/* ####################################
 *           Global Variable
 * ####################################
 */

uint32_t g_phys_port_cpu = ~0;
EXPORT_SYMBOL(g_phys_port_cpu);
uint32_t g_phys_port_atm_wan = ~0;
EXPORT_SYMBOL(g_phys_port_atm_wan);
uint32_t g_phys_port_atm_wan_vlan = 1;
EXPORT_SYMBOL(g_phys_port_atm_wan_vlan);

PPA_LIST_HEAD manual_del_iface_list;
EXPORT_SYMBOL(manual_del_iface_list);

static struct phys_port_info *g_phys_port_info;
static PPA_LOCK g_phys_port_lock;

static struct netif_info *g_netif;
static PPA_LOCK g_netif_lock;

/* ####################################
 *           Extern Variable
 * ####################################
 */
#if defined(CONFIG_LTQ_PPA_GRX500) && CONFIG_LTQ_PPA_GRX500
extern int32_t ppa_get_fid(PPA_IFNAME *ifname, uint16_t *fid);
extern int32_t ppa_drv_tmu_set_checksum_queue_map ( uint32_t pmac_port);
#endif
#if defined(CONFIG_PPTP_MODULE) || defined(CONFIG_PPTP)
extern uint32_t ppa_is_pptp_netif(PPA_NETIF *netif);
#endif

/* ####################################
 *            Local Function
 * ####################################
 */

#if defined(CONFIG_LTQ_PPA_GRX500) && CONFIG_LTQ_PPA_GRX500
static void ppa_add_vlan_entry(PPA_NETIF *netif, dp_subif_t *dp_subif,
struct netif_info *p_ifinfo, PPE_OUT_VLAN_INFO *vlan_info,
uint8_t *add_flag_fail)
{
		struct module *oner = NULL;
		ppa_memset(dp_subif, 0, sizeof(dp_subif));
		dp_subif->port_id = p_ifinfo->phys_port;
		/* get the subifid field [11:8] from dp library */
		if ((dp_get_netif_subifid(netif, NULL, NULL, NULL,
			dp_subif, DP_F_SUBIF_LOGICAL)) == PPA_SUCCESS) {
			p_ifinfo->subif_id |= (dp_subif->subif) & DP_SUBIF_MASK;
			return;
		} else if (!strlen(p_ifinfo->manual_lower_ifname)) {
			/*  not the mac vlan interfaces */
			dp_subif->subif = -1;
			oner = dp_get_module_owner(p_ifinfo->phys_port);
			if (dp_register_subif(oner, p_ifinfo->netif,
				p_ifinfo->name, dp_subif,
					DP_F_SUBIF_LOGICAL) != PPA_SUCCESS) {
					ppa_debug(DBG_ENABLE_MASK_DEBUG_PRINT, "dp_register_subif fail\n");
				*add_flag_fail = 1;
				return;/*failed to add*/
			}
			p_ifinfo->subif_id |= (dp_subif->subif) & DP_SUBIF_MASK;
			vlan_info->port_id = p_ifinfo->phys_port;
			vlan_info->subif_id = ((p_ifinfo->subif_id
						& DP_SUBIF_MASK) >> 8);
			/* get the VLAN protocol type from the inner VLAN
			 * interface
			 */
			vlan_info->vlan_type =
			ppa_get_vlan_type(p_ifinfo->in_vlan_netif);
			/* NETIF_VLAN_OUTER flag will be set only if the
			 * interface is double VLAN tagged (eg eth1.100.10)
			 */
			if (p_ifinfo->flags & NETIF_VLAN_OUTER) {
				vlan_info->stag_vlan_id = p_ifinfo->outer_vid;
				vlan_info->stag_ins = 1;
				vlan_info->stag_rem = 1;
			}
			/* in case of single VLAN tagged interface we need to
			 * check the VLAN type and
			 * 1. IF the VLAN type is 0x8100; remov: the incoming
			 * ctag vlan and add the new vlan in ctag
			 * 2. IF the VLAN type is 0x88A8; preserve the incoming
			 * ctag and add stag
			 */
			if (p_ifinfo->flags & NETIF_VLAN_INNER) {
				if (vlan_info->vlan_type ==
					PPA_VLAN_PROTO_8021Q) {
					vlan_info->vlan_id =
						p_ifinfo->inner_vid;
					vlan_info->ctag_ins = 1;
					vlan_info->ctag_rem = 1;
				} else if (vlan_info->vlan_type ==
						PPA_VLAN_PROTO_8021AD) {
					vlan_info->stag_vlan_id =
						p_ifinfo->inner_vid;
					vlan_info->stag_ins = 1;
				}
			}
			ppa_debug(DBG_ENABLE_MASK_DEBUG_PRINT,
				"netif=%s portid=%d subifid=%d\n", netif->name,
				dp_subif->port_id, dp_subif->subif);
			if (ppa_hsel_add_outer_vlan_entry(vlan_info, 0,
						PAE_HAL) != PPA_SUCCESS)
				ppa_debug(DBG_ENABLE_MASK_DEBUG_PRINT,
					"hsel_add_outer_vlan_entry fail\n");
		}
	return;
}
#endif

#if defined(CONFIG_LTQ_PPA_API_DIRECTPATH)
static int32_t ppa_check_if_netif_directpath(PPA_NETIF *netif, uint16_t flag)
{
	int8_t ret = PPA_FAILURE;
	int8_t found = 0;
	struct ppe_directpath_data *info;
	uint32_t pos = 0;

	ret = ppa_directpath_data_start_iteration(&pos, &info);
	if (ret == PPA_SUCCESS) {
		do {
			if ((info->flags & PPE_DIRECTPATH_DATA_ENTRY_VALID)
			    && info->netif == netif) {
				found = 1;
				ret = PPA_SUCCESS;
				break;
			}
			ret = ppa_directpath_data_iterate_next(&pos, &info);
		} while (ret == PPA_SUCCESS);
	}
	ppa_directpath_data_stop_iteration();

	if (found == 1)
		return PPA_SUCCESS;
	else
		return PPA_FAILURE;
}
#endif

/*  Physical Network Interface Operation Function */
static INLINE struct phys_port_info *ppa_phys_port_alloc_item(void)
{
	struct phys_port_info *obj;

	obj = (struct phys_port_info *)ppa_malloc(sizeof(*obj));
	if (obj)
		ppa_memset(obj, 0, sizeof(*obj));
	return obj;
}

static INLINE void ppa_phys_port_free_item(struct phys_port_info *obj)
{
	ppa_free(obj);
}

static void ppa_phys_port_free_list(void)
{
	struct phys_port_info *obj;

	ppa_lock_get(&g_phys_port_lock);
	while (g_phys_port_info) {
		obj = g_phys_port_info;
		g_phys_port_info = g_phys_port_info->next;

		ppa_phys_port_free_item(obj);
	}
	g_phys_port_cpu = ~0;
	g_phys_port_atm_wan = ~0;
	ppa_lock_release(&g_phys_port_lock);
}

static int32_t ppa_phys_port_lookup(PPA_IFNAME ifname[PPA_IF_NAME_SIZE],
				    struct phys_port_info **pp_info)
{
	int32_t ret = PPA_ENOTAVAIL;
	struct phys_port_info *obj;

	ppa_lock_get(&g_phys_port_lock);
	for (obj = g_phys_port_info; obj; obj = obj->next) {
		if (strcmp(obj->ifname, ifname) == 0) {
			ret = PPA_SUCCESS;
			if (pp_info)
				*pp_info = obj;
			break;
		}
	}
	ppa_lock_release(&g_phys_port_lock);

	return ret;
}

/*  Network Interface Operation Functions */
static INLINE struct netif_info *ppa_netif_alloc_item(void)
{
	struct netif_info *obj;

	obj = (struct netif_info *)ppa_malloc(sizeof(*obj));
	if (obj) {
		ppa_memset(obj, 0, sizeof(*obj));
		obj->mac_entry = ~0;
		ppa_atomic_set(&obj->count, 1);
	}

	return obj;
}

static INLINE void ppa_netif_free_item(struct netif_info *obj)
{
	if (ppa_atomic_dec(&obj->count) == 0) {
		PPE_ROUTE_MAC_INFO mac_info = {0};
		mac_info.mac_ix = obj->mac_entry;
		ppa_drv_del_mac_entry(&mac_info, 0);

		/* resotre old wanitf if necessary */
		if (obj->f_wanitf.flag_already_wanitf) {
			PPE_WANITF_CFG wanitf_cfg = {0};
			if (obj->f_wanitf.old_lan_flag)
				wanitf_cfg.lan_flag = 1;
			else
				wanitf_cfg.lan_flag = 0;
			wanitf_cfg.physical_port = obj->phys_port;
			ppa_set_wan_itf(&wanitf_cfg, 0);
		}
		ppa_free(obj);
	}
}

void ppa_netif_lock_list(void)
{
	ppa_lock_get(&g_netif_lock);
}
EXPORT_SYMBOL(ppa_netif_lock_list);

void ppa_netif_unlock_list(void)
{
	ppa_lock_release(&g_netif_lock);
}
EXPORT_SYMBOL(ppa_netif_unlock_list);

static INLINE void __ppa_netif_add_item(struct netif_info *obj)
{
	ppa_atomic_inc(&obj->count);
	ppa_netif_lock_list();
	obj->next = g_netif;
	g_netif = obj;
	ppa_netif_unlock_list();
}

static INLINE void ppa_netif_remove_item(PPA_IFNAME ifname[PPA_IF_NAME_SIZE],
					 struct netif_info **pp_info)
{
	struct netif_info *p_prev, *p_cur;

	if (pp_info)
		*pp_info = NULL;
	p_prev = NULL;
	ppa_netif_lock_list();
	for (p_cur = g_netif; p_cur; p_prev = p_cur, p_cur = p_cur->next)
		if (strcmp(p_cur->name, ifname) == 0) {
			if (!p_prev)
				g_netif = p_cur->next;
			else
				p_prev->next = p_cur->next;
			if (pp_info)
				*pp_info = p_cur;
			else
				ppa_netif_free_item(p_cur);
			break;
		}
	ppa_netif_unlock_list();
}

static void ppa_netif_free_list(void)
{
	struct netif_info *obj;

	ppa_netif_lock_list();
	while (g_netif) {
		obj = g_netif;
		g_netif = g_netif->next;

		ppa_netif_free_item(obj);
		obj = NULL;
	}
	ppa_netif_unlock_list();
}

/* ####################################
 *           Global Function
 * ####################################
 */

int32_t ppa_phys_port_add(PPA_IFNAME *ifname, uint32_t port)
{
	struct phys_port_info *obj;
	uint32_t mode = 0;
	uint32_t type = 0;
	uint32_t vlan = 0;
	PPE_IFINFO if_info;
	uint32_t irq_flag = 0;

	if (!ifname)
		return PPA_EINVAL;

	ppa_memset(&if_info, 0, sizeof(if_info));
	if_info.port = port;

	ppa_drv_get_phys_port_info(&if_info, 0);
	if ((if_info.if_flags & PPA_PHYS_PORT_FLAGS_VALID)) {

		switch (if_info.if_flags & PPA_PHYS_PORT_FLAGS_MODE_MASK) {
		case PPA_PHYS_PORT_FLAGS_MODE_LAN:
			mode = 1;
			break;
		case PPA_PHYS_PORT_FLAGS_MODE_WAN:
			mode = 2;
			break;
		case PPA_PHYS_PORT_FLAGS_MODE_MIX:
			mode = 3;
		}

		switch (if_info.if_flags & PPA_PHYS_PORT_FLAGS_TYPE_MASK) {
		case PPA_PHYS_PORT_FLAGS_TYPE_CPU:
			type = 0;
			break;
		case PPA_PHYS_PORT_FLAGS_TYPE_ATM:
			type = 1;
			break;
		case PPA_PHYS_PORT_FLAGS_TYPE_ETH:
			type = 2;
			break;
		case PPA_PHYS_PORT_FLAGS_TYPE_EXT:
			type = 3;
		}
		vlan = (if_info.if_flags & PPA_PHYS_PORT_FLAGS_OUTER_VLAN)
			? 2 : 1;
	}
	/*trick here with ppa_lock_get2 since it will be called in irqs_disabled
	 * mode by directpath wlan registering
	 */
	irq_flag = ppa_lock_get2(&g_phys_port_lock);
	for (obj = g_phys_port_info; obj; obj = obj->next)
		if (obj->port == port) {
			snprintf(obj->ifname, sizeof(obj->ifname), "%s", ifname);
			obj->mode = mode;
			obj->type = type;
			obj->vlan   = vlan;
			break;
		}
	ppa_lock_release2(&g_phys_port_lock, irq_flag);

	if (!obj) {
		obj = ppa_phys_port_alloc_item();
		if (!obj)
			return PPA_ENOMEM;
		snprintf(obj->ifname, sizeof(obj->ifname), "%s", ifname);
		obj->mode   = mode;
		obj->type   = type;
		obj->port   = port;
		obj->vlan   = vlan;
		irq_flag = ppa_lock_get2(&g_phys_port_lock);
		obj->next = g_phys_port_info;
		g_phys_port_info = obj;
		ppa_lock_release2(&g_phys_port_lock, irq_flag);
	}
	return PPA_SUCCESS;
}

void ppa_phys_port_remove(uint32_t port)
{
	struct phys_port_info *p_prev, *p_cur;
	uint32_t irq_flags = 0;

	p_prev = NULL;

	/*trick here with ppa_lock_get2 since it will be called in irqs_disabled
	 * mode by directpath wlan registering
	 */
	irq_flags = ppa_lock_get2(&g_phys_port_lock);
	p_cur = g_phys_port_info;
	for (; p_cur; p_prev = p_cur, p_cur = p_cur->next)
		if (p_cur->port == port) {
			if (!p_prev)
				g_phys_port_info = p_cur->next;
			else
				p_prev->next = p_cur->next;
			ppa_lock_release2(&g_phys_port_lock, irq_flags);
			ppa_phys_port_free_item(p_cur);
			return;
		}
	ppa_lock_release2(&g_phys_port_lock, irq_flags);
}

int32_t ppa_phys_port_get_first_eth_lan_port(uint32_t *ifid,
					     PPA_IFNAME **ifname)
{
	int32_t ret;
	struct phys_port_info *obj;

	if (!ifid || !ifname)
		return PPA_EINVAL;

	ret = PPA_ENOTAVAIL;

	ppa_lock_get(&g_phys_port_lock);
	for (obj = g_phys_port_info; obj; obj = obj->next)
		if (obj->mode == 1 && obj->type == 2) {
			*ifid = obj->port;
			*ifname = &(obj->ifname[0]);
			ret = PPA_SUCCESS;
			break;
		}
	ppa_lock_release(&g_phys_port_lock);

	return ret;
}

int32_t ppa_phys_port_start_iteration(uint32_t *ppos,
				      struct phys_port_info **ifinfo)
{
	uint32_t l;
	struct phys_port_info *p;

	ppa_lock_get(&g_phys_port_lock);

	p = g_phys_port_info;
	l = *ppos;
	while (p && l) {
		p = p->next;
		l--;
	}

	if (l == 0 && p) {
		++*ppos;
		*ifinfo = p;
		return PPA_SUCCESS;
	} else {
		*ifinfo = NULL;
		return PPA_FAILURE;
	}
}
EXPORT_SYMBOL(ppa_phys_port_start_iteration);

int32_t ppa_phys_port_iterate_next(uint32_t *ppos,
				   struct phys_port_info **ifinfo)
{
	if (*ifinfo) {
		++*ppos;
		*ifinfo = (*ifinfo)->next;
		return *ifinfo ? PPA_SUCCESS : PPA_FAILURE;
	} else {
		return PPA_FAILURE;
	}
}
EXPORT_SYMBOL(ppa_phys_port_iterate_next);

void ppa_phys_port_stop_iteration(void)
{
	ppa_lock_release(&g_phys_port_lock);
}
EXPORT_SYMBOL(ppa_phys_port_stop_iteration);

#if defined(CONFIG_LTQ_PPA_IF_MIB) && CONFIG_LTQ_PPA_IF_MIB
static inline void ppa_add_subif(struct netif_info *pnet_if, const char *ifname)
{
	if (pnet_if->sub_if_index < PPA_IF_SUB_NAME_MAX_NUM) {
		ppa_strncpy(pnet_if->sub_if_name[pnet_if->sub_if_index],
			    ifname, PPA_IF_NAME_SIZE);
		pnet_if->sub_if_index++;
	}
}
#else
#define ppa_add_subif(pnet_if, ifname)
#endif


#if defined(CONFIG_LTQ_PPA_GRX500) && CONFIG_LTQ_PPA_GRX500
/* Add pce rule to avoid local traffic from hitting the acceleration lookup */
static void ppa_add_bridge_class_rule(struct netif_info *p_ifinfo,
				      PPA_NETIF *netif)
{
	uint32_t brip = 0;
	PPA_CLASS_RULE class_rule;

	if (ppa_get_netif_ip(&brip, netif) == PPA_SUCCESS) {
		ppa_memset(&class_rule, 0, sizeof(PPA_CLASS_RULE));

		class_rule.in_dev = GSWR_INGRESS;
		class_rule.category = CAT_MGMT;

		class_rule.pattern.bEnable = 1;
		class_rule.pattern.eDstIP_Select = 1;
		class_rule.pattern.nDstIP.nIPv4 = brip;
		class_rule.pattern.nDstIP_Mask = 0xFF00;

		class_rule.action.fwd_action.rtaccelenable = 0;
		class_rule.action.fwd_action.rtctrlenable = 1;

		class_rule.action.fwd_action.processpath = 4;

		class_rule.action.rmon_action = 1;
		class_rule.action.rmon_id = 23;

		if (ppa_add_class_rule(&class_rule) == PPA_SUCCESS)
			p_ifinfo->fid_index = class_rule.uidx;
	}
}
#endif

static void ppa_update_netif_name(PPA_NETIF *netif)
{
	struct netif_info *p;
	bool found = false;
	PPA_IFNAME ifname[PPA_IF_NAME_SIZE];

	ifname[0] = 0;

	ppa_netif_lock_list();
	for (p = g_netif; p; p = p->next)
		if (p->netif == netif) {
			found = true;
			ppa_strncpy(ifname, p->name, PPA_IF_NAME_SIZE);
			break;
		}

	if (!found || ifname[0] == 0) {
		ppa_netif_unlock_list();
		return;
	}

	ppa_debug(DBG_ENABLE_MASK_DEBUG_PRINT,
		  "updating netif name change [%s:%s]\n",
		  ifname, ppa_get_netif_name(netif));

	for (p = g_netif; p; p = p->next) {
		if (ppa_str_cmp(p->name, ifname))
			ppa_strncpy(p->name, netif->name, PPA_IF_NAME_SIZE);

		if (ppa_str_cmp(p->manual_lower_ifname, ifname))
			ppa_strncpy(p->manual_lower_ifname, netif->name,
				    PPA_IF_NAME_SIZE);

		if (ppa_str_cmp(p->phys_netif_name, ifname))
			ppa_strncpy(p->phys_netif_name, netif->name,
				    PPA_IF_NAME_SIZE);

	}
	ppa_netif_unlock_list();
}

static void ppa_update_netif_mac(PPA_NETIF *netif)
{
	PPA_IFNAME *ifname;
	struct netif_info *p_ifinfo = NULL;
	PPE_ROUTE_MAC_INFO mac_info;

	ifname = ppa_get_netif_name(netif);
	if (ifname == NULL)
		return;

	ppa_remove_sessions_on_netif(ifname);

	if (ppa_get_netif_info(ifname, &p_ifinfo) == PPA_SUCCESS &&
	    p_ifinfo != NULL) {
		if ((p_ifinfo->flags & NETIF_MAC_ENTRY_CREATED)) {
			ppa_memset(&mac_info, 0, sizeof(PPE_ROUTE_MAC_INFO));
			mac_info.mac_ix = p_ifinfo->mac_entry;
			ppa_drv_del_mac_entry(&mac_info, 0);
			p_ifinfo->mac_entry = ~0;
			p_ifinfo->flags &= ~NETIF_MAC_ENTRY_CREATED;
		}
		if (ppa_get_netif_hwaddr(p_ifinfo->netif, p_ifinfo->mac,
					 1) == PPA_SUCCESS &&
		    (p_ifinfo->mac[0] |
		     p_ifinfo->mac[1] |
		     p_ifinfo->mac[2] |
		     p_ifinfo->mac[3] |
		     p_ifinfo->mac[4] |
		     p_ifinfo->mac[5]) != 0) {
			p_ifinfo->flags |= NETIF_MAC_AVAILABLE;
		} else {
			mac_info.mac_ix = p_ifinfo->mac_entry;
			ppa_drv_del_mac_entry(&mac_info, 0);
			p_ifinfo->mac_entry = ~0;
			p_ifinfo->flags &= ~(NETIF_MAC_ENTRY_CREATED
					     | NETIF_MAC_AVAILABLE);
		}

		if ((p_ifinfo->flags & NETIF_MAC_AVAILABLE)) {
			ppa_memset(&mac_info, 0, sizeof(PPE_ROUTE_MAC_INFO));
			ppa_memcpy(mac_info.mac, p_ifinfo->mac,
				   sizeof(mac_info.mac));
			if (ppa_drv_add_mac_entry(&mac_info,
						  0) == PPA_SUCCESS) {
				p_ifinfo->mac_entry = mac_info.mac_ix;
				p_ifinfo->flags |= NETIF_MAC_ENTRY_CREATED;
			} else {
				ppa_debug(DBG_ENABLE_MASK_ERR,
					  "add_mac_entry failed\n");
			}
		}
		ppa_netif_put(p_ifinfo);
	}
}

static void ppa_register_new_netif(PPA_NETIF *netif)
{
	PPA_IFNAME phy_ifname[PPA_IF_NAME_SIZE];
	PPA_IFNAME *ifname;
	struct netif_info *p_ifinfo = NULL;
	int f_is_lan = 0;
	int force_wanitf = 0;
	struct iface_list *local;

	phy_ifname[0] = 0;
	ifname = ppa_get_netif_name(netif);
	if (ifname == NULL)
		return;

	/* Maually deleted ifname from PPA should not be added until it is
	 * explicitaly added.
	 */

	ppa_list_for_each_entry(local, &manual_del_iface_list, node_ptr)
		if (ppa_str_cmp(local->name, ifname)) {
			ppa_debug(DBG_ENABLE_MASK_DEBUG_PRINT,
				  "Manually deleted[%s] cannot be auto added\n",
				  ifname);
			return;
		}

	/* Iface was already added into PPA durig init or before
	 * creation of netif, and needs relearning after netif creation
	 */
	if (ppa_get_netif_info(ifname, &p_ifinfo) == PPA_SUCCESS &&
	    p_ifinfo != NULL) {
		ppa_netif_put(p_ifinfo);
		ppa_debug(DBG_ENABLE_MASK_DEBUG_PRINT,
			  "Update already exsiting iface[%s]\n", ifname);
		ppa_netif_update(netif, NULL);
		return;
	}

	/* New netif will automatically be added into PPA if its physcial
	 * is already present in PPA. If netif is bridge, it will be added
	 * to LAN group. All handling done after ppacmd init.
	 */
	if ((ppa_get_physical_if(netif, NULL, phy_ifname) == PPA_SUCCESS) &&
	    (ppa_strlen(phy_ifname) > 0)) {
		if ((ppa_get_netif_info(phy_ifname, &p_ifinfo) == PPA_SUCCESS)
		    && (p_ifinfo != NULL)) {
			f_is_lan = p_ifinfo->flags & NETIF_LAN_IF;
			force_wanitf = p_ifinfo->f_wanitf.flag_force_wanitf;
			ppa_netif_put(p_ifinfo);

			if (ppa_netif_add(ifname, f_is_lan, NULL, NULL,
					  force_wanitf) != PPA_SUCCESS)
				ppa_debug(DBG_ENABLE_MASK_DEBUG_PRINT,
					  "Adding iface[%s] to PPA failed\n",
					  ifname);
		} else if (ppa_if_is_br_if(netif, NULL)) {
			ppa_netif_add(ifname, NETIF_LAN_IF, NULL, NULL, 0);
			ppa_debug(DBG_ENABLE_MASK_DEBUG_PRINT,
				  "dynamically adding bridge iface[%s]\n",
				  ifname);
		} else if (ppa_if_is_br2684(netif, NULL)) {
			ppa_netif_add(ifname, f_is_lan, NULL, NULL, 0);
			ppa_debug(DBG_ENABLE_MASK_DEBUG_PRINT,
				  "dynamically adding ATM iface[%s]\n", ifname);
		}

	}
}

static void ppa_unregister_new_netif(PPA_NETIF *netif)
{
	PPA_IFNAME phy_ifname[PPA_IF_NAME_SIZE];
	PPA_IFNAME *ifname;
	struct netif_info *p_ifinfo = NULL;
	int f_is_lan = 0;

	phy_ifname[0] = 0;

	ifname = ppa_get_netif_name(netif);

	if (ifname == NULL)
		return;

	/* Logical netif will automatically be removed from PPA after
	 * ppacmd init. All handling is done after ppacmd init
	 */

	if (ppa_get_netif_info(ifname, &p_ifinfo) != PPA_SUCCESS
	    || p_ifinfo == NULL)
		return;

	f_is_lan = p_ifinfo->flags & NETIF_LAN_IF;
	if (ppa_memcmp(p_ifinfo->name, p_ifinfo->phys_netif_name,
		       ppa_strlen(p_ifinfo->name)) != 0) {
		ppa_netif_put(p_ifinfo);
		ppa_debug(DBG_ENABLE_MASK_DEBUG_PRINT,
			  "dynamically removing netif[%s]\n", ifname);
		ppa_netif_remove(ifname, f_is_lan);
		return;
	} else {
		/* Physical netif removed from system.
		 * So assigning NULL to PPA netif entry.
		 */
		p_ifinfo->netif = NULL;
		ppa_netif_put(p_ifinfo);
	}
	if (ppa_if_is_br_if(netif, NULL)) {
		ppa_netif_remove(ifname, f_is_lan);
		ppa_debug(DBG_ENABLE_MASK_DEBUG_PRINT,
			  "dynamically removing bridge[%s]\n", ifname);
	} else if (ppa_if_is_br2684(netif, NULL)) {
		ppa_netif_remove(ifname, f_is_lan);
		ppa_debug(DBG_ENABLE_MASK_DEBUG_PRINT,
			  "dynamically removing ATM iface[%s]\n", ifname);
	}
}

static void ppa_netif_up(PPA_NETIF *netif)
{
	struct netif_info *p_ifinfo = NULL;
	PPA_IFNAME *ifname;

	/* ppa_get_physical_if() fails for pppoe net_dev because call to
	 * ppa_check_is_pppoe_netif() also validated only if pppoe_addr
	 * is assigned to fetch the physical interface.
	 * So, adding pppoe into ppa on up event
	 */
	if (ppa_check_is_ppp_netif(netif))
		ppa_register_new_netif(netif);

	ifname = ppa_get_netif_name(netif);
	if (ifname == NULL)
		return;

	ppa_netif_lock_list();
	for (p_ifinfo = g_netif; p_ifinfo; p_ifinfo = p_ifinfo->next) {
		if (strcmp(p_ifinfo->name, ifname) == 0) {
			p_ifinfo->enable = true;
			break;
		}
	}
	ppa_netif_unlock_list();
}

static void ppa_netif_down(PPA_NETIF *netif)
{
	struct netif_info *p_ifinfo = NULL;
	PPA_IFNAME *ifname;

	ifname = ppa_get_netif_name(netif);
	if (ifname == NULL)
		return;

	ppa_netif_lock_list();
	for (p_ifinfo = g_netif; p_ifinfo; p_ifinfo = p_ifinfo->next) {
		if (strcmp(p_ifinfo->name, ifname) == 0) {
			p_ifinfo->enable = false;
			break;
		}
	}
	ppa_netif_unlock_list();
	ppa_remove_sessions_on_netif(ifname);
}

int ppa_phy_netdevice_event(PPA_NOTIFIER_BLOCK *nb,
			    unsigned long action, void *ptr)
{
	PPA_NETIF *netif = NULL;
	PPA_IFNAME *ifname = NULL;

	if (ptr == NULL)
		return PPA_NOTIFY_BAD;

	netif = ppa_netdev_notifier_info_to_dev(ptr);

        ifname = ppa_get_netif_name(netif);
#if defined(CONFIG_PPTP_MODULE) || defined(CONFIG_PPTP)
	if(ppa_is_pptp_netif(netif)) {

		return PPA_NOTIFY_BAD;
	}
#endif
        if (strnstr(ifname,"ppp",PPA_IF_NAME_SIZE)== 0){ 

		return PPA_NOTIFY_BAD;
	}

	switch (action) {
	case NETDEV_REGISTER:
		ppa_register_new_netif(netif);
		break;
	case NETDEV_UNREGISTER:
		ppa_unregister_new_netif(netif);
		break;
	case NETDEV_CHANGEADDR:
		ppa_update_netif_mac(netif);
	case NETDEV_CHANGENAME:
		ppa_update_netif_name(netif);
		break;
	case NETDEV_UP:
		ppa_netif_up(netif);
		break;
	case NETDEV_DOWN:
		ppa_netif_down(netif);
		break;
	case NETDEV_PRE_UP:
	case NETDEV_CHANGE:
	case NETDEV_POST_INIT:
	case NETDEV_POST_TYPE_CHANGE:
		ppa_netif_update(netif, NULL);
		break;
	}
	ppa_debug(DBG_ENABLE_MASK_DEBUG_PRINT,
			"ppa_netdevice_event[%s:%x]\n",
			ppa_get_netif_name(netif), action);
	return PPA_NOTIFY_OK;
}

PPA_NOTIFIER_BLOCK ppa_netdevice_notifier = {
	.notifier_call = ppa_phy_netdevice_event
};

#if defined(CONFIG_PPA_PUMA7) && defined(CONFIG_TI_HIL_PROFILE_INTRUSIVE_P7)
static void ppa_netdev_pp_prepare_vpid(struct netif_info *p_ifinfo,
				       uint32_t flags)
{
	PPA_NETIF *netif, *lnetif;
	uint16_t setup_flag = 0;
	uint32_t ip = 0;

	PPA_IFNAME underlying_ifname[PPA_IF_NAME_SIZE];

	lnetif = netif = NULL;
	underlying_ifname[0] = '\0';

	netif = ppa_get_netif(p_ifinfo->name);
	if (netif != NULL) {
		if ((ppa_get_netif_ip(&ip, netif) == PPA_SUCCESS)
		    && ip > 0) {
			/* for NETIF_PPPOE, create VPID on actual interafce */
			if (p_ifinfo->flags & NETIF_PPPOE &&
			    ppa_pppoe_get_physical_if(netif, NULL, underlying_ifname) == PPA_SUCCESS) {
				netif = ppa_get_netif(underlying_ifname);
			}
			setup_flag = 1;
		}
		/* check if this is a bonded slave interface */
		if (ppa_is_bond_slave(NULL, netif))
			setup_flag = 1;
		/* check if interface is under bridge */
		if (ppa_is_netif_bridged(netif))
			setup_flag = 1;
		/* check if interface is LAN and not bridge */
		if (flags && !(ppa_if_is_br_if(netif, NULL)))
			setup_flag = 1;
		if ((p_ifinfo->flags & NETIF_PHY_TUNNEL) ||
				(p_ifinfo->flags & NETIF_PPPOL2TP))
			setup_flag = 0;

		if (setup_flag) {
			// for virtual interface copy pid_handle and do netdev cloning
			lnetif = ppa_get_netif(p_ifinfo->phys_netif_name);
			if (lnetif != NULL && netif != NULL) {
				netif->vpid_block.parent_pid_handle = lnetif->pid_handle;
				netif->pid_handle = lnetif->pid_handle;
				ti_hil_clone_netdev_pp_info(netif, lnetif);
			}

			/* for VLAN interface set vpid block type as
			 * AVALANCHE_PP_VPID_VLAN
			 */
			if (p_ifinfo->flags & NETIF_VLAN) {
				netif->vpid_block.type = AVALANCHE_PP_VPID_VLAN;
				if (p_ifinfo->flags & NETIF_VLAN_INNER)
					netif->vpid_block.vlan_identifier = p_ifinfo->inner_vid;
			} else {
				netif->vpid_block.type = AVALANCHE_PP_VPID_ETHERNET;
			}
			ti_hil_pp_event (TI_PP_ADD_VPID, netif);
		}
	}
	return;
}

static void ppa_netdev_pp_remove_vpid(struct netif_info *p_ifinfo)
{
	PPA_NETIF *lnetif, *netif;
	PPA_IFNAME underlying_ifname[PPA_IF_NAME_SIZE];
	netif = ppa_get_netif(p_ifinfo->name);
	if(netif != NULL) {
		/* for NETIF_PPPOE, delete VPID of actual interafce */
		if (p_ifinfo->flags & NETIF_PPPOE &&
				(ppa_pppoe_get_physical_if(netif, NULL,
							   underlying_ifname) == PPA_SUCCESS)) {
			lnetif = ppa_get_netif(underlying_ifname);
			if (lnetif != NULL) {
				if (lnetif->qos_shutdown_hook != NULL)
					lnetif->qos_shutdown_hook(lnetif);
				ti_hil_pp_event(TI_PP_REMOVE_VPID,
						lnetif);
			}
		} else {
			if (netif->qos_shutdown_hook != NULL)
				netif->qos_shutdown_hook(netif);
			ti_hil_pp_event(TI_PP_REMOVE_VPID, netif);
		}
	}
	return;
}
#endif

int32_t ppa_netif_add(PPA_IFNAME *ifname, int f_is_lan,
		      struct netif_info **pp_ifinfo, PPA_IFNAME *ifname_lower,
		      int force_wanitf)
{
	struct netif_info *p_ifinfo;
	struct netif_info *tmp_info;
	PPA_NETIF *netif, *netif_tmp = NULL;
	PPA_VCC *vcc;
	int32_t dslwan_qid;
	PPA_IFNAME underlying_ifname[PPA_IF_NAME_SIZE];
	uint32_t vid[2] = {0};
	struct phys_port_info *p_phys_port = NULL;
#define DEFAULT_OUTER_VLAN_ID 0x81000000
	PPA_NETIF *tmp_vlan_netif[2] = {NULL};
	uint8_t add_flag_fail = 0;
	int32_t ret = PPA_SUCCESS;
	uint8_t isIPv4Gre, is_gretap;
#if defined(CONFIG_LTQ_PPA_GRX500) && CONFIG_LTQ_PPA_GRX500
	dp_subif_t dp_subif = {0};
	PPE_OUT_VLAN_INFO vlan_info = {0};
	PPA_NETIF *brif = NULL;
	struct module *oner = NULL;
	PPA_BR_PORT_INFO port_info = {0};
#endif
 	struct netif_info *pp_netif_info = NULL;

	netif = ppa_get_netif(ifname);
#if defined(CONFIG_LTQ_PPA_GRX500) && CONFIG_LTQ_PPA_GRX500
	if (ppa_is_netif_bridged(netif)) {
		ppa_debug(DBG_ENABLE_MASK_DEBUG_PRINT,
			  "netif=%s is under bridge\n", netif->name);
		ppa_rtnl_lock();
		brif = ppa_netdev_master_upper_dev_get(netif);
		ppa_rtnl_unlock();
	}
#endif

	if (ppa_get_netif_info(ifname, &p_ifinfo) == PPA_SUCCESS) {
		ppa_debug(DBG_ENABLE_MASK_DEBUG_PRINT,
			  "interface %s already exist\n", ifname);
		if (ifname_lower && ppa_strlen(ifname_lower)
		    && ppa_strlen(p_ifinfo->manual_lower_ifname)
		    && strcmp(ifname_lower,
			      p_ifinfo->manual_lower_ifname) != 0) {
			/* conflicts and it should update its physical port id
			 * and names. But temporarily we just return fail
			 */
			add_flag_fail = 1;
		}
		goto PPA_ADD_NETIF_DONE;
	}

	p_ifinfo = ppa_netif_alloc_item();
	if (!p_ifinfo)
		return PPA_ENOMEM;

	ppa_strncpy(p_ifinfo->name, ifname, sizeof(p_ifinfo->name));
	if (ifname_lower && ppa_strlen(ifname_lower)) {
		ppa_strncpy(p_ifinfo->manual_lower_ifname, ifname_lower,
			    sizeof(p_ifinfo->manual_lower_ifname)-1);
		ppa_debug(DBG_ENABLE_MASK_DEBUG_PRINT,
			  "Set manual_lower_ifname to %s\n",
			  p_ifinfo->manual_lower_ifname);
	} else {
		p_ifinfo->manual_lower_ifname[0] = 0;
		ppa_get_lower_if(NULL, ifname, p_ifinfo->manual_lower_ifname);
	}

	if (!netif) {
		p_ifinfo->netif = NULL;
		goto PPA_SKIP_NETIF_UPDATE;
	}

	p_ifinfo->netif = netif;
	p_ifinfo->mtu = netif->mtu;
#if defined(CONFIG_LTQ_PPA_GRX500) && CONFIG_LTQ_PPA_GRX500
	p_ifinfo->brif = brif;
#endif


LOOP_CHECK:
	if (!(p_ifinfo->flags & NETIF_MAC_AVAILABLE) &&
	    ppa_get_netif_hwaddr(netif, p_ifinfo->mac, 1) == PPA_SUCCESS &&
	    (p_ifinfo->mac[0] |
	     p_ifinfo->mac[1] |
	     p_ifinfo->mac[2] |
	     p_ifinfo->mac[3] |
	     p_ifinfo->mac[4] |
	     p_ifinfo->mac[5]) != 0) {
		p_ifinfo->flags |= NETIF_MAC_AVAILABLE;
	}

	netif_tmp = NULL;
	if (netif->type == ARPHRD_SIT) {
		p_ifinfo->flags |= NETIF_PHY_TUNNEL;
		if (ppa_get_6rd_phyif_fn != NULL)
			netif_tmp = ppa_get_6rd_phyif_fn(netif);
		if (!netif_tmp)
			ppa_debug(DBG_ENABLE_MASK_DEBUG_PRINT,
				  "Add sit device: %s, but cannot find the physical device\n",
				  netif->name);
	} else if (netif->type == ARPHRD_TUNNEL6) {
#if defined(CONFIG_LTQ_PPA_DSLITE) && CONFIG_LTQ_PPA_DSLITE
		p_ifinfo->flags |= NETIF_PHY_TUNNEL;
		if (ppa_get_ip4ip6_phyif_fn != NULL)
			netif_tmp = ppa_get_ip4ip6_phyif_fn(netif);
		if (!netif_tmp)
			ppa_debug(DBG_ENABLE_MASK_DEBUG_PRINT,
				  "Add ip4ip6 device: %s, but cannot find the physical device\n",
				  netif->name);
#endif
	} else {
		isIPv4Gre = is_gretap = 0;
		if (ppa_if_is_vlan_if(netif, NULL) &&
		    (ppa_vlan_get_underlying_if(netif, NULL, underlying_ifname)
		     == PPA_SUCCESS)) {
			netif_tmp = ppa_get_netif(underlying_ifname);
			if (ppa_is_gre_netif_type(netif_tmp, &isIPv4Gre,
						&is_gretap)) {
				ppa_debug(DBG_ENABLE_MASK_DEBUG_PRINT,
						"<%s> %s is a GRE interface!!!!!\n",
						__func__, netif_tmp->name);
				netif = netif_tmp;
			}
			netif_tmp = NULL;
		}

		if (ppa_is_gre_netif_type(netif, &isIPv4Gre, &is_gretap)) {

#if defined(CONFIG_PPTP_MODULE) || defined(CONFIG_PPTP)
			if(ppa_is_pptp_netif(netif)) {
				p_ifinfo->flags |= NETIF_PPTP_TUNNEL;
				netif_tmp = ppa_get_netif(p_ifinfo->manual_lower_ifname);
				// update the VLAN info
    				ppa_netif_lookup(netif_tmp, &pp_netif_info);
				if ( pp_netif_info && (pp_netif_info->flags & NETIF_VLAN_INNER) )
  				{
					p_ifinfo->flags |= NETIF_VLAN;
					p_ifinfo->inner_vid = pp_netif_info->inner_vid;
					p_ifinfo->flags |= NETIF_VLAN_INNER;
					p_ifinfo->in_vlan_netif = netif_tmp;
				}
				if ( pp_netif_info && (pp_netif_info->flags & NETIF_PPPOE) )
				{
					p_ifinfo->flags |= NETIF_PPPOE;
					p_ifinfo->pppoe_session_id = pp_netif_info->pppoe_session_id ;

				}
	
				p_ifinfo->manual_lower_ifname[0] = 0;
			} else {
				netif_tmp = ppa_get_gre_phyif(netif);
			}
#else
			netif_tmp = ppa_get_gre_phyif(netif);
#endif
			p_ifinfo->flags |= NETIF_PHY_TUNNEL | NETIF_GRE_TUNNEL;
			if (!netif_tmp) {
				ppa_debug(DBG_ENABLE_MASK_ERR,
					  "GRE device: %s, Could not find phyical device\n",
					  netif->name);
			} else {
				if (isIPv4Gre)
					p_ifinfo->greInfo.flowId = (is_gretap) ?
						FLOWID_IPV4_EoGRE :
						FLOWID_IPV4GRE;
				else
					p_ifinfo->greInfo.flowId = (is_gretap) ?
						FLOWID_IPV6_EoGRE :
						FLOWID_IPV6GRE;
			}
#if defined(CONFIG_LTQ_PPA_GRX500) && CONFIG_LTQ_PPA_GRX500
			ppa_get_gre_hdrlen(p_ifinfo->netif,
					   &p_ifinfo->greInfo.tnl_hdrlen);
#endif
		}
	}

	if (netif_tmp) {
		netif = netif_tmp;
		ppa_debug(DBG_ENABLE_MASK_DEBUG_PRINT,
			  "adding ppa subif(%s, %s)\n",
			  p_ifinfo->name, netif->name);
		ppa_add_subif(p_ifinfo, netif->name);
	}

	netif_tmp = ppa_get_netif(p_ifinfo->manual_lower_ifname);
	if (netif_tmp) {
		netif = netif_tmp;
		ppa_debug(DBG_ENABLE_MASK_DEBUG_PRINT,
			  "set netif to its manual_lower_ifname %s\n",
			  p_ifinfo->manual_lower_ifname);
		ppa_add_subif(p_ifinfo, netif->name);
	} else {
		ppa_debug(DBG_ENABLE_MASK_DEBUG_PRINT,
			  "ifname %s not exist ??\n",
			  p_ifinfo->manual_lower_ifname);
	}

	if (ppa_get_physical_if(netif, NULL,
				p_ifinfo->phys_netif_name) == PPA_SUCCESS) {
		p_ifinfo->flags |= NETIF_PHY_IF_GOT;
		ppa_debug(DBG_ENABLE_MASK_DEBUG_PRINT,
			  "phys_netif_name=%s with ifname=%s\n",
			  p_ifinfo->phys_netif_name, ifname);
		if (ppa_memcmp(p_ifinfo->phys_netif_name, ifname,
			       ppa_strlen(ifname)) == 0)
			p_ifinfo->f_wanitf.flag_root_itf = 1;
	}

#if defined(L2TP_CONFIG) && L2TP_CONFIG
back_to_ppp:
#endif
	if (ppa_if_is_ipoa(netif, NULL) &&
	    ppa_br2684_get_vcc(netif, &vcc) == PPA_SUCCESS) {
		dslwan_qid = ppa_drv_get_dslwan_qid_with_vcc(vcc);
		if (dslwan_qid >= 0) {
			p_ifinfo->flags |= NETIF_PHY_ATM
				| NETIF_BR2684 | NETIF_IPOA;

			p_ifinfo->vcc = vcc;
			p_ifinfo->dslwan_qid = dslwan_qid;
			goto PPA_NETIF_ADD_ATM_BASED_NETIF_DONE;
		}
	} else if (ppa_check_is_ppp_netif(netif)) {
		if (ppa_check_is_pppoe_netif(netif) &&
		    ppa_pppoe_get_physical_if(netif, NULL, underlying_ifname
					     ) == PPA_SUCCESS) {
			p_ifinfo->pppoe_session_id =
				ppa_pppoe_get_pppoe_session_id(netif);
			p_ifinfo->flags |= NETIF_PPPOE;
			netif = ppa_get_netif(underlying_ifname);
			if (netif)
				ppa_add_subif(p_ifinfo, netif->name);
		} else if (ppa_if_is_pppoa(netif, NULL) &&
			   ppa_pppoa_get_vcc(netif,
					     &vcc) == PPA_SUCCESS) {
			dslwan_qid = ppa_drv_get_dslwan_qid_with_vcc(vcc);
			if (dslwan_qid >= 0) {
				p_ifinfo->flags |= NETIF_PHY_ATM
					| NETIF_PPPOATM;
				p_ifinfo->vcc = vcc;
				p_ifinfo->dslwan_qid = dslwan_qid;
				goto PPA_NETIF_ADD_ATM_BASED_NETIF_DONE;
			}
#if defined(L2TP_CONFIG) && L2TP_CONFIG
		} else if (ppa_check_is_pppol2tp_netif(netif)) {
			if (ppa_pppol2tp_get_physical_if(netif, NULL,
							 underlying_ifname))
				ppa_debug(DBG_ENABLE_MASK_DEBUG_PRINT,
					  "ppa_pppol2tp_get_physical_if failed\n");
			p_ifinfo->pppol2tp_session_id =
				ppa_pppol2tp_get_l2tp_session_id(netif);
			p_ifinfo->pppol2tp_tunnel_id =
				ppa_pppol2tp_get_l2tp_tunnel_id(netif);
			p_ifinfo->flags |= NETIF_PPPOL2TP;

			netif = ppa_get_netif(underlying_ifname);
			if (netif && ppa_check_is_ppp_netif(netif))
				goto back_to_ppp;
#endif
		}
	}

	while (netif && ppa_if_is_vlan_if(netif, NULL) &&
	       ppa_vlan_get_underlying_if(netif, NULL,
					  underlying_ifname) == PPA_SUCCESS) {
		PPA_NETIF *new_netif;
		p_ifinfo->flags |= NETIF_VLAN;
		/* Done with setting flowid & TC */
		if (p_ifinfo->vlan_layer < NUM_ENTITY(vid)) {
			vid[p_ifinfo->vlan_layer] = ppa_get_vlan_id(netif);
			tmp_vlan_netif[p_ifinfo->vlan_layer] = netif;
		}

		p_ifinfo->vlan_layer++;
		new_netif = ppa_get_netif(underlying_ifname);
		if (new_netif == netif) {
			/* VLAN interface and underlying interface share
			 * the same name! Break the loop
			 */
			break;
		}
		netif = new_netif;
		ppa_add_subif(p_ifinfo, netif->name);
	}
	if (!netif)
		goto PPA_SKIP_NETIF_UPDATE;

	/* Special handling for those interface which added with
	 * manually specified lower interface with ppacmd addwan/addlan
	 * -l lower_interface
	 */
	if (__ppa_netif_lookup(netif->name, &tmp_info) == PPA_SUCCESS) {
		netif_tmp = ppa_get_netif(tmp_info->manual_lower_ifname);
		if (netif_tmp) {
			netif = netif_tmp;
			ppa_add_subif(p_ifinfo, netif->name);
			ppa_atomic_dec(&tmp_info->count);
			ppa_debug(DBG_ENABLE_MASK_DEBUG_PRINT,
				  "Need continue check for %s is manually added interface",
				  tmp_info->manual_lower_ifname);
			goto LOOP_CHECK;
		}
		ppa_atomic_dec(&tmp_info->count);
	}

	if (ppa_if_is_br_if(netif, NULL)) {
		p_ifinfo->flags |= NETIF_BRIDGE;
#if defined(CONFIG_LTQ_PPA_GRX500) && CONFIG_LTQ_PPA_GRX500
		ppa_add_bridge_class_rule(p_ifinfo, netif);
#endif
	} else if (ppa_if_is_br2684(netif, NULL) &&
		   ppa_br2684_get_vcc(netif, &vcc) == PPA_SUCCESS) {
		dslwan_qid = ppa_drv_get_dslwan_qid_with_vcc(vcc);
		if (dslwan_qid >= 0) {
			p_ifinfo->flags |= NETIF_PHY_ATM
				| NETIF_BR2684
				| NETIF_EOA;
			p_ifinfo->vcc = vcc;
			p_ifinfo->dslwan_qid = dslwan_qid;
		}
	} else
		p_ifinfo->flags |= NETIF_PHY_ETH;
#if defined(CONFIG_LTQ_PPA_GRX500) && CONFIG_LTQ_PPA_GRX500
#if defined(CONFIG_LTQ_PPA_API_DIRECTPATH)
	if (ppa_check_if_netif_directpath(netif, 0) == PPA_SUCCESS) {
		p_ifinfo->flags |= NETIF_DIRECTPATH;
		ppa_debug(DBG_ENABLE_MASK_DEBUG_PRINT,
			  "<%s> Interface %s added to the list\n",
			  __func__, netif->name);
		if ((dp_get_netif_subifid(netif, NULL, NULL, NULL,
			&dp_subif, 0)) == PPA_SUCCESS) {
			p_ifinfo->phys_port = dp_subif.port_id;
			p_ifinfo->flags |= NETIF_PHYS_PORT_GOT;
			p_ifinfo->subif_id = dp_subif.subif;
		} else {
			ppa_free(p_ifinfo);
			return PPA_ENOTPOSSIBLE;
		}
	}
#endif
#if defined(CONFIG_PPA_API_DIRECTCONNECT) && CONFIG_PPA_API_DIRECTCONNECT
	/* Check whether the netif is directconnect
	 * fastpath interface or not
	 */
	if (ppa_check_if_netif_fastpath_fn
	    && ppa_check_if_netif_fastpath_fn(netif, NULL, 0)) {
		p_ifinfo->flags |= NETIF_DIRECTCONNECT;
		/* Get PortId and SubifId = {VapId} corresponding to the
		 * directconnect netif
		 */
		if ((dp_get_netif_subifid(netif, NULL, NULL, NULL,
					  &dp_subif, 0)) == PPA_SUCCESS) {
			p_ifinfo->phys_port = dp_subif.port_id;
			p_ifinfo->flags |= NETIF_PHYS_PORT_GOT;
			p_ifinfo->subif_id = dp_subif.subif;
		} else {
			ppa_free(p_ifinfo);
			return PPA_ENOTPOSSIBLE;
		}
	}
#endif
#if defined(CONFIG_L2NAT_MODULE) || defined(CONFIG_L2NAT)
	/* Check whether the netif is an l2nat interface or not */
	if (ppa_check_if_netif_l2nat_fn &&
	    ppa_check_if_netif_l2nat_fn(netif, NULL, 0))
		p_ifinfo->flags |= NETIF_L2NAT;
#endif
#endif
PPA_SKIP_NETIF_UPDATE:
PPA_NETIF_ADD_ATM_BASED_NETIF_DONE:
	/*  ATM port is WAN port only */
	if ((p_ifinfo->flags & NETIF_PHY_ATM) && (!f_is_lan)) {
		ppa_debug(DBG_ENABLE_MASK_DEBUG_PRINT, "update ATM<%s> WAN ports\n", p_ifinfo->name);
		if (p_ifinfo->vlan_layer > 0 && (p_ifinfo->vlan_layer <=
			g_phys_port_atm_wan_vlan)) {
			if (p_ifinfo->vlan_layer == 2) {
				p_ifinfo->inner_vid = vid[0];
				p_ifinfo->outer_vid = DEFAULT_OUTER_VLAN_ID
					| vid[1];
				p_ifinfo->flags |= NETIF_VLAN_INNER
					| NETIF_VLAN_OUTER;
				p_ifinfo->in_vlan_netif = tmp_vlan_netif[0];
				p_ifinfo->out_vlan_netif = tmp_vlan_netif[1];
			} else if
				((p_ifinfo->vlan_layer == 1) &&
						(g_phys_port_atm_wan_vlan
								== 2)) {
					p_ifinfo->outer_vid =
					DEFAULT_OUTER_VLAN_ID | vid[0];
				p_ifinfo->flags |= NETIF_VLAN_OUTER;
				p_ifinfo->out_vlan_netif = tmp_vlan_netif[0];
			} else if
				((p_ifinfo->vlan_layer == 1) &&
						(g_phys_port_atm_wan_vlan
								== 1)) {
				p_ifinfo->inner_vid = vid[0];
				p_ifinfo->flags |= NETIF_VLAN_INNER;
				p_ifinfo->in_vlan_netif = tmp_vlan_netif[0];
			}
		} else if (p_ifinfo->vlan_layer > 0)
			p_ifinfo->flags |= NETIF_VLAN_CANT_SUPPORT;
		
	p_ifinfo->phys_port = g_phys_port_atm_wan;
	p_ifinfo->flags |= NETIF_PHYS_PORT_GOT;

#if defined(CONFIG_LTQ_PPA_GRX500) && CONFIG_LTQ_PPA_GRX500
	if (p_ifinfo->vcc == NULL)
		dp_subif.port_id = p_ifinfo->phys_port;
	if ((dp_get_netif_subifid(netif, NULL, p_ifinfo->vcc, NULL,
		&dp_subif, 0)) == PPA_SUCCESS) {
		if (p_ifinfo->vcc)
			p_ifinfo->phys_port = dp_subif.port_id;
		p_ifinfo->subif_id = (dp_subif.subif & 0x00FF);
	}
	if ((p_ifinfo->flags & NETIF_VLAN_INNER) || (p_ifinfo->flags
			& NETIF_VLAN_OUTER)) {
		netif = (p_ifinfo->out_vlan_netif) ?
		p_ifinfo->out_vlan_netif : ((p_ifinfo->in_vlan_netif)
		? p_ifinfo->in_vlan_netif : NULL);
		if (netif)
			ppa_add_vlan_entry(netif, &dp_subif, p_ifinfo,
				&vlan_info, &add_flag_fail);
	}
#endif
	} else if ((p_ifinfo->flags & NETIF_PHY_IF_GOT)
		&& !(p_ifinfo->flags & NETIF_BRIDGE)) {
		ret = ppa_phys_port_lookup(p_ifinfo->phys_netif_name,
			&p_phys_port);
#if defined(CONFIG_LTQ_PPA_GRX500) && CONFIG_LTQ_PPA_GRX500
	if (ret != PPA_SUCCESS) {
			/* If the interface is not a part of physical interface
			 * list. Check if it is a dynamic interface
			 */
			ppa_memset(&dp_subif, 0, sizeof(dp_subif));
			ret = dp_get_netif_subifid(netif, NULL, NULL, NULL,
						   &dp_subif, 0);
			if (ret == PPA_SUCCESS) {
				ppa_debug(DBG_ENABLE_MASK_DEBUG_PRINT,
					  "netif=%s portid=%d subifid=%d\n",
					  netif->name,
					  dp_subif.port_id, dp_subif.subif);
				ret = ppa_phys_port_add(netif->name,
							dp_subif.port_id);
				if (ret == PPA_SUCCESS) {
					p_ifinfo->subif_id = dp_subif.subif;
					ppa_phys_port_lookup(p_ifinfo->phys_netif_name,
							     &p_phys_port);
				}
			}
		}
#endif
		if (!p_phys_port) {
			/* case where netif has vlan without having p_phys_port */
			if (p_ifinfo->vlan_layer == 1) {
				p_ifinfo->inner_vid = vid[0];
				p_ifinfo->flags |= NETIF_VLAN_INNER;
				p_ifinfo->in_vlan_netif = tmp_vlan_netif[0];
			}
			goto PPA_PHYS_PORT_UPDATE_DONE;
		}

		if (p_ifinfo->vlan_layer > 0 &&
		    (p_ifinfo->vlan_layer <= p_phys_port->vlan)) {
			if (p_ifinfo->vlan_layer == 2) {
				p_ifinfo->inner_vid = vid[0];
				p_ifinfo->outer_vid = DEFAULT_OUTER_VLAN_ID
					| vid[1];
				p_ifinfo->flags |= NETIF_VLAN_INNER
					| NETIF_VLAN_OUTER;
				p_ifinfo->in_vlan_netif = tmp_vlan_netif[0];
				p_ifinfo->out_vlan_netif = tmp_vlan_netif[1];
			} else if ((p_ifinfo->vlan_layer == 1) &&
				   (p_phys_port->vlan == 2)) {
				p_ifinfo->outer_vid = DEFAULT_OUTER_VLAN_ID
					| vid[0];
				p_ifinfo->flags |= NETIF_VLAN_OUTER;
				p_ifinfo->out_vlan_netif = tmp_vlan_netif[0];
			} else if ((p_ifinfo->vlan_layer == 1) &&
				   (p_phys_port->vlan == 1)) {
				p_ifinfo->inner_vid = vid[0];
				p_ifinfo->flags |= NETIF_VLAN_INNER;
				p_ifinfo->in_vlan_netif = tmp_vlan_netif[0];
			}
		} else if (p_ifinfo->vlan_layer > 0)
				p_ifinfo->flags |= NETIF_VLAN_CANT_SUPPORT;
		p_ifinfo->phys_port = p_phys_port->port;
		p_ifinfo->flags |= NETIF_PHYS_PORT_GOT;
#if defined(CONFIG_LTQ_PPA_GRX500) && CONFIG_LTQ_PPA_GRX500
		ppa_memset(&dp_subif, 0, sizeof(dp_subif));
		/* If interface is VDSL so we need to get the Qid[6:3]
		 * from the base interface
		 */
		if ((dp_get_netif_subifid(netif, NULL, NULL, NULL,
				&dp_subif, 0)) == PPA_SUCCESS) {
			p_ifinfo->phys_port = dp_subif.port_id;
			p_ifinfo->subif_id = dp_subif.subif;
		}
		if ((p_ifinfo->flags & NETIF_VLAN_INNER) || (p_ifinfo->flags
			& NETIF_VLAN_OUTER)) {
		netif = (p_ifinfo->out_vlan_netif) ?
		p_ifinfo->out_vlan_netif : ((p_ifinfo->in_vlan_netif)
		? p_ifinfo->in_vlan_netif : NULL);
		if (netif)
			ppa_add_vlan_entry(netif, &dp_subif, p_ifinfo,
				&vlan_info, &add_flag_fail);
		}
#endif
	}

PPA_PHYS_PORT_UPDATE_DONE:
#if defined(CONFIG_LTQ_PPA_GRX500) && CONFIG_LTQ_PPA_GRX500
	/* Is netdev under bridge
	 * Note that device must be added to bridge before getting added to PPA
	 */
	if (brif != NULL && ppa_if_is_br_if(brif, NULL)) {
		if (ppa_get_fid(ppa_get_netif_name(brif),
				&p_ifinfo->fid) != PPA_SUCCESS)
			ppa_debug(DBG_ENABLE_MASK_ERR,
				"Failed in getting fid of bridge%s\n",
				ppa_get_netif_name(brif));

		/* if fid > 0 then bridge is not br0; then we need to
		 * add PCE rules to set alternate FID
		 */
		port_info.brid = p_ifinfo->fid;
		port_info.port = p_ifinfo->phys_port;
		if ((p_ifinfo->flags & NETIF_DIRECTPATH)
		    || (p_ifinfo->flags & NETIF_DIRECTCONNECT)) {
			port_info.subif_en = 1;
			port_info.subif = p_ifinfo->subif_id;
			if (ppa_drv_add_br_port(&port_info, 0) == PPA_SUCCESS)
				p_ifinfo->fid_index = port_info.index;
		} else if (p_ifinfo->fid || p_ifinfo->inner_vid) {
			port_info.vid = p_ifinfo->inner_vid;
			if (ppa_drv_add_br_port(&port_info, 0) == PPA_SUCCESS)
				p_ifinfo->fid_index = port_info.index;
		}
	}
#endif
	if ((p_ifinfo->flags & NETIF_MAC_AVAILABLE)) {
		PPE_ROUTE_MAC_INFO mac_info = {0};
		ppa_memcpy(mac_info.mac, p_ifinfo->mac, sizeof(mac_info.mac));
		if (ppa_drv_add_mac_entry(&mac_info, 0) == PPA_SUCCESS) {
			p_ifinfo->mac_entry = mac_info.mac_ix;
			p_ifinfo->flags |= NETIF_MAC_ENTRY_CREATED;
		} else {
			ppa_debug(DBG_ENABLE_MASK_ERR,
				  "add_mac_entry failed\n");
		}
	}

	if (ppa_check_is_ifup(p_ifinfo->netif))
		p_ifinfo->enable = true;
	else
		p_ifinfo->enable = false;

	__ppa_netif_add_item(p_ifinfo);

#if defined(CONFIG_LANTIQ_MCAST_HELPER_MODULE) || defined(CONFIG_LANTIQ_MCAST_HELPER)
#ifndef CONFIG_PPA_PUMA7
	if (f_is_lan) {
		char *addl_name = NULL;
		mcast_helper_register_module(p_ifinfo->netif, THIS_MODULE,
					     addl_name,
					     (int32_t *)mcast_module_config,
					     NULL,
					     MC_F_REGISTER | MC_F_DIRECTPATH);
	}
#else
	if (f_is_lan) {
		mcast_helper_register_module(p_ifinfo->netif, THIS_MODULE, NULL,
						(int32_t *)mcast_module_config_puma,
						NULL,
						MC_F_REGISTER | MC_F_DIRECTPATH);
	}
#endif
#endif
#if defined(CONFIG_PPA_PUMA7) && defined(CONFIG_TI_HIL_PROFILE_INTRUSIVE_P7)
	if (!(p_ifinfo->flags & NETIF_PHY_ATM) &&
			!(ppa_if_is_br2684(p_ifinfo->netif, p_ifinfo->name))) {
		ppa_debug(DBG_ENABLE_MASK_DEBUG_PRINT,
				" %s:%d : adding vpid for the interface %s\n",
				__func__, __LINE__, p_ifinfo->name);
		ppa_netdev_pp_prepare_vpid(p_ifinfo, f_is_lan);
	}
#endif
PPA_ADD_NETIF_DONE:
	if (force_wanitf && p_ifinfo->f_wanitf.flag_root_itf) {
		/* since it is physical root interface and the
		 * force_wanitf flag is set, then try to set wantif
		 * value accordingly
		 */
		PPE_WANITF_CFG wanitf_cfg = {0};
		p_ifinfo->f_wanitf.flag_force_wanitf = force_wanitf;
		ppa_debug(DBG_ENABLE_MASK_DEBUG_PRINT,
			  "step 1: flag_force_wanitf=%d, flag_root_itf=%d,flag_already_wanitf=%d\n",
			  p_ifinfo->f_wanitf.flag_force_wanitf,
			  p_ifinfo->f_wanitf.flag_root_itf,
			  p_ifinfo->f_wanitf.flag_already_wanitf);
		wanitf_cfg.lan_flag = f_is_lan ? 1 : 0;
		wanitf_cfg.physical_port = p_ifinfo->phys_port;
		if (ppa_set_wan_itf(&wanitf_cfg, 0) == PPA_SUCCESS &&
		    (!p_ifinfo->f_wanitf.flag_already_wanitf)) {
			/* only if */
			p_ifinfo->f_wanitf.flag_already_wanitf = 1;
			p_ifinfo->f_wanitf.old_lan_flag = wanitf_cfg.old_lan_flag;
			ppa_debug(DBG_ENABLE_MASK_DEBUG_PRINT,
				  "flag_already_wanitf set to 1 with old_lan_flag=%d\n",
				  wanitf_cfg.old_lan_flag);
		} else {
			ppa_debug(DBG_ENABLE_MASK_DEBUG_PRINT,
				  "ppa_set_wan_itf fail\n");
		}
	}

	/* unset all LAN/WAN flag */
	p_ifinfo->flags &= ~(NETIF_LAN_IF | NETIF_WAN_IF);
	/* reset LAN/WAN flag */
	p_ifinfo->flags |= f_is_lan ? NETIF_LAN_IF : NETIF_WAN_IF;

#if defined(CONFIG_LTQ_PPA_GRX500) && CONFIG_LTQ_PPA_GRX500
	if ( (p_ifinfo->flags & NETIF_WAN_IF) && (p_ifinfo->phys_port != ETH_WAN_PORT_ID)  )
	{
	 	ppa_drv_tmu_set_checksum_queue_map(p_ifinfo->phys_port);
	}
#endif

	if (pp_ifinfo)
		*pp_ifinfo = p_ifinfo;
	else
		ppa_netif_free_item(p_ifinfo);

	if (add_flag_fail)
		return PPA_FAILURE;
	return PPA_SUCCESS;
}

void ppa_netif_remove(PPA_IFNAME *ifname, int f_is_lan)
{
	struct netif_info *p_ifinfo;
#if defined(CONFIG_LTQ_PPA_GRX500) && CONFIG_LTQ_PPA_GRX500
	struct module *oner = NULL;
	dp_subif_t dp_subif = {0};
	PPA_CLASS_RULE class_rule;
	PPA_BR_PORT_INFO port_info = {0};
#endif
	if (ppa_get_netif_info(ifname, &p_ifinfo) == PPA_SUCCESS) {
		p_ifinfo->flags &= f_is_lan ? ~NETIF_LAN_IF : ~NETIF_WAN_IF;
		if (p_ifinfo->flags & (NETIF_LAN_IF | NETIF_WAN_IF)) {
			ppa_netif_free_item(p_ifinfo);
			return;
		}
#if defined(CONFIG_LTQ_PPA_GRX500) && CONFIG_LTQ_PPA_GRX500
		if (p_ifinfo->fid || p_ifinfo->inner_vid ||
		    (p_ifinfo->flags & NETIF_DIRECTPATH) ||
		    (p_ifinfo->flags & NETIF_DIRECTCONNECT)) {
			port_info.brid = p_ifinfo->fid;
			port_info.port = p_ifinfo->phys_port;
			port_info.index =  p_ifinfo->fid_index;
			ppa_drv_del_br_port(&port_info, 0);
		}

		if (p_ifinfo->flags & NETIF_BRIDGE) {
			ppa_memset(&class_rule, 0, sizeof(PPA_CLASS_RULE));

			class_rule.in_dev = GSWR_INGRESS;
			class_rule.category = CAT_MGMT;
			class_rule.uidx = p_ifinfo->fid_index;

			ppa_del_class_rule(&class_rule);
		}

		if ((p_ifinfo->flags & NETIF_VLAN_INNER) ||
		    (p_ifinfo->flags & NETIF_VLAN_OUTER)) {
			if (strlen(p_ifinfo->manual_lower_ifname) == 0) {
				/* Not the mac vlan interfaces */
				oner = dp_get_module_owner(p_ifinfo->phys_port);

				dp_subif.port_id = p_ifinfo->phys_port;
				dp_subif.subif = (p_ifinfo->subif_id & 0x0F00);

				if (dp_register_subif(oner, p_ifinfo->netif,
						      p_ifinfo->name, &dp_subif,
						      DP_F_DEREGISTER
						     ) != PPA_SUCCESS)
					ppa_debug(DBG_ENABLE_MASK_DEBUG_PRINT,
						  "dp_register_subif deregister failed\n");
				else
					ppa_debug(DBG_ENABLE_MASK_DEBUG_PRINT,
						  "%s unregistered!!\n",
						  p_ifinfo->name);
			}
		}
#endif
#if defined(CONFIG_PPA_PUMA7) && defined(CONFIG_TI_HIL_PROFILE_INTRUSIVE_P7)
		if (!(p_ifinfo->flags & NETIF_PHY_ATM) &&
				!(ppa_if_is_br2684(p_ifinfo->netif, p_ifinfo->name))) {
			ppa_debug(DBG_ENABLE_MASK_DEBUG_PRINT,
					" %s:%d : removing vpid for the interface %s\n",
					__func__, __LINE__, p_ifinfo->name);
			ppa_netdev_pp_remove_vpid(p_ifinfo);
		}
#endif
		ppa_netif_remove_item(ifname, NULL);
		if ((p_ifinfo->flags & NETIF_MAC_ENTRY_CREATED)) {
			PPE_ROUTE_MAC_INFO mac_info = {0};
			mac_info.mac_ix = p_ifinfo->mac_entry;
			ppa_drv_del_mac_entry(&mac_info, 0);
			p_ifinfo->mac_entry = ~0;
			p_ifinfo->flags &= ~NETIF_MAC_ENTRY_CREATED;
		}
#if defined(CONFIG_LANTIQ_MCAST_HELPER_MODULE) || defined(CONFIG_LANTIQ_MCAST_HELPER)
#ifndef CONFIG_PPA_PUMA7
		if (f_is_lan) {
			char *addl_name = NULL;
			mcast_helper_register_module(p_ifinfo->netif,
						     THIS_MODULE,
						     addl_name,
						     (int32_t *)mcast_module_config,
						     NULL,
						     MC_F_DEREGISTER | MC_F_DIRECTPATH);
		}
#else
	if (f_is_lan) {
		mcast_helper_register_module(p_ifinfo->netif, THIS_MODULE, NULL,
						(int32_t *)mcast_module_config_puma,
						NULL,
						MC_F_DEREGISTER | MC_F_DIRECTPATH);
	}
#endif
#endif
		ppa_netif_put(p_ifinfo);
	}
}

/* Returns netif when it is available in lookup table
 * Should be used in the configuration path to get netif_info.
 */
int32_t ppa_get_netif_info(const PPA_IFNAME *ifname,
			   struct netif_info **pp_info)
{
	int32_t ret = PPA_ENOTAVAIL;
	struct netif_info *p;

	if (ifname == NULL) {
		ppa_debug(DBG_ENABLE_MASK_ERR, "ppa_get_netif_info is called with (NULL)\n");
		return PPA_EINVAL;
	}
	ppa_netif_lock_list();
	for (p = g_netif; p; p = p->next) {
		if (strcmp(p->name, ifname) == 0) {
			ret = PPA_SUCCESS;
			if (pp_info) {
				ppa_atomic_inc(&p->count);
				*pp_info = p;
			}
			break;
		}
	}
	ppa_netif_unlock_list();

	return ret;
}

int32_t __ppa_netif_lookup(PPA_IFNAME *ifname, struct netif_info **pp_info)
{
	int32_t ret = PPA_ENOTAVAIL;
	struct netif_info *p;

	for (p = g_netif; p; p = p->next) {
		if (strcmp(p->name, ifname) == 0 && p->enable == true) {
			ret = PPA_SUCCESS;
			if (pp_info) {
				ppa_atomic_inc(&p->count);
				*pp_info = p;
			}
			break;
		}
	}
	return ret;
}

/* Returns netif_info only when it is up and available in lookup table.
 * Should be used in the learning path to get netif_info.
 */
int32_t ppa_netif_lookup(PPA_IFNAME *ifname, struct netif_info **pp_info)
{
	int32_t ret;

	if (ifname == NULL) {
		ppa_debug(DBG_ENABLE_MASK_ERR, "ppa_netif_lookup is called with (NULL)\n");
		return PPA_EINVAL;
	}
	ppa_netif_lock_list();
	ret = __ppa_netif_lookup(ifname, pp_info);
	ppa_netif_unlock_list();

	return ret;
}

void ppa_netif_put(struct netif_info *p_info)
{
	if (p_info)
		ppa_netif_free_item(p_info);
}

/* This is called only from netif_update to check tunnel or any other interface
 * on top of tunnel.
 */
uint32_t ppa_is_tunnel_if(PPA_NETIF *netif)
{

	if ((netif->type == ARPHRD_SIT) ||
	    (netif->type == ARPHRD_TUNNEL6) ||
	    (ppa_is_gre_netif(netif)) ||
	    ppa_if_is_vlan_if(netif, NULL))
		return 1;
	else
		return 0;
}

int32_t ppa_netif_update(PPA_NETIF *netif, PPA_IFNAME *ifname)
{
	struct netif_info *p_info;
	int f_need_update = 0;
	uint32_t flags;
	uint32_t force_wantif;
	PPA_IFNAME manual_lower_ifname[PPA_IF_NAME_SIZE];
#if defined(L2TP_CONFIG) && L2TP_CONFIG
	PPA_IFNAME phy_ifname[PPA_IF_NAME_SIZE];
	PPA_NETIF *new_netif;
#endif
	PPA_IF_STATS hw_accel_stats_tmp;
	PPA_IF_STATS sw_accel_stats_tmp;

	if (netif)
		ifname = ppa_get_netif_name(netif);
	else
		netif = ppa_get_netif(ifname);

	if (!netif || !ifname) {
		ppa_debug(DBG_ENABLE_MASK_DEBUG_PRINT,
			  "fail: cannot find device\n");
		return PPA_EINVAL;
	}

	if (ppa_get_netif_info(ifname, &p_info) != PPA_SUCCESS) {
		ppa_debug(DBG_ENABLE_MASK_DEBUG_PRINT,
			  "fail: device: %s not accelerated\n", ifname);
		return PPA_ENOTAVAIL;
	}

	flags = p_info->flags;

	if (!ppa_is_netif_equal(netif, p_info->netif)) {
		f_need_update = 1;
	} else if ((flags & NETIF_PHYS_PORT_GOT) == 0 &&
		   (flags & (NETIF_BRIDGE | NETIF_PHY_IF_GOT)) !=
		   (NETIF_BRIDGE | NETIF_PHY_IF_GOT)) {
		f_need_update = 1;
#if defined(L2TP_CONFIG) && L2TP_CONFIG
	} else if ((flags & NETIF_PPPOL2TP)) {
		if (!ppa_check_is_pppol2tp_netif(netif)) {
			f_need_update = 1;
		} else {
			p_info->pppol2tp_session_id =
				ppa_pppol2tp_get_l2tp_session_id(netif);
			p_info->pppol2tp_tunnel_id =
				ppa_pppol2tp_get_l2tp_tunnel_id(netif);

			if (ppa_pppol2tp_get_base_netif(netif, phy_ifname
						       ) == PPA_SUCCESS) {
				new_netif = ppa_get_netif(phy_ifname);
				if (ppa_check_is_ppp_netif(new_netif)) {
					if (!ppa_check_is_pppoe_netif(new_netif))
						f_need_update = 1;
					else
						p_info->pppoe_session_id = ppa_pppoe_get_pppoe_session_id(new_netif);
				}
			}
		}
#endif
	} else if ((flags & NETIF_PPPOE)) {
		if (!ppa_check_is_pppoe_netif(netif)) {
			if (ppa_is_tunnel_if(netif) == 0)
				f_need_update = 1;
		} else {
			p_info->pppoe_session_id =
				ppa_pppoe_get_pppoe_session_id(netif);
		}
	} else if ((flags & NETIF_PPPOATM)) {
		if (!ppa_if_is_pppoa(netif, NULL)) {
			if (ppa_is_tunnel_if(netif) == 0)
				f_need_update = 1;
		}
	}

	if (!f_need_update &&
	    (flags & (NETIF_BRIDGE | NETIF_PHY_ETH | NETIF_EOA)) != 0) {
#if defined(CONFIG_L2NAT_MODULE) || defined(CONFIG_L2NAT)
		/* Check whether the netif is an l2nat interface or not */
		if (ppa_check_if_netif_l2nat_fn) {
			if (ppa_check_if_netif_l2nat_fn(netif, NULL, 0))
				p_info->flags |= NETIF_L2NAT;
			else
				p_info->flags &= ~NETIF_L2NAT;
		}
#endif
	}

	/* save the force_wanitf flag */
	force_wantif = p_info->f_wanitf.flag_force_wanitf;
	if (ppa_strlen(p_info->manual_lower_ifname))
		ppa_strncpy(manual_lower_ifname, p_info->manual_lower_ifname,
			    sizeof(manual_lower_ifname));
	else
		manual_lower_ifname[0] = 0;

	if (f_need_update) {
		hw_accel_stats_tmp.rx_bytes = p_info->hw_accel_stats.rx_bytes;
		hw_accel_stats_tmp.tx_bytes = p_info->hw_accel_stats.tx_bytes;
		sw_accel_stats_tmp.rx_bytes = p_info->sw_accel_stats.rx_bytes;
		sw_accel_stats_tmp.tx_bytes = p_info->sw_accel_stats.tx_bytes;
	}

	ppa_netif_put(p_info);

	if (f_need_update) {
		if ((flags & NETIF_LAN_IF))
			ppa_netif_remove(ifname, 1);
		if ((flags & NETIF_WAN_IF))
			ppa_netif_remove(ifname, 0);

		if ((flags & NETIF_LAN_IF) &&
		    ppa_netif_add(ifname, 1, NULL, manual_lower_ifname,
				  force_wantif) != PPA_SUCCESS) {
			ppa_debug(DBG_ENABLE_MASK_DEBUG_PRINT,
				  "update lan interface %s fail\n", ifname);
			return PPA_FAILURE;
		}

		if ((flags & NETIF_WAN_IF) &&
		    ppa_netif_add(ifname, 0, NULL, manual_lower_ifname,
				  force_wantif) != PPA_SUCCESS) {
			ppa_debug(DBG_ENABLE_MASK_DEBUG_PRINT,
				  "update wan interface %s fail\n", ifname);
			return PPA_FAILURE;
		}

		if (ppa_get_netif_info(ifname, &p_info) != PPA_SUCCESS) {
			ppa_debug(DBG_ENABLE_MASK_DEBUG_PRINT,
				  "fail: device: %s not accelerated\n", ifname);
			return PPA_ENOTAVAIL;
		}

		p_info->hw_accel_stats.rx_bytes = hw_accel_stats_tmp.rx_bytes;
		p_info->hw_accel_stats.tx_bytes = hw_accel_stats_tmp.tx_bytes;
		p_info->sw_accel_stats.rx_bytes = sw_accel_stats_tmp.rx_bytes;
		p_info->sw_accel_stats.tx_bytes = sw_accel_stats_tmp.tx_bytes;

		ppa_netif_put(p_info);
	}
	return PPA_SUCCESS;
}
EXPORT_SYMBOL(ppa_netif_update);

int32_t ppa_netif_start_iteration(uint32_t *ppos, struct netif_info **ifinfo)
{
	uint32_t l;
	struct netif_info *p;

	ppa_netif_lock_list();

	if (!ppa_is_init()) {
		*ifinfo = NULL;
		return PPA_FAILURE;
	}

	p = g_netif;
	l = *ppos;
	while (p && l) {
		p = p->next;
		l--;
	}

	if (l == 0 && p) {
		++*ppos;
		*ifinfo = p;
		return PPA_SUCCESS;
	} else {
		*ifinfo = NULL;
		return PPA_FAILURE;
	}
}
EXPORT_SYMBOL(ppa_netif_start_iteration);

int32_t ppa_netif_iterate_next(uint32_t *ppos, struct netif_info **ifinfo)
{
	if (*ifinfo) {
		++*ppos;
		*ifinfo = (*ifinfo)->next;
		return *ifinfo ? PPA_SUCCESS : PPA_FAILURE;
	} else {
		return PPA_FAILURE;
	}
}
EXPORT_SYMBOL(ppa_netif_iterate_next);

void ppa_netif_stop_iteration(void)
{
	ppa_netif_unlock_list();
}
EXPORT_SYMBOL(ppa_netif_stop_iteration);

/* ####################################
 *           Init/Cleanup API
 * ####################################
 */
int32_t ppa_api_netif_manager_init(void)
{
	struct phys_port_info *p_phys_port_info;
#if defined(CONFIG_LTQ_PPA_API_DIRECTPATH)
	struct ppe_directpath_data *info;
#endif
	uint32_t pos = 0;
	int i, ret = PPA_SUCCESS;
	PPE_IFINFO if_info;
	PPE_COUNT_CFG count = {0};

	ppa_netif_free_list();
	ppa_phys_port_free_list();

	ppa_drv_get_number_of_phys_port(&count, 0);

	for (i = 0; i <= count.num; i++) {
		ppa_memset(&if_info, 0, sizeof(PPE_IFINFO));
		if_info.port = i;
		ppa_drv_get_phys_port_info(&if_info, 0);
		switch ((if_info.if_flags & (PPA_PHYS_PORT_FLAGS_TYPE_MASK |
					     PPA_PHYS_PORT_FLAGS_MODE_MASK |
					     PPA_PHYS_PORT_FLAGS_VALID))) {
		case PPA_PHYS_PORT_FLAGS_MODE_CPU_VALID:
			if (g_phys_port_cpu == ~0)
				g_phys_port_cpu = i;
			break;
		case PPA_PHYS_PORT_FLAGS_MODE_ATM_WAN_VALID:
			if (g_phys_port_atm_wan == ~0)
				g_phys_port_atm_wan = i;
			if (if_info.if_flags & PPA_PHYS_PORT_FLAGS_OUTER_VLAN)
				g_phys_port_atm_wan_vlan = 2;
			else
				g_phys_port_atm_wan_vlan = 1;
			break;
		case PPA_PHYS_PORT_FLAGS_MODE_ETH_LAN_VALID:
		case PPA_PHYS_PORT_FLAGS_MODE_ETH_WAN_VALID:
		case PPA_PHYS_PORT_FLAGS_MODE_ETH_MIX_VALID:
		case PPA_PHYS_PORT_FLAGS_MODE_EXT_LAN_VALID:
			if (if_info.ifname[0]) {
				p_phys_port_info = ppa_phys_port_alloc_item();
				if (!p_phys_port_info)
					goto PPA_API_NETIF_MANAGER_INIT_FAIL;
				strcpy(p_phys_port_info->ifname,
				       if_info.ifname);
				switch ((if_info.if_flags &
					 PPA_PHYS_PORT_FLAGS_MODE_MASK)) {
				case PPA_PHYS_PORT_FLAGS_MODE_LAN:
					p_phys_port_info->mode = 1;
					break;
				case PPA_PHYS_PORT_FLAGS_MODE_WAN:
					p_phys_port_info->mode = 2;
					break;
				case PPA_PHYS_PORT_FLAGS_MODE_MIX:
					p_phys_port_info->mode = 3;
				}
				if ((if_info.if_flags &
				     PPA_PHYS_PORT_FLAGS_TYPE_MASK) ==
				    PPA_PHYS_PORT_FLAGS_TYPE_ETH)
					p_phys_port_info->type = 2;
				else
					p_phys_port_info->type = 3;
				if (if_info.if_flags &
				    PPA_PHYS_PORT_FLAGS_OUTER_VLAN)
					p_phys_port_info->vlan = 2;
				else
					p_phys_port_info->vlan = 1;
				p_phys_port_info->port = i;
				ppa_lock_get(&g_phys_port_lock);
				p_phys_port_info->next = g_phys_port_info;
				g_phys_port_info = p_phys_port_info;
				ppa_lock_release(&g_phys_port_lock);
			}
		}
	}

	pos = 0;
#if defined(CONFIG_LTQ_PPA_API_DIRECTPATH)
	if (ppa_is_init()) {
		ret = ppa_directpath_data_start_iteration(&pos, &info);
		if (ret == PPA_SUCCESS) {
			do {
				if ((info->flags &
				     PPE_DIRECTPATH_DATA_ENTRY_VALID) &&
				    info->netif)
					ppa_phys_port_add(info->netif->name,
							  info->ifid);
			} while (ppa_directpath_data_iterate_next(&pos, &info) == PPA_SUCCESS);
		}
		ppa_directpath_data_stop_iteration();
	}
#endif
	PPA_LIST_HEAD_INIT(&manual_del_iface_list);
	ppa_register_netdevice_notifier(&ppa_netdevice_notifier);
	return ret;

PPA_API_NETIF_MANAGER_INIT_FAIL:
	ppa_phys_port_free_list();
	return PPA_ENOMEM;
}

void ppa_api_netif_manager_exit(void)
{
	ppa_netif_free_list();
	ppa_unregister_netdevice_notifier(&ppa_netdevice_notifier);
	ppa_phys_port_free_list();
}

int32_t ppa_api_netif_manager_create(void)
{
	if (ppa_lock_init(&g_phys_port_lock)) {
		ppa_debug(DBG_ENABLE_MASK_ERR,
			  "Failed in creating lock for physical network interface list.\n");
		return PPA_EIO;
	}

	if (ppa_lock_init(&g_netif_lock)) {
		ppa_lock_destroy(&g_phys_port_lock);
		ppa_debug(DBG_ENABLE_MASK_ERR,
			  "Failed in creating lock for network interface list.\n");
		return PPA_EIO;
	}
	return PPA_SUCCESS;
}

void ppa_api_netif_manager_destroy(void)
{
	ppa_lock_destroy(&g_netif_lock);
	ppa_lock_destroy(&g_phys_port_lock);
}
