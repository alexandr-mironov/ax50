
# Copyright (C) 2014 OpenWrt.org
#
# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
#

include $(TOPDIR)/rules.mk

PKG_NAME:=luacurl
PKG_VERSION:=v3
PKG_RELEASE:=0.3.7

PKG_SOURCE:=$(PKG_NAME)-$(PKG_VERSION).tar.gz
PKG_SOURCE_URL:=https://github.com/Lua-cURL/Lua-cURLv3
PKG_SOURCE_VERSION:=d7d3af0b662cefeabf6f47fb1137f0adc04e4002
PKG_SOURCE_PROTO:=git
PKG_SOURCE_SUBDIR:=$(PKG_NAME)-$(PKG_VERSION)

include $(INCLUDE_DIR)/package.mk
include $(INCLUDE_DIR)/cmake.mk

define Package/luacurl
  SUBMENU:=Lua
  SECTION:=lang
  CATEGORY:=Languages
  TITLE:=Lua-cURL
  URL:=http://msva.github.io/lua-curl/
  DEPENDS:=+liblua +libcurl
endef

define Package/luacurl/description
 Lua-cURL is aiming for a full-fledged libcurl binding (easy/multi/share
 interface) to the functionality of Lua
endef

CMAKE_OPTIONS += \
	-DUSE_LUA=ON

define Package/luacurl/install
	$(INSTALL_DIR) $(1)/usr/lib/lua
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/cURL.so $(1)/usr/lib/lua/
endef

$(eval $(call BuildPackage,luacurl))
