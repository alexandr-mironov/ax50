/******************************************************************************

                         Copyright (c) 2012, 2014, 2015
                            Lantiq Deutschland GmbH

  For licensing information, see the file 'LICENSE' in the root folder of
  this software module.

******************************************************************************/
 
#ifndef _LTQ_GSW_KERNEL_API_H_
#define _LTQ_GSW_KERNEL_API_H_

#include "lantiq_gsw.h"
#include "lantiq_gsw_flow.h"
#include "lantiq_gsw_routing.h"
#ifdef __KERNEL__
#include "net/uapi_lantiq_gsw_api.h"
#else
#include "uapi_lantiq_gsw_api.h"
#endif
/* Group definitions for Doxygen */
/** \defgroup ETHSW_KERNELAPI Ethernet Switch Linux Kernel Interface
    This chapter describes the entire interface to access and
    configure the various services of the Ethernet switch module of xRX200/xRX300/xRX500 family within the Linux kernel space. */

/*@{*/

/**
   Releases an Ethernet switch device handle which was previously
   allocated by \ref gsw_api_kopen.

   \param handle Ethernet switch device handle, given by \ref gsw_api_kopen.

   \return Return value as follows:
   - GSW_statusOk: if successful
   - An error code in case an error occurred.
*/
int gsw_api_kclose(GSW_API_HANDLE handle);

/*@}*/ /* GSWIP_ROUTE_IOCTL */

extern void gsw_api_disable_switch_ports(void);

#endif /* _LTQ_GSW_KERNEL_API_H_ */
