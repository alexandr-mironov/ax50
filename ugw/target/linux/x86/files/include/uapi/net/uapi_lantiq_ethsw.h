#ifndef _LANTIQ_UAPI_ETHSW_H_
#define _LANTIQ_UAPI_ETHSW_H_

/* IOCTL MAGIC */
#define IFX_ETHSW_MAGIC ('E')


/* -------------------------------------------------------------------------- */
/*                 Structure and Enumeration Type Defintions                  */
/* -------------------------------------------------------------------------- */

/** \addtogroup ETHSW_IOCTL_BRIDGE */
/*@{*/

/** MAC Address Field Size.
    Number of bytes used to store MAC address information. */
/** This is the unsigned 32-bit datatype. */
typedef unsigned int    u32;
/** This is the unsigned 8-bit datatype. */
typedef unsigned char   u8;
/** This is the unsigned 16-bit datatype. */
typedef unsigned short  u16;
/** This is the unsigned 16-bit datatype. */
/* typedef unsigned short  IFX_uint16_t; */
/** A type for handling boolean issues. */

typedef enum {
        LTQ_FALSE               = 0,
        LTQ_TRUE                = 1
} ltq_bool_t;

typedef union {
        /** Describe the IPv4 address.
        Only used if the IPv4 address should be read or configured.
        Cannot be used together with the IPv6 address fields. */
        u32     nIPv4;
        /** Describe the IPv6 address.
        Only used if the IPv6 address should be read or configured.
        Cannot be used together with the IPv4 address fields. */
        u16     nIPv6[8];
} IFX_ETHSW_IP_t;

/** Ethernet port interface mode.
        A port might support only a subset of the possible settings.
        Used by \ref IFX_ETHSW_portLinkCfg_t. */
typedef enum {
        /** Normal PHY interface (twisted pair), use the internal MII Interface. */
        IFX_ETHSW_PORT_HW_MII   = 0,
        /** Reduced MII interface in normal mode. */
        IFX_ETHSW_PORT_HW_RMII  = 1,
        /** GMII or MII, depending upon the speed. */
        IFX_ETHSW_PORT_HW_GMII  = 2,
        /** RGMII mode. */
        IFX_ETHSW_PORT_HW_RGMII = 3
} IFX_ETHSW_MII_Mode_t;

/** Ethernt port configuration for PHY or MAC mode.
        Used by \ref IFX_ETHSW_portLinkCfg_t. */
typedef enum {
        /** MAC Mode. The Ethernet port is configured to work in MAC mode. */
        IFX_ETHSW_PORT_MAC      = 0,
        /** PHY Mode. The Ethernet port is configured to work in PHY mode. */
        IFX_ETHSW_PORT_PHY      = 1
} IFX_ETHSW_MII_Type_t;


/** Ethernet port speed mode.
        A port might support only a subset of the possible settings.
        Used by \ref IFX_ETHSW_portLinkCfg_t. */
typedef enum {
        /** 10 Mbit/s */
        IFX_ETHSW_PORT_SPEED_10 = 10,
        /** 100 Mbit/s */
        IFX_ETHSW_PORT_SPEED_100        = 100,
        /** 200 Mbit/s */
        IFX_ETHSW_PORT_SPEED_200        = 200,
        /** 1000 Mbit/s */
        IFX_ETHSW_PORT_SPEED_1000       = 1000
} IFX_ETHSW_portSpeed_t;

/** Ethernet port duplex status.
        Used by \ref IFX_ETHSW_portLinkCfg_t. */
typedef enum {
        /** Port operates in full-duplex mode */
        IFX_ETHSW_DUPLEX_FULL   = 0,
        /** Port operates in half-duplex mode */
        IFX_ETHSW_DUPLEX_HALF   = 1
} IFX_ETHSW_portDuplex_t;

/** Force the MAC and PHY link modus.
        Used by \ref IFX_ETHSW_portLinkCfg_t. */
typedef enum {
        /** Link up. Any connected LED
        still behaves based on the real PHY status. */
        IFX_ETHSW_PORT_LINK_UP  = 0,
        /** Link down. */
        IFX_ETHSW_PORT_LINK_DOWN        = 1
} IFX_ETHSW_portLink_t;


