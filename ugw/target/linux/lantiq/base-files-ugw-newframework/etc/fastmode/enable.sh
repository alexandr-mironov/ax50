#!/bin/sh
echo "Preparing for Production Mode..."
/etc/fastmode/prepare.sh
if [ $? != 0 ]; then
  echo "ERROR: failed to prepare production mode"
  exit 1
fi

echo "Enabling Production Mode..."
uboot_env --add --name Production --value true 2>&1 > /dev/null # could fail if Production already exists
uboot_env --set --name Production --value true 2>&1 > /dev/null
uboot_env --set --name Production --value true 2>&1 > /dev/null # yes, sometimes it's better to try twice...
if [ "`uboot_env --get --name Production`" != "true" ] ; then
  echo "ERROR: Failed to set production mode"
  exit 1
fi

echo "Restarting system into Production Mode..."
sync
reboot
