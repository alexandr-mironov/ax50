/*
 *  This program is free software; you can redistribute it and/or modify it
 *  under the terms of the GNU General Public License version 2 as published
 *  by the Free Software Foundation.
 *
 *  Copyright (C) 2010 John Crispin <blogic@openwrt.org>
 *  Copyright (C) 2013 Lei Chuanhua <Chuanhua.lei@lantiq.com>
 */

#ifndef _LTQ_XWAY_H__
#define _LTQ_XWAY_H__

#ifdef CONFIG_SOC_TYPE_XWAY

#include <lantiq.h>

/* Chip IDs */
#define SOC_ID_DANUBE1		0x129
#define SOC_ID_DANUBE2		0x12B
#define SOC_ID_TWINPASS		0x12D
#define SOC_ID_AMAZON_SE_1	0x152 /* 50601 */
#define SOC_ID_AMAZON_SE_2	0x153 /* 50600 */
#define SOC_ID_ARX188		0x16C
#define SOC_ID_ARX168_1		0x16D
#define SOC_ID_ARX168_2		0x16E
#define SOC_ID_ARX182		0x16F
#define SOC_ID_GRX188		0x170
#define SOC_ID_GRX168		0x171

#define SOC_ID_VRX288		0x1C0 /* v1.1 */
#define SOC_ID_VRX282		0x1C1 /* v1.1 */
#define SOC_ID_VRX268		0x1C2 /* v1.1 */
#define SOC_ID_GRX268		0x1C8 /* v1.1 */
#define SOC_ID_GRX288		0x1C9 /* v1.1 */
#define SOC_ID_VRX288_2		0x00B /* v1.2 */
#define SOC_ID_VRX268_2		0x00C /* v1.2 */
#define SOC_ID_GRX288_2		0x00D /* v1.2 */
#define SOC_ID_GRX282_2		0x00E /* v1.2 */
#define SOC_ID_VRX220		0x000

#define SOC_ID_ARX362		0x004
#define SOC_ID_ARX368		0x005
#define SOC_ID_ARX382		0x007
#define SOC_ID_ARX388		0x008
#define SOC_ID_URX388		0x009
#define SOC_ID_GRX383		0x010
#define SOC_ID_GRX369		0x011
#define SOC_ID_GRX387		0x00F
#define SOC_ID_GRX389		0x012

 /* SoC Types */
#define SOC_TYPE_DANUBE		0x01
#define SOC_TYPE_TWINPASS	0x02
#define SOC_TYPE_AR9		0x03
#define SOC_TYPE_VR9		0x04 /* v1.1 */
#define SOC_TYPE_VR9_2		0x05 /* v1.2 */
#define SOC_TYPE_AMAZON_SE	0x06
#define SOC_TYPE_AR10		0x07
#define SOC_TYPE_GRX390		0x08
#define SOC_TYPE_VRX220		0x09

static inline int ltq_is_ase(void)
{
	return (ltq_get_soc_type() == SOC_TYPE_AMAZON_SE);
}

static inline int ltq_is_danube(void)
{
	return (ltq_get_soc_type() == SOC_TYPE_DANUBE);
}

static inline int ltq_is_ar9(void)
{
	return (ltq_get_soc_type() == SOC_TYPE_AR9);
}

static inline int ltq_is_vr9(void)
{
	int type = ltq_get_soc_type();
	if ((type == SOC_TYPE_VR9) || (type == SOC_TYPE_VR9_2))
		return 1;
	else
		return 0;
}

static inline int ltq_is_ar10(void)
{
	return (ltq_get_soc_type() == SOC_TYPE_AR10);
}

static inline int ltq_is_grx390(void)
{
	return (ltq_get_soc_type() == SOC_TYPE_GRX390);
}

/* BOOT_SEL - find what boot media we have */
#define BS_EXT_ROM		0x0
#define BS_FLASH		0x1
#define BS_MII0			0x2
#define BS_PCI			0x3
#define BS_UART1		0x4
#define BS_SPI			0x5
#define BS_NAND			0x6
#define BS_RMII0		0x7

/* helpers used to access the cgu */
#define ltq_cgu_w32(x, y)	ltq_w32((x), ltq_cgu_membase + (y))
#define ltq_cgu_r32(x)		ltq_r32(ltq_cgu_membase + (x))
extern __iomem void *ltq_cgu_membase;

/* helpers used to access the rcu */
void ltq_rcu_w32(uint32_t val, uint32_t reg_off);
uint32_t ltq_rcu_r32(uint32_t reg_off);
void ltq_rcu_w32_mask(uint32_t clr, uint32_t set, uint32_t reg_off);
void ltq_endian_set(int bitn);
void ltq_endian_clr(int bitn);
static inline void ltq_pcie_clk_out(int bitn) {};

void ltq_usb_config(int usb_id, int usb_cfg_state);


/*
 * during early_printk no ioremap is possible
 * lets use KSEG1 instead
 */
#define LTQ_ASC1_BASE_ADDR	0x1E100C00
#define LTQ_EARLY_ASC		KSEG1ADDR(LTQ_ASC1_BASE_ADDR)

/* EBU - external bus unit */
#define LTQ_EBU_BUSCON0		0x0060
#define LTQ_EBU_PCC_CON		0x0090
#define LTQ_EBU_PCC_IEN		0x00A4
#define LTQ_EBU_PCC_ISTAT	0x00A0
#define LTQ_EBU_BUSCON1		0x0064
#define LTQ_EBU_ADDRSEL1	0x0024
#define EBU_WRDIS		0x80000000

/* WDT */
#define LTQ_RST_CAUSE_WDTRST	0x20

/* MPS - multi processor unit (voice) */
#define LTQ_MPS_BASE_ADDR	(KSEG1 + 0x1F107000)
#define LTQ_MPS_CHIPID		((u32 *)(LTQ_MPS_BASE_ADDR + 0x0344))
#define LTQ_FUSE_ID_CFG 	((u32 *)(LTQ_MPS_BASE_ADDR + 0x0350))

/* allow booting xrx200 phys */
int xrx200_gphy_boot(struct device *dev, unsigned int id, dma_addr_t dev_addr);

/* request a non-gpio and set the PIO config */
#define PMU_PPE			 BIT(13)

/* allow the ethernet driver to load a flash mapped mac addr */
const u8* ltq_get_eth_mac(void);

int ltq_reset_get_status (void);
int ltq_ts_get_temp(int *p_temp);

#endif /* CONFIG_SOC_TYPE_XWAY */
#endif /* _LTQ_XWAY_H__ */
