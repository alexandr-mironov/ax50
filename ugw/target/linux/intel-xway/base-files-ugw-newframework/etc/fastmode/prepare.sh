#!/bin/sh
prepare_script=/tmp/caltest_prepare_fastmode
scripts_archive_path=/etc/fastmode/wlan_wave.tar.gz
read_script=/tmp/calread

GRX350_PLATFORM_NAME="EASY350 ANYWAN (GRX350) Router model"
GRX330_PLATFORM_NAME="EASY330 AC1200 35B"
IRE220_PLATFORM_NAME="EASY350 ANYWAN IRE220 model"

# TODO: run if exists /etc/init.d/ire_configure config disable

if grep -w -q "Production=true" /proc/cmdline; then
  echo "ERROR: cannot run prepare - platform already in Production Mode."
  echo "       you can run /etc/fastmode/restore.sh to reboot the platfom into normal mode and retry"
  exit 1
fi

echo "Waiting for wlan interface..."
timeout=120
while [ $timeout -gt 0 ] ; do
  ifconfig | grep wlan0 > /dev/null 2>&1
  if [ "${?}" = "0" ] ; then
    break
  fi
  sleep 5
  timeout=`expr $timeout - 5`
done
if [ $timeout -le 0 ] ; then
  echo "ERROR: timed out waiting for wlan interface"
  exit 1
fi

# Set system parameters - these settings affect the generated wlan scripts
echo "Setting system parameters for Production Mode..."
echo -n > $prepare_script

# check if beerocks is enabled
echo "object:Device.X_INTEL_COM_BEEROCKS.: :" > $read_script
echo "param:Enable: :" >> $read_script
caltest -g $read_script -c WEB 2> /dev/null | grep '"paramValue" : "true"' > /dev/null

# if beerocks is enabled disable it
if [ "${?}" == "0" ] ; then
  echo "Stopping BeeRocks..."
  /opt/beerocks/beerocks_utils.sh killall
  if [ "${?}" != "0" ] ; then
    echo "ERROR: Failed to kill beerocks deamons"
    exit 1
  fi

  echo "object:Device.X_INTEL_COM_BEEROCKS.: :MODIFY" >> $prepare_script
  echo "param:Enable: :false" >> $prepare_script

  caltest -s $prepare_script -c SERVD
  if [ "${?}" != "0" ] ; then
    echo "ERROR: Failed to update DB"
    exit 1
  fi

  echo -n > $prepare_script
  echo "object:Device.WiFi.Radio.1.X_LANTIQ_COM_Vendor.: :MODIFY" >> $prepare_script
  echo "param:WaveExternallyManaged: :false" >> $prepare_script
fi

echo "object:Device.DeviceInfo.: :" > $read_script
echo "param:HardwareVersion: :" >> $read_script
platform=$(caltest -g $read_script -c WEB 2> /dev/null | grep paramValue)

echo -n > $prepare_script
if echo "$platform" | grep -q "$GRX350_PLATFORM_NAME" ; then
  channels='5 149 36'
elif echo "$platform" | grep -q "$IRE220_PLATFORM_NAME" ; then
  channels='5 149 36'
elif echo "$platform" | grep -q "$GRX330_PLATFORM_NAME" ; then
  channels='11 36'
else
  echo "ERROR: current platform doesn't support production mode"
  exit 1
fi

# loop over available AP radios 
# APs use even mumbered interface names e.g. wlan0, wlan2, etc.
# Radios and AccessPoint database objects are numbered from 1 e.g. 1, 2, 3, etc.
ap=1
for channel in $channels; do

  # check if an AP exist
  if_num=`expr 2 \* \( $ap - 1 \)`
  if_name="wlan${if_num}"
  ifconfig -a | grep $if_name > /dev/null 2>&1
  # if the AP exist set appropritae parameters in the DB
  if [ "${?}" = "0" ] ; then
    echo "object:Device.WiFi.AccessPoint.${ap}.Security.: :MODIFY" >> $prepare_script
    echo "param:ModeEnabled: :None"                                >> $prepare_script
    echo "object:Device.WiFi.SSID.${ap}.: :MODIFY"                 >> $prepare_script
    echo "param:SSID: :TEST_SSID_${ap}"                            >> $prepare_script
    echo "object:Device.WiFi.AccessPoint.${ap}.: :MODIFY"          >> $prepare_script
    echo "param:Enable: :true"                                     >> $prepare_script
    echo "object:Device.WiFi.Radio.${ap}.: :MODIFY"                >> $prepare_script
    echo "param:AutoChannelEnable: :false"                         >> $prepare_script
    echo "param:IEEE80211hEnabled: :false"                         >> $prepare_script
    echo "param:Channel: :${channel}"                              >> $prepare_script
    echo "param:Enable: :true"                                     >> $prepare_script
  fi

  ap=$((ap+1))
done

caltest -s $prepare_script -c WEB
if [ "${?}" != "0" ] ; then
  echo "ERROR: Failed to update DB"
  exit 1
fi

echo "Collecting wlan scripts..."
cd /opt/lantiq/wave/confs/
tar -cvzf $scripts_archive_path runner_hw_init.sh runner_up_wlan*.sh hostapd_wlan*.conf drvhlpr_wlan*.conf
if [ "${?}" != "0" ] ; then
  echo "ERROR: Failed to create wlan scripts archive"
  exit 1
fi
cd -

echo "******************************************************************************************************"
echo "WLAN scripts archive for Production Mode is ready at ${scripts_archive_path}"
echo "You can now run /etc/fastmode/enable.sh to reboot this platform into Production Mode"
echo "Or you can copy ${scripts_archive_path} to be used for production of other platforms of the same model"
echo "PRODUCTION PREPARE DONE" # keep this string as is - it is used by the production automation scripts
echo "******************************************************************************************************"
