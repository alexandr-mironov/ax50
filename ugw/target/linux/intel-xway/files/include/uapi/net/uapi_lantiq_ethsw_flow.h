#ifndef _LANTIQ_UAPI_ETHSW_FLOW_H_
#define _LANTIQ_UAPI_ETHSW_FLOW_H_

/* IOCTL MAGIC */
#define IFX_FLOW_MAGIC ('F')

/** Parameter to delete a rule from the packet classification engine.
    Used by \ref IFX_FLOW_PCE_RULE_DELETE. */
typedef struct
{
   /** Action Index in the Packet Classification Engine.
       It corresponds to the table rule index. */
   u32  nIndex;
}IFX_FLOW_PCE_ruleDelete_t;


/** Register access parameter to directly read or write switch
    internal registers.
    Used by \ref IFX_FLOW_REGISTER_SET and \ref IFX_FLOW_REGISTER_GET. */
typedef struct
{
   /** Register Address Offset for read or write access. */
   u16  nRegAddr;
   /** Value to write to or read from 'nRegAddr'. */
   u16  nData;
}IFX_FLOW_register_t;

/** Rule selection for IPv4/IPv6.
    Used by \ref IFX_FLOW_PCE_pattern_t. */
typedef enum
{
   /** Rule Pattern for IP selection disabled. */
   IFX_FLOW_PCE_IP_DISABLED     = 0,
   /** Rule Pattern for IPv4. */
   IFX_FLOW_PCE_IP_V4   = 1,
   /** Rule Pattern for IPv6. */
   IFX_FLOW_PCE_IP_V6   = 2
}IFX_FLOW_PCE_IP_t;

/** IGMP Snooping Control.
    Used by \ref IFX_FLOW_PCE_action_t. */
typedef enum
{
   /** Disabled. IGMP Snooping is disabled. */
   IFX_FLOW_PCE_ACTION_IGMP_SNOOP_DISABLE       = 0,
   /** Default. Regular Packet. No IGMP Snooping action required. */
   IFX_FLOW_PCE_ACTION_IGMP_SNOOP_REGULAR       = 1,
   /** IGMP Report/Join Message. */
   IFX_FLOW_PCE_ACTION_IGMP_SNOOP_REPORT        = 2,
   /** IGMP Leave Message. */
   IFX_FLOW_PCE_ACTION_IGMP_SNOOP_LEAVE = 3,
   /**  Router Solicitation/Advertisement message. */
   IFX_FLOW_PCE_ACTION_IGMP_SNOOP_AD    = 4,
   /** IGMP Query Message. */
   IFX_FLOW_PCE_ACTION_IGMP_SNOOP_QUERY = 5,
   /** IGMP Group Specific Query Message. */
   IFX_FLOW_PCE_ACTION_IGMP_SNOOP_QUERY_GROUP   = 6,
   /** IGMP General Query message without Router Solicitation. */
   IFX_FLOW_PCE_ACTION_IGMP_SNOOP_QUERY_NO_ROUTER = 7
}IFX_FLOW_PCE_ActionIGMP_Snoop_t;

/** MAC Address Learning control.
    Used by \ref IFX_FLOW_PCE_action_t. */
typedef enum
{
   /** MAC Address Learning action is disabled. MAC address learning is
       not influenced by this rule. */
   IFX_FLOW_PCE_ACTION_LEARNING_DISABLE = 0,
   /** Learning is based on the forwarding decision. If the packet is discarded,
       the address is not learned. If the packet is forwarded to any egress port,
       the address is learned. */
   IFX_FLOW_PCE_ACTION_LEARNING_REGULAR = 1,
   /** Force No Learning. The address is not learned; forwarding decision
       ignored. */
   IFX_FLOW_PCE_ACTION_LEARNING_FORCE_NOT       = 2,
   /** Force Learning. The address is learned, the forwarding decision ignored.
       Note: The MAC Learning Control signals delivered to Port-Map filtering
       and combined with Final Forwarding Decision. The result is used as a
       feedback for MAC Address learning in the Bridging Table. */
   IFX_FLOW_PCE_ACTION_LEARNING_FORCE   = 3
}IFX_FLOW_PCE_ActionLearning_t;

