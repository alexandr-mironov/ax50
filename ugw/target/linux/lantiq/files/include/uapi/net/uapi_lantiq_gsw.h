#ifndef _LANTIQ_UAPI_GSW_H_
#define _LANTIQ_UAPI_GSW_H_
/*-----UAPI header file for lantiq_gsw.h-----*/


#include "gsw_types.h"
#define GSW_MAGIC ('E')

/* -------------------------------------------------------------------------- */
/*                 Structure and Enumeration Type Defintions                  */
/* -------------------------------------------------------------------------- */

/** \brief Ethernet flow control status.
    Used by \ref GSW_portCfg_t. */
typedef enum
{
   /** Automatic flow control mode selection through auto-negotiation. */
   GSW_FLOW_AUTO        = 0,
   /** Receive flow control only */
   GSW_FLOW_RX  = 1,
   /** Transmit flow control only */
   GSW_FLOW_TX  = 2,
   /** Receive and Transmit flow control */
   GSW_FLOW_RXTX        = 3,
   /** No flow control */
   GSW_FLOW_OFF = 4
} GSW_portFlow_t;


/** \brief Port Enable Type Selection.
    Used by \ref GSW_portCfg_t. */
typedef enum
{
   /** The port is disabled in both directions. */
   GSW_PORT_DISABLE     = 0,
   /** The port is enabled in both directions (ingress and egress). */
   GSW_PORT_ENABLE_RXTX = 1,
   /** The port is enabled in the receive (ingress) direction only. */
   GSW_PORT_ENABLE_RX   = 2,
   /** The port is enabled in the transmit (egress) direction only. */
   GSW_PORT_ENABLE_TX   = 3
} GSW_portEnable_t;

/** \brief Port Mirror Options.
    Used by \ref GSW_portCfg_t. */
typedef enum
{
   /** Mirror Feature is disabled. Normal port usage. */
   GSW_PORT_MONITOR_NONE        = 0,
   /** Port Ingress packets are mirrored to the monitor port. */
   GSW_PORT_MONITOR_RX  = 1,
   /** Port Egress packets are mirrored to the monitor port. */
   GSW_PORT_MONITOR_TX  = 2,
   /** Port Ingress and Egress packets are mirrored to the monitor port. */
   GSW_PORT_MONITOR_RXTX        = 3,
   /** Packet mirroring of 'unknown VLAN violation' frames. */
   GSW_PORT_MONITOR_VLAN_UNKNOWN          = 4,
   /** Packet mirroring of 'VLAN ingress or egress membership violation' frames. */
   GSW_PORT_MONITOR_VLAN_MEMBERSHIP       = 16,
   /** Packet mirroring of 'port state violation' frames. */
   GSW_PORT_MONITOR_PORT_STATE  = 32,
   /** Packet mirroring of 'MAC learning limit violation' frames. */
   GSW_PORT_MONITOR_LEARNING_LIMIT        = 64,
   /** Packet mirroring of 'port lock violation' frames. */
   GSW_PORT_MONITOR_PORT_LOCK   = 128
} GSW_portMonitor_t;

/** \brief Interface RMON Counter Mode - (FID, SUBID or FLOWID) Config - GSWIP-3.0 only.
    Used by \ref GSW_portCfg_t. */
typedef enum
{
   /** FID based Interface RMON counters Usage */
   GSW_IF_RMON_FID      = 0,
   /** Sub-Interface Id based Interface RMON counters Usage */
   GSW_IF_RMON_SUBID    = 1,
   /** Flow Id (LSB bits 3 to 0) based Interface RMON counters Usage */
   GSW_IF_RMON_FLOWID_LSB       = 2,
   /** Flow Id (MSB bits 7 to 4) based Interface RMON counters Usage */
   GSW_IF_RMON_FLOWID_MSB       = 3
} GSW_If_RMON_Mode_t;


/** \brief Port Configuration Parameters.
    Used by \ref GSW_PORT_CFG_GET and \ref GSW_PORT_CFG_SET. */
