/*******************************************************************************
**
** FILE NAME    : ppa_api_proc.c
** PROJECT      : PPA
** MODULES      : PPA API (Routing/Bridging Acceleration APIs)
**
** DATE         : 3 NOV 2008
** AUTHOR       : Xu Liang
** DESCRIPTION  : PPA Protocol Stack Hook API Proc Filesystem Functions
** COPYRIGHT    :              Copyright (c) 2009
**                          Lantiq Deutschland GmbH
**                   Am Campeon 3; 85579 Neubiberg, Germany
**
**   For licensing information, see the file 'LICENSE' in the root folder of
**   this software module.
**
** HISTORY
** $Date        $Author         $Comment
** 03 NOV 2008  Xu Liang        Initiate Version
*******************************************************************************/



/*
 * ####################################
 *              Head File
 * ####################################
 */

/*
 *  Common Head File
 */
//#include <linux/autoconf.h>
#include <linux/version.h>
#if LINUX_VERSION_CODE < KERNEL_VERSION(2, 6, 33)
#include <linux/autoconf.h>
#else
#include <generated/autoconf.h>
#endif
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/version.h>
#include <linux/types.h>
#include <linux/init.h>
#include <linux/slab.h>
#include <linux/proc_fs.h>
#include <linux/seq_file.h>
#include <linux/netdevice.h>
#include <linux/in.h>
#include <net/sock.h>
#include <net/ip_vs.h>
#include <asm/time.h>
#include <linux/kallsyms.h>

/*
 *  PPA Specific Head File
 */
#include <net/ppa_api.h>
#include <net/ppa_ppe_hal.h>
#include "ppa_api_misc.h"
#include "ppa_api_session.h"
#if IS_ENABLED(CONFIG_LTQ_PPA_QOS)
#include "ppa_api_qos.h"
#endif
#if defined(CONFIG_LTQ_PPA_HANDLE_CONNTRACK_SESSIONS)
#include "ppa_api_session_limit.h"
#endif
#include "ppa_api_netif.h"
#include "ppe_drv_wrapper.h"
#if defined(CONFIG_LTQ_PPA_HAL_SELECTOR) && CONFIG_LTQ_PPA_HAL_SELECTOR
#include "ppa_hal_wrapper.h"
#endif
#include "ppa_api_proc.h"
#include "ppa_api_tools.h"
#include "ppa_api_debug.h"
#include "ppa_api_sw_accel.h"


/*
 * ####################################
 *              Definition
 * ####################################
 */

#define STRBUF_LEN 64
#define STRBUF_SMALL_LEN 32

/*
 *  Compilation Switch
 */



/*
 * ####################################
 *              Data Type
 * ####################################
 */



/*
 * ####################################
 *             Declaration
 * ####################################
 */
#if defined(CONFIG_LTQ_PPA_GRX500) && CONFIG_LTQ_PPA_GRX500
static ssize_t proc_write_classprio_seq(struct file *, const char __user *, size_t, loff_t *);
static int proc_read_classprio_seq_open(struct inode *, struct file *);
static int proc_read_classprio(struct seq_file *, void *);
#if defined(CONFIG_LTQ_PPA_COC_SUPPORT)
static int proc_read_threshold(struct seq_file *, void *);
static ssize_t proc_write_threshold(struct file *, const char __user *, size_t, loff_t *);
static int proc_read_threshold_seq_open(struct inode *, struct file *);

static int proc_read_window(struct seq_file *, void *);
static ssize_t proc_write_window(struct file *, const char __user *, size_t, loff_t *);
static int proc_read_window_seq_open(struct inode *, struct file *);
#endif
#endif

static int proc_read_dbg(struct seq_file *, void *);
static ssize_t proc_write_dbg(struct file *, const char __user *, size_t, loff_t *);
static int proc_read_dbg_seq_open(struct inode *, struct file *);

static int proc_read_hook(struct seq_file *, void *);
#if defined(CONFIG_LTQ_PPA_HANDLE_CONNTRACK_SESSIONS)
static int proc_read_sess_mgmt(struct seq_file *, void *);
#endif
static ssize_t proc_write_hook(struct file *, const char __user *, size_t, loff_t *);
static int proc_read_hook_seq_open(struct inode *, struct file *);

static int proc_read_filter(struct seq_file *, void *);
static ssize_t proc_write_filter(struct file *, const char __user *, size_t, loff_t *);
static int proc_read_filter_seq_open(struct inode *, struct file *);

static int proc_read_queue_per_port(struct seq_file *, void *);
static ssize_t proc_write_queue_per_port(struct file *, const char __user *, size_t, loff_t *);
static int proc_read_queue_per_port_seq_open(struct inode *, struct file *);

static void *proc_read_phys_port_seq_start(struct seq_file *, loff_t *);
static void *proc_read_phys_port_seq_next(struct seq_file *, void *, loff_t *);
static void proc_read_phys_port_seq_stop(struct seq_file *, void *);
static int proc_read_phys_port_seq_show(struct seq_file *, void *);
static int proc_read_phys_port_seq_open(struct inode *, struct file *);

static void *proc_read_netif_seq_start(struct seq_file *, loff_t *);
static void *proc_read_netif_seq_next(struct seq_file *, void *, loff_t *);
static void proc_read_netif_seq_stop(struct seq_file *, void *);
static int proc_read_netif_seq_show(struct seq_file *, void *);
static int proc_read_netif_seq_open(struct inode *, struct file *);
static ssize_t proc_file_write_netif(struct file *, const char __user *, size_t, loff_t *);

static void *proc_read_session_seq_start(struct seq_file *, loff_t *);
static void *proc_read_session_seq_next(struct seq_file *, void *, loff_t *);
static void proc_read_session_seq_stop(struct seq_file *, void *);
static void print_session_ifid(struct seq_file *, char *, uint32_t);
static void printk_session_ifid(char *, uint32_t);
static void print_session_flags(struct seq_file *, char *, uint32_t);
static void printk_session_flags(char *, uint32_t);
#if defined(ENABLE_SESSION_DEBUG_FLAGS) && ENABLE_SESSION_DEBUG_FLAGS
static void print_session_debug_flags(struct seq_file *, char *, uint32_t);
static void printk_session_debug_flags(char *, uint32_t);
#endif
static INLINE int proc_read_routing_mini_session_seq_show(struct seq_file *, void *);
static INLINE int proc_read_mc_mini_group_seq_show(struct seq_file *, void *);
static INLINE int proc_read_bridging_mini_session_seq_show(struct seq_file *, void *);
static int proc_read_mini_session_seq_show(struct seq_file *, void *);
static int proc_read_mini_session_seq_open(struct inode *, struct file *);
static ssize_t proc_file_write_mini_session(struct file *, const char __user *, size_t, loff_t *);
int ppa_session_find_unicast_routing(char *);
int ppa_session_find_unicast_routing_sw_hdr(char *);
int ppa_session_find_multicast_routing(char *);
int ppa_session_find_bridging(char *);
void ppa_unicast_routing_print_session(struct session_list_item *p_item);
void ppa_unicast_routing_print_session_sw_hdr(struct session_list_item *p_item);
void ppa_multicast_routing_print_session(struct mc_group_list_item *p_item);
void ppa_bridging_print_session(struct bridging_session_list_item *p_item);
unsigned char *ppa_get_sw_hdr_tx_handler_name(int *tx_handler);

static INLINE int proc_read_routing_session_seq_show(struct seq_file *, void *);
static INLINE int proc_read_mc_group_seq_show(struct seq_file *, void *);
static INLINE int proc_read_bridging_session_seq_show(struct seq_file *, void *);
static int proc_read_session_seq_show(struct seq_file *, void *);
static int proc_read_session_seq_open(struct inode *, struct file *);

#ifdef CONFIG_LTQ_PPA_API_DIRECTPATH
  static void *proc_read_directpath_seq_start(struct seq_file *, loff_t *);
  static void *proc_read_directpath_seq_next(struct seq_file *, void *, loff_t *);
  static void proc_read_directpath_seq_stop(struct seq_file *, void *);
  static int proc_read_directpath_seq_show(struct seq_file *, void *);
  static int proc_read_directpath_seq_open(struct inode *, struct file *);
  static ssize_t proc_file_write_directpath(struct file *, const char __user *, size_t, loff_t *);
#endif

#if defined(CONFIG_LTQ_PPA_API_SW_FASTPATH)
extern int32_t (*ppa_sw_fastpath_enable_hook)(uint32_t, uint32_t);
extern int32_t (*ppa_get_sw_fastpath_status_hook)(uint32_t *, uint32_t);
static int proc_read_swfpstatus_seq_open(struct inode *, struct file *);
static ssize_t proc_write_swfpstatus(struct file *, const char __user *, size_t , loff_t *);
#if IS_ENABLED(CONFIG_LTQ_PPA_SGA)
static int proc_read_sga_status_seq_open(struct inode *, struct file *);
static ssize_t proc_write_sga_status(struct file *, const char __user *, size_t , loff_t *);
#endif
#if IS_ENABLED(CONFIG_LTQ_PPA_SGA)
extern int32_t (*ppa_sga_enable_hook)(uint32_t *f_enable, uint32_t flags);
extern int32_t (*ppa_sga_status_hook)(uint32_t *f_enable, uint32_t flags);
#endif
#if defined(CONFIG_LTQ_PPA_TCP_LITEPATH) && CONFIG_LTQ_PPA_TCP_LITEPATH
extern int32_t (*ppa_tcp_litepath_enable_hook)(uint32_t, uint32_t);
extern int32_t (*ppa_get_tcp_litepath_status_hook)(uint32_t *, uint32_t);
static int proc_read_tcp_litepath_status_seq_open(struct inode *, struct file *);
static ssize_t proc_write_tcp_litepath_status(struct file *, const char __user *, size_t , loff_t *);
#endif
#endif
static int proc_file_br_flow_open(struct inode *inode, struct file *file);
static ssize_t proc_file_br_flow_write(struct file *file, 
                                       const char __user *buf, 
                                       size_t count, 
                                       loff_t *ppos);

static unsigned char *ppa_sw_ipv4_name();
static unsigned char *ppa_sw_ipv6_name();
static unsigned char *ppa_sw_6rd_name();
static unsigned char *ppa_sw_dslite_name();
static unsigned char *ppa_sw_bridged_name();
#if defined(CONFIG_LTQ_PPA_TCP_LITEPATH) && CONFIG_LTQ_PPA_TCP_LITEPATH
static unsigned char *ppa_sw_ltcp_name();
#if defined(CONFIG_LTQ_PPA_LRO) && CONFIG_LTQ_PPA_LRO
static unsigned char *ppa_sw_ltcp_lro_name();
#endif
#endif

typedef unsigned char *(*ppa_get_sw_hdr_type_name)();

static ppa_get_sw_hdr_type_name ppa_get_sw_hdr_type[SW_ACC_TYPE_MAX] = {
  ppa_sw_ipv4_name,
  ppa_sw_ipv6_name,
  ppa_sw_6rd_name,
  ppa_sw_dslite_name,
  ppa_sw_bridged_name,
#if defined(CONFIG_LTQ_PPA_TCP_LITEPATH) && CONFIG_LTQ_PPA_TCP_LITEPATH
  ppa_sw_ltcp_name,
#if defined(CONFIG_LTQ_PPA_LRO) && CONFIG_LTQ_PPA_LRO
  ppa_sw_ltcp_lro_name
#endif
#endif
};

//  string process help function
static int stricmp(const char *, const char *);
static int strincmp(const char *, const char *, int);
static INLINE unsigned int get_number(char **p, int *len, int is_hex);
static INLINE int get_token(char **, char **, int *, int *);
static INLINE void ignore_space(char **, int *);
int ppa_split_buffer(char *buffer, char *array[], int max_param_num);



/*
 * ####################################
 *           Global Variable
 * ####################################
 */
extern int g_ppa_proc_dir_flag;
extern struct proc_dir_entry *g_ppa_proc_dir;
static char session_buf[STRBUF_LEN];

static short ppa_port_queue_num_status;
static int g_ppa_api_proc_dir_flag = 0;
static struct proc_dir_entry *g_ppa_api_proc_dir = NULL;

#if defined(CONFIG_LTQ_PPA_GRX500) && CONFIG_LTQ_PPA_GRX500
extern int g_eth_class_prio_map[2][16];
static struct file_operations g_proc_file_classprio_seq_fops = {
    .owner      = THIS_MODULE,
    .open       = proc_read_classprio_seq_open,
    .read       = seq_read,
    .write      = proc_write_classprio_seq,
    .llseek     = seq_lseek,
    .release    = single_release,
};
static int proc_read_classprio_seq_open(struct inode *inode, struct file *file)
{
    return single_open(file, proc_read_classprio, NULL);
}

#if defined(CONFIG_LTQ_PPA_COC_SUPPORT)
extern uint64_t g_ppa_dp_thresh;
extern uint64_t g_ppa_dp_window;
static int g_ppa_api_coc_proc_dir_flag = 0;
static struct proc_dir_entry *g_ppa_api_coc_proc_dir = NULL;

static struct file_operations g_proc_file_window_seq_fops = {
    .owner      = THIS_MODULE,
    .open       = proc_read_window_seq_open,
    .read       = seq_read,
    .write      = proc_write_window,
    .llseek     = seq_lseek,
    .release    = single_release,
};

static int proc_read_window_seq_open(struct inode *inode, struct file *file)
{
    return single_open(file, proc_read_window, NULL);
}

static struct file_operations g_proc_file_threshold_seq_fops = {
    .owner      = THIS_MODULE,
    .open       = proc_read_threshold_seq_open,
    .read       = seq_read,
    .write      = proc_write_threshold,
    .llseek     = seq_lseek,
    .release    = single_release,
};

static int proc_read_threshold_seq_open(struct inode *inode, struct file *file)
{
    return single_open(file, proc_read_threshold, NULL);
}

#endif
#endif

static struct file_operations g_proc_file_dbg_seq_fops = {
    .owner      = THIS_MODULE,
    .open       = proc_read_dbg_seq_open,
    .read       = seq_read,
    .write      = proc_write_dbg,
    .llseek     = seq_lseek,
    .release    = single_release,
};

static int proc_read_dbg_seq_open(struct inode *inode, struct file *file)
{
    return single_open(file, proc_read_dbg, NULL);
}

static struct file_operations g_proc_file_hook_seq_fops = {
    .owner      = THIS_MODULE,
    .open       = proc_read_hook_seq_open,
    .read       = seq_read,
    .write      = proc_write_hook,
    .llseek     = seq_lseek,
    .release    = single_release,
};

static int proc_read_hook_seq_open(struct inode *inode, struct file *file)
{
    return single_open(file, proc_read_hook, NULL);
}

static struct file_operations g_proc_file_filter_seq_fops = {
    .owner      = THIS_MODULE,
    .open       = proc_read_filter_seq_open,
    .read       = seq_read,
    .write      = proc_write_filter,
    .llseek     = seq_lseek,
    .release    = single_release,
};

static int proc_read_filter_seq_open(struct inode *inode, struct file *file)
{
    return single_open(file, proc_read_filter, NULL);
}

static struct file_operations g_proc_file_queue_per_port_seq_fops = {
    .owner      = THIS_MODULE,
    .open       = proc_read_queue_per_port_seq_open,
    .read       = seq_read,
    .write      = proc_write_queue_per_port,
    .llseek     = seq_lseek,
    .release    = single_release,
};

static int proc_read_queue_per_port_seq_open(struct inode *inode, struct file *file)
{
    return single_open(file, proc_read_queue_per_port, NULL);
}

#if IS_ENABLED(CONFIG_LTQ_PPA_GRX500) && IS_ENABLED(CONFIG_LTQ_PPA_QOS)
static ssize_t proc_write_inggrp(struct file *file, const char __user *buf, size_t count, loff_t *data)
{
    ppa_qos_inggrp_free_list();
    return count;
}

extern int32_t qosal_get_qos_inggrp(PPA_QOS_INGGRP inggrp, PPA_IFNAME ifnames[PPA_QOS_MAX_IF_PER_INGGRP][PPA_IF_NAME_SIZE]);
static int proc_read_inggrp(struct seq_file *seq, void *v)
{
    PPA_IFNAME ifnames[PPA_QOS_MAX_IF_PER_INGGRP][PPA_IF_NAME_SIZE];
    int32_t i, j, count;

    seq_printf(seq, "Ingress Groups interfaces\n");

    memset(ifnames, 0, sizeof(ifnames));

    for (i = 0; i < PPA_QOS_INGGRP_MAX; i++) {
        count = qosal_get_qos_inggrp(i, ifnames);
        if ( count ) {
            seq_printf(seq, "Ingress Group %d has %d interfaces:\n", i, count);
            for (j = 0; j < count; j++)
                seq_printf(seq, "  %s\n", ifnames[j]);
        }
        memset(ifnames, 0, sizeof(ifnames));
    }

    return 0;
}

static int proc_read_inggrp_seq_open(struct inode *inode, struct file *file)
{
    return single_open(file, proc_read_inggrp, NULL);
}

static struct file_operations g_proc_file_inggrp_seq_fops = {
    .owner      = THIS_MODULE,
    .open       = proc_read_inggrp_seq_open,
    .read       = seq_read,
    .write      = proc_write_inggrp,
    .llseek     = seq_lseek,
    .release    = single_release,
};
#endif
#if defined(CONFIG_LTQ_PPA_HANDLE_CONNTRACK_SESSIONS)
static int proc_read_sess_mgmt_seq_open(struct inode *inode, struct file *file)
{
    return single_open(file, proc_read_sess_mgmt, NULL);
}

static struct file_operations g_proc_file_sess_mgmt_seq_fops = {
    .owner      = THIS_MODULE,
    .open       = proc_read_sess_mgmt_seq_open,
    .read       = seq_read,
    .llseek     = seq_lseek,
    .release    = single_release,
};
#endif

static struct seq_operations g_proc_read_phys_port_seq_ops = {
    .start      = proc_read_phys_port_seq_start,
    .next       = proc_read_phys_port_seq_next,
    .stop       = proc_read_phys_port_seq_stop,
    .show       = proc_read_phys_port_seq_show,
};
static struct file_operations g_proc_file_phys_port_seq_fops = {
    .owner      = THIS_MODULE,
    .open       = proc_read_phys_port_seq_open,
    .read       = seq_read,
    .llseek     = seq_lseek,
    .release    = seq_release,
};
static uint32_t g_proc_read_phys_port_pos = 0;

static struct seq_operations g_proc_read_netif_seq_ops = {
    .start      = proc_read_netif_seq_start,
    .next       = proc_read_netif_seq_next,
    .stop       = proc_read_netif_seq_stop,
    .show       = proc_read_netif_seq_show,
};
static struct file_operations g_proc_file_netif_seq_fops = {
    .owner      = THIS_MODULE,
    .open       = proc_read_netif_seq_open,
    .read       = seq_read,
    .write      = proc_file_write_netif,
    .llseek     = seq_lseek,
    .release    = seq_release,
};
static uint32_t g_proc_read_netif_pos = 0;

static struct seq_operations g_proc_read_session_seq_ops = {
    .start      = proc_read_session_seq_start,
    .next       = proc_read_session_seq_next,
    .stop       = proc_read_session_seq_stop,
    .show       = proc_read_session_seq_show,
};

static struct seq_operations g_proc_read_mini_session_seq_ops = {
	.start      = proc_read_session_seq_start,
	.next       = proc_read_session_seq_next,
	.stop       = proc_read_session_seq_stop,
	.show       = proc_read_mini_session_seq_show,
};

static struct file_operations g_proc_file_session_seq_fops = {
    .owner      = THIS_MODULE,
    .open       = proc_read_session_seq_open,
    .read       = seq_read,
    .llseek     = seq_lseek,
    .release    = seq_release,
};

static struct file_operations g_proc_file_mini_session_seq_fops = {
	.owner      = THIS_MODULE,
	.open       = proc_read_mini_session_seq_open,
	.read       = seq_read,
	.write      = proc_file_write_mini_session,
	.llseek     = seq_lseek,
	.release    = seq_release,
};
static uint32_t g_proc_read_session_pos = 0;
static uint32_t g_proc_read_session_pos_prev = ~0;

static char *g_str_dest[] = {
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL
};

