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
// This file tests the "parse_lldp_TLV_from_packet()" function by providing
// some test input streams and checking the generated output structure.
//

#include "platform.h"
#include "utils.h"

#include "lldp_tlvs.h"
#include "lldp_tlv_test_vectors.h"

INT8U _check(const char *test_description, INT8U *input, INT8U *expected_output)
{
    INT8U  result;
    INT8U *real_output;
    
    real_output = parse_lldp_TLV_from_packet(input);

    if (0 == compare_lldp_TLV_structures(real_output, expected_output))
    {
        result = 0;
        PLATFORM_PRINTF("%-100s: OK\n", test_description);
    }
    else
    {
        result = 1; 
        PLATFORM_PRINTF("%-100s: KO !!!\n", test_description);
        PLATFORM_PRINTF("  Expected output:\n");
        visit_lldp_TLV_structure(expected_output, print_callback, PLATFORM_PRINTF, "");
        PLATFORM_PRINTF("  Real output    :\n");
        visit_lldp_TLV_structure(real_output, print_callback, PLATFORM_PRINTF, "");
    }

    return result;
}


int main(void)
{
    INT8U result = 0;

    #define LLDPTLVPARSE001 "LLDPTLVPARSE001 - Parse end of LLDP TLV (lldp_tlv_stream_001)"
    result += _check(LLDPTLVPARSE001, lldp_tlv_stream_001, (INT8U *)&lldp_tlv_structure_001);

    #define LLDPTLVPARSE002 "LLDPTLVPARSE002 - Parse chassis ID TLV (lldp_tlv_stream_002)"
    result += _check(LLDPTLVPARSE002, lldp_tlv_stream_002, (INT8U *)&lldp_tlv_structure_002);

    #define LLDPTLVPARSE003 "LLDPTLVPARSE003 - Parse port ID TLV (lldp_tlv_stream_003)"
    result += _check(LLDPTLVPARSE003, lldp_tlv_stream_003, (INT8U *)&lldp_tlv_structure_003);

    #define LLDPTLVPARSE004 "LLDPTLVPARSE004 - Parse time to live TLV (lldp_tlv_stream_004)"
    result += _check(LLDPTLVPARSE004, lldp_tlv_stream_004, (INT8U *)&lldp_tlv_structure_004);

    // Return the number of test cases that failed
    //
    return result;
}






