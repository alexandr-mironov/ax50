#/bin/sh
###############################################################################
#  
# Copyright (c) 2017, Broadband Forum
# Copyright (c) 2017, MaxLinear, Inc. and its affiliates
# 
# Redistribution and use in source and binary forms, with or
# without modification, are permitted provided that the following
# conditions are met:
# 
# 1. Redistributions of source code must retain the above copyright
#    notice, this list of conditions and the following disclaimer.
# 
# 2. Redistributions in binary form must reproduce the above
#    copyright notice, this list of conditions and the following
#    disclaimer in the documentation and/or other materials
#    provided with the distribution.
# 
# 3. Neither the name of the copyright holder nor the names of its
#    contributors may be used to endorse or promote products
#    derived from this software without specific prior written
#    permission.
# 
# THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND
# CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES,
# INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
# MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
# DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR
# CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
# SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
# NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
# LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
# CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
# STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
# ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
# ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
# 
# The above license is used as a license under copyright only.
# Please reference the Forum IPR Policy for patent licensing terms
# <https://www.broadband-forum.org/ipr-policy>.
# 
# Any moral rights which are necessary to exercise under the above
# license grant are also deemed granted under this license.

##############################################################################
#
# Description: This script is in charge of monitoring network topology changes
#              and inform the 1905 stack that a new device has been connected 
#              or a device has been disconnected.
#              
#              This script is automatically started by the 'start_linksys.sh' 
#              script.
#              
#              In this example, the script only monitors GHN and WIFI 
#              interfaces. If something occurs in these two interfaces,
#              a "touch" will be done to the /tmp/topology_change file to 
#              inform the 1905 stack that the topology must be refreshed.
#               
###############################################################################

GHN_INTERFACE_MAC=$1
GHN_INTERFACE=eth0
WIFI_INTERFACE=wlan1

wifi_device_list_old=""
ghn_device_list_old=""
while true;
do
  echo "Refreshing device list...."
  wifi_device_list=`iw dev $WIFI_INTERFACE station dump | grep Station | cut -f2 -d' '`
  ghn_device_list=`./configlayer -i $GHN_INTERFACE -m $GHN_INTERFACE_MAC -o GETLEGACY -p DIDMNG.GENERAL.MACS -w paterna`
  if [ "$wifi_device_list" != "$wifi_device_list_old" ] || [ "$ghn_device_list" != "$ghn_device_list_old" ] 
  then
      echo "Topology has changed"
      touch /tmp/topology_change 
      echo "Old list :"
      echo $wifi_device_list_old
      echo $ghn_device_list_old
      echo "New list :"
      echo $wifi_device_list
      echo $ghn_device_list
      wifi_device_list_old=$wifi_device_list
      ghn_device_list_old=$ghn_device_list
  fi
  sleep 5
done