#ifdef CONFIG_LTQ_PPA_API_DIRECTPATH
  static struct seq_operations g_proc_read_directpath_seq_ops = {
      .start      = proc_read_directpath_seq_start,
      .next       = proc_read_directpath_seq_next,
      .stop       = proc_read_directpath_seq_stop,
      .show       = proc_read_directpath_seq_show,
  };
  static struct file_operations g_proc_file_directpath_seq_fops = {
      .owner      = THIS_MODULE,
      .open       = proc_read_directpath_seq_open,
      .read       = seq_read,
      .write      = proc_file_write_directpath,
      .llseek     = seq_lseek,
      .release    = seq_release,
  };
  static uint32_t g_proc_read_directpath_pos = 0;
#endif

#if defined(CONFIG_LTQ_PPA_API_SW_FASTPATH)
static struct file_operations g_proc_file_swfp_status = {
    .owner      = THIS_MODULE,
    .open       = proc_read_swfpstatus_seq_open,
    .read       = seq_read,
    .write      = proc_write_swfpstatus,
    .llseek     = seq_lseek,
    .release    = seq_release,
};
#if IS_ENABLED(CONFIG_LTQ_PPA_SGA)
static struct file_operations g_proc_file_sga_status = {
    .owner      = THIS_MODULE,
    .open       = proc_read_sga_status_seq_open,
    .read       = seq_read,
    .write      = proc_write_sga_status,
    .llseek     = seq_lseek,
    .release    = seq_release,
};
#endif
#if defined(CONFIG_LTQ_PPA_TCP_LITEPATH) && CONFIG_LTQ_PPA_TCP_LITEPATH
static struct file_operations g_proc_file_tcp_litepath_status = {
    .owner      = THIS_MODULE,
    .open       = proc_read_tcp_litepath_status_seq_open,
    .read       = seq_read,
    .write      = proc_write_tcp_litepath_status,
    .llseek     = seq_lseek,
    .release    = seq_release,
};
#endif
#endif

static struct file_operations g_proc_file_br_flow_learning = {
    .owner      = THIS_MODULE,
    .open       = proc_file_br_flow_open,
    .read       = seq_read,
    .write      = proc_file_br_flow_write,
    .llseek     = seq_lseek,
    .release    = seq_release,
};

#if LINUX_VERSION_CODE >= KERNEL_VERSION(2,6,32)
extern struct proc_dir_entry proc_root;
#endif

enum {
	FAMILY_DANUBE   = 1,
	FAMILY_TWINPASS = 2,
	FAMILY_AMAZON_SE= 3,
	FAMILY_AR9      = 5,
	FAMILY_VR9      = 7,
	FAMILY_AR10     = 8,
};

enum {
	ITF_2MII        = 1,
	ITF_1MII_ATMWAN = 2,
	ITF_1MII_PTMWAN = 3,
	ITF_2MII_ATMWAN = 4,
	ITF_2MII_PTMWAN = 5,
	ITF_2MII_BONDING= 7,
};

enum {
    TYPE_A1     = 1,
    TYPE_B1     = 2,
    TYPE_E1     = 3,
    TYPE_A5     = 4,
    TYPE_D5     = 5,
    TYPE_D5v2   = 6,
    TYPE_E5     = 7,
};



/*
 * ####################################
 *           Extern Variable
 * ####################################
 */



/*
 * ####################################
 *            Local Function
 * ####################################
 */
int Atoi(char *str)
{
    int res = 0;  // Initialize result
    int sign = 1;  // Initialize sign as positive
    int i = 0;  // Initialize index of first digit

    // If number is negative, then update sign
    if (str[0] == '-')
    {
        sign = -1;
        i++;  // Also update index of first digit
    }

    // Iterate through all digits and update the result
    for (; str[i] != '\0'; ++i)
        res = res*10 + str[i] - '0';

    // Return result with sign
    return sign*res;
}


#if defined(CONFIG_LTQ_PPA_GRX500) && CONFIG_LTQ_PPA_GRX500
static int proc_read_classprio(struct seq_file *seq, void *v)
{

    int i, j;

    //  skb->priority to firmware queue map (for LAN interface, QId is virtual one maitained by driver)
    seq_printf(seq,        "Class to Priority Map:\n");
    seq_printf(seq,        "  class     :  0  1  2  3  4  5  6  7  8  9 10 11 12 13 14 15\n");
    for ( i = 0; i < 2; i++ )
    {
        seq_printf(seq,    "  wlan%d     :", i);
        for ( j = 0; j < NUM_ENTITY(g_eth_class_prio_map[i]); j++ )
            seq_printf(seq," %2d", g_eth_class_prio_map[i][j]);
        seq_printf(seq,    "\n");
    }

    return 0;

}

static ssize_t proc_write_classprio_seq(struct file *file, const char __user *buf, size_t count, loff_t *data)
{

    char local_buf[2048];
    int len;
    char *p1, *p2;
    int colon = 1;
    unsigned int port = ~0;
    int prio = -1;
    int class = -1;

    len = sizeof(local_buf) < count ? sizeof(local_buf) - 1 : count;
    len = len - copy_from_user(local_buf, buf, len);
    local_buf[len] = 0;

    p1 = local_buf;
    while ( get_token(&p1, &p2, &len, &colon) )
    {
        if ( stricmp(p1, "help") == 0 )
        {
            printk("echo <wlanX> class xx prio xx [class xx prio xx] > /proc/ppa/api/classprio\n");
            break;
        }
        else if ( stricmp(p1, "wlan0") == 0 )
        {
            port = 0;
            prio = class = -1;
            ppa_debug(DBG_ENABLE_MASK_DEBUG_PRINT,"port = 0");
        }
        else if ( stricmp(p1, "wlan1") == 0 )
        {
            port = 1;
            prio = class = -1;
            ppa_debug(DBG_ENABLE_MASK_DEBUG_PRINT,"port = 1");
        }
        else if ( stricmp(p1, "wlan2") == 0 )
        {
            port = 2;
            prio = class = -1;
            ppa_debug(DBG_ENABLE_MASK_DEBUG_PRINT,"port = 2");
        }
        else if ( stricmp(p1, "wlan3") == 0 )
        {
            port = 3;
            prio = class = -1;
            ppa_debug(DBG_ENABLE_MASK_DEBUG_PRINT,"port = 3");
        }
/*        else if ( stricmp(p1, "pvc") == 0 )
        {
            err("atm is not valid");
            prio = queue = -1;
        }*/
        else if ( port != ~0 )
        {
            if ( stricmp(p1, "c") == 0 || stricmp(p1, "class") == 0 )
            {
                ignore_space(&p2, &len);
                class = get_number(&p2, &len, 0);
                ppa_debug(DBG_ENABLE_MASK_DEBUG_PRINT,"class = %d", class);
                if ( port > 0 && port <= 1 && class >= 0 && class < NUM_ENTITY(g_eth_class_prio_map[port]) )
                {
                    if ( prio >= 0 )
                        g_eth_class_prio_map[port][class] = prio;
                }
                else
                {
                    ppa_debug(DBG_ENABLE_MASK_DEBUG_PRINT,"class (%d) is out of range 0 - %d", class, NUM_ENTITY(g_eth_class_prio_map[port]) - 1);
                }
            }
            else if ( stricmp(p1, "p") == 0 || stricmp(p1, "prio") == 0 )
            {
                ignore_space(&p2, &len);
                prio = get_number(&p2, &len, 0);
                ppa_debug(DBG_ENABLE_MASK_DEBUG_PRINT,"prio = %d", prio);
                if ( port > 0 && port <= 1 && prio >= 0 && prio < 8 )
                {
                    if ( class >= 0 )
                        g_eth_class_prio_map[port][class] = prio;
                }
                else
                {
                    ppa_debug(DBG_ENABLE_MASK_DEBUG_PRINT,"prio (%d) is out of range 0 - %d", prio, 8);
                }
            }
            else
            {
                ppa_debug(DBG_ENABLE_MASK_DEBUG_PRINT,"unknown command (%s)", p1);
            }
        }
        else
        {
            ppa_debug(DBG_ENABLE_MASK_DEBUG_PRINT,"unknown command (%s)", p1);
        }

        p1 = p2;
        colon = 1;
    }

    return count;
}

#if defined(CONFIG_LTQ_PPA_COC_SUPPORT)
static int proc_read_window(struct seq_file *seq, void *v)
{
    seq_printf(seq, "Window = %lld sec\n", g_ppa_dp_window);
}

static ssize_t proc_write_window(struct file *file, const char __user *buf, size_t count, loff_t *data)
{
    int len;
    char str[64];
    char *p;

    len = min(count, (size_t)(sizeof(str) - 1));
    len -= ppa_copy_from_user(str, buf, len);
    while ( len && str[len - 1] <= ' ' )
        len--;
    str[len] = 0;
    for ( p = str; *p && *p <= ' '; p++, len-- );
    if ( !*p )
        return count;
    else if ( strincmp(p, "help", 4) == 0 )
    	printk("<time(in sec)> > /proc/ppa/api/coc/window\n");
   	
    g_ppa_dp_window = Atoi(p);
    printk("window = %lld\n", g_ppa_dp_window);   
    return count ;
}

static int proc_read_threshold(struct seq_file *seq, void *v)
{
    seq_printf(seq, "Threshold =%lld bytes\n", g_ppa_dp_thresh);
}

static ssize_t proc_write_threshold(struct file *file, const char __user *buf, size_t count, loff_t *data)
{
    int len;
    char str[64];
    char *p;

    len = min(count, (size_t)(sizeof(str) - 1));
    len -= ppa_copy_from_user(str, buf, len);
    while ( len && str[len - 1] <= ' ' )
        len--;
    str[len] = 0;
    for ( p = str; *p && *p <= ' '; p++, len-- );
    if ( !*p )
        return count;
    else if ( strincmp(p, "help", 4) == 0 )
    	printk("<No of bytes> > /proc/ppa/api/coc/threshold\n");

    g_ppa_dp_thresh = Atoi(p);
    printk("threshold = %lld\n", g_ppa_dp_thresh);   
    return count ;
}
#endif
#endif

struct ppa_dgb_info
{
    char *cmd;
    char *description;
    uint32_t flag;
};

static struct ppa_dgb_info dbg_enable_mask_str[] = {
    {"err",      "error print",                     DBG_ENABLE_MASK_ERR },
    {"dbg",       "debug print",                    DBG_ENABLE_MASK_DEBUG_PRINT},
    {"dbg2",      "dbg2",                           DBG_ENABLE_MASK_DEBUG2_PRINT | DBG_ENABLE_MASK_DEBUG_PRINT},
    {"assert",    "assert",                         DBG_ENABLE_MASK_ASSERT},
    {"uc",        "dump unicast routing session",   DBG_ENABLE_MASK_DUMP_ROUTING_SESSION},
    {"mc",        "dump multicast session",         DBG_ENABLE_MASK_DUMP_MC_GROUP },
    {"br",        "dump bridging session",          DBG_ENABLE_MASK_DUMP_BRIDGING_SESSION},
    {"init",      "dump init",                      DBG_ENABLE_MASK_DUMP_INIT},
    {"qos",       "dbg qos",                        DBG_ENABLE_MASK_QOS},
    {"pwm",       "dbg pwm",                        DBG_ENABLE_MASK_PWM},
    {"mfe",       "dbg multiple field",             DBG_ENABLE_MASK_MFE},
    {"pri",       "test qos queue via skb tos",     DBG_ENABLE_MASK_PRI_TEST},
    {"mark",      "test qos queue via skb mark",    DBG_ENABLE_MASK_MARK_TEST},
    {"ssn",       "dbg routing/bridge session",     DBG_ENABLE_MASK_SESSION},

    /*the last one */
    {"all",       "enable all debug",                -1}
};

static int proc_read_dbg(struct seq_file *seq, void *v)
{
    int i;

    for ( i = 0; i < NUM_ENTITY(dbg_enable_mask_str) -1; i++ )  //skip -1
    {
        seq_printf(seq, "%-10s(%-40s):        %-5s\n", dbg_enable_mask_str[i].cmd, dbg_enable_mask_str[i].description, (g_ppa_dbg_enable & dbg_enable_mask_str[i].flag)  ? "enabled" : "disabled");
    }

    return 0;
}

static ssize_t proc_write_dbg(struct file *file, const char __user *buf, size_t count, loff_t *data)
{
    int len;
    char str[64];
    char *p;

    int f_enable = 0;
    int i;
    uint32_t value=0;

    len = min(count, (size_t)(sizeof(str) - 1));
    len -= ppa_copy_from_user(str, buf, len);
    while ( len && str[len - 1] <= ' ' )
        len--;
    str[len] = 0;
    for ( p = str; *p && *p <= ' '; p++, len-- );
    if ( !*p )
        return count;

    if ( strincmp(p, "enable", 6) == 0 )
    {
        p += 6 + 1;  //skip enable and one blank
        len -= 6 + 1;  //len maybe negative now if there is no other parameters
        f_enable = 1;
    }
    else if ( strincmp(p, "disable", 7) == 0 )
    {
        p += 7 + 1;  //skip disable and one blank
        len -= 7 + 1; //len maybe negative now if there is no other parameters
        f_enable = -1;
    }
    else if ( strincmp(p, "help", 4) == 0 || *p == '?' )
    {
         printk("echo <enable/disable> [");
         for ( i = 0; i < NUM_ENTITY(dbg_enable_mask_str); i++ ) printk("%s/", dbg_enable_mask_str[i].cmd );
         printk("] [max_print_num]> /proc/ppa/api/dbg\n");
         printk("    Note: Default max_print_num is no limit\n");
         ppa_debug(DBG_ENABLE_MASK_DEBUG_PRINT,"    Current max_print_num=%d\n", max_print_num );
    }

    if ( f_enable )
    {
        if ( (len <= 0) || ( p[0] >= '0' && p[1] <= '9') )
        {
            if ( f_enable > 0 )
                g_ppa_dbg_enable |= DBG_ENABLE_MASK_ALL;
            else
                g_ppa_dbg_enable &= ~DBG_ENABLE_MASK_ALL;
        }
        else
        {
            do
            {
                for ( i = 0; i < NUM_ENTITY(dbg_enable_mask_str); i++ )
                    if ( strincmp(p, dbg_enable_mask_str[i].cmd, strlen(dbg_enable_mask_str[i].cmd) ) == 0 )
                    {
                        if ( f_enable > 0 )
                            g_ppa_dbg_enable |= dbg_enable_mask_str[i].flag;
                        else
                            g_ppa_dbg_enable &= ~dbg_enable_mask_str[i].flag;
                        p += strlen(dbg_enable_mask_str[i].cmd) + 1; //skip one blank
                        len -= strlen(dbg_enable_mask_str[i].cmd) + 1; //skip one blank. len maybe negative now if there is no other parameters
						
                        break;
                    }
            } while ( i < NUM_ENTITY(dbg_enable_mask_str) );
        }
		
		if( len > 0 )
		{
			value = get_number(&p, &len, 0);
	        if( value ) 
	        {
	            max_print_num=value;	            
	        }
            ppa_debug(DBG_ENABLE_MASK_DEBUG_PRINT,"max_print_num=%d\n", max_print_num );
       }	
		
    }

    return count;
}

static int proc_read_hook(struct seq_file *seq, void *v)
{
    if ( !ppa_is_init() )
        seq_printf(seq, "PPA: not init\n");
    else
    {
        seq_printf(seq, "PPA routing\n");
        seq_printf(seq, "  ppa_session_add            - %s\n", ppa_hook_session_add_fn ?       "hooked" : "not hooked");
        seq_printf(seq, "  ppa_session_delete         - %s\n", ppa_hook_session_del_fn ?       "hooked" : "not hooked");
#if defined(CONFIG_LTQ_PPA_HANDLE_CONNTRACK_SESSIONS)
        seq_printf(seq, "  ppa_session_prio           - %s\n", ppa_hook_session_prio_fn ?       "hooked" : "not hooked");
#endif
        seq_printf(seq, "  ppa_inactivity_status      - %s\n", ppa_hook_inactivity_status_fn ? "hooked" : "not hooked");
        seq_printf(seq, "  ppa_set_session_inactivity - %s\n", ppa_hook_set_inactivity_fn ?    "hooked" : "not hooked");
        seq_printf(seq, "PPA bridging\n");
        seq_printf(seq, "  ppa_bridge_entry_add               - %s\n", ppa_hook_bridge_entry_add_fn ?               "hooked" : "not hooked");
        seq_printf(seq, "  ppa_bridge_entry_delete            - %s\n", ppa_hook_bridge_entry_delete_fn ?            "hooked" : "not hooked");
        seq_printf(seq, "  ppa_bridge_entry_hit_time          - %s\n", ppa_hook_bridge_entry_hit_time_fn ?          "hooked" : "not hooked");
        seq_printf(seq, "  ppa_session_bradd                  - %s\n", ppa_hook_session_bradd_fn ?          "hooked" : "not hooked");
    }

    return 0;
}

static int proc_read_filter(struct seq_file *seq, void *v)
{
	if (!ppa_is_init()) {
		seq_printf(seq, "PPA: not init\n");
	} else {
		seq_printf(seq, "------------------------------------------------\n");
		seq_printf(seq, "  PPA Filtered Packets (Not Accelerated) Stats\n");
		seq_printf(seq, "------------------------------------------------\n\n");
		seq_printf(seq, "ppa_is_pkt_host_output			: %d\n", ppa_filter.ppa_is_pkt_host_output);
		seq_printf(seq, "ppa_is_pkt_host_broadcast		: %d\n", ppa_filter.ppa_is_pkt_broadcast);
		seq_printf(seq, "ppa_is_pkt_host_multicast		: %d\n", ppa_filter.ppa_is_pkt_multicast);
		seq_printf(seq, "ppa_is_pkt_host_loopback		: %d\n", ppa_filter.ppa_is_pkt_loopback);
		seq_printf(seq, "ppa_is_pkt_protocol_invalid		: %d\n", ppa_filter.ppa_is_pkt_protocol_invalid);
		seq_printf(seq, "ppa_is_pkt_fragment			: %d\n", ppa_filter.ppa_is_pkt_fragment);
		seq_printf(seq, "ppa_is_pkt_ignore_special_session	: %d\n", ppa_filter.ppa_is_pkt_ignore_special_session);
		seq_printf(seq, "ppa_is_pkt_not_routing			: %d\n", ppa_filter.ppa_is_pkt_not_routing);
		seq_printf(seq, "ppa_is_total_filtered			: %d\n", ppa_filter.ppa_is_filtered);
		seq_printf(seq, "------------------------------------------------\n\n");
	}
	return 0;
}

static ssize_t proc_write_filter(struct file *file, const char __user *buf, size_t count, loff_t *data)
{
	int len;
	char str[PROC_STR_LEN];
	char *cmd;

	len = min(count, (size_t)(PROC_STR_LEN - 1));

	len -= ppa_copy_from_user(str, buf, len);

	/* skip spaces */
	while (len && str[len - 1] <= ' ')
		len--;

	str[len] = 0;
	for (cmd = str; *cmd && (*cmd) <= ' '; cmd++, len--)
		;

	if (!(*cmd))
		return count;

	if (stricmp(cmd, "reset") == 0) {
		ppa_memset(&ppa_filter, 0, sizeof(ppa_filter));
	} else {
		printk("Usage: echo reset > /proc/ppa/api/filter\n");
		printk("About: This proc entry is to see the filtered packets that\n");
		printk("could not be accelerated\n");
	}
	return count;
}

static int proc_read_queue_per_port(struct seq_file *seq, void *v)
{
	int i;
	if (ppa_port_queue_num_status == 1) {
		if (!ppa_is_init()) {
			seq_printf(seq, "PPA: not init\n");
		} else {
			seq_printf(seq, "------------------------------------------------\n");
			seq_printf(seq, "    PPA No. of Queues per Port with status\n");
			seq_printf(seq, "------------------------------------------------\n");
			seq_printf(seq, "PORT_ID	      NUM_QUEUES	PORT_STATUS\n");
			seq_printf(seq, "------------------------------------------------\n");
			for (i = 0; i < PPA_MAX_PORT_NUM; i++) {
				seq_printf(seq, "%d	   |	  %2d	   |	%s\n", ppa_port_qnum[i].portid, ppa_port_qnum[i].num, ppa_port_qnum[i].status);
			}
			seq_printf(seq, "------------------------------------------------\n");
		}
	} else {
		seq_printf(seq, "This proc entry is disabled. You can enable it by doing\n");
		seq_printf(seq, "echo enable > /proc/ppa/api/queue/per/port\n");
	}

	return 0;
}

