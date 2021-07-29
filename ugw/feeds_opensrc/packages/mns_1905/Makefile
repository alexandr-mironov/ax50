include $(TOPDIR)/rules.mk
include $(INCLUDE_DIR)/kernel.mk

PKG_NAME:=mns_1905
PKG_RELEASE:=1
PKG_VERSION:=1.0.0.0

PKG_BUILD_DIR := $(BUILD_DIR)/$(PKG_NAME)

include $(INCLUDE_DIR)/package.mk
include $(INCLUDE_DIR)/kernel.mk
 
define Package/$(PKG_NAME)
	SECTION:=utils
	CATEGORY:=Intel
	TITLE:=MNS 1905
	URL:=http://www.intel.com
	MAINTAINER:=Intel Co.
	MENU:=1
	DEPENDS:=+librt +libpthread +libpcap +libopenssl +libcrypto
endef

define Package/$(PKG_NAME)/description
	MNS 1905
endef


define Build/Prepare
	$(call Build/Prepare/Default)
	ln -fs `pwd`/src/* $(PKG_BUILD_DIR)/
	echo PKG_BUILD_DIR=${PKG_BUILD_DIR}
endef

define Build/Compile
	$(MAKE) -C "$(PKG_BUILD_DIR)" \
		KERNEL_INCLUDE_PATH="$(LINUX_DIR)/include" \
		CC="$(TARGET_CROSS)gcc"
endef

define Package/$(PKG_NAME)/install
	$(INSTALL_DIR) $(1)/usr/sbin $(1)/etc/init.d/
	$(INSTALL_DIR) $(1)/$(VENDOR_PATH)/usr/sbin
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/output/{al_entity,hle_entity} $(1)/$(VENDOR_PATH)/usr/sbin
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/output/mns_1905.sh $(1)/etc/init.d/
endef

define Build/Clean
	if [ -d $(PKG_BUILD_DIR) ]; then $(MAKE) -C $(PKG_BUILD_DIR) clean; \
	$(RM) -r $(PKG_BUILD_DIR)/ipkg-$(BOARD); fi
endef

$(eval $(call BuildPackage,$(PKG_NAME)))
