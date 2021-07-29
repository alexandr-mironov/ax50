#!/bin/sh /etc/rc.common
# Copyright (C) 2015 Lantiq Beteiligungs-GmbH Co. KG

START=81
STOP=06

BOND_IF_NAME=eth0_0

start() {
	echo "Starting ethernet bonding ....."

	[ -e /etc/rc.d/config.sh ] && . /etc/rc.d/config.sh

	if [ "$CONFIG_IFX_MODEL_NAME" = "GRX350_1600_MR_AXEPOINT_6X_WAV500_ETH_RT_74" -o "$CONFIG_IFX_MODEL_NAME" = "GRX350_1600_MR_AXEPOINT_6X_WAV600_ETH_RT_74" ]
	then
		mem -s 0x16080120 -w 0x800 -u
		mem -s 0x1c003c1c -w 0x7c -u
		mem -s 0x1a003d10 -w 0x1806 -u

		mem -s 0x16080120 -w 0x100800 -u
		switch_cli GSW_PORT_CFG_SET nPortId=6 eEnable=1

		mem -s 0x16000010 -w 0x80000000 -u
		mem -s 0x16000010 -w 0x0 -u
		BOND_IF_NAME=eth0_5
	fi

	insmod /lib/modules/*/ltq_eth_bond_dp.ko

	sleep 1
	ifconfig $BOND_IF_NAME up -arp
}

stop () {

	[ -e /etc/rc.d/config.sh ] && . /etc/rc.d/config.sh

	if [ "$CONFIG_IFX_MODEL_NAME" = "GRX350_1600_MR_AXEPOINT_6X_WAV500_ETH_RT_74" -o "$CONFIG_IFX_MODEL_NAME" = "GRX350_1600_MR_AXEPOINT_6X_WAV600_ETH_RT_74" ]
	then
		BOND_IF_NAME=eth0_5
	fi

	ifconfig $BOND_IF_NAME down

	rmmod /lib/modules/*/ltq_eth_bond_dp.ko
}

