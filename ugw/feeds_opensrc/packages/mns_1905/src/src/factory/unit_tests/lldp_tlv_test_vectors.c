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

#include "lldp_tlvs.h"


// This file contains test vectors than can be used to check the
// "parse_lldp_TLV_from_packet()" and "forge_lldp_TLV_from_structure()"
// functions
//
// Each test vector is made up of three variables:
//
//   - A TLV structure
//   - An array of bits representing the network packet
//   - An variable holding the length of the packet
//
// Note that some test vectors can be used to test both functions, while others
// can only be used to test "forge_lldp_TLV_from_structure()" or
// "parse_lldp_TLV_from_packet()":
//
//   - Test vectors marked with "TLV --> packet" can only be used to test the
//     "forge_lldp_TLV_from_structure()" function.
//
//   - Test vectors marked with "TLV <-- packet" can only be used to test the
//     "parse_lldp_TLV_from_packet()" function.
//
//   - All the other test vectors are marked with "TLC <--> packet", meaning
//     they can be used to test  both functions.
//
// The reason this is happening is that, according to the standard, sometimes
// bits are ignored/changed/forced-to-a-value when forging a packet. Thus, not
// all test vectors are "inversible" (ie. forge(parse(stream)) != x)
//
// This is how you use these test vectors:
//
//   A) stream = forge_lldp_TLV_from_structure(tlv_xxx, &stream_len);
//
//   B) tlv = parse_lldp_TLV_from_packet(stream_xxx); 
//


////////////////////////////////////////////////////////////////////////////////
//// Test vector 001 (TLV <--> packet)
////////////////////////////////////////////////////////////////////////////////

struct endOfLldppduTLV lldp_tlv_structure_001 =
{
    .tlv_type          = TLV_TYPE_END_OF_LLDPPDU,
};

INT8U lldp_tlv_stream_001[] =
{
    0x00, 0x00,
};

INT16U lldp_tlv_stream_len_001 = 2;


////////////////////////////////////////////////////////////////////////////////
//// Test vector 002 (TLV <--> packet)
////////////////////////////////////////////////////////////////////////////////

struct chassisIdTLV lldp_tlv_structure_002 =
{
    .tlv_type            = TLV_TYPE_CHASSIS_ID,
    .chassis_id_subtype  = CHASSIS_ID_TLV_SUBTYPE_MAC_ADDRESS,
    .chassis_id          = {0x01, 0x02, 0x03, 0x04, 0x05, 0x06},
};

INT8U lldp_tlv_stream_002[] =
{
    0x02, 0x07,
    0x04,
    0x01, 0x02, 0x03, 0x04, 0x05, 0x06,
};

INT16U lldp_tlv_stream_len_002 = 9;


////////////////////////////////////////////////////////////////////////////////
//// Test vector 003 (TLV <--> packet)
////////////////////////////////////////////////////////////////////////////////

struct portIdTLV lldp_tlv_structure_003 =
{
    .tlv_type            = TLV_TYPE_PORT_ID,
    .port_id_subtype     = PORT_ID_TLV_SUBTYPE_MAC_ADDRESS,
    .port_id             = {0x01, 0x02, 0x03, 0x04, 0x05, 0x06},
};

INT8U lldp_tlv_stream_003[] =
{
    0x04, 0x07,
    0x03,
    0x01, 0x02, 0x03, 0x04, 0x05, 0x06,
};

INT16U lldp_tlv_stream_len_003 = 9;


////////////////////////////////////////////////////////////////////////////////
//// Test vector 004 (TLV <--> packet)
////////////////////////////////////////////////////////////////////////////////

struct timeToLiveTypeTLV lldp_tlv_structure_004 =
{
    .tlv_type            = TLV_TYPE_TIME_TO_LIVE,
    .ttl                 = TIME_TO_LIVE_TLV_1905_DEFAULT_VALUE,
};

INT8U lldp_tlv_stream_004[] =
{
    0x06, 0x02,
    0x00, 0xb4,
};

INT16U lldp_tlv_stream_len_004 = 4;
