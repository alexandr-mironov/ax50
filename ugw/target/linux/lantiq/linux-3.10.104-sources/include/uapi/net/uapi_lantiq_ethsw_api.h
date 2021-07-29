#ifndef _LTQ_UAPI_ETHSW_KERNEL_API_H_
#define _LTQ_UAPI_ETHSW_KERNEL_API_H_

#include "uapi_lantiq_ethsw.h"
#include "uapi_lantiq_ethsw_flow.h"

/** Definition of the device handle that is retrieved during
    the \ref ifx_ethsw_kopen call. This handle is used to access the switch
    device while calling \ref ifx_ethsw_kioctl. */
typedef unsigned int LTQ_ETHSW_API_HANDLE;

/**
   Request a device handle for a dedicated Ethernet switch device. The switch
   device is identified by the given device name (e.g. "/dev/switch/1").
   The device handle is the return value of this function. This handle is
   used to access the switch parameter and features while
   calling \ref ifx_ethsw_kioctl. Please call the function
   \ref ifx_ethsw_kclose to release a device handle that is not needed anymore.

   \param name Pointer to the device name of the requested Ethernet switch device.

   \remarks The client kernel module should check the function return value.
   A returned zero indicates that the resource allocation failed.

   \return Return the device handle in case the requested device is available.
   It returns a zero in case the device does not exist or is blocked
   by another application.
*/
LTQ_ETHSW_API_HANDLE ltq_ethsw_api_kopen(char *name);

/**
   Calls the switch API driver implementation with the given command and the
   parameter argument. The called Ethernet switch device is identified by the
   given device handle. This handle was previously requested by
   calling \ref ifx_ethsw_kopen.

   \param handle Ethernet switch device handle, given by \ref ifx_ethsw_kopen.
   \param command Switch API command to perform.
   \param arg Command arguments. This argument is basically a reference to
   the command parameter structure.

   \remarks The commands and arguments are the same as normally used over
   the Linux ioctl interface from user space.

   \return Return value as follows:
   - LTQ_SUCCESS: if successful
   - An error code in case an error occurred.
*/
int ltq_ethsw_api_kioctl(LTQ_ETHSW_API_HANDLE handle, unsigned int command, unsigned int arg);


#endif /* _LTQ_UAPI_ETHSW_KERNEL_API_H_ */