static ssize_t proc_write_queue_per_port(struct file *file, const char __user *buf, size_t count, loff_t *data)
{
	int len;
	char str[PROC_STR_LEN];
	char *cmd;

	len = min(count, (size_t)(PROC_STR_LEN - 1));

	len -= ppa_copy_from_user(str, buf, len);

	/* skip spaces */
	while (len && str[len - 1] <= ' ')
		len--;

	str[len] = 0;
	for (cmd = str; *cmd && (*cmd) <= ' '; cmd++, len--)
		;

	if (!(*cmd))
		return count;

	if (stricmp(cmd, "enable") == 0) {
		ppa_port_queue_num_status = 1;
	} else if (stricmp(cmd, "disable") == 0) {
		ppa_port_queue_num_status = 0;
	} else {
		printk("Usage: echo enable/disable > /proc/ppa/api/queue_per_port\n");
		printk("If enabled, this proc entry will help the user to see the number of\n");
		printk("queues associated per ppa port\n");
	}

	return count;
}

#if defined(CONFIG_LTQ_PPA_HANDLE_CONNTRACK_SESSIONS)
	
static int proc_read_sess_mgmt(struct seq_file *seq, void *v)
{
	int session_type, session_prio, engine;
    if ( !ppa_is_init() )
        seq_printf(seq, "PPA: not init\n");
    else
    {
#if defined(CONFIG_LTQ_PPA_HAL_SELECTOR) && CONFIG_LTQ_PPA_HAL_SELECTOR
        seq_printf(seq, "\t\t\t%-20s%-20s","PAE", "MPE");
#else
        seq_printf(seq, "\t\t\t%-20s", "PPE");
#endif
#if defined(CONFIG_LTQ_PPA_API_SW_FASTPATH)
		seq_printf(seq, "%-20s", "SWAC");
#endif
		for(session_type=0; session_type<MAX_SESSION_TYPE; session_type++) {
			
			switch(session_type) {
				case LAN:
					seq_printf(seq, "\n%-20s", "LAN");
					break;
				case WAN:
					seq_printf(seq, "\n%-20s", "WAN");
					break;
			}

			for(session_prio=0; session_prio<MAX_SESSION_PRIORITY; session_prio++) {
			
				switch(session_prio+1) {
					case HIGH:
						seq_printf(seq, "\n%-20s", "HIGH:");
						break;
					case DEFAULT:	
						seq_printf(seq, "\n%-20s", "DEFAULT:");
						break;
					case LOW:
						seq_printf(seq, "\n%-20s", "LOW:");
						break;
				}
				for(engine=0; engine<MAX_DATA_FLOW_ENGINES; engine++)
					seq_printf(seq, "\t%-18d", session_count[session_type][session_prio][engine]);
			}
			seq_printf(seq, "\n");
		}
   }
   return 0;
}
#endif

static ssize_t proc_write_hook(struct file *file, const char __user *buf, size_t count, loff_t *data)
{
    int len;
    char str[64];
    char *p;
    int i;
    PPA_VERSION ppe_fw={0};

    len = min(count, (size_t)(sizeof(str) - 1));
    len -= ppa_copy_from_user(str, buf, len);
    while ( len && str[len - 1] <= ' ' )
        len--;
    str[len] = 0;
    for ( p = str; *p && *p <= ' '; p++, len-- );
    if ( !*p )
        return count;

    if ( stricmp(p, "enable") == 0 )
    {
        PPA_IFINFO lanif_info[] = {
            {"eth0",        0},
            {"eth1",        0},
            {"eth0.5",      0},
            {"br0",         0},
        };
        PPA_IFINFO wanif_info[] = {
            {"eth1",        0},
            {"ppp0",        0},
            {"nas0",        0},
            {"nas1",        0},
        };
        PPA_INIT_INFO ppa_init_info = {
            lan_rx_checks : {
                f_ip_verify         : 0,
                f_tcp_udp_verify    : 0,
                f_tcp_udp_err_drop  : 0,
                f_drop_on_no_hit    : 0,
                f_mc_drop_on_no_hit : 0
            },
            wan_rx_checks : {
                f_ip_verify         : 0,
                f_tcp_udp_verify    : 0,
                f_tcp_udp_err_drop  : 0,
                f_drop_on_no_hit    : 0,
                f_mc_drop_on_no_hit : 0
            },
            num_lanifs              : NUM_ENTITY(lanif_info),
            p_lanifs                : lanif_info,
            num_wanifs              : NUM_ENTITY(wanif_info),
            p_wanifs                : wanif_info,
            max_lan_source_entries  : 64,
            max_wan_source_entries  : 64,
            max_mc_entries          : 32,
            max_bridging_entries    : 128,
            add_requires_min_hits   : 2
        };

        uint32_t f_incorrect_fw = 1;

        ppe_fw.index = 1;
        if( ppa_drv_get_firmware_id(&ppe_fw, 0) != PPA_SUCCESS )
        {
            ppe_fw.index = 0;
            ppa_drv_get_firmware_id(&ppe_fw, 0);
        }

        switch ( ppe_fw.family )
        {
        case FAMILY_DANUBE: //  Danube/Twinpass
        case FAMILY_TWINPASS:
            if ( ppe_fw.itf == ITF_2MII )               //  D4
            {
                ppa_init_info.max_lan_source_entries = 128;
                ppa_init_info.max_wan_source_entries = 128;
                ppa_init_info.max_mc_entries         = 32;
                ppa_init_info.max_bridging_entries   = 256;
                f_incorrect_fw = 0;
                for ( i = 0; i < NUM_ENTITY(lanif_info); i++ )
                    if ( strcmp(lanif_info[i].ifname, "eth1") == 0 )
                        lanif_info[i].ifname = NULL;
            }
            else if ( ppe_fw.itf == ITF_1MII_ATMWAN )   //  A4
            {
                ppa_init_info.max_lan_source_entries = 64;
                ppa_init_info.max_wan_source_entries = 64;
                ppa_init_info.max_mc_entries         = 32;
                ppa_init_info.max_bridging_entries   = 128;
                f_incorrect_fw = 0;
                for ( i = 0; i < NUM_ENTITY(lanif_info); i++ )
                    if ( strcmp(lanif_info[i].ifname, "eth1") == 0 )
                        lanif_info[i].ifname = NULL;
                for ( i = 0; i < NUM_ENTITY(wanif_info); i++ )
                    if ( strcmp(wanif_info[i].ifname, "eth1") == 0 )
                        wanif_info[i].ifname = NULL;
            }
            break;
        case FAMILY_AMAZON_SE: //  Amazon SE
            if ( ppe_fw.itf == ITF_1MII_ATMWAN )        //  A4
            {
                ppa_init_info.max_lan_source_entries = 44;
                ppa_init_info.max_wan_source_entries = 44;
                ppa_init_info.max_mc_entries         = 32;
                ppa_init_info.max_bridging_entries   = 128;
                f_incorrect_fw = 0;
                for ( i = 0; i < NUM_ENTITY(lanif_info); i++ )
                    if ( strcmp(lanif_info[i].ifname, "eth1") == 0 )
                        lanif_info[i].ifname = NULL;
                for ( i = 0; i < NUM_ENTITY(wanif_info); i++ )
                    if ( strcmp(wanif_info[i].ifname, "eth1") == 0 )
                        wanif_info[i].ifname = NULL;
            }
            else if ( ppe_fw.itf == ITF_1MII_PTMWAN )   //  E4
            {
                ppa_init_info.max_lan_source_entries = 0;
                ppa_init_info.max_wan_source_entries = 88;
                ppa_init_info.max_mc_entries         = 32;
                ppa_init_info.max_bridging_entries   = 128;
                f_incorrect_fw = 0;
                for ( i = 0; i < NUM_ENTITY(lanif_info); i++ )
                    if ( strcmp(lanif_info[i].ifname, "eth1") == 0 )
                        lanif_info[i].ifname = NULL;
                for ( i = 0; i < NUM_ENTITY(wanif_info); i++ )
                    if ( strcmp(wanif_info[i].ifname, "eth1") == 0 )
                        wanif_info[i].ifname = "ptm0";
            }
            break;
        case FAMILY_AR9: //  AR9/AR10
        case FAMILY_AR10:
            if ( ppe_fw.itf == ITF_2MII                 //  D5
                || (ppe_fw.itf == 0 && ppe_fw.type == TYPE_D5) )
            {
                ppa_init_info.max_lan_source_entries = 576;
                ppa_init_info.max_wan_source_entries = 576;
                ppa_init_info.max_mc_entries         = 64;
                ppa_init_info.max_bridging_entries   = 0;   //  bridging done by internal switch
                f_incorrect_fw = 0;
                for ( i = 0; i < NUM_ENTITY(lanif_info); i++ )
                    if ( strcmp(lanif_info[i].ifname, "eth1") == 0 )
                        lanif_info[i].ifname = NULL;
            }
            else if ( ppe_fw.itf == ITF_2MII_ATMWAN     //  A5
                || (ppe_fw.itf == 0 && ppe_fw.type == TYPE_A5) )
            {
                ppa_init_info.max_lan_source_entries = 192;
                ppa_init_info.max_wan_source_entries = 192;
                ppa_init_info.max_mc_entries         = 64;
                ppa_init_info.max_bridging_entries   = 512;
                f_incorrect_fw = 0;
                for ( i = 0; i < NUM_ENTITY(wanif_info); i++ )
                    if ( strcmp(wanif_info[i].ifname, "eth1") == 0 )
                        wanif_info[i].ifname = NULL;
            }
            else if ( ppe_fw.itf == ITF_2MII_PTMWAN     //  E5
                && (ppe_fw.itf == 0 && ppe_fw.type == TYPE_E5) )
            {
                ppa_init_info.max_lan_source_entries = 192;
                ppa_init_info.max_wan_source_entries = 192;
                ppa_init_info.max_mc_entries         = 64;
                ppa_init_info.max_bridging_entries   = 512;
                f_incorrect_fw = 0;
                for ( i = 0; i < NUM_ENTITY(wanif_info); i++ )
                    if ( strcmp(wanif_info[i].ifname, "eth1") == 0 )
                        wanif_info[i].ifname = "ptm0";
            }
            break;
        case FAMILY_VR9:
            if ( ppe_fw.itf == ITF_2MII || ppe_fw.itf == ITF_2MII_BONDING   //  D5/E5/BONDING
                || (ppe_fw.itf == 0 && (ppe_fw.type == TYPE_E1 || ppe_fw.type == TYPE_D5 || ppe_fw.type == TYPE_D5v2)) )
            {
                ppa_init_info.max_lan_source_entries = 192;
                ppa_init_info.max_wan_source_entries = 192;
                ppa_init_info.max_mc_entries         = 64;
                ppa_init_info.max_bridging_entries   = 0;   //  bridging done by internal switch;
                f_incorrect_fw = 0;
                for ( i = 0; i < NUM_ENTITY(lanif_info); i++ )
                    if ( strcmp(lanif_info[i].ifname, "eth1") == 0 )
                        lanif_info[i].ifname = NULL;
            }
            else if ( ppe_fw.itf == ITF_2MII_ATMWAN                         //  A5
                || (ppe_fw.itf == 0 && ppe_fw.type == TYPE_A5) )
            {
                ppa_init_info.max_lan_source_entries = 192;
                ppa_init_info.max_wan_source_entries = 192;
                ppa_init_info.max_mc_entries         = 64;
                ppa_init_info.max_bridging_entries   = 0;   //  bridging done by internal switch;
                f_incorrect_fw = 0;
                for ( i = 0; i < NUM_ENTITY(lanif_info); i++ )
                    if ( strcmp(lanif_info[i].ifname, "eth1") == 0 )
                        lanif_info[i].ifname = NULL;
            }
            break;
        }

        if ( !f_incorrect_fw )
        {
            PPA_MAX_ENTRY_INFO entry={0};

            ppa_drv_get_max_entries(&entry, 0);

            ppa_init_info.max_lan_source_entries = entry.max_lan_entries;
            ppa_init_info.max_wan_source_entries = entry.max_wan_entries;
            ppa_init_info.max_mc_entries         = entry.max_mc_entries;
            ppa_init_info.max_bridging_entries   = entry.max_bridging_entries;

            ppa_exit();
            ppa_init(&ppa_init_info, 0);
            ppa_enable(1, 1, 0);
        }
        else
        {
           printk("wrong version:family=%d, and itf=%d\n", ppe_fw.family, ppe_fw.itf );
        }
    }
    else if ( stricmp(p, "disable") == 0 )
    {
        ppa_enable(0, 0, 0);
        ppa_exit();
    }
    else
        printk("echo enable/disable > /proc/ppa/api/hook\n");

    return count;
}


static void *proc_read_phys_port_seq_start(struct seq_file *seq, loff_t *ppos)
{
    struct phys_port_info *ifinfo;

    if ( *ppos != 0 )
        (*ppos)--;

    g_proc_read_phys_port_pos = (uint32_t)*ppos;
    if ( ppa_phys_port_start_iteration(&g_proc_read_phys_port_pos, &ifinfo) == PPA_SUCCESS )
    {
        *ppos = g_proc_read_phys_port_pos;
        return ifinfo;
    }
    else
        return NULL;
}

static void *proc_read_phys_port_seq_next(struct seq_file *seq, void *v, loff_t *ppos)
{
    struct phys_port_info *ifinfo = (struct phys_port_info *)v;

    g_proc_read_phys_port_pos = (uint32_t)*ppos;
    if ( ppa_phys_port_iterate_next(&g_proc_read_phys_port_pos, &ifinfo) == PPA_SUCCESS )
    {
        *ppos = g_proc_read_phys_port_pos;
        return ifinfo;
    }
    else
        return NULL;
}

static void proc_read_phys_port_seq_stop(struct seq_file *seq, void *v)
{
    ppa_phys_port_stop_iteration();
}

static int proc_read_phys_port_seq_show(struct seq_file *seq, void *v)
{
    static const char *str_mode[] = {
        "CPU",
        "LAN",
        "WAN",
        "MIX (LAN/WAN)"
    };
    static const char *str_type[] = {
        "CPU",
        "ATM",
        "ETH",
        "EXT"
    };
    static const char *str_vlan[] = {
        "no VLAN",
        "inner VLAN",
        "outer VLAN",
        "N/A"
    };

    struct phys_port_info *ifinfo = (struct phys_port_info *)v;
    static int extra_itf = 0;

    if ( g_proc_read_phys_port_pos == 1 )
    {
        seq_printf(seq, "Physical Port List\n");
        if ( PPA_IS_PORT_CPU0_AVAILABLE() )
        {
            seq_printf(seq, "  no. %u\n", ++extra_itf);
            seq_printf(seq, "    mode             = %s\n", str_mode[0]);
            seq_printf(seq, "    type             = %s\n", str_type[0]);
            seq_printf(seq, "    vlan             = %s\n", str_vlan[0]);
            seq_printf(seq, "    port             = %d\n", PPA_PORT_CPU0);
        }
        if ( PPA_IS_PORT_ATM_AVAILABLE() )
        {
            seq_printf(seq, "  no. %u\n", ++extra_itf);
            seq_printf(seq, "    mode             = %s\n", str_mode[2]);
            seq_printf(seq, "    type             = %s\n", str_type[1]);
            seq_printf(seq, "    vlan             = %s\n", str_vlan[PPA_PORT_ATM_VLAN_FLAGS]);
            seq_printf(seq, "    port             = %d\n", PPA_PORT_ATM);
        }
    }

    seq_printf(seq,     "  no. %u\n", g_proc_read_phys_port_pos + extra_itf);
    seq_printf(seq,     "    next             = %08X\n", (uint32_t)ifinfo->next);
    seq_printf(seq,     "    mode             = %s\n", str_mode[ifinfo->mode]);
    seq_printf(seq,     "    type             = %s\n", str_type[ifinfo->type]);
    seq_printf(seq,     "    vlan             = %s\n", str_vlan[ifinfo->vlan]);
    seq_printf(seq,     "    port             = %d\n", ifinfo->port);
    seq_printf(seq,     "    ifname           = %s\n", ifinfo->ifname);

    return 0;
}

static int proc_read_phys_port_seq_open(struct inode *inode, struct file *file)
{
    return seq_open(file, &g_proc_read_phys_port_seq_ops);
}

static void *proc_read_netif_seq_start(struct seq_file *seq, loff_t *ppos)
{
    struct netif_info *ifinfo;

    g_proc_read_netif_pos = (uint32_t)*ppos;
    if ( ppa_netif_start_iteration(&g_proc_read_netif_pos, &ifinfo) == PPA_SUCCESS )
    {
        return ifinfo;
    }
    else
        return NULL;
}

static void *proc_read_netif_seq_next(struct seq_file *seq, void *v, loff_t *ppos)
{
    struct netif_info *ifinfo = (struct netif_info *)v;

    ++*ppos;                                //  workaround for wrong display
    g_proc_read_netif_pos = (uint32_t)*ppos;
    if ( ppa_netif_iterate_next(&g_proc_read_netif_pos, &ifinfo) == PPA_SUCCESS )
    {
        return ifinfo;
    }
    else
        return NULL;
}

static void proc_read_netif_seq_stop(struct seq_file *seq, void *v)
{
    ppa_netif_stop_iteration();
}

static int proc_read_netif_seq_show(struct seq_file *seq, void *v)
{
    static const char *str_flag[] = {
        "NETIF_VLAN",               //  0x00000001
        "NETIF_BRIDGE",
        "INVALID",
        "INVALID",
        "NETIF_PHY_ETH",            //  0x00000010
        "NETIF_PHY_ATM",
        "NETIF_PHY_TUNNEL",
        "INVALID",
        "NETIF_BR2684",             //  0x00000100
        "NETIF_EOA",
        "NETIF_IPOA",
        "NETIF_PPPOATM",
        "NETIF_PPPOE",              //  0x00001000
        "NETIF_VLAN_INNER",
        "NETIF_VLAN_OUTER",
        "NETIF_VLAN_CANT_SUPPORT",
        "NETIF_LAN_IF",             //  0x00010000
        "NETIF_WAN_IF",
        "NETIF_PHY_IF_GOT",
        "NETIF_PHYS_PORT_GOT",
        "NETIF_MAC_AVAILABLE",      //  0x00100000
        "NETIF_MAC_ENTRY_CREATED",
        "NETIF_PPPOL2TP",
        "NETIF_DIRECTPATH",
        "NETIF_GRE_TUNNEL",         //  0x01000000
        "NETIF_DIRECTCONNECT",
        "NETIF_L2NAT",
#if defined(CONFIG_PPTP_MODULE) || defined(CONFIG_PPTP)
        "NETIF_PPTP_TUNNEL",
#endif
    };

    struct netif_info *ifinfo = (struct netif_info *)v;
    int flag;
    unsigned long bit;
    int i;

    if ( g_proc_read_netif_pos == 1 )
        seq_printf(seq, "NetIF List\n");

    seq_printf(seq,     "  no. %u\n", g_proc_read_netif_pos);
    seq_printf(seq,     "    next             = %08X\n", (uint32_t)ifinfo->next);
    seq_printf(seq,	"    status           = %s\n",
	       (ifinfo->enable ? "enabled" : "disabled"));
    seq_printf(seq,     "    count            = %d\n", ppa_atomic_read(&ifinfo->count));
    seq_printf(seq,     "    name             = %s\n", ifinfo->name);
    if ( (ifinfo->flags & NETIF_PHY_IF_GOT) )
        seq_printf(seq, "    phys_netif_name  = %s\n", ifinfo->phys_netif_name);
    else
        seq_printf(seq, "    phys_netif_name  = N/A\n");    
    seq_printf(seq, "    lower_ifname     = %s\n", ifinfo->manual_lower_ifname);        
    if ( ifinfo->netif != NULL )
        seq_printf(seq, "    netif            = %08X\n", (uint32_t)ifinfo->netif);
    else
        seq_printf(seq, "    netif            = N/A\n");
    if ( (ifinfo->flags & NETIF_MAC_AVAILABLE) )
        seq_printf(seq, "    mac              = %02x:%02x:%02x:%02x:%02x:%02x\n", (u32)ifinfo->mac[0], (u32)ifinfo->mac[1], (u32)ifinfo->mac[2], (u32)ifinfo->mac[3], (u32)ifinfo->mac[4], (u32)ifinfo->mac[5]);
    else
        seq_printf(seq, "    mac              = N/A\n");
    seq_printf(seq,     "    flags            = ");
    flag = 0;
    for ( bit = 1, i = 0; i < sizeof(str_flag) / sizeof(*str_flag); bit <<= 1, i++ )
        if ( (ifinfo->flags & bit) )
        {
            if ( flag++ )
                seq_printf(seq, " | ");
            seq_printf(seq, str_flag[i]);
        }
    if ( flag )
        seq_printf(seq, "\n");
    else
        seq_printf(seq, "NULL\n");
    seq_printf(seq,     "    vlan_layer       = %u\n", ifinfo->vlan_layer);
    if ( (ifinfo->flags & NETIF_VLAN_INNER) )
        seq_printf(seq, "    inner_vid        = 0x%x\n", ifinfo->inner_vid);
    if ( (ifinfo->flags & NETIF_VLAN_OUTER) )
        seq_printf(seq, "    outer_vid        = 0x%x\n", ifinfo->outer_vid);
    if ( (ifinfo->flags & NETIF_PPPOE) )
        seq_printf(seq, "    pppoe_session_id = %u\n", ifinfo->pppoe_session_id);
    if ( (ifinfo->flags & NETIF_PHY_ATM) )
        seq_printf(seq, "    dslwan_qid       = %u (RX), %u (TX)\n", (ifinfo->dslwan_qid >> 8) & 0xFF, ifinfo->dslwan_qid & 0xFF);
    if ( (ifinfo->flags & NETIF_PHYS_PORT_GOT) )
        seq_printf(seq, "    phys_port        = %u\n", ifinfo->phys_port);
    else
        seq_printf(seq, "    phys_port        = N/A\n");
    if ( ifinfo->mac_entry == ~0 )
        seq_printf(seq, "    mac_entry        = N/A\n");
    else
        seq_printf(seq, "    mac_entry        = %u\n", ifinfo->mac_entry);

    if( ifinfo->out_vlan_netif )
        seq_printf(seq, "    out_vlan_if      = %s\n", ppa_get_netif_name(ifinfo->out_vlan_netif) );

    if( ifinfo->in_vlan_netif )
        seq_printf(seq, "    in_vlan_if       = %s\n", ppa_get_netif_name(ifinfo->in_vlan_netif) );

#if defined(CONFIG_LTQ_PPA_IF_MIB) && CONFIG_LTQ_PPA_IF_MIB
    for(i=0; i<ifinfo->sub_if_index; i++)
    {
        if( i==0 ) 
            seq_printf(seq, "    sub-interfaces = ");
        seq_printf(seq, "%s ", ifinfo->sub_if_name[i]);        
        if( i == ifinfo->sub_if_index -1 )
        {
            seq_printf(seq, " with rx/tx:%llu/%llu(%llu:%llu/%llu:%llu)\n",ifinfo->hw_accel_stats.rx_bytes - ifinfo->prev_clear_acc_rx,ifinfo->hw_accel_stats.tx_bytes - ifinfo->prev_clear_acc_tx,
			              ifinfo->hw_accel_stats.rx_bytes, ifinfo->prev_clear_acc_rx, ifinfo->hw_accel_stats.tx_bytes, ifinfo->prev_clear_acc_tx);
        }
    }
#endif


    return 0;
}

