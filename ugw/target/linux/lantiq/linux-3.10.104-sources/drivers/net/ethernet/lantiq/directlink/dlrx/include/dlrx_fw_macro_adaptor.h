/*******************************************************************************

  Intel DirectLink driver
  Copyright(c) 2016 Intel Corporation.

  This program is free software; you can redistribute it and/or modify it
  under the terms and conditions of the GNU General Public License,
  version 2, as published by the Free Software Foundation.

  This program is distributed in the hope it will be useful, but WITHOUT
  ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
  FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
  more details.

  You should have received a copy of the GNU General Public License along with
  this program; if not, write to the Free Software Foundation, Inc.,
  51 Franklin St - Fifth Floor, Boston, MA 02110-1301 USA.

  The full GNU General Public License is included in this distribution in
  the file called "COPYING".

*******************************************************************************/
#ifndef __DLRX_FW_MACRO_ADAPTOR_H_
#define __DLRX_FW_MACRO_ADAPTOR_H_


/* 1 NOTE: This header files only defines macros
* for similar named elements in the specified structures.
*/


#include "dlrx_fw_data_structure_macro.h"

#define DLRX_FORM_SET_MACRO_NAME(name1, name2, ...)		\
	do {							\
		if (g_qca_hw == BEELINER_BOARD) { \
			name1##_BEELINER_##name2(__VA_ARGS__); \
		} else {						\
			name1##_PEREGRINE_##name2(__VA_ARGS__); \
		} \
	} while (0)


