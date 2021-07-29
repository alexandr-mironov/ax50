#!/bin/sh

tun_type=$1
oper=$2
tunnel_name=$3
proto=$4
wan_ipaddr=$5
peer_ipaddr=$6

help()
{
    echo "Invalid argument:"
    echo "    ./gre.sh EoGRE ADD <tunnel name> <IPv4/IPv6> <wan ip addr> <peer ip addr> <lan bridge name> <wan interface name>"
    echo "    ./gre.sh EoGRE DEL <IPv4/IPv6> <tunnel name>"
    echo "    ./gre.sh IPoGRE ADD <tunnel name> <IPv4/IPv6> <wan ip addr> <peer ip addr> <tunnel ip addr> <tunnel netmask>"
    echo "    ./gre.sh IPoGRE DEL <IPv4/IPv6> <tunnel name>"
    echo ""
    exit
}

configure_eogre()
{
    lan_br_name=$1
    wan_ifname=$2
    
    lowermtu=$(cat /sys/class/net/$wan_ifname/mtu)
    
    uci set network.$tunnel_name=interface
    if [ "$proto" == "IPv4" ]; then
	gremtu=`expr $lowermtu - 38`
        uci set network.$tunnel_name.proto='gretap'
        uci set network.$tunnel_name.ipaddr=$wan_ipaddr
        uci set network.$tunnel_name.peeraddr=$peer_ipaddr
    elif [ "$proto" == "IPv6" ]; then
	gremtu=`expr $lowermtu - 52`
        uci set network.$tunnel_name.proto='grev6tap'
        uci set network.$tunnel_name.ip6addr=$wan_ipaddr
        uci set network.$tunnel_name.peer6addr=$peer_ipaddr
    else
    	echo "Improper IP proto" > /dev/console
    	help
    fi
    uci set network.$tunnel_name.mtu=$gremtu
    uci set network.$tunnel_name.network=$lan_br_name
    uci commit

    ubus call network reload

    echo enable > /proc/ppa/api/bridged_flow_learning
}

destroy_eogre()
{
    uci delete network.$tunnel_name
    uci commit

    ubus call network reload

    echo disable > /proc/ppa/api/bridged_flow_learning
}

configure_ipogre()
{
    tun_ipaddr=$1
    tun_subnet_prefix=$2

    uci set network.$tunnel_name=interface
    if [ "$proto" == "IPv4" ]; then
        uci set network.$tunnel_name.proto='gre'
        uci set network.$tunnel_name.ipaddr=$wan_ipaddr
        uci set network.$tunnel_name.peeraddr=$peer_ipaddr
    elif [ "$proto" == "IPv6" ]; then
        uci set network.$tunnel_name.proto='grev6'
        uci set network.$tunnel_name.ip6addr=$wan_ipaddr
        uci set network.$tunnel_name.peer6addr=$peer_ipaddr
    else
    	echo "Improper IP proto" > /dev/console
    	help
    fi
    uci set network.$tunnel_name.tunipaddr=$tun_ipaddr
    uci set network.$tunnel_name.tunnetmask=$tun_subnet_prefix
    uci commit

    # Allow GRE Traffic from WAN
    val=$(uci add firewall rule)
    uci set firewall.$val.name='Allow-GRE'
    uci set firewall.$val.src='wan'
    uci set firewall.$val.proto='gre'
    if [ "$proto" == "IPv4" ]; then
        uci set firewall.$val.family='ipv4'
    elif [ "$proto" == "IPv6" ]; then
        uci set firewall.$val.family='ipv6'
    fi
    uci set firewall.$val.target='ACCEPT'
    uci commit firewall

    /etc/init.d/firewall restart 2>/dev/null

    ubus call network reload
}

destroy_ipogre()
{
    uci delete network.$tunnel_name
    uci commit

    ubus call network reload
}

[ $# -lt 3 ] && help
case $oper in
    ADD)
        if [ "$tun_type" == "EoGRE" ]; then
            [ $# -ne 8 ] && help
            configure_eogre $7 $8
        elif [ "$tun_type" == "IPoGRE" ]; then
            [ $# -ne 8 ] && help
            configure_ipogre $7 $8
        else
            help
        fi
    ;;

    DEL)
        if [ "$tun_type" == "EoGRE" ]; then
            [ $# -ne 3 ] && help
            destroy_eogre
        elif [ "$tun_type" == "IPoGRE" ]; then
            [ $# -ne 3 ] && help
            destroy_ipogre
        else
            help
        fi
    ;;

    *)
        help
esac