typedef struct
{
   /** Ethernet Port number (zero-based counting). The valid range is hardware
       dependent. An error code is delivered if the selected port is not
       available. */
   u8   nPortId;
   /** Enable Port (ingress only, egress only, both directions, or disabled).
       This parameter is used for Spanning Tree Protocol and 802.1X applications. */
   GSW_portEnable_t     eEnable;
   /** Drop unknown unicast packets.
       Do not send out unknown unicast packets on this port,
       if the boolean parameter is enabled. By default packets of this type
       are forwarded to this port. */
   ltq_bool_t   bUnicastUnknownDrop;
   /** Drop unknown multicast packets.
       Do not send out unknown multicast packets on this port,
       if boolean parameter is enabled. By default packets of this type
       are forwarded to this port.
       Some platforms also drop broadcast packets. */
   ltq_bool_t   bMulticastUnknownDrop;
   /** Drop reserved packet types
       (destination address from '01 80 C2 00 00 00' to
       '01 80 C2 00 00 2F') received on this port. */
   ltq_bool_t   bReservedPacketDrop;
   /** Drop Broadcast packets received on this port. By default packets of this
     type are forwarded to this port. */
   ltq_bool_t   bBroadcastDrop;
   /** Enables MAC address table aging.
       The MAC table entries learned on this port are removed after the
       aging time has expired.
       The aging time is a global parameter, common to all ports. */
   ltq_bool_t   bAging;
   /** MAC address table learning on the port specified by 'nPortId'.
       By default this parameter is always enabled. */
   ltq_bool_t   bLearning;
   /** Automatic MAC address table learning locking on the port specified
       by 'nPortId'.
       This parameter is only taken into account when 'bLearning' is enabled. */
   ltq_bool_t   bLearningMAC_PortLock;
   /** Automatic MAC address table learning limitation on this port.
       The learning functionality is disabled when the limit value is zero.
       The value 0xFFFF to allow unlimited learned address.
       This parameter is only taken into account when 'bLearning' is enabled. */
   u16 nLearningLimit;
   /** MAC spoofing detection. Identifies ingress packets that carry
       a MAC source address which was previously learned on a different ingress
       port (learned by MAC bridging table). This also applies to static added
       entries. Those violated packets could be accepted or discarded,
       depending on the global switch configuration 'bMAC_SpoofingAction'.
       This parameter is only taken into account when 'bLearning' is enabled. */
   ltq_bool_t   bMAC_SpoofingDetection;
   /** Port Flow Control Status. Enables the flow control function. */
   GSW_portFlow_t       eFlowCtrl;
   /** Port monitor feature. Allows forwarding of egress and/or ingress
       packets to the monitor port. If enabled, the monitor port gets
       a copy of the selected packet type. */
   GSW_portMonitor_t    ePortMonitor;
   /** Assign Interface RMON Counters for this Port - GSWIP-3.0 */
   ltq_bool_t   bIfCounters;
   /** Interface RMON Counters Start Index - GSWIP-3.0. 
       Value of (-1) denotes unassigned Interface Counters.
       Valid range : 0-255 available to be shared amongst ports in desired way*/
   int nIfCountStartIdx;
   /** Interface RMON Counters Mode - GSWIP-3.0 */
   GSW_If_RMON_Mode_t   eIfRMONmode;
} GSW_portCfg_t;

/** \brief Ethernet port speed mode.
    For certain generations of GSWIP, a port might support only a subset of the possible settings.
    Used by \ref GSW_portLinkCfg_t. */
typedef enum
{
   /** 10 Mbit/s */
   GSW_PORT_SPEED_10    = 10,
   /** 100 Mbit/s */
   GSW_PORT_SPEED_100   = 100,
   /** 200 Mbit/s */
   GSW_PORT_SPEED_200   = 200,
   /** 1000 Mbit/s */
   GSW_PORT_SPEED_1000  = 1000
} GSW_portSpeed_t;

/**
 \brief RMON Counters for individual Port.
 This structure contains the RMON counters of an Ethernet Switch Port.
    Used by \ref GSW_RMON_PORT_GET. */
