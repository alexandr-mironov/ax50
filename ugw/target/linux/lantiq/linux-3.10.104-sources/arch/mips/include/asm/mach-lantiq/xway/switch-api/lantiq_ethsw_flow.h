/******************************************************************************

                         Copyright (c) 2012, 2014, 2015
                            Lantiq Deutschland GmbH

  For licensing information, see the file 'LICENSE' in the root folder of
  this software module.

******************************************************************************/
 
#ifndef _LANTIQ_ETHSW_FLOW_H_
#define _LANTIQ_ETHSW_FLOW_H_

#ifdef __KERNEL__
#include "net/uapi_lantiq_ethsw_flow.h"
#else
#include "uapi_lantiq_ethsw_flow.h"
#endif

/* =================================== */
/* Global typedef forward declarations */
/* =================================== */

/* ============================= */
/* Local Macros & Definitions    */
/* ============================= */

/* Group definitions for Doxygen */
/** \defgroup FLOW_IOCTL XWAY VRX200 and XWAY GRX200 Family Specific Ethernet Switch API
    This chapter describes the XWAY VRX200 and XWAY GRX200 Family specific
    interfaces for accessing and configuring the services of the Ethernet switch module.
    These features are a device-specific enhancement of the generic Switch API part. */
/*@{*/

/** \defgroup FLOW_IOCTL_DEBUG Debug Features
    XWAY VRX200 and XWAY GRX200 Family specific features for system
    integration and debug sessions.
*/
/** \defgroup FLOW_IOCTL_IRQ Interrupt Handling
    Configure XWAY VRX200 and XWAY GRX200 Family specific hardware
    support to generate interrupts
    and read out the interrupt sources.
*/
/** \defgroup FLOW_IOCTL_OAM Operation, Administration, and Management Functions
    This chapter summarizes the functions that are provided to monitor the
    data traffic passing through the device.
*/
/** \defgroup FLOW_IOCTL_CLASSUNIT Packet Classification Engine
    Configures and controls the classification unit of the XWAY VRX200
    and XWAY GRX200 Family hardware.
*/

/*@}*/

/* -------------------------------------------------------------------------- */
/*                 Structure and Enumeration Type Defintions                  */
/* -------------------------------------------------------------------------- */

/** \addtogroup FLOW_IOCTL_DEBUG */
/*@{*/


/*@}*/ /* FLOW_IOCTL_DEBUG */

/** \addtogroup FLOW_IOCTL_IRQ */
/*@{*/

/** Interrupt Source Selector.
    Used by \ref IFX_FLOW_irq_t. */
typedef enum
{
   /** Wake-on-LAN Interrupt.
       The parameter 'nPortId' specifies the relative MAC port. */
   IFX_FLOW_IRQ_WOL	= 0,
   /** Port Limit Alert Interrupt. This interrupt is asserted when the number
       of learned MAC addresses exceeds the configured limit for
       the ingress port.
       The parameter 'nPortId' specifies the relative MAC port. */
   IFX_FLOW_IRQ_LIMIT_ALERT	= 1,
   /** Port Lock Alert Interrupt.
       This interrupt is asserted when a source MAC address is learned on a
       locked port and is received on another port.
       The parameter 'nPortId' specifies the relative MAC port. */
   IFX_FLOW_IRQ_LOCK_ALERT	= 2
}IFX_FLOW_irqSrc_t;

/** Interrupt bits. Depending on the hardware device type, not all interrupts might be available.
    Used by \ref IFX_FLOW_IRQ_MASK_GET, \ref IFX_FLOW_IRQ_MASK_SET,
    \ref IFX_FLOW_IRQ_GET and \ref IFX_FLOW_IRQ_STATUS_CLEAR. */
typedef struct
{
   /** Ethernet Port number (zero-based counting). The valid range is hardware dependent.
       An error code is delivered if the selected port is not
       available. This port parameter is needed for some interrupts
       that are specified by 'nIrqSrc'. For all other interrupts, this
       parameter is "don't care". */
   u32	nPortId;
   /** Interrupt source. */
   IFX_FLOW_irqSrc_t	eIrqSrc;
}IFX_FLOW_irq_t;

