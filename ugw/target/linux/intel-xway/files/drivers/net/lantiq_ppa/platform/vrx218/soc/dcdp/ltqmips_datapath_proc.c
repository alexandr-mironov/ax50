#include <linux/module.h>
#include <net/datapath_proc_api.h>	/*for proc api */
#include <net/datapath_api.h>

#include "datapath.h"

#define DP_PROC_NAME			"dp"
#define DP_PROC_BASE			"/proc/"DP_PROC_NAME"/"
#define DP_PROC_PARENT			""

#define DP_PROC_FILE_DBG		"dbg"
#define DP_PROC_FILE_PORT		"ports"
#define DP_PROC_FILE_IFSTATS		"if_stats"
#define DP_PROC_FILE_IFSTATS_CPU	"if_stats_cpu"
#define DP_PROC_FILE_IFSTATS_ACCEL	"if_stats_accel"

static void proc_dbg_read(struct seq_file *s);
static ssize_t proc_dbg_write(struct file *, const char *, size_t, loff_t *);
static void proc_ports_dump(struct seq_file *s);

static void proc_ifstats_read(struct seq_file *s);
static ssize_t proc_ifstats_write(struct file *file, const char *buf,
				size_t count, loff_t *ppos);

static void proc_ifstats_cpu_read(struct seq_file *s);
static ssize_t proc_ifstats_cpu_write(struct file *file, const char *buf,
				size_t count, loff_t *ppos);

static void proc_ifstats_accel_read(struct seq_file *s);
static ssize_t proc_ifstats_accel_write(struct file *file, const char *buf,
				size_t count, loff_t *ppos);

extern unsigned int dp_dbg_flag;

static struct dp_proc_entry dp_proc_entries[] = {
	/*name single_callback_t multi_callback_t/_start write_callback_t */
	{DP_PROC_FILE_DBG, proc_dbg_read, NULL, NULL, proc_dbg_write},
	{DP_PROC_FILE_PORT, proc_ports_dump, NULL, NULL, NULL},
	{DP_PROC_FILE_IFSTATS, proc_ifstats_read, NULL, NULL, proc_ifstats_write},
	{DP_PROC_FILE_IFSTATS_CPU, proc_ifstats_cpu_read, NULL, NULL, proc_ifstats_cpu_write},
	{DP_PROC_FILE_IFSTATS_ACCEL, proc_ifstats_accel_read, NULL, NULL, proc_ifstats_accel_write},

	/*the last place holder*/
	{NULL, NULL, NULL, NULL, NULL}
};
static struct proc_dir_entry *dp_proc_node;

struct proc_dir_entry *dp_proc_install(struct proc_dir_entry *parent_proc_dir)
{

	dp_proc_node = proc_mkdir(DP_PROC_PARENT DP_PROC_NAME, parent_proc_dir);

	if (dp_proc_node != NULL) {
		int i;

		for (i = 0; i < ARRAY_SIZE(dp_proc_entries); i++)
			dp_proc_entry_create(dp_proc_node,
					     &dp_proc_entries[i]);
	} else {
		DP_ERROR("cannot create proc entry");
		return NULL;
	}

	return dp_proc_node;
}

void dp_proc_remove(void)
{
	proc_remove(dp_proc_node);
}
static void proc_ports_dump(struct seq_file *m)
{
	int i,j;
	struct pmac_port_info *p;
	struct dp_subif_info *s;

	for (i = 0; i < DP_MAX_PORT_IDX; i++) {
		p = &dp_port_info[i];

		seq_printf(m, "[%d]: [%s]\n", i, p->dev ? p->dev->name : "no device");
		seq_printf(m, "============================\n");
		seq_printf(m, "status:          [%s][%d]\n", dp_port_status_str[p->status], p->status);
		seq_printf(m, "alloc_flags:     [0x%x]\n", p->alloc_flags); 
		if (p->dev) {
			seq_printf(m, "dev->name  [%s]\n", p->dev->name);
		}
		seq_printf(m, "dev_port         [%d]\n", p->dev_port);
		seq_printf(m, "tx_err_drop      [%d]\n", p->tx_err_drop);
		seq_printf(m, "rx_err_drop      [%d]\n", p->rx_err_drop);
		seq_printf(m, "num_subif        [%d]\n", p->num_subif);
		for (j = 0; j < MAX_SUBIF_PER_PORT; j++) {
			s = &p->subif_info[j];
			if (s->flags == SUBIF_FREE)
				continue;
			seq_printf(m, "\n");
			seq_printf(m, "\t[%d]: [%s]\n", j, s->device_name);
			seq_printf(m, "\t============================\n");
			seq_printf(m, "\tflags            [%s]\n", dp_subif_status_str[s->flags]);
			seq_printf(m, "\tsubif            [0x%x]\n", s->subif);
			seq_printf(m, "\tvap              [%d]\n", get_vap(s->subif));
			if (s->netif) {
				seq_printf(m, "\tdev->name  [%s]\n", s->netif->name);
			}
		}
		seq_printf(m, "\n");
	}
}