typedef struct
{
   /** Ethernet Port number (zero-based counting). The valid range is hardware
       dependent. An error code is delivered if the selected port is not
       available. This parameter specifies for which MAC port the RMON
       counter is read. It has to be set by the application before
       calling \ref GSW_RMON_PORT_GET. */
   u8   nPortId;
   /** Receive Packet Count (only packets that are accepted and not discarded). */
   u32  nRxGoodPkts;
   /** Receive Unicast Packet Count. */
   u32  nRxUnicastPkts;
   /** Receive Broadcast Packet Count. */
   u32  nRxBroadcastPkts;
   /** Receive Multicast Packet Count. */
   u32  nRxMulticastPkts;
   /** Receive FCS Error Packet Count. */
   u32  nRxFCSErrorPkts;
   /** Receive Undersize Good Packet Count. */
   u32  nRxUnderSizeGoodPkts;
   /** Receive Oversize Good Packet Count. */
   u32  nRxOversizeGoodPkts;
   /** Receive Undersize Error Packet Count. */
   u32  nRxUnderSizeErrorPkts;
   /** Receive Good Pause Packet Count. */
   u32  nRxGoodPausePkts;
   /** Receive Oversize Error Packet Count. */
   u32  nRxOversizeErrorPkts;
   /** Receive Align Error Packet Count. */
   u32  nRxAlignErrorPkts;
   /** Filtered Packet Count. */
   u32  nRxFilteredPkts;
   /** Receive Size 64 Bytes Packet Count. */
   u32  nRx64BytePkts;
   /** Receive Size 65-127 Bytes Packet Count. */
   u32  nRx127BytePkts;
   /** Receive Size 128-255 Bytes Packet Count. */
   u32  nRx255BytePkts;
   /** Receive Size 256-511 Bytes Packet Count. */
   u32  nRx511BytePkts;
   /** Receive Size 512-1023 Bytes Packet Count. */
   u32  nRx1023BytePkts;
   /** Receive Size 1024-1522 Bytes (or more, if configured) Packet Count. */
   u32  nRxMaxBytePkts;
   /** Overall Transmit Good Packets Count. */
   u32  nTxGoodPkts;
   /** Transmit Unicast Packet Count. */
   u32  nTxUnicastPkts;
   /** Transmit Broadcast Packet Count. */
   u32  nTxBroadcastPkts;
   /** Transmit Multicast Packet Count. */
   u32  nTxMulticastPkts;
   /** Transmit Single Collision Count. */
   u32  nTxSingleCollCount;
   /** Transmit Multiple Collision Count. */
   u32  nTxMultCollCount;
   /** Transmit Late Collision Count. */
   u32  nTxLateCollCount;
   /** Transmit Excessive Collision Count. */
   u32  nTxExcessCollCount;
   /** Transmit Collision Count. */
   u32  nTxCollCount;
   /** Transmit Pause Packet Count. */
   u32  nTxPauseCount;
   /** Transmit Size 64 Bytes Packet Count. */
   u32  nTx64BytePkts;
   /** Transmit Size 65-127 Bytes Packet Count. */
   u32  nTx127BytePkts;
   /** Transmit Size 128-255 Bytes Packet Count. */
   u32  nTx255BytePkts;
   /** Transmit Size 256-511 Bytes Packet Count. */
   u32  nTx511BytePkts;
   /** Transmit Size 512-1023 Bytes Packet Count. */
   u32  nTx1023BytePkts;
   /** Transmit Size 1024-1522 Bytes (or more, if configured) Packet Count. */
   u32  nTxMaxBytePkts;
   /** Transmit Drop Packet Count. */
   u32  nTxDroppedPkts;
   /** Transmit Dropped Packet Count, based on Congestion Management. */
   u32  nTxAcmDroppedPkts;
   /** Receive Dropped Packet Count. */
   u32  nRxDroppedPkts;
   /** Receive Good Byte Count (64 bit). */
   u64  nRxGoodBytes;
   /** Receive Bad Byte Count (64 bit). */
   u64  nRxBadBytes;
   /** Transmit Good Byte Count (64 bit). */
   u64  nTxGoodBytes;
} GSW_RMON_Port_cnt_t;


/** \brief Force the MAC and PHY link modus.
    Used by \ref GSW_portLinkCfg_t. */
typedef enum
{
   /** Link up. Any connected LED
       still behaves based on the real PHY status. */
   GSW_PORT_LINK_UP     = 0,
   /** Link down. */
   GSW_PORT_LINK_DOWN   = 1
} GSW_portLink_t;


/** \brief Port monitor configuration.
    Used by \ref GSW_MONITOR_PORT_CFG_GET and \ref GSW_MONITOR_PORT_CFG_SET. */
typedef struct
{
   /** Ethernet Port number (zero-based counting). The valid range is hardware
       dependent. An error code is delivered if the selected port is not
       available. */
   u8   nPortId;
   /** This port is used as a monitor port. To use this feature, the port
     mirror function is enabled on one or more ports. */
   ltq_bool_t   bMonitorPort;
} GSW_monitorPortCfg_t;

/** \brief Ethernet port duplex status.
    Used by \ref GSW_portLinkCfg_t. */
typedef enum
{
   /** Port operates in full-duplex mode */
   GSW_DUPLEX_FULL      = 0,
   /** Port operates in half-duplex mode */
   GSW_DUPLEX_HALF      = 1
} GSW_portDuplex_t;

