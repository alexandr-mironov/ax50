
#include <linux/module.h>
#include <linux/init.h>
#include <linux/sched.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/errno.h>
#include <linux/proc_fs.h>
#include <linux/interrupt.h>
#include <linux/timer.h>
#include <asm/mipsregs.h>
#include <asm/mipsmtregs.h>
#include <net/datapath_proc_api.h>
#include <linux/version.h>
#include <linux/clk.h>
#include <linux/math64.h> 


#ifndef TC_USAGE
/*
 * MIPS32 VPEControl Register (CP0 Register 1, Select 1)
 */
#define VPECONTROL_TARGTC1	0x000000ff	
#define  VPECONTROL_TARGTC_SHIFT	 0	
#define VPECONTROL_TARGVPE	0x00003c00	
#define  VPECONTROL_TARGVPE_SHIFT	10	
#define VPECONTROL_TE1		0x00008000	
#define VPECONTROL_EXCPT1	0x00070000	
#define  VPECONTROL_EXCPT_SHIFT	        16	


#define _m32c0_mftc0(rt,sel)                                                   \
({                                                                      \
         unsigned long  __res;                                          \
                                                                        \
        __asm__ __volatile__(                                           \
        "       .set    push                                    \n"     \
        "       .set    mips32r2                                \n"     \
        "       .set    noat                                    \n"     \
        "       # mftc0 $1, $" #rt ", " #sel "                  \n"     \
        "       .word   0x41000800 | (" #rt " << 16) | " #sel " \n"     \
        "       move    %0, $1                                  \n"     \
        "       .set    pop                                     \n"     \
        : "=r" (__res));                                                \
                                                                        \
        __res;                                                          \
})

#define _m32c0_mttc0(rd, sel, v)                                                       \
({                                                                      \
        __asm__ __volatile__(                                           \
        "       .set    push                                    \n"     \
        "       .set    mips32r2                                \n"     \
        "       .set    noat                                    \n"     \
        "       move    $1, %0                                  \n"     \
        "       # mttc0 %0," #rd ", " #sel "                    \n"     \
        "       .word   0x41810000 | (" #rd " << 11) | " #sel " \n"     \
        "       .set    pop                                     \n"     \
        :                                                               \
        : "r" (v));                                                     \
})

/*
 * VPE
 */
#define mips32_getvpecontrol()		_m32c0_mftc0(1, 1)
#define mips32_setvpecontrol(val)	_m32c0_mttc0(1, 1, val)
#define mips32_mt_getvpeconf0()		_m32c0_mftc0(1, 2)
#define mips32_mt_setvpeconf0(val)	_m32c0_mttc0(1, 2, val)

/*
 * targeted VPE register macros
 */
#define mips32_mt_settarget(tc) \
	mips32_setvpecontrol ( \
		(mips32_getvpecontrol () & ~(VPECONTROL_TARGTC1)) \
		| ((tc) << VPECONTROL_TARGTC_SHIFT))


/////////////////// performance counters //////////////
#define mips32_mt_getperfcntrs0()	_m32c0_mftc0(25, 1)
#define mips32_mt_getperfcntrs1()	_m32c0_mftc0(25, 3)
#define mips32_mt_setperfcntrs0(val)   _m32c0_mttc0(25, 1, val)
#define mips32_mt_setperfcntrs1(val)   _m32c0_mttc0(25, 3, val)
#define mips32_mt_setperfcontrl0(val)	_m32c0_mttc0(25, 0, val)
#define mips32_mt_setperfcontrl1(val)	_m32c0_mttc0(25, 2, val)


#endif /* TC_USAGE */

/* Macro Defnitions */

#define CYCLE_EVENT 0
#define INST_EVENT 1
#define TC_NUM 5
#define STAL_EVENT 18
#define time_elapsed(cycles) (cycles * 2 )
#define TRUE 1
#define FALSE 0
#define STD_DUR 3
#define NUM_CORE 2
#define CORE0 0
#define CORE1 1
#define CPU0 0
#define CPU2 2
#define PARAM_SIZE 16
#define BUF_SIZE 256
#define NUM_CPU 2
#define NUM_VPE 2

