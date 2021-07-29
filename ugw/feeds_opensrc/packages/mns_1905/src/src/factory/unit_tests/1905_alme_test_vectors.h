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

#ifndef _1905_ALME_TEST_VECTORS_H_
#define _1905_ALME_TEST_VECTORS_H_

#include "1905_alme.h"

extern struct getIntfListRequestALME         x1905_alme_structure_001;
extern INT8U                                 x1905_alme_stream_001[];
extern INT16U                                x1905_alme_stream_len_001;

extern struct getIntfListResponseALME        x1905_alme_structure_002;
extern INT8U                                 x1905_alme_stream_002[];
extern INT16U                                x1905_alme_stream_len_002;

extern struct getIntfListResponseALME        x1905_alme_structure_003;
extern INT8U                                 x1905_alme_stream_003[];
extern INT16U                                x1905_alme_stream_len_003;

extern struct getIntfListResponseALME        x1905_alme_structure_004;
extern INT8U                                 x1905_alme_stream_004[];
extern INT16U                                x1905_alme_stream_len_004;

extern struct setIntfPwrStateRequestALME     x1905_alme_structure_005;
extern INT8U                                 x1905_alme_stream_005[];
extern INT16U                                x1905_alme_stream_len_005;

extern struct setIntfPwrStateRequestALME     x1905_alme_structure_006;
extern INT8U                                 x1905_alme_stream_006[];
extern INT16U                                x1905_alme_stream_len_006;

extern struct setIntfPwrStateConfirmALME     x1905_alme_structure_007;
extern INT8U                                 x1905_alme_stream_007[];
extern INT16U                                x1905_alme_stream_len_007;

extern struct setIntfPwrStateConfirmALME     x1905_alme_structure_008;
extern INT8U                                 x1905_alme_stream_008[];
extern INT16U                                x1905_alme_stream_len_008;

extern struct getIntfPwrStateRequestALME     x1905_alme_structure_009;
extern INT8U                                 x1905_alme_stream_009[];
extern INT16U                                x1905_alme_stream_len_009;

extern struct getIntfPwrStateResponseALME    x1905_alme_structure_010;
extern INT8U                                 x1905_alme_stream_010[];
extern INT16U                                x1905_alme_stream_len_010;

extern struct setFwdRuleRequestALME          x1905_alme_structure_011;
extern INT8U                                 x1905_alme_stream_011[];
extern INT16U                                x1905_alme_stream_len_011;

extern struct setFwdRuleRequestALME          x1905_alme_structure_012;
extern INT8U                                 x1905_alme_stream_012[];
extern INT16U                                x1905_alme_stream_len_012;

extern struct setFwdRuleConfirmALME          x1905_alme_structure_013;
extern INT8U                                 x1905_alme_stream_013[];
extern INT16U                                x1905_alme_stream_len_013;

extern struct getFwdRulesRequestALME         x1905_alme_structure_014;
extern INT8U                                 x1905_alme_stream_014[];
extern INT16U                                x1905_alme_stream_len_014;

extern struct getFwdRulesResponseALME        x1905_alme_structure_015;
extern INT8U                                 x1905_alme_stream_015[];
extern INT16U                                x1905_alme_stream_len_015;

extern struct getFwdRulesResponseALME        x1905_alme_structure_016;
extern INT8U                                 x1905_alme_stream_016[];
extern INT16U                                x1905_alme_stream_len_016;

extern struct getFwdRulesResponseALME        x1905_alme_structure_017;
extern INT8U                                 x1905_alme_stream_017[];
extern INT16U                                x1905_alme_stream_len_017;

extern struct modifyFwdRuleRequestALME       x1905_alme_structure_018;
extern INT8U                                 x1905_alme_stream_018[];
extern INT16U                                x1905_alme_stream_len_018;

extern struct modifyFwdRuleConfirmALME       x1905_alme_structure_019;
extern INT8U                                 x1905_alme_stream_019[];
extern INT16U                                x1905_alme_stream_len_019;

extern struct modifyFwdRuleConfirmALME       x1905_alme_structure_020;
extern INT8U                                 x1905_alme_stream_020[];
extern INT16U                                x1905_alme_stream_len_020;

extern struct removeFwdRuleRequestALME       x1905_alme_structure_021;
extern INT8U                                 x1905_alme_stream_021[];
extern INT16U                                x1905_alme_stream_len_021;

extern struct removeFwdRuleConfirmALME       x1905_alme_structure_022;
extern INT8U                                 x1905_alme_stream_022[];
extern INT16U                                x1905_alme_stream_len_022;

extern struct getMetricRequestALME           x1905_alme_structure_023;
extern INT8U                                 x1905_alme_stream_023[];
extern INT16U                                x1905_alme_stream_len_023;

extern struct getMetricResponseALME          x1905_alme_structure_024;
extern INT8U                                 x1905_alme_stream_024[];
extern INT16U                                x1905_alme_stream_len_024;

extern struct getMetricResponseALME          x1905_alme_structure_025;
extern INT8U                                 x1905_alme_stream_025[];
extern INT16U                                x1905_alme_stream_len_025;

#endif

