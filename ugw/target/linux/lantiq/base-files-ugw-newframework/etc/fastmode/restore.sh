#!/bin/sh
uboot_env --set --name Production --value false 2>&1 > /dev/null
uboot_env --set --name Production --value false 2>&1 > /dev/null # yes, sometimes it's better to try twice...
rm -rf /overlay/*
reboot