static int proc_read_netif_seq_open(struct inode *inode, struct file *file)
{
    return seq_open(file, &g_proc_read_netif_seq_ops);
}

static ssize_t proc_file_write_netif(struct file *file, const char __user *buf, size_t count, loff_t *ppos)
{
    int len;
    char str[64];
    char *p;

    PPA_IFINFO ifinfo;
    int f_is_lanif = -1;

    len = min(count, (size_t)sizeof(str) - 1);
    len -= ppa_copy_from_user(str, buf, len);
    while ( len && str[len - 1] <= ' ' )
        len--;
    str[len] = 0;
    for ( p = str; *p && *p <= ' '; p++, len-- );
    if ( !*p )
        return count;

    if ( strincmp(p, "add ", 4) == 0 )
    {
        p += 4;

        while ( *p && *p <= ' ' )
            p++;

        if ( strincmp(p, "lan ", 4) == 0 )
            f_is_lanif = 1;
        else if ( strincmp(p, "wan ",4) == 0 )
            f_is_lanif = 0;

        if ( f_is_lanif >= 0 )
        {
            p += 4;

            while ( *p && *p <= ' ' )
                p++;

            ifinfo.ifname = p;
            ifinfo.if_flags = f_is_lanif ? PPA_F_LAN_IF : 0;
            ppa_add_if(&ifinfo, 0);
        }
    }
    else if ( strincmp(p, "del ", 4) == 0 )
    {
        p += 4;

        while ( *p && *p <= ' ' )
            p++;

        if ( strincmp(p, "lan ", 4) == 0 )
            f_is_lanif = 1;
        else if ( strincmp(p, "wan ",4) == 0 )
            f_is_lanif = 0;

        if ( f_is_lanif >= 0 )
        {
            p += 4;

            while ( *p && *p <= ' ' )
                p++;

            ifinfo.ifname = p;
            ifinfo.if_flags = f_is_lanif ? PPA_F_LAN_IF : 0;
            ppa_del_if(&ifinfo, 0);
        }
        else
        {
            ifinfo.ifname = p;
            ifinfo.if_flags = 0;
            ppa_del_if(&ifinfo, 0);
            ifinfo.if_flags = PPA_F_LAN_IF;
            ppa_del_if(&ifinfo, 0);
        }
    }
    else if ( strincmp(p, "update ", 7) == 0 )
    {
        p += 7;

        while ( *p && *p <= ' ' )
            p++;

        if ( *p )
        {
            int32_t ret = ppa_netif_update(NULL, p);

            if ( ret == PPA_SUCCESS )
                printk("Successfully\n");
            else
                pr_err("Failed: %d\n", ret);
        }
    }

    return count;
}

static void *proc_read_session_seq_start(struct seq_file *seq, loff_t *ppos)
{
    struct session_list_item *p_rt_item;
    struct mc_group_list_item *p_mc_item;
    struct bridging_session_list_item *p_br_item;
    uint32_t type;

    if ( *ppos == 0 )
    {
        g_proc_read_session_pos = 0;
        g_proc_read_session_pos_prev = ~0;
    }
    else
        g_proc_read_session_pos = g_proc_read_session_pos_prev;
    type = g_proc_read_session_pos & 0x30000000;
    g_proc_read_session_pos &= 0x0FFFFFFF;
    switch ( type )
    {
    case 0x00000000:
        if ( ppa_session_start_iteration(&g_proc_read_session_pos, &p_rt_item) == PPA_SUCCESS )
        {
            *ppos = g_proc_read_session_pos;
            return p_rt_item;
        }
        else
        {
            ppa_session_stop_iteration();
            g_proc_read_session_pos = 0;
        }
    case 0x10000000:
        if ( ppa_mc_group_start_iteration(&g_proc_read_session_pos, &p_mc_item) == PPA_SUCCESS )
        {
            g_proc_read_session_pos |= 0x10000000;
            *ppos = g_proc_read_session_pos;
            return p_mc_item;
        }
        else
        {
            ppa_mc_group_stop_iteration();
            g_proc_read_session_pos = 0;
        }
    case 0x20000000:
        if ( ppa_bridging_session_start_iteration(&g_proc_read_session_pos, &p_br_item) == PPA_SUCCESS )
        {
            g_proc_read_session_pos |= 0x20000000;
            *ppos = g_proc_read_session_pos;
            return p_br_item;
        }
        else
        {
            g_proc_read_session_pos |= 0x20000000;
            *ppos = g_proc_read_session_pos;
        }
    }

    return NULL;
}

static void *proc_read_session_seq_next(struct seq_file *seq, void *v, loff_t *ppos)
{
    uint32_t type;

    g_proc_read_session_pos_prev = (uint32_t)*ppos;
    g_proc_read_session_pos = (uint32_t)*ppos;
    type = g_proc_read_session_pos & 0x30000000;
    g_proc_read_session_pos &= 0x0FFFFFFF;
    switch ( type )
    {
    case 0x00000000:
        if ( ppa_session_iterate_next(&g_proc_read_session_pos, (struct session_list_item **)&v) == PPA_SUCCESS )
        {
            *ppos = g_proc_read_session_pos;
            return v;
        }
        else
        {
            ppa_session_stop_iteration();
            g_proc_read_session_pos = 0;
            if ( ppa_mc_group_start_iteration(&g_proc_read_session_pos, (struct mc_group_list_item **)&v) == PPA_SUCCESS )
            {
                g_proc_read_session_pos |= 0x10000000;
                *ppos = g_proc_read_session_pos;
                return v;
            }
            ppa_mc_group_stop_iteration();
            g_proc_read_session_pos = 0;
            if ( ppa_bridging_session_start_iteration(&g_proc_read_session_pos, (struct bridging_session_list_item **)&v) == PPA_SUCCESS )
            {
                g_proc_read_session_pos |= 0x20000000;
                *ppos = g_proc_read_session_pos;
                return v;
            }
            g_proc_read_session_pos |= 0x20000000;
            *ppos = g_proc_read_session_pos;
            return NULL;
        }
        break;
    case 0x10000000:
        if ( ppa_mc_group_iterate_next(&g_proc_read_session_pos, (struct mc_group_list_item **)&v) == PPA_SUCCESS )
        {
            g_proc_read_session_pos |= 0x10000000;
            *ppos = g_proc_read_session_pos;
            return v;
        }
        else
        {
            ppa_mc_group_stop_iteration();
            g_proc_read_session_pos = 0;
            if ( ppa_bridging_session_start_iteration(&g_proc_read_session_pos, (struct bridging_session_list_item **)&v) == PPA_SUCCESS )
            {
                g_proc_read_session_pos |= 0x20000000;
                *ppos = g_proc_read_session_pos;
                return v;
            }
            g_proc_read_session_pos |= 0x20000000;
            *ppos = g_proc_read_session_pos;
            return NULL;
        }
        break;
    case 0x20000000:
        if ( ppa_bridging_session_iterate_next(&g_proc_read_session_pos, (struct bridging_session_list_item **)&v) == PPA_SUCCESS )
        {
            g_proc_read_session_pos |= 0x20000000;
            *ppos = g_proc_read_session_pos;
            return v;
        }
        else
        {
            g_proc_read_session_pos |= 0x20000000;
            *ppos = g_proc_read_session_pos;
            return NULL;
        }
        break;
    default:
        return NULL;
    }
}

static void proc_read_session_seq_stop(struct seq_file *seq, void *v)
{
    switch ( g_proc_read_session_pos & 0x30000000 )
    {
    case 0x00000000: ppa_session_stop_iteration(); break;
    case 0x10000000: ppa_mc_group_stop_iteration(); break;                     
    case 0x20000000: ppa_bridging_session_stop_iteration();
    }
}

static void print_session_ifid(struct seq_file *seq, char *str, uint32_t ifid)
{
    const char *pstr =  ifid < NUM_ENTITY(g_str_dest) ? g_str_dest[ifid] : "INVALID";

    seq_printf(seq, str);
    seq_printf(seq, "%u - %s\n", ifid, pstr);
}

static void printk_session_ifid(char *str, uint32_t ifid)
{
	const char *pstr =  ifid < NUM_ENTITY(g_str_dest) ? g_str_dest[ifid] : "INVALID";

	printk(str);
	printk("%u - %s\n", ifid, pstr);
}

static void print_session_flags(struct seq_file *seq, char *str, uint32_t flags)
{
    static const char *str_flag[] = {
        "IS_REPLY",                 //  0x00000001
        "Reserved",
        "SESSION_IS_TCP",
        "STAMPING",
        "ADDED_IN_HW",              //  0x00000010
        "NOT_ACCEL_FOR_MGM",
        "STATIC",
        "DROP",
        "VALID_NAT_IP",             //  0x00000100
        "VALID_NAT_PORT",
        "VALID_NAT_SNAT",
        "NOT_ACCELABLE",
        "VALID_VLAN_INS",           //  0x00001000
        "VALID_VLAN_RM",
        "SESSION_VALID_OUT_VLAN_INS",
        "SESSION_VALID_OUT_VLAN_RM",
        "VALID_PPPOE",              //  0x00010000
        "VALID_NEW_SRC_MAC",
        "VALID_MTU",
        "VALID_NEW_DSCP",
        "SESSION_VALID_DSLWAN_QID", //  0x00100000
        "SESSION_TX_ITF_IPOA",
        "SESSION_TX_ITF_PPPOA",
        "Reserved",
        "SRC_MAC_DROP_EN",          //  0x01000000
        "SESSION_TUNNEL_6RD",
        "SESSION_TUNNEL_DSLITE",
        "Reserved",
        "LAN_ENTRY",                //  0x10000000
        "WAN_ENTRY",
        "IPV6",
        "ADDED_IN_SW",
    };

    int flag;
    unsigned long bit;
    int i;

    seq_printf(seq, str);

    flag = 0;
    for ( bit = 1, i = 0; bit; bit <<= 1, i++ )
        if ( (flags & bit) )
        {
            if ( flag++ )
                seq_printf(seq, "| ");
            seq_printf(seq, str_flag[i]);
            //seq_printf(seq, " ");
        }
    if ( flag )
        seq_printf(seq, "\n");
    else
        seq_printf(seq, "NULL\n");
}

static void printk_session_flags(char *str, uint32_t flags)
{
	static const char *str_flag[] = {
		"IS_REPLY",                 //  0x00000001
		"Reserved",
		"SESSION_IS_TCP",
		"STAMPING",
		"ADDED_IN_HW",              //  0x00000010
		"NOT_ACCEL_FOR_MGM",
		"STATIC",
		"DROP",
		"VALID_NAT_IP",             //  0x00000100
		"VALID_NAT_PORT",
		"VALID_NAT_SNAT",
		"NOT_ACCELABLE",
		"VALID_VLAN_INS",           //  0x00001000
		"VALID_VLAN_RM",
		"SESSION_VALID_OUT_VLAN_INS",
		"SESSION_VALID_OUT_VLAN_RM",
		"VALID_PPPOE",              //  0x00010000
		"VALID_NEW_SRC_MAC",
		"VALID_MTU",
		"VALID_NEW_DSCP",
		"SESSION_VALID_DSLWAN_QID", //  0x00100000
		"SESSION_TX_ITF_IPOA",
		"SESSION_TX_ITF_PPPOA",
		"Reserved",
		"SRC_MAC_DROP_EN",          //  0x01000000
		"SESSION_TUNNEL_6RD",
		"SESSION_TUNNEL_DSLITE",
		"Reserved",
		"LAN_ENTRY",                //  0x10000000
		"WAN_ENTRY",
		"IPV6",
		"ADDED_IN_SW",
	};

	int flag;
	unsigned long bit;
	int i;

	printk(str);

	flag = 0;
	for (bit = 1, i = 0; bit; bit <<= 1, i++)
		if ((flags & bit))
		{
			if (flag++)
				printk("| ");
			printk(str_flag[i]);
		}
	if (flag)
		printk("\n");
	else
		printk("NULL\n");
}

#if defined(ENABLE_SESSION_DEBUG_FLAGS) && ENABLE_SESSION_DEBUG_FLAGS
static void print_session_debug_flags(struct seq_file *seq, char *str, uint32_t flags)
{
 /* Below macro is defined in ppa_api_session.h" 
  #define SESSION_DBG_NOT_REACH_MIN_HITS        0x00000001
  #define SESSION_DBG_ALG                       0x00000002
  #define SESSION_DBG_ZERO_DST_MAC              0x00000004
  #define SESSION_DBG_TCP_NOT_ESTABLISHED       0x00000008
  #define SESSION_DBG_RX_IF_NOT_IN_IF_LIST      0x00000010
  #define SESSION_DBG_TX_IF_NOT_IN_IF_LIST      0x00000020
  #define SESSION_DBG_RX_IF_UPDATE_FAIL         0x00000040
  #define SESSION_DBG_TX_IF_UPDATE_FAIL         0x00000080
  #define SESSION_DBG_SRC_BRG_IF_NOT_IN_BRG_TBL 0x00000100
  #define SESSION_DBG_SRC_IF_NOT_IN_IF_LIST     0x00000200
  #define SESSION_DBG_DST_BRG_IF_NOT_IN_BRG_TBL 0x00000400
  #define SESSION_DBG_DST_IF_NOT_IN_IF_LIST     0x00000800
  #define SESSION_DBG_ADD_PPPOE_ENTRY_FAIL      0x00001000
  #define SESSION_DBG_ADD_MTU_ENTRY_FAIL        0x00002000
  #define SESSION_DBG_ADD_MAC_ENTRY_FAIL        0x00004000
  #define SESSION_DBG_ADD_OUT_VLAN_ENTRY_FAIL   0x00008000
  #define SESSION_DBG_RX_PPPOE                  0x00010000
  #define SESSION_DBG_TX_PPPOE                  0x00020000
  #define SESSION_DBG_TX_BR2684_EOA             0x00040000
  #define SESSION_DBG_TX_BR2684_IPOA            0x00080000
  #define SESSION_DBG_TX_PPPOA                  0x00100000
  #define SESSION_DBG_GET_DST_MAC_FAIL          0x00200000
  #define SESSION_DBG_RX_INNER_VLAN             0x00400000
  #define SESSION_DBG_RX_OUTER_VLAN             0x00800000
  #define SESSION_DBG_TX_INNER_VLAN             0x01000000
  #define SESSION_DBG_TX_OUTER_VLAN             0x02000000
  #define SESSION_DBG_RX_VLAN_CANT_SUPPORT      0x04000000
  #define SESSION_DBG_TX_VLAN_CANT_SUPPORT      0x08000000
  #define SESSION_DBG_UPDATE_HASH_FAIL          0x10000000
  #define SESSION_DBG_PPE_EDIT_LIMIT  0x20000000
*/
    static const char *str_flag[] = {
        "NOT_REACH_MIN_HITS",           //  0x00000001
        "ALG",
        "ZERO_DST_MAC",
        "TCP_NOT_ESTABLISHED",
        "RX_IF_NOT_IN_IF_LIST",         //  0x00000010
        "TX_IF_NOT_IN_IF_LIST",
        "RX_IF_UPDATE_FAIL",
        "TX_IF_UPDATE_FAIL",
        "SRC_BRG_IF_NOT_IN_BRG_TBL",    //  0x00000100
        "SRC_IF_NOT_IN_IF_LIST",
        "DST_BRG_IF_NOT_IN_BRG_TBL",
        "DST_IF_NOT_IN_IF_LIST",
        "ADD_PPPOE_ENTRY_FAIL",         //  0x00001000
        "ADD_MTU_ENTRY_FAIL",
        "ADD_MAC_ENTRY_FAIL",
        "ADD_OUT_VLAN_ENTRY_FAIL",
        "RX_PPPOE",                     //  0x00010000
        "TX_PPPOE",
        "TX_BR2684_EOA",
        "TX_BR2684_IPOA",
        "TX_PPPOA",                     //  0x00100000
        "GET_DST_MAC_FAIL",
        "RX_INNER_VLAN",
        "RX_OUTER_VLAN",
        "TX_INNER_VLAN",                //  0x01000000
        "TX_OUTER_VLAN",
        "RX_VLAN_CANT_SUPPORT",
        "TX_VLAN_CANT_SUPPORT",
        "UPDATE_HASH_FAIL",             //  0x10000000
        "PPE Limitation",
        "INVALID",
        "INVALID",
    };

    int flag;
    unsigned long bit;
    int i;

    seq_printf(seq, str);

    flag = 0;
    for ( bit = 1, i = 0; bit; bit <<= 1, i++ )
        if ( (flags & bit) )
        {
            if ( flag++ )
                seq_printf(seq, "| ");
            seq_printf(seq, str_flag[i]);
            seq_printf(seq, " ");
        }
    if ( flag )
        seq_printf(seq, "\n");
    else
        seq_printf(seq, "NULL\n");
}

