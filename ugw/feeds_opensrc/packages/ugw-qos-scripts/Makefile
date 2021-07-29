# 
# Copyright (C) 2006-2015 OpenWrt.org
#
# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
#

include $(TOPDIR)/rules.mk

PKG_NAME:=ugw-qos-scripts
PKG_VERSION:=1.0.0
PKG_RELEASE:=1


PKG_BUILD_DIR := $(BUILD_DIR)/$(PKG_NAME)

include $(INCLUDE_DIR)/package.mk

define Package/ugw-qos-scripts
  SECTION:=utils
  CATEGORY:=Base system
  TITLE:=UGW QoS scripts
  PKGARCH:=all
endef

define Package/ugw-qos-scripts/description
 A set of scripts that abstract QoS configuration into a simple 
 configuration file supporting stanzas that specify any number of QoS 
 entries.
endef

define Package/ugw-qos-scripts/conffiles
/etc/config/qos
endef

define Build/Prepare
endef

define Build/Configure
endef

define Build/Compile
endef

define Package/ugw-qos-scripts/install
	$(INSTALL_DIR) $(1)
	$(CP) ./files/* $(1)/
endef

$(eval $(call BuildPackage,ugw-qos-scripts))
