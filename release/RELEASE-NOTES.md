# AX50 OpenWrt Firmware v0.1.0-alpha

**Статус: ALPHA — требуется проверка на реальном железе**

## Целевое устройство

- **Роутер:** TP-Link Archer AX50 v1
- **SoC:** Lantiq GRX350 (MIPS32r2, 1004Kc, 800MHz)
- **RAM:** 256 MB DDR3
- **Flash:** 128 MB NAND
- **Target:** `lantiq/xrx500/easy350_anywan`

## Образы прошивки

| Файл | Размер | Назначение |
|------|--------|------------|
| `fullimage.img` | 11 MB | Полный образ (ядро + rootfs) для sysupgrade или TFTP |
| `uImage` | 2.8 MB | Ядро Linux 3.10.104 (MIPS, LZMA) |
| `rootfs.img` | 7.3 MB | Корневая ФС (SquashFS + UBI) |
| `uImage_bootcore` | 2.0 MB | BootCore загрузчик |
| `openwrt-*-squashfs.image` | 11 MB | Альтернативный squashfs образ |
| `sha256sums.txt` | — | Контрольные суммы |

## Рабочий функционал

### Сеть
- **Ethernet:** Lantiq Intel Ethernet driver (kmod-intel_eth_drv_xrx500)
- **IPv4/IPv6:** полная поддержка, dual-stack
- **DHCP-сервер:** dnsmasq
- **DHCPv6:** odhcpd + wide-dhcpv6
- **PPPoE/PPPoA:** ppp + ppp-mod-pppoe + ppp-mod-pppoa
- **Bridge:** bridge-utils, ebtables
- **VLAN:** swconfig
- **DS-Lite, MAP-E:** ds-lite, map (IPv4-over-IPv6 туннели)
- **Маршрутизация:** ip (iproute2), quagga (RIPd)

### Firewall / NAT
- **iptables:** полный набор (conntrack, ipopt, ipsec, nfqueue, ipset)
- **ip6tables:** IPv6 firewall
- **conntrack-tools:** отслеживание соединений
- **ipset:** наборы IP-адресов (пригодится для маршрутизации по доменам)
- **tc:** traffic control / QoS (kmod-sched-core)

### VPN / Tunnels
- **strongSwan 5.5:** IPsec IKEv1/IKEv2 (полный набор модулей)
- **ipsec-tools:** IPsec legacy
- **L2TP:** kmod-l2tp
- **IP tunnels:** kmod-iptunnel, kmod-iptunnel4, kmod-iptunnel6, kmod-sit, kmod-ip6-tunnel
- **socat:** универсальный TCP/UDP relay

### Управление
- **LuCI:** веб-интерфейс (luci-light + bootstrap тема)
- **SSH:** Dropbear SSH-сервер
- **uhttpd:** HTTP-сервер для LuCI
- **lighttpd:** дополнительный HTTP-сервер
- **ubus/uci:** стандартная OpenWrt шина управления
- **opkg:** менеджер пакетов

### Диагностика
- **tcpdump:** захват трафика
- **strace:** трассировка системных вызовов
- **ethtool/ethping/ethtrace:** диагностика Ethernet
- **conntrack:** просмотр NAT-таблицы
- **mtd-utils:** полный набор (nanddump, nandwrite, ubi*)

### Службы
- **Samba 3:** файловый сервер (SMB)
- **vsftpd:** FTP-сервер
- **miniDLNA:** DLNA медиасервер
- **radvd:** Router Advertisement daemon
- **stunnel:** TLS-обёртка для TCP
- **syslog-ng:** логирование

### USB
- **kmod-usb-core:** USB-хост
- **kmod-usb-net/cdc-mbim/cdc-ncm:** USB-модемы (LTE)
- **wwan/umbim:** управление LTE-модемами

## Что НЕ работает / отсутствует

### WiFi
**WiFi не включён.** Проприетарные драйверы Lantiq Wave500/Wave600
находились в отсутствующих фидах (`ugw_packages`, `thirdparty_sw`).
По ТЗ WiFi не требуется (AX50 как проводной VPN-шлюз).

### VPN (xray-core)
Xray-core ещё не добавлен. Это следующий этап:
- Кросс-компиляция Go-бинарника `GOOS=linux GOARCH=mips GOMIPS=softfloat`
- VLESS+Reality клиент
- dnsmasq ipset + iptables TPROXY маршрутизация по доменам

### OpenVPN
Отключён в конфигурации. Может быть включён при необходимости.

### PPA (Packet Processing Accelerator)
Hardware-ускорение маршрутизации Lantiq отключено (фиды PPA отсутствуют).
Используются stub-функции. Производительность роутинга — программная.

## Известные риски

1. **Образ собран для reference design `easy350_anywan`**, а не специфично
   для TP-Link AX50. Потенциальные отличия: GPIO mapping, LED, кнопки.

2. **Partition layout** соответствует DTS из SDK. Если TP-Link изменил layout
   в заводской прошивке — `sysupgrade` может не работать корректно.

3. **Перед прошивкой обязательно:**
   - Сделать бэкап: `./scripts/ax50-backup.sh root@192.168.1.1`
   - Убедиться что U-Boot TFTP recovery работает (серийная консоль)

## Контрольные суммы

См. файлы `sha256sums.txt` и `md5sums.txt` в каталоге релиза.

## Как прошить

```bash
# 1. Бэкап текущей прошивки
./scripts/ax50-backup.sh root@192.168.1.1

# 2. Прошивка
./scripts/ax50-flash.sh root@192.168.1.1 release/fullimage.img
```

Подробнее: [BUILD.md](../BUILD.md)
