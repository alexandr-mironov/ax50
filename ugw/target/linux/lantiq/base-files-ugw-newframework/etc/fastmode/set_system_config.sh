#!/bin/sh /etc/rc.common

START=01

start() {
	rm -rf /etc/init.d/csd /etc/init.d/servd /etc/init.d/ltq_cgroups_startup.sh /etc/init.d/polld
	rm -rf /etc/init.d/ltq_hwmon.sh	/etc/init.d/usb_host_device.sh /etc/init.d/usb_led.sh /etc/init.d/usb_automount_status.sh
	rm -rf /etc/init.d/ltq_pmcu.sh /etc/init.d/ltq_temp.sh /etc/init.d/pm_util.sh /etc/init.d/ltq_regulator.sh

	kmodloader /etc/modules-production.d/
	ppacmd init

	ifconfig lo up
	ifconfig eth0_1 up
	ifconfig eth0_2 up
	ifconfig eth0_3 up
	ifconfig eth0_4 up
	ifconfig eth1 up
	brctl addbr br-lan
	ip link set br-lan up
	brctl addif br-lan eth0_1
	brctl addif br-lan eth0_2
	brctl addif br-lan eth0_3
	brctl addif br-lan eth0_4

	ifconfig br-lan 192.168.1.1 netmask 255.255.255.0

	ppacmd addlan -i br-lan
	ppacmd addlan -i eth0_1
	ppacmd addlan -i eth0_2
	ppacmd addlan -i eth0_3
	ppacmd addlan -i eth0_4
	ppacmd addwan -i eth1

	echo "production system config done" > /dev/console
}
