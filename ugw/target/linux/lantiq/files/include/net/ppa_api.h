#ifndef __PPA_API_H__20081031_1913__
#define __PPA_API_H__20081031_1913__


/*******************************************************************************
 **
 ** FILE NAME    : ppa_api.h
 ** PROJECT      : PPA
 ** MODULES      : PPA API (Routing/Bridging Acceleration APIs)
 **
 ** DATE         : 31 OCT 2008
 ** AUTHOR       : Xu Liang
 ** DESCRIPTION  : PPA Protocol Stack Hook API Header File
 ** COPYRIGHT    :              Copyright (c) 2009
 **                          Lantiq Deutschland GmbH
 **                   Am Campeon 3; 85579 Neubiberg, Germany
 **
 **   For licensing information, see the file 'LICENSE' in the root folder of
 **   this software module.
 **
 ** HISTORY
 ** $Date        $Author                	$Comment
 ** 31 OCT 2008  Xu Liang               	Initiate Version
 ** 10 DEC 2012  Manamohan Shetty   	Added the support for RTP,MIB mode and CAPWAP
 ** 08 APR 2014  Kamal Eradath		GRX500 Adaptations
 *******************************************************************************/
/*! \file ppa_api.h
  \brief This file contains es.
  provide PPA API.
 */

/** \defgroup PPA_API PPA Kernel Hook and Userspace Function API
  \brief PPA is a loadable network module. Hence, it exports its API though function pointer hooks. Callers need to check that hooks are non-NULL before invoking them. The hooks are initialized when the PPA is initialized. Certain API which are control / configuration related are also exposed to user space applications through the ioctl API. The PPA Kernel and Userspace API are discussed in the following sections:
 */
/* @{*/
/** \defgroup PPA_IOCTL PPA Userspace API
  \brief  The subset of PPA API which is exposed to userspace for control and configuration of the PPA is invoked through
  an ioctls()/system call interface as described in this section.
  The API is defined in the following two source files:
  - ppa_api.h: Header file for PPA API
  - ppa_api.c: C Implementation file for PPA API
 */

/** \defgroup PPA_HOOK_API PPA Hook API
  \brief  PPA is a loadable network module. Hence, it exports its API though function pointer hooks.  Callers need to check that hooks are non-NULL before invoking them. The hooks are initialized  when the PPA is initialized.
  - ppa_hook.h: Header file for PPA API
  - ppa_hook.c: C Implementation file for PPA API
 */

/** \defgroup PPA_PWM_API PPA Power Management API
  \brief  PPA Power Management  API provide PPA Power Management and IOCTL API
  The API is defined in the following two source files
  - ppa_api_pwm.h: Header file for PPA API
  - ppa_api_pwm.c: C Implementation file for PPA Power management API
  - ppa_api_pwm_logic.c: C impelementation file for Powr management Logic and interface with PPE driver
 */
/** \defgroup PPA_API_DIRECTPATH PPA Direct Path API
  \brief  This section describes the PPA DirectPath API that allows a driver on a CPU to bypass the protocol stack and send and receive packets directly from the PPA acceleration function. For a 2-CPU system, this API is used to communicate with devices whose drivers are running on the 2nd CPU (or Core 1) - usually Core 1 is not running any protocol stack, and all protocol stack intelligence is on Core 0. This API is not yet implemented for PPE D4 or A4 firmware. It is provided as advance information on the DirectPath interfaces.The PPA DirectPath aims to accelerate packet processing by reducing CPU load  when the protocol stack processes the packet. It allows a CPU-bound driver to directly talk to the PPA and to the PPE engine bypassing the stack path and providing a short-cut.
  - ppa_api_directpath.h: Header file for PPA API
  - ppa_api_directpath.c: C Implementation file for PPA API
 */

/** \defgroup PPA_ADAPTATION_LAYER PPA Stack Adaptation API
  \brief  PPA module aims for OS and Protocol stack independence, and the
  core PPA logic does not access any OS or Protocol stack implementation
  specific structures directly. The PPA Protocol Stack Adaptation layer
  provides API that allows for straight-forward and structured OS / protocol
  stack porting of the PPA just by porting the Adaptation Layer (AL) API.
  The AL API is defined in the following two source files
  - ppa_stack_al.h: Header file for AL layer
  - ppa_stack_al.c: C Implementation file for AL API
 */
/* @}*/



#include <uapi/net/ppa_api.h>

#include <net/ppa_api_common.h>
#ifdef __KERNEL__
#include <net/ppa_api_directpath.h>
#endif

#if defined(CONFIG_LTQ_PPA_GRX500) && CONFIG_LTQ_PPA_GRX500
#ifdef __KERNEL__
#include <xway/switch-api/gsw_types.h>
#include <xway/switch-api/lantiq_gsw_flow.h>
#else
#include <net/gsw_types.h>
#include <net/lantiq_gsw_flow.h>
#endif
#endif

#include <stdbool.h> 


/*
 * ####################################
 *              Definition
 * ####################################
 */

#if defined(WMM_QOS_CONFIG) && WMM_QOS_CONFIG
#define WMM_QOS_DEV_F_REG 			0x00000001

#define WMM_QOS_DEV_F_DREG 			0x00000002
#endif/* WMM_QOS_CONFIG */

#ifdef NO_DOXY

#define SESSION_LIST_HASH_SHIFT                 8
#define SESSION_LIST_HASH_MASK                  ((1 << SESSION_LIST_HASH_BIT_LENGTH) - 1)
#define SESSION_LIST_HASH_VALUE(x, is_reply)    (((((uint32_t)(x) >> SESSION_LIST_HASH_SHIFT) & SESSION_LIST_HASH_MASK) << 1) | ((is_reply) ? 1 : 0))

#define SESSION_LIST_MC_HASH_SHIFT              0
#define SESSION_LIST_MC_HASH_BIT_LENGTH         6
#define SESSION_LIST_MC_HASH_MASK               ((1 << SESSION_LIST_MC_HASH_BIT_LENGTH) - 1)
#define SESSION_LIST_MC_HASH_TABLE_SIZE         (1 << SESSION_LIST_MC_HASH_BIT_LENGTH)
#define SESSION_LIST_MC_HASH_VALUE(x)           (((uint32_t)(x) >> SESSION_LIST_MC_HASH_SHIFT) & SESSION_LIST_MC_HASH_MASK)

#define BRIDGING_SESSION_LIST_HASH_BIT_LENGTH   8
#define BRIDGING_SESSION_LIST_HASH_MASK         ((1 << BRIDGING_SESSION_LIST_HASH_BIT_LENGTH) - 1)
#define BRIDGING_SESSION_LIST_HASH_TABLE_SIZE   (1 << BRIDGING_SESSION_LIST_HASH_BIT_LENGTH)
#define PPA_BRIDGING_SESSION_LIST_HASH_VALUE(x)     ( ( ((uint32_t)((uint8_t *)(x))[4] << 8) | ((uint8_t *)(x))[5] ) & BRIDGING_SESSION_LIST_HASH_MASK )


#define VLAN_ID_SPLIT(full_id, pri, cfi, vid)   pri=( (full_id) >> 13 ) & 7; cfi=( (full_id) >>12) & 1; vid= (full_id) & 0xFFF
#define VLAN_ID_CONBINE(full_id, pri, cfi, vid)   full_id =( ( (uint16_t)(pri) & 7) << 13 )  | ( ( (uint16_t)( cfi) & 1) << 12  )  | ((uint16_t) (vid) & 0xFFF )

#define PPA_JIFFY_MILLSEC(x, hz) (x * 1000 /(hz))

#define WRAPROUND_32BITS  ((uint64_t)0xFFFFFFFF)
#define WRAPROUND_64BITS  ((uint64_t)0xFFFFFFFFFFFFFFFF)
#if !(defined(CONFIG_LTQ_PPA_GRX500) && CONFIG_LTQ_PPA_GRX500)
#define WRAPROUND_SESSION_MIB  ((uint64_t)0x1FFFFFE0) /*note, 0xFFFFFF * 0x20. In PPE FW, 1 means 32 bytes, ie 0x20 this value will be different with GRX500 platform */
#else
#define WRAPROUND_SESSION_MIB WRAPROUND_32BITS
#endif

#if IS_ENABLED(CONFIG_LTQ_PPA_QOS_MPE_ACCEL)
/* Flag to extract bit 28 of extmark to check if DS_QOS is enabled for this session*/
#define SESSION_DS_QOS_SET				0x10000000

/* Flag to extract bit 17 of extmark that specifies if Ingress / Egress QoS enabled for sesssion */
#define SESSION_ING_EGR_QOS				0x00020000

/* Flag to extract bit 18 of extmark that specifies if classification is done from PCE or iptables */
#define SESSION_PCE_CLASSIFICATION		0x00040000

/* Flag to extract bits 19-20 of extmark that specifies if TC bits are set for Ingress Qs / Egress Qs / Both (Ingress & Egress Qs) */
#define SESSION_ING_TC_SET				0x00080000
#define SESSION_EGR_TC_SET				0x00100000

/* Flag to extract bits 21-22 of extmark that specifies the Ingress group of the session */
#define SESSION_ING_GROUP				0x00600000

