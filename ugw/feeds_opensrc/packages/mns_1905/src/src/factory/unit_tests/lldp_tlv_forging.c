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

//
// This file tests the "forge_lldp_TLV_from_structure()" function by providing
// some test input structures and checking the generated output stream.
//

#include "platform.h"
#include "lldp_tlvs.h"
#include "lldp_tlv_test_vectors.h"

INT8U _check(const char *test_description, INT8U *input, INT8U *expected_output, INT16U expected_output_len)
{
    INT8U  result;
    INT8U *real_output;
    INT16U real_output_len;
    
    real_output = forge_lldp_TLV_from_structure((INT8U *)input, &real_output_len);

    if (NULL == real_output)
    {
        PLATFORM_PRINTF("%-100s: KO !!!\n", test_description);
        PLATFORM_PRINTF("  forge_lldp_TLV_from_structure() returned a NULL pointer\n");

        return 1;
    }

    if ((expected_output_len == real_output_len) && (0 == PLATFORM_MEMCMP(expected_output, real_output, real_output_len)))
    {
        result = 0;
        PLATFORM_PRINTF("%-100s: OK\n", test_description);
    }
    else
    {
        INT16U i;

        result = 1; 
        PLATFORM_PRINTF("%-100s: KO !!!\n", test_description);
        PLATFORM_PRINTF("  Expected output: ");
        for (i=0; i<expected_output_len; i++)
        {
            PLATFORM_PRINTF("%02x ",expected_output[i]);
        }
        PLATFORM_PRINTF("\n");
        PLATFORM_PRINTF("  Real output    : ");
        for (i=0; i<real_output_len; i++)
        {
            PLATFORM_PRINTF("%02x ",real_output[i]);
        }
        PLATFORM_PRINTF("\n");
    }

    return result;
}


int main(void)
{
    INT8U result = 0;

    #define LLDPTLVFORGE001 "LLDPTLVFORGE001 - Forge end of LLDP TLV (lldp_tlv_structure_001)"
    result += _check(LLDPTLVFORGE001, (INT8U *)&lldp_tlv_structure_001, lldp_tlv_stream_001, lldp_tlv_stream_len_001);

    #define LLDPTLVFORGE002 "LLDPTLVFORGE002 - Forge chassis ID TLV (lldp_tlv_structure_002)"
    result += _check(LLDPTLVFORGE002, (INT8U *)&lldp_tlv_structure_002, lldp_tlv_stream_002, lldp_tlv_stream_len_002);

    #define LLDPTLVFORGE003 "LLDPTLVFORGE003 - Forge port ID TLV (lldp_tlv_structure_003)"
    result += _check(LLDPTLVFORGE003, (INT8U *)&lldp_tlv_structure_003, lldp_tlv_stream_003, lldp_tlv_stream_len_003);

    #define LLDPTLVFORGE004 "LLDPTLVFORGE004 - Forge time to live TLV (lldp_tlv_structure_004)"
    result += _check(LLDPTLVFORGE004, (INT8U *)&lldp_tlv_structure_004, lldp_tlv_stream_004, lldp_tlv_stream_len_004);

    // Return the number of test cases that failed
    //
    return result;
}