/** Flow Meter Assignment control.
    Used by \ref IFX_FLOW_PCE_action_t. */
typedef enum
{
   /** Action Disable. */
   IFX_FLOW_PCE_ACTION_METER_DISABLE    = 0,
   /** Action Enable.
       The action is enabled but no dedicated metering instance is assigned by the rule. */
   IFX_FLOW_PCE_ACTION_METER_REGULAR    = 1,
   /** Action Enable. Assign one meter instance as given in parameter "nMeterId". */
   IFX_FLOW_PCE_ACTION_METER_1  = 2,
   /** Action Enable. Assign pair of meter instances.
       These instances are "nMeterId" and the next following meter instance index. */
   IFX_FLOW_PCE_ACTION_METER_1_2        = 3
}IFX_FLOW_PCE_ActionMeter_t;

/** Traffic Class Action Selector.
    Used by \ref IFX_FLOW_PCE_action_t. */
typedef enum
{
   /** Disabled. Traffic class action is disabled. */
   IFX_FLOW_PCE_ACTION_TRAFFIC_CLASS_DISABLE    = 0,
   /** Regular Class. Traffic class action is enabled and the CoS
       classification traffic class is used. */
   IFX_FLOW_PCE_ACTION_TRAFFIC_CLASS_REGULAR    = 1,
   /** Alternative Class. Traffic class action is enabled and the
       class of the 'nTrafficClassAlter' field is used. */
   IFX_FLOW_PCE_ACTION_TRAFFIC_CLASS_ALTERNATIVE        = 2,
}IFX_FLOW_PCE_ActionTrafficClass_t;

/** Interrupt Control Action Selector.
    Used by \ref IFX_FLOW_PCE_action_t. */
typedef enum
{
   /** Disabled. Interrupt Control Action is disabled for this rule. */
   IFX_FLOW_PCE_ACTION_IRQ_DISABLE      = 0,
   /** Regular Packet. The Interrupt Control Action is enabled, the packet is
       treated as a regular packet and no interrupt event is generated. */
   IFX_FLOW_PCE_ACTION_IRQ_REGULAR      = 1,
   /** Interrupt Event. The Interrupt Control Action is enabled and an
       interrupt event is generated. */
   IFX_FLOW_PCE_ACTION_IRQ_EVENT        = 2
}IFX_FLOW_PCE_ActionIrq_t;

/** Cross State Action Selector.
    Used by \ref IFX_FLOW_PCE_action_t. */
typedef enum
{
   /** Disable. The Cross State Action is disabled. */
   IFX_FLOW_PCE_ACTION_CROSS_STATE_DISABLE      = 0,
   /** Regular Packet. The Cross State Action is enabled and the packet is
       treated as a non-Cross-State packet (regular packet). Therefore it does
       not ignore Port-State filtering rules. */
   IFX_FLOW_PCE_ACTION_CROSS_STATE_REGULAR      = 1,
   /** Cross-State packet. The Cross State Action is enabled and the packet is
       treated as a Cross-State packet. It ignores the Port-State
       filtering rules. */
   IFX_FLOW_PCE_ACTION_CROSS_STATE_CROSS        = 2
}IFX_FLOW_PCE_ActionCrossState_t;

/** Critical Frame Action Selector.
    Used by \ref IFX_FLOW_PCE_action_t. */
typedef enum
{
   /** Disable. The Critical Frame Action is disabled. */
   IFX_FLOW_PCE_ACTION_CRITICAL_FRAME_DISABLE   = 0,
   /** Regular Packet. The Critical Frame Action is enabled and the packet is
       treated as a non-Critical Frame. */
   IFX_FLOW_PCE_ACTION_CRITICAL_FRAME_REGULAR   = 1,
   /** Critical Packet. The Critical Frame Action is enabled and the packet is
       treated as a Critical Frame. */
   IFX_FLOW_PCE_ACTION_CRITICAL_FRAME_CRITICAL  = 2
}IFX_FLOW_PCE_ActionCriticalFrame_t;