#define M_PERFCTL_EXL			(1	<<  0)
#define M_PERFCTL_KERNEL		(1	<<  1)
#define M_PERFCTL_SUPERVISOR		(1  <<  2)
#define M_PERFCTL_USER			(1  <<  3)
#define M_PERFCTL_INTERRUPT_ENABLE	(1	<<  5)
#define M_PERFCTL_EVENT(event) (((event) & 0x3ff)  << 5)
#define M_PERFCTL_EVENT_MASK 0xfe0
#define M_PERFCTL_CONFIG_MASK 0x3fff801f
#define M_PERFCTL_MT_EN(filter) ((filter) << 20)
#define M_PERFCTL_VPEID(vpe) ((vpe)   << 16)
#define M_PERFCTL_CONFIG_MASK 0x3fff801f

#define	   M_TC_EN_ALL			M_PERFCTL_MT_EN(0)
#define	   M_TC_EN_VPE			M_PERFCTL_MT_EN(1)
#define	   M_TC_EN_TC			M_PERFCTL_MT_EN(2)

/* Function Prototypes */
int config_perf_counter(int);
int duration_handling(int timeout_val);
void system_load_report(void);


/* Global variables */
static int duration=0,flag=0;

static struct proc_dir_entry* s_cpuload_proc;
struct clk *clk_get_cpu(void);

/* structure definitions */

typedef struct {		
    uint32_t    start;
    uint32_t    end; 
    uint64_t    total; 
}timestamp_t;

typedef struct { 
    uint64_t    instr;
    uint64_t    vpeload;
    uint64_t    vpeload_mod; 
    timestamp_t inst_ts; 
}vpe_info_t;

typedef struct {  
    uint64_t    coreload; /* total number of cycles consumed */
    uint64_t    total_insts;
    uint64_t    duration;
    uint64_t    coreload_mod;
    vpe_info_t  vpe_info[NUM_VPE];  
    uint64_t    cpi; /*Cycles per Inststruction */
    uint64_t    cpi_mod;
    uint64_t 	tmp_cpi; /*for calculation only used*/
    timestamp_t cycle_ts;  /* timstamp for cycles elapsed */
    timestamp_t dur_ts;	/*System taken time */
    timestamp_t stalls_ts; /* all stall on CPU */
	
	uint64_t    tmp_coreload;
	uint64_t    tmp_coreload_mod;
}core_info_t;

typedef struct {  
    uint64_t    sysload;
    uint64_t    sysload_mod;
    uint64_t    cpu_freq_MHz;
    uint64_t    duration;
    uint64_t    duration_mod;
    uint64_t    time_elaps;
    uint64_t    total_cycles;
    core_info_t    core_info[NUM_CPU];
}sysinfo_t;

sysinfo_t sysinfo;

/*
*	System load computed, considering all running CPU's.
	@sys_load  : (Total Cycles Used by both CPUs) / ( time_taken(dur) by both COREs)
*/
void system_load_report()
{
	uint64_t tmp=0;
	sysinfo_t    *p_sys_info    = &sysinfo;
	core_info_t  *p_core_info_0 = &sysinfo.core_info[CORE0];
	core_info_t  *p_core_info_1 = &sysinfo.core_info[CORE1];
	
	p_sys_info->time_elaps = (time_elapsed(p_core_info_0->duration) + 
					time_elapsed(p_core_info_1->duration));

	/* flag=2, div by both core freq */ 
	if(flag == 2) {
		tmp = div64_u64(p_sys_info->time_elaps, (p_sys_info->cpu_freq_MHz * 2));
	} else {
			tmp = div64_u64(p_sys_info->time_elaps, (p_sys_info->cpu_freq_MHz));
			}

	p_sys_info->duration = (div64_u64(tmp ,1000000));
	p_sys_info->duration_mod = (div64_u64(tmp * 100,1000000) -
					(p_sys_info->duration * 100));
	if(p_sys_info->duration_mod >= 95 ) {
		p_sys_info->duration = p_sys_info->duration + 1;
		p_sys_info->duration_mod = 0;
	}
	
	p_sys_info->total_cycles =  (p_core_info_0->cycle_ts.total + 
					p_core_info_1->cycle_ts.total) * 100;
	p_sys_info->sysload = div64_u64(p_sys_info->total_cycles,
					p_sys_info->time_elaps);
	p_sys_info->sysload_mod = (div64_u64(p_sys_info->total_cycles * 100,
			p_sys_info->time_elaps) - (p_sys_info->sysload * 100));
	     

}

