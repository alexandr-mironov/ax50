#!/bin/sh /etc/rc.common

USE_PROCD=1
START=100
#brlan_mac=$(ifconfig br-lan | awk '/^[a-z]/ { iface=$1; mac=$NF; next } /inet addr:/ { print mac }')
al_mac=$(cat /opt/lantiq/etc/nextmac.conf | grep eth0_1 | cut -d" " -f2)
start_service() {
        procd_open_instance
        procd_set_param command al_entity -m $al_mac -i br-lan -vvv
        procd_set_param respawn
        procd_close_instance
}
service_triggers()
{
	# add here dependency for which we want to reload al_entity
        procd_add_reload_trigger  "/tmp/beerocks/beerocks_slave_version"
}

