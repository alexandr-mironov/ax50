obj-$(CONFIG_LANTIQ_VRX318) += ltq_vrx318.o
obj-$(CONFIG_LANTIQ_ETH_FRAMEWORK) += lantiq_eth_framework.o
obj-$(CONFIG_LTQ_ETH_OAM) += ltq_eth_oam_handler.o
ifneq ($(CONFIG_LTQ_ETH_OAM),)
  obj-y += ltq_eth_oam_netif.o
endif
obj-$(CONFIG_LTQ_ETHSW_API) += switch-api/
ifeq ($(CONFIG_SOC_XWAY),)
obj-$(CONFIG_LTQ_DATAPATH) += datapath/
endif
obj-$(CONFIG_LTQ_TMU) += tmu/
obj-$(CONFIG_LTQ_CBM) += cbm/
obj-$(CONFIG_LTQ_ETH_XRX500) += ltq_eth_drv_xrx500.o
obj-$(CONFIG_LTQ_TOE_DRIVER) += ltq_toe_drv.o
obj-$(CONFIG_VRX318_DATAPATH) += vrx318/
obj-$(CONFIG_LTQ_DIRECTCONNECT_DP) += directconnect_dp/
ifeq ($(CONFIG_LTQ_PPA_GRX500),y)
obj-$(CONFIG_ACCL_11AC) += directlink/
endif
ifneq ($(CONFIG_ACCL_11AC),)
obj-$(CONFIG_ACCL_11AC_DLRX) += directlink/dlrx/dlrx_fw/
endif
