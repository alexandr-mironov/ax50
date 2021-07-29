/******************************************************************************
 **
 ** FILE NAME    : ppa_hook.c
 ** PROJECT      : PPA
 ** MODULES      : PPA Protocol Stack Hooks
 **
 ** DATE         : 3 NOV 2008
 ** AUTHOR       : Xu Liang
 ** DESCRIPTION  : PPA Protocol Stack Hook Pointers
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
 *******************************************************************************/



/*
 * ####################################
 *              Version No.
 * ####################################
 */
#define VER_FAMILY      0x60        //  bit 0: res
//      1: Danube
//      2: Twinpass
//      3: Amazon-SE
//      4: res
//      5: AR9
//      6: GR9
#define VER_DRTYPE      0x08        //  bit 0: Normal Data Path driver
//      1: Indirect-Fast Path driver
//      2: HAL driver
//      3: Hook driver
//      4: Stack/System Adaption Layer driver
//      5: PPA API driver
#define VER_INTERFACE   0x00        //  bit 0: MII 0
//      1: MII 1
//      2: ATM WAN
//      3: PTM WAN
#define VER_ACCMODE     0x03        //  bit 0: Routing
//      1: Bridging
#define VER_MAJOR       0
#define VER_MID         0
#define VER_MINOR       2



/*
 * ####################################
 *              Head File
 * ####################################
 */

/*
 *  Common Head File
 */
//#include <linux/autoconf.h>
#include <linux/version.h>
#if LINUX_VERSION_CODE < KERNEL_VERSION(2, 6, 33)
#include <linux/autoconf.h>
#else
#include <generated/autoconf.h>
#endif

#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/version.h>
#include <linux/types.h>
#include <linux/init.h>
#include <linux/slab.h>
#include <linux/netdevice.h>
#include <linux/atmdev.h>
#include <net/sock.h>

/*
 *  Chip Specific Head File
 */
#include <net/ppa_api.h>
#include <net/ppa_api_directpath.h>


/*
 * ####################################
 *           Export  PPA hook functions
 * ####################################
 */

/**********************************************************************************************
 * PPA unicast routing hook function:ppa_hook_session_add_fn
 * It it used to check unicast routing session and if necessary, add it to PPE FW to acceleration this session.
 * This hook will be invoked when a packet is handled before NAT and after NAT
 * input parameter PPA_BUF *: IP packet
 * input parameter PPA_SESSION *: routing session in network stack
 * input parameter uint32_t: this flag mainly to indicate the hook is invoked before NAT or after NAT
 * return: PPA_SESSION_ADDED: this session is added into PPE FW, ie, it is accelerated by PPE
 *            PPA_SESSION_EXISTS: already added into PPE FW
 *            PPA_SESSION_NOT_ADDED: not added int PPE FW for some reasons.
 *            ...
 **********************************************************************************************/
int32_t (*ppa_hook_session_add_fn)(PPA_BUF *, PPA_SESSION *, uint32_t) = NULL;
int32_t (*ppa_hook_session_bradd_fn)(PPA_BUF *, PPA_SESSION *, uint32_t) = NULL;

void (*ppa_hook_pitem_refcnt_inc_fn)(PPA_BUF *) = NULL;
void (*ppa_hook_pitem_refcnt_dec_fn)(PPA_BUF *) = NULL;
#if defined(CONFIG_LTQ_PPA_MPE_IP97)
int32_t (*ppa_hook_session_ipsec_add_fn)(PPA_XFRM_STATE *, sa_direction ) = NULL;
int32_t (*ppa_hook_session_ipsec_del_fn)(PPA_XFRM_STATE *) = NULL;
#endif

/**********************************************************************************************
 * PPA unicast routing hook function:ppa_hook_session_add_fn
 * It it used to delete a  unicast routing session when it is timeout, reset or purposely.
 * input parameter PPA_SESSION *: the session pointer
 * input parameter uint32_t: for future purpose
 * return: PPA_SUCCESS: this session is deleted sucessfully from PPE FW
 *            ...
 **********************************************************************************************/
int32_t (*ppa_hook_session_del_fn)(PPA_SESSION *, uint32_t) = NULL;

/**********************************************************************************************
 * PPA session priority hook function:ppa_hook_session_prio_fn
 * It is used to get session priority  of a ppa session.
 * input parameter PPA_SESSION *: the session pointer
 * input parameter uint32_t: for future purpose
 * return: session priority
 *            ...
 **********************************************************************************************/
int32_t (*ppa_hook_session_prio_fn)(PPA_SESSION *, uint32_t) = NULL;

