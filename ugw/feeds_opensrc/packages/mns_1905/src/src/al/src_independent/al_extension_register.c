/*
 *  Broadband Forum BUS (Broadband User Services) Work Area
 *
 *  Copyright (c) 2017, Broadband Forum
 *  Copyright (c) 2017, MaxLinear, Inc. and its affiliates
 *  
 *  Redistribution and use in source and binary forms, with or
 *  without modification, are permitted provided that the following
 *  conditions are met:
 *  
 *  1. Redistributions of source code must retain the above copyright
 *     notice, this list of conditions and the following disclaimer.
 *  
 *  2. Redistributions in binary form must reproduce the above
 *     copyright notice, this list of conditions and the following
 *     disclaimer in the documentation and/or other materials
 *     provided with the distribution.
 *  
 *  3. Neither the name of the copyright holder nor the names of its
 *     contributors may be used to endorse or promote products
 *     derived from this software without specific prior written
 *     permission.
 *  
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND
 *  CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES,
 *  INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 *  MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 *  DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR
 *  CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 *  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
 *  NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 *  LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 *  CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
 *  STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 *  ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
 *  ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *  
 *  The above license is used as a license under copyright only.
 *  Please reference the Forum IPR Policy for patent licensing terms
 *  <https://www.broadband-forum.org/ipr-policy>.
 *  
 *  Any moral rights which are necessary to exercise under the above
 *  license grant are also deemed granted under this license.
 */


// This is the file where you must register your new non-standard ieee1905
// functionality
//
// You must simply:
// - Add the 'include' files where your registration functions are declared
// - Register your protocol extensions in 'start1905ALProtocolExtension()'
//
// Example: BBF protocol extension
//
// ////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// //   // BBF extensions                                                                                        //
// //   #include "bbf_send.h"                                                                                    //
// //   #include "bbf_recv.h"                                                                                    //
// //                                                                                                            //
// //   INT8U start1905ALProtocolExtension(void)                                                                 //
// //   {                                                                                                        //
// //       // BBF protocol extension                                                                            //
// //       //                                                                                                   //
// //       PLATFORM_PRINTF_DEBUG_DETAIL("Registering BBF protocol extensions...\n");                            //
// //       if (0 == register1905CmduExtension("BBF", CBKSend1905BBFExtensions, CBKprocess1905BBFExtensions))    //
// //       {                                                                                                    //
// //           PLATFORM_PRINTF_DEBUG_ERROR("Could not register BBF protocol extension\n");                      //
// //           return 0;                                                                                        //
// //       }                                                                                                    //
// //                                                                                                            //
// //       if (0 == register1905AlmeDumpExtension("BBF",                                                        //
// //                                              CBKObtainBBFExtendedLocalInfo,                                //
// //                                              CBKUpdateBBFExtendedInfo,                                     //
// //                                              CBKDumpBBFExtendedInfo))                                      //
// //       {                                                                                                    //
// //           PLATFORM_PRINTF_DEBUG_ERROR("Could not register BBF datamodel protocol extension\n");            //
// //           return 0;                                                                                        //
// //       }                                                                                                    //
// //   }                                                                                                        //
// ////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Note: Please, take this source code example as a template.
//       You can find the 'start1905ALProtocolExtension()' function at the end
//       of the file.
//
//
// Brief description
// -----------------
//
// The ieee1905 standard opens the door to non-standard extensions. Neither new
// CMDUs nor new TLVs can be created, but there is a TLV (Vendor Specific TLV)
// which can be used to embed any kind of information.
//
// So, the main idea is simple. Add as many Vendor Specific TLVs as you need in
// the appropiated CMDUs.
//
// But... how?
// These new TLVs must be added when the appropiated CMDU is built. Likewise,
// these new TLVs must be processed when a CMDU is received and act accordingly.
// Our ieee1905 stack implementation supports this functionality via callbacks:
// - one used to add Vendor Specific TLVs when a CMDU is built
// - one used to process the incoming Vendor Specific TLVs
//
// Use 'register1905CmduExtension()' to register these two callbacks.
//
// Note: Please try to keep the following function naming convention:
//       CBKSend1905***Extensions
//       CBKProcess1905***Extensions
//
//       where *** identifies the registered extension (BBF in the above example)
//
// All the CBKSend1905***Extensions() functions will be called from send1905RawPacket()
// which is implemented in the 'al_send.c' file. At this point, the CMDU is already
// built by the stack, and these CBKSend1905***Extensions() functions will be responsible
// for extending the list of TLVs included in this CMDU.
//
// All the CBKprocess1905***Extensions() functions will be called from process1905Cmdu()
// which is implemented in 'al_recv.c' file. At this point, the incoming CMDU has not been
// processed by the stack yet. Each CBKSend1905***Extensions() function will be responsible
// for processing its own Vendor Specific TLVs (ie. CMDU contains extensions from several
// third-party implementations). Finally, the stack will process the standard TLvs and
// free all no longer used resources.
//
// So, it's easy, register one callback for each direction (incoming/outgoing CMDU).
// This way, non-standard data will be shared to other 1905 nodes (via CMDU exchanges)
// ... but ... is that enough? No...
//
// How do we obtain this non-standard data from an external entity?
// It makes sense to get this data from an external entity who will be responsible for
// analyzing it and taking decisions accordingly (i.e. the main router retrieving
// info from the whole network)
//
// The ieee1905 standard does ***not*** provide a way to get non-standard info.
// So what can we do? ... well, this stack implements a non-standard ALME called
// 'dnd' which will return the whole datamodel data (in a text-plain format).
// Each third-party developer may extend this ALME response to include its own
// non-standard info by using the next function:
//
//   register1905AlmeDumpExtension()
//
// This function registers three callbacks:
// - CBKObtain***ExtendedLocalInfo: get non-standard info from the device itself
// - CBKUpdate***ExtendedInfo     : update non-standard info in the datamodel
// - CBKDump***ExtendedInfo       : dump non-standard datamodel info
//
// Why are these three callbacks required? This is how the ieee1905 stack works:
// - when a 'dnd' ALME request is received, the whole datamodel is dumped (the
//   stack runs through the datamodel generating the report which will be embedded
//   inside the ALME response). In this regard, the whole datamodel is expected to
//   be updated. Datamodel info related to the neighbor devices is updated
//   with the CMDU transactions, but datamodel info related to the device itself
//   is updated internally and only when it's required (not periodically), like
//   in this scenario. Otherwise, ALME response would contain obsolete info.
//   Updating the device itself info is presented as a two step process: first,
//   obtain the non-standard data (embedded in Vendor Specific TLVs), and then
//   update the datamodel with these extra TLVs.
//
// Take the BBF ALME callbacks as a reference implementation.
//