/*@}*/ /* FLOW_IOCTL_IRQ */

/** \addtogroup FLOW_IOCTL_CLASSUNIT */
/*@{*/

/*@}*/ /* FLOW_IOCTL_CLASSUNIT */

/** \addtogroup FLOW_IOCTL_OAM */
/*@{*/

/** Reset selection.
    Used by \ref IFX_FLOW_reset_t. */
typedef enum
{
   /** Switch Macro reset */
   IFX_FLOW_RESET_SWITCH	= 0,
   /** MDIO master interface reset */
   IFX_FLOW_RESET_MDIO	= 1,
}IFX_FLOW_resetMode_t;

/** Reset selection.
    Used by \ref IFX_FLOW_RESET. */
typedef struct
{
   /** Reset selection. */
   IFX_FLOW_resetMode_t	eReset;
}IFX_FLOW_reset_t;

/** Number of extended RMON counter. */
#define IFX_FLOW_RMON_EXTEND_NUM	24

/**
   Hardware platform extended RMON Counters.
   This structure contains additional RMON counters of one Ethernet Switch Port.
   These counters can be used by the packet classification engine and can be
   freely assigned to dedicated packet rules and flows.
    Used by \ref IFX_FLOW_RMON_EXTEND_GET. */
typedef struct
{
   /** Ethernet Port number (zero-based counting). The valid range is hardware
       dependent. An error code is delivered if the selected port is not
       available. */
   u8		nPortId;
   /** Traffic flow counters */
   u32	nTrafficFlowCnt[IFX_FLOW_RMON_EXTEND_NUM];
}IFX_FLOW_RMON_extendGet_t;

/** This structure describes the second, nano second and fractional
    nano second counter part of the switch reference timer. This
    reference counter can be read by
    using \ref IFX_FLOW_TIMESTAMP_TIMER_GET , and it can be modified
    by using \ref IFX_FLOW_TIMESTAMP_TIMER_SET . */
typedef struct
{
   /** Second. Absolute second timer count. */
   u32	nSec;
   /** Nano Second. Absolute nano second timer count. */
   u32	nNanoSec;
   /** Fractional Nano Second. Absolute fractional nano
       second timer count.
       This counter specifis a 2^32 fractional 'nNanoSec'. */
   u32	nFractionalNanoSec;
}IFX_FLOW_TIMESTAMP_Timer_t;

/** This structure describes the port related time stamp.
    Used by \ref IFX_FLOW_TIMESTAMP_PORT_READ.
*/
typedef struct
{
   /** Ethernet Port number (zero-based counting). The valid range is hardware
       dependent. An error code is delivered if the selected port is not
       available. */
   u8		nPortId;
   /** Second. Absolute second timer count. */
   u32	nIngressSec;
   /** Nano Second. Absolute nano second timer count. */
   u32	nIngressNanoSec;
   /** Second. Absolute second timer count. */
   u32	nEgressSec;
   /** Nano Second. Absolute nano second timer count. */
   u32	nEgressNanoSec;
}IFX_FLOW_TIMESTAMP_PortRead_t;

/*@}*/ /* FLOW_IOCTL_OAM */

/* -------------------------------------------------------------------------- */
/*                        IOCTL Command Definitions                           */
/* -------------------------------------------------------------------------- */

/** \addtogroup FLOW_IOCTL_DEBUG */
/*@{*/

/**
   Read an internal register. The register offset defines which register to access in
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
#define IFX_FLOW_REGISTER_GET	_IOWR(IFX_FLOW_MAGIC, 0x02, IFX_FLOW_register_t)

/*@}*/ /* FLOW_IOCTL_DEBUG */

