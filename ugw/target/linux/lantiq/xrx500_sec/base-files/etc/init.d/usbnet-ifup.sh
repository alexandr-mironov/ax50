#!/bin/sh /etc/rc.common

START=999

. /lib/functions/common_utils.sh

start() {
        ifconfig eth0 192.168.1.1 up
        chmod 777 -R /www
}