static void printk_session_debug_flags(char *str, uint32_t flags)
{
	static const char *str_flag[] = {
		"NOT_REACH_MIN_HITS",           //  0x00000001
		"ALG",
		"ZERO_DST_MAC",
		"TCP_NOT_ESTABLISHED",
		"RX_IF_NOT_IN_IF_LIST",         //  0x00000010
		"TX_IF_NOT_IN_IF_LIST",
		"RX_IF_UPDATE_FAIL",
		"TX_IF_UPDATE_FAIL",
		"SRC_BRG_IF_NOT_IN_BRG_TBL",    //  0x00000100
		"SRC_IF_NOT_IN_IF_LIST",
		"DST_BRG_IF_NOT_IN_BRG_TBL",
		"DST_IF_NOT_IN_IF_LIST",
		"ADD_PPPOE_ENTRY_FAIL",         //  0x00001000
		"ADD_MTU_ENTRY_FAIL",
		"ADD_MAC_ENTRY_FAIL",
		"ADD_OUT_VLAN_ENTRY_FAIL",
		"RX_PPPOE",                     //  0x00010000
		"TX_PPPOE",
		"TX_BR2684_EOA",
		"TX_BR2684_IPOA",
		"TX_PPPOA",                     //  0x00100000
		"GET_DST_MAC_FAIL",
		"RX_INNER_VLAN",
		"RX_OUTER_VLAN",
		"TX_INNER_VLAN",                //  0x01000000
		"TX_OUTER_VLAN",
		"RX_VLAN_CANT_SUPPORT",
		"TX_VLAN_CANT_SUPPORT",
		"UPDATE_HASH_FAIL",             //  0x10000000
		"PPE Limitation",
		"INVALID",
		"INVALID",
	};

	int flag;
	unsigned long bit;
	int i;

	printk(str);

	flag = 0;
	for (bit = 1, i = 0; bit; bit <<= 1, i++)
		if ((flags & bit))
		{
			if (flag++)
				printk("| ");
			printk(str_flag[i]);
			printk(" ");
		}
	if (flag)
		printk("\n");
	else
		printk("NULL\n");

}
#endif

static INLINE int proc_read_routing_session_seq_show(struct seq_file *seq, void *v)
{
    struct session_list_item *p_item = v;
    uint32_t pos = g_proc_read_session_pos & 0x0FFFFFFF;
    int8_t strbuf[64];
#if defined(MIB_MODE_ENABLE) && MIB_MODE_ENABLE
        PPE_MIB_MODE_ENABLE mib_cfg;
#endif

    if ( pos == 1 )
        seq_printf(seq, "Session List (Unicast Routing)\n");

    seq_printf(seq,     "  no. %d\n", pos);
    seq_printf(seq,     "    next             = 0x%08X\n", (uint32_t)&p_item->hlist);
    seq_printf(seq,     "    session          = 0x%08X\n", (uint32_t)p_item->session);
    seq_printf(seq,     "    ip_proto         = %u\n",   (uint32_t)p_item->ip_proto);
#ifdef CONFIG_PPA_PP_LEARNING
    seq_printf(seq,     "    eth_type         = %u\n",   (uint32_t)p_item->protocol);
#endif
    seq_printf(seq,     "    ip_tos           = %u\n",   (uint32_t)p_item->ip_tos);
    seq_printf(seq,     "    src_ip           = %s\n",   ppa_get_pkt_ip_string(p_item->src_ip, p_item->flags & SESSION_IS_IPV6, strbuf));
    seq_printf(seq,     "    src_port         = %u\n",   (uint32_t)p_item->src_port);
    seq_printf(seq,     "    src_mac[6]       = %s\n",	 ppa_get_pkt_mac_string(p_item->src_mac, strbuf));
    seq_printf(seq,     "    dst_ip           = %s\n",   ppa_get_pkt_ip_string(p_item->dst_ip, p_item->flags & SESSION_IS_IPV6, strbuf));
    seq_printf(seq,     "    dst_port         = %u\n",   (uint32_t)p_item->dst_port);
    seq_printf(seq,     "    dst_mac[6]       = %s\n",   ppa_get_pkt_mac_string(p_item->dst_mac, strbuf));
    seq_printf(seq,     "    nat_ip           = %s\n",   ppa_get_pkt_ip_string(p_item->nat_ip, p_item->flags & SESSION_IS_IPV6, strbuf));
    seq_printf(seq,     "    nat_port         = %u\n",   (uint32_t)p_item->nat_port);
    seq_printf(seq,     "    nat_src_mac[6]   = %s\n",   ppa_get_pkt_mac_string(p_item->nat_src_mac, strbuf));
    seq_printf(seq,     "    num_adds         = %u( minimum required hit is %d)\n",   (uint32_t)p_item->num_adds, g_ppa_min_hits);
#ifdef CONFIG_MIPS
    if ( (uint32_t)p_item->rx_if < KSEG0 || (uint32_t)p_item->rx_if >= KSEG1 )
        seq_printf(seq,     "    rx_if            = %s (0x%08X)\n", "N/A", (uint32_t)p_item->rx_if);
    else
#endif
    seq_printf(seq,     "    rx_if            = %s (0x%08X)\n", p_item->rx_if == NULL ? "N/A" : ppa_get_netif_name(p_item->rx_if), (uint32_t)p_item->rx_if);
#ifdef CONFIG_MIPS
    if ( (uint32_t)p_item->tx_if < KSEG0 || (uint32_t)p_item->tx_if >= KSEG1 )
        seq_printf(seq,     "    tx_if            = %s (0x%08X)\n", "N/A(may no ip output hook or not meet hit count)", (uint32_t)p_item->tx_if);
    else
#endif
    seq_printf(seq,     "    tx_if            = %s (0x%08X)\n", p_item->tx_if == NULL ? "N/A" : ppa_get_netif_name(p_item->tx_if), (uint32_t)p_item->tx_if);
    seq_printf(seq,     "    timeout          = %u\n",   p_item->timeout);
    seq_printf(seq,     "    last_hit_time    = %u (now %u)\n",   p_item->last_hit_time, ppa_get_time_in_sec());
    seq_printf(seq,     "    new_dscp         = %u\n",   (uint32_t)p_item->new_dscp);
    seq_printf(seq,     "    pppoe_session_id = %u\n",   (uint32_t)p_item->pppoe_session_id);
    seq_printf(seq,     "    new_vci          = 0x%04X\n", (uint32_t)p_item->new_vci);
    seq_printf(seq,     "    out_vlan_tag     = 0x%08X\n", p_item->out_vlan_tag);
    seq_printf(seq,     "    mtu              = %u\n",   p_item->mtu);
    seq_printf(seq,     "    dslwan_qid       = %u (RX), %u (TX)\n",   ((uint32_t)p_item->dslwan_qid >> 8) & 0xFF, (uint32_t)p_item->dslwan_qid & 0xFF);
    seq_printf(seq,     "    skb priority     = %02u\n",   p_item->priority);
    seq_printf(seq,     "    skb mark         = %02u\n",   p_item->mark);
    seq_printf(seq,     "    referece count   = %d\n",   p_item->used);
    print_session_ifid(seq, "    dest_ifid        = ",   p_item->dest_ifid);

    print_session_flags(seq, "    flags            = ", p_item->flags);
#if defined(ENABLE_SESSION_DEBUG_FLAGS) && ENABLE_SESSION_DEBUG_FLAGS
    print_session_debug_flags(seq, "    debug_flags      = ", p_item->debug_flags);
#endif
    
	if ( p_item->routing_entry == ~0 )
        seq_printf(seq, "    routing_entry    = N/A\n");
    else
        seq_printf(seq, "    routing_entry    = %u (%s)\n", p_item->routing_entry & 0x7FFFFFFF, (p_item->routing_entry & 0x80000000) ? "LAN" : "WAN");
    if ( p_item->pppoe_entry == ~0 )
        seq_printf(seq, "    pppoe_entry      = N/A\n");
    else
        seq_printf(seq, "    pppoe_entry      = %d\n", p_item->pppoe_entry);
    if ( p_item->mtu_entry == ~0 )
        seq_printf(seq, "    mtu_entry        = N/A\n");
    else
        seq_printf(seq, "    mtu_entry        = %d\n", p_item->mtu_entry);
    if ( p_item->src_mac_entry == ~0 )
        seq_printf(seq, "    src_mac_entry    = N/A\n");
    else
        seq_printf(seq, "    src_mac_entry    = %d\n", p_item->src_mac_entry);
    if ( p_item->out_vlan_entry == ~0 )
        seq_printf(seq, "    out_vlan_entry   = N/A\n");
    else
        seq_printf(seq, "    out_vlan_entry   = %u\n",   p_item->out_vlan_entry);
    seq_printf(seq, 	"    mips bytes       = %llu\n",   p_item->mips_bytes - p_item->prev_clear_mips_bytes);

#if defined(MIB_MODE_ENABLE) && MIB_MODE_ENABLE
    ppa_drv_get_mib_mode(&mib_cfg);
    {
         if(mib_cfg.session_mib_unit == 1)
            seq_printf(seq, 	"    hw accel packets   = %llu(%llu:%llu)\n",   p_item->acc_bytes - p_item->prev_clear_acc_bytes, p_item->acc_bytes, p_item->prev_clear_acc_bytes);
       else
            seq_printf(seq, 	"    hw accel bytes   = %llu(%llu:%llu)\n",   p_item->acc_bytes - p_item->prev_clear_acc_bytes, p_item->acc_bytes, p_item->prev_clear_acc_bytes);
         seq_printf(seq, "    accel last/poll  = %llu/%u\n",   p_item->last_bytes, ppa_get_hit_polling_time());
    }
#else
    seq_printf(seq, 	"    hw accel bytes   = %llu(%llu:%llu)\n",   p_item->acc_bytes - p_item->prev_clear_acc_bytes, p_item->acc_bytes, p_item->prev_clear_acc_bytes);
#endif
    seq_printf(seq,     "    collision_flag   = %d\n",   p_item->collision_flag);

#if defined(SESSION_STATISTIC_DEBUG) && SESSION_STATISTIC_DEBUG 
    if( p_item->flag2 & SESSION_FLAG2_HASH_INDEX_DONE ) 
        seq_printf(seq, "    hash table/index = %u/%u\n",   p_item->hash_table_id, p_item->hash_index);
#endif
    
    return 0;
}

static INLINE int proc_read_mc_group_seq_show(struct seq_file *seq, void *v)
{
    struct mc_group_list_item *p_item = v;
    uint32_t pos = g_proc_read_session_pos & 0x0FFFFFFF;
    int i, j;
    uint32_t bit;

    if ( pos == 1 )
        seq_printf(seq,     "Session List (Multicast Routing)\n");

    seq_printf(seq,         "  no. %d\n", pos);
    seq_printf(seq,         "    next             = %08X\n", (uint32_t)p_item->mc_hlist.next);
    seq_printf(seq,         "    mode             = %s\n", p_item->bridging_flag ?  "bridging": "routing");
    seq_printf(seq,         "    ip_mc_group      = %u.%u.%u.%u\n", p_item->ip_mc_group.ip.ip >> 24, (p_item->ip_mc_group.ip.ip >> 16) & 0xFF, (p_item->ip_mc_group.ip.ip >> 8) & 0xFF, p_item->ip_mc_group.ip.ip & 0xFF);
    seq_printf(seq,         "    interfaces       = %d\n", p_item->num_ifs);
    for ( i = 0; i < p_item->num_ifs; i++ )
        if ( (p_item->if_mask & (1 << i)) && p_item->netif[i] != NULL )
            seq_printf(seq, "      %d. %16s (TTL %u)\n", i, ppa_get_netif_name(p_item->netif[i]), p_item->ttl[i]);
        else
            seq_printf(seq, "      %d. N/A              (mask %d, netif %s)\n", i, (p_item->if_mask & (1 << i)) ? 1 : 0, p_item->netif[i] ? ppa_get_netif_name(p_item->netif[i]) : "NULL");
    seq_printf(seq,         "    src_interface    = %s\n",   p_item->src_netif ? ppa_get_netif_name(p_item->src_netif) : "N/A");
    seq_printf(seq,         "    new_dscp         = %04X\n", (uint32_t)p_item->new_dscp);
    seq_printf(seq,         "    new_vci          = %04X\n", (uint32_t)p_item->new_vci);
    seq_printf(seq,         "    out_vlan_tag     = %08X\n", p_item->out_vlan_tag);
    seq_printf(seq,         "    dslwan_qid       = %u\n",   (uint32_t)p_item->dslwan_qid);

    for ( i = j = 0, bit = 1; i < sizeof(p_item->dest_ifid) * 8; i++, bit <<= 1 )
        if ( (p_item->dest_ifid & bit) )
        {
            print_session_ifid(seq, "    dest_ifid        = ", i);
        }

    print_session_flags(seq, "    flags            = ", p_item->flags);

#if defined(ENABLE_SESSION_DEBUG_FLAGS) && ENABLE_SESSION_DEBUG_FLAGS
    print_session_debug_flags(seq, "    debug_flags      = ", p_item->debug_flags);
#endif
    
	if ( p_item->mc_entry == ~0 )
        seq_printf(seq,     "    mc_entry         = N/A\n");
    else
        seq_printf(seq,     "    mc_entry         = %d\n", p_item->mc_entry);
    if ( p_item->src_mac_entry == ~0 )
        seq_printf(seq,     "    src_mac_entry    = N/A\n");
    else
        seq_printf(seq,     "    src_mac_entry    = %d\n", p_item->src_mac_entry);
    if ( p_item->out_vlan_entry == ~0 )
        seq_printf(seq,     "    out_vlan_entry   = N/A\n");
    else
        seq_printf(seq,     "    out_vlan_entry   = %d\n",   p_item->out_vlan_entry);

    return 0;
}

static INLINE int proc_read_bridging_session_seq_show(struct seq_file *seq, void *v)
{
    struct bridging_session_list_item *p_item = v;
    uint32_t pos = g_proc_read_session_pos & 0x0FFFFFFF;

    if ( pos == 1 )
        seq_printf(seq, "Session List (Bridging)\n");

    seq_printf(seq,     "  no. %d\n", pos);
    seq_printf(seq,     "    next             = %08X\n", (uint32_t)&p_item->br_hlist);
    seq_printf(seq,     "    mac[6]           = %02x:%02x:%02x:%02x:%02x:%02x\n", (uint32_t)p_item->mac[0], (uint32_t)p_item->mac[1], (uint32_t)p_item->mac[2], (uint32_t)p_item->mac[3], (uint32_t)p_item->mac[4], (uint32_t)p_item->mac[5]);
    seq_printf(seq,     "    netif            = %s (%08X)\n", p_item->netif == NULL ? "N/A" : ppa_get_netif_name(p_item->netif), (uint32_t)p_item->netif);
    seq_printf(seq,     "    vci              = %04X\n", (uint32_t)p_item->vci);
    seq_printf(seq,     "    new_vci          = %04X\n", (uint32_t)p_item->new_vci);
    seq_printf(seq,     "    timeout          = %d\n",   p_item->timeout);
    seq_printf(seq,     "    last_hit_time    = %d\n",   p_item->last_hit_time);
    seq_printf(seq,     "    dslwan_qid       = %d\n",   (uint32_t)p_item->dslwan_qid);

    print_session_ifid(seq, "    dest_ifid        = ",   p_item->dest_ifid);

    print_session_flags(seq, "    flags            = ", p_item->flags);

#if defined(ENABLE_SESSION_DEBUG_FLAGS) && ENABLE_SESSION_DEBUG_FLAGS
    print_session_debug_flags(seq, "    debug_flags      = ", p_item->debug_flags);
#endif
    if ( p_item->bridging_entry == ~0 )
        seq_printf(seq, "    bridging_entry   = N/A\n");
    else if ( (p_item->bridging_entry & 0x80000000) )
        seq_printf(seq, "    bridging_entry   = %08X\n", p_item->bridging_entry);
    else
        seq_printf(seq, "    bridging_entry   = %d\n", p_item->bridging_entry);

    return 0;
}

static INLINE int proc_read_routing_mini_session_seq_show(struct seq_file *seq, void *v)
{
	struct session_list_item *p_item = v;
	uint32_t pos = g_proc_read_session_pos & 0x0FFFFFFF;
	int8_t strbuf1[64], strbuf2[64], strbuf3[64];

	if (pos == 1) {
		seq_printf(seq, "===================================================================================================================================================\n");
		seq_printf(seq, "\t\t\t\t\t\tSession List (Unicast Routing)\n");
		seq_printf(seq, "===================================================================================================================================================\n");
		seq_printf(seq, "      No.|    Session|          Src_IP|          Dst_IP|          Nat_IP| Src_Port| Dst_Port| HW Flag| SW Flag|            Rx_If|            Tx_If\n");
		seq_printf(seq, "===================================================================================================================================================\n");
	}
	seq_printf(seq,
	" %8d| 0x%08X| %15s| %15s| %15s| %8u| %8u| %7s| %7s| %16s| %16s\n",
	pos,
	(uint32_t)p_item->session,
	ppa_get_pkt_ip_string(p_item->src_ip, p_item->flags & SESSION_IS_IPV6, strbuf1),
	ppa_get_pkt_ip_string(p_item->dst_ip, p_item->flags & SESSION_IS_IPV6, strbuf2),
	ppa_get_pkt_ip_string(p_item->nat_ip, p_item->flags & SESSION_IS_IPV6, strbuf3),
	(uint32_t)p_item->src_port,
	(uint32_t)p_item->dst_port,
	(p_item->flags & (SESSION_ADDED_IN_HW) ? "Yes" : " No"),
	(p_item->flags & (SESSION_ADDED_IN_SW) ? "Yes" : " No"),
	(p_item->rx_if == NULL ? "N/A" : ppa_get_netif_name(p_item->rx_if)),
	(p_item->tx_if == NULL ? "N/A" : ppa_get_netif_name(p_item->tx_if)));
	return 0;
}

static INLINE int proc_read_mc_mini_group_seq_show(struct seq_file *seq, void *v)
{
	struct mc_group_list_item *p_item = v;
	uint32_t pos = g_proc_read_session_pos & 0x0FFFFFFF;
	char mc_entry[STRBUF_SMALL_LEN], src_mac_entry[STRBUF_SMALL_LEN];

	if (pos == 1) {
		seq_printf(seq, "===================================================================================================================================================\n");
		seq_printf(seq, "\t\t\t\t\t\tSession List (Multicast Routing)\n");
		seq_printf(seq, "===================================================================================================================================================\n");
		seq_printf(seq, "      No.| Mc_hlist.next|     Mode|     IP_mc_group|    Src_Interface| Mc_entry| Src_mac_entry| Out_vlan|  dslwan_qid| HW Flag| SW Flag\n");
		seq_printf(seq, "===================================================================================================================================================\n");
	}

	if (p_item->mc_entry == ~0)
		snprintf(mc_entry, sizeof(mc_entry), "N/A");
	else
		snprintf(mc_entry, sizeof(mc_entry), "%d", p_item->mc_entry);

	if (p_item->src_mac_entry == ~0)
		snprintf(src_mac_entry, sizeof(src_mac_entry), "N/A");
	else
		snprintf(src_mac_entry, sizeof(src_mac_entry), "%d", p_item->src_mac_entry);

	seq_printf(seq,
	" %8d| %13X| %8s| %3u.%3u.%3u.%3u| %16s| %8s| %13s| %08X| %11u| %7s| %7s\n",
	pos,
	(uint32_t)p_item->mc_hlist.next,
	p_item->bridging_flag ? "bridging" : "routing",
	p_item->ip_mc_group.ip.ip >> 24,
	(p_item->ip_mc_group.ip.ip >> 16) & 0xFF,
	(p_item->ip_mc_group.ip.ip >> 8) & 0xFF,
	p_item->ip_mc_group.ip.ip & 0xFF,
	p_item->src_netif ? ppa_get_netif_name(p_item->src_netif) : "N/A",
	mc_entry,
	src_mac_entry,
	p_item->out_vlan_tag,
	(uint32_t)p_item->dslwan_qid,
	(p_item->flags & (SESSION_ADDED_IN_HW) ? "Yes" : " No"),
	(p_item->flags & (SESSION_ADDED_IN_SW) ? "Yes" : " No"));

	return 0;
}

static INLINE int proc_read_bridging_mini_session_seq_show(struct seq_file *seq, void *v)
{
	struct bridging_session_list_item *p_item = v;
	uint32_t pos = g_proc_read_session_pos & 0x0FFFFFFF;

	if (pos == 1) {
		seq_printf(seq, "===================================================================================================================================================\n");
		seq_printf(seq, "\t\t\t\t\t\tSession List (Bridging)\n");
		seq_printf(seq, "===================================================================================================================================================\n");
		seq_printf(seq, "      No.| Br_hlist|            Mac[6]|            Netif|        dest_ifid|  dslwan_qid| HW Flag| SW Flag| Timeout\n");
		seq_printf(seq, "===================================================================================================================================================\n");
	}
	seq_printf(seq,
	" %8d| %08X| %02x:%02x:%02x:%02x:%02x:%02x| %16s| %16d| %11u| %7s| %7s| %7d\n",
	pos,
	(uint32_t)&p_item->br_hlist,
	(uint32_t)p_item->mac[0],
	(uint32_t)p_item->mac[1],
	(uint32_t)p_item->mac[2],
	(uint32_t)p_item->mac[3],
	(uint32_t)p_item->mac[4],
	(uint32_t)p_item->mac[5],
	(p_item->netif == NULL ? "N/A" : ppa_get_netif_name(p_item->netif)),
	(uint32_t)p_item->dest_ifid,
	(uint32_t)p_item->dslwan_qid,
	(p_item->flags & (SESSION_ADDED_IN_HW) ? "Yes" : " No"),
	(p_item->flags & (SESSION_ADDED_IN_SW) ? "Yes" : " No"),
	p_item->timeout);

	return 0;

}