/* Flag to extract bits 23-27 of extmark that are set with TC of Ingress Qs */
#define SESSION_INGRESS_TC				0x0F800000

#define SESSION_FLAG2_DS_MPE_QOS		0x00008000 //Flag for DS_QOS capab

#define ING_TC_SET_POS					19
#define EGR_TC_SET_POS					20
#define ING_GROUP_POS					21
#define INGRESS_TC_BIT_POS				23
#endif /* CONFIG_LTQ_PPA_QOS_MPE_ACCEL */

#ifdef __KERNEL__
#if IS_ENABLED(WMM_QOS_CONFIG)
typedef int (*PPA_QOS_CLASS2PRIO_CB)(int32_t , PPA_NETIF *, uint8_t *);
#endif
#endif


#if defined(CONFIG_LTQ_PPA_MPE_IP97)

struct ipsec_tunnel_intf {
	PPA_IPADDR         src_ip;
	PPA_NETIF          *tx_if;
};

typedef enum {
	OUTBOUND=0,
	INBOUND
} sa_direction;

typedef struct {
	int tunnel_id;
	uint32_t tx_pkt_count;
	uint32_t tx_byte_count;
	uint32_t rx_pkt_count;
	uint32_t rx_byte_count;

}IPSEC_TUNNEL_MIB_INFO;

#endif

#if defined(CONFIG_LTQ_PPA_HAL_SELECTOR)

typedef enum {
	PPE_HAL=0,
	PAE_HAL,
	MPE_HAL,
	TMU_HAL,
	LRO_HAL,
	DSL_HAL,
	SWAC_HAL,
	PUMA_HAL,
	MAX_HAL
} PPA_HAL_ID;

typedef enum {
	SESS_BRIDG=1,
	SESS_IPV4,
	SESS_IPV6,
	SESS_MC_DS,
	SESS_MC_DS_VAP,
	TUNNEL_6RD,
	TUNNEL_DSLITE,
	TUNNEL_L2TP_US,
	TUNNEL_L2TP_DS,
	TUNNEL_CAPWAP_US,
	TUNNEL_CAPWAP_DS,
	TUNNEL_ENCRYPT,
	TUNNEL_DECRYPT,
	TUNNEL_GRE_US,
	TUNNEL_GRE_DS,
	TUNNEL_IPSEC_US,
	TUNNEL_IPSEC_DS,
	TUNNEL_IPSEC_MIB,
	QOS_INIT,
	QOS_UNINIT,
	QOS_CLASSIFY,
	QOS_QUEUE,
	QOS_INGGRP,
	Q_SCH_WFQ,
	Q_SCH_SP,
	Q_DROP_DT,
	Q_DROP_RED,
	Q_DROP_WRED,
	Q_SHAPER,
	PORT_SHAPER,
	QOS_LAN_CLASSIFY,
	QOS_LAN_QUEUE,
	QOS_WMM_INIT,
	QOS_WMM_UNINIT,
	XDSL_PHY,
	SESS_NAT_LOOPBACK,
	PORT_METER,
	QUEUE_THRESHOLD,
#if IS_ENABLED(CONFIG_LTQ_PPA_QOS_MPE_ACCEL)
	MPE_DS_QOS,
#endif
	MAX_CAPS
} PPA_API_CAPS;

#define PPA_VERSION_LEN 	64
#define MAX_TUNNEL_ENTRIES      16

#define FLAG_SESSION_HI_PRIO    0x0001
#define FLAG_SESSION_SWAPPED    0x0002
#define FLAG_SESSION_LOCK_FAIL  0x0004

// tunnel table datastructures
#endif //defined(CONFIG_LTQ_PPA_HAL_SELECTOR)


/* PPA default values */
#define PPA_IPV4_HDR_LEN    20
#define PPA_IPV6_HDR_LEN    40

#define PPA_VLAN_PROTO_8021Q  0x8100
#define PPA_VLAN_PROTO_8021AD 0x88A8

#endif //NO_DOXY

/*
 * ####################################
 *              Data Type
 * ####################################
 */

/* -------------------------------------------------------------------------- */
/*                 Structure and Enumeration Type Defintions                  */
/* -------------------------------------------------------------------------- */

/** \addtogroup  PPA_HOOK_API */
/*@{*/

/*!
  \brief  ppa_ct_counter  holds the connection statistics.
 */
typedef struct {
	uint32_t txPackets;  /*!< Tx Packets - Packets from LAN to WAN. Currently not available */
	uint64_t txBytes;    /*!< Tx bytes   - Bytes from LAN to WAN */
	uint32_t rxPackets;  /*!< Rx Packets - Packets from WAN to LAN. Currently not available */
	uint64_t rxBytes;    /*!< Rx Bytes   - Bytes from WAN to LAN */
	uint32_t lastHitTime; /*!< Last hit time in secs. It is approximate
				time in seconds when a packet is seen on this
				connection. Note that seconds calculation is
				based on jiffies */
} PPA_CT_COUNTER;


/*!
  \brief This is the data structure for PPA Interface Info specification.
 */
typedef struct {
	PPA_IFNAME *ifname;     /*!< Name of the stack interface */
	uint32_t    if_flags;   /*!< Flags for Interface. Valid values are below: PPA_F_LAN_IF and PPA_F_WAN_IF */
	uint32_t    port;       /*!< physical port id  for this Interface. Valid values are below: 0 ~  */
	uint32_t    force_wanitf_flag;   /*!< force_wanitf_flag is used for force change PPE FW's LAN/WAN interface */
	PPA_IFNAME  *ifname_lower;     /*!< Name of the manually configured its lower interface */
	uint8_t    hw_disable;  /*!< If this flag is set then only HW acceleration would be disabled for ifname (SW acceleration would still work for ifname) */
} PPA_IFINFO;

/*!
  \brief This is the data structure for PPA Initialization kernel hook function
 */
typedef struct {
    PPA_VERIFY_CHECKS   lan_rx_checks;      /*!<   LAN Ingress packet checks */
    PPA_VERIFY_CHECKS   wan_rx_checks;      /*!<   WAN Ingress packet checks */
    uint32_t    num_lanifs;                 /*!<   Number of LAN side interfaces */
    PPA_IFINFO *p_lanifs;                   /*!<   Pointer to array of LAN Interfaces. */
    uint32_t    num_wanifs;                 /*!<   Number of WAN side interfaces */
    PPA_IFINFO *p_wanifs;                   /*!<   Pointer to array of WAN Interfaces. */
    uint32_t    max_lan_source_entries;     /*!<   Maximum Number of session entries with LAN source */
    uint32_t    max_wan_source_entries;     /*!<   Maximum Number of session entries with WAN source */
    uint32_t    max_mc_entries;             /*!<   Maximum Number of multicast sessions */
    uint32_t    max_bridging_entries;       /*!<   Maximum Number of bridging entries */
    uint32_t    add_requires_min_hits;      /*!<   Minimum number of calls to ppa_add_session() before session would be added in h/w - calls from the same hook position in stack. Currently, set to 1 */
#if defined(CONFIG_LTQ_PPA_HANDLE_CONNTRACK_SESSIONS)
    uint32_t    add_requires_lan_collisions;/*!<   Minimum number of LAN collision entries to be reserved in h/w*/
    uint32_t    add_requires_wan_collisions;/*!<   Minimum number of WAN collision entries to be reserved in h/w*/
#endif
} PPA_INIT_INFO;

/*!
  \brief This is the data structure which specifies an interface and its TTL value as applicable for multicast routing.
 */
typedef struct {
	PPA_IFNAME *ifname; /*!<   Pointer to interface name.  */
	uint8_t     ttl;    /*!<  Time to Live (TTL) value of interface which is used for multicast routing to decide if a packet can be routed onto that interface
			      Note, it is not used at present.
			     */
} IF_TTL_ENTRY;


/*!
  \brief This is the data structure for PPA Multicast Group membership. It specifies the interfaces which are members of
  the specified IP Multicast Group address. Please see the discussion on outer and inner VLAN tags in the
  section on PPA_SESSION_EXTRA data structure.
 */
