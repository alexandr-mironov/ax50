obj-$(CONFIG_LTQ_PPA_DATAPATH)	+= ltqmips_ppe_drv.o
obj-$(CONFIG_ACCL_11AC)         += directlink/
obj-$(CONFIG_DIRECTCONNECT_DP_API) += dcdp/
#obj-$(CONFIG_IFX_PPA_DATAPATH)	+= ltqmips_datapath.o ltqmips_hal.o

ltqmips_ppe_drv-objs = ltqmips_datapath.o ltqmips_hal.o ltqmips_ppe_drv_stub.o
ifneq ($(CONFIG_DIRECTCONNECT_DP_API),)#
	ltqmips_ppe_drv-objs += dcdp/ltqmips_datapath_api.o dcdp/ltqmips_datapath_proc_api.o dcdp/ltqmips_datapath_proc.o 
endif