/** Ethernet port clock source configuration.
        Used by \ref IFX_ETHSW_portLinkCfg_t. */
typedef enum {
        /** Clock Mode not applicable. */
        IFX_ETHSW_PORT_CLK_NA   = 0,
        /** Clock Master Mode. The port is configured to provide the clock as output signal. */
        IFX_ETHSW_PORT_CLK_MASTER       = 1,
        /** Clock Slave Mode. The port is configured to use the input clock signal. */
        IFX_ETHSW_PORT_CLK_SLAVE        = 2
} IFX_ETHSW_clkMode_t;


/** Ethernet port link, speed status and flow control status.
    Used by \ref IFX_ETHSW_PORT_LINK_CFG_GET
    and \ref IFX_ETHSW_PORT_LINK_CFG_SET. */
typedef struct {
        /** Ethernet Port number (zero-based counting). The valid range is hardware
        dependent. An error code is delivered if the selected port is not
        available. */
        u8      nPortId;
        /** Force Port Duplex Mode.
                - LTQ_FALSE: Negotiate Duplex Mode. Auto-negotiation mode.
                        Negotiated duplex mode given in 'eDuplex' during
                        IFX_ETHSW_PORT_LINK_CFG_GET calls.
                - LTQ_TRUE: Force Duplex Mode. Force duplex mode in 'eDuplex'.
        */
        ltq_bool_t      bDuplexForce;
        /** Port Duplex Status. */
        IFX_ETHSW_portDuplex_t  eDuplex;
        /** Force Link Speed.
                - LTQ_FALSE: Negotiate Link Speed. Negotiated speed given in
                                'eSpeed' during IFX_ETHSW_PORT_LINK_CFG_GET calls.
                - LTQ_TRUE: Force Link Speed. Forced speed mode in 'eSpeed'.
        */
        ltq_bool_t      bSpeedForce;
        /** Ethernet port link up/down and speed status. */
        IFX_ETHSW_portSpeed_t   eSpeed;
        /** Force Link.
        - LTQ_FALSE: Auto-negotiate Link. Current link status is given in
                'eLink' during IFX_ETHSW_PORT_LINK_CFG_GET calls.
        - LTQ_TRUE: Force Duplex Mode. Force duplex mode in 'eLink'.
        */
        ltq_bool_t      bLinkForce;
        /** Link Status. Read out the current link status.
        Note that the link could be forced by setting 'bLinkForce'. */
        IFX_ETHSW_portLink_t    eLink;
        /** Selected interface mode (MII/RMII/RGMII/GMII). */
        IFX_ETHSW_MII_Mode_t    eMII_Mode;
        /** Select MAC or PHY mode (PHY = Reverse xMII). */
        IFX_ETHSW_MII_Type_t    eMII_Type;
        /** Interface Clock mode (used for RMII mode). */
        IFX_ETHSW_clkMode_t     eClkMode;
        /** 'Low Power Idle' Support for 'Energy Efficient Ethernet'.
        Only enable this feature in case the attached PHY also supports it. */
        ltq_bool_t      bLPI;
} IFX_ETHSW_portLinkCfg_t;

/**
   Read out the Ethernet port's speed, link status, and flow control status.
   The information for one single port 'nPortId' is returned.
   An error code is returned if the selected port does not exist.

   \param IFX_ETHSW_portLinkCfg_t Pointer to
      an \ref IFX_ETHSW_portLinkCfg_t structure to read out the port status.

        \remarks The function returns an error code in case an error occurs.
                The error code is described in \ref IFX_ETHSW_status_t.

   \return Return value as follows:
   - LTQ_SUCCESS: if successful
   - An error code in case an error occurs
*/
#define IFX_ETHSW_PORT_LINK_CFG_GET     _IOWR(IFX_ETHSW_MAGIC, 0x4F, IFX_ETHSW_portLinkCfg_t)


#endif    /* _LANTIQ_UAPI_ETHSW_H_ */