typedef struct {
	IP_ADDR_C       ip_mc_group;    /*!<   Multicast IP address group */
	int8_t          num_ifs;        /*!<   Number of Interfaces which are member of this Multicast IP group address */
	IF_TTL_ENTRY    array_mem_ifs[PPA_MAX_MC_IFS_NUM];  /*!< Array of interface elements of maximum PPA_MAX_MC_IFS_NUM elements.
							      Actual number of entries is specified by num_ifs */
	uint8_t         if_mask;        /*!<   Mask of Interfaces corresponding to num_ifs interfaces specified in array_mem_ifs. For internaly use only. */
	PPA_IFNAME     *src_ifname;     /*!<   the source interface of specified multicast IP address group */
	uint32_t        vlan_insert     :1;     /*!<   If inner VLAN tag should be inserted into the frame at egress. Valid values are: PPA_ENABLED and PPA_DISABLED */
	uint32_t        vlan_remove     :1;     /*!<  If inner VLAN untagging should be performed on the received frame. Untagging, if enabled, is
						  carried out before any VLAN tag insert. Valid values are:PPA_ENABLED and PPA_DISABLED */
	uint32_t        out_vlan_insert :1;     /*!<   If outer VLAN tag should be inserted into the frame at egress. Valid values are: PPA_ENABLED and PPA_DISABLED */
	uint32_t        out_vlan_remove :1;     /*!<  If outer VLAN untagging should be performed on the received frame. Untagging, if enabled, is
						  carried out before any VLAN tag insert. Valid values are:PPA_ENABLED and PPA_DISABLED */
	uint32_t        dslwan_qid_remark:1;    /*!<   not use at present */
	uint32_t        reserved1       :3;     /*!<   valid in A4/A5 */
	uint32_t        vlan_prio       :3;     /*!<   802.1p VLAN priority configuration. Valid values are 0-7. */
	uint32_t        vlan_cfi        :1;     /*!<   Always set to 1 for Ethernet frames */
	uint32_t        vlan_id         :12;    /*!<   VLAN Id to be used to tag the frame. Valid values are 0-4095 */
	uint32_t        out_vlan_tag;           /*!<   Outer VLAN tag value including VLAN Id. */
	uint32_t        new_dscp_en     :1;     /*!<   If new dscp value should be set. Valid values are:PPA_ENABLED and PPA_DISABLED */
	uint32_t        res             :15;    /*!<   reserved */
	uint32_t        new_dscp        :16;    /*!<   New DSCP code point value for the session.Valid values are 0-63. */
	uint16_t        dslwan_qid;             /*!<   not use at present */

	uint32_t        bridging_flag;          /*!<   0 - routing mode/igmp proxy, 1 - bridge mode/igmp snooping. */
	uint8_t         mac[PPA_ETH_ALEN];      /*!<  reserved for future */
	uint8_t         SSM_flag;     /*!< Set the flag if source specific forwarding is required default 0*/
	IP_ADDR_C       source_ip;    /*!<  source ip address */
#if defined(RTP_SAMPLING_ENABLE) && RTP_SAMPLING_ENABLE
	uint8_t         RTP_flag;   /*!< rtp flag */
#endif
#if defined(CONFIG_LTQ_PPA_GRX500) && CONFIG_LTQ_PPA_GRX500
	uint16_t	    group_id;		    /*!<   Multicast group identifier allocated by the multicast daemon */
	uint8_t         src_mac[PPA_ETH_ALEN];      /*!< source mac address for grx5xx. */
#endif
} PPA_MC_GROUP;

/*!
  \brief This data structure is an abstraction for unicast and multicast routing sessions.
  Pointer to any kind of PPA session
 */
typedef void PPA_U_SESSION;

/*!
  \brief This is the data structure for standard packet and byte statistics for an interface.
 */
typedef struct {
	uint32_t    tx_pkts;            /*!<   Number of transmitted packets through the interface */
	uint32_t    rx_pkts;            /*!<   Number of received packets through the interface */
	uint32_t    tx_discard_pkts;    /*!<   Number of packets discarded while transmitting through the interface. */
	uint32_t    tx_error_pkts;      /*!<   Number of transmit errors through the interface. */
	uint32_t    rx_discard_pkts;    /*!<   Number of received packets through the interface that were discarded */
	uint32_t    rx_error_pkts;      /*!<   Number of received errors through the interface. */
	uint32_t    tx_bytes;           /*!<   Number of transmit bytes through the interface */
	uint32_t    rx_bytes;           /*!<   Number of received bytes through the interface */

#if defined(CONFIG_LTQ_PPA_HAL_SELECTOR)
        uint32_t    rx_pkts_prev[MAX_HAL];     
        uint32_t    tx_pkts_prev[MAX_HAL];    
#endif

} PPA_IF_STATS;

/*!
  \brief This is the data structure for PPA accelerated statistics for an interface. Depending on the platform and
  acceleration capabilities, some of the statistics may not be available.
 */
typedef struct {
	uint32_t    fast_routed_tcp_pkts;       /*!< Fastpath routed TCP unicast packets Tx */
	uint32_t    fast_routed_udp_pkts;       /*!< Fastpath routed UDP unicast packets Tx */
	uint32_t    fast_routed_udp_mcast_pkts; /*!< Fastpath routed UDP multicast packets Tx */
	uint32_t    fast_drop_pkts;             /*!< Fastpath ingress pkts dropped */
	uint32_t    fast_drop_bytes;            /*!< Fastpath ingress bytes dropped */
	uint32_t    fast_ingress_cpu_pkts;      /*!< Fastpath ingress CPU pkts */
	uint32_t    fast_ingress_cpu_bytes;     /*!< Fastpath ingress CPU bytes */
	uint32_t    rx_pkt_errors;              /*!< Fastpath packet error */
	uint32_t    fast_bridged_ucast_pkts;    /*!< Fastpath bridged unicast pkts */
	uint32_t    fast_bridged_mcast_pkts;    /*!< Fastpath bridged multicast pkts */
	uint32_t    fast_bridged_bcast_pkts;    /*!< Fastpath bridged broadcast pkts */
	uint32_t    fast_bridged_bytes;         /*!< Fastpath bridged bytes */
} PPA_ACCEL_STATS;


/*!
  \brief Union of PPA VLAN filter criteria.
 */
typedef union
{
	PPA_IFNAME     *ifname; /*!< Pointer to interface name on which VLAN filter match is to be performed. */
	IPADDR          ip_src; /*!< IP source address of ingress frame for VLAN filter matching. */
	uint32_t        eth_protocol;       /*!< Ethernet protocol as a match filter for VLAN filter matching */
	uint32_t        ingress_vlan_tag;   /*!< Ingress frame VLAN tag as match criteria for VLAN filter matching */
} match_criteria_vlan;

/*!
  \brief This data structure specifies the filter or match criteria for applying VLAN transforms based on rules. It is currently supported only for bridging paths.
 */
typedef struct {
	match_criteria_vlan    match_field;            /*!< Union of VLAN filter criteria */
	uint32_t        match_flags;    /*!< Indicates which VLAN filter criteria is specified in this VLAN match entry.
					  Valid values are one of the following: \n
					  PPA_F_VLAN_FILTER_IFNAME \n
					  PPA_F_VLAN_FILTER_IP_SRC \n
					  PPA_F_VLAN_FILTER_ETH_PROTO \n
					  PPA_F_VLAN_FILTER_VLAN_TAG \n
					 */
} PPA_VLAN_MATCH_FIELD;

/*!
  \brief This is the data structure for PPA VLAN configuration ioctl() on a per interface basis from userspace. It is currently
  supported only for bridging paths.
 */
typedef struct {
	uint16_t        vlan_vci;   /*!< VLAN Information including VLAN Id, 802.1p and CFI bits. */
	uint16_t        qid;        /*!< queue index */
	uint32_t        out_vlan_id; /*!< out vlan id */
	uint32_t        inner_vlan_tag_ctrl;/*!< none(0)/remove(1)/insert(2)/replac(3), for vlan tag based only. */
	uint32_t        out_vlan_tag_ctrl;  /*!< none(0)/remove(1)/insert(2)/replac(3), for vlan tag based only. */
	uint16_t        num_ifs;    /*!< Number of interfaces in the array of PPA_IFINFO structures. */
	PPA_IFINFO     *vlan_if_membership; /*!< Pointer to array of interface info structures for each interface which is a member of this VLAN group. The number of entries is given by num_ifs. */
} PPA_VLAN_INFO;

/*!
  \brief This is the data structure for PPA VLAN filter configuration. It is currently supported only for bridging paths
 */
typedef struct {
	PPA_VLAN_MATCH_FIELD    match_field;    /*!< VLAN Match field information */
	PPA_VLAN_INFO           vlan_info;      /*!< VLAN Group and Membership Info */
} PPA_VLAN_FILTER_CONFIG;


#if defined(CONFIG_LTQ_PMCU) || defined(CONFIG_LTQ_PMCU_MODULE)
/*!
  \brief Union of ppa power transitin watermark.
 */
union watermark {
	uint32_t ppa_pwm_wm1;  /*!< Watermark value for PPE transition between D0 and D1 */
	uint32_t ppa_pwm_wm2;  /*!< Watermark value for PPE transition between D1 and D2 */
	uint32_t ppa_pwm_wm3;  /*!< Watermark value for PPE transition between D2 and D3 */
};

/*!
  \brief This is the data structure definition for PPA PWM states water mark
 */
typedef struct {
	int16_t flag;   /*!< flag indicating if watermark type. flag=1: watermark is packet count; flag=2: watermark is byte count  */
	int32_t time_interval; /*!< time interval of watermarks in milliseconds. */
	union watermark WM;  /*!< Watermark value for PPE transition */
}WM_t;

/*!
  \brief This is the data structure for PPA Power management basic watermark configuration
 */
typedef struct {
	WM_t ppa_pwm_wm1;  /*!< Watermark value for PPE transition between D0 and D1 */
	WM_t ppa_pwm_wm2;  /*!< Watermark value for PPE transition between D1 and D2*/
	WM_t ppa_pwm_wm3;  /*!< Watermark value for PPE transition between D2 and D3*/
}PPA_PWM_WM_t;

/*!
  \brief This is the data structure for PPA Power management configuration
 */