/** Timestamp Action Selector.
    Used by \ref IFX_FLOW_PCE_action_t. */
typedef enum
{
   /** Disable. Timestamp Action is disabled for this rule. */
   IFX_FLOW_PCE_ACTION_TIMESTAMP_DISABLE        = 0,
   /** Regular Packet. The Timestamp Action is enabled for this rule.
       The packet is treated as a regular packet and no timing information
       is stored. */
   IFX_FLOW_PCE_ACTION_TIMESTAMP_REGULAR        = 1,
   /** Receive/Transmit Timing packet. Ingress and Egress Timestamps for
       this packet should be stored. */
   IFX_FLOW_PCE_ACTION_TIMESTAMP_STORED = 2
}IFX_FLOW_PCE_ActionTimestamp_t;

/** Forwarding Group Action Selector.
    This flow table action and the 'bFlowID_Action' action
    can be used exclusively.
    Used by \ref IFX_FLOW_PCE_action_t. */
typedef enum
{
   /** Disable. Forwarding Group Action is disabled. */
   IFX_FLOW_PCE_ACTION_PORTMAP_DISABLE  = 0,
   /** Regular Packet. Forwarding Action enabled. Select Default
       Port-Map (result of Default Forwarding Classification). */
   IFX_FLOW_PCE_ACTION_PORTMAP_REGULAR  = 1,
   /** Discard. Discard the packets. */
   IFX_FLOW_PCE_ACTION_PORTMAP_DISCARD  = 2,
   /** Forward to the CPU port. This requires that the CPU port is previously
       set by calling \ref IFX_ETHSW_CPU_PORT_CFG_SET. */
   IFX_FLOW_PCE_ACTION_PORTMAP_CPU      = 3,
   /** Forward to a portmap, selected by the parameter 'nForwardPortMap'.
       Please note that this feature is not supported by all
       hardware platforms. */
   IFX_FLOW_PCE_ACTION_PORTMAP_ALTERNATIVE      = 4,
   /** The packet is treated as Multicast Router
       Solicitation/Advertisement or Query packet. */
   IFX_FLOW_PCE_ACTION_PORTMAP_MULTICAST_ROUTER = 5,
   /** The packet is interpreted as Multicast packet and learned in the
       multicast group table. */
   IFX_FLOW_PCE_ACTION_PORTMAP_MULTICAST_HW_TABLE = 6,
   /** The CTAG VLAN portmap classification result is replaced by the
       portmap parameter 'nForwardPortMap'. All other classification
       results stay unchanged and will be combined together with
       the overwritten portmap. */
   IFX_FLOW_PCE_ACTION_PORTMAP_ALTERNATIVE_VLAN = 7,
   /** Add STAG VLAN portmap 'nForwardPortMap' to the overall portmap
       classification result (AND'ed with the portmap). */
   IFX_FLOW_PCE_ACTION_PORTMAP_ALTERNATIVE_STAG_VLAN    = 8
}IFX_FLOW_PCE_ActionPortmap_t;

/** VLAN Group Action Selector.
    Used by \ref IFX_FLOW_PCE_action_t. */
typedef enum
{
   /** Disabled. The VLAN Action is disabled. */
   IFX_FLOW_PCE_ACTION_VLAN_DISABLE     = 0,
   /** Regular VLAN. VLAN Action enabled. Select Default VLAN ID. */
   IFX_FLOW_PCE_ACTION_VLAN_REGULAR     = 1,
   /** Alternative VLAN. VLAN Action enabled.
       Select Alternative VLAN as configured in 'nVLAN_Id'
       or 'nSVLAN_Id'. For CTAG VLAN it requires that this VLAN ID
       is configured by calling
       \ref IFX_ETHSW_VLAN_ID_CREATE in advance.
       This additional call is not required for STAG VLAN. */
   IFX_FLOW_PCE_ACTION_VLAN_ALTERNATIVE = 2
}IFX_FLOW_PCE_ActionVLAN_t;

/** Cross VLAN Action Selector.
    Used by \ref IFX_FLOW_PCE_action_t. */
