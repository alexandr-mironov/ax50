#!/bin/sh
# Factory reset config files
#

rm -rf /overlay/etc/config
rm -rf /overlay/etc/uci-defaults
rm -rf /overlay/opt/lantiq/wave/db/instance

sync
reboot
