obj-y := prom.o clk.o irq.o sysctrl.o ngi.o timer.o
obj-$(CONFIG_SERIAL_GRX500_BOOTCORE_CONSOLE) += early_printk.o
ifdef CONFIG_RESET_IAP
obj-y += interaptiv_reset.o
endif
