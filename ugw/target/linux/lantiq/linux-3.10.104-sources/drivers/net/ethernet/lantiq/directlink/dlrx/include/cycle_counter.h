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
#ifndef __CYCLEX_COUNTER_H__
#define __CYCLEX_COUNTER_H__

/*---------------------------------------------
*          #defines
*---------------------------------------------*/
extern void *CycleCounter_Create(char *);
extern void CycleCounter_Start(void *);
extern void CycleCounter_End(void *);

extern void *function1_cycles, *function2_cycles, *function3_cycles;
extern void *function4_cycles, *function5_cycles, *function6_cycles;
extern void *function7_cycles, *function8_cycles;
extern void *functionA_cycles, *functionB_cycles;
extern void *functionC_cycles, *functionD_cycles;

/* above function1_cycles  and fucntion2_cycles
* are pointer for function1 and function2 respectively
*/


#endif