static int proc_read_session_seq_show(struct seq_file *seq, void *v)
{
    switch ( g_proc_read_session_pos & 0x30000000 )
    {
    case 0x00000000: return proc_read_routing_session_seq_show(seq, v);
    case 0x10000000: return proc_read_mc_group_seq_show(seq, v);
    case 0x20000000: return proc_read_bridging_session_seq_show(seq, v);
    default:         return 0;
    }
}
static int proc_read_mini_session_seq_show(struct seq_file *seq, void *v)
{
	switch (g_proc_read_session_pos & 0x30000000)
	{
		case 0x00000000: return proc_read_routing_mini_session_seq_show(seq, v);
		case 0x10000000: return proc_read_mc_mini_group_seq_show(seq, v);
		case 0x20000000: return proc_read_bridging_mini_session_seq_show(seq, v);
		default:         return 0;
	}
}

static int proc_read_session_seq_open(struct inode *inode, struct file *file)
{
    return seq_open(file, &g_proc_read_session_seq_ops);
}

static int proc_read_mini_session_seq_open(struct inode *inode, struct file *file)
{
    return seq_open(file, &g_proc_read_mini_session_seq_ops);
}
int ppa_split_buffer(char *buffer, char *array[], int max_param_num)
{
	int i, set_copy = 0;
	int res = 0;
	int len;

	for (i = 0; i < max_param_num; i++)
		array[i] = NULL;
	if (!buffer)
		return 0;
	len = strlen(buffer);
	for (i = 0; i < max_param_num;) {
		while (len && ((*buffer == ' ') || (*buffer == '\r') || (*buffer == '\r'))) {
			buffer++;
			len--;
		}
		for (;
				*buffer != ' ' && *buffer != '\0' && *buffer != '\r' &&
				*buffer != '\n' && *buffer != '\t'; buffer++, len--) {
			/*Find first valid charactor */
			set_copy = 1;
			if (!array[i])
				array[i] = buffer;
		}

		if (set_copy == 1) {
			i++;
			if (*buffer == '\0' || *buffer == '\r' ||
					*buffer == '\n') {
				*buffer = 0;
				break;
			}
			*buffer = 0;
			buffer++;
			len--;
			set_copy = 0;

		} else {
			if (*buffer == '\0' || *buffer == '\r' ||
					*buffer == '\n')
				break;
			buffer++;
			len--;
		}
	}
	res = i;

	return res;
}

static ssize_t proc_file_write_mini_session(struct file *file, const char __user *buf, size_t count,
                            loff_t *ppos)
{
	int len, num;
	char str[64];
	char *param_list[5];
	len = (sizeof(str) > count) ? count : sizeof(str) - 1;
	len -= copy_from_user(str, buf, len);
	str[len] = 0;

	if (!len)
		return count;

	num = ppa_split_buffer(str, param_list, ARRAY_SIZE(param_list));

	if (num < 2)
		goto PRINT_USAGE;

	if (stricmp(param_list[0], "u") == 0) {
		snprintf(session_buf, sizeof(session_buf), "%s", param_list[1]);
		if(!ppa_session_find_unicast_routing(session_buf))
			printk("No Unicast Routing Session with session-id = %s is present\n", session_buf);
		memset(session_buf, 0, sizeof(session_buf));
	}
	else if (stricmp(param_list[0], "m") == 0) {
		snprintf(session_buf, sizeof(session_buf), "%s", param_list[1]);
		if(!ppa_session_find_multicast_routing(session_buf))
			printk("No Multicast Routing Session with mc_hlist.next = %s is present\n", session_buf);
		memset(session_buf, 0, sizeof(session_buf));
	}
	else if (stricmp(param_list[0], "b") == 0) {
		snprintf(session_buf, sizeof(session_buf), "%s", param_list[1]);
		if(!ppa_session_find_bridging(session_buf))
			printk("No Bridging Session with session-id = %s is present\n", session_buf);
		memset(session_buf, 0, sizeof(session_buf));
	}
#if defined(CONFIG_LTQ_PPA_API_SW_FASTPATH)
	else if (stricmp(param_list[0], "s") == 0 && stricmp(param_list[1], "u") == 0) {
		snprintf(session_buf, sizeof(session_buf), "%s", param_list[2]);
		if (!ppa_session_find_unicast_routing_sw_hdr(session_buf))
			printk("No Unicast Routing Session with session-id = %s is present\n", session_buf);
		memset(session_buf, 0, sizeof(session_buf));
	}
#endif
	else
		goto PRINT_USAGE;

	return count;

PRINT_USAGE:
	printk("Usage:\n");
	printk("Display unicast routing session information:  echo u session-id > /proc/ppa/api/mini_session\n");
	printk("Display multicast routing session information:  echo m mc_hlist.next > /proc/ppa/api/mini_session\n");
	printk("Display bridging session information:  echo b br_hlist > /proc/ppa/api/mini_session\n");
#if defined(CONFIG_LTQ_PPA_API_SW_FASTPATH)
	printk("Display software accelerated header information for unicast routing session:  echo s u session-id > /proc/ppa/api/mini_session\n");
#endif
	return count;

}

int ppa_session_find_unicast_routing(char *session_buf_unicast)
{
	struct session_list_item *pp_item = NULL;
	uint32_t pos = 0, match = 0, i;

	if (ppa_session_start_iteration(&pos, &pp_item) == PPA_SUCCESS) {
		printk("=================================================================================================================\n");
		printk("                                     Unicast Routing Session(s)\n");
		printk("=================================================================================================================\n");
		do {
			if (!kstrtol(session_buf_unicast, 16, &i) && (uint32_t)pp_item->session == i) {
				printk("    No. %d\n", ++match);
				printk("=================================================================================================================\n");
				ppa_unicast_routing_print_session(pp_item);
				printk("=================================================================================================================\n");
			}
		} while(ppa_session_iterate_next(&pos, &pp_item) == PPA_SUCCESS);
	}

        ppa_session_stop_iteration();
	return match;
}

int ppa_session_find_unicast_routing_sw_hdr(char *session_buf_unicast)
{
	struct session_list_item *pp_item = NULL;
	uint32_t pos = 0, match = 0, present = 0, i;

	if (ppa_session_start_iteration(&pos, &pp_item) == PPA_SUCCESS) {
		printk("=================================================================================================================\n");
		printk("                                     Unicast Routing Session(s) Sw Accel header\n");
		printk("=================================================================================================================\n");
		do {
			if (!kstrtol(session_buf_unicast, 16, &i) && (uint32_t)pp_item->session == i) {
				present = 1;
				if (pp_item->flags & (SESSION_ADDED_IN_SW)) {
					printk("    No. %d\n", ++match);
					printk("=================================================================================================================\n");
					ppa_unicast_routing_print_session_sw_hdr(pp_item);
					printk("=================================================================================================================\n");
				}
				else {
					printk("Unicast Routing Session with Session ID 0x%08X is not Added in Software\n", (uint32_t)pp_item->session);
				}
			}
		} while (ppa_session_iterate_next(&pos, &pp_item) == PPA_SUCCESS);
	}

        ppa_session_stop_iteration();
	return present;
}

int ppa_session_find_multicast_routing(char *session_buf_multicast)
{
	struct mc_group_list_item *pp_item = NULL;
	uint32_t pos = 0, match = 0, i;

	if (ppa_mc_group_start_iteration(&pos, &pp_item) == PPA_SUCCESS) {
		printk("=================================================================================================================\n");
		printk("                                       Multicast Routing Session(s)\n");
		printk("=================================================================================================================\n");
		do {
			if (!kstrtol(session_buf_multicast, 16, &i) && (uint32_t)pp_item->mc_hlist.next == i) {
				printk("    No. %d\n", ++match);
				printk("=================================================================================================================\n");
				ppa_multicast_routing_print_session(pp_item);
				printk("=================================================================================================================\n");
			}
		} while (ppa_mc_group_iterate_next(&pos, &pp_item) == PPA_SUCCESS);
	}

	ppa_mc_group_stop_iteration();
	return match;
}

int ppa_session_find_bridging(char *session_buf_bridge)
{
	struct bridging_session_list_item *pp_item = NULL;
	uint32_t pos = 0, match = 0, i;

	if (ppa_bridging_session_start_iteration(&pos, &pp_item) == PPA_SUCCESS) {
		printk("=================================================================================================================\n");
		printk("                                           Bridging Session(s)\n");
		printk("=================================================================================================================\n");
		do {
			if (!kstrtol(session_buf_bridge, 16, &i) && (uint32_t)&pp_item->br_hlist == i) {
				printk("    No. %d\n", ++match);
				printk("=================================================================================================================\n");
				ppa_bridging_print_session(pp_item);
				printk("=================================================================================================================\n");
			}
		} while(ppa_bridging_session_iterate_next(&pos, &pp_item) == PPA_SUCCESS);
	}

	ppa_bridging_session_stop_iteration();
	return match;
}

void ppa_unicast_routing_print_session(struct session_list_item *p_item)
{
	int8_t strbuf[64];
#if defined(MIB_MODE_ENABLE) && MIB_MODE_ENABLE
	PPE_MIB_MODE_ENABLE mib_cfg;
#endif
	printk("    next             = 0x%08X\n", (uint32_t)&p_item->hlist);
	printk("    session          = 0x%08X\n", (uint32_t)p_item->session);
	printk("    ip_proto         = %u\n",   (uint32_t)p_item->ip_proto);
#ifdef CONFIG_PPA_PP_LEARNING
	printk("    eth_type         = %u\n",   (uint32_t)p_item->protocol);
#endif
	printk("    ip_tos           = %u\n",   (uint32_t)p_item->ip_tos);
	printk("    src_ip           = %s\n",   ppa_get_pkt_ip_string(p_item->src_ip, p_item->flags & SESSION_IS_IPV6, strbuf));
	printk("    src_port         = %u\n",   (uint32_t)p_item->src_port);
	printk("    src_mac[6]       = %s\n",	 ppa_get_pkt_mac_string(p_item->src_mac, strbuf));
	printk("    dst_ip           = %s\n",   ppa_get_pkt_ip_string(p_item->dst_ip, p_item->flags & SESSION_IS_IPV6, strbuf));
	printk("    dst_port         = %u\n",   (uint32_t)p_item->dst_port);
	printk("    dst_mac[6]       = %s\n",   ppa_get_pkt_mac_string(p_item->dst_mac, strbuf));
	printk("    nat_ip           = %s\n",   ppa_get_pkt_ip_string(p_item->nat_ip, p_item->flags & SESSION_IS_IPV6, strbuf));
	printk("    nat_port         = %u\n",   (uint32_t)p_item->nat_port);
	printk("    nat_src_mac[6]   = %s\n",   ppa_get_pkt_mac_string(p_item->nat_src_mac, strbuf));
	printk("    num_adds         = %u( minimum required hit is %d)\n",   (uint32_t)p_item->num_adds, g_ppa_min_hits);
#ifdef CONFIG_MIPS
	if ((uint32_t)p_item->rx_if < KSEG0 || (uint32_t)p_item->rx_if >= KSEG1)
		printk("    rx_if            = %s (0x%08X)\n", "N/A", (uint32_t)p_item->rx_if);
	else
#endif
		printk("    rx_if            = %s (0x%08X)\n", p_item->rx_if == NULL ? "N/A" : ppa_get_netif_name(p_item->rx_if), (uint32_t)p_item->rx_if);
#ifdef CONFIG_MIPS
	if ((uint32_t)p_item->tx_if < KSEG0 || (uint32_t)p_item->tx_if >= KSEG1)
		printk("    tx_if            = %s (0x%08X)\n", "N/A(may no ip output hook or not meet hit count)", (uint32_t)p_item->tx_if);
	else
#endif
		printk("    tx_if            = %s (0x%08X)\n", p_item->tx_if == NULL ? "N/A" : ppa_get_netif_name(p_item->tx_if), (uint32_t)p_item->tx_if);
	printk("    timeout          = %u\n",   p_item->timeout);
	printk("    last_hit_time    = %u (now %u)\n",   p_item->last_hit_time, ppa_get_time_in_sec());
	printk("    new_dscp         = %u\n",   (uint32_t)p_item->new_dscp);
	printk("    pppoe_session_id = %u\n",   (uint32_t)p_item->pppoe_session_id);
	printk("    new_vci          = 0x%04X\n", (uint32_t)p_item->new_vci);
	printk("    out_vlan_tag     = 0x%08X\n", p_item->out_vlan_tag);
	printk("    mtu              = %u\n",   p_item->mtu);
	printk("    dslwan_qid       = %u (RX), %u (TX)\n",   ((uint32_t)p_item->dslwan_qid >> 8) & 0xFF, (uint32_t)p_item->dslwan_qid & 0xFF);
	printk("    skb priority     = %02u\n",   p_item->priority);
	printk("    skb mark         = %02u\n",   p_item->mark);
	printk_session_ifid("    dest_ifid        = ",   p_item->dest_ifid);

	printk_session_flags("    flags            = ", p_item->flags);
#if defined(ENABLE_SESSION_DEBUG_FLAGS) && ENABLE_SESSION_DEBUG_FLAGS
	printk_session_debug_flags("    debug_flags      = ", p_item->debug_flags);
#endif

	if (p_item->routing_entry == ~0)
		printk("    routing_entry    = N/A\n");
	else
		printk("    routing_entry    = %u (%s)\n", p_item->routing_entry & 0x7FFFFFFF, (p_item->routing_entry & 0x80000000) ? "LAN" : "WAN");
	if (p_item->pppoe_entry == ~0)
		printk("    pppoe_entry      = N/A\n");
	else
		printk("    pppoe_entry      = %d\n", p_item->pppoe_entry);
	if (p_item->mtu_entry == ~0)
		printk("    mtu_entry        = N/A\n");
	else
		printk("    mtu_entry        = %d\n", p_item->mtu_entry);
	if (p_item->src_mac_entry == ~0)
		printk("    src_mac_entry    = N/A\n");
	else
		printk("    src_mac_entry    = %d\n", p_item->src_mac_entry);
	if (p_item->out_vlan_entry == ~0)
		printk("    out_vlan_entry   = N/A\n");
	else
		printk("    out_vlan_entry   = %u\n",   p_item->out_vlan_entry);
	printk("    mips bytes       = %llu\n",   p_item->mips_bytes - p_item->prev_clear_mips_bytes);

#if defined(MIB_MODE_ENABLE) && MIB_MODE_ENABLE
	ppa_drv_get_mib_mode(&mib_cfg);
	{
		if (mib_cfg.session_mib_unit == 1)
			printk("    hw accel packets   = %llu(%llu:%llu)\n",   p_item->acc_bytes - p_item->prev_clear_acc_bytes, p_item->acc_bytes, p_item->prev_clear_acc_bytes);
		else
			printk("    hw accel bytes   = %llu(%llu:%llu)\n",   p_item->acc_bytes - p_item->prev_clear_acc_bytes, p_item->acc_bytes, p_item->prev_clear_acc_bytes);
		printk("    accel last/poll  = %llu/%u\n",   p_item->last_bytes, ppa_get_hit_polling_time());
	}
#else
	printk("    hw accel bytes   = %llu(%llu:%llu)\n",   p_item->acc_bytes - p_item->prev_clear_acc_bytes, p_item->acc_bytes, p_item->prev_clear_acc_bytes);
#endif
	printk("    collision_flag   = %d\n",   p_item->collision_flag);

#if defined(SESSION_STATISTIC_DEBUG) && SESSION_STATISTIC_DEBUG
	if (p_item->flag2 & SESSION_FLAG2_HASH_INDEX_DONE)
		printk("    hash table/index = %u/%u\n",   p_item->hash_table_id, p_item->hash_index);
#endif
}

void ppa_unicast_routing_print_session_sw_hdr(struct session_list_item *p_item)
{
#if IS_ENABLED(CONFIG_LTQ_PPA_API_SW_FASTPATH)
	t_sw_hdr *swh = NULL;
	if (p_item->sah != NULL) {
		swh = (t_sw_hdr *)p_item->sah;
		printk("    session          		= 0x%08X\n", (uint32_t)p_item->session);
		printk("    tot_hdr_len      		= %u\n", swh->tot_hdr_len);
		printk("    transport hdr offset  	= %u\n", swh->transport_offset); 
		printk("    network hdr offset		= %u\n", swh->network_offset);
		printk("    extmark          		= %u\n", swh->extmark);
		printk("    type     			= %s\n", (swh->type < SW_ACC_TYPE_MAX ? ppa_get_sw_hdr_type[swh->type]() : "UNKNOWN"));
		printk("    tx_if		        = %s\n", (swh->tx_if == NULL ? "N/A" : ppa_get_netif_name(swh->tx_if)));
		printk("    tx_handler		        = %s\n", ppa_get_sw_hdr_tx_handler_name(swh->tx_handler));
		printk("    Hexdump of Header      	=\n\n");
		print_hex_dump(KERN_DEBUG, "", DUMP_PREFIX_NONE, 16, 1, swh, swh->tot_hdr_len, true);
	}
	else {
		printk(" No Sw Accel header for 0x%08x session is present\n", (uint32_t)p_item->session);
	}
#endif
}

static unsigned char *ppa_sw_ipv4_name()
{
	return "SW_ACC_TYPE_IPV4";
}
static unsigned char *ppa_sw_ipv6_name()
{
	return "SW_ACC_TYPE_IPV6";
}
static unsigned char *ppa_sw_6rd_name()
{
	return "SW_ACC_TYPE_6RD";
}
static unsigned char *ppa_sw_dslite_name()
{
	return "SW_ACC_TYPE_DSLITE";
}
static unsigned char *ppa_sw_bridged_name()
{
	return "SW_ACC_TYPE_BRIDGED";
}
#if defined(CONFIG_LTQ_PPA_TCP_LITEPATH) && CONFIG_LTQ_PPA_TCP_LITEPATH
static unsigned char *ppa_sw_ltcp_name()
{
	return "SW_ACC_TYPE_LTCP";
}
#if defined(CONFIG_LTQ_PPA_LRO) && CONFIG_LTQ_PPA_LRO
static unsigned char *ppa_sw_ltcp_lro_name()
{
	return "SW_ACC_TYPE_LTCP_LRO";
}
#endif
#endif

unsigned char *ppa_get_sw_hdr_tx_handler_name(int *tx_handler)
{
	if (tx_handler == &dev_queue_xmit)
		return "dev_queue_xmit";
#if defined(CONFIG_LTQ_PPA_TCP_LITEPATH) && CONFIG_LTQ_PPA_TCP_LITEPATH
	else if (tx_handler == &ppa_sw_litepath_local_deliver)
		return "ppa_sw_litepath_local_deliver";
#endif
	else
		return (tx_handler) ? "Unknown" : "NULL";
}

