ARCH:=mips
SUBTARGET:=xrx500_sec
BOARDNAME:=Lantiq xRX500 True virtualization
FEATURES:=squashfs jffs2 atm
CFLAGS+= -mtune=1004kc

DEFAULT_PACKAGES+=LTQBASE kmod-pppoa ppp-mod-pppoa linux-atm atm-tools br2684ctl swconfig kmod-lantiq_ppa_xrx500 ppp-mod-pppol2tp

define Target/Description
	Lantiq xRX500 True virtualization
endef