/**********************************************************************************************
 * PPA unicast routing hook function:ppa_hook_session_accel_fn
 * It it used to set/reset flag to accelerate the session
 * input parameter PPA_SESSION *: the session pointer
 * input parameter uint8_t: flag to set/reset acceleration
 * return: PPA_SUCCESS: session is configured with the input flag
 **********************************************************************************************/

int32_t (*ppa_hook_session_accel_fn)(PPA_SESSION *, uint8_t) = NULL;
/**********************************************************************************************
 * PPA unicast routing hook function:ppa_hook_get_ct_stats_fn
 * It it used to read the statistics counters of specified session
 * input parameter PPA_SESSION *: the session pointer
 * input parameter PPA_CT_COUNTER *: the session stats counter structure pointer
 * return: PPA_SUCCESS: the session statistics read sucessfully
 **********************************************************************************************/

int32_t (*ppa_hook_get_ct_stats_fn)(PPA_SESSION *, PPA_CT_COUNTER*) = NULL;
/**********************************************************************************************
 * PPA unicast  hook function:ppa_hook_inactivity_status_fn
 * It it used to check whether a unicast session is timeout or not.
 * Normally it is called by network stack which want to delete a session without any traffic for sometime.
 * input parameter PPA_U_SESSION *: the unicast session pointer
 * return: PPA_HIT: the session still hit and should keep it
 *            PPA_TIMEOUT: timeout already
 **********************************************************************************************/
int32_t (*ppa_hook_inactivity_status_fn)(PPA_U_SESSION *) = NULL;


/**********************************************************************************************
 * PPA unicast  hook function:ppa_hook_set_inactivity_fn
 * It it used to set one unicast session timeout value
 * Normally it is called to prolong one sessions duration.
 * input parameter PPA_U_SESSION *: the unicast session pointer
 * input parameter int32_t: the timeout value
 * return: PPA_SUCCESS: update timeout sucessfully
 *            PPA_FAILURE: fail to update timeout value

 **********************************************************************************************/
int32_t (*ppa_hook_set_inactivity_fn)(PPA_U_SESSION*, int32_t) = NULL;

/**********************************************************************************************
 * PPA briding learning hook function:ppa_hook_bridge_entry_add_fn
 * It it used to add a bridging mac addresss into PPE FW.
 * This hook will be invoked when bridging learned a mac address or purposely to filter one mac address.
 * input parameter uint8_t*: the mac address
 * input parameter PPA_NETIF *: the interface which learned the mac address
 * input parameter PPA_NETIF *: bridge interface
 * input parameter uint32_t: PPA_F_STATIC_ENTRY means static mode,
 *                                       PPA_F_DROP_PACKET means drop the packet, otherwise accelerate the packet.
 * return: PPA_SESSION_ADDED: this session is added into PPE FW, ie, it is accelerated by PPE
 *            PPA_SESSION_EXISTS: already added into PPE FW
 *            PPA_SESSION_NOT_ADDED: not added int PPE FW for some reasons.
 **********************************************************************************************/
int32_t (*ppa_hook_bridge_entry_add_fn)(uint8_t *, PPA_NETIF *, PPA_NETIF *, uint32_t) = NULL;

/**********************************************************************************************
 * PPA briding learning hook function:ppa_hook_bridge_entry_delete_fn
 * It it used to delete a bridging mac addresss from PPE FW.
 * Normally this hook will be invoked when mac address timeout.
 * input parameter uint8_t*: the mac address
 * input parameter PPA_NETIF *: bridge interface
 * input parameter uint32_t: flag for future purpose
 * return: PPA_SESSION_ADDED: this session is added into PPE FW, ie, it is accelerated by PPE
 * return: PPA_SUCCESS: set timeout value sucessfully.
 *            PPA_FAILURE: failed to update
 **********************************************************************************************/
int32_t (*ppa_hook_bridge_entry_delete_fn)(uint8_t *, PPA_NETIF *,  uint32_t) = NULL;


/**********************************************************************************************
 * PPA bridge  hook function:ppa_hook_bridge_entry_hit_time_fn
 * It it used to get last hit time
 * input parameter uint8_t *: the mac address
 * input parameter PPA_NETIF *: bridge interface
 * input parameter uint32_t *: the last hit time
 * return: PPA_HIT: sucessfully get the last hit time
 *            PPA_SESSION_NOT_ADDED: the mac address not in PPE FW yet
 **********************************************************************************************/
int32_t (*ppa_hook_bridge_entry_hit_time_fn)(uint8_t *, PPA_NETIF *, uint32_t *) = NULL;

