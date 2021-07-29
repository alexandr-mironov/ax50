/******************************************************************************

                         Copyright (c) 2012, 2014, 2015
                            Lantiq Deutschland GmbH

  For licensing information, see the file 'LICENSE' in the root folder of
  this software module.

******************************************************************************/
 
#ifndef _LANTIQ_ETHSW_FLOW_H_
#define _LANTIQ_ETHSW_FLOW_H_
#ifdef __KERNEL__
#include "net/uapi_lantiq_gsw_flow.h"
#else
#include "uapi_lantiq_gsw_flow.h"
#endif
/* =================================== */
/* Global typedef forward declarations */
/* =================================== */

/* ============================= */
/* Local Macros & Definitions    */
/* ============================= */


/* Group definitions for Doxygen */
/** \defgroup GSW_FLOW_GROUP GSWIP Packet Classification Engine (PCE) related APIs
    \brief This chapter describes the GSWIP's PCE and other low level related APIs. 
*/
/*@{*/

/** \defgroup GSW_IOCTL_DEBUG Debug Features
   \brief Switch Registers write and read for any low level operations including debug.
*/
/** \defgroup GSW_IOCTL_IRQ Interrupt Handling
    \brief Configure GSWIP support to configure and read out the interrupt mask and sources.
*/
/** \defgroup GSW_IOCTL_SYS GSWIP System Functions
    \brief This chapter summarizes the functions that are provided to handle system aspects of GSWIP.
*/
/** \defgroup GSW_IOCTL_CLASS Packet Classification Engine
    \brief Configures and controls the classification unit of the GSWIP.
*/

/*@}*/

/* -------------------------------------------------------------------------- */
/*                 Structure and Enumeration Type Defintions                  */
/* -------------------------------------------------------------------------- */

/** \addtogroup GSW_IOCTL_DEBUG */
/*@{*/

/*@}*/ /* GSW_IOCTL_DEBUG */

/** \addtogroup GSW_IOCTL_IRQ */
/*@{*/

/** \brief Interrupt Source Selector.
    Used by \ref GSW_irq_t. */
typedef enum
{
   /** Wake-on-LAN Interrupt. The configured packet flow will trigger WoL interrupt.
       The parameter 'nPortId' specifies the relative MAC port. */
   GSW_IRQ_WOL	= 0,
   /** Port Limit Alert Interrupt. This interrupt is asserted when the number
       of learned MAC addresses exceeds the configured limit for
       the ingress port.
       The parameter 'nPortId' specifies the relative MAC port. */
   GSW_IRQ_LIMIT_ALERT	= 1,
   /** Port Lock Alert Interrupt.
       This interrupt is asserted when a source MAC address is learned on a
       locked port and is received on another port.
       The parameter 'nPortId' specifies the relative MAC port. */
   GSW_IRQ_LOCK_ALERT	= 2
}GSW_irqSrc_t;

/** \brief Interrupt bits. Depending on the hardware device type, not all interrupts might be available.
    Used by \ref GSW_IRQ_MASK_GET, \ref GSW_IRQ_MASK_SET,
    \ref GSW_IRQ_GET and \ref GSW_IRQ_STATUS_CLEAR. */
typedef struct
{
   /** Ethernet Port number (zero-based counting). The valid range is hardware dependent.
       An error code is delivered if the selected port is not
       available. This port parameter is needed for some interrupts
       that are specified by 'nIrqSrc'. For all other interrupts, this
       parameter is "don't care". */
   u32	nPortId;
   /** Interrupt Source Type. */
   GSW_irqSrc_t	eIrqSrc;
}GSW_irq_t;

/*@}*/ /* GSW_IOCTL_IRQ */

/** \addtogroup GSW_IOCTL_SYS */
/*@{*/

/** \brief Reset selection.
    Used by \ref GSW_reset_t. */
typedef enum
{
   /** Switch Macro reset */
   GSW_RESET_SWITCH	= 0,
   /** MDIO master interface reset */
   GSW_RESET_MDIO	= 1,
}GSW_resetMode_t;

/** \brief Reset selection.
    Used by \ref GSW_RESET. */
typedef struct
{
   /** Reset selection. */
   GSW_resetMode_t	eReset;
}GSW_reset_t;

/** Number of extended RMON counter. */
#define GSW_RMON_EXTEND_NUM	24