static void proc_dbg_read(struct seq_file *s)
{
	int i;

	seq_printf(s, "dp_dbg_flag=0x%08x\n", dp_dbg_flag);
	seq_printf(s, "Supported Flags =%d\n",
		   get_dp_dbg_flag_str_size());
	seq_printf(s, "Enabled Flags(0x%0x):", dp_dbg_flag);

	for (i = 0; i < get_dp_dbg_flag_str_size(); i++)
		if ((dp_dbg_flag & dp_dbg_flag_list[i]) ==
		    dp_dbg_flag_list[i])
			seq_printf(s, "%s ", dp_dbg_flag_str[i]);

	seq_printf(s, "\n\n");
}

static ssize_t proc_dbg_write(struct file *file, const char *buf, size_t count,
		       loff_t *ppos)
{
	int len, i, j;
	char str[64];
	int num;
	char *param_list[20];
	int f_enable;

	len = (sizeof(str) > count) ? count : sizeof(str) - 1;
	len -= copy_from_user(str, buf, len);
	str[len] = 0;
	num = dp_split_buffer(str, param_list, ARRAY_SIZE(param_list));

	if (dp_strcmpi(param_list[0], "enable") == 0)
		f_enable = 1;
	else if (dp_strcmpi(param_list[0], "disable") == 0)
		f_enable = -1;
	else
		goto help;

	if (!param_list[1]) {	/*no parameter after enable or disable */
		set_ltq_dbg_flag(dp_dbg_flag, f_enable, -1);
		goto EXIT;
	}

	for (i = 1; i < num; i++) {
		for (j = 0; j < get_dp_dbg_flag_str_size(); j++) {
			if (dp_strcmpi(param_list[i],
				       dp_dbg_flag_str[j]) == 0) {
				set_ltq_dbg_flag(dp_dbg_flag,
						 f_enable, dp_dbg_flag_list[j]);
				break;
			}
		}
	}

EXIT:
	return count;
help:
	pr_info("echo <enable/disable> ");

	for (i = 0; i < get_dp_dbg_flag_str_size(); i++)
		pr_info("%s ", dp_dbg_flag_str[i]);

	pr_info(" > /proc/dp/dbg\n");
	
	return count;
}

static void __maybe_unused dp_send_packet(u8 *pdata, int len, char *devname, u32 flag)
{
	struct sk_buff *skb;
	dp_subif_t subif = {0};

	skb = alloc_skb(len + 8, GFP_ATOMIC);

	if (unlikely(!skb)) {
		DP_ERROR("allocate skb fail\n");
		return;
	}

	skb->DW0 = 0;
	skb->DW1 = 0;
	skb->DW2 = 0;
	skb->DW3 = 0;
	memcpy(skb->data, pdata, len);
	skb->len = len;
	skb_put(skb, skb->len);
	skb->dev = dev_get_by_name(&init_net, devname);

	if (dp_get_netif_subifid(skb->dev, skb, NULL, skb->data, &subif, 0)) {
		DP_ERROR("dp_get_netif_subifid failed for %s\n", skb->dev->name);
		dev_kfree_skb_any(skb);
		return;
	}

	((struct dma_tx_desc_1 *) & (skb->DW1))->field.ep = subif.port_id;
	((struct dma_tx_desc_0 *) & (skb->DW0))->field.dest_sub_if_id = subif.subif;
	dp_xmit(skb->dev, &subif, skb, skb->len, flag);
}

