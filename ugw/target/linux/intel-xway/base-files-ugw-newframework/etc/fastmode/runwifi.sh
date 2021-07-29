#!/bin/sh
cp /opt/lantiq/wave/scripts/* /tmp > /dev/null 2>&1
cd /opt/lantiq/wave/confs/
tar -xvzf /etc/fastmode/wlan_wave.tar.gz > /dev/null
./runner_hw_init.sh
for i in [ 0 2 4 ]; do
  if [ -e ./runner_up_wlan${i}.sh ]; then
    ./runner_up_wlan${i}.sh
  fi
done
cd -

# kill old driver helper instances
sleep 2
killall drvhlpr > /dev/null 2>&1

echo ${0} DONE