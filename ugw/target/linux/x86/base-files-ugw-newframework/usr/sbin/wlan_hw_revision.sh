#!/bin/sh
cal_mtd=`grep -w calibration /proc/mtd | cut -d: -f1`
interface=$1
cal_file=cal_${interface}.bin
device_id_l_offset=10     # 0x0a
device_id_h_offset=11
hw_revision_offset=44   # 0x2c

print_usage () {
  echo "usage: ${0} <ifname> [<mode>]"
  echo "where ifname is either wlan2 or wlan4"
  echo "and mode is either 2h, 2l, 4h or 4l (where 2l is 2x2 low band and 4h is 4x4 high band)"
}
  
case "${1}" in
  wlan[24])
    interface=$1
    ;;
  *)
    echo "ERROR: wrong interface specified \"${1}\""
    print_usage
    exit 1
    ;;
esac

case "${2}" in
  2l|2L)
    new_hw_revision='\x52'
    ;;
  2h|2H)
    new_hw_revision='\x53'
    ;;
  4l|4L)
    new_hw_revision='\x54'
    ;;
  4h|4H)
    new_hw_revision='\x55'
    ;;
  \\x??)
    new_hw_revision=$2
    ;;
  "")
    ;;
  *)
    echo "ERROR: wrong mode specified"
    print_usage
    exit 1
    ;;    
esac

rm -rf /tmp/_calibration
mkdir -p /tmp/_calibration
cd /tmp/_calibration/

nanddump -q /dev/$cal_mtd | tar -xz 2>&-
if [ "${?}" != "0" ] ; then
  echo "ERROR: Failed to read nand content"
  exit 1
fi

tar -xzf wlanconfig.gz
if [ "${?}" != "0" ] ; then
  echo "ERROR: Failed to extract current calibration file"
  exit 1
fi

if [ ! -f $cal_file ]; then
  echo "ERROR: ${cal_file} file not found"
  exit 1
fi

# check cal_file device id
device_id_l=`printf '%02x' "'\`dd if=${cal_file} bs=1 skip=${device_id_l_offset} count=1 2>&-\`'"`
device_id_h=`printf '%02x' "'\`dd if=${cal_file} bs=1 skip=${device_id_h_offset} count=1 2>&-\`'"`
device_id="${device_id_h}${device_id_l}"

case "${device_id}" in
  0810|0800)
    echo "${cal_file} has WAVE500 device id"
    ;;
  *)
    echo "ERROR: ${cal_file} has an unknown device id ${device_id}"
    exit 1
    ;;
esac

old_hw_revision=`printf '%2x' "'\`dd if=${cal_file} bs=1 skip=${hw_revision_offset} count=1 2>&-\`'"`
echo "current hw revision for ${interface} is '\\x${old_hw_revision}'"

if [ "${new_hw_revision}" == "" ]; then
  echo "no revision specified - will not change hw revision"
  exit 0
else
  echo "modifying ${interface} to hw revision '${new_hw_revision}'..."
fi

cp $cal_file tmp.bin
echo -e $new_hw_revision | dd of=tmp.bin bs=1 seek=$hw_revision_offset count=1 2>&-
cat tmp.bin 1<> $cal_file
rm tmp.bin

tar -czf wlanconfig.gz *.bin
if [ "${?}" != "0" ] ; then
  echo "ERROR: Failed to pack modified calibration files"
  exit 1
fi

tar -cz *.gz | nandwrite -e -q -p /dev/$cal_mtd 2>&-
if [ "${?}" != "0" ] ; then
  echo "ERROR: Failed to write modified calibration file to nand"
  exit 1
fi

echo "calibraion updated successfully (${interface} hw revision changed from '\\x${old_hw_revision}' to '${new_hw_revision}')"
echo "please reboot the system for changes to take effect"