/** \brief Ethernet port interface mode.
    A port might support only a subset of the possible settings.
    Used by \ref GSW_portLinkCfg_t. */
typedef enum
{
   /** Normal PHY interface (twisted pair), use the internal MII Interface. */
   GSW_PORT_HW_MII      = 0,
   /** Reduced MII interface in normal mode. */
   GSW_PORT_HW_RMII     = 1,
   /** GMII or MII, depending upon the speed. */
   GSW_PORT_HW_GMII     = 2,
   /** RGMII mode. */
   GSW_PORT_HW_RGMII    = 3
} GSW_MII_Mode_t;

/** \brief Ethernet port configuration for PHY or MAC mode.
    Used by \ref GSW_portLinkCfg_t. */
typedef enum
{
   /** MAC Mode. The Ethernet port is configured to work in MAC mode. */
   GSW_PORT_MAC = 0,
   /** PHY Mode. The Ethernet port is configured to work in PHY mode. */
   GSW_PORT_PHY = 1
} GSW_MII_Type_t;

/** \brief Ethernet port clock source configuration.
    Used by \ref GSW_portLinkCfg_t. */
typedef enum
{
   /** Clock Mode not applicable. */
   GSW_PORT_CLK_NA      = 0,
   /** Clock Master Mode. The port is configured to provide the clock as output signal. */
   GSW_PORT_CLK_MASTER  = 1,
   /** Clock Slave Mode. The port is configured to use the input clock signal. */
   GSW_PORT_CLK_SLAVE   = 2
} GSW_clkMode_t;

/** \brief Ethernet port link, speed status and flow control status.
    Used by \ref GSW_PORT_LINK_CFG_GET and \ref GSW_PORT_LINK_CFG_SET. */
typedef struct
{
   /** Ethernet Port number (zero-based counting). The valid range is hardware
       dependent. An error code is delivered if the selected port is not
       available. */
   u8   nPortId;
   /** Force Port Duplex Mode.

       - 0: Negotiate Duplex Mode. Auto-negotiation mode. Negotiated
         duplex mode given in 'eDuplex'
         during GSW_PORT_LINK_CFG_GET calls.
       - 1: Force Duplex Mode. Force duplex mode in 'eDuplex'.
   */
   ltq_bool_t   bDuplexForce;
   /** Port Duplex Status. */
   GSW_portDuplex_t     eDuplex;
   /** Force Link Speed.

       - 0: Negotiate Link Speed. Negotiated speed given in
         'eSpeed' during GSW_PORT_LINK_CFG_GET calls.
       - 1: Force Link Speed. Forced speed mode in 'eSpeed'.
   */
   ltq_bool_t   bSpeedForce;
   /** Ethernet port link up/down and speed status. */
   GSW_portSpeed_t      eSpeed;
  /** Force Link.

       - 0: Auto-negotiate Link. Current link status is given in
         'eLink' during GSW_PORT_LINK_CFG_GET calls.
       - 1: Force Duplex Mode. Force duplex mode in 'eLink'.
   */
   ltq_bool_t   bLinkForce;
   /** Link Status. Read out the current link status.
       Note that the link could be forced by setting 'bLinkForce'. */
   GSW_portLink_t       eLink;
   /** Selected interface mode (MII/RMII/RGMII/GMII). */
   GSW_MII_Mode_t       eMII_Mode;
   /** Select MAC or PHY mode (PHY = Reverse xMII). */
   GSW_MII_Type_t       eMII_Type;
   /** Interface Clock mode (used for RMII mode). */
   GSW_clkMode_t        eClkMode;
   /** 'Low Power Idle' Support for 'Energy Efficient Ethernet'.
       Only enable this feature in case the attached PHY also supports it. */
   ltq_bool_t   bLPI;
} GSW_portLinkCfg_t;


typedef struct
{
   /** IP source address is used by the
       hash algorithm to calculate the egress trunking port index. */
   ltq_bool_t bIP_Src;
   /** IP destination address is used by the
       hash algorithm to calculate the egress trunking port index. */
   ltq_bool_t bIP_Dst;
   /** MAC source address is used by the
       hash algorithm to calculate the egress trunking port index. */
   ltq_bool_t bMAC_Src;
   /** MAC destination address is used by the
       hash algorithm to calculate the egress trunking port index. */
   ltq_bool_t bMAC_Dst;
} GSW_trunkingCfg_t;

