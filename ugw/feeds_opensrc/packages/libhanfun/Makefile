#
# ULE Alliance's HAN-FUN OpenWrt package
#

include $(TOPDIR)/rules.mk

PKG_NAME:=hanfun
PKG_VERSION:=1.5.0
PKG_RELEASE:=1
PKG_INSTALL:=0
PKG_SOURCE_PROTO:=git
PKG_SOURCE_SUBDIR:=$(PKG_NAME)-$(PKG_VERSION)
#PKG_SOURCE_VERSION:= v1.4.3
PKG_SOURCE_VERSION:= e33cd401fb193b4cbd51f150cf813053f5dcaa7e
PKG_SOURCE:=$(PKG_NAME)-$(PKG_VERSION)-$(PKG_SOURCE_VERSION).tar.xz
#PKG_SOURCE_URL:=http://www.ulealliance.org
PKG_SOURCE_URL:=https://github.com/ULE-Alliance/hanfun.git
#PKG_CAT=zcat
#PKG_MD5SUM:=28828832fb3fa3771165665e5aa1440b
PKG_MD5SUM:= 5bf341879dc2429681d8207367d9d65d
#PKG_BUILD_DIR:=$(BUILD_DIR)/$(PKG_NAME)-$(PKG_VERSION)
PKG_DEFAULT_CUSTOM_SOURCE_DIR:=$(PKG_SOURCE)

TARGET_CFLAGS += -DHF_APP_CONFIG_FILE="\\\"/flash/HF_rc.conf\\\"" -DHF_LOG_LEVEL=HF_LOG_LEVEL_DEBUG

CMAKE_OPTIONS:= -DHF_BASE_LIB=ON -DHF_APP_EXT_REG=ON
CMAKE_OPTIONS += -DHF_GROUP_SUPPORT=ON -DHF_EVENT_SCHEDULING_SUPPORT=ON -DHF_WEEKLY_SCHEDULING_SUPPORT=ON -DHF_TIME_SUPPORT=ON -DHF_BATCH_PROGRAM_SUPPORT=ON

include $(INCLUDE_DIR)/package-version-override.mk
include $(INCLUDE_DIR)/package.mk
include $(INCLUDE_DIR)/cmake.mk

define Package/libhanfun
  SECTION:=libs
  CATEGORY:=Libraries
  TITLE:=Home Area Network FUNctional protocol
  URL:=http://www.ulealliance.org
  MAINTAINER:=Bithium
  MENU:=1
  DEPENDS:=+libstdcpp +libc +libgcc
endef

define Package/libhanfun/description
  Implementation of the HAN-FUN application specification.
endef

define Build/InstallDev
  pushd $(PKG_BUILD_DIR) && make DESTDIR=$(1) install && popd
endef

$(eval $(call BuildPackage,libhanfun))