#if defined(CONFIG_LTQ_PPA_IF_MIB) && CONFIG_LTQ_PPA_IF_MIB
/**********************************************************************************************
 * PPA mibs  hook function:ppa_hook_get_accel_stats_fn
 * It it used to port acclerated mib status, like accelerated rx/tx packet number and so on
 * input parameter PPA_IFNAME *: specify which port's acceleration mibs want to get
 * output parameter PPA_ACCEL_STATS *
 * input parameter uint32_t: for future purpose
 * return: PPA_SUCCESS: get   sucessfully
 *            PPA_FAILURE: fail to get
 **********************************************************************************************/
int32_t (*ppa_hook_get_netif_accel_stats_fn)(PPA_IFNAME *, PPA_NETIF_ACCEL_STATS *, uint32_t) = NULL;
#endif

#if defined(CONFIG_PPA_API_DIRECTCONNECT) && CONFIG_PPA_API_DIRECTCONNECT
/**********************************************************************************************
 * PPA interface hook function:ppa_check_if_netif_fastpath_fn
 * It it used to check if network interface like, WAVE500, ACA is a fastpath interface
 * input parameter PPA_NETIF *: pointer to stack network interface structure
 * input parameter char *: interface name
 * input parameter uint32_t: for future purpose
 * return: 1: if ACA or WLAN fastpath interface
 *            0: otherwise
 **********************************************************************************************/
int32_t (*ppa_check_if_netif_fastpath_fn)(PPA_NETIF *, char *, uint32_t) = NULL;

/**********************************************************************************************
 * PPA interface hook function:ppa_hook_disconn_if_fn
 * It is used to delete one WAVE500 STA from PPA
 * input parameter PPA_NETIF *: the linux interface name, like wlan0
 * input parameter PPA_DP_SUBIF *: WAVE500 port id and subif id including station id
 * input parameter uint8_t *: WAVE500 STA mac address
 * input parameter uint32_t: for future purpose
 * return: PPA_SUCCESS: delete sucessfully
 *            PPA_FAILURE: fail to delete
 **********************************************************************************************/
int32_t (*ppa_hook_disconn_if_fn)(PPA_NETIF *, PPA_DP_SUBIF *, uint8_t *, uint32_t) = NULL;

#if defined(WMM_QOS_CONFIG) && WMM_QOS_CONFIG
int32_t (*ppa_register_qos_class2prio_hook_fn)( int32_t ,PPA_NETIF *, PPA_QOS_CLASS2PRIO_CB , uint32_t) = NULL;
#endif

#endif

/**********************************************************************************************
 * PPA Extra ethernet interface  hook function :ppa_hook_addppa_hook_directpath_register_dev_fn_if_fn
 * it is used to register/de-register a device  for direct path support
 * output parameter uint32_t *: return the virtual port id
 * input parameter PPA_NETIF *: the linux interface name, like wlan0
 * input parameter PPA_DIRECTPATH_CB *: mainly provide callback function, like start_tx_fn, stop_tx_fn, rx_fn
 * input parameter uint32_t: PPA_F_DIRECTPATH_REGISTER for register, otherwise for de-register
 * return: PPA_SUCCESS: register sucessfully
 *            others: fail to register
 **********************************************************************************************/
int32_t (*ppa_hook_directpath_register_dev_fn)(uint32_t *, PPA_NETIF *, PPA_DIRECTPATH_CB *, uint32_t) = NULL;

/**********************************************************************************************
 * PPA Extended ethernet interface  hook function :ppa_hook_addppa_hook_directpath_register_dev_fn_if_fn
 * it is used to register/de-register a device  for direct path support
 * output parameter PPA_SUBIF *: return the virtual port id and sub interface id
 * input parameter PPA_NETIF *: the linux interface name, like wlan0
 * input parameter PPA_DIRECTPATH_CB *: mainly provide callback function, like start_tx_fn, stop_tx_fn, rx_fn
 * input parameter uint32_t: PPA_F_DIRECTPATH_REGISTER for register, otherwise for de-register
 * return: PPA_SUCCESS: register sucessfully
 *            others: fail to register
 **********************************************************************************************/

int32_t (*ppa_hook_directpath_ex_register_dev_fn)(PPA_SUBIF *, PPA_NETIF *, PPA_DIRECTPATH_CB *, uint32_t) = NULL;

/**********************************************************************************************
 * PPA Extra ethernet interface  hook function :ppa_hook_directlink_register_dev_fn, a wrap function of directpath registration for directlink
 * it is used to register/de-register a device  for directlink support
 * output parameter int32_t *: return the virtual port id
 * input parameter PPA_DTLK_T *: directlink information
 * input parameter PPA_DIRECTPATH_CB *: mainly provide callback function, like start_tx_fn, stop_tx_fn, rx_fn
 * input parameter uint32_t: PPA_F_DIRECTPATH_REGISTER for register, otherwise for de-register
 * return: IFX_SUCCESS: register sucessfully
 *            others: fail to register
 **********************************************************************************************/