/**
   \brief Hardware platform extended RMON Counters.
   This structure contains additional RMON counters of one Ethernet Switch Port.
   These counters can be used by the packet classification engine and can be
   freely assigned to dedicated packet rules and flows.
    Used by \ref GSW_RMON_EXTEND_GET. */
typedef struct
{
   /** Ethernet Port number (zero-based counting). The valid range is hardware
       dependent. An error code is delivered if the selected port is not
       available. */
   u8		nPortId;
   /** Traffic flow counters */
   u32	nTrafficFlowCnt[GSW_RMON_EXTEND_NUM];
}GSW_RMON_extendGet_t;

/** \brief This structure describes the second, nano second and fractional
    nano second counterpart of the switch reference timer. This
    reference counter can be read by
    using \ref GSW_TIMESTAMP_TIMER_GET , and it can be modified
    by using \ref GSW_TIMESTAMP_TIMER_SET . */
typedef struct
{
   /** Second. Absolute second timer count. */
   u32	nSec;
   /** Nano Second. Absolute nanosecond timer count. */
   u32	nNanoSec;
   /** Fractional NanoSecond. Absolute fractional nanosecond timer count.
       This counter specifis a 2^32 fractional 'nNanoSec'. */
   u32	nFractionalNanoSec;
}GSW_TIMESTAMP_Timer_t;

/** \brief This structure describes the port related time stamp.
    Used by \ref GSW_TIMESTAMP_PORT_READ.
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
}GSW_TIMESTAMP_PortRead_t;

/*@}*/ /* GSW_IOCTL_SYS */

/* -------------------------------------------------------------------------- */
/*                        IOCTL Command Definitions                           */
/* -------------------------------------------------------------------------- */

/** \addtogroup GSW_IOCTL_DEBUG */
/*@{*/

/*@}*/ /* GSW_IOCTL_DEBUG */

/** \addtogroup GSW_IOCTL_IRQ */
/*@{*/
/**
   \brief Get the interrupt enable configuration. This assignment can be set using \ref GSW_IRQ_MASK_SET.

   \param GSW_irq_t Pointer to an \ref GSW_irq_t structure.

   \remarks The function returns an error code in case an error occurs.
            The error code is described in \ref GSW_return_t.

   \return Return value as follows:
   - GSW_statusOk: if successful
   - An error code in case an error occurs

*/
#define GSW_IRQ_MASK_GET	_IOWR(GSW_FLOW_MAGIC, 0x03, GSW_irq_t)

/**
   \brief Set the interrupt enable configuration. This assignment can be read using \ref GSW_IRQ_MASK_GET.
   Setting interrupts that are not supported by hardware results in an error response.

   \param GSW_irq_t Pointer to
      an \ref GSW_irq_t structure.

   \remarks The function returns an error code in case an error occurs.
            The error code is described in \ref GSW_return_t.

   \return Return value as follows:
   - GSW_statusOk: if successful
   - An error code in case an error occurs

*/
#define GSW_IRQ_MASK_SET	_IOW(GSW_FLOW_MAGIC, 0x04, GSW_irq_t)

/**
   \brief Read the interrupt status. Interrupt status indications can be cleared using \ref GSW_IRQ_STATUS_CLEAR.

   \param GSW_irq_t Pointer to
      an \ref GSW_irq_t structure.

   \remarks The function returns an error code in case an error occurs.
            The error code is described in \ref GSW_return_t.

   \return Return value as follows:
   - GSW_statusOk: if successful
   - An error code in case an error occurs

*/
#define GSW_IRQ_GET	_IOWR(GSW_FLOW_MAGIC, 0x05, GSW_irq_t)

/**
   \brief Clear individual interrupt status bits. Interrupt status indications can be read using \ref GSW_IRQ_GET.

   \param GSW_irq_t Pointer to
      an \ref GSW_irq_t structure.

   \remarks The function returns an error code in case an error occurs.
            The error code is described in \ref GSW_return_t.

   \return Return value as follows:
   - GSW_statusOk: if successful
   - An error code in case an error occurs

*/
#define GSW_IRQ_STATUS_CLEAR _IOW(GSW_FLOW_MAGIC, 0x06, GSW_irq_t)

/*@}*/ /* GSW_IOCTL_IRQ */

