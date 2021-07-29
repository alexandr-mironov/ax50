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

#ifndef _BBF_TLV_TEST_VECTORS_H_
#define _BBF_TLV_TEST_VECTORS_H_

#include "bbf_tlvs.h"

#define CHECK_TRUE     0 // Check a successful parse/forge operation
#define CHECK_FALSE    1 // Check a wrong parse operation (malformed frame)

extern struct linkMetricQueryTLV                       bbf_tlv_structure_001;
extern INT8U                                           bbf_tlv_stream_001[];
extern INT16U                                          bbf_tlv_stream_len_001;

extern struct linkMetricQueryTLV                       bbf_tlv_structure_002;
extern INT8U                                           bbf_tlv_stream_002[];
extern INT8U                                           bbf_tlv_stream_002b[];
extern INT16U                                          bbf_tlv_stream_len_002;

extern struct linkMetricQueryTLV                       bbf_tlv_structure_003;
extern INT8U                                           bbf_tlv_stream_003[];
extern INT16U                                          bbf_tlv_stream_len_003;

extern struct linkMetricQueryTLV                       bbf_tlv_structure_004;
extern INT8U                                           bbf_tlv_stream_004[];
extern INT8U                                           bbf_tlv_stream_004b[];
extern INT16U                                          bbf_tlv_stream_len_004;

extern struct linkMetricQueryTLV                       bbf_tlv_structure_005;
extern INT8U                                           bbf_tlv_stream_005[];
extern INT16U                                          bbf_tlv_stream_len_005;

extern struct linkMetricQueryTLV                       bbf_tlv_structure_006;
extern INT8U                                           bbf_tlv_stream_006[];
extern INT8U                                           bbf_tlv_stream_006b[];
extern INT16U                                          bbf_tlv_stream_len_006;

extern struct linkMetricQueryTLV                       bbf_tlv_structure_007;
extern INT8U                                           bbf_tlv_stream_007[];
extern INT16U                                          bbf_tlv_stream_len_007;

#endif

