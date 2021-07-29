#!/bin/sh
# Copyright(c) Lantiq Deutschland GmbH 2014
#######################################################################
# DSL CPE Control Notification script called by DSL CPE Control Daemon.
#######################################################################
#
# Macros exported by DSL CPE control Application:-
#
# DSL_NOTIFICATION_TYPE="DSL_STATUS|DSL_INTERFACE_STATUS|DSL_DATARATE_STATUS|DSL_DATARATE_STATUS_US"
# In DSL_STATUS:-
#	DSL_BONDING_STATUS="INACTIVE|ACTIVE"
#	DSL_LINE_NUMBER=" |-1|1|2"
#	DSL_XTU_STATUS="VDSL|ADSL"
#	DSL_TC_LAYER_STATUS="ATM|PTM|EFM"
# In DSL_INTERFACE_STATUS:-
#	DSL_INTERFACE_STATUS="UP|DOWN|READY|TRAINING"
#	DSL_LINE_NUMBER=" -1|1|2"
#	DSL_XTU_STATUS="VDSL|ADSL"
#	DSL_TC_LAYER_STATUS="ATM|PTM|EFM"
#	DSL_DATARATE_US_BC0
#	DSL_DATARATE_DS_BC0
# In DSL_DATARATE_STATUS and DSL_DATARATE_STATUS_US
#	DSL_LINE_NUMBER=" -1|1|2"
#	DSL_XTU_STATUS="VDSL|ADSL"
#	DSL_TC_LAYER_STATUS="ATM|PTM|EFM"
#	DSL_DATARATE_US_BC0
#	DSL_DATARATE_DS_BC0
#
#########################################################################

outp ()
{
	echo "$@" > /dev/console
}

print_details ()
{
	outp "DSL_BONDING_STATUS: $DSL_BONDING_STATUS"
	outp "DSL_LINE_NUMBER: $DSL_LINE_NUMBER"
	outp "DSL_XTU_STATUS: $DSL_XTU_STATUS"
	outp "DSL_TC_LAYER_STATUS: $DSL_TC_LAYER_STATUS"
	outp "DSL_DATARATE_US_BC0: $DSL_DATARATE_US_BC0"
	outp "DSL_DATARATE_DS_BC0: $DSL_DATARATE_DS_BC0"
}

case $DSL_NOTIFICATION_TYPE in
	DSL_STATUS)
			case "$DSL_XTU_STATUS" in
					"VDSL")
						outp "VDSL mode"
						;;
					"ADSL")
						case "$DSL_TC_LAYER_STATUS" in
							"ATM")
								outp "ADSL-ATM mode"
								;;
							"PTM")
								outp "ADSL-PTM mode"
								;;
					 esac
			esac
	;;
	DSL_INTERFACE_STATUS)
		outp "DSL_INTERFACE_STATUS: $DSL_INTERFACE_STATUS"

		if [ -n "$DSL_INTERFACE_STATUS" -a "$DSL_INTERFACE_STATUS" = "UP" ]; then
			if [ "$DSL_TC_LAYER_STATUS" = "ATM" ]; then
				/etc/init.d/br2684ctl start
			fi
			echo "DSL US Data Rate = $(( $DSL_DATARATE_US_BC0 / 1000 )) kbps" > /dev/console
			echo "DSL DS Data Rate = $(( $DSL_DATARATE_DS_BC0 / 1000 )) kbps" > /dev/console
		elif [ -n "$DSL_INTERFACE_STATUS" -a "$DSL_INTERFACE_STATUS" = "DOWN" ]; then
			if [ "$DSL_TC_LAYER_STATUS" = "ATM" ]; then
				/etc/init.d/br2684ctl stop
			fi
		fi
	;;
	DSL_DATARATE_STATUS)
		outp "DSL US Data Rate = $(( $DSL_DATARATE_US_BC0 / 1000 )) kbps"
		outp "DSL DS Data Rate = $(( $DSL_DATARATE_DS_BC0 / 1000 )) kbps"
	;;
	DSL_DATARATE_STATUS_US)
		outp "DSL_DATARATE_STATUS_US"
		outp "DSL US Data Rate = $(( $DSL_DATARATE_US_BC0 / 1000 )) kbps"
	;;
	*)
		outp "DSL_UNKNOWN"
	;;
esac

