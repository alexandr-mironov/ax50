# Lantiq SoC xRX500 Family/Reference Boards

define Profile/None
  NAME:=Generic Profile
endef

define Profile/None/Description
	Basic profile
endef
$(eval $(call Profile,None))

define Profile/easy350_hwvt_800m
  NAME:=EASY350 True virtualization ANYWAN 800Mhz Board
endef

define Profile/easy350_hwvt_800m/Description
        EASY350 True virtualization ANYWAN 800Mhz DT
endef
$(eval $(call Profile,easy350_hwvt_800m))


