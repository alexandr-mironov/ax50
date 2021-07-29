/*
 * This file provides functions for MXIC ECC-Free Nand, which is an SLC 
 * NAND flash solution with embedded error correction code (ECC).
 *
 * Derived from Toshiba's drivers/mtd/nand/nand_benand.c
 * (C) Copyright TOSHIBA CORPORATION 2013
 * All Rights Reserved.
 *
 * (C) Copyright INTEL CORPORATION 2017
 * All Rights Reserved.
 * Author: Brandon.yang@intel.com
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
 */

#include <linux/types.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/slab.h>
#include <linux/bitops.h>
#include <linux/mtd/mtd.h>
#include <linux/mtd/nand.h>
#include <linux/mtd/nand_benand.h>

/* The ECC Bits Status for MXIC_MX30LF1GE8AB */
#define NAND_ECC_STATUS_0_1_BIT_ERR	0x00
#define NAND_ECC_STATUS_2_BIT_ERR	0x10
#define NAND_ECC_STATUS_3_BIT_ERR	0x08
#define NAND_ECC_STATUS_4_BIT_ERR	0x18

static struct nand_ecclayout benand_oob_64 = {
	.eccbytes = 0,
	.eccpos = {},
	.oobfree = {
		{.offset = 2, .length = 62}
	}
};

static struct nand_ecclayout benand_oob_128 = {
	.eccbytes = 0,
	.eccpos = {},
	.oobfree = {
		{.offset = 2, .length = 126}
	}
};

static int nand_benand_status_chk(struct mtd_info *mtd, struct nand_chip *chip)
{
	unsigned int max_bitflips = 0;
	u8 status;

	/* Check Read Status */
	chip->cmdfunc(mtd, NAND_CMD_STATUS, -1, -1);
	status = chip->read_byte(mtd);

	/* timeout */
	if (!(status & NAND_STATUS_READY)) {
		pr_debug("BENAND : Time Out!\n");
		return -EIO;
	}

	/* uncorrectable */
	else if (status & NAND_STATUS_FAIL)
		mtd->ecc_stats.failed++;

	/* correctable: MXIC recommends to rewrite when 3~4 bits error been corrected */
	else if (status & NAND_ECC_STATUS_3_BIT_ERR) {
                max_bitflips = 3;
                mtd->ecc_stats.corrected += max_bitflips;
        }
	else if ((status & NAND_ECC_STATUS_4_BIT_ERR) == NAND_ECC_STATUS_4_BIT_ERR) {
		max_bitflips = 4;
		mtd->ecc_stats.corrected += max_bitflips;
	}

	return max_bitflips;
}

/**
 * nand_read_page_raw - [Intern] read raw page data with benand.
 * @mtd: mtd info structure
 * @chip: nand chip info structure
 * @buf: buffer to store read data
 * @oob_required: caller requires OOB data read to chip->oob_poi
 * @page: page number to read
 *
 * Not for syndrome calculating ECC controllers, which use a special oob layout.
 */

int nand_read_page_benand(struct mtd_info *mtd, struct nand_chip *chip,
			  uint8_t *buf, int oob_required, int page)
{
	unsigned int max_bitflips = 0;

	chip->ecc.read_page_raw(mtd, chip, buf, oob_required, page);

	/* Check Read Status */
	max_bitflips = nand_benand_status_chk(mtd, chip);

	return max_bitflips;
}
EXPORT_SYMBOL(nand_read_page_benand);

int nand_read_subpage_benand(struct mtd_info *mtd, struct nand_chip *chip,
			uint32_t data_offs, uint32_t readlen, uint8_t *bufpoi)
{
	uint8_t *p;
	unsigned int max_bitflips = 0;

	if (data_offs != 0)
		chip->cmdfunc(mtd, NAND_CMD_RNDOUT, data_offs, -1);

	p = bufpoi + data_offs;
	chip->read_buf(mtd, p, readlen);

	max_bitflips = nand_benand_status_chk(mtd, chip);

	return max_bitflips;
}
EXPORT_SYMBOL(nand_read_subpage_benand);

void nand_benand_init(struct mtd_info *mtd)
{
	struct nand_chip *chip = mtd->priv;

	chip->options |= NAND_SUBPAGE_READ;

	switch (mtd->oobsize) {
	case 64:
		chip->ecc.layout = &benand_oob_64;
		break;
	case 128:
		chip->ecc.layout = &benand_oob_128;
		break;
	default:
		pr_warn("No oob scheme defined for oobsize %d\n",
				mtd->oobsize);
		BUG();
	}
}
EXPORT_SYMBOL(nand_benand_init);

MODULE_AUTHOR("INTEL Corporation");
MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("ECC-Free NAND (embedded ECC NAND) support");