static u8 __maybe_unused ipv4_plain_udp[] = {
	0x00, 0x00, 0x01, 0x00, 0x00, 0x01,  /*mac*/
	0x00, 0x10, 0x94, 0x00, 0x00, 0x02,
	0x08, 0x00, /*type*/
	0x45, 0x00, 0x00, 0x3E, 0x00, 0x00, 0x00, 0x00, 0xFF, 0x11, /*ip header*/
	0x3A, 0x56, 0xC0, 0x55, 0x01, 0x02, 0xC0, 0x00, 0x00, 0x01,
	0x04, 0x00, 0x00, 0x00, 0x00, 0x2A, 0x7A, 0x41, 0x00, 0x00, /*udp header*/
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00
};
static u8 __maybe_unused ipv4_plain_tcp[] = {
	0x00, 0x00, 0x01, 0x00, 0x00, 0x01, /*mac*/
	0x00, 0x10, 0x94, 0x00, 0x00, 0x02,
	0x08, 0x00,  /*type*/
	0x45, 0x00, 0x00, 0x3E, 0x00, 0x00, 0x00, 0x00, 0xFF, 0x06, /*ip header*/
	0x3A, 0x61, 0xC0, 0x55, 0x01, 0x02, 0xC0, 0x00, 0x00, 0x01,
	0x04, 0x00, 0x04, 0x00, 0x00, 0x01, 0xE2, 0x40, 0x00, 0x03, /*tcp header*/
	0x94, 0x47, 0x50, 0x10, 0x10, 0x00, 0x9F, 0xD9, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00
};

