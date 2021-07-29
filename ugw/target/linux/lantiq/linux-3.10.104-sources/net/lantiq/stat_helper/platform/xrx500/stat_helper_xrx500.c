#include <linux/netdevice.h>
#include <linux/if_arp.h>
#include <linux/if.h>

#include <net/ppa_api.h>

#include "../stat_helper_platform.h"
#include "stat_helper_xrx500.h"

struct rtnl_link_stats64*
stat_helper_platform_dev_get_extended_stats64(struct net_device *dev,
									 struct rtnl_link_stats64 *storage)
{
	stat_helper_dev_stats64_t stats;
	PPA_NETIF_ACCEL_STATS ppa_stats;

	/* Loopback, or any other Unknown interface */
	if ( (dev->type == ARPHRD_LOOPBACK) || (dev->type == ARPHRD_NONE) || (dev->type == ARPHRD_VOID) ) {
		return storage;
	}


	if( (_stat_helper_is_ptmwan_basedev(dev)) || (_stat_helper_is_ethwan_basedev(dev)) ||
		_stat_helper_is_wlan_basedev(dev) ){
		return storage;
	}


	/* Upper layer interface, such as PPP, Dslite, 6RD, VLAN, Bridge, MACVLAN etc. */
	if (_stat_helper_is_upper_layer_dev(dev)) {
		/* NOTE : Linux driver maintains only MIPS counters */

#if (defined(CONFIG_LTQ_PPA_API) || defined(CONFIG_LTQ_PPA_API_MODULE))

		memset(&ppa_stats, 0, sizeof(PPA_NETIF_ACCEL_STATS));

		/* get PPA HW and SW accelerated session stats */
		if (ppa_hook_get_netif_accel_stats_fn) {
			ppa_hook_get_netif_accel_stats_fn(dev->name, &ppa_stats, (PPA_F_NETIF_HW_ACCEL | PPA_F_NETIF_SW_ACCEL));
		}

		/* add with ppa HW and SW accelerated stats */
		storage->rx_bytes += ppa_stats.hw_accel_stats.rx_bytes + ppa_stats.sw_accel_stats.rx_bytes;
		storage->tx_bytes += ppa_stats.hw_accel_stats.tx_bytes + ppa_stats.sw_accel_stats.tx_bytes;
          
		storage->rx_packets += ppa_stats.hw_accel_stats.rx_pkts;
		storage->tx_packets += ppa_stats.hw_accel_stats.tx_pkts;
#endif
	}

	/* PTM WAN interface, say ptm0 */
	else if (_stat_helper_is_ptmwan_basedev(dev)) {
		/* NOTE : Linux driver maintains only MIPS counters */

#if (defined(CONFIG_LTQ_PPA_API) || defined(CONFIG_LTQ_PPA_API_MODULE))

		memset(&ppa_stats, 0, sizeof(PPA_NETIF_ACCEL_STATS));

		/* get PPE port MIB stats and HW accelerated session stats (only for tx_bytes) */
		if (ppa_hook_get_netif_accel_stats_fn) {
			ppa_hook_get_netif_accel_stats_fn(dev->name, &ppa_stats, (PPA_F_NETIF_HW_ACCEL | PPA_F_NETIF_SW_ACCEL));
		}

		/* add with ppa HW and SW accelerated stats */
		storage->rx_bytes += ppa_stats.hw_accel_stats.rx_bytes + ppa_stats.sw_accel_stats.rx_bytes;
		storage->tx_bytes += ppa_stats.hw_accel_stats.tx_bytes + ppa_stats.sw_accel_stats.tx_bytes;
          
		storage->rx_packets += ppa_stats.hw_accel_stats.rx_pkts;
		storage->tx_packets += ppa_stats.hw_accel_stats.tx_pkts;
#endif
	}

	/* ATM WAN interface, such as nas0, nas1 and so on */
	else if (_stat_helper_is_atmwan_basedev(dev)) {
		/* NOTE : Linux driver maintains only MIPS counters */

#if (defined(CONFIG_LTQ_PPA_API) || defined(CONFIG_LTQ_PPA_API_MODULE))
		/* FIXME : Currently packet counters are not available from PPA */

		memset(&ppa_stats, 0, sizeof(PPA_NETIF_ACCEL_STATS));

		/* get PPA HW accelerated session stats */
		if (ppa_hook_get_netif_accel_stats_fn) {
			ppa_hook_get_netif_accel_stats_fn(dev->name, &ppa_stats, (PPA_F_NETIF_HW_ACCEL | PPA_F_NETIF_SW_ACCEL));
		}

		/* add with ppa HW accelerated session stats */
		storage->rx_bytes += ppa_stats.hw_accel_stats.rx_bytes + ppa_stats.sw_accel_stats.rx_bytes;
		storage->tx_bytes += ppa_stats.hw_accel_stats.tx_bytes + ppa_stats.sw_accel_stats.tx_bytes;
          
		storage->rx_packets += ppa_stats.hw_accel_stats.rx_pkts;
		storage->tx_packets += ppa_stats.hw_accel_stats.tx_pkts;
#endif
	}

	/* Do nothing for any other interface */

	return storage;
}