/*
 *cpuload_report
 *@core_num 	Core number
 *Calculating	Total cycles,Instructions executed VPE0 & VPE1. 
				Core_load and Total instructions 
 * @CPI 	Cycles per instruction  
 */
static void cpuload_report(int core_num)
{
	uint64_t tmp=0;
	core_info_t  *p_core_info = &sysinfo.core_info[core_num];
	vpe_info_t   *p_vpe0_info = &sysinfo.core_info[core_num].vpe_info[0];
	vpe_info_t   *p_vpe1_info = &sysinfo.core_info[core_num].vpe_info[1];

	/* Calculating coreload */    
	/* Simplification : core_load =	((Cycles Consumed * 100) /
						(cycles taken for execution * 2)) 
	*/  
	#if 0  
	p_core_info->coreload = div64_u64((p_core_info->cycle_ts.total * 100),
					time_elapsed(p_core_info->duration));

	/* To get the rem, To print more accurate CPU load */
	tmp = div64_u64((p_core_info->cycle_ts.total * 10000),
					time_elapsed(p_core_info->duration));
	p_core_info->coreload_mod = ( tmp - (p_core_info->coreload * 100 ));
	#endif 

	p_core_info->total_insts = (p_vpe0_info->instr + p_vpe1_info->instr);
	
	/* CPI(Cycles per Instructions)
	 * To get more accurate VPE load, We need to multiply Consumed_Cycles by 100
	 * After getting VPE_load, divide VPE_load by 100
	 */
	p_core_info->cpi = div64_u64(p_core_info->cycle_ts.total ,  
					 p_core_info->total_insts);

	/* for vpe load calculation tmp_cpi is used only */ 
	p_core_info->tmp_cpi = div64_u64(p_core_info->cycle_ts.total * 100,  
					p_core_info->total_insts);

	/* coreload calculation using cpi */
	p_core_info->coreload = div64_u64(( p_core_info->tmp_cpi * 
					p_core_info->total_insts ), 
					time_elapsed(p_core_info->duration));
	
	tmp = div64_u64(( p_core_info->tmp_cpi * p_core_info->total_insts * 100),
					time_elapsed(p_core_info->duration));
	p_core_info->coreload_mod = ( tmp - (p_core_info->coreload * 100));

	/* To print decimal */
	tmp = div64_u64(p_core_info->cycle_ts.total * 100, p_core_info->total_insts);
	p_core_info->cpi_mod = ( tmp - ( p_core_info->cpi * 100));

	
  	/* VPE0 load */
	p_vpe0_info->vpeload = div64_u64((p_core_info->tmp_cpi * p_vpe0_info->instr),
					time_elapsed(p_core_info->duration));	

	tmp = div64_u64((p_core_info->tmp_cpi * p_vpe0_info->instr * 100),
					time_elapsed(p_core_info->duration));
	p_vpe0_info->vpeload_mod = (tmp - (p_vpe0_info->vpeload * 100));
	
	/* VPE1 load */
	p_vpe1_info->vpeload = div64_u64((p_core_info->tmp_cpi * p_vpe1_info->instr),
					time_elapsed(p_core_info->duration));

	tmp =  div64_u64((p_core_info->tmp_cpi * p_vpe1_info->instr * 100),
					time_elapsed(p_core_info->duration));

	p_vpe1_info->vpeload_mod = (tmp - (p_vpe1_info->vpeload * 100));
	
	/* 2nd deciaml handling */
	tmp = (p_vpe0_info->vpeload_mod + p_vpe1_info->vpeload_mod);
	tmp = (tmp > 100) ? (tmp - 100) : tmp;
	tmp = (p_core_info->coreload_mod - tmp );
	
	if( tmp == 1 && (p_vpe0_info->vpeload_mod < 99))
		p_vpe0_info->vpeload_mod = p_vpe0_info->vpeload_mod + tmp;
	else if( tmp == 1 && (p_vpe1_info->vpeload_mod < 99))
		p_vpe1_info->vpeload_mod = p_vpe1_info->vpeload_mod + tmp;
	
}

/*
 *read_timestamp_start
 *@core_num	core number
 *	Reading Performance counters per core or vpe 
 *	before starting timer, 
 */