/** \brief Ethernet port trunking configuration.
    Used by \ref GSW_TRUNKING_PORT_CFG_GET
    and \ref GSW_TRUNKING_PORT_CFG_SET. */
typedef struct
{
   /** Ports are aggregated.
       Enabling means that the 'nPortId' and
       the 'nAggrPortId' ports form an aggregated link. */
   ltq_bool_t bAggregateEnable;
   /** Ethernet Port number (zero-based counting).
       The valid range is hardware dependent.
       An error code is delivered if the selected port is not
       available. */
   u32 nPortId;
   /** Second Aggregated Ethernet Port number (zero-based counting).
       The valid range is hardware dependent.
       An error code is delivered if the selected port is not
       available. */
   u32 nAggrPortId;
} GSW_trunkingPortCfg_t;

/**
   \brief Read out the current port trunking algorithm that is used to retrieved if
   a packet is sent on the lower or higher trunking port index number. The algorithm
   performs an hash calculation over the MAC- and IP- addresses using the
   source- and destination- fields. This command retrieve which of the
   mentioned fields is used by the hash algorithm.
   The usage of any field could be configured over
   the \ref GSW_TRUNKING_CFG_SET command.

   \param GSW_trunkingCfg_t Pointer to a
      configuration \ref GSW_trunkingCfg_t

   \remarks The function returns an error code in case an error occurs.
            The error code is described in \ref GSW_return_t.

   \return Return value as follows:
   - GSW_statusOk: if successful
   - An error code in case an error occurs
*/
#define GSW_TRUNKING_CFG_GET	_IOWR(GSW_MAGIC, 0x65, GSW_trunkingCfg_t)
/**
   \brief Configure the current port trunking algorithm that is used to retrieved if
   a packet is sent on the lower or higher trunking port index number. The algorithm
   performs an hash calculation over the MAC- and IP- addresses using the
   source- and destination- fields. This command retrieve which of the
   mentioned fields is used by the hash algorithm.
   The usage of any field could be configured over
   the \ref GSW_TRUNKING_CFG_SET command.

   \param GSW_trunkingCfg_t Pointer to a
      configuration \ref GSW_trunkingCfg_t

   \remarks The function returns an error code in case an error occurs.
            The error code is described in \ref GSW_return_t.

   \return Return value as follows:
   - GSW_statusOk: if successful
   - An error code in case an error occurs
*/
#define GSW_TRUNKING_CFG_SET	_IOW(GSW_MAGIC, 0x66, GSW_trunkingCfg_t)
/**
   \brief Read out the port trunking state of a given physical Ethernet switch port 'nPortId'.
   Switch API sets the boolean flag 'bAggregateEnable' and the aggregated trunking
   port 'nAggrPortId' in case trunking is enabled on the port.

   Port trunking can be configures by using the command \ref GSW_TRUNKING_PORT_CFG_GET.

   \param GSW_trunkingPortCfg_t Pointer to a
      configuration \ref GSW_trunkingPortCfg_t

   \remarks The function returns an error code in case an error occurs.
            The error code is described in \ref GSW_return_t.

   \return Return value as follows:
   - GSW_statusOk: if successful
   - An error code in case an error occurs
*/
#define GSW_TRUNKING_PORT_CFG_GET	_IOWR(GSW_MAGIC, 0x67, GSW_trunkingPortCfg_t)
/**
   \brief Configure the port trunking on two physical Ethernet switch ports.
   A new port trunking group of two groups could be placed or removed.
   The two port index number are given with the parameter 'nPortId' and 'nAggrPortId'.

   The current trunking port state can be read out by using the command \ref GSW_TRUNKING_PORT_CFG_GET.

   \param GSW_trunkingPortCfg_t Pointer to a
      configuration \ref GSW_trunkingPortCfg_t

   \remarks The function returns an error code in case an error occurs.
            The error code is described in \ref GSW_return_t.

   \return Return value as follows:
   - GSW_statusOk: if successful
   - An error code in case an error occurs
*/
#define GSW_TRUNKING_PORT_CFG_SET	_IOW(GSW_MAGIC, 0x68, GSW_trunkingPortCfg_t)

/*@}*/ /* GSW_IOCTL_PMAC */

/* -------------------------------------------------------------------------- */
/*                        IOCTL Command Definitions                           */
/* -------------------------------------------------------------------------- */

