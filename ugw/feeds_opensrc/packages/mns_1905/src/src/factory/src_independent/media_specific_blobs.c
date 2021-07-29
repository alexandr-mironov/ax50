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

#include "platform.h"

#include "media_specific_blobs.h"


////////////////////////////////////////////////////////////////////////////////
// Actual API functions
////////////////////////////////////////////////////////////////////////////////

INT8U *forge_media_specific_blob(struct genericInterfaceType *m, INT16U *len)
{
    #define ITU_T_GHN_XML "http://handle.itu.int/11.1002/3000/1706"

    INT8U *ret;

    ret = NULL;

    if (NULL == m->generic_phy_description_xml_url)
    {
        return NULL;
    }

    if (0 == PLATFORM_MEMCMP(m->generic_phy_description_xml_url, ITU_T_GHN_XML, PLATFORM_STRLEN(ITU_T_GHN_XML)+1))
    {
        // This XML file defines the *same* media specific data format for all
        // interfaces that meet the following requirements:
        //
        //   - OUI     = 00:19:A7
        //   - Variant = 0, 1, 2, 3 or 4 (it also defines 10 and 11, but we will
        //               ignore these)

        if (
             m->oui[0] != 0x00 ||
             m->oui[1] != 0x19 ||
             m->oui[2] != 0xa7
           )
        {
            // Unknown OUI
        }
        else if (
             m->variant_index != 0 &&
             m->variant_index != 1 &&
             m->variant_index != 2 &&
             m->variant_index != 3 &&
             m->variant_index != 4
           )
        {
            // Unknown variant
        }
        else
        {
           // The 1905 media specific field is made up of FIVE bytes:
           //
           //   0x01, 0x00, 0x02, dni[0], dni[1]
           //
           // (see ITU-T G.9979 Tables 8.2 and 8.3)
           //
           *len   = 5;
           ret    = (INT8U *)PLATFORM_MALLOC(*len);
           ret[0] = 0x01;
           ret[1] = 0x00;
           ret[2] = 0x02;
           ret[3] = m->media_specific.ituGhn.dni[0];
           ret[4] = m->media_specific.ituGhn.dni[1];
        }
    }

    if (NULL == ret)
    {
        // If we get to this point and "ret" is still "NULL", that means that the
        // "XML"/"OUI"/"variant_index" combination has not been recognized, and thus
        // we will simply return the contents of the "unsupported" structure.
        //
        *len = m->media_specific.unsupported.bytes_nr;
        ret  = (INT8U *)PLATFORM_MALLOC(*len);

        PLATFORM_MEMCPY(ret, m->media_specific.unsupported.bytes, *len);
    }

    return ret;
}