void
read_timestamp_start(int core_num) 
{

  	core_info_t  *p_core_info = &sysinfo.core_info[core_num];
  	vpe_info_t   *p_vpe0_info = &sysinfo.core_info[core_num].vpe_info[0];
  	vpe_info_t   *p_vpe1_info = &sysinfo.core_info[core_num].vpe_info[1];
	
	write_c0_count((unsigned int)0);	
	write_c0_perfcntr0((unsigned int)0);
	write_c0_perfcntr1((unsigned int)0);
	mips32_mt_setperfcntrs0((unsigned int)0);
	mips32_mt_setperfcntrs1((unsigned int)0);

	p_core_info->dur_ts.start = read_c0_count();
  	p_core_info->cycle_ts.start = read_c0_perfcntr0();
	p_core_info->stalls_ts.start = mips32_mt_getperfcntrs0();
  	p_vpe0_info->inst_ts.start = read_c0_perfcntr1();
  	p_vpe1_info->inst_ts.start = mips32_mt_getperfcntrs1();
}

/*
 * read_timestamp_end
 *	@core_num	
 *	Reading Performance counters after timer expires 
 */
void read_timestamp_end(int core_num)
{
	uint64_t tmp;
	core_info_t  *p_core_info = &sysinfo.core_info[core_num];
 	vpe_info_t   *p_vpe0_info = &sysinfo.core_info[core_num].vpe_info[0];
	vpe_info_t   *p_vpe1_info = &sysinfo.core_info[core_num].vpe_info[1];

 	p_core_info->cycle_ts.end = read_c0_perfcntr0();
	p_core_info->stalls_ts.end = mips32_mt_getperfcntrs0();
 	p_vpe0_info->inst_ts.end = read_c0_perfcntr1();
 	p_vpe1_info->inst_ts.end = mips32_mt_getperfcntrs1();
	p_core_info->dur_ts.end = read_c0_count();

	/* Calculating total cycles */
	if (p_core_info->cycle_ts.start  > p_core_info->cycle_ts.end)
		tmp = (uint64_t)((0xffffffff - p_core_info->cycle_ts.start ) + 	
						p_core_info->cycle_ts.end);
	else
		tmp = (uint64_t)(p_core_info->cycle_ts.end -
					 	p_core_info->cycle_ts.start);
	p_core_info->cycle_ts.total += tmp; 

	/* Stalls */
	if (p_core_info->stalls_ts.start  > p_core_info->stalls_ts.end)
		tmp = (uint64_t)((0xffffffff  - p_core_info->stalls_ts.start ) + 	
						p_core_info->stalls_ts.end );
	else
		tmp =(uint64_t)( p_core_info->stalls_ts.end -
						p_core_info->stalls_ts.start);
	p_core_info->stalls_ts.total += tmp; 

	/* Calculating Total Instruction executed on VPE0 */
	if (p_vpe0_info->inst_ts.start > p_vpe0_info->inst_ts.end)
		tmp = (uint64_t)((0xffffffff - p_vpe0_info->inst_ts.start) +
						p_vpe0_info->inst_ts.end );	 
	else
		tmp = (uint64_t)(p_vpe0_info->inst_ts.end -
						p_vpe0_info->inst_ts.start);
	p_vpe0_info->instr += tmp;
	
	/* Calculating Total Instruction executed on VPE1 */	
	if (p_vpe1_info->inst_ts.start > p_vpe1_info->inst_ts.end)
		tmp = (uint64_t)((0xffffffff- p_vpe1_info->inst_ts.start) +
						p_vpe1_info->inst_ts.end );
	else
		tmp = (uint64_t)(p_vpe1_info->inst_ts.end -
						p_vpe1_info->inst_ts.start);
	p_vpe1_info->instr += tmp;
	
	if ( p_core_info->dur_ts.start > p_core_info->dur_ts.end)
		tmp = (uint64_t)((0xffffffff - p_core_info->dur_ts.start) +
						p_core_info->dur_ts.end);
	else
		tmp = (uint64_t)( p_core_info->dur_ts.end -
						p_core_info->dur_ts.start);
	p_core_info->duration += tmp;

}


/*
 * config_perf_counter
 * _perfctrl0 and _perfctrl1 register are configured 
 * Before start counting the cycles and Instructions 
 */
