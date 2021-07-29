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
#ifndef __DLRX_FW_DATA_STRUCTURE_MACRO_H_
#define __DLRX_FW_DATA_STRUCTURE_MACRO_H_

/*-----------------------
*Data Structure #defines
*-----------------------*/

#define O_DLRX_RXPB_HDR_PEREGRINE_insig0 0
#define B_DLRX_RXPB_HDR_PEREGRINE_insig0 0
#define W_DLRX_RXPB_HDR_PEREGRINE_insig0 2
#define M_DLRX_RXPB_HDR_PEREGRINE_insig0 0x00000003

#define DLRX_RXPB_HDR_PEREGRINE_insig0_get_indirect(base, offset)	((((*(base + O_DLRX_RXPB_HDR_PEREGRINE_insig0 + offset)) & M_DLRX_RXPB_HDR_PEREGRINE_insig0) >> B_DLRX_RXPB_HDR_PEREGRINE_insig0))

#define DLRX_RXPB_HDR_PEREGRINE_insig0_get_direct(dword)	((((dword) & M_DLRX_RXPB_HDR_PEREGRINE_insig0) >> B_DLRX_RXPB_HDR_PEREGRINE_insig0))

#define DLRX_RXPB_HDR_PEREGRINE_insig0_set_indirect(base, offset, val) \
	do {                                                              \
		(*(base + O_DLRX_RXPB_HDR_PEREGRINE_insig0 + offset)) &= (~(M_DLRX_RXPB_HDR_PEREGRINE_insig0));    \
		(*(base + O_DLRX_RXPB_HDR_PEREGRINE_insig0 + offset)) |= ((val << B_DLRX_RXPB_HDR_PEREGRINE_insig0) & M_DLRX_RXPB_HDR_PEREGRINE_insig0);    \
	} while (0)

#define DLRX_RXPB_HDR_PEREGRINE_insig0_set_direct(dword, val) \
	do {                                                               \
		(dword) &= (~(M_DLRX_RXPB_HDR_PEREGRINE_insig0));    \
		(dword) |= ((val << B_DLRX_RXPB_HDR_PEREGRINE_insig0) & M_DLRX_RXPB_HDR_PEREGRINE_insig0);    \
	} while (0)

#define DLRX_RXPB_HDR_PEREGRINE_insig0_clear_indirect(base, offset)	((*(base + O_DLRX_RXPB_HDR_PEREGRINE_insig0 + offset)) &= (~(M_DLRX_RXPB_HDR_PEREGRINE_insig0)))

#define DLRX_RXPB_HDR_PEREGRINE_insig0_clear_direct(dword)	((dword) &= (~(M_DLRX_RXPB_HDR_PEREGRINE_insig0)))

#define O_DLRX_RXPB_HDR_PEREGRINE_mcast_bcast 0
#define B_DLRX_RXPB_HDR_PEREGRINE_mcast_bcast 2
#define W_DLRX_RXPB_HDR_PEREGRINE_mcast_bcast 1
#define M_DLRX_RXPB_HDR_PEREGRINE_mcast_bcast 0x00000004

#define DLRX_RXPB_HDR_PEREGRINE_mcast_bcast_get_indirect(base, offset)	((((*(base + O_DLRX_RXPB_HDR_PEREGRINE_mcast_bcast + offset)) & M_DLRX_RXPB_HDR_PEREGRINE_mcast_bcast) >> B_DLRX_RXPB_HDR_PEREGRINE_mcast_bcast))

#define DLRX_RXPB_HDR_PEREGRINE_mcast_bcast_get_direct(dword)	((((dword) & M_DLRX_RXPB_HDR_PEREGRINE_mcast_bcast) >> B_DLRX_RXPB_HDR_PEREGRINE_mcast_bcast))

#define DLRX_RXPB_HDR_PEREGRINE_mcast_bcast_set_indirect(base, offset, val) \
	do {                                                              \
		(*(base + O_DLRX_RXPB_HDR_PEREGRINE_mcast_bcast + offset)) &= (~(M_DLRX_RXPB_HDR_PEREGRINE_mcast_bcast));    \
		(*(base + O_DLRX_RXPB_HDR_PEREGRINE_mcast_bcast + offset)) |= ((val << B_DLRX_RXPB_HDR_PEREGRINE_mcast_bcast) & M_DLRX_RXPB_HDR_PEREGRINE_mcast_bcast);    \
	} while (0)

#define DLRX_RXPB_HDR_PEREGRINE_mcast_bcast_set_direct(dword, val) \
	do {                                                               \
		(dword) &= (~(M_DLRX_RXPB_HDR_PEREGRINE_mcast_bcast));    \
		(dword) |= ((val << B_DLRX_RXPB_HDR_PEREGRINE_mcast_bcast) & M_DLRX_RXPB_HDR_PEREGRINE_mcast_bcast);    \
	} while (0)

#define DLRX_RXPB_HDR_PEREGRINE_mcast_bcast_clear_indirect(base, offset)	((*(base + O_DLRX_RXPB_HDR_PEREGRINE_mcast_bcast + offset)) &= (~(M_DLRX_RXPB_HDR_PEREGRINE_mcast_bcast)))

#define DLRX_RXPB_HDR_PEREGRINE_mcast_bcast_clear_direct(dword)	((dword) &= (~(M_DLRX_RXPB_HDR_PEREGRINE_mcast_bcast)))

#define O_DLRX_RXPB_HDR_PEREGRINE_insig1 0
#define B_DLRX_RXPB_HDR_PEREGRINE_insig1 3
#define W_DLRX_RXPB_HDR_PEREGRINE_insig1 28
#define M_DLRX_RXPB_HDR_PEREGRINE_insig1 0x7ffffff8

#define DLRX_RXPB_HDR_PEREGRINE_insig1_get_indirect(base, offset)	((((*(base + O_DLRX_RXPB_HDR_PEREGRINE_insig1 + offset)) & M_DLRX_RXPB_HDR_PEREGRINE_insig1) >> B_DLRX_RXPB_HDR_PEREGRINE_insig1))

#define DLRX_RXPB_HDR_PEREGRINE_insig1_get_direct(dword)	((((dword) & M_DLRX_RXPB_HDR_PEREGRINE_insig1) >> B_DLRX_RXPB_HDR_PEREGRINE_insig1))

#define DLRX_RXPB_HDR_PEREGRINE_insig1_set_indirect(base, offset, val) \
	do {                                                              \
		(*(base + O_DLRX_RXPB_HDR_PEREGRINE_insig1 + offset)) &= (~(M_DLRX_RXPB_HDR_PEREGRINE_insig1));    \
		(*(base + O_DLRX_RXPB_HDR_PEREGRINE_insig1 + offset)) |= ((val << B_DLRX_RXPB_HDR_PEREGRINE_insig1) & M_DLRX_RXPB_HDR_PEREGRINE_insig1);    \
	} while (0)

#define DLRX_RXPB_HDR_PEREGRINE_insig1_set_direct(dword, val) \
	do {                                                               \
		(dword) &= (~(M_DLRX_RXPB_HDR_PEREGRINE_insig1));    \
		(dword) |= ((val << B_DLRX_RXPB_HDR_PEREGRINE_insig1) & M_DLRX_RXPB_HDR_PEREGRINE_insig1);    \
	} while (0)

#define DLRX_RXPB_HDR_PEREGRINE_insig1_clear_indirect(base, offset)	((*(base + O_DLRX_RXPB_HDR_PEREGRINE_insig1 + offset)) &= (~(M_DLRX_RXPB_HDR_PEREGRINE_insig1)))

#define DLRX_RXPB_HDR_PEREGRINE_insig1_clear_direct(dword)	((dword) &= (~(M_DLRX_RXPB_HDR_PEREGRINE_insig1)))

#define O_DLRX_RXPB_HDR_PEREGRINE_msdu_load_status 0
#define B_DLRX_RXPB_HDR_PEREGRINE_msdu_load_status 31
#define W_DLRX_RXPB_HDR_PEREGRINE_msdu_load_status 1
#define M_DLRX_RXPB_HDR_PEREGRINE_msdu_load_status 0x80000000

#define DLRX_RXPB_HDR_PEREGRINE_msdu_load_status_get_indirect(base, offset)	((((*(base + O_DLRX_RXPB_HDR_PEREGRINE_msdu_load_status + offset)) & M_DLRX_RXPB_HDR_PEREGRINE_msdu_load_status) >> B_DLRX_RXPB_HDR_PEREGRINE_msdu_load_status))

#define DLRX_RXPB_HDR_PEREGRINE_msdu_load_status_get_direct(dword)	((((dword) & M_DLRX_RXPB_HDR_PEREGRINE_msdu_load_status) >> B_DLRX_RXPB_HDR_PEREGRINE_msdu_load_status))

#define DLRX_RXPB_HDR_PEREGRINE_msdu_load_status_set_indirect(base, offset, val) \
	do {                                                              \
		(*(base + O_DLRX_RXPB_HDR_PEREGRINE_msdu_load_status + offset)) &= (~(M_DLRX_RXPB_HDR_PEREGRINE_msdu_load_status));    \
		(*(base + O_DLRX_RXPB_HDR_PEREGRINE_msdu_load_status + offset)) |= ((val << B_DLRX_RXPB_HDR_PEREGRINE_msdu_load_status) & M_DLRX_RXPB_HDR_PEREGRINE_msdu_load_status);    \
	} while (0)

#define DLRX_RXPB_HDR_PEREGRINE_msdu_load_status_set_direct(dword, val) \
	do {                                                               \
		(dword) &= (~(M_DLRX_RXPB_HDR_PEREGRINE_msdu_load_status));    \
		(dword) |= ((val << B_DLRX_RXPB_HDR_PEREGRINE_msdu_load_status) & M_DLRX_RXPB_HDR_PEREGRINE_msdu_load_status);    \
	} while (0)

#define DLRX_RXPB_HDR_PEREGRINE_msdu_load_status_clear_indirect(base, offset)	((*(base + O_DLRX_RXPB_HDR_PEREGRINE_msdu_load_status + offset)) &= (~(M_DLRX_RXPB_HDR_PEREGRINE_msdu_load_status)))

#define DLRX_RXPB_HDR_PEREGRINE_msdu_load_status_clear_direct(dword)	((dword) &= (~(M_DLRX_RXPB_HDR_PEREGRINE_msdu_load_status)))

#define O_DLRX_RXPB_HDR_PEREGRINE_insig2 1
#define B_DLRX_RXPB_HDR_PEREGRINE_insig2 0
#define W_DLRX_RXPB_HDR_PEREGRINE_insig2 16
#define M_DLRX_RXPB_HDR_PEREGRINE_insig2 0x0000ffff

#define DLRX_RXPB_HDR_PEREGRINE_insig2_get_indirect(base, offset)	((((*(base + O_DLRX_RXPB_HDR_PEREGRINE_insig2 + offset)) & M_DLRX_RXPB_HDR_PEREGRINE_insig2) >> B_DLRX_RXPB_HDR_PEREGRINE_insig2))

#define DLRX_RXPB_HDR_PEREGRINE_insig2_get_direct(dword)	((((dword) & M_DLRX_RXPB_HDR_PEREGRINE_insig2) >> B_DLRX_RXPB_HDR_PEREGRINE_insig2))

#define DLRX_RXPB_HDR_PEREGRINE_insig2_set_indirect(base, offset, val) \
	do {                                                              \
		(*(base + O_DLRX_RXPB_HDR_PEREGRINE_insig2 + offset)) &= (~(M_DLRX_RXPB_HDR_PEREGRINE_insig2));    \
		(*(base + O_DLRX_RXPB_HDR_PEREGRINE_insig2 + offset)) |= ((val << B_DLRX_RXPB_HDR_PEREGRINE_insig2) & M_DLRX_RXPB_HDR_PEREGRINE_insig2);    \
	} while (0)

#define DLRX_RXPB_HDR_PEREGRINE_insig2_set_direct(dword, val) \
	do {                                                               \
		(dword) &= (~(M_DLRX_RXPB_HDR_PEREGRINE_insig2));    \
		(dword) |= ((val << B_DLRX_RXPB_HDR_PEREGRINE_insig2) & M_DLRX_RXPB_HDR_PEREGRINE_insig2);    \
	} while (0)

#define DLRX_RXPB_HDR_PEREGRINE_insig2_clear_indirect(base, offset)	((*(base + O_DLRX_RXPB_HDR_PEREGRINE_insig2 + offset)) &= (~(M_DLRX_RXPB_HDR_PEREGRINE_insig2)))

#define DLRX_RXPB_HDR_PEREGRINE_insig2_clear_direct(dword)	((dword) &= (~(M_DLRX_RXPB_HDR_PEREGRINE_insig2)))

#define O_DLRX_RXPB_HDR_PEREGRINE_msdu_chain_num 1
#define B_DLRX_RXPB_HDR_PEREGRINE_msdu_chain_num 16
#define W_DLRX_RXPB_HDR_PEREGRINE_msdu_chain_num 8
#define M_DLRX_RXPB_HDR_PEREGRINE_msdu_chain_num 0x00ff0000

#define DLRX_RXPB_HDR_PEREGRINE_msdu_chain_num_get_indirect(base, offset)	((((*(base + O_DLRX_RXPB_HDR_PEREGRINE_msdu_chain_num + offset)) & M_DLRX_RXPB_HDR_PEREGRINE_msdu_chain_num) >> B_DLRX_RXPB_HDR_PEREGRINE_msdu_chain_num))

#define DLRX_RXPB_HDR_PEREGRINE_msdu_chain_num_get_direct(dword)	((((dword) & M_DLRX_RXPB_HDR_PEREGRINE_msdu_chain_num) >> B_DLRX_RXPB_HDR_PEREGRINE_msdu_chain_num))

#define DLRX_RXPB_HDR_PEREGRINE_msdu_chain_num_set_indirect(base, offset, val) \
	do {                                                              \
		(*(base + O_DLRX_RXPB_HDR_PEREGRINE_msdu_chain_num + offset)) &= (~(M_DLRX_RXPB_HDR_PEREGRINE_msdu_chain_num));    \
		(*(base + O_DLRX_RXPB_HDR_PEREGRINE_msdu_chain_num + offset)) |= ((val << B_DLRX_RXPB_HDR_PEREGRINE_msdu_chain_num) & M_DLRX_RXPB_HDR_PEREGRINE_msdu_chain_num);    \
	} while (0)

#define DLRX_RXPB_HDR_PEREGRINE_msdu_chain_num_set_direct(dword, val) \
	do {                                                               \
		(dword) &= (~(M_DLRX_RXPB_HDR_PEREGRINE_msdu_chain_num));    \
		(dword) |= ((val << B_DLRX_RXPB_HDR_PEREGRINE_msdu_chain_num) & M_DLRX_RXPB_HDR_PEREGRINE_msdu_chain_num);    \
	} while (0)

#define DLRX_RXPB_HDR_PEREGRINE_msdu_chain_num_clear_indirect(base, offset)	((*(base + O_DLRX_RXPB_HDR_PEREGRINE_msdu_chain_num + offset)) &= (~(M_DLRX_RXPB_HDR_PEREGRINE_msdu_chain_num)))

#define DLRX_RXPB_HDR_PEREGRINE_msdu_chain_num_clear_direct(dword)	((dword) &= (~(M_DLRX_RXPB_HDR_PEREGRINE_msdu_chain_num)))

#define O_DLRX_RXPB_HDR_PEREGRINE_insig3 1
#define B_DLRX_RXPB_HDR_PEREGRINE_insig3 24
#define W_DLRX_RXPB_HDR_PEREGRINE_insig3 8
#define M_DLRX_RXPB_HDR_PEREGRINE_insig3 0xff000000

#define DLRX_RXPB_HDR_PEREGRINE_insig3_get_indirect(base, offset)	((((*(base + O_DLRX_RXPB_HDR_PEREGRINE_insig3 + offset)) & M_DLRX_RXPB_HDR_PEREGRINE_insig3) >> B_DLRX_RXPB_HDR_PEREGRINE_insig3))

#define DLRX_RXPB_HDR_PEREGRINE_insig3_get_direct(dword)	((((dword) & M_DLRX_RXPB_HDR_PEREGRINE_insig3) >> B_DLRX_RXPB_HDR_PEREGRINE_insig3))

#define DLRX_RXPB_HDR_PEREGRINE_insig3_set_indirect(base, offset, val) \
	do {                                                              \
		(*(base + O_DLRX_RXPB_HDR_PEREGRINE_insig3 + offset)) &= (~(M_DLRX_RXPB_HDR_PEREGRINE_insig3));    \
		(*(base + O_DLRX_RXPB_HDR_PEREGRINE_insig3 + offset)) |= ((val << B_DLRX_RXPB_HDR_PEREGRINE_insig3) & M_DLRX_RXPB_HDR_PEREGRINE_insig3);    \
	} while (0)

#define DLRX_RXPB_HDR_PEREGRINE_insig3_set_direct(dword, val) \
	do {                                                               \
		(dword) &= (~(M_DLRX_RXPB_HDR_PEREGRINE_insig3));    \
		(dword) |= ((val << B_DLRX_RXPB_HDR_PEREGRINE_insig3) & M_DLRX_RXPB_HDR_PEREGRINE_insig3);    \
	} while (0)

#define DLRX_RXPB_HDR_PEREGRINE_insig3_clear_indirect(base, offset)	((*(base + O_DLRX_RXPB_HDR_PEREGRINE_insig3 + offset)) &= (~(M_DLRX_RXPB_HDR_PEREGRINE_insig3)))

#define DLRX_RXPB_HDR_PEREGRINE_insig3_clear_direct(dword)	((dword) &= (~(M_DLRX_RXPB_HDR_PEREGRINE_insig3)))

#define O_DLRX_RXPB_HDR_PEREGRINE_insig4 2
#define B_DLRX_RXPB_HDR_PEREGRINE_insig4 0
#define W_DLRX_RXPB_HDR_PEREGRINE_insig4 16
#define M_DLRX_RXPB_HDR_PEREGRINE_insig4 0x0000ffff

#define DLRX_RXPB_HDR_PEREGRINE_insig4_get_indirect(base, offset)	((((*(base + O_DLRX_RXPB_HDR_PEREGRINE_insig4 + offset)) & M_DLRX_RXPB_HDR_PEREGRINE_insig4) >> B_DLRX_RXPB_HDR_PEREGRINE_insig4))

#define DLRX_RXPB_HDR_PEREGRINE_insig4_get_direct(dword)	((((dword) & M_DLRX_RXPB_HDR_PEREGRINE_insig4) >> B_DLRX_RXPB_HDR_PEREGRINE_insig4))

#define DLRX_RXPB_HDR_PEREGRINE_insig4_set_indirect(base, offset, val) \
	do {                                                              \
		(*(base + O_DLRX_RXPB_HDR_PEREGRINE_insig4 + offset)) &= (~(M_DLRX_RXPB_HDR_PEREGRINE_insig4));    \
		(*(base + O_DLRX_RXPB_HDR_PEREGRINE_insig4 + offset)) |= ((val << B_DLRX_RXPB_HDR_PEREGRINE_insig4) & M_DLRX_RXPB_HDR_PEREGRINE_insig4);    \
	} while (0)

#define DLRX_RXPB_HDR_PEREGRINE_insig4_set_direct(dword, val) \
	do {                                                               \
		(dword) &= (~(M_DLRX_RXPB_HDR_PEREGRINE_insig4));    \
		(dword) |= ((val << B_DLRX_RXPB_HDR_PEREGRINE_insig4) & M_DLRX_RXPB_HDR_PEREGRINE_insig4);    \
	} while (0)

#define DLRX_RXPB_HDR_PEREGRINE_insig4_clear_indirect(base, offset)	((*(base + O_DLRX_RXPB_HDR_PEREGRINE_insig4 + offset)) &= (~(M_DLRX_RXPB_HDR_PEREGRINE_insig4)))

#define DLRX_RXPB_HDR_PEREGRINE_insig4_clear_direct(dword)	((dword) &= (~(M_DLRX_RXPB_HDR_PEREGRINE_insig4)))

#define O_DLRX_RXPB_HDR_PEREGRINE_seqid 2
#define B_DLRX_RXPB_HDR_PEREGRINE_seqid 16
#define W_DLRX_RXPB_HDR_PEREGRINE_seqid 12
#define M_DLRX_RXPB_HDR_PEREGRINE_seqid 0x0fff0000

#define DLRX_RXPB_HDR_PEREGRINE_seqid_get_indirect(base, offset)	((((*(base + O_DLRX_RXPB_HDR_PEREGRINE_seqid + offset)) & M_DLRX_RXPB_HDR_PEREGRINE_seqid) >> B_DLRX_RXPB_HDR_PEREGRINE_seqid))

#define DLRX_RXPB_HDR_PEREGRINE_seqid_get_direct(dword)	((((dword) & M_DLRX_RXPB_HDR_PEREGRINE_seqid) >> B_DLRX_RXPB_HDR_PEREGRINE_seqid))

#define DLRX_RXPB_HDR_PEREGRINE_seqid_set_indirect(base, offset, val) \
	do {                                                              \
		(*(base + O_DLRX_RXPB_HDR_PEREGRINE_seqid + offset)) &= (~(M_DLRX_RXPB_HDR_PEREGRINE_seqid));    \
		(*(base + O_DLRX_RXPB_HDR_PEREGRINE_seqid + offset)) |= ((val << B_DLRX_RXPB_HDR_PEREGRINE_seqid) & M_DLRX_RXPB_HDR_PEREGRINE_seqid);    \
	} while (0)

#define DLRX_RXPB_HDR_PEREGRINE_seqid_set_direct(dword, val) \
	do {                                                               \
		(dword) &= (~(M_DLRX_RXPB_HDR_PEREGRINE_seqid));    \
		(dword) |= ((val << B_DLRX_RXPB_HDR_PEREGRINE_seqid) & M_DLRX_RXPB_HDR_PEREGRINE_seqid);    \
	} while (0)

#define DLRX_RXPB_HDR_PEREGRINE_seqid_clear_indirect(base, offset)	((*(base + O_DLRX_RXPB_HDR_PEREGRINE_seqid + offset)) &= (~(M_DLRX_RXPB_HDR_PEREGRINE_seqid)))

#define DLRX_RXPB_HDR_PEREGRINE_seqid_clear_direct(dword)	((dword) &= (~(M_DLRX_RXPB_HDR_PEREGRINE_seqid)))

#define O_DLRX_RXPB_HDR_PEREGRINE_insig5 2
#define B_DLRX_RXPB_HDR_PEREGRINE_insig5 28
#define W_DLRX_RXPB_HDR_PEREGRINE_insig5 4
#define M_DLRX_RXPB_HDR_PEREGRINE_insig5 0xf0000000

#define DLRX_RXPB_HDR_PEREGRINE_insig5_get_indirect(base, offset)	((((*(base + O_DLRX_RXPB_HDR_PEREGRINE_insig5 + offset)) & M_DLRX_RXPB_HDR_PEREGRINE_insig5) >> B_DLRX_RXPB_HDR_PEREGRINE_insig5))

#define DLRX_RXPB_HDR_PEREGRINE_insig5_get_direct(dword)	((((dword) & M_DLRX_RXPB_HDR_PEREGRINE_insig5) >> B_DLRX_RXPB_HDR_PEREGRINE_insig5))

#define DLRX_RXPB_HDR_PEREGRINE_insig5_set_indirect(base, offset, val) \
	do {                                                              \
		(*(base + O_DLRX_RXPB_HDR_PEREGRINE_insig5 + offset)) &= (~(M_DLRX_RXPB_HDR_PEREGRINE_insig5));    \
		(*(base + O_DLRX_RXPB_HDR_PEREGRINE_insig5 + offset)) |= ((val << B_DLRX_RXPB_HDR_PEREGRINE_insig5) & M_DLRX_RXPB_HDR_PEREGRINE_insig5);    \
	} while (0)

#define DLRX_RXPB_HDR_PEREGRINE_insig5_set_direct(dword, val) \
	do {                                                               \
		(dword) &= (~(M_DLRX_RXPB_HDR_PEREGRINE_insig5));    \
		(dword) |= ((val << B_DLRX_RXPB_HDR_PEREGRINE_insig5) & M_DLRX_RXPB_HDR_PEREGRINE_insig5);    \
	} while (0)

#define DLRX_RXPB_HDR_PEREGRINE_insig5_clear_indirect(base, offset)	((*(base + O_DLRX_RXPB_HDR_PEREGRINE_insig5 + offset)) &= (~(M_DLRX_RXPB_HDR_PEREGRINE_insig5)))

#define DLRX_RXPB_HDR_PEREGRINE_insig5_clear_direct(dword)	((dword) &= (~(M_DLRX_RXPB_HDR_PEREGRINE_insig5)))

#define O_DLRX_RXPB_HDR_PEREGRINE_pn_31_0 3
#define B_DLRX_RXPB_HDR_PEREGRINE_pn_31_0 0
#define W_DLRX_RXPB_HDR_PEREGRINE_pn_31_0 32
#define M_DLRX_RXPB_HDR_PEREGRINE_pn_31_0 0xffffffff

#define DLRX_RXPB_HDR_PEREGRINE_pn_31_0_get_indirect(base, offset)	((((*(base + O_DLRX_RXPB_HDR_PEREGRINE_pn_31_0 + offset)) & M_DLRX_RXPB_HDR_PEREGRINE_pn_31_0) >> B_DLRX_RXPB_HDR_PEREGRINE_pn_31_0))

#define DLRX_RXPB_HDR_PEREGRINE_pn_31_0_get_direct(dword)	((((dword) & M_DLRX_RXPB_HDR_PEREGRINE_pn_31_0) >> B_DLRX_RXPB_HDR_PEREGRINE_pn_31_0))

#define DLRX_RXPB_HDR_PEREGRINE_pn_31_0_set_indirect(base, offset, val)    \
	do {                                                              \
		(*(base + O_DLRX_RXPB_HDR_PEREGRINE_pn_31_0 + offset)) &= (~(M_DLRX_RXPB_HDR_PEREGRINE_pn_31_0));    \
		(*(base + O_DLRX_RXPB_HDR_PEREGRINE_pn_31_0 + offset)) |= ((val << B_DLRX_RXPB_HDR_PEREGRINE_pn_31_0) & M_DLRX_RXPB_HDR_PEREGRINE_pn_31_0);    \
	} while (0)

#define DLRX_RXPB_HDR_PEREGRINE_pn_31_0_set_direct(dword, val)    \
	do {                                                               \
		(dword) &= (~(M_DLRX_RXPB_HDR_PEREGRINE_pn_31_0));    \
		(dword) |= ((val << B_DLRX_RXPB_HDR_PEREGRINE_pn_31_0) & M_DLRX_RXPB_HDR_PEREGRINE_pn_31_0);    \
	} while (0)

#define DLRX_RXPB_HDR_PEREGRINE_pn_31_0_clear_indirect(base, offset)	((*(base + O_DLRX_RXPB_HDR_PEREGRINE_pn_31_0 + offset)) &= (~(M_DLRX_RXPB_HDR_PEREGRINE_pn_31_0)))

#define DLRX_RXPB_HDR_PEREGRINE_pn_31_0_clear_direct(dword)	((dword) &= (~(M_DLRX_RXPB_HDR_PEREGRINE_pn_31_0)))

#define O_DLRX_RXPB_HDR_PEREGRINE_pn_47_32 4
#define B_DLRX_RXPB_HDR_PEREGRINE_pn_47_32 0
#define W_DLRX_RXPB_HDR_PEREGRINE_pn_47_32 16
#define M_DLRX_RXPB_HDR_PEREGRINE_pn_47_32 0x0000ffff

#define DLRX_RXPB_HDR_PEREGRINE_pn_47_32_get_indirect(base, offset)	((((*(base + O_DLRX_RXPB_HDR_PEREGRINE_pn_47_32 + offset)) & M_DLRX_RXPB_HDR_PEREGRINE_pn_47_32) >> B_DLRX_RXPB_HDR_PEREGRINE_pn_47_32))

#define DLRX_RXPB_HDR_PEREGRINE_pn_47_32_get_direct(dword)	((((dword) & M_DLRX_RXPB_HDR_PEREGRINE_pn_47_32) >> B_DLRX_RXPB_HDR_PEREGRINE_pn_47_32))

#define DLRX_RXPB_HDR_PEREGRINE_pn_47_32_set_indirect(base, offset, val) \
	do {                                                              \
		(*(base + O_DLRX_RXPB_HDR_PEREGRINE_pn_47_32 + offset)) &= (~(M_DLRX_RXPB_HDR_PEREGRINE_pn_47_32));    \
		(*(base + O_DLRX_RXPB_HDR_PEREGRINE_pn_47_32 + offset)) |= ((val << B_DLRX_RXPB_HDR_PEREGRINE_pn_47_32) & M_DLRX_RXPB_HDR_PEREGRINE_pn_47_32);    \
	} while (0)

#define DLRX_RXPB_HDR_PEREGRINE_pn_47_32_set_direct(dword, val) \
	do {                                                               \
		(dword) &= (~(M_DLRX_RXPB_HDR_PEREGRINE_pn_47_32));    \
		(dword) |= ((val << B_DLRX_RXPB_HDR_PEREGRINE_pn_47_32) & M_DLRX_RXPB_HDR_PEREGRINE_pn_47_32);    \
	} while (0)

#define DLRX_RXPB_HDR_PEREGRINE_pn_47_32_clear_indirect(base, offset)	((*(base + O_DLRX_RXPB_HDR_PEREGRINE_pn_47_32 + offset)) &= (~(M_DLRX_RXPB_HDR_PEREGRINE_pn_47_32)))

#define DLRX_RXPB_HDR_PEREGRINE_pn_47_32_clear_direct(dword)	((dword) &= (~(M_DLRX_RXPB_HDR_PEREGRINE_pn_47_32)))

#define O_DLRX_RXPB_HDR_PEREGRINE_insig6 4
#define B_DLRX_RXPB_HDR_PEREGRINE_insig6 16
#define W_DLRX_RXPB_HDR_PEREGRINE_insig6 16
#define M_DLRX_RXPB_HDR_PEREGRINE_insig6 0xffff0000

#define DLRX_RXPB_HDR_PEREGRINE_insig6_get_indirect(base, offset)	((((*(base + O_DLRX_RXPB_HDR_PEREGRINE_insig6 + offset)) & M_DLRX_RXPB_HDR_PEREGRINE_insig6) >> B_DLRX_RXPB_HDR_PEREGRINE_insig6))

#define DLRX_RXPB_HDR_PEREGRINE_insig6_get_direct(dword)	((((dword) & M_DLRX_RXPB_HDR_PEREGRINE_insig6) >> B_DLRX_RXPB_HDR_PEREGRINE_insig6))

#define DLRX_RXPB_HDR_PEREGRINE_insig6_set_indirect(base, offset, val) \
	do {                                                              \
		(*(base + O_DLRX_RXPB_HDR_PEREGRINE_insig6 + offset)) &= (~(M_DLRX_RXPB_HDR_PEREGRINE_insig6));    \
		(*(base + O_DLRX_RXPB_HDR_PEREGRINE_insig6 + offset)) |= ((val << B_DLRX_RXPB_HDR_PEREGRINE_insig6) & M_DLRX_RXPB_HDR_PEREGRINE_insig6);    \
	} while (0)

#define DLRX_RXPB_HDR_PEREGRINE_insig6_set_direct(dword, val) \
	do {                                                               \
		(dword) &= (~(M_DLRX_RXPB_HDR_PEREGRINE_insig6));    \
		(dword) |= ((val << B_DLRX_RXPB_HDR_PEREGRINE_insig6) & M_DLRX_RXPB_HDR_PEREGRINE_insig6);    \
	} while (0)

#define DLRX_RXPB_HDR_PEREGRINE_insig6_clear_indirect(base, offset)	((*(base + O_DLRX_RXPB_HDR_PEREGRINE_insig6 + offset)) &= (~(M_DLRX_RXPB_HDR_PEREGRINE_insig6)))

#define DLRX_RXPB_HDR_PEREGRINE_insig6_clear_direct(dword)	((dword) &= (~(M_DLRX_RXPB_HDR_PEREGRINE_insig6)))

#define O_DLRX_RXPB_HDR_PEREGRINE_msdu_len 5
#define B_DLRX_RXPB_HDR_PEREGRINE_msdu_len 0
#define W_DLRX_RXPB_HDR_PEREGRINE_msdu_len 14
#define M_DLRX_RXPB_HDR_PEREGRINE_msdu_len 0x00003fff

#define DLRX_RXPB_HDR_PEREGRINE_msdu_len_get_indirect(base, offset)	((((*(base + O_DLRX_RXPB_HDR_PEREGRINE_msdu_len + offset)) & M_DLRX_RXPB_HDR_PEREGRINE_msdu_len) >> B_DLRX_RXPB_HDR_PEREGRINE_msdu_len))

#define DLRX_RXPB_HDR_PEREGRINE_msdu_len_get_direct(dword)	((((dword) & M_DLRX_RXPB_HDR_PEREGRINE_msdu_len) >> B_DLRX_RXPB_HDR_PEREGRINE_msdu_len))

#define DLRX_RXPB_HDR_PEREGRINE_msdu_len_set_indirect(base, offset, val) \
	do {                                                              \
		(*(base + O_DLRX_RXPB_HDR_PEREGRINE_msdu_len + offset)) &= (~(M_DLRX_RXPB_HDR_PEREGRINE_msdu_len));    \
		(*(base + O_DLRX_RXPB_HDR_PEREGRINE_msdu_len + offset)) |= ((val << B_DLRX_RXPB_HDR_PEREGRINE_msdu_len) & M_DLRX_RXPB_HDR_PEREGRINE_msdu_len);    \
	} while (0)

#define DLRX_RXPB_HDR_PEREGRINE_msdu_len_set_direct(dword, val) \
	do {                                                               \
		(dword) &= (~(M_DLRX_RXPB_HDR_PEREGRINE_msdu_len));    \
		(dword) |= ((val << B_DLRX_RXPB_HDR_PEREGRINE_msdu_len) & M_DLRX_RXPB_HDR_PEREGRINE_msdu_len);    \
	} while (0)

#define DLRX_RXPB_HDR_PEREGRINE_msdu_len_clear_indirect(base, offset)	((*(base + O_DLRX_RXPB_HDR_PEREGRINE_msdu_len + offset)) &= (~(M_DLRX_RXPB_HDR_PEREGRINE_msdu_len)))

#define DLRX_RXPB_HDR_PEREGRINE_msdu_len_clear_direct(dword)	((dword) &= (~(M_DLRX_RXPB_HDR_PEREGRINE_msdu_len)))

#define O_DLRX_RXPB_HDR_PEREGRINE_insig7 5
#define B_DLRX_RXPB_HDR_PEREGRINE_insig7 14
#define W_DLRX_RXPB_HDR_PEREGRINE_insig7 18
#define M_DLRX_RXPB_HDR_PEREGRINE_insig7 0xffffc000

#define DLRX_RXPB_HDR_PEREGRINE_insig7_get_indirect(base, offset)	((((*(base + O_DLRX_RXPB_HDR_PEREGRINE_insig7 + offset)) & M_DLRX_RXPB_HDR_PEREGRINE_insig7) >> B_DLRX_RXPB_HDR_PEREGRINE_insig7))

#define DLRX_RXPB_HDR_PEREGRINE_insig7_get_direct(dword)	((((dword) & M_DLRX_RXPB_HDR_PEREGRINE_insig7) >> B_DLRX_RXPB_HDR_PEREGRINE_insig7))

#define DLRX_RXPB_HDR_PEREGRINE_insig7_set_indirect(base, offset, val) \
	do {                                                              \
		(*(base + O_DLRX_RXPB_HDR_PEREGRINE_insig7 + offset)) &= (~(M_DLRX_RXPB_HDR_PEREGRINE_insig7));    \
		(*(base + O_DLRX_RXPB_HDR_PEREGRINE_insig7 + offset)) |= ((val << B_DLRX_RXPB_HDR_PEREGRINE_insig7) & M_DLRX_RXPB_HDR_PEREGRINE_insig7);    \
	} while (0)

#define DLRX_RXPB_HDR_PEREGRINE_insig7_set_direct(dword, val) \
	do {                                                               \
		(dword) &= (~(M_DLRX_RXPB_HDR_PEREGRINE_insig7));    \
		(dword) |= ((val << B_DLRX_RXPB_HDR_PEREGRINE_insig7) & M_DLRX_RXPB_HDR_PEREGRINE_insig7);    \
	} while (0)

#define DLRX_RXPB_HDR_PEREGRINE_insig7_clear_indirect(base, offset)	((*(base + O_DLRX_RXPB_HDR_PEREGRINE_insig7 + offset)) &= (~(M_DLRX_RXPB_HDR_PEREGRINE_insig7)))

#define DLRX_RXPB_HDR_PEREGRINE_insig7_clear_direct(dword)	((dword) &= (~(M_DLRX_RXPB_HDR_PEREGRINE_insig7)))

#define O_DLRX_RXPB_HDR_PEREGRINE_insig8 6
#define B_DLRX_RXPB_HDR_PEREGRINE_insig8 0
#define W_DLRX_RXPB_HDR_PEREGRINE_insig8 32
#define M_DLRX_RXPB_HDR_PEREGRINE_insig8 0xffffffff

#define DLRX_RXPB_HDR_PEREGRINE_insig8_get_indirect(base, offset)	((((*(base + O_DLRX_RXPB_HDR_PEREGRINE_insig8 + offset)) & M_DLRX_RXPB_HDR_PEREGRINE_insig8) >> B_DLRX_RXPB_HDR_PEREGRINE_insig8))

#define DLRX_RXPB_HDR_PEREGRINE_insig8_get_direct(dword)	((((dword) & M_DLRX_RXPB_HDR_PEREGRINE_insig8) >> B_DLRX_RXPB_HDR_PEREGRINE_insig8))

#define DLRX_RXPB_HDR_PEREGRINE_insig8_set_indirect(base, offset, val)    \
	do {                                                              \
		(*(base + O_DLRX_RXPB_HDR_PEREGRINE_insig8 + offset)) &= (~(M_DLRX_RXPB_HDR_PEREGRINE_insig8));    \
		(*(base + O_DLRX_RXPB_HDR_PEREGRINE_insig8 + offset)) |= ((val << B_DLRX_RXPB_HDR_PEREGRINE_insig8) & M_DLRX_RXPB_HDR_PEREGRINE_insig8);    \
	} while (0)

#define DLRX_RXPB_HDR_PEREGRINE_insig8_set_direct(dword, val)    \
	do {                                                               \
		(dword) &= (~(M_DLRX_RXPB_HDR_PEREGRINE_insig8));    \
		(dword) |= ((val << B_DLRX_RXPB_HDR_PEREGRINE_insig8) & M_DLRX_RXPB_HDR_PEREGRINE_insig8);    \
	} while (0)

#define DLRX_RXPB_HDR_PEREGRINE_insig8_clear_indirect(base, offset)	((*(base + O_DLRX_RXPB_HDR_PEREGRINE_insig8 + offset)) &= (~(M_DLRX_RXPB_HDR_PEREGRINE_insig8)))

#define DLRX_RXPB_HDR_PEREGRINE_insig8_clear_direct(dword)	((dword) &= (~(M_DLRX_RXPB_HDR_PEREGRINE_insig8)))

#define O_DLRX_RXPB_HDR_PEREGRINE_insig9 7
#define B_DLRX_RXPB_HDR_PEREGRINE_insig9 0
#define W_DLRX_RXPB_HDR_PEREGRINE_insig9 32
#define M_DLRX_RXPB_HDR_PEREGRINE_insig9 0xffffffff

#define DLRX_RXPB_HDR_PEREGRINE_insig9_get_indirect(base, offset)	((((*(base + O_DLRX_RXPB_HDR_PEREGRINE_insig9 + offset)) & M_DLRX_RXPB_HDR_PEREGRINE_insig9) >> B_DLRX_RXPB_HDR_PEREGRINE_insig9))

#define DLRX_RXPB_HDR_PEREGRINE_insig9_get_direct(dword)	((((dword) & M_DLRX_RXPB_HDR_PEREGRINE_insig9) >> B_DLRX_RXPB_HDR_PEREGRINE_insig9))

#define DLRX_RXPB_HDR_PEREGRINE_insig9_set_indirect(base, offset, val)    \
	do {                                                              \
		(*(base + O_DLRX_RXPB_HDR_PEREGRINE_insig9 + offset)) &= (~(M_DLRX_RXPB_HDR_PEREGRINE_insig9));    \
		(*(base + O_DLRX_RXPB_HDR_PEREGRINE_insig9 + offset)) |= ((val << B_DLRX_RXPB_HDR_PEREGRINE_insig9) & M_DLRX_RXPB_HDR_PEREGRINE_insig9);    \
	} while (0)

#define DLRX_RXPB_HDR_PEREGRINE_insig9_set_direct(dword, val)    \
	do {                                                               \
		(dword) &= (~(M_DLRX_RXPB_HDR_PEREGRINE_insig9));    \
		(dword) |= ((val << B_DLRX_RXPB_HDR_PEREGRINE_insig9) & M_DLRX_RXPB_HDR_PEREGRINE_insig9);    \
	} while (0)

#define DLRX_RXPB_HDR_PEREGRINE_insig9_clear_indirect(base, offset)	((*(base + O_DLRX_RXPB_HDR_PEREGRINE_insig9 + offset)) &= (~(M_DLRX_RXPB_HDR_PEREGRINE_insig9)))

#define DLRX_RXPB_HDR_PEREGRINE_insig9_clear_direct(dword)	((dword) &= (~(M_DLRX_RXPB_HDR_PEREGRINE_insig9)))

#define O_DLRX_RXPB_HDR_PEREGRINE_insig10 8
#define B_DLRX_RXPB_HDR_PEREGRINE_insig10 0
#define W_DLRX_RXPB_HDR_PEREGRINE_insig10 32
#define M_DLRX_RXPB_HDR_PEREGRINE_insig10 0xffffffff

#define DLRX_RXPB_HDR_PEREGRINE_insig10_get_indirect(base, offset)	((((*(base + O_DLRX_RXPB_HDR_PEREGRINE_insig10 + offset)) & M_DLRX_RXPB_HDR_PEREGRINE_insig10) >> B_DLRX_RXPB_HDR_PEREGRINE_insig10))

#define DLRX_RXPB_HDR_PEREGRINE_insig10_get_direct(dword)	((((dword) & M_DLRX_RXPB_HDR_PEREGRINE_insig10) >> B_DLRX_RXPB_HDR_PEREGRINE_insig10))

#define DLRX_RXPB_HDR_PEREGRINE_insig10_set_indirect(base, offset, val)    \
	do {                                                              \
		(*(base + O_DLRX_RXPB_HDR_PEREGRINE_insig10 + offset)) &= (~(M_DLRX_RXPB_HDR_PEREGRINE_insig10));    \
		(*(base + O_DLRX_RXPB_HDR_PEREGRINE_insig10 + offset)) |= ((val << B_DLRX_RXPB_HDR_PEREGRINE_insig10) & M_DLRX_RXPB_HDR_PEREGRINE_insig10);    \
	} while (0)

#define DLRX_RXPB_HDR_PEREGRINE_insig10_set_direct(dword, val)    \
	do {                                                               \
		(dword) &= (~(M_DLRX_RXPB_HDR_PEREGRINE_insig10));    \
		(dword) |= ((val << B_DLRX_RXPB_HDR_PEREGRINE_insig10) & M_DLRX_RXPB_HDR_PEREGRINE_insig10);    \
	} while (0)

#define DLRX_RXPB_HDR_PEREGRINE_insig10_clear_indirect(base, offset)	((*(base + O_DLRX_RXPB_HDR_PEREGRINE_insig10 + offset)) &= (~(M_DLRX_RXPB_HDR_PEREGRINE_insig10)))

#define DLRX_RXPB_HDR_PEREGRINE_insig10_clear_direct(dword)	((dword) &= (~(M_DLRX_RXPB_HDR_PEREGRINE_insig10)))

#define O_DLRX_RXPB_HDR_PEREGRINE_insig11 9
#define B_DLRX_RXPB_HDR_PEREGRINE_insig11 0
#define W_DLRX_RXPB_HDR_PEREGRINE_insig11 16
#define M_DLRX_RXPB_HDR_PEREGRINE_insig11 0x0000ffff

#define DLRX_RXPB_HDR_PEREGRINE_insig11_get_indirect(base, offset)	((((*(base + O_DLRX_RXPB_HDR_PEREGRINE_insig11 + offset)) & M_DLRX_RXPB_HDR_PEREGRINE_insig11) >> B_DLRX_RXPB_HDR_PEREGRINE_insig11))

#define DLRX_RXPB_HDR_PEREGRINE_insig11_get_direct(dword)	((((dword) & M_DLRX_RXPB_HDR_PEREGRINE_insig11) >> B_DLRX_RXPB_HDR_PEREGRINE_insig11))

#define DLRX_RXPB_HDR_PEREGRINE_insig11_set_indirect(base, offset, val) \
	do {                                                              \
		(*(base + O_DLRX_RXPB_HDR_PEREGRINE_insig11 + offset)) &= (~(M_DLRX_RXPB_HDR_PEREGRINE_insig11));    \
		(*(base + O_DLRX_RXPB_HDR_PEREGRINE_insig11 + offset)) |= ((val << B_DLRX_RXPB_HDR_PEREGRINE_insig11) & M_DLRX_RXPB_HDR_PEREGRINE_insig11);    \
	} while (0)

#define DLRX_RXPB_HDR_PEREGRINE_insig11_set_direct(dword, val) \
	do {                                                               \
		(dword) &= (~(M_DLRX_RXPB_HDR_PEREGRINE_insig11));    \
		(dword) |= ((val << B_DLRX_RXPB_HDR_PEREGRINE_insig11) & M_DLRX_RXPB_HDR_PEREGRINE_insig11);    \
	} while (0)

#define DLRX_RXPB_HDR_PEREGRINE_insig11_clear_indirect(base, offset)	((*(base + O_DLRX_RXPB_HDR_PEREGRINE_insig11 + offset)) &= (~(M_DLRX_RXPB_HDR_PEREGRINE_insig11)))

#define DLRX_RXPB_HDR_PEREGRINE_insig11_clear_direct(dword)	((dword) &= (~(M_DLRX_RXPB_HDR_PEREGRINE_insig11)))

#define O_DLRX_RXPB_HDR_PEREGRINE_pn_63_48 9
#define B_DLRX_RXPB_HDR_PEREGRINE_pn_63_48 16
#define W_DLRX_RXPB_HDR_PEREGRINE_pn_63_48 16
#define M_DLRX_RXPB_HDR_PEREGRINE_pn_63_48 0xffff0000

#define DLRX_RXPB_HDR_PEREGRINE_pn_63_48_get_indirect(base, offset)	((((*(base + O_DLRX_RXPB_HDR_PEREGRINE_pn_63_48 + offset)) & M_DLRX_RXPB_HDR_PEREGRINE_pn_63_48) >> B_DLRX_RXPB_HDR_PEREGRINE_pn_63_48))

#define DLRX_RXPB_HDR_PEREGRINE_pn_63_48_get_direct(dword)	((((dword) & M_DLRX_RXPB_HDR_PEREGRINE_pn_63_48) >> B_DLRX_RXPB_HDR_PEREGRINE_pn_63_48))

#define DLRX_RXPB_HDR_PEREGRINE_pn_63_48_set_indirect(base, offset, val) \
	do {                                                              \
		(*(base + O_DLRX_RXPB_HDR_PEREGRINE_pn_63_48 + offset)) &= (~(M_DLRX_RXPB_HDR_PEREGRINE_pn_63_48));    \
		(*(base + O_DLRX_RXPB_HDR_PEREGRINE_pn_63_48 + offset)) |= ((val << B_DLRX_RXPB_HDR_PEREGRINE_pn_63_48) & M_DLRX_RXPB_HDR_PEREGRINE_pn_63_48);    \
	} while (0)

#define DLRX_RXPB_HDR_PEREGRINE_pn_63_48_set_direct(dword, val) \
	do {                                                               \
		(dword) &= (~(M_DLRX_RXPB_HDR_PEREGRINE_pn_63_48));    \
		(dword) |= ((val << B_DLRX_RXPB_HDR_PEREGRINE_pn_63_48) & M_DLRX_RXPB_HDR_PEREGRINE_pn_63_48);    \
	} while (0)

#define DLRX_RXPB_HDR_PEREGRINE_pn_63_48_clear_indirect(base, offset)	((*(base + O_DLRX_RXPB_HDR_PEREGRINE_pn_63_48 + offset)) &= (~(M_DLRX_RXPB_HDR_PEREGRINE_pn_63_48)))

#define DLRX_RXPB_HDR_PEREGRINE_pn_63_48_clear_direct(dword)	((dword) &= (~(M_DLRX_RXPB_HDR_PEREGRINE_pn_63_48)))

#define O_DLRX_RXPB_HDR_PEREGRINE_pn_95_64 10
#define B_DLRX_RXPB_HDR_PEREGRINE_pn_95_64 0
#define W_DLRX_RXPB_HDR_PEREGRINE_pn_95_64 32
#define M_DLRX_RXPB_HDR_PEREGRINE_pn_95_64 0xffffffff

#define DLRX_RXPB_HDR_PEREGRINE_pn_95_64_get_indirect(base, offset)	((((*(base + O_DLRX_RXPB_HDR_PEREGRINE_pn_95_64 + offset)) & M_DLRX_RXPB_HDR_PEREGRINE_pn_95_64) >> B_DLRX_RXPB_HDR_PEREGRINE_pn_95_64))

#define DLRX_RXPB_HDR_PEREGRINE_pn_95_64_get_direct(dword)	((((dword) & M_DLRX_RXPB_HDR_PEREGRINE_pn_95_64) >> B_DLRX_RXPB_HDR_PEREGRINE_pn_95_64))

#define DLRX_RXPB_HDR_PEREGRINE_pn_95_64_set_indirect(base, offset, val)    \
	do {                                                              \
		(*(base + O_DLRX_RXPB_HDR_PEREGRINE_pn_95_64 + offset)) &= (~(M_DLRX_RXPB_HDR_PEREGRINE_pn_95_64));    \
		(*(base + O_DLRX_RXPB_HDR_PEREGRINE_pn_95_64 + offset)) |= ((val << B_DLRX_RXPB_HDR_PEREGRINE_pn_95_64) & M_DLRX_RXPB_HDR_PEREGRINE_pn_95_64);    \
	} while (0)

#define DLRX_RXPB_HDR_PEREGRINE_pn_95_64_set_direct(dword, val)    \
	do {                                                               \
		(dword) &= (~(M_DLRX_RXPB_HDR_PEREGRINE_pn_95_64));    \
		(dword) |= ((val << B_DLRX_RXPB_HDR_PEREGRINE_pn_95_64) & M_DLRX_RXPB_HDR_PEREGRINE_pn_95_64);    \
	} while (0)

#define DLRX_RXPB_HDR_PEREGRINE_pn_95_64_clear_indirect(base, offset)	((*(base + O_DLRX_RXPB_HDR_PEREGRINE_pn_95_64 + offset)) &= (~(M_DLRX_RXPB_HDR_PEREGRINE_pn_95_64)))

#define DLRX_RXPB_HDR_PEREGRINE_pn_95_64_clear_direct(dword)	((dword) &= (~(M_DLRX_RXPB_HDR_PEREGRINE_pn_95_64)))

#define O_DLRX_RXPB_HDR_PEREGRINE_pn_127_96 11
#define B_DLRX_RXPB_HDR_PEREGRINE_pn_127_96 0
#define W_DLRX_RXPB_HDR_PEREGRINE_pn_127_96 32
#define M_DLRX_RXPB_HDR_PEREGRINE_pn_127_96 0xffffffff

#define DLRX_RXPB_HDR_PEREGRINE_pn_127_96_get_indirect(base, offset)	((((*(base + O_DLRX_RXPB_HDR_PEREGRINE_pn_127_96 + offset)) & M_DLRX_RXPB_HDR_PEREGRINE_pn_127_96) >> B_DLRX_RXPB_HDR_PEREGRINE_pn_127_96))

#define DLRX_RXPB_HDR_PEREGRINE_pn_127_96_get_direct(dword)	((((dword) & M_DLRX_RXPB_HDR_PEREGRINE_pn_127_96) >> B_DLRX_RXPB_HDR_PEREGRINE_pn_127_96))

#define DLRX_RXPB_HDR_PEREGRINE_pn_127_96_set_indirect(base, offset, val)    \
	do {                                                              \
		(*(base + O_DLRX_RXPB_HDR_PEREGRINE_pn_127_96 + offset)) &= (~(M_DLRX_RXPB_HDR_PEREGRINE_pn_127_96));    \
		(*(base + O_DLRX_RXPB_HDR_PEREGRINE_pn_127_96 + offset)) |= ((val << B_DLRX_RXPB_HDR_PEREGRINE_pn_127_96) & M_DLRX_RXPB_HDR_PEREGRINE_pn_127_96);    \
	} while (0)

#define DLRX_RXPB_HDR_PEREGRINE_pn_127_96_set_direct(dword, val)    \
	do {                                                               \
		(dword) &= (~(M_DLRX_RXPB_HDR_PEREGRINE_pn_127_96));    \
		(dword) |= ((val << B_DLRX_RXPB_HDR_PEREGRINE_pn_127_96) & M_DLRX_RXPB_HDR_PEREGRINE_pn_127_96);    \
	} while (0)

#define DLRX_RXPB_HDR_PEREGRINE_pn_127_96_clear_indirect(base, offset)	((*(base + O_DLRX_RXPB_HDR_PEREGRINE_pn_127_96 + offset)) &= (~(M_DLRX_RXPB_HDR_PEREGRINE_pn_127_96)))

#define DLRX_RXPB_HDR_PEREGRINE_pn_127_96_clear_direct(dword)	((dword) &= (~(M_DLRX_RXPB_HDR_PEREGRINE_pn_127_96)))

#define O_DLRX_RXPB_HDR_PEREGRINE_insig12 12
#define B_DLRX_RXPB_HDR_PEREGRINE_insig12 0
#define W_DLRX_RXPB_HDR_PEREGRINE_insig12 14
#define M_DLRX_RXPB_HDR_PEREGRINE_insig12 0x00003fff

#define DLRX_RXPB_HDR_PEREGRINE_insig12_get_indirect(base, offset)	((((*(base + O_DLRX_RXPB_HDR_PEREGRINE_insig12 + offset)) & M_DLRX_RXPB_HDR_PEREGRINE_insig12) >> B_DLRX_RXPB_HDR_PEREGRINE_insig12))

#define DLRX_RXPB_HDR_PEREGRINE_insig12_get_direct(dword)	((((dword) & M_DLRX_RXPB_HDR_PEREGRINE_insig12) >> B_DLRX_RXPB_HDR_PEREGRINE_insig12))

#define DLRX_RXPB_HDR_PEREGRINE_insig12_set_indirect(base, offset, val) \
	do {                                                              \
		(*(base + O_DLRX_RXPB_HDR_PEREGRINE_insig12 + offset)) &= (~(M_DLRX_RXPB_HDR_PEREGRINE_insig12));    \
		(*(base + O_DLRX_RXPB_HDR_PEREGRINE_insig12 + offset)) |= ((val << B_DLRX_RXPB_HDR_PEREGRINE_insig12) & M_DLRX_RXPB_HDR_PEREGRINE_insig12);    \
	} while (0)

#define DLRX_RXPB_HDR_PEREGRINE_insig12_set_direct(dword, val) \
	do {                                                               \
		(dword) &= (~(M_DLRX_RXPB_HDR_PEREGRINE_insig12));    \
		(dword) |= ((val << B_DLRX_RXPB_HDR_PEREGRINE_insig12) & M_DLRX_RXPB_HDR_PEREGRINE_insig12);    \
	} while (0)

#define DLRX_RXPB_HDR_PEREGRINE_insig12_clear_indirect(base, offset)	((*(base + O_DLRX_RXPB_HDR_PEREGRINE_insig12 + offset)) &= (~(M_DLRX_RXPB_HDR_PEREGRINE_insig12)))

#define DLRX_RXPB_HDR_PEREGRINE_insig12_clear_direct(dword)	((dword) &= (~(M_DLRX_RXPB_HDR_PEREGRINE_insig12)))

#define O_DLRX_RXPB_HDR_PEREGRINE_first_msdu 12
#define B_DLRX_RXPB_HDR_PEREGRINE_first_msdu 14
#define W_DLRX_RXPB_HDR_PEREGRINE_first_msdu 1
#define M_DLRX_RXPB_HDR_PEREGRINE_first_msdu 0x00004000

#define DLRX_RXPB_HDR_PEREGRINE_first_msdu_get_indirect(base, offset)	((((*(base + O_DLRX_RXPB_HDR_PEREGRINE_first_msdu + offset)) & M_DLRX_RXPB_HDR_PEREGRINE_first_msdu) >> B_DLRX_RXPB_HDR_PEREGRINE_first_msdu))

#define DLRX_RXPB_HDR_PEREGRINE_first_msdu_get_direct(dword)	((((dword) & M_DLRX_RXPB_HDR_PEREGRINE_first_msdu) >> B_DLRX_RXPB_HDR_PEREGRINE_first_msdu))

#define DLRX_RXPB_HDR_PEREGRINE_first_msdu_set_indirect(base, offset, val) \
	do {                                                              \
		(*(base + O_DLRX_RXPB_HDR_PEREGRINE_first_msdu + offset)) &= (~(M_DLRX_RXPB_HDR_PEREGRINE_first_msdu));    \
		(*(base + O_DLRX_RXPB_HDR_PEREGRINE_first_msdu + offset)) |= ((val << B_DLRX_RXPB_HDR_PEREGRINE_first_msdu) & M_DLRX_RXPB_HDR_PEREGRINE_first_msdu);    \
	} while (0)

#define DLRX_RXPB_HDR_PEREGRINE_first_msdu_set_direct(dword, val) \
	do {                                                               \
		(dword) &= (~(M_DLRX_RXPB_HDR_PEREGRINE_first_msdu));    \
		(dword) |= ((val << B_DLRX_RXPB_HDR_PEREGRINE_first_msdu) & M_DLRX_RXPB_HDR_PEREGRINE_first_msdu);    \
	} while (0)

#define DLRX_RXPB_HDR_PEREGRINE_first_msdu_clear_indirect(base, offset)	((*(base + O_DLRX_RXPB_HDR_PEREGRINE_first_msdu + offset)) &= (~(M_DLRX_RXPB_HDR_PEREGRINE_first_msdu)))

#define DLRX_RXPB_HDR_PEREGRINE_first_msdu_clear_direct(dword)	((dword) &= (~(M_DLRX_RXPB_HDR_PEREGRINE_first_msdu)))

#define O_DLRX_RXPB_HDR_PEREGRINE_last_msdu 12
#define B_DLRX_RXPB_HDR_PEREGRINE_last_msdu 15
#define W_DLRX_RXPB_HDR_PEREGRINE_last_msdu 1
#define M_DLRX_RXPB_HDR_PEREGRINE_last_msdu 0x00008000

#define DLRX_RXPB_HDR_PEREGRINE_last_msdu_get_indirect(base, offset)	((((*(base + O_DLRX_RXPB_HDR_PEREGRINE_last_msdu + offset)) & M_DLRX_RXPB_HDR_PEREGRINE_last_msdu) >> B_DLRX_RXPB_HDR_PEREGRINE_last_msdu))

#define DLRX_RXPB_HDR_PEREGRINE_last_msdu_get_direct(dword)	((((dword) & M_DLRX_RXPB_HDR_PEREGRINE_last_msdu) >> B_DLRX_RXPB_HDR_PEREGRINE_last_msdu))

#define DLRX_RXPB_HDR_PEREGRINE_last_msdu_set_indirect(base, offset, val) \
	do {                                                              \
		(*(base + O_DLRX_RXPB_HDR_PEREGRINE_last_msdu + offset)) &= (~(M_DLRX_RXPB_HDR_PEREGRINE_last_msdu));    \
		(*(base + O_DLRX_RXPB_HDR_PEREGRINE_last_msdu + offset)) |= ((val << B_DLRX_RXPB_HDR_PEREGRINE_last_msdu) & M_DLRX_RXPB_HDR_PEREGRINE_last_msdu);    \
	} while (0)

#define DLRX_RXPB_HDR_PEREGRINE_last_msdu_set_direct(dword, val) \
	do {                                                               \
		(dword) &= (~(M_DLRX_RXPB_HDR_PEREGRINE_last_msdu));    \
		(dword) |= ((val << B_DLRX_RXPB_HDR_PEREGRINE_last_msdu) & M_DLRX_RXPB_HDR_PEREGRINE_last_msdu);    \
	} while (0)

#define DLRX_RXPB_HDR_PEREGRINE_last_msdu_clear_indirect(base, offset)	((*(base + O_DLRX_RXPB_HDR_PEREGRINE_last_msdu + offset)) &= (~(M_DLRX_RXPB_HDR_PEREGRINE_last_msdu)))

#define DLRX_RXPB_HDR_PEREGRINE_last_msdu_clear_direct(dword)	((dword) &= (~(M_DLRX_RXPB_HDR_PEREGRINE_last_msdu)))

#define O_DLRX_RXPB_HDR_PEREGRINE_insig13 12
#define B_DLRX_RXPB_HDR_PEREGRINE_insig13 16
#define W_DLRX_RXPB_HDR_PEREGRINE_insig13 16
#define M_DLRX_RXPB_HDR_PEREGRINE_insig13 0xffff0000

#define DLRX_RXPB_HDR_PEREGRINE_insig13_get_indirect(base, offset)	((((*(base + O_DLRX_RXPB_HDR_PEREGRINE_insig13 + offset)) & M_DLRX_RXPB_HDR_PEREGRINE_insig13) >> B_DLRX_RXPB_HDR_PEREGRINE_insig13))

#define DLRX_RXPB_HDR_PEREGRINE_insig13_get_direct(dword)	((((dword) & M_DLRX_RXPB_HDR_PEREGRINE_insig13) >> B_DLRX_RXPB_HDR_PEREGRINE_insig13))

#define DLRX_RXPB_HDR_PEREGRINE_insig13_set_indirect(base, offset, val) \
	do {                                                              \
		(*(base + O_DLRX_RXPB_HDR_PEREGRINE_insig13 + offset)) &= (~(M_DLRX_RXPB_HDR_PEREGRINE_insig13));    \
		(*(base + O_DLRX_RXPB_HDR_PEREGRINE_insig13 + offset)) |= ((val << B_DLRX_RXPB_HDR_PEREGRINE_insig13) & M_DLRX_RXPB_HDR_PEREGRINE_insig13);    \
	} while (0)

#define DLRX_RXPB_HDR_PEREGRINE_insig13_set_direct(dword, val) \
	do {                                                               \
		(dword) &= (~(M_DLRX_RXPB_HDR_PEREGRINE_insig13));    \
		(dword) |= ((val << B_DLRX_RXPB_HDR_PEREGRINE_insig13) & M_DLRX_RXPB_HDR_PEREGRINE_insig13);    \
	} while (0)

#define DLRX_RXPB_HDR_PEREGRINE_insig13_clear_indirect(base, offset)	((*(base + O_DLRX_RXPB_HDR_PEREGRINE_insig13 + offset)) &= (~(M_DLRX_RXPB_HDR_PEREGRINE_insig13)))

#define DLRX_RXPB_HDR_PEREGRINE_insig13_clear_direct(dword)	((dword) &= (~(M_DLRX_RXPB_HDR_PEREGRINE_insig13)))

#define O_DLRX_RXPB_HDR_BEELINER_insig0 0
#define B_DLRX_RXPB_HDR_BEELINER_insig0 0
#define W_DLRX_RXPB_HDR_BEELINER_insig0 2
#define M_DLRX_RXPB_HDR_BEELINER_insig0 0x00000003

#define DLRX_RXPB_HDR_BEELINER_insig0_get_indirect(base, offset)	((((*(base + O_DLRX_RXPB_HDR_BEELINER_insig0 + offset)) & M_DLRX_RXPB_HDR_BEELINER_insig0) >> B_DLRX_RXPB_HDR_BEELINER_insig0))

#define DLRX_RXPB_HDR_BEELINER_insig0_get_direct(dword)	((((dword) & M_DLRX_RXPB_HDR_BEELINER_insig0) >> B_DLRX_RXPB_HDR_BEELINER_insig0))

#define DLRX_RXPB_HDR_BEELINER_insig0_set_indirect(base, offset, val) \
	do {                                                              \
		(*(base + O_DLRX_RXPB_HDR_BEELINER_insig0 + offset)) &= (~(M_DLRX_RXPB_HDR_BEELINER_insig0));    \
		(*(base + O_DLRX_RXPB_HDR_BEELINER_insig0 + offset)) |= ((val << B_DLRX_RXPB_HDR_BEELINER_insig0) & M_DLRX_RXPB_HDR_BEELINER_insig0);    \
	} while (0)

#define DLRX_RXPB_HDR_BEELINER_insig0_set_direct(dword, val) \
	do {                                                               \
		(dword) &= (~(M_DLRX_RXPB_HDR_BEELINER_insig0));    \
		(dword) |= ((val << B_DLRX_RXPB_HDR_BEELINER_insig0) & M_DLRX_RXPB_HDR_BEELINER_insig0);    \
	} while (0)

#define DLRX_RXPB_HDR_BEELINER_insig0_clear_indirect(base, offset)	((*(base + O_DLRX_RXPB_HDR_BEELINER_insig0 + offset)) &= (~(M_DLRX_RXPB_HDR_BEELINER_insig0)))

#define DLRX_RXPB_HDR_BEELINER_insig0_clear_direct(dword)	((dword) &= (~(M_DLRX_RXPB_HDR_BEELINER_insig0)))

#define O_DLRX_RXPB_HDR_BEELINER_mcast_bcast 0
#define B_DLRX_RXPB_HDR_BEELINER_mcast_bcast 2
#define W_DLRX_RXPB_HDR_BEELINER_mcast_bcast 1
#define M_DLRX_RXPB_HDR_BEELINER_mcast_bcast 0x00000004

#define DLRX_RXPB_HDR_BEELINER_mcast_bcast_get_indirect(base, offset)	((((*(base + O_DLRX_RXPB_HDR_BEELINER_mcast_bcast + offset)) & M_DLRX_RXPB_HDR_BEELINER_mcast_bcast) >> B_DLRX_RXPB_HDR_BEELINER_mcast_bcast))

#define DLRX_RXPB_HDR_BEELINER_mcast_bcast_get_direct(dword)	((((dword) & M_DLRX_RXPB_HDR_BEELINER_mcast_bcast) >> B_DLRX_RXPB_HDR_BEELINER_mcast_bcast))

#define DLRX_RXPB_HDR_BEELINER_mcast_bcast_set_indirect(base, offset, val) \
	do {                                                              \
		(*(base + O_DLRX_RXPB_HDR_BEELINER_mcast_bcast + offset)) &= (~(M_DLRX_RXPB_HDR_BEELINER_mcast_bcast));    \
		(*(base + O_DLRX_RXPB_HDR_BEELINER_mcast_bcast + offset)) |= ((val << B_DLRX_RXPB_HDR_BEELINER_mcast_bcast) & M_DLRX_RXPB_HDR_BEELINER_mcast_bcast);    \
	} while (0)

#define DLRX_RXPB_HDR_BEELINER_mcast_bcast_set_direct(dword, val) \
	do {                                                               \
		(dword) &= (~(M_DLRX_RXPB_HDR_BEELINER_mcast_bcast));    \
		(dword) |= ((val << B_DLRX_RXPB_HDR_BEELINER_mcast_bcast) & M_DLRX_RXPB_HDR_BEELINER_mcast_bcast);    \
	} while (0)

#define DLRX_RXPB_HDR_BEELINER_mcast_bcast_clear_indirect(base, offset)	((*(base + O_DLRX_RXPB_HDR_BEELINER_mcast_bcast + offset)) &= (~(M_DLRX_RXPB_HDR_BEELINER_mcast_bcast)))

#define DLRX_RXPB_HDR_BEELINER_mcast_bcast_clear_direct(dword)	((dword) &= (~(M_DLRX_RXPB_HDR_BEELINER_mcast_bcast)))

#define O_DLRX_RXPB_HDR_BEELINER_insig1 0
#define B_DLRX_RXPB_HDR_BEELINER_insig1 3
#define W_DLRX_RXPB_HDR_BEELINER_insig1 28
#define M_DLRX_RXPB_HDR_BEELINER_insig1 0x7ffffff8

#define DLRX_RXPB_HDR_BEELINER_insig1_get_indirect(base, offset)	((((*(base + O_DLRX_RXPB_HDR_BEELINER_insig1 + offset)) & M_DLRX_RXPB_HDR_BEELINER_insig1) >> B_DLRX_RXPB_HDR_BEELINER_insig1))

#define DLRX_RXPB_HDR_BEELINER_insig1_get_direct(dword)	((((dword) & M_DLRX_RXPB_HDR_BEELINER_insig1) >> B_DLRX_RXPB_HDR_BEELINER_insig1))

#define DLRX_RXPB_HDR_BEELINER_insig1_set_indirect(base, offset, val) \
	do {                                                              \
		(*(base + O_DLRX_RXPB_HDR_BEELINER_insig1 + offset)) &= (~(M_DLRX_RXPB_HDR_BEELINER_insig1));    \
		(*(base + O_DLRX_RXPB_HDR_BEELINER_insig1 + offset)) |= ((val << B_DLRX_RXPB_HDR_BEELINER_insig1) & M_DLRX_RXPB_HDR_BEELINER_insig1);    \
	} while (0)

#define DLRX_RXPB_HDR_BEELINER_insig1_set_direct(dword, val) \
	do {                                                               \
		(dword) &= (~(M_DLRX_RXPB_HDR_BEELINER_insig1));    \
		(dword) |= ((val << B_DLRX_RXPB_HDR_BEELINER_insig1) & M_DLRX_RXPB_HDR_BEELINER_insig1);    \
	} while (0)

#define DLRX_RXPB_HDR_BEELINER_insig1_clear_indirect(base, offset)	((*(base + O_DLRX_RXPB_HDR_BEELINER_insig1 + offset)) &= (~(M_DLRX_RXPB_HDR_BEELINER_insig1)))

#define DLRX_RXPB_HDR_BEELINER_insig1_clear_direct(dword)	((dword) &= (~(M_DLRX_RXPB_HDR_BEELINER_insig1)))

#define O_DLRX_RXPB_HDR_BEELINER_msdu_load_status 0
#define B_DLRX_RXPB_HDR_BEELINER_msdu_load_status 31
#define W_DLRX_RXPB_HDR_BEELINER_msdu_load_status 1
#define M_DLRX_RXPB_HDR_BEELINER_msdu_load_status 0x80000000

#define DLRX_RXPB_HDR_BEELINER_msdu_load_status_get_indirect(base, offset)	((((*(base + O_DLRX_RXPB_HDR_BEELINER_msdu_load_status + offset)) & M_DLRX_RXPB_HDR_BEELINER_msdu_load_status) >> B_DLRX_RXPB_HDR_BEELINER_msdu_load_status))

#define DLRX_RXPB_HDR_BEELINER_msdu_load_status_get_direct(dword)	((((dword) & M_DLRX_RXPB_HDR_BEELINER_msdu_load_status) >> B_DLRX_RXPB_HDR_BEELINER_msdu_load_status))

#define DLRX_RXPB_HDR_BEELINER_msdu_load_status_set_indirect(base, offset, val) \
	do {                                                              \
		(*(base + O_DLRX_RXPB_HDR_BEELINER_msdu_load_status + offset)) &= (~(M_DLRX_RXPB_HDR_BEELINER_msdu_load_status));    \
		(*(base + O_DLRX_RXPB_HDR_BEELINER_msdu_load_status + offset)) |= ((val << B_DLRX_RXPB_HDR_BEELINER_msdu_load_status) & M_DLRX_RXPB_HDR_BEELINER_msdu_load_status);    \
	} while (0)

#define DLRX_RXPB_HDR_BEELINER_msdu_load_status_set_direct(dword, val) \
	do {                                                               \
		(dword) &= (~(M_DLRX_RXPB_HDR_BEELINER_msdu_load_status));    \
		(dword) |= ((val << B_DLRX_RXPB_HDR_BEELINER_msdu_load_status) & M_DLRX_RXPB_HDR_BEELINER_msdu_load_status);    \
	} while (0)

#define DLRX_RXPB_HDR_BEELINER_msdu_load_status_clear_indirect(base, offset)	((*(base + O_DLRX_RXPB_HDR_BEELINER_msdu_load_status + offset)) &= (~(M_DLRX_RXPB_HDR_BEELINER_msdu_load_status)))

#define DLRX_RXPB_HDR_BEELINER_msdu_load_status_clear_direct(dword)	((dword) &= (~(M_DLRX_RXPB_HDR_BEELINER_msdu_load_status)))

#define O_DLRX_RXPB_HDR_BEELINER_insig2 1
#define B_DLRX_RXPB_HDR_BEELINER_insig2 0
#define W_DLRX_RXPB_HDR_BEELINER_insig2 16
#define M_DLRX_RXPB_HDR_BEELINER_insig2 0x0000ffff

#define DLRX_RXPB_HDR_BEELINER_insig2_get_indirect(base, offset)	((((*(base + O_DLRX_RXPB_HDR_BEELINER_insig2 + offset)) & M_DLRX_RXPB_HDR_BEELINER_insig2) >> B_DLRX_RXPB_HDR_BEELINER_insig2))

#define DLRX_RXPB_HDR_BEELINER_insig2_get_direct(dword)	((((dword) & M_DLRX_RXPB_HDR_BEELINER_insig2) >> B_DLRX_RXPB_HDR_BEELINER_insig2))

#define DLRX_RXPB_HDR_BEELINER_insig2_set_indirect(base, offset, val) \
	do {                                                              \
		(*(base + O_DLRX_RXPB_HDR_BEELINER_insig2 + offset)) &= (~(M_DLRX_RXPB_HDR_BEELINER_insig2));    \
		(*(base + O_DLRX_RXPB_HDR_BEELINER_insig2 + offset)) |= ((val << B_DLRX_RXPB_HDR_BEELINER_insig2) & M_DLRX_RXPB_HDR_BEELINER_insig2);    \
	} while (0)

#define DLRX_RXPB_HDR_BEELINER_insig2_set_direct(dword, val) \
	do {                                                               \
		(dword) &= (~(M_DLRX_RXPB_HDR_BEELINER_insig2));    \
		(dword) |= ((val << B_DLRX_RXPB_HDR_BEELINER_insig2) & M_DLRX_RXPB_HDR_BEELINER_insig2);    \
	} while (0)

#define DLRX_RXPB_HDR_BEELINER_insig2_clear_indirect(base, offset)	((*(base + O_DLRX_RXPB_HDR_BEELINER_insig2 + offset)) &= (~(M_DLRX_RXPB_HDR_BEELINER_insig2)))

#define DLRX_RXPB_HDR_BEELINER_insig2_clear_direct(dword)	((dword) &= (~(M_DLRX_RXPB_HDR_BEELINER_insig2)))

#define O_DLRX_RXPB_HDR_BEELINER_msdu_chain_num 1
#define B_DLRX_RXPB_HDR_BEELINER_msdu_chain_num 16
#define W_DLRX_RXPB_HDR_BEELINER_msdu_chain_num 8
#define M_DLRX_RXPB_HDR_BEELINER_msdu_chain_num 0x00ff0000

#define DLRX_RXPB_HDR_BEELINER_msdu_chain_num_get_indirect(base, offset)	((((*(base + O_DLRX_RXPB_HDR_BEELINER_msdu_chain_num + offset)) & M_DLRX_RXPB_HDR_BEELINER_msdu_chain_num) >> B_DLRX_RXPB_HDR_BEELINER_msdu_chain_num))

#define DLRX_RXPB_HDR_BEELINER_msdu_chain_num_get_direct(dword)	((((dword) & M_DLRX_RXPB_HDR_BEELINER_msdu_chain_num) >> B_DLRX_RXPB_HDR_BEELINER_msdu_chain_num))

#define DLRX_RXPB_HDR_BEELINER_msdu_chain_num_set_indirect(base, offset, val) \
	do {                                                              \
		(*(base + O_DLRX_RXPB_HDR_BEELINER_msdu_chain_num + offset)) &= (~(M_DLRX_RXPB_HDR_BEELINER_msdu_chain_num));    \
		(*(base + O_DLRX_RXPB_HDR_BEELINER_msdu_chain_num + offset)) |= ((val << B_DLRX_RXPB_HDR_BEELINER_msdu_chain_num) & M_DLRX_RXPB_HDR_BEELINER_msdu_chain_num);    \
	} while (0)

#define DLRX_RXPB_HDR_BEELINER_msdu_chain_num_set_direct(dword, val) \
	do {                                                               \
		(dword) &= (~(M_DLRX_RXPB_HDR_BEELINER_msdu_chain_num));    \
		(dword) |= ((val << B_DLRX_RXPB_HDR_BEELINER_msdu_chain_num) & M_DLRX_RXPB_HDR_BEELINER_msdu_chain_num);    \
	} while (0)

#define DLRX_RXPB_HDR_BEELINER_msdu_chain_num_clear_indirect(base, offset)	((*(base + O_DLRX_RXPB_HDR_BEELINER_msdu_chain_num + offset)) &= (~(M_DLRX_RXPB_HDR_BEELINER_msdu_chain_num)))

#define DLRX_RXPB_HDR_BEELINER_msdu_chain_num_clear_direct(dword)	((dword) &= (~(M_DLRX_RXPB_HDR_BEELINER_msdu_chain_num)))

#define O_DLRX_RXPB_HDR_BEELINER_insig3 1
#define B_DLRX_RXPB_HDR_BEELINER_insig3 24
#define W_DLRX_RXPB_HDR_BEELINER_insig3 8
#define M_DLRX_RXPB_HDR_BEELINER_insig3 0xff000000

#define DLRX_RXPB_HDR_BEELINER_insig3_get_indirect(base, offset)	((((*(base + O_DLRX_RXPB_HDR_BEELINER_insig3 + offset)) & M_DLRX_RXPB_HDR_BEELINER_insig3) >> B_DLRX_RXPB_HDR_BEELINER_insig3))

#define DLRX_RXPB_HDR_BEELINER_insig3_get_direct(dword)	((((dword) & M_DLRX_RXPB_HDR_BEELINER_insig3) >> B_DLRX_RXPB_HDR_BEELINER_insig3))

#define DLRX_RXPB_HDR_BEELINER_insig3_set_indirect(base, offset, val) \
	do {                                                              \
		(*(base + O_DLRX_RXPB_HDR_BEELINER_insig3 + offset)) &= (~(M_DLRX_RXPB_HDR_BEELINER_insig3));    \
		(*(base + O_DLRX_RXPB_HDR_BEELINER_insig3 + offset)) |= ((val << B_DLRX_RXPB_HDR_BEELINER_insig3) & M_DLRX_RXPB_HDR_BEELINER_insig3);    \
	} while (0)

#define DLRX_RXPB_HDR_BEELINER_insig3_set_direct(dword, val) \
	do {                                                               \
		(dword) &= (~(M_DLRX_RXPB_HDR_BEELINER_insig3));    \
		(dword) |= ((val << B_DLRX_RXPB_HDR_BEELINER_insig3) & M_DLRX_RXPB_HDR_BEELINER_insig3);    \
	} while (0)

#define DLRX_RXPB_HDR_BEELINER_insig3_clear_indirect(base, offset)	((*(base + O_DLRX_RXPB_HDR_BEELINER_insig3 + offset)) &= (~(M_DLRX_RXPB_HDR_BEELINER_insig3)))

#define DLRX_RXPB_HDR_BEELINER_insig3_clear_direct(dword)	((dword) &= (~(M_DLRX_RXPB_HDR_BEELINER_insig3)))

#define O_DLRX_RXPB_HDR_BEELINER_insig4 2
#define B_DLRX_RXPB_HDR_BEELINER_insig4 0
#define W_DLRX_RXPB_HDR_BEELINER_insig4 16
#define M_DLRX_RXPB_HDR_BEELINER_insig4 0x0000ffff

#define DLRX_RXPB_HDR_BEELINER_insig4_get_indirect(base, offset)	((((*(base + O_DLRX_RXPB_HDR_BEELINER_insig4 + offset)) & M_DLRX_RXPB_HDR_BEELINER_insig4) >> B_DLRX_RXPB_HDR_BEELINER_insig4))

#define DLRX_RXPB_HDR_BEELINER_insig4_get_direct(dword)	((((dword) & M_DLRX_RXPB_HDR_BEELINER_insig4) >> B_DLRX_RXPB_HDR_BEELINER_insig4))

#define DLRX_RXPB_HDR_BEELINER_insig4_set_indirect(base, offset, val) \
	do {                                                              \
		(*(base + O_DLRX_RXPB_HDR_BEELINER_insig4 + offset)) &= (~(M_DLRX_RXPB_HDR_BEELINER_insig4));    \
		(*(base + O_DLRX_RXPB_HDR_BEELINER_insig4 + offset)) |= ((val << B_DLRX_RXPB_HDR_BEELINER_insig4) & M_DLRX_RXPB_HDR_BEELINER_insig4);    \
	} while (0)

#define DLRX_RXPB_HDR_BEELINER_insig4_set_direct(dword, val) \
	do {                                                               \
		(dword) &= (~(M_DLRX_RXPB_HDR_BEELINER_insig4));    \
		(dword) |= ((val << B_DLRX_RXPB_HDR_BEELINER_insig4) & M_DLRX_RXPB_HDR_BEELINER_insig4);    \
	} while (0)

#define DLRX_RXPB_HDR_BEELINER_insig4_clear_indirect(base, offset)	((*(base + O_DLRX_RXPB_HDR_BEELINER_insig4 + offset)) &= (~(M_DLRX_RXPB_HDR_BEELINER_insig4)))

#define DLRX_RXPB_HDR_BEELINER_insig4_clear_direct(dword)	((dword) &= (~(M_DLRX_RXPB_HDR_BEELINER_insig4)))

#define O_DLRX_RXPB_HDR_BEELINER_seqid 2
#define B_DLRX_RXPB_HDR_BEELINER_seqid 16
#define W_DLRX_RXPB_HDR_BEELINER_seqid 12
#define M_DLRX_RXPB_HDR_BEELINER_seqid 0x0fff0000

#define DLRX_RXPB_HDR_BEELINER_seqid_get_indirect(base, offset)	((((*(base + O_DLRX_RXPB_HDR_BEELINER_seqid + offset)) & M_DLRX_RXPB_HDR_BEELINER_seqid) >> B_DLRX_RXPB_HDR_BEELINER_seqid))

#define DLRX_RXPB_HDR_BEELINER_seqid_get_direct(dword)	((((dword) & M_DLRX_RXPB_HDR_BEELINER_seqid) >> B_DLRX_RXPB_HDR_BEELINER_seqid))

#define DLRX_RXPB_HDR_BEELINER_seqid_set_indirect(base, offset, val) \
	do {                                                              \
		(*(base + O_DLRX_RXPB_HDR_BEELINER_seqid + offset)) &= (~(M_DLRX_RXPB_HDR_BEELINER_seqid));    \
		(*(base + O_DLRX_RXPB_HDR_BEELINER_seqid + offset)) |= ((val << B_DLRX_RXPB_HDR_BEELINER_seqid) & M_DLRX_RXPB_HDR_BEELINER_seqid);    \
	} while (0)

#define DLRX_RXPB_HDR_BEELINER_seqid_set_direct(dword, val) \
	do {                                                               \
		(dword) &= (~(M_DLRX_RXPB_HDR_BEELINER_seqid));    \
		(dword) |= ((val << B_DLRX_RXPB_HDR_BEELINER_seqid) & M_DLRX_RXPB_HDR_BEELINER_seqid);    \
	} while (0)

#define DLRX_RXPB_HDR_BEELINER_seqid_clear_indirect(base, offset)	((*(base + O_DLRX_RXPB_HDR_BEELINER_seqid + offset)) &= (~(M_DLRX_RXPB_HDR_BEELINER_seqid)))

#define DLRX_RXPB_HDR_BEELINER_seqid_clear_direct(dword)	((dword) &= (~(M_DLRX_RXPB_HDR_BEELINER_seqid)))

#define O_DLRX_RXPB_HDR_BEELINER_insig5 2
#define B_DLRX_RXPB_HDR_BEELINER_insig5 28
#define W_DLRX_RXPB_HDR_BEELINER_insig5 4
#define M_DLRX_RXPB_HDR_BEELINER_insig5 0xf0000000

#define DLRX_RXPB_HDR_BEELINER_insig5_get_indirect(base, offset)	((((*(base + O_DLRX_RXPB_HDR_BEELINER_insig5 + offset)) & M_DLRX_RXPB_HDR_BEELINER_insig5) >> B_DLRX_RXPB_HDR_BEELINER_insig5))

#define DLRX_RXPB_HDR_BEELINER_insig5_get_direct(dword)	((((dword) & M_DLRX_RXPB_HDR_BEELINER_insig5) >> B_DLRX_RXPB_HDR_BEELINER_insig5))

#define DLRX_RXPB_HDR_BEELINER_insig5_set_indirect(base, offset, val) \
	do {                                                              \
		(*(base + O_DLRX_RXPB_HDR_BEELINER_insig5 + offset)) &= (~(M_DLRX_RXPB_HDR_BEELINER_insig5));    \
		(*(base + O_DLRX_RXPB_HDR_BEELINER_insig5 + offset)) |= ((val << B_DLRX_RXPB_HDR_BEELINER_insig5) & M_DLRX_RXPB_HDR_BEELINER_insig5);    \
	} while (0)

#define DLRX_RXPB_HDR_BEELINER_insig5_set_direct(dword, val) \
	do {                                                               \
		(dword) &= (~(M_DLRX_RXPB_HDR_BEELINER_insig5));    \
		(dword) |= ((val << B_DLRX_RXPB_HDR_BEELINER_insig5) & M_DLRX_RXPB_HDR_BEELINER_insig5);    \
	} while (0)

#define DLRX_RXPB_HDR_BEELINER_insig5_clear_indirect(base, offset)	((*(base + O_DLRX_RXPB_HDR_BEELINER_insig5 + offset)) &= (~(M_DLRX_RXPB_HDR_BEELINER_insig5)))

#define DLRX_RXPB_HDR_BEELINER_insig5_clear_direct(dword)	((dword) &= (~(M_DLRX_RXPB_HDR_BEELINER_insig5)))

#define O_DLRX_RXPB_HDR_BEELINER_pn_31_0 3
#define B_DLRX_RXPB_HDR_BEELINER_pn_31_0 0
#define W_DLRX_RXPB_HDR_BEELINER_pn_31_0 32
#define M_DLRX_RXPB_HDR_BEELINER_pn_31_0 0xffffffff

#define DLRX_RXPB_HDR_BEELINER_pn_31_0_get_indirect(base, offset)	((((*(base + O_DLRX_RXPB_HDR_BEELINER_pn_31_0 + offset)) & M_DLRX_RXPB_HDR_BEELINER_pn_31_0) >> B_DLRX_RXPB_HDR_BEELINER_pn_31_0))

#define DLRX_RXPB_HDR_BEELINER_pn_31_0_get_direct(dword)	((((dword) & M_DLRX_RXPB_HDR_BEELINER_pn_31_0) >> B_DLRX_RXPB_HDR_BEELINER_pn_31_0))

#define DLRX_RXPB_HDR_BEELINER_pn_31_0_set_indirect(base, offset, val)    \
	do {                                                              \
		(*(base + O_DLRX_RXPB_HDR_BEELINER_pn_31_0 + offset)) &= (~(M_DLRX_RXPB_HDR_BEELINER_pn_31_0));    \
		(*(base + O_DLRX_RXPB_HDR_BEELINER_pn_31_0 + offset)) |= ((val << B_DLRX_RXPB_HDR_BEELINER_pn_31_0) & M_DLRX_RXPB_HDR_BEELINER_pn_31_0);    \
	} while (0)

#define DLRX_RXPB_HDR_BEELINER_pn_31_0_set_direct(dword, val)    \
	do {                                                               \
		(dword) &= (~(M_DLRX_RXPB_HDR_BEELINER_pn_31_0));    \
		(dword) |= ((val << B_DLRX_RXPB_HDR_BEELINER_pn_31_0) & M_DLRX_RXPB_HDR_BEELINER_pn_31_0);    \
	} while (0)

#define DLRX_RXPB_HDR_BEELINER_pn_31_0_clear_indirect(base, offset)	((*(base + O_DLRX_RXPB_HDR_BEELINER_pn_31_0 + offset)) &= (~(M_DLRX_RXPB_HDR_BEELINER_pn_31_0)))

#define DLRX_RXPB_HDR_BEELINER_pn_31_0_clear_direct(dword)	((dword) &= (~(M_DLRX_RXPB_HDR_BEELINER_pn_31_0)))

#define O_DLRX_RXPB_HDR_BEELINER_pn_47_32 4
#define B_DLRX_RXPB_HDR_BEELINER_pn_47_32 0
#define W_DLRX_RXPB_HDR_BEELINER_pn_47_32 16
#define M_DLRX_RXPB_HDR_BEELINER_pn_47_32 0x0000ffff

#define DLRX_RXPB_HDR_BEELINER_pn_47_32_get_indirect(base, offset)	((((*(base + O_DLRX_RXPB_HDR_BEELINER_pn_47_32 + offset)) & M_DLRX_RXPB_HDR_BEELINER_pn_47_32) >> B_DLRX_RXPB_HDR_BEELINER_pn_47_32))

#define DLRX_RXPB_HDR_BEELINER_pn_47_32_get_direct(dword)	((((dword) & M_DLRX_RXPB_HDR_BEELINER_pn_47_32) >> B_DLRX_RXPB_HDR_BEELINER_pn_47_32))

#define DLRX_RXPB_HDR_BEELINER_pn_47_32_set_indirect(base, offset, val) \
	do {                                                              \
		(*(base + O_DLRX_RXPB_HDR_BEELINER_pn_47_32 + offset)) &= (~(M_DLRX_RXPB_HDR_BEELINER_pn_47_32));    \
		(*(base + O_DLRX_RXPB_HDR_BEELINER_pn_47_32 + offset)) |= ((val << B_DLRX_RXPB_HDR_BEELINER_pn_47_32) & M_DLRX_RXPB_HDR_BEELINER_pn_47_32);    \
	} while (0)

#define DLRX_RXPB_HDR_BEELINER_pn_47_32_set_direct(dword, val) \
	do {                                                               \
		(dword) &= (~(M_DLRX_RXPB_HDR_BEELINER_pn_47_32));    \
		(dword) |= ((val << B_DLRX_RXPB_HDR_BEELINER_pn_47_32) & M_DLRX_RXPB_HDR_BEELINER_pn_47_32);    \
	} while (0)

#define DLRX_RXPB_HDR_BEELINER_pn_47_32_clear_indirect(base, offset)	((*(base + O_DLRX_RXPB_HDR_BEELINER_pn_47_32 + offset)) &= (~(M_DLRX_RXPB_HDR_BEELINER_pn_47_32)))

#define DLRX_RXPB_HDR_BEELINER_pn_47_32_clear_direct(dword)	((dword) &= (~(M_DLRX_RXPB_HDR_BEELINER_pn_47_32)))

#define O_DLRX_RXPB_HDR_BEELINER_insig6 4
#define B_DLRX_RXPB_HDR_BEELINER_insig6 16
#define W_DLRX_RXPB_HDR_BEELINER_insig6 16
#define M_DLRX_RXPB_HDR_BEELINER_insig6 0xffff0000

#define DLRX_RXPB_HDR_BEELINER_insig6_get_indirect(base, offset)	((((*(base + O_DLRX_RXPB_HDR_BEELINER_insig6 + offset)) & M_DLRX_RXPB_HDR_BEELINER_insig6) >> B_DLRX_RXPB_HDR_BEELINER_insig6))

#define DLRX_RXPB_HDR_BEELINER_insig6_get_direct(dword)	((((dword) & M_DLRX_RXPB_HDR_BEELINER_insig6) >> B_DLRX_RXPB_HDR_BEELINER_insig6))

#define DLRX_RXPB_HDR_BEELINER_insig6_set_indirect(base, offset, val) \
	do {                                                              \
		(*(base + O_DLRX_RXPB_HDR_BEELINER_insig6 + offset)) &= (~(M_DLRX_RXPB_HDR_BEELINER_insig6));    \
		(*(base + O_DLRX_RXPB_HDR_BEELINER_insig6 + offset)) |= ((val << B_DLRX_RXPB_HDR_BEELINER_insig6) & M_DLRX_RXPB_HDR_BEELINER_insig6);    \
	} while (0)

#define DLRX_RXPB_HDR_BEELINER_insig6_set_direct(dword, val) \
	do {                                                               \
		(dword) &= (~(M_DLRX_RXPB_HDR_BEELINER_insig6));    \
		(dword) |= ((val << B_DLRX_RXPB_HDR_BEELINER_insig6) & M_DLRX_RXPB_HDR_BEELINER_insig6);    \
	} while (0)

#define DLRX_RXPB_HDR_BEELINER_insig6_clear_indirect(base, offset)	((*(base + O_DLRX_RXPB_HDR_BEELINER_insig6 + offset)) &= (~(M_DLRX_RXPB_HDR_BEELINER_insig6)))

#define DLRX_RXPB_HDR_BEELINER_insig6_clear_direct(dword)	((dword) &= (~(M_DLRX_RXPB_HDR_BEELINER_insig6)))

#define O_DLRX_RXPB_HDR_BEELINER_msdu_len 5
#define B_DLRX_RXPB_HDR_BEELINER_msdu_len 0
#define W_DLRX_RXPB_HDR_BEELINER_msdu_len 14
#define M_DLRX_RXPB_HDR_BEELINER_msdu_len 0x00003fff

#define DLRX_RXPB_HDR_BEELINER_msdu_len_get_indirect(base, offset)	((((*(base + O_DLRX_RXPB_HDR_BEELINER_msdu_len + offset)) & M_DLRX_RXPB_HDR_BEELINER_msdu_len) >> B_DLRX_RXPB_HDR_BEELINER_msdu_len))

#define DLRX_RXPB_HDR_BEELINER_msdu_len_get_direct(dword)	((((dword) & M_DLRX_RXPB_HDR_BEELINER_msdu_len) >> B_DLRX_RXPB_HDR_BEELINER_msdu_len))

#define DLRX_RXPB_HDR_BEELINER_msdu_len_set_indirect(base, offset, val) \
	do {                                                              \
		(*(base + O_DLRX_RXPB_HDR_BEELINER_msdu_len + offset)) &= (~(M_DLRX_RXPB_HDR_BEELINER_msdu_len));    \
		(*(base + O_DLRX_RXPB_HDR_BEELINER_msdu_len + offset)) |= ((val << B_DLRX_RXPB_HDR_BEELINER_msdu_len) & M_DLRX_RXPB_HDR_BEELINER_msdu_len);    \
	} while (0)

#define DLRX_RXPB_HDR_BEELINER_msdu_len_set_direct(dword, val) \
	do {                                                               \
		(dword) &= (~(M_DLRX_RXPB_HDR_BEELINER_msdu_len));    \
		(dword) |= ((val << B_DLRX_RXPB_HDR_BEELINER_msdu_len) & M_DLRX_RXPB_HDR_BEELINER_msdu_len);    \
	} while (0)

#define DLRX_RXPB_HDR_BEELINER_msdu_len_clear_indirect(base, offset)	((*(base + O_DLRX_RXPB_HDR_BEELINER_msdu_len + offset)) &= (~(M_DLRX_RXPB_HDR_BEELINER_msdu_len)))

#define DLRX_RXPB_HDR_BEELINER_msdu_len_clear_direct(dword)	((dword) &= (~(M_DLRX_RXPB_HDR_BEELINER_msdu_len)))

#define O_DLRX_RXPB_HDR_BEELINER_insig7 5
#define B_DLRX_RXPB_HDR_BEELINER_insig7 14
#define W_DLRX_RXPB_HDR_BEELINER_insig7 18
#define M_DLRX_RXPB_HDR_BEELINER_insig7 0xffffc000

#define DLRX_RXPB_HDR_BEELINER_insig7_get_indirect(base, offset)	((((*(base + O_DLRX_RXPB_HDR_BEELINER_insig7 + offset)) & M_DLRX_RXPB_HDR_BEELINER_insig7) >> B_DLRX_RXPB_HDR_BEELINER_insig7))

#define DLRX_RXPB_HDR_BEELINER_insig7_get_direct(dword)	((((dword) & M_DLRX_RXPB_HDR_BEELINER_insig7) >> B_DLRX_RXPB_HDR_BEELINER_insig7))

#define DLRX_RXPB_HDR_BEELINER_insig7_set_indirect(base, offset, val) \
	do {                                                              \
		(*(base + O_DLRX_RXPB_HDR_BEELINER_insig7 + offset)) &= (~(M_DLRX_RXPB_HDR_BEELINER_insig7));    \
		(*(base + O_DLRX_RXPB_HDR_BEELINER_insig7 + offset)) |= ((val << B_DLRX_RXPB_HDR_BEELINER_insig7) & M_DLRX_RXPB_HDR_BEELINER_insig7);    \
	} while (0)

#define DLRX_RXPB_HDR_BEELINER_insig7_set_direct(dword, val) \
	do {                                                               \
		(dword) &= (~(M_DLRX_RXPB_HDR_BEELINER_insig7));    \
		(dword) |= ((val << B_DLRX_RXPB_HDR_BEELINER_insig7) & M_DLRX_RXPB_HDR_BEELINER_insig7);    \
	} while (0)

#define DLRX_RXPB_HDR_BEELINER_insig7_clear_indirect(base, offset)	((*(base + O_DLRX_RXPB_HDR_BEELINER_insig7 + offset)) &= (~(M_DLRX_RXPB_HDR_BEELINER_insig7)))

#define DLRX_RXPB_HDR_BEELINER_insig7_clear_direct(dword)	((dword) &= (~(M_DLRX_RXPB_HDR_BEELINER_insig7)))

#define O_DLRX_RXPB_HDR_BEELINER_insig8 6
#define B_DLRX_RXPB_HDR_BEELINER_insig8 0
#define W_DLRX_RXPB_HDR_BEELINER_insig8 32
#define M_DLRX_RXPB_HDR_BEELINER_insig8 0xffffffff

#define DLRX_RXPB_HDR_BEELINER_insig8_get_indirect(base, offset)	((((*(base + O_DLRX_RXPB_HDR_BEELINER_insig8 + offset)) & M_DLRX_RXPB_HDR_BEELINER_insig8) >> B_DLRX_RXPB_HDR_BEELINER_insig8))

#define DLRX_RXPB_HDR_BEELINER_insig8_get_direct(dword)	((((dword) & M_DLRX_RXPB_HDR_BEELINER_insig8) >> B_DLRX_RXPB_HDR_BEELINER_insig8))

#define DLRX_RXPB_HDR_BEELINER_insig8_set_indirect(base, offset, val)    \
	do {                                                              \
		(*(base + O_DLRX_RXPB_HDR_BEELINER_insig8 + offset)) &= (~(M_DLRX_RXPB_HDR_BEELINER_insig8));    \
		(*(base + O_DLRX_RXPB_HDR_BEELINER_insig8 + offset)) |= ((val << B_DLRX_RXPB_HDR_BEELINER_insig8) & M_DLRX_RXPB_HDR_BEELINER_insig8);    \
	} while (0)

#define DLRX_RXPB_HDR_BEELINER_insig8_set_direct(dword, val)    \
	do {                                                               \
		(dword) &= (~(M_DLRX_RXPB_HDR_BEELINER_insig8));    \
		(dword) |= ((val << B_DLRX_RXPB_HDR_BEELINER_insig8) & M_DLRX_RXPB_HDR_BEELINER_insig8);    \
	} while (0)

#define DLRX_RXPB_HDR_BEELINER_insig8_clear_indirect(base, offset)	((*(base + O_DLRX_RXPB_HDR_BEELINER_insig8 + offset)) &= (~(M_DLRX_RXPB_HDR_BEELINER_insig8)))

#define DLRX_RXPB_HDR_BEELINER_insig8_clear_direct(dword)	((dword) &= (~(M_DLRX_RXPB_HDR_BEELINER_insig8)))

#define O_DLRX_RXPB_HDR_BEELINER_insig9 7
#define B_DLRX_RXPB_HDR_BEELINER_insig9 0
#define W_DLRX_RXPB_HDR_BEELINER_insig9 32
#define M_DLRX_RXPB_HDR_BEELINER_insig9 0xffffffff

#define DLRX_RXPB_HDR_BEELINER_insig9_get_indirect(base, offset)	((((*(base + O_DLRX_RXPB_HDR_BEELINER_insig9 + offset)) & M_DLRX_RXPB_HDR_BEELINER_insig9) >> B_DLRX_RXPB_HDR_BEELINER_insig9))

#define DLRX_RXPB_HDR_BEELINER_insig9_get_direct(dword)	((((dword) & M_DLRX_RXPB_HDR_BEELINER_insig9) >> B_DLRX_RXPB_HDR_BEELINER_insig9))

#define DLRX_RXPB_HDR_BEELINER_insig9_set_indirect(base, offset, val)    \
	do {                                                              \
		(*(base + O_DLRX_RXPB_HDR_BEELINER_insig9 + offset)) &= (~(M_DLRX_RXPB_HDR_BEELINER_insig9));    \
		(*(base + O_DLRX_RXPB_HDR_BEELINER_insig9 + offset)) |= ((val << B_DLRX_RXPB_HDR_BEELINER_insig9) & M_DLRX_RXPB_HDR_BEELINER_insig9);    \
	} while (0)

#define DLRX_RXPB_HDR_BEELINER_insig9_set_direct(dword, val)    \
	do {                                                               \
		(dword) &= (~(M_DLRX_RXPB_HDR_BEELINER_insig9));    \
		(dword) |= ((val << B_DLRX_RXPB_HDR_BEELINER_insig9) & M_DLRX_RXPB_HDR_BEELINER_insig9);    \
	} while (0)

#define DLRX_RXPB_HDR_BEELINER_insig9_clear_indirect(base, offset)	((*(base + O_DLRX_RXPB_HDR_BEELINER_insig9 + offset)) &= (~(M_DLRX_RXPB_HDR_BEELINER_insig9)))

#define DLRX_RXPB_HDR_BEELINER_insig9_clear_direct(dword)	((dword) &= (~(M_DLRX_RXPB_HDR_BEELINER_insig9)))

#define O_DLRX_RXPB_HDR_BEELINER_insig10 8
#define B_DLRX_RXPB_HDR_BEELINER_insig10 0
#define W_DLRX_RXPB_HDR_BEELINER_insig10 32
#define M_DLRX_RXPB_HDR_BEELINER_insig10 0xffffffff

#define DLRX_RXPB_HDR_BEELINER_insig10_get_indirect(base, offset)	((((*(base + O_DLRX_RXPB_HDR_BEELINER_insig10 + offset)) & M_DLRX_RXPB_HDR_BEELINER_insig10) >> B_DLRX_RXPB_HDR_BEELINER_insig10))

#define DLRX_RXPB_HDR_BEELINER_insig10_get_direct(dword)	((((dword) & M_DLRX_RXPB_HDR_BEELINER_insig10) >> B_DLRX_RXPB_HDR_BEELINER_insig10))

#define DLRX_RXPB_HDR_BEELINER_insig10_set_indirect(base, offset, val)    \
	do {                                                              \
		(*(base + O_DLRX_RXPB_HDR_BEELINER_insig10 + offset)) &= (~(M_DLRX_RXPB_HDR_BEELINER_insig10));    \
		(*(base + O_DLRX_RXPB_HDR_BEELINER_insig10 + offset)) |= ((val << B_DLRX_RXPB_HDR_BEELINER_insig10) & M_DLRX_RXPB_HDR_BEELINER_insig10);    \
	} while (0)

#define DLRX_RXPB_HDR_BEELINER_insig10_set_direct(dword, val)    \
	do {                                                               \
		(dword) &= (~(M_DLRX_RXPB_HDR_BEELINER_insig10));    \
		(dword) |= ((val << B_DLRX_RXPB_HDR_BEELINER_insig10) & M_DLRX_RXPB_HDR_BEELINER_insig10);    \
	} while (0)

#define DLRX_RXPB_HDR_BEELINER_insig10_clear_indirect(base, offset)	((*(base + O_DLRX_RXPB_HDR_BEELINER_insig10 + offset)) &= (~(M_DLRX_RXPB_HDR_BEELINER_insig10)))

#define DLRX_RXPB_HDR_BEELINER_insig10_clear_direct(dword)	((dword) &= (~(M_DLRX_RXPB_HDR_BEELINER_insig10)))

#define O_DLRX_RXPB_HDR_BEELINER_insig11 9
#define B_DLRX_RXPB_HDR_BEELINER_insig11 0
#define W_DLRX_RXPB_HDR_BEELINER_insig11 32
#define M_DLRX_RXPB_HDR_BEELINER_insig11 0xffffffff

#define DLRX_RXPB_HDR_BEELINER_insig11_get_indirect(base, offset)	((((*(base + O_DLRX_RXPB_HDR_BEELINER_insig11 + offset)) & M_DLRX_RXPB_HDR_BEELINER_insig11) >> B_DLRX_RXPB_HDR_BEELINER_insig11))

#define DLRX_RXPB_HDR_BEELINER_insig11_get_direct(dword)	((((dword) & M_DLRX_RXPB_HDR_BEELINER_insig11) >> B_DLRX_RXPB_HDR_BEELINER_insig11))

#define DLRX_RXPB_HDR_BEELINER_insig11_set_indirect(base, offset, val)    \
	do {                                                              \
		(*(base + O_DLRX_RXPB_HDR_BEELINER_insig11 + offset)) &= (~(M_DLRX_RXPB_HDR_BEELINER_insig11));    \
		(*(base + O_DLRX_RXPB_HDR_BEELINER_insig11 + offset)) |= ((val << B_DLRX_RXPB_HDR_BEELINER_insig11) & M_DLRX_RXPB_HDR_BEELINER_insig11);    \
	} while (0)

#define DLRX_RXPB_HDR_BEELINER_insig11_set_direct(dword, val)    \
	do {                                                               \
		(dword) &= (~(M_DLRX_RXPB_HDR_BEELINER_insig11));    \
		(dword) |= ((val << B_DLRX_RXPB_HDR_BEELINER_insig11) & M_DLRX_RXPB_HDR_BEELINER_insig11);    \
	} while (0)

#define DLRX_RXPB_HDR_BEELINER_insig11_clear_indirect(base, offset)	((*(base + O_DLRX_RXPB_HDR_BEELINER_insig11 + offset)) &= (~(M_DLRX_RXPB_HDR_BEELINER_insig11)))

#define DLRX_RXPB_HDR_BEELINER_insig11_clear_direct(dword)	((dword) &= (~(M_DLRX_RXPB_HDR_BEELINER_insig11)))

#define O_DLRX_RXPB_HDR_BEELINER_insig12 10
#define B_DLRX_RXPB_HDR_BEELINER_insig12 0
#define W_DLRX_RXPB_HDR_BEELINER_insig12 16
#define M_DLRX_RXPB_HDR_BEELINER_insig12 0x0000ffff

#define DLRX_RXPB_HDR_BEELINER_insig12_get_indirect(base, offset)	((((*(base + O_DLRX_RXPB_HDR_BEELINER_insig12 + offset)) & M_DLRX_RXPB_HDR_BEELINER_insig12) >> B_DLRX_RXPB_HDR_BEELINER_insig12))

#define DLRX_RXPB_HDR_BEELINER_insig12_get_direct(dword)	((((dword) & M_DLRX_RXPB_HDR_BEELINER_insig12) >> B_DLRX_RXPB_HDR_BEELINER_insig12))

#define DLRX_RXPB_HDR_BEELINER_insig12_set_indirect(base, offset, val) \
	do {                                                              \
		(*(base + O_DLRX_RXPB_HDR_BEELINER_insig12 + offset)) &= (~(M_DLRX_RXPB_HDR_BEELINER_insig12));    \
		(*(base + O_DLRX_RXPB_HDR_BEELINER_insig12 + offset)) |= ((val << B_DLRX_RXPB_HDR_BEELINER_insig12) & M_DLRX_RXPB_HDR_BEELINER_insig12);    \
	} while (0)

#define DLRX_RXPB_HDR_BEELINER_insig12_set_direct(dword, val) \
	do {                                                               \
		(dword) &= (~(M_DLRX_RXPB_HDR_BEELINER_insig12));    \
		(dword) |= ((val << B_DLRX_RXPB_HDR_BEELINER_insig12) & M_DLRX_RXPB_HDR_BEELINER_insig12);    \
	} while (0)

#define DLRX_RXPB_HDR_BEELINER_insig12_clear_indirect(base, offset)	((*(base + O_DLRX_RXPB_HDR_BEELINER_insig12 + offset)) &= (~(M_DLRX_RXPB_HDR_BEELINER_insig12)))

#define DLRX_RXPB_HDR_BEELINER_insig12_clear_direct(dword)	((dword) &= (~(M_DLRX_RXPB_HDR_BEELINER_insig12)))

#define O_DLRX_RXPB_HDR_BEELINER_pn_63_48 10
#define B_DLRX_RXPB_HDR_BEELINER_pn_63_48 16
#define W_DLRX_RXPB_HDR_BEELINER_pn_63_48 16
#define M_DLRX_RXPB_HDR_BEELINER_pn_63_48 0xffff0000

#define DLRX_RXPB_HDR_BEELINER_pn_63_48_get_indirect(base, offset)	((((*(base + O_DLRX_RXPB_HDR_BEELINER_pn_63_48 + offset)) & M_DLRX_RXPB_HDR_BEELINER_pn_63_48) >> B_DLRX_RXPB_HDR_BEELINER_pn_63_48))

#define DLRX_RXPB_HDR_BEELINER_pn_63_48_get_direct(dword)	((((dword) & M_DLRX_RXPB_HDR_BEELINER_pn_63_48) >> B_DLRX_RXPB_HDR_BEELINER_pn_63_48))

#define DLRX_RXPB_HDR_BEELINER_pn_63_48_set_indirect(base, offset, val) \
	do {                                                              \
		(*(base + O_DLRX_RXPB_HDR_BEELINER_pn_63_48 + offset)) &= (~(M_DLRX_RXPB_HDR_BEELINER_pn_63_48));    \
		(*(base + O_DLRX_RXPB_HDR_BEELINER_pn_63_48 + offset)) |= ((val << B_DLRX_RXPB_HDR_BEELINER_pn_63_48) & M_DLRX_RXPB_HDR_BEELINER_pn_63_48);    \
	} while (0)

#define DLRX_RXPB_HDR_BEELINER_pn_63_48_set_direct(dword, val) \
	do {                                                               \
		(dword) &= (~(M_DLRX_RXPB_HDR_BEELINER_pn_63_48));    \
		(dword) |= ((val << B_DLRX_RXPB_HDR_BEELINER_pn_63_48) & M_DLRX_RXPB_HDR_BEELINER_pn_63_48);    \
	} while (0)

#define DLRX_RXPB_HDR_BEELINER_pn_63_48_clear_indirect(base, offset)	((*(base + O_DLRX_RXPB_HDR_BEELINER_pn_63_48 + offset)) &= (~(M_DLRX_RXPB_HDR_BEELINER_pn_63_48)))

#define DLRX_RXPB_HDR_BEELINER_pn_63_48_clear_direct(dword)	((dword) &= (~(M_DLRX_RXPB_HDR_BEELINER_pn_63_48)))

#define O_DLRX_RXPB_HDR_BEELINER_pn_95_64 11
#define B_DLRX_RXPB_HDR_BEELINER_pn_95_64 0
#define W_DLRX_RXPB_HDR_BEELINER_pn_95_64 32
#define M_DLRX_RXPB_HDR_BEELINER_pn_95_64 0xffffffff

#define DLRX_RXPB_HDR_BEELINER_pn_95_64_get_indirect(base, offset)	((((*(base + O_DLRX_RXPB_HDR_BEELINER_pn_95_64 + offset)) & M_DLRX_RXPB_HDR_BEELINER_pn_95_64) >> B_DLRX_RXPB_HDR_BEELINER_pn_95_64))

#define DLRX_RXPB_HDR_BEELINER_pn_95_64_get_direct(dword)	((((dword) & M_DLRX_RXPB_HDR_BEELINER_pn_95_64) >> B_DLRX_RXPB_HDR_BEELINER_pn_95_64))

#define DLRX_RXPB_HDR_BEELINER_pn_95_64_set_indirect(base, offset, val)    \
	do {                                                              \
		(*(base + O_DLRX_RXPB_HDR_BEELINER_pn_95_64 + offset)) &= (~(M_DLRX_RXPB_HDR_BEELINER_pn_95_64));    \
		(*(base + O_DLRX_RXPB_HDR_BEELINER_pn_95_64 + offset)) |= ((val << B_DLRX_RXPB_HDR_BEELINER_pn_95_64) & M_DLRX_RXPB_HDR_BEELINER_pn_95_64);    \
	} while (0)

#define DLRX_RXPB_HDR_BEELINER_pn_95_64_set_direct(dword, val)    \
	do {                                                               \
		(dword) &= (~(M_DLRX_RXPB_HDR_BEELINER_pn_95_64));    \
		(dword) |= ((val << B_DLRX_RXPB_HDR_BEELINER_pn_95_64) & M_DLRX_RXPB_HDR_BEELINER_pn_95_64);    \
	} while (0)

#define DLRX_RXPB_HDR_BEELINER_pn_95_64_clear_indirect(base, offset)	((*(base + O_DLRX_RXPB_HDR_BEELINER_pn_95_64 + offset)) &= (~(M_DLRX_RXPB_HDR_BEELINER_pn_95_64)))

#define DLRX_RXPB_HDR_BEELINER_pn_95_64_clear_direct(dword)	((dword) &= (~(M_DLRX_RXPB_HDR_BEELINER_pn_95_64)))

#define O_DLRX_RXPB_HDR_BEELINER_pn_127_96 12
#define B_DLRX_RXPB_HDR_BEELINER_pn_127_96 0
#define W_DLRX_RXPB_HDR_BEELINER_pn_127_96 32
#define M_DLRX_RXPB_HDR_BEELINER_pn_127_96 0xffffffff

#define DLRX_RXPB_HDR_BEELINER_pn_127_96_get_indirect(base, offset)	((((*(base + O_DLRX_RXPB_HDR_BEELINER_pn_127_96 + offset)) & M_DLRX_RXPB_HDR_BEELINER_pn_127_96) >> B_DLRX_RXPB_HDR_BEELINER_pn_127_96))

#define DLRX_RXPB_HDR_BEELINER_pn_127_96_get_direct(dword)	((((dword) & M_DLRX_RXPB_HDR_BEELINER_pn_127_96) >> B_DLRX_RXPB_HDR_BEELINER_pn_127_96))

#define DLRX_RXPB_HDR_BEELINER_pn_127_96_set_indirect(base, offset, val)    \
	do {                                                              \
		(*(base + O_DLRX_RXPB_HDR_BEELINER_pn_127_96 + offset)) &= (~(M_DLRX_RXPB_HDR_BEELINER_pn_127_96));    \
		(*(base + O_DLRX_RXPB_HDR_BEELINER_pn_127_96 + offset)) |= ((val << B_DLRX_RXPB_HDR_BEELINER_pn_127_96) & M_DLRX_RXPB_HDR_BEELINER_pn_127_96);    \
	} while (0)

#define DLRX_RXPB_HDR_BEELINER_pn_127_96_set_direct(dword, val)    \
	do {                                                               \
		(dword) &= (~(M_DLRX_RXPB_HDR_BEELINER_pn_127_96));    \
		(dword) |= ((val << B_DLRX_RXPB_HDR_BEELINER_pn_127_96) & M_DLRX_RXPB_HDR_BEELINER_pn_127_96);    \
	} while (0)

#define DLRX_RXPB_HDR_BEELINER_pn_127_96_clear_indirect(base, offset)	((*(base + O_DLRX_RXPB_HDR_BEELINER_pn_127_96 + offset)) &= (~(M_DLRX_RXPB_HDR_BEELINER_pn_127_96)))

#define DLRX_RXPB_HDR_BEELINER_pn_127_96_clear_direct(dword)	((dword) &= (~(M_DLRX_RXPB_HDR_BEELINER_pn_127_96)))

#define O_DLRX_RXPB_HDR_BEELINER_insig13 13
#define B_DLRX_RXPB_HDR_BEELINER_insig13 0
#define W_DLRX_RXPB_HDR_BEELINER_insig13 14
#define M_DLRX_RXPB_HDR_BEELINER_insig13 0x00003fff

#define DLRX_RXPB_HDR_BEELINER_insig13_get_indirect(base, offset)	((((*(base + O_DLRX_RXPB_HDR_BEELINER_insig13 + offset)) & M_DLRX_RXPB_HDR_BEELINER_insig13) >> B_DLRX_RXPB_HDR_BEELINER_insig13))

#define DLRX_RXPB_HDR_BEELINER_insig13_get_direct(dword)	((((dword) & M_DLRX_RXPB_HDR_BEELINER_insig13) >> B_DLRX_RXPB_HDR_BEELINER_insig13))

#define DLRX_RXPB_HDR_BEELINER_insig13_set_indirect(base, offset, val) \
	do {                                                              \
		(*(base + O_DLRX_RXPB_HDR_BEELINER_insig13 + offset)) &= (~(M_DLRX_RXPB_HDR_BEELINER_insig13));    \
		(*(base + O_DLRX_RXPB_HDR_BEELINER_insig13 + offset)) |= ((val << B_DLRX_RXPB_HDR_BEELINER_insig13) & M_DLRX_RXPB_HDR_BEELINER_insig13);    \
	} while (0)

#define DLRX_RXPB_HDR_BEELINER_insig13_set_direct(dword, val) \
	do {                                                               \
		(dword) &= (~(M_DLRX_RXPB_HDR_BEELINER_insig13));    \
		(dword) |= ((val << B_DLRX_RXPB_HDR_BEELINER_insig13) & M_DLRX_RXPB_HDR_BEELINER_insig13);    \
	} while (0)

#define DLRX_RXPB_HDR_BEELINER_insig13_clear_indirect(base, offset)	((*(base + O_DLRX_RXPB_HDR_BEELINER_insig13 + offset)) &= (~(M_DLRX_RXPB_HDR_BEELINER_insig13)))

#define DLRX_RXPB_HDR_BEELINER_insig13_clear_direct(dword)	((dword) &= (~(M_DLRX_RXPB_HDR_BEELINER_insig13)))

#define O_DLRX_RXPB_HDR_BEELINER_first_msdu 13
#define B_DLRX_RXPB_HDR_BEELINER_first_msdu 14
#define W_DLRX_RXPB_HDR_BEELINER_first_msdu 1
#define M_DLRX_RXPB_HDR_BEELINER_first_msdu 0x00004000

#define DLRX_RXPB_HDR_BEELINER_first_msdu_get_indirect(base, offset)	((((*(base + O_DLRX_RXPB_HDR_BEELINER_first_msdu + offset)) & M_DLRX_RXPB_HDR_BEELINER_first_msdu) >> B_DLRX_RXPB_HDR_BEELINER_first_msdu))

#define DLRX_RXPB_HDR_BEELINER_first_msdu_get_direct(dword)	((((dword) & M_DLRX_RXPB_HDR_BEELINER_first_msdu) >> B_DLRX_RXPB_HDR_BEELINER_first_msdu))

#define DLRX_RXPB_HDR_BEELINER_first_msdu_set_indirect(base, offset, val) \
	do {                                                              \
		(*(base + O_DLRX_RXPB_HDR_BEELINER_first_msdu + offset)) &= (~(M_DLRX_RXPB_HDR_BEELINER_first_msdu));    \
		(*(base + O_DLRX_RXPB_HDR_BEELINER_first_msdu + offset)) |= ((val << B_DLRX_RXPB_HDR_BEELINER_first_msdu) & M_DLRX_RXPB_HDR_BEELINER_first_msdu);    \
	} while (0)

#define DLRX_RXPB_HDR_BEELINER_first_msdu_set_direct(dword, val) \
	do {                                                               \
		(dword) &= (~(M_DLRX_RXPB_HDR_BEELINER_first_msdu));    \
		(dword) |= ((val << B_DLRX_RXPB_HDR_BEELINER_first_msdu) & M_DLRX_RXPB_HDR_BEELINER_first_msdu);    \
	} while (0)

#define DLRX_RXPB_HDR_BEELINER_first_msdu_clear_indirect(base, offset)	((*(base + O_DLRX_RXPB_HDR_BEELINER_first_msdu + offset)) &= (~(M_DLRX_RXPB_HDR_BEELINER_first_msdu)))

#define DLRX_RXPB_HDR_BEELINER_first_msdu_clear_direct(dword)	((dword) &= (~(M_DLRX_RXPB_HDR_BEELINER_first_msdu)))

#define O_DLRX_RXPB_HDR_BEELINER_last_msdu 13
#define B_DLRX_RXPB_HDR_BEELINER_last_msdu 15
#define W_DLRX_RXPB_HDR_BEELINER_last_msdu 1
#define M_DLRX_RXPB_HDR_BEELINER_last_msdu 0x00008000

#define DLRX_RXPB_HDR_BEELINER_last_msdu_get_indirect(base, offset)	((((*(base + O_DLRX_RXPB_HDR_BEELINER_last_msdu + offset)) & M_DLRX_RXPB_HDR_BEELINER_last_msdu) >> B_DLRX_RXPB_HDR_BEELINER_last_msdu))

#define DLRX_RXPB_HDR_BEELINER_last_msdu_get_direct(dword)	((((dword) & M_DLRX_RXPB_HDR_BEELINER_last_msdu) >> B_DLRX_RXPB_HDR_BEELINER_last_msdu))

#define DLRX_RXPB_HDR_BEELINER_last_msdu_set_indirect(base, offset, val) \
	do {                                                              \
		(*(base + O_DLRX_RXPB_HDR_BEELINER_last_msdu + offset)) &= (~(M_DLRX_RXPB_HDR_BEELINER_last_msdu));    \
		(*(base + O_DLRX_RXPB_HDR_BEELINER_last_msdu + offset)) |= ((val << B_DLRX_RXPB_HDR_BEELINER_last_msdu) & M_DLRX_RXPB_HDR_BEELINER_last_msdu);    \
	} while (0)

#define DLRX_RXPB_HDR_BEELINER_last_msdu_set_direct(dword, val) \
	do {                                                               \
		(dword) &= (~(M_DLRX_RXPB_HDR_BEELINER_last_msdu));    \
		(dword) |= ((val << B_DLRX_RXPB_HDR_BEELINER_last_msdu) & M_DLRX_RXPB_HDR_BEELINER_last_msdu);    \
	} while (0)

#define DLRX_RXPB_HDR_BEELINER_last_msdu_clear_indirect(base, offset)	((*(base + O_DLRX_RXPB_HDR_BEELINER_last_msdu + offset)) &= (~(M_DLRX_RXPB_HDR_BEELINER_last_msdu)))

#define DLRX_RXPB_HDR_BEELINER_last_msdu_clear_direct(dword)	((dword) &= (~(M_DLRX_RXPB_HDR_BEELINER_last_msdu)))

#define O_DLRX_RXPB_HDR_BEELINER_insig14 13
#define B_DLRX_RXPB_HDR_BEELINER_insig14 16
#define W_DLRX_RXPB_HDR_BEELINER_insig14 16
#define M_DLRX_RXPB_HDR_BEELINER_insig14 0xffff0000

#define DLRX_RXPB_HDR_BEELINER_insig14_get_indirect(base, offset)	((((*(base + O_DLRX_RXPB_HDR_BEELINER_insig14 + offset)) & M_DLRX_RXPB_HDR_BEELINER_insig14) >> B_DLRX_RXPB_HDR_BEELINER_insig14))

#define DLRX_RXPB_HDR_BEELINER_insig14_get_direct(dword)	((((dword) & M_DLRX_RXPB_HDR_BEELINER_insig14) >> B_DLRX_RXPB_HDR_BEELINER_insig14))

#define DLRX_RXPB_HDR_BEELINER_insig14_set_indirect(base, offset, val) \
	do {                                                              \
		(*(base + O_DLRX_RXPB_HDR_BEELINER_insig14 + offset)) &= (~(M_DLRX_RXPB_HDR_BEELINER_insig14));    \
		(*(base + O_DLRX_RXPB_HDR_BEELINER_insig14 + offset)) |= ((val << B_DLRX_RXPB_HDR_BEELINER_insig14) & M_DLRX_RXPB_HDR_BEELINER_insig14);    \
	} while (0)

#define DLRX_RXPB_HDR_BEELINER_insig14_set_direct(dword, val) \
	do {                                                               \
		(dword) &= (~(M_DLRX_RXPB_HDR_BEELINER_insig14));    \
		(dword) |= ((val << B_DLRX_RXPB_HDR_BEELINER_insig14) & M_DLRX_RXPB_HDR_BEELINER_insig14);    \
	} while (0)

#define DLRX_RXPB_HDR_BEELINER_insig14_clear_indirect(base, offset)	((*(base + O_DLRX_RXPB_HDR_BEELINER_insig14 + offset)) &= (~(M_DLRX_RXPB_HDR_BEELINER_insig14)))

#define DLRX_RXPB_HDR_BEELINER_insig14_clear_direct(dword)	((dword) &= (~(M_DLRX_RXPB_HDR_BEELINER_insig14)))

#define O_DLRX_RXPB_HDR_BEELINER_insig15 14
#define B_DLRX_RXPB_HDR_BEELINER_insig15 0
#define W_DLRX_RXPB_HDR_BEELINER_insig15 32
#define M_DLRX_RXPB_HDR_BEELINER_insig15 0xffffffff

#define DLRX_RXPB_HDR_BEELINER_insig15_get_indirect(base, offset)	((((*(base + O_DLRX_RXPB_HDR_BEELINER_insig15 + offset)) & M_DLRX_RXPB_HDR_BEELINER_insig15) >> B_DLRX_RXPB_HDR_BEELINER_insig15))

#define DLRX_RXPB_HDR_BEELINER_insig15_get_direct(dword)	((((dword) & M_DLRX_RXPB_HDR_BEELINER_insig15) >> B_DLRX_RXPB_HDR_BEELINER_insig15))

#define DLRX_RXPB_HDR_BEELINER_insig15_set_indirect(base, offset, val)    \
	do {                                                              \
		(*(base + O_DLRX_RXPB_HDR_BEELINER_insig15 + offset)) &= (~(M_DLRX_RXPB_HDR_BEELINER_insig15));    \
		(*(base + O_DLRX_RXPB_HDR_BEELINER_insig15 + offset)) |= ((val << B_DLRX_RXPB_HDR_BEELINER_insig15) & M_DLRX_RXPB_HDR_BEELINER_insig15);    \
	} while (0)

#define DLRX_RXPB_HDR_BEELINER_insig15_set_direct(dword, val)    \
	do {                                                               \
		(dword) &= (~(M_DLRX_RXPB_HDR_BEELINER_insig15));    \
		(dword) |= ((val << B_DLRX_RXPB_HDR_BEELINER_insig15) & M_DLRX_RXPB_HDR_BEELINER_insig15);    \
	} while (0)

#define DLRX_RXPB_HDR_BEELINER_insig15_clear_indirect(base, offset)	((*(base + O_DLRX_RXPB_HDR_BEELINER_insig15 + offset)) &= (~(M_DLRX_RXPB_HDR_BEELINER_insig15)))

#define DLRX_RXPB_HDR_BEELINER_insig15_clear_direct(dword)	((dword) &= (~(M_DLRX_RXPB_HDR_BEELINER_insig15)))

#define O_DLRX_RXPB_HDR_BEELINER_insig16 15
#define B_DLRX_RXPB_HDR_BEELINER_insig16 0
#define W_DLRX_RXPB_HDR_BEELINER_insig16 32
#define M_DLRX_RXPB_HDR_BEELINER_insig16 0xffffffff

#define DLRX_RXPB_HDR_BEELINER_insig16_get_indirect(base, offset)	((((*(base + O_DLRX_RXPB_HDR_BEELINER_insig16 + offset)) & M_DLRX_RXPB_HDR_BEELINER_insig16) >> B_DLRX_RXPB_HDR_BEELINER_insig16))

#define DLRX_RXPB_HDR_BEELINER_insig16_get_direct(dword)	((((dword) & M_DLRX_RXPB_HDR_BEELINER_insig16) >> B_DLRX_RXPB_HDR_BEELINER_insig16))

#define DLRX_RXPB_HDR_BEELINER_insig16_set_indirect(base, offset, val)    \
	do {                                                              \
		(*(base + O_DLRX_RXPB_HDR_BEELINER_insig16 + offset)) &= (~(M_DLRX_RXPB_HDR_BEELINER_insig16));    \
		(*(base + O_DLRX_RXPB_HDR_BEELINER_insig16 + offset)) |= ((val << B_DLRX_RXPB_HDR_BEELINER_insig16) & M_DLRX_RXPB_HDR_BEELINER_insig16);    \
	} while (0)

#define DLRX_RXPB_HDR_BEELINER_insig16_set_direct(dword, val)    \
	do {                                                               \
		(dword) &= (~(M_DLRX_RXPB_HDR_BEELINER_insig16));    \
		(dword) |= ((val << B_DLRX_RXPB_HDR_BEELINER_insig16) & M_DLRX_RXPB_HDR_BEELINER_insig16);    \
	} while (0)

#define DLRX_RXPB_HDR_BEELINER_insig16_clear_indirect(base, offset)	((*(base + O_DLRX_RXPB_HDR_BEELINER_insig16 + offset)) &= (~(M_DLRX_RXPB_HDR_BEELINER_insig16)))

#define DLRX_RXPB_HDR_BEELINER_insig16_clear_direct(dword)	((dword) &= (~(M_DLRX_RXPB_HDR_BEELINER_insig16)))

#define O_DLRX_RXPB_HDR_BEELINER_insig17 16
#define B_DLRX_RXPB_HDR_BEELINER_insig17 0
#define W_DLRX_RXPB_HDR_BEELINER_insig17 32
#define M_DLRX_RXPB_HDR_BEELINER_insig17 0xffffffff

#define DLRX_RXPB_HDR_BEELINER_insig17_get_indirect(base, offset)	((((*(base + O_DLRX_RXPB_HDR_BEELINER_insig17 + offset)) & M_DLRX_RXPB_HDR_BEELINER_insig17) >> B_DLRX_RXPB_HDR_BEELINER_insig17))

#define DLRX_RXPB_HDR_BEELINER_insig17_get_direct(dword)	((((dword) & M_DLRX_RXPB_HDR_BEELINER_insig17) >> B_DLRX_RXPB_HDR_BEELINER_insig17))

#define DLRX_RXPB_HDR_BEELINER_insig17_set_indirect(base, offset, val)    \
	do {                                                              \
		(*(base + O_DLRX_RXPB_HDR_BEELINER_insig17 + offset)) &= (~(M_DLRX_RXPB_HDR_BEELINER_insig17));    \
		(*(base + O_DLRX_RXPB_HDR_BEELINER_insig17 + offset)) |= ((val << B_DLRX_RXPB_HDR_BEELINER_insig17) & M_DLRX_RXPB_HDR_BEELINER_insig17);    \
	} while (0)

#define DLRX_RXPB_HDR_BEELINER_insig17_set_direct(dword, val)    \
	do {                                                               \
		(dword) &= (~(M_DLRX_RXPB_HDR_BEELINER_insig17));    \
		(dword) |= ((val << B_DLRX_RXPB_HDR_BEELINER_insig17) & M_DLRX_RXPB_HDR_BEELINER_insig17);    \
	} while (0)

#define DLRX_RXPB_HDR_BEELINER_insig17_clear_indirect(base, offset)	((*(base + O_DLRX_RXPB_HDR_BEELINER_insig17 + offset)) &= (~(M_DLRX_RXPB_HDR_BEELINER_insig17)))

#define DLRX_RXPB_HDR_BEELINER_insig17_clear_direct(dword)	((dword) &= (~(M_DLRX_RXPB_HDR_BEELINER_insig17)))

#define O_DLRX_RXPB_HDR_BEELINER_insig18 17
#define B_DLRX_RXPB_HDR_BEELINER_insig18 0
#define W_DLRX_RXPB_HDR_BEELINER_insig18 10
#define M_DLRX_RXPB_HDR_BEELINER_insig18 0x000003ff

#define DLRX_RXPB_HDR_BEELINER_insig18_get_indirect(base, offset)	((((*(base + O_DLRX_RXPB_HDR_BEELINER_insig18 + offset)) & M_DLRX_RXPB_HDR_BEELINER_insig18) >> B_DLRX_RXPB_HDR_BEELINER_insig18))

#define DLRX_RXPB_HDR_BEELINER_insig18_get_direct(dword)	((((dword) & M_DLRX_RXPB_HDR_BEELINER_insig18) >> B_DLRX_RXPB_HDR_BEELINER_insig18))

#define DLRX_RXPB_HDR_BEELINER_insig18_set_indirect(base, offset, val) \
	do {                                                              \
		(*(base + O_DLRX_RXPB_HDR_BEELINER_insig18 + offset)) &= (~(M_DLRX_RXPB_HDR_BEELINER_insig18));    \
		(*(base + O_DLRX_RXPB_HDR_BEELINER_insig18 + offset)) |= ((val << B_DLRX_RXPB_HDR_BEELINER_insig18) & M_DLRX_RXPB_HDR_BEELINER_insig18);    \
	} while (0)

#define DLRX_RXPB_HDR_BEELINER_insig18_set_direct(dword, val) \
	do {                                                               \
		(dword) &= (~(M_DLRX_RXPB_HDR_BEELINER_insig18));    \
		(dword) |= ((val << B_DLRX_RXPB_HDR_BEELINER_insig18) & M_DLRX_RXPB_HDR_BEELINER_insig18);    \
	} while (0)

#define DLRX_RXPB_HDR_BEELINER_insig18_clear_indirect(base, offset)	((*(base + O_DLRX_RXPB_HDR_BEELINER_insig18 + offset)) &= (~(M_DLRX_RXPB_HDR_BEELINER_insig18)))

#define DLRX_RXPB_HDR_BEELINER_insig18_clear_direct(dword)	((dword) &= (~(M_DLRX_RXPB_HDR_BEELINER_insig18)))

#define O_DLRX_RXPB_HDR_BEELINER_l3_header_padding 17
#define B_DLRX_RXPB_HDR_BEELINER_l3_header_padding 10
#define W_DLRX_RXPB_HDR_BEELINER_l3_header_padding 3
#define M_DLRX_RXPB_HDR_BEELINER_l3_header_padding 0x00001c00

#define DLRX_RXPB_HDR_BEELINER_l3_header_padding_get_indirect(base, offset)	((((*(base + O_DLRX_RXPB_HDR_BEELINER_l3_header_padding + offset)) & M_DLRX_RXPB_HDR_BEELINER_l3_header_padding) >> B_DLRX_RXPB_HDR_BEELINER_l3_header_padding))

#define DLRX_RXPB_HDR_BEELINER_l3_header_padding_get_direct(dword)	((((dword) & M_DLRX_RXPB_HDR_BEELINER_l3_header_padding) >> B_DLRX_RXPB_HDR_BEELINER_l3_header_padding))

#define DLRX_RXPB_HDR_BEELINER_l3_header_padding_set_indirect(base, offset, val) \
	do {                                                              \
		(*(base + O_DLRX_RXPB_HDR_BEELINER_l3_header_padding + offset)) &= (~(M_DLRX_RXPB_HDR_BEELINER_l3_header_padding));    \
		(*(base + O_DLRX_RXPB_HDR_BEELINER_l3_header_padding + offset)) |= ((val << B_DLRX_RXPB_HDR_BEELINER_l3_header_padding) & M_DLRX_RXPB_HDR_BEELINER_l3_header_padding);    \
	} while (0)

#define DLRX_RXPB_HDR_BEELINER_l3_header_padding_set_direct(dword, val) \
	do {                                                               \
		(dword) &= (~(M_DLRX_RXPB_HDR_BEELINER_l3_header_padding));    \
		(dword) |= ((val << B_DLRX_RXPB_HDR_BEELINER_l3_header_padding) & M_DLRX_RXPB_HDR_BEELINER_l3_header_padding);    \
	} while (0)

#define DLRX_RXPB_HDR_BEELINER_l3_header_padding_clear_indirect(base, offset)	((*(base + O_DLRX_RXPB_HDR_BEELINER_l3_header_padding + offset)) &= (~(M_DLRX_RXPB_HDR_BEELINER_l3_header_padding)))

#define DLRX_RXPB_HDR_BEELINER_l3_header_padding_clear_direct(dword)	((dword) &= (~(M_DLRX_RXPB_HDR_BEELINER_l3_header_padding)))

#define O_DLRX_RXPB_HDR_BEELINER_insig19 17
#define B_DLRX_RXPB_HDR_BEELINER_insig19 13
#define W_DLRX_RXPB_HDR_BEELINER_insig19 19
#define M_DLRX_RXPB_HDR_BEELINER_insig19 0xffffe000

#define DLRX_RXPB_HDR_BEELINER_insig19_get_indirect(base, offset)	((((*(base + O_DLRX_RXPB_HDR_BEELINER_insig19 + offset)) & M_DLRX_RXPB_HDR_BEELINER_insig19) >> B_DLRX_RXPB_HDR_BEELINER_insig19))

#define DLRX_RXPB_HDR_BEELINER_insig19_get_direct(dword)	((((dword) & M_DLRX_RXPB_HDR_BEELINER_insig19) >> B_DLRX_RXPB_HDR_BEELINER_insig19))

#define DLRX_RXPB_HDR_BEELINER_insig19_set_indirect(base, offset, val) \
	do {                                                              \
		(*(base + O_DLRX_RXPB_HDR_BEELINER_insig19 + offset)) &= (~(M_DLRX_RXPB_HDR_BEELINER_insig19));    \
		(*(base + O_DLRX_RXPB_HDR_BEELINER_insig19 + offset)) |= ((val << B_DLRX_RXPB_HDR_BEELINER_insig19) & M_DLRX_RXPB_HDR_BEELINER_insig19);    \
	} while (0)

#define DLRX_RXPB_HDR_BEELINER_insig19_set_direct(dword, val) \
	do {                                                               \
		(dword) &= (~(M_DLRX_RXPB_HDR_BEELINER_insig19));    \
		(dword) |= ((val << B_DLRX_RXPB_HDR_BEELINER_insig19) & M_DLRX_RXPB_HDR_BEELINER_insig19);    \
	} while (0)

#define DLRX_RXPB_HDR_BEELINER_insig19_clear_indirect(base, offset)	((*(base + O_DLRX_RXPB_HDR_BEELINER_insig19 + offset)) &= (~(M_DLRX_RXPB_HDR_BEELINER_insig19)))

#define DLRX_RXPB_HDR_BEELINER_insig19_clear_direct(dword)	((dword) &= (~(M_DLRX_RXPB_HDR_BEELINER_insig19)))

#define O_DLRX_RXPB_HDR_BEELINER_insig20 18
#define B_DLRX_RXPB_HDR_BEELINER_insig20 0
#define W_DLRX_RXPB_HDR_BEELINER_insig20 32
#define M_DLRX_RXPB_HDR_BEELINER_insig20 0xffffffff

#define DLRX_RXPB_HDR_BEELINER_insig20_get_indirect(base, offset)	((((*(base + O_DLRX_RXPB_HDR_BEELINER_insig20 + offset)) & M_DLRX_RXPB_HDR_BEELINER_insig20) >> B_DLRX_RXPB_HDR_BEELINER_insig20))

#define DLRX_RXPB_HDR_BEELINER_insig20_get_direct(dword)	((((dword) & M_DLRX_RXPB_HDR_BEELINER_insig20) >> B_DLRX_RXPB_HDR_BEELINER_insig20))

#define DLRX_RXPB_HDR_BEELINER_insig20_set_indirect(base, offset, val)    \
	do {                                                              \
		(*(base + O_DLRX_RXPB_HDR_BEELINER_insig20 + offset)) &= (~(M_DLRX_RXPB_HDR_BEELINER_insig20));    \
		(*(base + O_DLRX_RXPB_HDR_BEELINER_insig20 + offset)) |= ((val << B_DLRX_RXPB_HDR_BEELINER_insig20) & M_DLRX_RXPB_HDR_BEELINER_insig20);    \
	} while (0)

#define DLRX_RXPB_HDR_BEELINER_insig20_set_direct(dword, val)    \
	do {                                                               \
		(dword) &= (~(M_DLRX_RXPB_HDR_BEELINER_insig20));    \
		(dword) |= ((val << B_DLRX_RXPB_HDR_BEELINER_insig20) & M_DLRX_RXPB_HDR_BEELINER_insig20);    \
	} while (0)

#define DLRX_RXPB_HDR_BEELINER_insig20_clear_indirect(base, offset)	((*(base + O_DLRX_RXPB_HDR_BEELINER_insig20 + offset)) &= (~(M_DLRX_RXPB_HDR_BEELINER_insig20)))

#define DLRX_RXPB_HDR_BEELINER_insig20_clear_direct(dword)	((dword) &= (~(M_DLRX_RXPB_HDR_BEELINER_insig20)))

#define O_DLRX_RXPB_PMAC_HDR_fwd 0
#define B_DLRX_RXPB_PMAC_HDR_fwd 0
#define W_DLRX_RXPB_PMAC_HDR_fwd 1
#define M_DLRX_RXPB_PMAC_HDR_fwd 0x00000001

#define DLRX_RXPB_PMAC_HDR_fwd_get_indirect(base, offset)	((((*(base + O_DLRX_RXPB_PMAC_HDR_fwd + offset)) & M_DLRX_RXPB_PMAC_HDR_fwd) >> B_DLRX_RXPB_PMAC_HDR_fwd))

#define DLRX_RXPB_PMAC_HDR_fwd_get_direct(dword)	((((dword) & M_DLRX_RXPB_PMAC_HDR_fwd) >> B_DLRX_RXPB_PMAC_HDR_fwd))

#define DLRX_RXPB_PMAC_HDR_fwd_set_indirect(base, offset, val) \
	do {                                                              \
		(*(base + O_DLRX_RXPB_PMAC_HDR_fwd + offset)) &= (~(M_DLRX_RXPB_PMAC_HDR_fwd));    \
		(*(base + O_DLRX_RXPB_PMAC_HDR_fwd + offset)) |= ((val << B_DLRX_RXPB_PMAC_HDR_fwd) & M_DLRX_RXPB_PMAC_HDR_fwd);    \
	} while (0)

#define DLRX_RXPB_PMAC_HDR_fwd_set_direct(dword, val) \
	do {                                                               \
		(dword) &= (~(M_DLRX_RXPB_PMAC_HDR_fwd));    \
		(dword) |= ((val << B_DLRX_RXPB_PMAC_HDR_fwd) & M_DLRX_RXPB_PMAC_HDR_fwd);    \
	} while (0)

#define DLRX_RXPB_PMAC_HDR_fwd_clear_indirect(base, offset)	((*(base + O_DLRX_RXPB_PMAC_HDR_fwd + offset)) &= (~(M_DLRX_RXPB_PMAC_HDR_fwd)))

#define DLRX_RXPB_PMAC_HDR_fwd_clear_direct(dword)	((dword) &= (~(M_DLRX_RXPB_PMAC_HDR_fwd)))

#define O_DLRX_RXPB_PMAC_HDR_discard 0
#define B_DLRX_RXPB_PMAC_HDR_discard 1
#define W_DLRX_RXPB_PMAC_HDR_discard 1
#define M_DLRX_RXPB_PMAC_HDR_discard 0x00000002

#define DLRX_RXPB_PMAC_HDR_discard_get_indirect(base, offset)	((((*(base + O_DLRX_RXPB_PMAC_HDR_discard + offset)) & M_DLRX_RXPB_PMAC_HDR_discard) >> B_DLRX_RXPB_PMAC_HDR_discard))

#define DLRX_RXPB_PMAC_HDR_discard_get_direct(dword)	((((dword) & M_DLRX_RXPB_PMAC_HDR_discard) >> B_DLRX_RXPB_PMAC_HDR_discard))

#define DLRX_RXPB_PMAC_HDR_discard_set_indirect(base, offset, val) \
	do {                                                              \
		(*(base + O_DLRX_RXPB_PMAC_HDR_discard + offset)) &= (~(M_DLRX_RXPB_PMAC_HDR_discard));    \
		(*(base + O_DLRX_RXPB_PMAC_HDR_discard + offset)) |= ((val << B_DLRX_RXPB_PMAC_HDR_discard) & M_DLRX_RXPB_PMAC_HDR_discard);    \
	} while (0)

#define DLRX_RXPB_PMAC_HDR_discard_set_direct(dword, val) \
	do {                                                               \
		(dword) &= (~(M_DLRX_RXPB_PMAC_HDR_discard));    \
		(dword) |= ((val << B_DLRX_RXPB_PMAC_HDR_discard) & M_DLRX_RXPB_PMAC_HDR_discard);    \
	} while (0)

#define DLRX_RXPB_PMAC_HDR_discard_clear_indirect(base, offset)	((*(base + O_DLRX_RXPB_PMAC_HDR_discard + offset)) &= (~(M_DLRX_RXPB_PMAC_HDR_discard)))

#define DLRX_RXPB_PMAC_HDR_discard_clear_direct(dword)	((dword) &= (~(M_DLRX_RXPB_PMAC_HDR_discard)))

#define O_DLRX_RXPB_PMAC_HDR_rsvd0 0
#define B_DLRX_RXPB_PMAC_HDR_rsvd0 2
#define W_DLRX_RXPB_PMAC_HDR_rsvd0 6
#define M_DLRX_RXPB_PMAC_HDR_rsvd0 0x000000fc

#define DLRX_RXPB_PMAC_HDR_rsvd0_get_indirect(base, offset)	((((*(base + O_DLRX_RXPB_PMAC_HDR_rsvd0 + offset)) & M_DLRX_RXPB_PMAC_HDR_rsvd0) >> B_DLRX_RXPB_PMAC_HDR_rsvd0))

#define DLRX_RXPB_PMAC_HDR_rsvd0_get_direct(dword)	((((dword) & M_DLRX_RXPB_PMAC_HDR_rsvd0) >> B_DLRX_RXPB_PMAC_HDR_rsvd0))

#define DLRX_RXPB_PMAC_HDR_rsvd0_set_indirect(base, offset, val) \
	do {                                                              \
		(*(base + O_DLRX_RXPB_PMAC_HDR_rsvd0 + offset)) &= (~(M_DLRX_RXPB_PMAC_HDR_rsvd0));    \
		(*(base + O_DLRX_RXPB_PMAC_HDR_rsvd0 + offset)) |= ((val << B_DLRX_RXPB_PMAC_HDR_rsvd0) & M_DLRX_RXPB_PMAC_HDR_rsvd0);    \
	} while (0)

#define DLRX_RXPB_PMAC_HDR_rsvd0_set_direct(dword, val) \
	do {                                                               \
		(dword) &= (~(M_DLRX_RXPB_PMAC_HDR_rsvd0));    \
		(dword) |= ((val << B_DLRX_RXPB_PMAC_HDR_rsvd0) & M_DLRX_RXPB_PMAC_HDR_rsvd0);    \
	} while (0)

#define DLRX_RXPB_PMAC_HDR_rsvd0_clear_indirect(base, offset)	((*(base + O_DLRX_RXPB_PMAC_HDR_rsvd0 + offset)) &= (~(M_DLRX_RXPB_PMAC_HDR_rsvd0)))

#define DLRX_RXPB_PMAC_HDR_rsvd0_clear_direct(dword)	((dword) &= (~(M_DLRX_RXPB_PMAC_HDR_rsvd0)))

#define O_DLRX_RXPB_PMAC_HDR_vap 0
#define B_DLRX_RXPB_PMAC_HDR_vap 8
#define W_DLRX_RXPB_PMAC_HDR_vap 4
#define M_DLRX_RXPB_PMAC_HDR_vap 0x00000f00

#define DLRX_RXPB_PMAC_HDR_vap_get_indirect(base, offset)	((((*(base + O_DLRX_RXPB_PMAC_HDR_vap + offset)) & M_DLRX_RXPB_PMAC_HDR_vap) >> B_DLRX_RXPB_PMAC_HDR_vap))

#define DLRX_RXPB_PMAC_HDR_vap_get_direct(dword)	((((dword) & M_DLRX_RXPB_PMAC_HDR_vap) >> B_DLRX_RXPB_PMAC_HDR_vap))

#define DLRX_RXPB_PMAC_HDR_vap_set_indirect(base, offset, val) \
	do {                                                              \
		(*(base + O_DLRX_RXPB_PMAC_HDR_vap + offset)) &= (~(M_DLRX_RXPB_PMAC_HDR_vap));    \
		(*(base + O_DLRX_RXPB_PMAC_HDR_vap + offset)) |= ((val << B_DLRX_RXPB_PMAC_HDR_vap) & M_DLRX_RXPB_PMAC_HDR_vap);    \
	} while (0)

#define DLRX_RXPB_PMAC_HDR_vap_set_direct(dword, val) \
	do {                                                               \
		(dword) &= (~(M_DLRX_RXPB_PMAC_HDR_vap));    \
		(dword) |= ((val << B_DLRX_RXPB_PMAC_HDR_vap) & M_DLRX_RXPB_PMAC_HDR_vap);    \
	} while (0)

#define DLRX_RXPB_PMAC_HDR_vap_clear_indirect(base, offset)	((*(base + O_DLRX_RXPB_PMAC_HDR_vap + offset)) &= (~(M_DLRX_RXPB_PMAC_HDR_vap)))

#define DLRX_RXPB_PMAC_HDR_vap_clear_direct(dword)	((dword) &= (~(M_DLRX_RXPB_PMAC_HDR_vap)))

#define O_DLRX_RXPB_PMAC_HDR_fwd1 0
#define B_DLRX_RXPB_PMAC_HDR_fwd1 12
#define W_DLRX_RXPB_PMAC_HDR_fwd1 1
#define M_DLRX_RXPB_PMAC_HDR_fwd1 0x00001000

#define DLRX_RXPB_PMAC_HDR_fwd1_get_indirect(base, offset)	((((*(base + O_DLRX_RXPB_PMAC_HDR_fwd1 + offset)) & M_DLRX_RXPB_PMAC_HDR_fwd1) >> B_DLRX_RXPB_PMAC_HDR_fwd1))

#define DLRX_RXPB_PMAC_HDR_fwd1_get_direct(dword)	((((dword) & M_DLRX_RXPB_PMAC_HDR_fwd1) >> B_DLRX_RXPB_PMAC_HDR_fwd1))

#define DLRX_RXPB_PMAC_HDR_fwd1_set_indirect(base, offset, val) \
	do {                                                              \
		(*(base + O_DLRX_RXPB_PMAC_HDR_fwd1 + offset)) &= (~(M_DLRX_RXPB_PMAC_HDR_fwd1));    \
		(*(base + O_DLRX_RXPB_PMAC_HDR_fwd1 + offset)) |= ((val << B_DLRX_RXPB_PMAC_HDR_fwd1) & M_DLRX_RXPB_PMAC_HDR_fwd1);    \
	} while (0)

#define DLRX_RXPB_PMAC_HDR_fwd1_set_direct(dword, val) \
	do {                                                               \
		(dword) &= (~(M_DLRX_RXPB_PMAC_HDR_fwd1));    \
		(dword) |= ((val << B_DLRX_RXPB_PMAC_HDR_fwd1) & M_DLRX_RXPB_PMAC_HDR_fwd1);    \
	} while (0)

#define DLRX_RXPB_PMAC_HDR_fwd1_clear_indirect(base, offset)	((*(base + O_DLRX_RXPB_PMAC_HDR_fwd1 + offset)) &= (~(M_DLRX_RXPB_PMAC_HDR_fwd1)))

#define DLRX_RXPB_PMAC_HDR_fwd1_clear_direct(dword)	((dword) &= (~(M_DLRX_RXPB_PMAC_HDR_fwd1)))

#define O_DLRX_RXPB_PMAC_HDR_rsvd1 0
#define B_DLRX_RXPB_PMAC_HDR_rsvd1 13
#define W_DLRX_RXPB_PMAC_HDR_rsvd1 3
#define M_DLRX_RXPB_PMAC_HDR_rsvd1 0x0000e000

#define DLRX_RXPB_PMAC_HDR_rsvd1_get_indirect(base, offset)	((((*(base + O_DLRX_RXPB_PMAC_HDR_rsvd1 + offset)) & M_DLRX_RXPB_PMAC_HDR_rsvd1) >> B_DLRX_RXPB_PMAC_HDR_rsvd1))

#define DLRX_RXPB_PMAC_HDR_rsvd1_get_direct(dword)	((((dword) & M_DLRX_RXPB_PMAC_HDR_rsvd1) >> B_DLRX_RXPB_PMAC_HDR_rsvd1))

#define DLRX_RXPB_PMAC_HDR_rsvd1_set_indirect(base, offset, val) \
	do {                                                              \
		(*(base + O_DLRX_RXPB_PMAC_HDR_rsvd1 + offset)) &= (~(M_DLRX_RXPB_PMAC_HDR_rsvd1));    \
		(*(base + O_DLRX_RXPB_PMAC_HDR_rsvd1 + offset)) |= ((val << B_DLRX_RXPB_PMAC_HDR_rsvd1) & M_DLRX_RXPB_PMAC_HDR_rsvd1);    \
	} while (0)

#define DLRX_RXPB_PMAC_HDR_rsvd1_set_direct(dword, val) \
	do {                                                               \
		(dword) &= (~(M_DLRX_RXPB_PMAC_HDR_rsvd1));    \
		(dword) |= ((val << B_DLRX_RXPB_PMAC_HDR_rsvd1) & M_DLRX_RXPB_PMAC_HDR_rsvd1);    \
	} while (0)

#define DLRX_RXPB_PMAC_HDR_rsvd1_clear_indirect(base, offset)	((*(base + O_DLRX_RXPB_PMAC_HDR_rsvd1 + offset)) &= (~(M_DLRX_RXPB_PMAC_HDR_rsvd1)))

#define DLRX_RXPB_PMAC_HDR_rsvd1_clear_direct(dword)	((dword) &= (~(M_DLRX_RXPB_PMAC_HDR_rsvd1)))

#define O_DLRX_RXPB_PMAC_HDR_dest_int 0
#define B_DLRX_RXPB_PMAC_HDR_dest_int 16
#define W_DLRX_RXPB_PMAC_HDR_dest_int 4
#define M_DLRX_RXPB_PMAC_HDR_dest_int 0x000f0000

#define DLRX_RXPB_PMAC_HDR_dest_int_get_indirect(base, offset)	((((*(base + O_DLRX_RXPB_PMAC_HDR_dest_int + offset)) & M_DLRX_RXPB_PMAC_HDR_dest_int) >> B_DLRX_RXPB_PMAC_HDR_dest_int))

#define DLRX_RXPB_PMAC_HDR_dest_int_get_direct(dword)	((((dword) & M_DLRX_RXPB_PMAC_HDR_dest_int) >> B_DLRX_RXPB_PMAC_HDR_dest_int))

#define DLRX_RXPB_PMAC_HDR_dest_int_set_indirect(base, offset, val) \
	do {                                                              \
		(*(base + O_DLRX_RXPB_PMAC_HDR_dest_int + offset)) &= (~(M_DLRX_RXPB_PMAC_HDR_dest_int));    \
		(*(base + O_DLRX_RXPB_PMAC_HDR_dest_int + offset)) |= ((val << B_DLRX_RXPB_PMAC_HDR_dest_int) & M_DLRX_RXPB_PMAC_HDR_dest_int);    \
	} while (0)

#define DLRX_RXPB_PMAC_HDR_dest_int_set_direct(dword, val) \
	do {                                                               \
		(dword) &= (~(M_DLRX_RXPB_PMAC_HDR_dest_int));    \
		(dword) |= ((val << B_DLRX_RXPB_PMAC_HDR_dest_int) & M_DLRX_RXPB_PMAC_HDR_dest_int);    \
	} while (0)

#define DLRX_RXPB_PMAC_HDR_dest_int_clear_indirect(base, offset)	((*(base + O_DLRX_RXPB_PMAC_HDR_dest_int + offset)) &= (~(M_DLRX_RXPB_PMAC_HDR_dest_int)))

#define DLRX_RXPB_PMAC_HDR_dest_int_clear_direct(dword)	((dword) &= (~(M_DLRX_RXPB_PMAC_HDR_dest_int)))

#define O_DLRX_RXPB_PMAC_HDR_rsvd2 0
#define B_DLRX_RXPB_PMAC_HDR_rsvd2 20
#define W_DLRX_RXPB_PMAC_HDR_rsvd2 4
#define M_DLRX_RXPB_PMAC_HDR_rsvd2 0x00f00000

#define DLRX_RXPB_PMAC_HDR_rsvd2_get_indirect(base, offset)	((((*(base + O_DLRX_RXPB_PMAC_HDR_rsvd2 + offset)) & M_DLRX_RXPB_PMAC_HDR_rsvd2) >> B_DLRX_RXPB_PMAC_HDR_rsvd2))

#define DLRX_RXPB_PMAC_HDR_rsvd2_get_direct(dword)	((((dword) & M_DLRX_RXPB_PMAC_HDR_rsvd2) >> B_DLRX_RXPB_PMAC_HDR_rsvd2))

#define DLRX_RXPB_PMAC_HDR_rsvd2_set_indirect(base, offset, val) \
	do {                                                              \
		(*(base + O_DLRX_RXPB_PMAC_HDR_rsvd2 + offset)) &= (~(M_DLRX_RXPB_PMAC_HDR_rsvd2));    \
		(*(base + O_DLRX_RXPB_PMAC_HDR_rsvd2 + offset)) |= ((val << B_DLRX_RXPB_PMAC_HDR_rsvd2) & M_DLRX_RXPB_PMAC_HDR_rsvd2);    \
	} while (0)

#define DLRX_RXPB_PMAC_HDR_rsvd2_set_direct(dword, val) \
	do {                                                               \
		(dword) &= (~(M_DLRX_RXPB_PMAC_HDR_rsvd2));    \
		(dword) |= ((val << B_DLRX_RXPB_PMAC_HDR_rsvd2) & M_DLRX_RXPB_PMAC_HDR_rsvd2);    \
	} while (0)

#define DLRX_RXPB_PMAC_HDR_rsvd2_clear_indirect(base, offset)	((*(base + O_DLRX_RXPB_PMAC_HDR_rsvd2 + offset)) &= (~(M_DLRX_RXPB_PMAC_HDR_rsvd2)))

#define DLRX_RXPB_PMAC_HDR_rsvd2_clear_direct(dword)	((dword) &= (~(M_DLRX_RXPB_PMAC_HDR_rsvd2)))

#define O_DLRX_RXPB_PMAC_HDR_src_int 0
#define B_DLRX_RXPB_PMAC_HDR_src_int 24
#define W_DLRX_RXPB_PMAC_HDR_src_int 4
#define M_DLRX_RXPB_PMAC_HDR_src_int 0x0f000000

#define DLRX_RXPB_PMAC_HDR_src_int_get_indirect(base, offset)	((((*(base + O_DLRX_RXPB_PMAC_HDR_src_int + offset)) & M_DLRX_RXPB_PMAC_HDR_src_int) >> B_DLRX_RXPB_PMAC_HDR_src_int))

#define DLRX_RXPB_PMAC_HDR_src_int_get_direct(dword)	((((dword) & M_DLRX_RXPB_PMAC_HDR_src_int) >> B_DLRX_RXPB_PMAC_HDR_src_int))

#define DLRX_RXPB_PMAC_HDR_src_int_set_indirect(base, offset, val) \
	do {                                                              \
		(*(base + O_DLRX_RXPB_PMAC_HDR_src_int + offset)) &= (~(M_DLRX_RXPB_PMAC_HDR_src_int));    \
		(*(base + O_DLRX_RXPB_PMAC_HDR_src_int + offset)) |= ((val << B_DLRX_RXPB_PMAC_HDR_src_int) & M_DLRX_RXPB_PMAC_HDR_src_int);    \
	} while (0)

#define DLRX_RXPB_PMAC_HDR_src_int_set_direct(dword, val) \
	do {                                                               \
		(dword) &= (~(M_DLRX_RXPB_PMAC_HDR_src_int));    \
		(dword) |= ((val << B_DLRX_RXPB_PMAC_HDR_src_int) & M_DLRX_RXPB_PMAC_HDR_src_int);    \
	} while (0)

#define DLRX_RXPB_PMAC_HDR_src_int_clear_indirect(base, offset)	((*(base + O_DLRX_RXPB_PMAC_HDR_src_int + offset)) &= (~(M_DLRX_RXPB_PMAC_HDR_src_int)))

#define DLRX_RXPB_PMAC_HDR_src_int_clear_direct(dword)	((dword) &= (~(M_DLRX_RXPB_PMAC_HDR_src_int)))

#define O_DLRX_RXPB_PMAC_HDR_rsvd3 0
#define B_DLRX_RXPB_PMAC_HDR_rsvd3 28
#define W_DLRX_RXPB_PMAC_HDR_rsvd3 4
#define M_DLRX_RXPB_PMAC_HDR_rsvd3 0xf0000000

#define DLRX_RXPB_PMAC_HDR_rsvd3_get_indirect(base, offset)	((((*(base + O_DLRX_RXPB_PMAC_HDR_rsvd3 + offset)) & M_DLRX_RXPB_PMAC_HDR_rsvd3) >> B_DLRX_RXPB_PMAC_HDR_rsvd3))

#define DLRX_RXPB_PMAC_HDR_rsvd3_get_direct(dword)	((((dword) & M_DLRX_RXPB_PMAC_HDR_rsvd3) >> B_DLRX_RXPB_PMAC_HDR_rsvd3))

#define DLRX_RXPB_PMAC_HDR_rsvd3_set_indirect(base, offset, val) \
	do {                                                              \
		(*(base + O_DLRX_RXPB_PMAC_HDR_rsvd3 + offset)) &= (~(M_DLRX_RXPB_PMAC_HDR_rsvd3));    \
		(*(base + O_DLRX_RXPB_PMAC_HDR_rsvd3 + offset)) |= ((val << B_DLRX_RXPB_PMAC_HDR_rsvd3) & M_DLRX_RXPB_PMAC_HDR_rsvd3);    \
	} while (0)

#define DLRX_RXPB_PMAC_HDR_rsvd3_set_direct(dword, val) \
	do {                                                               \
		(dword) &= (~(M_DLRX_RXPB_PMAC_HDR_rsvd3));    \
		(dword) |= ((val << B_DLRX_RXPB_PMAC_HDR_rsvd3) & M_DLRX_RXPB_PMAC_HDR_rsvd3);    \
	} while (0)

#define DLRX_RXPB_PMAC_HDR_rsvd3_clear_indirect(base, offset)	((*(base + O_DLRX_RXPB_PMAC_HDR_rsvd3 + offset)) &= (~(M_DLRX_RXPB_PMAC_HDR_rsvd3)))

#define DLRX_RXPB_PMAC_HDR_rsvd3_clear_direct(dword)	((dword) &= (~(M_DLRX_RXPB_PMAC_HDR_rsvd3)))

#define O_DLRX_RXPB_WLAN_DRV_HDR_fw_rx_desc_byte 0
#define B_DLRX_RXPB_WLAN_DRV_HDR_fw_rx_desc_byte 0
#define W_DLRX_RXPB_WLAN_DRV_HDR_fw_rx_desc_byte 8
#define M_DLRX_RXPB_WLAN_DRV_HDR_fw_rx_desc_byte 0x000000ff

#define DLRX_RXPB_WLAN_DRV_HDR_fw_rx_desc_byte_get_indirect(base, offset)	((((*(base + O_DLRX_RXPB_WLAN_DRV_HDR_fw_rx_desc_byte + offset)) & M_DLRX_RXPB_WLAN_DRV_HDR_fw_rx_desc_byte) >> B_DLRX_RXPB_WLAN_DRV_HDR_fw_rx_desc_byte))

#define DLRX_RXPB_WLAN_DRV_HDR_fw_rx_desc_byte_get_direct(dword)	((((dword) & M_DLRX_RXPB_WLAN_DRV_HDR_fw_rx_desc_byte) >> B_DLRX_RXPB_WLAN_DRV_HDR_fw_rx_desc_byte))

#define DLRX_RXPB_WLAN_DRV_HDR_fw_rx_desc_byte_set_indirect(base, offset, val) \
	do {                                                              \
		(*(base + O_DLRX_RXPB_WLAN_DRV_HDR_fw_rx_desc_byte + offset)) &= (~(M_DLRX_RXPB_WLAN_DRV_HDR_fw_rx_desc_byte));    \
		(*(base + O_DLRX_RXPB_WLAN_DRV_HDR_fw_rx_desc_byte + offset)) |= ((val << B_DLRX_RXPB_WLAN_DRV_HDR_fw_rx_desc_byte) & M_DLRX_RXPB_WLAN_DRV_HDR_fw_rx_desc_byte);    \
	} while (0)

#define DLRX_RXPB_WLAN_DRV_HDR_fw_rx_desc_byte_set_direct(dword, val) \
	do {                                                               \
		(dword) &= (~(M_DLRX_RXPB_WLAN_DRV_HDR_fw_rx_desc_byte));    \
		(dword) |= ((val << B_DLRX_RXPB_WLAN_DRV_HDR_fw_rx_desc_byte) & M_DLRX_RXPB_WLAN_DRV_HDR_fw_rx_desc_byte);    \
	} while (0)

#define DLRX_RXPB_WLAN_DRV_HDR_fw_rx_desc_byte_clear_indirect(base, offset)	((*(base + O_DLRX_RXPB_WLAN_DRV_HDR_fw_rx_desc_byte + offset)) &= (~(M_DLRX_RXPB_WLAN_DRV_HDR_fw_rx_desc_byte)))

#define DLRX_RXPB_WLAN_DRV_HDR_fw_rx_desc_byte_clear_direct(dword)	((dword) &= (~(M_DLRX_RXPB_WLAN_DRV_HDR_fw_rx_desc_byte)))

#define O_DLRX_RXPB_WLAN_DRV_HDR_mpdu_status 0
#define B_DLRX_RXPB_WLAN_DRV_HDR_mpdu_status 8
#define W_DLRX_RXPB_WLAN_DRV_HDR_mpdu_status 8
#define M_DLRX_RXPB_WLAN_DRV_HDR_mpdu_status 0x0000ff00

#define DLRX_RXPB_WLAN_DRV_HDR_mpdu_status_get_indirect(base, offset)	((((*(base + O_DLRX_RXPB_WLAN_DRV_HDR_mpdu_status + offset)) & M_DLRX_RXPB_WLAN_DRV_HDR_mpdu_status) >> B_DLRX_RXPB_WLAN_DRV_HDR_mpdu_status))

#define DLRX_RXPB_WLAN_DRV_HDR_mpdu_status_get_direct(dword)	((((dword) & M_DLRX_RXPB_WLAN_DRV_HDR_mpdu_status) >> B_DLRX_RXPB_WLAN_DRV_HDR_mpdu_status))

#define DLRX_RXPB_WLAN_DRV_HDR_mpdu_status_set_indirect(base, offset, val) \
	do {                                                              \
		(*(base + O_DLRX_RXPB_WLAN_DRV_HDR_mpdu_status + offset)) &= (~(M_DLRX_RXPB_WLAN_DRV_HDR_mpdu_status));    \
		(*(base + O_DLRX_RXPB_WLAN_DRV_HDR_mpdu_status + offset)) |= ((val << B_DLRX_RXPB_WLAN_DRV_HDR_mpdu_status) & M_DLRX_RXPB_WLAN_DRV_HDR_mpdu_status);    \
	} while (0)

#define DLRX_RXPB_WLAN_DRV_HDR_mpdu_status_set_direct(dword, val) \
	do {                                                               \
		(dword) &= (~(M_DLRX_RXPB_WLAN_DRV_HDR_mpdu_status));    \
		(dword) |= ((val << B_DLRX_RXPB_WLAN_DRV_HDR_mpdu_status) & M_DLRX_RXPB_WLAN_DRV_HDR_mpdu_status);    \
	} while (0)

#define DLRX_RXPB_WLAN_DRV_HDR_mpdu_status_clear_indirect(base, offset)	((*(base + O_DLRX_RXPB_WLAN_DRV_HDR_mpdu_status + offset)) &= (~(M_DLRX_RXPB_WLAN_DRV_HDR_mpdu_status)))

#define DLRX_RXPB_WLAN_DRV_HDR_mpdu_status_clear_direct(dword)	((dword) &= (~(M_DLRX_RXPB_WLAN_DRV_HDR_mpdu_status)))

#define O_DLRX_RXPB_WLAN_DRV_HDR_rsvd0 0
#define B_DLRX_RXPB_WLAN_DRV_HDR_rsvd0 16
#define W_DLRX_RXPB_WLAN_DRV_HDR_rsvd0 16
#define M_DLRX_RXPB_WLAN_DRV_HDR_rsvd0 0xffff0000

#define DLRX_RXPB_WLAN_DRV_HDR_rsvd0_get_indirect(base, offset)	((((*(base + O_DLRX_RXPB_WLAN_DRV_HDR_rsvd0 + offset)) & M_DLRX_RXPB_WLAN_DRV_HDR_rsvd0) >> B_DLRX_RXPB_WLAN_DRV_HDR_rsvd0))

#define DLRX_RXPB_WLAN_DRV_HDR_rsvd0_get_direct(dword)	((((dword) & M_DLRX_RXPB_WLAN_DRV_HDR_rsvd0) >> B_DLRX_RXPB_WLAN_DRV_HDR_rsvd0))

#define DLRX_RXPB_WLAN_DRV_HDR_rsvd0_set_indirect(base, offset, val) \
	do {                                                              \
		(*(base + O_DLRX_RXPB_WLAN_DRV_HDR_rsvd0 + offset)) &= (~(M_DLRX_RXPB_WLAN_DRV_HDR_rsvd0));    \
		(*(base + O_DLRX_RXPB_WLAN_DRV_HDR_rsvd0 + offset)) |= ((val << B_DLRX_RXPB_WLAN_DRV_HDR_rsvd0) & M_DLRX_RXPB_WLAN_DRV_HDR_rsvd0);    \
	} while (0)

#define DLRX_RXPB_WLAN_DRV_HDR_rsvd0_set_direct(dword, val) \
	do {                                                               \
		(dword) &= (~(M_DLRX_RXPB_WLAN_DRV_HDR_rsvd0));    \
		(dword) |= ((val << B_DLRX_RXPB_WLAN_DRV_HDR_rsvd0) & M_DLRX_RXPB_WLAN_DRV_HDR_rsvd0);    \
	} while (0)

#define DLRX_RXPB_WLAN_DRV_HDR_rsvd0_clear_indirect(base, offset)	((*(base + O_DLRX_RXPB_WLAN_DRV_HDR_rsvd0 + offset)) &= (~(M_DLRX_RXPB_WLAN_DRV_HDR_rsvd0)))

#define DLRX_RXPB_WLAN_DRV_HDR_rsvd0_clear_direct(dword)	((dword) &= (~(M_DLRX_RXPB_WLAN_DRV_HDR_rsvd0)))

#define O_DLRX_IND_MSG_htt_hdr 0
#define B_DLRX_IND_MSG_htt_hdr 0
#define W_DLRX_IND_MSG_htt_hdr 32
#define M_DLRX_IND_MSG_htt_hdr 0xffffffff

#define DLRX_IND_MSG_htt_hdr_get_indirect(base, offset)	((((*(base + O_DLRX_IND_MSG_htt_hdr + offset)) & M_DLRX_IND_MSG_htt_hdr) >> B_DLRX_IND_MSG_htt_hdr))

#define DLRX_IND_MSG_htt_hdr_get_direct(dword)	((((dword) & M_DLRX_IND_MSG_htt_hdr) >> B_DLRX_IND_MSG_htt_hdr))

#define DLRX_IND_MSG_htt_hdr_set_indirect(base, offset, val)    \
	do {                                                              \
		(*(base + O_DLRX_IND_MSG_htt_hdr + offset)) &= (~(M_DLRX_IND_MSG_htt_hdr));    \
		(*(base + O_DLRX_IND_MSG_htt_hdr + offset)) |= ((val << B_DLRX_IND_MSG_htt_hdr) & M_DLRX_IND_MSG_htt_hdr);    \
	} while (0)

#define DLRX_IND_MSG_htt_hdr_set_direct(dword, val)    \
	do {                                                               \
		(dword) &= (~(M_DLRX_IND_MSG_htt_hdr));    \
		(dword) |= ((val << B_DLRX_IND_MSG_htt_hdr) & M_DLRX_IND_MSG_htt_hdr);    \
	} while (0)

#define DLRX_IND_MSG_htt_hdr_clear_indirect(base, offset)	((*(base + O_DLRX_IND_MSG_htt_hdr + offset)) &= (~(M_DLRX_IND_MSG_htt_hdr)))

#define DLRX_IND_MSG_htt_hdr_clear_direct(dword)	((dword) &= (~(M_DLRX_IND_MSG_htt_hdr)))

#define O_DLRX_IND_MSG_msg_type 2
#define B_DLRX_IND_MSG_msg_type 0
#define W_DLRX_IND_MSG_msg_type 8
#define M_DLRX_IND_MSG_msg_type 0x000000ff

#define DLRX_IND_MSG_msg_type_get_indirect(base, offset)	((((*(base + O_DLRX_IND_MSG_msg_type + offset)) & M_DLRX_IND_MSG_msg_type) >> B_DLRX_IND_MSG_msg_type))

#define DLRX_IND_MSG_msg_type_get_direct(dword)	((((dword) & M_DLRX_IND_MSG_msg_type) >> B_DLRX_IND_MSG_msg_type))

#define DLRX_IND_MSG_msg_type_set_indirect(base, offset, val) \
	do {                                                              \
		(*(base + O_DLRX_IND_MSG_msg_type + offset)) &= (~(M_DLRX_IND_MSG_msg_type));    \
		(*(base + O_DLRX_IND_MSG_msg_type + offset)) |= ((val << B_DLRX_IND_MSG_msg_type) & M_DLRX_IND_MSG_msg_type);    \
	} while (0)

#define DLRX_IND_MSG_msg_type_set_direct(dword, val) \
	do {                                                               \
		(dword) &= (~(M_DLRX_IND_MSG_msg_type));    \
		(dword) |= ((val << B_DLRX_IND_MSG_msg_type) & M_DLRX_IND_MSG_msg_type);    \
	} while (0)

#define DLRX_IND_MSG_msg_type_clear_indirect(base, offset)	((*(base + O_DLRX_IND_MSG_msg_type + offset)) &= (~(M_DLRX_IND_MSG_msg_type)))

#define DLRX_IND_MSG_msg_type_clear_direct(dword)	((dword) &= (~(M_DLRX_IND_MSG_msg_type)))

#define O_DLRX_IND_MSG_ext_tid 2
#define B_DLRX_IND_MSG_ext_tid 8
#define W_DLRX_IND_MSG_ext_tid 5
#define M_DLRX_IND_MSG_ext_tid 0x00001f00

#define DLRX_IND_MSG_ext_tid_get_indirect(base, offset)	((((*(base + O_DLRX_IND_MSG_ext_tid + offset)) & M_DLRX_IND_MSG_ext_tid) >> B_DLRX_IND_MSG_ext_tid))

#define DLRX_IND_MSG_ext_tid_get_direct(dword)	((((dword) & M_DLRX_IND_MSG_ext_tid) >> B_DLRX_IND_MSG_ext_tid))

#define DLRX_IND_MSG_ext_tid_set_indirect(base, offset, val) \
	do {                                                              \
		(*(base + O_DLRX_IND_MSG_ext_tid + offset)) &= (~(M_DLRX_IND_MSG_ext_tid));    \
		(*(base + O_DLRX_IND_MSG_ext_tid + offset)) |= ((val << B_DLRX_IND_MSG_ext_tid) & M_DLRX_IND_MSG_ext_tid);    \
	} while (0)

#define DLRX_IND_MSG_ext_tid_set_direct(dword, val) \
	do {                                                               \
		(dword) &= (~(M_DLRX_IND_MSG_ext_tid));    \
		(dword) |= ((val << B_DLRX_IND_MSG_ext_tid) & M_DLRX_IND_MSG_ext_tid);    \
	} while (0)

#define DLRX_IND_MSG_ext_tid_clear_indirect(base, offset)	((*(base + O_DLRX_IND_MSG_ext_tid + offset)) &= (~(M_DLRX_IND_MSG_ext_tid)))

#define DLRX_IND_MSG_ext_tid_clear_direct(dword)	((dword) &= (~(M_DLRX_IND_MSG_ext_tid)))

#define O_DLRX_IND_MSG_fv 2
#define B_DLRX_IND_MSG_fv 13
#define W_DLRX_IND_MSG_fv 1
#define M_DLRX_IND_MSG_fv 0x00002000

#define DLRX_IND_MSG_fv_get_indirect(base, offset)	((((*(base + O_DLRX_IND_MSG_fv + offset)) & M_DLRX_IND_MSG_fv) >> B_DLRX_IND_MSG_fv))

#define DLRX_IND_MSG_fv_get_direct(dword)	((((dword) & M_DLRX_IND_MSG_fv) >> B_DLRX_IND_MSG_fv))

#define DLRX_IND_MSG_fv_set_indirect(base, offset, val) \
	do {                                                              \
		(*(base + O_DLRX_IND_MSG_fv + offset)) &= (~(M_DLRX_IND_MSG_fv));    \
		(*(base + O_DLRX_IND_MSG_fv + offset)) |= ((val << B_DLRX_IND_MSG_fv) & M_DLRX_IND_MSG_fv);    \
	} while (0)

#define DLRX_IND_MSG_fv_set_direct(dword, val) \
	do {                                                               \
		(dword) &= (~(M_DLRX_IND_MSG_fv));    \
		(dword) |= ((val << B_DLRX_IND_MSG_fv) & M_DLRX_IND_MSG_fv);    \
	} while (0)

#define DLRX_IND_MSG_fv_clear_indirect(base, offset)	((*(base + O_DLRX_IND_MSG_fv + offset)) &= (~(M_DLRX_IND_MSG_fv)))

#define DLRX_IND_MSG_fv_clear_direct(dword)	((dword) &= (~(M_DLRX_IND_MSG_fv)))

#define O_DLRX_IND_MSG_rv 2
#define B_DLRX_IND_MSG_rv 14
#define W_DLRX_IND_MSG_rv 1
#define M_DLRX_IND_MSG_rv 0x00004000

#define DLRX_IND_MSG_rv_get_indirect(base, offset)	((((*(base + O_DLRX_IND_MSG_rv + offset)) & M_DLRX_IND_MSG_rv) >> B_DLRX_IND_MSG_rv))

#define DLRX_IND_MSG_rv_get_direct(dword)	((((dword) & M_DLRX_IND_MSG_rv) >> B_DLRX_IND_MSG_rv))

#define DLRX_IND_MSG_rv_set_indirect(base, offset, val) \
	do {                                                              \
		(*(base + O_DLRX_IND_MSG_rv + offset)) &= (~(M_DLRX_IND_MSG_rv));    \
		(*(base + O_DLRX_IND_MSG_rv + offset)) |= ((val << B_DLRX_IND_MSG_rv) & M_DLRX_IND_MSG_rv);    \
	} while (0)

#define DLRX_IND_MSG_rv_set_direct(dword, val) \
	do {                                                               \
		(dword) &= (~(M_DLRX_IND_MSG_rv));    \
		(dword) |= ((val << B_DLRX_IND_MSG_rv) & M_DLRX_IND_MSG_rv);    \
	} while (0)

#define DLRX_IND_MSG_rv_clear_indirect(base, offset)	((*(base + O_DLRX_IND_MSG_rv + offset)) &= (~(M_DLRX_IND_MSG_rv)))

#define DLRX_IND_MSG_rv_clear_direct(dword)	((dword) &= (~(M_DLRX_IND_MSG_rv)))

#define O_DLRX_IND_MSG_rsvd0 2
#define B_DLRX_IND_MSG_rsvd0 15
#define W_DLRX_IND_MSG_rsvd0 1
#define M_DLRX_IND_MSG_rsvd0 0x00008000

#define DLRX_IND_MSG_rsvd0_get_indirect(base, offset)	((((*(base + O_DLRX_IND_MSG_rsvd0 + offset)) & M_DLRX_IND_MSG_rsvd0) >> B_DLRX_IND_MSG_rsvd0))

#define DLRX_IND_MSG_rsvd0_get_direct(dword)	((((dword) & M_DLRX_IND_MSG_rsvd0) >> B_DLRX_IND_MSG_rsvd0))

#define DLRX_IND_MSG_rsvd0_set_indirect(base, offset, val) \
	do {                                                              \
		(*(base + O_DLRX_IND_MSG_rsvd0 + offset)) &= (~(M_DLRX_IND_MSG_rsvd0));    \
		(*(base + O_DLRX_IND_MSG_rsvd0 + offset)) |= ((val << B_DLRX_IND_MSG_rsvd0) & M_DLRX_IND_MSG_rsvd0);    \
	} while (0)

#define DLRX_IND_MSG_rsvd0_set_direct(dword, val) \
	do {                                                               \
		(dword) &= (~(M_DLRX_IND_MSG_rsvd0));    \
		(dword) |= ((val << B_DLRX_IND_MSG_rsvd0) & M_DLRX_IND_MSG_rsvd0);    \
	} while (0)

#define DLRX_IND_MSG_rsvd0_clear_indirect(base, offset)	((*(base + O_DLRX_IND_MSG_rsvd0 + offset)) &= (~(M_DLRX_IND_MSG_rsvd0)))

#define DLRX_IND_MSG_rsvd0_clear_direct(dword)	((dword) &= (~(M_DLRX_IND_MSG_rsvd0)))

#define O_DLRX_IND_MSG_peer_id 2
#define B_DLRX_IND_MSG_peer_id 16
#define W_DLRX_IND_MSG_peer_id 16
#define M_DLRX_IND_MSG_peer_id 0xffff0000

#define DLRX_IND_MSG_peer_id_get_indirect(base, offset)	((((*(base + O_DLRX_IND_MSG_peer_id + offset)) & M_DLRX_IND_MSG_peer_id) >> B_DLRX_IND_MSG_peer_id))

#define DLRX_IND_MSG_peer_id_get_direct(dword)	((((dword) & M_DLRX_IND_MSG_peer_id) >> B_DLRX_IND_MSG_peer_id))

#define DLRX_IND_MSG_peer_id_set_indirect(base, offset, val) \
	do {                                                              \
		(*(base + O_DLRX_IND_MSG_peer_id + offset)) &= (~(M_DLRX_IND_MSG_peer_id));    \
		(*(base + O_DLRX_IND_MSG_peer_id + offset)) |= ((val << B_DLRX_IND_MSG_peer_id) & M_DLRX_IND_MSG_peer_id);    \
	} while (0)

#define DLRX_IND_MSG_peer_id_set_direct(dword, val) \
	do {                                                               \
		(dword) &= (~(M_DLRX_IND_MSG_peer_id));    \
		(dword) |= ((val << B_DLRX_IND_MSG_peer_id) & M_DLRX_IND_MSG_peer_id);    \
	} while (0)

#define DLRX_IND_MSG_peer_id_clear_indirect(base, offset)	((*(base + O_DLRX_IND_MSG_peer_id + offset)) &= (~(M_DLRX_IND_MSG_peer_id)))

#define DLRX_IND_MSG_peer_id_clear_direct(dword)	((dword) &= (~(M_DLRX_IND_MSG_peer_id)))

#define O_DLRX_IND_MSG_flush_start_seqid 3
#define B_DLRX_IND_MSG_flush_start_seqid 0
#define W_DLRX_IND_MSG_flush_start_seqid 6
#define M_DLRX_IND_MSG_flush_start_seqid 0x0000003f

#define DLRX_IND_MSG_flush_start_seqid_get_indirect(base, offset)	((((*(base + O_DLRX_IND_MSG_flush_start_seqid + offset)) & M_DLRX_IND_MSG_flush_start_seqid) >> B_DLRX_IND_MSG_flush_start_seqid))

#define DLRX_IND_MSG_flush_start_seqid_get_direct(dword)	((((dword) & M_DLRX_IND_MSG_flush_start_seqid) >> B_DLRX_IND_MSG_flush_start_seqid))

#define DLRX_IND_MSG_flush_start_seqid_set_indirect(base, offset, val) \
	do {                                                              \
		(*(base + O_DLRX_IND_MSG_flush_start_seqid + offset)) &= (~(M_DLRX_IND_MSG_flush_start_seqid));    \
		(*(base + O_DLRX_IND_MSG_flush_start_seqid + offset)) |= ((val << B_DLRX_IND_MSG_flush_start_seqid) & M_DLRX_IND_MSG_flush_start_seqid);    \
	} while (0)

#define DLRX_IND_MSG_flush_start_seqid_set_direct(dword, val) \
	do {                                                               \
		(dword) &= (~(M_DLRX_IND_MSG_flush_start_seqid));    \
		(dword) |= ((val << B_DLRX_IND_MSG_flush_start_seqid) & M_DLRX_IND_MSG_flush_start_seqid);    \
	} while (0)

#define DLRX_IND_MSG_flush_start_seqid_clear_indirect(base, offset)	((*(base + O_DLRX_IND_MSG_flush_start_seqid + offset)) &= (~(M_DLRX_IND_MSG_flush_start_seqid)))

#define DLRX_IND_MSG_flush_start_seqid_clear_direct(dword)	((dword) &= (~(M_DLRX_IND_MSG_flush_start_seqid)))

#define O_DLRX_IND_MSG_flush_end_seqid 3
#define B_DLRX_IND_MSG_flush_end_seqid 6
#define W_DLRX_IND_MSG_flush_end_seqid 6
#define M_DLRX_IND_MSG_flush_end_seqid 0x00000fc0

#define DLRX_IND_MSG_flush_end_seqid_get_indirect(base, offset)	((((*(base + O_DLRX_IND_MSG_flush_end_seqid + offset)) & M_DLRX_IND_MSG_flush_end_seqid) >> B_DLRX_IND_MSG_flush_end_seqid))

#define DLRX_IND_MSG_flush_end_seqid_get_direct(dword)	((((dword) & M_DLRX_IND_MSG_flush_end_seqid) >> B_DLRX_IND_MSG_flush_end_seqid))

#define DLRX_IND_MSG_flush_end_seqid_set_indirect(base, offset, val) \
	do {                                                              \
		(*(base + O_DLRX_IND_MSG_flush_end_seqid + offset)) &= (~(M_DLRX_IND_MSG_flush_end_seqid));    \
		(*(base + O_DLRX_IND_MSG_flush_end_seqid + offset)) |= ((val << B_DLRX_IND_MSG_flush_end_seqid) & M_DLRX_IND_MSG_flush_end_seqid);    \
	} while (0)

#define DLRX_IND_MSG_flush_end_seqid_set_direct(dword, val) \
	do {                                                               \
		(dword) &= (~(M_DLRX_IND_MSG_flush_end_seqid));    \
		(dword) |= ((val << B_DLRX_IND_MSG_flush_end_seqid) & M_DLRX_IND_MSG_flush_end_seqid);    \
	} while (0)

#define DLRX_IND_MSG_flush_end_seqid_clear_indirect(base, offset)	((*(base + O_DLRX_IND_MSG_flush_end_seqid + offset)) &= (~(M_DLRX_IND_MSG_flush_end_seqid)))

#define DLRX_IND_MSG_flush_end_seqid_clear_direct(dword)	((dword) &= (~(M_DLRX_IND_MSG_flush_end_seqid)))

#define O_DLRX_IND_MSG_release_start_seqid 3
#define B_DLRX_IND_MSG_release_start_seqid 12
#define W_DLRX_IND_MSG_release_start_seqid 6
#define M_DLRX_IND_MSG_release_start_seqid 0x0003f000

#define DLRX_IND_MSG_release_start_seqid_get_indirect(base, offset)	((((*(base + O_DLRX_IND_MSG_release_start_seqid + offset)) & M_DLRX_IND_MSG_release_start_seqid) >> B_DLRX_IND_MSG_release_start_seqid))

#define DLRX_IND_MSG_release_start_seqid_get_direct(dword)	((((dword) & M_DLRX_IND_MSG_release_start_seqid) >> B_DLRX_IND_MSG_release_start_seqid))

#define DLRX_IND_MSG_release_start_seqid_set_indirect(base, offset, val) \
	do {                                                              \
		(*(base + O_DLRX_IND_MSG_release_start_seqid + offset)) &= (~(M_DLRX_IND_MSG_release_start_seqid));    \
		(*(base + O_DLRX_IND_MSG_release_start_seqid + offset)) |= ((val << B_DLRX_IND_MSG_release_start_seqid) & M_DLRX_IND_MSG_release_start_seqid);    \
	} while (0)

#define DLRX_IND_MSG_release_start_seqid_set_direct(dword, val) \
	do {                                                               \
		(dword) &= (~(M_DLRX_IND_MSG_release_start_seqid));    \
		(dword) |= ((val << B_DLRX_IND_MSG_release_start_seqid) & M_DLRX_IND_MSG_release_start_seqid);    \
	} while (0)

#define DLRX_IND_MSG_release_start_seqid_clear_indirect(base, offset)	((*(base + O_DLRX_IND_MSG_release_start_seqid + offset)) &= (~(M_DLRX_IND_MSG_release_start_seqid)))

#define DLRX_IND_MSG_release_start_seqid_clear_direct(dword)	((dword) &= (~(M_DLRX_IND_MSG_release_start_seqid)))

#define O_DLRX_IND_MSG_release_end_seqid 3
#define B_DLRX_IND_MSG_release_end_seqid 18
#define W_DLRX_IND_MSG_release_end_seqid 6
#define M_DLRX_IND_MSG_release_end_seqid 0x00fc0000

#define DLRX_IND_MSG_release_end_seqid_get_indirect(base, offset)	((((*(base + O_DLRX_IND_MSG_release_end_seqid + offset)) & M_DLRX_IND_MSG_release_end_seqid) >> B_DLRX_IND_MSG_release_end_seqid))

#define DLRX_IND_MSG_release_end_seqid_get_direct(dword)	((((dword) & M_DLRX_IND_MSG_release_end_seqid) >> B_DLRX_IND_MSG_release_end_seqid))

#define DLRX_IND_MSG_release_end_seqid_set_indirect(base, offset, val) \
	do {                                                              \
		(*(base + O_DLRX_IND_MSG_release_end_seqid + offset)) &= (~(M_DLRX_IND_MSG_release_end_seqid));    \
		(*(base + O_DLRX_IND_MSG_release_end_seqid + offset)) |= ((val << B_DLRX_IND_MSG_release_end_seqid) & M_DLRX_IND_MSG_release_end_seqid);    \
	} while (0)

#define DLRX_IND_MSG_release_end_seqid_set_direct(dword, val) \
	do {                                                               \
		(dword) &= (~(M_DLRX_IND_MSG_release_end_seqid));    \
		(dword) |= ((val << B_DLRX_IND_MSG_release_end_seqid) & M_DLRX_IND_MSG_release_end_seqid);    \
	} while (0)

#define DLRX_IND_MSG_release_end_seqid_clear_indirect(base, offset)	((*(base + O_DLRX_IND_MSG_release_end_seqid + offset)) &= (~(M_DLRX_IND_MSG_release_end_seqid)))

#define DLRX_IND_MSG_release_end_seqid_clear_direct(dword)	((dword) &= (~(M_DLRX_IND_MSG_release_end_seqid)))

#define O_DLRX_IND_MSG_mpdu_ranges_num 3
#define B_DLRX_IND_MSG_mpdu_ranges_num 24
#define W_DLRX_IND_MSG_mpdu_ranges_num 8
#define M_DLRX_IND_MSG_mpdu_ranges_num 0xff000000

#define DLRX_IND_MSG_mpdu_ranges_num_get_indirect(base, offset)	((((*(base + O_DLRX_IND_MSG_mpdu_ranges_num + offset)) & M_DLRX_IND_MSG_mpdu_ranges_num) >> B_DLRX_IND_MSG_mpdu_ranges_num))

#define DLRX_IND_MSG_mpdu_ranges_num_get_direct(dword)	((((dword) & M_DLRX_IND_MSG_mpdu_ranges_num) >> B_DLRX_IND_MSG_mpdu_ranges_num))

#define DLRX_IND_MSG_mpdu_ranges_num_set_indirect(base, offset, val) \
	do {                                                              \
		(*(base + O_DLRX_IND_MSG_mpdu_ranges_num + offset)) &= (~(M_DLRX_IND_MSG_mpdu_ranges_num));    \
		(*(base + O_DLRX_IND_MSG_mpdu_ranges_num + offset)) |= ((val << B_DLRX_IND_MSG_mpdu_ranges_num) & M_DLRX_IND_MSG_mpdu_ranges_num);    \
	} while (0)

#define DLRX_IND_MSG_mpdu_ranges_num_set_direct(dword, val) \
	do {                                                               \
		(dword) &= (~(M_DLRX_IND_MSG_mpdu_ranges_num));    \
		(dword) |= ((val << B_DLRX_IND_MSG_mpdu_ranges_num) & M_DLRX_IND_MSG_mpdu_ranges_num);    \
	} while (0)

#define DLRX_IND_MSG_mpdu_ranges_num_clear_indirect(base, offset)	((*(base + O_DLRX_IND_MSG_mpdu_ranges_num + offset)) &= (~(M_DLRX_IND_MSG_mpdu_ranges_num)))

#define DLRX_IND_MSG_mpdu_ranges_num_clear_direct(dword)	((dword) &= (~(M_DLRX_IND_MSG_mpdu_ranges_num)))

#define O_DLRX_IND_MSG_rsvd2 4
#define B_DLRX_IND_MSG_rsvd2 0
#define W_DLRX_IND_MSG_rsvd2 32
#define M_DLRX_IND_MSG_rsvd2 0xffffffff

#define DLRX_IND_MSG_rsvd2_get_indirect(base, offset)	((((*(base + O_DLRX_IND_MSG_rsvd2 + offset)) & M_DLRX_IND_MSG_rsvd2) >> B_DLRX_IND_MSG_rsvd2))

#define DLRX_IND_MSG_rsvd2_get_direct(dword)	((((dword) & M_DLRX_IND_MSG_rsvd2) >> B_DLRX_IND_MSG_rsvd2))

#define DLRX_IND_MSG_rsvd2_set_indirect(base, offset, val)    \
	do {                                                              \
		(*(base + O_DLRX_IND_MSG_rsvd2 + offset)) &= (~(M_DLRX_IND_MSG_rsvd2));    \
		(*(base + O_DLRX_IND_MSG_rsvd2 + offset)) |= ((val << B_DLRX_IND_MSG_rsvd2) & M_DLRX_IND_MSG_rsvd2);    \
	} while (0)

#define DLRX_IND_MSG_rsvd2_set_direct(dword, val)    \
	do {                                                               \
		(dword) &= (~(M_DLRX_IND_MSG_rsvd2));    \
		(dword) |= ((val << B_DLRX_IND_MSG_rsvd2) & M_DLRX_IND_MSG_rsvd2);    \
	} while (0)

#define DLRX_IND_MSG_rsvd2_clear_indirect(base, offset)	((*(base + O_DLRX_IND_MSG_rsvd2 + offset)) &= (~(M_DLRX_IND_MSG_rsvd2)))

#define DLRX_IND_MSG_rsvd2_clear_direct(dword)	((dword) &= (~(M_DLRX_IND_MSG_rsvd2)))

#define O_DLRX_IND_MSG_rsvd3 5
#define B_DLRX_IND_MSG_rsvd3 0
#define W_DLRX_IND_MSG_rsvd3 32
#define M_DLRX_IND_MSG_rsvd3 0xffffffff

#define DLRX_IND_MSG_rsvd3_get_indirect(base, offset)	((((*(base + O_DLRX_IND_MSG_rsvd3 + offset)) & M_DLRX_IND_MSG_rsvd3) >> B_DLRX_IND_MSG_rsvd3))

#define DLRX_IND_MSG_rsvd3_get_direct(dword)	((((dword) & M_DLRX_IND_MSG_rsvd3) >> B_DLRX_IND_MSG_rsvd3))

#define DLRX_IND_MSG_rsvd3_set_indirect(base, offset, val)    \
	do {                                                              \
		(*(base + O_DLRX_IND_MSG_rsvd3 + offset)) &= (~(M_DLRX_IND_MSG_rsvd3));    \
		(*(base + O_DLRX_IND_MSG_rsvd3 + offset)) |= ((val << B_DLRX_IND_MSG_rsvd3) & M_DLRX_IND_MSG_rsvd3);    \
	} while (0)

#define DLRX_IND_MSG_rsvd3_set_direct(dword, val)    \
	do {                                                               \
		(dword) &= (~(M_DLRX_IND_MSG_rsvd3));    \
		(dword) |= ((val << B_DLRX_IND_MSG_rsvd3) & M_DLRX_IND_MSG_rsvd3);    \
	} while (0)

#define DLRX_IND_MSG_rsvd3_clear_indirect(base, offset)	((*(base + O_DLRX_IND_MSG_rsvd3 + offset)) &= (~(M_DLRX_IND_MSG_rsvd3)))

#define DLRX_IND_MSG_rsvd3_clear_direct(dword)	((dword) &= (~(M_DLRX_IND_MSG_rsvd3)))

#define O_DLRX_IND_MSG_rsvd4 6
#define B_DLRX_IND_MSG_rsvd4 0
#define W_DLRX_IND_MSG_rsvd4 32
#define M_DLRX_IND_MSG_rsvd4 0xffffffff

#define DLRX_IND_MSG_rsvd4_get_indirect(base, offset)	((((*(base + O_DLRX_IND_MSG_rsvd4 + offset)) & M_DLRX_IND_MSG_rsvd4) >> B_DLRX_IND_MSG_rsvd4))

#define DLRX_IND_MSG_rsvd4_get_direct(dword)	((((dword) & M_DLRX_IND_MSG_rsvd4) >> B_DLRX_IND_MSG_rsvd4))

#define DLRX_IND_MSG_rsvd4_set_indirect(base, offset, val)    \
	do {                                                              \
		(*(base + O_DLRX_IND_MSG_rsvd4 + offset)) &= (~(M_DLRX_IND_MSG_rsvd4));    \
		(*(base + O_DLRX_IND_MSG_rsvd4 + offset)) |= ((val << B_DLRX_IND_MSG_rsvd4) & M_DLRX_IND_MSG_rsvd4);    \
	} while (0)

#define DLRX_IND_MSG_rsvd4_set_direct(dword, val)    \
	do {                                                               \
		(dword) &= (~(M_DLRX_IND_MSG_rsvd4));    \
		(dword) |= ((val << B_DLRX_IND_MSG_rsvd4) & M_DLRX_IND_MSG_rsvd4);    \
	} while (0)

#define DLRX_IND_MSG_rsvd4_clear_indirect(base, offset)	((*(base + O_DLRX_IND_MSG_rsvd4 + offset)) &= (~(M_DLRX_IND_MSG_rsvd4)))

#define DLRX_IND_MSG_rsvd4_clear_direct(dword)	((dword) &= (~(M_DLRX_IND_MSG_rsvd4)))

#define O_DLRX_IND_MSG_rsvd5 7
#define B_DLRX_IND_MSG_rsvd5 0
#define W_DLRX_IND_MSG_rsvd5 32
#define M_DLRX_IND_MSG_rsvd5 0xffffffff

#define DLRX_IND_MSG_rsvd5_get_indirect(base, offset)	((((*(base + O_DLRX_IND_MSG_rsvd5 + offset)) & M_DLRX_IND_MSG_rsvd5) >> B_DLRX_IND_MSG_rsvd5))

#define DLRX_IND_MSG_rsvd5_get_direct(dword)	((((dword) & M_DLRX_IND_MSG_rsvd5) >> B_DLRX_IND_MSG_rsvd5))

#define DLRX_IND_MSG_rsvd5_set_indirect(base, offset, val)    \
	do {                                                              \
		(*(base + O_DLRX_IND_MSG_rsvd5 + offset)) &= (~(M_DLRX_IND_MSG_rsvd5));    \
		(*(base + O_DLRX_IND_MSG_rsvd5 + offset)) |= ((val << B_DLRX_IND_MSG_rsvd5) & M_DLRX_IND_MSG_rsvd5);    \
	} while (0)

#define DLRX_IND_MSG_rsvd5_set_direct(dword, val)    \
	do {                                                               \
		(dword) &= (~(M_DLRX_IND_MSG_rsvd5));    \
		(dword) |= ((val << B_DLRX_IND_MSG_rsvd5) & M_DLRX_IND_MSG_rsvd5);    \
	} while (0)

#define DLRX_IND_MSG_rsvd5_clear_indirect(base, offset)	((*(base + O_DLRX_IND_MSG_rsvd5 + offset)) &= (~(M_DLRX_IND_MSG_rsvd5)))

#define DLRX_IND_MSG_rsvd5_clear_direct(dword)	((dword) &= (~(M_DLRX_IND_MSG_rsvd5)))

#define O_DLRX_IND_MSG_rsvd6 8
#define B_DLRX_IND_MSG_rsvd6 0
#define W_DLRX_IND_MSG_rsvd6 32
#define M_DLRX_IND_MSG_rsvd6 0xffffffff

#define DLRX_IND_MSG_rsvd6_get_indirect(base, offset)	((((*(base + O_DLRX_IND_MSG_rsvd6 + offset)) & M_DLRX_IND_MSG_rsvd6) >> B_DLRX_IND_MSG_rsvd6))

#define DLRX_IND_MSG_rsvd6_get_direct(dword)	((((dword) & M_DLRX_IND_MSG_rsvd6) >> B_DLRX_IND_MSG_rsvd6))

#define DLRX_IND_MSG_rsvd6_set_indirect(base, offset, val)    \
	do {                                                              \
		(*(base + O_DLRX_IND_MSG_rsvd6 + offset)) &= (~(M_DLRX_IND_MSG_rsvd6));    \
		(*(base + O_DLRX_IND_MSG_rsvd6 + offset)) |= ((val << B_DLRX_IND_MSG_rsvd6) & M_DLRX_IND_MSG_rsvd6);    \
	} while (0)

#define DLRX_IND_MSG_rsvd6_set_direct(dword, val)    \
	do {                                                               \
		(dword) &= (~(M_DLRX_IND_MSG_rsvd6));    \
		(dword) |= ((val << B_DLRX_IND_MSG_rsvd6) & M_DLRX_IND_MSG_rsvd6);    \
	} while (0)

#define DLRX_IND_MSG_rsvd6_clear_indirect(base, offset)	((*(base + O_DLRX_IND_MSG_rsvd6 + offset)) &= (~(M_DLRX_IND_MSG_rsvd6)))

#define DLRX_IND_MSG_rsvd6_clear_direct(dword)	((dword) &= (~(M_DLRX_IND_MSG_rsvd6)))

#define O_DLRX_IND_MSG_rsvd7 9
#define B_DLRX_IND_MSG_rsvd7 0
#define W_DLRX_IND_MSG_rsvd7 32
#define M_DLRX_IND_MSG_rsvd7 0xffffffff

#define DLRX_IND_MSG_rsvd7_get_indirect(base, offset)	((((*(base + O_DLRX_IND_MSG_rsvd7 + offset)) & M_DLRX_IND_MSG_rsvd7) >> B_DLRX_IND_MSG_rsvd7))

#define DLRX_IND_MSG_rsvd7_get_direct(dword)	((((dword) & M_DLRX_IND_MSG_rsvd7) >> B_DLRX_IND_MSG_rsvd7))

#define DLRX_IND_MSG_rsvd7_set_indirect(base, offset, val)    \
	do {                                                              \
		(*(base + O_DLRX_IND_MSG_rsvd7 + offset)) &= (~(M_DLRX_IND_MSG_rsvd7));    \
		(*(base + O_DLRX_IND_MSG_rsvd7 + offset)) |= ((val << B_DLRX_IND_MSG_rsvd7) & M_DLRX_IND_MSG_rsvd7);    \
	} while (0)

#define DLRX_IND_MSG_rsvd7_set_direct(dword, val)    \
	do {                                                               \
		(dword) &= (~(M_DLRX_IND_MSG_rsvd7));    \
		(dword) |= ((val << B_DLRX_IND_MSG_rsvd7) & M_DLRX_IND_MSG_rsvd7);    \
	} while (0)

#define DLRX_IND_MSG_rsvd7_clear_indirect(base, offset)	((*(base + O_DLRX_IND_MSG_rsvd7 + offset)) &= (~(M_DLRX_IND_MSG_rsvd7)))

#define DLRX_IND_MSG_rsvd7_clear_direct(dword)	((dword) &= (~(M_DLRX_IND_MSG_rsvd7)))

#define O_DLRX_IND_MSG_rsvd8 10
#define B_DLRX_IND_MSG_rsvd8 0
#define W_DLRX_IND_MSG_rsvd8 32
#define M_DLRX_IND_MSG_rsvd8 0xffffffff

#define DLRX_IND_MSG_rsvd8_get_indirect(base, offset)	((((*(base + O_DLRX_IND_MSG_rsvd8 + offset)) & M_DLRX_IND_MSG_rsvd8) >> B_DLRX_IND_MSG_rsvd8))

#define DLRX_IND_MSG_rsvd8_get_direct(dword)	((((dword) & M_DLRX_IND_MSG_rsvd8) >> B_DLRX_IND_MSG_rsvd8))

#define DLRX_IND_MSG_rsvd8_set_indirect(base, offset, val)    \
	do {                                                              \
		(*(base + O_DLRX_IND_MSG_rsvd8 + offset)) &= (~(M_DLRX_IND_MSG_rsvd8));    \
		(*(base + O_DLRX_IND_MSG_rsvd8 + offset)) |= ((val << B_DLRX_IND_MSG_rsvd8) & M_DLRX_IND_MSG_rsvd8);    \
	} while (0)

#define DLRX_IND_MSG_rsvd8_set_direct(dword, val)    \
	do {                                                               \
		(dword) &= (~(M_DLRX_IND_MSG_rsvd8));    \
		(dword) |= ((val << B_DLRX_IND_MSG_rsvd8) & M_DLRX_IND_MSG_rsvd8);    \
	} while (0)

#define DLRX_IND_MSG_rsvd8_clear_indirect(base, offset)	((*(base + O_DLRX_IND_MSG_rsvd8 + offset)) &= (~(M_DLRX_IND_MSG_rsvd8)))

#define DLRX_IND_MSG_rsvd8_clear_direct(dword)	((dword) &= (~(M_DLRX_IND_MSG_rsvd8)))

#define O_DLRX_IND_MSG_rsvd9 11
#define B_DLRX_IND_MSG_rsvd9 0
#define W_DLRX_IND_MSG_rsvd9 32
#define M_DLRX_IND_MSG_rsvd9 0xffffffff

#define DLRX_IND_MSG_rsvd9_get_indirect(base, offset)	((((*(base + O_DLRX_IND_MSG_rsvd9 + offset)) & M_DLRX_IND_MSG_rsvd9) >> B_DLRX_IND_MSG_rsvd9))

#define DLRX_IND_MSG_rsvd9_get_direct(dword)	((((dword) & M_DLRX_IND_MSG_rsvd9) >> B_DLRX_IND_MSG_rsvd9))

#define DLRX_IND_MSG_rsvd9_set_indirect(base, offset, val)    \
	do {                                                              \
		(*(base + O_DLRX_IND_MSG_rsvd9 + offset)) &= (~(M_DLRX_IND_MSG_rsvd9));    \
		(*(base + O_DLRX_IND_MSG_rsvd9 + offset)) |= ((val << B_DLRX_IND_MSG_rsvd9) & M_DLRX_IND_MSG_rsvd9);    \
	} while (0)

#define DLRX_IND_MSG_rsvd9_set_direct(dword, val)    \
	do {                                                               \
		(dword) &= (~(M_DLRX_IND_MSG_rsvd9));    \
		(dword) |= ((val << B_DLRX_IND_MSG_rsvd9) & M_DLRX_IND_MSG_rsvd9);    \
	} while (0)

#define DLRX_IND_MSG_rsvd9_clear_indirect(base, offset)	((*(base + O_DLRX_IND_MSG_rsvd9 + offset)) &= (~(M_DLRX_IND_MSG_rsvd9)))

#define DLRX_IND_MSG_rsvd9_clear_direct(dword)	((dword) &= (~(M_DLRX_IND_MSG_rsvd9)))

#define O_DLRX_IND_MSG_rsvd10 12
#define B_DLRX_IND_MSG_rsvd10 0
#define W_DLRX_IND_MSG_rsvd10 32
#define M_DLRX_IND_MSG_rsvd10 0xffffffff

#define DLRX_IND_MSG_rsvd10_get_indirect(base, offset)	((((*(base + O_DLRX_IND_MSG_rsvd10 + offset)) & M_DLRX_IND_MSG_rsvd10) >> B_DLRX_IND_MSG_rsvd10))

#define DLRX_IND_MSG_rsvd10_get_direct(dword)	((((dword) & M_DLRX_IND_MSG_rsvd10) >> B_DLRX_IND_MSG_rsvd10))

#define DLRX_IND_MSG_rsvd10_set_indirect(base, offset, val)    \
	do {                                                              \
		(*(base + O_DLRX_IND_MSG_rsvd10 + offset)) &= (~(M_DLRX_IND_MSG_rsvd10));    \
		(*(base + O_DLRX_IND_MSG_rsvd10 + offset)) |= ((val << B_DLRX_IND_MSG_rsvd10) & M_DLRX_IND_MSG_rsvd10);    \
	} while (0)

#define DLRX_IND_MSG_rsvd10_set_direct(dword, val)    \
	do {                                                               \
		(dword) &= (~(M_DLRX_IND_MSG_rsvd10));    \
		(dword) |= ((val << B_DLRX_IND_MSG_rsvd10) & M_DLRX_IND_MSG_rsvd10);    \
	} while (0)

#define DLRX_IND_MSG_rsvd10_clear_indirect(base, offset)	((*(base + O_DLRX_IND_MSG_rsvd10 + offset)) &= (~(M_DLRX_IND_MSG_rsvd10)))

#define DLRX_IND_MSG_rsvd10_clear_direct(dword)	((dword) &= (~(M_DLRX_IND_MSG_rsvd10)))

#define O_DLRX_IND_MSG_fw_rx_desc_byte_num 13
#define B_DLRX_IND_MSG_fw_rx_desc_byte_num 0
#define W_DLRX_IND_MSG_fw_rx_desc_byte_num 16
#define M_DLRX_IND_MSG_fw_rx_desc_byte_num 0x0000ffff

#define DLRX_IND_MSG_fw_rx_desc_byte_num_get_indirect(base, offset)	((((*(base + O_DLRX_IND_MSG_fw_rx_desc_byte_num + offset)) & M_DLRX_IND_MSG_fw_rx_desc_byte_num) >> B_DLRX_IND_MSG_fw_rx_desc_byte_num))

#define DLRX_IND_MSG_fw_rx_desc_byte_num_get_direct(dword)	((((dword) & M_DLRX_IND_MSG_fw_rx_desc_byte_num) >> B_DLRX_IND_MSG_fw_rx_desc_byte_num))

#define DLRX_IND_MSG_fw_rx_desc_byte_num_set_indirect(base, offset, val) \
	do {                                                              \
		(*(base + O_DLRX_IND_MSG_fw_rx_desc_byte_num + offset)) &= (~(M_DLRX_IND_MSG_fw_rx_desc_byte_num));    \
		(*(base + O_DLRX_IND_MSG_fw_rx_desc_byte_num + offset)) |= ((val << B_DLRX_IND_MSG_fw_rx_desc_byte_num) & M_DLRX_IND_MSG_fw_rx_desc_byte_num);    \
	} while (0)

#define DLRX_IND_MSG_fw_rx_desc_byte_num_set_direct(dword, val) \
	do {                                                               \
		(dword) &= (~(M_DLRX_IND_MSG_fw_rx_desc_byte_num));    \
		(dword) |= ((val << B_DLRX_IND_MSG_fw_rx_desc_byte_num) & M_DLRX_IND_MSG_fw_rx_desc_byte_num);    \
	} while (0)

#define DLRX_IND_MSG_fw_rx_desc_byte_num_clear_indirect(base, offset)	((*(base + O_DLRX_IND_MSG_fw_rx_desc_byte_num + offset)) &= (~(M_DLRX_IND_MSG_fw_rx_desc_byte_num)))

#define DLRX_IND_MSG_fw_rx_desc_byte_num_clear_direct(dword)	((dword) &= (~(M_DLRX_IND_MSG_fw_rx_desc_byte_num)))

#define O_DLRX_IND_MSG_rsvd11 13
#define B_DLRX_IND_MSG_rsvd11 16
#define W_DLRX_IND_MSG_rsvd11 16
#define M_DLRX_IND_MSG_rsvd11 0xffff0000

#define DLRX_IND_MSG_rsvd11_get_indirect(base, offset)	((((*(base + O_DLRX_IND_MSG_rsvd11 + offset)) & M_DLRX_IND_MSG_rsvd11) >> B_DLRX_IND_MSG_rsvd11))

#define DLRX_IND_MSG_rsvd11_get_direct(dword)	((((dword) & M_DLRX_IND_MSG_rsvd11) >> B_DLRX_IND_MSG_rsvd11))

#define DLRX_IND_MSG_rsvd11_set_indirect(base, offset, val) \
	do {                                                              \
		(*(base + O_DLRX_IND_MSG_rsvd11 + offset)) &= (~(M_DLRX_IND_MSG_rsvd11));    \
		(*(base + O_DLRX_IND_MSG_rsvd11 + offset)) |= ((val << B_DLRX_IND_MSG_rsvd11) & M_DLRX_IND_MSG_rsvd11);    \
	} while (0)

#define DLRX_IND_MSG_rsvd11_set_direct(dword, val) \
	do {                                                               \
		(dword) &= (~(M_DLRX_IND_MSG_rsvd11));    \
		(dword) |= ((val << B_DLRX_IND_MSG_rsvd11) & M_DLRX_IND_MSG_rsvd11);    \
	} while (0)

#define DLRX_IND_MSG_rsvd11_clear_indirect(base, offset)	((*(base + O_DLRX_IND_MSG_rsvd11 + offset)) &= (~(M_DLRX_IND_MSG_rsvd11)))

#define DLRX_IND_MSG_rsvd11_clear_direct(dword)	((dword) &= (~(M_DLRX_IND_MSG_rsvd11)))

#define O_FW_RX_DESC_BYTE_discard_msdu0 0
#define B_FW_RX_DESC_BYTE_discard_msdu0 0
#define W_FW_RX_DESC_BYTE_discard_msdu0 1
#define M_FW_RX_DESC_BYTE_discard_msdu0 0x00000001

#define FW_RX_DESC_BYTE_discard_msdu0_get_indirect(base, offset)	((((*(base + O_FW_RX_DESC_BYTE_discard_msdu0 + offset)) & M_FW_RX_DESC_BYTE_discard_msdu0) >> B_FW_RX_DESC_BYTE_discard_msdu0))

#define FW_RX_DESC_BYTE_discard_msdu0_get_direct(dword)	((((dword) & M_FW_RX_DESC_BYTE_discard_msdu0) >> B_FW_RX_DESC_BYTE_discard_msdu0))

#define FW_RX_DESC_BYTE_discard_msdu0_set_indirect(base, offset, val) \
	do {                                                              \
		(*(base + O_FW_RX_DESC_BYTE_discard_msdu0 + offset)) &= (~(M_FW_RX_DESC_BYTE_discard_msdu0));    \
		(*(base + O_FW_RX_DESC_BYTE_discard_msdu0 + offset)) |= ((val << B_FW_RX_DESC_BYTE_discard_msdu0) & M_FW_RX_DESC_BYTE_discard_msdu0);    \
	} while (0)

#define FW_RX_DESC_BYTE_discard_msdu0_set_direct(dword, val) \
	do {                                                               \
		(dword) &= (~(M_FW_RX_DESC_BYTE_discard_msdu0));    \
		(dword) |= ((val << B_FW_RX_DESC_BYTE_discard_msdu0) & M_FW_RX_DESC_BYTE_discard_msdu0);    \
	} while (0)

#define FW_RX_DESC_BYTE_discard_msdu0_clear_indirect(base, offset)	((*(base + O_FW_RX_DESC_BYTE_discard_msdu0 + offset)) &= (~(M_FW_RX_DESC_BYTE_discard_msdu0)))

#define FW_RX_DESC_BYTE_discard_msdu0_clear_direct(dword)	((dword) &= (~(M_FW_RX_DESC_BYTE_discard_msdu0)))

#define O_FW_RX_DESC_BYTE_forward_msdu0 0
#define B_FW_RX_DESC_BYTE_forward_msdu0 1
#define W_FW_RX_DESC_BYTE_forward_msdu0 1
#define M_FW_RX_DESC_BYTE_forward_msdu0 0x00000002

#define FW_RX_DESC_BYTE_forward_msdu0_get_indirect(base, offset)	((((*(base + O_FW_RX_DESC_BYTE_forward_msdu0 + offset)) & M_FW_RX_DESC_BYTE_forward_msdu0) >> B_FW_RX_DESC_BYTE_forward_msdu0))

#define FW_RX_DESC_BYTE_forward_msdu0_get_direct(dword)	((((dword) & M_FW_RX_DESC_BYTE_forward_msdu0) >> B_FW_RX_DESC_BYTE_forward_msdu0))

#define FW_RX_DESC_BYTE_forward_msdu0_set_indirect(base, offset, val) \
	do {                                                              \
		(*(base + O_FW_RX_DESC_BYTE_forward_msdu0 + offset)) &= (~(M_FW_RX_DESC_BYTE_forward_msdu0));    \
		(*(base + O_FW_RX_DESC_BYTE_forward_msdu0 + offset)) |= ((val << B_FW_RX_DESC_BYTE_forward_msdu0) & M_FW_RX_DESC_BYTE_forward_msdu0);    \
	} while (0)

#define FW_RX_DESC_BYTE_forward_msdu0_set_direct(dword, val) \
	do {                                                               \
		(dword) &= (~(M_FW_RX_DESC_BYTE_forward_msdu0));    \
		(dword) |= ((val << B_FW_RX_DESC_BYTE_forward_msdu0) & M_FW_RX_DESC_BYTE_forward_msdu0);    \
	} while (0)

#define FW_RX_DESC_BYTE_forward_msdu0_clear_indirect(base, offset)	((*(base + O_FW_RX_DESC_BYTE_forward_msdu0 + offset)) &= (~(M_FW_RX_DESC_BYTE_forward_msdu0)))

#define FW_RX_DESC_BYTE_forward_msdu0_clear_direct(dword)	((dword) &= (~(M_FW_RX_DESC_BYTE_forward_msdu0)))

#define O_FW_RX_DESC_BYTE_rsvd1_msdu0 0
#define B_FW_RX_DESC_BYTE_rsvd1_msdu0 2
#define W_FW_RX_DESC_BYTE_rsvd1_msdu0 3
#define M_FW_RX_DESC_BYTE_rsvd1_msdu0 0x0000001c

#define FW_RX_DESC_BYTE_rsvd1_msdu0_get_indirect(base, offset)	((((*(base + O_FW_RX_DESC_BYTE_rsvd1_msdu0 + offset)) & M_FW_RX_DESC_BYTE_rsvd1_msdu0) >> B_FW_RX_DESC_BYTE_rsvd1_msdu0))

#define FW_RX_DESC_BYTE_rsvd1_msdu0_get_direct(dword)	((((dword) & M_FW_RX_DESC_BYTE_rsvd1_msdu0) >> B_FW_RX_DESC_BYTE_rsvd1_msdu0))

#define FW_RX_DESC_BYTE_rsvd1_msdu0_set_indirect(base, offset, val) \
	do {                                                              \
		(*(base + O_FW_RX_DESC_BYTE_rsvd1_msdu0 + offset)) &= (~(M_FW_RX_DESC_BYTE_rsvd1_msdu0));    \
		(*(base + O_FW_RX_DESC_BYTE_rsvd1_msdu0 + offset)) |= ((val << B_FW_RX_DESC_BYTE_rsvd1_msdu0) & M_FW_RX_DESC_BYTE_rsvd1_msdu0);    \
	} while (0)

#define FW_RX_DESC_BYTE_rsvd1_msdu0_set_direct(dword, val) \
	do {                                                               \
		(dword) &= (~(M_FW_RX_DESC_BYTE_rsvd1_msdu0));    \
		(dword) |= ((val << B_FW_RX_DESC_BYTE_rsvd1_msdu0) & M_FW_RX_DESC_BYTE_rsvd1_msdu0);    \
	} while (0)

#define FW_RX_DESC_BYTE_rsvd1_msdu0_clear_indirect(base, offset)	((*(base + O_FW_RX_DESC_BYTE_rsvd1_msdu0 + offset)) &= (~(M_FW_RX_DESC_BYTE_rsvd1_msdu0)))

#define FW_RX_DESC_BYTE_rsvd1_msdu0_clear_direct(dword)	((dword) &= (~(M_FW_RX_DESC_BYTE_rsvd1_msdu0)))

#define O_FW_RX_DESC_BYTE_inspect_msdu0 0
#define B_FW_RX_DESC_BYTE_inspect_msdu0 5
#define W_FW_RX_DESC_BYTE_inspect_msdu0 1
#define M_FW_RX_DESC_BYTE_inspect_msdu0 0x00000020

#define FW_RX_DESC_BYTE_inspect_msdu0_get_indirect(base, offset)	((((*(base + O_FW_RX_DESC_BYTE_inspect_msdu0 + offset)) & M_FW_RX_DESC_BYTE_inspect_msdu0) >> B_FW_RX_DESC_BYTE_inspect_msdu0))

#define FW_RX_DESC_BYTE_inspect_msdu0_get_direct(dword)	((((dword) & M_FW_RX_DESC_BYTE_inspect_msdu0) >> B_FW_RX_DESC_BYTE_inspect_msdu0))

#define FW_RX_DESC_BYTE_inspect_msdu0_set_indirect(base, offset, val) \
	do {                                                              \
		(*(base + O_FW_RX_DESC_BYTE_inspect_msdu0 + offset)) &= (~(M_FW_RX_DESC_BYTE_inspect_msdu0));    \
		(*(base + O_FW_RX_DESC_BYTE_inspect_msdu0 + offset)) |= ((val << B_FW_RX_DESC_BYTE_inspect_msdu0) & M_FW_RX_DESC_BYTE_inspect_msdu0);    \
	} while (0)

#define FW_RX_DESC_BYTE_inspect_msdu0_set_direct(dword, val) \
	do {                                                               \
		(dword) &= (~(M_FW_RX_DESC_BYTE_inspect_msdu0));    \
		(dword) |= ((val << B_FW_RX_DESC_BYTE_inspect_msdu0) & M_FW_RX_DESC_BYTE_inspect_msdu0);    \
	} while (0)

#define FW_RX_DESC_BYTE_inspect_msdu0_clear_indirect(base, offset)	((*(base + O_FW_RX_DESC_BYTE_inspect_msdu0 + offset)) &= (~(M_FW_RX_DESC_BYTE_inspect_msdu0)))

#define FW_RX_DESC_BYTE_inspect_msdu0_clear_direct(dword)	((dword) &= (~(M_FW_RX_DESC_BYTE_inspect_msdu0)))

#define O_FW_RX_DESC_BYTE_rsvd2_msdu0 0
#define B_FW_RX_DESC_BYTE_rsvd2_msdu0 6
#define W_FW_RX_DESC_BYTE_rsvd2_msdu0 2
#define M_FW_RX_DESC_BYTE_rsvd2_msdu0 0x000000c0

#define FW_RX_DESC_BYTE_rsvd2_msdu0_get_indirect(base, offset)	((((*(base + O_FW_RX_DESC_BYTE_rsvd2_msdu0 + offset)) & M_FW_RX_DESC_BYTE_rsvd2_msdu0) >> B_FW_RX_DESC_BYTE_rsvd2_msdu0))

#define FW_RX_DESC_BYTE_rsvd2_msdu0_get_direct(dword)	((((dword) & M_FW_RX_DESC_BYTE_rsvd2_msdu0) >> B_FW_RX_DESC_BYTE_rsvd2_msdu0))

#define FW_RX_DESC_BYTE_rsvd2_msdu0_set_indirect(base, offset, val) \
	do {                                                              \
		(*(base + O_FW_RX_DESC_BYTE_rsvd2_msdu0 + offset)) &= (~(M_FW_RX_DESC_BYTE_rsvd2_msdu0));    \
		(*(base + O_FW_RX_DESC_BYTE_rsvd2_msdu0 + offset)) |= ((val << B_FW_RX_DESC_BYTE_rsvd2_msdu0) & M_FW_RX_DESC_BYTE_rsvd2_msdu0);    \
	} while (0)

#define FW_RX_DESC_BYTE_rsvd2_msdu0_set_direct(dword, val) \
	do {                                                               \
		(dword) &= (~(M_FW_RX_DESC_BYTE_rsvd2_msdu0));    \
		(dword) |= ((val << B_FW_RX_DESC_BYTE_rsvd2_msdu0) & M_FW_RX_DESC_BYTE_rsvd2_msdu0);    \
	} while (0)

#define FW_RX_DESC_BYTE_rsvd2_msdu0_clear_indirect(base, offset)	((*(base + O_FW_RX_DESC_BYTE_rsvd2_msdu0 + offset)) &= (~(M_FW_RX_DESC_BYTE_rsvd2_msdu0)))

#define FW_RX_DESC_BYTE_rsvd2_msdu0_clear_direct(dword)	((dword) &= (~(M_FW_RX_DESC_BYTE_rsvd2_msdu0)))

#define O_FW_RX_DESC_BYTE_discard_msdu1 0
#define B_FW_RX_DESC_BYTE_discard_msdu1 8
#define W_FW_RX_DESC_BYTE_discard_msdu1 1
#define M_FW_RX_DESC_BYTE_discard_msdu1 0x00000100

#define FW_RX_DESC_BYTE_discard_msdu1_get_indirect(base, offset)	((((*(base + O_FW_RX_DESC_BYTE_discard_msdu1 + offset)) & M_FW_RX_DESC_BYTE_discard_msdu1) >> B_FW_RX_DESC_BYTE_discard_msdu1))

#define FW_RX_DESC_BYTE_discard_msdu1_get_direct(dword)	((((dword) & M_FW_RX_DESC_BYTE_discard_msdu1) >> B_FW_RX_DESC_BYTE_discard_msdu1))

#define FW_RX_DESC_BYTE_discard_msdu1_set_indirect(base, offset, val) \
	do {                                                              \
		(*(base + O_FW_RX_DESC_BYTE_discard_msdu1 + offset)) &= (~(M_FW_RX_DESC_BYTE_discard_msdu1));    \
		(*(base + O_FW_RX_DESC_BYTE_discard_msdu1 + offset)) |= ((val << B_FW_RX_DESC_BYTE_discard_msdu1) & M_FW_RX_DESC_BYTE_discard_msdu1);    \
	} while (0)

#define FW_RX_DESC_BYTE_discard_msdu1_set_direct(dword, val) \
	do {                                                               \
		(dword) &= (~(M_FW_RX_DESC_BYTE_discard_msdu1));    \
		(dword) |= ((val << B_FW_RX_DESC_BYTE_discard_msdu1) & M_FW_RX_DESC_BYTE_discard_msdu1);    \
	} while (0)

#define FW_RX_DESC_BYTE_discard_msdu1_clear_indirect(base, offset)	((*(base + O_FW_RX_DESC_BYTE_discard_msdu1 + offset)) &= (~(M_FW_RX_DESC_BYTE_discard_msdu1)))

#define FW_RX_DESC_BYTE_discard_msdu1_clear_direct(dword)	((dword) &= (~(M_FW_RX_DESC_BYTE_discard_msdu1)))

#define O_FW_RX_DESC_BYTE_forward_msdu1 0
#define B_FW_RX_DESC_BYTE_forward_msdu1 9
#define W_FW_RX_DESC_BYTE_forward_msdu1 1
#define M_FW_RX_DESC_BYTE_forward_msdu1 0x00000200

#define FW_RX_DESC_BYTE_forward_msdu1_get_indirect(base, offset)	((((*(base + O_FW_RX_DESC_BYTE_forward_msdu1 + offset)) & M_FW_RX_DESC_BYTE_forward_msdu1) >> B_FW_RX_DESC_BYTE_forward_msdu1))

#define FW_RX_DESC_BYTE_forward_msdu1_get_direct(dword)	((((dword) & M_FW_RX_DESC_BYTE_forward_msdu1) >> B_FW_RX_DESC_BYTE_forward_msdu1))

#define FW_RX_DESC_BYTE_forward_msdu1_set_indirect(base, offset, val) \
	do {                                                              \
		(*(base + O_FW_RX_DESC_BYTE_forward_msdu1 + offset)) &= (~(M_FW_RX_DESC_BYTE_forward_msdu1));    \
		(*(base + O_FW_RX_DESC_BYTE_forward_msdu1 + offset)) |= ((val << B_FW_RX_DESC_BYTE_forward_msdu1) & M_FW_RX_DESC_BYTE_forward_msdu1);    \
	} while (0)

#define FW_RX_DESC_BYTE_forward_msdu1_set_direct(dword, val) \
	do {                                                               \
		(dword) &= (~(M_FW_RX_DESC_BYTE_forward_msdu1));    \
		(dword) |= ((val << B_FW_RX_DESC_BYTE_forward_msdu1) & M_FW_RX_DESC_BYTE_forward_msdu1);    \
	} while (0)

#define FW_RX_DESC_BYTE_forward_msdu1_clear_indirect(base, offset)	((*(base + O_FW_RX_DESC_BYTE_forward_msdu1 + offset)) &= (~(M_FW_RX_DESC_BYTE_forward_msdu1)))

#define FW_RX_DESC_BYTE_forward_msdu1_clear_direct(dword)	((dword) &= (~(M_FW_RX_DESC_BYTE_forward_msdu1)))

#define O_FW_RX_DESC_BYTE_rsvd1_msdu1 0
#define B_FW_RX_DESC_BYTE_rsvd1_msdu1 10
#define W_FW_RX_DESC_BYTE_rsvd1_msdu1 3
#define M_FW_RX_DESC_BYTE_rsvd1_msdu1 0x00001c00

#define FW_RX_DESC_BYTE_rsvd1_msdu1_get_indirect(base, offset)	((((*(base + O_FW_RX_DESC_BYTE_rsvd1_msdu1 + offset)) & M_FW_RX_DESC_BYTE_rsvd1_msdu1) >> B_FW_RX_DESC_BYTE_rsvd1_msdu1))

#define FW_RX_DESC_BYTE_rsvd1_msdu1_get_direct(dword)	((((dword) & M_FW_RX_DESC_BYTE_rsvd1_msdu1) >> B_FW_RX_DESC_BYTE_rsvd1_msdu1))

#define FW_RX_DESC_BYTE_rsvd1_msdu1_set_indirect(base, offset, val) \
	do {                                                              \
		(*(base + O_FW_RX_DESC_BYTE_rsvd1_msdu1 + offset)) &= (~(M_FW_RX_DESC_BYTE_rsvd1_msdu1));    \
		(*(base + O_FW_RX_DESC_BYTE_rsvd1_msdu1 + offset)) |= ((val << B_FW_RX_DESC_BYTE_rsvd1_msdu1) & M_FW_RX_DESC_BYTE_rsvd1_msdu1);    \
	} while (0)

#define FW_RX_DESC_BYTE_rsvd1_msdu1_set_direct(dword, val) \
	do {                                                               \
		(dword) &= (~(M_FW_RX_DESC_BYTE_rsvd1_msdu1));    \
		(dword) |= ((val << B_FW_RX_DESC_BYTE_rsvd1_msdu1) & M_FW_RX_DESC_BYTE_rsvd1_msdu1);    \
	} while (0)

#define FW_RX_DESC_BYTE_rsvd1_msdu1_clear_indirect(base, offset)	((*(base + O_FW_RX_DESC_BYTE_rsvd1_msdu1 + offset)) &= (~(M_FW_RX_DESC_BYTE_rsvd1_msdu1)))

#define FW_RX_DESC_BYTE_rsvd1_msdu1_clear_direct(dword)	((dword) &= (~(M_FW_RX_DESC_BYTE_rsvd1_msdu1)))

#define O_FW_RX_DESC_BYTE_inspect_msdu1 0
#define B_FW_RX_DESC_BYTE_inspect_msdu1 13
#define W_FW_RX_DESC_BYTE_inspect_msdu1 1
#define M_FW_RX_DESC_BYTE_inspect_msdu1 0x00002000

#define FW_RX_DESC_BYTE_inspect_msdu1_get_indirect(base, offset)	((((*(base + O_FW_RX_DESC_BYTE_inspect_msdu1 + offset)) & M_FW_RX_DESC_BYTE_inspect_msdu1) >> B_FW_RX_DESC_BYTE_inspect_msdu1))

#define FW_RX_DESC_BYTE_inspect_msdu1_get_direct(dword)	((((dword) & M_FW_RX_DESC_BYTE_inspect_msdu1) >> B_FW_RX_DESC_BYTE_inspect_msdu1))

#define FW_RX_DESC_BYTE_inspect_msdu1_set_indirect(base, offset, val) \
	do {                                                              \
		(*(base + O_FW_RX_DESC_BYTE_inspect_msdu1 + offset)) &= (~(M_FW_RX_DESC_BYTE_inspect_msdu1));    \
		(*(base + O_FW_RX_DESC_BYTE_inspect_msdu1 + offset)) |= ((val << B_FW_RX_DESC_BYTE_inspect_msdu1) & M_FW_RX_DESC_BYTE_inspect_msdu1);    \
	} while (0)

#define FW_RX_DESC_BYTE_inspect_msdu1_set_direct(dword, val) \
	do {                                                               \
		(dword) &= (~(M_FW_RX_DESC_BYTE_inspect_msdu1));    \
		(dword) |= ((val << B_FW_RX_DESC_BYTE_inspect_msdu1) & M_FW_RX_DESC_BYTE_inspect_msdu1);    \
	} while (0)

#define FW_RX_DESC_BYTE_inspect_msdu1_clear_indirect(base, offset)	((*(base + O_FW_RX_DESC_BYTE_inspect_msdu1 + offset)) &= (~(M_FW_RX_DESC_BYTE_inspect_msdu1)))

#define FW_RX_DESC_BYTE_inspect_msdu1_clear_direct(dword)	((dword) &= (~(M_FW_RX_DESC_BYTE_inspect_msdu1)))

#define O_FW_RX_DESC_BYTE_rsvd2_msdu1 0
#define B_FW_RX_DESC_BYTE_rsvd2_msdu1 14
#define W_FW_RX_DESC_BYTE_rsvd2_msdu1 2
#define M_FW_RX_DESC_BYTE_rsvd2_msdu1 0x0000c000

#define FW_RX_DESC_BYTE_rsvd2_msdu1_get_indirect(base, offset)	((((*(base + O_FW_RX_DESC_BYTE_rsvd2_msdu1 + offset)) & M_FW_RX_DESC_BYTE_rsvd2_msdu1) >> B_FW_RX_DESC_BYTE_rsvd2_msdu1))

#define FW_RX_DESC_BYTE_rsvd2_msdu1_get_direct(dword)	((((dword) & M_FW_RX_DESC_BYTE_rsvd2_msdu1) >> B_FW_RX_DESC_BYTE_rsvd2_msdu1))

#define FW_RX_DESC_BYTE_rsvd2_msdu1_set_indirect(base, offset, val) \
	do {                                                              \
		(*(base + O_FW_RX_DESC_BYTE_rsvd2_msdu1 + offset)) &= (~(M_FW_RX_DESC_BYTE_rsvd2_msdu1));    \
		(*(base + O_FW_RX_DESC_BYTE_rsvd2_msdu1 + offset)) |= ((val << B_FW_RX_DESC_BYTE_rsvd2_msdu1) & M_FW_RX_DESC_BYTE_rsvd2_msdu1);    \
	} while (0)

#define FW_RX_DESC_BYTE_rsvd2_msdu1_set_direct(dword, val) \
	do {                                                               \
		(dword) &= (~(M_FW_RX_DESC_BYTE_rsvd2_msdu1));    \
		(dword) |= ((val << B_FW_RX_DESC_BYTE_rsvd2_msdu1) & M_FW_RX_DESC_BYTE_rsvd2_msdu1);    \
	} while (0)

#define FW_RX_DESC_BYTE_rsvd2_msdu1_clear_indirect(base, offset)	((*(base + O_FW_RX_DESC_BYTE_rsvd2_msdu1 + offset)) &= (~(M_FW_RX_DESC_BYTE_rsvd2_msdu1)))

#define FW_RX_DESC_BYTE_rsvd2_msdu1_clear_direct(dword)	((dword) &= (~(M_FW_RX_DESC_BYTE_rsvd2_msdu1)))

#define O_FW_RX_DESC_BYTE_discard_msdu2 0
#define B_FW_RX_DESC_BYTE_discard_msdu2 16
#define W_FW_RX_DESC_BYTE_discard_msdu2 1
#define M_FW_RX_DESC_BYTE_discard_msdu2 0x00010000

#define FW_RX_DESC_BYTE_discard_msdu2_get_indirect(base, offset)	((((*(base + O_FW_RX_DESC_BYTE_discard_msdu2 + offset)) & M_FW_RX_DESC_BYTE_discard_msdu2) >> B_FW_RX_DESC_BYTE_discard_msdu2))

#define FW_RX_DESC_BYTE_discard_msdu2_get_direct(dword)	((((dword) & M_FW_RX_DESC_BYTE_discard_msdu2) >> B_FW_RX_DESC_BYTE_discard_msdu2))

#define FW_RX_DESC_BYTE_discard_msdu2_set_indirect(base, offset, val) \
	do {                                                              \
		(*(base + O_FW_RX_DESC_BYTE_discard_msdu2 + offset)) &= (~(M_FW_RX_DESC_BYTE_discard_msdu2));    \
		(*(base + O_FW_RX_DESC_BYTE_discard_msdu2 + offset)) |= ((val << B_FW_RX_DESC_BYTE_discard_msdu2) & M_FW_RX_DESC_BYTE_discard_msdu2);    \
	} while (0)

#define FW_RX_DESC_BYTE_discard_msdu2_set_direct(dword, val) \
	do {                                                               \
		(dword) &= (~(M_FW_RX_DESC_BYTE_discard_msdu2));    \
		(dword) |= ((val << B_FW_RX_DESC_BYTE_discard_msdu2) & M_FW_RX_DESC_BYTE_discard_msdu2);    \
	} while (0)

#define FW_RX_DESC_BYTE_discard_msdu2_clear_indirect(base, offset)	((*(base + O_FW_RX_DESC_BYTE_discard_msdu2 + offset)) &= (~(M_FW_RX_DESC_BYTE_discard_msdu2)))

#define FW_RX_DESC_BYTE_discard_msdu2_clear_direct(dword)	((dword) &= (~(M_FW_RX_DESC_BYTE_discard_msdu2)))

#define O_FW_RX_DESC_BYTE_forward_msdu2 0
#define B_FW_RX_DESC_BYTE_forward_msdu2 17
#define W_FW_RX_DESC_BYTE_forward_msdu2 1
#define M_FW_RX_DESC_BYTE_forward_msdu2 0x00020000

#define FW_RX_DESC_BYTE_forward_msdu2_get_indirect(base, offset)	((((*(base + O_FW_RX_DESC_BYTE_forward_msdu2 + offset)) & M_FW_RX_DESC_BYTE_forward_msdu2) >> B_FW_RX_DESC_BYTE_forward_msdu2))

#define FW_RX_DESC_BYTE_forward_msdu2_get_direct(dword)	((((dword) & M_FW_RX_DESC_BYTE_forward_msdu2) >> B_FW_RX_DESC_BYTE_forward_msdu2))

#define FW_RX_DESC_BYTE_forward_msdu2_set_indirect(base, offset, val) \
	do {                                                              \
		(*(base + O_FW_RX_DESC_BYTE_forward_msdu2 + offset)) &= (~(M_FW_RX_DESC_BYTE_forward_msdu2));    \
		(*(base + O_FW_RX_DESC_BYTE_forward_msdu2 + offset)) |= ((val << B_FW_RX_DESC_BYTE_forward_msdu2) & M_FW_RX_DESC_BYTE_forward_msdu2);    \
	} while (0)

#define FW_RX_DESC_BYTE_forward_msdu2_set_direct(dword, val) \
	do {                                                               \
		(dword) &= (~(M_FW_RX_DESC_BYTE_forward_msdu2));    \
		(dword) |= ((val << B_FW_RX_DESC_BYTE_forward_msdu2) & M_FW_RX_DESC_BYTE_forward_msdu2);    \
	} while (0)

#define FW_RX_DESC_BYTE_forward_msdu2_clear_indirect(base, offset)	((*(base + O_FW_RX_DESC_BYTE_forward_msdu2 + offset)) &= (~(M_FW_RX_DESC_BYTE_forward_msdu2)))

#define FW_RX_DESC_BYTE_forward_msdu2_clear_direct(dword)	((dword) &= (~(M_FW_RX_DESC_BYTE_forward_msdu2)))

#define O_FW_RX_DESC_BYTE_rsvd1_msdu2 0
#define B_FW_RX_DESC_BYTE_rsvd1_msdu2 18
#define W_FW_RX_DESC_BYTE_rsvd1_msdu2 3
#define M_FW_RX_DESC_BYTE_rsvd1_msdu2 0x001c0000

#define FW_RX_DESC_BYTE_rsvd1_msdu2_get_indirect(base, offset)	((((*(base + O_FW_RX_DESC_BYTE_rsvd1_msdu2 + offset)) & M_FW_RX_DESC_BYTE_rsvd1_msdu2) >> B_FW_RX_DESC_BYTE_rsvd1_msdu2))

#define FW_RX_DESC_BYTE_rsvd1_msdu2_get_direct(dword)	((((dword) & M_FW_RX_DESC_BYTE_rsvd1_msdu2) >> B_FW_RX_DESC_BYTE_rsvd1_msdu2))

#define FW_RX_DESC_BYTE_rsvd1_msdu2_set_indirect(base, offset, val) \
	do {                                                              \
		(*(base + O_FW_RX_DESC_BYTE_rsvd1_msdu2 + offset)) &= (~(M_FW_RX_DESC_BYTE_rsvd1_msdu2));    \
		(*(base + O_FW_RX_DESC_BYTE_rsvd1_msdu2 + offset)) |= ((val << B_FW_RX_DESC_BYTE_rsvd1_msdu2) & M_FW_RX_DESC_BYTE_rsvd1_msdu2);    \
	} while (0)

#define FW_RX_DESC_BYTE_rsvd1_msdu2_set_direct(dword, val) \
	do {                                                               \
		(dword) &= (~(M_FW_RX_DESC_BYTE_rsvd1_msdu2));    \
		(dword) |= ((val << B_FW_RX_DESC_BYTE_rsvd1_msdu2) & M_FW_RX_DESC_BYTE_rsvd1_msdu2);    \
	} while (0)

#define FW_RX_DESC_BYTE_rsvd1_msdu2_clear_indirect(base, offset)	((*(base + O_FW_RX_DESC_BYTE_rsvd1_msdu2 + offset)) &= (~(M_FW_RX_DESC_BYTE_rsvd1_msdu2)))

#define FW_RX_DESC_BYTE_rsvd1_msdu2_clear_direct(dword)	((dword) &= (~(M_FW_RX_DESC_BYTE_rsvd1_msdu2)))

#define O_FW_RX_DESC_BYTE_inspect_msdu2 0
#define B_FW_RX_DESC_BYTE_inspect_msdu2 21
#define W_FW_RX_DESC_BYTE_inspect_msdu2 1
#define M_FW_RX_DESC_BYTE_inspect_msdu2 0x00200000

#define FW_RX_DESC_BYTE_inspect_msdu2_get_indirect(base, offset)	((((*(base + O_FW_RX_DESC_BYTE_inspect_msdu2 + offset)) & M_FW_RX_DESC_BYTE_inspect_msdu2) >> B_FW_RX_DESC_BYTE_inspect_msdu2))

#define FW_RX_DESC_BYTE_inspect_msdu2_get_direct(dword)	((((dword) & M_FW_RX_DESC_BYTE_inspect_msdu2) >> B_FW_RX_DESC_BYTE_inspect_msdu2))

#define FW_RX_DESC_BYTE_inspect_msdu2_set_indirect(base, offset, val) \
	do {                                                              \
		(*(base + O_FW_RX_DESC_BYTE_inspect_msdu2 + offset)) &= (~(M_FW_RX_DESC_BYTE_inspect_msdu2));    \
		(*(base + O_FW_RX_DESC_BYTE_inspect_msdu2 + offset)) |= ((val << B_FW_RX_DESC_BYTE_inspect_msdu2) & M_FW_RX_DESC_BYTE_inspect_msdu2);    \
	} while (0)

#define FW_RX_DESC_BYTE_inspect_msdu2_set_direct(dword, val) \
	do {                                                               \
		(dword) &= (~(M_FW_RX_DESC_BYTE_inspect_msdu2));    \
		(dword) |= ((val << B_FW_RX_DESC_BYTE_inspect_msdu2) & M_FW_RX_DESC_BYTE_inspect_msdu2);    \
	} while (0)

#define FW_RX_DESC_BYTE_inspect_msdu2_clear_indirect(base, offset)	((*(base + O_FW_RX_DESC_BYTE_inspect_msdu2 + offset)) &= (~(M_FW_RX_DESC_BYTE_inspect_msdu2)))

#define FW_RX_DESC_BYTE_inspect_msdu2_clear_direct(dword)	((dword) &= (~(M_FW_RX_DESC_BYTE_inspect_msdu2)))

#define O_FW_RX_DESC_BYTE_rsvd2_msdu2 0
#define B_FW_RX_DESC_BYTE_rsvd2_msdu2 22
#define W_FW_RX_DESC_BYTE_rsvd2_msdu2 2
#define M_FW_RX_DESC_BYTE_rsvd2_msdu2 0x00c00000

#define FW_RX_DESC_BYTE_rsvd2_msdu2_get_indirect(base, offset)	((((*(base + O_FW_RX_DESC_BYTE_rsvd2_msdu2 + offset)) & M_FW_RX_DESC_BYTE_rsvd2_msdu2) >> B_FW_RX_DESC_BYTE_rsvd2_msdu2))

#define FW_RX_DESC_BYTE_rsvd2_msdu2_get_direct(dword)	((((dword) & M_FW_RX_DESC_BYTE_rsvd2_msdu2) >> B_FW_RX_DESC_BYTE_rsvd2_msdu2))

#define FW_RX_DESC_BYTE_rsvd2_msdu2_set_indirect(base, offset, val) \
	do {                                                              \
		(*(base + O_FW_RX_DESC_BYTE_rsvd2_msdu2 + offset)) &= (~(M_FW_RX_DESC_BYTE_rsvd2_msdu2));    \
		(*(base + O_FW_RX_DESC_BYTE_rsvd2_msdu2 + offset)) |= ((val << B_FW_RX_DESC_BYTE_rsvd2_msdu2) & M_FW_RX_DESC_BYTE_rsvd2_msdu2);    \
	} while (0)

#define FW_RX_DESC_BYTE_rsvd2_msdu2_set_direct(dword, val) \
	do {                                                               \
		(dword) &= (~(M_FW_RX_DESC_BYTE_rsvd2_msdu2));    \
		(dword) |= ((val << B_FW_RX_DESC_BYTE_rsvd2_msdu2) & M_FW_RX_DESC_BYTE_rsvd2_msdu2);    \
	} while (0)

#define FW_RX_DESC_BYTE_rsvd2_msdu2_clear_indirect(base, offset)	((*(base + O_FW_RX_DESC_BYTE_rsvd2_msdu2 + offset)) &= (~(M_FW_RX_DESC_BYTE_rsvd2_msdu2)))

#define FW_RX_DESC_BYTE_rsvd2_msdu2_clear_direct(dword)	((dword) &= (~(M_FW_RX_DESC_BYTE_rsvd2_msdu2)))

#define O_FW_RX_DESC_BYTE_discard_msdu3 0
#define B_FW_RX_DESC_BYTE_discard_msdu3 24
#define W_FW_RX_DESC_BYTE_discard_msdu3 1
#define M_FW_RX_DESC_BYTE_discard_msdu3 0x01000000

#define FW_RX_DESC_BYTE_discard_msdu3_get_indirect(base, offset)	((((*(base + O_FW_RX_DESC_BYTE_discard_msdu3 + offset)) & M_FW_RX_DESC_BYTE_discard_msdu3) >> B_FW_RX_DESC_BYTE_discard_msdu3))

#define FW_RX_DESC_BYTE_discard_msdu3_get_direct(dword)	((((dword) & M_FW_RX_DESC_BYTE_discard_msdu3) >> B_FW_RX_DESC_BYTE_discard_msdu3))

#define FW_RX_DESC_BYTE_discard_msdu3_set_indirect(base, offset, val) \
	do {                                                              \
		(*(base + O_FW_RX_DESC_BYTE_discard_msdu3 + offset)) &= (~(M_FW_RX_DESC_BYTE_discard_msdu3));    \
		(*(base + O_FW_RX_DESC_BYTE_discard_msdu3 + offset)) |= ((val << B_FW_RX_DESC_BYTE_discard_msdu3) & M_FW_RX_DESC_BYTE_discard_msdu3);    \
	} while (0)

#define FW_RX_DESC_BYTE_discard_msdu3_set_direct(dword, val) \
	do {                                                               \
		(dword) &= (~(M_FW_RX_DESC_BYTE_discard_msdu3));    \
		(dword) |= ((val << B_FW_RX_DESC_BYTE_discard_msdu3) & M_FW_RX_DESC_BYTE_discard_msdu3);    \
	} while (0)

#define FW_RX_DESC_BYTE_discard_msdu3_clear_indirect(base, offset)	((*(base + O_FW_RX_DESC_BYTE_discard_msdu3 + offset)) &= (~(M_FW_RX_DESC_BYTE_discard_msdu3)))

#define FW_RX_DESC_BYTE_discard_msdu3_clear_direct(dword)	((dword) &= (~(M_FW_RX_DESC_BYTE_discard_msdu3)))

#define O_FW_RX_DESC_BYTE_forward_msdu3 0
#define B_FW_RX_DESC_BYTE_forward_msdu3 25
#define W_FW_RX_DESC_BYTE_forward_msdu3 1
#define M_FW_RX_DESC_BYTE_forward_msdu3 0x02000000

#define FW_RX_DESC_BYTE_forward_msdu3_get_indirect(base, offset)	((((*(base + O_FW_RX_DESC_BYTE_forward_msdu3 + offset)) & M_FW_RX_DESC_BYTE_forward_msdu3) >> B_FW_RX_DESC_BYTE_forward_msdu3))

#define FW_RX_DESC_BYTE_forward_msdu3_get_direct(dword)	((((dword) & M_FW_RX_DESC_BYTE_forward_msdu3) >> B_FW_RX_DESC_BYTE_forward_msdu3))

#define FW_RX_DESC_BYTE_forward_msdu3_set_indirect(base, offset, val) \
	do {                                                              \
		(*(base + O_FW_RX_DESC_BYTE_forward_msdu3 + offset)) &= (~(M_FW_RX_DESC_BYTE_forward_msdu3));    \
		(*(base + O_FW_RX_DESC_BYTE_forward_msdu3 + offset)) |= ((val << B_FW_RX_DESC_BYTE_forward_msdu3) & M_FW_RX_DESC_BYTE_forward_msdu3);    \
	} while (0)

#define FW_RX_DESC_BYTE_forward_msdu3_set_direct(dword, val) \
	do {                                                               \
		(dword) &= (~(M_FW_RX_DESC_BYTE_forward_msdu3));    \
		(dword) |= ((val << B_FW_RX_DESC_BYTE_forward_msdu3) & M_FW_RX_DESC_BYTE_forward_msdu3);    \
	} while (0)

#define FW_RX_DESC_BYTE_forward_msdu3_clear_indirect(base, offset)	((*(base + O_FW_RX_DESC_BYTE_forward_msdu3 + offset)) &= (~(M_FW_RX_DESC_BYTE_forward_msdu3)))

#define FW_RX_DESC_BYTE_forward_msdu3_clear_direct(dword)	((dword) &= (~(M_FW_RX_DESC_BYTE_forward_msdu3)))

#define O_FW_RX_DESC_BYTE_rsvd1_msdu3 0
#define B_FW_RX_DESC_BYTE_rsvd1_msdu3 26
#define W_FW_RX_DESC_BYTE_rsvd1_msdu3 3
#define M_FW_RX_DESC_BYTE_rsvd1_msdu3 0x1c000000

#define FW_RX_DESC_BYTE_rsvd1_msdu3_get_indirect(base, offset)	((((*(base + O_FW_RX_DESC_BYTE_rsvd1_msdu3 + offset)) & M_FW_RX_DESC_BYTE_rsvd1_msdu3) >> B_FW_RX_DESC_BYTE_rsvd1_msdu3))

#define FW_RX_DESC_BYTE_rsvd1_msdu3_get_direct(dword)	((((dword) & M_FW_RX_DESC_BYTE_rsvd1_msdu3) >> B_FW_RX_DESC_BYTE_rsvd1_msdu3))

#define FW_RX_DESC_BYTE_rsvd1_msdu3_set_indirect(base, offset, val) \
	do {                                                              \
		(*(base + O_FW_RX_DESC_BYTE_rsvd1_msdu3 + offset)) &= (~(M_FW_RX_DESC_BYTE_rsvd1_msdu3));    \
		(*(base + O_FW_RX_DESC_BYTE_rsvd1_msdu3 + offset)) |= ((val << B_FW_RX_DESC_BYTE_rsvd1_msdu3) & M_FW_RX_DESC_BYTE_rsvd1_msdu3);    \
	} while (0)

#define FW_RX_DESC_BYTE_rsvd1_msdu3_set_direct(dword, val) \
	do {                                                               \
		(dword) &= (~(M_FW_RX_DESC_BYTE_rsvd1_msdu3));    \
		(dword) |= ((val << B_FW_RX_DESC_BYTE_rsvd1_msdu3) & M_FW_RX_DESC_BYTE_rsvd1_msdu3);    \
	} while (0)

#define FW_RX_DESC_BYTE_rsvd1_msdu3_clear_indirect(base, offset)	((*(base + O_FW_RX_DESC_BYTE_rsvd1_msdu3 + offset)) &= (~(M_FW_RX_DESC_BYTE_rsvd1_msdu3)))

#define FW_RX_DESC_BYTE_rsvd1_msdu3_clear_direct(dword)	((dword) &= (~(M_FW_RX_DESC_BYTE_rsvd1_msdu3)))

#define O_FW_RX_DESC_BYTE_inspect_msdu3 0
#define B_FW_RX_DESC_BYTE_inspect_msdu3 29
#define W_FW_RX_DESC_BYTE_inspect_msdu3 1
#define M_FW_RX_DESC_BYTE_inspect_msdu3 0x20000000

#define FW_RX_DESC_BYTE_inspect_msdu3_get_indirect(base, offset)	((((*(base + O_FW_RX_DESC_BYTE_inspect_msdu3 + offset)) & M_FW_RX_DESC_BYTE_inspect_msdu3) >> B_FW_RX_DESC_BYTE_inspect_msdu3))

#define FW_RX_DESC_BYTE_inspect_msdu3_get_direct(dword)	((((dword) & M_FW_RX_DESC_BYTE_inspect_msdu3) >> B_FW_RX_DESC_BYTE_inspect_msdu3))

#define FW_RX_DESC_BYTE_inspect_msdu3_set_indirect(base, offset, val) \
	do {                                                              \
		(*(base + O_FW_RX_DESC_BYTE_inspect_msdu3 + offset)) &= (~(M_FW_RX_DESC_BYTE_inspect_msdu3));    \
		(*(base + O_FW_RX_DESC_BYTE_inspect_msdu3 + offset)) |= ((val << B_FW_RX_DESC_BYTE_inspect_msdu3) & M_FW_RX_DESC_BYTE_inspect_msdu3);    \
	} while (0)

#define FW_RX_DESC_BYTE_inspect_msdu3_set_direct(dword, val) \
	do {                                                               \
		(dword) &= (~(M_FW_RX_DESC_BYTE_inspect_msdu3));    \
		(dword) |= ((val << B_FW_RX_DESC_BYTE_inspect_msdu3) & M_FW_RX_DESC_BYTE_inspect_msdu3);    \
	} while (0)

#define FW_RX_DESC_BYTE_inspect_msdu3_clear_indirect(base, offset)	((*(base + O_FW_RX_DESC_BYTE_inspect_msdu3 + offset)) &= (~(M_FW_RX_DESC_BYTE_inspect_msdu3)))

#define FW_RX_DESC_BYTE_inspect_msdu3_clear_direct(dword)	((dword) &= (~(M_FW_RX_DESC_BYTE_inspect_msdu3)))

#define O_FW_RX_DESC_BYTE_rsvd2_msdu3 0
#define B_FW_RX_DESC_BYTE_rsvd2_msdu3 30
#define W_FW_RX_DESC_BYTE_rsvd2_msdu3 2
#define M_FW_RX_DESC_BYTE_rsvd2_msdu3 0xc0000000

#define FW_RX_DESC_BYTE_rsvd2_msdu3_get_indirect(base, offset)	((((*(base + O_FW_RX_DESC_BYTE_rsvd2_msdu3 + offset)) & M_FW_RX_DESC_BYTE_rsvd2_msdu3) >> B_FW_RX_DESC_BYTE_rsvd2_msdu3))

#define FW_RX_DESC_BYTE_rsvd2_msdu3_get_direct(dword)	((((dword) & M_FW_RX_DESC_BYTE_rsvd2_msdu3) >> B_FW_RX_DESC_BYTE_rsvd2_msdu3))

#define FW_RX_DESC_BYTE_rsvd2_msdu3_set_indirect(base, offset, val) \
	do {                                                              \
		(*(base + O_FW_RX_DESC_BYTE_rsvd2_msdu3 + offset)) &= (~(M_FW_RX_DESC_BYTE_rsvd2_msdu3));    \
		(*(base + O_FW_RX_DESC_BYTE_rsvd2_msdu3 + offset)) |= ((val << B_FW_RX_DESC_BYTE_rsvd2_msdu3) & M_FW_RX_DESC_BYTE_rsvd2_msdu3);    \
	} while (0)

#define FW_RX_DESC_BYTE_rsvd2_msdu3_set_direct(dword, val) \
	do {                                                               \
		(dword) &= (~(M_FW_RX_DESC_BYTE_rsvd2_msdu3));    \
		(dword) |= ((val << B_FW_RX_DESC_BYTE_rsvd2_msdu3) & M_FW_RX_DESC_BYTE_rsvd2_msdu3);    \
	} while (0)

#define FW_RX_DESC_BYTE_rsvd2_msdu3_clear_indirect(base, offset)	((*(base + O_FW_RX_DESC_BYTE_rsvd2_msdu3 + offset)) &= (~(M_FW_RX_DESC_BYTE_rsvd2_msdu3)))

#define FW_RX_DESC_BYTE_rsvd2_msdu3_clear_direct(dword)	((dword) &= (~(M_FW_RX_DESC_BYTE_rsvd2_msdu3)))

#define O_CTXT_MPDU_mpdu_cnt_mpdu_range0 0
#define B_CTXT_MPDU_mpdu_cnt_mpdu_range0 0
#define W_CTXT_MPDU_mpdu_cnt_mpdu_range0 8
#define M_CTXT_MPDU_mpdu_cnt_mpdu_range0 0x000000ff

#define CTXT_MPDU_mpdu_cnt_mpdu_range0_get_indirect(base, offset)	((((*(base + O_CTXT_MPDU_mpdu_cnt_mpdu_range0 + offset)) & M_CTXT_MPDU_mpdu_cnt_mpdu_range0) >> B_CTXT_MPDU_mpdu_cnt_mpdu_range0))

#define CTXT_MPDU_mpdu_cnt_mpdu_range0_get_direct(dword)	((((dword) & M_CTXT_MPDU_mpdu_cnt_mpdu_range0) >> B_CTXT_MPDU_mpdu_cnt_mpdu_range0))

#define CTXT_MPDU_mpdu_cnt_mpdu_range0_set_indirect(base, offset, val) \
	do {                                                              \
		(*(base + O_CTXT_MPDU_mpdu_cnt_mpdu_range0 + offset)) &= (~(M_CTXT_MPDU_mpdu_cnt_mpdu_range0));    \
		(*(base + O_CTXT_MPDU_mpdu_cnt_mpdu_range0 + offset)) |= ((val << B_CTXT_MPDU_mpdu_cnt_mpdu_range0) & M_CTXT_MPDU_mpdu_cnt_mpdu_range0);    \
	} while (0)

#define CTXT_MPDU_mpdu_cnt_mpdu_range0_set_direct(dword, val) \
	do {                                                               \
		(dword) &= (~(M_CTXT_MPDU_mpdu_cnt_mpdu_range0));    \
		(dword) |= ((val << B_CTXT_MPDU_mpdu_cnt_mpdu_range0) & M_CTXT_MPDU_mpdu_cnt_mpdu_range0);    \
	} while (0)

#define CTXT_MPDU_mpdu_cnt_mpdu_range0_clear_indirect(base, offset)	((*(base + O_CTXT_MPDU_mpdu_cnt_mpdu_range0 + offset)) &= (~(M_CTXT_MPDU_mpdu_cnt_mpdu_range0)))

#define CTXT_MPDU_mpdu_cnt_mpdu_range0_clear_direct(dword)	((dword) &= (~(M_CTXT_MPDU_mpdu_cnt_mpdu_range0)))

#define O_CTXT_MPDU_mpdu_status_mpdu_range0 0
#define B_CTXT_MPDU_mpdu_status_mpdu_range0 8
#define W_CTXT_MPDU_mpdu_status_mpdu_range0 8
#define M_CTXT_MPDU_mpdu_status_mpdu_range0 0x0000ff00

#define CTXT_MPDU_mpdu_status_mpdu_range0_get_indirect(base, offset)	((((*(base + O_CTXT_MPDU_mpdu_status_mpdu_range0 + offset)) & M_CTXT_MPDU_mpdu_status_mpdu_range0) >> B_CTXT_MPDU_mpdu_status_mpdu_range0))

#define CTXT_MPDU_mpdu_status_mpdu_range0_get_direct(dword)	((((dword) & M_CTXT_MPDU_mpdu_status_mpdu_range0) >> B_CTXT_MPDU_mpdu_status_mpdu_range0))

#define CTXT_MPDU_mpdu_status_mpdu_range0_set_indirect(base, offset, val) \
	do {                                                              \
		(*(base + O_CTXT_MPDU_mpdu_status_mpdu_range0 + offset)) &= (~(M_CTXT_MPDU_mpdu_status_mpdu_range0));    \
		(*(base + O_CTXT_MPDU_mpdu_status_mpdu_range0 + offset)) |= ((val << B_CTXT_MPDU_mpdu_status_mpdu_range0) & M_CTXT_MPDU_mpdu_status_mpdu_range0);    \
	} while (0)

#define CTXT_MPDU_mpdu_status_mpdu_range0_set_direct(dword, val) \
	do {                                                               \
		(dword) &= (~(M_CTXT_MPDU_mpdu_status_mpdu_range0));    \
		(dword) |= ((val << B_CTXT_MPDU_mpdu_status_mpdu_range0) & M_CTXT_MPDU_mpdu_status_mpdu_range0);    \
	} while (0)

#define CTXT_MPDU_mpdu_status_mpdu_range0_clear_indirect(base, offset)	((*(base + O_CTXT_MPDU_mpdu_status_mpdu_range0 + offset)) &= (~(M_CTXT_MPDU_mpdu_status_mpdu_range0)))

#define CTXT_MPDU_mpdu_status_mpdu_range0_clear_direct(dword)	((dword) &= (~(M_CTXT_MPDU_mpdu_status_mpdu_range0)))

#define O_CTXT_MPDU_mpdu_cnt_mpdu_range1 0
#define B_CTXT_MPDU_mpdu_cnt_mpdu_range1 16
#define W_CTXT_MPDU_mpdu_cnt_mpdu_range1 8
#define M_CTXT_MPDU_mpdu_cnt_mpdu_range1 0x00ff0000

#define CTXT_MPDU_mpdu_cnt_mpdu_range1_get_indirect(base, offset)	((((*(base + O_CTXT_MPDU_mpdu_cnt_mpdu_range1 + offset)) & M_CTXT_MPDU_mpdu_cnt_mpdu_range1) >> B_CTXT_MPDU_mpdu_cnt_mpdu_range1))

#define CTXT_MPDU_mpdu_cnt_mpdu_range1_get_direct(dword)	((((dword) & M_CTXT_MPDU_mpdu_cnt_mpdu_range1) >> B_CTXT_MPDU_mpdu_cnt_mpdu_range1))

#define CTXT_MPDU_mpdu_cnt_mpdu_range1_set_indirect(base, offset, val) \
	do {                                                              \
		(*(base + O_CTXT_MPDU_mpdu_cnt_mpdu_range1 + offset)) &= (~(M_CTXT_MPDU_mpdu_cnt_mpdu_range1));    \
		(*(base + O_CTXT_MPDU_mpdu_cnt_mpdu_range1 + offset)) |= ((val << B_CTXT_MPDU_mpdu_cnt_mpdu_range1) & M_CTXT_MPDU_mpdu_cnt_mpdu_range1);    \
	} while (0)

#define CTXT_MPDU_mpdu_cnt_mpdu_range1_set_direct(dword, val) \
	do {                                                               \
		(dword) &= (~(M_CTXT_MPDU_mpdu_cnt_mpdu_range1));    \
		(dword) |= ((val << B_CTXT_MPDU_mpdu_cnt_mpdu_range1) & M_CTXT_MPDU_mpdu_cnt_mpdu_range1);    \
	} while (0)

#define CTXT_MPDU_mpdu_cnt_mpdu_range1_clear_indirect(base, offset)	((*(base + O_CTXT_MPDU_mpdu_cnt_mpdu_range1 + offset)) &= (~(M_CTXT_MPDU_mpdu_cnt_mpdu_range1)))

#define CTXT_MPDU_mpdu_cnt_mpdu_range1_clear_direct(dword)	((dword) &= (~(M_CTXT_MPDU_mpdu_cnt_mpdu_range1)))

#define O_CTXT_MPDU_mpdu_status_mpdu_range1 0
#define B_CTXT_MPDU_mpdu_status_mpdu_range1 24
#define W_CTXT_MPDU_mpdu_status_mpdu_range1 8
#define M_CTXT_MPDU_mpdu_status_mpdu_range1 0xff000000

#define CTXT_MPDU_mpdu_status_mpdu_range1_get_indirect(base, offset)	((((*(base + O_CTXT_MPDU_mpdu_status_mpdu_range1 + offset)) & M_CTXT_MPDU_mpdu_status_mpdu_range1) >> B_CTXT_MPDU_mpdu_status_mpdu_range1))

#define CTXT_MPDU_mpdu_status_mpdu_range1_get_direct(dword)	((((dword) & M_CTXT_MPDU_mpdu_status_mpdu_range1) >> B_CTXT_MPDU_mpdu_status_mpdu_range1))

#define CTXT_MPDU_mpdu_status_mpdu_range1_set_indirect(base, offset, val) \
	do {                                                              \
		(*(base + O_CTXT_MPDU_mpdu_status_mpdu_range1 + offset)) &= (~(M_CTXT_MPDU_mpdu_status_mpdu_range1));    \
		(*(base + O_CTXT_MPDU_mpdu_status_mpdu_range1 + offset)) |= ((val << B_CTXT_MPDU_mpdu_status_mpdu_range1) & M_CTXT_MPDU_mpdu_status_mpdu_range1);    \
	} while (0)

#define CTXT_MPDU_mpdu_status_mpdu_range1_set_direct(dword, val) \
	do {                                                               \
		(dword) &= (~(M_CTXT_MPDU_mpdu_status_mpdu_range1));    \
		(dword) |= ((val << B_CTXT_MPDU_mpdu_status_mpdu_range1) & M_CTXT_MPDU_mpdu_status_mpdu_range1);    \
	} while (0)

#define CTXT_MPDU_mpdu_status_mpdu_range1_clear_indirect(base, offset)	((*(base + O_CTXT_MPDU_mpdu_status_mpdu_range1 + offset)) &= (~(M_CTXT_MPDU_mpdu_status_mpdu_range1)))

#define CTXT_MPDU_mpdu_status_mpdu_range1_clear_direct(dword)	((dword) &= (~(M_CTXT_MPDU_mpdu_status_mpdu_range1)))

#define O_DLRX_FLUSH_MSG_htt_hdr 0
#define B_DLRX_FLUSH_MSG_htt_hdr 0
#define W_DLRX_FLUSH_MSG_htt_hdr 32
#define M_DLRX_FLUSH_MSG_htt_hdr 0xffffffff

#define DLRX_FLUSH_MSG_htt_hdr_get_indirect(base, offset)	((((*(base + O_DLRX_FLUSH_MSG_htt_hdr + offset)) & M_DLRX_FLUSH_MSG_htt_hdr) >> B_DLRX_FLUSH_MSG_htt_hdr))

#define DLRX_FLUSH_MSG_htt_hdr_get_direct(dword)	((((dword) & M_DLRX_FLUSH_MSG_htt_hdr) >> B_DLRX_FLUSH_MSG_htt_hdr))

#define DLRX_FLUSH_MSG_htt_hdr_set_indirect(base, offset, val)    \
	do {                                                              \
		(*(base + O_DLRX_FLUSH_MSG_htt_hdr + offset)) &= (~(M_DLRX_FLUSH_MSG_htt_hdr));    \
		(*(base + O_DLRX_FLUSH_MSG_htt_hdr + offset)) |= ((val << B_DLRX_FLUSH_MSG_htt_hdr) & M_DLRX_FLUSH_MSG_htt_hdr);    \
	} while (0)

#define DLRX_FLUSH_MSG_htt_hdr_set_direct(dword, val)    \
	do {                                                               \
		(dword) &= (~(M_DLRX_FLUSH_MSG_htt_hdr));    \
		(dword) |= ((val << B_DLRX_FLUSH_MSG_htt_hdr) & M_DLRX_FLUSH_MSG_htt_hdr);    \
	} while (0)

#define DLRX_FLUSH_MSG_htt_hdr_clear_indirect(base, offset)	((*(base + O_DLRX_FLUSH_MSG_htt_hdr + offset)) &= (~(M_DLRX_FLUSH_MSG_htt_hdr)))

#define DLRX_FLUSH_MSG_htt_hdr_clear_direct(dword)	((dword) &= (~(M_DLRX_FLUSH_MSG_htt_hdr)))

#define O_DLRX_FLUSH_MSG_msg_type 2
#define B_DLRX_FLUSH_MSG_msg_type 0
#define W_DLRX_FLUSH_MSG_msg_type 8
#define M_DLRX_FLUSH_MSG_msg_type 0x000000ff

#define DLRX_FLUSH_MSG_msg_type_get_indirect(base, offset)	((((*(base + O_DLRX_FLUSH_MSG_msg_type + offset)) & M_DLRX_FLUSH_MSG_msg_type) >> B_DLRX_FLUSH_MSG_msg_type))

#define DLRX_FLUSH_MSG_msg_type_get_direct(dword)	((((dword) & M_DLRX_FLUSH_MSG_msg_type) >> B_DLRX_FLUSH_MSG_msg_type))

#define DLRX_FLUSH_MSG_msg_type_set_indirect(base, offset, val) \
	do {                                                              \
		(*(base + O_DLRX_FLUSH_MSG_msg_type + offset)) &= (~(M_DLRX_FLUSH_MSG_msg_type));    \
		(*(base + O_DLRX_FLUSH_MSG_msg_type + offset)) |= ((val << B_DLRX_FLUSH_MSG_msg_type) & M_DLRX_FLUSH_MSG_msg_type);    \
	} while (0)

#define DLRX_FLUSH_MSG_msg_type_set_direct(dword, val) \
	do {                                                               \
		(dword) &= (~(M_DLRX_FLUSH_MSG_msg_type));    \
		(dword) |= ((val << B_DLRX_FLUSH_MSG_msg_type) & M_DLRX_FLUSH_MSG_msg_type);    \
	} while (0)

#define DLRX_FLUSH_MSG_msg_type_clear_indirect(base, offset)	((*(base + O_DLRX_FLUSH_MSG_msg_type + offset)) &= (~(M_DLRX_FLUSH_MSG_msg_type)))

#define DLRX_FLUSH_MSG_msg_type_clear_direct(dword)	((dword) &= (~(M_DLRX_FLUSH_MSG_msg_type)))

#define O_DLRX_FLUSH_MSG_peer_id 2
#define B_DLRX_FLUSH_MSG_peer_id 8
#define W_DLRX_FLUSH_MSG_peer_id 16
#define M_DLRX_FLUSH_MSG_peer_id 0x00ffff00

#define DLRX_FLUSH_MSG_peer_id_get_indirect(base, offset)	((((*(base + O_DLRX_FLUSH_MSG_peer_id + offset)) & M_DLRX_FLUSH_MSG_peer_id) >> B_DLRX_FLUSH_MSG_peer_id))

#define DLRX_FLUSH_MSG_peer_id_get_direct(dword)	((((dword) & M_DLRX_FLUSH_MSG_peer_id) >> B_DLRX_FLUSH_MSG_peer_id))

#define DLRX_FLUSH_MSG_peer_id_set_indirect(base, offset, val) \
	do {                                                              \
		(*(base + O_DLRX_FLUSH_MSG_peer_id + offset)) &= (~(M_DLRX_FLUSH_MSG_peer_id));    \
		(*(base + O_DLRX_FLUSH_MSG_peer_id + offset)) |= ((val << B_DLRX_FLUSH_MSG_peer_id) & M_DLRX_FLUSH_MSG_peer_id);    \
	} while (0)

#define DLRX_FLUSH_MSG_peer_id_set_direct(dword, val) \
	do {                                                               \
		(dword) &= (~(M_DLRX_FLUSH_MSG_peer_id));    \
		(dword) |= ((val << B_DLRX_FLUSH_MSG_peer_id) & M_DLRX_FLUSH_MSG_peer_id);    \
	} while (0)

#define DLRX_FLUSH_MSG_peer_id_clear_indirect(base, offset)	((*(base + O_DLRX_FLUSH_MSG_peer_id + offset)) &= (~(M_DLRX_FLUSH_MSG_peer_id)))

#define DLRX_FLUSH_MSG_peer_id_clear_direct(dword)	((dword) &= (~(M_DLRX_FLUSH_MSG_peer_id)))

#define O_DLRX_FLUSH_MSG_ext_tid 2
#define B_DLRX_FLUSH_MSG_ext_tid 24
#define W_DLRX_FLUSH_MSG_ext_tid 5
#define M_DLRX_FLUSH_MSG_ext_tid 0x1f000000

#define DLRX_FLUSH_MSG_ext_tid_get_indirect(base, offset)	((((*(base + O_DLRX_FLUSH_MSG_ext_tid + offset)) & M_DLRX_FLUSH_MSG_ext_tid) >> B_DLRX_FLUSH_MSG_ext_tid))

#define DLRX_FLUSH_MSG_ext_tid_get_direct(dword)	((((dword) & M_DLRX_FLUSH_MSG_ext_tid) >> B_DLRX_FLUSH_MSG_ext_tid))

#define DLRX_FLUSH_MSG_ext_tid_set_indirect(base, offset, val) \
	do {                                                              \
		(*(base + O_DLRX_FLUSH_MSG_ext_tid + offset)) &= (~(M_DLRX_FLUSH_MSG_ext_tid));    \
		(*(base + O_DLRX_FLUSH_MSG_ext_tid + offset)) |= ((val << B_DLRX_FLUSH_MSG_ext_tid) & M_DLRX_FLUSH_MSG_ext_tid);    \
	} while (0)

#define DLRX_FLUSH_MSG_ext_tid_set_direct(dword, val) \
	do {                                                               \
		(dword) &= (~(M_DLRX_FLUSH_MSG_ext_tid));    \
		(dword) |= ((val << B_DLRX_FLUSH_MSG_ext_tid) & M_DLRX_FLUSH_MSG_ext_tid);    \
	} while (0)

#define DLRX_FLUSH_MSG_ext_tid_clear_indirect(base, offset)	((*(base + O_DLRX_FLUSH_MSG_ext_tid + offset)) &= (~(M_DLRX_FLUSH_MSG_ext_tid)))

#define DLRX_FLUSH_MSG_ext_tid_clear_direct(dword)	((dword) &= (~(M_DLRX_FLUSH_MSG_ext_tid)))

#define O_DLRX_FLUSH_MSG_rsvd1 2
#define B_DLRX_FLUSH_MSG_rsvd1 29
#define W_DLRX_FLUSH_MSG_rsvd1 3
#define M_DLRX_FLUSH_MSG_rsvd1 0xe0000000

#define DLRX_FLUSH_MSG_rsvd1_get_indirect(base, offset)	((((*(base + O_DLRX_FLUSH_MSG_rsvd1 + offset)) & M_DLRX_FLUSH_MSG_rsvd1) >> B_DLRX_FLUSH_MSG_rsvd1))

#define DLRX_FLUSH_MSG_rsvd1_get_direct(dword)	((((dword) & M_DLRX_FLUSH_MSG_rsvd1) >> B_DLRX_FLUSH_MSG_rsvd1))

#define DLRX_FLUSH_MSG_rsvd1_set_indirect(base, offset, val) \
	do {                                                              \
		(*(base + O_DLRX_FLUSH_MSG_rsvd1 + offset)) &= (~(M_DLRX_FLUSH_MSG_rsvd1));    \
		(*(base + O_DLRX_FLUSH_MSG_rsvd1 + offset)) |= ((val << B_DLRX_FLUSH_MSG_rsvd1) & M_DLRX_FLUSH_MSG_rsvd1);    \
	} while (0)

#define DLRX_FLUSH_MSG_rsvd1_set_direct(dword, val) \
	do {                                                               \
		(dword) &= (~(M_DLRX_FLUSH_MSG_rsvd1));    \
		(dword) |= ((val << B_DLRX_FLUSH_MSG_rsvd1) & M_DLRX_FLUSH_MSG_rsvd1);    \
	} while (0)

#define DLRX_FLUSH_MSG_rsvd1_clear_indirect(base, offset)	((*(base + O_DLRX_FLUSH_MSG_rsvd1 + offset)) &= (~(M_DLRX_FLUSH_MSG_rsvd1)))

#define DLRX_FLUSH_MSG_rsvd1_clear_direct(dword)	((dword) &= (~(M_DLRX_FLUSH_MSG_rsvd1)))

#define O_DLRX_FLUSH_MSG_rsvd2 3
#define B_DLRX_FLUSH_MSG_rsvd2 0
#define W_DLRX_FLUSH_MSG_rsvd2 8
#define M_DLRX_FLUSH_MSG_rsvd2 0x000000ff

#define DLRX_FLUSH_MSG_rsvd2_get_indirect(base, offset)	((((*(base + O_DLRX_FLUSH_MSG_rsvd2 + offset)) & M_DLRX_FLUSH_MSG_rsvd2) >> B_DLRX_FLUSH_MSG_rsvd2))

#define DLRX_FLUSH_MSG_rsvd2_get_direct(dword)	((((dword) & M_DLRX_FLUSH_MSG_rsvd2) >> B_DLRX_FLUSH_MSG_rsvd2))

#define DLRX_FLUSH_MSG_rsvd2_set_indirect(base, offset, val) \
	do {                                                              \
		(*(base + O_DLRX_FLUSH_MSG_rsvd2 + offset)) &= (~(M_DLRX_FLUSH_MSG_rsvd2));    \
		(*(base + O_DLRX_FLUSH_MSG_rsvd2 + offset)) |= ((val << B_DLRX_FLUSH_MSG_rsvd2) & M_DLRX_FLUSH_MSG_rsvd2);    \
	} while (0)

#define DLRX_FLUSH_MSG_rsvd2_set_direct(dword, val) \
	do {                                                               \
		(dword) &= (~(M_DLRX_FLUSH_MSG_rsvd2));    \
		(dword) |= ((val << B_DLRX_FLUSH_MSG_rsvd2) & M_DLRX_FLUSH_MSG_rsvd2);    \
	} while (0)

#define DLRX_FLUSH_MSG_rsvd2_clear_indirect(base, offset)	((*(base + O_DLRX_FLUSH_MSG_rsvd2 + offset)) &= (~(M_DLRX_FLUSH_MSG_rsvd2)))

#define DLRX_FLUSH_MSG_rsvd2_clear_direct(dword)	((dword) &= (~(M_DLRX_FLUSH_MSG_rsvd2)))

#define O_DLRX_FLUSH_MSG_mpdu_status 3
#define B_DLRX_FLUSH_MSG_mpdu_status 8
#define W_DLRX_FLUSH_MSG_mpdu_status 8
#define M_DLRX_FLUSH_MSG_mpdu_status 0x0000ff00

#define DLRX_FLUSH_MSG_mpdu_status_get_indirect(base, offset)	((((*(base + O_DLRX_FLUSH_MSG_mpdu_status + offset)) & M_DLRX_FLUSH_MSG_mpdu_status) >> B_DLRX_FLUSH_MSG_mpdu_status))

#define DLRX_FLUSH_MSG_mpdu_status_get_direct(dword)	((((dword) & M_DLRX_FLUSH_MSG_mpdu_status) >> B_DLRX_FLUSH_MSG_mpdu_status))

#define DLRX_FLUSH_MSG_mpdu_status_set_indirect(base, offset, val) \
	do {                                                              \
		(*(base + O_DLRX_FLUSH_MSG_mpdu_status + offset)) &= (~(M_DLRX_FLUSH_MSG_mpdu_status));    \
		(*(base + O_DLRX_FLUSH_MSG_mpdu_status + offset)) |= ((val << B_DLRX_FLUSH_MSG_mpdu_status) & M_DLRX_FLUSH_MSG_mpdu_status);    \
	} while (0)

#define DLRX_FLUSH_MSG_mpdu_status_set_direct(dword, val) \
	do {                                                               \
		(dword) &= (~(M_DLRX_FLUSH_MSG_mpdu_status));    \
		(dword) |= ((val << B_DLRX_FLUSH_MSG_mpdu_status) & M_DLRX_FLUSH_MSG_mpdu_status);    \
	} while (0)

#define DLRX_FLUSH_MSG_mpdu_status_clear_indirect(base, offset)	((*(base + O_DLRX_FLUSH_MSG_mpdu_status + offset)) &= (~(M_DLRX_FLUSH_MSG_mpdu_status)))

#define DLRX_FLUSH_MSG_mpdu_status_clear_direct(dword)	((dword) &= (~(M_DLRX_FLUSH_MSG_mpdu_status)))

#define O_DLRX_FLUSH_MSG_flush_start_seqid 3
#define B_DLRX_FLUSH_MSG_flush_start_seqid 16
#define W_DLRX_FLUSH_MSG_flush_start_seqid 6
#define M_DLRX_FLUSH_MSG_flush_start_seqid 0x003f0000

#define DLRX_FLUSH_MSG_flush_start_seqid_get_indirect(base, offset)	((((*(base + O_DLRX_FLUSH_MSG_flush_start_seqid + offset)) & M_DLRX_FLUSH_MSG_flush_start_seqid) >> B_DLRX_FLUSH_MSG_flush_start_seqid))

#define DLRX_FLUSH_MSG_flush_start_seqid_get_direct(dword)	((((dword) & M_DLRX_FLUSH_MSG_flush_start_seqid) >> B_DLRX_FLUSH_MSG_flush_start_seqid))

#define DLRX_FLUSH_MSG_flush_start_seqid_set_indirect(base, offset, val) \
	do {                                                              \
		(*(base + O_DLRX_FLUSH_MSG_flush_start_seqid + offset)) &= (~(M_DLRX_FLUSH_MSG_flush_start_seqid));    \
		(*(base + O_DLRX_FLUSH_MSG_flush_start_seqid + offset)) |= ((val << B_DLRX_FLUSH_MSG_flush_start_seqid) & M_DLRX_FLUSH_MSG_flush_start_seqid);    \
	} while (0)

#define DLRX_FLUSH_MSG_flush_start_seqid_set_direct(dword, val) \
	do {                                                               \
		(dword) &= (~(M_DLRX_FLUSH_MSG_flush_start_seqid));    \
		(dword) |= ((val << B_DLRX_FLUSH_MSG_flush_start_seqid) & M_DLRX_FLUSH_MSG_flush_start_seqid);    \
	} while (0)

#define DLRX_FLUSH_MSG_flush_start_seqid_clear_indirect(base, offset)	((*(base + O_DLRX_FLUSH_MSG_flush_start_seqid + offset)) &= (~(M_DLRX_FLUSH_MSG_flush_start_seqid)))

#define DLRX_FLUSH_MSG_flush_start_seqid_clear_direct(dword)	((dword) &= (~(M_DLRX_FLUSH_MSG_flush_start_seqid)))

#define O_DLRX_FLUSH_MSG_rsvd3 3
#define B_DLRX_FLUSH_MSG_rsvd3 22
#define W_DLRX_FLUSH_MSG_rsvd3 2
#define M_DLRX_FLUSH_MSG_rsvd3 0x00c00000

#define DLRX_FLUSH_MSG_rsvd3_get_indirect(base, offset)	((((*(base + O_DLRX_FLUSH_MSG_rsvd3 + offset)) & M_DLRX_FLUSH_MSG_rsvd3) >> B_DLRX_FLUSH_MSG_rsvd3))

#define DLRX_FLUSH_MSG_rsvd3_get_direct(dword)	((((dword) & M_DLRX_FLUSH_MSG_rsvd3) >> B_DLRX_FLUSH_MSG_rsvd3))

#define DLRX_FLUSH_MSG_rsvd3_set_indirect(base, offset, val) \
	do {                                                              \
		(*(base + O_DLRX_FLUSH_MSG_rsvd3 + offset)) &= (~(M_DLRX_FLUSH_MSG_rsvd3));    \
		(*(base + O_DLRX_FLUSH_MSG_rsvd3 + offset)) |= ((val << B_DLRX_FLUSH_MSG_rsvd3) & M_DLRX_FLUSH_MSG_rsvd3);    \
	} while (0)

#define DLRX_FLUSH_MSG_rsvd3_set_direct(dword, val) \
	do {                                                               \
		(dword) &= (~(M_DLRX_FLUSH_MSG_rsvd3));    \
		(dword) |= ((val << B_DLRX_FLUSH_MSG_rsvd3) & M_DLRX_FLUSH_MSG_rsvd3);    \
	} while (0)

#define DLRX_FLUSH_MSG_rsvd3_clear_indirect(base, offset)	((*(base + O_DLRX_FLUSH_MSG_rsvd3 + offset)) &= (~(M_DLRX_FLUSH_MSG_rsvd3)))

#define DLRX_FLUSH_MSG_rsvd3_clear_direct(dword)	((dword) &= (~(M_DLRX_FLUSH_MSG_rsvd3)))

#define O_DLRX_FLUSH_MSG_flush_end_seqid 3
#define B_DLRX_FLUSH_MSG_flush_end_seqid 24
#define W_DLRX_FLUSH_MSG_flush_end_seqid 6
#define M_DLRX_FLUSH_MSG_flush_end_seqid 0x3f000000

#define DLRX_FLUSH_MSG_flush_end_seqid_get_indirect(base, offset)	((((*(base + O_DLRX_FLUSH_MSG_flush_end_seqid + offset)) & M_DLRX_FLUSH_MSG_flush_end_seqid) >> B_DLRX_FLUSH_MSG_flush_end_seqid))

#define DLRX_FLUSH_MSG_flush_end_seqid_get_direct(dword)	((((dword) & M_DLRX_FLUSH_MSG_flush_end_seqid) >> B_DLRX_FLUSH_MSG_flush_end_seqid))

#define DLRX_FLUSH_MSG_flush_end_seqid_set_indirect(base, offset, val) \
	do {                                                              \
		(*(base + O_DLRX_FLUSH_MSG_flush_end_seqid + offset)) &= (~(M_DLRX_FLUSH_MSG_flush_end_seqid));    \
		(*(base + O_DLRX_FLUSH_MSG_flush_end_seqid + offset)) |= ((val << B_DLRX_FLUSH_MSG_flush_end_seqid) & M_DLRX_FLUSH_MSG_flush_end_seqid);    \
	} while (0)

#define DLRX_FLUSH_MSG_flush_end_seqid_set_direct(dword, val) \
	do {                                                               \
		(dword) &= (~(M_DLRX_FLUSH_MSG_flush_end_seqid));    \
		(dword) |= ((val << B_DLRX_FLUSH_MSG_flush_end_seqid) & M_DLRX_FLUSH_MSG_flush_end_seqid);    \
	} while (0)

#define DLRX_FLUSH_MSG_flush_end_seqid_clear_indirect(base, offset)	((*(base + O_DLRX_FLUSH_MSG_flush_end_seqid + offset)) &= (~(M_DLRX_FLUSH_MSG_flush_end_seqid)))

#define DLRX_FLUSH_MSG_flush_end_seqid_clear_direct(dword)	((dword) &= (~(M_DLRX_FLUSH_MSG_flush_end_seqid)))

#define O_DLRX_FLUSH_MSG_rsvd4 3
#define B_DLRX_FLUSH_MSG_rsvd4 30
#define W_DLRX_FLUSH_MSG_rsvd4 2
#define M_DLRX_FLUSH_MSG_rsvd4 0xc0000000

#define DLRX_FLUSH_MSG_rsvd4_get_indirect(base, offset)	((((*(base + O_DLRX_FLUSH_MSG_rsvd4 + offset)) & M_DLRX_FLUSH_MSG_rsvd4) >> B_DLRX_FLUSH_MSG_rsvd4))

#define DLRX_FLUSH_MSG_rsvd4_get_direct(dword)	((((dword) & M_DLRX_FLUSH_MSG_rsvd4) >> B_DLRX_FLUSH_MSG_rsvd4))

#define DLRX_FLUSH_MSG_rsvd4_set_indirect(base, offset, val) \
	do {                                                              \
		(*(base + O_DLRX_FLUSH_MSG_rsvd4 + offset)) &= (~(M_DLRX_FLUSH_MSG_rsvd4));    \
		(*(base + O_DLRX_FLUSH_MSG_rsvd4 + offset)) |= ((val << B_DLRX_FLUSH_MSG_rsvd4) & M_DLRX_FLUSH_MSG_rsvd4);    \
	} while (0)

#define DLRX_FLUSH_MSG_rsvd4_set_direct(dword, val) \
	do {                                                               \
		(dword) &= (~(M_DLRX_FLUSH_MSG_rsvd4));    \
		(dword) |= ((val << B_DLRX_FLUSH_MSG_rsvd4) & M_DLRX_FLUSH_MSG_rsvd4);    \
	} while (0)

#define DLRX_FLUSH_MSG_rsvd4_clear_indirect(base, offset)	((*(base + O_DLRX_FLUSH_MSG_rsvd4 + offset)) &= (~(M_DLRX_FLUSH_MSG_rsvd4)))

#define DLRX_FLUSH_MSG_rsvd4_clear_direct(dword)	((dword) &= (~(M_DLRX_FLUSH_MSG_rsvd4)))

#define O_DLRX_FRAG_IND_MSG_htt_hdr 0
#define B_DLRX_FRAG_IND_MSG_htt_hdr 0
#define W_DLRX_FRAG_IND_MSG_htt_hdr 32
#define M_DLRX_FRAG_IND_MSG_htt_hdr 0xffffffff

#define DLRX_FRAG_IND_MSG_htt_hdr_get_indirect(base, offset)	((((*(base + O_DLRX_FRAG_IND_MSG_htt_hdr + offset)) & M_DLRX_FRAG_IND_MSG_htt_hdr) >> B_DLRX_FRAG_IND_MSG_htt_hdr))

#define DLRX_FRAG_IND_MSG_htt_hdr_get_direct(dword)	((((dword) & M_DLRX_FRAG_IND_MSG_htt_hdr) >> B_DLRX_FRAG_IND_MSG_htt_hdr))

#define DLRX_FRAG_IND_MSG_htt_hdr_set_indirect(base, offset, val)    \
	do {                                                              \
		(*(base + O_DLRX_FRAG_IND_MSG_htt_hdr + offset)) &= (~(M_DLRX_FRAG_IND_MSG_htt_hdr));    \
		(*(base + O_DLRX_FRAG_IND_MSG_htt_hdr + offset)) |= ((val << B_DLRX_FRAG_IND_MSG_htt_hdr) & M_DLRX_FRAG_IND_MSG_htt_hdr);    \
	} while (0)

#define DLRX_FRAG_IND_MSG_htt_hdr_set_direct(dword, val)    \
	do {                                                               \
		(dword) &= (~(M_DLRX_FRAG_IND_MSG_htt_hdr));    \
		(dword) |= ((val << B_DLRX_FRAG_IND_MSG_htt_hdr) & M_DLRX_FRAG_IND_MSG_htt_hdr);    \
	} while (0)

#define DLRX_FRAG_IND_MSG_htt_hdr_clear_indirect(base, offset)	((*(base + O_DLRX_FRAG_IND_MSG_htt_hdr + offset)) &= (~(M_DLRX_FRAG_IND_MSG_htt_hdr)))

#define DLRX_FRAG_IND_MSG_htt_hdr_clear_direct(dword)	((dword) &= (~(M_DLRX_FRAG_IND_MSG_htt_hdr)))

#define O_DLRX_FRAG_IND_MSG_msg_type 2
#define B_DLRX_FRAG_IND_MSG_msg_type 0
#define W_DLRX_FRAG_IND_MSG_msg_type 8
#define M_DLRX_FRAG_IND_MSG_msg_type 0x000000ff

#define DLRX_FRAG_IND_MSG_msg_type_get_indirect(base, offset)	((((*(base + O_DLRX_FRAG_IND_MSG_msg_type + offset)) & M_DLRX_FRAG_IND_MSG_msg_type) >> B_DLRX_FRAG_IND_MSG_msg_type))

#define DLRX_FRAG_IND_MSG_msg_type_get_direct(dword)	((((dword) & M_DLRX_FRAG_IND_MSG_msg_type) >> B_DLRX_FRAG_IND_MSG_msg_type))

#define DLRX_FRAG_IND_MSG_msg_type_set_indirect(base, offset, val) \
	do {                                                              \
		(*(base + O_DLRX_FRAG_IND_MSG_msg_type + offset)) &= (~(M_DLRX_FRAG_IND_MSG_msg_type));    \
		(*(base + O_DLRX_FRAG_IND_MSG_msg_type + offset)) |= ((val << B_DLRX_FRAG_IND_MSG_msg_type) & M_DLRX_FRAG_IND_MSG_msg_type);    \
	} while (0)

#define DLRX_FRAG_IND_MSG_msg_type_set_direct(dword, val) \
	do {                                                               \
		(dword) &= (~(M_DLRX_FRAG_IND_MSG_msg_type));    \
		(dword) |= ((val << B_DLRX_FRAG_IND_MSG_msg_type) & M_DLRX_FRAG_IND_MSG_msg_type);    \
	} while (0)

#define DLRX_FRAG_IND_MSG_msg_type_clear_indirect(base, offset)	((*(base + O_DLRX_FRAG_IND_MSG_msg_type + offset)) &= (~(M_DLRX_FRAG_IND_MSG_msg_type)))

#define DLRX_FRAG_IND_MSG_msg_type_clear_direct(dword)	((dword) &= (~(M_DLRX_FRAG_IND_MSG_msg_type)))

#define O_DLRX_FRAG_IND_MSG_ext_tid 2
#define B_DLRX_FRAG_IND_MSG_ext_tid 8
#define W_DLRX_FRAG_IND_MSG_ext_tid 5
#define M_DLRX_FRAG_IND_MSG_ext_tid 0x00001f00

#define DLRX_FRAG_IND_MSG_ext_tid_get_indirect(base, offset)	((((*(base + O_DLRX_FRAG_IND_MSG_ext_tid + offset)) & M_DLRX_FRAG_IND_MSG_ext_tid) >> B_DLRX_FRAG_IND_MSG_ext_tid))

#define DLRX_FRAG_IND_MSG_ext_tid_get_direct(dword)	((((dword) & M_DLRX_FRAG_IND_MSG_ext_tid) >> B_DLRX_FRAG_IND_MSG_ext_tid))

#define DLRX_FRAG_IND_MSG_ext_tid_set_indirect(base, offset, val) \
	do {                                                              \
		(*(base + O_DLRX_FRAG_IND_MSG_ext_tid + offset)) &= (~(M_DLRX_FRAG_IND_MSG_ext_tid));    \
		(*(base + O_DLRX_FRAG_IND_MSG_ext_tid + offset)) |= ((val << B_DLRX_FRAG_IND_MSG_ext_tid) & M_DLRX_FRAG_IND_MSG_ext_tid);    \
	} while (0)

#define DLRX_FRAG_IND_MSG_ext_tid_set_direct(dword, val) \
	do {                                                               \
		(dword) &= (~(M_DLRX_FRAG_IND_MSG_ext_tid));    \
		(dword) |= ((val << B_DLRX_FRAG_IND_MSG_ext_tid) & M_DLRX_FRAG_IND_MSG_ext_tid);    \
	} while (0)

#define DLRX_FRAG_IND_MSG_ext_tid_clear_indirect(base, offset)	((*(base + O_DLRX_FRAG_IND_MSG_ext_tid + offset)) &= (~(M_DLRX_FRAG_IND_MSG_ext_tid)))

#define DLRX_FRAG_IND_MSG_ext_tid_clear_direct(dword)	((dword) &= (~(M_DLRX_FRAG_IND_MSG_ext_tid)))

#define O_DLRX_FRAG_IND_MSG_fv 2
#define B_DLRX_FRAG_IND_MSG_fv 13
#define W_DLRX_FRAG_IND_MSG_fv 1
#define M_DLRX_FRAG_IND_MSG_fv 0x00002000

#define DLRX_FRAG_IND_MSG_fv_get_indirect(base, offset)	((((*(base + O_DLRX_FRAG_IND_MSG_fv + offset)) & M_DLRX_FRAG_IND_MSG_fv) >> B_DLRX_FRAG_IND_MSG_fv))

#define DLRX_FRAG_IND_MSG_fv_get_direct(dword)	((((dword) & M_DLRX_FRAG_IND_MSG_fv) >> B_DLRX_FRAG_IND_MSG_fv))

#define DLRX_FRAG_IND_MSG_fv_set_indirect(base, offset, val) \
	do {                                                              \
		(*(base + O_DLRX_FRAG_IND_MSG_fv + offset)) &= (~(M_DLRX_FRAG_IND_MSG_fv));    \
		(*(base + O_DLRX_FRAG_IND_MSG_fv + offset)) |= ((val << B_DLRX_FRAG_IND_MSG_fv) & M_DLRX_FRAG_IND_MSG_fv);    \
	} while (0)

#define DLRX_FRAG_IND_MSG_fv_set_direct(dword, val) \
	do {                                                               \
		(dword) &= (~(M_DLRX_FRAG_IND_MSG_fv));    \
		(dword) |= ((val << B_DLRX_FRAG_IND_MSG_fv) & M_DLRX_FRAG_IND_MSG_fv);    \
	} while (0)

#define DLRX_FRAG_IND_MSG_fv_clear_indirect(base, offset)	((*(base + O_DLRX_FRAG_IND_MSG_fv + offset)) &= (~(M_DLRX_FRAG_IND_MSG_fv)))

#define DLRX_FRAG_IND_MSG_fv_clear_direct(dword)	((dword) &= (~(M_DLRX_FRAG_IND_MSG_fv)))

#define O_DLRX_FRAG_IND_MSG_rsvd0 2
#define B_DLRX_FRAG_IND_MSG_rsvd0 14
#define W_DLRX_FRAG_IND_MSG_rsvd0 2
#define M_DLRX_FRAG_IND_MSG_rsvd0 0x0000c000

#define DLRX_FRAG_IND_MSG_rsvd0_get_indirect(base, offset)	((((*(base + O_DLRX_FRAG_IND_MSG_rsvd0 + offset)) & M_DLRX_FRAG_IND_MSG_rsvd0) >> B_DLRX_FRAG_IND_MSG_rsvd0))

#define DLRX_FRAG_IND_MSG_rsvd0_get_direct(dword)	((((dword) & M_DLRX_FRAG_IND_MSG_rsvd0) >> B_DLRX_FRAG_IND_MSG_rsvd0))

#define DLRX_FRAG_IND_MSG_rsvd0_set_indirect(base, offset, val) \
	do {                                                              \
		(*(base + O_DLRX_FRAG_IND_MSG_rsvd0 + offset)) &= (~(M_DLRX_FRAG_IND_MSG_rsvd0));    \
		(*(base + O_DLRX_FRAG_IND_MSG_rsvd0 + offset)) |= ((val << B_DLRX_FRAG_IND_MSG_rsvd0) & M_DLRX_FRAG_IND_MSG_rsvd0);    \
	} while (0)

#define DLRX_FRAG_IND_MSG_rsvd0_set_direct(dword, val) \
	do {                                                               \
		(dword) &= (~(M_DLRX_FRAG_IND_MSG_rsvd0));    \
		(dword) |= ((val << B_DLRX_FRAG_IND_MSG_rsvd0) & M_DLRX_FRAG_IND_MSG_rsvd0);    \
	} while (0)

#define DLRX_FRAG_IND_MSG_rsvd0_clear_indirect(base, offset)	((*(base + O_DLRX_FRAG_IND_MSG_rsvd0 + offset)) &= (~(M_DLRX_FRAG_IND_MSG_rsvd0)))

#define DLRX_FRAG_IND_MSG_rsvd0_clear_direct(dword)	((dword) &= (~(M_DLRX_FRAG_IND_MSG_rsvd0)))

#define O_DLRX_FRAG_IND_MSG_peer_id 2
#define B_DLRX_FRAG_IND_MSG_peer_id 16
#define W_DLRX_FRAG_IND_MSG_peer_id 16
#define M_DLRX_FRAG_IND_MSG_peer_id 0xffff0000

#define DLRX_FRAG_IND_MSG_peer_id_get_indirect(base, offset)	((((*(base + O_DLRX_FRAG_IND_MSG_peer_id + offset)) & M_DLRX_FRAG_IND_MSG_peer_id) >> B_DLRX_FRAG_IND_MSG_peer_id))

#define DLRX_FRAG_IND_MSG_peer_id_get_direct(dword)	((((dword) & M_DLRX_FRAG_IND_MSG_peer_id) >> B_DLRX_FRAG_IND_MSG_peer_id))

#define DLRX_FRAG_IND_MSG_peer_id_set_indirect(base, offset, val) \
	do {                                                              \
		(*(base + O_DLRX_FRAG_IND_MSG_peer_id + offset)) &= (~(M_DLRX_FRAG_IND_MSG_peer_id));    \
		(*(base + O_DLRX_FRAG_IND_MSG_peer_id + offset)) |= ((val << B_DLRX_FRAG_IND_MSG_peer_id) & M_DLRX_FRAG_IND_MSG_peer_id);    \
	} while (0)

#define DLRX_FRAG_IND_MSG_peer_id_set_direct(dword, val) \
	do {                                                               \
		(dword) &= (~(M_DLRX_FRAG_IND_MSG_peer_id));    \
		(dword) |= ((val << B_DLRX_FRAG_IND_MSG_peer_id) & M_DLRX_FRAG_IND_MSG_peer_id);    \
	} while (0)

#define DLRX_FRAG_IND_MSG_peer_id_clear_indirect(base, offset)	((*(base + O_DLRX_FRAG_IND_MSG_peer_id + offset)) &= (~(M_DLRX_FRAG_IND_MSG_peer_id)))

#define DLRX_FRAG_IND_MSG_peer_id_clear_direct(dword)	((dword) &= (~(M_DLRX_FRAG_IND_MSG_peer_id)))

#define O_DLRX_FRAG_IND_MSG_flush_start_seqid 3
#define B_DLRX_FRAG_IND_MSG_flush_start_seqid 0
#define W_DLRX_FRAG_IND_MSG_flush_start_seqid 6
#define M_DLRX_FRAG_IND_MSG_flush_start_seqid 0x0000003f

#define DLRX_FRAG_IND_MSG_flush_start_seqid_get_indirect(base, offset)	((((*(base + O_DLRX_FRAG_IND_MSG_flush_start_seqid + offset)) & M_DLRX_FRAG_IND_MSG_flush_start_seqid) >> B_DLRX_FRAG_IND_MSG_flush_start_seqid))

#define DLRX_FRAG_IND_MSG_flush_start_seqid_get_direct(dword)	((((dword) & M_DLRX_FRAG_IND_MSG_flush_start_seqid) >> B_DLRX_FRAG_IND_MSG_flush_start_seqid))

#define DLRX_FRAG_IND_MSG_flush_start_seqid_set_indirect(base, offset, val) \
	do {                                                              \
		(*(base + O_DLRX_FRAG_IND_MSG_flush_start_seqid + offset)) &= (~(M_DLRX_FRAG_IND_MSG_flush_start_seqid));    \
		(*(base + O_DLRX_FRAG_IND_MSG_flush_start_seqid + offset)) |= ((val << B_DLRX_FRAG_IND_MSG_flush_start_seqid) & M_DLRX_FRAG_IND_MSG_flush_start_seqid);    \
	} while (0)

#define DLRX_FRAG_IND_MSG_flush_start_seqid_set_direct(dword, val) \
	do {                                                               \
		(dword) &= (~(M_DLRX_FRAG_IND_MSG_flush_start_seqid));    \
		(dword) |= ((val << B_DLRX_FRAG_IND_MSG_flush_start_seqid) & M_DLRX_FRAG_IND_MSG_flush_start_seqid);    \
	} while (0)

#define DLRX_FRAG_IND_MSG_flush_start_seqid_clear_indirect(base, offset)	((*(base + O_DLRX_FRAG_IND_MSG_flush_start_seqid + offset)) &= (~(M_DLRX_FRAG_IND_MSG_flush_start_seqid)))

#define DLRX_FRAG_IND_MSG_flush_start_seqid_clear_direct(dword)	((dword) &= (~(M_DLRX_FRAG_IND_MSG_flush_start_seqid)))

#define O_DLRX_FRAG_IND_MSG_flush_end_seqid 3
#define B_DLRX_FRAG_IND_MSG_flush_end_seqid 6
#define W_DLRX_FRAG_IND_MSG_flush_end_seqid 6
#define M_DLRX_FRAG_IND_MSG_flush_end_seqid 0x00000fc0

#define DLRX_FRAG_IND_MSG_flush_end_seqid_get_indirect(base, offset)	((((*(base + O_DLRX_FRAG_IND_MSG_flush_end_seqid + offset)) & M_DLRX_FRAG_IND_MSG_flush_end_seqid) >> B_DLRX_FRAG_IND_MSG_flush_end_seqid))

#define DLRX_FRAG_IND_MSG_flush_end_seqid_get_direct(dword)	((((dword) & M_DLRX_FRAG_IND_MSG_flush_end_seqid) >> B_DLRX_FRAG_IND_MSG_flush_end_seqid))

#define DLRX_FRAG_IND_MSG_flush_end_seqid_set_indirect(base, offset, val) \
	do {                                                              \
		(*(base + O_DLRX_FRAG_IND_MSG_flush_end_seqid + offset)) &= (~(M_DLRX_FRAG_IND_MSG_flush_end_seqid));    \
		(*(base + O_DLRX_FRAG_IND_MSG_flush_end_seqid + offset)) |= ((val << B_DLRX_FRAG_IND_MSG_flush_end_seqid) & M_DLRX_FRAG_IND_MSG_flush_end_seqid);    \
	} while (0)

#define DLRX_FRAG_IND_MSG_flush_end_seqid_set_direct(dword, val) \
	do {                                                               \
		(dword) &= (~(M_DLRX_FRAG_IND_MSG_flush_end_seqid));    \
		(dword) |= ((val << B_DLRX_FRAG_IND_MSG_flush_end_seqid) & M_DLRX_FRAG_IND_MSG_flush_end_seqid);    \
	} while (0)

#define DLRX_FRAG_IND_MSG_flush_end_seqid_clear_indirect(base, offset)	((*(base + O_DLRX_FRAG_IND_MSG_flush_end_seqid + offset)) &= (~(M_DLRX_FRAG_IND_MSG_flush_end_seqid)))

#define DLRX_FRAG_IND_MSG_flush_end_seqid_clear_direct(dword)	((dword) &= (~(M_DLRX_FRAG_IND_MSG_flush_end_seqid)))

#define O_DLRX_FRAG_IND_MSG_rsvd2 3
#define B_DLRX_FRAG_IND_MSG_rsvd2 12
#define W_DLRX_FRAG_IND_MSG_rsvd2 20
#define M_DLRX_FRAG_IND_MSG_rsvd2 0xfffff000

#define DLRX_FRAG_IND_MSG_rsvd2_get_indirect(base, offset)	((((*(base + O_DLRX_FRAG_IND_MSG_rsvd2 + offset)) & M_DLRX_FRAG_IND_MSG_rsvd2) >> B_DLRX_FRAG_IND_MSG_rsvd2))

#define DLRX_FRAG_IND_MSG_rsvd2_get_direct(dword)	((((dword) & M_DLRX_FRAG_IND_MSG_rsvd2) >> B_DLRX_FRAG_IND_MSG_rsvd2))

#define DLRX_FRAG_IND_MSG_rsvd2_set_indirect(base, offset, val) \
	do {                                                              \
		(*(base + O_DLRX_FRAG_IND_MSG_rsvd2 + offset)) &= (~(M_DLRX_FRAG_IND_MSG_rsvd2));    \
		(*(base + O_DLRX_FRAG_IND_MSG_rsvd2 + offset)) |= ((val << B_DLRX_FRAG_IND_MSG_rsvd2) & M_DLRX_FRAG_IND_MSG_rsvd2);    \
	} while (0)

#define DLRX_FRAG_IND_MSG_rsvd2_set_direct(dword, val) \
	do {                                                               \
		(dword) &= (~(M_DLRX_FRAG_IND_MSG_rsvd2));    \
		(dword) |= ((val << B_DLRX_FRAG_IND_MSG_rsvd2) & M_DLRX_FRAG_IND_MSG_rsvd2);    \
	} while (0)

#define DLRX_FRAG_IND_MSG_rsvd2_clear_indirect(base, offset)	((*(base + O_DLRX_FRAG_IND_MSG_rsvd2 + offset)) &= (~(M_DLRX_FRAG_IND_MSG_rsvd2)))

#define DLRX_FRAG_IND_MSG_rsvd2_clear_direct(dword)	((dword) &= (~(M_DLRX_FRAG_IND_MSG_rsvd2)))

#define O_DLRX_FRAG_IND_MSG_fw_rx_desc_byte_num 4
#define B_DLRX_FRAG_IND_MSG_fw_rx_desc_byte_num 0
#define W_DLRX_FRAG_IND_MSG_fw_rx_desc_byte_num 16
#define M_DLRX_FRAG_IND_MSG_fw_rx_desc_byte_num 0x0000ffff

#define DLRX_FRAG_IND_MSG_fw_rx_desc_byte_num_get_indirect(base, offset)	((((*(base + O_DLRX_FRAG_IND_MSG_fw_rx_desc_byte_num + offset)) & M_DLRX_FRAG_IND_MSG_fw_rx_desc_byte_num) >> B_DLRX_FRAG_IND_MSG_fw_rx_desc_byte_num))

#define DLRX_FRAG_IND_MSG_fw_rx_desc_byte_num_get_direct(dword)	((((dword) & M_DLRX_FRAG_IND_MSG_fw_rx_desc_byte_num) >> B_DLRX_FRAG_IND_MSG_fw_rx_desc_byte_num))

#define DLRX_FRAG_IND_MSG_fw_rx_desc_byte_num_set_indirect(base, offset, val) \
	do {                                                              \
		(*(base + O_DLRX_FRAG_IND_MSG_fw_rx_desc_byte_num + offset)) &= (~(M_DLRX_FRAG_IND_MSG_fw_rx_desc_byte_num));    \
		(*(base + O_DLRX_FRAG_IND_MSG_fw_rx_desc_byte_num + offset)) |= ((val << B_DLRX_FRAG_IND_MSG_fw_rx_desc_byte_num) & M_DLRX_FRAG_IND_MSG_fw_rx_desc_byte_num);    \
	} while (0)

#define DLRX_FRAG_IND_MSG_fw_rx_desc_byte_num_set_direct(dword, val) \
	do {                                                               \
		(dword) &= (~(M_DLRX_FRAG_IND_MSG_fw_rx_desc_byte_num));    \
		(dword) |= ((val << B_DLRX_FRAG_IND_MSG_fw_rx_desc_byte_num) & M_DLRX_FRAG_IND_MSG_fw_rx_desc_byte_num);    \
	} while (0)

#define DLRX_FRAG_IND_MSG_fw_rx_desc_byte_num_clear_indirect(base, offset)	((*(base + O_DLRX_FRAG_IND_MSG_fw_rx_desc_byte_num + offset)) &= (~(M_DLRX_FRAG_IND_MSG_fw_rx_desc_byte_num)))

#define DLRX_FRAG_IND_MSG_fw_rx_desc_byte_num_clear_direct(dword)	((dword) &= (~(M_DLRX_FRAG_IND_MSG_fw_rx_desc_byte_num)))

#define O_DLRX_FRAG_IND_MSG_rsvd3 4
#define B_DLRX_FRAG_IND_MSG_rsvd3 16
#define W_DLRX_FRAG_IND_MSG_rsvd3 16
#define M_DLRX_FRAG_IND_MSG_rsvd3 0xffff0000

#define DLRX_FRAG_IND_MSG_rsvd3_get_indirect(base, offset)	((((*(base + O_DLRX_FRAG_IND_MSG_rsvd3 + offset)) & M_DLRX_FRAG_IND_MSG_rsvd3) >> B_DLRX_FRAG_IND_MSG_rsvd3))

#define DLRX_FRAG_IND_MSG_rsvd3_get_direct(dword)	((((dword) & M_DLRX_FRAG_IND_MSG_rsvd3) >> B_DLRX_FRAG_IND_MSG_rsvd3))

#define DLRX_FRAG_IND_MSG_rsvd3_set_indirect(base, offset, val) \
	do {                                                              \
		(*(base + O_DLRX_FRAG_IND_MSG_rsvd3 + offset)) &= (~(M_DLRX_FRAG_IND_MSG_rsvd3));    \
		(*(base + O_DLRX_FRAG_IND_MSG_rsvd3 + offset)) |= ((val << B_DLRX_FRAG_IND_MSG_rsvd3) & M_DLRX_FRAG_IND_MSG_rsvd3);    \
	} while (0)

#define DLRX_FRAG_IND_MSG_rsvd3_set_direct(dword, val) \
	do {                                                               \
		(dword) &= (~(M_DLRX_FRAG_IND_MSG_rsvd3));    \
		(dword) |= ((val << B_DLRX_FRAG_IND_MSG_rsvd3) & M_DLRX_FRAG_IND_MSG_rsvd3);    \
	} while (0)

#define DLRX_FRAG_IND_MSG_rsvd3_clear_indirect(base, offset)	((*(base + O_DLRX_FRAG_IND_MSG_rsvd3 + offset)) &= (~(M_DLRX_FRAG_IND_MSG_rsvd3)))

#define DLRX_FRAG_IND_MSG_rsvd3_clear_direct(dword)	((dword) &= (~(M_DLRX_FRAG_IND_MSG_rsvd3)))

#define O_DLRX_FRAG_IND_MSG_fw_rx_desc_byte_msdu0 5
#define B_DLRX_FRAG_IND_MSG_fw_rx_desc_byte_msdu0 0
#define W_DLRX_FRAG_IND_MSG_fw_rx_desc_byte_msdu0 8
#define M_DLRX_FRAG_IND_MSG_fw_rx_desc_byte_msdu0 0x000000ff

#define DLRX_FRAG_IND_MSG_fw_rx_desc_byte_msdu0_get_indirect(base, offset)	((((*(base + O_DLRX_FRAG_IND_MSG_fw_rx_desc_byte_msdu0 + offset)) & M_DLRX_FRAG_IND_MSG_fw_rx_desc_byte_msdu0) >> B_DLRX_FRAG_IND_MSG_fw_rx_desc_byte_msdu0))

#define DLRX_FRAG_IND_MSG_fw_rx_desc_byte_msdu0_get_direct(dword)	((((dword) & M_DLRX_FRAG_IND_MSG_fw_rx_desc_byte_msdu0) >> B_DLRX_FRAG_IND_MSG_fw_rx_desc_byte_msdu0))

#define DLRX_FRAG_IND_MSG_fw_rx_desc_byte_msdu0_set_indirect(base, offset, val) \
	do {                                                              \
		(*(base + O_DLRX_FRAG_IND_MSG_fw_rx_desc_byte_msdu0 + offset)) &= (~(M_DLRX_FRAG_IND_MSG_fw_rx_desc_byte_msdu0));    \
		(*(base + O_DLRX_FRAG_IND_MSG_fw_rx_desc_byte_msdu0 + offset)) |= ((val << B_DLRX_FRAG_IND_MSG_fw_rx_desc_byte_msdu0) & M_DLRX_FRAG_IND_MSG_fw_rx_desc_byte_msdu0);    \
	} while (0)

#define DLRX_FRAG_IND_MSG_fw_rx_desc_byte_msdu0_set_direct(dword, val) \
	do {                                                               \
		(dword) &= (~(M_DLRX_FRAG_IND_MSG_fw_rx_desc_byte_msdu0));    \
		(dword) |= ((val << B_DLRX_FRAG_IND_MSG_fw_rx_desc_byte_msdu0) & M_DLRX_FRAG_IND_MSG_fw_rx_desc_byte_msdu0);    \
	} while (0)

#define DLRX_FRAG_IND_MSG_fw_rx_desc_byte_msdu0_clear_indirect(base, offset)	((*(base + O_DLRX_FRAG_IND_MSG_fw_rx_desc_byte_msdu0 + offset)) &= (~(M_DLRX_FRAG_IND_MSG_fw_rx_desc_byte_msdu0)))

#define DLRX_FRAG_IND_MSG_fw_rx_desc_byte_msdu0_clear_direct(dword)	((dword) &= (~(M_DLRX_FRAG_IND_MSG_fw_rx_desc_byte_msdu0)))

#define O_DLRX_FRAG_IND_MSG_padding 5
#define B_DLRX_FRAG_IND_MSG_padding 8
#define W_DLRX_FRAG_IND_MSG_padding 24
#define M_DLRX_FRAG_IND_MSG_padding 0xffffff00

#define DLRX_FRAG_IND_MSG_padding_get_indirect(base, offset)	((((*(base + O_DLRX_FRAG_IND_MSG_padding + offset)) & M_DLRX_FRAG_IND_MSG_padding) >> B_DLRX_FRAG_IND_MSG_padding))

#define DLRX_FRAG_IND_MSG_padding_get_direct(dword)	((((dword) & M_DLRX_FRAG_IND_MSG_padding) >> B_DLRX_FRAG_IND_MSG_padding))

#define DLRX_FRAG_IND_MSG_padding_set_indirect(base, offset, val) \
	do {                                                              \
		(*(base + O_DLRX_FRAG_IND_MSG_padding + offset)) &= (~(M_DLRX_FRAG_IND_MSG_padding));    \
		(*(base + O_DLRX_FRAG_IND_MSG_padding + offset)) |= ((val << B_DLRX_FRAG_IND_MSG_padding) & M_DLRX_FRAG_IND_MSG_padding);    \
	} while (0)

#define DLRX_FRAG_IND_MSG_padding_set_direct(dword, val) \
	do {                                                               \
		(dword) &= (~(M_DLRX_FRAG_IND_MSG_padding));    \
		(dword) |= ((val << B_DLRX_FRAG_IND_MSG_padding) & M_DLRX_FRAG_IND_MSG_padding);    \
	} while (0)

#define DLRX_FRAG_IND_MSG_padding_clear_indirect(base, offset)	((*(base + O_DLRX_FRAG_IND_MSG_padding + offset)) &= (~(M_DLRX_FRAG_IND_MSG_padding)))

#define DLRX_FRAG_IND_MSG_padding_clear_direct(dword)	((dword) &= (~(M_DLRX_FRAG_IND_MSG_padding)))

#define O_DLRX_FRAG_IND_MSG_rxpb_ptr_read_index 6
#define B_DLRX_FRAG_IND_MSG_rxpb_ptr_read_index 0
#define W_DLRX_FRAG_IND_MSG_rxpb_ptr_read_index 12
#define M_DLRX_FRAG_IND_MSG_rxpb_ptr_read_index 0x00000fff

#define DLRX_FRAG_IND_MSG_rxpb_ptr_read_index_get_indirect(base, offset)	((((*(base + O_DLRX_FRAG_IND_MSG_rxpb_ptr_read_index + offset)) & M_DLRX_FRAG_IND_MSG_rxpb_ptr_read_index) >> B_DLRX_FRAG_IND_MSG_rxpb_ptr_read_index))

#define DLRX_FRAG_IND_MSG_rxpb_ptr_read_index_get_direct(dword)	((((dword) & M_DLRX_FRAG_IND_MSG_rxpb_ptr_read_index) >> B_DLRX_FRAG_IND_MSG_rxpb_ptr_read_index))

#define DLRX_FRAG_IND_MSG_rxpb_ptr_read_index_set_indirect(base, offset, val) \
	do {                                                              \
		(*(base + O_DLRX_FRAG_IND_MSG_rxpb_ptr_read_index + offset)) &= (~(M_DLRX_FRAG_IND_MSG_rxpb_ptr_read_index));    \
		(*(base + O_DLRX_FRAG_IND_MSG_rxpb_ptr_read_index + offset)) |= ((val << B_DLRX_FRAG_IND_MSG_rxpb_ptr_read_index) & M_DLRX_FRAG_IND_MSG_rxpb_ptr_read_index);    \
	} while (0)

#define DLRX_FRAG_IND_MSG_rxpb_ptr_read_index_set_direct(dword, val) \
	do {                                                               \
		(dword) &= (~(M_DLRX_FRAG_IND_MSG_rxpb_ptr_read_index));    \
		(dword) |= ((val << B_DLRX_FRAG_IND_MSG_rxpb_ptr_read_index) & M_DLRX_FRAG_IND_MSG_rxpb_ptr_read_index);    \
	} while (0)

#define DLRX_FRAG_IND_MSG_rxpb_ptr_read_index_clear_indirect(base, offset)	((*(base + O_DLRX_FRAG_IND_MSG_rxpb_ptr_read_index + offset)) &= (~(M_DLRX_FRAG_IND_MSG_rxpb_ptr_read_index)))

#define DLRX_FRAG_IND_MSG_rxpb_ptr_read_index_clear_direct(dword)	((dword) &= (~(M_DLRX_FRAG_IND_MSG_rxpb_ptr_read_index)))

#define O_DLRX_FRAG_IND_MSG_rsvd4 6
#define B_DLRX_FRAG_IND_MSG_rsvd4 12
#define W_DLRX_FRAG_IND_MSG_rsvd4 20
#define M_DLRX_FRAG_IND_MSG_rsvd4 0xfffff000

#define DLRX_FRAG_IND_MSG_rsvd4_get_indirect(base, offset)	((((*(base + O_DLRX_FRAG_IND_MSG_rsvd4 + offset)) & M_DLRX_FRAG_IND_MSG_rsvd4) >> B_DLRX_FRAG_IND_MSG_rsvd4))

#define DLRX_FRAG_IND_MSG_rsvd4_get_direct(dword)	((((dword) & M_DLRX_FRAG_IND_MSG_rsvd4) >> B_DLRX_FRAG_IND_MSG_rsvd4))

#define DLRX_FRAG_IND_MSG_rsvd4_set_indirect(base, offset, val) \
	do {                                                              \
		(*(base + O_DLRX_FRAG_IND_MSG_rsvd4 + offset)) &= (~(M_DLRX_FRAG_IND_MSG_rsvd4));    \
		(*(base + O_DLRX_FRAG_IND_MSG_rsvd4 + offset)) |= ((val << B_DLRX_FRAG_IND_MSG_rsvd4) & M_DLRX_FRAG_IND_MSG_rsvd4);    \
	} while (0)

#define DLRX_FRAG_IND_MSG_rsvd4_set_direct(dword, val) \
	do {                                                               \
		(dword) &= (~(M_DLRX_FRAG_IND_MSG_rsvd4));    \
		(dword) |= ((val << B_DLRX_FRAG_IND_MSG_rsvd4) & M_DLRX_FRAG_IND_MSG_rsvd4);    \
	} while (0)

#define DLRX_FRAG_IND_MSG_rsvd4_clear_indirect(base, offset)	((*(base + O_DLRX_FRAG_IND_MSG_rsvd4 + offset)) &= (~(M_DLRX_FRAG_IND_MSG_rsvd4)))

#define DLRX_FRAG_IND_MSG_rsvd4_clear_direct(dword)	((dword) &= (~(M_DLRX_FRAG_IND_MSG_rsvd4)))

#define O_DLRX_TX_CMPL_MSG_htt_hdr 0
#define B_DLRX_TX_CMPL_MSG_htt_hdr 0
#define W_DLRX_TX_CMPL_MSG_htt_hdr 32
#define M_DLRX_TX_CMPL_MSG_htt_hdr 0xffffffff

#define DLRX_TX_CMPL_MSG_htt_hdr_get_indirect(base, offset)	((((*(base + O_DLRX_TX_CMPL_MSG_htt_hdr + offset)) & M_DLRX_TX_CMPL_MSG_htt_hdr) >> B_DLRX_TX_CMPL_MSG_htt_hdr))

#define DLRX_TX_CMPL_MSG_htt_hdr_get_direct(dword)	((((dword) & M_DLRX_TX_CMPL_MSG_htt_hdr) >> B_DLRX_TX_CMPL_MSG_htt_hdr))

#define DLRX_TX_CMPL_MSG_htt_hdr_set_indirect(base, offset, val)    \
	do {                                                              \
		(*(base + O_DLRX_TX_CMPL_MSG_htt_hdr + offset)) &= (~(M_DLRX_TX_CMPL_MSG_htt_hdr));    \
		(*(base + O_DLRX_TX_CMPL_MSG_htt_hdr + offset)) |= ((val << B_DLRX_TX_CMPL_MSG_htt_hdr) & M_DLRX_TX_CMPL_MSG_htt_hdr);    \
	} while (0)

#define DLRX_TX_CMPL_MSG_htt_hdr_set_direct(dword, val)    \
	do {                                                               \
		(dword) &= (~(M_DLRX_TX_CMPL_MSG_htt_hdr));    \
		(dword) |= ((val << B_DLRX_TX_CMPL_MSG_htt_hdr) & M_DLRX_TX_CMPL_MSG_htt_hdr);    \
	} while (0)

#define DLRX_TX_CMPL_MSG_htt_hdr_clear_indirect(base, offset)	((*(base + O_DLRX_TX_CMPL_MSG_htt_hdr + offset)) &= (~(M_DLRX_TX_CMPL_MSG_htt_hdr)))

#define DLRX_TX_CMPL_MSG_htt_hdr_clear_direct(dword)	((dword) &= (~(M_DLRX_TX_CMPL_MSG_htt_hdr)))

#define O_DLRX_TX_CMPL_MSG_msg_type 2
#define B_DLRX_TX_CMPL_MSG_msg_type 0
#define W_DLRX_TX_CMPL_MSG_msg_type 8
#define M_DLRX_TX_CMPL_MSG_msg_type 0x000000ff

#define DLRX_TX_CMPL_MSG_msg_type_get_indirect(base, offset)	((((*(base + O_DLRX_TX_CMPL_MSG_msg_type + offset)) & M_DLRX_TX_CMPL_MSG_msg_type) >> B_DLRX_TX_CMPL_MSG_msg_type))

#define DLRX_TX_CMPL_MSG_msg_type_get_direct(dword)	((((dword) & M_DLRX_TX_CMPL_MSG_msg_type) >> B_DLRX_TX_CMPL_MSG_msg_type))

#define DLRX_TX_CMPL_MSG_msg_type_set_indirect(base, offset, val) \
	do {                                                              \
		(*(base + O_DLRX_TX_CMPL_MSG_msg_type + offset)) &= (~(M_DLRX_TX_CMPL_MSG_msg_type));    \
		(*(base + O_DLRX_TX_CMPL_MSG_msg_type + offset)) |= ((val << B_DLRX_TX_CMPL_MSG_msg_type) & M_DLRX_TX_CMPL_MSG_msg_type);    \
	} while (0)

#define DLRX_TX_CMPL_MSG_msg_type_set_direct(dword, val) \
	do {                                                               \
		(dword) &= (~(M_DLRX_TX_CMPL_MSG_msg_type));    \
		(dword) |= ((val << B_DLRX_TX_CMPL_MSG_msg_type) & M_DLRX_TX_CMPL_MSG_msg_type);    \
	} while (0)

#define DLRX_TX_CMPL_MSG_msg_type_clear_indirect(base, offset)	((*(base + O_DLRX_TX_CMPL_MSG_msg_type + offset)) &= (~(M_DLRX_TX_CMPL_MSG_msg_type)))

#define DLRX_TX_CMPL_MSG_msg_type_clear_direct(dword)	((dword) &= (~(M_DLRX_TX_CMPL_MSG_msg_type)))

#define O_DLRX_TX_CMPL_MSG_status 2
#define B_DLRX_TX_CMPL_MSG_status 8
#define W_DLRX_TX_CMPL_MSG_status 3
#define M_DLRX_TX_CMPL_MSG_status 0x00000700

#define DLRX_TX_CMPL_MSG_status_get_indirect(base, offset)	((((*(base + O_DLRX_TX_CMPL_MSG_status + offset)) & M_DLRX_TX_CMPL_MSG_status) >> B_DLRX_TX_CMPL_MSG_status))

#define DLRX_TX_CMPL_MSG_status_get_direct(dword)	((((dword) & M_DLRX_TX_CMPL_MSG_status) >> B_DLRX_TX_CMPL_MSG_status))

#define DLRX_TX_CMPL_MSG_status_set_indirect(base, offset, val) \
	do {                                                              \
		(*(base + O_DLRX_TX_CMPL_MSG_status + offset)) &= (~(M_DLRX_TX_CMPL_MSG_status));    \
		(*(base + O_DLRX_TX_CMPL_MSG_status + offset)) |= ((val << B_DLRX_TX_CMPL_MSG_status) & M_DLRX_TX_CMPL_MSG_status);    \
	} while (0)

#define DLRX_TX_CMPL_MSG_status_set_direct(dword, val) \
	do {                                                               \
		(dword) &= (~(M_DLRX_TX_CMPL_MSG_status));    \
		(dword) |= ((val << B_DLRX_TX_CMPL_MSG_status) & M_DLRX_TX_CMPL_MSG_status);    \
	} while (0)

#define DLRX_TX_CMPL_MSG_status_clear_indirect(base, offset)	((*(base + O_DLRX_TX_CMPL_MSG_status + offset)) &= (~(M_DLRX_TX_CMPL_MSG_status)))

#define DLRX_TX_CMPL_MSG_status_clear_direct(dword)	((dword) &= (~(M_DLRX_TX_CMPL_MSG_status)))

#define O_DLRX_TX_CMPL_MSG_pb_ptr_rel_num 2
#define B_DLRX_TX_CMPL_MSG_pb_ptr_rel_num 16
#define W_DLRX_TX_CMPL_MSG_pb_ptr_rel_num 8
#define M_DLRX_TX_CMPL_MSG_pb_ptr_rel_num 0x00ff0000

#define DLRX_TX_CMPL_MSG_pb_ptr_rel_num_get_indirect(base, offset)	((((*(base + O_DLRX_TX_CMPL_MSG_pb_ptr_rel_num + offset)) & M_DLRX_TX_CMPL_MSG_pb_ptr_rel_num) >> B_DLRX_TX_CMPL_MSG_pb_ptr_rel_num))

#define DLRX_TX_CMPL_MSG_pb_ptr_rel_num_get_direct(dword)	((((dword) & M_DLRX_TX_CMPL_MSG_pb_ptr_rel_num) >> B_DLRX_TX_CMPL_MSG_pb_ptr_rel_num))

#define DLRX_TX_CMPL_MSG_pb_ptr_rel_num_set_indirect(base, offset, val) \
	do {                                                              \
		(*(base + O_DLRX_TX_CMPL_MSG_pb_ptr_rel_num + offset)) &= (~(M_DLRX_TX_CMPL_MSG_pb_ptr_rel_num));    \
		(*(base + O_DLRX_TX_CMPL_MSG_pb_ptr_rel_num + offset)) |= ((val << B_DLRX_TX_CMPL_MSG_pb_ptr_rel_num) & M_DLRX_TX_CMPL_MSG_pb_ptr_rel_num);    \
	} while (0)

#define DLRX_TX_CMPL_MSG_pb_ptr_rel_num_set_direct(dword, val) \
	do {                                                               \
		(dword) &= (~(M_DLRX_TX_CMPL_MSG_pb_ptr_rel_num));    \
		(dword) |= ((val << B_DLRX_TX_CMPL_MSG_pb_ptr_rel_num) & M_DLRX_TX_CMPL_MSG_pb_ptr_rel_num);    \
	} while (0)

#define DLRX_TX_CMPL_MSG_pb_ptr_rel_num_clear_indirect(base, offset)	((*(base + O_DLRX_TX_CMPL_MSG_pb_ptr_rel_num + offset)) &= (~(M_DLRX_TX_CMPL_MSG_pb_ptr_rel_num)))

#define DLRX_TX_CMPL_MSG_pb_ptr_rel_num_clear_direct(dword)	((dword) &= (~(M_DLRX_TX_CMPL_MSG_pb_ptr_rel_num)))

#define O_DLRX_TX_CMPL_MSG_free_txpb_ptr 3
#define B_DLRX_TX_CMPL_MSG_free_txpb_ptr 0
#define W_DLRX_TX_CMPL_MSG_free_txpb_ptr 32
#define M_DLRX_TX_CMPL_MSG_free_txpb_ptr 0xffffffff

#define DLRX_TX_CMPL_MSG_free_txpb_ptr_get_indirect(base, offset)	((((*(base + O_DLRX_TX_CMPL_MSG_free_txpb_ptr + offset)) & M_DLRX_TX_CMPL_MSG_free_txpb_ptr) >> B_DLRX_TX_CMPL_MSG_free_txpb_ptr))

#define DLRX_TX_CMPL_MSG_free_txpb_ptr_get_direct(dword)	((((dword) & M_DLRX_TX_CMPL_MSG_free_txpb_ptr) >> B_DLRX_TX_CMPL_MSG_free_txpb_ptr))

#define DLRX_TX_CMPL_MSG_free_txpb_ptr_set_indirect(base, offset, val)    \
	do {                                                              \
		(*(base + O_DLRX_TX_CMPL_MSG_free_txpb_ptr + offset)) &= (~(M_DLRX_TX_CMPL_MSG_free_txpb_ptr));    \
		(*(base + O_DLRX_TX_CMPL_MSG_free_txpb_ptr + offset)) |= ((val << B_DLRX_TX_CMPL_MSG_free_txpb_ptr) & M_DLRX_TX_CMPL_MSG_free_txpb_ptr);    \
	} while (0)

#define DLRX_TX_CMPL_MSG_free_txpb_ptr_set_direct(dword, val)    \
	do {                                                               \
		(dword) &= (~(M_DLRX_TX_CMPL_MSG_free_txpb_ptr));    \
		(dword) |= ((val << B_DLRX_TX_CMPL_MSG_free_txpb_ptr) & M_DLRX_TX_CMPL_MSG_free_txpb_ptr);    \
	} while (0)

#define DLRX_TX_CMPL_MSG_free_txpb_ptr_clear_indirect(base, offset)	((*(base + O_DLRX_TX_CMPL_MSG_free_txpb_ptr + offset)) &= (~(M_DLRX_TX_CMPL_MSG_free_txpb_ptr)))

#define DLRX_TX_CMPL_MSG_free_txpb_ptr_clear_direct(dword)	((dword) &= (~(M_DLRX_TX_CMPL_MSG_free_txpb_ptr)))

#define O_DLRX_RO_MAINLIST_last_pn_dw0 0
#define B_DLRX_RO_MAINLIST_last_pn_dw0 0
#define W_DLRX_RO_MAINLIST_last_pn_dw0 32
#define M_DLRX_RO_MAINLIST_last_pn_dw0 0xffffffff

#define DLRX_RO_MAINLIST_last_pn_dw0_get_indirect(base, offset)	((((*(base + O_DLRX_RO_MAINLIST_last_pn_dw0 + offset)) & M_DLRX_RO_MAINLIST_last_pn_dw0) >> B_DLRX_RO_MAINLIST_last_pn_dw0))

#define DLRX_RO_MAINLIST_last_pn_dw0_get_direct(dword)	((((dword) & M_DLRX_RO_MAINLIST_last_pn_dw0) >> B_DLRX_RO_MAINLIST_last_pn_dw0))

#define DLRX_RO_MAINLIST_last_pn_dw0_set_indirect(base, offset, val)    \
	do {                                                              \
		(*(base + O_DLRX_RO_MAINLIST_last_pn_dw0 + offset)) &= (~(M_DLRX_RO_MAINLIST_last_pn_dw0));    \
		(*(base + O_DLRX_RO_MAINLIST_last_pn_dw0 + offset)) |= ((val << B_DLRX_RO_MAINLIST_last_pn_dw0) & M_DLRX_RO_MAINLIST_last_pn_dw0);    \
	} while (0)

#define DLRX_RO_MAINLIST_last_pn_dw0_set_direct(dword, val)    \
	do {                                                               \
		(dword) &= (~(M_DLRX_RO_MAINLIST_last_pn_dw0));    \
		(dword) |= ((val << B_DLRX_RO_MAINLIST_last_pn_dw0) & M_DLRX_RO_MAINLIST_last_pn_dw0);    \
	} while (0)

#define DLRX_RO_MAINLIST_last_pn_dw0_clear_indirect(base, offset)	((*(base + O_DLRX_RO_MAINLIST_last_pn_dw0 + offset)) &= (~(M_DLRX_RO_MAINLIST_last_pn_dw0)))

#define DLRX_RO_MAINLIST_last_pn_dw0_clear_direct(dword)	((dword) &= (~(M_DLRX_RO_MAINLIST_last_pn_dw0)))

#define O_DLRX_RO_MAINLIST_last_pn_dw1 1
#define B_DLRX_RO_MAINLIST_last_pn_dw1 0
#define W_DLRX_RO_MAINLIST_last_pn_dw1 32
#define M_DLRX_RO_MAINLIST_last_pn_dw1 0xffffffff

#define DLRX_RO_MAINLIST_last_pn_dw1_get_indirect(base, offset)	((((*(base + O_DLRX_RO_MAINLIST_last_pn_dw1 + offset)) & M_DLRX_RO_MAINLIST_last_pn_dw1) >> B_DLRX_RO_MAINLIST_last_pn_dw1))

#define DLRX_RO_MAINLIST_last_pn_dw1_get_direct(dword)	((((dword) & M_DLRX_RO_MAINLIST_last_pn_dw1) >> B_DLRX_RO_MAINLIST_last_pn_dw1))

#define DLRX_RO_MAINLIST_last_pn_dw1_set_indirect(base, offset, val)    \
	do {                                                              \
		(*(base + O_DLRX_RO_MAINLIST_last_pn_dw1 + offset)) &= (~(M_DLRX_RO_MAINLIST_last_pn_dw1));    \
		(*(base + O_DLRX_RO_MAINLIST_last_pn_dw1 + offset)) |= ((val << B_DLRX_RO_MAINLIST_last_pn_dw1) & M_DLRX_RO_MAINLIST_last_pn_dw1);    \
	} while (0)

#define DLRX_RO_MAINLIST_last_pn_dw1_set_direct(dword, val)    \
	do {                                                               \
		(dword) &= (~(M_DLRX_RO_MAINLIST_last_pn_dw1));    \
		(dword) |= ((val << B_DLRX_RO_MAINLIST_last_pn_dw1) & M_DLRX_RO_MAINLIST_last_pn_dw1);    \
	} while (0)

#define DLRX_RO_MAINLIST_last_pn_dw1_clear_indirect(base, offset)	((*(base + O_DLRX_RO_MAINLIST_last_pn_dw1 + offset)) &= (~(M_DLRX_RO_MAINLIST_last_pn_dw1)))

#define DLRX_RO_MAINLIST_last_pn_dw1_clear_direct(dword)	((dword) &= (~(M_DLRX_RO_MAINLIST_last_pn_dw1)))

#define O_DLRX_RO_MAINLIST_last_pn_dw2 2
#define B_DLRX_RO_MAINLIST_last_pn_dw2 0
#define W_DLRX_RO_MAINLIST_last_pn_dw2 32
#define M_DLRX_RO_MAINLIST_last_pn_dw2 0xffffffff

#define DLRX_RO_MAINLIST_last_pn_dw2_get_indirect(base, offset)	((((*(base + O_DLRX_RO_MAINLIST_last_pn_dw2 + offset)) & M_DLRX_RO_MAINLIST_last_pn_dw2) >> B_DLRX_RO_MAINLIST_last_pn_dw2))

#define DLRX_RO_MAINLIST_last_pn_dw2_get_direct(dword)	((((dword) & M_DLRX_RO_MAINLIST_last_pn_dw2) >> B_DLRX_RO_MAINLIST_last_pn_dw2))

#define DLRX_RO_MAINLIST_last_pn_dw2_set_indirect(base, offset, val)    \
	do {                                                              \
		(*(base + O_DLRX_RO_MAINLIST_last_pn_dw2 + offset)) &= (~(M_DLRX_RO_MAINLIST_last_pn_dw2));    \
		(*(base + O_DLRX_RO_MAINLIST_last_pn_dw2 + offset)) |= ((val << B_DLRX_RO_MAINLIST_last_pn_dw2) & M_DLRX_RO_MAINLIST_last_pn_dw2);    \
	} while (0)

#define DLRX_RO_MAINLIST_last_pn_dw2_set_direct(dword, val)    \
	do {                                                               \
		(dword) &= (~(M_DLRX_RO_MAINLIST_last_pn_dw2));    \
		(dword) |= ((val << B_DLRX_RO_MAINLIST_last_pn_dw2) & M_DLRX_RO_MAINLIST_last_pn_dw2);    \
	} while (0)

#define DLRX_RO_MAINLIST_last_pn_dw2_clear_indirect(base, offset)	((*(base + O_DLRX_RO_MAINLIST_last_pn_dw2 + offset)) &= (~(M_DLRX_RO_MAINLIST_last_pn_dw2)))

#define DLRX_RO_MAINLIST_last_pn_dw2_clear_direct(dword)	((dword) &= (~(M_DLRX_RO_MAINLIST_last_pn_dw2)))

#define O_DLRX_RO_MAINLIST_last_pn_dw3 3
#define B_DLRX_RO_MAINLIST_last_pn_dw3 0
#define W_DLRX_RO_MAINLIST_last_pn_dw3 32
#define M_DLRX_RO_MAINLIST_last_pn_dw3 0xffffffff

#define DLRX_RO_MAINLIST_last_pn_dw3_get_indirect(base, offset)	((((*(base + O_DLRX_RO_MAINLIST_last_pn_dw3 + offset)) & M_DLRX_RO_MAINLIST_last_pn_dw3) >> B_DLRX_RO_MAINLIST_last_pn_dw3))

#define DLRX_RO_MAINLIST_last_pn_dw3_get_direct(dword)	((((dword) & M_DLRX_RO_MAINLIST_last_pn_dw3) >> B_DLRX_RO_MAINLIST_last_pn_dw3))

#define DLRX_RO_MAINLIST_last_pn_dw3_set_indirect(base, offset, val)    \
	do {                                                              \
		(*(base + O_DLRX_RO_MAINLIST_last_pn_dw3 + offset)) &= (~(M_DLRX_RO_MAINLIST_last_pn_dw3));    \
		(*(base + O_DLRX_RO_MAINLIST_last_pn_dw3 + offset)) |= ((val << B_DLRX_RO_MAINLIST_last_pn_dw3) & M_DLRX_RO_MAINLIST_last_pn_dw3);    \
	} while (0)

#define DLRX_RO_MAINLIST_last_pn_dw3_set_direct(dword, val)    \
	do {                                                               \
		(dword) &= (~(M_DLRX_RO_MAINLIST_last_pn_dw3));    \
		(dword) |= ((val << B_DLRX_RO_MAINLIST_last_pn_dw3) & M_DLRX_RO_MAINLIST_last_pn_dw3);    \
	} while (0)

#define DLRX_RO_MAINLIST_last_pn_dw3_clear_indirect(base, offset)	((*(base + O_DLRX_RO_MAINLIST_last_pn_dw3 + offset)) &= (~(M_DLRX_RO_MAINLIST_last_pn_dw3)))

#define DLRX_RO_MAINLIST_last_pn_dw3_clear_direct(dword)	((dword) &= (~(M_DLRX_RO_MAINLIST_last_pn_dw3)))

#define O_DLRX_RO_MAINLIST_first_ptr 4
#define B_DLRX_RO_MAINLIST_first_ptr 0
#define W_DLRX_RO_MAINLIST_first_ptr 16
#define M_DLRX_RO_MAINLIST_first_ptr 0x0000ffff

#define DLRX_RO_MAINLIST_first_ptr_get_indirect(base, offset)	((((*(base + O_DLRX_RO_MAINLIST_first_ptr + offset)) & M_DLRX_RO_MAINLIST_first_ptr) >> B_DLRX_RO_MAINLIST_first_ptr))

#define DLRX_RO_MAINLIST_first_ptr_get_direct(dword)	((((dword) & M_DLRX_RO_MAINLIST_first_ptr) >> B_DLRX_RO_MAINLIST_first_ptr))

#define DLRX_RO_MAINLIST_first_ptr_set_indirect(base, offset, val) \
	do {                                                              \
		(*(base + O_DLRX_RO_MAINLIST_first_ptr + offset)) &= (~(M_DLRX_RO_MAINLIST_first_ptr));    \
		(*(base + O_DLRX_RO_MAINLIST_first_ptr + offset)) |= ((val << B_DLRX_RO_MAINLIST_first_ptr) & M_DLRX_RO_MAINLIST_first_ptr);    \
	} while (0)

#define DLRX_RO_MAINLIST_first_ptr_set_direct(dword, val) \
	do {                                                               \
		(dword) &= (~(M_DLRX_RO_MAINLIST_first_ptr));    \
		(dword) |= ((val << B_DLRX_RO_MAINLIST_first_ptr) & M_DLRX_RO_MAINLIST_first_ptr);    \
	} while (0)

#define DLRX_RO_MAINLIST_first_ptr_clear_indirect(base, offset)	((*(base + O_DLRX_RO_MAINLIST_first_ptr + offset)) &= (~(M_DLRX_RO_MAINLIST_first_ptr)))

#define DLRX_RO_MAINLIST_first_ptr_clear_direct(dword)	((dword) &= (~(M_DLRX_RO_MAINLIST_first_ptr)))

#define O_DLRX_RO_MAINLIST_msdu_num 4
#define B_DLRX_RO_MAINLIST_msdu_num 16
#define W_DLRX_RO_MAINLIST_msdu_num 15
#define M_DLRX_RO_MAINLIST_msdu_num 0x7fff0000

#define DLRX_RO_MAINLIST_msdu_num_get_indirect(base, offset)	((((*(base + O_DLRX_RO_MAINLIST_msdu_num + offset)) & M_DLRX_RO_MAINLIST_msdu_num) >> B_DLRX_RO_MAINLIST_msdu_num))

#define DLRX_RO_MAINLIST_msdu_num_get_direct(dword)	((((dword) & M_DLRX_RO_MAINLIST_msdu_num) >> B_DLRX_RO_MAINLIST_msdu_num))

#define DLRX_RO_MAINLIST_msdu_num_set_indirect(base, offset, val) \
	do {                                                              \
		(*(base + O_DLRX_RO_MAINLIST_msdu_num + offset)) &= (~(M_DLRX_RO_MAINLIST_msdu_num));    \
		(*(base + O_DLRX_RO_MAINLIST_msdu_num + offset)) |= ((val << B_DLRX_RO_MAINLIST_msdu_num) & M_DLRX_RO_MAINLIST_msdu_num);    \
	} while (0)

#define DLRX_RO_MAINLIST_msdu_num_set_direct(dword, val) \
	do {                                                               \
		(dword) &= (~(M_DLRX_RO_MAINLIST_msdu_num));    \
		(dword) |= ((val << B_DLRX_RO_MAINLIST_msdu_num) & M_DLRX_RO_MAINLIST_msdu_num);    \
	} while (0)

#define DLRX_RO_MAINLIST_msdu_num_clear_indirect(base, offset)	((*(base + O_DLRX_RO_MAINLIST_msdu_num + offset)) &= (~(M_DLRX_RO_MAINLIST_msdu_num)))

#define DLRX_RO_MAINLIST_msdu_num_clear_direct(dword)	((dword) &= (~(M_DLRX_RO_MAINLIST_msdu_num)))

#define O_DLRX_RO_MAINLIST_mcast_bcast 4
#define B_DLRX_RO_MAINLIST_mcast_bcast 31
#define W_DLRX_RO_MAINLIST_mcast_bcast 1
#define M_DLRX_RO_MAINLIST_mcast_bcast 0x80000000

#define DLRX_RO_MAINLIST_mcast_bcast_get_indirect(base, offset)	((((*(base + O_DLRX_RO_MAINLIST_mcast_bcast + offset)) & M_DLRX_RO_MAINLIST_mcast_bcast) >> B_DLRX_RO_MAINLIST_mcast_bcast))

#define DLRX_RO_MAINLIST_mcast_bcast_get_direct(dword)	((((dword) & M_DLRX_RO_MAINLIST_mcast_bcast) >> B_DLRX_RO_MAINLIST_mcast_bcast))

#define DLRX_RO_MAINLIST_mcast_bcast_set_indirect(base, offset, val) \
	do {                                                              \
		(*(base + O_DLRX_RO_MAINLIST_mcast_bcast + offset)) &= (~(M_DLRX_RO_MAINLIST_mcast_bcast));    \
		(*(base + O_DLRX_RO_MAINLIST_mcast_bcast + offset)) |= ((val << B_DLRX_RO_MAINLIST_mcast_bcast) & M_DLRX_RO_MAINLIST_mcast_bcast);    \
	} while (0)

#define DLRX_RO_MAINLIST_mcast_bcast_set_direct(dword, val) \
	do {                                                               \
		(dword) &= (~(M_DLRX_RO_MAINLIST_mcast_bcast));    \
		(dword) |= ((val << B_DLRX_RO_MAINLIST_mcast_bcast) & M_DLRX_RO_MAINLIST_mcast_bcast);    \
	} while (0)

#define DLRX_RO_MAINLIST_mcast_bcast_clear_indirect(base, offset)	((*(base + O_DLRX_RO_MAINLIST_mcast_bcast + offset)) &= (~(M_DLRX_RO_MAINLIST_mcast_bcast)))

#define DLRX_RO_MAINLIST_mcast_bcast_clear_direct(dword)	((dword) &= (~(M_DLRX_RO_MAINLIST_mcast_bcast)))

#define O_DLRX_RO_LINKLIST_pn_dw0 0
#define B_DLRX_RO_LINKLIST_pn_dw0 0
#define W_DLRX_RO_LINKLIST_pn_dw0 32
#define M_DLRX_RO_LINKLIST_pn_dw0 0xffffffff

#define DLRX_RO_LINKLIST_pn_dw0_get_indirect(base, offset)	((((*(base + O_DLRX_RO_LINKLIST_pn_dw0 + offset)) & M_DLRX_RO_LINKLIST_pn_dw0) >> B_DLRX_RO_LINKLIST_pn_dw0))

#define DLRX_RO_LINKLIST_pn_dw0_get_direct(dword)	((((dword) & M_DLRX_RO_LINKLIST_pn_dw0) >> B_DLRX_RO_LINKLIST_pn_dw0))

#define DLRX_RO_LINKLIST_pn_dw0_set_indirect(base, offset, val)    \
	do {                                                              \
		(*(base + O_DLRX_RO_LINKLIST_pn_dw0 + offset)) &= (~(M_DLRX_RO_LINKLIST_pn_dw0));    \
		(*(base + O_DLRX_RO_LINKLIST_pn_dw0 + offset)) |= ((val << B_DLRX_RO_LINKLIST_pn_dw0) & M_DLRX_RO_LINKLIST_pn_dw0);    \
	} while (0)

#define DLRX_RO_LINKLIST_pn_dw0_set_direct(dword, val)    \
	do {                                                               \
		(dword) &= (~(M_DLRX_RO_LINKLIST_pn_dw0));    \
		(dword) |= ((val << B_DLRX_RO_LINKLIST_pn_dw0) & M_DLRX_RO_LINKLIST_pn_dw0);    \
	} while (0)

#define DLRX_RO_LINKLIST_pn_dw0_clear_indirect(base, offset)	((*(base + O_DLRX_RO_LINKLIST_pn_dw0 + offset)) &= (~(M_DLRX_RO_LINKLIST_pn_dw0)))

#define DLRX_RO_LINKLIST_pn_dw0_clear_direct(dword)	((dword) &= (~(M_DLRX_RO_LINKLIST_pn_dw0)))

#define O_DLRX_RO_LINKLIST_pn_dw1 1
#define B_DLRX_RO_LINKLIST_pn_dw1 0
#define W_DLRX_RO_LINKLIST_pn_dw1 32
#define M_DLRX_RO_LINKLIST_pn_dw1 0xffffffff

#define DLRX_RO_LINKLIST_pn_dw1_get_indirect(base, offset)	((((*(base + O_DLRX_RO_LINKLIST_pn_dw1 + offset)) & M_DLRX_RO_LINKLIST_pn_dw1) >> B_DLRX_RO_LINKLIST_pn_dw1))

#define DLRX_RO_LINKLIST_pn_dw1_get_direct(dword)	((((dword) & M_DLRX_RO_LINKLIST_pn_dw1) >> B_DLRX_RO_LINKLIST_pn_dw1))

#define DLRX_RO_LINKLIST_pn_dw1_set_indirect(base, offset, val)    \
	do {                                                              \
		(*(base + O_DLRX_RO_LINKLIST_pn_dw1 + offset)) &= (~(M_DLRX_RO_LINKLIST_pn_dw1));    \
		(*(base + O_DLRX_RO_LINKLIST_pn_dw1 + offset)) |= ((val << B_DLRX_RO_LINKLIST_pn_dw1) & M_DLRX_RO_LINKLIST_pn_dw1);    \
	} while (0)

#define DLRX_RO_LINKLIST_pn_dw1_set_direct(dword, val)    \
	do {                                                               \
		(dword) &= (~(M_DLRX_RO_LINKLIST_pn_dw1));    \
		(dword) |= ((val << B_DLRX_RO_LINKLIST_pn_dw1) & M_DLRX_RO_LINKLIST_pn_dw1);    \
	} while (0)

#define DLRX_RO_LINKLIST_pn_dw1_clear_indirect(base, offset)	((*(base + O_DLRX_RO_LINKLIST_pn_dw1 + offset)) &= (~(M_DLRX_RO_LINKLIST_pn_dw1)))

#define DLRX_RO_LINKLIST_pn_dw1_clear_direct(dword)	((dword) &= (~(M_DLRX_RO_LINKLIST_pn_dw1)))

#define O_DLRX_RO_LINKLIST_pn_dw2 2
#define B_DLRX_RO_LINKLIST_pn_dw2 0
#define W_DLRX_RO_LINKLIST_pn_dw2 32
#define M_DLRX_RO_LINKLIST_pn_dw2 0xffffffff

#define DLRX_RO_LINKLIST_pn_dw2_get_indirect(base, offset)	((((*(base + O_DLRX_RO_LINKLIST_pn_dw2 + offset)) & M_DLRX_RO_LINKLIST_pn_dw2) >> B_DLRX_RO_LINKLIST_pn_dw2))

#define DLRX_RO_LINKLIST_pn_dw2_get_direct(dword)	((((dword) & M_DLRX_RO_LINKLIST_pn_dw2) >> B_DLRX_RO_LINKLIST_pn_dw2))

#define DLRX_RO_LINKLIST_pn_dw2_set_indirect(base, offset, val)    \
	do {                                                              \
		(*(base + O_DLRX_RO_LINKLIST_pn_dw2 + offset)) &= (~(M_DLRX_RO_LINKLIST_pn_dw2));    \
		(*(base + O_DLRX_RO_LINKLIST_pn_dw2 + offset)) |= ((val << B_DLRX_RO_LINKLIST_pn_dw2) & M_DLRX_RO_LINKLIST_pn_dw2);    \
	} while (0)

#define DLRX_RO_LINKLIST_pn_dw2_set_direct(dword, val)    \
	do {                                                               \
		(dword) &= (~(M_DLRX_RO_LINKLIST_pn_dw2));    \
		(dword) |= ((val << B_DLRX_RO_LINKLIST_pn_dw2) & M_DLRX_RO_LINKLIST_pn_dw2);    \
	} while (0)

#define DLRX_RO_LINKLIST_pn_dw2_clear_indirect(base, offset)	((*(base + O_DLRX_RO_LINKLIST_pn_dw2 + offset)) &= (~(M_DLRX_RO_LINKLIST_pn_dw2)))

#define DLRX_RO_LINKLIST_pn_dw2_clear_direct(dword)	((dword) &= (~(M_DLRX_RO_LINKLIST_pn_dw2)))

#define O_DLRX_RO_LINKLIST_pn_dw3 3
#define B_DLRX_RO_LINKLIST_pn_dw3 0
#define W_DLRX_RO_LINKLIST_pn_dw3 32
#define M_DLRX_RO_LINKLIST_pn_dw3 0xffffffff

#define DLRX_RO_LINKLIST_pn_dw3_get_indirect(base, offset)	((((*(base + O_DLRX_RO_LINKLIST_pn_dw3 + offset)) & M_DLRX_RO_LINKLIST_pn_dw3) >> B_DLRX_RO_LINKLIST_pn_dw3))

#define DLRX_RO_LINKLIST_pn_dw3_get_direct(dword)	((((dword) & M_DLRX_RO_LINKLIST_pn_dw3) >> B_DLRX_RO_LINKLIST_pn_dw3))

#define DLRX_RO_LINKLIST_pn_dw3_set_indirect(base, offset, val)    \
	do {                                                              \
		(*(base + O_DLRX_RO_LINKLIST_pn_dw3 + offset)) &= (~(M_DLRX_RO_LINKLIST_pn_dw3));    \
		(*(base + O_DLRX_RO_LINKLIST_pn_dw3 + offset)) |= ((val << B_DLRX_RO_LINKLIST_pn_dw3) & M_DLRX_RO_LINKLIST_pn_dw3);    \
	} while (0)

#define DLRX_RO_LINKLIST_pn_dw3_set_direct(dword, val)    \
	do {                                                               \
		(dword) &= (~(M_DLRX_RO_LINKLIST_pn_dw3));    \
		(dword) |= ((val << B_DLRX_RO_LINKLIST_pn_dw3) & M_DLRX_RO_LINKLIST_pn_dw3);    \
	} while (0)

#define DLRX_RO_LINKLIST_pn_dw3_clear_indirect(base, offset)	((*(base + O_DLRX_RO_LINKLIST_pn_dw3 + offset)) &= (~(M_DLRX_RO_LINKLIST_pn_dw3)))

#define DLRX_RO_LINKLIST_pn_dw3_clear_direct(dword)	((dword) &= (~(M_DLRX_RO_LINKLIST_pn_dw3)))

#define O_DLRX_RO_LINKLIST_msdu_len 4
#define B_DLRX_RO_LINKLIST_msdu_len 0
#define W_DLRX_RO_LINKLIST_msdu_len 16
#define M_DLRX_RO_LINKLIST_msdu_len 0x0000ffff

#define DLRX_RO_LINKLIST_msdu_len_get_indirect(base, offset)	((((*(base + O_DLRX_RO_LINKLIST_msdu_len + offset)) & M_DLRX_RO_LINKLIST_msdu_len) >> B_DLRX_RO_LINKLIST_msdu_len))

#define DLRX_RO_LINKLIST_msdu_len_get_direct(dword)	((((dword) & M_DLRX_RO_LINKLIST_msdu_len) >> B_DLRX_RO_LINKLIST_msdu_len))

#define DLRX_RO_LINKLIST_msdu_len_set_indirect(base, offset, val) \
	do {                                                              \
		(*(base + O_DLRX_RO_LINKLIST_msdu_len + offset)) &= (~(M_DLRX_RO_LINKLIST_msdu_len));    \
		(*(base + O_DLRX_RO_LINKLIST_msdu_len + offset)) |= ((val << B_DLRX_RO_LINKLIST_msdu_len) & M_DLRX_RO_LINKLIST_msdu_len);    \
	} while (0)

#define DLRX_RO_LINKLIST_msdu_len_set_direct(dword, val) \
	do {                                                               \
		(dword) &= (~(M_DLRX_RO_LINKLIST_msdu_len));    \
		(dword) |= ((val << B_DLRX_RO_LINKLIST_msdu_len) & M_DLRX_RO_LINKLIST_msdu_len);    \
	} while (0)

#define DLRX_RO_LINKLIST_msdu_len_clear_indirect(base, offset)	((*(base + O_DLRX_RO_LINKLIST_msdu_len + offset)) &= (~(M_DLRX_RO_LINKLIST_msdu_len)))

#define DLRX_RO_LINKLIST_msdu_len_clear_direct(dword)	((dword) &= (~(M_DLRX_RO_LINKLIST_msdu_len)))

#define O_DLRX_RO_LINKLIST_fwd 4
#define B_DLRX_RO_LINKLIST_fwd 16
#define W_DLRX_RO_LINKLIST_fwd 1
#define M_DLRX_RO_LINKLIST_fwd 0x00010000

#define DLRX_RO_LINKLIST_fwd_get_indirect(base, offset)	((((*(base + O_DLRX_RO_LINKLIST_fwd + offset)) & M_DLRX_RO_LINKLIST_fwd) >> B_DLRX_RO_LINKLIST_fwd))

#define DLRX_RO_LINKLIST_fwd_get_direct(dword)	((((dword) & M_DLRX_RO_LINKLIST_fwd) >> B_DLRX_RO_LINKLIST_fwd))

#define DLRX_RO_LINKLIST_fwd_set_indirect(base, offset, val) \
	do {                                                              \
		(*(base + O_DLRX_RO_LINKLIST_fwd + offset)) &= (~(M_DLRX_RO_LINKLIST_fwd));    \
		(*(base + O_DLRX_RO_LINKLIST_fwd + offset)) |= ((val << B_DLRX_RO_LINKLIST_fwd) & M_DLRX_RO_LINKLIST_fwd);    \
	} while (0)

#define DLRX_RO_LINKLIST_fwd_set_direct(dword, val) \
	do {                                                               \
		(dword) &= (~(M_DLRX_RO_LINKLIST_fwd));    \
		(dword) |= ((val << B_DLRX_RO_LINKLIST_fwd) & M_DLRX_RO_LINKLIST_fwd);    \
	} while (0)

#define DLRX_RO_LINKLIST_fwd_clear_indirect(base, offset)	((*(base + O_DLRX_RO_LINKLIST_fwd + offset)) &= (~(M_DLRX_RO_LINKLIST_fwd)))

#define DLRX_RO_LINKLIST_fwd_clear_direct(dword)	((dword) &= (~(M_DLRX_RO_LINKLIST_fwd)))

#define O_DLRX_RO_LINKLIST_discard 4
#define B_DLRX_RO_LINKLIST_discard 17
#define W_DLRX_RO_LINKLIST_discard 1
#define M_DLRX_RO_LINKLIST_discard 0x00020000

#define DLRX_RO_LINKLIST_discard_get_indirect(base, offset)	((((*(base + O_DLRX_RO_LINKLIST_discard + offset)) & M_DLRX_RO_LINKLIST_discard) >> B_DLRX_RO_LINKLIST_discard))

#define DLRX_RO_LINKLIST_discard_get_direct(dword)	((((dword) & M_DLRX_RO_LINKLIST_discard) >> B_DLRX_RO_LINKLIST_discard))

#define DLRX_RO_LINKLIST_discard_set_indirect(base, offset, val) \
	do {                                                              \
		(*(base + O_DLRX_RO_LINKLIST_discard + offset)) &= (~(M_DLRX_RO_LINKLIST_discard));    \
		(*(base + O_DLRX_RO_LINKLIST_discard + offset)) |= ((val << B_DLRX_RO_LINKLIST_discard) & M_DLRX_RO_LINKLIST_discard);    \
	} while (0)

#define DLRX_RO_LINKLIST_discard_set_direct(dword, val) \
	do {                                                               \
		(dword) &= (~(M_DLRX_RO_LINKLIST_discard));    \
		(dword) |= ((val << B_DLRX_RO_LINKLIST_discard) & M_DLRX_RO_LINKLIST_discard);    \
	} while (0)

#define DLRX_RO_LINKLIST_discard_clear_indirect(base, offset)	((*(base + O_DLRX_RO_LINKLIST_discard + offset)) &= (~(M_DLRX_RO_LINKLIST_discard)))

#define DLRX_RO_LINKLIST_discard_clear_direct(dword)	((dword) &= (~(M_DLRX_RO_LINKLIST_discard)))

#define O_DLRX_RO_LINKLIST_inspect 4
#define B_DLRX_RO_LINKLIST_inspect 18
#define W_DLRX_RO_LINKLIST_inspect 1
#define M_DLRX_RO_LINKLIST_inspect 0x00040000

#define DLRX_RO_LINKLIST_inspect_get_indirect(base, offset)	((((*(base + O_DLRX_RO_LINKLIST_inspect + offset)) & M_DLRX_RO_LINKLIST_inspect) >> B_DLRX_RO_LINKLIST_inspect))

#define DLRX_RO_LINKLIST_inspect_get_direct(dword)	((((dword) & M_DLRX_RO_LINKLIST_inspect) >> B_DLRX_RO_LINKLIST_inspect))

#define DLRX_RO_LINKLIST_inspect_set_indirect(base, offset, val) \
	do {                                                              \
		(*(base + O_DLRX_RO_LINKLIST_inspect + offset)) &= (~(M_DLRX_RO_LINKLIST_inspect));    \
		(*(base + O_DLRX_RO_LINKLIST_inspect + offset)) |= ((val << B_DLRX_RO_LINKLIST_inspect) & M_DLRX_RO_LINKLIST_inspect);    \
	} while (0)

#define DLRX_RO_LINKLIST_inspect_set_direct(dword, val) \
	do {                                                               \
		(dword) &= (~(M_DLRX_RO_LINKLIST_inspect));    \
		(dword) |= ((val << B_DLRX_RO_LINKLIST_inspect) & M_DLRX_RO_LINKLIST_inspect);    \
	} while (0)

#define DLRX_RO_LINKLIST_inspect_clear_indirect(base, offset)	((*(base + O_DLRX_RO_LINKLIST_inspect + offset)) &= (~(M_DLRX_RO_LINKLIST_inspect)))

#define DLRX_RO_LINKLIST_inspect_clear_direct(dword)	((dword) &= (~(M_DLRX_RO_LINKLIST_inspect)))

#define O_DLRX_RO_LINKLIST_rsvd0 4
#define B_DLRX_RO_LINKLIST_rsvd0 19
#define W_DLRX_RO_LINKLIST_rsvd0 1
#define M_DLRX_RO_LINKLIST_rsvd0 0x00080000

#define DLRX_RO_LINKLIST_rsvd0_get_indirect(base, offset)	((((*(base + O_DLRX_RO_LINKLIST_rsvd0 + offset)) & M_DLRX_RO_LINKLIST_rsvd0) >> B_DLRX_RO_LINKLIST_rsvd0))

#define DLRX_RO_LINKLIST_rsvd0_get_direct(dword)	((((dword) & M_DLRX_RO_LINKLIST_rsvd0) >> B_DLRX_RO_LINKLIST_rsvd0))

#define DLRX_RO_LINKLIST_rsvd0_set_indirect(base, offset, val) \
	do {                                                              \
		(*(base + O_DLRX_RO_LINKLIST_rsvd0 + offset)) &= (~(M_DLRX_RO_LINKLIST_rsvd0));    \
		(*(base + O_DLRX_RO_LINKLIST_rsvd0 + offset)) |= ((val << B_DLRX_RO_LINKLIST_rsvd0) & M_DLRX_RO_LINKLIST_rsvd0);    \
	} while (0)

#define DLRX_RO_LINKLIST_rsvd0_set_direct(dword, val) \
	do {                                                               \
		(dword) &= (~(M_DLRX_RO_LINKLIST_rsvd0));    \
		(dword) |= ((val << B_DLRX_RO_LINKLIST_rsvd0) & M_DLRX_RO_LINKLIST_rsvd0);    \
	} while (0)

#define DLRX_RO_LINKLIST_rsvd0_clear_indirect(base, offset)	((*(base + O_DLRX_RO_LINKLIST_rsvd0 + offset)) &= (~(M_DLRX_RO_LINKLIST_rsvd0)))

#define DLRX_RO_LINKLIST_rsvd0_clear_direct(dword)	((dword) &= (~(M_DLRX_RO_LINKLIST_rsvd0)))

#define O_DLRX_RO_LINKLIST_next_ptr 4
#define B_DLRX_RO_LINKLIST_next_ptr 20
#define W_DLRX_RO_LINKLIST_next_ptr 12
#define M_DLRX_RO_LINKLIST_next_ptr 0xfff00000

#define DLRX_RO_LINKLIST_next_ptr_get_indirect(base, offset)	((((*(base + O_DLRX_RO_LINKLIST_next_ptr + offset)) & M_DLRX_RO_LINKLIST_next_ptr) >> B_DLRX_RO_LINKLIST_next_ptr))

#define DLRX_RO_LINKLIST_next_ptr_get_direct(dword)	((((dword) & M_DLRX_RO_LINKLIST_next_ptr) >> B_DLRX_RO_LINKLIST_next_ptr))

#define DLRX_RO_LINKLIST_next_ptr_set_indirect(base, offset, val) \
	do {                                                              \
		(*(base + O_DLRX_RO_LINKLIST_next_ptr + offset)) &= (~(M_DLRX_RO_LINKLIST_next_ptr));    \
		(*(base + O_DLRX_RO_LINKLIST_next_ptr + offset)) |= ((val << B_DLRX_RO_LINKLIST_next_ptr) & M_DLRX_RO_LINKLIST_next_ptr);    \
	} while (0)

#define DLRX_RO_LINKLIST_next_ptr_set_direct(dword, val) \
	do {                                                               \
		(dword) &= (~(M_DLRX_RO_LINKLIST_next_ptr));    \
		(dword) |= ((val << B_DLRX_RO_LINKLIST_next_ptr) & M_DLRX_RO_LINKLIST_next_ptr);    \
	} while (0)

#define DLRX_RO_LINKLIST_next_ptr_clear_indirect(base, offset)	((*(base + O_DLRX_RO_LINKLIST_next_ptr + offset)) &= (~(M_DLRX_RO_LINKLIST_next_ptr)))

#define DLRX_RO_LINKLIST_next_ptr_clear_direct(dword)	((dword) &= (~(M_DLRX_RO_LINKLIST_next_ptr)))

#define O_DLRX_RO_LINKLIST_rxpb_ptr 5
#define B_DLRX_RO_LINKLIST_rxpb_ptr 0
#define W_DLRX_RO_LINKLIST_rxpb_ptr 32
#define M_DLRX_RO_LINKLIST_rxpb_ptr 0xffffffff

#define DLRX_RO_LINKLIST_rxpb_ptr_get_indirect(base, offset)	((((*(base + O_DLRX_RO_LINKLIST_rxpb_ptr + offset)) & M_DLRX_RO_LINKLIST_rxpb_ptr) >> B_DLRX_RO_LINKLIST_rxpb_ptr))

#define DLRX_RO_LINKLIST_rxpb_ptr_get_direct(dword)	((((dword) & M_DLRX_RO_LINKLIST_rxpb_ptr) >> B_DLRX_RO_LINKLIST_rxpb_ptr))

#define DLRX_RO_LINKLIST_rxpb_ptr_set_indirect(base, offset, val)    \
	do {                                                              \
		(*(base + O_DLRX_RO_LINKLIST_rxpb_ptr + offset)) &= (~(M_DLRX_RO_LINKLIST_rxpb_ptr));    \
		(*(base + O_DLRX_RO_LINKLIST_rxpb_ptr + offset)) |= ((val << B_DLRX_RO_LINKLIST_rxpb_ptr) & M_DLRX_RO_LINKLIST_rxpb_ptr);    \
	} while (0)

#define DLRX_RO_LINKLIST_rxpb_ptr_set_direct(dword, val)    \
	do {                                                               \
		(dword) &= (~(M_DLRX_RO_LINKLIST_rxpb_ptr));    \
		(dword) |= ((val << B_DLRX_RO_LINKLIST_rxpb_ptr) & M_DLRX_RO_LINKLIST_rxpb_ptr);    \
	} while (0)

#define DLRX_RO_LINKLIST_rxpb_ptr_clear_indirect(base, offset)	((*(base + O_DLRX_RO_LINKLIST_rxpb_ptr + offset)) &= (~(M_DLRX_RO_LINKLIST_rxpb_ptr)))

#define DLRX_RO_LINKLIST_rxpb_ptr_clear_direct(dword)	((dword) &= (~(M_DLRX_RO_LINKLIST_rxpb_ptr)))

#define O_DLRX_RXPB_PTR_REL_MSG_rsvd0 0
#define B_DLRX_RXPB_PTR_REL_MSG_rsvd0 0
#define W_DLRX_RXPB_PTR_REL_MSG_rsvd0 16
#define M_DLRX_RXPB_PTR_REL_MSG_rsvd0 0x0000ffff

#define DLRX_RXPB_PTR_REL_MSG_rsvd0_get_indirect(base, offset)	((((*(base + O_DLRX_RXPB_PTR_REL_MSG_rsvd0 + offset)) & M_DLRX_RXPB_PTR_REL_MSG_rsvd0) >> B_DLRX_RXPB_PTR_REL_MSG_rsvd0))

#define DLRX_RXPB_PTR_REL_MSG_rsvd0_get_direct(dword)	((((dword) & M_DLRX_RXPB_PTR_REL_MSG_rsvd0) >> B_DLRX_RXPB_PTR_REL_MSG_rsvd0))

#define DLRX_RXPB_PTR_REL_MSG_rsvd0_set_indirect(base, offset, val) \
	do {                                                              \
		(*(base + O_DLRX_RXPB_PTR_REL_MSG_rsvd0 + offset)) &= (~(M_DLRX_RXPB_PTR_REL_MSG_rsvd0));    \
		(*(base + O_DLRX_RXPB_PTR_REL_MSG_rsvd0 + offset)) |= ((val << B_DLRX_RXPB_PTR_REL_MSG_rsvd0) & M_DLRX_RXPB_PTR_REL_MSG_rsvd0);    \
	} while (0)

#define DLRX_RXPB_PTR_REL_MSG_rsvd0_set_direct(dword, val) \
	do {                                                               \
		(dword) &= (~(M_DLRX_RXPB_PTR_REL_MSG_rsvd0));    \
		(dword) |= ((val << B_DLRX_RXPB_PTR_REL_MSG_rsvd0) & M_DLRX_RXPB_PTR_REL_MSG_rsvd0);    \
	} while (0)

#define DLRX_RXPB_PTR_REL_MSG_rsvd0_clear_indirect(base, offset)	((*(base + O_DLRX_RXPB_PTR_REL_MSG_rsvd0 + offset)) &= (~(M_DLRX_RXPB_PTR_REL_MSG_rsvd0)))

#define DLRX_RXPB_PTR_REL_MSG_rsvd0_clear_direct(dword)	((dword) &= (~(M_DLRX_RXPB_PTR_REL_MSG_rsvd0)))

#define O_DLRX_RXPB_PTR_REL_MSG_pb_ptr_rel_num 0
#define B_DLRX_RXPB_PTR_REL_MSG_pb_ptr_rel_num 16
#define W_DLRX_RXPB_PTR_REL_MSG_pb_ptr_rel_num 7
#define M_DLRX_RXPB_PTR_REL_MSG_pb_ptr_rel_num 0x007f0000

#define DLRX_RXPB_PTR_REL_MSG_pb_ptr_rel_num_get_indirect(base, offset)	((((*(base + O_DLRX_RXPB_PTR_REL_MSG_pb_ptr_rel_num + offset)) & M_DLRX_RXPB_PTR_REL_MSG_pb_ptr_rel_num) >> B_DLRX_RXPB_PTR_REL_MSG_pb_ptr_rel_num))

#define DLRX_RXPB_PTR_REL_MSG_pb_ptr_rel_num_get_direct(dword)	((((dword) & M_DLRX_RXPB_PTR_REL_MSG_pb_ptr_rel_num) >> B_DLRX_RXPB_PTR_REL_MSG_pb_ptr_rel_num))

#define DLRX_RXPB_PTR_REL_MSG_pb_ptr_rel_num_set_indirect(base, offset, val) \
	do {                                                              \
		(*(base + O_DLRX_RXPB_PTR_REL_MSG_pb_ptr_rel_num + offset)) &= (~(M_DLRX_RXPB_PTR_REL_MSG_pb_ptr_rel_num));    \
		(*(base + O_DLRX_RXPB_PTR_REL_MSG_pb_ptr_rel_num + offset)) |= ((val << B_DLRX_RXPB_PTR_REL_MSG_pb_ptr_rel_num) & M_DLRX_RXPB_PTR_REL_MSG_pb_ptr_rel_num);    \
	} while (0)

#define DLRX_RXPB_PTR_REL_MSG_pb_ptr_rel_num_set_direct(dword, val) \
	do {                                                               \
		(dword) &= (~(M_DLRX_RXPB_PTR_REL_MSG_pb_ptr_rel_num));    \
		(dword) |= ((val << B_DLRX_RXPB_PTR_REL_MSG_pb_ptr_rel_num) & M_DLRX_RXPB_PTR_REL_MSG_pb_ptr_rel_num);    \
	} while (0)

#define DLRX_RXPB_PTR_REL_MSG_pb_ptr_rel_num_clear_indirect(base, offset)	((*(base + O_DLRX_RXPB_PTR_REL_MSG_pb_ptr_rel_num + offset)) &= (~(M_DLRX_RXPB_PTR_REL_MSG_pb_ptr_rel_num)))

#define DLRX_RXPB_PTR_REL_MSG_pb_ptr_rel_num_clear_direct(dword)	((dword) &= (~(M_DLRX_RXPB_PTR_REL_MSG_pb_ptr_rel_num)))

#define O_DLRX_RXPB_PTR_REL_MSG_rsvd1 0
#define B_DLRX_RXPB_PTR_REL_MSG_rsvd1 23
#define W_DLRX_RXPB_PTR_REL_MSG_rsvd1 9
#define M_DLRX_RXPB_PTR_REL_MSG_rsvd1 0xff800000

#define DLRX_RXPB_PTR_REL_MSG_rsvd1_get_indirect(base, offset)	((((*(base + O_DLRX_RXPB_PTR_REL_MSG_rsvd1 + offset)) & M_DLRX_RXPB_PTR_REL_MSG_rsvd1) >> B_DLRX_RXPB_PTR_REL_MSG_rsvd1))

#define DLRX_RXPB_PTR_REL_MSG_rsvd1_get_direct(dword)	((((dword) & M_DLRX_RXPB_PTR_REL_MSG_rsvd1) >> B_DLRX_RXPB_PTR_REL_MSG_rsvd1))

#define DLRX_RXPB_PTR_REL_MSG_rsvd1_set_indirect(base, offset, val) \
	do {                                                              \
		(*(base + O_DLRX_RXPB_PTR_REL_MSG_rsvd1 + offset)) &= (~(M_DLRX_RXPB_PTR_REL_MSG_rsvd1));    \
		(*(base + O_DLRX_RXPB_PTR_REL_MSG_rsvd1 + offset)) |= ((val << B_DLRX_RXPB_PTR_REL_MSG_rsvd1) & M_DLRX_RXPB_PTR_REL_MSG_rsvd1);    \
	} while (0)

#define DLRX_RXPB_PTR_REL_MSG_rsvd1_set_direct(dword, val) \
	do {                                                               \
		(dword) &= (~(M_DLRX_RXPB_PTR_REL_MSG_rsvd1));    \
		(dword) |= ((val << B_DLRX_RXPB_PTR_REL_MSG_rsvd1) & M_DLRX_RXPB_PTR_REL_MSG_rsvd1);    \
	} while (0)

#define DLRX_RXPB_PTR_REL_MSG_rsvd1_clear_indirect(base, offset)	((*(base + O_DLRX_RXPB_PTR_REL_MSG_rsvd1 + offset)) &= (~(M_DLRX_RXPB_PTR_REL_MSG_rsvd1)))

#define DLRX_RXPB_PTR_REL_MSG_rsvd1_clear_direct(dword)	((dword) &= (~(M_DLRX_RXPB_PTR_REL_MSG_rsvd1)))

#define O_DLRX_RXPB_PTR_REL_MSG_rxpb_ptr 1
#define B_DLRX_RXPB_PTR_REL_MSG_rxpb_ptr 0
#define W_DLRX_RXPB_PTR_REL_MSG_rxpb_ptr 32
#define M_DLRX_RXPB_PTR_REL_MSG_rxpb_ptr 0xffffffff

#define DLRX_RXPB_PTR_REL_MSG_rxpb_ptr_get_indirect(base, offset)	((((*(base + O_DLRX_RXPB_PTR_REL_MSG_rxpb_ptr + offset)) & M_DLRX_RXPB_PTR_REL_MSG_rxpb_ptr) >> B_DLRX_RXPB_PTR_REL_MSG_rxpb_ptr))

#define DLRX_RXPB_PTR_REL_MSG_rxpb_ptr_get_direct(dword)	((((dword) & M_DLRX_RXPB_PTR_REL_MSG_rxpb_ptr) >> B_DLRX_RXPB_PTR_REL_MSG_rxpb_ptr))

#define DLRX_RXPB_PTR_REL_MSG_rxpb_ptr_set_indirect(base, offset, val)    \
	do {                                                              \
		(*(base + O_DLRX_RXPB_PTR_REL_MSG_rxpb_ptr + offset)) &= (~(M_DLRX_RXPB_PTR_REL_MSG_rxpb_ptr));    \
		(*(base + O_DLRX_RXPB_PTR_REL_MSG_rxpb_ptr + offset)) |= ((val << B_DLRX_RXPB_PTR_REL_MSG_rxpb_ptr) & M_DLRX_RXPB_PTR_REL_MSG_rxpb_ptr);    \
	} while (0)

#define DLRX_RXPB_PTR_REL_MSG_rxpb_ptr_set_direct(dword, val)    \
	do {                                                               \
		(dword) &= (~(M_DLRX_RXPB_PTR_REL_MSG_rxpb_ptr));    \
		(dword) |= ((val << B_DLRX_RXPB_PTR_REL_MSG_rxpb_ptr) & M_DLRX_RXPB_PTR_REL_MSG_rxpb_ptr);    \
	} while (0)

#define DLRX_RXPB_PTR_REL_MSG_rxpb_ptr_clear_indirect(base, offset)	((*(base + O_DLRX_RXPB_PTR_REL_MSG_rxpb_ptr + offset)) &= (~(M_DLRX_RXPB_PTR_REL_MSG_rxpb_ptr)))

#define DLRX_RXPB_PTR_REL_MSG_rxpb_ptr_clear_direct(dword)	((dword) &= (~(M_DLRX_RXPB_PTR_REL_MSG_rxpb_ptr)))

#define O_VAP_DATA_MIB_txpdu_low 0
#define B_VAP_DATA_MIB_txpdu_low 0
#define W_VAP_DATA_MIB_txpdu_low 32
#define M_VAP_DATA_MIB_txpdu_low 0xffffffff

#define VAP_DATA_MIB_txpdu_low_get_indirect(base, offset)	((((*(base + O_VAP_DATA_MIB_txpdu_low + offset)) & M_VAP_DATA_MIB_txpdu_low) >> B_VAP_DATA_MIB_txpdu_low))

#define VAP_DATA_MIB_txpdu_low_get_direct(dword)	((((dword) & M_VAP_DATA_MIB_txpdu_low) >> B_VAP_DATA_MIB_txpdu_low))

#define VAP_DATA_MIB_txpdu_low_set_indirect(base, offset, val)    \
	do {                                                              \
		(*(base + O_VAP_DATA_MIB_txpdu_low + offset)) &= (~(M_VAP_DATA_MIB_txpdu_low));    \
		(*(base + O_VAP_DATA_MIB_txpdu_low + offset)) |= ((val << B_VAP_DATA_MIB_txpdu_low) & M_VAP_DATA_MIB_txpdu_low);    \
	} while (0)

#define VAP_DATA_MIB_txpdu_low_set_direct(dword, val)    \
	do {                                                               \
		(dword) &= (~(M_VAP_DATA_MIB_txpdu_low));    \
		(dword) |= ((val << B_VAP_DATA_MIB_txpdu_low) & M_VAP_DATA_MIB_txpdu_low);    \
	} while (0)

#define VAP_DATA_MIB_txpdu_low_clear_indirect(base, offset)	((*(base + O_VAP_DATA_MIB_txpdu_low + offset)) &= (~(M_VAP_DATA_MIB_txpdu_low)))

#define VAP_DATA_MIB_txpdu_low_clear_direct(dword)	((dword) &= (~(M_VAP_DATA_MIB_txpdu_low)))

#define O_VAP_DATA_MIB_txpdu_high 1
#define B_VAP_DATA_MIB_txpdu_high 0
#define W_VAP_DATA_MIB_txpdu_high 32
#define M_VAP_DATA_MIB_txpdu_high 0xffffffff

#define VAP_DATA_MIB_txpdu_high_get_indirect(base, offset)	((((*(base + O_VAP_DATA_MIB_txpdu_high + offset)) & M_VAP_DATA_MIB_txpdu_high) >> B_VAP_DATA_MIB_txpdu_high))

#define VAP_DATA_MIB_txpdu_high_get_direct(dword)	((((dword) & M_VAP_DATA_MIB_txpdu_high) >> B_VAP_DATA_MIB_txpdu_high))

#define VAP_DATA_MIB_txpdu_high_set_indirect(base, offset, val)    \
	do {                                                              \
		(*(base + O_VAP_DATA_MIB_txpdu_high + offset)) &= (~(M_VAP_DATA_MIB_txpdu_high));    \
		(*(base + O_VAP_DATA_MIB_txpdu_high + offset)) |= ((val << B_VAP_DATA_MIB_txpdu_high) & M_VAP_DATA_MIB_txpdu_high);    \
	} while (0)

#define VAP_DATA_MIB_txpdu_high_set_direct(dword, val)    \
	do {                                                               \
		(dword) &= (~(M_VAP_DATA_MIB_txpdu_high));    \
		(dword) |= ((val << B_VAP_DATA_MIB_txpdu_high) & M_VAP_DATA_MIB_txpdu_high);    \
	} while (0)

#define VAP_DATA_MIB_txpdu_high_clear_indirect(base, offset)	((*(base + O_VAP_DATA_MIB_txpdu_high + offset)) &= (~(M_VAP_DATA_MIB_txpdu_high)))

#define VAP_DATA_MIB_txpdu_high_clear_direct(dword)	((dword) &= (~(M_VAP_DATA_MIB_txpdu_high)))

#define O_VAP_DATA_MIB_txbytes_low 2
#define B_VAP_DATA_MIB_txbytes_low 0
#define W_VAP_DATA_MIB_txbytes_low 32
#define M_VAP_DATA_MIB_txbytes_low 0xffffffff

#define VAP_DATA_MIB_txbytes_low_get_indirect(base, offset)	((((*(base + O_VAP_DATA_MIB_txbytes_low + offset)) & M_VAP_DATA_MIB_txbytes_low) >> B_VAP_DATA_MIB_txbytes_low))

#define VAP_DATA_MIB_txbytes_low_get_direct(dword)	((((dword) & M_VAP_DATA_MIB_txbytes_low) >> B_VAP_DATA_MIB_txbytes_low))

#define VAP_DATA_MIB_txbytes_low_set_indirect(base, offset, val)    \
	do {                                                              \
		(*(base + O_VAP_DATA_MIB_txbytes_low + offset)) &= (~(M_VAP_DATA_MIB_txbytes_low));    \
		(*(base + O_VAP_DATA_MIB_txbytes_low + offset)) |= ((val << B_VAP_DATA_MIB_txbytes_low) & M_VAP_DATA_MIB_txbytes_low);    \
	} while (0)

#define VAP_DATA_MIB_txbytes_low_set_direct(dword, val)    \
	do {                                                               \
		(dword) &= (~(M_VAP_DATA_MIB_txbytes_low));    \
		(dword) |= ((val << B_VAP_DATA_MIB_txbytes_low) & M_VAP_DATA_MIB_txbytes_low);    \
	} while (0)

#define VAP_DATA_MIB_txbytes_low_clear_indirect(base, offset)	((*(base + O_VAP_DATA_MIB_txbytes_low + offset)) &= (~(M_VAP_DATA_MIB_txbytes_low)))

#define VAP_DATA_MIB_txbytes_low_clear_direct(dword)	((dword) &= (~(M_VAP_DATA_MIB_txbytes_low)))

#define O_VAP_DATA_MIB_txbytes_high 3
#define B_VAP_DATA_MIB_txbytes_high 0
#define W_VAP_DATA_MIB_txbytes_high 32
#define M_VAP_DATA_MIB_txbytes_high 0xffffffff

#define VAP_DATA_MIB_txbytes_high_get_indirect(base, offset)	((((*(base + O_VAP_DATA_MIB_txbytes_high + offset)) & M_VAP_DATA_MIB_txbytes_high) >> B_VAP_DATA_MIB_txbytes_high))

#define VAP_DATA_MIB_txbytes_high_get_direct(dword)	((((dword) & M_VAP_DATA_MIB_txbytes_high) >> B_VAP_DATA_MIB_txbytes_high))

#define VAP_DATA_MIB_txbytes_high_set_indirect(base, offset, val)    \
	do {                                                              \
		(*(base + O_VAP_DATA_MIB_txbytes_high + offset)) &= (~(M_VAP_DATA_MIB_txbytes_high));    \
		(*(base + O_VAP_DATA_MIB_txbytes_high + offset)) |= ((val << B_VAP_DATA_MIB_txbytes_high) & M_VAP_DATA_MIB_txbytes_high);    \
	} while (0)

#define VAP_DATA_MIB_txbytes_high_set_direct(dword, val)    \
	do {                                                               \
		(dword) &= (~(M_VAP_DATA_MIB_txbytes_high));    \
		(dword) |= ((val << B_VAP_DATA_MIB_txbytes_high) & M_VAP_DATA_MIB_txbytes_high);    \
	} while (0)

#define VAP_DATA_MIB_txbytes_high_clear_indirect(base, offset)	((*(base + O_VAP_DATA_MIB_txbytes_high + offset)) &= (~(M_VAP_DATA_MIB_txbytes_high)))

#define VAP_DATA_MIB_txbytes_high_clear_direct(dword)	((dword) &= (~(M_VAP_DATA_MIB_txbytes_high)))

#define O_VAP_DATA_MIB_txdrop_low 4
#define B_VAP_DATA_MIB_txdrop_low 0
#define W_VAP_DATA_MIB_txdrop_low 32
#define M_VAP_DATA_MIB_txdrop_low 0xffffffff

#define VAP_DATA_MIB_txdrop_low_get_indirect(base, offset)	((((*(base + O_VAP_DATA_MIB_txdrop_low + offset)) & M_VAP_DATA_MIB_txdrop_low) >> B_VAP_DATA_MIB_txdrop_low))

#define VAP_DATA_MIB_txdrop_low_get_direct(dword)	((((dword) & M_VAP_DATA_MIB_txdrop_low) >> B_VAP_DATA_MIB_txdrop_low))

#define VAP_DATA_MIB_txdrop_low_set_indirect(base, offset, val)    \
	do {                                                              \
		(*(base + O_VAP_DATA_MIB_txdrop_low + offset)) &= (~(M_VAP_DATA_MIB_txdrop_low));    \
		(*(base + O_VAP_DATA_MIB_txdrop_low + offset)) |= ((val << B_VAP_DATA_MIB_txdrop_low) & M_VAP_DATA_MIB_txdrop_low);    \
	} while (0)

#define VAP_DATA_MIB_txdrop_low_set_direct(dword, val)    \
	do {                                                               \
		(dword) &= (~(M_VAP_DATA_MIB_txdrop_low));    \
		(dword) |= ((val << B_VAP_DATA_MIB_txdrop_low) & M_VAP_DATA_MIB_txdrop_low);    \
	} while (0)

#define VAP_DATA_MIB_txdrop_low_clear_indirect(base, offset)	((*(base + O_VAP_DATA_MIB_txdrop_low + offset)) &= (~(M_VAP_DATA_MIB_txdrop_low)))

#define VAP_DATA_MIB_txdrop_low_clear_direct(dword)	((dword) &= (~(M_VAP_DATA_MIB_txdrop_low)))

#define O_VAP_DATA_MIB_txdrop_high 5
#define B_VAP_DATA_MIB_txdrop_high 0
#define W_VAP_DATA_MIB_txdrop_high 32
#define M_VAP_DATA_MIB_txdrop_high 0xffffffff

#define VAP_DATA_MIB_txdrop_high_get_indirect(base, offset)	((((*(base + O_VAP_DATA_MIB_txdrop_high + offset)) & M_VAP_DATA_MIB_txdrop_high) >> B_VAP_DATA_MIB_txdrop_high))

#define VAP_DATA_MIB_txdrop_high_get_direct(dword)	((((dword) & M_VAP_DATA_MIB_txdrop_high) >> B_VAP_DATA_MIB_txdrop_high))

#define VAP_DATA_MIB_txdrop_high_set_indirect(base, offset, val)    \
	do {                                                              \
		(*(base + O_VAP_DATA_MIB_txdrop_high + offset)) &= (~(M_VAP_DATA_MIB_txdrop_high));    \
		(*(base + O_VAP_DATA_MIB_txdrop_high + offset)) |= ((val << B_VAP_DATA_MIB_txdrop_high) & M_VAP_DATA_MIB_txdrop_high);    \
	} while (0)

#define VAP_DATA_MIB_txdrop_high_set_direct(dword, val)    \
	do {                                                               \
		(dword) &= (~(M_VAP_DATA_MIB_txdrop_high));    \
		(dword) |= ((val << B_VAP_DATA_MIB_txdrop_high) & M_VAP_DATA_MIB_txdrop_high);    \
	} while (0)

#define VAP_DATA_MIB_txdrop_high_clear_indirect(base, offset)	((*(base + O_VAP_DATA_MIB_txdrop_high + offset)) &= (~(M_VAP_DATA_MIB_txdrop_high)))

#define VAP_DATA_MIB_txdrop_high_clear_direct(dword)	((dword) &= (~(M_VAP_DATA_MIB_txdrop_high)))

#define O_VAP_DATA_MIB_rx_fwd_pdu_low 6
#define B_VAP_DATA_MIB_rx_fwd_pdu_low 0
#define W_VAP_DATA_MIB_rx_fwd_pdu_low 32
#define M_VAP_DATA_MIB_rx_fwd_pdu_low 0xffffffff

#define VAP_DATA_MIB_rx_fwd_pdu_low_get_indirect(base, offset)	((((*(base + O_VAP_DATA_MIB_rx_fwd_pdu_low + offset)) & M_VAP_DATA_MIB_rx_fwd_pdu_low) >> B_VAP_DATA_MIB_rx_fwd_pdu_low))

#define VAP_DATA_MIB_rx_fwd_pdu_low_get_direct(dword)	((((dword) & M_VAP_DATA_MIB_rx_fwd_pdu_low) >> B_VAP_DATA_MIB_rx_fwd_pdu_low))

#define VAP_DATA_MIB_rx_fwd_pdu_low_set_indirect(base, offset, val)    \
	do {                                                              \
		(*(base + O_VAP_DATA_MIB_rx_fwd_pdu_low + offset)) &= (~(M_VAP_DATA_MIB_rx_fwd_pdu_low));    \
		(*(base + O_VAP_DATA_MIB_rx_fwd_pdu_low + offset)) |= ((val << B_VAP_DATA_MIB_rx_fwd_pdu_low) & M_VAP_DATA_MIB_rx_fwd_pdu_low);    \
	} while (0)

#define VAP_DATA_MIB_rx_fwd_pdu_low_set_direct(dword, val)    \
	do {                                                               \
		(dword) &= (~(M_VAP_DATA_MIB_rx_fwd_pdu_low));    \
		(dword) |= ((val << B_VAP_DATA_MIB_rx_fwd_pdu_low) & M_VAP_DATA_MIB_rx_fwd_pdu_low);    \
	} while (0)

#define VAP_DATA_MIB_rx_fwd_pdu_low_clear_indirect(base, offset)	((*(base + O_VAP_DATA_MIB_rx_fwd_pdu_low + offset)) &= (~(M_VAP_DATA_MIB_rx_fwd_pdu_low)))

#define VAP_DATA_MIB_rx_fwd_pdu_low_clear_direct(dword)	((dword) &= (~(M_VAP_DATA_MIB_rx_fwd_pdu_low)))

#define O_VAP_DATA_MIB_rx_fwd_pdu_high 7
#define B_VAP_DATA_MIB_rx_fwd_pdu_high 0
#define W_VAP_DATA_MIB_rx_fwd_pdu_high 32
#define M_VAP_DATA_MIB_rx_fwd_pdu_high 0xffffffff

#define VAP_DATA_MIB_rx_fwd_pdu_high_get_indirect(base, offset)	((((*(base + O_VAP_DATA_MIB_rx_fwd_pdu_high + offset)) & M_VAP_DATA_MIB_rx_fwd_pdu_high) >> B_VAP_DATA_MIB_rx_fwd_pdu_high))

#define VAP_DATA_MIB_rx_fwd_pdu_high_get_direct(dword)	((((dword) & M_VAP_DATA_MIB_rx_fwd_pdu_high) >> B_VAP_DATA_MIB_rx_fwd_pdu_high))

#define VAP_DATA_MIB_rx_fwd_pdu_high_set_indirect(base, offset, val)    \
	do {                                                              \
		(*(base + O_VAP_DATA_MIB_rx_fwd_pdu_high + offset)) &= (~(M_VAP_DATA_MIB_rx_fwd_pdu_high));    \
		(*(base + O_VAP_DATA_MIB_rx_fwd_pdu_high + offset)) |= ((val << B_VAP_DATA_MIB_rx_fwd_pdu_high) & M_VAP_DATA_MIB_rx_fwd_pdu_high);    \
	} while (0)

#define VAP_DATA_MIB_rx_fwd_pdu_high_set_direct(dword, val)    \
	do {                                                               \
		(dword) &= (~(M_VAP_DATA_MIB_rx_fwd_pdu_high));    \
		(dword) |= ((val << B_VAP_DATA_MIB_rx_fwd_pdu_high) & M_VAP_DATA_MIB_rx_fwd_pdu_high);    \
	} while (0)

#define VAP_DATA_MIB_rx_fwd_pdu_high_clear_indirect(base, offset)	((*(base + O_VAP_DATA_MIB_rx_fwd_pdu_high + offset)) &= (~(M_VAP_DATA_MIB_rx_fwd_pdu_high)))

#define VAP_DATA_MIB_rx_fwd_pdu_high_clear_direct(dword)	((dword) &= (~(M_VAP_DATA_MIB_rx_fwd_pdu_high)))

#define O_VAP_DATA_MIB_rx_fwd_bytes_low 8
#define B_VAP_DATA_MIB_rx_fwd_bytes_low 0
#define W_VAP_DATA_MIB_rx_fwd_bytes_low 32
#define M_VAP_DATA_MIB_rx_fwd_bytes_low 0xffffffff

#define VAP_DATA_MIB_rx_fwd_bytes_low_get_indirect(base, offset)	((((*(base + O_VAP_DATA_MIB_rx_fwd_bytes_low + offset)) & M_VAP_DATA_MIB_rx_fwd_bytes_low) >> B_VAP_DATA_MIB_rx_fwd_bytes_low))

#define VAP_DATA_MIB_rx_fwd_bytes_low_get_direct(dword)	((((dword) & M_VAP_DATA_MIB_rx_fwd_bytes_low) >> B_VAP_DATA_MIB_rx_fwd_bytes_low))

#define VAP_DATA_MIB_rx_fwd_bytes_low_set_indirect(base, offset, val)    \
	do {                                                              \
		(*(base + O_VAP_DATA_MIB_rx_fwd_bytes_low + offset)) &= (~(M_VAP_DATA_MIB_rx_fwd_bytes_low));    \
		(*(base + O_VAP_DATA_MIB_rx_fwd_bytes_low + offset)) |= ((val << B_VAP_DATA_MIB_rx_fwd_bytes_low) & M_VAP_DATA_MIB_rx_fwd_bytes_low);    \
	} while (0)

#define VAP_DATA_MIB_rx_fwd_bytes_low_set_direct(dword, val)    \
	do {                                                               \
		(dword) &= (~(M_VAP_DATA_MIB_rx_fwd_bytes_low));    \
		(dword) |= ((val << B_VAP_DATA_MIB_rx_fwd_bytes_low) & M_VAP_DATA_MIB_rx_fwd_bytes_low);    \
	} while (0)

#define VAP_DATA_MIB_rx_fwd_bytes_low_clear_indirect(base, offset)	((*(base + O_VAP_DATA_MIB_rx_fwd_bytes_low + offset)) &= (~(M_VAP_DATA_MIB_rx_fwd_bytes_low)))

#define VAP_DATA_MIB_rx_fwd_bytes_low_clear_direct(dword)	((dword) &= (~(M_VAP_DATA_MIB_rx_fwd_bytes_low)))

#define O_VAP_DATA_MIB_rx_fwd_bytes_high 9
#define B_VAP_DATA_MIB_rx_fwd_bytes_high 0
#define W_VAP_DATA_MIB_rx_fwd_bytes_high 32
#define M_VAP_DATA_MIB_rx_fwd_bytes_high 0xffffffff

#define VAP_DATA_MIB_rx_fwd_bytes_high_get_indirect(base, offset)	((((*(base + O_VAP_DATA_MIB_rx_fwd_bytes_high + offset)) & M_VAP_DATA_MIB_rx_fwd_bytes_high) >> B_VAP_DATA_MIB_rx_fwd_bytes_high))

#define VAP_DATA_MIB_rx_fwd_bytes_high_get_direct(dword)	((((dword) & M_VAP_DATA_MIB_rx_fwd_bytes_high) >> B_VAP_DATA_MIB_rx_fwd_bytes_high))

#define VAP_DATA_MIB_rx_fwd_bytes_high_set_indirect(base, offset, val)    \
	do {                                                              \
		(*(base + O_VAP_DATA_MIB_rx_fwd_bytes_high + offset)) &= (~(M_VAP_DATA_MIB_rx_fwd_bytes_high));    \
		(*(base + O_VAP_DATA_MIB_rx_fwd_bytes_high + offset)) |= ((val << B_VAP_DATA_MIB_rx_fwd_bytes_high) & M_VAP_DATA_MIB_rx_fwd_bytes_high);    \
	} while (0)

#define VAP_DATA_MIB_rx_fwd_bytes_high_set_direct(dword, val)    \
	do {                                                               \
		(dword) &= (~(M_VAP_DATA_MIB_rx_fwd_bytes_high));    \
		(dword) |= ((val << B_VAP_DATA_MIB_rx_fwd_bytes_high) & M_VAP_DATA_MIB_rx_fwd_bytes_high);    \
	} while (0)

#define VAP_DATA_MIB_rx_fwd_bytes_high_clear_indirect(base, offset)	((*(base + O_VAP_DATA_MIB_rx_fwd_bytes_high + offset)) &= (~(M_VAP_DATA_MIB_rx_fwd_bytes_high)))

#define VAP_DATA_MIB_rx_fwd_bytes_high_clear_direct(dword)	((dword) &= (~(M_VAP_DATA_MIB_rx_fwd_bytes_high)))

#define O_VAP_DATA_MIB_rx_inspect_pdu_low 10
#define B_VAP_DATA_MIB_rx_inspect_pdu_low 0
#define W_VAP_DATA_MIB_rx_inspect_pdu_low 32
#define M_VAP_DATA_MIB_rx_inspect_pdu_low 0xffffffff

#define VAP_DATA_MIB_rx_inspect_pdu_low_get_indirect(base, offset)	((((*(base + O_VAP_DATA_MIB_rx_inspect_pdu_low + offset)) & M_VAP_DATA_MIB_rx_inspect_pdu_low) >> B_VAP_DATA_MIB_rx_inspect_pdu_low))

#define VAP_DATA_MIB_rx_inspect_pdu_low_get_direct(dword)	((((dword) & M_VAP_DATA_MIB_rx_inspect_pdu_low) >> B_VAP_DATA_MIB_rx_inspect_pdu_low))

#define VAP_DATA_MIB_rx_inspect_pdu_low_set_indirect(base, offset, val)    \
	do {                                                              \
		(*(base + O_VAP_DATA_MIB_rx_inspect_pdu_low + offset)) &= (~(M_VAP_DATA_MIB_rx_inspect_pdu_low));    \
		(*(base + O_VAP_DATA_MIB_rx_inspect_pdu_low + offset)) |= ((val << B_VAP_DATA_MIB_rx_inspect_pdu_low) & M_VAP_DATA_MIB_rx_inspect_pdu_low);    \
	} while (0)

#define VAP_DATA_MIB_rx_inspect_pdu_low_set_direct(dword, val)    \
	do {                                                               \
		(dword) &= (~(M_VAP_DATA_MIB_rx_inspect_pdu_low));    \
		(dword) |= ((val << B_VAP_DATA_MIB_rx_inspect_pdu_low) & M_VAP_DATA_MIB_rx_inspect_pdu_low);    \
	} while (0)

#define VAP_DATA_MIB_rx_inspect_pdu_low_clear_indirect(base, offset)	((*(base + O_VAP_DATA_MIB_rx_inspect_pdu_low + offset)) &= (~(M_VAP_DATA_MIB_rx_inspect_pdu_low)))

#define VAP_DATA_MIB_rx_inspect_pdu_low_clear_direct(dword)	((dword) &= (~(M_VAP_DATA_MIB_rx_inspect_pdu_low)))

#define O_VAP_DATA_MIB_rx_inspect_pdu_high 11
#define B_VAP_DATA_MIB_rx_inspect_pdu_high 0
#define W_VAP_DATA_MIB_rx_inspect_pdu_high 32
#define M_VAP_DATA_MIB_rx_inspect_pdu_high 0xffffffff

#define VAP_DATA_MIB_rx_inspect_pdu_high_get_indirect(base, offset)	((((*(base + O_VAP_DATA_MIB_rx_inspect_pdu_high + offset)) & M_VAP_DATA_MIB_rx_inspect_pdu_high) >> B_VAP_DATA_MIB_rx_inspect_pdu_high))

#define VAP_DATA_MIB_rx_inspect_pdu_high_get_direct(dword)	((((dword) & M_VAP_DATA_MIB_rx_inspect_pdu_high) >> B_VAP_DATA_MIB_rx_inspect_pdu_high))

#define VAP_DATA_MIB_rx_inspect_pdu_high_set_indirect(base, offset, val)    \
	do {                                                              \
		(*(base + O_VAP_DATA_MIB_rx_inspect_pdu_high + offset)) &= (~(M_VAP_DATA_MIB_rx_inspect_pdu_high));    \
		(*(base + O_VAP_DATA_MIB_rx_inspect_pdu_high + offset)) |= ((val << B_VAP_DATA_MIB_rx_inspect_pdu_high) & M_VAP_DATA_MIB_rx_inspect_pdu_high);    \
	} while (0)

#define VAP_DATA_MIB_rx_inspect_pdu_high_set_direct(dword, val)    \
	do {                                                               \
		(dword) &= (~(M_VAP_DATA_MIB_rx_inspect_pdu_high));    \
		(dword) |= ((val << B_VAP_DATA_MIB_rx_inspect_pdu_high) & M_VAP_DATA_MIB_rx_inspect_pdu_high);    \
	} while (0)

#define VAP_DATA_MIB_rx_inspect_pdu_high_clear_indirect(base, offset)	((*(base + O_VAP_DATA_MIB_rx_inspect_pdu_high + offset)) &= (~(M_VAP_DATA_MIB_rx_inspect_pdu_high)))

#define VAP_DATA_MIB_rx_inspect_pdu_high_clear_direct(dword)	((dword) &= (~(M_VAP_DATA_MIB_rx_inspect_pdu_high)))

#define O_VAP_DATA_MIB_rx_inspect_bytes_low 12
#define B_VAP_DATA_MIB_rx_inspect_bytes_low 0
#define W_VAP_DATA_MIB_rx_inspect_bytes_low 32
#define M_VAP_DATA_MIB_rx_inspect_bytes_low 0xffffffff

#define VAP_DATA_MIB_rx_inspect_bytes_low_get_indirect(base, offset)	((((*(base + O_VAP_DATA_MIB_rx_inspect_bytes_low + offset)) & M_VAP_DATA_MIB_rx_inspect_bytes_low) >> B_VAP_DATA_MIB_rx_inspect_bytes_low))

#define VAP_DATA_MIB_rx_inspect_bytes_low_get_direct(dword)	((((dword) & M_VAP_DATA_MIB_rx_inspect_bytes_low) >> B_VAP_DATA_MIB_rx_inspect_bytes_low))

#define VAP_DATA_MIB_rx_inspect_bytes_low_set_indirect(base, offset, val)    \
	do {                                                              \
		(*(base + O_VAP_DATA_MIB_rx_inspect_bytes_low + offset)) &= (~(M_VAP_DATA_MIB_rx_inspect_bytes_low));    \
		(*(base + O_VAP_DATA_MIB_rx_inspect_bytes_low + offset)) |= ((val << B_VAP_DATA_MIB_rx_inspect_bytes_low) & M_VAP_DATA_MIB_rx_inspect_bytes_low);    \
	} while (0)

#define VAP_DATA_MIB_rx_inspect_bytes_low_set_direct(dword, val)    \
	do {                                                               \
		(dword) &= (~(M_VAP_DATA_MIB_rx_inspect_bytes_low));    \
		(dword) |= ((val << B_VAP_DATA_MIB_rx_inspect_bytes_low) & M_VAP_DATA_MIB_rx_inspect_bytes_low);    \
	} while (0)

#define VAP_DATA_MIB_rx_inspect_bytes_low_clear_indirect(base, offset)	((*(base + O_VAP_DATA_MIB_rx_inspect_bytes_low + offset)) &= (~(M_VAP_DATA_MIB_rx_inspect_bytes_low)))

#define VAP_DATA_MIB_rx_inspect_bytes_low_clear_direct(dword)	((dword) &= (~(M_VAP_DATA_MIB_rx_inspect_bytes_low)))

#define O_VAP_DATA_MIB_rx_inspect_bytes_high 13
#define B_VAP_DATA_MIB_rx_inspect_bytes_high 0
#define W_VAP_DATA_MIB_rx_inspect_bytes_high 32
#define M_VAP_DATA_MIB_rx_inspect_bytes_high 0xffffffff

#define VAP_DATA_MIB_rx_inspect_bytes_high_get_indirect(base, offset)	((((*(base + O_VAP_DATA_MIB_rx_inspect_bytes_high + offset)) & M_VAP_DATA_MIB_rx_inspect_bytes_high) >> B_VAP_DATA_MIB_rx_inspect_bytes_high))

#define VAP_DATA_MIB_rx_inspect_bytes_high_get_direct(dword)	((((dword) & M_VAP_DATA_MIB_rx_inspect_bytes_high) >> B_VAP_DATA_MIB_rx_inspect_bytes_high))

#define VAP_DATA_MIB_rx_inspect_bytes_high_set_indirect(base, offset, val)    \
	do {                                                              \
		(*(base + O_VAP_DATA_MIB_rx_inspect_bytes_high + offset)) &= (~(M_VAP_DATA_MIB_rx_inspect_bytes_high));    \
		(*(base + O_VAP_DATA_MIB_rx_inspect_bytes_high + offset)) |= ((val << B_VAP_DATA_MIB_rx_inspect_bytes_high) & M_VAP_DATA_MIB_rx_inspect_bytes_high);    \
	} while (0)

#define VAP_DATA_MIB_rx_inspect_bytes_high_set_direct(dword, val)    \
	do {                                                               \
		(dword) &= (~(M_VAP_DATA_MIB_rx_inspect_bytes_high));    \
		(dword) |= ((val << B_VAP_DATA_MIB_rx_inspect_bytes_high) & M_VAP_DATA_MIB_rx_inspect_bytes_high);    \
	} while (0)

#define VAP_DATA_MIB_rx_inspect_bytes_high_clear_indirect(base, offset)	((*(base + O_VAP_DATA_MIB_rx_inspect_bytes_high + offset)) &= (~(M_VAP_DATA_MIB_rx_inspect_bytes_high)))

#define VAP_DATA_MIB_rx_inspect_bytes_high_clear_direct(dword)	((dword) &= (~(M_VAP_DATA_MIB_rx_inspect_bytes_high)))

#define O_VAP_DATA_MIB_rx_discard_pdu_low 14
#define B_VAP_DATA_MIB_rx_discard_pdu_low 0
#define W_VAP_DATA_MIB_rx_discard_pdu_low 32
#define M_VAP_DATA_MIB_rx_discard_pdu_low 0xffffffff

#define VAP_DATA_MIB_rx_discard_pdu_low_get_indirect(base, offset)	((((*(base + O_VAP_DATA_MIB_rx_discard_pdu_low + offset)) & M_VAP_DATA_MIB_rx_discard_pdu_low) >> B_VAP_DATA_MIB_rx_discard_pdu_low))

#define VAP_DATA_MIB_rx_discard_pdu_low_get_direct(dword)	((((dword) & M_VAP_DATA_MIB_rx_discard_pdu_low) >> B_VAP_DATA_MIB_rx_discard_pdu_low))

#define VAP_DATA_MIB_rx_discard_pdu_low_set_indirect(base, offset, val)    \
	do {                                                              \
		(*(base + O_VAP_DATA_MIB_rx_discard_pdu_low + offset)) &= (~(M_VAP_DATA_MIB_rx_discard_pdu_low));    \
		(*(base + O_VAP_DATA_MIB_rx_discard_pdu_low + offset)) |= ((val << B_VAP_DATA_MIB_rx_discard_pdu_low) & M_VAP_DATA_MIB_rx_discard_pdu_low);    \
	} while (0)

#define VAP_DATA_MIB_rx_discard_pdu_low_set_direct(dword, val)    \
	do {                                                               \
		(dword) &= (~(M_VAP_DATA_MIB_rx_discard_pdu_low));    \
		(dword) |= ((val << B_VAP_DATA_MIB_rx_discard_pdu_low) & M_VAP_DATA_MIB_rx_discard_pdu_low);    \
	} while (0)

#define VAP_DATA_MIB_rx_discard_pdu_low_clear_indirect(base, offset)	((*(base + O_VAP_DATA_MIB_rx_discard_pdu_low + offset)) &= (~(M_VAP_DATA_MIB_rx_discard_pdu_low)))

#define VAP_DATA_MIB_rx_discard_pdu_low_clear_direct(dword)	((dword) &= (~(M_VAP_DATA_MIB_rx_discard_pdu_low)))

#define O_VAP_DATA_MIB_rx_discard_pdu_high 15
#define B_VAP_DATA_MIB_rx_discard_pdu_high 0
#define W_VAP_DATA_MIB_rx_discard_pdu_high 32
#define M_VAP_DATA_MIB_rx_discard_pdu_high 0xffffffff

#define VAP_DATA_MIB_rx_discard_pdu_high_get_indirect(base, offset)	((((*(base + O_VAP_DATA_MIB_rx_discard_pdu_high + offset)) & M_VAP_DATA_MIB_rx_discard_pdu_high) >> B_VAP_DATA_MIB_rx_discard_pdu_high))

#define VAP_DATA_MIB_rx_discard_pdu_high_get_direct(dword)	((((dword) & M_VAP_DATA_MIB_rx_discard_pdu_high) >> B_VAP_DATA_MIB_rx_discard_pdu_high))

#define VAP_DATA_MIB_rx_discard_pdu_high_set_indirect(base, offset, val)    \
	do {                                                              \
		(*(base + O_VAP_DATA_MIB_rx_discard_pdu_high + offset)) &= (~(M_VAP_DATA_MIB_rx_discard_pdu_high));    \
		(*(base + O_VAP_DATA_MIB_rx_discard_pdu_high + offset)) |= ((val << B_VAP_DATA_MIB_rx_discard_pdu_high) & M_VAP_DATA_MIB_rx_discard_pdu_high);    \
	} while (0)

#define VAP_DATA_MIB_rx_discard_pdu_high_set_direct(dword, val)    \
	do {                                                               \
		(dword) &= (~(M_VAP_DATA_MIB_rx_discard_pdu_high));    \
		(dword) |= ((val << B_VAP_DATA_MIB_rx_discard_pdu_high) & M_VAP_DATA_MIB_rx_discard_pdu_high);    \
	} while (0)

#define VAP_DATA_MIB_rx_discard_pdu_high_clear_indirect(base, offset)	((*(base + O_VAP_DATA_MIB_rx_discard_pdu_high + offset)) &= (~(M_VAP_DATA_MIB_rx_discard_pdu_high)))

#define VAP_DATA_MIB_rx_discard_pdu_high_clear_direct(dword)	((dword) &= (~(M_VAP_DATA_MIB_rx_discard_pdu_high)))

#define O_VAP_DATA_MIB_rx_discard_bytes_low 16
#define B_VAP_DATA_MIB_rx_discard_bytes_low 0
#define W_VAP_DATA_MIB_rx_discard_bytes_low 32
#define M_VAP_DATA_MIB_rx_discard_bytes_low 0xffffffff

#define VAP_DATA_MIB_rx_discard_bytes_low_get_indirect(base, offset)	((((*(base + O_VAP_DATA_MIB_rx_discard_bytes_low + offset)) & M_VAP_DATA_MIB_rx_discard_bytes_low) >> B_VAP_DATA_MIB_rx_discard_bytes_low))

#define VAP_DATA_MIB_rx_discard_bytes_low_get_direct(dword)	((((dword) & M_VAP_DATA_MIB_rx_discard_bytes_low) >> B_VAP_DATA_MIB_rx_discard_bytes_low))

#define VAP_DATA_MIB_rx_discard_bytes_low_set_indirect(base, offset, val)    \
	do {                                                              \
		(*(base + O_VAP_DATA_MIB_rx_discard_bytes_low + offset)) &= (~(M_VAP_DATA_MIB_rx_discard_bytes_low));    \
		(*(base + O_VAP_DATA_MIB_rx_discard_bytes_low + offset)) |= ((val << B_VAP_DATA_MIB_rx_discard_bytes_low) & M_VAP_DATA_MIB_rx_discard_bytes_low);    \
	} while (0)

#define VAP_DATA_MIB_rx_discard_bytes_low_set_direct(dword, val)    \
	do {                                                               \
		(dword) &= (~(M_VAP_DATA_MIB_rx_discard_bytes_low));    \
		(dword) |= ((val << B_VAP_DATA_MIB_rx_discard_bytes_low) & M_VAP_DATA_MIB_rx_discard_bytes_low);    \
	} while (0)

#define VAP_DATA_MIB_rx_discard_bytes_low_clear_indirect(base, offset)	((*(base + O_VAP_DATA_MIB_rx_discard_bytes_low + offset)) &= (~(M_VAP_DATA_MIB_rx_discard_bytes_low)))

#define VAP_DATA_MIB_rx_discard_bytes_low_clear_direct(dword)	((dword) &= (~(M_VAP_DATA_MIB_rx_discard_bytes_low)))

#define O_VAP_DATA_MIB_rx_discard_bytes_high 17
#define B_VAP_DATA_MIB_rx_discard_bytes_high 0
#define W_VAP_DATA_MIB_rx_discard_bytes_high 32
#define M_VAP_DATA_MIB_rx_discard_bytes_high 0xffffffff

#define VAP_DATA_MIB_rx_discard_bytes_high_get_indirect(base, offset)	((((*(base + O_VAP_DATA_MIB_rx_discard_bytes_high + offset)) & M_VAP_DATA_MIB_rx_discard_bytes_high) >> B_VAP_DATA_MIB_rx_discard_bytes_high))

#define VAP_DATA_MIB_rx_discard_bytes_high_get_direct(dword)	((((dword) & M_VAP_DATA_MIB_rx_discard_bytes_high) >> B_VAP_DATA_MIB_rx_discard_bytes_high))

#define VAP_DATA_MIB_rx_discard_bytes_high_set_indirect(base, offset, val)    \
	do {                                                              \
		(*(base + O_VAP_DATA_MIB_rx_discard_bytes_high + offset)) &= (~(M_VAP_DATA_MIB_rx_discard_bytes_high));    \
		(*(base + O_VAP_DATA_MIB_rx_discard_bytes_high + offset)) |= ((val << B_VAP_DATA_MIB_rx_discard_bytes_high) & M_VAP_DATA_MIB_rx_discard_bytes_high);    \
	} while (0)

#define VAP_DATA_MIB_rx_discard_bytes_high_set_direct(dword, val)    \
	do {                                                               \
		(dword) &= (~(M_VAP_DATA_MIB_rx_discard_bytes_high));    \
		(dword) |= ((val << B_VAP_DATA_MIB_rx_discard_bytes_high) & M_VAP_DATA_MIB_rx_discard_bytes_high);    \
	} while (0)

#define VAP_DATA_MIB_rx_discard_bytes_high_clear_indirect(base, offset)	((*(base + O_VAP_DATA_MIB_rx_discard_bytes_high + offset)) &= (~(M_VAP_DATA_MIB_rx_discard_bytes_high)))

#define VAP_DATA_MIB_rx_discard_bytes_high_clear_direct(dword)	((dword) &= (~(M_VAP_DATA_MIB_rx_discard_bytes_high)))

#define O_VAP_DATA_MIB_rx_pn_pdu_low 18
#define B_VAP_DATA_MIB_rx_pn_pdu_low 0
#define W_VAP_DATA_MIB_rx_pn_pdu_low 32
#define M_VAP_DATA_MIB_rx_pn_pdu_low 0xffffffff

#define VAP_DATA_MIB_rx_pn_pdu_low_get_indirect(base, offset)	((((*(base + O_VAP_DATA_MIB_rx_pn_pdu_low + offset)) & M_VAP_DATA_MIB_rx_pn_pdu_low) >> B_VAP_DATA_MIB_rx_pn_pdu_low))

#define VAP_DATA_MIB_rx_pn_pdu_low_get_direct(dword)	((((dword) & M_VAP_DATA_MIB_rx_pn_pdu_low) >> B_VAP_DATA_MIB_rx_pn_pdu_low))

#define VAP_DATA_MIB_rx_pn_pdu_low_set_indirect(base, offset, val)    \
	do {                                                              \
		(*(base + O_VAP_DATA_MIB_rx_pn_pdu_low + offset)) &= (~(M_VAP_DATA_MIB_rx_pn_pdu_low));    \
		(*(base + O_VAP_DATA_MIB_rx_pn_pdu_low + offset)) |= ((val << B_VAP_DATA_MIB_rx_pn_pdu_low) & M_VAP_DATA_MIB_rx_pn_pdu_low);    \
	} while (0)

#define VAP_DATA_MIB_rx_pn_pdu_low_set_direct(dword, val)    \
	do {                                                               \
		(dword) &= (~(M_VAP_DATA_MIB_rx_pn_pdu_low));    \
		(dword) |= ((val << B_VAP_DATA_MIB_rx_pn_pdu_low) & M_VAP_DATA_MIB_rx_pn_pdu_low);    \
	} while (0)

#define VAP_DATA_MIB_rx_pn_pdu_low_clear_indirect(base, offset)	((*(base + O_VAP_DATA_MIB_rx_pn_pdu_low + offset)) &= (~(M_VAP_DATA_MIB_rx_pn_pdu_low)))

#define VAP_DATA_MIB_rx_pn_pdu_low_clear_direct(dword)	((dword) &= (~(M_VAP_DATA_MIB_rx_pn_pdu_low)))

#define O_VAP_DATA_MIB_rx_pn_pdu_high 19
#define B_VAP_DATA_MIB_rx_pn_pdu_high 0
#define W_VAP_DATA_MIB_rx_pn_pdu_high 32
#define M_VAP_DATA_MIB_rx_pn_pdu_high 0xffffffff

#define VAP_DATA_MIB_rx_pn_pdu_high_get_indirect(base, offset)	((((*(base + O_VAP_DATA_MIB_rx_pn_pdu_high + offset)) & M_VAP_DATA_MIB_rx_pn_pdu_high) >> B_VAP_DATA_MIB_rx_pn_pdu_high))

#define VAP_DATA_MIB_rx_pn_pdu_high_get_direct(dword)	((((dword) & M_VAP_DATA_MIB_rx_pn_pdu_high) >> B_VAP_DATA_MIB_rx_pn_pdu_high))

#define VAP_DATA_MIB_rx_pn_pdu_high_set_indirect(base, offset, val)    \
	do {                                                              \
		(*(base + O_VAP_DATA_MIB_rx_pn_pdu_high + offset)) &= (~(M_VAP_DATA_MIB_rx_pn_pdu_high));    \
		(*(base + O_VAP_DATA_MIB_rx_pn_pdu_high + offset)) |= ((val << B_VAP_DATA_MIB_rx_pn_pdu_high) & M_VAP_DATA_MIB_rx_pn_pdu_high);    \
	} while (0)

#define VAP_DATA_MIB_rx_pn_pdu_high_set_direct(dword, val)    \
	do {                                                               \
		(dword) &= (~(M_VAP_DATA_MIB_rx_pn_pdu_high));    \
		(dword) |= ((val << B_VAP_DATA_MIB_rx_pn_pdu_high) & M_VAP_DATA_MIB_rx_pn_pdu_high);    \
	} while (0)

#define VAP_DATA_MIB_rx_pn_pdu_high_clear_indirect(base, offset)	((*(base + O_VAP_DATA_MIB_rx_pn_pdu_high + offset)) &= (~(M_VAP_DATA_MIB_rx_pn_pdu_high)))

#define VAP_DATA_MIB_rx_pn_pdu_high_clear_direct(dword)	((dword) &= (~(M_VAP_DATA_MIB_rx_pn_pdu_high)))

#define O_VAP_DATA_MIB_rx_pn_bytes_low 20
#define B_VAP_DATA_MIB_rx_pn_bytes_low 0
#define W_VAP_DATA_MIB_rx_pn_bytes_low 32
#define M_VAP_DATA_MIB_rx_pn_bytes_low 0xffffffff

#define VAP_DATA_MIB_rx_pn_bytes_low_get_indirect(base, offset)	((((*(base + O_VAP_DATA_MIB_rx_pn_bytes_low + offset)) & M_VAP_DATA_MIB_rx_pn_bytes_low) >> B_VAP_DATA_MIB_rx_pn_bytes_low))

#define VAP_DATA_MIB_rx_pn_bytes_low_get_direct(dword)	((((dword) & M_VAP_DATA_MIB_rx_pn_bytes_low) >> B_VAP_DATA_MIB_rx_pn_bytes_low))

#define VAP_DATA_MIB_rx_pn_bytes_low_set_indirect(base, offset, val)    \
	do {                                                              \
		(*(base + O_VAP_DATA_MIB_rx_pn_bytes_low + offset)) &= (~(M_VAP_DATA_MIB_rx_pn_bytes_low));    \
		(*(base + O_VAP_DATA_MIB_rx_pn_bytes_low + offset)) |= ((val << B_VAP_DATA_MIB_rx_pn_bytes_low) & M_VAP_DATA_MIB_rx_pn_bytes_low);    \
	} while (0)

#define VAP_DATA_MIB_rx_pn_bytes_low_set_direct(dword, val)    \
	do {                                                               \
		(dword) &= (~(M_VAP_DATA_MIB_rx_pn_bytes_low));    \
		(dword) |= ((val << B_VAP_DATA_MIB_rx_pn_bytes_low) & M_VAP_DATA_MIB_rx_pn_bytes_low);    \
	} while (0)

#define VAP_DATA_MIB_rx_pn_bytes_low_clear_indirect(base, offset)	((*(base + O_VAP_DATA_MIB_rx_pn_bytes_low + offset)) &= (~(M_VAP_DATA_MIB_rx_pn_bytes_low)))

#define VAP_DATA_MIB_rx_pn_bytes_low_clear_direct(dword)	((dword) &= (~(M_VAP_DATA_MIB_rx_pn_bytes_low)))

#define O_VAP_DATA_MIB_rx_pn_bytes_high 21
#define B_VAP_DATA_MIB_rx_pn_bytes_high 0
#define W_VAP_DATA_MIB_rx_pn_bytes_high 32
#define M_VAP_DATA_MIB_rx_pn_bytes_high 0xffffffff

#define VAP_DATA_MIB_rx_pn_bytes_high_get_indirect(base, offset)	((((*(base + O_VAP_DATA_MIB_rx_pn_bytes_high + offset)) & M_VAP_DATA_MIB_rx_pn_bytes_high) >> B_VAP_DATA_MIB_rx_pn_bytes_high))

#define VAP_DATA_MIB_rx_pn_bytes_high_get_direct(dword)	((((dword) & M_VAP_DATA_MIB_rx_pn_bytes_high) >> B_VAP_DATA_MIB_rx_pn_bytes_high))

#define VAP_DATA_MIB_rx_pn_bytes_high_set_indirect(base, offset, val)    \
	do {                                                              \
		(*(base + O_VAP_DATA_MIB_rx_pn_bytes_high + offset)) &= (~(M_VAP_DATA_MIB_rx_pn_bytes_high));    \
		(*(base + O_VAP_DATA_MIB_rx_pn_bytes_high + offset)) |= ((val << B_VAP_DATA_MIB_rx_pn_bytes_high) & M_VAP_DATA_MIB_rx_pn_bytes_high);    \
	} while (0)

#define VAP_DATA_MIB_rx_pn_bytes_high_set_direct(dword, val)    \
	do {                                                               \
		(dword) &= (~(M_VAP_DATA_MIB_rx_pn_bytes_high));    \
		(dword) |= ((val << B_VAP_DATA_MIB_rx_pn_bytes_high) & M_VAP_DATA_MIB_rx_pn_bytes_high);    \
	} while (0)

#define VAP_DATA_MIB_rx_pn_bytes_high_clear_indirect(base, offset)	((*(base + O_VAP_DATA_MIB_rx_pn_bytes_high + offset)) &= (~(M_VAP_DATA_MIB_rx_pn_bytes_high)))

#define VAP_DATA_MIB_rx_pn_bytes_high_clear_direct(dword)	((dword) &= (~(M_VAP_DATA_MIB_rx_pn_bytes_high)))

#define O_VAP_DATA_MIB_rx_drop_pdu_low 22
#define B_VAP_DATA_MIB_rx_drop_pdu_low 0
#define W_VAP_DATA_MIB_rx_drop_pdu_low 32
#define M_VAP_DATA_MIB_rx_drop_pdu_low 0xffffffff

#define VAP_DATA_MIB_rx_drop_pdu_low_get_indirect(base, offset)	((((*(base + O_VAP_DATA_MIB_rx_drop_pdu_low + offset)) & M_VAP_DATA_MIB_rx_drop_pdu_low) >> B_VAP_DATA_MIB_rx_drop_pdu_low))

#define VAP_DATA_MIB_rx_drop_pdu_low_get_direct(dword)	((((dword) & M_VAP_DATA_MIB_rx_drop_pdu_low) >> B_VAP_DATA_MIB_rx_drop_pdu_low))

#define VAP_DATA_MIB_rx_drop_pdu_low_set_indirect(base, offset, val)    \
	do {                                                              \
		(*(base + O_VAP_DATA_MIB_rx_drop_pdu_low + offset)) &= (~(M_VAP_DATA_MIB_rx_drop_pdu_low));    \
		(*(base + O_VAP_DATA_MIB_rx_drop_pdu_low + offset)) |= ((val << B_VAP_DATA_MIB_rx_drop_pdu_low) & M_VAP_DATA_MIB_rx_drop_pdu_low);    \
	} while (0)

#define VAP_DATA_MIB_rx_drop_pdu_low_set_direct(dword, val)    \
	do {                                                               \
		(dword) &= (~(M_VAP_DATA_MIB_rx_drop_pdu_low));    \
		(dword) |= ((val << B_VAP_DATA_MIB_rx_drop_pdu_low) & M_VAP_DATA_MIB_rx_drop_pdu_low);    \
	} while (0)

#define VAP_DATA_MIB_rx_drop_pdu_low_clear_indirect(base, offset)	((*(base + O_VAP_DATA_MIB_rx_drop_pdu_low + offset)) &= (~(M_VAP_DATA_MIB_rx_drop_pdu_low)))

#define VAP_DATA_MIB_rx_drop_pdu_low_clear_direct(dword)	((dword) &= (~(M_VAP_DATA_MIB_rx_drop_pdu_low)))

#define O_VAP_DATA_MIB_rx_drop_pdu_high 23
#define B_VAP_DATA_MIB_rx_drop_pdu_high 0
#define W_VAP_DATA_MIB_rx_drop_pdu_high 32
#define M_VAP_DATA_MIB_rx_drop_pdu_high 0xffffffff

#define VAP_DATA_MIB_rx_drop_pdu_high_get_indirect(base, offset)	((((*(base + O_VAP_DATA_MIB_rx_drop_pdu_high + offset)) & M_VAP_DATA_MIB_rx_drop_pdu_high) >> B_VAP_DATA_MIB_rx_drop_pdu_high))

#define VAP_DATA_MIB_rx_drop_pdu_high_get_direct(dword)	((((dword) & M_VAP_DATA_MIB_rx_drop_pdu_high) >> B_VAP_DATA_MIB_rx_drop_pdu_high))

#define VAP_DATA_MIB_rx_drop_pdu_high_set_indirect(base, offset, val)    \
	do {                                                              \
		(*(base + O_VAP_DATA_MIB_rx_drop_pdu_high + offset)) &= (~(M_VAP_DATA_MIB_rx_drop_pdu_high));    \
		(*(base + O_VAP_DATA_MIB_rx_drop_pdu_high + offset)) |= ((val << B_VAP_DATA_MIB_rx_drop_pdu_high) & M_VAP_DATA_MIB_rx_drop_pdu_high);    \
	} while (0)

#define VAP_DATA_MIB_rx_drop_pdu_high_set_direct(dword, val)    \
	do {                                                               \
		(dword) &= (~(M_VAP_DATA_MIB_rx_drop_pdu_high));    \
		(dword) |= ((val << B_VAP_DATA_MIB_rx_drop_pdu_high) & M_VAP_DATA_MIB_rx_drop_pdu_high);    \
	} while (0)

#define VAP_DATA_MIB_rx_drop_pdu_high_clear_indirect(base, offset)	((*(base + O_VAP_DATA_MIB_rx_drop_pdu_high + offset)) &= (~(M_VAP_DATA_MIB_rx_drop_pdu_high)))

#define VAP_DATA_MIB_rx_drop_pdu_high_clear_direct(dword)	((dword) &= (~(M_VAP_DATA_MIB_rx_drop_pdu_high)))

#define O_VAP_DATA_MIB_rx_drop_bytes_low 24
#define B_VAP_DATA_MIB_rx_drop_bytes_low 0
#define W_VAP_DATA_MIB_rx_drop_bytes_low 32
#define M_VAP_DATA_MIB_rx_drop_bytes_low 0xffffffff

#define VAP_DATA_MIB_rx_drop_bytes_low_get_indirect(base, offset)	((((*(base + O_VAP_DATA_MIB_rx_drop_bytes_low + offset)) & M_VAP_DATA_MIB_rx_drop_bytes_low) >> B_VAP_DATA_MIB_rx_drop_bytes_low))

#define VAP_DATA_MIB_rx_drop_bytes_low_get_direct(dword)	((((dword) & M_VAP_DATA_MIB_rx_drop_bytes_low) >> B_VAP_DATA_MIB_rx_drop_bytes_low))

#define VAP_DATA_MIB_rx_drop_bytes_low_set_indirect(base, offset, val)    \
	do {                                                              \
		(*(base + O_VAP_DATA_MIB_rx_drop_bytes_low + offset)) &= (~(M_VAP_DATA_MIB_rx_drop_bytes_low));    \
		(*(base + O_VAP_DATA_MIB_rx_drop_bytes_low + offset)) |= ((val << B_VAP_DATA_MIB_rx_drop_bytes_low) & M_VAP_DATA_MIB_rx_drop_bytes_low);    \
	} while (0)

#define VAP_DATA_MIB_rx_drop_bytes_low_set_direct(dword, val)    \
	do {                                                               \
		(dword) &= (~(M_VAP_DATA_MIB_rx_drop_bytes_low));    \
		(dword) |= ((val << B_VAP_DATA_MIB_rx_drop_bytes_low) & M_VAP_DATA_MIB_rx_drop_bytes_low);    \
	} while (0)

#define VAP_DATA_MIB_rx_drop_bytes_low_clear_indirect(base, offset)	((*(base + O_VAP_DATA_MIB_rx_drop_bytes_low + offset)) &= (~(M_VAP_DATA_MIB_rx_drop_bytes_low)))

#define VAP_DATA_MIB_rx_drop_bytes_low_clear_direct(dword)	((dword) &= (~(M_VAP_DATA_MIB_rx_drop_bytes_low)))

#define O_VAP_DATA_MIB_rx_drop_bytes_high 25
#define B_VAP_DATA_MIB_rx_drop_bytes_high 0
#define W_VAP_DATA_MIB_rx_drop_bytes_high 32
#define M_VAP_DATA_MIB_rx_drop_bytes_high 0xffffffff

#define VAP_DATA_MIB_rx_drop_bytes_high_get_indirect(base, offset)	((((*(base + O_VAP_DATA_MIB_rx_drop_bytes_high + offset)) & M_VAP_DATA_MIB_rx_drop_bytes_high) >> B_VAP_DATA_MIB_rx_drop_bytes_high))

#define VAP_DATA_MIB_rx_drop_bytes_high_get_direct(dword)	((((dword) & M_VAP_DATA_MIB_rx_drop_bytes_high) >> B_VAP_DATA_MIB_rx_drop_bytes_high))

#define VAP_DATA_MIB_rx_drop_bytes_high_set_indirect(base, offset, val)    \
	do {                                                              \
		(*(base + O_VAP_DATA_MIB_rx_drop_bytes_high + offset)) &= (~(M_VAP_DATA_MIB_rx_drop_bytes_high));    \
		(*(base + O_VAP_DATA_MIB_rx_drop_bytes_high + offset)) |= ((val << B_VAP_DATA_MIB_rx_drop_bytes_high) & M_VAP_DATA_MIB_rx_drop_bytes_high);    \
	} while (0)

#define VAP_DATA_MIB_rx_drop_bytes_high_set_direct(dword, val)    \
	do {                                                               \
		(dword) &= (~(M_VAP_DATA_MIB_rx_drop_bytes_high));    \
		(dword) |= ((val << B_VAP_DATA_MIB_rx_drop_bytes_high) & M_VAP_DATA_MIB_rx_drop_bytes_high);    \
	} while (0)

#define VAP_DATA_MIB_rx_drop_bytes_high_clear_indirect(base, offset)	((*(base + O_VAP_DATA_MIB_rx_drop_bytes_high + offset)) &= (~(M_VAP_DATA_MIB_rx_drop_bytes_high)))

#define VAP_DATA_MIB_rx_drop_bytes_high_clear_direct(dword)	((dword) &= (~(M_VAP_DATA_MIB_rx_drop_bytes_high)))

#define O_VAP_DATA_MIB_rx_rcv_pdu_low 26
#define B_VAP_DATA_MIB_rx_rcv_pdu_low 0
#define W_VAP_DATA_MIB_rx_rcv_pdu_low 32
#define M_VAP_DATA_MIB_rx_rcv_pdu_low 0xffffffff

#define VAP_DATA_MIB_rx_rcv_pdu_low_get_indirect(base, offset)	((((*(base + O_VAP_DATA_MIB_rx_rcv_pdu_low + offset)) & M_VAP_DATA_MIB_rx_rcv_pdu_low) >> B_VAP_DATA_MIB_rx_rcv_pdu_low))

#define VAP_DATA_MIB_rx_rcv_pdu_low_get_direct(dword)	((((dword) & M_VAP_DATA_MIB_rx_rcv_pdu_low) >> B_VAP_DATA_MIB_rx_rcv_pdu_low))

#define VAP_DATA_MIB_rx_rcv_pdu_low_set_indirect(base, offset, val)    \
	do {                                                              \
		(*(base + O_VAP_DATA_MIB_rx_rcv_pdu_low + offset)) &= (~(M_VAP_DATA_MIB_rx_rcv_pdu_low));    \
		(*(base + O_VAP_DATA_MIB_rx_rcv_pdu_low + offset)) |= ((val << B_VAP_DATA_MIB_rx_rcv_pdu_low) & M_VAP_DATA_MIB_rx_rcv_pdu_low);    \
	} while (0)

#define VAP_DATA_MIB_rx_rcv_pdu_low_set_direct(dword, val)    \
	do {                                                               \
		(dword) &= (~(M_VAP_DATA_MIB_rx_rcv_pdu_low));    \
		(dword) |= ((val << B_VAP_DATA_MIB_rx_rcv_pdu_low) & M_VAP_DATA_MIB_rx_rcv_pdu_low);    \
	} while (0)

#define VAP_DATA_MIB_rx_rcv_pdu_low_clear_indirect(base, offset)	((*(base + O_VAP_DATA_MIB_rx_rcv_pdu_low + offset)) &= (~(M_VAP_DATA_MIB_rx_rcv_pdu_low)))

#define VAP_DATA_MIB_rx_rcv_pdu_low_clear_direct(dword)	((dword) &= (~(M_VAP_DATA_MIB_rx_rcv_pdu_low)))

#define O_VAP_DATA_MIB_rx_rcv_pdu_high 27
#define B_VAP_DATA_MIB_rx_rcv_pdu_high 0
#define W_VAP_DATA_MIB_rx_rcv_pdu_high 32
#define M_VAP_DATA_MIB_rx_rcv_pdu_high 0xffffffff

#define VAP_DATA_MIB_rx_rcv_pdu_high_get_indirect(base, offset)	((((*(base + O_VAP_DATA_MIB_rx_rcv_pdu_high + offset)) & M_VAP_DATA_MIB_rx_rcv_pdu_high) >> B_VAP_DATA_MIB_rx_rcv_pdu_high))

#define VAP_DATA_MIB_rx_rcv_pdu_high_get_direct(dword)	((((dword) & M_VAP_DATA_MIB_rx_rcv_pdu_high) >> B_VAP_DATA_MIB_rx_rcv_pdu_high))

#define VAP_DATA_MIB_rx_rcv_pdu_high_set_indirect(base, offset, val)    \
	do {                                                              \
		(*(base + O_VAP_DATA_MIB_rx_rcv_pdu_high + offset)) &= (~(M_VAP_DATA_MIB_rx_rcv_pdu_high));    \
		(*(base + O_VAP_DATA_MIB_rx_rcv_pdu_high + offset)) |= ((val << B_VAP_DATA_MIB_rx_rcv_pdu_high) & M_VAP_DATA_MIB_rx_rcv_pdu_high);    \
	} while (0)

#define VAP_DATA_MIB_rx_rcv_pdu_high_set_direct(dword, val)    \
	do {                                                               \
		(dword) &= (~(M_VAP_DATA_MIB_rx_rcv_pdu_high));    \
		(dword) |= ((val << B_VAP_DATA_MIB_rx_rcv_pdu_high) & M_VAP_DATA_MIB_rx_rcv_pdu_high);    \
	} while (0)

#define VAP_DATA_MIB_rx_rcv_pdu_high_clear_indirect(base, offset)	((*(base + O_VAP_DATA_MIB_rx_rcv_pdu_high + offset)) &= (~(M_VAP_DATA_MIB_rx_rcv_pdu_high)))

#define VAP_DATA_MIB_rx_rcv_pdu_high_clear_direct(dword)	((dword) &= (~(M_VAP_DATA_MIB_rx_rcv_pdu_high)))

#define O_VAP_DATA_MIB_rx_rcv_bytes_low 28
#define B_VAP_DATA_MIB_rx_rcv_bytes_low 0
#define W_VAP_DATA_MIB_rx_rcv_bytes_low 32
#define M_VAP_DATA_MIB_rx_rcv_bytes_low 0xffffffff

#define VAP_DATA_MIB_rx_rcv_bytes_low_get_indirect(base, offset)	((((*(base + O_VAP_DATA_MIB_rx_rcv_bytes_low + offset)) & M_VAP_DATA_MIB_rx_rcv_bytes_low) >> B_VAP_DATA_MIB_rx_rcv_bytes_low))

#define VAP_DATA_MIB_rx_rcv_bytes_low_get_direct(dword)	((((dword) & M_VAP_DATA_MIB_rx_rcv_bytes_low) >> B_VAP_DATA_MIB_rx_rcv_bytes_low))

#define VAP_DATA_MIB_rx_rcv_bytes_low_set_indirect(base, offset, val)    \
	do {                                                              \
		(*(base + O_VAP_DATA_MIB_rx_rcv_bytes_low + offset)) &= (~(M_VAP_DATA_MIB_rx_rcv_bytes_low));    \
		(*(base + O_VAP_DATA_MIB_rx_rcv_bytes_low + offset)) |= ((val << B_VAP_DATA_MIB_rx_rcv_bytes_low) & M_VAP_DATA_MIB_rx_rcv_bytes_low);    \
	} while (0)

#define VAP_DATA_MIB_rx_rcv_bytes_low_set_direct(dword, val)    \
	do {                                                               \
		(dword) &= (~(M_VAP_DATA_MIB_rx_rcv_bytes_low));    \
		(dword) |= ((val << B_VAP_DATA_MIB_rx_rcv_bytes_low) & M_VAP_DATA_MIB_rx_rcv_bytes_low);    \
	} while (0)

#define VAP_DATA_MIB_rx_rcv_bytes_low_clear_indirect(base, offset)	((*(base + O_VAP_DATA_MIB_rx_rcv_bytes_low + offset)) &= (~(M_VAP_DATA_MIB_rx_rcv_bytes_low)))

#define VAP_DATA_MIB_rx_rcv_bytes_low_clear_direct(dword)	((dword) &= (~(M_VAP_DATA_MIB_rx_rcv_bytes_low)))

#define O_VAP_DATA_MIB_rx_rcv_bytes_high 29
#define B_VAP_DATA_MIB_rx_rcv_bytes_high 0
#define W_VAP_DATA_MIB_rx_rcv_bytes_high 32
#define M_VAP_DATA_MIB_rx_rcv_bytes_high 0xffffffff

#define VAP_DATA_MIB_rx_rcv_bytes_high_get_indirect(base, offset)	((((*(base + O_VAP_DATA_MIB_rx_rcv_bytes_high + offset)) & M_VAP_DATA_MIB_rx_rcv_bytes_high) >> B_VAP_DATA_MIB_rx_rcv_bytes_high))

#define VAP_DATA_MIB_rx_rcv_bytes_high_get_direct(dword)	((((dword) & M_VAP_DATA_MIB_rx_rcv_bytes_high) >> B_VAP_DATA_MIB_rx_rcv_bytes_high))

#define VAP_DATA_MIB_rx_rcv_bytes_high_set_indirect(base, offset, val)    \
	do {                                                              \
		(*(base + O_VAP_DATA_MIB_rx_rcv_bytes_high + offset)) &= (~(M_VAP_DATA_MIB_rx_rcv_bytes_high));    \
		(*(base + O_VAP_DATA_MIB_rx_rcv_bytes_high + offset)) |= ((val << B_VAP_DATA_MIB_rx_rcv_bytes_high) & M_VAP_DATA_MIB_rx_rcv_bytes_high);    \
	} while (0)

#define VAP_DATA_MIB_rx_rcv_bytes_high_set_direct(dword, val)    \
	do {                                                               \
		(dword) &= (~(M_VAP_DATA_MIB_rx_rcv_bytes_high));    \
		(dword) |= ((val << B_VAP_DATA_MIB_rx_rcv_bytes_high) & M_VAP_DATA_MIB_rx_rcv_bytes_high);    \
	} while (0)

#define VAP_DATA_MIB_rx_rcv_bytes_high_clear_indirect(base, offset)	((*(base + O_VAP_DATA_MIB_rx_rcv_bytes_high + offset)) &= (~(M_VAP_DATA_MIB_rx_rcv_bytes_high)))

#define VAP_DATA_MIB_rx_rcv_bytes_high_clear_direct(dword)	((dword) &= (~(M_VAP_DATA_MIB_rx_rcv_bytes_high)))

#define O_VAP_DATA_MISC_MIB_rx_gswip_packets_low 0
#define B_VAP_DATA_MISC_MIB_rx_gswip_packets_low 0
#define W_VAP_DATA_MISC_MIB_rx_gswip_packets_low 32
#define M_VAP_DATA_MISC_MIB_rx_gswip_packets_low 0xffffffff

#define VAP_DATA_MISC_MIB_rx_gswip_packets_low_get_indirect(base, offset)	((((*(base + O_VAP_DATA_MISC_MIB_rx_gswip_packets_low + offset)) & M_VAP_DATA_MISC_MIB_rx_gswip_packets_low) >> B_VAP_DATA_MISC_MIB_rx_gswip_packets_low))

#define VAP_DATA_MISC_MIB_rx_gswip_packets_low_get_direct(dword)	((((dword) & M_VAP_DATA_MISC_MIB_rx_gswip_packets_low) >> B_VAP_DATA_MISC_MIB_rx_gswip_packets_low))

#define VAP_DATA_MISC_MIB_rx_gswip_packets_low_set_indirect(base, offset, val)    \
	do {                                                              \
		(*(base + O_VAP_DATA_MISC_MIB_rx_gswip_packets_low + offset)) &= (~(M_VAP_DATA_MISC_MIB_rx_gswip_packets_low));    \
		(*(base + O_VAP_DATA_MISC_MIB_rx_gswip_packets_low + offset)) |= ((val << B_VAP_DATA_MISC_MIB_rx_gswip_packets_low) & M_VAP_DATA_MISC_MIB_rx_gswip_packets_low);    \
	} while (0)

#define VAP_DATA_MISC_MIB_rx_gswip_packets_low_set_direct(dword, val)    \
	do {                                                               \
		(dword) &= (~(M_VAP_DATA_MISC_MIB_rx_gswip_packets_low));    \
		(dword) |= ((val << B_VAP_DATA_MISC_MIB_rx_gswip_packets_low) & M_VAP_DATA_MISC_MIB_rx_gswip_packets_low);    \
	} while (0)

#define VAP_DATA_MISC_MIB_rx_gswip_packets_low_clear_indirect(base, offset)	((*(base + O_VAP_DATA_MISC_MIB_rx_gswip_packets_low + offset)) &= (~(M_VAP_DATA_MISC_MIB_rx_gswip_packets_low)))

#define VAP_DATA_MISC_MIB_rx_gswip_packets_low_clear_direct(dword)	((dword) &= (~(M_VAP_DATA_MISC_MIB_rx_gswip_packets_low)))

#define O_VAP_DATA_MISC_MIB_rx_gswip_packets_high 1
#define B_VAP_DATA_MISC_MIB_rx_gswip_packets_high 0
#define W_VAP_DATA_MISC_MIB_rx_gswip_packets_high 32
#define M_VAP_DATA_MISC_MIB_rx_gswip_packets_high 0xffffffff

#define VAP_DATA_MISC_MIB_rx_gswip_packets_high_get_indirect(base, offset)	((((*(base + O_VAP_DATA_MISC_MIB_rx_gswip_packets_high + offset)) & M_VAP_DATA_MISC_MIB_rx_gswip_packets_high) >> B_VAP_DATA_MISC_MIB_rx_gswip_packets_high))

#define VAP_DATA_MISC_MIB_rx_gswip_packets_high_get_direct(dword)	((((dword) & M_VAP_DATA_MISC_MIB_rx_gswip_packets_high) >> B_VAP_DATA_MISC_MIB_rx_gswip_packets_high))

#define VAP_DATA_MISC_MIB_rx_gswip_packets_high_set_indirect(base, offset, val)    \
	do {                                                              \
		(*(base + O_VAP_DATA_MISC_MIB_rx_gswip_packets_high + offset)) &= (~(M_VAP_DATA_MISC_MIB_rx_gswip_packets_high));    \
		(*(base + O_VAP_DATA_MISC_MIB_rx_gswip_packets_high + offset)) |= ((val << B_VAP_DATA_MISC_MIB_rx_gswip_packets_high) & M_VAP_DATA_MISC_MIB_rx_gswip_packets_high);    \
	} while (0)

#define VAP_DATA_MISC_MIB_rx_gswip_packets_high_set_direct(dword, val)    \
	do {                                                               \
		(dword) &= (~(M_VAP_DATA_MISC_MIB_rx_gswip_packets_high));    \
		(dword) |= ((val << B_VAP_DATA_MISC_MIB_rx_gswip_packets_high) & M_VAP_DATA_MISC_MIB_rx_gswip_packets_high);    \
	} while (0)

#define VAP_DATA_MISC_MIB_rx_gswip_packets_high_clear_indirect(base, offset)	((*(base + O_VAP_DATA_MISC_MIB_rx_gswip_packets_high + offset)) &= (~(M_VAP_DATA_MISC_MIB_rx_gswip_packets_high)))

#define VAP_DATA_MISC_MIB_rx_gswip_packets_high_clear_direct(dword)	((dword) &= (~(M_VAP_DATA_MISC_MIB_rx_gswip_packets_high)))

#define O_VAP_DATA_MISC_MIB_rx_gswip_bytes_low 2
#define B_VAP_DATA_MISC_MIB_rx_gswip_bytes_low 0
#define W_VAP_DATA_MISC_MIB_rx_gswip_bytes_low 32
#define M_VAP_DATA_MISC_MIB_rx_gswip_bytes_low 0xffffffff

#define VAP_DATA_MISC_MIB_rx_gswip_bytes_low_get_indirect(base, offset)	((((*(base + O_VAP_DATA_MISC_MIB_rx_gswip_bytes_low + offset)) & M_VAP_DATA_MISC_MIB_rx_gswip_bytes_low) >> B_VAP_DATA_MISC_MIB_rx_gswip_bytes_low))

#define VAP_DATA_MISC_MIB_rx_gswip_bytes_low_get_direct(dword)	((((dword) & M_VAP_DATA_MISC_MIB_rx_gswip_bytes_low) >> B_VAP_DATA_MISC_MIB_rx_gswip_bytes_low))

#define VAP_DATA_MISC_MIB_rx_gswip_bytes_low_set_indirect(base, offset, val)    \
	do {                                                              \
		(*(base + O_VAP_DATA_MISC_MIB_rx_gswip_bytes_low + offset)) &= (~(M_VAP_DATA_MISC_MIB_rx_gswip_bytes_low));    \
		(*(base + O_VAP_DATA_MISC_MIB_rx_gswip_bytes_low + offset)) |= ((val << B_VAP_DATA_MISC_MIB_rx_gswip_bytes_low) & M_VAP_DATA_MISC_MIB_rx_gswip_bytes_low);    \
	} while (0)

#define VAP_DATA_MISC_MIB_rx_gswip_bytes_low_set_direct(dword, val)    \
	do {                                                               \
		(dword) &= (~(M_VAP_DATA_MISC_MIB_rx_gswip_bytes_low));    \
		(dword) |= ((val << B_VAP_DATA_MISC_MIB_rx_gswip_bytes_low) & M_VAP_DATA_MISC_MIB_rx_gswip_bytes_low);    \
	} while (0)

#define VAP_DATA_MISC_MIB_rx_gswip_bytes_low_clear_indirect(base, offset)	((*(base + O_VAP_DATA_MISC_MIB_rx_gswip_bytes_low + offset)) &= (~(M_VAP_DATA_MISC_MIB_rx_gswip_bytes_low)))

#define VAP_DATA_MISC_MIB_rx_gswip_bytes_low_clear_direct(dword)	((dword) &= (~(M_VAP_DATA_MISC_MIB_rx_gswip_bytes_low)))

#define O_VAP_DATA_MISC_MIB_rx_gswip_bytes_high 3
#define B_VAP_DATA_MISC_MIB_rx_gswip_bytes_high 0
#define W_VAP_DATA_MISC_MIB_rx_gswip_bytes_high 32
#define M_VAP_DATA_MISC_MIB_rx_gswip_bytes_high 0xffffffff

#define VAP_DATA_MISC_MIB_rx_gswip_bytes_high_get_indirect(base, offset)	((((*(base + O_VAP_DATA_MISC_MIB_rx_gswip_bytes_high + offset)) & M_VAP_DATA_MISC_MIB_rx_gswip_bytes_high) >> B_VAP_DATA_MISC_MIB_rx_gswip_bytes_high))

#define VAP_DATA_MISC_MIB_rx_gswip_bytes_high_get_direct(dword)	((((dword) & M_VAP_DATA_MISC_MIB_rx_gswip_bytes_high) >> B_VAP_DATA_MISC_MIB_rx_gswip_bytes_high))

#define VAP_DATA_MISC_MIB_rx_gswip_bytes_high_set_indirect(base, offset, val)    \
	do {                                                              \
		(*(base + O_VAP_DATA_MISC_MIB_rx_gswip_bytes_high + offset)) &= (~(M_VAP_DATA_MISC_MIB_rx_gswip_bytes_high));    \
		(*(base + O_VAP_DATA_MISC_MIB_rx_gswip_bytes_high + offset)) |= ((val << B_VAP_DATA_MISC_MIB_rx_gswip_bytes_high) & M_VAP_DATA_MISC_MIB_rx_gswip_bytes_high);    \
	} while (0)

#define VAP_DATA_MISC_MIB_rx_gswip_bytes_high_set_direct(dword, val)    \
	do {                                                               \
		(dword) &= (~(M_VAP_DATA_MISC_MIB_rx_gswip_bytes_high));    \
		(dword) |= ((val << B_VAP_DATA_MISC_MIB_rx_gswip_bytes_high) & M_VAP_DATA_MISC_MIB_rx_gswip_bytes_high);    \
	} while (0)

#define VAP_DATA_MISC_MIB_rx_gswip_bytes_high_clear_indirect(base, offset)	((*(base + O_VAP_DATA_MISC_MIB_rx_gswip_bytes_high + offset)) &= (~(M_VAP_DATA_MISC_MIB_rx_gswip_bytes_high)))

#define VAP_DATA_MISC_MIB_rx_gswip_bytes_high_clear_direct(dword)	((dword) &= (~(M_VAP_DATA_MISC_MIB_rx_gswip_bytes_high)))

#define O_VAP_DATA_MISC_MIB_rx_wlan_packets_low 4
#define B_VAP_DATA_MISC_MIB_rx_wlan_packets_low 0
#define W_VAP_DATA_MISC_MIB_rx_wlan_packets_low 32
#define M_VAP_DATA_MISC_MIB_rx_wlan_packets_low 0xffffffff

#define VAP_DATA_MISC_MIB_rx_wlan_packets_low_get_indirect(base, offset)	((((*(base + O_VAP_DATA_MISC_MIB_rx_wlan_packets_low + offset)) & M_VAP_DATA_MISC_MIB_rx_wlan_packets_low) >> B_VAP_DATA_MISC_MIB_rx_wlan_packets_low))

#define VAP_DATA_MISC_MIB_rx_wlan_packets_low_get_direct(dword)	((((dword) & M_VAP_DATA_MISC_MIB_rx_wlan_packets_low) >> B_VAP_DATA_MISC_MIB_rx_wlan_packets_low))

#define VAP_DATA_MISC_MIB_rx_wlan_packets_low_set_indirect(base, offset, val)    \
	do {                                                              \
		(*(base + O_VAP_DATA_MISC_MIB_rx_wlan_packets_low + offset)) &= (~(M_VAP_DATA_MISC_MIB_rx_wlan_packets_low));    \
		(*(base + O_VAP_DATA_MISC_MIB_rx_wlan_packets_low + offset)) |= ((val << B_VAP_DATA_MISC_MIB_rx_wlan_packets_low) & M_VAP_DATA_MISC_MIB_rx_wlan_packets_low);    \
	} while (0)

#define VAP_DATA_MISC_MIB_rx_wlan_packets_low_set_direct(dword, val)    \
	do {                                                               \
		(dword) &= (~(M_VAP_DATA_MISC_MIB_rx_wlan_packets_low));    \
		(dword) |= ((val << B_VAP_DATA_MISC_MIB_rx_wlan_packets_low) & M_VAP_DATA_MISC_MIB_rx_wlan_packets_low);    \
	} while (0)

#define VAP_DATA_MISC_MIB_rx_wlan_packets_low_clear_indirect(base, offset)	((*(base + O_VAP_DATA_MISC_MIB_rx_wlan_packets_low + offset)) &= (~(M_VAP_DATA_MISC_MIB_rx_wlan_packets_low)))

#define VAP_DATA_MISC_MIB_rx_wlan_packets_low_clear_direct(dword)	((dword) &= (~(M_VAP_DATA_MISC_MIB_rx_wlan_packets_low)))

#define O_VAP_DATA_MISC_MIB_rx_wlan_packets_high 5
#define B_VAP_DATA_MISC_MIB_rx_wlan_packets_high 0
#define W_VAP_DATA_MISC_MIB_rx_wlan_packets_high 32
#define M_VAP_DATA_MISC_MIB_rx_wlan_packets_high 0xffffffff

#define VAP_DATA_MISC_MIB_rx_wlan_packets_high_get_indirect(base, offset)	((((*(base + O_VAP_DATA_MISC_MIB_rx_wlan_packets_high + offset)) & M_VAP_DATA_MISC_MIB_rx_wlan_packets_high) >> B_VAP_DATA_MISC_MIB_rx_wlan_packets_high))

#define VAP_DATA_MISC_MIB_rx_wlan_packets_high_get_direct(dword)	((((dword) & M_VAP_DATA_MISC_MIB_rx_wlan_packets_high) >> B_VAP_DATA_MISC_MIB_rx_wlan_packets_high))

#define VAP_DATA_MISC_MIB_rx_wlan_packets_high_set_indirect(base, offset, val)    \
	do {                                                              \
		(*(base + O_VAP_DATA_MISC_MIB_rx_wlan_packets_high + offset)) &= (~(M_VAP_DATA_MISC_MIB_rx_wlan_packets_high));    \
		(*(base + O_VAP_DATA_MISC_MIB_rx_wlan_packets_high + offset)) |= ((val << B_VAP_DATA_MISC_MIB_rx_wlan_packets_high) & M_VAP_DATA_MISC_MIB_rx_wlan_packets_high);    \
	} while (0)

#define VAP_DATA_MISC_MIB_rx_wlan_packets_high_set_direct(dword, val)    \
	do {                                                               \
		(dword) &= (~(M_VAP_DATA_MISC_MIB_rx_wlan_packets_high));    \
		(dword) |= ((val << B_VAP_DATA_MISC_MIB_rx_wlan_packets_high) & M_VAP_DATA_MISC_MIB_rx_wlan_packets_high);    \
	} while (0)

#define VAP_DATA_MISC_MIB_rx_wlan_packets_high_clear_indirect(base, offset)	((*(base + O_VAP_DATA_MISC_MIB_rx_wlan_packets_high + offset)) &= (~(M_VAP_DATA_MISC_MIB_rx_wlan_packets_high)))

#define VAP_DATA_MISC_MIB_rx_wlan_packets_high_clear_direct(dword)	((dword) &= (~(M_VAP_DATA_MISC_MIB_rx_wlan_packets_high)))

#define O_VAP_DATA_MISC_MIB_rx_wlan_bytes_low 6
#define B_VAP_DATA_MISC_MIB_rx_wlan_bytes_low 0
#define W_VAP_DATA_MISC_MIB_rx_wlan_bytes_low 32
#define M_VAP_DATA_MISC_MIB_rx_wlan_bytes_low 0xffffffff

#define VAP_DATA_MISC_MIB_rx_wlan_bytes_low_get_indirect(base, offset)	((((*(base + O_VAP_DATA_MISC_MIB_rx_wlan_bytes_low + offset)) & M_VAP_DATA_MISC_MIB_rx_wlan_bytes_low) >> B_VAP_DATA_MISC_MIB_rx_wlan_bytes_low))

#define VAP_DATA_MISC_MIB_rx_wlan_bytes_low_get_direct(dword)	((((dword) & M_VAP_DATA_MISC_MIB_rx_wlan_bytes_low) >> B_VAP_DATA_MISC_MIB_rx_wlan_bytes_low))

#define VAP_DATA_MISC_MIB_rx_wlan_bytes_low_set_indirect(base, offset, val)    \
	do {                                                              \
		(*(base + O_VAP_DATA_MISC_MIB_rx_wlan_bytes_low + offset)) &= (~(M_VAP_DATA_MISC_MIB_rx_wlan_bytes_low));    \
		(*(base + O_VAP_DATA_MISC_MIB_rx_wlan_bytes_low + offset)) |= ((val << B_VAP_DATA_MISC_MIB_rx_wlan_bytes_low) & M_VAP_DATA_MISC_MIB_rx_wlan_bytes_low);    \
	} while (0)

#define VAP_DATA_MISC_MIB_rx_wlan_bytes_low_set_direct(dword, val)    \
	do {                                                               \
		(dword) &= (~(M_VAP_DATA_MISC_MIB_rx_wlan_bytes_low));    \
		(dword) |= ((val << B_VAP_DATA_MISC_MIB_rx_wlan_bytes_low) & M_VAP_DATA_MISC_MIB_rx_wlan_bytes_low);    \
	} while (0)

#define VAP_DATA_MISC_MIB_rx_wlan_bytes_low_clear_indirect(base, offset)	((*(base + O_VAP_DATA_MISC_MIB_rx_wlan_bytes_low + offset)) &= (~(M_VAP_DATA_MISC_MIB_rx_wlan_bytes_low)))

#define VAP_DATA_MISC_MIB_rx_wlan_bytes_low_clear_direct(dword)	((dword) &= (~(M_VAP_DATA_MISC_MIB_rx_wlan_bytes_low)))

#define O_VAP_DATA_MISC_MIB_rx_wlan_bytes_high 7
#define B_VAP_DATA_MISC_MIB_rx_wlan_bytes_high 0
#define W_VAP_DATA_MISC_MIB_rx_wlan_bytes_high 32
#define M_VAP_DATA_MISC_MIB_rx_wlan_bytes_high 0xffffffff

#define VAP_DATA_MISC_MIB_rx_wlan_bytes_high_get_indirect(base, offset)	((((*(base + O_VAP_DATA_MISC_MIB_rx_wlan_bytes_high + offset)) & M_VAP_DATA_MISC_MIB_rx_wlan_bytes_high) >> B_VAP_DATA_MISC_MIB_rx_wlan_bytes_high))

#define VAP_DATA_MISC_MIB_rx_wlan_bytes_high_get_direct(dword)	((((dword) & M_VAP_DATA_MISC_MIB_rx_wlan_bytes_high) >> B_VAP_DATA_MISC_MIB_rx_wlan_bytes_high))

#define VAP_DATA_MISC_MIB_rx_wlan_bytes_high_set_indirect(base, offset, val)    \
	do {                                                              \
		(*(base + O_VAP_DATA_MISC_MIB_rx_wlan_bytes_high + offset)) &= (~(M_VAP_DATA_MISC_MIB_rx_wlan_bytes_high));    \
		(*(base + O_VAP_DATA_MISC_MIB_rx_wlan_bytes_high + offset)) |= ((val << B_VAP_DATA_MISC_MIB_rx_wlan_bytes_high) & M_VAP_DATA_MISC_MIB_rx_wlan_bytes_high);    \
	} while (0)

#define VAP_DATA_MISC_MIB_rx_wlan_bytes_high_set_direct(dword, val)    \
	do {                                                               \
		(dword) &= (~(M_VAP_DATA_MISC_MIB_rx_wlan_bytes_high));    \
		(dword) |= ((val << B_VAP_DATA_MISC_MIB_rx_wlan_bytes_high) & M_VAP_DATA_MISC_MIB_rx_wlan_bytes_high);    \
	} while (0)

#define VAP_DATA_MISC_MIB_rx_wlan_bytes_high_clear_indirect(base, offset)	((*(base + O_VAP_DATA_MISC_MIB_rx_wlan_bytes_high + offset)) &= (~(M_VAP_DATA_MISC_MIB_rx_wlan_bytes_high)))

#define VAP_DATA_MISC_MIB_rx_wlan_bytes_high_clear_direct(dword)	((dword) &= (~(M_VAP_DATA_MISC_MIB_rx_wlan_bytes_high)))

#define O_VAP_DATA_MISC_MIB_rx_protocol_stack_packets_low 8
#define B_VAP_DATA_MISC_MIB_rx_protocol_stack_packets_low 0
#define W_VAP_DATA_MISC_MIB_rx_protocol_stack_packets_low 32
#define M_VAP_DATA_MISC_MIB_rx_protocol_stack_packets_low 0xffffffff

#define VAP_DATA_MISC_MIB_rx_protocol_stack_packets_low_get_indirect(base, offset)	((((*(base + O_VAP_DATA_MISC_MIB_rx_protocol_stack_packets_low + offset)) & M_VAP_DATA_MISC_MIB_rx_protocol_stack_packets_low) >> B_VAP_DATA_MISC_MIB_rx_protocol_stack_packets_low))

#define VAP_DATA_MISC_MIB_rx_protocol_stack_packets_low_get_direct(dword)	((((dword) & M_VAP_DATA_MISC_MIB_rx_protocol_stack_packets_low) >> B_VAP_DATA_MISC_MIB_rx_protocol_stack_packets_low))

#define VAP_DATA_MISC_MIB_rx_protocol_stack_packets_low_set_indirect(base, offset, val)    \
	do {                                                              \
		(*(base + O_VAP_DATA_MISC_MIB_rx_protocol_stack_packets_low + offset)) &= (~(M_VAP_DATA_MISC_MIB_rx_protocol_stack_packets_low));    \
		(*(base + O_VAP_DATA_MISC_MIB_rx_protocol_stack_packets_low + offset)) |= ((val << B_VAP_DATA_MISC_MIB_rx_protocol_stack_packets_low) & M_VAP_DATA_MISC_MIB_rx_protocol_stack_packets_low);    \
	} while (0)

#define VAP_DATA_MISC_MIB_rx_protocol_stack_packets_low_set_direct(dword, val)    \
	do {                                                               \
		(dword) &= (~(M_VAP_DATA_MISC_MIB_rx_protocol_stack_packets_low));    \
		(dword) |= ((val << B_VAP_DATA_MISC_MIB_rx_protocol_stack_packets_low) & M_VAP_DATA_MISC_MIB_rx_protocol_stack_packets_low);    \
	} while (0)

#define VAP_DATA_MISC_MIB_rx_protocol_stack_packets_low_clear_indirect(base, offset)	((*(base + O_VAP_DATA_MISC_MIB_rx_protocol_stack_packets_low + offset)) &= (~(M_VAP_DATA_MISC_MIB_rx_protocol_stack_packets_low)))

#define VAP_DATA_MISC_MIB_rx_protocol_stack_packets_low_clear_direct(dword)	((dword) &= (~(M_VAP_DATA_MISC_MIB_rx_protocol_stack_packets_low)))

#define O_VAP_DATA_MISC_MIB_rx_protocol_stack_packets_high 9
#define B_VAP_DATA_MISC_MIB_rx_protocol_stack_packets_high 0
#define W_VAP_DATA_MISC_MIB_rx_protocol_stack_packets_high 32
#define M_VAP_DATA_MISC_MIB_rx_protocol_stack_packets_high 0xffffffff

#define VAP_DATA_MISC_MIB_rx_protocol_stack_packets_high_get_indirect(base, offset)	((((*(base + O_VAP_DATA_MISC_MIB_rx_protocol_stack_packets_high + offset)) & M_VAP_DATA_MISC_MIB_rx_protocol_stack_packets_high) >> B_VAP_DATA_MISC_MIB_rx_protocol_stack_packets_high))

#define VAP_DATA_MISC_MIB_rx_protocol_stack_packets_high_get_direct(dword)	((((dword) & M_VAP_DATA_MISC_MIB_rx_protocol_stack_packets_high) >> B_VAP_DATA_MISC_MIB_rx_protocol_stack_packets_high))

#define VAP_DATA_MISC_MIB_rx_protocol_stack_packets_high_set_indirect(base, offset, val)    \
	do {                                                              \
		(*(base + O_VAP_DATA_MISC_MIB_rx_protocol_stack_packets_high + offset)) &= (~(M_VAP_DATA_MISC_MIB_rx_protocol_stack_packets_high));    \
		(*(base + O_VAP_DATA_MISC_MIB_rx_protocol_stack_packets_high + offset)) |= ((val << B_VAP_DATA_MISC_MIB_rx_protocol_stack_packets_high) & M_VAP_DATA_MISC_MIB_rx_protocol_stack_packets_high);    \
	} while (0)

#define VAP_DATA_MISC_MIB_rx_protocol_stack_packets_high_set_direct(dword, val)    \
	do {                                                               \
		(dword) &= (~(M_VAP_DATA_MISC_MIB_rx_protocol_stack_packets_high));    \
		(dword) |= ((val << B_VAP_DATA_MISC_MIB_rx_protocol_stack_packets_high) & M_VAP_DATA_MISC_MIB_rx_protocol_stack_packets_high);    \
	} while (0)

#define VAP_DATA_MISC_MIB_rx_protocol_stack_packets_high_clear_indirect(base, offset)	((*(base + O_VAP_DATA_MISC_MIB_rx_protocol_stack_packets_high + offset)) &= (~(M_VAP_DATA_MISC_MIB_rx_protocol_stack_packets_high)))

#define VAP_DATA_MISC_MIB_rx_protocol_stack_packets_high_clear_direct(dword)	((dword) &= (~(M_VAP_DATA_MISC_MIB_rx_protocol_stack_packets_high)))

#define O_VAP_DATA_MISC_MIB_rx_protocol_stack_bytes_low 10
#define B_VAP_DATA_MISC_MIB_rx_protocol_stack_bytes_low 0
#define W_VAP_DATA_MISC_MIB_rx_protocol_stack_bytes_low 32
#define M_VAP_DATA_MISC_MIB_rx_protocol_stack_bytes_low 0xffffffff

#define VAP_DATA_MISC_MIB_rx_protocol_stack_bytes_low_get_indirect(base, offset)	((((*(base + O_VAP_DATA_MISC_MIB_rx_protocol_stack_bytes_low + offset)) & M_VAP_DATA_MISC_MIB_rx_protocol_stack_bytes_low) >> B_VAP_DATA_MISC_MIB_rx_protocol_stack_bytes_low))

#define VAP_DATA_MISC_MIB_rx_protocol_stack_bytes_low_get_direct(dword)	((((dword) & M_VAP_DATA_MISC_MIB_rx_protocol_stack_bytes_low) >> B_VAP_DATA_MISC_MIB_rx_protocol_stack_bytes_low))

#define VAP_DATA_MISC_MIB_rx_protocol_stack_bytes_low_set_indirect(base, offset, val)    \
	do {                                                              \
		(*(base + O_VAP_DATA_MISC_MIB_rx_protocol_stack_bytes_low + offset)) &= (~(M_VAP_DATA_MISC_MIB_rx_protocol_stack_bytes_low));    \
		(*(base + O_VAP_DATA_MISC_MIB_rx_protocol_stack_bytes_low + offset)) |= ((val << B_VAP_DATA_MISC_MIB_rx_protocol_stack_bytes_low) & M_VAP_DATA_MISC_MIB_rx_protocol_stack_bytes_low);    \
	} while (0)

#define VAP_DATA_MISC_MIB_rx_protocol_stack_bytes_low_set_direct(dword, val)    \
	do {                                                               \
		(dword) &= (~(M_VAP_DATA_MISC_MIB_rx_protocol_stack_bytes_low));    \
		(dword) |= ((val << B_VAP_DATA_MISC_MIB_rx_protocol_stack_bytes_low) & M_VAP_DATA_MISC_MIB_rx_protocol_stack_bytes_low);    \
	} while (0)

#define VAP_DATA_MISC_MIB_rx_protocol_stack_bytes_low_clear_indirect(base, offset)	((*(base + O_VAP_DATA_MISC_MIB_rx_protocol_stack_bytes_low + offset)) &= (~(M_VAP_DATA_MISC_MIB_rx_protocol_stack_bytes_low)))

#define VAP_DATA_MISC_MIB_rx_protocol_stack_bytes_low_clear_direct(dword)	((dword) &= (~(M_VAP_DATA_MISC_MIB_rx_protocol_stack_bytes_low)))

#define O_VAP_DATA_MISC_MIB_rx_protocol_stack_bytes_high 11
#define B_VAP_DATA_MISC_MIB_rx_protocol_stack_bytes_high 0
#define W_VAP_DATA_MISC_MIB_rx_protocol_stack_bytes_high 32
#define M_VAP_DATA_MISC_MIB_rx_protocol_stack_bytes_high 0xffffffff

#define VAP_DATA_MISC_MIB_rx_protocol_stack_bytes_high_get_indirect(base, offset)	((((*(base + O_VAP_DATA_MISC_MIB_rx_protocol_stack_bytes_high + offset)) & M_VAP_DATA_MISC_MIB_rx_protocol_stack_bytes_high) >> B_VAP_DATA_MISC_MIB_rx_protocol_stack_bytes_high))

#define VAP_DATA_MISC_MIB_rx_protocol_stack_bytes_high_get_direct(dword)	((((dword) & M_VAP_DATA_MISC_MIB_rx_protocol_stack_bytes_high) >> B_VAP_DATA_MISC_MIB_rx_protocol_stack_bytes_high))

#define VAP_DATA_MISC_MIB_rx_protocol_stack_bytes_high_set_indirect(base, offset, val)    \
	do {                                                              \
		(*(base + O_VAP_DATA_MISC_MIB_rx_protocol_stack_bytes_high + offset)) &= (~(M_VAP_DATA_MISC_MIB_rx_protocol_stack_bytes_high));    \
		(*(base + O_VAP_DATA_MISC_MIB_rx_protocol_stack_bytes_high + offset)) |= ((val << B_VAP_DATA_MISC_MIB_rx_protocol_stack_bytes_high) & M_VAP_DATA_MISC_MIB_rx_protocol_stack_bytes_high);    \
	} while (0)

#define VAP_DATA_MISC_MIB_rx_protocol_stack_bytes_high_set_direct(dword, val)    \
	do {                                                               \
		(dword) &= (~(M_VAP_DATA_MISC_MIB_rx_protocol_stack_bytes_high));    \
		(dword) |= ((val << B_VAP_DATA_MISC_MIB_rx_protocol_stack_bytes_high) & M_VAP_DATA_MISC_MIB_rx_protocol_stack_bytes_high);    \
	} while (0)

#define VAP_DATA_MISC_MIB_rx_protocol_stack_bytes_high_clear_indirect(base, offset)	((*(base + O_VAP_DATA_MISC_MIB_rx_protocol_stack_bytes_high + offset)) &= (~(M_VAP_DATA_MISC_MIB_rx_protocol_stack_bytes_high)))

#define VAP_DATA_MISC_MIB_rx_protocol_stack_bytes_high_clear_direct(dword)	((dword) &= (~(M_VAP_DATA_MISC_MIB_rx_protocol_stack_bytes_high)))

#define O_VAP_DATA_MISC_MIB_rx_forward_packets_low 12
#define B_VAP_DATA_MISC_MIB_rx_forward_packets_low 0
#define W_VAP_DATA_MISC_MIB_rx_forward_packets_low 32
#define M_VAP_DATA_MISC_MIB_rx_forward_packets_low 0xffffffff

#define VAP_DATA_MISC_MIB_rx_forward_packets_low_get_indirect(base, offset)	((((*(base + O_VAP_DATA_MISC_MIB_rx_forward_packets_low + offset)) & M_VAP_DATA_MISC_MIB_rx_forward_packets_low) >> B_VAP_DATA_MISC_MIB_rx_forward_packets_low))

#define VAP_DATA_MISC_MIB_rx_forward_packets_low_get_direct(dword)	((((dword) & M_VAP_DATA_MISC_MIB_rx_forward_packets_low) >> B_VAP_DATA_MISC_MIB_rx_forward_packets_low))

#define VAP_DATA_MISC_MIB_rx_forward_packets_low_set_indirect(base, offset, val)    \
	do {                                                              \
		(*(base + O_VAP_DATA_MISC_MIB_rx_forward_packets_low + offset)) &= (~(M_VAP_DATA_MISC_MIB_rx_forward_packets_low));    \
		(*(base + O_VAP_DATA_MISC_MIB_rx_forward_packets_low + offset)) |= ((val << B_VAP_DATA_MISC_MIB_rx_forward_packets_low) & M_VAP_DATA_MISC_MIB_rx_forward_packets_low);    \
	} while (0)

#define VAP_DATA_MISC_MIB_rx_forward_packets_low_set_direct(dword, val)    \
	do {                                                               \
		(dword) &= (~(M_VAP_DATA_MISC_MIB_rx_forward_packets_low));    \
		(dword) |= ((val << B_VAP_DATA_MISC_MIB_rx_forward_packets_low) & M_VAP_DATA_MISC_MIB_rx_forward_packets_low);    \
	} while (0)

#define VAP_DATA_MISC_MIB_rx_forward_packets_low_clear_indirect(base, offset)	((*(base + O_VAP_DATA_MISC_MIB_rx_forward_packets_low + offset)) &= (~(M_VAP_DATA_MISC_MIB_rx_forward_packets_low)))

#define VAP_DATA_MISC_MIB_rx_forward_packets_low_clear_direct(dword)	((dword) &= (~(M_VAP_DATA_MISC_MIB_rx_forward_packets_low)))

#define O_VAP_DATA_MISC_MIB_rx_forward_packets_high 13
#define B_VAP_DATA_MISC_MIB_rx_forward_packets_high 0
#define W_VAP_DATA_MISC_MIB_rx_forward_packets_high 32
#define M_VAP_DATA_MISC_MIB_rx_forward_packets_high 0xffffffff

#define VAP_DATA_MISC_MIB_rx_forward_packets_high_get_indirect(base, offset)	((((*(base + O_VAP_DATA_MISC_MIB_rx_forward_packets_high + offset)) & M_VAP_DATA_MISC_MIB_rx_forward_packets_high) >> B_VAP_DATA_MISC_MIB_rx_forward_packets_high))

#define VAP_DATA_MISC_MIB_rx_forward_packets_high_get_direct(dword)	((((dword) & M_VAP_DATA_MISC_MIB_rx_forward_packets_high) >> B_VAP_DATA_MISC_MIB_rx_forward_packets_high))

#define VAP_DATA_MISC_MIB_rx_forward_packets_high_set_indirect(base, offset, val)    \
	do {                                                              \
		(*(base + O_VAP_DATA_MISC_MIB_rx_forward_packets_high + offset)) &= (~(M_VAP_DATA_MISC_MIB_rx_forward_packets_high));    \
		(*(base + O_VAP_DATA_MISC_MIB_rx_forward_packets_high + offset)) |= ((val << B_VAP_DATA_MISC_MIB_rx_forward_packets_high) & M_VAP_DATA_MISC_MIB_rx_forward_packets_high);    \
	} while (0)

#define VAP_DATA_MISC_MIB_rx_forward_packets_high_set_direct(dword, val)    \
	do {                                                               \
		(dword) &= (~(M_VAP_DATA_MISC_MIB_rx_forward_packets_high));    \
		(dword) |= ((val << B_VAP_DATA_MISC_MIB_rx_forward_packets_high) & M_VAP_DATA_MISC_MIB_rx_forward_packets_high);    \
	} while (0)

#define VAP_DATA_MISC_MIB_rx_forward_packets_high_clear_indirect(base, offset)	((*(base + O_VAP_DATA_MISC_MIB_rx_forward_packets_high + offset)) &= (~(M_VAP_DATA_MISC_MIB_rx_forward_packets_high)))

#define VAP_DATA_MISC_MIB_rx_forward_packets_high_clear_direct(dword)	((dword) &= (~(M_VAP_DATA_MISC_MIB_rx_forward_packets_high)))

#define O_VAP_DATA_MISC_MIB_rx_forward_bytes_low 14
#define B_VAP_DATA_MISC_MIB_rx_forward_bytes_low 0
#define W_VAP_DATA_MISC_MIB_rx_forward_bytes_low 32
#define M_VAP_DATA_MISC_MIB_rx_forward_bytes_low 0xffffffff

#define VAP_DATA_MISC_MIB_rx_forward_bytes_low_get_indirect(base, offset)	((((*(base + O_VAP_DATA_MISC_MIB_rx_forward_bytes_low + offset)) & M_VAP_DATA_MISC_MIB_rx_forward_bytes_low) >> B_VAP_DATA_MISC_MIB_rx_forward_bytes_low))

#define VAP_DATA_MISC_MIB_rx_forward_bytes_low_get_direct(dword)	((((dword) & M_VAP_DATA_MISC_MIB_rx_forward_bytes_low) >> B_VAP_DATA_MISC_MIB_rx_forward_bytes_low))

#define VAP_DATA_MISC_MIB_rx_forward_bytes_low_set_indirect(base, offset, val)    \
	do {                                                              \
		(*(base + O_VAP_DATA_MISC_MIB_rx_forward_bytes_low + offset)) &= (~(M_VAP_DATA_MISC_MIB_rx_forward_bytes_low));    \
		(*(base + O_VAP_DATA_MISC_MIB_rx_forward_bytes_low + offset)) |= ((val << B_VAP_DATA_MISC_MIB_rx_forward_bytes_low) & M_VAP_DATA_MISC_MIB_rx_forward_bytes_low);    \
	} while (0)

#define VAP_DATA_MISC_MIB_rx_forward_bytes_low_set_direct(dword, val)    \
	do {                                                               \
		(dword) &= (~(M_VAP_DATA_MISC_MIB_rx_forward_bytes_low));    \
		(dword) |= ((val << B_VAP_DATA_MISC_MIB_rx_forward_bytes_low) & M_VAP_DATA_MISC_MIB_rx_forward_bytes_low);    \
	} while (0)

#define VAP_DATA_MISC_MIB_rx_forward_bytes_low_clear_indirect(base, offset)	((*(base + O_VAP_DATA_MISC_MIB_rx_forward_bytes_low + offset)) &= (~(M_VAP_DATA_MISC_MIB_rx_forward_bytes_low)))

#define VAP_DATA_MISC_MIB_rx_forward_bytes_low_clear_direct(dword)	((dword) &= (~(M_VAP_DATA_MISC_MIB_rx_forward_bytes_low)))

#define O_VAP_DATA_MISC_MIB_rx_forward_bytes_high 15
#define B_VAP_DATA_MISC_MIB_rx_forward_bytes_high 0
#define W_VAP_DATA_MISC_MIB_rx_forward_bytes_high 32
#define M_VAP_DATA_MISC_MIB_rx_forward_bytes_high 0xffffffff

#define VAP_DATA_MISC_MIB_rx_forward_bytes_high_get_indirect(base, offset)	((((*(base + O_VAP_DATA_MISC_MIB_rx_forward_bytes_high + offset)) & M_VAP_DATA_MISC_MIB_rx_forward_bytes_high) >> B_VAP_DATA_MISC_MIB_rx_forward_bytes_high))

#define VAP_DATA_MISC_MIB_rx_forward_bytes_high_get_direct(dword)	((((dword) & M_VAP_DATA_MISC_MIB_rx_forward_bytes_high) >> B_VAP_DATA_MISC_MIB_rx_forward_bytes_high))

#define VAP_DATA_MISC_MIB_rx_forward_bytes_high_set_indirect(base, offset, val)    \
	do {                                                              \
		(*(base + O_VAP_DATA_MISC_MIB_rx_forward_bytes_high + offset)) &= (~(M_VAP_DATA_MISC_MIB_rx_forward_bytes_high));    \
		(*(base + O_VAP_DATA_MISC_MIB_rx_forward_bytes_high + offset)) |= ((val << B_VAP_DATA_MISC_MIB_rx_forward_bytes_high) & M_VAP_DATA_MISC_MIB_rx_forward_bytes_high);    \
	} while (0)

#define VAP_DATA_MISC_MIB_rx_forward_bytes_high_set_direct(dword, val)    \
	do {                                                               \
		(dword) &= (~(M_VAP_DATA_MISC_MIB_rx_forward_bytes_high));    \
		(dword) |= ((val << B_VAP_DATA_MISC_MIB_rx_forward_bytes_high) & M_VAP_DATA_MISC_MIB_rx_forward_bytes_high);    \
	} while (0)

#define VAP_DATA_MISC_MIB_rx_forward_bytes_high_clear_indirect(base, offset)	((*(base + O_VAP_DATA_MISC_MIB_rx_forward_bytes_high + offset)) &= (~(M_VAP_DATA_MISC_MIB_rx_forward_bytes_high)))

#define VAP_DATA_MISC_MIB_rx_forward_bytes_high_clear_direct(dword)	((dword) &= (~(M_VAP_DATA_MISC_MIB_rx_forward_bytes_high)))

#define O_DLRX_DATA_MIB_rx_success_mpdu 0
#define B_DLRX_DATA_MIB_rx_success_mpdu 0
#define W_DLRX_DATA_MIB_rx_success_mpdu 32
#define M_DLRX_DATA_MIB_rx_success_mpdu 0xffffffff

#define DLRX_DATA_MIB_rx_success_mpdu_get_indirect(base, offset)	((((*(base + O_DLRX_DATA_MIB_rx_success_mpdu + offset)) & M_DLRX_DATA_MIB_rx_success_mpdu) >> B_DLRX_DATA_MIB_rx_success_mpdu))

#define DLRX_DATA_MIB_rx_success_mpdu_get_direct(dword)	((((dword) & M_DLRX_DATA_MIB_rx_success_mpdu) >> B_DLRX_DATA_MIB_rx_success_mpdu))

#define DLRX_DATA_MIB_rx_success_mpdu_set_indirect(base, offset, val)    \
	do {                                                              \
		(*(base + O_DLRX_DATA_MIB_rx_success_mpdu + offset)) &= (~(M_DLRX_DATA_MIB_rx_success_mpdu));    \
		(*(base + O_DLRX_DATA_MIB_rx_success_mpdu + offset)) |= ((val << B_DLRX_DATA_MIB_rx_success_mpdu) & M_DLRX_DATA_MIB_rx_success_mpdu);    \
	} while (0)

#define DLRX_DATA_MIB_rx_success_mpdu_set_direct(dword, val)    \
	do {                                                               \
		(dword) &= (~(M_DLRX_DATA_MIB_rx_success_mpdu));    \
		(dword) |= ((val << B_DLRX_DATA_MIB_rx_success_mpdu) & M_DLRX_DATA_MIB_rx_success_mpdu);    \
	} while (0)

#define DLRX_DATA_MIB_rx_success_mpdu_clear_indirect(base, offset)	((*(base + O_DLRX_DATA_MIB_rx_success_mpdu + offset)) &= (~(M_DLRX_DATA_MIB_rx_success_mpdu)))

#define DLRX_DATA_MIB_rx_success_mpdu_clear_direct(dword)	((dword) &= (~(M_DLRX_DATA_MIB_rx_success_mpdu)))

#define O_DLRX_DATA_MIB_rx_success_msdu 1
#define B_DLRX_DATA_MIB_rx_success_msdu 0
#define W_DLRX_DATA_MIB_rx_success_msdu 32
#define M_DLRX_DATA_MIB_rx_success_msdu 0xffffffff

#define DLRX_DATA_MIB_rx_success_msdu_get_indirect(base, offset)	((((*(base + O_DLRX_DATA_MIB_rx_success_msdu + offset)) & M_DLRX_DATA_MIB_rx_success_msdu) >> B_DLRX_DATA_MIB_rx_success_msdu))

#define DLRX_DATA_MIB_rx_success_msdu_get_direct(dword)	((((dword) & M_DLRX_DATA_MIB_rx_success_msdu) >> B_DLRX_DATA_MIB_rx_success_msdu))

#define DLRX_DATA_MIB_rx_success_msdu_set_indirect(base, offset, val)    \
	do {                                                              \
		(*(base + O_DLRX_DATA_MIB_rx_success_msdu + offset)) &= (~(M_DLRX_DATA_MIB_rx_success_msdu));    \
		(*(base + O_DLRX_DATA_MIB_rx_success_msdu + offset)) |= ((val << B_DLRX_DATA_MIB_rx_success_msdu) & M_DLRX_DATA_MIB_rx_success_msdu);    \
	} while (0)

#define DLRX_DATA_MIB_rx_success_msdu_set_direct(dword, val)    \
	do {                                                               \
		(dword) &= (~(M_DLRX_DATA_MIB_rx_success_msdu));    \
		(dword) |= ((val << B_DLRX_DATA_MIB_rx_success_msdu) & M_DLRX_DATA_MIB_rx_success_msdu);    \
	} while (0)

#define DLRX_DATA_MIB_rx_success_msdu_clear_indirect(base, offset)	((*(base + O_DLRX_DATA_MIB_rx_success_msdu + offset)) &= (~(M_DLRX_DATA_MIB_rx_success_msdu)))

#define DLRX_DATA_MIB_rx_success_msdu_clear_direct(dword)	((dword) &= (~(M_DLRX_DATA_MIB_rx_success_msdu)))

#define O_DLRX_DATA_MIB_rx_error2_mpdu 2
#define B_DLRX_DATA_MIB_rx_error2_mpdu 0
#define W_DLRX_DATA_MIB_rx_error2_mpdu 32
#define M_DLRX_DATA_MIB_rx_error2_mpdu 0xffffffff

#define DLRX_DATA_MIB_rx_error2_mpdu_get_indirect(base, offset)	((((*(base + O_DLRX_DATA_MIB_rx_error2_mpdu + offset)) & M_DLRX_DATA_MIB_rx_error2_mpdu) >> B_DLRX_DATA_MIB_rx_error2_mpdu))

#define DLRX_DATA_MIB_rx_error2_mpdu_get_direct(dword)	((((dword) & M_DLRX_DATA_MIB_rx_error2_mpdu) >> B_DLRX_DATA_MIB_rx_error2_mpdu))

#define DLRX_DATA_MIB_rx_error2_mpdu_set_indirect(base, offset, val)    \
	do {                                                              \
		(*(base + O_DLRX_DATA_MIB_rx_error2_mpdu + offset)) &= (~(M_DLRX_DATA_MIB_rx_error2_mpdu));    \
		(*(base + O_DLRX_DATA_MIB_rx_error2_mpdu + offset)) |= ((val << B_DLRX_DATA_MIB_rx_error2_mpdu) & M_DLRX_DATA_MIB_rx_error2_mpdu);    \
	} while (0)

#define DLRX_DATA_MIB_rx_error2_mpdu_set_direct(dword, val)    \
	do {                                                               \
		(dword) &= (~(M_DLRX_DATA_MIB_rx_error2_mpdu));    \
		(dword) |= ((val << B_DLRX_DATA_MIB_rx_error2_mpdu) & M_DLRX_DATA_MIB_rx_error2_mpdu);    \
	} while (0)

#define DLRX_DATA_MIB_rx_error2_mpdu_clear_indirect(base, offset)	((*(base + O_DLRX_DATA_MIB_rx_error2_mpdu + offset)) &= (~(M_DLRX_DATA_MIB_rx_error2_mpdu)))

#define DLRX_DATA_MIB_rx_error2_mpdu_clear_direct(dword)	((dword) &= (~(M_DLRX_DATA_MIB_rx_error2_mpdu)))

#define O_DLRX_DATA_MIB_rx_error2_msdu 3
#define B_DLRX_DATA_MIB_rx_error2_msdu 0
#define W_DLRX_DATA_MIB_rx_error2_msdu 32
#define M_DLRX_DATA_MIB_rx_error2_msdu 0xffffffff

#define DLRX_DATA_MIB_rx_error2_msdu_get_indirect(base, offset)	((((*(base + O_DLRX_DATA_MIB_rx_error2_msdu + offset)) & M_DLRX_DATA_MIB_rx_error2_msdu) >> B_DLRX_DATA_MIB_rx_error2_msdu))

#define DLRX_DATA_MIB_rx_error2_msdu_get_direct(dword)	((((dword) & M_DLRX_DATA_MIB_rx_error2_msdu) >> B_DLRX_DATA_MIB_rx_error2_msdu))

#define DLRX_DATA_MIB_rx_error2_msdu_set_indirect(base, offset, val)    \
	do {                                                              \
		(*(base + O_DLRX_DATA_MIB_rx_error2_msdu + offset)) &= (~(M_DLRX_DATA_MIB_rx_error2_msdu));    \
		(*(base + O_DLRX_DATA_MIB_rx_error2_msdu + offset)) |= ((val << B_DLRX_DATA_MIB_rx_error2_msdu) & M_DLRX_DATA_MIB_rx_error2_msdu);    \
	} while (0)

#define DLRX_DATA_MIB_rx_error2_msdu_set_direct(dword, val)    \
	do {                                                               \
		(dword) &= (~(M_DLRX_DATA_MIB_rx_error2_msdu));    \
		(dword) |= ((val << B_DLRX_DATA_MIB_rx_error2_msdu) & M_DLRX_DATA_MIB_rx_error2_msdu);    \
	} while (0)

#define DLRX_DATA_MIB_rx_error2_msdu_clear_indirect(base, offset)	((*(base + O_DLRX_DATA_MIB_rx_error2_msdu + offset)) &= (~(M_DLRX_DATA_MIB_rx_error2_msdu)))

#define DLRX_DATA_MIB_rx_error2_msdu_clear_direct(dword)	((dword) &= (~(M_DLRX_DATA_MIB_rx_error2_msdu)))

#define O_DLRX_DATA_MIB_rx_error3_mpdu 4
#define B_DLRX_DATA_MIB_rx_error3_mpdu 0
#define W_DLRX_DATA_MIB_rx_error3_mpdu 32
#define M_DLRX_DATA_MIB_rx_error3_mpdu 0xffffffff

#define DLRX_DATA_MIB_rx_error3_mpdu_get_indirect(base, offset)	((((*(base + O_DLRX_DATA_MIB_rx_error3_mpdu + offset)) & M_DLRX_DATA_MIB_rx_error3_mpdu) >> B_DLRX_DATA_MIB_rx_error3_mpdu))

#define DLRX_DATA_MIB_rx_error3_mpdu_get_direct(dword)	((((dword) & M_DLRX_DATA_MIB_rx_error3_mpdu) >> B_DLRX_DATA_MIB_rx_error3_mpdu))

#define DLRX_DATA_MIB_rx_error3_mpdu_set_indirect(base, offset, val)    \
	do {                                                              \
		(*(base + O_DLRX_DATA_MIB_rx_error3_mpdu + offset)) &= (~(M_DLRX_DATA_MIB_rx_error3_mpdu));    \
		(*(base + O_DLRX_DATA_MIB_rx_error3_mpdu + offset)) |= ((val << B_DLRX_DATA_MIB_rx_error3_mpdu) & M_DLRX_DATA_MIB_rx_error3_mpdu);    \
	} while (0)

#define DLRX_DATA_MIB_rx_error3_mpdu_set_direct(dword, val)    \
	do {                                                               \
		(dword) &= (~(M_DLRX_DATA_MIB_rx_error3_mpdu));    \
		(dword) |= ((val << B_DLRX_DATA_MIB_rx_error3_mpdu) & M_DLRX_DATA_MIB_rx_error3_mpdu);    \
	} while (0)

#define DLRX_DATA_MIB_rx_error3_mpdu_clear_indirect(base, offset)	((*(base + O_DLRX_DATA_MIB_rx_error3_mpdu + offset)) &= (~(M_DLRX_DATA_MIB_rx_error3_mpdu)))

#define DLRX_DATA_MIB_rx_error3_mpdu_clear_direct(dword)	((dword) &= (~(M_DLRX_DATA_MIB_rx_error3_mpdu)))

#define O_DLRX_DATA_MIB_rx_error3_msdu 5
#define B_DLRX_DATA_MIB_rx_error3_msdu 0
#define W_DLRX_DATA_MIB_rx_error3_msdu 32
#define M_DLRX_DATA_MIB_rx_error3_msdu 0xffffffff

#define DLRX_DATA_MIB_rx_error3_msdu_get_indirect(base, offset)	((((*(base + O_DLRX_DATA_MIB_rx_error3_msdu + offset)) & M_DLRX_DATA_MIB_rx_error3_msdu) >> B_DLRX_DATA_MIB_rx_error3_msdu))

#define DLRX_DATA_MIB_rx_error3_msdu_get_direct(dword)	((((dword) & M_DLRX_DATA_MIB_rx_error3_msdu) >> B_DLRX_DATA_MIB_rx_error3_msdu))

#define DLRX_DATA_MIB_rx_error3_msdu_set_indirect(base, offset, val)    \
	do {                                                              \
		(*(base + O_DLRX_DATA_MIB_rx_error3_msdu + offset)) &= (~(M_DLRX_DATA_MIB_rx_error3_msdu));    \
		(*(base + O_DLRX_DATA_MIB_rx_error3_msdu + offset)) |= ((val << B_DLRX_DATA_MIB_rx_error3_msdu) & M_DLRX_DATA_MIB_rx_error3_msdu);    \
	} while (0)

#define DLRX_DATA_MIB_rx_error3_msdu_set_direct(dword, val)    \
	do {                                                               \
		(dword) &= (~(M_DLRX_DATA_MIB_rx_error3_msdu));    \
		(dword) |= ((val << B_DLRX_DATA_MIB_rx_error3_msdu) & M_DLRX_DATA_MIB_rx_error3_msdu);    \
	} while (0)

#define DLRX_DATA_MIB_rx_error3_msdu_clear_indirect(base, offset)	((*(base + O_DLRX_DATA_MIB_rx_error3_msdu + offset)) &= (~(M_DLRX_DATA_MIB_rx_error3_msdu)))

#define DLRX_DATA_MIB_rx_error3_msdu_clear_direct(dword)	((dword) &= (~(M_DLRX_DATA_MIB_rx_error3_msdu)))

#define O_DLRX_DATA_MIB_rx_error4_mpdu 6
#define B_DLRX_DATA_MIB_rx_error4_mpdu 0
#define W_DLRX_DATA_MIB_rx_error4_mpdu 32
#define M_DLRX_DATA_MIB_rx_error4_mpdu 0xffffffff

#define DLRX_DATA_MIB_rx_error4_mpdu_get_indirect(base, offset)	((((*(base + O_DLRX_DATA_MIB_rx_error4_mpdu + offset)) & M_DLRX_DATA_MIB_rx_error4_mpdu) >> B_DLRX_DATA_MIB_rx_error4_mpdu))

#define DLRX_DATA_MIB_rx_error4_mpdu_get_direct(dword)	((((dword) & M_DLRX_DATA_MIB_rx_error4_mpdu) >> B_DLRX_DATA_MIB_rx_error4_mpdu))

#define DLRX_DATA_MIB_rx_error4_mpdu_set_indirect(base, offset, val)    \
	do {                                                              \
		(*(base + O_DLRX_DATA_MIB_rx_error4_mpdu + offset)) &= (~(M_DLRX_DATA_MIB_rx_error4_mpdu));    \
		(*(base + O_DLRX_DATA_MIB_rx_error4_mpdu + offset)) |= ((val << B_DLRX_DATA_MIB_rx_error4_mpdu) & M_DLRX_DATA_MIB_rx_error4_mpdu);    \
	} while (0)

#define DLRX_DATA_MIB_rx_error4_mpdu_set_direct(dword, val)    \
	do {                                                               \
		(dword) &= (~(M_DLRX_DATA_MIB_rx_error4_mpdu));    \
		(dword) |= ((val << B_DLRX_DATA_MIB_rx_error4_mpdu) & M_DLRX_DATA_MIB_rx_error4_mpdu);    \
	} while (0)

#define DLRX_DATA_MIB_rx_error4_mpdu_clear_indirect(base, offset)	((*(base + O_DLRX_DATA_MIB_rx_error4_mpdu + offset)) &= (~(M_DLRX_DATA_MIB_rx_error4_mpdu)))

#define DLRX_DATA_MIB_rx_error4_mpdu_clear_direct(dword)	((dword) &= (~(M_DLRX_DATA_MIB_rx_error4_mpdu)))

#define O_DLRX_DATA_MIB_rx_error4_msdu 7
#define B_DLRX_DATA_MIB_rx_error4_msdu 0
#define W_DLRX_DATA_MIB_rx_error4_msdu 32
#define M_DLRX_DATA_MIB_rx_error4_msdu 0xffffffff

#define DLRX_DATA_MIB_rx_error4_msdu_get_indirect(base, offset)	((((*(base + O_DLRX_DATA_MIB_rx_error4_msdu + offset)) & M_DLRX_DATA_MIB_rx_error4_msdu) >> B_DLRX_DATA_MIB_rx_error4_msdu))

#define DLRX_DATA_MIB_rx_error4_msdu_get_direct(dword)	((((dword) & M_DLRX_DATA_MIB_rx_error4_msdu) >> B_DLRX_DATA_MIB_rx_error4_msdu))

#define DLRX_DATA_MIB_rx_error4_msdu_set_indirect(base, offset, val)    \
	do {                                                              \
		(*(base + O_DLRX_DATA_MIB_rx_error4_msdu + offset)) &= (~(M_DLRX_DATA_MIB_rx_error4_msdu));    \
		(*(base + O_DLRX_DATA_MIB_rx_error4_msdu + offset)) |= ((val << B_DLRX_DATA_MIB_rx_error4_msdu) & M_DLRX_DATA_MIB_rx_error4_msdu);    \
	} while (0)

#define DLRX_DATA_MIB_rx_error4_msdu_set_direct(dword, val)    \
	do {                                                               \
		(dword) &= (~(M_DLRX_DATA_MIB_rx_error4_msdu));    \
		(dword) |= ((val << B_DLRX_DATA_MIB_rx_error4_msdu) & M_DLRX_DATA_MIB_rx_error4_msdu);    \
	} while (0)

#define DLRX_DATA_MIB_rx_error4_msdu_clear_indirect(base, offset)	((*(base + O_DLRX_DATA_MIB_rx_error4_msdu + offset)) &= (~(M_DLRX_DATA_MIB_rx_error4_msdu)))

#define DLRX_DATA_MIB_rx_error4_msdu_clear_direct(dword)	((dword) &= (~(M_DLRX_DATA_MIB_rx_error4_msdu)))

#define O_DLRX_DATA_MIB_rx_error5_mpdu 8
#define B_DLRX_DATA_MIB_rx_error5_mpdu 0
#define W_DLRX_DATA_MIB_rx_error5_mpdu 32
#define M_DLRX_DATA_MIB_rx_error5_mpdu 0xffffffff

#define DLRX_DATA_MIB_rx_error5_mpdu_get_indirect(base, offset)	((((*(base + O_DLRX_DATA_MIB_rx_error5_mpdu + offset)) & M_DLRX_DATA_MIB_rx_error5_mpdu) >> B_DLRX_DATA_MIB_rx_error5_mpdu))

#define DLRX_DATA_MIB_rx_error5_mpdu_get_direct(dword)	((((dword) & M_DLRX_DATA_MIB_rx_error5_mpdu) >> B_DLRX_DATA_MIB_rx_error5_mpdu))

#define DLRX_DATA_MIB_rx_error5_mpdu_set_indirect(base, offset, val)    \
	do {                                                              \
		(*(base + O_DLRX_DATA_MIB_rx_error5_mpdu + offset)) &= (~(M_DLRX_DATA_MIB_rx_error5_mpdu));    \
		(*(base + O_DLRX_DATA_MIB_rx_error5_mpdu + offset)) |= ((val << B_DLRX_DATA_MIB_rx_error5_mpdu) & M_DLRX_DATA_MIB_rx_error5_mpdu);    \
	} while (0)

#define DLRX_DATA_MIB_rx_error5_mpdu_set_direct(dword, val)    \
	do {                                                               \
		(dword) &= (~(M_DLRX_DATA_MIB_rx_error5_mpdu));    \
		(dword) |= ((val << B_DLRX_DATA_MIB_rx_error5_mpdu) & M_DLRX_DATA_MIB_rx_error5_mpdu);    \
	} while (0)

#define DLRX_DATA_MIB_rx_error5_mpdu_clear_indirect(base, offset)	((*(base + O_DLRX_DATA_MIB_rx_error5_mpdu + offset)) &= (~(M_DLRX_DATA_MIB_rx_error5_mpdu)))

#define DLRX_DATA_MIB_rx_error5_mpdu_clear_direct(dword)	((dword) &= (~(M_DLRX_DATA_MIB_rx_error5_mpdu)))

#define O_DLRX_DATA_MIB_rx_error5_msdu 9
#define B_DLRX_DATA_MIB_rx_error5_msdu 0
#define W_DLRX_DATA_MIB_rx_error5_msdu 32
#define M_DLRX_DATA_MIB_rx_error5_msdu 0xffffffff

#define DLRX_DATA_MIB_rx_error5_msdu_get_indirect(base, offset)	((((*(base + O_DLRX_DATA_MIB_rx_error5_msdu + offset)) & M_DLRX_DATA_MIB_rx_error5_msdu) >> B_DLRX_DATA_MIB_rx_error5_msdu))

#define DLRX_DATA_MIB_rx_error5_msdu_get_direct(dword)	((((dword) & M_DLRX_DATA_MIB_rx_error5_msdu) >> B_DLRX_DATA_MIB_rx_error5_msdu))

#define DLRX_DATA_MIB_rx_error5_msdu_set_indirect(base, offset, val)    \
	do {                                                              \
		(*(base + O_DLRX_DATA_MIB_rx_error5_msdu + offset)) &= (~(M_DLRX_DATA_MIB_rx_error5_msdu));    \
		(*(base + O_DLRX_DATA_MIB_rx_error5_msdu + offset)) |= ((val << B_DLRX_DATA_MIB_rx_error5_msdu) & M_DLRX_DATA_MIB_rx_error5_msdu);    \
	} while (0)

#define DLRX_DATA_MIB_rx_error5_msdu_set_direct(dword, val)    \
	do {                                                               \
		(dword) &= (~(M_DLRX_DATA_MIB_rx_error5_msdu));    \
		(dword) |= ((val << B_DLRX_DATA_MIB_rx_error5_msdu) & M_DLRX_DATA_MIB_rx_error5_msdu);    \
	} while (0)

#define DLRX_DATA_MIB_rx_error5_msdu_clear_indirect(base, offset)	((*(base + O_DLRX_DATA_MIB_rx_error5_msdu + offset)) &= (~(M_DLRX_DATA_MIB_rx_error5_msdu)))

#define DLRX_DATA_MIB_rx_error5_msdu_clear_direct(dword)	((dword) &= (~(M_DLRX_DATA_MIB_rx_error5_msdu)))

#define O_DLRX_DATA_MIB_rx_error6_mpdu 10
#define B_DLRX_DATA_MIB_rx_error6_mpdu 0
#define W_DLRX_DATA_MIB_rx_error6_mpdu 32
#define M_DLRX_DATA_MIB_rx_error6_mpdu 0xffffffff

#define DLRX_DATA_MIB_rx_error6_mpdu_get_indirect(base, offset)	((((*(base + O_DLRX_DATA_MIB_rx_error6_mpdu + offset)) & M_DLRX_DATA_MIB_rx_error6_mpdu) >> B_DLRX_DATA_MIB_rx_error6_mpdu))

#define DLRX_DATA_MIB_rx_error6_mpdu_get_direct(dword)	((((dword) & M_DLRX_DATA_MIB_rx_error6_mpdu) >> B_DLRX_DATA_MIB_rx_error6_mpdu))

#define DLRX_DATA_MIB_rx_error6_mpdu_set_indirect(base, offset, val)    \
	do {                                                              \
		(*(base + O_DLRX_DATA_MIB_rx_error6_mpdu + offset)) &= (~(M_DLRX_DATA_MIB_rx_error6_mpdu));    \
		(*(base + O_DLRX_DATA_MIB_rx_error6_mpdu + offset)) |= ((val << B_DLRX_DATA_MIB_rx_error6_mpdu) & M_DLRX_DATA_MIB_rx_error6_mpdu);    \
	} while (0)

#define DLRX_DATA_MIB_rx_error6_mpdu_set_direct(dword, val)    \
	do {                                                               \
		(dword) &= (~(M_DLRX_DATA_MIB_rx_error6_mpdu));    \
		(dword) |= ((val << B_DLRX_DATA_MIB_rx_error6_mpdu) & M_DLRX_DATA_MIB_rx_error6_mpdu);    \
	} while (0)

#define DLRX_DATA_MIB_rx_error6_mpdu_clear_indirect(base, offset)	((*(base + O_DLRX_DATA_MIB_rx_error6_mpdu + offset)) &= (~(M_DLRX_DATA_MIB_rx_error6_mpdu)))

#define DLRX_DATA_MIB_rx_error6_mpdu_clear_direct(dword)	((dword) &= (~(M_DLRX_DATA_MIB_rx_error6_mpdu)))

#define O_DLRX_DATA_MIB_rx_error6_msdu 11
#define B_DLRX_DATA_MIB_rx_error6_msdu 0
#define W_DLRX_DATA_MIB_rx_error6_msdu 32
#define M_DLRX_DATA_MIB_rx_error6_msdu 0xffffffff

#define DLRX_DATA_MIB_rx_error6_msdu_get_indirect(base, offset)	((((*(base + O_DLRX_DATA_MIB_rx_error6_msdu + offset)) & M_DLRX_DATA_MIB_rx_error6_msdu) >> B_DLRX_DATA_MIB_rx_error6_msdu))

#define DLRX_DATA_MIB_rx_error6_msdu_get_direct(dword)	((((dword) & M_DLRX_DATA_MIB_rx_error6_msdu) >> B_DLRX_DATA_MIB_rx_error6_msdu))

#define DLRX_DATA_MIB_rx_error6_msdu_set_indirect(base, offset, val)    \
	do {                                                              \
		(*(base + O_DLRX_DATA_MIB_rx_error6_msdu + offset)) &= (~(M_DLRX_DATA_MIB_rx_error6_msdu));    \
		(*(base + O_DLRX_DATA_MIB_rx_error6_msdu + offset)) |= ((val << B_DLRX_DATA_MIB_rx_error6_msdu) & M_DLRX_DATA_MIB_rx_error6_msdu);    \
	} while (0)

#define DLRX_DATA_MIB_rx_error6_msdu_set_direct(dword, val)    \
	do {                                                               \
		(dword) &= (~(M_DLRX_DATA_MIB_rx_error6_msdu));    \
		(dword) |= ((val << B_DLRX_DATA_MIB_rx_error6_msdu) & M_DLRX_DATA_MIB_rx_error6_msdu);    \
	} while (0)

#define DLRX_DATA_MIB_rx_error6_msdu_clear_indirect(base, offset)	((*(base + O_DLRX_DATA_MIB_rx_error6_msdu + offset)) &= (~(M_DLRX_DATA_MIB_rx_error6_msdu)))

#define DLRX_DATA_MIB_rx_error6_msdu_clear_direct(dword)	((dword) &= (~(M_DLRX_DATA_MIB_rx_error6_msdu)))

#define O_DLRX_DATA_MIB_rx_error7_mpdu 12
#define B_DLRX_DATA_MIB_rx_error7_mpdu 0
#define W_DLRX_DATA_MIB_rx_error7_mpdu 32
#define M_DLRX_DATA_MIB_rx_error7_mpdu 0xffffffff

#define DLRX_DATA_MIB_rx_error7_mpdu_get_indirect(base, offset)	((((*(base + O_DLRX_DATA_MIB_rx_error7_mpdu + offset)) & M_DLRX_DATA_MIB_rx_error7_mpdu) >> B_DLRX_DATA_MIB_rx_error7_mpdu))

#define DLRX_DATA_MIB_rx_error7_mpdu_get_direct(dword)	((((dword) & M_DLRX_DATA_MIB_rx_error7_mpdu) >> B_DLRX_DATA_MIB_rx_error7_mpdu))

#define DLRX_DATA_MIB_rx_error7_mpdu_set_indirect(base, offset, val)    \
	do {                                                              \
		(*(base + O_DLRX_DATA_MIB_rx_error7_mpdu + offset)) &= (~(M_DLRX_DATA_MIB_rx_error7_mpdu));    \
		(*(base + O_DLRX_DATA_MIB_rx_error7_mpdu + offset)) |= ((val << B_DLRX_DATA_MIB_rx_error7_mpdu) & M_DLRX_DATA_MIB_rx_error7_mpdu);    \
	} while (0)

#define DLRX_DATA_MIB_rx_error7_mpdu_set_direct(dword, val)    \
	do {                                                               \
		(dword) &= (~(M_DLRX_DATA_MIB_rx_error7_mpdu));    \
		(dword) |= ((val << B_DLRX_DATA_MIB_rx_error7_mpdu) & M_DLRX_DATA_MIB_rx_error7_mpdu);    \
	} while (0)

#define DLRX_DATA_MIB_rx_error7_mpdu_clear_indirect(base, offset)	((*(base + O_DLRX_DATA_MIB_rx_error7_mpdu + offset)) &= (~(M_DLRX_DATA_MIB_rx_error7_mpdu)))

#define DLRX_DATA_MIB_rx_error7_mpdu_clear_direct(dword)	((dword) &= (~(M_DLRX_DATA_MIB_rx_error7_mpdu)))

#define O_DLRX_DATA_MIB_rx_error7_msdu 13
#define B_DLRX_DATA_MIB_rx_error7_msdu 0
#define W_DLRX_DATA_MIB_rx_error7_msdu 32
#define M_DLRX_DATA_MIB_rx_error7_msdu 0xffffffff

#define DLRX_DATA_MIB_rx_error7_msdu_get_indirect(base, offset)	((((*(base + O_DLRX_DATA_MIB_rx_error7_msdu + offset)) & M_DLRX_DATA_MIB_rx_error7_msdu) >> B_DLRX_DATA_MIB_rx_error7_msdu))

#define DLRX_DATA_MIB_rx_error7_msdu_get_direct(dword)	((((dword) & M_DLRX_DATA_MIB_rx_error7_msdu) >> B_DLRX_DATA_MIB_rx_error7_msdu))

#define DLRX_DATA_MIB_rx_error7_msdu_set_indirect(base, offset, val)    \
	do {                                                              \
		(*(base + O_DLRX_DATA_MIB_rx_error7_msdu + offset)) &= (~(M_DLRX_DATA_MIB_rx_error7_msdu));    \
		(*(base + O_DLRX_DATA_MIB_rx_error7_msdu + offset)) |= ((val << B_DLRX_DATA_MIB_rx_error7_msdu) & M_DLRX_DATA_MIB_rx_error7_msdu);    \
	} while (0)

#define DLRX_DATA_MIB_rx_error7_msdu_set_direct(dword, val)    \
	do {                                                               \
		(dword) &= (~(M_DLRX_DATA_MIB_rx_error7_msdu));    \
		(dword) |= ((val << B_DLRX_DATA_MIB_rx_error7_msdu) & M_DLRX_DATA_MIB_rx_error7_msdu);    \
	} while (0)

#define DLRX_DATA_MIB_rx_error7_msdu_clear_indirect(base, offset)	((*(base + O_DLRX_DATA_MIB_rx_error7_msdu + offset)) &= (~(M_DLRX_DATA_MIB_rx_error7_msdu)))

#define DLRX_DATA_MIB_rx_error7_msdu_clear_direct(dword)	((dword) &= (~(M_DLRX_DATA_MIB_rx_error7_msdu)))

#define O_DLRX_DATA_MIB_rx_error8_mpdu 14
#define B_DLRX_DATA_MIB_rx_error8_mpdu 0
#define W_DLRX_DATA_MIB_rx_error8_mpdu 32
#define M_DLRX_DATA_MIB_rx_error8_mpdu 0xffffffff

#define DLRX_DATA_MIB_rx_error8_mpdu_get_indirect(base, offset)	((((*(base + O_DLRX_DATA_MIB_rx_error8_mpdu + offset)) & M_DLRX_DATA_MIB_rx_error8_mpdu) >> B_DLRX_DATA_MIB_rx_error8_mpdu))

#define DLRX_DATA_MIB_rx_error8_mpdu_get_direct(dword)	((((dword) & M_DLRX_DATA_MIB_rx_error8_mpdu) >> B_DLRX_DATA_MIB_rx_error8_mpdu))

#define DLRX_DATA_MIB_rx_error8_mpdu_set_indirect(base, offset, val)    \
	do {                                                              \
		(*(base + O_DLRX_DATA_MIB_rx_error8_mpdu + offset)) &= (~(M_DLRX_DATA_MIB_rx_error8_mpdu));    \
		(*(base + O_DLRX_DATA_MIB_rx_error8_mpdu + offset)) |= ((val << B_DLRX_DATA_MIB_rx_error8_mpdu) & M_DLRX_DATA_MIB_rx_error8_mpdu);    \
	} while (0)

#define DLRX_DATA_MIB_rx_error8_mpdu_set_direct(dword, val)    \
	do {                                                               \
		(dword) &= (~(M_DLRX_DATA_MIB_rx_error8_mpdu));    \
		(dword) |= ((val << B_DLRX_DATA_MIB_rx_error8_mpdu) & M_DLRX_DATA_MIB_rx_error8_mpdu);    \
	} while (0)

#define DLRX_DATA_MIB_rx_error8_mpdu_clear_indirect(base, offset)	((*(base + O_DLRX_DATA_MIB_rx_error8_mpdu + offset)) &= (~(M_DLRX_DATA_MIB_rx_error8_mpdu)))

#define DLRX_DATA_MIB_rx_error8_mpdu_clear_direct(dword)	((dword) &= (~(M_DLRX_DATA_MIB_rx_error8_mpdu)))

#define O_DLRX_DATA_MIB_rx_error8_msdu 15
#define B_DLRX_DATA_MIB_rx_error8_msdu 0
#define W_DLRX_DATA_MIB_rx_error8_msdu 32
#define M_DLRX_DATA_MIB_rx_error8_msdu 0xffffffff

#define DLRX_DATA_MIB_rx_error8_msdu_get_indirect(base, offset)	((((*(base + O_DLRX_DATA_MIB_rx_error8_msdu + offset)) & M_DLRX_DATA_MIB_rx_error8_msdu) >> B_DLRX_DATA_MIB_rx_error8_msdu))

#define DLRX_DATA_MIB_rx_error8_msdu_get_direct(dword)	((((dword) & M_DLRX_DATA_MIB_rx_error8_msdu) >> B_DLRX_DATA_MIB_rx_error8_msdu))

#define DLRX_DATA_MIB_rx_error8_msdu_set_indirect(base, offset, val)    \
	do {                                                              \
		(*(base + O_DLRX_DATA_MIB_rx_error8_msdu + offset)) &= (~(M_DLRX_DATA_MIB_rx_error8_msdu));    \
		(*(base + O_DLRX_DATA_MIB_rx_error8_msdu + offset)) |= ((val << B_DLRX_DATA_MIB_rx_error8_msdu) & M_DLRX_DATA_MIB_rx_error8_msdu);    \
	} while (0)

#define DLRX_DATA_MIB_rx_error8_msdu_set_direct(dword, val)    \
	do {                                                               \
		(dword) &= (~(M_DLRX_DATA_MIB_rx_error8_msdu));    \
		(dword) |= ((val << B_DLRX_DATA_MIB_rx_error8_msdu) & M_DLRX_DATA_MIB_rx_error8_msdu);    \
	} while (0)

#define DLRX_DATA_MIB_rx_error8_msdu_clear_indirect(base, offset)	((*(base + O_DLRX_DATA_MIB_rx_error8_msdu + offset)) &= (~(M_DLRX_DATA_MIB_rx_error8_msdu)))

#define DLRX_DATA_MIB_rx_error8_msdu_clear_direct(dword)	((dword) &= (~(M_DLRX_DATA_MIB_rx_error8_msdu)))

#define O_DLRX_DATA_MIB_rx_error9_mpdu 16
#define B_DLRX_DATA_MIB_rx_error9_mpdu 0
#define W_DLRX_DATA_MIB_rx_error9_mpdu 32
#define M_DLRX_DATA_MIB_rx_error9_mpdu 0xffffffff

#define DLRX_DATA_MIB_rx_error9_mpdu_get_indirect(base, offset)	((((*(base + O_DLRX_DATA_MIB_rx_error9_mpdu + offset)) & M_DLRX_DATA_MIB_rx_error9_mpdu) >> B_DLRX_DATA_MIB_rx_error9_mpdu))

#define DLRX_DATA_MIB_rx_error9_mpdu_get_direct(dword)	((((dword) & M_DLRX_DATA_MIB_rx_error9_mpdu) >> B_DLRX_DATA_MIB_rx_error9_mpdu))

#define DLRX_DATA_MIB_rx_error9_mpdu_set_indirect(base, offset, val)    \
	do {                                                              \
		(*(base + O_DLRX_DATA_MIB_rx_error9_mpdu + offset)) &= (~(M_DLRX_DATA_MIB_rx_error9_mpdu));    \
		(*(base + O_DLRX_DATA_MIB_rx_error9_mpdu + offset)) |= ((val << B_DLRX_DATA_MIB_rx_error9_mpdu) & M_DLRX_DATA_MIB_rx_error9_mpdu);    \
	} while (0)

#define DLRX_DATA_MIB_rx_error9_mpdu_set_direct(dword, val)    \
	do {                                                               \
		(dword) &= (~(M_DLRX_DATA_MIB_rx_error9_mpdu));    \
		(dword) |= ((val << B_DLRX_DATA_MIB_rx_error9_mpdu) & M_DLRX_DATA_MIB_rx_error9_mpdu);    \
	} while (0)

#define DLRX_DATA_MIB_rx_error9_mpdu_clear_indirect(base, offset)	((*(base + O_DLRX_DATA_MIB_rx_error9_mpdu + offset)) &= (~(M_DLRX_DATA_MIB_rx_error9_mpdu)))

#define DLRX_DATA_MIB_rx_error9_mpdu_clear_direct(dword)	((dword) &= (~(M_DLRX_DATA_MIB_rx_error9_mpdu)))

#define O_DLRX_DATA_MIB_rx_error9_msdu 17
#define B_DLRX_DATA_MIB_rx_error9_msdu 0
#define W_DLRX_DATA_MIB_rx_error9_msdu 32
#define M_DLRX_DATA_MIB_rx_error9_msdu 0xffffffff

#define DLRX_DATA_MIB_rx_error9_msdu_get_indirect(base, offset)	((((*(base + O_DLRX_DATA_MIB_rx_error9_msdu + offset)) & M_DLRX_DATA_MIB_rx_error9_msdu) >> B_DLRX_DATA_MIB_rx_error9_msdu))

#define DLRX_DATA_MIB_rx_error9_msdu_get_direct(dword)	((((dword) & M_DLRX_DATA_MIB_rx_error9_msdu) >> B_DLRX_DATA_MIB_rx_error9_msdu))

#define DLRX_DATA_MIB_rx_error9_msdu_set_indirect(base, offset, val)    \
	do {                                                              \
		(*(base + O_DLRX_DATA_MIB_rx_error9_msdu + offset)) &= (~(M_DLRX_DATA_MIB_rx_error9_msdu));    \
		(*(base + O_DLRX_DATA_MIB_rx_error9_msdu + offset)) |= ((val << B_DLRX_DATA_MIB_rx_error9_msdu) & M_DLRX_DATA_MIB_rx_error9_msdu);    \
	} while (0)

#define DLRX_DATA_MIB_rx_error9_msdu_set_direct(dword, val)    \
	do {                                                               \
		(dword) &= (~(M_DLRX_DATA_MIB_rx_error9_msdu));    \
		(dword) |= ((val << B_DLRX_DATA_MIB_rx_error9_msdu) & M_DLRX_DATA_MIB_rx_error9_msdu);    \
	} while (0)

#define DLRX_DATA_MIB_rx_error9_msdu_clear_indirect(base, offset)	((*(base + O_DLRX_DATA_MIB_rx_error9_msdu + offset)) &= (~(M_DLRX_DATA_MIB_rx_error9_msdu)))

#define DLRX_DATA_MIB_rx_error9_msdu_clear_direct(dword)	((dword) &= (~(M_DLRX_DATA_MIB_rx_error9_msdu)))

#define O_DLRX_DATA_MIB_rx_errora_mpdu 18
#define B_DLRX_DATA_MIB_rx_errora_mpdu 0
#define W_DLRX_DATA_MIB_rx_errora_mpdu 32
#define M_DLRX_DATA_MIB_rx_errora_mpdu 0xffffffff

#define DLRX_DATA_MIB_rx_errora_mpdu_get_indirect(base, offset)	((((*(base + O_DLRX_DATA_MIB_rx_errora_mpdu + offset)) & M_DLRX_DATA_MIB_rx_errora_mpdu) >> B_DLRX_DATA_MIB_rx_errora_mpdu))

#define DLRX_DATA_MIB_rx_errora_mpdu_get_direct(dword)	((((dword) & M_DLRX_DATA_MIB_rx_errora_mpdu) >> B_DLRX_DATA_MIB_rx_errora_mpdu))

#define DLRX_DATA_MIB_rx_errora_mpdu_set_indirect(base, offset, val)    \
	do {                                                              \
		(*(base + O_DLRX_DATA_MIB_rx_errora_mpdu + offset)) &= (~(M_DLRX_DATA_MIB_rx_errora_mpdu));    \
		(*(base + O_DLRX_DATA_MIB_rx_errora_mpdu + offset)) |= ((val << B_DLRX_DATA_MIB_rx_errora_mpdu) & M_DLRX_DATA_MIB_rx_errora_mpdu);    \
	} while (0)

#define DLRX_DATA_MIB_rx_errora_mpdu_set_direct(dword, val)    \
	do {                                                               \
		(dword) &= (~(M_DLRX_DATA_MIB_rx_errora_mpdu));    \
		(dword) |= ((val << B_DLRX_DATA_MIB_rx_errora_mpdu) & M_DLRX_DATA_MIB_rx_errora_mpdu);    \
	} while (0)

#define DLRX_DATA_MIB_rx_errora_mpdu_clear_indirect(base, offset)	((*(base + O_DLRX_DATA_MIB_rx_errora_mpdu + offset)) &= (~(M_DLRX_DATA_MIB_rx_errora_mpdu)))

#define DLRX_DATA_MIB_rx_errora_mpdu_clear_direct(dword)	((dword) &= (~(M_DLRX_DATA_MIB_rx_errora_mpdu)))

#define O_DLRX_DATA_MIB_rx_errora_msdu 19
#define B_DLRX_DATA_MIB_rx_errora_msdu 0
#define W_DLRX_DATA_MIB_rx_errora_msdu 32
#define M_DLRX_DATA_MIB_rx_errora_msdu 0xffffffff

#define DLRX_DATA_MIB_rx_errora_msdu_get_indirect(base, offset)	((((*(base + O_DLRX_DATA_MIB_rx_errora_msdu + offset)) & M_DLRX_DATA_MIB_rx_errora_msdu) >> B_DLRX_DATA_MIB_rx_errora_msdu))

#define DLRX_DATA_MIB_rx_errora_msdu_get_direct(dword)	((((dword) & M_DLRX_DATA_MIB_rx_errora_msdu) >> B_DLRX_DATA_MIB_rx_errora_msdu))

#define DLRX_DATA_MIB_rx_errora_msdu_set_indirect(base, offset, val)    \
	do {                                                              \
		(*(base + O_DLRX_DATA_MIB_rx_errora_msdu + offset)) &= (~(M_DLRX_DATA_MIB_rx_errora_msdu));    \
		(*(base + O_DLRX_DATA_MIB_rx_errora_msdu + offset)) |= ((val << B_DLRX_DATA_MIB_rx_errora_msdu) & M_DLRX_DATA_MIB_rx_errora_msdu);    \
	} while (0)

#define DLRX_DATA_MIB_rx_errora_msdu_set_direct(dword, val)    \
	do {                                                               \
		(dword) &= (~(M_DLRX_DATA_MIB_rx_errora_msdu));    \
		(dword) |= ((val << B_DLRX_DATA_MIB_rx_errora_msdu) & M_DLRX_DATA_MIB_rx_errora_msdu);    \
	} while (0)

#define DLRX_DATA_MIB_rx_errora_msdu_clear_indirect(base, offset)	((*(base + O_DLRX_DATA_MIB_rx_errora_msdu + offset)) &= (~(M_DLRX_DATA_MIB_rx_errora_msdu)))

#define DLRX_DATA_MIB_rx_errora_msdu_clear_direct(dword)	((dword) &= (~(M_DLRX_DATA_MIB_rx_errora_msdu)))

#define O_DLRX_DATA_MIB_rx_drop_error5 20
#define B_DLRX_DATA_MIB_rx_drop_error5 0
#define W_DLRX_DATA_MIB_rx_drop_error5 32
#define M_DLRX_DATA_MIB_rx_drop_error5 0xffffffff

#define DLRX_DATA_MIB_rx_drop_error5_get_indirect(base, offset)	((((*(base + O_DLRX_DATA_MIB_rx_drop_error5 + offset)) & M_DLRX_DATA_MIB_rx_drop_error5) >> B_DLRX_DATA_MIB_rx_drop_error5))

#define DLRX_DATA_MIB_rx_drop_error5_get_direct(dword)	((((dword) & M_DLRX_DATA_MIB_rx_drop_error5) >> B_DLRX_DATA_MIB_rx_drop_error5))

#define DLRX_DATA_MIB_rx_drop_error5_set_indirect(base, offset, val)    \
	do {                                                              \
		(*(base + O_DLRX_DATA_MIB_rx_drop_error5 + offset)) &= (~(M_DLRX_DATA_MIB_rx_drop_error5));    \
		(*(base + O_DLRX_DATA_MIB_rx_drop_error5 + offset)) |= ((val << B_DLRX_DATA_MIB_rx_drop_error5) & M_DLRX_DATA_MIB_rx_drop_error5);    \
	} while (0)

#define DLRX_DATA_MIB_rx_drop_error5_set_direct(dword, val)    \
	do {                                                               \
		(dword) &= (~(M_DLRX_DATA_MIB_rx_drop_error5));    \
		(dword) |= ((val << B_DLRX_DATA_MIB_rx_drop_error5) & M_DLRX_DATA_MIB_rx_drop_error5);    \
	} while (0)

#define DLRX_DATA_MIB_rx_drop_error5_clear_indirect(base, offset)	((*(base + O_DLRX_DATA_MIB_rx_drop_error5 + offset)) &= (~(M_DLRX_DATA_MIB_rx_drop_error5)))

#define DLRX_DATA_MIB_rx_drop_error5_clear_direct(dword)	((dword) &= (~(M_DLRX_DATA_MIB_rx_drop_error5)))

#define O_DLRX_DATA_MIB_rx_drop_ro_linklist 21
#define B_DLRX_DATA_MIB_rx_drop_ro_linklist 0
#define W_DLRX_DATA_MIB_rx_drop_ro_linklist 32
#define M_DLRX_DATA_MIB_rx_drop_ro_linklist 0xffffffff

#define DLRX_DATA_MIB_rx_drop_ro_linklist_get_indirect(base, offset)	((((*(base + O_DLRX_DATA_MIB_rx_drop_ro_linklist + offset)) & M_DLRX_DATA_MIB_rx_drop_ro_linklist) >> B_DLRX_DATA_MIB_rx_drop_ro_linklist))

#define DLRX_DATA_MIB_rx_drop_ro_linklist_get_direct(dword)	((((dword) & M_DLRX_DATA_MIB_rx_drop_ro_linklist) >> B_DLRX_DATA_MIB_rx_drop_ro_linklist))

#define DLRX_DATA_MIB_rx_drop_ro_linklist_set_indirect(base, offset, val)    \
	do {                                                              \
		(*(base + O_DLRX_DATA_MIB_rx_drop_ro_linklist + offset)) &= (~(M_DLRX_DATA_MIB_rx_drop_ro_linklist));    \
		(*(base + O_DLRX_DATA_MIB_rx_drop_ro_linklist + offset)) |= ((val << B_DLRX_DATA_MIB_rx_drop_ro_linklist) & M_DLRX_DATA_MIB_rx_drop_ro_linklist);    \
	} while (0)

#define DLRX_DATA_MIB_rx_drop_ro_linklist_set_direct(dword, val)    \
	do {                                                               \
		(dword) &= (~(M_DLRX_DATA_MIB_rx_drop_ro_linklist));    \
		(dword) |= ((val << B_DLRX_DATA_MIB_rx_drop_ro_linklist) & M_DLRX_DATA_MIB_rx_drop_ro_linklist);    \
	} while (0)

#define DLRX_DATA_MIB_rx_drop_ro_linklist_clear_indirect(base, offset)	((*(base + O_DLRX_DATA_MIB_rx_drop_ro_linklist + offset)) &= (~(M_DLRX_DATA_MIB_rx_drop_ro_linklist)))

#define DLRX_DATA_MIB_rx_drop_ro_linklist_clear_direct(dword)	((dword) &= (~(M_DLRX_DATA_MIB_rx_drop_ro_linklist)))

#define O_DLRX_DATA_MIB_rx_drop_congestion_packets 22
#define B_DLRX_DATA_MIB_rx_drop_congestion_packets 0
#define W_DLRX_DATA_MIB_rx_drop_congestion_packets 32
#define M_DLRX_DATA_MIB_rx_drop_congestion_packets 0xffffffff

#define DLRX_DATA_MIB_rx_drop_congestion_packets_get_indirect(base, offset)	((((*(base + O_DLRX_DATA_MIB_rx_drop_congestion_packets + offset)) & M_DLRX_DATA_MIB_rx_drop_congestion_packets) >> B_DLRX_DATA_MIB_rx_drop_congestion_packets))

#define DLRX_DATA_MIB_rx_drop_congestion_packets_get_direct(dword)	((((dword) & M_DLRX_DATA_MIB_rx_drop_congestion_packets) >> B_DLRX_DATA_MIB_rx_drop_congestion_packets))

#define DLRX_DATA_MIB_rx_drop_congestion_packets_set_indirect(base, offset, val)    \
	do {                                                              \
		(*(base + O_DLRX_DATA_MIB_rx_drop_congestion_packets + offset)) &= (~(M_DLRX_DATA_MIB_rx_drop_congestion_packets));    \
		(*(base + O_DLRX_DATA_MIB_rx_drop_congestion_packets + offset)) |= ((val << B_DLRX_DATA_MIB_rx_drop_congestion_packets) & M_DLRX_DATA_MIB_rx_drop_congestion_packets);    \
	} while (0)

#define DLRX_DATA_MIB_rx_drop_congestion_packets_set_direct(dword, val)    \
	do {                                                               \
		(dword) &= (~(M_DLRX_DATA_MIB_rx_drop_congestion_packets));    \
		(dword) |= ((val << B_DLRX_DATA_MIB_rx_drop_congestion_packets) & M_DLRX_DATA_MIB_rx_drop_congestion_packets);    \
	} while (0)

#define DLRX_DATA_MIB_rx_drop_congestion_packets_clear_indirect(base, offset)	((*(base + O_DLRX_DATA_MIB_rx_drop_congestion_packets + offset)) &= (~(M_DLRX_DATA_MIB_rx_drop_congestion_packets)))

#define DLRX_DATA_MIB_rx_drop_congestion_packets_clear_direct(dword)	((dword) &= (~(M_DLRX_DATA_MIB_rx_drop_congestion_packets)))

#define O_DLRX_MSG_MIB_total_ce4_cpu_msg 0
#define B_DLRX_MSG_MIB_total_ce4_cpu_msg 0
#define W_DLRX_MSG_MIB_total_ce4_cpu_msg 32
#define M_DLRX_MSG_MIB_total_ce4_cpu_msg 0xffffffff

#define DLRX_MSG_MIB_total_ce4_cpu_msg_get_indirect(base, offset)	((((*(base + O_DLRX_MSG_MIB_total_ce4_cpu_msg + offset)) & M_DLRX_MSG_MIB_total_ce4_cpu_msg) >> B_DLRX_MSG_MIB_total_ce4_cpu_msg))

#define DLRX_MSG_MIB_total_ce4_cpu_msg_get_direct(dword)	((((dword) & M_DLRX_MSG_MIB_total_ce4_cpu_msg) >> B_DLRX_MSG_MIB_total_ce4_cpu_msg))

#define DLRX_MSG_MIB_total_ce4_cpu_msg_set_indirect(base, offset, val)    \
	do {                                                              \
		(*(base + O_DLRX_MSG_MIB_total_ce4_cpu_msg + offset)) &= (~(M_DLRX_MSG_MIB_total_ce4_cpu_msg));    \
		(*(base + O_DLRX_MSG_MIB_total_ce4_cpu_msg + offset)) |= ((val << B_DLRX_MSG_MIB_total_ce4_cpu_msg) & M_DLRX_MSG_MIB_total_ce4_cpu_msg);    \
	} while (0)

#define DLRX_MSG_MIB_total_ce4_cpu_msg_set_direct(dword, val)    \
	do {                                                               \
		(dword) &= (~(M_DLRX_MSG_MIB_total_ce4_cpu_msg));    \
		(dword) |= ((val << B_DLRX_MSG_MIB_total_ce4_cpu_msg) & M_DLRX_MSG_MIB_total_ce4_cpu_msg);    \
	} while (0)

#define DLRX_MSG_MIB_total_ce4_cpu_msg_clear_indirect(base, offset)	((*(base + O_DLRX_MSG_MIB_total_ce4_cpu_msg + offset)) &= (~(M_DLRX_MSG_MIB_total_ce4_cpu_msg)))

#define DLRX_MSG_MIB_total_ce4_cpu_msg_clear_direct(dword)	((dword) &= (~(M_DLRX_MSG_MIB_total_ce4_cpu_msg)))

#define O_DLRX_MSG_MIB_total_ce5_cpu_msg 1
#define B_DLRX_MSG_MIB_total_ce5_cpu_msg 0
#define W_DLRX_MSG_MIB_total_ce5_cpu_msg 32
#define M_DLRX_MSG_MIB_total_ce5_cpu_msg 0xffffffff

#define DLRX_MSG_MIB_total_ce5_cpu_msg_get_indirect(base, offset)	((((*(base + O_DLRX_MSG_MIB_total_ce5_cpu_msg + offset)) & M_DLRX_MSG_MIB_total_ce5_cpu_msg) >> B_DLRX_MSG_MIB_total_ce5_cpu_msg))

#define DLRX_MSG_MIB_total_ce5_cpu_msg_get_direct(dword)	((((dword) & M_DLRX_MSG_MIB_total_ce5_cpu_msg) >> B_DLRX_MSG_MIB_total_ce5_cpu_msg))

#define DLRX_MSG_MIB_total_ce5_cpu_msg_set_indirect(base, offset, val)    \
	do {                                                              \
		(*(base + O_DLRX_MSG_MIB_total_ce5_cpu_msg + offset)) &= (~(M_DLRX_MSG_MIB_total_ce5_cpu_msg));    \
		(*(base + O_DLRX_MSG_MIB_total_ce5_cpu_msg + offset)) |= ((val << B_DLRX_MSG_MIB_total_ce5_cpu_msg) & M_DLRX_MSG_MIB_total_ce5_cpu_msg);    \
	} while (0)

#define DLRX_MSG_MIB_total_ce5_cpu_msg_set_direct(dword, val)    \
	do {                                                               \
		(dword) &= (~(M_DLRX_MSG_MIB_total_ce5_cpu_msg));    \
		(dword) |= ((val << B_DLRX_MSG_MIB_total_ce5_cpu_msg) & M_DLRX_MSG_MIB_total_ce5_cpu_msg);    \
	} while (0)

#define DLRX_MSG_MIB_total_ce5_cpu_msg_clear_indirect(base, offset)	((*(base + O_DLRX_MSG_MIB_total_ce5_cpu_msg + offset)) &= (~(M_DLRX_MSG_MIB_total_ce5_cpu_msg)))

#define DLRX_MSG_MIB_total_ce5_cpu_msg_clear_direct(dword)	((dword) &= (~(M_DLRX_MSG_MIB_total_ce5_cpu_msg)))

#define O_DLRX_MSG_MIB_total_rx_ind_msg 2
#define B_DLRX_MSG_MIB_total_rx_ind_msg 0
#define W_DLRX_MSG_MIB_total_rx_ind_msg 32
#define M_DLRX_MSG_MIB_total_rx_ind_msg 0xffffffff

#define DLRX_MSG_MIB_total_rx_ind_msg_get_indirect(base, offset)	((((*(base + O_DLRX_MSG_MIB_total_rx_ind_msg + offset)) & M_DLRX_MSG_MIB_total_rx_ind_msg) >> B_DLRX_MSG_MIB_total_rx_ind_msg))

#define DLRX_MSG_MIB_total_rx_ind_msg_get_direct(dword)	((((dword) & M_DLRX_MSG_MIB_total_rx_ind_msg) >> B_DLRX_MSG_MIB_total_rx_ind_msg))

#define DLRX_MSG_MIB_total_rx_ind_msg_set_indirect(base, offset, val)    \
	do {                                                              \
		(*(base + O_DLRX_MSG_MIB_total_rx_ind_msg + offset)) &= (~(M_DLRX_MSG_MIB_total_rx_ind_msg));    \
		(*(base + O_DLRX_MSG_MIB_total_rx_ind_msg + offset)) |= ((val << B_DLRX_MSG_MIB_total_rx_ind_msg) & M_DLRX_MSG_MIB_total_rx_ind_msg);    \
	} while (0)

#define DLRX_MSG_MIB_total_rx_ind_msg_set_direct(dword, val)    \
	do {                                                               \
		(dword) &= (~(M_DLRX_MSG_MIB_total_rx_ind_msg));    \
		(dword) |= ((val << B_DLRX_MSG_MIB_total_rx_ind_msg) & M_DLRX_MSG_MIB_total_rx_ind_msg);    \
	} while (0)

#define DLRX_MSG_MIB_total_rx_ind_msg_clear_indirect(base, offset)	((*(base + O_DLRX_MSG_MIB_total_rx_ind_msg + offset)) &= (~(M_DLRX_MSG_MIB_total_rx_ind_msg)))

#define DLRX_MSG_MIB_total_rx_ind_msg_clear_direct(dword)	((dword) &= (~(M_DLRX_MSG_MIB_total_rx_ind_msg)))

#define O_DLRX_MSG_MIB_total_rx_flush_msg 3
#define B_DLRX_MSG_MIB_total_rx_flush_msg 0
#define W_DLRX_MSG_MIB_total_rx_flush_msg 32
#define M_DLRX_MSG_MIB_total_rx_flush_msg 0xffffffff

#define DLRX_MSG_MIB_total_rx_flush_msg_get_indirect(base, offset)	((((*(base + O_DLRX_MSG_MIB_total_rx_flush_msg + offset)) & M_DLRX_MSG_MIB_total_rx_flush_msg) >> B_DLRX_MSG_MIB_total_rx_flush_msg))

#define DLRX_MSG_MIB_total_rx_flush_msg_get_direct(dword)	((((dword) & M_DLRX_MSG_MIB_total_rx_flush_msg) >> B_DLRX_MSG_MIB_total_rx_flush_msg))

#define DLRX_MSG_MIB_total_rx_flush_msg_set_indirect(base, offset, val)    \
	do {                                                              \
		(*(base + O_DLRX_MSG_MIB_total_rx_flush_msg + offset)) &= (~(M_DLRX_MSG_MIB_total_rx_flush_msg));    \
		(*(base + O_DLRX_MSG_MIB_total_rx_flush_msg + offset)) |= ((val << B_DLRX_MSG_MIB_total_rx_flush_msg) & M_DLRX_MSG_MIB_total_rx_flush_msg);    \
	} while (0)

#define DLRX_MSG_MIB_total_rx_flush_msg_set_direct(dword, val)    \
	do {                                                               \
		(dword) &= (~(M_DLRX_MSG_MIB_total_rx_flush_msg));    \
		(dword) |= ((val << B_DLRX_MSG_MIB_total_rx_flush_msg) & M_DLRX_MSG_MIB_total_rx_flush_msg);    \
	} while (0)

#define DLRX_MSG_MIB_total_rx_flush_msg_clear_indirect(base, offset)	((*(base + O_DLRX_MSG_MIB_total_rx_flush_msg + offset)) &= (~(M_DLRX_MSG_MIB_total_rx_flush_msg)))

#define DLRX_MSG_MIB_total_rx_flush_msg_clear_direct(dword)	((dword) &= (~(M_DLRX_MSG_MIB_total_rx_flush_msg)))

#define O_DLRX_MSG_MIB_total_tx_cmp_msg 4
#define B_DLRX_MSG_MIB_total_tx_cmp_msg 0
#define W_DLRX_MSG_MIB_total_tx_cmp_msg 32
#define M_DLRX_MSG_MIB_total_tx_cmp_msg 0xffffffff

#define DLRX_MSG_MIB_total_tx_cmp_msg_get_indirect(base, offset)	((((*(base + O_DLRX_MSG_MIB_total_tx_cmp_msg + offset)) & M_DLRX_MSG_MIB_total_tx_cmp_msg) >> B_DLRX_MSG_MIB_total_tx_cmp_msg))

#define DLRX_MSG_MIB_total_tx_cmp_msg_get_direct(dword)	((((dword) & M_DLRX_MSG_MIB_total_tx_cmp_msg) >> B_DLRX_MSG_MIB_total_tx_cmp_msg))

#define DLRX_MSG_MIB_total_tx_cmp_msg_set_indirect(base, offset, val)    \
	do {                                                              \
		(*(base + O_DLRX_MSG_MIB_total_tx_cmp_msg + offset)) &= (~(M_DLRX_MSG_MIB_total_tx_cmp_msg));    \
		(*(base + O_DLRX_MSG_MIB_total_tx_cmp_msg + offset)) |= ((val << B_DLRX_MSG_MIB_total_tx_cmp_msg) & M_DLRX_MSG_MIB_total_tx_cmp_msg);    \
	} while (0)

#define DLRX_MSG_MIB_total_tx_cmp_msg_set_direct(dword, val)    \
	do {                                                               \
		(dword) &= (~(M_DLRX_MSG_MIB_total_tx_cmp_msg));    \
		(dword) |= ((val << B_DLRX_MSG_MIB_total_tx_cmp_msg) & M_DLRX_MSG_MIB_total_tx_cmp_msg);    \
	} while (0)

#define DLRX_MSG_MIB_total_tx_cmp_msg_clear_indirect(base, offset)	((*(base + O_DLRX_MSG_MIB_total_tx_cmp_msg + offset)) &= (~(M_DLRX_MSG_MIB_total_tx_cmp_msg)))

#define DLRX_MSG_MIB_total_tx_cmp_msg_clear_direct(dword)	((dword) &= (~(M_DLRX_MSG_MIB_total_tx_cmp_msg)))

#define O_DLRX_MSG_MIB_total_rx_ind_wlan_msg 5
#define B_DLRX_MSG_MIB_total_rx_ind_wlan_msg 0
#define W_DLRX_MSG_MIB_total_rx_ind_wlan_msg 32
#define M_DLRX_MSG_MIB_total_rx_ind_wlan_msg 0xffffffff

#define DLRX_MSG_MIB_total_rx_ind_wlan_msg_get_indirect(base, offset)	((((*(base + O_DLRX_MSG_MIB_total_rx_ind_wlan_msg + offset)) & M_DLRX_MSG_MIB_total_rx_ind_wlan_msg) >> B_DLRX_MSG_MIB_total_rx_ind_wlan_msg))

#define DLRX_MSG_MIB_total_rx_ind_wlan_msg_get_direct(dword)	((((dword) & M_DLRX_MSG_MIB_total_rx_ind_wlan_msg) >> B_DLRX_MSG_MIB_total_rx_ind_wlan_msg))

#define DLRX_MSG_MIB_total_rx_ind_wlan_msg_set_indirect(base, offset, val)    \
	do {                                                              \
		(*(base + O_DLRX_MSG_MIB_total_rx_ind_wlan_msg + offset)) &= (~(M_DLRX_MSG_MIB_total_rx_ind_wlan_msg));    \
		(*(base + O_DLRX_MSG_MIB_total_rx_ind_wlan_msg + offset)) |= ((val << B_DLRX_MSG_MIB_total_rx_ind_wlan_msg) & M_DLRX_MSG_MIB_total_rx_ind_wlan_msg);    \
	} while (0)

#define DLRX_MSG_MIB_total_rx_ind_wlan_msg_set_direct(dword, val)    \
	do {                                                               \
		(dword) &= (~(M_DLRX_MSG_MIB_total_rx_ind_wlan_msg));    \
		(dword) |= ((val << B_DLRX_MSG_MIB_total_rx_ind_wlan_msg) & M_DLRX_MSG_MIB_total_rx_ind_wlan_msg);    \
	} while (0)

#define DLRX_MSG_MIB_total_rx_ind_wlan_msg_clear_indirect(base, offset)	((*(base + O_DLRX_MSG_MIB_total_rx_ind_wlan_msg + offset)) &= (~(M_DLRX_MSG_MIB_total_rx_ind_wlan_msg)))

#define DLRX_MSG_MIB_total_rx_ind_wlan_msg_clear_direct(dword)	((dword) &= (~(M_DLRX_MSG_MIB_total_rx_ind_wlan_msg)))

#define O_DLRX_MSG_MIB_total_rx_flush_wlan_msg 6
#define B_DLRX_MSG_MIB_total_rx_flush_wlan_msg 0
#define W_DLRX_MSG_MIB_total_rx_flush_wlan_msg 32
#define M_DLRX_MSG_MIB_total_rx_flush_wlan_msg 0xffffffff

#define DLRX_MSG_MIB_total_rx_flush_wlan_msg_get_indirect(base, offset)	((((*(base + O_DLRX_MSG_MIB_total_rx_flush_wlan_msg + offset)) & M_DLRX_MSG_MIB_total_rx_flush_wlan_msg) >> B_DLRX_MSG_MIB_total_rx_flush_wlan_msg))

#define DLRX_MSG_MIB_total_rx_flush_wlan_msg_get_direct(dword)	((((dword) & M_DLRX_MSG_MIB_total_rx_flush_wlan_msg) >> B_DLRX_MSG_MIB_total_rx_flush_wlan_msg))

#define DLRX_MSG_MIB_total_rx_flush_wlan_msg_set_indirect(base, offset, val)    \
	do {                                                              \
		(*(base + O_DLRX_MSG_MIB_total_rx_flush_wlan_msg + offset)) &= (~(M_DLRX_MSG_MIB_total_rx_flush_wlan_msg));    \
		(*(base + O_DLRX_MSG_MIB_total_rx_flush_wlan_msg + offset)) |= ((val << B_DLRX_MSG_MIB_total_rx_flush_wlan_msg) & M_DLRX_MSG_MIB_total_rx_flush_wlan_msg);    \
	} while (0)

#define DLRX_MSG_MIB_total_rx_flush_wlan_msg_set_direct(dword, val)    \
	do {                                                               \
		(dword) &= (~(M_DLRX_MSG_MIB_total_rx_flush_wlan_msg));    \
		(dword) |= ((val << B_DLRX_MSG_MIB_total_rx_flush_wlan_msg) & M_DLRX_MSG_MIB_total_rx_flush_wlan_msg);    \
	} while (0)

#define DLRX_MSG_MIB_total_rx_flush_wlan_msg_clear_indirect(base, offset)	((*(base + O_DLRX_MSG_MIB_total_rx_flush_wlan_msg + offset)) &= (~(M_DLRX_MSG_MIB_total_rx_flush_wlan_msg)))

#define DLRX_MSG_MIB_total_rx_flush_wlan_msg_clear_direct(dword)	((dword) &= (~(M_DLRX_MSG_MIB_total_rx_flush_wlan_msg)))

#define O_DLRX_MSG_MIB_total_rx_frag_ind_msg 7
#define B_DLRX_MSG_MIB_total_rx_frag_ind_msg 0
#define W_DLRX_MSG_MIB_total_rx_frag_ind_msg 32
#define M_DLRX_MSG_MIB_total_rx_frag_ind_msg 0xffffffff

#define DLRX_MSG_MIB_total_rx_frag_ind_msg_get_indirect(base, offset)	((((*(base + O_DLRX_MSG_MIB_total_rx_frag_ind_msg + offset)) & M_DLRX_MSG_MIB_total_rx_frag_ind_msg) >> B_DLRX_MSG_MIB_total_rx_frag_ind_msg))

#define DLRX_MSG_MIB_total_rx_frag_ind_msg_get_direct(dword)	((((dword) & M_DLRX_MSG_MIB_total_rx_frag_ind_msg) >> B_DLRX_MSG_MIB_total_rx_frag_ind_msg))

#define DLRX_MSG_MIB_total_rx_frag_ind_msg_set_indirect(base, offset, val)    \
	do {                                                              \
		(*(base + O_DLRX_MSG_MIB_total_rx_frag_ind_msg + offset)) &= (~(M_DLRX_MSG_MIB_total_rx_frag_ind_msg));    \
		(*(base + O_DLRX_MSG_MIB_total_rx_frag_ind_msg + offset)) |= ((val << B_DLRX_MSG_MIB_total_rx_frag_ind_msg) & M_DLRX_MSG_MIB_total_rx_frag_ind_msg);    \
	} while (0)

#define DLRX_MSG_MIB_total_rx_frag_ind_msg_set_direct(dword, val)    \
	do {                                                               \
		(dword) &= (~(M_DLRX_MSG_MIB_total_rx_frag_ind_msg));    \
		(dword) |= ((val << B_DLRX_MSG_MIB_total_rx_frag_ind_msg) & M_DLRX_MSG_MIB_total_rx_frag_ind_msg);    \
	} while (0)

#define DLRX_MSG_MIB_total_rx_frag_ind_msg_clear_indirect(base, offset)	((*(base + O_DLRX_MSG_MIB_total_rx_frag_ind_msg + offset)) &= (~(M_DLRX_MSG_MIB_total_rx_frag_ind_msg)))

#define DLRX_MSG_MIB_total_rx_frag_ind_msg_clear_direct(dword)	((dword) &= (~(M_DLRX_MSG_MIB_total_rx_frag_ind_msg)))

#define O_DLRX_MSG_MIB_total_rx_invalid_tid_msg 8
#define B_DLRX_MSG_MIB_total_rx_invalid_tid_msg 0
#define W_DLRX_MSG_MIB_total_rx_invalid_tid_msg 32
#define M_DLRX_MSG_MIB_total_rx_invalid_tid_msg 0xffffffff

#define DLRX_MSG_MIB_total_rx_invalid_tid_msg_get_indirect(base, offset)	((((*(base + O_DLRX_MSG_MIB_total_rx_invalid_tid_msg + offset)) & M_DLRX_MSG_MIB_total_rx_invalid_tid_msg) >> B_DLRX_MSG_MIB_total_rx_invalid_tid_msg))

#define DLRX_MSG_MIB_total_rx_invalid_tid_msg_get_direct(dword)	((((dword) & M_DLRX_MSG_MIB_total_rx_invalid_tid_msg) >> B_DLRX_MSG_MIB_total_rx_invalid_tid_msg))

#define DLRX_MSG_MIB_total_rx_invalid_tid_msg_set_indirect(base, offset, val)    \
	do {                                                              \
		(*(base + O_DLRX_MSG_MIB_total_rx_invalid_tid_msg + offset)) &= (~(M_DLRX_MSG_MIB_total_rx_invalid_tid_msg));    \
		(*(base + O_DLRX_MSG_MIB_total_rx_invalid_tid_msg + offset)) |= ((val << B_DLRX_MSG_MIB_total_rx_invalid_tid_msg) & M_DLRX_MSG_MIB_total_rx_invalid_tid_msg);    \
	} while (0)

#define DLRX_MSG_MIB_total_rx_invalid_tid_msg_set_direct(dword, val)    \
	do {                                                               \
		(dword) &= (~(M_DLRX_MSG_MIB_total_rx_invalid_tid_msg));    \
		(dword) |= ((val << B_DLRX_MSG_MIB_total_rx_invalid_tid_msg) & M_DLRX_MSG_MIB_total_rx_invalid_tid_msg);    \
	} while (0)

#define DLRX_MSG_MIB_total_rx_invalid_tid_msg_clear_indirect(base, offset)	((*(base + O_DLRX_MSG_MIB_total_rx_invalid_tid_msg + offset)) &= (~(M_DLRX_MSG_MIB_total_rx_invalid_tid_msg)))

#define DLRX_MSG_MIB_total_rx_invalid_tid_msg_clear_direct(dword)	((dword) &= (~(M_DLRX_MSG_MIB_total_rx_invalid_tid_msg)))

#define O_DLRX_MISC_MIB_total_chained_mpdu 0
#define B_DLRX_MISC_MIB_total_chained_mpdu 0
#define W_DLRX_MISC_MIB_total_chained_mpdu 32
#define M_DLRX_MISC_MIB_total_chained_mpdu 0xffffffff

#define DLRX_MISC_MIB_total_chained_mpdu_get_indirect(base, offset)	((((*(base + O_DLRX_MISC_MIB_total_chained_mpdu + offset)) & M_DLRX_MISC_MIB_total_chained_mpdu) >> B_DLRX_MISC_MIB_total_chained_mpdu))

#define DLRX_MISC_MIB_total_chained_mpdu_get_direct(dword)	((((dword) & M_DLRX_MISC_MIB_total_chained_mpdu) >> B_DLRX_MISC_MIB_total_chained_mpdu))

#define DLRX_MISC_MIB_total_chained_mpdu_set_indirect(base, offset, val)    \
	do {                                                              \
		(*(base + O_DLRX_MISC_MIB_total_chained_mpdu + offset)) &= (~(M_DLRX_MISC_MIB_total_chained_mpdu));    \
		(*(base + O_DLRX_MISC_MIB_total_chained_mpdu + offset)) |= ((val << B_DLRX_MISC_MIB_total_chained_mpdu) & M_DLRX_MISC_MIB_total_chained_mpdu);    \
	} while (0)

#define DLRX_MISC_MIB_total_chained_mpdu_set_direct(dword, val)    \
	do {                                                               \
		(dword) &= (~(M_DLRX_MISC_MIB_total_chained_mpdu));    \
		(dword) |= ((val << B_DLRX_MISC_MIB_total_chained_mpdu) & M_DLRX_MISC_MIB_total_chained_mpdu);    \
	} while (0)

#define DLRX_MISC_MIB_total_chained_mpdu_clear_indirect(base, offset)	((*(base + O_DLRX_MISC_MIB_total_chained_mpdu + offset)) &= (~(M_DLRX_MISC_MIB_total_chained_mpdu)))

#define DLRX_MISC_MIB_total_chained_mpdu_clear_direct(dword)	((dword) &= (~(M_DLRX_MISC_MIB_total_chained_mpdu)))

#define O_DLRX_MISC_MIB_total_chained_msdu 1
#define B_DLRX_MISC_MIB_total_chained_msdu 0
#define W_DLRX_MISC_MIB_total_chained_msdu 32
#define M_DLRX_MISC_MIB_total_chained_msdu 0xffffffff

#define DLRX_MISC_MIB_total_chained_msdu_get_indirect(base, offset)	((((*(base + O_DLRX_MISC_MIB_total_chained_msdu + offset)) & M_DLRX_MISC_MIB_total_chained_msdu) >> B_DLRX_MISC_MIB_total_chained_msdu))

#define DLRX_MISC_MIB_total_chained_msdu_get_direct(dword)	((((dword) & M_DLRX_MISC_MIB_total_chained_msdu) >> B_DLRX_MISC_MIB_total_chained_msdu))

#define DLRX_MISC_MIB_total_chained_msdu_set_indirect(base, offset, val)    \
	do {                                                              \
		(*(base + O_DLRX_MISC_MIB_total_chained_msdu + offset)) &= (~(M_DLRX_MISC_MIB_total_chained_msdu));    \
		(*(base + O_DLRX_MISC_MIB_total_chained_msdu + offset)) |= ((val << B_DLRX_MISC_MIB_total_chained_msdu) & M_DLRX_MISC_MIB_total_chained_msdu);    \
	} while (0)

#define DLRX_MISC_MIB_total_chained_msdu_set_direct(dword, val)    \
	do {                                                               \
		(dword) &= (~(M_DLRX_MISC_MIB_total_chained_msdu));    \
		(dword) |= ((val << B_DLRX_MISC_MIB_total_chained_msdu) & M_DLRX_MISC_MIB_total_chained_msdu);    \
	} while (0)

#define DLRX_MISC_MIB_total_chained_msdu_clear_indirect(base, offset)	((*(base + O_DLRX_MISC_MIB_total_chained_msdu + offset)) &= (~(M_DLRX_MISC_MIB_total_chained_msdu)))

#define DLRX_MISC_MIB_total_chained_msdu_clear_direct(dword)	((dword) &= (~(M_DLRX_MISC_MIB_total_chained_msdu)))

#define O_DLRX_CFG_PEER_ID_TO_PEER_MAP_peer0 0
#define B_DLRX_CFG_PEER_ID_TO_PEER_MAP_peer0 0
#define W_DLRX_CFG_PEER_ID_TO_PEER_MAP_peer0 7
#define M_DLRX_CFG_PEER_ID_TO_PEER_MAP_peer0 0x0000007f

#define DLRX_CFG_PEER_ID_TO_PEER_MAP_peer0_get_indirect(base, offset)	((((*(base + O_DLRX_CFG_PEER_ID_TO_PEER_MAP_peer0 + offset)) & M_DLRX_CFG_PEER_ID_TO_PEER_MAP_peer0) >> B_DLRX_CFG_PEER_ID_TO_PEER_MAP_peer0))

#define DLRX_CFG_PEER_ID_TO_PEER_MAP_peer0_get_direct(dword)	((((dword) & M_DLRX_CFG_PEER_ID_TO_PEER_MAP_peer0) >> B_DLRX_CFG_PEER_ID_TO_PEER_MAP_peer0))

#define DLRX_CFG_PEER_ID_TO_PEER_MAP_peer0_set_indirect(base, offset, val) \
	do {                                                              \
		(*(base + O_DLRX_CFG_PEER_ID_TO_PEER_MAP_peer0 + offset)) &= (~(M_DLRX_CFG_PEER_ID_TO_PEER_MAP_peer0));    \
		(*(base + O_DLRX_CFG_PEER_ID_TO_PEER_MAP_peer0 + offset)) |= ((val << B_DLRX_CFG_PEER_ID_TO_PEER_MAP_peer0) & M_DLRX_CFG_PEER_ID_TO_PEER_MAP_peer0);    \
	} while (0)

#define DLRX_CFG_PEER_ID_TO_PEER_MAP_peer0_set_direct(dword, val) \
	do {                                                               \
		(dword) &= (~(M_DLRX_CFG_PEER_ID_TO_PEER_MAP_peer0));    \
		(dword) |= ((val << B_DLRX_CFG_PEER_ID_TO_PEER_MAP_peer0) & M_DLRX_CFG_PEER_ID_TO_PEER_MAP_peer0);    \
	} while (0)

#define DLRX_CFG_PEER_ID_TO_PEER_MAP_peer0_clear_indirect(base, offset)	((*(base + O_DLRX_CFG_PEER_ID_TO_PEER_MAP_peer0 + offset)) &= (~(M_DLRX_CFG_PEER_ID_TO_PEER_MAP_peer0)))

#define DLRX_CFG_PEER_ID_TO_PEER_MAP_peer0_clear_direct(dword)	((dword) &= (~(M_DLRX_CFG_PEER_ID_TO_PEER_MAP_peer0)))

#define O_DLRX_CFG_PEER_ID_TO_PEER_MAP_vld0 0
#define B_DLRX_CFG_PEER_ID_TO_PEER_MAP_vld0 7
#define W_DLRX_CFG_PEER_ID_TO_PEER_MAP_vld0 1
#define M_DLRX_CFG_PEER_ID_TO_PEER_MAP_vld0 0x00000080

#define DLRX_CFG_PEER_ID_TO_PEER_MAP_vld0_get_indirect(base, offset)	((((*(base + O_DLRX_CFG_PEER_ID_TO_PEER_MAP_vld0 + offset)) & M_DLRX_CFG_PEER_ID_TO_PEER_MAP_vld0) >> B_DLRX_CFG_PEER_ID_TO_PEER_MAP_vld0))

#define DLRX_CFG_PEER_ID_TO_PEER_MAP_vld0_get_direct(dword)	((((dword) & M_DLRX_CFG_PEER_ID_TO_PEER_MAP_vld0) >> B_DLRX_CFG_PEER_ID_TO_PEER_MAP_vld0))

#define DLRX_CFG_PEER_ID_TO_PEER_MAP_vld0_set_indirect(base, offset, val) \
	do {                                                              \
		(*(base + O_DLRX_CFG_PEER_ID_TO_PEER_MAP_vld0 + offset)) &= (~(M_DLRX_CFG_PEER_ID_TO_PEER_MAP_vld0));    \
		(*(base + O_DLRX_CFG_PEER_ID_TO_PEER_MAP_vld0 + offset)) |= ((val << B_DLRX_CFG_PEER_ID_TO_PEER_MAP_vld0) & M_DLRX_CFG_PEER_ID_TO_PEER_MAP_vld0);    \
	} while (0)

#define DLRX_CFG_PEER_ID_TO_PEER_MAP_vld0_set_direct(dword, val) \
	do {                                                               \
		(dword) &= (~(M_DLRX_CFG_PEER_ID_TO_PEER_MAP_vld0));    \
		(dword) |= ((val << B_DLRX_CFG_PEER_ID_TO_PEER_MAP_vld0) & M_DLRX_CFG_PEER_ID_TO_PEER_MAP_vld0);    \
	} while (0)

#define DLRX_CFG_PEER_ID_TO_PEER_MAP_vld0_clear_indirect(base, offset)	((*(base + O_DLRX_CFG_PEER_ID_TO_PEER_MAP_vld0 + offset)) &= (~(M_DLRX_CFG_PEER_ID_TO_PEER_MAP_vld0)))

#define DLRX_CFG_PEER_ID_TO_PEER_MAP_vld0_clear_direct(dword)	((dword) &= (~(M_DLRX_CFG_PEER_ID_TO_PEER_MAP_vld0)))

#define O_DLRX_CFG_PEER_ID_TO_PEER_MAP_peer1 0
#define B_DLRX_CFG_PEER_ID_TO_PEER_MAP_peer1 8
#define W_DLRX_CFG_PEER_ID_TO_PEER_MAP_peer1 7
#define M_DLRX_CFG_PEER_ID_TO_PEER_MAP_peer1 0x00007f00

#define DLRX_CFG_PEER_ID_TO_PEER_MAP_peer1_get_indirect(base, offset)	((((*(base + O_DLRX_CFG_PEER_ID_TO_PEER_MAP_peer1 + offset)) & M_DLRX_CFG_PEER_ID_TO_PEER_MAP_peer1) >> B_DLRX_CFG_PEER_ID_TO_PEER_MAP_peer1))

#define DLRX_CFG_PEER_ID_TO_PEER_MAP_peer1_get_direct(dword)	((((dword) & M_DLRX_CFG_PEER_ID_TO_PEER_MAP_peer1) >> B_DLRX_CFG_PEER_ID_TO_PEER_MAP_peer1))

#define DLRX_CFG_PEER_ID_TO_PEER_MAP_peer1_set_indirect(base, offset, val) \
	do {                                                              \
		(*(base + O_DLRX_CFG_PEER_ID_TO_PEER_MAP_peer1 + offset)) &= (~(M_DLRX_CFG_PEER_ID_TO_PEER_MAP_peer1));    \
		(*(base + O_DLRX_CFG_PEER_ID_TO_PEER_MAP_peer1 + offset)) |= ((val << B_DLRX_CFG_PEER_ID_TO_PEER_MAP_peer1) & M_DLRX_CFG_PEER_ID_TO_PEER_MAP_peer1);    \
	} while (0)

#define DLRX_CFG_PEER_ID_TO_PEER_MAP_peer1_set_direct(dword, val) \
	do {                                                               \
		(dword) &= (~(M_DLRX_CFG_PEER_ID_TO_PEER_MAP_peer1));    \
		(dword) |= ((val << B_DLRX_CFG_PEER_ID_TO_PEER_MAP_peer1) & M_DLRX_CFG_PEER_ID_TO_PEER_MAP_peer1);    \
	} while (0)

#define DLRX_CFG_PEER_ID_TO_PEER_MAP_peer1_clear_indirect(base, offset)	((*(base + O_DLRX_CFG_PEER_ID_TO_PEER_MAP_peer1 + offset)) &= (~(M_DLRX_CFG_PEER_ID_TO_PEER_MAP_peer1)))

#define DLRX_CFG_PEER_ID_TO_PEER_MAP_peer1_clear_direct(dword)	((dword) &= (~(M_DLRX_CFG_PEER_ID_TO_PEER_MAP_peer1)))

#define O_DLRX_CFG_PEER_ID_TO_PEER_MAP_vld1 0
#define B_DLRX_CFG_PEER_ID_TO_PEER_MAP_vld1 15
#define W_DLRX_CFG_PEER_ID_TO_PEER_MAP_vld1 1
#define M_DLRX_CFG_PEER_ID_TO_PEER_MAP_vld1 0x00008000

#define DLRX_CFG_PEER_ID_TO_PEER_MAP_vld1_get_indirect(base, offset)	((((*(base + O_DLRX_CFG_PEER_ID_TO_PEER_MAP_vld1 + offset)) & M_DLRX_CFG_PEER_ID_TO_PEER_MAP_vld1) >> B_DLRX_CFG_PEER_ID_TO_PEER_MAP_vld1))

#define DLRX_CFG_PEER_ID_TO_PEER_MAP_vld1_get_direct(dword)	((((dword) & M_DLRX_CFG_PEER_ID_TO_PEER_MAP_vld1) >> B_DLRX_CFG_PEER_ID_TO_PEER_MAP_vld1))

#define DLRX_CFG_PEER_ID_TO_PEER_MAP_vld1_set_indirect(base, offset, val) \
	do {                                                              \
		(*(base + O_DLRX_CFG_PEER_ID_TO_PEER_MAP_vld1 + offset)) &= (~(M_DLRX_CFG_PEER_ID_TO_PEER_MAP_vld1));    \
		(*(base + O_DLRX_CFG_PEER_ID_TO_PEER_MAP_vld1 + offset)) |= ((val << B_DLRX_CFG_PEER_ID_TO_PEER_MAP_vld1) & M_DLRX_CFG_PEER_ID_TO_PEER_MAP_vld1);    \
	} while (0)

#define DLRX_CFG_PEER_ID_TO_PEER_MAP_vld1_set_direct(dword, val) \
	do {                                                               \
		(dword) &= (~(M_DLRX_CFG_PEER_ID_TO_PEER_MAP_vld1));    \
		(dword) |= ((val << B_DLRX_CFG_PEER_ID_TO_PEER_MAP_vld1) & M_DLRX_CFG_PEER_ID_TO_PEER_MAP_vld1);    \
	} while (0)

#define DLRX_CFG_PEER_ID_TO_PEER_MAP_vld1_clear_indirect(base, offset)	((*(base + O_DLRX_CFG_PEER_ID_TO_PEER_MAP_vld1 + offset)) &= (~(M_DLRX_CFG_PEER_ID_TO_PEER_MAP_vld1)))

#define DLRX_CFG_PEER_ID_TO_PEER_MAP_vld1_clear_direct(dword)	((dword) &= (~(M_DLRX_CFG_PEER_ID_TO_PEER_MAP_vld1)))

#define O_DLRX_CFG_PEER_ID_TO_PEER_MAP_peer2 0
#define B_DLRX_CFG_PEER_ID_TO_PEER_MAP_peer2 16
#define W_DLRX_CFG_PEER_ID_TO_PEER_MAP_peer2 7
#define M_DLRX_CFG_PEER_ID_TO_PEER_MAP_peer2 0x007f0000

#define DLRX_CFG_PEER_ID_TO_PEER_MAP_peer2_get_indirect(base, offset)	((((*(base + O_DLRX_CFG_PEER_ID_TO_PEER_MAP_peer2 + offset)) & M_DLRX_CFG_PEER_ID_TO_PEER_MAP_peer2) >> B_DLRX_CFG_PEER_ID_TO_PEER_MAP_peer2))

#define DLRX_CFG_PEER_ID_TO_PEER_MAP_peer2_get_direct(dword)	((((dword) & M_DLRX_CFG_PEER_ID_TO_PEER_MAP_peer2) >> B_DLRX_CFG_PEER_ID_TO_PEER_MAP_peer2))

#define DLRX_CFG_PEER_ID_TO_PEER_MAP_peer2_set_indirect(base, offset, val) \
	do {                                                              \
		(*(base + O_DLRX_CFG_PEER_ID_TO_PEER_MAP_peer2 + offset)) &= (~(M_DLRX_CFG_PEER_ID_TO_PEER_MAP_peer2));    \
		(*(base + O_DLRX_CFG_PEER_ID_TO_PEER_MAP_peer2 + offset)) |= ((val << B_DLRX_CFG_PEER_ID_TO_PEER_MAP_peer2) & M_DLRX_CFG_PEER_ID_TO_PEER_MAP_peer2);    \
	} while (0)

#define DLRX_CFG_PEER_ID_TO_PEER_MAP_peer2_set_direct(dword, val) \
	do {                                                               \
		(dword) &= (~(M_DLRX_CFG_PEER_ID_TO_PEER_MAP_peer2));    \
		(dword) |= ((val << B_DLRX_CFG_PEER_ID_TO_PEER_MAP_peer2) & M_DLRX_CFG_PEER_ID_TO_PEER_MAP_peer2);    \
	} while (0)

#define DLRX_CFG_PEER_ID_TO_PEER_MAP_peer2_clear_indirect(base, offset)	((*(base + O_DLRX_CFG_PEER_ID_TO_PEER_MAP_peer2 + offset)) &= (~(M_DLRX_CFG_PEER_ID_TO_PEER_MAP_peer2)))

#define DLRX_CFG_PEER_ID_TO_PEER_MAP_peer2_clear_direct(dword)	((dword) &= (~(M_DLRX_CFG_PEER_ID_TO_PEER_MAP_peer2)))

#define O_DLRX_CFG_PEER_ID_TO_PEER_MAP_vld2 0
#define B_DLRX_CFG_PEER_ID_TO_PEER_MAP_vld2 23
#define W_DLRX_CFG_PEER_ID_TO_PEER_MAP_vld2 1
#define M_DLRX_CFG_PEER_ID_TO_PEER_MAP_vld2 0x00800000

#define DLRX_CFG_PEER_ID_TO_PEER_MAP_vld2_get_indirect(base, offset)	((((*(base + O_DLRX_CFG_PEER_ID_TO_PEER_MAP_vld2 + offset)) & M_DLRX_CFG_PEER_ID_TO_PEER_MAP_vld2) >> B_DLRX_CFG_PEER_ID_TO_PEER_MAP_vld2))

#define DLRX_CFG_PEER_ID_TO_PEER_MAP_vld2_get_direct(dword)	((((dword) & M_DLRX_CFG_PEER_ID_TO_PEER_MAP_vld2) >> B_DLRX_CFG_PEER_ID_TO_PEER_MAP_vld2))

#define DLRX_CFG_PEER_ID_TO_PEER_MAP_vld2_set_indirect(base, offset, val) \
	do {                                                              \
		(*(base + O_DLRX_CFG_PEER_ID_TO_PEER_MAP_vld2 + offset)) &= (~(M_DLRX_CFG_PEER_ID_TO_PEER_MAP_vld2));    \
		(*(base + O_DLRX_CFG_PEER_ID_TO_PEER_MAP_vld2 + offset)) |= ((val << B_DLRX_CFG_PEER_ID_TO_PEER_MAP_vld2) & M_DLRX_CFG_PEER_ID_TO_PEER_MAP_vld2);    \
	} while (0)

#define DLRX_CFG_PEER_ID_TO_PEER_MAP_vld2_set_direct(dword, val) \
	do {                                                               \
		(dword) &= (~(M_DLRX_CFG_PEER_ID_TO_PEER_MAP_vld2));    \
		(dword) |= ((val << B_DLRX_CFG_PEER_ID_TO_PEER_MAP_vld2) & M_DLRX_CFG_PEER_ID_TO_PEER_MAP_vld2);    \
	} while (0)

#define DLRX_CFG_PEER_ID_TO_PEER_MAP_vld2_clear_indirect(base, offset)	((*(base + O_DLRX_CFG_PEER_ID_TO_PEER_MAP_vld2 + offset)) &= (~(M_DLRX_CFG_PEER_ID_TO_PEER_MAP_vld2)))

#define DLRX_CFG_PEER_ID_TO_PEER_MAP_vld2_clear_direct(dword)	((dword) &= (~(M_DLRX_CFG_PEER_ID_TO_PEER_MAP_vld2)))

#define O_DLRX_CFG_PEER_ID_TO_PEER_MAP_peer3 0
#define B_DLRX_CFG_PEER_ID_TO_PEER_MAP_peer3 24
#define W_DLRX_CFG_PEER_ID_TO_PEER_MAP_peer3 7
#define M_DLRX_CFG_PEER_ID_TO_PEER_MAP_peer3 0x7f000000

#define DLRX_CFG_PEER_ID_TO_PEER_MAP_peer3_get_indirect(base, offset)	((((*(base + O_DLRX_CFG_PEER_ID_TO_PEER_MAP_peer3 + offset)) & M_DLRX_CFG_PEER_ID_TO_PEER_MAP_peer3) >> B_DLRX_CFG_PEER_ID_TO_PEER_MAP_peer3))

#define DLRX_CFG_PEER_ID_TO_PEER_MAP_peer3_get_direct(dword)	((((dword) & M_DLRX_CFG_PEER_ID_TO_PEER_MAP_peer3) >> B_DLRX_CFG_PEER_ID_TO_PEER_MAP_peer3))

#define DLRX_CFG_PEER_ID_TO_PEER_MAP_peer3_set_indirect(base, offset, val) \
	do {                                                              \
		(*(base + O_DLRX_CFG_PEER_ID_TO_PEER_MAP_peer3 + offset)) &= (~(M_DLRX_CFG_PEER_ID_TO_PEER_MAP_peer3));    \
		(*(base + O_DLRX_CFG_PEER_ID_TO_PEER_MAP_peer3 + offset)) |= ((val << B_DLRX_CFG_PEER_ID_TO_PEER_MAP_peer3) & M_DLRX_CFG_PEER_ID_TO_PEER_MAP_peer3);    \
	} while (0)

#define DLRX_CFG_PEER_ID_TO_PEER_MAP_peer3_set_direct(dword, val) \
	do {                                                               \
		(dword) &= (~(M_DLRX_CFG_PEER_ID_TO_PEER_MAP_peer3));    \
		(dword) |= ((val << B_DLRX_CFG_PEER_ID_TO_PEER_MAP_peer3) & M_DLRX_CFG_PEER_ID_TO_PEER_MAP_peer3);    \
	} while (0)

#define DLRX_CFG_PEER_ID_TO_PEER_MAP_peer3_clear_indirect(base, offset)	((*(base + O_DLRX_CFG_PEER_ID_TO_PEER_MAP_peer3 + offset)) &= (~(M_DLRX_CFG_PEER_ID_TO_PEER_MAP_peer3)))

#define DLRX_CFG_PEER_ID_TO_PEER_MAP_peer3_clear_direct(dword)	((dword) &= (~(M_DLRX_CFG_PEER_ID_TO_PEER_MAP_peer3)))

#define O_DLRX_CFG_PEER_ID_TO_PEER_MAP_vld3 0
#define B_DLRX_CFG_PEER_ID_TO_PEER_MAP_vld3 31
#define W_DLRX_CFG_PEER_ID_TO_PEER_MAP_vld3 1
#define M_DLRX_CFG_PEER_ID_TO_PEER_MAP_vld3 0x80000000

#define DLRX_CFG_PEER_ID_TO_PEER_MAP_vld3_get_indirect(base, offset)	((((*(base + O_DLRX_CFG_PEER_ID_TO_PEER_MAP_vld3 + offset)) & M_DLRX_CFG_PEER_ID_TO_PEER_MAP_vld3) >> B_DLRX_CFG_PEER_ID_TO_PEER_MAP_vld3))

#define DLRX_CFG_PEER_ID_TO_PEER_MAP_vld3_get_direct(dword)	((((dword) & M_DLRX_CFG_PEER_ID_TO_PEER_MAP_vld3) >> B_DLRX_CFG_PEER_ID_TO_PEER_MAP_vld3))

#define DLRX_CFG_PEER_ID_TO_PEER_MAP_vld3_set_indirect(base, offset, val) \
	do {                                                              \
		(*(base + O_DLRX_CFG_PEER_ID_TO_PEER_MAP_vld3 + offset)) &= (~(M_DLRX_CFG_PEER_ID_TO_PEER_MAP_vld3));    \
		(*(base + O_DLRX_CFG_PEER_ID_TO_PEER_MAP_vld3 + offset)) |= ((val << B_DLRX_CFG_PEER_ID_TO_PEER_MAP_vld3) & M_DLRX_CFG_PEER_ID_TO_PEER_MAP_vld3);    \
	} while (0)

#define DLRX_CFG_PEER_ID_TO_PEER_MAP_vld3_set_direct(dword, val) \
	do {                                                               \
		(dword) &= (~(M_DLRX_CFG_PEER_ID_TO_PEER_MAP_vld3));    \
		(dword) |= ((val << B_DLRX_CFG_PEER_ID_TO_PEER_MAP_vld3) & M_DLRX_CFG_PEER_ID_TO_PEER_MAP_vld3);    \
	} while (0)

#define DLRX_CFG_PEER_ID_TO_PEER_MAP_vld3_clear_indirect(base, offset)	((*(base + O_DLRX_CFG_PEER_ID_TO_PEER_MAP_vld3 + offset)) &= (~(M_DLRX_CFG_PEER_ID_TO_PEER_MAP_vld3)))

#define DLRX_CFG_PEER_ID_TO_PEER_MAP_vld3_clear_direct(dword)	((dword) &= (~(M_DLRX_CFG_PEER_ID_TO_PEER_MAP_vld3)))

#define O_DLRX_CFG_PEER_TO_VAP_PN_vap 0
#define B_DLRX_CFG_PEER_TO_VAP_PN_vap 0
#define W_DLRX_CFG_PEER_TO_VAP_PN_vap 4
#define M_DLRX_CFG_PEER_TO_VAP_PN_vap 0x0000000f

#define DLRX_CFG_PEER_TO_VAP_PN_vap_get_indirect(base, offset)	((((*(base + O_DLRX_CFG_PEER_TO_VAP_PN_vap + offset)) & M_DLRX_CFG_PEER_TO_VAP_PN_vap) >> B_DLRX_CFG_PEER_TO_VAP_PN_vap))

#define DLRX_CFG_PEER_TO_VAP_PN_vap_get_direct(dword)	((((dword) & M_DLRX_CFG_PEER_TO_VAP_PN_vap) >> B_DLRX_CFG_PEER_TO_VAP_PN_vap))

#define DLRX_CFG_PEER_TO_VAP_PN_vap_set_indirect(base, offset, val) \
	do {                                                              \
		(*(base + O_DLRX_CFG_PEER_TO_VAP_PN_vap + offset)) &= (~(M_DLRX_CFG_PEER_TO_VAP_PN_vap));    \
		(*(base + O_DLRX_CFG_PEER_TO_VAP_PN_vap + offset)) |= ((val << B_DLRX_CFG_PEER_TO_VAP_PN_vap) & M_DLRX_CFG_PEER_TO_VAP_PN_vap);    \
	} while (0)

#define DLRX_CFG_PEER_TO_VAP_PN_vap_set_direct(dword, val) \
	do {                                                               \
		(dword) &= (~(M_DLRX_CFG_PEER_TO_VAP_PN_vap));    \
		(dword) |= ((val << B_DLRX_CFG_PEER_TO_VAP_PN_vap) & M_DLRX_CFG_PEER_TO_VAP_PN_vap);    \
	} while (0)

#define DLRX_CFG_PEER_TO_VAP_PN_vap_clear_indirect(base, offset)	((*(base + O_DLRX_CFG_PEER_TO_VAP_PN_vap + offset)) &= (~(M_DLRX_CFG_PEER_TO_VAP_PN_vap)))

#define DLRX_CFG_PEER_TO_VAP_PN_vap_clear_direct(dword)	((dword) &= (~(M_DLRX_CFG_PEER_TO_VAP_PN_vap)))

#define O_DLRX_CFG_PEER_TO_VAP_PN_sec_type 0
#define B_DLRX_CFG_PEER_TO_VAP_PN_sec_type 4
#define W_DLRX_CFG_PEER_TO_VAP_PN_sec_type 2
#define M_DLRX_CFG_PEER_TO_VAP_PN_sec_type 0x00000030

#define DLRX_CFG_PEER_TO_VAP_PN_sec_type_get_indirect(base, offset)	((((*(base + O_DLRX_CFG_PEER_TO_VAP_PN_sec_type + offset)) & M_DLRX_CFG_PEER_TO_VAP_PN_sec_type) >> B_DLRX_CFG_PEER_TO_VAP_PN_sec_type))

#define DLRX_CFG_PEER_TO_VAP_PN_sec_type_get_direct(dword)	((((dword) & M_DLRX_CFG_PEER_TO_VAP_PN_sec_type) >> B_DLRX_CFG_PEER_TO_VAP_PN_sec_type))

#define DLRX_CFG_PEER_TO_VAP_PN_sec_type_set_indirect(base, offset, val) \
	do {                                                              \
		(*(base + O_DLRX_CFG_PEER_TO_VAP_PN_sec_type + offset)) &= (~(M_DLRX_CFG_PEER_TO_VAP_PN_sec_type));    \
		(*(base + O_DLRX_CFG_PEER_TO_VAP_PN_sec_type + offset)) |= ((val << B_DLRX_CFG_PEER_TO_VAP_PN_sec_type) & M_DLRX_CFG_PEER_TO_VAP_PN_sec_type);    \
	} while (0)

#define DLRX_CFG_PEER_TO_VAP_PN_sec_type_set_direct(dword, val) \
	do {                                                               \
		(dword) &= (~(M_DLRX_CFG_PEER_TO_VAP_PN_sec_type));    \
		(dword) |= ((val << B_DLRX_CFG_PEER_TO_VAP_PN_sec_type) & M_DLRX_CFG_PEER_TO_VAP_PN_sec_type);    \
	} while (0)

#define DLRX_CFG_PEER_TO_VAP_PN_sec_type_clear_indirect(base, offset)	((*(base + O_DLRX_CFG_PEER_TO_VAP_PN_sec_type + offset)) &= (~(M_DLRX_CFG_PEER_TO_VAP_PN_sec_type)))

#define DLRX_CFG_PEER_TO_VAP_PN_sec_type_clear_direct(dword)	((dword) &= (~(M_DLRX_CFG_PEER_TO_VAP_PN_sec_type)))

#define O_DLRX_CFG_PEER_TO_VAP_PN_acc_dis 0
#define B_DLRX_CFG_PEER_TO_VAP_PN_acc_dis 6
#define W_DLRX_CFG_PEER_TO_VAP_PN_acc_dis 1
#define M_DLRX_CFG_PEER_TO_VAP_PN_acc_dis 0x00000040

#define DLRX_CFG_PEER_TO_VAP_PN_acc_dis_get_indirect(base, offset)	((((*(base + O_DLRX_CFG_PEER_TO_VAP_PN_acc_dis + offset)) & M_DLRX_CFG_PEER_TO_VAP_PN_acc_dis) >> B_DLRX_CFG_PEER_TO_VAP_PN_acc_dis))

#define DLRX_CFG_PEER_TO_VAP_PN_acc_dis_get_direct(dword)	((((dword) & M_DLRX_CFG_PEER_TO_VAP_PN_acc_dis) >> B_DLRX_CFG_PEER_TO_VAP_PN_acc_dis))

#define DLRX_CFG_PEER_TO_VAP_PN_acc_dis_set_indirect(base, offset, val) \
	do {                                                              \
		(*(base + O_DLRX_CFG_PEER_TO_VAP_PN_acc_dis + offset)) &= (~(M_DLRX_CFG_PEER_TO_VAP_PN_acc_dis));    \
		(*(base + O_DLRX_CFG_PEER_TO_VAP_PN_acc_dis + offset)) |= ((val << B_DLRX_CFG_PEER_TO_VAP_PN_acc_dis) & M_DLRX_CFG_PEER_TO_VAP_PN_acc_dis);    \
	} while (0)

#define DLRX_CFG_PEER_TO_VAP_PN_acc_dis_set_direct(dword, val) \
	do {                                                               \
		(dword) &= (~(M_DLRX_CFG_PEER_TO_VAP_PN_acc_dis));    \
		(dword) |= ((val << B_DLRX_CFG_PEER_TO_VAP_PN_acc_dis) & M_DLRX_CFG_PEER_TO_VAP_PN_acc_dis);    \
	} while (0)

#define DLRX_CFG_PEER_TO_VAP_PN_acc_dis_clear_indirect(base, offset)	((*(base + O_DLRX_CFG_PEER_TO_VAP_PN_acc_dis + offset)) &= (~(M_DLRX_CFG_PEER_TO_VAP_PN_acc_dis)))

#define DLRX_CFG_PEER_TO_VAP_PN_acc_dis_clear_direct(dword)	((dword) &= (~(M_DLRX_CFG_PEER_TO_VAP_PN_acc_dis)))

#define O_DLRX_CFG_PEER_TO_VAP_PN_rsvd0 0
#define B_DLRX_CFG_PEER_TO_VAP_PN_rsvd0 7
#define W_DLRX_CFG_PEER_TO_VAP_PN_rsvd0 25
#define M_DLRX_CFG_PEER_TO_VAP_PN_rsvd0 0xffffff80

#define DLRX_CFG_PEER_TO_VAP_PN_rsvd0_get_indirect(base, offset)	((((*(base + O_DLRX_CFG_PEER_TO_VAP_PN_rsvd0 + offset)) & M_DLRX_CFG_PEER_TO_VAP_PN_rsvd0) >> B_DLRX_CFG_PEER_TO_VAP_PN_rsvd0))

#define DLRX_CFG_PEER_TO_VAP_PN_rsvd0_get_direct(dword)	((((dword) & M_DLRX_CFG_PEER_TO_VAP_PN_rsvd0) >> B_DLRX_CFG_PEER_TO_VAP_PN_rsvd0))

#define DLRX_CFG_PEER_TO_VAP_PN_rsvd0_set_indirect(base, offset, val) \
	do {                                                              \
		(*(base + O_DLRX_CFG_PEER_TO_VAP_PN_rsvd0 + offset)) &= (~(M_DLRX_CFG_PEER_TO_VAP_PN_rsvd0));    \
		(*(base + O_DLRX_CFG_PEER_TO_VAP_PN_rsvd0 + offset)) |= ((val << B_DLRX_CFG_PEER_TO_VAP_PN_rsvd0) & M_DLRX_CFG_PEER_TO_VAP_PN_rsvd0);    \
	} while (0)

#define DLRX_CFG_PEER_TO_VAP_PN_rsvd0_set_direct(dword, val) \
	do {                                                               \
		(dword) &= (~(M_DLRX_CFG_PEER_TO_VAP_PN_rsvd0));    \
		(dword) |= ((val << B_DLRX_CFG_PEER_TO_VAP_PN_rsvd0) & M_DLRX_CFG_PEER_TO_VAP_PN_rsvd0);    \
	} while (0)

#define DLRX_CFG_PEER_TO_VAP_PN_rsvd0_clear_indirect(base, offset)	((*(base + O_DLRX_CFG_PEER_TO_VAP_PN_rsvd0 + offset)) &= (~(M_DLRX_CFG_PEER_TO_VAP_PN_rsvd0)))

#define DLRX_CFG_PEER_TO_VAP_PN_rsvd0_clear_direct(dword)	((dword) &= (~(M_DLRX_CFG_PEER_TO_VAP_PN_rsvd0)))

#define O_DLRX_CFG_PEER_RESET_peer 0
#define B_DLRX_CFG_PEER_RESET_peer 0
#define W_DLRX_CFG_PEER_RESET_peer 7
#define M_DLRX_CFG_PEER_RESET_peer 0x0000007f

#define DLRX_CFG_PEER_RESET_peer_get_indirect(base, offset)	((((*(base + O_DLRX_CFG_PEER_RESET_peer + offset)) & M_DLRX_CFG_PEER_RESET_peer) >> B_DLRX_CFG_PEER_RESET_peer))

#define DLRX_CFG_PEER_RESET_peer_get_direct(dword)	((((dword) & M_DLRX_CFG_PEER_RESET_peer) >> B_DLRX_CFG_PEER_RESET_peer))

#define DLRX_CFG_PEER_RESET_peer_set_indirect(base, offset, val) \
	do {                                                              \
		(*(base + O_DLRX_CFG_PEER_RESET_peer + offset)) &= (~(M_DLRX_CFG_PEER_RESET_peer));    \
		(*(base + O_DLRX_CFG_PEER_RESET_peer + offset)) |= ((val << B_DLRX_CFG_PEER_RESET_peer) & M_DLRX_CFG_PEER_RESET_peer);    \
	} while (0)

#define DLRX_CFG_PEER_RESET_peer_set_direct(dword, val) \
	do {                                                               \
		(dword) &= (~(M_DLRX_CFG_PEER_RESET_peer));    \
		(dword) |= ((val << B_DLRX_CFG_PEER_RESET_peer) & M_DLRX_CFG_PEER_RESET_peer);    \
	} while (0)

#define DLRX_CFG_PEER_RESET_peer_clear_indirect(base, offset)	((*(base + O_DLRX_CFG_PEER_RESET_peer + offset)) &= (~(M_DLRX_CFG_PEER_RESET_peer)))

#define DLRX_CFG_PEER_RESET_peer_clear_direct(dword)	((dword) &= (~(M_DLRX_CFG_PEER_RESET_peer)))

#define O_DLRX_CFG_PEER_RESET_rsvd0 0
#define B_DLRX_CFG_PEER_RESET_rsvd0 7
#define W_DLRX_CFG_PEER_RESET_rsvd0 24
#define M_DLRX_CFG_PEER_RESET_rsvd0 0x7fffff80

#define DLRX_CFG_PEER_RESET_rsvd0_get_indirect(base, offset)	((((*(base + O_DLRX_CFG_PEER_RESET_rsvd0 + offset)) & M_DLRX_CFG_PEER_RESET_rsvd0) >> B_DLRX_CFG_PEER_RESET_rsvd0))

#define DLRX_CFG_PEER_RESET_rsvd0_get_direct(dword)	((((dword) & M_DLRX_CFG_PEER_RESET_rsvd0) >> B_DLRX_CFG_PEER_RESET_rsvd0))

#define DLRX_CFG_PEER_RESET_rsvd0_set_indirect(base, offset, val) \
	do {                                                              \
		(*(base + O_DLRX_CFG_PEER_RESET_rsvd0 + offset)) &= (~(M_DLRX_CFG_PEER_RESET_rsvd0));    \
		(*(base + O_DLRX_CFG_PEER_RESET_rsvd0 + offset)) |= ((val << B_DLRX_CFG_PEER_RESET_rsvd0) & M_DLRX_CFG_PEER_RESET_rsvd0);    \
	} while (0)

#define DLRX_CFG_PEER_RESET_rsvd0_set_direct(dword, val) \
	do {                                                               \
		(dword) &= (~(M_DLRX_CFG_PEER_RESET_rsvd0));    \
		(dword) |= ((val << B_DLRX_CFG_PEER_RESET_rsvd0) & M_DLRX_CFG_PEER_RESET_rsvd0);    \
	} while (0)

#define DLRX_CFG_PEER_RESET_rsvd0_clear_indirect(base, offset)	((*(base + O_DLRX_CFG_PEER_RESET_rsvd0 + offset)) &= (~(M_DLRX_CFG_PEER_RESET_rsvd0)))

#define DLRX_CFG_PEER_RESET_rsvd0_clear_direct(dword)	((dword) &= (~(M_DLRX_CFG_PEER_RESET_rsvd0)))

#define O_DLRX_CFG_PEER_RESET_req 0
#define B_DLRX_CFG_PEER_RESET_req 31
#define W_DLRX_CFG_PEER_RESET_req 1
#define M_DLRX_CFG_PEER_RESET_req 0x80000000

#define DLRX_CFG_PEER_RESET_req_get_indirect(base, offset)	((((*(base + O_DLRX_CFG_PEER_RESET_req + offset)) & M_DLRX_CFG_PEER_RESET_req) >> B_DLRX_CFG_PEER_RESET_req))

#define DLRX_CFG_PEER_RESET_req_get_direct(dword)	((((dword) & M_DLRX_CFG_PEER_RESET_req) >> B_DLRX_CFG_PEER_RESET_req))

#define DLRX_CFG_PEER_RESET_req_set_indirect(base, offset, val) \
	do {                                                              \
		(*(base + O_DLRX_CFG_PEER_RESET_req + offset)) &= (~(M_DLRX_CFG_PEER_RESET_req));    \
		(*(base + O_DLRX_CFG_PEER_RESET_req + offset)) |= ((val << B_DLRX_CFG_PEER_RESET_req) & M_DLRX_CFG_PEER_RESET_req);    \
	} while (0)

#define DLRX_CFG_PEER_RESET_req_set_direct(dword, val) \
	do {                                                               \
		(dword) &= (~(M_DLRX_CFG_PEER_RESET_req));    \
		(dword) |= ((val << B_DLRX_CFG_PEER_RESET_req) & M_DLRX_CFG_PEER_RESET_req);    \
	} while (0)

#define DLRX_CFG_PEER_RESET_req_clear_indirect(base, offset)	((*(base + O_DLRX_CFG_PEER_RESET_req + offset)) &= (~(M_DLRX_CFG_PEER_RESET_req)))

#define DLRX_CFG_PEER_RESET_req_clear_direct(dword)	((dword) &= (~(M_DLRX_CFG_PEER_RESET_req)))

#define O_DLRX_CFG_INVALID_TID_peer 0
#define B_DLRX_CFG_INVALID_TID_peer 0
#define W_DLRX_CFG_INVALID_TID_peer 7
#define M_DLRX_CFG_INVALID_TID_peer 0x0000007f

#define DLRX_CFG_INVALID_TID_peer_get_indirect(base, offset)	((((*(base + O_DLRX_CFG_INVALID_TID_peer + offset)) & M_DLRX_CFG_INVALID_TID_peer) >> B_DLRX_CFG_INVALID_TID_peer))

#define DLRX_CFG_INVALID_TID_peer_get_direct(dword)	((((dword) & M_DLRX_CFG_INVALID_TID_peer) >> B_DLRX_CFG_INVALID_TID_peer))

#define DLRX_CFG_INVALID_TID_peer_set_indirect(base, offset, val) \
	do {                                                              \
		(*(base + O_DLRX_CFG_INVALID_TID_peer + offset)) &= (~(M_DLRX_CFG_INVALID_TID_peer));    \
		(*(base + O_DLRX_CFG_INVALID_TID_peer + offset)) |= ((val << B_DLRX_CFG_INVALID_TID_peer) & M_DLRX_CFG_INVALID_TID_peer);    \
	} while (0)

#define DLRX_CFG_INVALID_TID_peer_set_direct(dword, val) \
	do {                                                               \
		(dword) &= (~(M_DLRX_CFG_INVALID_TID_peer));    \
		(dword) |= ((val << B_DLRX_CFG_INVALID_TID_peer) & M_DLRX_CFG_INVALID_TID_peer);    \
	} while (0)

#define DLRX_CFG_INVALID_TID_peer_clear_indirect(base, offset)	((*(base + O_DLRX_CFG_INVALID_TID_peer + offset)) &= (~(M_DLRX_CFG_INVALID_TID_peer)))

#define DLRX_CFG_INVALID_TID_peer_clear_direct(dword)	((dword) &= (~(M_DLRX_CFG_INVALID_TID_peer)))

#define O_DLRX_CFG_INVALID_TID_rsvd0 0
#define B_DLRX_CFG_INVALID_TID_rsvd0 7
#define W_DLRX_CFG_INVALID_TID_rsvd0 24
#define M_DLRX_CFG_INVALID_TID_rsvd0 0x7fffff80

#define DLRX_CFG_INVALID_TID_rsvd0_get_indirect(base, offset)	((((*(base + O_DLRX_CFG_INVALID_TID_rsvd0 + offset)) & M_DLRX_CFG_INVALID_TID_rsvd0) >> B_DLRX_CFG_INVALID_TID_rsvd0))

#define DLRX_CFG_INVALID_TID_rsvd0_get_direct(dword)	((((dword) & M_DLRX_CFG_INVALID_TID_rsvd0) >> B_DLRX_CFG_INVALID_TID_rsvd0))

#define DLRX_CFG_INVALID_TID_rsvd0_set_indirect(base, offset, val) \
	do {                                                              \
		(*(base + O_DLRX_CFG_INVALID_TID_rsvd0 + offset)) &= (~(M_DLRX_CFG_INVALID_TID_rsvd0));    \
		(*(base + O_DLRX_CFG_INVALID_TID_rsvd0 + offset)) |= ((val << B_DLRX_CFG_INVALID_TID_rsvd0) & M_DLRX_CFG_INVALID_TID_rsvd0);    \
	} while (0)

#define DLRX_CFG_INVALID_TID_rsvd0_set_direct(dword, val) \
	do {                                                               \
		(dword) &= (~(M_DLRX_CFG_INVALID_TID_rsvd0));    \
		(dword) |= ((val << B_DLRX_CFG_INVALID_TID_rsvd0) & M_DLRX_CFG_INVALID_TID_rsvd0);    \
	} while (0)

#define DLRX_CFG_INVALID_TID_rsvd0_clear_indirect(base, offset)	((*(base + O_DLRX_CFG_INVALID_TID_rsvd0 + offset)) &= (~(M_DLRX_CFG_INVALID_TID_rsvd0)))

#define DLRX_CFG_INVALID_TID_rsvd0_clear_direct(dword)	((dword) &= (~(M_DLRX_CFG_INVALID_TID_rsvd0)))

#define O_DLRX_CFG_INVALID_TID_req 0
#define B_DLRX_CFG_INVALID_TID_req 31
#define W_DLRX_CFG_INVALID_TID_req 1
#define M_DLRX_CFG_INVALID_TID_req 0x80000000

#define DLRX_CFG_INVALID_TID_req_get_indirect(base, offset)	((((*(base + O_DLRX_CFG_INVALID_TID_req + offset)) & M_DLRX_CFG_INVALID_TID_req) >> B_DLRX_CFG_INVALID_TID_req))

#define DLRX_CFG_INVALID_TID_req_get_direct(dword)	((((dword) & M_DLRX_CFG_INVALID_TID_req) >> B_DLRX_CFG_INVALID_TID_req))

#define DLRX_CFG_INVALID_TID_req_set_indirect(base, offset, val) \
	do {                                                              \
		(*(base + O_DLRX_CFG_INVALID_TID_req + offset)) &= (~(M_DLRX_CFG_INVALID_TID_req));    \
		(*(base + O_DLRX_CFG_INVALID_TID_req + offset)) |= ((val << B_DLRX_CFG_INVALID_TID_req) & M_DLRX_CFG_INVALID_TID_req);    \
	} while (0)

#define DLRX_CFG_INVALID_TID_req_set_direct(dword, val) \
	do {                                                               \
		(dword) &= (~(M_DLRX_CFG_INVALID_TID_req));    \
		(dword) |= ((val << B_DLRX_CFG_INVALID_TID_req) & M_DLRX_CFG_INVALID_TID_req);    \
	} while (0)

#define DLRX_CFG_INVALID_TID_req_clear_indirect(base, offset)	((*(base + O_DLRX_CFG_INVALID_TID_req + offset)) &= (~(M_DLRX_CFG_INVALID_TID_req)))

#define DLRX_CFG_INVALID_TID_req_clear_direct(dword)	((dword) &= (~(M_DLRX_CFG_INVALID_TID_req)))

#define O_DLRX_CFG_MIB_RESET_vap 0
#define B_DLRX_CFG_MIB_RESET_vap 0
#define W_DLRX_CFG_MIB_RESET_vap 4
#define M_DLRX_CFG_MIB_RESET_vap 0x0000000f

#define DLRX_CFG_MIB_RESET_vap_get_indirect(base, offset)	((((*(base + O_DLRX_CFG_MIB_RESET_vap + offset)) & M_DLRX_CFG_MIB_RESET_vap) >> B_DLRX_CFG_MIB_RESET_vap))

#define DLRX_CFG_MIB_RESET_vap_get_direct(dword)	((((dword) & M_DLRX_CFG_MIB_RESET_vap) >> B_DLRX_CFG_MIB_RESET_vap))

#define DLRX_CFG_MIB_RESET_vap_set_indirect(base, offset, val) \
	do {                                                              \
		(*(base + O_DLRX_CFG_MIB_RESET_vap + offset)) &= (~(M_DLRX_CFG_MIB_RESET_vap));    \
		(*(base + O_DLRX_CFG_MIB_RESET_vap + offset)) |= ((val << B_DLRX_CFG_MIB_RESET_vap) & M_DLRX_CFG_MIB_RESET_vap);    \
	} while (0)

#define DLRX_CFG_MIB_RESET_vap_set_direct(dword, val) \
	do {                                                               \
		(dword) &= (~(M_DLRX_CFG_MIB_RESET_vap));    \
		(dword) |= ((val << B_DLRX_CFG_MIB_RESET_vap) & M_DLRX_CFG_MIB_RESET_vap);    \
	} while (0)

#define DLRX_CFG_MIB_RESET_vap_clear_indirect(base, offset)	((*(base + O_DLRX_CFG_MIB_RESET_vap + offset)) &= (~(M_DLRX_CFG_MIB_RESET_vap)))

#define DLRX_CFG_MIB_RESET_vap_clear_direct(dword)	((dword) &= (~(M_DLRX_CFG_MIB_RESET_vap)))

#define O_DLRX_CFG_MIB_RESET_rsvd0 0
#define B_DLRX_CFG_MIB_RESET_rsvd0 4
#define W_DLRX_CFG_MIB_RESET_rsvd0 26
#define M_DLRX_CFG_MIB_RESET_rsvd0 0x3ffffff0

#define DLRX_CFG_MIB_RESET_rsvd0_get_indirect(base, offset)	((((*(base + O_DLRX_CFG_MIB_RESET_rsvd0 + offset)) & M_DLRX_CFG_MIB_RESET_rsvd0) >> B_DLRX_CFG_MIB_RESET_rsvd0))

#define DLRX_CFG_MIB_RESET_rsvd0_get_direct(dword)	((((dword) & M_DLRX_CFG_MIB_RESET_rsvd0) >> B_DLRX_CFG_MIB_RESET_rsvd0))

#define DLRX_CFG_MIB_RESET_rsvd0_set_indirect(base, offset, val) \
	do {                                                              \
		(*(base + O_DLRX_CFG_MIB_RESET_rsvd0 + offset)) &= (~(M_DLRX_CFG_MIB_RESET_rsvd0));    \
		(*(base + O_DLRX_CFG_MIB_RESET_rsvd0 + offset)) |= ((val << B_DLRX_CFG_MIB_RESET_rsvd0) & M_DLRX_CFG_MIB_RESET_rsvd0);    \
	} while (0)

#define DLRX_CFG_MIB_RESET_rsvd0_set_direct(dword, val) \
	do {                                                               \
		(dword) &= (~(M_DLRX_CFG_MIB_RESET_rsvd0));    \
		(dword) |= ((val << B_DLRX_CFG_MIB_RESET_rsvd0) & M_DLRX_CFG_MIB_RESET_rsvd0);    \
	} while (0)

#define DLRX_CFG_MIB_RESET_rsvd0_clear_indirect(base, offset)	((*(base + O_DLRX_CFG_MIB_RESET_rsvd0 + offset)) &= (~(M_DLRX_CFG_MIB_RESET_rsvd0)))

#define DLRX_CFG_MIB_RESET_rsvd0_clear_direct(dword)	((dword) &= (~(M_DLRX_CFG_MIB_RESET_rsvd0)))

#define O_DLRX_CFG_MIB_RESET_vapreq 0
#define B_DLRX_CFG_MIB_RESET_vapreq 30
#define W_DLRX_CFG_MIB_RESET_vapreq 1
#define M_DLRX_CFG_MIB_RESET_vapreq 0x40000000

#define DLRX_CFG_MIB_RESET_vapreq_get_indirect(base, offset)	((((*(base + O_DLRX_CFG_MIB_RESET_vapreq + offset)) & M_DLRX_CFG_MIB_RESET_vapreq) >> B_DLRX_CFG_MIB_RESET_vapreq))

#define DLRX_CFG_MIB_RESET_vapreq_get_direct(dword)	((((dword) & M_DLRX_CFG_MIB_RESET_vapreq) >> B_DLRX_CFG_MIB_RESET_vapreq))

#define DLRX_CFG_MIB_RESET_vapreq_set_indirect(base, offset, val) \
	do {                                                              \
		(*(base + O_DLRX_CFG_MIB_RESET_vapreq + offset)) &= (~(M_DLRX_CFG_MIB_RESET_vapreq));    \
		(*(base + O_DLRX_CFG_MIB_RESET_vapreq + offset)) |= ((val << B_DLRX_CFG_MIB_RESET_vapreq) & M_DLRX_CFG_MIB_RESET_vapreq);    \
	} while (0)

#define DLRX_CFG_MIB_RESET_vapreq_set_direct(dword, val) \
	do {                                                               \
		(dword) &= (~(M_DLRX_CFG_MIB_RESET_vapreq));    \
		(dword) |= ((val << B_DLRX_CFG_MIB_RESET_vapreq) & M_DLRX_CFG_MIB_RESET_vapreq);    \
	} while (0)

#define DLRX_CFG_MIB_RESET_vapreq_clear_indirect(base, offset)	((*(base + O_DLRX_CFG_MIB_RESET_vapreq + offset)) &= (~(M_DLRX_CFG_MIB_RESET_vapreq)))

#define DLRX_CFG_MIB_RESET_vapreq_clear_direct(dword)	((dword) &= (~(M_DLRX_CFG_MIB_RESET_vapreq)))

#define O_DLRX_CFG_MIB_RESET_allreq 0
#define B_DLRX_CFG_MIB_RESET_allreq 31
#define W_DLRX_CFG_MIB_RESET_allreq 1
#define M_DLRX_CFG_MIB_RESET_allreq 0x80000000

#define DLRX_CFG_MIB_RESET_allreq_get_indirect(base, offset)	((((*(base + O_DLRX_CFG_MIB_RESET_allreq + offset)) & M_DLRX_CFG_MIB_RESET_allreq) >> B_DLRX_CFG_MIB_RESET_allreq))

#define DLRX_CFG_MIB_RESET_allreq_get_direct(dword)	((((dword) & M_DLRX_CFG_MIB_RESET_allreq) >> B_DLRX_CFG_MIB_RESET_allreq))

#define DLRX_CFG_MIB_RESET_allreq_set_indirect(base, offset, val) \
	do {                                                              \
		(*(base + O_DLRX_CFG_MIB_RESET_allreq + offset)) &= (~(M_DLRX_CFG_MIB_RESET_allreq));    \
		(*(base + O_DLRX_CFG_MIB_RESET_allreq + offset)) |= ((val << B_DLRX_CFG_MIB_RESET_allreq) & M_DLRX_CFG_MIB_RESET_allreq);    \
	} while (0)

#define DLRX_CFG_MIB_RESET_allreq_set_direct(dword, val) \
	do {                                                               \
		(dword) &= (~(M_DLRX_CFG_MIB_RESET_allreq));    \
		(dword) |= ((val << B_DLRX_CFG_MIB_RESET_allreq) & M_DLRX_CFG_MIB_RESET_allreq);    \
	} while (0)

#define DLRX_CFG_MIB_RESET_allreq_clear_indirect(base, offset)	((*(base + O_DLRX_CFG_MIB_RESET_allreq + offset)) &= (~(M_DLRX_CFG_MIB_RESET_allreq)))

#define DLRX_CFG_MIB_RESET_allreq_clear_direct(dword)	((dword) &= (~(M_DLRX_CFG_MIB_RESET_allreq)))

#define O_DLRX_CFG_VAP2INT_MAP1_vap0 0
#define B_DLRX_CFG_VAP2INT_MAP1_vap0 0
#define W_DLRX_CFG_VAP2INT_MAP1_vap0 4
#define M_DLRX_CFG_VAP2INT_MAP1_vap0 0x0000000f

#define DLRX_CFG_VAP2INT_MAP1_vap0_get_indirect(base, offset)	((((*(base + O_DLRX_CFG_VAP2INT_MAP1_vap0 + offset)) & M_DLRX_CFG_VAP2INT_MAP1_vap0) >> B_DLRX_CFG_VAP2INT_MAP1_vap0))

#define DLRX_CFG_VAP2INT_MAP1_vap0_get_direct(dword)	((((dword) & M_DLRX_CFG_VAP2INT_MAP1_vap0) >> B_DLRX_CFG_VAP2INT_MAP1_vap0))

#define DLRX_CFG_VAP2INT_MAP1_vap0_set_indirect(base, offset, val) \
	do {                                                              \
		(*(base + O_DLRX_CFG_VAP2INT_MAP1_vap0 + offset)) &= (~(M_DLRX_CFG_VAP2INT_MAP1_vap0));    \
		(*(base + O_DLRX_CFG_VAP2INT_MAP1_vap0 + offset)) |= ((val << B_DLRX_CFG_VAP2INT_MAP1_vap0) & M_DLRX_CFG_VAP2INT_MAP1_vap0);    \
	} while (0)

#define DLRX_CFG_VAP2INT_MAP1_vap0_set_direct(dword, val) \
	do {                                                               \
		(dword) &= (~(M_DLRX_CFG_VAP2INT_MAP1_vap0));    \
		(dword) |= ((val << B_DLRX_CFG_VAP2INT_MAP1_vap0) & M_DLRX_CFG_VAP2INT_MAP1_vap0);    \
	} while (0)

#define DLRX_CFG_VAP2INT_MAP1_vap0_clear_indirect(base, offset)	((*(base + O_DLRX_CFG_VAP2INT_MAP1_vap0 + offset)) &= (~(M_DLRX_CFG_VAP2INT_MAP1_vap0)))

#define DLRX_CFG_VAP2INT_MAP1_vap0_clear_direct(dword)	((dword) &= (~(M_DLRX_CFG_VAP2INT_MAP1_vap0)))

#define O_DLRX_CFG_VAP2INT_MAP1_vap1 0
#define B_DLRX_CFG_VAP2INT_MAP1_vap1 4
#define W_DLRX_CFG_VAP2INT_MAP1_vap1 4
#define M_DLRX_CFG_VAP2INT_MAP1_vap1 0x000000f0

#define DLRX_CFG_VAP2INT_MAP1_vap1_get_indirect(base, offset)	((((*(base + O_DLRX_CFG_VAP2INT_MAP1_vap1 + offset)) & M_DLRX_CFG_VAP2INT_MAP1_vap1) >> B_DLRX_CFG_VAP2INT_MAP1_vap1))

#define DLRX_CFG_VAP2INT_MAP1_vap1_get_direct(dword)	((((dword) & M_DLRX_CFG_VAP2INT_MAP1_vap1) >> B_DLRX_CFG_VAP2INT_MAP1_vap1))

#define DLRX_CFG_VAP2INT_MAP1_vap1_set_indirect(base, offset, val) \
	do {                                                              \
		(*(base + O_DLRX_CFG_VAP2INT_MAP1_vap1 + offset)) &= (~(M_DLRX_CFG_VAP2INT_MAP1_vap1));    \
		(*(base + O_DLRX_CFG_VAP2INT_MAP1_vap1 + offset)) |= ((val << B_DLRX_CFG_VAP2INT_MAP1_vap1) & M_DLRX_CFG_VAP2INT_MAP1_vap1);    \
	} while (0)

#define DLRX_CFG_VAP2INT_MAP1_vap1_set_direct(dword, val) \
	do {                                                               \
		(dword) &= (~(M_DLRX_CFG_VAP2INT_MAP1_vap1));    \
		(dword) |= ((val << B_DLRX_CFG_VAP2INT_MAP1_vap1) & M_DLRX_CFG_VAP2INT_MAP1_vap1);    \
	} while (0)

#define DLRX_CFG_VAP2INT_MAP1_vap1_clear_indirect(base, offset)	((*(base + O_DLRX_CFG_VAP2INT_MAP1_vap1 + offset)) &= (~(M_DLRX_CFG_VAP2INT_MAP1_vap1)))

#define DLRX_CFG_VAP2INT_MAP1_vap1_clear_direct(dword)	((dword) &= (~(M_DLRX_CFG_VAP2INT_MAP1_vap1)))

#define O_DLRX_CFG_VAP2INT_MAP1_vap2 0
#define B_DLRX_CFG_VAP2INT_MAP1_vap2 8
#define W_DLRX_CFG_VAP2INT_MAP1_vap2 4
#define M_DLRX_CFG_VAP2INT_MAP1_vap2 0x00000f00

#define DLRX_CFG_VAP2INT_MAP1_vap2_get_indirect(base, offset)	((((*(base + O_DLRX_CFG_VAP2INT_MAP1_vap2 + offset)) & M_DLRX_CFG_VAP2INT_MAP1_vap2) >> B_DLRX_CFG_VAP2INT_MAP1_vap2))

#define DLRX_CFG_VAP2INT_MAP1_vap2_get_direct(dword)	((((dword) & M_DLRX_CFG_VAP2INT_MAP1_vap2) >> B_DLRX_CFG_VAP2INT_MAP1_vap2))

#define DLRX_CFG_VAP2INT_MAP1_vap2_set_indirect(base, offset, val) \
	do {                                                              \
		(*(base + O_DLRX_CFG_VAP2INT_MAP1_vap2 + offset)) &= (~(M_DLRX_CFG_VAP2INT_MAP1_vap2));    \
		(*(base + O_DLRX_CFG_VAP2INT_MAP1_vap2 + offset)) |= ((val << B_DLRX_CFG_VAP2INT_MAP1_vap2) & M_DLRX_CFG_VAP2INT_MAP1_vap2);    \
	} while (0)

#define DLRX_CFG_VAP2INT_MAP1_vap2_set_direct(dword, val) \
	do {                                                               \
		(dword) &= (~(M_DLRX_CFG_VAP2INT_MAP1_vap2));    \
		(dword) |= ((val << B_DLRX_CFG_VAP2INT_MAP1_vap2) & M_DLRX_CFG_VAP2INT_MAP1_vap2);    \
	} while (0)

#define DLRX_CFG_VAP2INT_MAP1_vap2_clear_indirect(base, offset)	((*(base + O_DLRX_CFG_VAP2INT_MAP1_vap2 + offset)) &= (~(M_DLRX_CFG_VAP2INT_MAP1_vap2)))

#define DLRX_CFG_VAP2INT_MAP1_vap2_clear_direct(dword)	((dword) &= (~(M_DLRX_CFG_VAP2INT_MAP1_vap2)))

#define O_DLRX_CFG_VAP2INT_MAP1_vap3 0
#define B_DLRX_CFG_VAP2INT_MAP1_vap3 12
#define W_DLRX_CFG_VAP2INT_MAP1_vap3 4
#define M_DLRX_CFG_VAP2INT_MAP1_vap3 0x0000f000

#define DLRX_CFG_VAP2INT_MAP1_vap3_get_indirect(base, offset)	((((*(base + O_DLRX_CFG_VAP2INT_MAP1_vap3 + offset)) & M_DLRX_CFG_VAP2INT_MAP1_vap3) >> B_DLRX_CFG_VAP2INT_MAP1_vap3))

#define DLRX_CFG_VAP2INT_MAP1_vap3_get_direct(dword)	((((dword) & M_DLRX_CFG_VAP2INT_MAP1_vap3) >> B_DLRX_CFG_VAP2INT_MAP1_vap3))

#define DLRX_CFG_VAP2INT_MAP1_vap3_set_indirect(base, offset, val) \
	do {                                                              \
		(*(base + O_DLRX_CFG_VAP2INT_MAP1_vap3 + offset)) &= (~(M_DLRX_CFG_VAP2INT_MAP1_vap3));    \
		(*(base + O_DLRX_CFG_VAP2INT_MAP1_vap3 + offset)) |= ((val << B_DLRX_CFG_VAP2INT_MAP1_vap3) & M_DLRX_CFG_VAP2INT_MAP1_vap3);    \
	} while (0)

#define DLRX_CFG_VAP2INT_MAP1_vap3_set_direct(dword, val) \
	do {                                                               \
		(dword) &= (~(M_DLRX_CFG_VAP2INT_MAP1_vap3));    \
		(dword) |= ((val << B_DLRX_CFG_VAP2INT_MAP1_vap3) & M_DLRX_CFG_VAP2INT_MAP1_vap3);    \
	} while (0)

#define DLRX_CFG_VAP2INT_MAP1_vap3_clear_indirect(base, offset)	((*(base + O_DLRX_CFG_VAP2INT_MAP1_vap3 + offset)) &= (~(M_DLRX_CFG_VAP2INT_MAP1_vap3)))

#define DLRX_CFG_VAP2INT_MAP1_vap3_clear_direct(dword)	((dword) &= (~(M_DLRX_CFG_VAP2INT_MAP1_vap3)))

#define O_DLRX_CFG_VAP2INT_MAP1_vap4 0
#define B_DLRX_CFG_VAP2INT_MAP1_vap4 16
#define W_DLRX_CFG_VAP2INT_MAP1_vap4 4
#define M_DLRX_CFG_VAP2INT_MAP1_vap4 0x000f0000

#define DLRX_CFG_VAP2INT_MAP1_vap4_get_indirect(base, offset)	((((*(base + O_DLRX_CFG_VAP2INT_MAP1_vap4 + offset)) & M_DLRX_CFG_VAP2INT_MAP1_vap4) >> B_DLRX_CFG_VAP2INT_MAP1_vap4))

#define DLRX_CFG_VAP2INT_MAP1_vap4_get_direct(dword)	((((dword) & M_DLRX_CFG_VAP2INT_MAP1_vap4) >> B_DLRX_CFG_VAP2INT_MAP1_vap4))

#define DLRX_CFG_VAP2INT_MAP1_vap4_set_indirect(base, offset, val) \
	do {                                                              \
		(*(base + O_DLRX_CFG_VAP2INT_MAP1_vap4 + offset)) &= (~(M_DLRX_CFG_VAP2INT_MAP1_vap4));    \
		(*(base + O_DLRX_CFG_VAP2INT_MAP1_vap4 + offset)) |= ((val << B_DLRX_CFG_VAP2INT_MAP1_vap4) & M_DLRX_CFG_VAP2INT_MAP1_vap4);    \
	} while (0)

#define DLRX_CFG_VAP2INT_MAP1_vap4_set_direct(dword, val) \
	do {                                                               \
		(dword) &= (~(M_DLRX_CFG_VAP2INT_MAP1_vap4));    \
		(dword) |= ((val << B_DLRX_CFG_VAP2INT_MAP1_vap4) & M_DLRX_CFG_VAP2INT_MAP1_vap4);    \
	} while (0)

#define DLRX_CFG_VAP2INT_MAP1_vap4_clear_indirect(base, offset)	((*(base + O_DLRX_CFG_VAP2INT_MAP1_vap4 + offset)) &= (~(M_DLRX_CFG_VAP2INT_MAP1_vap4)))

#define DLRX_CFG_VAP2INT_MAP1_vap4_clear_direct(dword)	((dword) &= (~(M_DLRX_CFG_VAP2INT_MAP1_vap4)))

#define O_DLRX_CFG_VAP2INT_MAP1_vap5 0
#define B_DLRX_CFG_VAP2INT_MAP1_vap5 20
#define W_DLRX_CFG_VAP2INT_MAP1_vap5 4
#define M_DLRX_CFG_VAP2INT_MAP1_vap5 0x00f00000

#define DLRX_CFG_VAP2INT_MAP1_vap5_get_indirect(base, offset)	((((*(base + O_DLRX_CFG_VAP2INT_MAP1_vap5 + offset)) & M_DLRX_CFG_VAP2INT_MAP1_vap5) >> B_DLRX_CFG_VAP2INT_MAP1_vap5))

#define DLRX_CFG_VAP2INT_MAP1_vap5_get_direct(dword)	((((dword) & M_DLRX_CFG_VAP2INT_MAP1_vap5) >> B_DLRX_CFG_VAP2INT_MAP1_vap5))

#define DLRX_CFG_VAP2INT_MAP1_vap5_set_indirect(base, offset, val) \
	do {                                                              \
		(*(base + O_DLRX_CFG_VAP2INT_MAP1_vap5 + offset)) &= (~(M_DLRX_CFG_VAP2INT_MAP1_vap5));    \
		(*(base + O_DLRX_CFG_VAP2INT_MAP1_vap5 + offset)) |= ((val << B_DLRX_CFG_VAP2INT_MAP1_vap5) & M_DLRX_CFG_VAP2INT_MAP1_vap5);    \
	} while (0)

#define DLRX_CFG_VAP2INT_MAP1_vap5_set_direct(dword, val) \
	do {                                                               \
		(dword) &= (~(M_DLRX_CFG_VAP2INT_MAP1_vap5));    \
		(dword) |= ((val << B_DLRX_CFG_VAP2INT_MAP1_vap5) & M_DLRX_CFG_VAP2INT_MAP1_vap5);    \
	} while (0)

#define DLRX_CFG_VAP2INT_MAP1_vap5_clear_indirect(base, offset)	((*(base + O_DLRX_CFG_VAP2INT_MAP1_vap5 + offset)) &= (~(M_DLRX_CFG_VAP2INT_MAP1_vap5)))

#define DLRX_CFG_VAP2INT_MAP1_vap5_clear_direct(dword)	((dword) &= (~(M_DLRX_CFG_VAP2INT_MAP1_vap5)))

#define O_DLRX_CFG_VAP2INT_MAP1_vap6 0
#define B_DLRX_CFG_VAP2INT_MAP1_vap6 24
#define W_DLRX_CFG_VAP2INT_MAP1_vap6 4
#define M_DLRX_CFG_VAP2INT_MAP1_vap6 0x0f000000

#define DLRX_CFG_VAP2INT_MAP1_vap6_get_indirect(base, offset)	((((*(base + O_DLRX_CFG_VAP2INT_MAP1_vap6 + offset)) & M_DLRX_CFG_VAP2INT_MAP1_vap6) >> B_DLRX_CFG_VAP2INT_MAP1_vap6))

#define DLRX_CFG_VAP2INT_MAP1_vap6_get_direct(dword)	((((dword) & M_DLRX_CFG_VAP2INT_MAP1_vap6) >> B_DLRX_CFG_VAP2INT_MAP1_vap6))

#define DLRX_CFG_VAP2INT_MAP1_vap6_set_indirect(base, offset, val) \
	do {                                                              \
		(*(base + O_DLRX_CFG_VAP2INT_MAP1_vap6 + offset)) &= (~(M_DLRX_CFG_VAP2INT_MAP1_vap6));    \
		(*(base + O_DLRX_CFG_VAP2INT_MAP1_vap6 + offset)) |= ((val << B_DLRX_CFG_VAP2INT_MAP1_vap6) & M_DLRX_CFG_VAP2INT_MAP1_vap6);    \
	} while (0)

#define DLRX_CFG_VAP2INT_MAP1_vap6_set_direct(dword, val) \
	do {                                                               \
		(dword) &= (~(M_DLRX_CFG_VAP2INT_MAP1_vap6));    \
		(dword) |= ((val << B_DLRX_CFG_VAP2INT_MAP1_vap6) & M_DLRX_CFG_VAP2INT_MAP1_vap6);    \
	} while (0)

#define DLRX_CFG_VAP2INT_MAP1_vap6_clear_indirect(base, offset)	((*(base + O_DLRX_CFG_VAP2INT_MAP1_vap6 + offset)) &= (~(M_DLRX_CFG_VAP2INT_MAP1_vap6)))

#define DLRX_CFG_VAP2INT_MAP1_vap6_clear_direct(dword)	((dword) &= (~(M_DLRX_CFG_VAP2INT_MAP1_vap6)))

#define O_DLRX_CFG_VAP2INT_MAP1_vap7 0
#define B_DLRX_CFG_VAP2INT_MAP1_vap7 28
#define W_DLRX_CFG_VAP2INT_MAP1_vap7 4
#define M_DLRX_CFG_VAP2INT_MAP1_vap7 0xf0000000

#define DLRX_CFG_VAP2INT_MAP1_vap7_get_indirect(base, offset)	((((*(base + O_DLRX_CFG_VAP2INT_MAP1_vap7 + offset)) & M_DLRX_CFG_VAP2INT_MAP1_vap7) >> B_DLRX_CFG_VAP2INT_MAP1_vap7))

#define DLRX_CFG_VAP2INT_MAP1_vap7_get_direct(dword)	((((dword) & M_DLRX_CFG_VAP2INT_MAP1_vap7) >> B_DLRX_CFG_VAP2INT_MAP1_vap7))

#define DLRX_CFG_VAP2INT_MAP1_vap7_set_indirect(base, offset, val) \
	do {                                                              \
		(*(base + O_DLRX_CFG_VAP2INT_MAP1_vap7 + offset)) &= (~(M_DLRX_CFG_VAP2INT_MAP1_vap7));    \
		(*(base + O_DLRX_CFG_VAP2INT_MAP1_vap7 + offset)) |= ((val << B_DLRX_CFG_VAP2INT_MAP1_vap7) & M_DLRX_CFG_VAP2INT_MAP1_vap7);    \
	} while (0)

#define DLRX_CFG_VAP2INT_MAP1_vap7_set_direct(dword, val) \
	do {                                                               \
		(dword) &= (~(M_DLRX_CFG_VAP2INT_MAP1_vap7));    \
		(dword) |= ((val << B_DLRX_CFG_VAP2INT_MAP1_vap7) & M_DLRX_CFG_VAP2INT_MAP1_vap7);    \
	} while (0)

#define DLRX_CFG_VAP2INT_MAP1_vap7_clear_indirect(base, offset)	((*(base + O_DLRX_CFG_VAP2INT_MAP1_vap7 + offset)) &= (~(M_DLRX_CFG_VAP2INT_MAP1_vap7)))

#define DLRX_CFG_VAP2INT_MAP1_vap7_clear_direct(dword)	((dword) &= (~(M_DLRX_CFG_VAP2INT_MAP1_vap7)))

#define O_DLRX_CFG_VAP2INT_MAP2_vap8 0
#define B_DLRX_CFG_VAP2INT_MAP2_vap8 0
#define W_DLRX_CFG_VAP2INT_MAP2_vap8 4
#define M_DLRX_CFG_VAP2INT_MAP2_vap8 0x0000000f

#define DLRX_CFG_VAP2INT_MAP2_vap8_get_indirect(base, offset)	((((*(base + O_DLRX_CFG_VAP2INT_MAP2_vap8 + offset)) & M_DLRX_CFG_VAP2INT_MAP2_vap8) >> B_DLRX_CFG_VAP2INT_MAP2_vap8))

#define DLRX_CFG_VAP2INT_MAP2_vap8_get_direct(dword)	((((dword) & M_DLRX_CFG_VAP2INT_MAP2_vap8) >> B_DLRX_CFG_VAP2INT_MAP2_vap8))

#define DLRX_CFG_VAP2INT_MAP2_vap8_set_indirect(base, offset, val) \
	do {                                                              \
		(*(base + O_DLRX_CFG_VAP2INT_MAP2_vap8 + offset)) &= (~(M_DLRX_CFG_VAP2INT_MAP2_vap8));    \
		(*(base + O_DLRX_CFG_VAP2INT_MAP2_vap8 + offset)) |= ((val << B_DLRX_CFG_VAP2INT_MAP2_vap8) & M_DLRX_CFG_VAP2INT_MAP2_vap8);    \
	} while (0)

#define DLRX_CFG_VAP2INT_MAP2_vap8_set_direct(dword, val) \
	do {                                                               \
		(dword) &= (~(M_DLRX_CFG_VAP2INT_MAP2_vap8));    \
		(dword) |= ((val << B_DLRX_CFG_VAP2INT_MAP2_vap8) & M_DLRX_CFG_VAP2INT_MAP2_vap8);    \
	} while (0)

#define DLRX_CFG_VAP2INT_MAP2_vap8_clear_indirect(base, offset)	((*(base + O_DLRX_CFG_VAP2INT_MAP2_vap8 + offset)) &= (~(M_DLRX_CFG_VAP2INT_MAP2_vap8)))

#define DLRX_CFG_VAP2INT_MAP2_vap8_clear_direct(dword)	((dword) &= (~(M_DLRX_CFG_VAP2INT_MAP2_vap8)))

#define O_DLRX_CFG_VAP2INT_MAP2_vap9 0
#define B_DLRX_CFG_VAP2INT_MAP2_vap9 4
#define W_DLRX_CFG_VAP2INT_MAP2_vap9 4
#define M_DLRX_CFG_VAP2INT_MAP2_vap9 0x000000f0

#define DLRX_CFG_VAP2INT_MAP2_vap9_get_indirect(base, offset)	((((*(base + O_DLRX_CFG_VAP2INT_MAP2_vap9 + offset)) & M_DLRX_CFG_VAP2INT_MAP2_vap9) >> B_DLRX_CFG_VAP2INT_MAP2_vap9))

#define DLRX_CFG_VAP2INT_MAP2_vap9_get_direct(dword)	((((dword) & M_DLRX_CFG_VAP2INT_MAP2_vap9) >> B_DLRX_CFG_VAP2INT_MAP2_vap9))

#define DLRX_CFG_VAP2INT_MAP2_vap9_set_indirect(base, offset, val) \
	do {                                                              \
		(*(base + O_DLRX_CFG_VAP2INT_MAP2_vap9 + offset)) &= (~(M_DLRX_CFG_VAP2INT_MAP2_vap9));    \
		(*(base + O_DLRX_CFG_VAP2INT_MAP2_vap9 + offset)) |= ((val << B_DLRX_CFG_VAP2INT_MAP2_vap9) & M_DLRX_CFG_VAP2INT_MAP2_vap9);    \
	} while (0)

#define DLRX_CFG_VAP2INT_MAP2_vap9_set_direct(dword, val) \
	do {                                                               \
		(dword) &= (~(M_DLRX_CFG_VAP2INT_MAP2_vap9));    \
		(dword) |= ((val << B_DLRX_CFG_VAP2INT_MAP2_vap9) & M_DLRX_CFG_VAP2INT_MAP2_vap9);    \
	} while (0)

#define DLRX_CFG_VAP2INT_MAP2_vap9_clear_indirect(base, offset)	((*(base + O_DLRX_CFG_VAP2INT_MAP2_vap9 + offset)) &= (~(M_DLRX_CFG_VAP2INT_MAP2_vap9)))

#define DLRX_CFG_VAP2INT_MAP2_vap9_clear_direct(dword)	((dword) &= (~(M_DLRX_CFG_VAP2INT_MAP2_vap9)))

#define O_DLRX_CFG_VAP2INT_MAP2_vap10 0
#define B_DLRX_CFG_VAP2INT_MAP2_vap10 8
#define W_DLRX_CFG_VAP2INT_MAP2_vap10 4
#define M_DLRX_CFG_VAP2INT_MAP2_vap10 0x00000f00

#define DLRX_CFG_VAP2INT_MAP2_vap10_get_indirect(base, offset)	((((*(base + O_DLRX_CFG_VAP2INT_MAP2_vap10 + offset)) & M_DLRX_CFG_VAP2INT_MAP2_vap10) >> B_DLRX_CFG_VAP2INT_MAP2_vap10))

#define DLRX_CFG_VAP2INT_MAP2_vap10_get_direct(dword)	((((dword) & M_DLRX_CFG_VAP2INT_MAP2_vap10) >> B_DLRX_CFG_VAP2INT_MAP2_vap10))

#define DLRX_CFG_VAP2INT_MAP2_vap10_set_indirect(base, offset, val) \
	do {                                                              \
		(*(base + O_DLRX_CFG_VAP2INT_MAP2_vap10 + offset)) &= (~(M_DLRX_CFG_VAP2INT_MAP2_vap10));    \
		(*(base + O_DLRX_CFG_VAP2INT_MAP2_vap10 + offset)) |= ((val << B_DLRX_CFG_VAP2INT_MAP2_vap10) & M_DLRX_CFG_VAP2INT_MAP2_vap10);    \
	} while (0)

#define DLRX_CFG_VAP2INT_MAP2_vap10_set_direct(dword, val) \
	do {                                                               \
		(dword) &= (~(M_DLRX_CFG_VAP2INT_MAP2_vap10));    \
		(dword) |= ((val << B_DLRX_CFG_VAP2INT_MAP2_vap10) & M_DLRX_CFG_VAP2INT_MAP2_vap10);    \
	} while (0)

#define DLRX_CFG_VAP2INT_MAP2_vap10_clear_indirect(base, offset)	((*(base + O_DLRX_CFG_VAP2INT_MAP2_vap10 + offset)) &= (~(M_DLRX_CFG_VAP2INT_MAP2_vap10)))

#define DLRX_CFG_VAP2INT_MAP2_vap10_clear_direct(dword)	((dword) &= (~(M_DLRX_CFG_VAP2INT_MAP2_vap10)))

#define O_DLRX_CFG_VAP2INT_MAP2_vap11 0
#define B_DLRX_CFG_VAP2INT_MAP2_vap11 12
#define W_DLRX_CFG_VAP2INT_MAP2_vap11 4
#define M_DLRX_CFG_VAP2INT_MAP2_vap11 0x0000f000

#define DLRX_CFG_VAP2INT_MAP2_vap11_get_indirect(base, offset)	((((*(base + O_DLRX_CFG_VAP2INT_MAP2_vap11 + offset)) & M_DLRX_CFG_VAP2INT_MAP2_vap11) >> B_DLRX_CFG_VAP2INT_MAP2_vap11))

#define DLRX_CFG_VAP2INT_MAP2_vap11_get_direct(dword)	((((dword) & M_DLRX_CFG_VAP2INT_MAP2_vap11) >> B_DLRX_CFG_VAP2INT_MAP2_vap11))

#define DLRX_CFG_VAP2INT_MAP2_vap11_set_indirect(base, offset, val) \
	do {                                                              \
		(*(base + O_DLRX_CFG_VAP2INT_MAP2_vap11 + offset)) &= (~(M_DLRX_CFG_VAP2INT_MAP2_vap11));    \
		(*(base + O_DLRX_CFG_VAP2INT_MAP2_vap11 + offset)) |= ((val << B_DLRX_CFG_VAP2INT_MAP2_vap11) & M_DLRX_CFG_VAP2INT_MAP2_vap11);    \
	} while (0)

#define DLRX_CFG_VAP2INT_MAP2_vap11_set_direct(dword, val) \
	do {                                                               \
		(dword) &= (~(M_DLRX_CFG_VAP2INT_MAP2_vap11));    \
		(dword) |= ((val << B_DLRX_CFG_VAP2INT_MAP2_vap11) & M_DLRX_CFG_VAP2INT_MAP2_vap11);    \
	} while (0)

#define DLRX_CFG_VAP2INT_MAP2_vap11_clear_indirect(base, offset)	((*(base + O_DLRX_CFG_VAP2INT_MAP2_vap11 + offset)) &= (~(M_DLRX_CFG_VAP2INT_MAP2_vap11)))

#define DLRX_CFG_VAP2INT_MAP2_vap11_clear_direct(dword)	((dword) &= (~(M_DLRX_CFG_VAP2INT_MAP2_vap11)))

#define O_DLRX_CFG_VAP2INT_MAP2_vap12 0
#define B_DLRX_CFG_VAP2INT_MAP2_vap12 16
#define W_DLRX_CFG_VAP2INT_MAP2_vap12 4
#define M_DLRX_CFG_VAP2INT_MAP2_vap12 0x000f0000

#define DLRX_CFG_VAP2INT_MAP2_vap12_get_indirect(base, offset)	((((*(base + O_DLRX_CFG_VAP2INT_MAP2_vap12 + offset)) & M_DLRX_CFG_VAP2INT_MAP2_vap12) >> B_DLRX_CFG_VAP2INT_MAP2_vap12))

#define DLRX_CFG_VAP2INT_MAP2_vap12_get_direct(dword)	((((dword) & M_DLRX_CFG_VAP2INT_MAP2_vap12) >> B_DLRX_CFG_VAP2INT_MAP2_vap12))

#define DLRX_CFG_VAP2INT_MAP2_vap12_set_indirect(base, offset, val) \
	do {                                                              \
		(*(base + O_DLRX_CFG_VAP2INT_MAP2_vap12 + offset)) &= (~(M_DLRX_CFG_VAP2INT_MAP2_vap12));    \
		(*(base + O_DLRX_CFG_VAP2INT_MAP2_vap12 + offset)) |= ((val << B_DLRX_CFG_VAP2INT_MAP2_vap12) & M_DLRX_CFG_VAP2INT_MAP2_vap12);    \
	} while (0)

#define DLRX_CFG_VAP2INT_MAP2_vap12_set_direct(dword, val) \
	do {                                                               \
		(dword) &= (~(M_DLRX_CFG_VAP2INT_MAP2_vap12));    \
		(dword) |= ((val << B_DLRX_CFG_VAP2INT_MAP2_vap12) & M_DLRX_CFG_VAP2INT_MAP2_vap12);    \
	} while (0)

#define DLRX_CFG_VAP2INT_MAP2_vap12_clear_indirect(base, offset)	((*(base + O_DLRX_CFG_VAP2INT_MAP2_vap12 + offset)) &= (~(M_DLRX_CFG_VAP2INT_MAP2_vap12)))

#define DLRX_CFG_VAP2INT_MAP2_vap12_clear_direct(dword)	((dword) &= (~(M_DLRX_CFG_VAP2INT_MAP2_vap12)))

#define O_DLRX_CFG_VAP2INT_MAP2_vap13 0
#define B_DLRX_CFG_VAP2INT_MAP2_vap13 20
#define W_DLRX_CFG_VAP2INT_MAP2_vap13 4
#define M_DLRX_CFG_VAP2INT_MAP2_vap13 0x00f00000

#define DLRX_CFG_VAP2INT_MAP2_vap13_get_indirect(base, offset)	((((*(base + O_DLRX_CFG_VAP2INT_MAP2_vap13 + offset)) & M_DLRX_CFG_VAP2INT_MAP2_vap13) >> B_DLRX_CFG_VAP2INT_MAP2_vap13))

#define DLRX_CFG_VAP2INT_MAP2_vap13_get_direct(dword)	((((dword) & M_DLRX_CFG_VAP2INT_MAP2_vap13) >> B_DLRX_CFG_VAP2INT_MAP2_vap13))

#define DLRX_CFG_VAP2INT_MAP2_vap13_set_indirect(base, offset, val) \
	do {                                                              \
		(*(base + O_DLRX_CFG_VAP2INT_MAP2_vap13 + offset)) &= (~(M_DLRX_CFG_VAP2INT_MAP2_vap13));    \
		(*(base + O_DLRX_CFG_VAP2INT_MAP2_vap13 + offset)) |= ((val << B_DLRX_CFG_VAP2INT_MAP2_vap13) & M_DLRX_CFG_VAP2INT_MAP2_vap13);    \
	} while (0)

#define DLRX_CFG_VAP2INT_MAP2_vap13_set_direct(dword, val) \
	do {                                                               \
		(dword) &= (~(M_DLRX_CFG_VAP2INT_MAP2_vap13));    \
		(dword) |= ((val << B_DLRX_CFG_VAP2INT_MAP2_vap13) & M_DLRX_CFG_VAP2INT_MAP2_vap13);    \
	} while (0)

#define DLRX_CFG_VAP2INT_MAP2_vap13_clear_indirect(base, offset)	((*(base + O_DLRX_CFG_VAP2INT_MAP2_vap13 + offset)) &= (~(M_DLRX_CFG_VAP2INT_MAP2_vap13)))

#define DLRX_CFG_VAP2INT_MAP2_vap13_clear_direct(dword)	((dword) &= (~(M_DLRX_CFG_VAP2INT_MAP2_vap13)))

#define O_DLRX_CFG_VAP2INT_MAP2_vap14 0
#define B_DLRX_CFG_VAP2INT_MAP2_vap14 24
#define W_DLRX_CFG_VAP2INT_MAP2_vap14 4
#define M_DLRX_CFG_VAP2INT_MAP2_vap14 0x0f000000

#define DLRX_CFG_VAP2INT_MAP2_vap14_get_indirect(base, offset)	((((*(base + O_DLRX_CFG_VAP2INT_MAP2_vap14 + offset)) & M_DLRX_CFG_VAP2INT_MAP2_vap14) >> B_DLRX_CFG_VAP2INT_MAP2_vap14))

#define DLRX_CFG_VAP2INT_MAP2_vap14_get_direct(dword)	((((dword) & M_DLRX_CFG_VAP2INT_MAP2_vap14) >> B_DLRX_CFG_VAP2INT_MAP2_vap14))

#define DLRX_CFG_VAP2INT_MAP2_vap14_set_indirect(base, offset, val) \
	do {                                                              \
		(*(base + O_DLRX_CFG_VAP2INT_MAP2_vap14 + offset)) &= (~(M_DLRX_CFG_VAP2INT_MAP2_vap14));    \
		(*(base + O_DLRX_CFG_VAP2INT_MAP2_vap14 + offset)) |= ((val << B_DLRX_CFG_VAP2INT_MAP2_vap14) & M_DLRX_CFG_VAP2INT_MAP2_vap14);    \
	} while (0)

#define DLRX_CFG_VAP2INT_MAP2_vap14_set_direct(dword, val) \
	do {                                                               \
		(dword) &= (~(M_DLRX_CFG_VAP2INT_MAP2_vap14));    \
		(dword) |= ((val << B_DLRX_CFG_VAP2INT_MAP2_vap14) & M_DLRX_CFG_VAP2INT_MAP2_vap14);    \
	} while (0)

#define DLRX_CFG_VAP2INT_MAP2_vap14_clear_indirect(base, offset)	((*(base + O_DLRX_CFG_VAP2INT_MAP2_vap14 + offset)) &= (~(M_DLRX_CFG_VAP2INT_MAP2_vap14)))

#define DLRX_CFG_VAP2INT_MAP2_vap14_clear_direct(dword)	((dword) &= (~(M_DLRX_CFG_VAP2INT_MAP2_vap14)))

#define O_DLRX_CFG_VAP2INT_MAP2_vap15 0
#define B_DLRX_CFG_VAP2INT_MAP2_vap15 28
#define W_DLRX_CFG_VAP2INT_MAP2_vap15 4
#define M_DLRX_CFG_VAP2INT_MAP2_vap15 0xf0000000

#define DLRX_CFG_VAP2INT_MAP2_vap15_get_indirect(base, offset)	((((*(base + O_DLRX_CFG_VAP2INT_MAP2_vap15 + offset)) & M_DLRX_CFG_VAP2INT_MAP2_vap15) >> B_DLRX_CFG_VAP2INT_MAP2_vap15))

#define DLRX_CFG_VAP2INT_MAP2_vap15_get_direct(dword)	((((dword) & M_DLRX_CFG_VAP2INT_MAP2_vap15) >> B_DLRX_CFG_VAP2INT_MAP2_vap15))

#define DLRX_CFG_VAP2INT_MAP2_vap15_set_indirect(base, offset, val) \
	do {                                                              \
		(*(base + O_DLRX_CFG_VAP2INT_MAP2_vap15 + offset)) &= (~(M_DLRX_CFG_VAP2INT_MAP2_vap15));    \
		(*(base + O_DLRX_CFG_VAP2INT_MAP2_vap15 + offset)) |= ((val << B_DLRX_CFG_VAP2INT_MAP2_vap15) & M_DLRX_CFG_VAP2INT_MAP2_vap15);    \
	} while (0)

#define DLRX_CFG_VAP2INT_MAP2_vap15_set_direct(dword, val) \
	do {                                                               \
		(dword) &= (~(M_DLRX_CFG_VAP2INT_MAP2_vap15));    \
		(dword) |= ((val << B_DLRX_CFG_VAP2INT_MAP2_vap15) & M_DLRX_CFG_VAP2INT_MAP2_vap15);    \
	} while (0)

#define DLRX_CFG_VAP2INT_MAP2_vap15_clear_indirect(base, offset)	((*(base + O_DLRX_CFG_VAP2INT_MAP2_vap15 + offset)) &= (~(M_DLRX_CFG_VAP2INT_MAP2_vap15)))

#define DLRX_CFG_VAP2INT_MAP2_vap15_clear_direct(dword)	((dword) &= (~(M_DLRX_CFG_VAP2INT_MAP2_vap15)))

#define O_DLRX_RXPB_PTR_RING_rxpb_ptr 0
#define B_DLRX_RXPB_PTR_RING_rxpb_ptr 0
#define W_DLRX_RXPB_PTR_RING_rxpb_ptr 32
#define M_DLRX_RXPB_PTR_RING_rxpb_ptr 0xffffffff

#define DLRX_RXPB_PTR_RING_rxpb_ptr_get_indirect(base, offset)	((((*(base + O_DLRX_RXPB_PTR_RING_rxpb_ptr + offset)) & M_DLRX_RXPB_PTR_RING_rxpb_ptr) >> B_DLRX_RXPB_PTR_RING_rxpb_ptr))

#define DLRX_RXPB_PTR_RING_rxpb_ptr_get_direct(dword)	((((dword) & M_DLRX_RXPB_PTR_RING_rxpb_ptr) >> B_DLRX_RXPB_PTR_RING_rxpb_ptr))

#define DLRX_RXPB_PTR_RING_rxpb_ptr_set_indirect(base, offset, val)    \
	do {                                                              \
		(*(base + O_DLRX_RXPB_PTR_RING_rxpb_ptr + offset)) &= (~(M_DLRX_RXPB_PTR_RING_rxpb_ptr));    \
		(*(base + O_DLRX_RXPB_PTR_RING_rxpb_ptr + offset)) |= ((val << B_DLRX_RXPB_PTR_RING_rxpb_ptr) & M_DLRX_RXPB_PTR_RING_rxpb_ptr);    \
	} while (0)

#define DLRX_RXPB_PTR_RING_rxpb_ptr_set_direct(dword, val)    \
	do {                                                               \
		(dword) &= (~(M_DLRX_RXPB_PTR_RING_rxpb_ptr));    \
		(dword) |= ((val << B_DLRX_RXPB_PTR_RING_rxpb_ptr) & M_DLRX_RXPB_PTR_RING_rxpb_ptr);    \
	} while (0)

#define DLRX_RXPB_PTR_RING_rxpb_ptr_clear_indirect(base, offset)	((*(base + O_DLRX_RXPB_PTR_RING_rxpb_ptr + offset)) &= (~(M_DLRX_RXPB_PTR_RING_rxpb_ptr)))

#define DLRX_RXPB_PTR_RING_rxpb_ptr_clear_direct(dword)	((dword) &= (~(M_DLRX_RXPB_PTR_RING_rxpb_ptr)))

#define O_DLRX_DMA_DES_data_len 0
#define B_DLRX_DMA_DES_data_len 0
#define W_DLRX_DMA_DES_data_len 16
#define M_DLRX_DMA_DES_data_len 0x0000ffff

#define DLRX_DMA_DES_data_len_get_indirect(base, offset)	((((*(base + O_DLRX_DMA_DES_data_len + offset)) & M_DLRX_DMA_DES_data_len) >> B_DLRX_DMA_DES_data_len))

#define DLRX_DMA_DES_data_len_get_direct(dword)	((((dword) & M_DLRX_DMA_DES_data_len) >> B_DLRX_DMA_DES_data_len))

#define DLRX_DMA_DES_data_len_set_indirect(base, offset, val) \
	do {                                                              \
		(*(base + O_DLRX_DMA_DES_data_len + offset)) &= (~(M_DLRX_DMA_DES_data_len));    \
		(*(base + O_DLRX_DMA_DES_data_len + offset)) |= ((val << B_DLRX_DMA_DES_data_len) & M_DLRX_DMA_DES_data_len);    \
	} while (0)

#define DLRX_DMA_DES_data_len_set_direct(dword, val) \
	do {                                                               \
		(dword) &= (~(M_DLRX_DMA_DES_data_len));    \
		(dword) |= ((val << B_DLRX_DMA_DES_data_len) & M_DLRX_DMA_DES_data_len);    \
	} while (0)

#define DLRX_DMA_DES_data_len_clear_indirect(base, offset)	((*(base + O_DLRX_DMA_DES_data_len + offset)) &= (~(M_DLRX_DMA_DES_data_len)))

#define DLRX_DMA_DES_data_len_clear_direct(dword)	((dword) &= (~(M_DLRX_DMA_DES_data_len)))

#define O_DLRX_DMA_DES_byte_off 0
#define B_DLRX_DMA_DES_byte_off 23
#define W_DLRX_DMA_DES_byte_off 2
#define M_DLRX_DMA_DES_byte_off 0x01800000

#define DLRX_DMA_DES_byte_off_get_indirect(base, offset)	((((*(base + O_DLRX_DMA_DES_byte_off + offset)) & M_DLRX_DMA_DES_byte_off) >> B_DLRX_DMA_DES_byte_off))

#define DLRX_DMA_DES_byte_off_get_direct(dword)	((((dword) & M_DLRX_DMA_DES_byte_off) >> B_DLRX_DMA_DES_byte_off))

#define DLRX_DMA_DES_byte_off_set_indirect(base, offset, val) \
	do {                                                              \
		(*(base + O_DLRX_DMA_DES_byte_off + offset)) &= (~(M_DLRX_DMA_DES_byte_off));    \
		(*(base + O_DLRX_DMA_DES_byte_off + offset)) |= ((val << B_DLRX_DMA_DES_byte_off) & M_DLRX_DMA_DES_byte_off);    \
	} while (0)

#define DLRX_DMA_DES_byte_off_set_direct(dword, val) \
	do {                                                               \
		(dword) &= (~(M_DLRX_DMA_DES_byte_off));    \
		(dword) |= ((val << B_DLRX_DMA_DES_byte_off) & M_DLRX_DMA_DES_byte_off);    \
	} while (0)

#define DLRX_DMA_DES_byte_off_clear_indirect(base, offset)	((*(base + O_DLRX_DMA_DES_byte_off + offset)) &= (~(M_DLRX_DMA_DES_byte_off)))

#define DLRX_DMA_DES_byte_off_clear_direct(dword)	((dword) &= (~(M_DLRX_DMA_DES_byte_off)))

#define O_DLRX_DMA_DES_eop 0
#define B_DLRX_DMA_DES_eop 28
#define W_DLRX_DMA_DES_eop 1
#define M_DLRX_DMA_DES_eop 0x10000000

#define DLRX_DMA_DES_eop_get_indirect(base, offset)	((((*(base + O_DLRX_DMA_DES_eop + offset)) & M_DLRX_DMA_DES_eop) >> B_DLRX_DMA_DES_eop))

#define DLRX_DMA_DES_eop_get_direct(dword)	((((dword) & M_DLRX_DMA_DES_eop) >> B_DLRX_DMA_DES_eop))

#define DLRX_DMA_DES_eop_set_indirect(base, offset, val) \
	do {                                                              \
		(*(base + O_DLRX_DMA_DES_eop + offset)) &= (~(M_DLRX_DMA_DES_eop));    \
		(*(base + O_DLRX_DMA_DES_eop + offset)) |= ((val << B_DLRX_DMA_DES_eop) & M_DLRX_DMA_DES_eop);    \
	} while (0)

#define DLRX_DMA_DES_eop_set_direct(dword, val) \
	do {                                                               \
		(dword) &= (~(M_DLRX_DMA_DES_eop));    \
		(dword) |= ((val << B_DLRX_DMA_DES_eop) & M_DLRX_DMA_DES_eop);    \
	} while (0)

#define DLRX_DMA_DES_eop_clear_indirect(base, offset)	((*(base + O_DLRX_DMA_DES_eop + offset)) &= (~(M_DLRX_DMA_DES_eop)))

#define DLRX_DMA_DES_eop_clear_direct(dword)	((dword) &= (~(M_DLRX_DMA_DES_eop)))

#define O_DLRX_DMA_DES_sop 0
#define B_DLRX_DMA_DES_sop 29
#define W_DLRX_DMA_DES_sop 1
#define M_DLRX_DMA_DES_sop 0x20000000

#define DLRX_DMA_DES_sop_get_indirect(base, offset)	((((*(base + O_DLRX_DMA_DES_sop + offset)) & M_DLRX_DMA_DES_sop) >> B_DLRX_DMA_DES_sop))

#define DLRX_DMA_DES_sop_get_direct(dword)	((((dword) & M_DLRX_DMA_DES_sop) >> B_DLRX_DMA_DES_sop))

#define DLRX_DMA_DES_sop_set_indirect(base, offset, val) \
	do {                                                              \
		(*(base + O_DLRX_DMA_DES_sop + offset)) &= (~(M_DLRX_DMA_DES_sop));    \
		(*(base + O_DLRX_DMA_DES_sop + offset)) |= ((val << B_DLRX_DMA_DES_sop) & M_DLRX_DMA_DES_sop);    \
	} while (0)

#define DLRX_DMA_DES_sop_set_direct(dword, val) \
	do {                                                               \
		(dword) &= (~(M_DLRX_DMA_DES_sop));    \
		(dword) |= ((val << B_DLRX_DMA_DES_sop) & M_DLRX_DMA_DES_sop);    \
	} while (0)

#define DLRX_DMA_DES_sop_clear_indirect(base, offset)	((*(base + O_DLRX_DMA_DES_sop + offset)) &= (~(M_DLRX_DMA_DES_sop)))

#define DLRX_DMA_DES_sop_clear_direct(dword)	((dword) &= (~(M_DLRX_DMA_DES_sop)))

#define O_DLRX_DMA_DES_c 0
#define B_DLRX_DMA_DES_c 30
#define W_DLRX_DMA_DES_c 1
#define M_DLRX_DMA_DES_c 0x40000000

#define DLRX_DMA_DES_c_get_indirect(base, offset)	((((*(base + O_DLRX_DMA_DES_c + offset)) & M_DLRX_DMA_DES_c) >> B_DLRX_DMA_DES_c))

#define DLRX_DMA_DES_c_get_direct(dword)	((((dword) & M_DLRX_DMA_DES_c) >> B_DLRX_DMA_DES_c))

#define DLRX_DMA_DES_c_set_indirect(base, offset, val) \
	do {                                                              \
		(*(base + O_DLRX_DMA_DES_c + offset)) &= (~(M_DLRX_DMA_DES_c));    \
		(*(base + O_DLRX_DMA_DES_c + offset)) |= ((val << B_DLRX_DMA_DES_c) & M_DLRX_DMA_DES_c);    \
	} while (0)

#define DLRX_DMA_DES_c_set_direct(dword, val) \
	do {                                                               \
		(dword) &= (~(M_DLRX_DMA_DES_c));    \
		(dword) |= ((val << B_DLRX_DMA_DES_c) & M_DLRX_DMA_DES_c);    \
	} while (0)

#define DLRX_DMA_DES_c_clear_indirect(base, offset)	((*(base + O_DLRX_DMA_DES_c + offset)) &= (~(M_DLRX_DMA_DES_c)))

#define DLRX_DMA_DES_c_clear_direct(dword)	((dword) &= (~(M_DLRX_DMA_DES_c)))

#define O_DLRX_DMA_DES_own 0
#define B_DLRX_DMA_DES_own 31
#define W_DLRX_DMA_DES_own 1
#define M_DLRX_DMA_DES_own 0x80000000

#define DLRX_DMA_DES_own_get_indirect(base, offset)	((((*(base + O_DLRX_DMA_DES_own + offset)) & M_DLRX_DMA_DES_own) >> B_DLRX_DMA_DES_own))

#define DLRX_DMA_DES_own_get_direct(dword)	((((dword) & M_DLRX_DMA_DES_own) >> B_DLRX_DMA_DES_own))

#define DLRX_DMA_DES_own_set_indirect(base, offset, val) \
	do {                                                              \
		(*(base + O_DLRX_DMA_DES_own + offset)) &= (~(M_DLRX_DMA_DES_own));    \
		(*(base + O_DLRX_DMA_DES_own + offset)) |= ((val << B_DLRX_DMA_DES_own) & M_DLRX_DMA_DES_own);    \
	} while (0)

#define DLRX_DMA_DES_own_set_direct(dword, val) \
	do {                                                               \
		(dword) &= (~(M_DLRX_DMA_DES_own));    \
		(dword) |= ((val << B_DLRX_DMA_DES_own) & M_DLRX_DMA_DES_own);    \
	} while (0)

#define DLRX_DMA_DES_own_clear_indirect(base, offset)	((*(base + O_DLRX_DMA_DES_own + offset)) &= (~(M_DLRX_DMA_DES_own)))

#define DLRX_DMA_DES_own_clear_direct(dword)	((dword) &= (~(M_DLRX_DMA_DES_own)))

#define O_DLRX_DMA_DES_data_ptr_rel 1
#define B_DLRX_DMA_DES_data_ptr_rel 0
#define W_DLRX_DMA_DES_data_ptr_rel 1
#define M_DLRX_DMA_DES_data_ptr_rel 0x00000001

#define DLRX_DMA_DES_data_ptr_rel_get_indirect(base, offset)	((((*(base + O_DLRX_DMA_DES_data_ptr_rel + offset)) & M_DLRX_DMA_DES_data_ptr_rel) >> B_DLRX_DMA_DES_data_ptr_rel))

#define DLRX_DMA_DES_data_ptr_rel_get_direct(dword)	((((dword) & M_DLRX_DMA_DES_data_ptr_rel) >> B_DLRX_DMA_DES_data_ptr_rel))

#define DLRX_DMA_DES_data_ptr_rel_set_indirect(base, offset, val) \
	do {                                                              \
		(*(base + O_DLRX_DMA_DES_data_ptr_rel + offset)) &= (~(M_DLRX_DMA_DES_data_ptr_rel));    \
		(*(base + O_DLRX_DMA_DES_data_ptr_rel + offset)) |= ((val << B_DLRX_DMA_DES_data_ptr_rel) & M_DLRX_DMA_DES_data_ptr_rel);    \
	} while (0)

#define DLRX_DMA_DES_data_ptr_rel_set_direct(dword, val) \
	do {                                                               \
		(dword) &= (~(M_DLRX_DMA_DES_data_ptr_rel));    \
		(dword) |= ((val << B_DLRX_DMA_DES_data_ptr_rel) & M_DLRX_DMA_DES_data_ptr_rel);    \
	} while (0)

#define DLRX_DMA_DES_data_ptr_rel_clear_indirect(base, offset)	((*(base + O_DLRX_DMA_DES_data_ptr_rel + offset)) &= (~(M_DLRX_DMA_DES_data_ptr_rel)))

#define DLRX_DMA_DES_data_ptr_rel_clear_direct(dword)	((dword) &= (~(M_DLRX_DMA_DES_data_ptr_rel)))

#define O_DLRX_DMA_DES_data_ptr 1
#define B_DLRX_DMA_DES_data_ptr 3
#define W_DLRX_DMA_DES_data_ptr 27
#define M_DLRX_DMA_DES_data_ptr 0x3ffffff8

#define DLRX_DMA_DES_data_ptr_get_indirect(base, offset)	((((*(base + O_DLRX_DMA_DES_data_ptr + offset)) & M_DLRX_DMA_DES_data_ptr) >> B_DLRX_DMA_DES_data_ptr))

#define DLRX_DMA_DES_data_ptr_get_direct(dword)	((((dword) & M_DLRX_DMA_DES_data_ptr) >> B_DLRX_DMA_DES_data_ptr))

#define DLRX_DMA_DES_data_ptr_set_indirect(base, offset, val) \
	do {                                                              \
		(*(base + O_DLRX_DMA_DES_data_ptr + offset)) &= (~(M_DLRX_DMA_DES_data_ptr));    \
		(*(base + O_DLRX_DMA_DES_data_ptr + offset)) |= ((val << B_DLRX_DMA_DES_data_ptr) & M_DLRX_DMA_DES_data_ptr);    \
	} while (0)

#define DLRX_DMA_DES_data_ptr_set_direct(dword, val) \
	do {                                                               \
		(dword) &= (~(M_DLRX_DMA_DES_data_ptr));    \
		(dword) |= ((val << B_DLRX_DMA_DES_data_ptr) & M_DLRX_DMA_DES_data_ptr);    \
	} while (0)

#define DLRX_DMA_DES_data_ptr_clear_indirect(base, offset)	((*(base + O_DLRX_DMA_DES_data_ptr + offset)) &= (~(M_DLRX_DMA_DES_data_ptr)))

#define DLRX_DMA_DES_data_ptr_clear_direct(dword)	((dword) &= (~(M_DLRX_DMA_DES_data_ptr)))

#define O_DLRX_CFG_CTXT_DMA_cfg_badr_dma 0
#define B_DLRX_CFG_CTXT_DMA_cfg_badr_dma 0
#define W_DLRX_CFG_CTXT_DMA_cfg_badr_dma 32
#define M_DLRX_CFG_CTXT_DMA_cfg_badr_dma 0xffffffff

#define DLRX_CFG_CTXT_DMA_cfg_badr_dma_get_indirect(base, offset)	((((*(base + O_DLRX_CFG_CTXT_DMA_cfg_badr_dma + offset)) & M_DLRX_CFG_CTXT_DMA_cfg_badr_dma) >> B_DLRX_CFG_CTXT_DMA_cfg_badr_dma))

#define DLRX_CFG_CTXT_DMA_cfg_badr_dma_get_direct(dword)	((((dword) & M_DLRX_CFG_CTXT_DMA_cfg_badr_dma) >> B_DLRX_CFG_CTXT_DMA_cfg_badr_dma))

#define DLRX_CFG_CTXT_DMA_cfg_badr_dma_set_indirect(base, offset, val)    \
	do {                                                              \
		(*(base + O_DLRX_CFG_CTXT_DMA_cfg_badr_dma + offset)) &= (~(M_DLRX_CFG_CTXT_DMA_cfg_badr_dma));    \
		(*(base + O_DLRX_CFG_CTXT_DMA_cfg_badr_dma + offset)) |= ((val << B_DLRX_CFG_CTXT_DMA_cfg_badr_dma) & M_DLRX_CFG_CTXT_DMA_cfg_badr_dma);    \
	} while (0)

#define DLRX_CFG_CTXT_DMA_cfg_badr_dma_set_direct(dword, val)    \
	do {                                                               \
		(dword) &= (~(M_DLRX_CFG_CTXT_DMA_cfg_badr_dma));    \
		(dword) |= ((val << B_DLRX_CFG_CTXT_DMA_cfg_badr_dma) & M_DLRX_CFG_CTXT_DMA_cfg_badr_dma);    \
	} while (0)

#define DLRX_CFG_CTXT_DMA_cfg_badr_dma_clear_indirect(base, offset)	((*(base + O_DLRX_CFG_CTXT_DMA_cfg_badr_dma + offset)) &= (~(M_DLRX_CFG_CTXT_DMA_cfg_badr_dma)))

#define DLRX_CFG_CTXT_DMA_cfg_badr_dma_clear_direct(dword)	((dword) &= (~(M_DLRX_CFG_CTXT_DMA_cfg_badr_dma)))

#define O_DLRX_CFG_CTXT_DMA_cfg_num_dma 1
#define B_DLRX_CFG_CTXT_DMA_cfg_num_dma 0
#define W_DLRX_CFG_CTXT_DMA_cfg_num_dma 32
#define M_DLRX_CFG_CTXT_DMA_cfg_num_dma 0xffffffff

#define DLRX_CFG_CTXT_DMA_cfg_num_dma_get_indirect(base, offset)	((((*(base + O_DLRX_CFG_CTXT_DMA_cfg_num_dma + offset)) & M_DLRX_CFG_CTXT_DMA_cfg_num_dma) >> B_DLRX_CFG_CTXT_DMA_cfg_num_dma))

#define DLRX_CFG_CTXT_DMA_cfg_num_dma_get_direct(dword)	((((dword) & M_DLRX_CFG_CTXT_DMA_cfg_num_dma) >> B_DLRX_CFG_CTXT_DMA_cfg_num_dma))

#define DLRX_CFG_CTXT_DMA_cfg_num_dma_set_indirect(base, offset, val)    \
	do {                                                              \
		(*(base + O_DLRX_CFG_CTXT_DMA_cfg_num_dma + offset)) &= (~(M_DLRX_CFG_CTXT_DMA_cfg_num_dma));    \
		(*(base + O_DLRX_CFG_CTXT_DMA_cfg_num_dma + offset)) |= ((val << B_DLRX_CFG_CTXT_DMA_cfg_num_dma) & M_DLRX_CFG_CTXT_DMA_cfg_num_dma);    \
	} while (0)

#define DLRX_CFG_CTXT_DMA_cfg_num_dma_set_direct(dword, val)    \
	do {                                                               \
		(dword) &= (~(M_DLRX_CFG_CTXT_DMA_cfg_num_dma));    \
		(dword) |= ((val << B_DLRX_CFG_CTXT_DMA_cfg_num_dma) & M_DLRX_CFG_CTXT_DMA_cfg_num_dma);    \
	} while (0)

#define DLRX_CFG_CTXT_DMA_cfg_num_dma_clear_indirect(base, offset)	((*(base + O_DLRX_CFG_CTXT_DMA_cfg_num_dma + offset)) &= (~(M_DLRX_CFG_CTXT_DMA_cfg_num_dma)))

#define DLRX_CFG_CTXT_DMA_cfg_num_dma_clear_direct(dword)	((dword) &= (~(M_DLRX_CFG_CTXT_DMA_cfg_num_dma)))

#define O_DLRX_CFG_CTXT_DMA_txdes_index 2
#define B_DLRX_CFG_CTXT_DMA_txdes_index 0
#define W_DLRX_CFG_CTXT_DMA_txdes_index 32
#define M_DLRX_CFG_CTXT_DMA_txdes_index 0xffffffff

#define DLRX_CFG_CTXT_DMA_txdes_index_get_indirect(base, offset)	((((*(base + O_DLRX_CFG_CTXT_DMA_txdes_index + offset)) & M_DLRX_CFG_CTXT_DMA_txdes_index) >> B_DLRX_CFG_CTXT_DMA_txdes_index))

#define DLRX_CFG_CTXT_DMA_txdes_index_get_direct(dword)	((((dword) & M_DLRX_CFG_CTXT_DMA_txdes_index) >> B_DLRX_CFG_CTXT_DMA_txdes_index))

#define DLRX_CFG_CTXT_DMA_txdes_index_set_indirect(base, offset, val)    \
	do {                                                              \
		(*(base + O_DLRX_CFG_CTXT_DMA_txdes_index + offset)) &= (~(M_DLRX_CFG_CTXT_DMA_txdes_index));    \
		(*(base + O_DLRX_CFG_CTXT_DMA_txdes_index + offset)) |= ((val << B_DLRX_CFG_CTXT_DMA_txdes_index) & M_DLRX_CFG_CTXT_DMA_txdes_index);    \
	} while (0)

#define DLRX_CFG_CTXT_DMA_txdes_index_set_direct(dword, val)    \
	do {                                                               \
		(dword) &= (~(M_DLRX_CFG_CTXT_DMA_txdes_index));    \
		(dword) |= ((val << B_DLRX_CFG_CTXT_DMA_txdes_index) & M_DLRX_CFG_CTXT_DMA_txdes_index);    \
	} while (0)

#define DLRX_CFG_CTXT_DMA_txdes_index_clear_indirect(base, offset)	((*(base + O_DLRX_CFG_CTXT_DMA_txdes_index + offset)) &= (~(M_DLRX_CFG_CTXT_DMA_txdes_index)))

#define DLRX_CFG_CTXT_DMA_txdes_index_clear_direct(dword)	((dword) &= (~(M_DLRX_CFG_CTXT_DMA_txdes_index)))

#define O_DLRX_CFG_CTXT_DMA_rsvd0 3
#define B_DLRX_CFG_CTXT_DMA_rsvd0 0
#define W_DLRX_CFG_CTXT_DMA_rsvd0 32
#define M_DLRX_CFG_CTXT_DMA_rsvd0 0xffffffff

#define DLRX_CFG_CTXT_DMA_rsvd0_get_indirect(base, offset)	((((*(base + O_DLRX_CFG_CTXT_DMA_rsvd0 + offset)) & M_DLRX_CFG_CTXT_DMA_rsvd0) >> B_DLRX_CFG_CTXT_DMA_rsvd0))

#define DLRX_CFG_CTXT_DMA_rsvd0_get_direct(dword)	((((dword) & M_DLRX_CFG_CTXT_DMA_rsvd0) >> B_DLRX_CFG_CTXT_DMA_rsvd0))

#define DLRX_CFG_CTXT_DMA_rsvd0_set_indirect(base, offset, val)    \
	do {                                                              \
		(*(base + O_DLRX_CFG_CTXT_DMA_rsvd0 + offset)) &= (~(M_DLRX_CFG_CTXT_DMA_rsvd0));    \
		(*(base + O_DLRX_CFG_CTXT_DMA_rsvd0 + offset)) |= ((val << B_DLRX_CFG_CTXT_DMA_rsvd0) & M_DLRX_CFG_CTXT_DMA_rsvd0);    \
	} while (0)

#define DLRX_CFG_CTXT_DMA_rsvd0_set_direct(dword, val)    \
	do {                                                               \
		(dword) &= (~(M_DLRX_CFG_CTXT_DMA_rsvd0));    \
		(dword) |= ((val << B_DLRX_CFG_CTXT_DMA_rsvd0) & M_DLRX_CFG_CTXT_DMA_rsvd0);    \
	} while (0)

#define DLRX_CFG_CTXT_DMA_rsvd0_clear_indirect(base, offset)	((*(base + O_DLRX_CFG_CTXT_DMA_rsvd0 + offset)) &= (~(M_DLRX_CFG_CTXT_DMA_rsvd0)))

#define DLRX_CFG_CTXT_DMA_rsvd0_clear_direct(dword)	((dword) &= (~(M_DLRX_CFG_CTXT_DMA_rsvd0)))

#define O_DLRX_CFG_CTXT_CE5BUF_cfg_badr_ce5buf 0
#define B_DLRX_CFG_CTXT_CE5BUF_cfg_badr_ce5buf 0
#define W_DLRX_CFG_CTXT_CE5BUF_cfg_badr_ce5buf 32
#define M_DLRX_CFG_CTXT_CE5BUF_cfg_badr_ce5buf 0xffffffff

#define DLRX_CFG_CTXT_CE5BUF_cfg_badr_ce5buf_get_indirect(base, offset)	((((*(base + O_DLRX_CFG_CTXT_CE5BUF_cfg_badr_ce5buf + offset)) & M_DLRX_CFG_CTXT_CE5BUF_cfg_badr_ce5buf) >> B_DLRX_CFG_CTXT_CE5BUF_cfg_badr_ce5buf))

#define DLRX_CFG_CTXT_CE5BUF_cfg_badr_ce5buf_get_direct(dword)	((((dword) & M_DLRX_CFG_CTXT_CE5BUF_cfg_badr_ce5buf) >> B_DLRX_CFG_CTXT_CE5BUF_cfg_badr_ce5buf))

#define DLRX_CFG_CTXT_CE5BUF_cfg_badr_ce5buf_set_indirect(base, offset, val)    \
	do {                                                              \
		(*(base + O_DLRX_CFG_CTXT_CE5BUF_cfg_badr_ce5buf + offset)) &= (~(M_DLRX_CFG_CTXT_CE5BUF_cfg_badr_ce5buf));    \
		(*(base + O_DLRX_CFG_CTXT_CE5BUF_cfg_badr_ce5buf + offset)) |= ((val << B_DLRX_CFG_CTXT_CE5BUF_cfg_badr_ce5buf) & M_DLRX_CFG_CTXT_CE5BUF_cfg_badr_ce5buf);    \
	} while (0)

#define DLRX_CFG_CTXT_CE5BUF_cfg_badr_ce5buf_set_direct(dword, val)    \
	do {                                                               \
		(dword) &= (~(M_DLRX_CFG_CTXT_CE5BUF_cfg_badr_ce5buf));    \
		(dword) |= ((val << B_DLRX_CFG_CTXT_CE5BUF_cfg_badr_ce5buf) & M_DLRX_CFG_CTXT_CE5BUF_cfg_badr_ce5buf);    \
	} while (0)

#define DLRX_CFG_CTXT_CE5BUF_cfg_badr_ce5buf_clear_indirect(base, offset)	((*(base + O_DLRX_CFG_CTXT_CE5BUF_cfg_badr_ce5buf + offset)) &= (~(M_DLRX_CFG_CTXT_CE5BUF_cfg_badr_ce5buf)))

#define DLRX_CFG_CTXT_CE5BUF_cfg_badr_ce5buf_clear_direct(dword)	((dword) &= (~(M_DLRX_CFG_CTXT_CE5BUF_cfg_badr_ce5buf)))

#define O_DLRX_CFG_CTXT_CE5BUF_cfg_num_ce5buf 1
#define B_DLRX_CFG_CTXT_CE5BUF_cfg_num_ce5buf 0
#define W_DLRX_CFG_CTXT_CE5BUF_cfg_num_ce5buf 32
#define M_DLRX_CFG_CTXT_CE5BUF_cfg_num_ce5buf 0xffffffff

#define DLRX_CFG_CTXT_CE5BUF_cfg_num_ce5buf_get_indirect(base, offset)	((((*(base + O_DLRX_CFG_CTXT_CE5BUF_cfg_num_ce5buf + offset)) & M_DLRX_CFG_CTXT_CE5BUF_cfg_num_ce5buf) >> B_DLRX_CFG_CTXT_CE5BUF_cfg_num_ce5buf))

#define DLRX_CFG_CTXT_CE5BUF_cfg_num_ce5buf_get_direct(dword)	((((dword) & M_DLRX_CFG_CTXT_CE5BUF_cfg_num_ce5buf) >> B_DLRX_CFG_CTXT_CE5BUF_cfg_num_ce5buf))

#define DLRX_CFG_CTXT_CE5BUF_cfg_num_ce5buf_set_indirect(base, offset, val)    \
	do {                                                              \
		(*(base + O_DLRX_CFG_CTXT_CE5BUF_cfg_num_ce5buf + offset)) &= (~(M_DLRX_CFG_CTXT_CE5BUF_cfg_num_ce5buf));    \
		(*(base + O_DLRX_CFG_CTXT_CE5BUF_cfg_num_ce5buf + offset)) |= ((val << B_DLRX_CFG_CTXT_CE5BUF_cfg_num_ce5buf) & M_DLRX_CFG_CTXT_CE5BUF_cfg_num_ce5buf);    \
	} while (0)

#define DLRX_CFG_CTXT_CE5BUF_cfg_num_ce5buf_set_direct(dword, val)    \
	do {                                                               \
		(dword) &= (~(M_DLRX_CFG_CTXT_CE5BUF_cfg_num_ce5buf));    \
		(dword) |= ((val << B_DLRX_CFG_CTXT_CE5BUF_cfg_num_ce5buf) & M_DLRX_CFG_CTXT_CE5BUF_cfg_num_ce5buf);    \
	} while (0)

#define DLRX_CFG_CTXT_CE5BUF_cfg_num_ce5buf_clear_indirect(base, offset)	((*(base + O_DLRX_CFG_CTXT_CE5BUF_cfg_num_ce5buf + offset)) &= (~(M_DLRX_CFG_CTXT_CE5BUF_cfg_num_ce5buf)))

#define DLRX_CFG_CTXT_CE5BUF_cfg_num_ce5buf_clear_direct(dword)	((dword) &= (~(M_DLRX_CFG_CTXT_CE5BUF_cfg_num_ce5buf)))

#define O_DLRX_CFG_CTXT_CE5BUF_cfg_size_ce5buf 2
#define B_DLRX_CFG_CTXT_CE5BUF_cfg_size_ce5buf 0
#define W_DLRX_CFG_CTXT_CE5BUF_cfg_size_ce5buf 32
#define M_DLRX_CFG_CTXT_CE5BUF_cfg_size_ce5buf 0xffffffff

#define DLRX_CFG_CTXT_CE5BUF_cfg_size_ce5buf_get_indirect(base, offset)	((((*(base + O_DLRX_CFG_CTXT_CE5BUF_cfg_size_ce5buf + offset)) & M_DLRX_CFG_CTXT_CE5BUF_cfg_size_ce5buf) >> B_DLRX_CFG_CTXT_CE5BUF_cfg_size_ce5buf))

#define DLRX_CFG_CTXT_CE5BUF_cfg_size_ce5buf_get_direct(dword)	((((dword) & M_DLRX_CFG_CTXT_CE5BUF_cfg_size_ce5buf) >> B_DLRX_CFG_CTXT_CE5BUF_cfg_size_ce5buf))

#define DLRX_CFG_CTXT_CE5BUF_cfg_size_ce5buf_set_indirect(base, offset, val)    \
	do {                                                              \
		(*(base + O_DLRX_CFG_CTXT_CE5BUF_cfg_size_ce5buf + offset)) &= (~(M_DLRX_CFG_CTXT_CE5BUF_cfg_size_ce5buf));    \
		(*(base + O_DLRX_CFG_CTXT_CE5BUF_cfg_size_ce5buf + offset)) |= ((val << B_DLRX_CFG_CTXT_CE5BUF_cfg_size_ce5buf) & M_DLRX_CFG_CTXT_CE5BUF_cfg_size_ce5buf);    \
	} while (0)

#define DLRX_CFG_CTXT_CE5BUF_cfg_size_ce5buf_set_direct(dword, val)    \
	do {                                                               \
		(dword) &= (~(M_DLRX_CFG_CTXT_CE5BUF_cfg_size_ce5buf));    \
		(dword) |= ((val << B_DLRX_CFG_CTXT_CE5BUF_cfg_size_ce5buf) & M_DLRX_CFG_CTXT_CE5BUF_cfg_size_ce5buf);    \
	} while (0)

#define DLRX_CFG_CTXT_CE5BUF_cfg_size_ce5buf_clear_indirect(base, offset)	((*(base + O_DLRX_CFG_CTXT_CE5BUF_cfg_size_ce5buf + offset)) &= (~(M_DLRX_CFG_CTXT_CE5BUF_cfg_size_ce5buf)))

#define DLRX_CFG_CTXT_CE5BUF_cfg_size_ce5buf_clear_direct(dword)	((dword) &= (~(M_DLRX_CFG_CTXT_CE5BUF_cfg_size_ce5buf)))

#define O_DLRX_CFG_CTXT_CE5BUF_cfg_size_shift_ce5buf 3
#define B_DLRX_CFG_CTXT_CE5BUF_cfg_size_shift_ce5buf 0
#define W_DLRX_CFG_CTXT_CE5BUF_cfg_size_shift_ce5buf 32
#define M_DLRX_CFG_CTXT_CE5BUF_cfg_size_shift_ce5buf 0xffffffff

#define DLRX_CFG_CTXT_CE5BUF_cfg_size_shift_ce5buf_get_indirect(base, offset)	((((*(base + O_DLRX_CFG_CTXT_CE5BUF_cfg_size_shift_ce5buf + offset)) & M_DLRX_CFG_CTXT_CE5BUF_cfg_size_shift_ce5buf) >> B_DLRX_CFG_CTXT_CE5BUF_cfg_size_shift_ce5buf))

#define DLRX_CFG_CTXT_CE5BUF_cfg_size_shift_ce5buf_get_direct(dword)	((((dword) & M_DLRX_CFG_CTXT_CE5BUF_cfg_size_shift_ce5buf) >> B_DLRX_CFG_CTXT_CE5BUF_cfg_size_shift_ce5buf))

#define DLRX_CFG_CTXT_CE5BUF_cfg_size_shift_ce5buf_set_indirect(base, offset, val)    \
	do {                                                              \
		(*(base + O_DLRX_CFG_CTXT_CE5BUF_cfg_size_shift_ce5buf + offset)) &= (~(M_DLRX_CFG_CTXT_CE5BUF_cfg_size_shift_ce5buf));    \
		(*(base + O_DLRX_CFG_CTXT_CE5BUF_cfg_size_shift_ce5buf + offset)) |= ((val << B_DLRX_CFG_CTXT_CE5BUF_cfg_size_shift_ce5buf) & M_DLRX_CFG_CTXT_CE5BUF_cfg_size_shift_ce5buf);    \
	} while (0)

#define DLRX_CFG_CTXT_CE5BUF_cfg_size_shift_ce5buf_set_direct(dword, val)    \
	do {                                                               \
		(dword) &= (~(M_DLRX_CFG_CTXT_CE5BUF_cfg_size_shift_ce5buf));    \
		(dword) |= ((val << B_DLRX_CFG_CTXT_CE5BUF_cfg_size_shift_ce5buf) & M_DLRX_CFG_CTXT_CE5BUF_cfg_size_shift_ce5buf);    \
	} while (0)

#define DLRX_CFG_CTXT_CE5BUF_cfg_size_shift_ce5buf_clear_indirect(base, offset)	((*(base + O_DLRX_CFG_CTXT_CE5BUF_cfg_size_shift_ce5buf + offset)) &= (~(M_DLRX_CFG_CTXT_CE5BUF_cfg_size_shift_ce5buf)))

#define DLRX_CFG_CTXT_CE5BUF_cfg_size_shift_ce5buf_clear_direct(dword)	((dword) &= (~(M_DLRX_CFG_CTXT_CE5BUF_cfg_size_shift_ce5buf)))

#define O_DLRX_CFG_CTXT_CE5BUF_cfg_badr_target_ce5_read_index 4
#define B_DLRX_CFG_CTXT_CE5BUF_cfg_badr_target_ce5_read_index 0
#define W_DLRX_CFG_CTXT_CE5BUF_cfg_badr_target_ce5_read_index 32
#define M_DLRX_CFG_CTXT_CE5BUF_cfg_badr_target_ce5_read_index 0xffffffff

#define DLRX_CFG_CTXT_CE5BUF_cfg_badr_target_ce5_read_index_get_indirect(base, offset)	((((*(base + O_DLRX_CFG_CTXT_CE5BUF_cfg_badr_target_ce5_read_index + offset)) & M_DLRX_CFG_CTXT_CE5BUF_cfg_badr_target_ce5_read_index) >> B_DLRX_CFG_CTXT_CE5BUF_cfg_badr_target_ce5_read_index))

#define DLRX_CFG_CTXT_CE5BUF_cfg_badr_target_ce5_read_index_get_direct(dword)	((((dword) & M_DLRX_CFG_CTXT_CE5BUF_cfg_badr_target_ce5_read_index) >> B_DLRX_CFG_CTXT_CE5BUF_cfg_badr_target_ce5_read_index))

#define DLRX_CFG_CTXT_CE5BUF_cfg_badr_target_ce5_read_index_set_indirect(base, offset, val)    \
	do {                                                              \
		(*(base + O_DLRX_CFG_CTXT_CE5BUF_cfg_badr_target_ce5_read_index + offset)) &= (~(M_DLRX_CFG_CTXT_CE5BUF_cfg_badr_target_ce5_read_index));    \
		(*(base + O_DLRX_CFG_CTXT_CE5BUF_cfg_badr_target_ce5_read_index + offset)) |= ((val << B_DLRX_CFG_CTXT_CE5BUF_cfg_badr_target_ce5_read_index) & M_DLRX_CFG_CTXT_CE5BUF_cfg_badr_target_ce5_read_index);    \
	} while (0)

#define DLRX_CFG_CTXT_CE5BUF_cfg_badr_target_ce5_read_index_set_direct(dword, val)    \
	do {                                                               \
		(dword) &= (~(M_DLRX_CFG_CTXT_CE5BUF_cfg_badr_target_ce5_read_index));    \
		(dword) |= ((val << B_DLRX_CFG_CTXT_CE5BUF_cfg_badr_target_ce5_read_index) & M_DLRX_CFG_CTXT_CE5BUF_cfg_badr_target_ce5_read_index);    \
	} while (0)

#define DLRX_CFG_CTXT_CE5BUF_cfg_badr_target_ce5_read_index_clear_indirect(base, offset)	((*(base + O_DLRX_CFG_CTXT_CE5BUF_cfg_badr_target_ce5_read_index + offset)) &= (~(M_DLRX_CFG_CTXT_CE5BUF_cfg_badr_target_ce5_read_index)))

#define DLRX_CFG_CTXT_CE5BUF_cfg_badr_target_ce5_read_index_clear_direct(dword)	((dword) &= (~(M_DLRX_CFG_CTXT_CE5BUF_cfg_badr_target_ce5_read_index)))

#define O_DLRX_CFG_CTXT_CE5BUF_cfg_badr_target_ce5_write_index 5
#define B_DLRX_CFG_CTXT_CE5BUF_cfg_badr_target_ce5_write_index 0
#define W_DLRX_CFG_CTXT_CE5BUF_cfg_badr_target_ce5_write_index 32
#define M_DLRX_CFG_CTXT_CE5BUF_cfg_badr_target_ce5_write_index 0xffffffff

#define DLRX_CFG_CTXT_CE5BUF_cfg_badr_target_ce5_write_index_get_indirect(base, offset)	((((*(base + O_DLRX_CFG_CTXT_CE5BUF_cfg_badr_target_ce5_write_index + offset)) & M_DLRX_CFG_CTXT_CE5BUF_cfg_badr_target_ce5_write_index) >> B_DLRX_CFG_CTXT_CE5BUF_cfg_badr_target_ce5_write_index))

#define DLRX_CFG_CTXT_CE5BUF_cfg_badr_target_ce5_write_index_get_direct(dword)	((((dword) & M_DLRX_CFG_CTXT_CE5BUF_cfg_badr_target_ce5_write_index) >> B_DLRX_CFG_CTXT_CE5BUF_cfg_badr_target_ce5_write_index))

#define DLRX_CFG_CTXT_CE5BUF_cfg_badr_target_ce5_write_index_set_indirect(base, offset, val)    \
	do {                                                              \
		(*(base + O_DLRX_CFG_CTXT_CE5BUF_cfg_badr_target_ce5_write_index + offset)) &= (~(M_DLRX_CFG_CTXT_CE5BUF_cfg_badr_target_ce5_write_index));    \
		(*(base + O_DLRX_CFG_CTXT_CE5BUF_cfg_badr_target_ce5_write_index + offset)) |= ((val << B_DLRX_CFG_CTXT_CE5BUF_cfg_badr_target_ce5_write_index) & M_DLRX_CFG_CTXT_CE5BUF_cfg_badr_target_ce5_write_index);    \
	} while (0)

#define DLRX_CFG_CTXT_CE5BUF_cfg_badr_target_ce5_write_index_set_direct(dword, val)    \
	do {                                                               \
		(dword) &= (~(M_DLRX_CFG_CTXT_CE5BUF_cfg_badr_target_ce5_write_index));    \
		(dword) |= ((val << B_DLRX_CFG_CTXT_CE5BUF_cfg_badr_target_ce5_write_index) & M_DLRX_CFG_CTXT_CE5BUF_cfg_badr_target_ce5_write_index);    \
	} while (0)

#define DLRX_CFG_CTXT_CE5BUF_cfg_badr_target_ce5_write_index_clear_indirect(base, offset)	((*(base + O_DLRX_CFG_CTXT_CE5BUF_cfg_badr_target_ce5_write_index + offset)) &= (~(M_DLRX_CFG_CTXT_CE5BUF_cfg_badr_target_ce5_write_index)))

#define DLRX_CFG_CTXT_CE5BUF_cfg_badr_target_ce5_write_index_clear_direct(dword)	((dword) &= (~(M_DLRX_CFG_CTXT_CE5BUF_cfg_badr_target_ce5_write_index)))

#define O_DLRX_CFG_CTXT_CE5BUF_local_ce5_read_index 6
#define B_DLRX_CFG_CTXT_CE5BUF_local_ce5_read_index 0
#define W_DLRX_CFG_CTXT_CE5BUF_local_ce5_read_index 32
#define M_DLRX_CFG_CTXT_CE5BUF_local_ce5_read_index 0xffffffff

#define DLRX_CFG_CTXT_CE5BUF_local_ce5_read_index_get_indirect(base, offset)	((((*(base + O_DLRX_CFG_CTXT_CE5BUF_local_ce5_read_index + offset)) & M_DLRX_CFG_CTXT_CE5BUF_local_ce5_read_index) >> B_DLRX_CFG_CTXT_CE5BUF_local_ce5_read_index))

#define DLRX_CFG_CTXT_CE5BUF_local_ce5_read_index_get_direct(dword)	((((dword) & M_DLRX_CFG_CTXT_CE5BUF_local_ce5_read_index) >> B_DLRX_CFG_CTXT_CE5BUF_local_ce5_read_index))

#define DLRX_CFG_CTXT_CE5BUF_local_ce5_read_index_set_indirect(base, offset, val)    \
	do {                                                              \
		(*(base + O_DLRX_CFG_CTXT_CE5BUF_local_ce5_read_index + offset)) &= (~(M_DLRX_CFG_CTXT_CE5BUF_local_ce5_read_index));    \
		(*(base + O_DLRX_CFG_CTXT_CE5BUF_local_ce5_read_index + offset)) |= ((val << B_DLRX_CFG_CTXT_CE5BUF_local_ce5_read_index) & M_DLRX_CFG_CTXT_CE5BUF_local_ce5_read_index);    \
	} while (0)

#define DLRX_CFG_CTXT_CE5BUF_local_ce5_read_index_set_direct(dword, val)    \
	do {                                                               \
		(dword) &= (~(M_DLRX_CFG_CTXT_CE5BUF_local_ce5_read_index));    \
		(dword) |= ((val << B_DLRX_CFG_CTXT_CE5BUF_local_ce5_read_index) & M_DLRX_CFG_CTXT_CE5BUF_local_ce5_read_index);    \
	} while (0)

#define DLRX_CFG_CTXT_CE5BUF_local_ce5_read_index_clear_indirect(base, offset)	((*(base + O_DLRX_CFG_CTXT_CE5BUF_local_ce5_read_index + offset)) &= (~(M_DLRX_CFG_CTXT_CE5BUF_local_ce5_read_index)))

#define DLRX_CFG_CTXT_CE5BUF_local_ce5_read_index_clear_direct(dword)	((dword) &= (~(M_DLRX_CFG_CTXT_CE5BUF_local_ce5_read_index)))

#define O_DLRX_CFG_CTXT_CE5BUF_local_ce5_parsing_index 7
#define B_DLRX_CFG_CTXT_CE5BUF_local_ce5_parsing_index 0
#define W_DLRX_CFG_CTXT_CE5BUF_local_ce5_parsing_index 32
#define M_DLRX_CFG_CTXT_CE5BUF_local_ce5_parsing_index 0xffffffff

#define DLRX_CFG_CTXT_CE5BUF_local_ce5_parsing_index_get_indirect(base, offset)	((((*(base + O_DLRX_CFG_CTXT_CE5BUF_local_ce5_parsing_index + offset)) & M_DLRX_CFG_CTXT_CE5BUF_local_ce5_parsing_index) >> B_DLRX_CFG_CTXT_CE5BUF_local_ce5_parsing_index))

#define DLRX_CFG_CTXT_CE5BUF_local_ce5_parsing_index_get_direct(dword)	((((dword) & M_DLRX_CFG_CTXT_CE5BUF_local_ce5_parsing_index) >> B_DLRX_CFG_CTXT_CE5BUF_local_ce5_parsing_index))

#define DLRX_CFG_CTXT_CE5BUF_local_ce5_parsing_index_set_indirect(base, offset, val)    \
	do {                                                              \
		(*(base + O_DLRX_CFG_CTXT_CE5BUF_local_ce5_parsing_index + offset)) &= (~(M_DLRX_CFG_CTXT_CE5BUF_local_ce5_parsing_index));    \
		(*(base + O_DLRX_CFG_CTXT_CE5BUF_local_ce5_parsing_index + offset)) |= ((val << B_DLRX_CFG_CTXT_CE5BUF_local_ce5_parsing_index) & M_DLRX_CFG_CTXT_CE5BUF_local_ce5_parsing_index);    \
	} while (0)

#define DLRX_CFG_CTXT_CE5BUF_local_ce5_parsing_index_set_direct(dword, val)    \
	do {                                                               \
		(dword) &= (~(M_DLRX_CFG_CTXT_CE5BUF_local_ce5_parsing_index));    \
		(dword) |= ((val << B_DLRX_CFG_CTXT_CE5BUF_local_ce5_parsing_index) & M_DLRX_CFG_CTXT_CE5BUF_local_ce5_parsing_index);    \
	} while (0)

#define DLRX_CFG_CTXT_CE5BUF_local_ce5_parsing_index_clear_indirect(base, offset)	((*(base + O_DLRX_CFG_CTXT_CE5BUF_local_ce5_parsing_index + offset)) &= (~(M_DLRX_CFG_CTXT_CE5BUF_local_ce5_parsing_index)))

#define DLRX_CFG_CTXT_CE5BUF_local_ce5_parsing_index_clear_direct(dword)	((dword) &= (~(M_DLRX_CFG_CTXT_CE5BUF_local_ce5_parsing_index)))

#define O_DLRX_CFG_CTXT_CE5BUF_ce5_msg_type 8
#define B_DLRX_CFG_CTXT_CE5BUF_ce5_msg_type 0
#define W_DLRX_CFG_CTXT_CE5BUF_ce5_msg_type 32
#define M_DLRX_CFG_CTXT_CE5BUF_ce5_msg_type 0xffffffff

#define DLRX_CFG_CTXT_CE5BUF_ce5_msg_type_get_indirect(base, offset)	((((*(base + O_DLRX_CFG_CTXT_CE5BUF_ce5_msg_type + offset)) & M_DLRX_CFG_CTXT_CE5BUF_ce5_msg_type) >> B_DLRX_CFG_CTXT_CE5BUF_ce5_msg_type))

#define DLRX_CFG_CTXT_CE5BUF_ce5_msg_type_get_direct(dword)	((((dword) & M_DLRX_CFG_CTXT_CE5BUF_ce5_msg_type) >> B_DLRX_CFG_CTXT_CE5BUF_ce5_msg_type))

#define DLRX_CFG_CTXT_CE5BUF_ce5_msg_type_set_indirect(base, offset, val)    \
	do {                                                              \
		(*(base + O_DLRX_CFG_CTXT_CE5BUF_ce5_msg_type + offset)) &= (~(M_DLRX_CFG_CTXT_CE5BUF_ce5_msg_type));    \
		(*(base + O_DLRX_CFG_CTXT_CE5BUF_ce5_msg_type + offset)) |= ((val << B_DLRX_CFG_CTXT_CE5BUF_ce5_msg_type) & M_DLRX_CFG_CTXT_CE5BUF_ce5_msg_type);    \
	} while (0)

#define DLRX_CFG_CTXT_CE5BUF_ce5_msg_type_set_direct(dword, val)    \
	do {                                                               \
		(dword) &= (~(M_DLRX_CFG_CTXT_CE5BUF_ce5_msg_type));    \
		(dword) |= ((val << B_DLRX_CFG_CTXT_CE5BUF_ce5_msg_type) & M_DLRX_CFG_CTXT_CE5BUF_ce5_msg_type);    \
	} while (0)

#define DLRX_CFG_CTXT_CE5BUF_ce5_msg_type_clear_indirect(base, offset)	((*(base + O_DLRX_CFG_CTXT_CE5BUF_ce5_msg_type + offset)) &= (~(M_DLRX_CFG_CTXT_CE5BUF_ce5_msg_type)))

#define DLRX_CFG_CTXT_CE5BUF_ce5_msg_type_clear_direct(dword)	((dword) &= (~(M_DLRX_CFG_CTXT_CE5BUF_ce5_msg_type)))

#define O_DLRX_CFG_CTXT_CE5DES_cfg_badr_ce5des 0
#define B_DLRX_CFG_CTXT_CE5DES_cfg_badr_ce5des 0
#define W_DLRX_CFG_CTXT_CE5DES_cfg_badr_ce5des 32
#define M_DLRX_CFG_CTXT_CE5DES_cfg_badr_ce5des 0xffffffff

#define DLRX_CFG_CTXT_CE5DES_cfg_badr_ce5des_get_indirect(base, offset)	((((*(base + O_DLRX_CFG_CTXT_CE5DES_cfg_badr_ce5des + offset)) & M_DLRX_CFG_CTXT_CE5DES_cfg_badr_ce5des) >> B_DLRX_CFG_CTXT_CE5DES_cfg_badr_ce5des))

#define DLRX_CFG_CTXT_CE5DES_cfg_badr_ce5des_get_direct(dword)	((((dword) & M_DLRX_CFG_CTXT_CE5DES_cfg_badr_ce5des) >> B_DLRX_CFG_CTXT_CE5DES_cfg_badr_ce5des))

#define DLRX_CFG_CTXT_CE5DES_cfg_badr_ce5des_set_indirect(base, offset, val)    \
	do {                                                              \
		(*(base + O_DLRX_CFG_CTXT_CE5DES_cfg_badr_ce5des + offset)) &= (~(M_DLRX_CFG_CTXT_CE5DES_cfg_badr_ce5des));    \
		(*(base + O_DLRX_CFG_CTXT_CE5DES_cfg_badr_ce5des + offset)) |= ((val << B_DLRX_CFG_CTXT_CE5DES_cfg_badr_ce5des) & M_DLRX_CFG_CTXT_CE5DES_cfg_badr_ce5des);    \
	} while (0)

#define DLRX_CFG_CTXT_CE5DES_cfg_badr_ce5des_set_direct(dword, val)    \
	do {                                                               \
		(dword) &= (~(M_DLRX_CFG_CTXT_CE5DES_cfg_badr_ce5des));    \
		(dword) |= ((val << B_DLRX_CFG_CTXT_CE5DES_cfg_badr_ce5des) & M_DLRX_CFG_CTXT_CE5DES_cfg_badr_ce5des);    \
	} while (0)

#define DLRX_CFG_CTXT_CE5DES_cfg_badr_ce5des_clear_indirect(base, offset)	((*(base + O_DLRX_CFG_CTXT_CE5DES_cfg_badr_ce5des + offset)) &= (~(M_DLRX_CFG_CTXT_CE5DES_cfg_badr_ce5des)))

#define DLRX_CFG_CTXT_CE5DES_cfg_badr_ce5des_clear_direct(dword)	((dword) &= (~(M_DLRX_CFG_CTXT_CE5DES_cfg_badr_ce5des)))

#define O_DLRX_CFG_CTXT_CE5DES_cfg_num_ce5des 1
#define B_DLRX_CFG_CTXT_CE5DES_cfg_num_ce5des 0
#define W_DLRX_CFG_CTXT_CE5DES_cfg_num_ce5des 32
#define M_DLRX_CFG_CTXT_CE5DES_cfg_num_ce5des 0xffffffff

#define DLRX_CFG_CTXT_CE5DES_cfg_num_ce5des_get_indirect(base, offset)	((((*(base + O_DLRX_CFG_CTXT_CE5DES_cfg_num_ce5des + offset)) & M_DLRX_CFG_CTXT_CE5DES_cfg_num_ce5des) >> B_DLRX_CFG_CTXT_CE5DES_cfg_num_ce5des))

#define DLRX_CFG_CTXT_CE5DES_cfg_num_ce5des_get_direct(dword)	((((dword) & M_DLRX_CFG_CTXT_CE5DES_cfg_num_ce5des) >> B_DLRX_CFG_CTXT_CE5DES_cfg_num_ce5des))

#define DLRX_CFG_CTXT_CE5DES_cfg_num_ce5des_set_indirect(base, offset, val)    \
	do {                                                              \
		(*(base + O_DLRX_CFG_CTXT_CE5DES_cfg_num_ce5des + offset)) &= (~(M_DLRX_CFG_CTXT_CE5DES_cfg_num_ce5des));    \
		(*(base + O_DLRX_CFG_CTXT_CE5DES_cfg_num_ce5des + offset)) |= ((val << B_DLRX_CFG_CTXT_CE5DES_cfg_num_ce5des) & M_DLRX_CFG_CTXT_CE5DES_cfg_num_ce5des);    \
	} while (0)

#define DLRX_CFG_CTXT_CE5DES_cfg_num_ce5des_set_direct(dword, val)    \
	do {                                                               \
		(dword) &= (~(M_DLRX_CFG_CTXT_CE5DES_cfg_num_ce5des));    \
		(dword) |= ((val << B_DLRX_CFG_CTXT_CE5DES_cfg_num_ce5des) & M_DLRX_CFG_CTXT_CE5DES_cfg_num_ce5des);    \
	} while (0)

#define DLRX_CFG_CTXT_CE5DES_cfg_num_ce5des_clear_indirect(base, offset)	((*(base + O_DLRX_CFG_CTXT_CE5DES_cfg_num_ce5des + offset)) &= (~(M_DLRX_CFG_CTXT_CE5DES_cfg_num_ce5des)))

#define DLRX_CFG_CTXT_CE5DES_cfg_num_ce5des_clear_direct(dword)	((dword) &= (~(M_DLRX_CFG_CTXT_CE5DES_cfg_num_ce5des)))

#define O_DLRX_CFG_CTXT_CE5DES_msg_len 2
#define B_DLRX_CFG_CTXT_CE5DES_msg_len 0
#define W_DLRX_CFG_CTXT_CE5DES_msg_len 32
#define M_DLRX_CFG_CTXT_CE5DES_msg_len 0xffffffff

#define DLRX_CFG_CTXT_CE5DES_msg_len_get_indirect(base, offset)	((((*(base + O_DLRX_CFG_CTXT_CE5DES_msg_len + offset)) & M_DLRX_CFG_CTXT_CE5DES_msg_len) >> B_DLRX_CFG_CTXT_CE5DES_msg_len))

#define DLRX_CFG_CTXT_CE5DES_msg_len_get_direct(dword)	((((dword) & M_DLRX_CFG_CTXT_CE5DES_msg_len) >> B_DLRX_CFG_CTXT_CE5DES_msg_len))

#define DLRX_CFG_CTXT_CE5DES_msg_len_set_indirect(base, offset, val)    \
	do {                                                              \
		(*(base + O_DLRX_CFG_CTXT_CE5DES_msg_len + offset)) &= (~(M_DLRX_CFG_CTXT_CE5DES_msg_len));    \
		(*(base + O_DLRX_CFG_CTXT_CE5DES_msg_len + offset)) |= ((val << B_DLRX_CFG_CTXT_CE5DES_msg_len) & M_DLRX_CFG_CTXT_CE5DES_msg_len);    \
	} while (0)

#define DLRX_CFG_CTXT_CE5DES_msg_len_set_direct(dword, val)    \
	do {                                                               \
		(dword) &= (~(M_DLRX_CFG_CTXT_CE5DES_msg_len));    \
		(dword) |= ((val << B_DLRX_CFG_CTXT_CE5DES_msg_len) & M_DLRX_CFG_CTXT_CE5DES_msg_len);    \
	} while (0)

#define DLRX_CFG_CTXT_CE5DES_msg_len_clear_indirect(base, offset)	((*(base + O_DLRX_CFG_CTXT_CE5DES_msg_len + offset)) &= (~(M_DLRX_CFG_CTXT_CE5DES_msg_len)))

#define DLRX_CFG_CTXT_CE5DES_msg_len_clear_direct(dword)	((dword) &= (~(M_DLRX_CFG_CTXT_CE5DES_msg_len)))

#define O_DLRX_CE5DES_FORMAT_dest_ptr 0
#define B_DLRX_CE5DES_FORMAT_dest_ptr 0
#define W_DLRX_CE5DES_FORMAT_dest_ptr 32
#define M_DLRX_CE5DES_FORMAT_dest_ptr 0xffffffff

#define DLRX_CE5DES_FORMAT_dest_ptr_get_indirect(base, offset)	((((*(base + O_DLRX_CE5DES_FORMAT_dest_ptr + offset)) & M_DLRX_CE5DES_FORMAT_dest_ptr) >> B_DLRX_CE5DES_FORMAT_dest_ptr))

#define DLRX_CE5DES_FORMAT_dest_ptr_get_direct(dword)	((((dword) & M_DLRX_CE5DES_FORMAT_dest_ptr) >> B_DLRX_CE5DES_FORMAT_dest_ptr))

#define DLRX_CE5DES_FORMAT_dest_ptr_set_indirect(base, offset, val)    \
	do {                                                              \
		(*(base + O_DLRX_CE5DES_FORMAT_dest_ptr + offset)) &= (~(M_DLRX_CE5DES_FORMAT_dest_ptr));    \
		(*(base + O_DLRX_CE5DES_FORMAT_dest_ptr + offset)) |= ((val << B_DLRX_CE5DES_FORMAT_dest_ptr) & M_DLRX_CE5DES_FORMAT_dest_ptr);    \
	} while (0)

#define DLRX_CE5DES_FORMAT_dest_ptr_set_direct(dword, val)    \
	do {                                                               \
		(dword) &= (~(M_DLRX_CE5DES_FORMAT_dest_ptr));    \
		(dword) |= ((val << B_DLRX_CE5DES_FORMAT_dest_ptr) & M_DLRX_CE5DES_FORMAT_dest_ptr);    \
	} while (0)

#define DLRX_CE5DES_FORMAT_dest_ptr_clear_indirect(base, offset)	((*(base + O_DLRX_CE5DES_FORMAT_dest_ptr + offset)) &= (~(M_DLRX_CE5DES_FORMAT_dest_ptr)))

#define DLRX_CE5DES_FORMAT_dest_ptr_clear_direct(dword)	((dword) &= (~(M_DLRX_CE5DES_FORMAT_dest_ptr)))

#define O_DLRX_CE5DES_FORMAT_nbytes 1
#define B_DLRX_CE5DES_FORMAT_nbytes 0
#define W_DLRX_CE5DES_FORMAT_nbytes 16
#define M_DLRX_CE5DES_FORMAT_nbytes 0x0000ffff

#define DLRX_CE5DES_FORMAT_nbytes_get_indirect(base, offset)	((((*(base + O_DLRX_CE5DES_FORMAT_nbytes + offset)) & M_DLRX_CE5DES_FORMAT_nbytes) >> B_DLRX_CE5DES_FORMAT_nbytes))

#define DLRX_CE5DES_FORMAT_nbytes_get_direct(dword)	((((dword) & M_DLRX_CE5DES_FORMAT_nbytes) >> B_DLRX_CE5DES_FORMAT_nbytes))

#define DLRX_CE5DES_FORMAT_nbytes_set_indirect(base, offset, val) \
	do {                                                              \
		(*(base + O_DLRX_CE5DES_FORMAT_nbytes + offset)) &= (~(M_DLRX_CE5DES_FORMAT_nbytes));    \
		(*(base + O_DLRX_CE5DES_FORMAT_nbytes + offset)) |= ((val << B_DLRX_CE5DES_FORMAT_nbytes) & M_DLRX_CE5DES_FORMAT_nbytes);    \
	} while (0)

#define DLRX_CE5DES_FORMAT_nbytes_set_direct(dword, val) \
	do {                                                               \
		(dword) &= (~(M_DLRX_CE5DES_FORMAT_nbytes));    \
		(dword) |= ((val << B_DLRX_CE5DES_FORMAT_nbytes) & M_DLRX_CE5DES_FORMAT_nbytes);    \
	} while (0)

#define DLRX_CE5DES_FORMAT_nbytes_clear_indirect(base, offset)	((*(base + O_DLRX_CE5DES_FORMAT_nbytes + offset)) &= (~(M_DLRX_CE5DES_FORMAT_nbytes)))

#define DLRX_CE5DES_FORMAT_nbytes_clear_direct(dword)	((dword) &= (~(M_DLRX_CE5DES_FORMAT_nbytes)))

#define O_DLRX_CE5DES_FORMAT_gather 1
#define B_DLRX_CE5DES_FORMAT_gather 16
#define W_DLRX_CE5DES_FORMAT_gather 1
#define M_DLRX_CE5DES_FORMAT_gather 0x00010000

#define DLRX_CE5DES_FORMAT_gather_get_indirect(base, offset)	((((*(base + O_DLRX_CE5DES_FORMAT_gather + offset)) & M_DLRX_CE5DES_FORMAT_gather) >> B_DLRX_CE5DES_FORMAT_gather))

#define DLRX_CE5DES_FORMAT_gather_get_direct(dword)	((((dword) & M_DLRX_CE5DES_FORMAT_gather) >> B_DLRX_CE5DES_FORMAT_gather))

#define DLRX_CE5DES_FORMAT_gather_set_indirect(base, offset, val) \
	do {                                                              \
		(*(base + O_DLRX_CE5DES_FORMAT_gather + offset)) &= (~(M_DLRX_CE5DES_FORMAT_gather));    \
		(*(base + O_DLRX_CE5DES_FORMAT_gather + offset)) |= ((val << B_DLRX_CE5DES_FORMAT_gather) & M_DLRX_CE5DES_FORMAT_gather);    \
	} while (0)

#define DLRX_CE5DES_FORMAT_gather_set_direct(dword, val) \
	do {                                                               \
		(dword) &= (~(M_DLRX_CE5DES_FORMAT_gather));    \
		(dword) |= ((val << B_DLRX_CE5DES_FORMAT_gather) & M_DLRX_CE5DES_FORMAT_gather);    \
	} while (0)

#define DLRX_CE5DES_FORMAT_gather_clear_indirect(base, offset)	((*(base + O_DLRX_CE5DES_FORMAT_gather + offset)) &= (~(M_DLRX_CE5DES_FORMAT_gather)))

#define DLRX_CE5DES_FORMAT_gather_clear_direct(dword)	((dword) &= (~(M_DLRX_CE5DES_FORMAT_gather)))

#define O_DLRX_CE5DES_FORMAT_byte_swap 1
#define B_DLRX_CE5DES_FORMAT_byte_swap 17
#define W_DLRX_CE5DES_FORMAT_byte_swap 1
#define M_DLRX_CE5DES_FORMAT_byte_swap 0x00020000

#define DLRX_CE5DES_FORMAT_byte_swap_get_indirect(base, offset)	((((*(base + O_DLRX_CE5DES_FORMAT_byte_swap + offset)) & M_DLRX_CE5DES_FORMAT_byte_swap) >> B_DLRX_CE5DES_FORMAT_byte_swap))

#define DLRX_CE5DES_FORMAT_byte_swap_get_direct(dword)	((((dword) & M_DLRX_CE5DES_FORMAT_byte_swap) >> B_DLRX_CE5DES_FORMAT_byte_swap))

#define DLRX_CE5DES_FORMAT_byte_swap_set_indirect(base, offset, val) \
	do {                                                              \
		(*(base + O_DLRX_CE5DES_FORMAT_byte_swap + offset)) &= (~(M_DLRX_CE5DES_FORMAT_byte_swap));    \
		(*(base + O_DLRX_CE5DES_FORMAT_byte_swap + offset)) |= ((val << B_DLRX_CE5DES_FORMAT_byte_swap) & M_DLRX_CE5DES_FORMAT_byte_swap);    \
	} while (0)

#define DLRX_CE5DES_FORMAT_byte_swap_set_direct(dword, val) \
	do {                                                               \
		(dword) &= (~(M_DLRX_CE5DES_FORMAT_byte_swap));    \
		(dword) |= ((val << B_DLRX_CE5DES_FORMAT_byte_swap) & M_DLRX_CE5DES_FORMAT_byte_swap);    \
	} while (0)

#define DLRX_CE5DES_FORMAT_byte_swap_clear_indirect(base, offset)	((*(base + O_DLRX_CE5DES_FORMAT_byte_swap + offset)) &= (~(M_DLRX_CE5DES_FORMAT_byte_swap)))

#define DLRX_CE5DES_FORMAT_byte_swap_clear_direct(dword)	((dword) &= (~(M_DLRX_CE5DES_FORMAT_byte_swap)))

#define O_DLRX_CE5DES_FORMAT_meta_data 1
#define B_DLRX_CE5DES_FORMAT_meta_data 18
#define W_DLRX_CE5DES_FORMAT_meta_data 14
#define M_DLRX_CE5DES_FORMAT_meta_data 0xfffc0000

#define DLRX_CE5DES_FORMAT_meta_data_get_indirect(base, offset)	((((*(base + O_DLRX_CE5DES_FORMAT_meta_data + offset)) & M_DLRX_CE5DES_FORMAT_meta_data) >> B_DLRX_CE5DES_FORMAT_meta_data))

#define DLRX_CE5DES_FORMAT_meta_data_get_direct(dword)	((((dword) & M_DLRX_CE5DES_FORMAT_meta_data) >> B_DLRX_CE5DES_FORMAT_meta_data))

#define DLRX_CE5DES_FORMAT_meta_data_set_indirect(base, offset, val) \
	do {                                                              \
		(*(base + O_DLRX_CE5DES_FORMAT_meta_data + offset)) &= (~(M_DLRX_CE5DES_FORMAT_meta_data));    \
		(*(base + O_DLRX_CE5DES_FORMAT_meta_data + offset)) |= ((val << B_DLRX_CE5DES_FORMAT_meta_data) & M_DLRX_CE5DES_FORMAT_meta_data);    \
	} while (0)

#define DLRX_CE5DES_FORMAT_meta_data_set_direct(dword, val) \
	do {                                                               \
		(dword) &= (~(M_DLRX_CE5DES_FORMAT_meta_data));    \
		(dword) |= ((val << B_DLRX_CE5DES_FORMAT_meta_data) & M_DLRX_CE5DES_FORMAT_meta_data);    \
	} while (0)

#define DLRX_CE5DES_FORMAT_meta_data_clear_indirect(base, offset)	((*(base + O_DLRX_CE5DES_FORMAT_meta_data + offset)) &= (~(M_DLRX_CE5DES_FORMAT_meta_data)))

#define DLRX_CE5DES_FORMAT_meta_data_clear_direct(dword)	((dword) &= (~(M_DLRX_CE5DES_FORMAT_meta_data)))

#define O_DLRX_CFG_CTXT_CPU_CE5DES_cfg_badr_cpu_ce5 0
#define B_DLRX_CFG_CTXT_CPU_CE5DES_cfg_badr_cpu_ce5 0
#define W_DLRX_CFG_CTXT_CPU_CE5DES_cfg_badr_cpu_ce5 32
#define M_DLRX_CFG_CTXT_CPU_CE5DES_cfg_badr_cpu_ce5 0xffffffff

#define DLRX_CFG_CTXT_CPU_CE5DES_cfg_badr_cpu_ce5_get_indirect(base, offset)	((((*(base + O_DLRX_CFG_CTXT_CPU_CE5DES_cfg_badr_cpu_ce5 + offset)) & M_DLRX_CFG_CTXT_CPU_CE5DES_cfg_badr_cpu_ce5) >> B_DLRX_CFG_CTXT_CPU_CE5DES_cfg_badr_cpu_ce5))

#define DLRX_CFG_CTXT_CPU_CE5DES_cfg_badr_cpu_ce5_get_direct(dword)	((((dword) & M_DLRX_CFG_CTXT_CPU_CE5DES_cfg_badr_cpu_ce5) >> B_DLRX_CFG_CTXT_CPU_CE5DES_cfg_badr_cpu_ce5))

#define DLRX_CFG_CTXT_CPU_CE5DES_cfg_badr_cpu_ce5_set_indirect(base, offset, val)    \
	do {                                                              \
		(*(base + O_DLRX_CFG_CTXT_CPU_CE5DES_cfg_badr_cpu_ce5 + offset)) &= (~(M_DLRX_CFG_CTXT_CPU_CE5DES_cfg_badr_cpu_ce5));    \
		(*(base + O_DLRX_CFG_CTXT_CPU_CE5DES_cfg_badr_cpu_ce5 + offset)) |= ((val << B_DLRX_CFG_CTXT_CPU_CE5DES_cfg_badr_cpu_ce5) & M_DLRX_CFG_CTXT_CPU_CE5DES_cfg_badr_cpu_ce5);    \
	} while (0)

#define DLRX_CFG_CTXT_CPU_CE5DES_cfg_badr_cpu_ce5_set_direct(dword, val)    \
	do {                                                               \
		(dword) &= (~(M_DLRX_CFG_CTXT_CPU_CE5DES_cfg_badr_cpu_ce5));    \
		(dword) |= ((val << B_DLRX_CFG_CTXT_CPU_CE5DES_cfg_badr_cpu_ce5) & M_DLRX_CFG_CTXT_CPU_CE5DES_cfg_badr_cpu_ce5);    \
	} while (0)

#define DLRX_CFG_CTXT_CPU_CE5DES_cfg_badr_cpu_ce5_clear_indirect(base, offset)	((*(base + O_DLRX_CFG_CTXT_CPU_CE5DES_cfg_badr_cpu_ce5 + offset)) &= (~(M_DLRX_CFG_CTXT_CPU_CE5DES_cfg_badr_cpu_ce5)))

#define DLRX_CFG_CTXT_CPU_CE5DES_cfg_badr_cpu_ce5_clear_direct(dword)	((dword) &= (~(M_DLRX_CFG_CTXT_CPU_CE5DES_cfg_badr_cpu_ce5)))

#define O_DLRX_CFG_CTXT_CPU_CE5DES_cfg_num_cpu_ce5 1
#define B_DLRX_CFG_CTXT_CPU_CE5DES_cfg_num_cpu_ce5 0
#define W_DLRX_CFG_CTXT_CPU_CE5DES_cfg_num_cpu_ce5 32
#define M_DLRX_CFG_CTXT_CPU_CE5DES_cfg_num_cpu_ce5 0xffffffff

#define DLRX_CFG_CTXT_CPU_CE5DES_cfg_num_cpu_ce5_get_indirect(base, offset)	((((*(base + O_DLRX_CFG_CTXT_CPU_CE5DES_cfg_num_cpu_ce5 + offset)) & M_DLRX_CFG_CTXT_CPU_CE5DES_cfg_num_cpu_ce5) >> B_DLRX_CFG_CTXT_CPU_CE5DES_cfg_num_cpu_ce5))

#define DLRX_CFG_CTXT_CPU_CE5DES_cfg_num_cpu_ce5_get_direct(dword)	((((dword) & M_DLRX_CFG_CTXT_CPU_CE5DES_cfg_num_cpu_ce5) >> B_DLRX_CFG_CTXT_CPU_CE5DES_cfg_num_cpu_ce5))

#define DLRX_CFG_CTXT_CPU_CE5DES_cfg_num_cpu_ce5_set_indirect(base, offset, val)    \
	do {                                                              \
		(*(base + O_DLRX_CFG_CTXT_CPU_CE5DES_cfg_num_cpu_ce5 + offset)) &= (~(M_DLRX_CFG_CTXT_CPU_CE5DES_cfg_num_cpu_ce5));    \
		(*(base + O_DLRX_CFG_CTXT_CPU_CE5DES_cfg_num_cpu_ce5 + offset)) |= ((val << B_DLRX_CFG_CTXT_CPU_CE5DES_cfg_num_cpu_ce5) & M_DLRX_CFG_CTXT_CPU_CE5DES_cfg_num_cpu_ce5);    \
	} while (0)

#define DLRX_CFG_CTXT_CPU_CE5DES_cfg_num_cpu_ce5_set_direct(dword, val)    \
	do {                                                               \
		(dword) &= (~(M_DLRX_CFG_CTXT_CPU_CE5DES_cfg_num_cpu_ce5));    \
		(dword) |= ((val << B_DLRX_CFG_CTXT_CPU_CE5DES_cfg_num_cpu_ce5) & M_DLRX_CFG_CTXT_CPU_CE5DES_cfg_num_cpu_ce5);    \
	} while (0)

#define DLRX_CFG_CTXT_CPU_CE5DES_cfg_num_cpu_ce5_clear_indirect(base, offset)	((*(base + O_DLRX_CFG_CTXT_CPU_CE5DES_cfg_num_cpu_ce5 + offset)) &= (~(M_DLRX_CFG_CTXT_CPU_CE5DES_cfg_num_cpu_ce5)))

#define DLRX_CFG_CTXT_CPU_CE5DES_cfg_num_cpu_ce5_clear_direct(dword)	((dword) &= (~(M_DLRX_CFG_CTXT_CPU_CE5DES_cfg_num_cpu_ce5)))

#define O_DLRX_CFG_CTXT_CPU_CE5DES_cpu_ce5_read_index 2
#define B_DLRX_CFG_CTXT_CPU_CE5DES_cpu_ce5_read_index 0
#define W_DLRX_CFG_CTXT_CPU_CE5DES_cpu_ce5_read_index 32
#define M_DLRX_CFG_CTXT_CPU_CE5DES_cpu_ce5_read_index 0xffffffff

#define DLRX_CFG_CTXT_CPU_CE5DES_cpu_ce5_read_index_get_indirect(base, offset)	((((*(base + O_DLRX_CFG_CTXT_CPU_CE5DES_cpu_ce5_read_index + offset)) & M_DLRX_CFG_CTXT_CPU_CE5DES_cpu_ce5_read_index) >> B_DLRX_CFG_CTXT_CPU_CE5DES_cpu_ce5_read_index))

#define DLRX_CFG_CTXT_CPU_CE5DES_cpu_ce5_read_index_get_direct(dword)	((((dword) & M_DLRX_CFG_CTXT_CPU_CE5DES_cpu_ce5_read_index) >> B_DLRX_CFG_CTXT_CPU_CE5DES_cpu_ce5_read_index))

#define DLRX_CFG_CTXT_CPU_CE5DES_cpu_ce5_read_index_set_indirect(base, offset, val)    \
	do {                                                              \
		(*(base + O_DLRX_CFG_CTXT_CPU_CE5DES_cpu_ce5_read_index + offset)) &= (~(M_DLRX_CFG_CTXT_CPU_CE5DES_cpu_ce5_read_index));    \
		(*(base + O_DLRX_CFG_CTXT_CPU_CE5DES_cpu_ce5_read_index + offset)) |= ((val << B_DLRX_CFG_CTXT_CPU_CE5DES_cpu_ce5_read_index) & M_DLRX_CFG_CTXT_CPU_CE5DES_cpu_ce5_read_index);    \
	} while (0)

#define DLRX_CFG_CTXT_CPU_CE5DES_cpu_ce5_read_index_set_direct(dword, val)    \
	do {                                                               \
		(dword) &= (~(M_DLRX_CFG_CTXT_CPU_CE5DES_cpu_ce5_read_index));    \
		(dword) |= ((val << B_DLRX_CFG_CTXT_CPU_CE5DES_cpu_ce5_read_index) & M_DLRX_CFG_CTXT_CPU_CE5DES_cpu_ce5_read_index);    \
	} while (0)

#define DLRX_CFG_CTXT_CPU_CE5DES_cpu_ce5_read_index_clear_indirect(base, offset)	((*(base + O_DLRX_CFG_CTXT_CPU_CE5DES_cpu_ce5_read_index + offset)) &= (~(M_DLRX_CFG_CTXT_CPU_CE5DES_cpu_ce5_read_index)))

#define DLRX_CFG_CTXT_CPU_CE5DES_cpu_ce5_read_index_clear_direct(dword)	((dword) &= (~(M_DLRX_CFG_CTXT_CPU_CE5DES_cpu_ce5_read_index)))

#define O_DLRX_CFG_CTXT_CPU_CE5DES_cpu_ce5_write_index 3
#define B_DLRX_CFG_CTXT_CPU_CE5DES_cpu_ce5_write_index 0
#define W_DLRX_CFG_CTXT_CPU_CE5DES_cpu_ce5_write_index 32
#define M_DLRX_CFG_CTXT_CPU_CE5DES_cpu_ce5_write_index 0xffffffff

#define DLRX_CFG_CTXT_CPU_CE5DES_cpu_ce5_write_index_get_indirect(base, offset)	((((*(base + O_DLRX_CFG_CTXT_CPU_CE5DES_cpu_ce5_write_index + offset)) & M_DLRX_CFG_CTXT_CPU_CE5DES_cpu_ce5_write_index) >> B_DLRX_CFG_CTXT_CPU_CE5DES_cpu_ce5_write_index))

#define DLRX_CFG_CTXT_CPU_CE5DES_cpu_ce5_write_index_get_direct(dword)	((((dword) & M_DLRX_CFG_CTXT_CPU_CE5DES_cpu_ce5_write_index) >> B_DLRX_CFG_CTXT_CPU_CE5DES_cpu_ce5_write_index))

#define DLRX_CFG_CTXT_CPU_CE5DES_cpu_ce5_write_index_set_indirect(base, offset, val)    \
	do {                                                              \
		(*(base + O_DLRX_CFG_CTXT_CPU_CE5DES_cpu_ce5_write_index + offset)) &= (~(M_DLRX_CFG_CTXT_CPU_CE5DES_cpu_ce5_write_index));    \
		(*(base + O_DLRX_CFG_CTXT_CPU_CE5DES_cpu_ce5_write_index + offset)) |= ((val << B_DLRX_CFG_CTXT_CPU_CE5DES_cpu_ce5_write_index) & M_DLRX_CFG_CTXT_CPU_CE5DES_cpu_ce5_write_index);    \
	} while (0)

#define DLRX_CFG_CTXT_CPU_CE5DES_cpu_ce5_write_index_set_direct(dword, val)    \
	do {                                                               \
		(dword) &= (~(M_DLRX_CFG_CTXT_CPU_CE5DES_cpu_ce5_write_index));    \
		(dword) |= ((val << B_DLRX_CFG_CTXT_CPU_CE5DES_cpu_ce5_write_index) & M_DLRX_CFG_CTXT_CPU_CE5DES_cpu_ce5_write_index);    \
	} while (0)

#define DLRX_CFG_CTXT_CPU_CE5DES_cpu_ce5_write_index_clear_indirect(base, offset)	((*(base + O_DLRX_CFG_CTXT_CPU_CE5DES_cpu_ce5_write_index + offset)) &= (~(M_DLRX_CFG_CTXT_CPU_CE5DES_cpu_ce5_write_index)))

#define DLRX_CFG_CTXT_CPU_CE5DES_cpu_ce5_write_index_clear_direct(dword)	((dword) &= (~(M_DLRX_CFG_CTXT_CPU_CE5DES_cpu_ce5_write_index)))

#define O_DLRX_CFG_CTXT_CPU_CE5DES_cpu_ce5_msg_done 4
#define B_DLRX_CFG_CTXT_CPU_CE5DES_cpu_ce5_msg_done 0
#define W_DLRX_CFG_CTXT_CPU_CE5DES_cpu_ce5_msg_done 32
#define M_DLRX_CFG_CTXT_CPU_CE5DES_cpu_ce5_msg_done 0xffffffff

#define DLRX_CFG_CTXT_CPU_CE5DES_cpu_ce5_msg_done_get_indirect(base, offset)	((((*(base + O_DLRX_CFG_CTXT_CPU_CE5DES_cpu_ce5_msg_done + offset)) & M_DLRX_CFG_CTXT_CPU_CE5DES_cpu_ce5_msg_done) >> B_DLRX_CFG_CTXT_CPU_CE5DES_cpu_ce5_msg_done))

#define DLRX_CFG_CTXT_CPU_CE5DES_cpu_ce5_msg_done_get_direct(dword)	((((dword) & M_DLRX_CFG_CTXT_CPU_CE5DES_cpu_ce5_msg_done) >> B_DLRX_CFG_CTXT_CPU_CE5DES_cpu_ce5_msg_done))

#define DLRX_CFG_CTXT_CPU_CE5DES_cpu_ce5_msg_done_set_indirect(base, offset, val)    \
	do {                                                              \
		(*(base + O_DLRX_CFG_CTXT_CPU_CE5DES_cpu_ce5_msg_done + offset)) &= (~(M_DLRX_CFG_CTXT_CPU_CE5DES_cpu_ce5_msg_done));    \
		(*(base + O_DLRX_CFG_CTXT_CPU_CE5DES_cpu_ce5_msg_done + offset)) |= ((val << B_DLRX_CFG_CTXT_CPU_CE5DES_cpu_ce5_msg_done) & M_DLRX_CFG_CTXT_CPU_CE5DES_cpu_ce5_msg_done);    \
	} while (0)

#define DLRX_CFG_CTXT_CPU_CE5DES_cpu_ce5_msg_done_set_direct(dword, val)    \
	do {                                                               \
		(dword) &= (~(M_DLRX_CFG_CTXT_CPU_CE5DES_cpu_ce5_msg_done));    \
		(dword) |= ((val << B_DLRX_CFG_CTXT_CPU_CE5DES_cpu_ce5_msg_done) & M_DLRX_CFG_CTXT_CPU_CE5DES_cpu_ce5_msg_done);    \
	} while (0)

#define DLRX_CFG_CTXT_CPU_CE5DES_cpu_ce5_msg_done_clear_indirect(base, offset)	((*(base + O_DLRX_CFG_CTXT_CPU_CE5DES_cpu_ce5_msg_done + offset)) &= (~(M_DLRX_CFG_CTXT_CPU_CE5DES_cpu_ce5_msg_done)))

#define DLRX_CFG_CTXT_CPU_CE5DES_cpu_ce5_msg_done_clear_direct(dword)	((dword) &= (~(M_DLRX_CFG_CTXT_CPU_CE5DES_cpu_ce5_msg_done)))

#define O_DLRX_CFG_CTXT_RXPB_PTR_RING_cfg_badr_rxpb_ptr_ring 0
#define B_DLRX_CFG_CTXT_RXPB_PTR_RING_cfg_badr_rxpb_ptr_ring 0
#define W_DLRX_CFG_CTXT_RXPB_PTR_RING_cfg_badr_rxpb_ptr_ring 32
#define M_DLRX_CFG_CTXT_RXPB_PTR_RING_cfg_badr_rxpb_ptr_ring 0xffffffff

#define DLRX_CFG_CTXT_RXPB_PTR_RING_cfg_badr_rxpb_ptr_ring_get_indirect(base, offset)	((((*(base + O_DLRX_CFG_CTXT_RXPB_PTR_RING_cfg_badr_rxpb_ptr_ring + offset)) & M_DLRX_CFG_CTXT_RXPB_PTR_RING_cfg_badr_rxpb_ptr_ring) >> B_DLRX_CFG_CTXT_RXPB_PTR_RING_cfg_badr_rxpb_ptr_ring))

#define DLRX_CFG_CTXT_RXPB_PTR_RING_cfg_badr_rxpb_ptr_ring_get_direct(dword)	((((dword) & M_DLRX_CFG_CTXT_RXPB_PTR_RING_cfg_badr_rxpb_ptr_ring) >> B_DLRX_CFG_CTXT_RXPB_PTR_RING_cfg_badr_rxpb_ptr_ring))

#define DLRX_CFG_CTXT_RXPB_PTR_RING_cfg_badr_rxpb_ptr_ring_set_indirect(base, offset, val)    \
	do {                                                              \
		(*(base + O_DLRX_CFG_CTXT_RXPB_PTR_RING_cfg_badr_rxpb_ptr_ring + offset)) &= (~(M_DLRX_CFG_CTXT_RXPB_PTR_RING_cfg_badr_rxpb_ptr_ring));    \
		(*(base + O_DLRX_CFG_CTXT_RXPB_PTR_RING_cfg_badr_rxpb_ptr_ring + offset)) |= ((val << B_DLRX_CFG_CTXT_RXPB_PTR_RING_cfg_badr_rxpb_ptr_ring) & M_DLRX_CFG_CTXT_RXPB_PTR_RING_cfg_badr_rxpb_ptr_ring);    \
	} while (0)

#define DLRX_CFG_CTXT_RXPB_PTR_RING_cfg_badr_rxpb_ptr_ring_set_direct(dword, val)    \
	do {                                                               \
		(dword) &= (~(M_DLRX_CFG_CTXT_RXPB_PTR_RING_cfg_badr_rxpb_ptr_ring));    \
		(dword) |= ((val << B_DLRX_CFG_CTXT_RXPB_PTR_RING_cfg_badr_rxpb_ptr_ring) & M_DLRX_CFG_CTXT_RXPB_PTR_RING_cfg_badr_rxpb_ptr_ring);    \
	} while (0)

#define DLRX_CFG_CTXT_RXPB_PTR_RING_cfg_badr_rxpb_ptr_ring_clear_indirect(base, offset)	((*(base + O_DLRX_CFG_CTXT_RXPB_PTR_RING_cfg_badr_rxpb_ptr_ring + offset)) &= (~(M_DLRX_CFG_CTXT_RXPB_PTR_RING_cfg_badr_rxpb_ptr_ring)))

#define DLRX_CFG_CTXT_RXPB_PTR_RING_cfg_badr_rxpb_ptr_ring_clear_direct(dword)	((dword) &= (~(M_DLRX_CFG_CTXT_RXPB_PTR_RING_cfg_badr_rxpb_ptr_ring)))

#define O_DLRX_CFG_CTXT_RXPB_PTR_RING_cfg_num_rxpb_ptr_ring 1
#define B_DLRX_CFG_CTXT_RXPB_PTR_RING_cfg_num_rxpb_ptr_ring 0
#define W_DLRX_CFG_CTXT_RXPB_PTR_RING_cfg_num_rxpb_ptr_ring 32
#define M_DLRX_CFG_CTXT_RXPB_PTR_RING_cfg_num_rxpb_ptr_ring 0xffffffff

#define DLRX_CFG_CTXT_RXPB_PTR_RING_cfg_num_rxpb_ptr_ring_get_indirect(base, offset)	((((*(base + O_DLRX_CFG_CTXT_RXPB_PTR_RING_cfg_num_rxpb_ptr_ring + offset)) & M_DLRX_CFG_CTXT_RXPB_PTR_RING_cfg_num_rxpb_ptr_ring) >> B_DLRX_CFG_CTXT_RXPB_PTR_RING_cfg_num_rxpb_ptr_ring))

#define DLRX_CFG_CTXT_RXPB_PTR_RING_cfg_num_rxpb_ptr_ring_get_direct(dword)	((((dword) & M_DLRX_CFG_CTXT_RXPB_PTR_RING_cfg_num_rxpb_ptr_ring) >> B_DLRX_CFG_CTXT_RXPB_PTR_RING_cfg_num_rxpb_ptr_ring))

#define DLRX_CFG_CTXT_RXPB_PTR_RING_cfg_num_rxpb_ptr_ring_set_indirect(base, offset, val)    \
	do {                                                              \
		(*(base + O_DLRX_CFG_CTXT_RXPB_PTR_RING_cfg_num_rxpb_ptr_ring + offset)) &= (~(M_DLRX_CFG_CTXT_RXPB_PTR_RING_cfg_num_rxpb_ptr_ring));    \
		(*(base + O_DLRX_CFG_CTXT_RXPB_PTR_RING_cfg_num_rxpb_ptr_ring + offset)) |= ((val << B_DLRX_CFG_CTXT_RXPB_PTR_RING_cfg_num_rxpb_ptr_ring) & M_DLRX_CFG_CTXT_RXPB_PTR_RING_cfg_num_rxpb_ptr_ring);    \
	} while (0)

#define DLRX_CFG_CTXT_RXPB_PTR_RING_cfg_num_rxpb_ptr_ring_set_direct(dword, val)    \
	do {                                                               \
		(dword) &= (~(M_DLRX_CFG_CTXT_RXPB_PTR_RING_cfg_num_rxpb_ptr_ring));    \
		(dword) |= ((val << B_DLRX_CFG_CTXT_RXPB_PTR_RING_cfg_num_rxpb_ptr_ring) & M_DLRX_CFG_CTXT_RXPB_PTR_RING_cfg_num_rxpb_ptr_ring);    \
	} while (0)

#define DLRX_CFG_CTXT_RXPB_PTR_RING_cfg_num_rxpb_ptr_ring_clear_indirect(base, offset)	((*(base + O_DLRX_CFG_CTXT_RXPB_PTR_RING_cfg_num_rxpb_ptr_ring + offset)) &= (~(M_DLRX_CFG_CTXT_RXPB_PTR_RING_cfg_num_rxpb_ptr_ring)))

#define DLRX_CFG_CTXT_RXPB_PTR_RING_cfg_num_rxpb_ptr_ring_clear_direct(dword)	((dword) &= (~(M_DLRX_CFG_CTXT_RXPB_PTR_RING_cfg_num_rxpb_ptr_ring)))

#define O_DLRX_CFG_CTXT_RXPB_PTR_RING_rxpb_ptr_write_index 2
#define B_DLRX_CFG_CTXT_RXPB_PTR_RING_rxpb_ptr_write_index 0
#define W_DLRX_CFG_CTXT_RXPB_PTR_RING_rxpb_ptr_write_index 32
#define M_DLRX_CFG_CTXT_RXPB_PTR_RING_rxpb_ptr_write_index 0xffffffff

#define DLRX_CFG_CTXT_RXPB_PTR_RING_rxpb_ptr_write_index_get_indirect(base, offset)	((((*(base + O_DLRX_CFG_CTXT_RXPB_PTR_RING_rxpb_ptr_write_index + offset)) & M_DLRX_CFG_CTXT_RXPB_PTR_RING_rxpb_ptr_write_index) >> B_DLRX_CFG_CTXT_RXPB_PTR_RING_rxpb_ptr_write_index))

#define DLRX_CFG_CTXT_RXPB_PTR_RING_rxpb_ptr_write_index_get_direct(dword)	((((dword) & M_DLRX_CFG_CTXT_RXPB_PTR_RING_rxpb_ptr_write_index) >> B_DLRX_CFG_CTXT_RXPB_PTR_RING_rxpb_ptr_write_index))

#define DLRX_CFG_CTXT_RXPB_PTR_RING_rxpb_ptr_write_index_set_indirect(base, offset, val)    \
	do {                                                              \
		(*(base + O_DLRX_CFG_CTXT_RXPB_PTR_RING_rxpb_ptr_write_index + offset)) &= (~(M_DLRX_CFG_CTXT_RXPB_PTR_RING_rxpb_ptr_write_index));    \
		(*(base + O_DLRX_CFG_CTXT_RXPB_PTR_RING_rxpb_ptr_write_index + offset)) |= ((val << B_DLRX_CFG_CTXT_RXPB_PTR_RING_rxpb_ptr_write_index) & M_DLRX_CFG_CTXT_RXPB_PTR_RING_rxpb_ptr_write_index);    \
	} while (0)

#define DLRX_CFG_CTXT_RXPB_PTR_RING_rxpb_ptr_write_index_set_direct(dword, val)    \
	do {                                                               \
		(dword) &= (~(M_DLRX_CFG_CTXT_RXPB_PTR_RING_rxpb_ptr_write_index));    \
		(dword) |= ((val << B_DLRX_CFG_CTXT_RXPB_PTR_RING_rxpb_ptr_write_index) & M_DLRX_CFG_CTXT_RXPB_PTR_RING_rxpb_ptr_write_index);    \
	} while (0)

#define DLRX_CFG_CTXT_RXPB_PTR_RING_rxpb_ptr_write_index_clear_indirect(base, offset)	((*(base + O_DLRX_CFG_CTXT_RXPB_PTR_RING_rxpb_ptr_write_index + offset)) &= (~(M_DLRX_CFG_CTXT_RXPB_PTR_RING_rxpb_ptr_write_index)))

#define DLRX_CFG_CTXT_RXPB_PTR_RING_rxpb_ptr_write_index_clear_direct(dword)	((dword) &= (~(M_DLRX_CFG_CTXT_RXPB_PTR_RING_rxpb_ptr_write_index)))

#define O_DLRX_CFG_CTXT_RXPB_PTR_RING_rxpb_ptr_read_index 3
#define B_DLRX_CFG_CTXT_RXPB_PTR_RING_rxpb_ptr_read_index 0
#define W_DLRX_CFG_CTXT_RXPB_PTR_RING_rxpb_ptr_read_index 32
#define M_DLRX_CFG_CTXT_RXPB_PTR_RING_rxpb_ptr_read_index 0xffffffff

#define DLRX_CFG_CTXT_RXPB_PTR_RING_rxpb_ptr_read_index_get_indirect(base, offset)	((((*(base + O_DLRX_CFG_CTXT_RXPB_PTR_RING_rxpb_ptr_read_index + offset)) & M_DLRX_CFG_CTXT_RXPB_PTR_RING_rxpb_ptr_read_index) >> B_DLRX_CFG_CTXT_RXPB_PTR_RING_rxpb_ptr_read_index))

#define DLRX_CFG_CTXT_RXPB_PTR_RING_rxpb_ptr_read_index_get_direct(dword)	((((dword) & M_DLRX_CFG_CTXT_RXPB_PTR_RING_rxpb_ptr_read_index) >> B_DLRX_CFG_CTXT_RXPB_PTR_RING_rxpb_ptr_read_index))

#define DLRX_CFG_CTXT_RXPB_PTR_RING_rxpb_ptr_read_index_set_indirect(base, offset, val)    \
	do {                                                              \
		(*(base + O_DLRX_CFG_CTXT_RXPB_PTR_RING_rxpb_ptr_read_index + offset)) &= (~(M_DLRX_CFG_CTXT_RXPB_PTR_RING_rxpb_ptr_read_index));    \
		(*(base + O_DLRX_CFG_CTXT_RXPB_PTR_RING_rxpb_ptr_read_index + offset)) |= ((val << B_DLRX_CFG_CTXT_RXPB_PTR_RING_rxpb_ptr_read_index) & M_DLRX_CFG_CTXT_RXPB_PTR_RING_rxpb_ptr_read_index);    \
	} while (0)

#define DLRX_CFG_CTXT_RXPB_PTR_RING_rxpb_ptr_read_index_set_direct(dword, val)    \
	do {                                                               \
		(dword) &= (~(M_DLRX_CFG_CTXT_RXPB_PTR_RING_rxpb_ptr_read_index));    \
		(dword) |= ((val << B_DLRX_CFG_CTXT_RXPB_PTR_RING_rxpb_ptr_read_index) & M_DLRX_CFG_CTXT_RXPB_PTR_RING_rxpb_ptr_read_index);    \
	} while (0)

#define DLRX_CFG_CTXT_RXPB_PTR_RING_rxpb_ptr_read_index_clear_indirect(base, offset)	((*(base + O_DLRX_CFG_CTXT_RXPB_PTR_RING_rxpb_ptr_read_index + offset)) &= (~(M_DLRX_CFG_CTXT_RXPB_PTR_RING_rxpb_ptr_read_index)))

#define DLRX_CFG_CTXT_RXPB_PTR_RING_rxpb_ptr_read_index_clear_direct(dword)	((dword) &= (~(M_DLRX_CFG_CTXT_RXPB_PTR_RING_rxpb_ptr_read_index)))

#define O_DLRX_CFG_CTXT_RXPB_cfg_size_rxpktdes 0
#define B_DLRX_CFG_CTXT_RXPB_cfg_size_rxpktdes 0
#define W_DLRX_CFG_CTXT_RXPB_cfg_size_rxpktdes 32
#define M_DLRX_CFG_CTXT_RXPB_cfg_size_rxpktdes 0xffffffff

#define DLRX_CFG_CTXT_RXPB_cfg_size_rxpktdes_get_indirect(base, offset)	((((*(base + O_DLRX_CFG_CTXT_RXPB_cfg_size_rxpktdes + offset)) & M_DLRX_CFG_CTXT_RXPB_cfg_size_rxpktdes) >> B_DLRX_CFG_CTXT_RXPB_cfg_size_rxpktdes))

#define DLRX_CFG_CTXT_RXPB_cfg_size_rxpktdes_get_direct(dword)	((((dword) & M_DLRX_CFG_CTXT_RXPB_cfg_size_rxpktdes) >> B_DLRX_CFG_CTXT_RXPB_cfg_size_rxpktdes))

#define DLRX_CFG_CTXT_RXPB_cfg_size_rxpktdes_set_indirect(base, offset, val)    \
	do {                                                              \
		(*(base + O_DLRX_CFG_CTXT_RXPB_cfg_size_rxpktdes + offset)) &= (~(M_DLRX_CFG_CTXT_RXPB_cfg_size_rxpktdes));    \
		(*(base + O_DLRX_CFG_CTXT_RXPB_cfg_size_rxpktdes + offset)) |= ((val << B_DLRX_CFG_CTXT_RXPB_cfg_size_rxpktdes) & M_DLRX_CFG_CTXT_RXPB_cfg_size_rxpktdes);    \
	} while (0)

#define DLRX_CFG_CTXT_RXPB_cfg_size_rxpktdes_set_direct(dword, val)    \
	do {                                                               \
		(dword) &= (~(M_DLRX_CFG_CTXT_RXPB_cfg_size_rxpktdes));    \
		(dword) |= ((val << B_DLRX_CFG_CTXT_RXPB_cfg_size_rxpktdes) & M_DLRX_CFG_CTXT_RXPB_cfg_size_rxpktdes);    \
	} while (0)

#define DLRX_CFG_CTXT_RXPB_cfg_size_rxpktdes_clear_indirect(base, offset)	((*(base + O_DLRX_CFG_CTXT_RXPB_cfg_size_rxpktdes + offset)) &= (~(M_DLRX_CFG_CTXT_RXPB_cfg_size_rxpktdes)))

#define DLRX_CFG_CTXT_RXPB_cfg_size_rxpktdes_clear_direct(dword)	((dword) &= (~(M_DLRX_CFG_CTXT_RXPB_cfg_size_rxpktdes)))

#define O_DLRX_CFG_CTXT_RXPB_cfg_offset_atten 1
#define B_DLRX_CFG_CTXT_RXPB_cfg_offset_atten 0
#define W_DLRX_CFG_CTXT_RXPB_cfg_offset_atten 32
#define M_DLRX_CFG_CTXT_RXPB_cfg_offset_atten 0xffffffff

#define DLRX_CFG_CTXT_RXPB_cfg_offset_atten_get_indirect(base, offset)	((((*(base + O_DLRX_CFG_CTXT_RXPB_cfg_offset_atten + offset)) & M_DLRX_CFG_CTXT_RXPB_cfg_offset_atten) >> B_DLRX_CFG_CTXT_RXPB_cfg_offset_atten))

#define DLRX_CFG_CTXT_RXPB_cfg_offset_atten_get_direct(dword)	((((dword) & M_DLRX_CFG_CTXT_RXPB_cfg_offset_atten) >> B_DLRX_CFG_CTXT_RXPB_cfg_offset_atten))

#define DLRX_CFG_CTXT_RXPB_cfg_offset_atten_set_indirect(base, offset, val)    \
	do {                                                              \
		(*(base + O_DLRX_CFG_CTXT_RXPB_cfg_offset_atten + offset)) &= (~(M_DLRX_CFG_CTXT_RXPB_cfg_offset_atten));    \
		(*(base + O_DLRX_CFG_CTXT_RXPB_cfg_offset_atten + offset)) |= ((val << B_DLRX_CFG_CTXT_RXPB_cfg_offset_atten) & M_DLRX_CFG_CTXT_RXPB_cfg_offset_atten);    \
	} while (0)

#define DLRX_CFG_CTXT_RXPB_cfg_offset_atten_set_direct(dword, val)    \
	do {                                                               \
		(dword) &= (~(M_DLRX_CFG_CTXT_RXPB_cfg_offset_atten));    \
		(dword) |= ((val << B_DLRX_CFG_CTXT_RXPB_cfg_offset_atten) & M_DLRX_CFG_CTXT_RXPB_cfg_offset_atten);    \
	} while (0)

#define DLRX_CFG_CTXT_RXPB_cfg_offset_atten_clear_indirect(base, offset)	((*(base + O_DLRX_CFG_CTXT_RXPB_cfg_offset_atten + offset)) &= (~(M_DLRX_CFG_CTXT_RXPB_cfg_offset_atten)))

#define DLRX_CFG_CTXT_RXPB_cfg_offset_atten_clear_direct(dword)	((dword) &= (~(M_DLRX_CFG_CTXT_RXPB_cfg_offset_atten)))

#define O_DLRX_CFG_CTXT_RO_LINKLIST_cfg_badr_ro_linklist 0
#define B_DLRX_CFG_CTXT_RO_LINKLIST_cfg_badr_ro_linklist 0
#define W_DLRX_CFG_CTXT_RO_LINKLIST_cfg_badr_ro_linklist 32
#define M_DLRX_CFG_CTXT_RO_LINKLIST_cfg_badr_ro_linklist 0xffffffff

#define DLRX_CFG_CTXT_RO_LINKLIST_cfg_badr_ro_linklist_get_indirect(base, offset)	((((*(base + O_DLRX_CFG_CTXT_RO_LINKLIST_cfg_badr_ro_linklist + offset)) & M_DLRX_CFG_CTXT_RO_LINKLIST_cfg_badr_ro_linklist) >> B_DLRX_CFG_CTXT_RO_LINKLIST_cfg_badr_ro_linklist))

#define DLRX_CFG_CTXT_RO_LINKLIST_cfg_badr_ro_linklist_get_direct(dword)	((((dword) & M_DLRX_CFG_CTXT_RO_LINKLIST_cfg_badr_ro_linklist) >> B_DLRX_CFG_CTXT_RO_LINKLIST_cfg_badr_ro_linklist))

#define DLRX_CFG_CTXT_RO_LINKLIST_cfg_badr_ro_linklist_set_indirect(base, offset, val)    \
	do {                                                              \
		(*(base + O_DLRX_CFG_CTXT_RO_LINKLIST_cfg_badr_ro_linklist + offset)) &= (~(M_DLRX_CFG_CTXT_RO_LINKLIST_cfg_badr_ro_linklist));    \
		(*(base + O_DLRX_CFG_CTXT_RO_LINKLIST_cfg_badr_ro_linklist + offset)) |= ((val << B_DLRX_CFG_CTXT_RO_LINKLIST_cfg_badr_ro_linklist) & M_DLRX_CFG_CTXT_RO_LINKLIST_cfg_badr_ro_linklist);    \
	} while (0)

#define DLRX_CFG_CTXT_RO_LINKLIST_cfg_badr_ro_linklist_set_direct(dword, val)    \
	do {                                                               \
		(dword) &= (~(M_DLRX_CFG_CTXT_RO_LINKLIST_cfg_badr_ro_linklist));    \
		(dword) |= ((val << B_DLRX_CFG_CTXT_RO_LINKLIST_cfg_badr_ro_linklist) & M_DLRX_CFG_CTXT_RO_LINKLIST_cfg_badr_ro_linklist);    \
	} while (0)

#define DLRX_CFG_CTXT_RO_LINKLIST_cfg_badr_ro_linklist_clear_indirect(base, offset)	((*(base + O_DLRX_CFG_CTXT_RO_LINKLIST_cfg_badr_ro_linklist + offset)) &= (~(M_DLRX_CFG_CTXT_RO_LINKLIST_cfg_badr_ro_linklist)))

#define DLRX_CFG_CTXT_RO_LINKLIST_cfg_badr_ro_linklist_clear_direct(dword)	((dword) &= (~(M_DLRX_CFG_CTXT_RO_LINKLIST_cfg_badr_ro_linklist)))

#define O_DLRX_CFG_CTXT_RO_LINKLIST_cfg_num_ro_linklist 1
#define B_DLRX_CFG_CTXT_RO_LINKLIST_cfg_num_ro_linklist 0
#define W_DLRX_CFG_CTXT_RO_LINKLIST_cfg_num_ro_linklist 32
#define M_DLRX_CFG_CTXT_RO_LINKLIST_cfg_num_ro_linklist 0xffffffff

#define DLRX_CFG_CTXT_RO_LINKLIST_cfg_num_ro_linklist_get_indirect(base, offset)	((((*(base + O_DLRX_CFG_CTXT_RO_LINKLIST_cfg_num_ro_linklist + offset)) & M_DLRX_CFG_CTXT_RO_LINKLIST_cfg_num_ro_linklist) >> B_DLRX_CFG_CTXT_RO_LINKLIST_cfg_num_ro_linklist))

#define DLRX_CFG_CTXT_RO_LINKLIST_cfg_num_ro_linklist_get_direct(dword)	((((dword) & M_DLRX_CFG_CTXT_RO_LINKLIST_cfg_num_ro_linklist) >> B_DLRX_CFG_CTXT_RO_LINKLIST_cfg_num_ro_linklist))

#define DLRX_CFG_CTXT_RO_LINKLIST_cfg_num_ro_linklist_set_indirect(base, offset, val)    \
	do {                                                              \
		(*(base + O_DLRX_CFG_CTXT_RO_LINKLIST_cfg_num_ro_linklist + offset)) &= (~(M_DLRX_CFG_CTXT_RO_LINKLIST_cfg_num_ro_linklist));    \
		(*(base + O_DLRX_CFG_CTXT_RO_LINKLIST_cfg_num_ro_linklist + offset)) |= ((val << B_DLRX_CFG_CTXT_RO_LINKLIST_cfg_num_ro_linklist) & M_DLRX_CFG_CTXT_RO_LINKLIST_cfg_num_ro_linklist);    \
	} while (0)

#define DLRX_CFG_CTXT_RO_LINKLIST_cfg_num_ro_linklist_set_direct(dword, val)    \
	do {                                                               \
		(dword) &= (~(M_DLRX_CFG_CTXT_RO_LINKLIST_cfg_num_ro_linklist));    \
		(dword) |= ((val << B_DLRX_CFG_CTXT_RO_LINKLIST_cfg_num_ro_linklist) & M_DLRX_CFG_CTXT_RO_LINKLIST_cfg_num_ro_linklist);    \
	} while (0)

#define DLRX_CFG_CTXT_RO_LINKLIST_cfg_num_ro_linklist_clear_indirect(base, offset)	((*(base + O_DLRX_CFG_CTXT_RO_LINKLIST_cfg_num_ro_linklist + offset)) &= (~(M_DLRX_CFG_CTXT_RO_LINKLIST_cfg_num_ro_linklist)))

#define DLRX_CFG_CTXT_RO_LINKLIST_cfg_num_ro_linklist_clear_direct(dword)	((dword) &= (~(M_DLRX_CFG_CTXT_RO_LINKLIST_cfg_num_ro_linklist)))

#define O_DLRX_CFG_CTXT_RO_LINKLIST_free_num_ro_linklist 2
#define B_DLRX_CFG_CTXT_RO_LINKLIST_free_num_ro_linklist 0
#define W_DLRX_CFG_CTXT_RO_LINKLIST_free_num_ro_linklist 32
#define M_DLRX_CFG_CTXT_RO_LINKLIST_free_num_ro_linklist 0xffffffff

#define DLRX_CFG_CTXT_RO_LINKLIST_free_num_ro_linklist_get_indirect(base, offset)	((((*(base + O_DLRX_CFG_CTXT_RO_LINKLIST_free_num_ro_linklist + offset)) & M_DLRX_CFG_CTXT_RO_LINKLIST_free_num_ro_linklist) >> B_DLRX_CFG_CTXT_RO_LINKLIST_free_num_ro_linklist))

#define DLRX_CFG_CTXT_RO_LINKLIST_free_num_ro_linklist_get_direct(dword)	((((dword) & M_DLRX_CFG_CTXT_RO_LINKLIST_free_num_ro_linklist) >> B_DLRX_CFG_CTXT_RO_LINKLIST_free_num_ro_linklist))

#define DLRX_CFG_CTXT_RO_LINKLIST_free_num_ro_linklist_set_indirect(base, offset, val)    \
	do {                                                              \
		(*(base + O_DLRX_CFG_CTXT_RO_LINKLIST_free_num_ro_linklist + offset)) &= (~(M_DLRX_CFG_CTXT_RO_LINKLIST_free_num_ro_linklist));    \
		(*(base + O_DLRX_CFG_CTXT_RO_LINKLIST_free_num_ro_linklist + offset)) |= ((val << B_DLRX_CFG_CTXT_RO_LINKLIST_free_num_ro_linklist) & M_DLRX_CFG_CTXT_RO_LINKLIST_free_num_ro_linklist);    \
	} while (0)

#define DLRX_CFG_CTXT_RO_LINKLIST_free_num_ro_linklist_set_direct(dword, val)    \
	do {                                                               \
		(dword) &= (~(M_DLRX_CFG_CTXT_RO_LINKLIST_free_num_ro_linklist));    \
		(dword) |= ((val << B_DLRX_CFG_CTXT_RO_LINKLIST_free_num_ro_linklist) & M_DLRX_CFG_CTXT_RO_LINKLIST_free_num_ro_linklist);    \
	} while (0)

#define DLRX_CFG_CTXT_RO_LINKLIST_free_num_ro_linklist_clear_indirect(base, offset)	((*(base + O_DLRX_CFG_CTXT_RO_LINKLIST_free_num_ro_linklist + offset)) &= (~(M_DLRX_CFG_CTXT_RO_LINKLIST_free_num_ro_linklist)))

#define DLRX_CFG_CTXT_RO_LINKLIST_free_num_ro_linklist_clear_direct(dword)	((dword) &= (~(M_DLRX_CFG_CTXT_RO_LINKLIST_free_num_ro_linklist)))

#define O_DLRX_CFG_CTXT_RO_LINKLIST_cur_ro_des_ptr 3
#define B_DLRX_CFG_CTXT_RO_LINKLIST_cur_ro_des_ptr 0
#define W_DLRX_CFG_CTXT_RO_LINKLIST_cur_ro_des_ptr 32
#define M_DLRX_CFG_CTXT_RO_LINKLIST_cur_ro_des_ptr 0xffffffff

#define DLRX_CFG_CTXT_RO_LINKLIST_cur_ro_des_ptr_get_indirect(base, offset)	((((*(base + O_DLRX_CFG_CTXT_RO_LINKLIST_cur_ro_des_ptr + offset)) & M_DLRX_CFG_CTXT_RO_LINKLIST_cur_ro_des_ptr) >> B_DLRX_CFG_CTXT_RO_LINKLIST_cur_ro_des_ptr))

#define DLRX_CFG_CTXT_RO_LINKLIST_cur_ro_des_ptr_get_direct(dword)	((((dword) & M_DLRX_CFG_CTXT_RO_LINKLIST_cur_ro_des_ptr) >> B_DLRX_CFG_CTXT_RO_LINKLIST_cur_ro_des_ptr))

#define DLRX_CFG_CTXT_RO_LINKLIST_cur_ro_des_ptr_set_indirect(base, offset, val)    \
	do {                                                              \
		(*(base + O_DLRX_CFG_CTXT_RO_LINKLIST_cur_ro_des_ptr + offset)) &= (~(M_DLRX_CFG_CTXT_RO_LINKLIST_cur_ro_des_ptr));    \
		(*(base + O_DLRX_CFG_CTXT_RO_LINKLIST_cur_ro_des_ptr + offset)) |= ((val << B_DLRX_CFG_CTXT_RO_LINKLIST_cur_ro_des_ptr) & M_DLRX_CFG_CTXT_RO_LINKLIST_cur_ro_des_ptr);    \
	} while (0)

#define DLRX_CFG_CTXT_RO_LINKLIST_cur_ro_des_ptr_set_direct(dword, val)    \
	do {                                                               \
		(dword) &= (~(M_DLRX_CFG_CTXT_RO_LINKLIST_cur_ro_des_ptr));    \
		(dword) |= ((val << B_DLRX_CFG_CTXT_RO_LINKLIST_cur_ro_des_ptr) & M_DLRX_CFG_CTXT_RO_LINKLIST_cur_ro_des_ptr);    \
	} while (0)

#define DLRX_CFG_CTXT_RO_LINKLIST_cur_ro_des_ptr_clear_indirect(base, offset)	((*(base + O_DLRX_CFG_CTXT_RO_LINKLIST_cur_ro_des_ptr + offset)) &= (~(M_DLRX_CFG_CTXT_RO_LINKLIST_cur_ro_des_ptr)))

#define DLRX_CFG_CTXT_RO_LINKLIST_cur_ro_des_ptr_clear_direct(dword)	((dword) &= (~(M_DLRX_CFG_CTXT_RO_LINKLIST_cur_ro_des_ptr)))

#define O_DLRX_CFG_CTXT_RO_LINKLIST_cur_ro_des_index 4
#define B_DLRX_CFG_CTXT_RO_LINKLIST_cur_ro_des_index 0
#define W_DLRX_CFG_CTXT_RO_LINKLIST_cur_ro_des_index 32
#define M_DLRX_CFG_CTXT_RO_LINKLIST_cur_ro_des_index 0xffffffff

#define DLRX_CFG_CTXT_RO_LINKLIST_cur_ro_des_index_get_indirect(base, offset)	((((*(base + O_DLRX_CFG_CTXT_RO_LINKLIST_cur_ro_des_index + offset)) & M_DLRX_CFG_CTXT_RO_LINKLIST_cur_ro_des_index) >> B_DLRX_CFG_CTXT_RO_LINKLIST_cur_ro_des_index))

#define DLRX_CFG_CTXT_RO_LINKLIST_cur_ro_des_index_get_direct(dword)	((((dword) & M_DLRX_CFG_CTXT_RO_LINKLIST_cur_ro_des_index) >> B_DLRX_CFG_CTXT_RO_LINKLIST_cur_ro_des_index))

#define DLRX_CFG_CTXT_RO_LINKLIST_cur_ro_des_index_set_indirect(base, offset, val)    \
	do {                                                              \
		(*(base + O_DLRX_CFG_CTXT_RO_LINKLIST_cur_ro_des_index + offset)) &= (~(M_DLRX_CFG_CTXT_RO_LINKLIST_cur_ro_des_index));    \
		(*(base + O_DLRX_CFG_CTXT_RO_LINKLIST_cur_ro_des_index + offset)) |= ((val << B_DLRX_CFG_CTXT_RO_LINKLIST_cur_ro_des_index) & M_DLRX_CFG_CTXT_RO_LINKLIST_cur_ro_des_index);    \
	} while (0)

#define DLRX_CFG_CTXT_RO_LINKLIST_cur_ro_des_index_set_direct(dword, val)    \
	do {                                                               \
		(dword) &= (~(M_DLRX_CFG_CTXT_RO_LINKLIST_cur_ro_des_index));    \
		(dword) |= ((val << B_DLRX_CFG_CTXT_RO_LINKLIST_cur_ro_des_index) & M_DLRX_CFG_CTXT_RO_LINKLIST_cur_ro_des_index);    \
	} while (0)

#define DLRX_CFG_CTXT_RO_LINKLIST_cur_ro_des_index_clear_indirect(base, offset)	((*(base + O_DLRX_CFG_CTXT_RO_LINKLIST_cur_ro_des_index + offset)) &= (~(M_DLRX_CFG_CTXT_RO_LINKLIST_cur_ro_des_index)))

#define DLRX_CFG_CTXT_RO_LINKLIST_cur_ro_des_index_clear_direct(dword)	((dword) &= (~(M_DLRX_CFG_CTXT_RO_LINKLIST_cur_ro_des_index)))

#define O_DLRX_CFG_CTXT_RO_LINKLIST_prev_ro_des_index 5
#define B_DLRX_CFG_CTXT_RO_LINKLIST_prev_ro_des_index 0
#define W_DLRX_CFG_CTXT_RO_LINKLIST_prev_ro_des_index 32
#define M_DLRX_CFG_CTXT_RO_LINKLIST_prev_ro_des_index 0xffffffff

#define DLRX_CFG_CTXT_RO_LINKLIST_prev_ro_des_index_get_indirect(base, offset)	((((*(base + O_DLRX_CFG_CTXT_RO_LINKLIST_prev_ro_des_index + offset)) & M_DLRX_CFG_CTXT_RO_LINKLIST_prev_ro_des_index) >> B_DLRX_CFG_CTXT_RO_LINKLIST_prev_ro_des_index))

#define DLRX_CFG_CTXT_RO_LINKLIST_prev_ro_des_index_get_direct(dword)	((((dword) & M_DLRX_CFG_CTXT_RO_LINKLIST_prev_ro_des_index) >> B_DLRX_CFG_CTXT_RO_LINKLIST_prev_ro_des_index))

#define DLRX_CFG_CTXT_RO_LINKLIST_prev_ro_des_index_set_indirect(base, offset, val)    \
	do {                                                              \
		(*(base + O_DLRX_CFG_CTXT_RO_LINKLIST_prev_ro_des_index + offset)) &= (~(M_DLRX_CFG_CTXT_RO_LINKLIST_prev_ro_des_index));    \
		(*(base + O_DLRX_CFG_CTXT_RO_LINKLIST_prev_ro_des_index + offset)) |= ((val << B_DLRX_CFG_CTXT_RO_LINKLIST_prev_ro_des_index) & M_DLRX_CFG_CTXT_RO_LINKLIST_prev_ro_des_index);    \
	} while (0)

#define DLRX_CFG_CTXT_RO_LINKLIST_prev_ro_des_index_set_direct(dword, val)    \
	do {                                                               \
		(dword) &= (~(M_DLRX_CFG_CTXT_RO_LINKLIST_prev_ro_des_index));    \
		(dword) |= ((val << B_DLRX_CFG_CTXT_RO_LINKLIST_prev_ro_des_index) & M_DLRX_CFG_CTXT_RO_LINKLIST_prev_ro_des_index);    \
	} while (0)

#define DLRX_CFG_CTXT_RO_LINKLIST_prev_ro_des_index_clear_indirect(base, offset)	((*(base + O_DLRX_CFG_CTXT_RO_LINKLIST_prev_ro_des_index + offset)) &= (~(M_DLRX_CFG_CTXT_RO_LINKLIST_prev_ro_des_index)))

#define DLRX_CFG_CTXT_RO_LINKLIST_prev_ro_des_index_clear_direct(dword)	((dword) &= (~(M_DLRX_CFG_CTXT_RO_LINKLIST_prev_ro_des_index)))

#define O_DLRX_CFG_CTXT_RO_LINKLIST_ro_des_free_head_index 6
#define B_DLRX_CFG_CTXT_RO_LINKLIST_ro_des_free_head_index 0
#define W_DLRX_CFG_CTXT_RO_LINKLIST_ro_des_free_head_index 32
#define M_DLRX_CFG_CTXT_RO_LINKLIST_ro_des_free_head_index 0xffffffff

#define DLRX_CFG_CTXT_RO_LINKLIST_ro_des_free_head_index_get_indirect(base, offset)	((((*(base + O_DLRX_CFG_CTXT_RO_LINKLIST_ro_des_free_head_index + offset)) & M_DLRX_CFG_CTXT_RO_LINKLIST_ro_des_free_head_index) >> B_DLRX_CFG_CTXT_RO_LINKLIST_ro_des_free_head_index))

#define DLRX_CFG_CTXT_RO_LINKLIST_ro_des_free_head_index_get_direct(dword)	((((dword) & M_DLRX_CFG_CTXT_RO_LINKLIST_ro_des_free_head_index) >> B_DLRX_CFG_CTXT_RO_LINKLIST_ro_des_free_head_index))

#define DLRX_CFG_CTXT_RO_LINKLIST_ro_des_free_head_index_set_indirect(base, offset, val)    \
	do {                                                              \
		(*(base + O_DLRX_CFG_CTXT_RO_LINKLIST_ro_des_free_head_index + offset)) &= (~(M_DLRX_CFG_CTXT_RO_LINKLIST_ro_des_free_head_index));    \
		(*(base + O_DLRX_CFG_CTXT_RO_LINKLIST_ro_des_free_head_index + offset)) |= ((val << B_DLRX_CFG_CTXT_RO_LINKLIST_ro_des_free_head_index) & M_DLRX_CFG_CTXT_RO_LINKLIST_ro_des_free_head_index);    \
	} while (0)

#define DLRX_CFG_CTXT_RO_LINKLIST_ro_des_free_head_index_set_direct(dword, val)    \
	do {                                                               \
		(dword) &= (~(M_DLRX_CFG_CTXT_RO_LINKLIST_ro_des_free_head_index));    \
		(dword) |= ((val << B_DLRX_CFG_CTXT_RO_LINKLIST_ro_des_free_head_index) & M_DLRX_CFG_CTXT_RO_LINKLIST_ro_des_free_head_index);    \
	} while (0)

#define DLRX_CFG_CTXT_RO_LINKLIST_ro_des_free_head_index_clear_indirect(base, offset)	((*(base + O_DLRX_CFG_CTXT_RO_LINKLIST_ro_des_free_head_index + offset)) &= (~(M_DLRX_CFG_CTXT_RO_LINKLIST_ro_des_free_head_index)))

#define DLRX_CFG_CTXT_RO_LINKLIST_ro_des_free_head_index_clear_direct(dword)	((dword) &= (~(M_DLRX_CFG_CTXT_RO_LINKLIST_ro_des_free_head_index)))

#define O_DLRX_CFG_CTXT_RO_LINKLIST_ro_des_free_tail_index 7
#define B_DLRX_CFG_CTXT_RO_LINKLIST_ro_des_free_tail_index 0
#define W_DLRX_CFG_CTXT_RO_LINKLIST_ro_des_free_tail_index 32
#define M_DLRX_CFG_CTXT_RO_LINKLIST_ro_des_free_tail_index 0xffffffff

#define DLRX_CFG_CTXT_RO_LINKLIST_ro_des_free_tail_index_get_indirect(base, offset)	((((*(base + O_DLRX_CFG_CTXT_RO_LINKLIST_ro_des_free_tail_index + offset)) & M_DLRX_CFG_CTXT_RO_LINKLIST_ro_des_free_tail_index) >> B_DLRX_CFG_CTXT_RO_LINKLIST_ro_des_free_tail_index))

#define DLRX_CFG_CTXT_RO_LINKLIST_ro_des_free_tail_index_get_direct(dword)	((((dword) & M_DLRX_CFG_CTXT_RO_LINKLIST_ro_des_free_tail_index) >> B_DLRX_CFG_CTXT_RO_LINKLIST_ro_des_free_tail_index))

#define DLRX_CFG_CTXT_RO_LINKLIST_ro_des_free_tail_index_set_indirect(base, offset, val)    \
	do {                                                              \
		(*(base + O_DLRX_CFG_CTXT_RO_LINKLIST_ro_des_free_tail_index + offset)) &= (~(M_DLRX_CFG_CTXT_RO_LINKLIST_ro_des_free_tail_index));    \
		(*(base + O_DLRX_CFG_CTXT_RO_LINKLIST_ro_des_free_tail_index + offset)) |= ((val << B_DLRX_CFG_CTXT_RO_LINKLIST_ro_des_free_tail_index) & M_DLRX_CFG_CTXT_RO_LINKLIST_ro_des_free_tail_index);    \
	} while (0)

#define DLRX_CFG_CTXT_RO_LINKLIST_ro_des_free_tail_index_set_direct(dword, val)    \
	do {                                                               \
		(dword) &= (~(M_DLRX_CFG_CTXT_RO_LINKLIST_ro_des_free_tail_index));    \
		(dword) |= ((val << B_DLRX_CFG_CTXT_RO_LINKLIST_ro_des_free_tail_index) & M_DLRX_CFG_CTXT_RO_LINKLIST_ro_des_free_tail_index);    \
	} while (0)

#define DLRX_CFG_CTXT_RO_LINKLIST_ro_des_free_tail_index_clear_indirect(base, offset)	((*(base + O_DLRX_CFG_CTXT_RO_LINKLIST_ro_des_free_tail_index + offset)) &= (~(M_DLRX_CFG_CTXT_RO_LINKLIST_ro_des_free_tail_index)))

#define DLRX_CFG_CTXT_RO_LINKLIST_ro_des_free_tail_index_clear_direct(dword)	((dword) &= (~(M_DLRX_CFG_CTXT_RO_LINKLIST_ro_des_free_tail_index)))

#define O_DLRX_CFG_CTXT_RO_MAINLIST_cfg_badr_ro_mainlist 0
#define B_DLRX_CFG_CTXT_RO_MAINLIST_cfg_badr_ro_mainlist 0
#define W_DLRX_CFG_CTXT_RO_MAINLIST_cfg_badr_ro_mainlist 32
#define M_DLRX_CFG_CTXT_RO_MAINLIST_cfg_badr_ro_mainlist 0xffffffff

#define DLRX_CFG_CTXT_RO_MAINLIST_cfg_badr_ro_mainlist_get_indirect(base, offset)	((((*(base + O_DLRX_CFG_CTXT_RO_MAINLIST_cfg_badr_ro_mainlist + offset)) & M_DLRX_CFG_CTXT_RO_MAINLIST_cfg_badr_ro_mainlist) >> B_DLRX_CFG_CTXT_RO_MAINLIST_cfg_badr_ro_mainlist))

#define DLRX_CFG_CTXT_RO_MAINLIST_cfg_badr_ro_mainlist_get_direct(dword)	((((dword) & M_DLRX_CFG_CTXT_RO_MAINLIST_cfg_badr_ro_mainlist) >> B_DLRX_CFG_CTXT_RO_MAINLIST_cfg_badr_ro_mainlist))

#define DLRX_CFG_CTXT_RO_MAINLIST_cfg_badr_ro_mainlist_set_indirect(base, offset, val)    \
	do {                                                              \
		(*(base + O_DLRX_CFG_CTXT_RO_MAINLIST_cfg_badr_ro_mainlist + offset)) &= (~(M_DLRX_CFG_CTXT_RO_MAINLIST_cfg_badr_ro_mainlist));    \
		(*(base + O_DLRX_CFG_CTXT_RO_MAINLIST_cfg_badr_ro_mainlist + offset)) |= ((val << B_DLRX_CFG_CTXT_RO_MAINLIST_cfg_badr_ro_mainlist) & M_DLRX_CFG_CTXT_RO_MAINLIST_cfg_badr_ro_mainlist);    \
	} while (0)

#define DLRX_CFG_CTXT_RO_MAINLIST_cfg_badr_ro_mainlist_set_direct(dword, val)    \
	do {                                                               \
		(dword) &= (~(M_DLRX_CFG_CTXT_RO_MAINLIST_cfg_badr_ro_mainlist));    \
		(dword) |= ((val << B_DLRX_CFG_CTXT_RO_MAINLIST_cfg_badr_ro_mainlist) & M_DLRX_CFG_CTXT_RO_MAINLIST_cfg_badr_ro_mainlist);    \
	} while (0)

#define DLRX_CFG_CTXT_RO_MAINLIST_cfg_badr_ro_mainlist_clear_indirect(base, offset)	((*(base + O_DLRX_CFG_CTXT_RO_MAINLIST_cfg_badr_ro_mainlist + offset)) &= (~(M_DLRX_CFG_CTXT_RO_MAINLIST_cfg_badr_ro_mainlist)))

#define DLRX_CFG_CTXT_RO_MAINLIST_cfg_badr_ro_mainlist_clear_direct(dword)	((dword) &= (~(M_DLRX_CFG_CTXT_RO_MAINLIST_cfg_badr_ro_mainlist)))

#define O_DLRX_CFG_CTXT_RO_MAINLIST_cfg_num_ro_mainlist 1
#define B_DLRX_CFG_CTXT_RO_MAINLIST_cfg_num_ro_mainlist 0
#define W_DLRX_CFG_CTXT_RO_MAINLIST_cfg_num_ro_mainlist 32
#define M_DLRX_CFG_CTXT_RO_MAINLIST_cfg_num_ro_mainlist 0xffffffff

#define DLRX_CFG_CTXT_RO_MAINLIST_cfg_num_ro_mainlist_get_indirect(base, offset)	((((*(base + O_DLRX_CFG_CTXT_RO_MAINLIST_cfg_num_ro_mainlist + offset)) & M_DLRX_CFG_CTXT_RO_MAINLIST_cfg_num_ro_mainlist) >> B_DLRX_CFG_CTXT_RO_MAINLIST_cfg_num_ro_mainlist))

#define DLRX_CFG_CTXT_RO_MAINLIST_cfg_num_ro_mainlist_get_direct(dword)	((((dword) & M_DLRX_CFG_CTXT_RO_MAINLIST_cfg_num_ro_mainlist) >> B_DLRX_CFG_CTXT_RO_MAINLIST_cfg_num_ro_mainlist))

#define DLRX_CFG_CTXT_RO_MAINLIST_cfg_num_ro_mainlist_set_indirect(base, offset, val)    \
	do {                                                              \
		(*(base + O_DLRX_CFG_CTXT_RO_MAINLIST_cfg_num_ro_mainlist + offset)) &= (~(M_DLRX_CFG_CTXT_RO_MAINLIST_cfg_num_ro_mainlist));    \
		(*(base + O_DLRX_CFG_CTXT_RO_MAINLIST_cfg_num_ro_mainlist + offset)) |= ((val << B_DLRX_CFG_CTXT_RO_MAINLIST_cfg_num_ro_mainlist) & M_DLRX_CFG_CTXT_RO_MAINLIST_cfg_num_ro_mainlist);    \
	} while (0)

#define DLRX_CFG_CTXT_RO_MAINLIST_cfg_num_ro_mainlist_set_direct(dword, val)    \
	do {                                                               \
		(dword) &= (~(M_DLRX_CFG_CTXT_RO_MAINLIST_cfg_num_ro_mainlist));    \
		(dword) |= ((val << B_DLRX_CFG_CTXT_RO_MAINLIST_cfg_num_ro_mainlist) & M_DLRX_CFG_CTXT_RO_MAINLIST_cfg_num_ro_mainlist);    \
	} while (0)

#define DLRX_CFG_CTXT_RO_MAINLIST_cfg_num_ro_mainlist_clear_indirect(base, offset)	((*(base + O_DLRX_CFG_CTXT_RO_MAINLIST_cfg_num_ro_mainlist + offset)) &= (~(M_DLRX_CFG_CTXT_RO_MAINLIST_cfg_num_ro_mainlist)))

#define DLRX_CFG_CTXT_RO_MAINLIST_cfg_num_ro_mainlist_clear_direct(dword)	((dword) &= (~(M_DLRX_CFG_CTXT_RO_MAINLIST_cfg_num_ro_mainlist)))

#define O_DLRX_CFG_CTXT_RO_MAINLIST_ro_mainlist_ptr 2
#define B_DLRX_CFG_CTXT_RO_MAINLIST_ro_mainlist_ptr 0
#define W_DLRX_CFG_CTXT_RO_MAINLIST_ro_mainlist_ptr 32
#define M_DLRX_CFG_CTXT_RO_MAINLIST_ro_mainlist_ptr 0xffffffff

#define DLRX_CFG_CTXT_RO_MAINLIST_ro_mainlist_ptr_get_indirect(base, offset)	((((*(base + O_DLRX_CFG_CTXT_RO_MAINLIST_ro_mainlist_ptr + offset)) & M_DLRX_CFG_CTXT_RO_MAINLIST_ro_mainlist_ptr) >> B_DLRX_CFG_CTXT_RO_MAINLIST_ro_mainlist_ptr))

#define DLRX_CFG_CTXT_RO_MAINLIST_ro_mainlist_ptr_get_direct(dword)	((((dword) & M_DLRX_CFG_CTXT_RO_MAINLIST_ro_mainlist_ptr) >> B_DLRX_CFG_CTXT_RO_MAINLIST_ro_mainlist_ptr))

#define DLRX_CFG_CTXT_RO_MAINLIST_ro_mainlist_ptr_set_indirect(base, offset, val)    \
	do {                                                              \
		(*(base + O_DLRX_CFG_CTXT_RO_MAINLIST_ro_mainlist_ptr + offset)) &= (~(M_DLRX_CFG_CTXT_RO_MAINLIST_ro_mainlist_ptr));    \
		(*(base + O_DLRX_CFG_CTXT_RO_MAINLIST_ro_mainlist_ptr + offset)) |= ((val << B_DLRX_CFG_CTXT_RO_MAINLIST_ro_mainlist_ptr) & M_DLRX_CFG_CTXT_RO_MAINLIST_ro_mainlist_ptr);    \
	} while (0)

#define DLRX_CFG_CTXT_RO_MAINLIST_ro_mainlist_ptr_set_direct(dword, val)    \
	do {                                                               \
		(dword) &= (~(M_DLRX_CFG_CTXT_RO_MAINLIST_ro_mainlist_ptr));    \
		(dword) |= ((val << B_DLRX_CFG_CTXT_RO_MAINLIST_ro_mainlist_ptr) & M_DLRX_CFG_CTXT_RO_MAINLIST_ro_mainlist_ptr);    \
	} while (0)

#define DLRX_CFG_CTXT_RO_MAINLIST_ro_mainlist_ptr_clear_indirect(base, offset)	((*(base + O_DLRX_CFG_CTXT_RO_MAINLIST_ro_mainlist_ptr + offset)) &= (~(M_DLRX_CFG_CTXT_RO_MAINLIST_ro_mainlist_ptr)))

#define DLRX_CFG_CTXT_RO_MAINLIST_ro_mainlist_ptr_clear_direct(dword)	((dword) &= (~(M_DLRX_CFG_CTXT_RO_MAINLIST_ro_mainlist_ptr)))

#define O_DLRX_CTXT_MSG_mpdu_cnt 0
#define B_DLRX_CTXT_MSG_mpdu_cnt 0
#define W_DLRX_CTXT_MSG_mpdu_cnt 32
#define M_DLRX_CTXT_MSG_mpdu_cnt 0xffffffff

#define DLRX_CTXT_MSG_mpdu_cnt_get_indirect(base, offset)	((((*(base + O_DLRX_CTXT_MSG_mpdu_cnt + offset)) & M_DLRX_CTXT_MSG_mpdu_cnt) >> B_DLRX_CTXT_MSG_mpdu_cnt))

#define DLRX_CTXT_MSG_mpdu_cnt_get_direct(dword)	((((dword) & M_DLRX_CTXT_MSG_mpdu_cnt) >> B_DLRX_CTXT_MSG_mpdu_cnt))

#define DLRX_CTXT_MSG_mpdu_cnt_set_indirect(base, offset, val)    \
	do {                                                              \
		(*(base + O_DLRX_CTXT_MSG_mpdu_cnt + offset)) &= (~(M_DLRX_CTXT_MSG_mpdu_cnt));    \
		(*(base + O_DLRX_CTXT_MSG_mpdu_cnt + offset)) |= ((val << B_DLRX_CTXT_MSG_mpdu_cnt) & M_DLRX_CTXT_MSG_mpdu_cnt);    \
	} while (0)

#define DLRX_CTXT_MSG_mpdu_cnt_set_direct(dword, val)    \
	do {                                                               \
		(dword) &= (~(M_DLRX_CTXT_MSG_mpdu_cnt));    \
		(dword) |= ((val << B_DLRX_CTXT_MSG_mpdu_cnt) & M_DLRX_CTXT_MSG_mpdu_cnt);    \
	} while (0)

#define DLRX_CTXT_MSG_mpdu_cnt_clear_indirect(base, offset)	((*(base + O_DLRX_CTXT_MSG_mpdu_cnt + offset)) &= (~(M_DLRX_CTXT_MSG_mpdu_cnt)))

#define DLRX_CTXT_MSG_mpdu_cnt_clear_direct(dword)	((dword) &= (~(M_DLRX_CTXT_MSG_mpdu_cnt)))

#define O_DLRX_CTXT_MSG_mpdu_status 1
#define B_DLRX_CTXT_MSG_mpdu_status 0
#define W_DLRX_CTXT_MSG_mpdu_status 32
#define M_DLRX_CTXT_MSG_mpdu_status 0xffffffff

#define DLRX_CTXT_MSG_mpdu_status_get_indirect(base, offset)	((((*(base + O_DLRX_CTXT_MSG_mpdu_status + offset)) & M_DLRX_CTXT_MSG_mpdu_status) >> B_DLRX_CTXT_MSG_mpdu_status))

#define DLRX_CTXT_MSG_mpdu_status_get_direct(dword)	((((dword) & M_DLRX_CTXT_MSG_mpdu_status) >> B_DLRX_CTXT_MSG_mpdu_status))

#define DLRX_CTXT_MSG_mpdu_status_set_indirect(base, offset, val)    \
	do {                                                              \
		(*(base + O_DLRX_CTXT_MSG_mpdu_status + offset)) &= (~(M_DLRX_CTXT_MSG_mpdu_status));    \
		(*(base + O_DLRX_CTXT_MSG_mpdu_status + offset)) |= ((val << B_DLRX_CTXT_MSG_mpdu_status) & M_DLRX_CTXT_MSG_mpdu_status);    \
	} while (0)

#define DLRX_CTXT_MSG_mpdu_status_set_direct(dword, val)    \
	do {                                                               \
		(dword) &= (~(M_DLRX_CTXT_MSG_mpdu_status));    \
		(dword) |= ((val << B_DLRX_CTXT_MSG_mpdu_status) & M_DLRX_CTXT_MSG_mpdu_status);    \
	} while (0)

#define DLRX_CTXT_MSG_mpdu_status_clear_indirect(base, offset)	((*(base + O_DLRX_CTXT_MSG_mpdu_status + offset)) &= (~(M_DLRX_CTXT_MSG_mpdu_status)))

#define DLRX_CTXT_MSG_mpdu_status_clear_direct(dword)	((dword) &= (~(M_DLRX_CTXT_MSG_mpdu_status)))

#define O_DLRX_CTXT_MSG_mpdu_range_index 2
#define B_DLRX_CTXT_MSG_mpdu_range_index 0
#define W_DLRX_CTXT_MSG_mpdu_range_index 32
#define M_DLRX_CTXT_MSG_mpdu_range_index 0xffffffff

#define DLRX_CTXT_MSG_mpdu_range_index_get_indirect(base, offset)	((((*(base + O_DLRX_CTXT_MSG_mpdu_range_index + offset)) & M_DLRX_CTXT_MSG_mpdu_range_index) >> B_DLRX_CTXT_MSG_mpdu_range_index))

#define DLRX_CTXT_MSG_mpdu_range_index_get_direct(dword)	((((dword) & M_DLRX_CTXT_MSG_mpdu_range_index) >> B_DLRX_CTXT_MSG_mpdu_range_index))

#define DLRX_CTXT_MSG_mpdu_range_index_set_indirect(base, offset, val)    \
	do {                                                              \
		(*(base + O_DLRX_CTXT_MSG_mpdu_range_index + offset)) &= (~(M_DLRX_CTXT_MSG_mpdu_range_index));    \
		(*(base + O_DLRX_CTXT_MSG_mpdu_range_index + offset)) |= ((val << B_DLRX_CTXT_MSG_mpdu_range_index) & M_DLRX_CTXT_MSG_mpdu_range_index);    \
	} while (0)

#define DLRX_CTXT_MSG_mpdu_range_index_set_direct(dword, val)    \
	do {                                                               \
		(dword) &= (~(M_DLRX_CTXT_MSG_mpdu_range_index));    \
		(dword) |= ((val << B_DLRX_CTXT_MSG_mpdu_range_index) & M_DLRX_CTXT_MSG_mpdu_range_index);    \
	} while (0)

#define DLRX_CTXT_MSG_mpdu_range_index_clear_indirect(base, offset)	((*(base + O_DLRX_CTXT_MSG_mpdu_range_index + offset)) &= (~(M_DLRX_CTXT_MSG_mpdu_range_index)))

#define DLRX_CTXT_MSG_mpdu_range_index_clear_direct(dword)	((dword) &= (~(M_DLRX_CTXT_MSG_mpdu_range_index)))

#define O_DLRX_CTXT_MSG_mpdu_index 3
#define B_DLRX_CTXT_MSG_mpdu_index 0
#define W_DLRX_CTXT_MSG_mpdu_index 32
#define M_DLRX_CTXT_MSG_mpdu_index 0xffffffff

#define DLRX_CTXT_MSG_mpdu_index_get_indirect(base, offset)	((((*(base + O_DLRX_CTXT_MSG_mpdu_index + offset)) & M_DLRX_CTXT_MSG_mpdu_index) >> B_DLRX_CTXT_MSG_mpdu_index))

#define DLRX_CTXT_MSG_mpdu_index_get_direct(dword)	((((dword) & M_DLRX_CTXT_MSG_mpdu_index) >> B_DLRX_CTXT_MSG_mpdu_index))

#define DLRX_CTXT_MSG_mpdu_index_set_indirect(base, offset, val)    \
	do {                                                              \
		(*(base + O_DLRX_CTXT_MSG_mpdu_index + offset)) &= (~(M_DLRX_CTXT_MSG_mpdu_index));    \
		(*(base + O_DLRX_CTXT_MSG_mpdu_index + offset)) |= ((val << B_DLRX_CTXT_MSG_mpdu_index) & M_DLRX_CTXT_MSG_mpdu_index);    \
	} while (0)

#define DLRX_CTXT_MSG_mpdu_index_set_direct(dword, val)    \
	do {                                                               \
		(dword) &= (~(M_DLRX_CTXT_MSG_mpdu_index));    \
		(dword) |= ((val << B_DLRX_CTXT_MSG_mpdu_index) & M_DLRX_CTXT_MSG_mpdu_index);    \
	} while (0)

#define DLRX_CTXT_MSG_mpdu_index_clear_indirect(base, offset)	((*(base + O_DLRX_CTXT_MSG_mpdu_index + offset)) &= (~(M_DLRX_CTXT_MSG_mpdu_index)))

#define DLRX_CTXT_MSG_mpdu_index_clear_direct(dword)	((dword) &= (~(M_DLRX_CTXT_MSG_mpdu_index)))

#define O_DLRX_CTXT_MSG_msdu_mpdu_index 4
#define B_DLRX_CTXT_MSG_msdu_mpdu_index 0
#define W_DLRX_CTXT_MSG_msdu_mpdu_index 32
#define M_DLRX_CTXT_MSG_msdu_mpdu_index 0xffffffff

#define DLRX_CTXT_MSG_msdu_mpdu_index_get_indirect(base, offset)	((((*(base + O_DLRX_CTXT_MSG_msdu_mpdu_index + offset)) & M_DLRX_CTXT_MSG_msdu_mpdu_index) >> B_DLRX_CTXT_MSG_msdu_mpdu_index))

#define DLRX_CTXT_MSG_msdu_mpdu_index_get_direct(dword)	((((dword) & M_DLRX_CTXT_MSG_msdu_mpdu_index) >> B_DLRX_CTXT_MSG_msdu_mpdu_index))

#define DLRX_CTXT_MSG_msdu_mpdu_index_set_indirect(base, offset, val)    \
	do {                                                              \
		(*(base + O_DLRX_CTXT_MSG_msdu_mpdu_index + offset)) &= (~(M_DLRX_CTXT_MSG_msdu_mpdu_index));    \
		(*(base + O_DLRX_CTXT_MSG_msdu_mpdu_index + offset)) |= ((val << B_DLRX_CTXT_MSG_msdu_mpdu_index) & M_DLRX_CTXT_MSG_msdu_mpdu_index);    \
	} while (0)

#define DLRX_CTXT_MSG_msdu_mpdu_index_set_direct(dword, val)    \
	do {                                                               \
		(dword) &= (~(M_DLRX_CTXT_MSG_msdu_mpdu_index));    \
		(dword) |= ((val << B_DLRX_CTXT_MSG_msdu_mpdu_index) & M_DLRX_CTXT_MSG_msdu_mpdu_index);    \
	} while (0)

#define DLRX_CTXT_MSG_msdu_mpdu_index_clear_indirect(base, offset)	((*(base + O_DLRX_CTXT_MSG_msdu_mpdu_index + offset)) &= (~(M_DLRX_CTXT_MSG_msdu_mpdu_index)))

#define DLRX_CTXT_MSG_msdu_mpdu_index_clear_direct(dword)	((dword) &= (~(M_DLRX_CTXT_MSG_msdu_mpdu_index)))

#define O_DLRX_CTXT_MSG_msdu_index 5
#define B_DLRX_CTXT_MSG_msdu_index 0
#define W_DLRX_CTXT_MSG_msdu_index 32
#define M_DLRX_CTXT_MSG_msdu_index 0xffffffff

#define DLRX_CTXT_MSG_msdu_index_get_indirect(base, offset)	((((*(base + O_DLRX_CTXT_MSG_msdu_index + offset)) & M_DLRX_CTXT_MSG_msdu_index) >> B_DLRX_CTXT_MSG_msdu_index))

#define DLRX_CTXT_MSG_msdu_index_get_direct(dword)	((((dword) & M_DLRX_CTXT_MSG_msdu_index) >> B_DLRX_CTXT_MSG_msdu_index))

#define DLRX_CTXT_MSG_msdu_index_set_indirect(base, offset, val)    \
	do {                                                              \
		(*(base + O_DLRX_CTXT_MSG_msdu_index + offset)) &= (~(M_DLRX_CTXT_MSG_msdu_index));    \
		(*(base + O_DLRX_CTXT_MSG_msdu_index + offset)) |= ((val << B_DLRX_CTXT_MSG_msdu_index) & M_DLRX_CTXT_MSG_msdu_index);    \
	} while (0)

#define DLRX_CTXT_MSG_msdu_index_set_direct(dword, val)    \
	do {                                                               \
		(dword) &= (~(M_DLRX_CTXT_MSG_msdu_index));    \
		(dword) |= ((val << B_DLRX_CTXT_MSG_msdu_index) & M_DLRX_CTXT_MSG_msdu_index);    \
	} while (0)

#define DLRX_CTXT_MSG_msdu_index_clear_indirect(base, offset)	((*(base + O_DLRX_CTXT_MSG_msdu_index + offset)) &= (~(M_DLRX_CTXT_MSG_msdu_index)))

#define DLRX_CTXT_MSG_msdu_index_clear_direct(dword)	((dword) &= (~(M_DLRX_CTXT_MSG_msdu_index)))

#define O_DLRX_CTXT_MSG_peer 6
#define B_DLRX_CTXT_MSG_peer 0
#define W_DLRX_CTXT_MSG_peer 32
#define M_DLRX_CTXT_MSG_peer 0xffffffff

#define DLRX_CTXT_MSG_peer_get_indirect(base, offset)	((((*(base + O_DLRX_CTXT_MSG_peer + offset)) & M_DLRX_CTXT_MSG_peer) >> B_DLRX_CTXT_MSG_peer))

#define DLRX_CTXT_MSG_peer_get_direct(dword)	((((dword) & M_DLRX_CTXT_MSG_peer) >> B_DLRX_CTXT_MSG_peer))

#define DLRX_CTXT_MSG_peer_set_indirect(base, offset, val)    \
	do {                                                              \
		(*(base + O_DLRX_CTXT_MSG_peer + offset)) &= (~(M_DLRX_CTXT_MSG_peer));    \
		(*(base + O_DLRX_CTXT_MSG_peer + offset)) |= ((val << B_DLRX_CTXT_MSG_peer) & M_DLRX_CTXT_MSG_peer);    \
	} while (0)

#define DLRX_CTXT_MSG_peer_set_direct(dword, val)    \
	do {                                                               \
		(dword) &= (~(M_DLRX_CTXT_MSG_peer));    \
		(dword) |= ((val << B_DLRX_CTXT_MSG_peer) & M_DLRX_CTXT_MSG_peer);    \
	} while (0)

#define DLRX_CTXT_MSG_peer_clear_indirect(base, offset)	((*(base + O_DLRX_CTXT_MSG_peer + offset)) &= (~(M_DLRX_CTXT_MSG_peer)))

#define DLRX_CTXT_MSG_peer_clear_direct(dword)	((dword) &= (~(M_DLRX_CTXT_MSG_peer)))

#define O_DLRX_CTXT_MSG_ext_tid 7
#define B_DLRX_CTXT_MSG_ext_tid 0
#define W_DLRX_CTXT_MSG_ext_tid 32
#define M_DLRX_CTXT_MSG_ext_tid 0xffffffff

#define DLRX_CTXT_MSG_ext_tid_get_indirect(base, offset)	((((*(base + O_DLRX_CTXT_MSG_ext_tid + offset)) & M_DLRX_CTXT_MSG_ext_tid) >> B_DLRX_CTXT_MSG_ext_tid))

#define DLRX_CTXT_MSG_ext_tid_get_direct(dword)	((((dword) & M_DLRX_CTXT_MSG_ext_tid) >> B_DLRX_CTXT_MSG_ext_tid))

#define DLRX_CTXT_MSG_ext_tid_set_indirect(base, offset, val)    \
	do {                                                              \
		(*(base + O_DLRX_CTXT_MSG_ext_tid + offset)) &= (~(M_DLRX_CTXT_MSG_ext_tid));    \
		(*(base + O_DLRX_CTXT_MSG_ext_tid + offset)) |= ((val << B_DLRX_CTXT_MSG_ext_tid) & M_DLRX_CTXT_MSG_ext_tid);    \
	} while (0)

#define DLRX_CTXT_MSG_ext_tid_set_direct(dword, val)    \
	do {                                                               \
		(dword) &= (~(M_DLRX_CTXT_MSG_ext_tid));    \
		(dword) |= ((val << B_DLRX_CTXT_MSG_ext_tid) & M_DLRX_CTXT_MSG_ext_tid);    \
	} while (0)

#define DLRX_CTXT_MSG_ext_tid_clear_indirect(base, offset)	((*(base + O_DLRX_CTXT_MSG_ext_tid + offset)) &= (~(M_DLRX_CTXT_MSG_ext_tid)))

#define DLRX_CTXT_MSG_ext_tid_clear_direct(dword)	((dword) &= (~(M_DLRX_CTXT_MSG_ext_tid)))

#define O_DLRX_CTXT_MSG_seqid 8
#define B_DLRX_CTXT_MSG_seqid 0
#define W_DLRX_CTXT_MSG_seqid 32
#define M_DLRX_CTXT_MSG_seqid 0xffffffff

#define DLRX_CTXT_MSG_seqid_get_indirect(base, offset)	((((*(base + O_DLRX_CTXT_MSG_seqid + offset)) & M_DLRX_CTXT_MSG_seqid) >> B_DLRX_CTXT_MSG_seqid))

#define DLRX_CTXT_MSG_seqid_get_direct(dword)	((((dword) & M_DLRX_CTXT_MSG_seqid) >> B_DLRX_CTXT_MSG_seqid))

#define DLRX_CTXT_MSG_seqid_set_indirect(base, offset, val)    \
	do {                                                              \
		(*(base + O_DLRX_CTXT_MSG_seqid + offset)) &= (~(M_DLRX_CTXT_MSG_seqid));    \
		(*(base + O_DLRX_CTXT_MSG_seqid + offset)) |= ((val << B_DLRX_CTXT_MSG_seqid) & M_DLRX_CTXT_MSG_seqid);    \
	} while (0)

#define DLRX_CTXT_MSG_seqid_set_direct(dword, val)    \
	do {                                                               \
		(dword) &= (~(M_DLRX_CTXT_MSG_seqid));    \
		(dword) |= ((val << B_DLRX_CTXT_MSG_seqid) & M_DLRX_CTXT_MSG_seqid);    \
	} while (0)

#define DLRX_CTXT_MSG_seqid_clear_indirect(base, offset)	((*(base + O_DLRX_CTXT_MSG_seqid + offset)) &= (~(M_DLRX_CTXT_MSG_seqid)))

#define DLRX_CTXT_MSG_seqid_clear_direct(dword)	((dword) &= (~(M_DLRX_CTXT_MSG_seqid)))

#define O_DLRX_CTXT_MSG_total_seqid 9
#define B_DLRX_CTXT_MSG_total_seqid 0
#define W_DLRX_CTXT_MSG_total_seqid 32
#define M_DLRX_CTXT_MSG_total_seqid 0xffffffff

#define DLRX_CTXT_MSG_total_seqid_get_indirect(base, offset)	((((*(base + O_DLRX_CTXT_MSG_total_seqid + offset)) & M_DLRX_CTXT_MSG_total_seqid) >> B_DLRX_CTXT_MSG_total_seqid))

#define DLRX_CTXT_MSG_total_seqid_get_direct(dword)	((((dword) & M_DLRX_CTXT_MSG_total_seqid) >> B_DLRX_CTXT_MSG_total_seqid))

#define DLRX_CTXT_MSG_total_seqid_set_indirect(base, offset, val)    \
	do {                                                              \
		(*(base + O_DLRX_CTXT_MSG_total_seqid + offset)) &= (~(M_DLRX_CTXT_MSG_total_seqid));    \
		(*(base + O_DLRX_CTXT_MSG_total_seqid + offset)) |= ((val << B_DLRX_CTXT_MSG_total_seqid) & M_DLRX_CTXT_MSG_total_seqid);    \
	} while (0)

#define DLRX_CTXT_MSG_total_seqid_set_direct(dword, val)    \
	do {                                                               \
		(dword) &= (~(M_DLRX_CTXT_MSG_total_seqid));    \
		(dword) |= ((val << B_DLRX_CTXT_MSG_total_seqid) & M_DLRX_CTXT_MSG_total_seqid);    \
	} while (0)

#define DLRX_CTXT_MSG_total_seqid_clear_indirect(base, offset)	((*(base + O_DLRX_CTXT_MSG_total_seqid + offset)) &= (~(M_DLRX_CTXT_MSG_total_seqid)))

#define DLRX_CTXT_MSG_total_seqid_clear_direct(dword)	((dword) &= (~(M_DLRX_CTXT_MSG_total_seqid)))

#define O_DLRX_CTXT_MSG_start_seqid 10
#define B_DLRX_CTXT_MSG_start_seqid 0
#define W_DLRX_CTXT_MSG_start_seqid 32
#define M_DLRX_CTXT_MSG_start_seqid 0xffffffff

#define DLRX_CTXT_MSG_start_seqid_get_indirect(base, offset)	((((*(base + O_DLRX_CTXT_MSG_start_seqid + offset)) & M_DLRX_CTXT_MSG_start_seqid) >> B_DLRX_CTXT_MSG_start_seqid))

#define DLRX_CTXT_MSG_start_seqid_get_direct(dword)	((((dword) & M_DLRX_CTXT_MSG_start_seqid) >> B_DLRX_CTXT_MSG_start_seqid))

#define DLRX_CTXT_MSG_start_seqid_set_indirect(base, offset, val)    \
	do {                                                              \
		(*(base + O_DLRX_CTXT_MSG_start_seqid + offset)) &= (~(M_DLRX_CTXT_MSG_start_seqid));    \
		(*(base + O_DLRX_CTXT_MSG_start_seqid + offset)) |= ((val << B_DLRX_CTXT_MSG_start_seqid) & M_DLRX_CTXT_MSG_start_seqid);    \
	} while (0)

#define DLRX_CTXT_MSG_start_seqid_set_direct(dword, val)    \
	do {                                                               \
		(dword) &= (~(M_DLRX_CTXT_MSG_start_seqid));    \
		(dword) |= ((val << B_DLRX_CTXT_MSG_start_seqid) & M_DLRX_CTXT_MSG_start_seqid);    \
	} while (0)

#define DLRX_CTXT_MSG_start_seqid_clear_indirect(base, offset)	((*(base + O_DLRX_CTXT_MSG_start_seqid + offset)) &= (~(M_DLRX_CTXT_MSG_start_seqid)))

#define DLRX_CTXT_MSG_start_seqid_clear_direct(dword)	((dword) &= (~(M_DLRX_CTXT_MSG_start_seqid)))

#define O_DLRX_CTXT_MSG_vap 11
#define B_DLRX_CTXT_MSG_vap 0
#define W_DLRX_CTXT_MSG_vap 32
#define M_DLRX_CTXT_MSG_vap 0xffffffff

#define DLRX_CTXT_MSG_vap_get_indirect(base, offset)	((((*(base + O_DLRX_CTXT_MSG_vap + offset)) & M_DLRX_CTXT_MSG_vap) >> B_DLRX_CTXT_MSG_vap))

#define DLRX_CTXT_MSG_vap_get_direct(dword)	((((dword) & M_DLRX_CTXT_MSG_vap) >> B_DLRX_CTXT_MSG_vap))

#define DLRX_CTXT_MSG_vap_set_indirect(base, offset, val)    \
	do {                                                              \
		(*(base + O_DLRX_CTXT_MSG_vap + offset)) &= (~(M_DLRX_CTXT_MSG_vap));    \
		(*(base + O_DLRX_CTXT_MSG_vap + offset)) |= ((val << B_DLRX_CTXT_MSG_vap) & M_DLRX_CTXT_MSG_vap);    \
	} while (0)

#define DLRX_CTXT_MSG_vap_set_direct(dword, val)    \
	do {                                                               \
		(dword) &= (~(M_DLRX_CTXT_MSG_vap));    \
		(dword) |= ((val << B_DLRX_CTXT_MSG_vap) & M_DLRX_CTXT_MSG_vap);    \
	} while (0)

#define DLRX_CTXT_MSG_vap_clear_indirect(base, offset)	((*(base + O_DLRX_CTXT_MSG_vap + offset)) &= (~(M_DLRX_CTXT_MSG_vap)))

#define DLRX_CTXT_MSG_vap_clear_direct(dword)	((dword) &= (~(M_DLRX_CTXT_MSG_vap)))

#define O_DLRX_CTXT_MSG_sec_type 12
#define B_DLRX_CTXT_MSG_sec_type 0
#define W_DLRX_CTXT_MSG_sec_type 32
#define M_DLRX_CTXT_MSG_sec_type 0xffffffff

#define DLRX_CTXT_MSG_sec_type_get_indirect(base, offset)	((((*(base + O_DLRX_CTXT_MSG_sec_type + offset)) & M_DLRX_CTXT_MSG_sec_type) >> B_DLRX_CTXT_MSG_sec_type))

#define DLRX_CTXT_MSG_sec_type_get_direct(dword)	((((dword) & M_DLRX_CTXT_MSG_sec_type) >> B_DLRX_CTXT_MSG_sec_type))

#define DLRX_CTXT_MSG_sec_type_set_indirect(base, offset, val)    \
	do {                                                              \
		(*(base + O_DLRX_CTXT_MSG_sec_type + offset)) &= (~(M_DLRX_CTXT_MSG_sec_type));    \
		(*(base + O_DLRX_CTXT_MSG_sec_type + offset)) |= ((val << B_DLRX_CTXT_MSG_sec_type) & M_DLRX_CTXT_MSG_sec_type);    \
	} while (0)

#define DLRX_CTXT_MSG_sec_type_set_direct(dword, val)    \
	do {                                                               \
		(dword) &= (~(M_DLRX_CTXT_MSG_sec_type));    \
		(dword) |= ((val << B_DLRX_CTXT_MSG_sec_type) & M_DLRX_CTXT_MSG_sec_type);    \
	} while (0)

#define DLRX_CTXT_MSG_sec_type_clear_indirect(base, offset)	((*(base + O_DLRX_CTXT_MSG_sec_type + offset)) &= (~(M_DLRX_CTXT_MSG_sec_type)))

#define DLRX_CTXT_MSG_sec_type_clear_direct(dword)	((dword) &= (~(M_DLRX_CTXT_MSG_sec_type)))

#define O_DLRX_CTXT_MSG_pn_pass 13
#define B_DLRX_CTXT_MSG_pn_pass 0
#define W_DLRX_CTXT_MSG_pn_pass 32
#define M_DLRX_CTXT_MSG_pn_pass 0xffffffff

#define DLRX_CTXT_MSG_pn_pass_get_indirect(base, offset)	((((*(base + O_DLRX_CTXT_MSG_pn_pass + offset)) & M_DLRX_CTXT_MSG_pn_pass) >> B_DLRX_CTXT_MSG_pn_pass))

#define DLRX_CTXT_MSG_pn_pass_get_direct(dword)	((((dword) & M_DLRX_CTXT_MSG_pn_pass) >> B_DLRX_CTXT_MSG_pn_pass))

#define DLRX_CTXT_MSG_pn_pass_set_indirect(base, offset, val)    \
	do {                                                              \
		(*(base + O_DLRX_CTXT_MSG_pn_pass + offset)) &= (~(M_DLRX_CTXT_MSG_pn_pass));    \
		(*(base + O_DLRX_CTXT_MSG_pn_pass + offset)) |= ((val << B_DLRX_CTXT_MSG_pn_pass) & M_DLRX_CTXT_MSG_pn_pass);    \
	} while (0)

#define DLRX_CTXT_MSG_pn_pass_set_direct(dword, val)    \
	do {                                                               \
		(dword) &= (~(M_DLRX_CTXT_MSG_pn_pass));    \
		(dword) |= ((val << B_DLRX_CTXT_MSG_pn_pass) & M_DLRX_CTXT_MSG_pn_pass);    \
	} while (0)

#define DLRX_CTXT_MSG_pn_pass_clear_indirect(base, offset)	((*(base + O_DLRX_CTXT_MSG_pn_pass + offset)) &= (~(M_DLRX_CTXT_MSG_pn_pass)))

#define DLRX_CTXT_MSG_pn_pass_clear_direct(dword)	((dword) &= (~(M_DLRX_CTXT_MSG_pn_pass)))

#define O_DLRX_CTXT_MSG_total_msdu 14
#define B_DLRX_CTXT_MSG_total_msdu 0
#define W_DLRX_CTXT_MSG_total_msdu 32
#define M_DLRX_CTXT_MSG_total_msdu 0xffffffff

#define DLRX_CTXT_MSG_total_msdu_get_indirect(base, offset)	((((*(base + O_DLRX_CTXT_MSG_total_msdu + offset)) & M_DLRX_CTXT_MSG_total_msdu) >> B_DLRX_CTXT_MSG_total_msdu))

#define DLRX_CTXT_MSG_total_msdu_get_direct(dword)	((((dword) & M_DLRX_CTXT_MSG_total_msdu) >> B_DLRX_CTXT_MSG_total_msdu))

#define DLRX_CTXT_MSG_total_msdu_set_indirect(base, offset, val)    \
	do {                                                              \
		(*(base + O_DLRX_CTXT_MSG_total_msdu + offset)) &= (~(M_DLRX_CTXT_MSG_total_msdu));    \
		(*(base + O_DLRX_CTXT_MSG_total_msdu + offset)) |= ((val << B_DLRX_CTXT_MSG_total_msdu) & M_DLRX_CTXT_MSG_total_msdu);    \
	} while (0)

#define DLRX_CTXT_MSG_total_msdu_set_direct(dword, val)    \
	do {                                                               \
		(dword) &= (~(M_DLRX_CTXT_MSG_total_msdu));    \
		(dword) |= ((val << B_DLRX_CTXT_MSG_total_msdu) & M_DLRX_CTXT_MSG_total_msdu);    \
	} while (0)

#define DLRX_CTXT_MSG_total_msdu_clear_indirect(base, offset)	((*(base + O_DLRX_CTXT_MSG_total_msdu + offset)) &= (~(M_DLRX_CTXT_MSG_total_msdu)))

#define DLRX_CTXT_MSG_total_msdu_clear_direct(dword)	((dword) &= (~(M_DLRX_CTXT_MSG_total_msdu)))

#define O_DLRX_CTXT_MSG_check_rv_pending 15
#define B_DLRX_CTXT_MSG_check_rv_pending 0
#define W_DLRX_CTXT_MSG_check_rv_pending 32
#define M_DLRX_CTXT_MSG_check_rv_pending 0xffffffff

#define DLRX_CTXT_MSG_check_rv_pending_get_indirect(base, offset)	((((*(base + O_DLRX_CTXT_MSG_check_rv_pending + offset)) & M_DLRX_CTXT_MSG_check_rv_pending) >> B_DLRX_CTXT_MSG_check_rv_pending))

#define DLRX_CTXT_MSG_check_rv_pending_get_direct(dword)	((((dword) & M_DLRX_CTXT_MSG_check_rv_pending) >> B_DLRX_CTXT_MSG_check_rv_pending))

#define DLRX_CTXT_MSG_check_rv_pending_set_indirect(base, offset, val)    \
	do {                                                              \
		(*(base + O_DLRX_CTXT_MSG_check_rv_pending + offset)) &= (~(M_DLRX_CTXT_MSG_check_rv_pending));    \
		(*(base + O_DLRX_CTXT_MSG_check_rv_pending + offset)) |= ((val << B_DLRX_CTXT_MSG_check_rv_pending) & M_DLRX_CTXT_MSG_check_rv_pending);    \
	} while (0)

#define DLRX_CTXT_MSG_check_rv_pending_set_direct(dword, val)    \
	do {                                                               \
		(dword) &= (~(M_DLRX_CTXT_MSG_check_rv_pending));    \
		(dword) |= ((val << B_DLRX_CTXT_MSG_check_rv_pending) & M_DLRX_CTXT_MSG_check_rv_pending);    \
	} while (0)

#define DLRX_CTXT_MSG_check_rv_pending_clear_indirect(base, offset)	((*(base + O_DLRX_CTXT_MSG_check_rv_pending + offset)) &= (~(M_DLRX_CTXT_MSG_check_rv_pending)))

#define DLRX_CTXT_MSG_check_rv_pending_clear_direct(dword)	((dword) &= (~(M_DLRX_CTXT_MSG_check_rv_pending)))

#define O_DLRX_CTXT_MSG_ext_ro_mainlist_ptr 16
#define B_DLRX_CTXT_MSG_ext_ro_mainlist_ptr 0
#define W_DLRX_CTXT_MSG_ext_ro_mainlist_ptr 32
#define M_DLRX_CTXT_MSG_ext_ro_mainlist_ptr 0xffffffff

#define DLRX_CTXT_MSG_ext_ro_mainlist_ptr_get_indirect(base, offset)	((((*(base + O_DLRX_CTXT_MSG_ext_ro_mainlist_ptr + offset)) & M_DLRX_CTXT_MSG_ext_ro_mainlist_ptr) >> B_DLRX_CTXT_MSG_ext_ro_mainlist_ptr))

#define DLRX_CTXT_MSG_ext_ro_mainlist_ptr_get_direct(dword)	((((dword) & M_DLRX_CTXT_MSG_ext_ro_mainlist_ptr) >> B_DLRX_CTXT_MSG_ext_ro_mainlist_ptr))

#define DLRX_CTXT_MSG_ext_ro_mainlist_ptr_set_indirect(base, offset, val)    \
	do {                                                              \
		(*(base + O_DLRX_CTXT_MSG_ext_ro_mainlist_ptr + offset)) &= (~(M_DLRX_CTXT_MSG_ext_ro_mainlist_ptr));    \
		(*(base + O_DLRX_CTXT_MSG_ext_ro_mainlist_ptr + offset)) |= ((val << B_DLRX_CTXT_MSG_ext_ro_mainlist_ptr) & M_DLRX_CTXT_MSG_ext_ro_mainlist_ptr);    \
	} while (0)

#define DLRX_CTXT_MSG_ext_ro_mainlist_ptr_set_direct(dword, val)    \
	do {                                                               \
		(dword) &= (~(M_DLRX_CTXT_MSG_ext_ro_mainlist_ptr));    \
		(dword) |= ((val << B_DLRX_CTXT_MSG_ext_ro_mainlist_ptr) & M_DLRX_CTXT_MSG_ext_ro_mainlist_ptr);    \
	} while (0)

#define DLRX_CTXT_MSG_ext_ro_mainlist_ptr_clear_indirect(base, offset)	((*(base + O_DLRX_CTXT_MSG_ext_ro_mainlist_ptr + offset)) &= (~(M_DLRX_CTXT_MSG_ext_ro_mainlist_ptr)))

#define DLRX_CTXT_MSG_ext_ro_mainlist_ptr_clear_direct(dword)	((dword) &= (~(M_DLRX_CTXT_MSG_ext_ro_mainlist_ptr)))

#define O_DLRX_CTXT_MSG_ext_msg_ptr 17
#define B_DLRX_CTXT_MSG_ext_msg_ptr 0
#define W_DLRX_CTXT_MSG_ext_msg_ptr 32
#define M_DLRX_CTXT_MSG_ext_msg_ptr 0xffffffff

#define DLRX_CTXT_MSG_ext_msg_ptr_get_indirect(base, offset)	((((*(base + O_DLRX_CTXT_MSG_ext_msg_ptr + offset)) & M_DLRX_CTXT_MSG_ext_msg_ptr) >> B_DLRX_CTXT_MSG_ext_msg_ptr))

#define DLRX_CTXT_MSG_ext_msg_ptr_get_direct(dword)	((((dword) & M_DLRX_CTXT_MSG_ext_msg_ptr) >> B_DLRX_CTXT_MSG_ext_msg_ptr))

#define DLRX_CTXT_MSG_ext_msg_ptr_set_indirect(base, offset, val)    \
	do {                                                              \
		(*(base + O_DLRX_CTXT_MSG_ext_msg_ptr + offset)) &= (~(M_DLRX_CTXT_MSG_ext_msg_ptr));    \
		(*(base + O_DLRX_CTXT_MSG_ext_msg_ptr + offset)) |= ((val << B_DLRX_CTXT_MSG_ext_msg_ptr) & M_DLRX_CTXT_MSG_ext_msg_ptr);    \
	} while (0)

#define DLRX_CTXT_MSG_ext_msg_ptr_set_direct(dword, val)    \
	do {                                                               \
		(dword) &= (~(M_DLRX_CTXT_MSG_ext_msg_ptr));    \
		(dword) |= ((val << B_DLRX_CTXT_MSG_ext_msg_ptr) & M_DLRX_CTXT_MSG_ext_msg_ptr);    \
	} while (0)

#define DLRX_CTXT_MSG_ext_msg_ptr_clear_indirect(base, offset)	((*(base + O_DLRX_CTXT_MSG_ext_msg_ptr + offset)) &= (~(M_DLRX_CTXT_MSG_ext_msg_ptr)))

#define DLRX_CTXT_MSG_ext_msg_ptr_clear_direct(dword)	((dword) &= (~(M_DLRX_CTXT_MSG_ext_msg_ptr)))

#define O_DLRX_CTXT_MSG_peer_vld 18
#define B_DLRX_CTXT_MSG_peer_vld 0
#define W_DLRX_CTXT_MSG_peer_vld 32
#define M_DLRX_CTXT_MSG_peer_vld 0xffffffff

#define DLRX_CTXT_MSG_peer_vld_get_indirect(base, offset)	((((*(base + O_DLRX_CTXT_MSG_peer_vld + offset)) & M_DLRX_CTXT_MSG_peer_vld) >> B_DLRX_CTXT_MSG_peer_vld))

#define DLRX_CTXT_MSG_peer_vld_get_direct(dword)	((((dword) & M_DLRX_CTXT_MSG_peer_vld) >> B_DLRX_CTXT_MSG_peer_vld))

#define DLRX_CTXT_MSG_peer_vld_set_indirect(base, offset, val)    \
	do {                                                              \
		(*(base + O_DLRX_CTXT_MSG_peer_vld + offset)) &= (~(M_DLRX_CTXT_MSG_peer_vld));    \
		(*(base + O_DLRX_CTXT_MSG_peer_vld + offset)) |= ((val << B_DLRX_CTXT_MSG_peer_vld) & M_DLRX_CTXT_MSG_peer_vld);    \
	} while (0)

#define DLRX_CTXT_MSG_peer_vld_set_direct(dword, val)    \
	do {                                                               \
		(dword) &= (~(M_DLRX_CTXT_MSG_peer_vld));    \
		(dword) |= ((val << B_DLRX_CTXT_MSG_peer_vld) & M_DLRX_CTXT_MSG_peer_vld);    \
	} while (0)

#define DLRX_CTXT_MSG_peer_vld_clear_indirect(base, offset)	((*(base + O_DLRX_CTXT_MSG_peer_vld + offset)) &= (~(M_DLRX_CTXT_MSG_peer_vld)))

#define DLRX_CTXT_MSG_peer_vld_clear_direct(dword)	((dword) &= (~(M_DLRX_CTXT_MSG_peer_vld)))

#define O_DLRX_CTXT_MSG_acc_dis 19
#define B_DLRX_CTXT_MSG_acc_dis 0
#define W_DLRX_CTXT_MSG_acc_dis 32
#define M_DLRX_CTXT_MSG_acc_dis 0xffffffff

#define DLRX_CTXT_MSG_acc_dis_get_indirect(base, offset)	((((*(base + O_DLRX_CTXT_MSG_acc_dis + offset)) & M_DLRX_CTXT_MSG_acc_dis) >> B_DLRX_CTXT_MSG_acc_dis))

#define DLRX_CTXT_MSG_acc_dis_get_direct(dword)	((((dword) & M_DLRX_CTXT_MSG_acc_dis) >> B_DLRX_CTXT_MSG_acc_dis))

#define DLRX_CTXT_MSG_acc_dis_set_indirect(base, offset, val)    \
	do {                                                              \
		(*(base + O_DLRX_CTXT_MSG_acc_dis + offset)) &= (~(M_DLRX_CTXT_MSG_acc_dis));    \
		(*(base + O_DLRX_CTXT_MSG_acc_dis + offset)) |= ((val << B_DLRX_CTXT_MSG_acc_dis) & M_DLRX_CTXT_MSG_acc_dis);    \
	} while (0)

#define DLRX_CTXT_MSG_acc_dis_set_direct(dword, val)    \
	do {                                                               \
		(dword) &= (~(M_DLRX_CTXT_MSG_acc_dis));    \
		(dword) |= ((val << B_DLRX_CTXT_MSG_acc_dis) & M_DLRX_CTXT_MSG_acc_dis);    \
	} while (0)

#define DLRX_CTXT_MSG_acc_dis_clear_indirect(base, offset)	((*(base + O_DLRX_CTXT_MSG_acc_dis + offset)) &= (~(M_DLRX_CTXT_MSG_acc_dis)))

#define DLRX_CTXT_MSG_acc_dis_clear_direct(dword)	((dword) &= (~(M_DLRX_CTXT_MSG_acc_dis)))

#define O_DLRX_CTXT_MSG_discard 20
#define B_DLRX_CTXT_MSG_discard 0
#define W_DLRX_CTXT_MSG_discard 1
#define M_DLRX_CTXT_MSG_discard 0x00000001

#define DLRX_CTXT_MSG_discard_get_indirect(base, offset)	((((*(base + O_DLRX_CTXT_MSG_discard + offset)) & M_DLRX_CTXT_MSG_discard) >> B_DLRX_CTXT_MSG_discard))

#define DLRX_CTXT_MSG_discard_get_direct(dword)	((((dword) & M_DLRX_CTXT_MSG_discard) >> B_DLRX_CTXT_MSG_discard))

#define DLRX_CTXT_MSG_discard_set_indirect(base, offset, val) \
	do {                                                              \
		(*(base + O_DLRX_CTXT_MSG_discard + offset)) &= (~(M_DLRX_CTXT_MSG_discard));    \
		(*(base + O_DLRX_CTXT_MSG_discard + offset)) |= ((val << B_DLRX_CTXT_MSG_discard) & M_DLRX_CTXT_MSG_discard);    \
	} while (0)

#define DLRX_CTXT_MSG_discard_set_direct(dword, val) \
	do {                                                               \
		(dword) &= (~(M_DLRX_CTXT_MSG_discard));    \
		(dword) |= ((val << B_DLRX_CTXT_MSG_discard) & M_DLRX_CTXT_MSG_discard);    \
	} while (0)

#define DLRX_CTXT_MSG_discard_clear_indirect(base, offset)	((*(base + O_DLRX_CTXT_MSG_discard + offset)) &= (~(M_DLRX_CTXT_MSG_discard)))

#define DLRX_CTXT_MSG_discard_clear_direct(dword)	((dword) &= (~(M_DLRX_CTXT_MSG_discard)))

#define O_DLRX_CTXT_MSG_forward 20
#define B_DLRX_CTXT_MSG_forward 1
#define W_DLRX_CTXT_MSG_forward 1
#define M_DLRX_CTXT_MSG_forward 0x00000002

#define DLRX_CTXT_MSG_forward_get_indirect(base, offset)	((((*(base + O_DLRX_CTXT_MSG_forward + offset)) & M_DLRX_CTXT_MSG_forward) >> B_DLRX_CTXT_MSG_forward))

#define DLRX_CTXT_MSG_forward_get_direct(dword)	((((dword) & M_DLRX_CTXT_MSG_forward) >> B_DLRX_CTXT_MSG_forward))

#define DLRX_CTXT_MSG_forward_set_indirect(base, offset, val) \
	do {                                                              \
		(*(base + O_DLRX_CTXT_MSG_forward + offset)) &= (~(M_DLRX_CTXT_MSG_forward));    \
		(*(base + O_DLRX_CTXT_MSG_forward + offset)) |= ((val << B_DLRX_CTXT_MSG_forward) & M_DLRX_CTXT_MSG_forward);    \
	} while (0)

#define DLRX_CTXT_MSG_forward_set_direct(dword, val) \
	do {                                                               \
		(dword) &= (~(M_DLRX_CTXT_MSG_forward));    \
		(dword) |= ((val << B_DLRX_CTXT_MSG_forward) & M_DLRX_CTXT_MSG_forward);    \
	} while (0)

#define DLRX_CTXT_MSG_forward_clear_indirect(base, offset)	((*(base + O_DLRX_CTXT_MSG_forward + offset)) &= (~(M_DLRX_CTXT_MSG_forward)))

#define DLRX_CTXT_MSG_forward_clear_direct(dword)	((dword) &= (~(M_DLRX_CTXT_MSG_forward)))

#define O_DLRX_CTXT_MSG_inspect 20
#define B_DLRX_CTXT_MSG_inspect 5
#define W_DLRX_CTXT_MSG_inspect 1
#define M_DLRX_CTXT_MSG_inspect 0x00000020

#define DLRX_CTXT_MSG_inspect_get_indirect(base, offset)	((((*(base + O_DLRX_CTXT_MSG_inspect + offset)) & M_DLRX_CTXT_MSG_inspect) >> B_DLRX_CTXT_MSG_inspect))

#define DLRX_CTXT_MSG_inspect_get_direct(dword)	((((dword) & M_DLRX_CTXT_MSG_inspect) >> B_DLRX_CTXT_MSG_inspect))

#define DLRX_CTXT_MSG_inspect_set_indirect(base, offset, val) \
	do {                                                              \
		(*(base + O_DLRX_CTXT_MSG_inspect + offset)) &= (~(M_DLRX_CTXT_MSG_inspect));    \
		(*(base + O_DLRX_CTXT_MSG_inspect + offset)) |= ((val << B_DLRX_CTXT_MSG_inspect) & M_DLRX_CTXT_MSG_inspect);    \
	} while (0)

#define DLRX_CTXT_MSG_inspect_set_direct(dword, val) \
	do {                                                               \
		(dword) &= (~(M_DLRX_CTXT_MSG_inspect));    \
		(dword) |= ((val << B_DLRX_CTXT_MSG_inspect) & M_DLRX_CTXT_MSG_inspect);    \
	} while (0)

#define DLRX_CTXT_MSG_inspect_clear_indirect(base, offset)	((*(base + O_DLRX_CTXT_MSG_inspect + offset)) &= (~(M_DLRX_CTXT_MSG_inspect)))

#define DLRX_CTXT_MSG_inspect_clear_direct(dword)	((dword) &= (~(M_DLRX_CTXT_MSG_inspect)))

#define O_DLRX_CFG_CTXT_RXPB_PTR_REL_MSGBUF_cfg_badr_rel_msgbuf 0
#define B_DLRX_CFG_CTXT_RXPB_PTR_REL_MSGBUF_cfg_badr_rel_msgbuf 0
#define W_DLRX_CFG_CTXT_RXPB_PTR_REL_MSGBUF_cfg_badr_rel_msgbuf 32
#define M_DLRX_CFG_CTXT_RXPB_PTR_REL_MSGBUF_cfg_badr_rel_msgbuf 0xffffffff

#define DLRX_CFG_CTXT_RXPB_PTR_REL_MSGBUF_cfg_badr_rel_msgbuf_get_indirect(base, offset)	((((*(base + O_DLRX_CFG_CTXT_RXPB_PTR_REL_MSGBUF_cfg_badr_rel_msgbuf + offset)) & M_DLRX_CFG_CTXT_RXPB_PTR_REL_MSGBUF_cfg_badr_rel_msgbuf) >> B_DLRX_CFG_CTXT_RXPB_PTR_REL_MSGBUF_cfg_badr_rel_msgbuf))

#define DLRX_CFG_CTXT_RXPB_PTR_REL_MSGBUF_cfg_badr_rel_msgbuf_get_direct(dword)	((((dword) & M_DLRX_CFG_CTXT_RXPB_PTR_REL_MSGBUF_cfg_badr_rel_msgbuf) >> B_DLRX_CFG_CTXT_RXPB_PTR_REL_MSGBUF_cfg_badr_rel_msgbuf))

#define DLRX_CFG_CTXT_RXPB_PTR_REL_MSGBUF_cfg_badr_rel_msgbuf_set_indirect(base, offset, val)    \
	do {                                                              \
		(*(base + O_DLRX_CFG_CTXT_RXPB_PTR_REL_MSGBUF_cfg_badr_rel_msgbuf + offset)) &= (~(M_DLRX_CFG_CTXT_RXPB_PTR_REL_MSGBUF_cfg_badr_rel_msgbuf));    \
		(*(base + O_DLRX_CFG_CTXT_RXPB_PTR_REL_MSGBUF_cfg_badr_rel_msgbuf + offset)) |= ((val << B_DLRX_CFG_CTXT_RXPB_PTR_REL_MSGBUF_cfg_badr_rel_msgbuf) & M_DLRX_CFG_CTXT_RXPB_PTR_REL_MSGBUF_cfg_badr_rel_msgbuf);    \
	} while (0)

#define DLRX_CFG_CTXT_RXPB_PTR_REL_MSGBUF_cfg_badr_rel_msgbuf_set_direct(dword, val)    \
	do {                                                               \
		(dword) &= (~(M_DLRX_CFG_CTXT_RXPB_PTR_REL_MSGBUF_cfg_badr_rel_msgbuf));    \
		(dword) |= ((val << B_DLRX_CFG_CTXT_RXPB_PTR_REL_MSGBUF_cfg_badr_rel_msgbuf) & M_DLRX_CFG_CTXT_RXPB_PTR_REL_MSGBUF_cfg_badr_rel_msgbuf);    \
	} while (0)

#define DLRX_CFG_CTXT_RXPB_PTR_REL_MSGBUF_cfg_badr_rel_msgbuf_clear_indirect(base, offset)	((*(base + O_DLRX_CFG_CTXT_RXPB_PTR_REL_MSGBUF_cfg_badr_rel_msgbuf + offset)) &= (~(M_DLRX_CFG_CTXT_RXPB_PTR_REL_MSGBUF_cfg_badr_rel_msgbuf)))

#define DLRX_CFG_CTXT_RXPB_PTR_REL_MSGBUF_cfg_badr_rel_msgbuf_clear_direct(dword)	((dword) &= (~(M_DLRX_CFG_CTXT_RXPB_PTR_REL_MSGBUF_cfg_badr_rel_msgbuf)))

#define O_DLRX_CFG_CTXT_RXPB_PTR_REL_MSGBUF_cfg_num_rel_msgbuf 1
#define B_DLRX_CFG_CTXT_RXPB_PTR_REL_MSGBUF_cfg_num_rel_msgbuf 0
#define W_DLRX_CFG_CTXT_RXPB_PTR_REL_MSGBUF_cfg_num_rel_msgbuf 32
#define M_DLRX_CFG_CTXT_RXPB_PTR_REL_MSGBUF_cfg_num_rel_msgbuf 0xffffffff

#define DLRX_CFG_CTXT_RXPB_PTR_REL_MSGBUF_cfg_num_rel_msgbuf_get_indirect(base, offset)	((((*(base + O_DLRX_CFG_CTXT_RXPB_PTR_REL_MSGBUF_cfg_num_rel_msgbuf + offset)) & M_DLRX_CFG_CTXT_RXPB_PTR_REL_MSGBUF_cfg_num_rel_msgbuf) >> B_DLRX_CFG_CTXT_RXPB_PTR_REL_MSGBUF_cfg_num_rel_msgbuf))

#define DLRX_CFG_CTXT_RXPB_PTR_REL_MSGBUF_cfg_num_rel_msgbuf_get_direct(dword)	((((dword) & M_DLRX_CFG_CTXT_RXPB_PTR_REL_MSGBUF_cfg_num_rel_msgbuf) >> B_DLRX_CFG_CTXT_RXPB_PTR_REL_MSGBUF_cfg_num_rel_msgbuf))

#define DLRX_CFG_CTXT_RXPB_PTR_REL_MSGBUF_cfg_num_rel_msgbuf_set_indirect(base, offset, val)    \
	do {                                                              \
		(*(base + O_DLRX_CFG_CTXT_RXPB_PTR_REL_MSGBUF_cfg_num_rel_msgbuf + offset)) &= (~(M_DLRX_CFG_CTXT_RXPB_PTR_REL_MSGBUF_cfg_num_rel_msgbuf));    \
		(*(base + O_DLRX_CFG_CTXT_RXPB_PTR_REL_MSGBUF_cfg_num_rel_msgbuf + offset)) |= ((val << B_DLRX_CFG_CTXT_RXPB_PTR_REL_MSGBUF_cfg_num_rel_msgbuf) & M_DLRX_CFG_CTXT_RXPB_PTR_REL_MSGBUF_cfg_num_rel_msgbuf);    \
	} while (0)

#define DLRX_CFG_CTXT_RXPB_PTR_REL_MSGBUF_cfg_num_rel_msgbuf_set_direct(dword, val)    \
	do {                                                               \
		(dword) &= (~(M_DLRX_CFG_CTXT_RXPB_PTR_REL_MSGBUF_cfg_num_rel_msgbuf));    \
		(dword) |= ((val << B_DLRX_CFG_CTXT_RXPB_PTR_REL_MSGBUF_cfg_num_rel_msgbuf) & M_DLRX_CFG_CTXT_RXPB_PTR_REL_MSGBUF_cfg_num_rel_msgbuf);    \
	} while (0)

#define DLRX_CFG_CTXT_RXPB_PTR_REL_MSGBUF_cfg_num_rel_msgbuf_clear_indirect(base, offset)	((*(base + O_DLRX_CFG_CTXT_RXPB_PTR_REL_MSGBUF_cfg_num_rel_msgbuf + offset)) &= (~(M_DLRX_CFG_CTXT_RXPB_PTR_REL_MSGBUF_cfg_num_rel_msgbuf)))

#define DLRX_CFG_CTXT_RXPB_PTR_REL_MSGBUF_cfg_num_rel_msgbuf_clear_direct(dword)	((dword) &= (~(M_DLRX_CFG_CTXT_RXPB_PTR_REL_MSGBUF_cfg_num_rel_msgbuf)))

#define O_DLRX_CFG_GLOBAL_dltx_enable 0
#define B_DLRX_CFG_GLOBAL_dltx_enable 0
#define W_DLRX_CFG_GLOBAL_dltx_enable 32
#define M_DLRX_CFG_GLOBAL_dltx_enable 0xffffffff

#define DLRX_CFG_GLOBAL_dltx_enable_get_indirect(base, offset)	((((*(base + O_DLRX_CFG_GLOBAL_dltx_enable + offset)) & M_DLRX_CFG_GLOBAL_dltx_enable) >> B_DLRX_CFG_GLOBAL_dltx_enable))

#define DLRX_CFG_GLOBAL_dltx_enable_get_direct(dword)	((((dword) & M_DLRX_CFG_GLOBAL_dltx_enable) >> B_DLRX_CFG_GLOBAL_dltx_enable))

#define DLRX_CFG_GLOBAL_dltx_enable_set_indirect(base, offset, val)    \
	do {                                                              \
		(*(base + O_DLRX_CFG_GLOBAL_dltx_enable + offset)) &= (~(M_DLRX_CFG_GLOBAL_dltx_enable));    \
		(*(base + O_DLRX_CFG_GLOBAL_dltx_enable + offset)) |= ((val << B_DLRX_CFG_GLOBAL_dltx_enable) & M_DLRX_CFG_GLOBAL_dltx_enable);    \
	} while (0)

#define DLRX_CFG_GLOBAL_dltx_enable_set_direct(dword, val)    \
	do {                                                               \
		(dword) &= (~(M_DLRX_CFG_GLOBAL_dltx_enable));    \
		(dword) |= ((val << B_DLRX_CFG_GLOBAL_dltx_enable) & M_DLRX_CFG_GLOBAL_dltx_enable);    \
	} while (0)

#define DLRX_CFG_GLOBAL_dltx_enable_clear_indirect(base, offset)	((*(base + O_DLRX_CFG_GLOBAL_dltx_enable + offset)) &= (~(M_DLRX_CFG_GLOBAL_dltx_enable)))

#define DLRX_CFG_GLOBAL_dltx_enable_clear_direct(dword)	((dword) &= (~(M_DLRX_CFG_GLOBAL_dltx_enable)))

#define O_DLRX_CFG_GLOBAL_dlrx_enable 1
#define B_DLRX_CFG_GLOBAL_dlrx_enable 0
#define W_DLRX_CFG_GLOBAL_dlrx_enable 32
#define M_DLRX_CFG_GLOBAL_dlrx_enable 0xffffffff

#define DLRX_CFG_GLOBAL_dlrx_enable_get_indirect(base, offset)	((((*(base + O_DLRX_CFG_GLOBAL_dlrx_enable + offset)) & M_DLRX_CFG_GLOBAL_dlrx_enable) >> B_DLRX_CFG_GLOBAL_dlrx_enable))

#define DLRX_CFG_GLOBAL_dlrx_enable_get_direct(dword)	((((dword) & M_DLRX_CFG_GLOBAL_dlrx_enable) >> B_DLRX_CFG_GLOBAL_dlrx_enable))

#define DLRX_CFG_GLOBAL_dlrx_enable_set_indirect(base, offset, val)    \
	do {                                                              \
		(*(base + O_DLRX_CFG_GLOBAL_dlrx_enable + offset)) &= (~(M_DLRX_CFG_GLOBAL_dlrx_enable));    \
		(*(base + O_DLRX_CFG_GLOBAL_dlrx_enable + offset)) |= ((val << B_DLRX_CFG_GLOBAL_dlrx_enable) & M_DLRX_CFG_GLOBAL_dlrx_enable);    \
	} while (0)

#define DLRX_CFG_GLOBAL_dlrx_enable_set_direct(dword, val)    \
	do {                                                               \
		(dword) &= (~(M_DLRX_CFG_GLOBAL_dlrx_enable));    \
		(dword) |= ((val << B_DLRX_CFG_GLOBAL_dlrx_enable) & M_DLRX_CFG_GLOBAL_dlrx_enable);    \
	} while (0)

#define DLRX_CFG_GLOBAL_dlrx_enable_clear_indirect(base, offset)	((*(base + O_DLRX_CFG_GLOBAL_dlrx_enable + offset)) &= (~(M_DLRX_CFG_GLOBAL_dlrx_enable)))

#define DLRX_CFG_GLOBAL_dlrx_enable_clear_direct(dword)	((dword) &= (~(M_DLRX_CFG_GLOBAL_dlrx_enable)))

#define O_DLRX_CFG_GLOBAL_dlrx_pcie_base 2
#define B_DLRX_CFG_GLOBAL_dlrx_pcie_base 0
#define W_DLRX_CFG_GLOBAL_dlrx_pcie_base 32
#define M_DLRX_CFG_GLOBAL_dlrx_pcie_base 0xffffffff

#define DLRX_CFG_GLOBAL_dlrx_pcie_base_get_indirect(base, offset)	((((*(base + O_DLRX_CFG_GLOBAL_dlrx_pcie_base + offset)) & M_DLRX_CFG_GLOBAL_dlrx_pcie_base) >> B_DLRX_CFG_GLOBAL_dlrx_pcie_base))

#define DLRX_CFG_GLOBAL_dlrx_pcie_base_get_direct(dword)	((((dword) & M_DLRX_CFG_GLOBAL_dlrx_pcie_base) >> B_DLRX_CFG_GLOBAL_dlrx_pcie_base))

#define DLRX_CFG_GLOBAL_dlrx_pcie_base_set_indirect(base, offset, val)    \
	do {                                                              \
		(*(base + O_DLRX_CFG_GLOBAL_dlrx_pcie_base + offset)) &= (~(M_DLRX_CFG_GLOBAL_dlrx_pcie_base));    \
		(*(base + O_DLRX_CFG_GLOBAL_dlrx_pcie_base + offset)) |= ((val << B_DLRX_CFG_GLOBAL_dlrx_pcie_base) & M_DLRX_CFG_GLOBAL_dlrx_pcie_base);    \
	} while (0)

#define DLRX_CFG_GLOBAL_dlrx_pcie_base_set_direct(dword, val)    \
	do {                                                               \
		(dword) &= (~(M_DLRX_CFG_GLOBAL_dlrx_pcie_base));    \
		(dword) |= ((val << B_DLRX_CFG_GLOBAL_dlrx_pcie_base) & M_DLRX_CFG_GLOBAL_dlrx_pcie_base);    \
	} while (0)

#define DLRX_CFG_GLOBAL_dlrx_pcie_base_clear_indirect(base, offset)	((*(base + O_DLRX_CFG_GLOBAL_dlrx_pcie_base + offset)) &= (~(M_DLRX_CFG_GLOBAL_dlrx_pcie_base)))

#define DLRX_CFG_GLOBAL_dlrx_pcie_base_clear_direct(dword)	((dword) &= (~(M_DLRX_CFG_GLOBAL_dlrx_pcie_base)))

#define O_DLRX_CFG_GLOBAL_dlrx_ddr_base 3
#define B_DLRX_CFG_GLOBAL_dlrx_ddr_base 0
#define W_DLRX_CFG_GLOBAL_dlrx_ddr_base 32
#define M_DLRX_CFG_GLOBAL_dlrx_ddr_base 0xffffffff

#define DLRX_CFG_GLOBAL_dlrx_ddr_base_get_indirect(base, offset)	((((*(base + O_DLRX_CFG_GLOBAL_dlrx_ddr_base + offset)) & M_DLRX_CFG_GLOBAL_dlrx_ddr_base) >> B_DLRX_CFG_GLOBAL_dlrx_ddr_base))

#define DLRX_CFG_GLOBAL_dlrx_ddr_base_get_direct(dword)	((((dword) & M_DLRX_CFG_GLOBAL_dlrx_ddr_base) >> B_DLRX_CFG_GLOBAL_dlrx_ddr_base))

#define DLRX_CFG_GLOBAL_dlrx_ddr_base_set_indirect(base, offset, val)    \
	do {                                                              \
		(*(base + O_DLRX_CFG_GLOBAL_dlrx_ddr_base + offset)) &= (~(M_DLRX_CFG_GLOBAL_dlrx_ddr_base));    \
		(*(base + O_DLRX_CFG_GLOBAL_dlrx_ddr_base + offset)) |= ((val << B_DLRX_CFG_GLOBAL_dlrx_ddr_base) & M_DLRX_CFG_GLOBAL_dlrx_ddr_base);    \
	} while (0)

#define DLRX_CFG_GLOBAL_dlrx_ddr_base_set_direct(dword, val)    \
	do {                                                               \
		(dword) &= (~(M_DLRX_CFG_GLOBAL_dlrx_ddr_base));    \
		(dword) |= ((val << B_DLRX_CFG_GLOBAL_dlrx_ddr_base) & M_DLRX_CFG_GLOBAL_dlrx_ddr_base);    \
	} while (0)

#define DLRX_CFG_GLOBAL_dlrx_ddr_base_clear_indirect(base, offset)	((*(base + O_DLRX_CFG_GLOBAL_dlrx_ddr_base + offset)) &= (~(M_DLRX_CFG_GLOBAL_dlrx_ddr_base)))

#define DLRX_CFG_GLOBAL_dlrx_ddr_base_clear_direct(dword)	((dword) &= (~(M_DLRX_CFG_GLOBAL_dlrx_ddr_base)))

#define O_DLRX_CFG_GLOBAL_dlrx_cfg_ctxt_base 4
#define B_DLRX_CFG_GLOBAL_dlrx_cfg_ctxt_base 0
#define W_DLRX_CFG_GLOBAL_dlrx_cfg_ctxt_base 32
#define M_DLRX_CFG_GLOBAL_dlrx_cfg_ctxt_base 0xffffffff

#define DLRX_CFG_GLOBAL_dlrx_cfg_ctxt_base_get_indirect(base, offset)	((((*(base + O_DLRX_CFG_GLOBAL_dlrx_cfg_ctxt_base + offset)) & M_DLRX_CFG_GLOBAL_dlrx_cfg_ctxt_base) >> B_DLRX_CFG_GLOBAL_dlrx_cfg_ctxt_base))

#define DLRX_CFG_GLOBAL_dlrx_cfg_ctxt_base_get_direct(dword)	((((dword) & M_DLRX_CFG_GLOBAL_dlrx_cfg_ctxt_base) >> B_DLRX_CFG_GLOBAL_dlrx_cfg_ctxt_base))

#define DLRX_CFG_GLOBAL_dlrx_cfg_ctxt_base_set_indirect(base, offset, val)    \
	do {                                                              \
		(*(base + O_DLRX_CFG_GLOBAL_dlrx_cfg_ctxt_base + offset)) &= (~(M_DLRX_CFG_GLOBAL_dlrx_cfg_ctxt_base));    \
		(*(base + O_DLRX_CFG_GLOBAL_dlrx_cfg_ctxt_base + offset)) |= ((val << B_DLRX_CFG_GLOBAL_dlrx_cfg_ctxt_base) & M_DLRX_CFG_GLOBAL_dlrx_cfg_ctxt_base);    \
	} while (0)

#define DLRX_CFG_GLOBAL_dlrx_cfg_ctxt_base_set_direct(dword, val)    \
	do {                                                               \
		(dword) &= (~(M_DLRX_CFG_GLOBAL_dlrx_cfg_ctxt_base));    \
		(dword) |= ((val << B_DLRX_CFG_GLOBAL_dlrx_cfg_ctxt_base) & M_DLRX_CFG_GLOBAL_dlrx_cfg_ctxt_base);    \
	} while (0)

#define DLRX_CFG_GLOBAL_dlrx_cfg_ctxt_base_clear_indirect(base, offset)	((*(base + O_DLRX_CFG_GLOBAL_dlrx_cfg_ctxt_base + offset)) &= (~(M_DLRX_CFG_GLOBAL_dlrx_cfg_ctxt_base)))

#define DLRX_CFG_GLOBAL_dlrx_cfg_ctxt_base_clear_direct(dword)	((dword) &= (~(M_DLRX_CFG_GLOBAL_dlrx_cfg_ctxt_base)))

#define O_DLRX_CFG_GLOBAL_dlrx_cfg_ctxt_max_size 5
#define B_DLRX_CFG_GLOBAL_dlrx_cfg_ctxt_max_size 0
#define W_DLRX_CFG_GLOBAL_dlrx_cfg_ctxt_max_size 32
#define M_DLRX_CFG_GLOBAL_dlrx_cfg_ctxt_max_size 0xffffffff

#define DLRX_CFG_GLOBAL_dlrx_cfg_ctxt_max_size_get_indirect(base, offset)	((((*(base + O_DLRX_CFG_GLOBAL_dlrx_cfg_ctxt_max_size + offset)) & M_DLRX_CFG_GLOBAL_dlrx_cfg_ctxt_max_size) >> B_DLRX_CFG_GLOBAL_dlrx_cfg_ctxt_max_size))

#define DLRX_CFG_GLOBAL_dlrx_cfg_ctxt_max_size_get_direct(dword)	((((dword) & M_DLRX_CFG_GLOBAL_dlrx_cfg_ctxt_max_size) >> B_DLRX_CFG_GLOBAL_dlrx_cfg_ctxt_max_size))

#define DLRX_CFG_GLOBAL_dlrx_cfg_ctxt_max_size_set_indirect(base, offset, val)    \
	do {                                                              \
		(*(base + O_DLRX_CFG_GLOBAL_dlrx_cfg_ctxt_max_size + offset)) &= (~(M_DLRX_CFG_GLOBAL_dlrx_cfg_ctxt_max_size));    \
		(*(base + O_DLRX_CFG_GLOBAL_dlrx_cfg_ctxt_max_size + offset)) |= ((val << B_DLRX_CFG_GLOBAL_dlrx_cfg_ctxt_max_size) & M_DLRX_CFG_GLOBAL_dlrx_cfg_ctxt_max_size);    \
	} while (0)

#define DLRX_CFG_GLOBAL_dlrx_cfg_ctxt_max_size_set_direct(dword, val)    \
	do {                                                               \
		(dword) &= (~(M_DLRX_CFG_GLOBAL_dlrx_cfg_ctxt_max_size));    \
		(dword) |= ((val << B_DLRX_CFG_GLOBAL_dlrx_cfg_ctxt_max_size) & M_DLRX_CFG_GLOBAL_dlrx_cfg_ctxt_max_size);    \
	} while (0)

#define DLRX_CFG_GLOBAL_dlrx_cfg_ctxt_max_size_clear_indirect(base, offset)	((*(base + O_DLRX_CFG_GLOBAL_dlrx_cfg_ctxt_max_size + offset)) &= (~(M_DLRX_CFG_GLOBAL_dlrx_cfg_ctxt_max_size)))

#define DLRX_CFG_GLOBAL_dlrx_cfg_ctxt_max_size_clear_direct(dword)	((dword) &= (~(M_DLRX_CFG_GLOBAL_dlrx_cfg_ctxt_max_size)))

#define O_DLRX_CFG_GLOBAL_fw_ver_id 6
#define B_DLRX_CFG_GLOBAL_fw_ver_id 0
#define W_DLRX_CFG_GLOBAL_fw_ver_id 32
#define M_DLRX_CFG_GLOBAL_fw_ver_id 0xffffffff

#define DLRX_CFG_GLOBAL_fw_ver_id_get_indirect(base, offset)	((((*(base + O_DLRX_CFG_GLOBAL_fw_ver_id + offset)) & M_DLRX_CFG_GLOBAL_fw_ver_id) >> B_DLRX_CFG_GLOBAL_fw_ver_id))

#define DLRX_CFG_GLOBAL_fw_ver_id_get_direct(dword)	((((dword) & M_DLRX_CFG_GLOBAL_fw_ver_id) >> B_DLRX_CFG_GLOBAL_fw_ver_id))

#define DLRX_CFG_GLOBAL_fw_ver_id_set_indirect(base, offset, val)    \
	do {                                                              \
		(*(base + O_DLRX_CFG_GLOBAL_fw_ver_id + offset)) &= (~(M_DLRX_CFG_GLOBAL_fw_ver_id));    \
		(*(base + O_DLRX_CFG_GLOBAL_fw_ver_id + offset)) |= ((val << B_DLRX_CFG_GLOBAL_fw_ver_id) & M_DLRX_CFG_GLOBAL_fw_ver_id);    \
	} while (0)

#define DLRX_CFG_GLOBAL_fw_ver_id_set_direct(dword, val)    \
	do {                                                               \
		(dword) &= (~(M_DLRX_CFG_GLOBAL_fw_ver_id));    \
		(dword) |= ((val << B_DLRX_CFG_GLOBAL_fw_ver_id) & M_DLRX_CFG_GLOBAL_fw_ver_id);    \
	} while (0)

#define DLRX_CFG_GLOBAL_fw_ver_id_clear_indirect(base, offset)	((*(base + O_DLRX_CFG_GLOBAL_fw_ver_id + offset)) &= (~(M_DLRX_CFG_GLOBAL_fw_ver_id)))

#define DLRX_CFG_GLOBAL_fw_ver_id_clear_direct(dword)	((dword) &= (~(M_DLRX_CFG_GLOBAL_fw_ver_id)))

#define O_DLRX_CFG_GLOBAL_fw_feature 7
#define B_DLRX_CFG_GLOBAL_fw_feature 0
#define W_DLRX_CFG_GLOBAL_fw_feature 32
#define M_DLRX_CFG_GLOBAL_fw_feature 0xffffffff

#define DLRX_CFG_GLOBAL_fw_feature_get_indirect(base, offset)	((((*(base + O_DLRX_CFG_GLOBAL_fw_feature + offset)) & M_DLRX_CFG_GLOBAL_fw_feature) >> B_DLRX_CFG_GLOBAL_fw_feature))

#define DLRX_CFG_GLOBAL_fw_feature_get_direct(dword)	((((dword) & M_DLRX_CFG_GLOBAL_fw_feature) >> B_DLRX_CFG_GLOBAL_fw_feature))

#define DLRX_CFG_GLOBAL_fw_feature_set_indirect(base, offset, val)    \
	do {                                                              \
		(*(base + O_DLRX_CFG_GLOBAL_fw_feature + offset)) &= (~(M_DLRX_CFG_GLOBAL_fw_feature));    \
		(*(base + O_DLRX_CFG_GLOBAL_fw_feature + offset)) |= ((val << B_DLRX_CFG_GLOBAL_fw_feature) & M_DLRX_CFG_GLOBAL_fw_feature);    \
	} while (0)

#define DLRX_CFG_GLOBAL_fw_feature_set_direct(dword, val)    \
	do {                                                               \
		(dword) &= (~(M_DLRX_CFG_GLOBAL_fw_feature));    \
		(dword) |= ((val << B_DLRX_CFG_GLOBAL_fw_feature) & M_DLRX_CFG_GLOBAL_fw_feature);    \
	} while (0)

#define DLRX_CFG_GLOBAL_fw_feature_clear_indirect(base, offset)	((*(base + O_DLRX_CFG_GLOBAL_fw_feature + offset)) &= (~(M_DLRX_CFG_GLOBAL_fw_feature)))

#define DLRX_CFG_GLOBAL_fw_feature_clear_direct(dword)	((dword) &= (~(M_DLRX_CFG_GLOBAL_fw_feature)))

#define O_DLRX_CFG_GLOBAL_debug_print_enable 8
#define B_DLRX_CFG_GLOBAL_debug_print_enable 0
#define W_DLRX_CFG_GLOBAL_debug_print_enable 32
#define M_DLRX_CFG_GLOBAL_debug_print_enable 0xffffffff

#define DLRX_CFG_GLOBAL_debug_print_enable_get_indirect(base, offset)	((((*(base + O_DLRX_CFG_GLOBAL_debug_print_enable + offset)) & M_DLRX_CFG_GLOBAL_debug_print_enable) >> B_DLRX_CFG_GLOBAL_debug_print_enable))

#define DLRX_CFG_GLOBAL_debug_print_enable_get_direct(dword)	((((dword) & M_DLRX_CFG_GLOBAL_debug_print_enable) >> B_DLRX_CFG_GLOBAL_debug_print_enable))

#define DLRX_CFG_GLOBAL_debug_print_enable_set_indirect(base, offset, val)    \
	do {                                                              \
		(*(base + O_DLRX_CFG_GLOBAL_debug_print_enable + offset)) &= (~(M_DLRX_CFG_GLOBAL_debug_print_enable));    \
		(*(base + O_DLRX_CFG_GLOBAL_debug_print_enable + offset)) |= ((val << B_DLRX_CFG_GLOBAL_debug_print_enable) & M_DLRX_CFG_GLOBAL_debug_print_enable);    \
	} while (0)

#define DLRX_CFG_GLOBAL_debug_print_enable_set_direct(dword, val)    \
	do {                                                               \
		(dword) &= (~(M_DLRX_CFG_GLOBAL_debug_print_enable));    \
		(dword) |= ((val << B_DLRX_CFG_GLOBAL_debug_print_enable) & M_DLRX_CFG_GLOBAL_debug_print_enable);    \
	} while (0)

#define DLRX_CFG_GLOBAL_debug_print_enable_clear_indirect(base, offset)	((*(base + O_DLRX_CFG_GLOBAL_debug_print_enable + offset)) &= (~(M_DLRX_CFG_GLOBAL_debug_print_enable)))

#define DLRX_CFG_GLOBAL_debug_print_enable_clear_direct(dword)	((dword) &= (~(M_DLRX_CFG_GLOBAL_debug_print_enable)))

#define O_DLRX_CFG_GLOBAL_dlrx_cfg_unload 9
#define B_DLRX_CFG_GLOBAL_dlrx_cfg_unload 0
#define W_DLRX_CFG_GLOBAL_dlrx_cfg_unload 32
#define M_DLRX_CFG_GLOBAL_dlrx_cfg_unload 0xffffffff

#define DLRX_CFG_GLOBAL_dlrx_cfg_unload_get_indirect(base, offset)	((((*(base + O_DLRX_CFG_GLOBAL_dlrx_cfg_unload + offset)) & M_DLRX_CFG_GLOBAL_dlrx_cfg_unload) >> B_DLRX_CFG_GLOBAL_dlrx_cfg_unload))

#define DLRX_CFG_GLOBAL_dlrx_cfg_unload_get_direct(dword)	((((dword) & M_DLRX_CFG_GLOBAL_dlrx_cfg_unload) >> B_DLRX_CFG_GLOBAL_dlrx_cfg_unload))

#define DLRX_CFG_GLOBAL_dlrx_cfg_unload_set_indirect(base, offset, val)    \
	do {                                                              \
		(*(base + O_DLRX_CFG_GLOBAL_dlrx_cfg_unload + offset)) &= (~(M_DLRX_CFG_GLOBAL_dlrx_cfg_unload));    \
		(*(base + O_DLRX_CFG_GLOBAL_dlrx_cfg_unload + offset)) |= ((val << B_DLRX_CFG_GLOBAL_dlrx_cfg_unload) & M_DLRX_CFG_GLOBAL_dlrx_cfg_unload);    \
	} while (0)

#define DLRX_CFG_GLOBAL_dlrx_cfg_unload_set_direct(dword, val)    \
	do {                                                               \
		(dword) &= (~(M_DLRX_CFG_GLOBAL_dlrx_cfg_unload));    \
		(dword) |= ((val << B_DLRX_CFG_GLOBAL_dlrx_cfg_unload) & M_DLRX_CFG_GLOBAL_dlrx_cfg_unload);    \
	} while (0)

#define DLRX_CFG_GLOBAL_dlrx_cfg_unload_clear_indirect(base, offset)	((*(base + O_DLRX_CFG_GLOBAL_dlrx_cfg_unload + offset)) &= (~(M_DLRX_CFG_GLOBAL_dlrx_cfg_unload)))

#define DLRX_CFG_GLOBAL_dlrx_cfg_unload_clear_direct(dword)	((dword) &= (~(M_DLRX_CFG_GLOBAL_dlrx_cfg_unload)))

#define O_DLRX_CFG_GLOBAL_dlrx_qca_hw 10
#define B_DLRX_CFG_GLOBAL_dlrx_qca_hw 0
#define W_DLRX_CFG_GLOBAL_dlrx_qca_hw 32
#define M_DLRX_CFG_GLOBAL_dlrx_qca_hw 0xffffffff

#define DLRX_CFG_GLOBAL_dlrx_qca_hw_get_indirect(base, offset)	((((*(base + O_DLRX_CFG_GLOBAL_dlrx_qca_hw + offset)) & M_DLRX_CFG_GLOBAL_dlrx_qca_hw) >> B_DLRX_CFG_GLOBAL_dlrx_qca_hw))

#define DLRX_CFG_GLOBAL_dlrx_qca_hw_get_direct(dword)	((((dword) & M_DLRX_CFG_GLOBAL_dlrx_qca_hw) >> B_DLRX_CFG_GLOBAL_dlrx_qca_hw))

#define DLRX_CFG_GLOBAL_dlrx_qca_hw_set_indirect(base, offset, val)    \
	do {                                                              \
		(*(base + O_DLRX_CFG_GLOBAL_dlrx_qca_hw + offset)) &= (~(M_DLRX_CFG_GLOBAL_dlrx_qca_hw));    \
		(*(base + O_DLRX_CFG_GLOBAL_dlrx_qca_hw + offset)) |= ((val << B_DLRX_CFG_GLOBAL_dlrx_qca_hw) & M_DLRX_CFG_GLOBAL_dlrx_qca_hw);    \
	} while (0)

#define DLRX_CFG_GLOBAL_dlrx_qca_hw_set_direct(dword, val)    \
	do {                                                               \
		(dword) &= (~(M_DLRX_CFG_GLOBAL_dlrx_qca_hw));    \
		(dword) |= ((val << B_DLRX_CFG_GLOBAL_dlrx_qca_hw) & M_DLRX_CFG_GLOBAL_dlrx_qca_hw);    \
	} while (0)

#define DLRX_CFG_GLOBAL_dlrx_qca_hw_clear_indirect(base, offset)	((*(base + O_DLRX_CFG_GLOBAL_dlrx_qca_hw + offset)) &= (~(M_DLRX_CFG_GLOBAL_dlrx_qca_hw)))

#define DLRX_CFG_GLOBAL_dlrx_qca_hw_clear_direct(dword)	((dword) &= (~(M_DLRX_CFG_GLOBAL_dlrx_qca_hw)))

#define O_DLRX_CFG_GLOBAL_dlrx_congestion_bit_timeout 11
#define B_DLRX_CFG_GLOBAL_dlrx_congestion_bit_timeout 0
#define W_DLRX_CFG_GLOBAL_dlrx_congestion_bit_timeout 32
#define M_DLRX_CFG_GLOBAL_dlrx_congestion_bit_timeout 0xffffffff

#define DLRX_CFG_GLOBAL_dlrx_congestion_bit_timeout_get_indirect(base, offset)	((((*(base + O_DLRX_CFG_GLOBAL_dlrx_congestion_bit_timeout + offset)) & M_DLRX_CFG_GLOBAL_dlrx_congestion_bit_timeout) >> B_DLRX_CFG_GLOBAL_dlrx_congestion_bit_timeout))

#define DLRX_CFG_GLOBAL_dlrx_congestion_bit_timeout_get_direct(dword)	((((dword) & M_DLRX_CFG_GLOBAL_dlrx_congestion_bit_timeout) >> B_DLRX_CFG_GLOBAL_dlrx_congestion_bit_timeout))

#define DLRX_CFG_GLOBAL_dlrx_congestion_bit_timeout_set_indirect(base, offset, val)    \
	do {                                                              \
		(*(base + O_DLRX_CFG_GLOBAL_dlrx_congestion_bit_timeout + offset)) &= (~(M_DLRX_CFG_GLOBAL_dlrx_congestion_bit_timeout));    \
		(*(base + O_DLRX_CFG_GLOBAL_dlrx_congestion_bit_timeout + offset)) |= ((val << B_DLRX_CFG_GLOBAL_dlrx_congestion_bit_timeout) & M_DLRX_CFG_GLOBAL_dlrx_congestion_bit_timeout);    \
	} while (0)

#define DLRX_CFG_GLOBAL_dlrx_congestion_bit_timeout_set_direct(dword, val)    \
	do {                                                               \
		(dword) &= (~(M_DLRX_CFG_GLOBAL_dlrx_congestion_bit_timeout));    \
		(dword) |= ((val << B_DLRX_CFG_GLOBAL_dlrx_congestion_bit_timeout) & M_DLRX_CFG_GLOBAL_dlrx_congestion_bit_timeout);    \
	} while (0)

#define DLRX_CFG_GLOBAL_dlrx_congestion_bit_timeout_clear_indirect(base, offset)	((*(base + O_DLRX_CFG_GLOBAL_dlrx_congestion_bit_timeout + offset)) &= (~(M_DLRX_CFG_GLOBAL_dlrx_congestion_bit_timeout)))

#define DLRX_CFG_GLOBAL_dlrx_congestion_bit_timeout_clear_direct(dword)	((dword) &= (~(M_DLRX_CFG_GLOBAL_dlrx_congestion_bit_timeout)))

#define O_DLRX_CFG_GLOBAL_dlrx_timout_count_th 12
#define B_DLRX_CFG_GLOBAL_dlrx_timout_count_th 0
#define W_DLRX_CFG_GLOBAL_dlrx_timout_count_th 32
#define M_DLRX_CFG_GLOBAL_dlrx_timout_count_th 0xffffffff

#define DLRX_CFG_GLOBAL_dlrx_timout_count_th_get_indirect(base, offset)	((((*(base + O_DLRX_CFG_GLOBAL_dlrx_timout_count_th + offset)) & M_DLRX_CFG_GLOBAL_dlrx_timout_count_th) >> B_DLRX_CFG_GLOBAL_dlrx_timout_count_th))

#define DLRX_CFG_GLOBAL_dlrx_timout_count_th_get_direct(dword)	((((dword) & M_DLRX_CFG_GLOBAL_dlrx_timout_count_th) >> B_DLRX_CFG_GLOBAL_dlrx_timout_count_th))

#define DLRX_CFG_GLOBAL_dlrx_timout_count_th_set_indirect(base, offset, val)    \
	do {                                                              \
		(*(base + O_DLRX_CFG_GLOBAL_dlrx_timout_count_th + offset)) &= (~(M_DLRX_CFG_GLOBAL_dlrx_timout_count_th));    \
		(*(base + O_DLRX_CFG_GLOBAL_dlrx_timout_count_th + offset)) |= ((val << B_DLRX_CFG_GLOBAL_dlrx_timout_count_th) & M_DLRX_CFG_GLOBAL_dlrx_timout_count_th);    \
	} while (0)

#define DLRX_CFG_GLOBAL_dlrx_timout_count_th_set_direct(dword, val)    \
	do {                                                               \
		(dword) &= (~(M_DLRX_CFG_GLOBAL_dlrx_timout_count_th));    \
		(dword) |= ((val << B_DLRX_CFG_GLOBAL_dlrx_timout_count_th) & M_DLRX_CFG_GLOBAL_dlrx_timout_count_th);    \
	} while (0)

#define DLRX_CFG_GLOBAL_dlrx_timout_count_th_clear_indirect(base, offset)	((*(base + O_DLRX_CFG_GLOBAL_dlrx_timout_count_th + offset)) &= (~(M_DLRX_CFG_GLOBAL_dlrx_timout_count_th)))

#define DLRX_CFG_GLOBAL_dlrx_timout_count_th_clear_direct(dword)	((dword) &= (~(M_DLRX_CFG_GLOBAL_dlrx_timout_count_th)))

#define O_DLRX_CFG_GLOBAL_dlrx_qca_hw_sub_type 13
#define B_DLRX_CFG_GLOBAL_dlrx_qca_hw_sub_type 0
#define W_DLRX_CFG_GLOBAL_dlrx_qca_hw_sub_type 32
#define M_DLRX_CFG_GLOBAL_dlrx_qca_hw_sub_type 0xffffffff

#define DLRX_CFG_GLOBAL_dlrx_qca_hw_sub_type_get_indirect(base, offset)	((((*(base + O_DLRX_CFG_GLOBAL_dlrx_qca_hw_sub_type + offset)) & M_DLRX_CFG_GLOBAL_dlrx_qca_hw_sub_type) >> B_DLRX_CFG_GLOBAL_dlrx_qca_hw_sub_type))

#define DLRX_CFG_GLOBAL_dlrx_qca_hw_sub_type_get_direct(dword)	((((dword) & M_DLRX_CFG_GLOBAL_dlrx_qca_hw_sub_type) >> B_DLRX_CFG_GLOBAL_dlrx_qca_hw_sub_type))

#define DLRX_CFG_GLOBAL_dlrx_qca_hw_sub_type_set_indirect(base, offset, val)    \
	do {                                                              \
		(*(base + O_DLRX_CFG_GLOBAL_dlrx_qca_hw_sub_type + offset)) &= (~(M_DLRX_CFG_GLOBAL_dlrx_qca_hw_sub_type));    \
		(*(base + O_DLRX_CFG_GLOBAL_dlrx_qca_hw_sub_type + offset)) |= ((val << B_DLRX_CFG_GLOBAL_dlrx_qca_hw_sub_type) & M_DLRX_CFG_GLOBAL_dlrx_qca_hw_sub_type);    \
	} while (0)

#define DLRX_CFG_GLOBAL_dlrx_qca_hw_sub_type_set_direct(dword, val)    \
	do {                                                               \
		(dword) &= (~(M_DLRX_CFG_GLOBAL_dlrx_qca_hw_sub_type));    \
		(dword) |= ((val << B_DLRX_CFG_GLOBAL_dlrx_qca_hw_sub_type) & M_DLRX_CFG_GLOBAL_dlrx_qca_hw_sub_type);    \
	} while (0)

#define DLRX_CFG_GLOBAL_dlrx_qca_hw_sub_type_clear_indirect(base, offset)	((*(base + O_DLRX_CFG_GLOBAL_dlrx_qca_hw_sub_type + offset)) &= (~(M_DLRX_CFG_GLOBAL_dlrx_qca_hw_sub_type)))

#define DLRX_CFG_GLOBAL_dlrx_qca_hw_sub_type_clear_direct(dword)	((dword) &= (~(M_DLRX_CFG_GLOBAL_dlrx_qca_hw_sub_type)))

#define O_DLRX_CFG_CTXT_PEER_HANDLER_cfg_peer_handler 0
#define B_DLRX_CFG_CTXT_PEER_HANDLER_cfg_peer_handler 0
#define W_DLRX_CFG_CTXT_PEER_HANDLER_cfg_peer_handler 32
#define M_DLRX_CFG_CTXT_PEER_HANDLER_cfg_peer_handler 0xffffffff

#define DLRX_CFG_CTXT_PEER_HANDLER_cfg_peer_handler_get_indirect(base, offset)	((((*(base + O_DLRX_CFG_CTXT_PEER_HANDLER_cfg_peer_handler + offset)) & M_DLRX_CFG_CTXT_PEER_HANDLER_cfg_peer_handler) >> B_DLRX_CFG_CTXT_PEER_HANDLER_cfg_peer_handler))

#define DLRX_CFG_CTXT_PEER_HANDLER_cfg_peer_handler_get_direct(dword)	((((dword) & M_DLRX_CFG_CTXT_PEER_HANDLER_cfg_peer_handler) >> B_DLRX_CFG_CTXT_PEER_HANDLER_cfg_peer_handler))

#define DLRX_CFG_CTXT_PEER_HANDLER_cfg_peer_handler_set_indirect(base, offset, val)    \
	do {                                                              \
		(*(base + O_DLRX_CFG_CTXT_PEER_HANDLER_cfg_peer_handler + offset)) &= (~(M_DLRX_CFG_CTXT_PEER_HANDLER_cfg_peer_handler));    \
		(*(base + O_DLRX_CFG_CTXT_PEER_HANDLER_cfg_peer_handler + offset)) |= ((val << B_DLRX_CFG_CTXT_PEER_HANDLER_cfg_peer_handler)&M_DLRX_CFG_CTXT_PEER_HANDLER_cfg_peer_handler);    \
	} while (0)

#define DLRX_CFG_CTXT_PEER_HANDLER_cfg_peer_handler_set_direct(dword, val)    \
	do {                                                               \
		(dword) &= (~(M_DLRX_CFG_CTXT_PEER_HANDLER_cfg_peer_handler));    \
		(dword) |= ((val << B_DLRX_CFG_CTXT_PEER_HANDLER_cfg_peer_handler)&M_DLRX_CFG_CTXT_PEER_HANDLER_cfg_peer_handler);    \
	} while (0)

#define DLRX_CFG_CTXT_PEER_HANDLER_cfg_peer_handler_clear_indirect(base, offset)	((*(base + O_DLRX_CFG_CTXT_PEER_HANDLER_cfg_peer_handler + offset)) &= (~(M_DLRX_CFG_CTXT_PEER_HANDLER_cfg_peer_handler)))

#define DLRX_CFG_CTXT_PEER_HANDLER_cfg_peer_handler_clear_direct(dword)	((dword) &= (~(M_DLRX_CFG_CTXT_PEER_HANDLER_cfg_peer_handler)))

#define O_DLRX_CFG_CTXT_PEER_HANDLER_cfg_peer_count 1
#define B_DLRX_CFG_CTXT_PEER_HANDLER_cfg_peer_count 0
#define W_DLRX_CFG_CTXT_PEER_HANDLER_cfg_peer_count 32
#define M_DLRX_CFG_CTXT_PEER_HANDLER_cfg_peer_count 0xffffffff

#define DLRX_CFG_CTXT_PEER_HANDLER_cfg_peer_count_get_indirect(base, offset)	((((*(base + O_DLRX_CFG_CTXT_PEER_HANDLER_cfg_peer_count + offset)) & M_DLRX_CFG_CTXT_PEER_HANDLER_cfg_peer_count) >> B_DLRX_CFG_CTXT_PEER_HANDLER_cfg_peer_count))

#define DLRX_CFG_CTXT_PEER_HANDLER_cfg_peer_count_get_direct(dword)	((((dword) & M_DLRX_CFG_CTXT_PEER_HANDLER_cfg_peer_count) >> B_DLRX_CFG_CTXT_PEER_HANDLER_cfg_peer_count))

#define DLRX_CFG_CTXT_PEER_HANDLER_cfg_peer_count_set_indirect(base, offset, val)    \
	do {                                                              \
		(*(base + O_DLRX_CFG_CTXT_PEER_HANDLER_cfg_peer_count + offset)) &= (~(M_DLRX_CFG_CTXT_PEER_HANDLER_cfg_peer_count));    \
		(*(base + O_DLRX_CFG_CTXT_PEER_HANDLER_cfg_peer_count + offset)) |= ((val << B_DLRX_CFG_CTXT_PEER_HANDLER_cfg_peer_count) & M_DLRX_CFG_CTXT_PEER_HANDLER_cfg_peer_count);    \
	} while (0)

#define DLRX_CFG_CTXT_PEER_HANDLER_cfg_peer_count_set_direct(dword, val)    \
	do {                                                               \
		(dword) &= (~(M_DLRX_CFG_CTXT_PEER_HANDLER_cfg_peer_count));    \
		(dword) |= ((val << B_DLRX_CFG_CTXT_PEER_HANDLER_cfg_peer_count) & M_DLRX_CFG_CTXT_PEER_HANDLER_cfg_peer_count);    \
	} while (0)

#define DLRX_CFG_CTXT_PEER_HANDLER_cfg_peer_count_clear_indirect(base, offset)	((*(base + O_DLRX_CFG_CTXT_PEER_HANDLER_cfg_peer_count + offset)) &= (~(M_DLRX_CFG_CTXT_PEER_HANDLER_cfg_peer_count)))

#define DLRX_CFG_CTXT_PEER_HANDLER_cfg_peer_count_clear_direct(dword)	((dword) &= (~(M_DLRX_CFG_CTXT_PEER_HANDLER_cfg_peer_count)))

#endif