void ppa_multicast_routing_print_session(struct mc_group_list_item *p_item)
{
	int i, j;
	uint32_t bit;
	printk("    next             = %08X\n", (uint32_t)p_item->mc_hlist.next);
	printk("    mode             = %s\n", p_item->bridging_flag ?  "bridging" : "routing");
	printk("    ip_mc_group      = %u.%u.%u.%u\n", p_item->ip_mc_group.ip.ip >> 24, (p_item->ip_mc_group.ip.ip >> 16) & 0xFF, (p_item->ip_mc_group.ip.ip >> 8) & 0xFF, p_item->ip_mc_group.ip.ip & 0xFF);
	printk("    interfaces       = %d\n", p_item->num_ifs);
	for (i = 0; i < p_item->num_ifs; i++)
		if ((p_item->if_mask & (1 << i)) && p_item->netif[i] != NULL)
			printk("      %d. %16s (TTL %u)\n", i, ppa_get_netif_name(p_item->netif[i]), p_item->ttl[i]);
		else
			printk("      %d. N/A              (mask %d, netif %s)\n", i, (p_item->if_mask & (1 << i)) ? 1 : 0, p_item->netif[i] ? ppa_get_netif_name(p_item->netif[i]) : "NULL");
	printk("    src_interface    = %s\n",   p_item->src_netif ? ppa_get_netif_name(p_item->src_netif) : "N/A");
	printk("    new_dscp         = %04X\n", (uint32_t)p_item->new_dscp);
	printk("    new_vci          = %04X\n", (uint32_t)p_item->new_vci);
	printk("    out_vlan_tag     = %08X\n", p_item->out_vlan_tag);
	printk("    dslwan_qid       = %u\n",   (uint32_t)p_item->dslwan_qid);

	for (i = j = 0, bit = 1; i < sizeof(p_item->dest_ifid) * 8; i++, bit <<= 1)
		if ((p_item->dest_ifid & bit)) {
			printk_session_ifid("    dest_ifid        = ", i);
		}

	printk_session_flags("    flags            = ", p_item->flags);

#if defined(ENABLE_SESSION_DEBUG_FLAGS) && ENABLE_SESSION_DEBUG_FLAGS
	printk_session_debug_flags("    debug_flags      = ", p_item->debug_flags);
#endif

	if (p_item->mc_entry == ~0)
		printk("    mc_entry         = N/A\n");
	else
		printk("    mc_entry         = %d\n", p_item->mc_entry);
	if (p_item->src_mac_entry == ~0)
		printk("    src_mac_entry    = N/A\n");
	else
		printk("    src_mac_entry    = %d\n", p_item->src_mac_entry);
	if (p_item->out_vlan_entry == ~0)
		printk("    out_vlan_entry   = N/A\n");
	else
		printk("    out_vlan_entry   = %d\n",   p_item->out_vlan_entry);
}

void ppa_bridging_print_session(struct bridging_session_list_item *p_item)
{

	printk("    next             = %08X\n", (uint32_t)&p_item->br_hlist);
	printk("    mac[6]           = %02x:%02x:%02x:%02x:%02x:%02x\n", (uint32_t)p_item->mac[0], (uint32_t)p_item->mac[1], (uint32_t)p_item->mac[2], (uint32_t)p_item->mac[3], (uint32_t)p_item->mac[4], (uint32_t)p_item->mac[5]);
	printk("    netif            = %s (%08X)\n", p_item->netif == NULL ? "N/A" : ppa_get_netif_name(p_item->netif), (uint32_t)p_item->netif);
	printk("    vci              = %04X\n", (uint32_t)p_item->vci);
	printk("    new_vci          = %04X\n", (uint32_t)p_item->new_vci);
	printk("    timeout          = %d\n",   p_item->timeout);
	printk("    last_hit_time    = %d\n",   p_item->last_hit_time);
	printk("    dslwan_qid       = %d\n",   (uint32_t)p_item->dslwan_qid);

	printk_session_ifid("    dest_ifid        = ",   p_item->dest_ifid);

	printk_session_flags("    flags            = ", p_item->flags);

#if defined(ENABLE_SESSION_DEBUG_FLAGS) && ENABLE_SESSION_DEBUG_FLAGS
	printk_session_debug_flags("    debug_flags      = ", p_item->debug_flags);
#endif
	if (p_item->bridging_entry == ~0)
		printk("    bridging_entry   = N/A\n");
	else if ((p_item->bridging_entry & 0x80000000))
		printk("    bridging_entry   = %08X\n", p_item->bridging_entry);
	else
		printk("    bridging_entry   = %d\n", p_item->bridging_entry);
}

#ifdef CONFIG_LTQ_PPA_API_DIRECTPATH

static void *proc_read_directpath_seq_start(struct seq_file *seq, loff_t *ppos)
{
    struct ppe_directpath_data *info;

    if ( *ppos != 0 )
        (*ppos)--;

    g_proc_read_directpath_pos = (uint32_t)*ppos;
    if ( ppa_directpath_data_start_iteration(&g_proc_read_directpath_pos, &info) == PPA_SUCCESS )
    {
        *ppos = g_proc_read_directpath_pos;
        return info;
    }
    else
        return NULL;
}

static void *proc_read_directpath_seq_next(struct seq_file *seq, void *v, loff_t *ppos)
{
    struct ppe_directpath_data *info = (struct ppe_directpath_data *)v;

    g_proc_read_directpath_pos = (uint32_t)*ppos ;//+ 15;
    if ( ppa_directpath_data_iterate_next(&g_proc_read_directpath_pos, &info) == PPA_SUCCESS )
    {
        *ppos = g_proc_read_directpath_pos;
        return info;
    }
    else
        return NULL;
}

static void proc_read_directpath_seq_stop(struct seq_file *seq, void *v)
{
    ppa_directpath_data_stop_iteration();
}

static int proc_read_directpath_seq_show(struct seq_file *seq, void *v)
{
    struct ppe_directpath_data *info = (struct ppe_directpath_data *)v;
    uint32_t start_ifid;
#if defined(CONFIG_KALLSYMS) && defined(CONFIG_LTQ_PPA_API_PROC)
    const char *name;
    unsigned long offset, size;
    char *modname;
    char namebuf[KSYM_NAME_LEN+1];
#endif

    ppa_directpath_get_ifid_range(&start_ifid, NULL);

    if ( g_proc_read_directpath_pos == 1 )
        seq_printf(seq, "Directpath Registry List\n");
#if !(defined(CONFIG_LTQ_PPA_GRX500) && CONFIG_LTQ_PPA_GRX500)
    seq_printf(seq,     "  ifid. %u\n", (start_ifid + g_proc_read_directpath_pos - 1));
#endif
#if defined(CONFIG_LTQ_PPA_GRX500) && CONFIG_LTQ_PPA_GRX500
    if ( (info->flags & PPE_DIRECTPATH_DATA_RX_ENABLE) )
#else
    if ( (info->flags & PPE_DIRECTPATH_DATA_ENTRY_VALID) )
#endif
    {
#if defined(CONFIG_LTQ_PPA_GRX500) && CONFIG_LTQ_PPA_GRX500
	    if((start_ifid + g_proc_read_directpath_pos -1)%(MAX_SUBIF + 1) == 0) {
		    seq_printf(seq,     "  Port. %u\n", (start_ifid + g_proc_read_directpath_pos -1)/(MAX_SUBIF + 1));
		    seq_printf(seq, "    callback\n");
#if defined(CONFIG_KALLSYMS) && defined(CONFIG_LTQ_PPA_API_PROC)
		    if ( info->callback.stop_tx_fn && (name = kallsyms_lookup((unsigned long)info->callback.stop_tx_fn, &size, &offset, &modname, namebuf)) )
			    seq_printf(seq, "      stop_tx_fn     = %s (%08x)\n", name, (u32)info->callback.stop_tx_fn);
		    else
			    seq_printf(seq, "      stop_tx_fn     = %08x\n", (u32)info->callback.stop_tx_fn);
		    if ( info->callback.start_tx_fn && (name = kallsyms_lookup((unsigned long)info->callback.start_tx_fn, &size, &offset, &modname, namebuf)) )
			    seq_printf(seq, "      start_tx_fn    = %s (%08x)\n", name, (u32)info->callback.start_tx_fn);
		    else
			    seq_printf(seq, "      start_tx_fn    = %08x\n", (u32)info->callback.start_tx_fn);
		    if ( info->callback.rx_fn && (name = kallsyms_lookup((unsigned long)info->callback.rx_fn, &size, &offset, &modname, namebuf)) )
			    seq_printf(seq, "      rx_fn          = %s (%08x)\n", name, (u32)info->callback.rx_fn);
		    else
			    seq_printf(seq, "      rx_fn          = %08x\n", (u32)info->callback.rx_fn);
#else
		    seq_printf(seq,     "      stop_tx_fn     = %08x\n", (u32)info->callback.stop_tx_fn);
		    seq_printf(seq,     "      start_tx_fn    = %08x\n", (u32)info->callback.start_tx_fn);
		    seq_printf(seq,     "      rx_fn          = %08x\n", (u32)info->callback.rx_fn);
#endif
		    if ( info->netif )
			    seq_printf(seq, "    netif            = %s (%08x)\n", info->netif->name, (u32)info->netif);
		    else
			    seq_printf(seq, "    netif            = N/A\n");
		    seq_printf(seq, "    ifid             = %d\n", (u32)info->ifid);
#if defined(CONFIG_LTQ_PPA_DIRECTPATH_TX_QUEUE_SIZE) || defined(CONFIG_LTQ_PPA_DIRECTPATH_TX_QUEUE_PKTS)
		    seq_printf(seq, "    skb_list         = %08x\n", (u32)info->skb_list);
#ifdef CONFIG_LTQ_PPA_DIRECTPATH_TX_QUEUE_SIZE
		    seq_printf(seq, "    skb_list_size    = %u\n", info->skb_list_size);
#else
		    seq_printf(seq, "    skb_list_len     = %u\n", info->skb_list_len);
#endif
#endif
		    seq_printf(seq, "    rx_fn_rxif_pkt   = %u\n", info->rx_fn_rxif_pkt);
		    seq_printf(seq, "    rx_fn_txif_pkt   = %u\n", info->rx_fn_txif_pkt);
		    seq_printf(seq, "    tx_pkt           = %u\n", info->tx_pkt);
		    seq_printf(seq, "    tx_pkt_dropped   = %u\n", info->tx_pkt_dropped);
		    seq_printf(seq, "    tx_pkt_queued    = %u\n", info->tx_pkt_queued);
		    seq_printf(seq, "    flags            = VALID");
		    if ( (info->flags & PPE_DIRECTPATH_DATA_RX_ENABLE) )
			    seq_printf(seq, " | RX_EN");
		    if ( (info->flags & PPE_DIRECTPATH_ETH) )
			    seq_printf(seq, " | ETH");
		    if ( (info->flags & PPE_DIRECTPATH_CORE0) )
			    seq_printf(seq, " | CPU0");
		    if ( (info->flags & PPE_DIRECTPATH_CORE1) )
			    seq_printf(seq, " | CPU1");
		    seq_printf(seq, "\n");

	    } else {
		    seq_printf(seq,     " \t Subif. %u\n", ((start_ifid + g_proc_read_directpath_pos -1)%(MAX_SUBIF + 1)) -1 );

		    seq_printf(seq, "\t    callback\n");
#if defined(CONFIG_KALLSYMS) && defined(CONFIG_LTQ_PPA_API_PROC)
		    if ( info->callback.stop_tx_fn && (name = kallsyms_lookup((unsigned long)info->callback.stop_tx_fn, &size, &offset, &modname, namebuf)) )
			    seq_printf(seq, "\t      stop_tx_fn     = %s (%08x)\n", name, (u32)info->callback.stop_tx_fn);
		    else
			    seq_printf(seq, "\t      stop_tx_fn     = %08x\n", (u32)info->callback.stop_tx_fn);
		    if ( info->callback.start_tx_fn && (name = kallsyms_lookup((unsigned long)info->callback.start_tx_fn, &size, &offset, &modname, namebuf)) )
			    seq_printf(seq, "\t      start_tx_fn    = %s (%08x)\n", name, (u32)info->callback.start_tx_fn);
		    else
			    seq_printf(seq, "\t      start_tx_fn    = %08x\n", (u32)info->callback.start_tx_fn);
		    if ( info->callback.rx_fn && (name = kallsyms_lookup((unsigned long)info->callback.rx_fn, &size, &offset, &modname, namebuf)) )
			    seq_printf(seq, "\t      rx_fn          = %s (%08x)\n", name, (u32)info->callback.rx_fn);
		    else
			    seq_printf(seq, "\t      rx_fn          = %08x\n", (u32)info->callback.rx_fn);
#else
		    seq_printf(seq,     "\t      stop_tx_fn     = %08x\n", (u32)info->callback.stop_tx_fn);
		    seq_printf(seq,     "\t      start_tx_fn    = %08x\n", (u32)info->callback.start_tx_fn);
		    seq_printf(seq,     "\t      rx_fn          = %08x\n", (u32)info->callback.rx_fn);
#endif
		    if ( info->netif )
			    seq_printf(seq, "\t    netif            = %s (%08x)\n", info->netif->name, (u32)info->netif);
		    else
			    seq_printf(seq, "\t    netif            = N/A\n");
		    seq_printf(seq, "\t    ifid             = %d\n", (u32)info->ifid);
#if defined(CONFIG_LTQ_PPA_DIRECTPATH_TX_QUEUE_SIZE) || defined(CONFIG_LTQ_PPA_DIRECTPATH_TX_QUEUE_PKTS)
		    seq_printf(seq, "\t    skb_list         = %08x\n", (u32)info->skb_list);
#ifdef CONFIG_LTQ_PPA_DIRECTPATH_TX_QUEUE_SIZE
		    seq_printf(seq, "\t    skb_list_size    = %u\n", info->skb_list_size);
#else
		    seq_printf(seq, "\t    skb_list_len     = %u\n", info->skb_list_len);
#endif
#endif
		    seq_printf(seq, "\t    rx_fn_rxif_pkt   = %u\n", info->rx_fn_rxif_pkt);
		    seq_printf(seq, "\t    rx_fn_txif_pkt   = %u\n", info->rx_fn_txif_pkt);
		    seq_printf(seq, "\t    tx_pkt           = %u\n", info->tx_pkt);
		    seq_printf(seq, "\t    tx_pkt_dropped   = %u\n", info->tx_pkt_dropped);
		    seq_printf(seq, "\t    tx_pkt_queued    = %u\n", info->tx_pkt_queued);
		    seq_printf(seq, "\t    flags            = VALID");
		    if ( (info->flags & PPE_DIRECTPATH_DATA_RX_ENABLE) )
			    seq_printf(seq, " | RX_EN");
		    if ( (info->flags & PPE_DIRECTPATH_ETH) )
			    seq_printf(seq, " | ETH");
		    if ( (info->flags & PPE_DIRECTPATH_CORE0) )
			    seq_printf(seq, " | CPU0");
		    if ( (info->flags & PPE_DIRECTPATH_CORE1) )
			    seq_printf(seq, " | CPU1");
		    seq_printf(seq, "\n");
	    }

#else
        seq_printf(seq, "    callback\n");
#if defined(CONFIG_KALLSYMS) && defined(CONFIG_LTQ_PPA_API_PROC)
        if ( info->callback.stop_tx_fn && (name = kallsyms_lookup((unsigned long)info->callback.stop_tx_fn, &size, &offset, &modname, namebuf)) )
            seq_printf(seq, "      stop_tx_fn     = %s (%08x)\n", name, (u32)info->callback.stop_tx_fn);
        else
            seq_printf(seq, "      stop_tx_fn     = %08x\n", (u32)info->callback.stop_tx_fn);
        if ( info->callback.start_tx_fn && (name = kallsyms_lookup((unsigned long)info->callback.start_tx_fn, &size, &offset, &modname, namebuf)) )
            seq_printf(seq, "      start_tx_fn    = %s (%08x)\n", name, (u32)info->callback.start_tx_fn);
        else
            seq_printf(seq, "      start_tx_fn    = %08x\n", (u32)info->callback.start_tx_fn);
        if ( info->callback.rx_fn && (name = kallsyms_lookup((unsigned long)info->callback.rx_fn, &size, &offset, &modname, namebuf)) )
            seq_printf(seq, "      rx_fn          = %s (%08x)\n", name, (u32)info->callback.rx_fn);
        else
            seq_printf(seq, "      rx_fn          = %08x\n", (u32)info->callback.rx_fn);
#else
        seq_printf(seq,     "      stop_tx_fn     = %08x\n", (u32)info->callback.stop_tx_fn);
        seq_printf(seq,     "      start_tx_fn    = %08x\n", (u32)info->callback.start_tx_fn);
        seq_printf(seq,     "      rx_fn          = %08x\n", (u32)info->callback.rx_fn);
#endif
        if ( info->netif )
            seq_printf(seq, "    netif            = %s (%08x)\n", info->netif->name, (u32)info->netif);
        else
            seq_printf(seq, "    netif            = N/A\n");
        seq_printf(seq, "    ifid             = %d\n", (u32)info->ifid);
#if defined(CONFIG_LTQ_PPA_DIRECTPATH_TX_QUEUE_SIZE) || defined(CONFIG_LTQ_PPA_DIRECTPATH_TX_QUEUE_PKTS)
        seq_printf(seq, "    skb_list         = %08x\n", (u32)info->skb_list);
  #ifdef CONFIG_LTQ_PPA_DIRECTPATH_TX_QUEUE_SIZE
        seq_printf(seq, "    skb_list_size    = %u\n", info->skb_list_size);
  #else
        seq_printf(seq, "    skb_list_len     = %u\n", info->skb_list_len);
  #endif
#endif
        seq_printf(seq, "    rx_fn_rxif_pkt   = %u\n", info->rx_fn_rxif_pkt);
        seq_printf(seq, "    rx_fn_txif_pkt   = %u\n", info->rx_fn_txif_pkt);
        seq_printf(seq, "    tx_pkt           = %u\n", info->tx_pkt);
        seq_printf(seq, "    tx_pkt_dropped   = %u\n", info->tx_pkt_dropped);
        seq_printf(seq, "    tx_pkt_queued    = %u\n", info->tx_pkt_queued);
        seq_printf(seq, "    flags            = VALID");
        if ( (info->flags & PPE_DIRECTPATH_DATA_RX_ENABLE) )
            seq_printf(seq, " | RX_EN");
        if ( (info->flags & PPE_DIRECTPATH_ETH) )
            seq_printf(seq, " | ETH");
        if ( (info->flags & PPE_DIRECTPATH_CORE0) )
            seq_printf(seq, " | CPU0");
        if ( (info->flags & PPE_DIRECTPATH_CORE1) )
            seq_printf(seq, " | CPU1");
        seq_printf(seq, "\n");
#endif
    }
#if !(defined(CONFIG_LTQ_PPA_GRX500) && CONFIG_LTQ_PPA_GRX500)
    else
        seq_printf(seq, "    flags            = INVALID\n");
#endif

    return 0;
}

static int proc_read_directpath_seq_open(struct inode *inode, struct file *file)
{
    return seq_open(file, &g_proc_read_directpath_seq_ops);
}

static ssize_t proc_file_write_directpath(struct file *file, const char __user *buf, size_t count, loff_t *ppos)
{
    int len;
    char str[64];
    char *p;

//    int32_t ret;
    uint32_t start_ifid, end_ifid;
//    uint32_t ifid;
//    uint32_t flags;
//    int pos;
//    int f_register_netdev = 0;
//    int i;

    if ( !ppa_hook_directpath_register_dev_fn )
    {
        pr_err("PPA is not inited!\n");
        return count;
    }

    len = min(count, (size_t)sizeof(str) - 1);
    len -= ppa_copy_from_user(str, buf, len);
    while ( len && str[len - 1] <= ' ' )
        len--;
    str[len] = 0;
    for ( p = str; *p && *p <= ' '; p++, len-- );
    if ( !*p )
        return count;

    ppa_directpath_get_ifid_range(&start_ifid, &end_ifid);

    if ( stricmp(p, "clean") == 0 || stricmp(p, "clear") == 0 )
    {
        struct ppe_directpath_data *info;
        uint32_t pos;

        if ( ppa_directpath_data_start_iteration(&pos, &info) == PPA_SUCCESS )
        {
            do
            {
                if ( (info->flags & PPE_DIRECTPATH_DATA_ENTRY_VALID) )
                {
                    info->rx_fn_rxif_pkt    = 0;
                    info->rx_fn_txif_pkt    = 0;
                    info->tx_pkt            = 0;
                    info->tx_pkt_dropped    = 0;
                    info->tx_pkt_queued     = 0;
                }
            } while ( ppa_directpath_data_iterate_next(&pos, &info) == PPA_SUCCESS );
        }
        ppa_directpath_data_stop_iteration();
    }
    else if ( strincmp(p, "clean ", 6) == 0 || strincmp(p, "clear ", 6) == 0 )
    {
        struct ppe_directpath_data *info;
        uint32_t pos = 0;

        p += 6;
        for ( ; *p && *p <= ' '; p++ );

        if ( *p && ppa_directpath_data_start_iteration(&pos, &info) == PPA_SUCCESS )
        {
            do
            {
                if ( (info->flags & PPE_DIRECTPATH_DATA_ENTRY_VALID) && info->netif && strcmp(info->netif->name, p) == 0 )
                {
                    info->rx_fn_rxif_pkt    = 0;
                    info->rx_fn_txif_pkt    = 0;
                    info->tx_pkt            = 0;
                    info->tx_pkt_dropped    = 0;
                    info->tx_pkt_queued     = 0;
                }
            } while ( ppa_directpath_data_iterate_next(&pos, &info) == PPA_SUCCESS );
        }
        ppa_directpath_data_stop_iteration();
    }
    else{
    };

    return count;
}