int config_perf_counter(int core_num)
{
	uint32_t configctrl=0, eventctrl=0;

	/* Configctrl has Kernel,EXL,Superviser,VPEID and MASK */
	configctrl = (M_PERFCTL_KERNEL | M_PERFCTL_EXL | M_PERFCTL_USER |
					M_PERFCTL_SUPERVISOR | M_PERFCTL_VPEID(0) |
					 M_TC_EN_VPE) & M_PERFCTL_CONFIG_MASK;

	/* Write eventctrl value to register, eventctrl is consist of
	 CYCLE_EVENT and configctrl
	 */
	eventctrl = M_PERFCTL_EVENT(CYCLE_EVENT) | configctrl; 
	write_c0_perfctrl0(eventctrl);

	/* Write eventctrl value to register, eventctrl is consist of
	 INST_EVENT and configctrl
	*/
	eventctrl = M_PERFCTL_EVENT(INST_EVENT) | configctrl;
	write_c0_perfctrl1(eventctrl);
	
	/* Setting Specific TC_NUM, Writing eventctrl regirster of that TC_NUM
	*/  
   	mips32_mt_settarget(TC_NUM);
 	
	eventctrl = M_PERFCTL_EVENT(STAL_EVENT) | M_PERFCTL_VPEID(1) | configctrl;
	mips32_mt_setperfcontrl0(eventctrl);

 	eventctrl = M_PERFCTL_EVENT(INST_EVENT) | M_PERFCTL_VPEID(1) | configctrl;
	mips32_mt_setperfcontrl1(eventctrl);

  return 0;
}