int32_t (*ppa_hook_directlink_register_dev_fn)(int32_t *, PPA_DTLK_T *, PPA_DIRECTPATH_CB *,uint32_t) = NULL;

/**********************************************************************************************
 * PPA Extra interface  hook function :ppa_hook_directpath_send_fn
 * it is used to send a packet to PPE FW when extra ethernet interface receive a packet
 * input parameter uint32_t:  the virtual port id
 * input parameter PPA_SKBUF *: the packet to send
 * input parameter int32_t *: the packet length
 * input parameter uint32_t: for future purpose
 * return: PPA_SUCCESS: send sucessfully
 *            others: fail to send
 **********************************************************************************************/
int32_t (*ppa_hook_directpath_send_fn)(uint32_t, PPA_SKBUF *, int32_t, uint32_t) = NULL;

/**********************************************************************************************
 * PPA Extra interface  hook function :ppa_hook_directpath_ex_send_fn
 * it is used to send a packet to PPE FW when extra ethernet interface receive a packet
 * input parameter PPA_SUBIF:  the virtual port id and sub interface id
 * input parameter int32_t *: the packet length
 * input parameter uint32_t: for future purpose
 * return: PPA_SUCCESS: send sucessfully
 *            others: fail to send
 **********************************************************************************************/
int32_t (*ppa_hook_directpath_ex_send_fn)(PPA_SUBIF *, PPA_SKBUF *, int32_t, uint32_t) = NULL;

/*Note, ppa_hook_directpath_enqueue_to_imq_fn will be set by imq module during initialization */
int32_t (*ppa_hook_directpath_enqueue_to_imq_fn)(PPA_SKBUF *skb, uint32_t portID) = NULL;
/*it will be called by imq module */
int32_t (*ppa_hook_directpath_reinject_from_imq_fn)(int32_t rx_if_id, PPA_SKBUF *buf, int32_t len, uint32_t flags) = NULL;
int32_t ppa_directpath_imq_en_flag=0;


/**********************************************************************************************
 * PPA Extra interface  hook function :ppa_hook_directpath_rx_stop_fn
 * it is used to stop forward packet to extra ethernet interface
 * input parameter uint32_t:  the virtual port id
 * input parameter uint32_t: for future purpose
 * return: PPA_SUCCESS: stop sucessfully
 *            others: fail to stop
 **********************************************************************************************/
int32_t (*ppa_hook_directpath_rx_stop_fn)(uint32_t, uint32_t) = NULL;

/**********************************************************************************************
 * PPA Extra interface  hook function :ppa_hook_directpath_ex_rx_stop_fn
 * it is used to stop forward packet to extra ethernet interface
 * input parameter PPA_SUBIF:  the virtual port id and sub interface id
 * input parameter uint32_t: for future purpose
 * return: PPA_SUCCESS: stop sucessfully
 *            others: fail to stop
 **********************************************************************************************/
int32_t (*ppa_hook_directpath_ex_rx_stop_fn)(PPA_SUBIF *, uint32_t) = NULL;

/**********************************************************************************************
 * PPA Extra interface  hook function :ppa_hook_directpath_rx_restart_fn
 * it is used to restart forwarding packet to extra ethernet interface
 * input parameter uint32_t:  the virtual port id
 * input parameter uint32_t: for future purpose
 * return: PPA_SUCCESS: restart forwarding sucessfully
 *            others: fail to restart forwarding
 **********************************************************************************************/
int32_t (*ppa_hook_directpath_rx_restart_fn)(uint32_t, uint32_t) = NULL;

/**********************************************************************************************
 * PPA Extra interface  hook function :ppa_hook_directpath_ex_rx_restart_fn
 * it is used to restart forwarding packet to extra ethernet interface
 * input parameter PPA_SUBIF:  the virtual port id and sub interface id
 * input parameter uint32_t: for future purpose
 * return: PPA_SUCCESS: restart forwarding sucessfully
 *            others: fail to restart forwarding
 **********************************************************************************************/
int32_t (*ppa_hook_directpath_ex_rx_restart_fn)(PPA_SUBIF *, uint32_t) = NULL;

int32_t (*ppa_hook_directpath_recycle_skb_fn)(PPA_SUBIF*, PPA_SKBUF*, uint32_t) = NULL;
PPA_SKBUF*  (*ppa_hook_directpath_alloc_skb_fn)(PPA_SUBIF*, int32_t, uint32_t) = NULL;