#include "platform.h"
#include "1905_cmdus.h"
#include "1905_tlvs.h"
#include "al_extension.h"

#ifdef REGISTER_EXTENSION_BBF
// BBF extensions
#  include "bbf_send.h"  // CBKSend1905BBFExtensions, CBKObtainBBFExtendedLocalInfo,
                         // CBKUpdateBBFExtendedInfo, CBKDumpBBFExtendedInfo
#  include "bbf_recv.h"  // CBKprocess1905BBFExtensions
#endif


////////////////////////////////////////////////////////////////////////////////
// Public function (extensions entry point).
////////////////////////////////////////////////////////////////////////////////

INT8U start1905ALExtensions(void)
{
#ifdef REGISTER_EXTENSION_BBF
    // BBF protocol extension
    //
    PLATFORM_PRINTF_DEBUG_DETAIL("Registering BBF protocol extensions...\n");
    if (0 == register1905CmduExtension("BBF", CBKprocess1905BBFExtensions, CBKSend1905BBFExtensions))
    {
        PLATFORM_PRINTF_DEBUG_ERROR("Could not register BBF protocol extension\n");
        return 0;
    }

    if (0 == register1905AlmeDumpExtension("BBF",
                                           CBKObtainBBFExtendedLocalInfo,
                                           CBKUpdateBBFExtendedInfo,
                                           CBKDumpBBFExtendedInfo))
    {
        PLATFORM_PRINTF_DEBUG_ERROR("Could not register BBF datamodel protocol extension\n");
        return 0;
    }
#endif

    // Feel free to add more 1905 protocol extensions
    //
    // ...


    return 1;
}