typedef struct {
	uint8_t ppa_pwm;  /*!< PPA power management mode: 0/1-OFF/ON */
	PPA_PWM_WM_t ppa_pwm_wm_up;  /*!< Watermark value for PPE transition for various states. */
	PPA_PWM_WM_t ppa_pwm_wm_down;  /*!< Watermark value for PPE transition for various states. */
	PPA_PWM_STATE_t e_ppa_pwm_init_state;  /*!< Initial power/performance state for PPE */
	uint32_t flag;  /*!< reserved.*/
}PPA_PWM_CONFIG_t;
#endif //end of CONFIG_LTQ_PMCU



/*!
  \brief This is the data structure for  PPA hooks list
 */
typedef struct PPA_HOOK_INFO_LIST {
	PPA_HOOK_INFO info;  /*!< ppa hook info */

	struct PPA_HOOK_INFO_LIST *next; /*!< point to next ppa hook info */
} PPA_HOOK_INFO_LIST;

/*!
  \brief This is the data structure for changing to FPI address
 */
typedef struct{
	uint32_t                    addr_orig;   /*!< original address */
	uint32_t                    addr_fpi;   /*!< converted FPI address */
	uint32_t                    flags;   /*!< reserved for future */
}PPA_FPI_ADDR;

#if defined(CONFIG_LTQ_PPA_IF_MIB) && CONFIG_LTQ_PPA_IF_MIB
/*!
  \brief This is the data structure for PPA accelerated statistics for an interface. Depending on the platform and
  acceleration capabilities, some of the statistics may not be available.
 */
typedef struct {
	PPA_PORT_MIB_INFO  port_mib_stats;
	PPA_IF_STATS hw_accel_stats;
	PPA_IF_STATS sw_accel_stats;
} PPA_NETIF_ACCEL_STATS;
#endif

#if defined(L2TP_CONFIG) && L2TP_CONFIG
/*!
  \brief This is the data structure for L2TP INFO
 */
typedef struct {
	uint32_t source_ip;
	uint32_t dest_ip;
	uint16_t tunnel_id;
	uint16_t session_id;
	uint32_t tunnel_idx;
	uint32_t tunnel_type;
	uint16_t ip_chksum;
	uint16_t udp_chksum;
} PPA_L2TP_INFO;

#endif

#ifdef NO_DOXY
typedef struct {
	uint32_t mtu_ix;
	uint32_t mtu;  // for add/del/get mtu entry only
} PPE_MTU_INFO;

typedef struct {
	uint32_t pppoe_ix;
	uint32_t pppoe_session_id;  // for add/del/get a pppoe entry only
} PPE_PPPOE_INFO;

#if defined(L2TP_CONFIG) && L2TP_CONFIG
typedef struct {
	uint32_t pppol2tp_ix;
	uint32_t pppol2tp_session_id;  // for add/del/get a pppoe entry only
	uint32_t pppol2tp_tunnel_id;
} PPE_PPPOL2TP_INFO;
#endif

typedef struct {
	uint32_t mac_ix;
	uint8_t mac[PPA_ETH_ALEN]; // for add/del/get a MAC entry only
} PPE_ROUTE_MAC_INFO;

typedef struct {
	uint32_t vlan_id; //out vlanid or ctag_vlan_id
	uint32_t vlan_entry;
#if defined(CONFIG_LTQ_PPA_GRX500) && CONFIG_LTQ_PPA_GRX500
	uint16_t port_id;
	uint16_t subif_id;
	uint16_t vlan_type;
	uint8_t  ctag_rem;
	uint8_t  ctag_ins;
	uint8_t  stag_rem;
	uint8_t  stag_ins;
	uint32_t stag_vlan_id;
#endif
} PPE_OUT_VLAN_INFO;

typedef struct {
	IP_ADDR ip;
	uint32_t ipv6_entry;
	uint32_t psuedo_ip;
} PPE_IPV6_INFO;

typedef enum {
	TUNNEL_TYPE_NULL = 0, /*!< Not Tunnel  */
	TUNNEL_TYPE_6RD,      /*!< 6rd Tunnel  */
	TUNNEL_TYPE_DSLITE,   /*!< DSLITE Tunnel  */
	TUNNEL_TYPE_CAPWAP,   /*!< CAPWAP Tunnel  */
	TUNNEL_TYPE_L2TP,     /*!< L2TP Tunnel  */
	TUNNEL_TYPE_EOGRE,    /*!< IPv4 Ethernet Over GRE Tunnel  */
	TUNNEL_TYPE_6EOGRE,    /*!< IPv6 Ethernet Over GRE Tunnel  */
	TUNNEL_TYPE_IPOGRE,   /*!< IPv4 IP Over GRE Tunnel  */
	TUNNEL_TYPE_IP6OGRE,   /*!< IPv6 IP Over GRE Tunnel  */
	TUNNEL_TYPE_IPSEC,    /*!< IPSEC Tunnel  */
	TUNNEL_TYPE_MAX       /*!< Not Valid Tunnel type  */
} e_Tunnel_Types;

typedef struct {
	uint32_t tunnel_idx;
	uint32_t tunnel_type;
	struct net_device *tx_dev;
} PPE_TUNNEL_INFO;

typedef struct {
	uint8_t f_ipv6;
	IP_ADDR src_ip;
	IP_ADDR dst_ip;
	uint32_t src_port;
	uint32_t dst_port;
	uint8_t session_id;
} PPA_LRO_INFO;

typedef struct {
	uint32_t f_is_lan;
	IP_ADDR_C src_ip;
	uint32_t src_port;
	IP_ADDR_C dst_ip;
	uint32_t dst_port;
	uint32_t f_is_tcp;   //  1: TCP, 0: UDP
	uint32_t route_type;
	IP_ADDR_C new_ip;   //NAT IP
	uint16_t new_port; //NAT UDP/TCP Port
	uint8_t  new_dst_mac[PPA_ETH_ALEN];
	PPE_ROUTE_MAC_INFO src_mac;
	PPE_MTU_INFO mtu_info;
	uint32_t pppoe_mode;
	PPE_PPPOE_INFO pppoe_info;
	PPE_TUNNEL_INFO tnnl_info;
#if defined(L2TP_CONFIG) && L2TP_CONFIG
	PPE_PPPOL2TP_INFO pppol2tp_info;
	PPE_TUNNEL_INFO l2tptnnl_info;
#endif

	uint32_t f_new_dscp_enable;
	uint32_t new_dscp;
	uint32_t f_vlan_ins_enable;
	uint32_t new_vci;
	uint32_t f_vlan_rm_enable;

	uint32_t f_out_vlan_ins_enable;
	PPE_OUT_VLAN_INFO out_vlan_info;
	uint32_t f_out_vlan_rm_enable;
	uint32_t dslwan_qid;
	uint32_t dest_list;
	uint32_t entry;
	uint32_t update_flags;  //for update_routing_entry only
	uint64_t bytes;  //for MIB
	uint32_t f_hit;  //only for test_and_clear_hit_stat
	uint8_t  collision_flag; // 1 mean the entry is in collsion table or no hashed table, like ASE/Danube
#if defined(CONFIG_LTQ_PPA_GRX500) && CONFIG_LTQ_PPA_GRX500
	int32_t hash_val;
	uint16_t dest_subif_id;
	uint16_t flags;
	uint8_t hi_prio;
	uint32_t   sessionAction; /* Pointer to session action */
#if defined(CONFIG_LTQ_PPA_IF_MIB) && CONFIG_LTQ_PPA_IF_MIB
	bool	is_rx_logical;
	bool    is_tx_logical;
	PPA_IFNAME rxifname[PPA_IF_NAME_SIZE];
	PPA_IFNAME txifname[PPA_IF_NAME_SIZE];
#endif
#endif
	uint32_t f_tc_remark_enable;
	uint32_t tc_remark;
	uint8_t     nFlowId; /* FlowId */
} PPE_ROUTING_INFO;

typedef struct{
	uint32_t f_is_lan;
	uint32_t entry_num;
	uint32_t mc_entry_num;
	uint32_t f_ip_verify;
	uint32_t f_tcpudp_verify;
	uint32_t f_tcpudp_err_drop;
	uint32_t f_drop_on_no_hit;
	uint32_t f_mc_drop_on_no_hit;
	uint32_t flags;
#if defined(CONFIG_LTQ_PPA_GRX500) && CONFIG_LTQ_PPA_GRX500
	uint8_t f_mpe_route;
	uint8_t f_l2tp_ds;
	uint8_t f_capwap_ds;
	uint8_t f_mc_vaps;
#endif
} PPE_ROUTING_CFG;

typedef struct{
	uint32_t entry_num;
	uint32_t br_to_src_port_mask;
	uint32_t br_to_src_port_en;
	uint32_t f_dest_vlan_en;
	uint32_t f_src_vlan_en;
	uint32_t f_mac_change_drop;
	uint32_t flags;
} PPE_BRDG_CFG;

typedef struct{
	uint32_t mode;
	uint32_t flags;
} PPE_FAST_MODE_CFG;

typedef struct {
	uint32_t        f_is_lan;
	uint32_t        f_enable;
	uint32_t        flags;
} PPE_ACC_ENABLE;