/**********************************************************************************************
 * PPA Extra interface  hook function :ppa_hook_get_ifid_for_netif_fn
 * it is used to get one extran ethernet interface virtual port id according to its interface pointer
 * input parameter uint32_t:  network  interface pointer
 * return: virtual port id: if sucessully, otherwise return -1, ie, PPA_FAILURE
 **********************************************************************************************/
int32_t (*ppa_hook_get_ifid_for_netif_fn)(PPA_NETIF *) = NULL;

/**********************************************************************************************
 * PPA LAN/WAN mode hook function :ppa_get_6rd_dmac_fn
 * it is used to get 6rd packet's destnation mac address
 * input parameter PPA_NETIF: the netdevice pointer
 * return: PPA_SUCCESS: get destination mac address sucessully
 *            PPA_FAILURE: fail to get destination mac address
 **********************************************************************************************/
#if LINUX_VERSION_CODE < KERNEL_VERSION(3,8,10)
int32_t (*ppa_get_6rd_dmac_fn)(PPA_NETIF *netif, uint8_t *mac,uint32_t daddr) = NULL;
#else
int32_t (*ppa_get_6rd_dmac_fn)(PPA_NETIF *netif, PPA_BUF *ppa_buf, uint8_t *mac,uint32_t daddr) = NULL;
#endif
#if LINUX_VERSION_CODE < KERNEL_VERSION(3,8,10)
int32_t (*ppa_get_ip4ip6_dmac_fn)(PPA_NETIF *netif, uint8_t *mac) = NULL;
#else
int32_t (*ppa_get_ip4ip6_dmac_fn)(PPA_NETIF *netif,PPA_BUF *ppa_buf, uint8_t *mac) = NULL;
#endif
PPA_NETIF* (*ppa_get_6rd_phyif_fn)(PPA_NETIF *netif)= NULL;
PPA_NETIF* (*ppa_get_ip4ip6_phyif_fn)(PPA_NETIF *netif)= NULL;

//#ifdef CONFIG_PPA_GRE
uint32_t (*ppa_is_ipv4_gretap_fn)(struct net_device *dev) = NULL;
uint32_t (*ppa_is_ipv6_gretap_fn)(struct net_device *dev) = NULL;
EXPORT_SYMBOL(ppa_is_ipv4_gretap_fn);
EXPORT_SYMBOL(ppa_is_ipv6_gretap_fn);
//#endif

#ifdef CONFIG_LTQ_PPA_QOS
int32_t (*ppa_hook_get_qos_qnum)( uint32_t portid, uint32_t flag) = NULL;
int32_t (*ppa_hook_get_qos_mib)( uint32_t portid, uint32_t queueid, PPA_QOS_MIB *mib, uint32_t flag) = NULL;
#ifdef CONFIG_LTQ_PPA_QOS_RATE_SHAPING
int32_t (*ppa_hook_set_ctrl_qos_rate)( uint32_t portid, uint32_t enable, uint32_t flag ) = NULL;
int32_t (*ppa_hook_get_ctrl_qos_rate)( uint32_t portid, uint32_t *enable, uint32_t flag ) = NULL;
int32_t (*ppa_hook_set_qos_rate)( uint32_t portid, uint32_t queueid, uint32_t rate, uint32_t burst, uint32_t flag) = NULL;
int32_t (*ppa_hook_get_qos_rate)( uint32_t portid, uint32_t queueid, uint32_t *rate, uint32_t *burst, uint32_t flag) = NULL;
int32_t (*ppa_hook_reset_qos_rate)( uint32_t portid, uint32_t queueid, uint32_t flag ) = NULL;
#endif  //end of  CONFIG_LTQ_PPA_QOS_RATE_SHAPING

#ifdef CONFIG_LTQ_PPA_QOS_WFQ
int32_t (*ppa_hook_set_ctrl_qos_wfq)( uint32_t portid, uint32_t enable, uint32_t flag) = NULL;
int32_t (*ppa_hook_get_ctrl_qos_wfq)( uint32_t portid, uint32_t *enable, uint32_t flag) = NULL;
int32_t (*ppa_hook_set_qos_wfq)( uint32_t portid, uint32_t queueid, uint32_t weight_level, uint32_t flag) = NULL;
int32_t (*ppa_hook_get_qos_wfq)( uint32_t portid, uint32_t queueid, uint32_t *weight_level, uint32_t flag) = NULL;
int32_t (*ppa_hook_reset_qos_wfq)( uint32_t portid, uint32_t queueid, uint32_t flag ) = NULL;
#endif  //end of  CONFIG_LTQ_PPA_QOS_WFQ

