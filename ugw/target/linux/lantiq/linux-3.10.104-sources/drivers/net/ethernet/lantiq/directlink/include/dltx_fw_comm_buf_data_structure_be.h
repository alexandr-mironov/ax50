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
#ifndef __DLTX_FW_COMM_BUF_DATA_STRUCTURE_BE_H_
#define __DLTX_FW_COMM_BUF_DATA_STRUCTURE_BE_H_

typedef struct {

	unsigned int rsvd14:31;
	unsigned int cmpl_status:1;

	unsigned int tx_cmpl_mib;

} dltx_tx_cmpl_flag_t;

typedef struct {

	unsigned int rsvd7:8;
	unsigned int num_pb_ptr_to_release:8;
	unsigned int rsvd8:8;
	unsigned int msg_type:8;

	unsigned int free_txpb_ptr[128];

} dltx_tx_cmpl_msg_t;

typedef struct {

	unsigned int cfg_badr_cpu_ce4;

	unsigned int cfg_num_cpu_ce4;

	unsigned int cpu_ce4_read_index;

	unsigned int cpu_ce4_write_index;

	unsigned int cpu_ce4_ppe_read_index;

	unsigned int cpu_ce4_msg_done;

	unsigned int _dw_res0[2];

} dltx_cfg_ctxt_cpu_ce4des_t;

typedef struct {

	unsigned int source_buffer_pointer;

	unsigned int meta_data:14;
	unsigned int byte_swap:1;
	unsigned int gather:1;
	unsigned int source_buffer_length:16;

} dltx_cpu_ce4des_format_t;

typedef struct {

	unsigned int cfg_badr_tx_cmpl_flag;

	unsigned int cfg_badr_tx_cmpl_buf;

	unsigned int cfg_num_tx_cmpl_buf;

	unsigned int _dw_res0[5];

} dltx_cfg_ctxt_comm_buff_t;

typedef struct {

	unsigned int valid;

	unsigned int action_type;

	unsigned int _dw_res0[62];

} dltx_drv_msg_t;

#endif