typedef enum
{
   /** Disabled. The Cross VLAN Action is disabled. */
   IFX_FLOW_PCE_ACTION_CROSS_VLAN_DISABLE       = 0,
   /** Regular VLAN Packet. Do not ignore VLAN filtering rules. */
   IFX_FLOW_PCE_ACTION_CROSS_VLAN_REGULAR       = 1,
   /** Cross-VLAN packet. Ignore VLAN filtering  rules.*/
   IFX_FLOW_PCE_ACTION_CROSS_VLAN_CROSS = 2
}IFX_FLOW_PCE_ActionCrossVLAN_t;


/** Packet Classification Engine Pattern Configuration.
    Used by \ref IFX_FLOW_PCE_rule_t. */
typedef struct
{
   /** Index */
   int  nIndex;

   /** Index is used (enabled) or set to unused (disabled) */
   ltq_bool_t   bEnable;

   /** Port ID used */
   ltq_bool_t   bPortIdEnable;
   /** Port ID */
   u8   nPortId;

   /** DSCP value used */
   ltq_bool_t   bDSCP_Enable;
   /** DSCP value */
   u8           nDSCP;

   /** CTAG VLAN PCP value used */
   ltq_bool_t   bPCP_Enable;
   /** CTAG VLAN PCP value */
   u8           nPCP;

   /** STAG VLAN PCP/DEI value used */
   ltq_bool_t    bSTAG_PCP_DEI_Enable;
   /** STAG VLAN PCP value */
   u8           nSTAG_PCP_DEI;

   /** Packet length used */
   ltq_bool_t   bPktLngEnable;
   /** Packet length */
   u16  nPktLng;
   /** Packet length Range */
   u16          nPktLngRange;

   /** Destination MAC address used */
   ltq_bool_t   bMAC_DstEnable;
   /** Destination MAC address */
   u8           nMAC_Dst[6];
   /** Destination MAC address mask.
       Please clear the bits of the nibbles that are not marked out and set all other bits.
       The LSB bit represents the lowest data nibble, the next bit the next nibble,
       and so on. */
   u16  nMAC_DstMask;

   /** Source MAC address used */
   ltq_bool_t   bMAC_SrcEnable;
   /** Source MAC address */
   u8   nMAC_Src[6];
   /** Source MAC address mask.
       Please clear the bits of the nibbles that are not marked out and set all other bits.
       The LSB bit represents the lowest data nibble, the next bit the next nibble,
       and so on. */
   u16  nMAC_SrcMask;

   /** MSB Application field used */
   ltq_bool_t   bAppDataMSB_Enable;
   /** MSB Application field.
       The first 2 bytes of the packet content following the IP header
       for TCP/UDP packets (source port field), or the first 2 bytes of packet content
       following the Ethertype for non-IP packets. Any part of this
       content can be masked-out by a programmable bit
       mask 'nAppMaskRangeMSB'. */
   u16  nAppDataMSB;
   /** MSB Application mask/range selection.
       If set to LTQ_TRUE, the field 'nAppMaskRangeMSB' is used as a
       range parameter, otherwise it is used as a nibble mask field. */
   ltq_bool_t   bAppMaskRangeMSB_Select;
   /** MSB Application mask/range. When used as a range parameter,
       1 bit represents 1 nibble mask of the 'nAppDataMSB' field.
       Please clear the bits of the nibbles that are not marked out and set all other bits.
       The LSB bit represents the lowest data nibble, the next bit the next nibble,
       and so on. */
   u16  nAppMaskRangeMSB;

   /** LSB Application used */
   ltq_bool_t   bAppDataLSB_Enable;
   /** LSB Application field.
       The following 2 bytes of the packet behind the 'nAppDataMSB' field.
       This is the destination port field for TCP/UDP packets,
       or byte 3 and byte 4 of the packet content following the Ethertype
       for non-IP packets. Any part of this content can be masked-out
       by a programmable bit mask 'nAppMaskRangeLSB'. */
   u16  nAppDataLSB;
   /** LSB Application mask/range selection.
       If set to LTQ_TRUE, the field 'nAppMaskRangeLSB' is used as
       a range parameter, otherwise it is used as a nibble mask field. */
   ltq_bool_t   bAppMaskRangeLSB_Select;
   /** LSB Application mask/range. When used as a range parameter,
       1 bit represents 1 nibble mask of the 'nAppDataLSB' field.
       Please clear the bits of the nibbles that are not marked out and set all other bits.
       The LSB bit represents the lowest data nibble, the next bit the next nibble,
       and so on. */
   u16  nAppMaskRangeLSB;

   /** DIP Selection. */
   IFX_FLOW_PCE_IP_t    eDstIP_Select;
   /** DIP */
   IFX_ETHSW_IP_t       nDstIP;
   /** DIP Nibble Mask.
       1 bit represents 1 nibble mask of the 'nDstIP' field.
       Please clear the bits of the nibbles that are not marked out and set all other bits.
       The LSB bit represents the lowest data nibble, the next bit the next nibble,
       and so on. */
   u32  nDstIP_Mask;

   /** SIP Selection. */
   IFX_FLOW_PCE_IP_t    eSrcIP_Select;
   /** SIP */
   IFX_ETHSW_IP_t       nSrcIP;
   /** SIP Nibble Mask.
       1 bit represents 1 nibble mask of the 'nSrcIP' field.
       Please clear the bits of the nibbles that are not marked out and set all other bits.
       The LSB bit represents the lowest data nibble, the next bit the next nibble,
       and so on. */
   u32  nSrcIP_Mask;

   /** Ethertype used. */
   ltq_bool_t   bEtherTypeEnable;
   /** Ethertype */
   u16  nEtherType;
   /** Ethertype Mask.
       1 bit represents 1 nibble mask of the 'nEtherType' field.
       Please clear the bits of the nibbles that are not marked out and set all other bits.
       The LSB bit represents the lowest data nibble, the next bit the next nibble,
       and so on. */
   u16  nEtherTypeMask;

   /** IP protocol used */
   ltq_bool_t   bProtocolEnable;
   /** IP protocol */
   u8   nProtocol;
   /** IP protocol Mask.
       1 bit represents 1 nibble mask of the 'nProtocol' field.
       Please clear the bits of the nibbles that are not marked out and set all other bits.
       The LSB bit represents the lowest data nibble, the next bit the next nibble,
       and so on. */
   u8   nProtocolMask;

   /** PPPoE used. */
   ltq_bool_t   bSessionIdEnable;
   /** PPPoE */
   u16  nSessionId;

   /** VLAN ID used. */
   ltq_bool_t   bVid;
   /** VLAN ID */
   u16  nVid;
   /** STAG VLAN ID used. */
   ltq_bool_t   bSLAN_Vid;
   /** STAG VLAN ID */
   u16  nSLAN_Vid;
}IFX_FLOW_PCE_pattern_t;