#if defined(MIB_MODE_ENABLE) && MIB_MODE_ENABLE

typedef struct {
	uint8_t        session_mib_unit;
} PPE_MIB_MODE_ENABLE;

#endif

typedef struct {
	uint32_t uc_dest_list;
	uint32_t mc_dest_list;
	uint32_t if_no;
} PPE_DEST_LIST;

typedef struct {
	uint32_t if_no;
	uint32_t f_eg_vlan_insert;
	uint32_t f_eg_vlan_remove;
	uint32_t f_ig_vlan_aware;
	uint32_t f_ig_src_ip_based;
	uint32_t f_ig_eth_type_based;
	uint32_t f_ig_vlanid_based;
	uint32_t f_ig_port_based;
	uint32_t f_eg_out_vlan_insert;
	uint32_t f_eg_out_vlan_remove;
	uint32_t f_ig_out_vlan_aware;
} PPE_BRDG_VLAN_CFG;


typedef struct {
	uint32_t entry;  /*so far it is only for get command*/
	uint32_t ig_criteria_type;
	uint32_t ig_criteria;;
	uint32_t new_vci;
	uint32_t dest_qos;
	PPE_OUT_VLAN_INFO out_vlan_info;
	uint32_t in_out_etag_ctrl;
	uint32_t vlan_port_map;
} PPE_BRDG_VLAN_FILTER_MAP;

typedef struct {
	uint32_t dest_ip_compare;
	uint32_t src_ip_compare;
	uint32_t f_vlan_ins_enable;
	uint32_t new_vci;
	uint32_t f_vlan_rm_enable;
	uint32_t f_src_mac_enable;
	uint32_t src_mac_ix;
	uint32_t pppoe_mode;
	uint32_t f_out_vlan_ins_enable;
	uint32_t f_tunnel_rm_enable;
	PPE_OUT_VLAN_INFO out_vlan_info;
	PPE_IPV6_INFO dst_ipv6_info;
	PPE_IPV6_INFO src_ipv6_info;
	uint32_t f_out_vlan_rm_enable;
	uint32_t f_new_dscp_enable;
	uint32_t new_dscp;
	uint32_t dest_qid;
	uint32_t dest_list;
	uint32_t route_type;
	uint32_t p_entry;
	uint64_t bytes;
	uint32_t f_hit;         //only for test_and_clear_hit_stat
	uint32_t update_flags;  //only for update only,not for new added one
#if defined(RTP_SAMPLING_ENABLE) && RTP_SAMPLING_ENABLE
	uint8_t  sample_en;   /*!< rtp flag */
	uint32_t rtp_pkt_cnt;  /*!< RTP packet mib */
	uint32_t rtp_seq_num;  /*!< RTP sequence number */
#endif
#if defined(CONFIG_LTQ_PPA_GRX500) && CONFIG_LTQ_PPA_GRX500
	int32_t	hash_val;
	uint32_t	f_ipv6;
	uint16_t	src_port;
	uint16_t	dst_port;
	uint16_t	group_id; //multicast grout id passed from mcastd
	uint16_t	subif_id;
	uint8_t	num_vap;
	uint8_t 	src_mac[PPA_ETH_ALEN];
	PPE_TUNNEL_INFO tnnl_info;
	uint32_t	mtu;
	uint16_t	flags; 	//input FLAG_SESSION_HI_PRIO
	//output FLAG_SESSION_SWAPPED
	uint16_t dest_subif[16];
	uint32_t sessionAction;
#endif
} PPE_MC_INFO;

typedef struct {
	uint32_t port;
	uint8_t  mac[PPA_ETH_ALEN];
	uint32_t f_src_mac_drop;
	uint32_t dslwan_qid;
	uint32_t dest_list;
	uint32_t p_entry;
	uint32_t f_hit; //only for test_and_clear_bridging_hit_stat
#if defined(CONFIG_LTQ_PPA_GRX500) && CONFIG_LTQ_PPA_GRX500
	uint32_t fid;
	int32_t  age_timer;
	uint16_t static_entry;
	uint16_t sub_ifid;
#endif
} PPE_BR_MAC_INFO;


typedef struct {
	uint16_t brid;
	uint32_t port;
#if defined(CONFIG_LTQ_PPA_GRX500) && CONFIG_LTQ_PPA_GRX500
	uint16_t subif_en;
	uint16_t subif;
#endif
	uint16_t vid;
	uint16_t index;
} PPA_BR_PORT_INFO;

struct ppe_itf_mib {
	uint32_t             ig_fast_brg_pkts;           // 0 bridge ?
	uint32_t             ig_fast_brg_bytes;          // 1 ?

	uint32_t             ig_fast_rt_ipv4_udp_pkts;   // 2 IPV4 routing
	uint32_t             ig_fast_rt_ipv4_tcp_pkts;   // 3
	uint32_t             ig_fast_rt_ipv4_mc_pkts;    // 4
	uint32_t             ig_fast_rt_ipv4_bytes;      // 5

	uint32_t             ig_fast_rt_ipv6_udp_pkts;   // 6 IPV6 routing
	uint32_t             ig_fast_rt_ipv6_tcp_pkts;   // 7
	uint32_t             res0;                       // 8
	uint32_t             ig_fast_rt_ipv6_bytes;      // 9

	uint32_t             res1;                       // A
	uint32_t             ig_cpu_pkts;
	uint32_t             ig_cpu_bytes;

	uint32_t             ig_drop_pkts;
	uint32_t             ig_drop_bytes;

	uint32_t             eg_fast_pkts;
#if defined(CONFIG_LTQ_PPA_GRX500) && CONFIG_LTQ_PPA_GRX500
	uint32_t		 ig_fast_rt_ipv6_mc_pkts;
	uint32_t		 eg_fast_bytes;
#endif
};


typedef struct {
	uint32_t itf ; //port
	struct ppe_itf_mib mib;
	uint32_t flag;
} PPE_ITF_MIB_INFO;

/* The main device statistics structure */
struct intf_mib {
       uint64_t    rx_packets;             /* total packets received       */
       uint64_t    tx_packets;             /* total packets transmitted    */
       uint64_t    rx_bytes;               /* total bytes received         */
       uint64_t    tx_bytes;               /* total bytes transmitted      */
       uint64_t    rx_errors;              /* bad packets received         */
       uint64_t    tx_errors;              /* packet transmit problems     */
       uint64_t    rx_dropped;             /* no space in linux buffers    */
       uint64_t    tx_dropped;             /* no space available in linux  */
       uint64_t    multicast;              /* multicast packets received   */
       uint64_t    collisions;

        /* detailed rx_errors: */
       uint64_t    rx_length_errors;
       uint64_t    rx_over_errors;         /* receiver ring buff overflow  */
       uint64_t    rx_crc_errors;          /* recved pkt with crc error    */
       uint64_t    rx_frame_errors;        /* recv'd frame alignment error */
       uint64_t    rx_fifo_errors;         /* recv'r fifo overrun          */
       uint64_t    rx_missed_errors;       /* receiver missed packet       */

        /* detailed tx_errors */
       uint64_t    tx_aborted_errors;
       uint64_t    tx_carrier_errors;
       uint64_t    tx_fifo_errors;
       uint64_t    tx_heartbeat_errors;
       uint64_t    tx_window_errors;

        /* for cslip etc */
       uint64_t    rx_compressed;
       uint64_t    tx_compressed;
};

typedef struct {
	struct intf_mib mib; 
	struct netif_info *ifinfo;
} PPA_ITF_MIB_INFO;



typedef struct {
	uint32_t f_enable ;
	uint32_t flags ;
} PPE_ENABLE_CFG;

typedef struct {
	int32_t num ;
	uint32_t flags ;
} PPE_COUNT_CFG;

typedef struct {
	uint32_t vfitler_type;
	int32_t num ;
	uint32_t flags ;
} PPE_VFILTER_COUNT_CFG;

typedef struct {
	PPA_MULTIFIELD_FLOW_INFO multifield_info;
	uint32_t entry;
	uint32_t flag;
} PPE_MULTIFILED_FLOW;

typedef struct {
	uint32_t portid;
	int32_t num ;
	uint32_t flags ;
} PPE_QOS_COUNT_CFG;

typedef struct {
	uint32_t portid;
	uint32_t queueid;
	uint32_t weight_level;
	uint32_t flag;
} PPE_QOS_WFQ_CFG;

typedef struct {
	uint32_t portid;
	uint32_t f_enable;
	uint32_t flag;
} PPE_QOS_ENABLE_CFG;

typedef struct {
	uint32_t portid;
	uint32_t queueid;
#if defined(MBR_CONFIG) && MBR_CONFIG
	int32_t  shaperid;
#endif
	uint32_t rate_in_kbps;
	uint32_t burst;
	uint32_t flag;
} PPE_QOS_RATE_SHAPING_CFG;


typedef struct {
	uint32_t vid;
} PPE_WAN_VID_RANGE;