/** \addtogroup GSW_IOCTL_SYS */
/*@{*/

/**
   \brief Forces a hardware reset of the switch device or switch macro. The device
   automatically comes back out of reset and contains the initial values.
   All previous configurations and statistics counters info are lost.

   \param GSW_reset_t Pointer to an \ref GSW_reset_t structure.

   \remarks The function returns an error code in case an error occurs.
            The error code is described in \ref GSW_return_t.

   \return Return value as follows:
   - GSW_statusOk: if successful
   - An error code in case an error occurs

   \remarks Not supported for all devices
*/
#define GSW_RESET	_IOW(GSW_FLOW_MAGIC, 0x0A, GSW_reset_t)

/**
   \brief Read out additional traffic flow (RMON) counters.
   The zero-based 'nPortId' structure element describes the physical switch
   port for the requested statistic information.

   \param GSW_RMON_extendGet_t  Pointer to a pre-allocated
   \ref GSW_RMON_extendGet_t structure. The structure element 'nPortId' is
   an input parameter that describes from which port to read the RMON counter.
   All remaining structure elements are filled with the counter values.
   The counter assignment needs to be done during the flow definition,
   for example in \ref GSW_PCE_RULE_WRITE.

   \remarks The function returns an error in case the given 'nPortId' is
   out of range.

   \remarks The function returns an error code in case an error occurs.
            The error code is described in \ref GSW_return_t.

   \return Return value as follows:
   - GSW_statusOk: if successful
   - An error code in case an error occurs
*/
#define GSW_RMON_EXTEND_GET	_IOWR(GSW_FLOW_MAGIC, 0x0B, GSW_RMON_extendGet_t)

/** \brief This command sets the packet timestamp reference counter.
    This reference timer is a switch global timer which is used by the
    packet timestamp capture when sending and receiving Ethernet port level.

    The command \ref GSW_TIMESTAMP_TIMER_GET allows to read out
    the current reference timer.

   \param GSW_TIMESTAMP_Timer_t Pointer to an \ref GSW_TIMESTAMP_Timer_t structure.

   \remarks The function returns an error code in case an error occurs.
            The error code is described in \ref GSW_return_t.

   \return Return value as follows:
   - GSW_statusOk: if successful
   - An error code in case an error occurs
*/
#define GSW_TIMESTAMP_TIMER_SET _IOW(GSW_FLOW_MAGIC, 0x0C, GSW_TIMESTAMP_Timer_t)

/** \brief This command reads out the switch global reference timer counter that is
    used by the packet timestamp capture when sending and receiving Ethernet port level.

    This reference timer is useful when processing the packet related
    timestamp information for delay calculation.

    The reference timer can be configured by \ref GSW_TIMESTAMP_TIMER_SET.

   \param GSW_TIMESTAMP_Timer_t Pointer to an \ref GSW_TIMESTAMP_Timer_t structure.

   \remarks The function returns an error code in case an error occurs.
            The error code is described in \ref GSW_return_t.

   \return Return value as follows:
   - GSW_statusOk: if successful
   - An error code in case an error occurs
*/
#define GSW_TIMESTAMP_TIMER_GET _IOWR(GSW_FLOW_MAGIC, 0x0D, GSW_TIMESTAMP_Timer_t)

/** \brief This command reads out the port related timestamp values. This timestamp is captured
    for ingress and egress packets triggered due to a traffic flow table timestamp action.
    A switch global reference timer is used for the timestamp capture operation.
    This global timer can be access by using \ref GSW_TIMESTAMP_TIMER_SET
    and \ref GSW_TIMESTAMP_TIMER_GET.

    A port related packet timestamp is triggered by the flow table
    action 'eTimestampAction'.

   \param GSW_TIMESTAMP_PortRead_t Pointer to
      an \ref GSW_TIMESTAMP_PortRead_t structure.

   \remarks The function returns an error code in case an error occurs.
            The error code is described in \ref GSW_return_t.

   \return Return value as follows:
   - GSW_statusOk: if successful
   - An error code in case an error occurs
*/
#define GSW_TIMESTAMP_PORT_READ _IOWR(GSW_FLOW_MAGIC, 0x0E, GSW_TIMESTAMP_PortRead_t)

/*@}*/ /* GSW_IOCTL_SYS */

#endif /* _LANTIQ_GSW_FLOW_H_ */
