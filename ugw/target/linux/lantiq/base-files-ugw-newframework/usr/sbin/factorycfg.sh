#!/bin/sh
. /etc/ugw_notify_defs.sh

_help()
{
	echo "Resets system configuration and applications.";
	echo "Default call is to reset only the system configuration."
	echo "Usage: $0 [ options ]";
	echo "Selective factory reset config:-"
	echo "     For now supported -wifi,-qos,-firewall";
	echo "     Example to reset wifi releated config"
	echo "     $0 -wifi "
	exit $1;
}

[ -n "$1" ] && {
	case "$1" in
		-h) _help 0;
		;;
		-wifi) WiFi=1;
		;;
		-qos) QoS=1;
		;;
		-network) network=1;
		;;
		-firewall) firewall=1;
		;;
		*) _help 1;
        esac
}

touch /mnt/factory_config_in_progress

#selective factory reset examples.
[ -n "$WiFi" ] && {
	echo " WiFi releated config getting reset ..."
	ubus call csd factoryreset '{ "object":"Device.WiFi."}'
	rm /mnt/factory_config_in_progress
	exit;
}

[ -n "$QoS" ] && {
	echo " QoS releated config getting reset ..."
	ubus call csd factoryreset '{ "object":"Device.QoS."}'
	rm /mnt/factory_config_in_progress
	exit;
}

[ -n "$firewall" ] && {
	echo " Firewall releated config getting reset ..."
	ubus call servd notify '{"nid":'$NOTIFY_FACTORY_RESET',"type":false}';
	ubus call csd factoryreset '{ "object":"Device.Firewall."}'
	rm /mnt/factory_config_in_progress
	exit;
}

[ -n "$network" ] && {
	## multiple objects to reset example ','
	echo " Network releated config getting reset ..."
	ubus call csd factoryreset '{ "object":"Device.IP.,Device.PPP."}'
	rm /mnt/factory_config_in_progress
	exit;
}

if [ -f /opt/lantiq/etc/uci_to_ipsec_config.sh ]; then
	. /opt/lantiq/etc/uci_to_ipsec_config.sh reset
	sync; sleep 1;
fi

if [ -f /etc/config/samba ]; then
	rm -f /overlay/etc/config/samba
	sleep 1;
fi

if [ -f /opt/lantiq/etc/nextmac.conf ] ; then 
	rm -f /opt/lantiq/etc/nextmac.conf
fi

if [ -f /etc/config/network ] ; then 
	rm -f /etc/config/network
fi

if [ -f /opt/lantiq/etc/.bootchk ] ; then 
	rm -f /opt/lantiq/etc/.bootchk
fi

if [ -d /opt/lantiq/servd/lib/gw_bkup ] ; then 
	/opt/beerocks/disable_sl.sh 0
fi

rm -f /overlay/opt/lantiq/etc/interfaces.cfg
rm -f /opt/lantiq/servd/etc/servd.conf
rm -f /opt/lantiq/etc/csd/AliasCnt.txt

ubus call csd factoryreset
sleep 2;

ubus call servd notify '{"nid":'$NOTIFY_FACTORY_RESET',"type":false}';
sleep 2;

rm /mnt/factory_config_in_progress

sync
reboot