typedef struct {
	PPA_IFNAME ifname[PPA_IF_NAME_SIZE];     /*!< Name of the stack interface */
	uint32_t    if_flags;   /*!< Flags for Interface. Valid values are below: PPA_F_LAN_IF and PPA_F_WAN_IF */
	uint32_t    port;   /*!< physical port id  for this Interface. Valid values are below: 0 ~  */
} PPE_IFINFO;

typedef struct {
	uint8_t lan_flag; // 1 means lan port, 0 means wan ports
	uint32_t physical_port;
	uint32_t old_lan_flag;  // 1 means lan port, 0 means wan ports
} PPE_WANITF_CFG;


typedef struct {
	uint8_t f_is_lan; // input: 1 means lan port, 0 means wan ports
	uint32_t src_ip;  // input:
	uint32_t src_port; //input:
	uint32_t dst_ip;   // input:
	uint32_t dst_port; // input:
	uint32_t hash_index;  //output
	uint32_t hash_table_id; //output mainly reserved for future GRX500 since LAN/WAN will share same hash table
	uint32_t flag; //reserved
} PPE_SESSION_HASH;

#endif  //end of NO_DOXY


#if defined(CONFIG_LTQ_PPA_API_SW_FASTPATH)

#endif

/*!
  \brief Enum for List of Engines that can perform QoS
 */
typedef enum {
	PPA_QOS_RESOURCE_CPU,
	PPA_QOS_RESOURCE_FW,
	PPA_QOS_RESOURCE_HW,
	PPA_QOS_RESOURCE_PPA
} PPA_QOS_RESOURCE;

/*!
  \brief Enum for Module type to be configured in PPA Engine
 */
typedef enum ppa_qos_module_type {
	PPA_QOS_MODULE_CLASSIFIER,
	PPA_QOS_MODULE_QUEUE,
	PPA_QOS_MODULE_BOTH
} PPA_QOS_MODULE_TYPE;

/*!
  \brief Engine Selector Capabilities Structure
 */
typedef struct {
	uint32_t q_max; /* Max number of queues supported by the engine */
	uint32_t q_cap; /* Bitmap to indicate various queueing capabilities supported by the engine */
	uint32_t q_len_max; /* Max queue length in Bytes supported by the engine */
	uint32_t cl_max; /* Max number of classifiers supported by the engine */
	uint32_t cl_cap; /* Bitmap to indicate various classifying capabilities supported by the engine */
} PPA_QOS_ENG_CAP;

/*!
  \brief QoS HAL Rate Shaping configuration structure
 */
typedef struct {
    PPA_IFNAME ifname[PPA_IF_NAME_SIZE];/*!< ifname of the interface on which the Queues & its shapers exist */
    char *dev_name;/*!<  dev name of the base interface for interface like pppoatm which do not have base netif */
    uint32_t portid;/*!< Port Id corresponding the interface/netif on which Queues/shapers exist */
    uint32_t queueid;/*!< Logical queue id while creating queue/physical queue id passed to TMU while shaper->queue assign */
#if defined(MBR_CONFIG) && MBR_CONFIG
	int32_t  shaperid;/*!< Logical shaper id while creating shaper/physical shaper id passed to TMU while shaper->queue assign */
#endif
	int32_t phys_shaperid;/*!< Physical shaper ID returned by TMU when a shaper is created*/
	PPA_QOS_SHAPER_CFG shaper;/*!< Shaper Info*/
	uint32_t rate_in_kbps;/*!< Peak rate in kbps*/
	uint32_t burst;/*!< Peak burst in kbps*/
	uint32_t flag;/*!< Flags for further use */
} QOS_RATE_SHAPING_CFG;

/*!
  \brief QoS Queue HAL DEL configuration structure
 */
typedef struct qos_q_del_cfg{
	char						*ifname;/*!< Interface name on which the Queue is modified*/
	char						*dev_name;/*!<  dev name of the base interface for interface like pppoatm which do not have base netif */
	int32_t						priority; /*!< Queue Priority or Precedence. Start from 1-16, with 1 as highest priority */
	int32_t						q_id; /*!< Original Queue id of the queue to be deleted */
	uint16_t 					intfId;/*!< flow Id + tc bits used for VAP's & Vlan interfaces*/
	uint32_t 					portid;/*!< Portid*/
	uint32_t 					flags;/*!< Flags for future use*/

}QOS_Q_DEL_CFG;

/*!
  \brief QoS Queue HAL ADD configuration structure
 */
typedef struct qos_q_add_cfg{
	char						*ifname;/*!< Interface name on which the Queue is modified*/
	char						*dev_name;/*!<  dev name of the base interface for interface like pppoatm which do not have base netif */
      	char	 					tc_map[MAX_TC_NUM];/*!< Which all Traffic Class(es) map to this Queue */
	uint8_t						tc_no; /*!< Number of Traffic Class(es) map to this Queue */
	uint8_t 					intfId_en;/*!<Enable/Disable for flow Id + tc bits used for VAP's & Vlan interfaces*/
	int32_t						weight; /*!< WFQ Weight */
	int32_t						priority; /*!< Queue Priority or Precedence. Start from 1-16, with 1 as highest priority */
	int32_t						qlen; /*!< Length of Queue in bytes */
	int32_t						q_id; /*!< Original Queue id of the Queue added */
	uint32_t 					portid;/*!< Portid*/
	uint16_t 					intfId;/*!< flow Id + tc bits used for VAP's & Vlan interfaces*/
	/* PPA_QOS_QSCHED_MODE may not be required as tmu hal can internaly find this out : Need to remove later*/
	PPA_QOS_QSCHED_MODE				q_type;/*!< Scheduler type */
	PPA_QOS_DROP_CFG				drop; /*!< Queue Drop Properties */
	uint32_t 					flags;/*!< Flags for future use*/

} QOS_Q_ADD_CFG;

/*!
  \brief QoS Queue HAL MOD configuration structure
 */
typedef struct qos_q_mod_cfg{
	char						*ifname;/*!< Interface name on which the Queue is modified*/
	uint32_t					enable; /*!< Whether Queue is enabled */
	int32_t						weight; /*!< WFQ Weight */
	int32_t						priority; /*!< Queue Priority or Precedence. Start from 1-16, with 1 as highest priority */
	int32_t						qlen; /*!< Length of Queue in bytes */
	int32_t						q_id; /*!< Original Queue id of the Queue modified */
	uint32_t 					portid;/*!< Portid*/
	PPA_QOS_QSCHED_MODE				q_type;/*!< Scheduler type */
	PPA_QOS_DROP_CFG				drop; /*!< Queue Drop Properties */
	uint32_t 					flags;/*!< Flags for future use*/

}QOS_Q_MOD_CFG;

/*!
  \brief QoS Modify QOS Sub interface to Port configuration structure
 */
typedef struct qos_mod_subif_port_cfg{
	char						ifname[PPA_IF_NAME_SIZE];/*!< Interface name on which the Queue is modified*/
	uint32_t 					port_id;/*!< Portid*/
	int32_t						priority_level; /*!< Queue Priority or Precedence. Start from 1-16, with 1 as highest priority */
	int32_t						weight; /*!< WFQ Weight */
	uint32_t 					flags;/*!< Flags for future use*/

} QOS_MOD_SUBIF_PORT_CFG;


/*!
  \brief PPA API QoS Add Shaper Configuration structure
 */
typedef struct ppa_qos_add_shaper_cfg {
	PPA_QOS_SHAPER_MODE       mode; /*!< Mode of Token Bucket shaper */
	uint32_t		enable; /*!< Enable for Shaper */
	uint32_t                cir; /*!< Committed Information Rate in bytes/s */
	uint32_t                cbs; /*!< Committed Burst Size in bytes */
	uint32_t                pir; /*!< Peak Information Rate in bytes/s */
	uint32_t                pbs; /*!< Peak Burst Size */
	uint32_t                flags; /*!< Flags define which shapers are enabled
					 - QOS_SHAPER_F_PIR
					 - QOS_SHAPER_F_CIR */
	uint32_t 	phys_shaperid;/*!< Physical Queue id of Queue that is added*/
#ifdef CONFIG_PPA_PUMA7
	char                   ifname[PPA_IF_NAME_SIZE];/*!< Interface name on which the shaper is created*/
#endif
} PPA_QOS_ADD_SHAPER_CFG;

/*!
  \brief PPA API QoS Add Queue Configuration structure
 */
typedef struct ppa_qos_add_queue_cfg {
	char		tc_map[MAX_TC_NUM];/*!< Which all Traffic Class(es) map to this Queue  */
	uint8_t		tc_no; /*!< Number of Traffic Class(es) map to this Queue */
	uint8_t 	intfId_en;/*!<Enable/Disable for flow Id + tc bits used for VAP's & Vlan interfaces*/
	uint16_t	intfId;/*!< flow Id + tc bits used for VAP's & Vlan interfaces */
	uint32_t	portid;/*!< PORT ID */
	int32_t		weight; /*!< WFQ Weight */
	int32_t		priority; /*!< Queue Priority or Precedence. Start from 1-16, with 1 as highest priority */
	int32_t		qlen; /*!< Length of Queue in bytes */
	PPA_QOS_QSCHED_MODE        q_type; /*!< QoS scheduler mode - Priority, WFQ */
	uint32_t 	queue_id;/*!< Physical Queue id of Queue that is added*/
	PPA_QOS_DROP_CFG	drop; /*!< Queue Drop Properties */
} PPA_QOS_ADD_QUEUE_CFG;