#endif  //end of CONFIG_LTQ_PPA_QOS

#if defined(CONFIG_LTQ_PPA_API_SW_FASTPATH)
/**************************************************************************************************
 * PPA based software acceleration function hook
 * gets called from netif_rx in dev.c
 * bye pass the linux sw stack and routes the packet based on the ppa session entry
 * input : sk_buff of incoming packet
 * output: PPA_SUCCESS if the packet is accelerated
 * 	    PPA_FAILURE if the packet is not accelerated
 **************************************************************************************************/
int32_t (*ppa_hook_sw_fastpath_send_fn)( struct sk_buff *skb ) = NULL;
int32_t (*ppa_hook_set_sw_fastpath_enable_fn)( uint32_t flags ) = NULL;
int32_t (*ppa_hook_get_sw_fastpath_status_fn)( uint32_t flags ) = NULL;
#endif


int32_t  (*ppa_hook_set_lan_seperate_flag_fn)( uint32_t flag) = NULL;
uint32_t (*ppa_hook_get_lan_seperate_flag_fn)( uint32_t flag) = NULL;
int32_t  (*ppa_hook_set_wan_seperate_flag_fn)( uint32_t flag) = NULL;
uint32_t (*ppa_hook_get_wan_seperate_flag_fn)( uint32_t flag) = NULL;


#if defined(CONFIG_L2NAT_MODULE) || defined(CONFIG_L2NAT)
/**********************************************************************************************
  * PPA interface hook function:ppa_check_if_netif_l2nat_fn
  * It it used to check if network interface is an l2nat interface
  * input parameter PPA_NETIF *: pointer to stack network interface structure
  * input parameter char *: interface name
  * input parameter uint32_t: for future purpose
  * return: 1: if network interafce is an l2nat interface
  *            0: otherwise
**********************************************************************************************/
int32_t (*ppa_check_if_netif_l2nat_fn)( PPA_NETIF *, char *, uint32_t ) = NULL;
#endif

#if PPA_DP_DBG_PARAM_ENABLE
/*Below varabiles are used for debugging only: force PPE driver to use kernel's boot parameter:
  if ppa_drv_datapath_dbg_param_enable is enabled, then PPE driver will take parameter from kernel's boot paramter whether
  PPE driver is static build in kernel or dynamic modules.

  Note, only if ppa_drv_dp_dbg_param_enable is enabled and PPE driver is in loadable module, then this feature may be activated.
  Otherwise, it will never be activated at all.

  For other non-linux OS, just disabled this feature, ie, not enable macro PPA_DP_DBG_PARAM_ENABLE
 */
int  ppa_drv_dp_dbg_param_enable = 0;
int  ppa_drv_dp_dbg_param_ethwan = 0;
int  ppa_drv_dp_dbg_param_wanitf = ~0;
int  ppa_drv_dp_dbg_param_ipv6_acc_en = 1;
int  ppa_drv_dp_dbg_param_wanqos_en = 8;

static int __init ppa_drv_dp_dbg_param_enable_setup(char *line)
{
	if ( strcmp(line, "1") == 0 )
		ppa_drv_dp_dbg_param_enable = 1;

	return 0;
}

static int __init ppa_drv_dp_dbg_param_wan_mode_setup(char *line)
{
	if ( strcmp(line, "1") == 0 )
		ppa_drv_dp_dbg_param_ethwan = 1;
	else if ( strcmp(line, "2") == 0 )
		ppa_drv_dp_dbg_param_ethwan = 2;

	return 0;
}

static int __init ppa_drv_dp_dbg_param_wanitf_setup(char *line)
{
	ppa_drv_dp_dbg_param_wanitf = simple_strtoul(line, NULL, 0);

	if ( ppa_drv_dp_dbg_param_wanitf > 0xFF )
		ppa_drv_dp_dbg_param_wanitf = ~0;

	return 0;
}

static int __init ppa_drv_dp_dbg_param_ipv6_acc_en_setup(char *line)
{
	if ( strcmp(line, "0") == 0 )
		ppa_drv_dp_dbg_param_ipv6_acc_en = 0;
	else
		ppa_drv_dp_dbg_param_ipv6_acc_en = 1;

	return 0;
}