/*
* Display the CPU load and VPE load. 
*/
static int proc_read_cpuload(struct seq_file *seq, void *v)
{
	sysinfo_t    *p_sys_info    = &sysinfo;
	core_info_t  *p_core_info_0 = &sysinfo.core_info[CORE0];
	vpe_info_t   *p_vpe0_info_0 = &sysinfo.core_info[CORE0].vpe_info[0];
	vpe_info_t   *p_vpe1_info_0 = &sysinfo.core_info[CORE0].vpe_info[1];
	core_info_t  *p_core_info_1 = &sysinfo.core_info[CORE1];
	vpe_info_t   *p_vpe0_info_1 = &sysinfo.core_info[CORE1].vpe_info[0];
	vpe_info_t   *p_vpe1_info_1 = &sysinfo.core_info[CORE1].vpe_info[1];

	seq_printf(seq,"Core_Frequency \t %llu\n",p_sys_info->cpu_freq_MHz);
	seq_printf(seq,"Duration(secs) \t %llu.%llu \n",p_sys_info->duration, 
			p_sys_info->duration_mod);
	if(p_sys_info->sysload_mod <= 9)
	seq_printf(seq,"System_Load(%) \t %llu.0%llu\n", p_sys_info->sysload,
			p_sys_info->sysload_mod);
	else
	seq_printf(seq,"System_Load(%) \t %llu.%llu\n", p_sys_info->sysload,
			p_sys_info->sysload_mod);

	if( flag == 2) {
		seq_printf(seq,"\nMetrics \t Core0 \t\t Core1\n");
		seq_printf(seq,"CPU_Cycles \t %llu \t %llu\n", 
				time_elapsed(p_core_info_0->duration),
				time_elapsed(p_core_info_1->duration));
		seq_printf(seq,"Used_Cycles \t %llu \t %llu\n",
				p_core_info_0->cycle_ts.total,
				p_core_info_1->cycle_ts.total);
		seq_printf(seq,"VPE0_Inst \t %llu \t %llu\n",
				p_vpe0_info_0->instr,p_vpe0_info_1->instr);
		seq_printf(seq,"VPE1_Inst \t %llu \t %llu\n", 
				p_vpe1_info_0->instr,p_vpe1_info_1->instr);
		seq_printf(seq,"Total_inst \t %llu \t %llu\n",
				p_core_info_0->total_insts, p_core_info_1->total_insts);

		if(p_core_info_0->cpi_mod <= 9 && p_core_info_1->cpi_mod <= 9)
		seq_printf(seq,"CPI \t\t %llu.0%llu \t\t %llu.0%llu\n", p_core_info_0->cpi,
				p_core_info_0->cpi_mod, p_core_info_1->cpi,
				p_core_info_1->cpi_mod);
		else if(p_core_info_0->cpi_mod <= 9)
		seq_printf(seq,"CPI \t\t %llu.0%llu \t\t %llu.%llu\n", p_core_info_0->cpi,
				p_core_info_0->cpi_mod, p_core_info_1->cpi,
				p_core_info_1->cpi_mod);
		else if(p_core_info_1->cpi_mod <= 9)
		seq_printf(seq,"CPI \t\t %llu.%llu \t\t %llu.0%llu\n", p_core_info_0->cpi,
				p_core_info_0->cpi_mod, p_core_info_1->cpi,
				p_core_info_1->cpi_mod);
		else	
		seq_printf(seq,"CPI \t\t %llu.%llu \t\t %llu.%llu\n", p_core_info_0->cpi,
				p_core_info_0->cpi_mod, p_core_info_1->cpi,
				p_core_info_1->cpi_mod);


		if(p_core_info_0->coreload_mod <= 9 && p_core_info_1->coreload_mod <= 9) 
		seq_printf(seq,"Core_Load(%) \t %llu.0%llu \t\t %llu.0%llu\n",
				p_core_info_0->coreload, p_core_info_0->coreload_mod,
				p_core_info_1->coreload, p_core_info_1->coreload_mod);
		else if(p_core_info_0->coreload_mod <= 9 ) 
		seq_printf(seq,"Core_Load(%) \t %llu.0%llu \t\t %llu.%llu\n",
				p_core_info_0->coreload, p_core_info_0->coreload_mod,
				p_core_info_1->coreload, p_core_info_1->coreload_mod);
		else if(p_core_info_1->coreload_mod <= 9 ) 
		seq_printf(seq,"Core_Load(%) \t %llu.%llu \t\t %llu.0%llu\n",
				p_core_info_0->coreload, p_core_info_0->coreload_mod,
				p_core_info_1->coreload, p_core_info_1->coreload_mod);
		else  
		seq_printf(seq,"Core_Load(%) \t %llu.%llu \t\t %llu.%llu\n",
				p_core_info_0->coreload, p_core_info_0->coreload_mod,
				p_core_info_1->coreload, p_core_info_1->coreload_mod);

		if(p_vpe0_info_0->vpeload_mod <= 9 && p_vpe0_info_1->vpeload_mod <= 9)
		seq_printf(seq,"VPE0_Load(%) \t %llu.0%llu \t\t %llu.0%llu\n",
				p_vpe0_info_0->vpeload, p_vpe0_info_0->vpeload_mod,
				p_vpe0_info_1->vpeload, p_vpe0_info_1->vpeload_mod);
		else if(p_vpe0_info_0->vpeload_mod <= 9)
		seq_printf(seq,"VPE0_Load(%) \t %llu.0%llu \t\t %llu.%llu\n",
				p_vpe0_info_0->vpeload, p_vpe0_info_0->vpeload_mod,
				p_vpe0_info_1->vpeload, p_vpe0_info_1->vpeload_mod);
		else if(p_vpe0_info_1->vpeload_mod <= 9)
		seq_printf(seq,"VPE0_Load(%) \t %llu.%llu \t\t %llu.0%llu\n",
				p_vpe0_info_0->vpeload, p_vpe0_info_0->vpeload_mod,
				p_vpe0_info_1->vpeload, p_vpe0_info_1->vpeload_mod);
		else 
		seq_printf(seq,"VPE0_Load(%) \t %llu.%llu \t\t %llu.%llu\n",
				p_vpe0_info_0->vpeload, p_vpe0_info_0->vpeload_mod,
				p_vpe0_info_1->vpeload, p_vpe0_info_1->vpeload_mod);
	

		if(p_vpe1_info_0->vpeload_mod <= 9 && p_vpe1_info_1->vpeload_mod <= 9 )
		seq_printf(seq,"VPE1_Load(%) \t %llu.0%llu \t\t %llu.0%llu\n", 
				p_vpe1_info_0->vpeload, p_vpe1_info_0->vpeload_mod,
				p_vpe1_info_1->vpeload, p_vpe1_info_1->vpeload_mod);
		else if(p_vpe1_info_0->vpeload_mod <= 9 )
		seq_printf(seq,"VPE1_Load(%) \t %llu.0%llu \t\t %llu.%llu\n", 
				p_vpe1_info_0->vpeload, p_vpe1_info_0->vpeload_mod,
				p_vpe1_info_1->vpeload, p_vpe1_info_1->vpeload_mod);
		else if(p_vpe1_info_1->vpeload_mod <= 9 )
		seq_printf(seq,"VPE1_Load(%) \t %llu.%llu \t\t %llu.0%llu\n", 
				p_vpe1_info_0->vpeload, p_vpe1_info_0->vpeload_mod,
				p_vpe1_info_1->vpeload, p_vpe1_info_1->vpeload_mod);
		else
		seq_printf(seq,"VPE1_Load(%) \t %llu.%llu \t\t %llu.%llu\n", 
				p_vpe1_info_0->vpeload, p_vpe1_info_0->vpeload_mod,
				p_vpe1_info_1->vpeload, p_vpe1_info_1->vpeload_mod);

	} else {
			seq_printf(seq,"\nMetrics \t Core0\n");
			seq_printf(seq,"CPU_Cycles \t %llu \n", 
					time_elapsed(p_core_info_0->duration));
			seq_printf(seq,"Used_Cycles \t %llu \n",
					p_core_info_0->cycle_ts.total);
			seq_printf(seq,"VPE0_Inst \t %llu \n",
					p_vpe0_info_0->instr);
			seq_printf(seq,"VPE1_Inst \t %llu \n", 
					p_vpe1_info_0->instr);
			seq_printf(seq,"Total_inst \t %llu \n",
					p_core_info_0->total_insts);
			if(p_core_info_0->cpi_mod <= 9)
			seq_printf(seq,"CPI \t\t %llu.0%llu \n", p_core_info_0->cpi,
					p_core_info_0->cpi_mod); 
			else
			seq_printf(seq,"CPI \t\t %llu.%llu \n", p_core_info_0->cpi,
					p_core_info_0->cpi_mod); 

			if(p_core_info_0->coreload_mod <= 9)
			seq_printf(seq,"Core_Load(%) \t %llu.0%llu \n",
					p_core_info_0->coreload, p_core_info_0->coreload_mod);
			else
			seq_printf(seq,"Core_Load(%) \t %llu.%llu \n",
					p_core_info_0->coreload, p_core_info_0->coreload_mod);

			if(p_vpe0_info_0->vpeload_mod <= 9)
			seq_printf(seq,"VPE0_Load(%) \t %llu.0%llu \n",
					p_vpe0_info_0->vpeload, p_vpe0_info_0->vpeload_mod);
			else
			seq_printf(seq,"VPE0_Load(%) \t %llu.%llu \n",
					p_vpe0_info_0->vpeload, p_vpe0_info_0->vpeload_mod);

			if(p_vpe1_info_0->vpeload_mod <= 9)
			seq_printf(seq,"VPE1_Load(%) \t %llu.0%llu \n", 
					p_vpe1_info_0->vpeload, p_vpe1_info_0->vpeload_mod);
			else
			seq_printf(seq,"VPE1_Load(%) \t %llu.%llu \n", 
					p_vpe1_info_0->vpeload, p_vpe1_info_0->vpeload_mod);

			}

	return 0;
}