/*!
  \brief PPA API QoS Modify Queue Configuration structure
 */
typedef struct ppa_qos_mod_queue_cfg {
	uint32_t		enable; /*!< Whether Queue is enabled */
	int32_t			weight; /*!< WFQ Weight */
	int32_t			priority; /*!< Queue Priority or Precedence. Start from 1-16, with 1 as highest priority */
	uint32_t	portid;/*!< PORT ID */
	PPA_QOS_QSCHED_MODE        q_type; /*!< QoS scheduler mode - Priority, WFQ */
	int32_t			qlen; /*!< Length of Queue in bytes */
	uint32_t		queue_id; /*!< Physical Queue id of Queue being modified*/
	uint32_t		flags; /*!< Flags for future use*/
	PPA_QOS_DROP_CFG	drop; /*!< Queue Drop Properties */
} PPA_QOS_MOD_QUEUE_CFG;


#define PPA_QOS_MAX_IF_PER_INGGRP   20
#define PPA_NUM_INGRESS_GROUPS 		PPA_QOS_INGGRP_MAX
#define PPA_INGGRP_INVALID(g) 		((g < PPA_QOS_INGGRP0) ||(g >= PPA_QOS_INGGRP_MAX))
#define PPA_INGGRP_VALID(g) 		(!PPA_INGGRP_INVALID(g))


/*!
  \brief PPA API QoS Ingress Group structure
 */
typedef struct ppa_qos_inggrp_cfg {
	PPA_IFNAME ifname[PPA_IF_NAME_SIZE];/*!< Ingress Interface name corresponding to a Ingress QoS group*/
	PPA_QOS_INGGRP ingress_group;/*!< Ingress QoS Group*/
	uint16_t flowId;/*!< FlowId value for a particular ingress group*/
	uint8_t flowId_en;/*!< FlowId enable/disable*/
	uint8_t enc;/*!< Encrytption bit used to select particular ingress group*/
	uint8_t dec;/*!< Decrytption bit used to select particular ingress group*/
	uint8_t mpe1;/*!< MPE1 bit used to select particular ingress group*/
	uint8_t mpe2;/*!< MPe2 bit used to select particular ingress group*/
	uint16_t tc;/*!< Traffic class used to select queue in a particular ingress group*/
	uint32_t ep;/*!< Egress port corresponding to a particular ingress flow*/
	uint32_t flags;/*!< Flags for Future use*/
}PPA_QOS_INGGRP_CFG;

/*!
  \brief PPA API Common QoS Queue Configuration structure for ADD/MODIFY/DEL operations
 */
typedef struct {
	uint32_t        enable; /*!< Whether Queue is enabled */
	uint32_t        status; /*!< Operational status of the queue. Only
				  valid on GET */
	char            name[MAX_Q_NAME_LEN]; /*!< Name or Alias of the
						queue, if any */
	uint32_t        owner; /*<!  Enumerated value of who is doing the operation.
				 Possible owners can be: TR-069, Web GUI, CLI, System, BaseRules */
	uint32_t        flags; /*<! Following flags can be kept per
				 filter structure -
				 - QOS_Q_F_MODIFIED : Modified after being originally added
				 - QOS_Q_F_MODIFIED_OTHER : Modified by an entity other than the owner
				 - QOS_Q_F_HW     : Set if this Q is in HW
				 - QOS_Q_F_INGRESS  : This queue is applied to ingress from the interface */
	uint32_t        queue_id; /*!< Queue Id for other operations */
	char	        tc_map[MAX_TC_NUM]; /*!< Which all Traffic Class(es) map to this Queue */
	uint8_t		tc_no; /*!< Number of Traffic Class(es) map to this Queue */
	/* ?? What about additional qselectors possible in GRX350 */
	int32_t         qlen; /*!< Length of Queue in bytes */
	int32_t         weight; /*!< WFQ Weight */
	int32_t         priority; /*!< Queue Priority or Precedence. Start from 1-16, with 1 as highest priority */
	PPA_QOS_DROP_CFG  drop; /*!< Queue Drop Properties */
	PPA_QOS_QSCHED_MODE        sched; /*!< QoS scheduler mode - Priority, WFQ */
	PPA_QOS_SHAPER_CFG    shaper; /*!< Shaper Configuration */
} PPA_QOS_QUEUE_CFG;


/*!
  \brief PPA API Engine Info Configuration structure
 */
typedef struct {
	uint32_t engine_id; /* to be alloted by engine selector, es can create and pass this id to engine on first invoke, Id can be allotted from enum engines_t */
	int32_t (*init) (PPA_QOS_MODULE_TYPE); /* Callback function to initialize the engine*/
	int32_t (*fini) (PPA_QOS_MODULE_TYPE); /* Callback function to un-initialize the engine*/
	int32_t (*queue_add) (char *, PPA_QOS_QUEUE_CFG *); /* Callback function to add a queue for the given interface in the engine*/
	int32_t (*queue_modify) (char *, PPA_QOS_QUEUE_CFG *); /* Callback function to modify a queue for the given interface in the engine*/
	int32_t (*queue_delete) (char *, PPA_QOS_QUEUE_CFG *); /* Callback function to delete a queue for the given interface in the engine*/
	int32_t (*class_add) (PPA_QOS_QUEUE_CFG *); /* Callback function to add a classifier for the given interface in the engine*/
	int32_t (*class_modify) (PPA_QOS_QUEUE_CFG *); /* Callback function to modify a classifier for the given interface in the engine*/
	int32_t (*class_delete) (PPA_QOS_QUEUE_CFG *); /* Callback function to delete a classifier for the given interface in the engine*/
	//Callback for port shape
	PPA_QOS_ENG_CAP engine_capab; /* engine's capabilities */
	PPA_QOS_RESOURCE used_resource; /* Used resource to achieve the functionality. //each engine shall provide its capabilities and resources needed for that, so that engine selector can use this as well as some other info like number of sessions handeled by a particular resource at present. eg switch can do queueing in hardware and sw engine can do the same using CPU. */
}PPA_CMD_QOS_ENGINE_INFO;

typedef PPA_QOS_SHAPER_CFG PPA_CMD_SHAPER_INFO;
#if defined(CONFIG_LTQ_PPA_HAL_SELECTOR)
typedef struct {
	uint8_t hop_limit; 		/*!< PPA ip6hdr hop limit*/
	uint32_t	saddr[4];	/*!< PPA ip6hdr src address*/
	uint32_t    daddr[4];	/*!< PPA ip6hdr dst address*/
} PPA_IP6HDR;

typedef struct {
	uint32_t saddr;		/*!< PPA ip4hdr src address*/
	uint32_t daddr;		/*!< PPA ip4hdr src address*/
} PPA_IP4HDR;


#if defined(CONFIG_LTQ_PPA_MPE_IP97) && CONFIG_LTQ_PPA_MPE_IP97
#define PPA_IPSEC_NOT_ADDED                -1
#define PPA_IPSEC_EXISTS                   0
#define PPA_IPSEC_ADDED                    1

#define  IP_PROTO_ESP      50
#define	 ESP_HEADER	   73
typedef struct {
	PPA_XFRM_STATE * inbound;
	PPA_XFRM_STATE * outbound;
	sa_direction dir;
	uint32_t  routeindex;
#if 1
	uint32_t  inbound_pkt_cnt;
	uint32_t  inbound_byte_cnt;
	uint32_t  outbound_pkt_cnt;
	uint32_t  outbound_byte_cnt;
#endif
} PPA_IPSEC_INFO;
#endif


typedef union {
	PPA_IP4HDR		ip4_hdr;	/*!< PPA ip4 hdr*/
	PPA_IP6HDR		ip6_hdr;	/*!< PPA ip6 hdr*/
#if defined(L2TP_CONFIG) && L2TP_CONFIG
	PPA_L2TP_INFO	l2tp_hdr;	/*!< PPA l2tp hdr*/
#endif
#if defined(CAP_WAP_CONFIG) && CAP_WAP_CONFIG
	PPA_CMD_CAPWAP_INFO	capwap_hdr;	/*!< PPA capwap hdr*/
#endif

#if defined(CONFIG_LTQ_PPA_MPE_IP97) && CONFIG_LTQ_PPA_MPE_IP97
	PPA_IPSEC_INFO	ipsec_hdr;	/*!< PPA ipsec hdr*/
#endif

} ppa_tunnel_info;

typedef struct {
	int32_t		tunnel_type; 	/*!< PPA tunnel type*/
	ppa_tunnel_info	tunnel_info;	/*!< PPA tunnel info*/
	void	       *hal_buffer;	/*!< PPA hal buffer*/
} ppa_tunnel_entry;

typedef struct{
	uint16_t enabled;   /*!< Entry is valid*/
	uint16_t f_ipv6; 	/*!< PPA flag ipv6*/
	IP_ADDR srcip;	/*!< PPA source ip*/
	IP_ADDR dstip;	/*!< PPA destination ip*/
	uint32_t srcport;	/*!< PPA source port*/
	uint32_t dstport;	/*!< PPA destination port*/
	uint16_t aggr_mtu;	/*!< PPA aggrate mtu*/
	uint32_t timeout;	/*!< PPA timeout*/
	uint16_t session_uid[2];	/*!< PPA session id*/
} ppa_lro_entry;
#endif