/** \addtogroup FLOW_IOCTL_IRQ */
/*@{*/
/**
   Get the interrupt enable configuration. This assignment can be set using \ref IFX_FLOW_IRQ_MASK_SET.

   \param IFX_FLOW_irq_t Pointer to
      an \ref IFX_FLOW_irq_t structure.

   \remarks The function returns an error code in case an error occurs.
            The error code is described in \ref IFX_ETHSW_status_t.

   \return Return value as follows:
   - IFX_SUCCESS: if successful
   - An error code in case an error occurs

*/
#define IFX_FLOW_IRQ_MASK_GET	_IOWR(IFX_FLOW_MAGIC, 0x03, IFX_FLOW_irq_t)

/**
   Set the interrupt enable configuration. This assignment can be read using \ref IFX_FLOW_IRQ_MASK_GET.
   Setting interrupts that are not supported by hardware results in an error response.

   \param IFX_FLOW_irq_t Pointer to
      an \ref IFX_FLOW_irq_t structure.

   \remarks The function returns an error code in case an error occurs.
            The error code is described in \ref IFX_ETHSW_status_t.

   \return Return value as follows:
   - IFX_SUCCESS: if successful
   - An error code in case an error occurs

*/
#define IFX_FLOW_IRQ_MASK_SET	_IOW(IFX_FLOW_MAGIC, 0x04, IFX_FLOW_irq_t)

/**
   Read the interrupt status. Interrupt status indications can be cleared using \ref IFX_FLOW_IRQ_STATUS_CLEAR.

   \param IFX_FLOW_irq_t Pointer to
      an \ref IFX_FLOW_irq_t structure.

   \remarks The function returns an error code in case an error occurs.
            The error code is described in \ref IFX_ETHSW_status_t.

   \return Return value as follows:
   - IFX_SUCCESS: if successful
   - An error code in case an error occurs

*/
#define IFX_FLOW_IRQ_GET	_IOWR(IFX_FLOW_MAGIC, 0x05, IFX_FLOW_irq_t)

/**
   Clear individual interrupt status bits. Interrupt status indications can be read using \ref IFX_FLOW_IRQ_GET.

   \param IFX_FLOW_irq_t Pointer to
      an \ref IFX_FLOW_irq_t structure.

   \remarks The function returns an error code in case an error occurs.
            The error code is described in \ref IFX_ETHSW_status_t.

   \return Return value as follows:
   - IFX_SUCCESS: if successful
   - An error code in case an error occurs

*/
#define IFX_FLOW_IRQ_STATUS_CLEAR _IOW(IFX_FLOW_MAGIC, 0x06, IFX_FLOW_irq_t)

/*@}*/ /* FLOW_IOCTL_IRQ */

/** \addtogroup FLOW_IOCTL_CLASSUNIT */
/*@{*/

/**
   This command allows the reading out of a rule pattern and action of the
   packet classification engine.
   A rule can be written using the command \ref IFX_FLOW_PCE_RULE_WRITE.

   \param IFX_FLOW_PCE_rule_t Pointer to \ref IFX_FLOW_PCE_rule_t.

   \remarks The function returns an error code in case an error occurs.
            The error code is described in \ref IFX_ETHSW_status_t.

   \return Return value as follows:
   - IFX_SUCCESS: if successful
   - An error code in case an error occurs
*/
#define IFX_FLOW_PCE_RULE_READ	_IOWR(IFX_FLOW_MAGIC, 0x08, IFX_FLOW_PCE_rule_t)

/*@}*/ /* FLOW_IOCTL_CLASSUNIT */

/** \addtogroup FLOW_IOCTL_OAM */
/*@{*/

/**
   Forces a hardware reset of the switch device or switch macro. The device
   automatically comes back out of reset and contains the initial values.
   All previous configurations are lost.

   \param IFX_FLOW_reset_t Pointer to an \ref IFX_FLOW_reset_t structure.

   \remarks The function returns an error code in case an error occurs.
            The error code is described in \ref IFX_ETHSW_status_t.

   \return Return value as follows:
   - IFX_SUCCESS: if successful
   - An error code in case an error occurs

   \remarks Not supported for all devices
*/
#define IFX_FLOW_RESET	_IOW(IFX_FLOW_MAGIC, 0x0A, IFX_FLOW_reset_t)