static int __init ppa_drv_dp_dbg_param_wanqos_en_setup(char *line)
{
	ppa_drv_dp_dbg_param_wanqos_en = simple_strtoul(line, NULL, 0);

	if ( ppa_drv_dp_dbg_param_wanqos_en > 8 )
		ppa_drv_dp_dbg_param_wanqos_en = 0;

	return 0;
}
#if defined(CONFIG_PPTP_MODULE) || defined(CONFIG_PPTP)
int32_t (*ppa_pptp_get_callid_fn)(struct net_device *ppp_dev,struct ppp_channel *chan) = NULL;
int32_t (*ppa_pptp_get_seq_num_fn)(struct net_device *ppp_dev,void *chan,int *sent_seq,int *rcv_seq) = NULL;
int32_t (*ppa_pptp_get_outer_src_dst_addr_fn)(struct net_device *ppp_dev,void *chan,uint32_t *outer_srcip,uint32_t *outer_dstip,struct rtable *rut,uint8_t *mac,struct net_device *base_dev) = NULL;
int32_t (*ppa_get_pptp_hdrlen_fn)(struct net_device *ppp_dev,void *chan) = NULL;
int32_t (*ppa_form_pptp_hdr_fn)(struct net_device *ppp_dev,void *chan,void *hdr) = NULL;
int32_t (*ppa_update_pptp_hdr_fn)(struct net_device *ppp_dev,void *chan, void *hdr,int len) = NULL;
int32_t (*ppa_pptp_rcv_fn)(struct net_device *ppp_dev,struct ppp_channel *chan, struct sk_buff *skb,uint32_t pptp_gre_header_len) = NULL;
int32_t (*ppa_check_pptp_ack_flag_fn)(struct sk_buff *skb) = NULL;
#endif
void* (*ppa_get_pptp_info_fn)(struct net_device *ppp_dev) =NULL;



__setup("param_en=", ppa_drv_dp_dbg_param_enable_setup);
__setup("ethwan=", ppa_drv_dp_dbg_param_wan_mode_setup);
__setup("wanitf=", ppa_drv_dp_dbg_param_wanitf_setup);
__setup("ipv6_acc_en=", ppa_drv_dp_dbg_param_ipv6_acc_en_setup);
__setup("wanqos_en=", ppa_drv_dp_dbg_param_wanqos_en_setup);
#endif //end of PPA_DP_DBG_PARAM_ENABLE

EXPORT_SYMBOL(ppa_drv_dp_dbg_param_enable);
EXPORT_SYMBOL(ppa_drv_dp_dbg_param_ethwan);
EXPORT_SYMBOL(ppa_drv_dp_dbg_param_wanitf);
EXPORT_SYMBOL(ppa_drv_dp_dbg_param_ipv6_acc_en);
EXPORT_SYMBOL(ppa_drv_dp_dbg_param_wanqos_en);
/* End of debugging code */

EXPORT_SYMBOL(ppa_hook_session_accel_fn);
EXPORT_SYMBOL(ppa_hook_session_add_fn);
EXPORT_SYMBOL(ppa_hook_get_ct_stats_fn);
EXPORT_SYMBOL(ppa_hook_session_bradd_fn);
EXPORT_SYMBOL(ppa_hook_session_del_fn);
EXPORT_SYMBOL(ppa_hook_pitem_refcnt_inc_fn);
EXPORT_SYMBOL(ppa_hook_pitem_refcnt_dec_fn);
#if defined(CONFIG_LTQ_PPA_MPE_IP97)
EXPORT_SYMBOL(ppa_hook_session_ipsec_add_fn);
EXPORT_SYMBOL(ppa_hook_session_ipsec_del_fn);
#endif
EXPORT_SYMBOL(ppa_hook_session_prio_fn);
EXPORT_SYMBOL(ppa_hook_inactivity_status_fn);
EXPORT_SYMBOL(ppa_hook_set_inactivity_fn);
EXPORT_SYMBOL(ppa_hook_bridge_entry_add_fn);
EXPORT_SYMBOL(ppa_hook_bridge_entry_delete_fn);
EXPORT_SYMBOL(ppa_hook_bridge_entry_hit_time_fn);
#if defined(CONFIG_LTQ_PPA_IF_MIB) && CONFIG_LTQ_PPA_IF_MIB
EXPORT_SYMBOL(ppa_hook_get_netif_accel_stats_fn);
#endif
#if defined(CONFIG_PPA_API_DIRECTCONNECT) && CONFIG_PPA_API_DIRECTCONNECT
EXPORT_SYMBOL(ppa_check_if_netif_fastpath_fn);
EXPORT_SYMBOL(ppa_hook_disconn_if_fn);
#if defined(WMM_QOS_CONFIG) && WMM_QOS_CONFIG
EXPORT_SYMBOL(ppa_register_qos_class2prio_hook_fn);
#endif
#endif
EXPORT_SYMBOL(ppa_hook_directpath_register_dev_fn);
EXPORT_SYMBOL(ppa_hook_directpath_ex_register_dev_fn);
EXPORT_SYMBOL(ppa_hook_directlink_register_dev_fn);
EXPORT_SYMBOL(ppa_hook_directpath_send_fn);
EXPORT_SYMBOL(ppa_hook_directpath_ex_send_fn);
EXPORT_SYMBOL(ppa_hook_directpath_rx_stop_fn);
EXPORT_SYMBOL(ppa_hook_directpath_ex_rx_stop_fn);
EXPORT_SYMBOL(ppa_hook_directpath_rx_restart_fn);
EXPORT_SYMBOL(ppa_hook_directpath_ex_rx_restart_fn);
EXPORT_SYMBOL(ppa_hook_directpath_alloc_skb_fn);
EXPORT_SYMBOL(ppa_hook_directpath_recycle_skb_fn);
EXPORT_SYMBOL(ppa_hook_get_ifid_for_netif_fn);
#ifdef CONFIG_LTQ_PPA_QOS
EXPORT_SYMBOL(ppa_hook_get_qos_qnum);
EXPORT_SYMBOL(ppa_hook_get_qos_mib);