/*
 * ####################################
 *             Declaration
 * ####################################
 */

#ifdef __KERNEL__
#ifdef NO_DOXY

#ifdef CONFIG_LTQ_PORT_MIRROR
extern struct net_device * (*get_mirror_netdev)(void);
extern uint32_t (*is_device_type_wireless)(void);
#define SKB_MIRROR_FLAG  0x2000
#endif

#define ENUM_STRING(x)   #x
void ppa_subsystem_id(uint32_t *,
		uint32_t *,
		uint32_t *,
		uint32_t *,
		uint32_t *,
		uint32_t *,
		uint32_t *,
		uint32_t *);

void ppa_get_api_id(uint32_t *,
		uint32_t *,
		uint32_t *,
		uint32_t *,
		uint32_t *,
		uint32_t *,
		uint32_t *);


int32_t ppa_init(PPA_INIT_INFO *, uint32_t);
void ppa_exit(void);

int32_t ppa_enable(uint32_t, uint32_t, uint32_t);
int32_t ppa_get_status(uint32_t *, uint32_t *, uint32_t);

#if defined(MIB_MODE_ENABLE) && MIB_MODE_ENABLE
int32_t ppa_set_mib_mode(uint8_t );
int32_t ppa_get_mib_mode(uint8_t* );
#endif
int32_t ppa_session_accel(PPA_SESSION *p_session, uint8_t enable);
int32_t ppa_get_ct_stats(PPA_SESSION *p_session, PPA_CT_COUNTER *pCtCounter);

int32_t ppa_session_add(PPA_BUF *, PPA_SESSION *, uint32_t);
int32_t ppa_session_modify(PPA_SESSION *, PPA_SESSION_EXTRA *, uint32_t);
int32_t ppa_session_get(PPA_SESSION ***, PPA_SESSION_EXTRA **, int32_t *, uint32_t);

int32_t ppa_mc_group_update(PPA_MC_GROUP *, uint32_t);
int32_t ppa_mc_group_get(IP_ADDR_C, IP_ADDR_C, PPA_MC_GROUP *, uint32_t);
int32_t ppa_mc_entry_modify(IP_ADDR_C,IP_ADDR_C, PPA_MC_GROUP *, PPA_SESSION_EXTRA *, uint32_t);
int32_t ppa_mc_entry_get(IP_ADDR_C, IP_ADDR_C, PPA_SESSION_EXTRA *, uint32_t);

void ppa_pitem_refcnt_inc(PPA_BUF *ppa_buf);
void ppa_pitem_refcnt_dec(PPA_BUF *ppa_buf);
#if defined(CONFIG_LTQ_PPA_MPE_IP97)
int32_t ppa_session_ipsec_add(PPA_XFRM_STATE *ppa_x, sa_direction dir);
int32_t ppa_session_ipsec_delete(PPA_XFRM_STATE *ppa_x);
#endif

#if defined(RTP_SAMPLING_ENABLE) && RTP_SAMPLING_ENABLE
int32_t ppa_mc_entry_rtp_get(IP_ADDR_C, IP_ADDR_C, uint8_t*);
int32_t ppa_mc_entry_rtp_set(PPA_MC_GROUP*);
#endif

#if defined(CAP_WAP_CONFIG) && CAP_WAP_CONFIG
int32_t ppa_capwap_update(PPA_CMD_CAPWAP_INFO *);
int32_t ppa_capwap_delete(PPA_CMD_CAPWAP_INFO *);
#endif

int32_t ppa_multicast_pkt_srcif_add(PPA_BUF *, PPA_NETIF *);

#if defined(CONFIG_LTQ_PPA_GRX500) && CONFIG_LTQ_PPA_GRX500
int32_t ppa_add_class_rule(PPA_CLASS_RULE *rule);
int32_t ppa_mod_class_rule(PPA_CLASS_RULE *rule);
int32_t ppa_del_class_rule(PPA_CLASS_RULE *rule);
int32_t ppa_get_class_rule(PPA_CLASS_RULE *rule);

int32_t ppa_set_qos_meter(PPA_QOS_METER_CFG *meter_cfg);
int32_t ppa_set_queue_threshold(PPA_QOS_QUEUE_THRESHOLD_CFG *queue_thr_cfg);
#endif

int32_t ppa_inactivity_status(PPA_U_SESSION *);
int32_t ppa_set_session_inactivity(PPA_U_SESSION *, int32_t);

int32_t ppa_bridge_entry_add(uint8_t *, PPA_NETIF *, PPA_NETIF *, uint32_t);
int32_t ppa_bridge_entry_delete(uint8_t *, PPA_NETIF *, uint32_t);
int32_t ppa_bridge_entry_delete_all(uint32_t f_enable);
int32_t ppa_bridge_entry_hit_time(uint8_t *, PPA_NETIF *, uint32_t *);
int32_t ppa_bridge_entry_inactivity_status(uint8_t *, PPA_NETIF *);
int32_t ppa_set_bridge_entry_timeout(uint8_t *, PPA_NETIF *, uint32_t);
int32_t ppa_hook_bridge_enable(uint32_t f_enable, uint32_t flags);
int32_t ppa_hook_get_bridge_status(uint32_t *f_enable, uint32_t flags);

int32_t ppa_set_bridge_if_vlan_config(PPA_NETIF *, PPA_VLAN_TAG_CTRL *, PPA_VLAN_CFG *, uint32_t);
int32_t ppa_get_bridge_if_vlan_config(PPA_NETIF *, PPA_VLAN_TAG_CTRL *, PPA_VLAN_CFG *, uint32_t);
int32_t ppa_vlan_filter_add(PPA_VLAN_MATCH_FIELD *, PPA_VLAN_INFO *, uint32_t);
int32_t ppa_vlan_filter_del(PPA_VLAN_MATCH_FIELD *, PPA_VLAN_INFO *, uint32_t);
int32_t ppa_vlan_filter_get_all(int32_t *, PPA_VLAN_FILTER_CONFIG *, uint32_t);
int32_t ppa_vlan_filter_del_all(uint32_t);

int32_t ppa_get_if_stats(PPA_IFNAME *, PPA_IF_STATS *, uint32_t);
int32_t ppa_get_accel_stats(PPA_IFNAME *, PPA_ACCEL_STATS *, uint32_t);
#if defined(CONFIG_LTQ_PPA_IF_MIB) && CONFIG_LTQ_PPA_IF_MIB
int32_t ppa_get_netif_accel_stats(PPA_IFNAME *, PPA_NETIF_ACCEL_STATS *, uint32_t);
#endif

int32_t ppa_hook_set_ppe_fastpath_enable(uint32_t f_enable, uint32_t flags);
int32_t ppa_hook_get_ppe_fastpath_enable(uint32_t *f_enable, uint32_t flags);

int32_t ppa_set_if_mac_address(PPA_IFNAME *, uint8_t *, uint32_t);
int32_t ppa_get_if_mac_address(PPA_IFNAME *, uint8_t *, uint32_t);

int32_t ppa_add_if(PPA_IFINFO *, uint32_t);
int32_t ppa_del_if(PPA_IFINFO *, uint32_t);
int32_t ppa_get_if(int32_t *, PPA_IFINFO **, uint32_t);
#if defined(CONFIG_PPA_API_DIRECTCONNECT) && CONFIG_PPA_API_DIRECTCONNECT
int32_t ppa_disconn_if(PPA_NETIF *, PPA_DP_SUBIF *, uint8_t *, uint32_t);
#if IS_ENABLED(CONFIG_LTQ_PPA_QOS) && IS_ENABLED(WMM_QOS_CONFIG)
int32_t ppa_register_for_qos_class2prio(int32_t , struct net_device *,PPA_QOS_CLASS2PRIO_CB  , uint32_t );
#endif
#endif

int32_t ppa_hook_wan_mii0_vlan_range_add(PPA_VLAN_RANGE *, uint32_t);
int32_t ppa_hook_wan_mii0_vlan_range_del(PPA_VLAN_RANGE *, int32_t);
int32_t ppa_hook_wan_mii0_vlan_ranges_get(int32_t *, PPA_VLAN_RANGE *, uint32_t);

int32_t ppa_get_max_entries(PPA_MAX_ENTRY_INFO *max_entry, uint32_t flags);
int32_t ppa_ip_comare( PPA_IPADDR ip1, PPA_IPADDR ip2, uint32_t flag );
int32_t ppa_zero_ip( PPA_IPADDR ip);
int32_t ppa_ip_sprintf( char *buf, PPA_IPADDR ip, uint32_t flag);
extern uint32_t g_ppa_ppa_mtu;
extern uint32_t g_ppa_min_hits;
extern volatile u_int8_t g_ppe_fastpath_enabled;
#endif //NO_DOXY

#endif //end of  __KERNEL__

#ifdef __KERNEL__
#include <net/ppa_hook.h>
#endif

#endif  //   __PPA_API_H__20081031_1913__