/**
   Read out additional traffic flow (RMON) counters.
   The zero-based 'nPortId' structure element describes the physical switch
   port for the requested statistic information.

   \param IFX_FLOW_RMON_extendGet_t  Pointer to a pre-allocated
   \ref IFX_FLOW_RMON_extendGet_t structure. The structure element 'nPortId' is
   an input parameter that describes from which port to read the RMON counter.
   All remaining structure elements are filled with the counter values.
   The counter assignment needs to be done during the flow definition,
   for example in \ref IFX_FLOW_PCE_RULE_WRITE.

   \remarks The function returns an error in case the given 'nPortId' is
   out of range.

   \remarks The function returns an error code in case an error occurs.
            The error code is described in \ref IFX_ETHSW_status_t.

   \return Return value as follows:
   - IFX_SUCCESS: if successful
   - An error code in case an error occurs
*/
#define IFX_FLOW_RMON_EXTEND_GET	_IOWR(IFX_FLOW_MAGIC, 0x0B, IFX_FLOW_RMON_extendGet_t)

/** This command sets the packet timestamp reference counter.
    This reference timer is a switch global timer which is used by the
    packet timestamp capture when sending and receiving Ethernet port level.

    The command \ref IFX_FLOW_TIMESTAMP_TIMER_GET allows to read out
    the current reference timer.

   \param IFX_FLOW_TIMESTAMP_Timer_t Pointer to an \ref IFX_FLOW_TIMESTAMP_Timer_t structure.

   \remarks The function returns an error code in case an error occurs.
            The error code is described in \ref IFX_ETHSW_status_t.

   \return Return value as follows:
   - IFX_SUCCESS: if successful
   - An error code in case an error occurs
*/
#define IFX_FLOW_TIMESTAMP_TIMER_SET _IOW(IFX_FLOW_MAGIC, 0x0C, IFX_FLOW_TIMESTAMP_Timer_t)

/** This command reads out the switch global reference timer counter that is
    used by the packet timestamp capture when sending and receiving Ethernet port level.

    This reference timer is useful when processing the packet related
    timestamp information for delay calculation.

    The reference timer can be configured by \ref IFX_FLOW_TIMESTAMP_TIMER_SET.

   \param IFX_FLOW_TIMESTAMP_Timer_t Pointer to an \ref IFX_FLOW_TIMESTAMP_Timer_t structure.

   \remarks The function returns an error code in case an error occurs.
            The error code is described in \ref IFX_ETHSW_status_t.

   \return Return value as follows:
   - IFX_SUCCESS: if successful
   - An error code in case an error occurs
*/
#define IFX_FLOW_TIMESTAMP_TIMER_GET _IOR(IFX_FLOW_MAGIC, 0x0D, IFX_FLOW_TIMESTAMP_Timer_t)

/** This command reads out the port related time stamp values. This time stamp is captured
    for ingress and egress packets triggered due to a traffic flow table time stamp action.
    A switch global reference timer is used for the time stamp capture operation.
    This global timer can be access by using \ref IFX_FLOW_TIMESTAMP_TIMER_SET
    and \ref IFX_FLOW_TIMESTAMP_TIMER_GET.

    A port related packet timestamp is triggered by the flow table
    action 'eTimestampAction'.

   \param IFX_FLOW_TIMESTAMP_PortRead_t Pointer to
      an \ref IFX_FLOW_TIMESTAMP_PortRead_t structure.

   \remarks The function returns an error code in case an error occurs.
            The error code is described in \ref IFX_ETHSW_status_t.

   \return Return value as follows:
   - IFX_SUCCESS: if successful
   - An error code in case an error occurs
*/
#define IFX_FLOW_TIMESTAMP_PORT_READ _IOWR(IFX_FLOW_MAGIC, 0x0E, IFX_FLOW_TIMESTAMP_PortRead_t)

/*@}*/ /* FLOW_IOCTL_OAM */

#endif /* _LANTIQ_ETHSW_FLOW_H_ */