#define DLRX_FORM_GET_MACRO_NAME(name1, name2, ...) \
	((g_qca_hw == BEELINER_BOARD) ? name1##_BEELINER_##name2(__VA_ARGS__) : \
			name1##_PEREGRINE_##name2(__VA_ARGS__))



#define DLRX_RXPB_HDR_mcast_bcast_get_indirect(base, offset)   \
	DLRX_FORM_GET_MACRO_NAME(DLRX_RXPB_HDR, mcast_bcast_get_indirect, base, offset)

#define DLRX_RXPB_HDR_mcast_bcast_get_direct(dword)   \
	DLRX_FORM_GET_MACRO_NAME(DLRX_RXPB_HDR, mcast_bcast_get_direct, dword)

#define DLRX_RXPB_HDR_mcast_bcast_set_indirect(base, offset, val)   \
	DLRX_FORM_SET_MACRO_NAME(DLRX_RXPB_HDR, mcast_bcast_set_indirect, base, offset, val)

#define DLRX_RXPB_HDR_mcast_bcast_set_direct(dword, val)   \
	DLRX_FORM_SET_MACRO_NAME(DLRX_RXPB_HDR, mcast_bcast_set_direct, dword, val)

#define DLRX_RXPB_HDR_mcast_bcast_clear_indirect(base, offset)   \
	DLRX_FORM_SET_MACRO_NAME(DLRX_RXPB_HDR, mcast_bcast_clear_indirect, base, offset)

#define DLRX_RXPB_HDR_mcast_bcast_clear_direct(dword)   \
	DLRX_FORM_SET_MACRO_NAME(DLRX_RXPB_HDR, mcast_bcast_clear_direct, dword)


#define DLRX_RXPB_HDR_msdu_load_status_get_indirect(base, offset)   \
	DLRX_FORM_GET_MACRO_NAME(DLRX_RXPB_HDR, msdu_load_status_get_indirect, base, offset)

#define DLRX_RXPB_HDR_msdu_load_status_get_direct(dword)   \
	DLRX_FORM_GET_MACRO_NAME(DLRX_RXPB_HDR, msdu_load_status_get_direct, dword)

#define DLRX_RXPB_HDR_msdu_load_status_set_indirect(base, offset, val)   \
	DLRX_FORM_SET_MACRO_NAME(DLRX_RXPB_HDR, msdu_load_status_set_indirect, base, offset, val)

#define DLRX_RXPB_HDR_msdu_load_status_set_direct(dword, val)   \
	DLRX_FORM_SET_MACRO_NAME(DLRX_RXPB_HDR, msdu_load_status_set_direct, dword, val)

#define DLRX_RXPB_HDR_msdu_load_status_clear_indirect(base, offset)   \
	DLRX_FORM_SET_MACRO_NAME(DLRX_RXPB_HDR, msdu_load_status_clear_indirect, base, offset)

#define DLRX_RXPB_HDR_msdu_load_status_clear_direct(dword)   \
	DLRX_FORM_SET_MACRO_NAME(DLRX_RXPB_HDR, msdu_load_status_clear_direct, dword)


#define DLRX_RXPB_HDR_msdu_chain_num_get_indirect(base, offset)   \
	DLRX_FORM_GET_MACRO_NAME(DLRX_RXPB_HDR, msdu_chain_num_get_indirect, base, offset)

#define DLRX_RXPB_HDR_msdu_chain_num_get_direct(dword)   \
	DLRX_FORM_GET_MACRO_NAME(DLRX_RXPB_HDR, msdu_chain_num_get_direct, dword)

#define DLRX_RXPB_HDR_msdu_chain_num_set_indirect(base, offset, val)   \
	DLRX_FORM_SET_MACRO_NAME(DLRX_RXPB_HDR, msdu_chain_num_set_indirect, base, offset, val)

#define DLRX_RXPB_HDR_msdu_chain_num_set_direct(dword, val)   \
	DLRX_FORM_SET_MACRO_NAME(DLRX_RXPB_HDR, msdu_chain_num_set_direct, dword, val)

#define DLRX_RXPB_HDR_msdu_chain_num_clear_indirect(base, offset)   \
	DLRX_FORM_SET_MACRO_NAME(DLRX_RXPB_HDR, msdu_chain_num_clear_indirect, base, offset)

#define DLRX_RXPB_HDR_msdu_chain_num_clear_direct(dword)   \
	DLRX_FORM_SET_MACRO_NAME(DLRX_RXPB_HDR, msdu_chain_num_clear_direct, dword)


#define DLRX_RXPB_HDR_seqid_get_indirect(base, offset)   \
	DLRX_FORM_GET_MACRO_NAME(DLRX_RXPB_HDR, seqid_get_indirect, base, offset)

#define DLRX_RXPB_HDR_seqid_get_direct(dword)   \
	DLRX_FORM_GET_MACRO_NAME(DLRX_RXPB_HDR, seqid_get_direct, dword)

#define DLRX_RXPB_HDR_seqid_set_indirect(base, offset, val)   \
	DLRX_FORM_SET_MACRO_NAME(DLRX_RXPB_HDR, seqid_set_indirect, base, offset, val)

#define DLRX_RXPB_HDR_seqid_set_direct(dword, val)   \
	DLRX_FORM_SET_MACRO_NAME(DLRX_RXPB_HDR, seqid_set_direct, dword, val)

#define DLRX_RXPB_HDR_seqid_clear_indirect(base, offset)   \
	DLRX_FORM_SET_MACRO_NAME(DLRX_RXPB_HDR, seqid_clear_indirect, base, offset)

#define DLRX_RXPB_HDR_seqid_clear_direct(dword)   \
	DLRX_FORM_SET_MACRO_NAME(DLRX_RXPB_HDR, seqid_clear_direct, dword)


#define DLRX_RXPB_HDR_pn_31_0_get_indirect(base, offset)   \
	DLRX_FORM_GET_MACRO_NAME(DLRX_RXPB_HDR, pn_31_0_get_indirect, base, offset)

#define DLRX_RXPB_HDR_pn_31_0_get_direct(dword)   \
	DLRX_FORM_GET_MACRO_NAME(DLRX_RXPB_HDR, pn_31_0_get_direct, dword)

#define DLRX_RXPB_HDR_pn_31_0_set_indirect(base, offset, val)   \
	DLRX_FORM_SET_MACRO_NAME(DLRX_RXPB_HDR, pn_31_0_set_indirect, base, offset, val)

#define DLRX_RXPB_HDR_pn_31_0_set_direct(dword, val)   \
	DLRX_FORM_SET_MACRO_NAME(DLRX_RXPB_HDR, pn_31_0_set_direct, dword, val)

#define DLRX_RXPB_HDR_pn_31_0_clear_indirect(base, offset)   \
	DLRX_FORM_SET_MACRO_NAME(DLRX_RXPB_HDR, pn_31_0_clear_indirect, base, offset)

#define DLRX_RXPB_HDR_pn_31_0_clear_direct(dword)   \
	DLRX_FORM_SET_MACRO_NAME(DLRX_RXPB_HDR, pn_31_0_clear_direct, dword)


#define DLRX_RXPB_HDR_pn_47_32_get_indirect(base, offset)   \
	DLRX_FORM_GET_MACRO_NAME(DLRX_RXPB_HDR, pn_47_32_get_indirect, base, offset)

#define DLRX_RXPB_HDR_pn_47_32_get_direct(dword)   \
	DLRX_FORM_GET_MACRO_NAME(DLRX_RXPB_HDR, pn_47_32_get_direct, dword)

#define DLRX_RXPB_HDR_pn_47_32_set_indirect(base, offset, val)   \
	DLRX_FORM_SET_MACRO_NAME(DLRX_RXPB_HDR, pn_47_32_set_indirect, base, offset, val)

#define DLRX_RXPB_HDR_pn_47_32_set_direct(dword, val)   \
	DLRX_FORM_SET_MACRO_NAME(DLRX_RXPB_HDR, pn_47_32_set_direct, dword, val)

#define DLRX_RXPB_HDR_pn_47_32_clear_indirect(base, offset)   \
	DLRX_FORM_SET_MACRO_NAME(DLRX_RXPB_HDR, pn_47_32_clear_indirect, base, offset)

#define DLRX_RXPB_HDR_pn_47_32_clear_direct(dword)   \
	DLRX_FORM_SET_MACRO_NAME(DLRX_RXPB_HDR, pn_47_32_clear_direct, dword)


#define DLRX_RXPB_HDR_msdu_len_get_indirect(base, offset)   \
	DLRX_FORM_GET_MACRO_NAME(DLRX_RXPB_HDR, msdu_len_get_indirect, base, offset)

#define DLRX_RXPB_HDR_msdu_len_get_direct(dword)   \
	DLRX_FORM_GET_MACRO_NAME(DLRX_RXPB_HDR, msdu_len_get_direct, dword)

#define DLRX_RXPB_HDR_msdu_len_set_indirect(base, offset, val)   \
	DLRX_FORM_SET_MACRO_NAME(DLRX_RXPB_HDR, msdu_len_set_indirect, base, offset, val)

#define DLRX_RXPB_HDR_msdu_len_set_direct(dword, val)   \
	DLRX_FORM_SET_MACRO_NAME(DLRX_RXPB_HDR, msdu_len_set_direct, dword, val)

#define DLRX_RXPB_HDR_msdu_len_clear_indirect(base, offset)   \
	DLRX_FORM_SET_MACRO_NAME(DLRX_RXPB_HDR, msdu_len_clear_indirect, base, offset)

#define DLRX_RXPB_HDR_msdu_len_clear_direct(dword)   \
	DLRX_FORM_SET_MACRO_NAME(DLRX_RXPB_HDR, msdu_len_clear_direct, dword)

#define DLRX_RXPB_HDR_pn_63_48_get_indirect(base, offset)   \
	DLRX_FORM_GET_MACRO_NAME(DLRX_RXPB_HDR, pn_63_48_get_indirect, base, offset)

#define DLRX_RXPB_HDR_pn_63_48_get_direct(dword)   \
	DLRX_FORM_GET_MACRO_NAME(DLRX_RXPB_HDR, pn_63_48_get_direct, dword)

#define DLRX_RXPB_HDR_pn_63_48_set_indirect(base, offset, val)   \
	DLRX_FORM_SET_MACRO_NAME(DLRX_RXPB_HDR, pn_63_48_set_indirect, base, offset, val)

#define DLRX_RXPB_HDR_pn_63_48_set_direct(dword, val)   \
	DLRX_FORM_SET_MACRO_NAME(DLRX_RXPB_HDR, pn_63_48_set_direct, dword, val)

#define DLRX_RXPB_HDR_pn_63_48_clear_indirect(base, offset)   \
	DLRX_FORM_SET_MACRO_NAME(DLRX_RXPB_HDR, pn_63_48_clear_indirect, base, offset)

#define DLRX_RXPB_HDR_pn_63_48_clear_direct(dword)   \
	DLRX_FORM_SET_MACRO_NAME(DLRX_RXPB_HDR, pn_63_48_clear_direct, dword)

#define DLRX_RXPB_HDR_pn_95_64_get_indirect(base, offset)   \
	DLRX_FORM_GET_MACRO_NAME(DLRX_RXPB_HDR, pn_95_64_get_indirect, base, offset)

#define DLRX_RXPB_HDR_pn_95_64_get_direct(dword)   \
	DLRX_FORM_GET_MACRO_NAME(DLRX_RXPB_HDR, pn_95_64_get_direct, dword)

#define DLRX_RXPB_HDR_pn_95_64_set_indirect(base, offset, val)   \
	DLRX_FORM_SET_MACRO_NAME(DLRX_RXPB_HDR, pn_95_64_set_indirect, base, offset, val)

#define DLRX_RXPB_HDR_pn_95_64_set_direct(dword, val)   \
	DLRX_FORM_SET_MACRO_NAME(DLRX_RXPB_HDR, pn_95_64_set_direct, dword, val)

#define DLRX_RXPB_HDR_pn_95_64_clear_indirect(base, offset)   \
	DLRX_FORM_SET_MACRO_NAME(DLRX_RXPB_HDR, pn_95_64_clear_indirect, base, offset)

#define DLRX_RXPB_HDR_pn_95_64_clear_direct(dword)   \
	DLRX_FORM_SET_MACRO_NAME(DLRX_RXPB_HDR, pn_95_64_clear_direct, dword)


#define DLRX_RXPB_HDR_pn_127_96_get_indirect(base, offset)   \
	DLRX_FORM_GET_MACRO_NAME(DLRX_RXPB_HDR, pn_127_96_get_indirect, base, offset)

#define DLRX_RXPB_HDR_pn_127_96_get_direct(dword)   \
	DLRX_FORM_GET_MACRO_NAME(DLRX_RXPB_HDR, pn_127_96_get_direct, dword)

#define DLRX_RXPB_HDR_pn_127_96_set_indirect(base, offset, val)   \
	DLRX_FORM_SET_MACRO_NAME(DLRX_RXPB_HDR, pn_127_96_set_indirect, base, offset, val)

#define DLRX_RXPB_HDR_pn_127_96_set_direct(dword, val)   \
	DLRX_FORM_SET_MACRO_NAME(DLRX_RXPB_HDR, pn_127_96_set_direct, dword, val)

#define DLRX_RXPB_HDR_pn_127_96_clear_indirect(base, offset)   \
	DLRX_FORM_SET_MACRO_NAME(DLRX_RXPB_HDR, pn_127_96_clear_indirect, base, offset)

#define DLRX_RXPB_HDR_pn_127_96_clear_direct(dword)   \
	DLRX_FORM_SET_MACRO_NAME(DLRX_RXPB_HDR, pn_127_96_clear_direct, dword)


#define DLRX_RXPB_HDR_first_msdu_get_indirect(base, offset)   \
	DLRX_FORM_GET_MACRO_NAME(DLRX_RXPB_HDR, first_msdu_get_indirect, base, offset)

#define DLRX_RXPB_HDR_first_msdu_get_direct(dword)   \
	DLRX_FORM_GET_MACRO_NAME(DLRX_RXPB_HDR, first_msdu_get_direct, dword)

#define DLRX_RXPB_HDR_first_msdu_set_indirect(base, offset, val)   \
	DLRX_FORM_SET_MACRO_NAME(DLRX_RXPB_HDR, first_msdu_set_indirect, base, offset, val)

#define DLRX_RXPB_HDR_first_msdu_set_direct(dword, val)   \
	DLRX_FORM_SET_MACRO_NAME(DLRX_RXPB_HDR, first_msdu_set_direct, dword, val)

#define DLRX_RXPB_HDR_first_msdu_clear_indirect(base, offset)   \
	DLRX_FORM_SET_MACRO_NAME(DLRX_RXPB_HDR, first_msdu_clear_indirect, base, offset)

#define DLRX_RXPB_HDR_first_msdu_clear_direct(dword)   \
	DLRX_FORM_SET_MACRO_NAME(DLRX_RXPB_HDR, first_msdu_clear_direct, dword)


#define DLRX_RXPB_HDR_last_msdu_get_indirect(base, offset)   \
	DLRX_FORM_GET_MACRO_NAME(DLRX_RXPB_HDR, last_msdu_get_indirect, base, offset)

#define DLRX_RXPB_HDR_last_msdu_get_direct(dword)   \
	DLRX_FORM_GET_MACRO_NAME(DLRX_RXPB_HDR, last_msdu_get_direct, dword)

#define DLRX_RXPB_HDR_last_msdu_set_indirect(base, offset, val)   \
	DLRX_FORM_SET_MACRO_NAME(DLRX_RXPB_HDR, last_msdu_set_indirect, base, offset, val)

#define DLRX_RXPB_HDR_last_msdu_set_direct(dword, val)   \
	DLRX_FORM_SET_MACRO_NAME(DLRX_RXPB_HDR, last_msdu_set_direct, dword, val)

#define DLRX_RXPB_HDR_last_msdu_clear_indirect(base, offset) \
	DLRX_FORM_SET_MACRO_NAME(DLRX_RXPB_HDR, last_msdu_clear_indirect, base, offset)

#define DLRX_RXPB_HDR_last_msdu_clear_direct(dword) \
	DLRX_FORM_SET_MACRO_NAME(DLRX_RXPB_HDR, last_msdu_clear_direct, dword)


#endif