/*
* stats for other core
 	@info  : either to start reading the counters or end reading counters
		@TRUE  : Start reading counters
		@FALSE : End reading counters 
*/

void smp_cpuload_other_core(void *info)
{
	int start = (int)info;
	int core_num = smp_processor_id() <= 1 ?CORE0:CORE1;
	
	if(start) {
		config_perf_counter(core_num);
		read_timestamp_start(core_num);
	}
	else {
		read_timestamp_end(core_num);
	}
}

/*
* Reading duration from the proc/cpuload
* Duration : In sec.
*/
static ssize_t proc_write_cpuload(struct file *file, 
		const char __user *user_buf, size_t count, loff_t *data)
{
 
	char buf[BUF_SIZE];
	int num,loop_count,leftout_time,i;
	char *param_list[PARAM_SIZE];
	unsigned char *str; 
 	struct clk *cpu_clk;
	sysinfo_t *p_sys_info = &sysinfo;

 	memset(&sysinfo, 0, sizeof(sysinfo));
	
	if (copy_from_user(buf, user_buf, min(count, (sizeof(buf) - 1))))
		return -EFAULT;

	num = dp_split_buffer(buf, param_list, ARRAY_SIZE(param_list));

	if (num <= 0 || num >= 2 || dp_strcmpi(param_list[0], "help") == 0) {
		pr_info("echo duration > /proc/cpuload\n");
		return count;
	}

	str = param_list[0];
	for(i=0 ; i < strlen(param_list[0]); i++) {
		if(str[i] == '.'){
			pr_info("Provide duration in integer!!\n");
			return count;
		}
	}

	duration = dp_atoi(param_list[0]);
	/* check duration , if 0, take deafult duration=5 */
	
	if(duration == 0) {
		pr_info("Zero can't be taken, Running for default duration(5 sec)\n");
		duration = 5;
	}	
	/* Getting CPU frequency */
	cpu_clk = clk_get_cpu();
	p_sys_info->cpu_freq_MHz = clk_get_rate(cpu_clk) / 1000000;
	

	/* More than STD_DUE is handled in loop */
	if(duration > STD_DUR) {
		loop_count = duration / STD_DUR;
		leftout_time = duration % STD_DUR;

		for( i=0;i<loop_count;i++)
			duration_handling(STD_DUR);

		if(leftout_time)
			duration_handling(leftout_time);
	} else 
			duration_handling(duration);

	/* Calculate the cpu load */
	cpuload_report(CORE0);
	if(flag == 2)
	cpuload_report(CORE1);

    /* report system load */
	system_load_report();

	return count;
}

