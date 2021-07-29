/*******************************************************************************

  Intel MIPS TC driver
  Copyright(c) 2017 Intel Corporation.

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
#ifndef __MIPS_TC_SG__
#define __MIPS_TC_SG__

#define SUPPORT_DSL_BONDING_FEATURE 1
#ifdef SUPPORT_DSL_BONDING_FEATURE
#define RUN_MIPS_TC 1
/* #define USE_CACHED_MECHANISM 1 */
#define rx_out_des_size		16
extern void mips_tc_init(u32 *);
extern int mips_tc_sg(struct mips_tc_sg_mem *shared_vir_mem);

#if USE_CACHED_MECHANISM
int mips_tc_cache_flush(u32 start_addr, u32 size);
int mips_tc_cache_invalidate(u32 start_addr, u32 size);
#endif /* USE_CACHED_MECHANISM */

#endif
#endif /* __MIPS_TC_SG__ */
