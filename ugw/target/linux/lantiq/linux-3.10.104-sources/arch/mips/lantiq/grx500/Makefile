ifdef CONFIG_HW_VIRT_SEC_OS
obj-y := prom.o sysctrl.o irq.o clk.o 
else
obj-y := prom.o reset.o sysctrl.o irq.o clk.o dma.o ltq_dma.o gptu.o mtlk_init.o
endif
obj-$(CONFIG_XRX500_PHY_FW) += xrx500_phy_fw.o