/** Packet Classification Engine Action Configuration.
    Used by \ref IFX_FLOW_PCE_rule_t. */
typedef struct
{
   /** Action "Traffic Class" Group.
       Traffic class action enable */
   IFX_FLOW_PCE_ActionTrafficClass_t    eTrafficClassAction;
   /** Alternative Traffic class */
   u8   nTrafficClassAlternate;

   /** Action "IGMP Snooping" Group.
       IGMP Snooping control and enable. Please note that the 'nPortMapAction'
       configuration is ignored in case the IGMP snooping is enabled.
       Here, on read operations,
       'nPortMapAction = IFX_FLOW_PCE_ACTION_PORTMAP_DISABLE' is returned. */
   IFX_FLOW_PCE_ActionIGMP_Snoop_t      eSnoopingTypeAction;

   /** Action "Learning" Group.
       Learning action control and enable */
   IFX_FLOW_PCE_ActionLearning_t        eLearningAction;

   /** Action "Interrupt" Group.
       Interrupt action generate and enable */
   IFX_FLOW_PCE_ActionIrq_t     eIrqAction;

   /** Action "Cross State" Group.
       Cross state action control and enable */
   IFX_FLOW_PCE_ActionCrossState_t      eCrossStateAction;

   /** Action "Critical Frames" Group.
       Critical Frame action control and enable */
   IFX_FLOW_PCE_ActionCriticalFrame_t   eCritFrameAction;

   /** Action "Timestamp" Group. Time stamp action control and enable */
   IFX_FLOW_PCE_ActionTimestamp_t       eTimestampAction;

   /** Action "Forwarding" Group.
       Port map action enable. This port forwarding configuration is ignored
       in case the action "IGMP Snooping" is enabled via the
       parameter 'nSnoopingTypeAction'. */
   IFX_FLOW_PCE_ActionPortmap_t ePortMapAction;
   /** Target portmap for forwarded packets, only used if selected by
       'nPortMapAction'. Forwarding is done
       if 'nPortMapAction = IFX_FLOW_PCE_ACTION_PORTMAP_ALTERNATIVE'.
       Every bit in the portmap represents one port (port 0 = LSB bit). */
   u32  nForwardPortMap;

   /** Action "Remarking" Group. Remarking action enable */
   ltq_bool_t   bRemarkAction;
   /** CTAG VLAN PCP remarking enable.
       Remarking enabling means that remarking is possible in case
       the port configuration or metering enables remarking on that
       packet. Disabling remarking means that it is forced to
       not remarking this packet, independent of any port remarking of
       metering configuration. */
   ltq_bool_t   bRemarkPCP;
   /** STAG VLAN PCP remarking enable.
       Remarking enabling means that remarking is possible in case
       the port configuration or metering enables remarking on that
       packet. Disabling remarking means that it is forced to
       not remarking this packet, independent of any port remarking of
       metering configuration. */
   ltq_bool_t   bRemarkSTAG_PCP;
   /** STAG VLAN DEI remarking enable.
       Remarking enabling means that remarking is possible in case
       the port configuration or metering enables remarking on that
       packet. Disabling remarking means that it is forced to
       not remarking this packet, independent of any port remarking of
       metering configuration. */
   ltq_bool_t   bRemarkSTAG_DEI;
   /** DSCP remarking enable
       Remarking enabling means that remarking is possible in case
       the port configuration or metering enables remarking on that
       packet. Disabling remarking means that it is forced to
       not remarking this packet, independent of any port remarking of
       metering configuration. */
   ltq_bool_t   bRemarkDSCP;
   /** Class remarking enable
       Remarking enabling means that remarking is possible in case
       the port configuration or metering enables remarking on that
       packet. Disabling remarking means that it is forced to
       not remarking this packet, independent of any port remarking of
       metering configuration. */
   ltq_bool_t   bRemarkClass;

   /** Action "Meter" Group. Meter action control and enable.
       If metering action enabled, specified metering instance number
       overrules any other metering assignment.
       Up to two metering instances can be applied to a single packet. */
   IFX_FLOW_PCE_ActionMeter_t   eMeterAction;
   /** Meter ID */
   u8   nMeterId;

   /** Action "RMON" Group. RMON action enable */
   ltq_bool_t   bRMON_Action;
   /** Counter ID (The index starts counting from zero). */
   u8   nRMON_Id;

   /** Action "CTAG VLAN" Group. VLAN action enable */
   IFX_FLOW_PCE_ActionVLAN_t    eVLAN_Action;
   /** Alternative CTAG VLAN Id */
   u16  nVLAN_Id;

   /** Action "STAG VLAN" Group. VLAN action enable */
   IFX_FLOW_PCE_ActionVLAN_t    eSVLAN_Action;
   /** Alternative STAG VLAN Id */
   u16  nSVLAN_Id;
   /** Action "Cross VLAN" Group. Cross VLAN action enable */
   IFX_FLOW_PCE_ActionCrossVLAN_t       eVLAN_CrossAction;
                                /** Alternative FID */
   u8   nFId;
   /** Port BitMap Mux control */
        ltq_bool_t      bPortBitMapMuxControl;
        /** Trunking action enable  */
        ltq_bool_t      bPortTrunkAction;
        /**  Port Link Selection control */
        ltq_bool_t      bPortLinkSelection;
        /**  CVLAN Ignore control */
        ltq_bool_t      bCVLAN_Ignore_Control;
   /** Action "Flow ID".
       The Switch supports enhancing the egress packets by a device specific
       special tag header. This header contains detailed switch classification
       results. One header file is a 'Flow ID', which can be explicitly set as
       flow table action when hitting a table rule.
       If selected, the Flow ID is given by the parameter 'nFlowID'. */
   ltq_bool_t   bFlowID_Action;

   /** Flow ID */
   u16  nFlowID;
}IFX_FLOW_PCE_action_t;


