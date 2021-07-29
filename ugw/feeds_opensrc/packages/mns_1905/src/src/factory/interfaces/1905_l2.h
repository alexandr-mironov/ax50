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

#ifndef _1905_L2_H_
#define _1905_L2_H_

// Ethernet types por 1905 and LLDP packets
//
#define ETHERTYPE_1905  (0x893a)
#define ETHERTYPE_LLDP  (0x88cc)


// 1905 multicast address ("01:80:C2:00:00:13")
//
#define MCAST_1905_B0 (0x01)
#define MCAST_1905_B1 (0x80)
#define MCAST_1905_B2 (0xC2)
#define MCAST_1905_B3 (0x00)
#define MCAST_1905_B4 (0x00)
#define MCAST_1905_B5 (0x13)
#define MCAST_1905  {MCAST_1905_B0, MCAST_1905_B1, MCAST_1905_B2, MCAST_1905_B3, MCAST_1905_B4, MCAST_1905_B5}


// LLDP nearest bridge multicast address ("01:80:C2:00:00:0E")
//
#define MCAST_LLDP_B0  (0x01)
#define MCAST_LLDP_B1  (0x80)
#define MCAST_LLDP_B2  (0xC2)
#define MCAST_LLDP_B3  (0x00)
#define MCAST_LLDP_B4  (0x00)
#define MCAST_LLDP_B5  (0x0E)
#define MCAST_LLDP  {MCAST_LLDP_B0, MCAST_LLDP_B1, MCAST_LLDP_B2, MCAST_LLDP_B3, MCAST_LLDP_B4, MCAST_LLDP_B5}

#endif