#endif

#if defined(CONFIG_LTQ_PPA_API_SW_FASTPATH)
static int proc_read_swfpstatus(struct seq_file *seq, void *v)
{
  uint32_t status=0;
  if(ppa_get_sw_fastpath_status_hook)
	ppa_get_sw_fastpath_status_hook(&status,0);
  
  seq_printf(seq, "software fastpath is = %s\n", status?"Enabled":"Disabled");
  return 0;
}

static int proc_read_swfpstatus_seq_open(struct inode *inode, struct file *file)
{
  return single_open(file, proc_read_swfpstatus, NULL);
}

static ssize_t proc_write_swfpstatus(struct file *file, 
                                       const char __user *buf, 
                                       size_t count, 
                                       loff_t *ppos)
{
  int len;
  char str[64];
  char *cmd;
  uint32_t status=0;

  len = min(count, (size_t)(sizeof(str) - 1));
    
  len -= ppa_copy_from_user(str, buf, len);
 
  /* skip spaces */  
  while ( len && str[len - 1] <= ' ' )
    len--;
    
  str[len] = 0;
  for ( cmd = str; *cmd && (*cmd) <= ' '; cmd++, len-- );
  
  if( !(*cmd) )
    return count;

  if ( stricmp(cmd, "enable") == 0 ) {
    status=1;
  } else if ( stricmp(cmd, "disable") == 0 ) {
    status=0;
  } else {
    printk("echo enable/disable > /proc/ppa/api/sw_fastpath\n");
  }

  if(ppa_sw_fastpath_enable_hook) 
	ppa_sw_fastpath_enable_hook(status,0);

  return count;
}

#if IS_ENABLED(CONFIG_LTQ_PPA_SGA)
static int proc_read_sga_status(struct seq_file *seq, void *v)
{
  uint32_t status=0;
  if(ppa_sga_status_hook)
	ppa_sga_status_hook(&status, 0);
  
  seq_printf(seq, "PPA SGA is = %s\n", status ? "Enabled" : "Disabled");
  return 0;
}

static int proc_read_sga_status_seq_open(struct inode *inode, struct file *file)
{
  return single_open(file, proc_read_sga_status, NULL);
}

static ssize_t proc_write_sga_status(struct file *file, 
                                       const char __user *buf, 
                                       size_t count, 
                                       loff_t *ppos)
{
  int len;
  char str[64];
  char *cmd;
  uint32_t status=0;

  len = min(count, (size_t)(sizeof(str) - 1));
    
  len -= ppa_copy_from_user(str, buf, len);
 
  /* skip spaces */  
  while ( len && str[len - 1] <= ' ' )
    len--;
    
  str[len] = 0;
  for ( cmd = str; *cmd && (*cmd) <= ' '; cmd++, len-- );
  
  if( !(*cmd) )
    return -EFAULT;

  if ( stricmp(cmd, "enable") == 0 ) {
    status=1;
  } else if ( stricmp(cmd, "disable") == 0 ) {
    status=0;
  } else {
    printk("echo enable/disable > /proc/ppa/api/sga_hook\n");
    return -EFAULT;
  }

  if(ppa_sga_enable_hook) 
	ppa_sga_enable_hook(status, 0);

  return count;
}
#endif

#if defined(CONFIG_LTQ_PPA_TCP_LITEPATH) && CONFIG_LTQ_PPA_TCP_LITEPATH
static int proc_read_tcplp_status(struct seq_file *seq, void *v)
{
  uint32_t status=0;
  if(ppa_get_tcp_litepath_status_hook)
	ppa_get_tcp_litepath_status_hook(&status,0);
  
  seq_printf(seq, "TCP litpath is = %s\n", status?"Enabled":"Disabled");
  return 0;
}

static int proc_read_tcp_litepath_status_seq_open(struct inode *inode, struct file *file)
{
  return single_open(file, proc_read_tcplp_status, NULL);
}

static ssize_t proc_write_tcp_litepath_status(struct file *file, 
                                       const char __user *buf, 
                                       size_t count, 
                                       loff_t *ppos)
{
  int len;
  char str[64];
  char *cmd;
  uint32_t status=0;

  len = min(count, (size_t)(sizeof(str) - 1));
    
  len -= ppa_copy_from_user(str, buf, len);
 
  /* skip spaces */  
  while ( len && str[len - 1] <= ' ' )
    len--;
    
  str[len] = 0;
  for ( cmd = str; *cmd && (*cmd) <= ' '; cmd++, len-- );
  
  if( !(*cmd) )
    return count;

  if ( stricmp(cmd, "enable") == 0 ) {
    status=1;
  } else if ( stricmp(cmd, "disable") == 0 ) {
    status=0;
  } else {
    printk("echo enable/disable > /proc/ppa/api/tcp_litepath\n");
  }

  if(ppa_tcp_litepath_enable_hook) 
	ppa_tcp_litepath_enable_hook(status,0);

  return count;
}
#endif
#endif

static int proc_read_br_flow_learning(struct seq_file *seq, void *v)
{
  seq_printf(seq, "bridgef_flow_learning = %s\n", 
      ppa_session_bridged_flow_status()?"Enabled":"Disabled");
  return 0;
}

static int proc_file_br_flow_open(struct inode *inode, struct file *file)
{
  return single_open(file, proc_read_br_flow_learning, NULL);
}

static ssize_t proc_file_br_flow_write(struct file *file, 
                                       const char __user *buf, 
                                       size_t count, 
                                       loff_t *ppos)
{
  int len;
  char str[64];
  char *cmd;

  len = min(count, (size_t)(sizeof(str) - 1));
    
  len -= ppa_copy_from_user(str, buf, len);
 
  /* skip spaces */  
  while ( len && str[len - 1] <= ' ' )
    len--;
    
  str[len] = 0;
  for ( cmd = str; *cmd && (*cmd) <= ' '; cmd++, len-- );
  
  if( !(*cmd) )
    return count;

  if ( stricmp(cmd, "enable") == 0 ) {
    ppa_session_bridged_flow_set_status(1);
  } else if ( stricmp(cmd, "disable") == 0 ) {
    ppa_session_bridged_flow_set_status(0);
  } else {
    printk("echo enable/disable > /proc/ppa/api/bridged_flow_learning\n");
  }

  return count;
}

/*
 *  string process help function
 */

static int stricmp(const char *p1, const char *p2)
{
    int c1, c2;

    while ( *p1 && *p2 )
    {
        c1 = *p1 >= 'A' && *p1 <= 'Z' ? *p1 + 'a' - 'A' : *p1;
        c2 = *p2 >= 'A' && *p2 <= 'Z' ? *p2 + 'a' - 'A' : *p2;
        if ( (c1 -= c2) )
            return c1;
        p1++;
        p2++;
    }

    return *p1 - *p2;
}

static int strincmp(const char *p1, const char *p2, int n)
{
    int c1 = 0, c2;

    while ( n && *p1 && *p2 )
    {
        c1 = *p1 >= 'A' && *p1 <= 'Z' ? *p1 + 'a' - 'A' : *p1;
        c2 = *p2 >= 'A' && *p2 <= 'Z' ? *p2 + 'a' - 'A' : *p2;
        if ( (c1 -= c2) )
            return c1;
        p1++;
        p2++;
        n--;
    }

    return n ? *p1 - *p2 : c1;
}

static INLINE unsigned int get_number(char **p, int *len, int is_hex)
{
    unsigned int ret = 0;
    int n = 0;    

    ppa_debug(DBG_ENABLE_MASK_DEBUG_PRINT,"enter get_number\n");
    if ( (*p)[0] == '0' && (*p)[1] == 'x' )
    {
        is_hex = 1;
        (*p) += 2;
        (*len) -= 2;
    }

    if ( is_hex )
    {
        while ( *len && ((**p >= '0' && **p <= '9') || (**p >= 'a' && **p <= 'f') || (**p >= 'A' && **p <= 'F')) )
        {
            if ( **p >= '0' && **p <= '9' )
                n = **p - '0';
            else if ( **p >= 'a' && **p <= 'f' )
               n = **p - 'a' + 10;
            else if ( **p >= 'A' && **p <= 'F' )
                n = **p - 'A' + 10;
            ret = (ret << 4) | n;
            (*p)++;
            (*len)--;
        }
    }
    else
    {
        while ( *len && **p >= '0' && **p <= '9' )
        {
            n = **p - '0';
            ret = ret * 10 + n;
            (*p)++;
            (*len)--;
        }
    }
    
    return ret;
}

static INLINE int get_token(char **p1, char **p2, int *len, int *colon)
{
    int tlen = 0;

    while ( *len && !((**p1 >= 'A' && **p1 <= 'Z') || (**p1 >= 'a' && **p1<= 'z') || (**p1 >= '0' && **p1<= '9')) )
    {
        (*p1)++;
        (*len)--;
    }
    if ( !*len )
        return 0;

    if ( *colon )
    {
        *colon = 0;
        *p2 = *p1;
        while ( *len && **p2 > ' ' && **p2 != ',' )
        {
            if ( **p2 == ':' )
            {
                *colon = 1;
                break;
            }
            (*p2)++;
            (*len)--;
            tlen++;
        }
        **p2 = 0;
    }
    else
    {
        *p2 = *p1;
        while ( *len && **p2 > ' ' && **p2 != ',' )
        {
            (*p2)++;
            (*len)--;
            tlen++;
        }
        **p2 = 0;
    }

    return tlen;
}

static INLINE void ignore_space(char **p, int *len)
{
    while ( *len && (**p <= ' ' || **p == ':' || **p == '.' || **p == ',') )
    {
        (*p)++;
        (*len)--;
    }
}

/*
 * ####################################
 *           Global Function
 * ####################################
 */



/*
 * ####################################
 *           Init/Cleanup API
 * ####################################
 */

void ppa_api_proc_file_create(void)
{
    struct proc_dir_entry *res;
    uint32_t f_incorrect_fw = 1;
    int i;
    PPA_VERSION ver={0};

    ver.index = 1;
    if( ppa_drv_get_firmware_id(&ver, 0) != PPA_SUCCESS)
    {
        ver.index = 0;
        ppa_drv_get_firmware_id(&ver, 0);
    }
    switch ( ver.family )
    {
    case 1: //  Danube
    case 2: //  Twinpass
    case 3: //  Amazon-SE
        g_str_dest[0] = "ETH0";
        g_str_dest[2] = "CPU0";
        g_str_dest[3] = "EXT_INT1";
        g_str_dest[4] = "EXT_INT2";
        g_str_dest[5] = "EXT_INT3";
        g_str_dest[6] = "EXT_INT4";
        g_str_dest[7] = "EXT_INT5";
        if ( ver.itf == 1        //  D4
            && ver.family != 3)
        {
            g_str_dest[1] = "ETH1";
            f_incorrect_fw = 0;
        }
        else if ( ver.itf == 2 ) //  A4
        {
            g_str_dest[1] = "ATM";
            f_incorrect_fw = 0;
        }
        break;
    case 5: //  AR9
    case 6: //  GR9
        g_str_dest[0] = "ETH0";
        g_str_dest[1] = "ETH1";
        g_str_dest[2] = "CPU0";
        g_str_dest[3] = "EXT_INT1";
        g_str_dest[4] = "EXT_INT2";
        g_str_dest[5] = "EXT_INT3";
        if ( ver.itf == 1 )      //  D5
        {
            g_str_dest[6] = "EXT_INT4";
            g_str_dest[7] = "EXT_INT5";
            f_incorrect_fw = 0;
        }
        else if ( ver.itf == 4 ) //  A5
        {
            g_str_dest[6] = "ATM_res";
            g_str_dest[7] = "ATM";
            f_incorrect_fw = 0;
        }
    case 7: //  VR9
        g_str_dest[0] = "ETH0";
        g_str_dest[1] = "ETH1";
        g_str_dest[2] = "CPU0";
        g_str_dest[3] = "EXT_INT1";
        g_str_dest[4] = "EXT_INT2";
        g_str_dest[5] = "EXT_INT3";
        if ( ver.itf == 1 )      //  D5
        {
            g_str_dest[6] = "EXT_INT4";
            g_str_dest[7] = "EXT_INT5";
            f_incorrect_fw = 0;
        }
        else if ( ver.itf == 4 ) //  A5
        {
            g_str_dest[6] = "ATM_res";
            g_str_dest[7] = "ATM";
            f_incorrect_fw = 0;
        }
        else if ( ver.itf == 5 ) //  E5
        {
            g_str_dest[6] = "PTM_res";
            g_str_dest[7] = "PTM";
            f_incorrect_fw = 0;
        }
    }
    if ( f_incorrect_fw )
    {
        for ( i = 0; i < NUM_ENTITY(g_str_dest); i++ )
            g_str_dest[i] = "INVALID";
    }

    if(!g_ppa_proc_dir_flag) {
	g_ppa_proc_dir = proc_mkdir("ppa", NULL);
	g_ppa_proc_dir_flag = 1;
    }

    g_ppa_api_proc_dir = proc_mkdir("api", g_ppa_proc_dir);
    g_ppa_api_proc_dir_flag = 1;
    
#ifdef CONFIG_LTQ_PPA_API_DIRECTPATH
#if defined(CONFIG_LTQ_PPA_GRX500) && CONFIG_LTQ_PPA_GRX500
#if defined(CONFIG_LTQ_PPA_COC_SUPPORT)
    if(!g_ppa_api_coc_proc_dir_flag) {
	g_ppa_api_coc_proc_dir = proc_mkdir("coc", g_ppa_api_proc_dir);
	g_ppa_api_coc_proc_dir_flag = 1;
    }
#endif
#endif
#endif
#if IS_ENABLED(CONFIG_LTQ_PPA_GRX500) && IS_ENABLED(CONFIG_LTQ_PPA_QOS)
    res = proc_create("class2prio",
                            S_IRUGO|S_IWUSR,
                            g_ppa_api_proc_dir,
			    &g_proc_file_classprio_seq_fops);
    res = proc_create("inggrp",
                            S_IRUGO|S_IWUSR,
                            g_ppa_api_proc_dir,
			    &g_proc_file_inggrp_seq_fops);
#endif
    res = proc_create("dbg",
                            S_IRUGO|S_IWUSR,
                            g_ppa_api_proc_dir,
			    &g_proc_file_dbg_seq_fops);
    res = proc_create("hook",
                            S_IRUGO|S_IWUSR,
                            g_ppa_api_proc_dir,
			    &g_proc_file_hook_seq_fops);

	res = proc_create("filter", S_IRUGO|S_IWUSR, g_ppa_api_proc_dir, &g_proc_file_filter_seq_fops);

	res = proc_create("queue_per_port", S_IRUGO|S_IWUSR, g_ppa_api_proc_dir, &g_proc_file_queue_per_port_seq_fops);

	res = proc_create("mini_session", S_IRUGO, g_ppa_api_proc_dir, &g_proc_file_mini_session_seq_fops);

    res = proc_create("phys_port",
                            S_IRUGO,
                            g_ppa_api_proc_dir,
			    &g_proc_file_phys_port_seq_fops);
    res = proc_create("netif",
                            S_IRUGO|S_IWUSR,
                            g_ppa_api_proc_dir,
			    &g_proc_file_netif_seq_fops);
    res = proc_create("session",
                            S_IRUGO,
                            g_ppa_api_proc_dir,
			    &g_proc_file_session_seq_fops);
#ifdef CONFIG_LTQ_PPA_API_DIRECTPATH
    res = proc_create("directpath",
                            S_IRUGO|S_IWUSR,
                            g_ppa_api_proc_dir,
			    &g_proc_file_directpath_seq_fops);
#endif
#if defined(CONFIG_LTQ_PPA_HANDLE_CONNTRACK_SESSIONS)
    res = proc_create("sess-mgmt",
                            S_IRUGO|S_IWUSR,
                            g_ppa_api_proc_dir,
			    &g_proc_file_sess_mgmt_seq_fops);
#endif

#if defined(CONFIG_LTQ_PPA_API_SW_FASTPATH)
    res = proc_create("sw_fastpath",
                            S_IRUGO|S_IWUSR,
                            g_ppa_api_proc_dir,
			    &g_proc_file_swfp_status);
#if IS_ENABLED(CONFIG_LTQ_PPA_SGA)
    res = proc_create("sga_hook",
                            S_IRUGO|S_IWUSR,
                            g_ppa_api_proc_dir,
			    &g_proc_file_sga_status);
#endif
#if defined(CONFIG_LTQ_PPA_TCP_LITEPATH) && CONFIG_LTQ_PPA_TCP_LITEPATH
    res = proc_create("tcp_litepath",
                            S_IRUGO|S_IWUSR,
                            g_ppa_api_proc_dir,
			    &g_proc_file_tcp_litepath_status);
#endif
#endif

    res = proc_create("bridged_flow_learning",
                            S_IRUGO|S_IWUSR,
                            g_ppa_api_proc_dir,
			    &g_proc_file_br_flow_learning);
#ifdef CONFIG_LTQ_PPA_API_DIRECTPATH
#if defined(CONFIG_LTQ_PPA_GRX500) && CONFIG_LTQ_PPA_GRX500
#if defined(CONFIG_LTQ_PPA_COC_SUPPORT)
    res = proc_create("window",
                            S_IRUGO|S_IWUSR,
                            g_ppa_api_coc_proc_dir,
			    &g_proc_file_window_seq_fops);
    res = proc_create("threshold",
                            S_IRUGO|S_IWUSR,
                            g_ppa_api_coc_proc_dir,
			    &g_proc_file_threshold_seq_fops);
#endif
#endif
#endif

}

void ppa_api_proc_file_destroy(void)
{
#ifdef CONFIG_LTQ_PPA_API_DIRECTPATH
    remove_proc_entry("directpath",
                      g_ppa_api_proc_dir);
#if defined(CONFIG_LTQ_PPA_GRX500) && CONFIG_LTQ_PPA_GRX500
#if defined(CONFIG_LTQ_PPA_COC_SUPPORT)
    remove_proc_entry("window",
                      g_ppa_api_coc_proc_dir);
    remove_proc_entry("threshold",
                      g_ppa_api_coc_proc_dir);
    if ( g_ppa_api_coc_proc_dir_flag )
    {
        remove_proc_entry("coc",
                          g_ppa_api_proc_dir);
        g_ppa_api_coc_proc_dir = NULL;
        g_ppa_api_coc_proc_dir_flag = 0;
    }
#endif
#endif
#endif

    remove_proc_entry("session",
                      g_ppa_api_proc_dir);

    remove_proc_entry("netif",
                      g_ppa_api_proc_dir);

    remove_proc_entry("phys_port",
                      g_ppa_api_proc_dir);

    remove_proc_entry("hook",
                      g_ppa_api_proc_dir);

	remove_proc_entry("filter", g_ppa_api_proc_dir);

	remove_proc_entry("queue_per_port", g_ppa_api_proc_dir);

	remove_proc_entry("mini_session", g_ppa_api_proc_dir);

#if defined(CONFIG_LTQ_PPA_API_SW_FASTPATH)
    remove_proc_entry("sw_fastpath",
                            g_ppa_api_proc_dir);
#if defined(CONFIG_LTQ_PPA_TCP_LITEPATH) && CONFIG_LTQ_PPA_TCP_LITEPATH
    remove_proc_entry("tcp_litepath",
                            g_ppa_api_proc_dir);
#endif
#endif

#if defined(CONFIG_LTQ_PPA_GRX500) && CONFIG_LTQ_PPA_GRX500
    remove_proc_entry("inggrp",
		      g_ppa_api_proc_dir);
    remove_proc_entry("class2prio",
		      g_ppa_api_proc_dir);
#endif
#if defined(CONFIG_LTQ_PPA_HANDLE_CONNTRACK_SESSIONS)
    remove_proc_entry("sess-mgmt",
                      g_ppa_api_proc_dir);
#endif
    remove_proc_entry("bridged_flow_learning", g_ppa_api_proc_dir); 
    remove_proc_entry("dbg",
                      g_ppa_api_proc_dir);
    if ( g_ppa_api_proc_dir_flag )
    {
        remove_proc_entry("api",
                          g_ppa_proc_dir);
        g_ppa_api_proc_dir = NULL;
        g_ppa_api_proc_dir_flag = 0;
    }
#if 0
    if ( g_ppa_proc_dir_flag )
    {
        remove_proc_entry("ppa", NULL);
        g_ppa_proc_dir = NULL;
        g_ppa_proc_dir_flag = 0;
    }
#endif
}