#ifdef CONFIG_LTQ_PPA_QOS_RATE_SHAPING
EXPORT_SYMBOL(ppa_hook_set_ctrl_qos_rate);
EXPORT_SYMBOL(ppa_hook_get_ctrl_qos_rate);
EXPORT_SYMBOL(ppa_hook_set_qos_rate);
EXPORT_SYMBOL(ppa_hook_get_qos_rate);
EXPORT_SYMBOL(ppa_hook_reset_qos_rate);
#endif // CONFIG_LTQ_PPA_QOS_RATE_SHAPING

#ifdef CONFIG_LTQ_PPA_QOS_WFQ
EXPORT_SYMBOL(ppa_hook_set_ctrl_qos_wfq);
EXPORT_SYMBOL(ppa_hook_get_ctrl_qos_wfq);
EXPORT_SYMBOL(ppa_hook_set_qos_wfq);
EXPORT_SYMBOL(ppa_hook_get_qos_wfq);
EXPORT_SYMBOL(ppa_hook_reset_qos_wfq);
#endif // end of CONFIG_LTQ_PPA_QOS_WFQ
#endif //end of CONFIG_LTQ_PPA_QOS
EXPORT_SYMBOL(ppa_get_6rd_dmac_fn);
EXPORT_SYMBOL(ppa_get_ip4ip6_dmac_fn);
EXPORT_SYMBOL(ppa_get_6rd_phyif_fn);
EXPORT_SYMBOL(ppa_get_ip4ip6_phyif_fn);
EXPORT_SYMBOL(ppa_hook_directpath_enqueue_to_imq_fn);
EXPORT_SYMBOL(ppa_directpath_imq_en_flag);
EXPORT_SYMBOL(ppa_hook_directpath_reinject_from_imq_fn);
EXPORT_SYMBOL(ppa_hook_set_lan_seperate_flag_fn);
EXPORT_SYMBOL(ppa_hook_get_lan_seperate_flag_fn);
EXPORT_SYMBOL(ppa_hook_set_wan_seperate_flag_fn);
EXPORT_SYMBOL(ppa_hook_get_wan_seperate_flag_fn);
#if defined(CONFIG_LTQ_PPA_API_SW_FASTPATH)
EXPORT_SYMBOL(ppa_hook_set_sw_fastpath_enable_fn);
EXPORT_SYMBOL(ppa_hook_get_sw_fastpath_status_fn);
EXPORT_SYMBOL(ppa_hook_sw_fastpath_send_fn);
#endif
#if defined(CONFIG_L2NAT_MODULE) || defined(CONFIG_L2NAT)
EXPORT_SYMBOL(ppa_check_if_netif_l2nat_fn);
#endif

#if defined(CONFIG_PPTP_MODULE) || defined(CONFIG_PPTP)
EXPORT_SYMBOL(ppa_pptp_get_callid_fn);
EXPORT_SYMBOL(ppa_pptp_get_outer_src_dst_addr_fn);
EXPORT_SYMBOL(ppa_get_pptp_hdrlen_fn);
EXPORT_SYMBOL(ppa_form_pptp_hdr_fn);
EXPORT_SYMBOL(ppa_update_pptp_hdr_fn);
EXPORT_SYMBOL(ppa_pptp_get_seq_num_fn);
EXPORT_SYMBOL(ppa_pptp_rcv_fn);
EXPORT_SYMBOL(ppa_check_pptp_ack_flag_fn);
#endif
EXPORT_SYMBOL(ppa_get_pptp_info_fn);