/** Parameter to add/read a rule to/from the packet classification engine.
    Used by \ref IFX_FLOW_PCE_RULE_WRITE and \ref IFX_FLOW_PCE_RULE_READ. */
typedef struct
{
   /** Rule Pattern Part. */
   IFX_FLOW_PCE_pattern_t       pattern;
   /** Rule Action Part. */
   IFX_FLOW_PCE_action_t        action;
}IFX_FLOW_PCE_rule_t;

/*@}*/ /* FLOW_IOCTL_OAM */

/* -------------------------------------------------------------------------- */
/*                        IOCTL Command Definitions                           */
/* -------------------------------------------------------------------------- */

/** \addtogroup FLOW_IOCTL_DEBUG */
/*@{*/

/**
   Write to an internal register. The register offset defines which register to access in
   which table. This routine only accesses the M4599_PDI and
   the ETHSW_PDI of the switch. All PHY registers are accessed
   via \ref IFX_ETHSW_MDIO_DATA_WRITE and \ref IFX_ETHSW_MDIO_DATA_READ.
   Note that the switch API implementation checks whether the given address is
   inside the valid address range. It returns with an error in case an invalid
   address is given.

   \param IFX_FLOW_register_t Pointer to \ref IFX_FLOW_register_t.

   \remarks The function returns an error code in case an error occurs.
            The error code is described in \ref IFX_ETHSW_status_t.

   \return Return value as follows:
   - IFX_SUCCESS: if successful
   - An error code in case an error occurs
*/
#define IFX_FLOW_REGISTER_SET   _IOW(IFX_FLOW_MAGIC, 0x01, IFX_FLOW_register_t)