/*
* This function is called,for each STD_DUR(duration)
*/
int duration_handling(int timeout_val)
{

	int cpu_id,core_num,core_num2,status;
	
	cpu_id = smp_processor_id();
		
	if( cpu_id == 0 || cpu_id == 1 ) {
		core_num = CORE0;
		core_num2 = CPU2;
	}
	else if( cpu_id == 2 || cpu_id == 3 ) {
		core_num = CORE1;
		core_num2 = CPU0;
	}else {
		pr_info(" Wrong CPU_id !!!! \n");
		return 0;
	}

	/* flag=2, when both cores are up */	
	if(flag == 2){
		status = smp_call_function_single(core_num2,
					smp_cpuload_other_core,(void*)TRUE,TRUE);
		if(status)
			   pr_info("SMP call failed ",status);
	}
	
	config_perf_counter(core_num);
	
	/*  get the timestamp */
	read_timestamp_start(core_num);
  	
	/*start the timer */
	set_current_state(TASK_INTERRUPTIBLE);
	schedule_timeout(timeout_val * HZ);
	
	/* get the timestamp */
	read_timestamp_end(core_num);
	
	/* Based on flag,smp_call for other call */
	if(flag == 2)
		smp_call_function_single(core_num2,
			smp_cpuload_other_core,(void *)FALSE,TRUE);
	return 0;
        
}


static int proc_open_cpuload(struct inode *inode, struct file *file)
{
	return single_open(file, proc_read_cpuload, NULL);
}

static struct file_operations s_proc_cpuload_fops = {   
	.owner      = THIS_MODULE,    
	.open       = proc_open_cpuload,
	.read       = seq_read,
	.write	    = proc_write_cpuload,
	.llseek     = seq_lseek,
	.release    = seq_release,
};

static void cpuload_proc_create(void)
{
	proc_create("cpuload", S_IRUGO, s_cpuload_proc, &s_proc_cpuload_fops);
}

static void cpuload_proc_destory(void)
{   
	remove_proc_entry("cpuload", s_cpuload_proc);    
	proc_remove(s_cpuload_proc);
	s_cpuload_proc = NULL;
}

static int __init cpuload_init(void)
{ 
	int j; 
	/* To know, How many core's are running in system */
	for_each_online_cpu(j)
			flag++;

	memset(&sysinfo, 0, sizeof(sysinfo)); 
	printk("cpuload module inserted\n"); 
	cpuload_proc_create();  
	return 0;
}

static void __exit cpuload_exit(void)
{
	printk("cpuload module removed\n"); 
	cpuload_proc_destory();
}

module_init(cpuload_init);
module_exit(cpuload_exit);
MODULE_AUTHOR("LANTIQ");
MODULE_DESCRIPTION("CPU LOAD");
MODULE_LICENSE("GPL");






