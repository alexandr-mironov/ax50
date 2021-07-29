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

#ifndef _MEDIA_SPECIFIC_BLOBS_H_
#define _MEDIA_SPECIFIC_BLOBS_H_


////////////////////////////////////////////////////////////////////////////////
// Structure type used for generic interfaces
////////////////////////////////////////////////////////////////////////////////

// The 1905 standard originally only recognized a limited set of interface
// types (IEEE802.11, IEEE802.3, IEEE1901, MOCA, ...) and for each of these
// types some parameters were defined (for example, the "bssid" and other
// things for IEEE802.11 interfaces, the "networ).
//
// Later, the standard was expanded to accept arbitrary parameters from all
// types of interfaces. This is done by using the next structure.
//
struct genericInterfaceType
{
    INT8U oui[3];           // Three bytes containing either the
                            // "Organizationally Unique Identifier"
                            // ("http://standards.ieee.org/develop/regauth/oui")
                            // or the "Company ID"
                            // ("http://standards.ieee.org/develop/regauth/cid")
                            // responsible for this particular interface type.

    char *generic_phy_description_xml_url;
                            // NULL terminated string pointing to the URL of
                            // the "Generic Phy XML Description Document" that
                            // describes the properties of this interface type.
                            // This document must conform to the "Generic Phy
                            // XML schema"
                            // ("http://standards.ieee.org/downloads/1905/GenericPhyInfoV1.xsd")
                           
    INT8U variant_index;    // The "Generic Phy XML Description Document" might
                            // might contain more than one "class" of
                            // interfaces for each OUI. This variable is used
                            // to identify which class/variant is the one that
                            // applies to this particular interface type.

    char *variant_name;     // NULL terminated string containing the "friendly
                            // name" this variant receives in the "Generic Phy
                            // XML Description Document".
                            // Must not be longer than 32 bytes (including the
                            // final NULL character).
                            //   NOTE: The OUI and variant_index are
                            //   enough to identify a variant inside a
                            //   "Generic Phy XML Description Document",
                            //   however we required this field too for
                            //   convinience.

    union _mediaSpecific
    {
        struct _ituGhn
        {
            // This is the structure to fill when:
            //
            //  - 'generic_phy_description_xml_url' is set to
            //    "http://handle.itu.int/11.1002/3000/1706"
            //
            //  - 'oui' is set to 00:19:A7
            //
            //  - ...and the 'variant_index' is set to either 1, 2, 3 or 4

            INT8U dni[2];   // Domain name identifier (see clause
                            // 8.6.8.2.1 of "ITU-T G.9961")
        } ituGhn;

        struct _unsupported
        {
            // This is the structure to fill in all other cases. If you don't
            // want to provide media specific data, just set 'bytes_nr' to '0',
            // otherwise use this array to send arbitrary data to upper layers
            //
            INT16U  bytes_nr;
            INT8U  *bytes;

        } unsupported;

    } media_specific;

};



////////////////////////////////////////////////////////////////////////////////
// Main API functions
////////////////////////////////////////////////////////////////////////////////

// This function receives a pointer to a "genericInterfaceType" structure and
// then allocates and returns a buffer holding the array of bytes that should
// be inserted in the 1905 "media_specific" fields present in several TLVs
// ("generic phy device information TLV", "push button generic phy event
// notification TLV" and "power off interface TLV").
//
// This function "translates" the "genericInterfaceType" structure fields
// specific for each supported interface type into a stream of bytes according
// to the corresponding standard that applies to each particular type of
// interface.
//
// The returned pointer can later be free with "free_media_specific_blob()"
//
// 'len' is an output argument that holds the length of the returned buffer.
//
INT8U *forge_media_specific_blob(struct genericInterfaceType *m, INT16U *len);

// 'forge_media_specific_blob()' returns a regular buffer which can be freed
// using this macro defined to be PLATFORM_FREE
//
#define  free_media_specific_blob  PLATFORM_FREE

#endif