/**
   \brief Read out the current Ethernet port configuration.

   \param GSW_portCfg_t Pointer to a port configuration
   \ref GSW_portCfg_t structure to fill out by the driver.
   The parameter 'nPortId' tells the driver which port parameter is requested.

   \remarks The function returns an error code in case an error occurs.
            The error code is described in \ref GSW_return_t.

   \return Return value as follows:
   - GSW_statusOk: if successful
   - An error code in case an error occurs
*/
#define GSW_PORT_CFG_GET        _IOWR(GSW_MAGIC, 0x49, GSW_portCfg_t)

/** \addtogroup GSW_IOCTL_BRIDGE */
/*@{*/

/**
   \brief Read out the Ethernet port's speed, link status, and flow control status.
   The information for one single port 'nPortId' is returned.
   An error code is returned if the selected port does not exist.

   \param GSW_portLinkCfg_t Pointer to
      an \ref GSW_portLinkCfg_t structure to read out the port status.

   \remarks The function returns an error code in case an error occurs.
            The error code is described in \ref GSW_return_t.

   \return Return value as follows:
   - GSW_statusOk: if successful
   - An error code in case an error occurs
*/
#define GSW_PORT_LINK_CFG_GET   _IOWR(GSW_MAGIC, 0x4F, GSW_portLinkCfg_t)

/**
   \brief Set the Ethernet port configuration.

   \param GSW_portCfg_t Pointer to an \ref GSW_portCfg_t structure
   to configure the switch port hardware.

   \remarks The function returns an error code in case an error occurs.
            The error code is described in \ref GSW_return_t.

   \return Return value as follows:
   - GSW_statusOk: if successful
   - An error code in case an error occurs
*/
#define GSW_PORT_CFG_SET        _IOW(GSW_MAGIC, 0x4A, GSW_portCfg_t)

/**
   \brief Reads out the current monitor options for a
   dedicated Ethernet port. This configuration can be set
   using \ref GSW_MONITOR_PORT_CFG_SET.

   \param GSW_monitorPortCfg_t Pointer
          to \ref GSW_monitorPortCfg_t.

   \remarks The function returns an error code in case an error occurs.
            The error code is described in \ref GSW_return_t.

   \return Return value as follows:
   - GSW_statusOk: if successful
   - An error code in case an error occurs
*/
#define GSW_MONITOR_PORT_CFG_GET        _IOWR(GSW_MAGIC, 0x57, GSW_monitorPortCfg_t)

/**
   \brief Configures the monitor options for a
   dedicated Ethernet port. This current configuration can be read back
   using \ref GSW_MONITOR_PORT_CFG_GET.

   \param GSW_monitorPortCfg_t Pointer
          to \ref GSW_monitorPortCfg_t.

   \remarks The function returns an error code in case an error occurs.
            The error code is described in \ref GSW_return_t.

   \return Return value as follows:
   - GSW_statusOk: if successful
   - An error code in case an error occurs
*/
#define GSW_MONITOR_PORT_CFG_SET        _IOW(GSW_MAGIC, 0x58, GSW_monitorPortCfg_t)

/**
   \brief Set the Ethernet port link, speed status and flow control status.
   The configuration applies to a single port 'nPortId'.

   \param GSW_portLinkCfg_t Pointer to
      an \ref GSW_portLinkCfg_t structure to set the port configuration.

   \remarks The function returns an error code in case an error occurs.
            The error code is described in \ref GSW_return_t.

   \return Return value as follows:
   - GSW_statusOk: if successful
   - An error code in case an error occurs
*/
#define GSW_PORT_LINK_CFG_SET   _IOW(GSW_MAGIC, 0x50, GSW_portLinkCfg_t)

/*@}*/ /* GSW_IOCTL_OAM */

/** \addtogroup GSW_IOCTL_RMON */
/*@{*/

/**
   \brief Read out the Ethernet port statistic counter (RMON counter).
   The zero-based 'nPortId' structure element describes the physical switch
   port for the requested statistic information.

   \param GSW_RMON_Port_cnt_t  Pointer to pre-allocated
   \ref GSW_RMON_Port_cnt_t structure. The structure element 'nPortId' is
   an input parameter that describes from which port to read the RMON counter.
   All remaining structure elements are filled with the counter values.

   \remarks The function returns an error in case the given 'nPortId' is
   out of range.

   \remarks The function returns an error code in case an error occurs.
            The error code is described in \ref GSW_return_t.

   \return Return value as follows:
   - GSW_statusOk: if successful
   - An error code in case an error occurs
*/
#define GSW_RMON_PORT_GET       _IOWR(GSW_MAGIC, 0x59, GSW_RMON_Port_cnt_t)


#endif /*  _LANTIQ_UAPI_GSW_H_ */
