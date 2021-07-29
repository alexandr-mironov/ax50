Source-Makefile: feeds/open_applications/libnet-1.1.x/Makefile
Package: libnet1
Version: 1.1.2.1-2
Depends: +!PACKAGE_ecos:libc +SSP_SUPPORT:libssp +USE_GLIBC:librt +USE_GLIBC:libpthread +libpcap
Conflicts: 
Menu-Depends: 
Provides: 
Build-Depends: libtool libintl libiconv
Section: libs
Category: Libraries
Title: Low-level packet creation library (v1.1.x)
Maintainer: 
Source: libnet.tar.gz
Type: ipkg
Description: Low-level packet creation library (v1.1.x)
http://www.packetfactory.net/libnet/

@@