static u8 __maybe_unused ipv6_plain_udp[] = {
	0x00, 0x00, 0x01, 0x00, 0x00, 0x01,  /*mac*/
	0x00, 0x10, 0x94, 0x00, 0x00, 0x02,
	0x86, 0xDD, /*type*/
	0x60, 0x00, 0x00, 0x00, 0x00, 0x3E, 0x11, 0xFF, 0x20, 0x00, /*ip header*/
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x02, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01,
	0x04, 0x00, 0x00, 0x00, 0x00, 0x3E, 0xBB, 0x6F, 0x00, 0x00, /*udp header*/
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00
};
static u8 __maybe_unused ipv6_plain_tcp[] = {
	0x00, 0x00, 0x01, 0x00, 0x00, 0x01, /*mac*/
	0x00, 0x10, 0x94, 0x00, 0x00, 0x02,
	0x86, 0xDD, /*type*/
	0x60, 0x00, 0x00, 0x00, 0x00, 0x46, 0x06, 0xFF, 0x20, 0x00, /*ip header*/
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x02, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01,
	0x04, 0x00, 0x04, 0x00, 0x00, 0x01, 0xE2, 0x40, 0x00, 0x03, /*tcp header*/
	0x94, 0x47, 0x50, 0x10, 0x10, 0x00, 0xE1, 0x13, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /*data*/
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

static u8 __maybe_unused ipv6_extensions_udp[] = {
	0x00, 0x00, 0x01, 0x00, 0x00, 0x01,/*mac*/
	0x00, 0x10, 0x94, 0x00, 0x00, 0x02,
	0x86, 0xDD,/*type*/
	0x60, 0x00, 0x00, 0x00, 0x00, 0x8E, 0x00, 0xFF, 0x20, 0x00, /*ip header*/
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x02, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01,
	0x3C, 0x00, 0x01, 0x04, 0x00, 0x00, 0x00, 0x00,/*next extension:hop*/
	0x2B, 0x00, 0x01, 0x04, 0x00, 0x00, 0x00, 0x00,/*next extension:Destination*/
	0x11, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,/*next extension:Routing*/
	0x04, 0x00, 0x00, 0x00, 0x00, 0x76, 0xBA, 0xFF, 0x00, 0x00, /*udp header*/
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};
static u8 __maybe_unused ipv6_extensions_tcp[] = {
	0x00, 0x00, 0x01, 0x00, 0x00, 0x01, /*mac*/
	0x00, 0x10, 0x94, 0x00, 0x00, 0x02,
	0x86, 0xDD, /*type*/
	0x60, 0x00, 0x00, 0x00, 0x00, 0x8E, 0x00, 0xFF, 0x20, 0x00, /*ip header*/
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x02, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01,
	0x3C, 0x00, 0x01, 0x04, 0x00, 0x00, 0x00, 0x00, /*next extension:hop*/
	0x2B, 0x00, 0x01, 0x04, 0x00, 0x00, 0x00, 0x00, /*next extension:Destination*/
	0x06, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /*next extension:Routing*/
	0x04, 0x00, 0x04, 0x00, 0x00, 0x01, 0xE2, 0x40, 0x00, 0x03, /*tcp header*/
	0x94, 0x47, 0x50, 0x10, 0x10, 0x00, 0xE0, 0xE3, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

static u8 __maybe_unused rd6_ip4_ip6_udp[] = {
	0x00, 0x00, 0x01, 0x00, 0x00, 0x01, /*mac*/
	0x00, 0x10, 0x94, 0x00, 0x00, 0x02,
	0x08, 0x00, /*type*/
	0x45, 0x00, 0x00, 0x6E, 0x00, 0x00, 0x00, 0x00, 0xFF, 0x29, /*ip4 header*/
	0x3A, 0x0E, 0xC0, 0x55, 0x01, 0x02, 0xC0, 0x00, 0x00, 0x01,
	0x60, 0x00, 0x00, 0x00, 0x00, 0x32, 0x11, 0xFF, 0x20, 0x00, /*ip6 header*/
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x02, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01,
	0x04, 0x00, 0x00, 0x00, 0x00, 0x32, 0xBB, 0x87, 0x00, 0x00, /*udp header*/
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};
static u8 __maybe_unused rd6_ip4_ip6_tcp[] = {
	0x00, 0x00, 0x01, 0x00, 0x00, 0x01,/*mac*/
	0x00, 0x10, 0x94, 0x00, 0x00, 0x02,
	0x08, 0x00, /*type*/
	0x45, 0x00, 0x00, 0x6E, 0x00, 0x00, 0x00, 0x00, 0xFF, 0x29, /*ip4 header*/
	0x3A, 0x0E, 0xC0, 0x55, 0x01, 0x02, 0xC0, 0x00, 0x00, 0x01,
	0x60, 0x00, 0x00, 0x00, 0x00, 0x32, 0x06, 0xFF, 0x20, 0x00, /*ip6 header*/
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x02, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01,
	0x04, 0x00, 0x04, 0x00, 0x00, 0x01, 0xE2, 0x40, 0x00, 0x03, /*tcp header*/
	0x94, 0x47, 0x50, 0x10, 0x10, 0x00, 0xE1, 0x27, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};
static u8 __maybe_unused dslite_ip6_ip4_udp[] = {
	0x00, 0x00, 0x01, 0x00, 0x00, 0x01, /*mac*/
	0x00, 0x10, 0x94, 0x00, 0x00, 0x02,
	0x86, 0xDD, /*type*/
	0x60, 0x00, 0x00, 0x00, 0x00, 0x46, 0x04, 0xFF, 0x20, 0x00, /*ip6 header*/
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x02, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01,
	0x45, 0x00, 0x00, 0x46, 0x00, 0x00, 0x00, 0x00, 0xFF, 0x11, /*ip4 header*/
	0x3A, 0x4E, 0xC0, 0x55, 0x01, 0x02, 0xC0, 0x00, 0x00, 0x01,
	0x04, 0x00, 0x00, 0x00, 0x00, 0x32, 0x7A, 0x31, 0x00, 0x00, /*udp header*/
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

static u8 __maybe_unused dslite_ip6_ip4_tcp[] = {
	0x00, 0x00, 0x01, 0x00, 0x00, 0x01,/*mac*/
	0x00, 0x10, 0x94, 0x00, 0x00, 0x02,
	0x86, 0xDD, /*type*/
	0x60, 0x00, 0x00, 0x00, 0x00, 0x46, 0x04, 0xFF, 0x20, 0x00,  /*ip6 header*/
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x02, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01,
	0x45, 0x00, 0x00, 0x46, 0x00, 0x00, 0x00, 0x00, 0xFF, 0x06, /*ip4 header*/
	0x3A, 0x59, 0xC0, 0x55, 0x01, 0x02, 0xC0, 0x00, 0x00, 0x01,
	0x04, 0x00, 0x04, 0x00, 0x00, 0x01, 0xE2, 0x40, 0x00, 0x03, /*tcp header*/
	0x94, 0x47, 0x50, 0x10, 0x10, 0x00, 0x9F, 0xD1, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

static void seq_print_if_stats(struct seq_file *m,
			   struct rtnl_link_stats64 *if_stats)
{
	seq_printf(m, "\trx_packets:         [%12llu]\n", if_stats->rx_packets);
	seq_printf(m, "\trx_bytes:           [%12llu]\n", if_stats->rx_bytes);
	seq_printf(m, "\trx_dropped:         [%12llu]\n", if_stats->rx_dropped);
	seq_printf(m, "\ttx_packets:         [%12llu]\n", if_stats->tx_packets);
	seq_printf(m, "\ttx_bytes:           [%12llu]\n", if_stats->tx_bytes);
	seq_printf(m, "\ttx_dropped:         [%12llu]\n", if_stats->tx_dropped);
	seq_printf(m, "\tmulticast:          [%12llu]\n", if_stats->multicast);
}

static void proc_ifstats_all_read(struct seq_file *m, uint32_t flags)
{
	int i,j, ret = DP_SUCCESS;
	struct pmac_port_info *p;
	struct dp_subif_info *s;
	struct rtnl_link_stats64 if_stats;

	for (i = 1; i < DP_MAX_PORTS; i++) {
		p = &dp_port_info[i];

		if (p->status < PORT_DEV_REGISTERED)
			continue;

		seq_printf(m, "[%d]: [%s]\n", i, p->dev ? p->dev->name : "no device");
		seq_printf(m, "============================\n");
		seq_printf(m, "\n");

		for (j = 0; j < MAX_SUBIF_PER_PORT; j++) {
			s = &p->subif_info[j];

			if (s->flags == SUBIF_FREE)
				continue;

			memset(&if_stats, 0, sizeof(if_stats));

			ret = dp_get_netif_stats(s->netif, NULL, &if_stats, flags);

			seq_printf(m, "\t[%d]: [%s]\n", j, s->device_name);
			seq_printf(m, "\t==================================\n");
			if (!ret)
				seq_print_if_stats(m, &if_stats);
			else
				seq_printf(m, "\tfailed to get stats\n");
			seq_printf(m, "\n");
		}
		seq_printf(m, "\n");
	}
}

static ssize_t proc_ifstats_all_write(struct file *file, const char *buf,
				size_t count, loff_t *ppos, uint32_t flags)
{
	unsigned char tmp[32];
	int cmd;
	struct pmac_port_info *p;
	struct dp_subif_info *s;
	int i,j;

	if (count > 32)
		return -EINVAL;

	if (copy_from_user(tmp, buf, count))
		return -EFAULT;

	sscanf(tmp, "%d", &cmd);


	if (cmd != 0)
		return -EINVAL;

	for (i = 1; i < DP_MAX_PORTS; i++) {
		p = &dp_port_info[i];

		if (p->status < PORT_DEV_REGISTERED)
			continue;

		for (j = 0; j < MAX_SUBIF_PER_PORT; j++) {
			s = &p->subif_info[j];

			if (s->flags == SUBIF_FREE)
				continue;

			dp_clear_netif_stats(s->netif, NULL, flags);
		}
	}
	return count;
}

static void proc_ifstats_accel_read(struct seq_file *s)
{
	return proc_ifstats_all_read(s, DP_STATS_ACCEL);
}

static ssize_t proc_ifstats_accel_write(struct file *file, const char *buf,
					size_t count, loff_t *ppos)
{
	return proc_ifstats_all_write(file, buf, count, ppos, DP_STATS_ACCEL);
}
static void proc_ifstats_cpu_read(struct seq_file *s)
{
	return proc_ifstats_all_read(s, DP_STATS_CPU);
}

static ssize_t proc_ifstats_cpu_write(struct file *file, const char *buf,
					size_t count, loff_t *ppos)
{
	return proc_ifstats_all_write(file, buf, count, ppos, DP_STATS_CPU);
}

static void proc_ifstats_read(struct seq_file *s)
{
	return proc_ifstats_all_read(s, DP_STATS_ALL);
}

static ssize_t proc_ifstats_write(struct file *file, const char *buf,
				size_t count, loff_t *ppos)
{
	return proc_ifstats_all_write(file, buf, count, ppos, DP_STATS_ALL);
}
