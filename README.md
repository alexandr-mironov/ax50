# AX50 Mesh Firmware (in development)

OpenWRT TP-Link AX50 Firmware

## Installing dependencies
```
sudo apt install libncurses5 libncurses5-dev m4 bison gawk flex g++ gengetopt gitk zlib1g-dev autoconf autopoint libtool shtool autogen mtd-utils intltool sharutils libstdc++5 texinfo dos2unix xsltproc device-tree-compiler qemu gperf liblzo2-dev uuid-dev build-essential lzma-dev liblzma-dev lzma binutils-dev patch cmake libglib2.0-dev gtk-doc-tools
```
## In case you have Ubuntu on amd
```
sudo dpkg --add-architecture i386
sudo apt update
sudo apt install libelf1:i386 libncurses5:i386 libc6-i386 lib32stdc++6 lib32z1 libc6-dev-i386
```
## Notes:
not fount candidates in wsl ubuntu 20.04
```
libstdc++6-4.4-dev g++-4.4 ia32-libs uboot-mkimage
```