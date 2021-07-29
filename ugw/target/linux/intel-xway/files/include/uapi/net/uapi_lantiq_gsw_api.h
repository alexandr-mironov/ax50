#ifndef _LTQ_UAPI_GSW_KERNEL_API_H_
#define _LTQ_UAPI_GSW_KERNEL_API_H_
/*-----UAPI header file for lantiq_gsw_api.h-----*/

#include "uapi_lantiq_gsw.h"
#include "uapi_lantiq_gsw_flow.h"

/** Definition of the device handle that is retrieved during
    the \ref gsw_api_kopen call. This handle is used to access the switch
    device while calling \ref gsw_api_kioctl. */
typedef unsigned int GSW_API_HANDLE;

/**
   Request a device handle for a dedicated Ethernet switch device. The switch
   device is identified by the given device name (e.g. "/dev/switch/1").
   The device handle is the return value of this function. This handle is
   used to access the switch parameter and features while
   calling \ref gsw_api_kioctl. Please call the function
   \ref gsw_api_kclose to release a device handle that is not needed anymore.

   \param name Pointer to the device name of the requested Ethernet switch device.

   \remarks The client kernel module should check the function return value.
   A returned zero indicates that the resource allocation failed.

   \return Return the device handle in case the requested device is available.
   It returns a zero in case the device does not exist or is blocked
   by another application.
*/
GSW_API_HANDLE gsw_api_kopen(char *name);

/**
   Calls the switch API driver implementation with the given command and the
   parameter argument. The called Ethernet switch device is identified by the
   given device handle. This handle was previously requested by
   calling gsw_api_kopen function.

   \param handle Ethernet switch device handle, given by \ref gsw_api_kopen.
   \param command Switch API command to perform.
   \param arg Command arguments. This argument is basically a reference to
   the command parameter structure.

   \remarks The commands and arguments are the same as normally used over
   the Linux ioctl interface from user space.

   \return Return value as follows:
   - GSW_statusOk: if successful
   - An error code in case an error occurred.
*/
int gsw_api_kioctl(GSW_API_HANDLE handle, unsigned int command, unsigned int arg);

#endif /* _LTQ_UAPI_GSW_KERNEL_API_H__ */