/*@}*/ /* FLOW_IOCTL_IRQ */

/** \addtogroup FLOW_IOCTL_CLASSUNIT */
/*@{*/

/**
   This command writes a rule pattern and action to the table of the packet
   classification engine. The pattern part describes the parameter to identify an
   incoming packet to which the dedicated actions should be applied.
   A rule can be read using the command \ref IFX_FLOW_PCE_RULE_READ.

   \param IFX_FLOW_PCE_rule_t Pointer to \ref IFX_FLOW_PCE_rule_t.

   \remarks The function returns an error code in case an error occurs.
            The error code is described in \ref IFX_ETHSW_status_t.

   \return Return value as follows:
   - IFX_SUCCESS: if successful
   - An error code in case an error occurs
*/
#define IFX_FLOW_PCE_RULE_WRITE _IOW(IFX_FLOW_MAGIC, 0x07, IFX_FLOW_PCE_rule_t)

/**
   This command deletes a complete rule from the packet classification engine.
   A delete operation is done on the rule of a dedicated index 'nIndex'.
   A rule can be written over using the command \ref IFX_FLOW_PCE_RULE_WRITE.

   \param IFX_FLOW_PCE_ruleDelete_t Pointer to \ref IFX_FLOW_PCE_ruleDelete_t.

   \remarks The function returns an error code in case an error occurs.
            The error code is described in \ref IFX_ETHSW_status_t.

   \return Return value as follows:
   - IFX_SUCCESS: if successful
   - An error code in case an error occurs
*/
#define IFX_FLOW_PCE_RULE_DELETE  _IOW(IFX_FLOW_MAGIC, 0x09, IFX_FLOW_PCE_ruleDelete_t)


#endif /* _LANTIQ_UAPI_ETHSW_FLOW_H_ */


