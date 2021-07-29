/*
 * (C) Copyright 2016 Intel Corporation
 * Author: William Widjaja <w.widjaja@intel.com>
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; version 2
 * of the License.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 */
#include <linux/module.h>
#include <linux/delay.h>
#include <linux/mtd/mtd.h>
#include <linux/mtd/partitions.h>
#include <linux/mtd/nand.h>
#include <linux/spi/spi.h>
#include <linux/of.h>

#include "ltq_spinand.h"

/*============================================================================*/
/* Macro and Switches */
/*============================================================================*/

/*******************************************************************************
 * fix wrong VID_HDR_OFFSET for UBI due to the minimum calculation involve
 * sub page RW size , so we must put no sub page option
 ******************************************************************************/
#define NONANDSUBPAGEREAD

/*******************************************************************************
 * No timeout while waiting for SPI NAND chip status to be ready
 ******************************************************************************/
#define NOTIMEOUT

/*============================================================================*/
/* Global Vars */
/*============================================================================*/

/*============================================================================*/
/* Helper functions  */
/*============================================================================*/

/*
 * mtd_to_privbuf - [INTERN] to convert mtd_info* to spinand_privbuf*
 * @mtd: MTD device structure
 * Description:
 *    Helper function to convert mtd_info* to spinand_privbuf*.
 */
static inline struct spinand_privbuf* mtd_to_privbuf(struct mtd_info *mtd)
{
	struct nand_chip *chip = (struct nand_chip *)mtd->priv;
	struct spinand_info *info = (struct spinand_info *)chip->priv;
	struct spinand_privbuf *state = (struct spinand_privbuf *)info->priv;

	return state;
}

/*
 * spi_to_info - [INTERN] to convert spi_device* to spinand_info*
 * @mtd: MTD device structure
 * Description:
 *    Helper function to convert spi_device* to spinand_info*.
 */
static inline struct spinand_info* spi_to_info(struct spi_device *spi)
{
	struct mtd_info *mtd = (struct mtd_info *)dev_get_drvdata((const struct device *)&(spi->dev));
	struct nand_chip *chip = (struct nand_chip *)mtd->priv;
	struct spinand_info *info = (struct spinand_info *)chip->priv;

	return info;
}

/*============================================================================*/
/* nand scan hook functions for SPI NAND */
/*============================================================================*/

#define LP_OPTIONS NAND_SAMSUNG_LP_OPTIONS

/*
 * The chip ID list:
 *    name, device ID, page size, chip size in MiB, eraseblock size, options
 *
 * If page size and eraseblock size are 0, the sizes are taken from the
 * extended chip ID.
 */
struct nand_flash_dev spinand_flash_ids[] = {

	{"SPI NAND Gigadevice 1Gbit 3.3v",
		{ .id = {0xc8, 0xb1} }, 2048, 128, 0x20000, LP_OPTIONS, 2, 128},
	{"SPI NAND Gigadevice 2Gbit 3.3v",
		{ .id = {0xc8, 0xb2} }, 2048, 256, 0x20000, LP_OPTIONS, 2, 128},
	{"SPI NAND Gigadevice 4Gbit 3.3v",
		{ .id = {0xc8, 0xb4} }, 4096, 512, 0x40000, LP_OPTIONS, 2, 256},
	{"SPI NAND Gigadevice 4Gbit 1.8v",
		{ .id = {0xc8, 0xA4} }, 4096, 512, 0x40000, LP_OPTIONS, 2, 256},
	{"SPI NAND Micron 128MiB 3,3V 8-bit",
		{ .id = {0x2c, 0x11} }, 2048, 128, 0x20000, LP_OPTIONS, 2, 64},
	{"SPI NAND Micron 128MiB 3,3V 8-bit",
		{ .id = {0x2c, 0x12} }, 2048, 128, 0x20000, LP_OPTIONS, 2, 64},
	{"SPI NAND MT29F2G01AAAED 256MiB",
		{ .id = {0x2c, 0x22} }, 2048, 256, 0x20000, LP_OPTIONS, 2, 64},
	{"SPI NAND MT29F4G01AAADD 512MiB",
		{ .id = {0x2c, 0x32} }, 2048, 512, 0x20000, LP_OPTIONS, 2, 64},
	{"SPI NAND TC58CVG0S3 1Gbit",
		{ .id = {0x98, 0xc2} }, 2048, 128, 0x20000, LP_OPTIONS, 2, 64},
	{"SPI NAND TC58CVG1S3 2Gbit",
		{ .id = {0x98, 0xcb} }, 2048, 256, 0x20000, LP_OPTIONS, 2, 64},
	{"SPI NAND TC58CVG2S0 4Gbit",
		{ .id = {0x98, 0xcd} }, 4096, 512, 0x40000, LP_OPTIONS, 2, 128},
	{"SPI NAND MX35LFE4AB 1Gbit",
		{ .id = {0xc2, 0x12} }, 2048, 128, 0x20000, LP_OPTIONS, 2, 64},
};

/**
*  Default OOB area specification layout
*/
static struct nand_ecclayout micron_ecc_layout_64 = {
	.eccbytes = 32,
	.eccpos = {
		   8, 9, 10, 11, 12, 13, 14, 15,
		   24, 25, 26, 27, 28, 29, 30, 21,
		   40, 41, 42, 43, 44, 45, 46, 47,
		   56, 57, 58, 59, 60, 61, 62, 63},
	.oobavail = 30,
	.oobfree = {
		{.offset = 2,
		 .length = 6},
		{.offset = 16,
		 .length = 8},
		{.offset = 32,
		 .length = 8},
		{.offset = 48,
		 .length = 8}, }
};

static struct nand_ecclayout gd5f_ecc_layout_256 = {
	.eccbytes = 128,
	.eccpos = {
		128, 129, 130, 131, 132, 133, 134, 135,
		136, 137, 138, 139, 140, 141, 142, 143,
		144, 145, 146, 147, 148, 149, 150, 151,
		152, 153, 154, 155, 156, 157, 158, 159,
		160, 161, 162, 163, 164, 165, 166, 167,
		168, 169, 170, 171, 172, 173, 174, 175,
		176, 177, 178, 179, 180, 181, 182, 183,
		184, 185, 186, 187, 188, 189, 190, 191,
		192, 193, 194, 195, 196, 197, 198, 199,
		200, 201, 202, 203, 204, 205, 206, 207,
		208, 209, 210, 211, 212, 213, 214, 215,
		216, 217, 218, 219, 220, 221, 222, 223,
		224, 225, 226, 227, 228, 229, 230, 231,
		232, 233, 234, 235, 236, 237, 238, 239,
		240, 241, 242, 243, 244, 245, 246, 247,
		248, 249, 250, 251, 252, 253, 254, 255
	},
	.oobavail = 127,
	.oobfree = { {1, 127} }
};

static struct nand_ecclayout gd5f_ecc_layout_128 = {
	.eccbytes = 64,
	.eccpos = {
		64, 65, 66, 67, 68, 69, 70, 72,
		72, 73, 74, 75, 76, 77, 78, 79,
		80, 81, 82, 83, 84, 85, 86, 87,
		88, 89, 90, 91, 92, 93, 94, 95,
		96, 97, 98, 99, 100, 101, 102, 103,
		104, 105, 106, 107, 108, 109, 110, 111,
		112, 113, 114, 115, 116, 117, 118, 119,
		120, 121, 122, 123, 124, 125, 126, 127,
	},
	.oobavail = 62,
	.oobfree = { {2, 63} }
};

static int spi_nand_manufacture_init(struct mtd_info *mtd, struct nand_chip *chip, struct nand_flash_dev *type)
{
	struct spinand_info *info = (struct spinand_info *)chip->priv;

	switch (type->mfr_id) {
	case NAND_MFR_MICRON:

		if (mtd->oobsize== 64)
			chip->ecc.layout = &micron_ecc_layout_64;

		chip->ecc.strength = 4; /* 4 bits correction per page region (512 bytes) */
		chip->ecc.size     = mtd->writesize >> 2;
		//chip->ecc.steps    = 4; /* 4 regions within page  NOTE: removed here since it is calculated in nand_scan_tail */
		chip->ecc.bytes    = 8; /* pretty sure it is 8 bytes ECC per sub page from oob layout */

		/*!<WW: This force BBT out of OOB area , they put it inside a inband */
		/* or possibly data area, im just concerned whether the reason it is put */
		/* into non oob because Internal ECC occupy the whole oob spare area ? */
		/* BUT WE HAVE TO MAKE IT MATCH WITH WHAT IT IS USED BY UBOOT, AND THEY */
		/* USE THE USUAL OOB AREA */
		/* NOTE:*/
		/* For much research, in MICRON Devices it does point it out to the problem BBT Marker is */
		/* put on byte 8 of OOB which is where ECC parity bytes is stored for Main 0 */
		/* or User data 0 , I THINK IT IS SAFER TO ENABLE THE OPTION NAND_BBT_NO_OOB */
		/* and move the BBT Marker out of OOB Area */
		chip->bbt_options |= NAND_BBT_NO_OOB;
		break;
	case NAND_MFR_TOSHIBA:
		if (mtd->oobsize == 64)
			chip->ecc.layout = &micron_ecc_layout_64; /* to make mtd happy , i really guess it entirely free*/

		/* !<WW: Toshiba Internal ECC 8 Bits per 528(512+16), but this is plus 16 bytes in OOB */
		/* It seem like ecc_step_ds expect just the page size step though so i put it */
		/* 2048 divided by 4 (one page is divided by 4 and paired each 512 bytes with 16 bytes in OOB)*/
		/*
		 * @steps:      number of ECC steps per page
		 * @size:       data bytes per ECC step
		 * @bytes:      ECC bytes per step
		 * @strength:   max number of correctible bits per ECC step
		 * @total:      total number of ECC bytes per page
		 */
		chip->ecc.strength = 8; /* 8 bits correction per page region (512 bytes) */
		chip->ecc.size	   = 512; /* sub page region (512 bytes) */
		//if (mtd->writesize == 8192 )
			//chip->ecc.steps    = 8; /* 8 regions / sub pages within page  NOTE: removed here since it is calculated in nand_scan_tail */
		//else
			//chip->ecc.steps    = 4; /* 4 regions within page  NOTE: removed here since it is calculated in nand_scan_tail */
		chip->ecc.bytes    = 16; /* !<TODO : it think the extra 64 bytes in OOB is the ECC bytes , since we hv 4 subpage so 16 */

		break;
	case NAND_MFR_MACRONIX:
		if (mtd->oobsize == 64)
			chip->ecc.layout = &micron_ecc_layout_64; /* to make mtd happy , i really guess it entirely free*/

		/* !<WW: MXIC Internal ECC 4 Bits per 528 Segment (512+16), but this is plus 16 bytes in OOB */
		/* It seem like ecc_step_ds expect just the page size step though so i put it */
		/* 2048 divided by 4 (one page is divided by 4 and paired each 512 bytes with 16 bytes in OOB)*/
		chip->ecc.strength = 4; /* 4 bits correction per page region (512 bytes) */
		chip->ecc.size     = mtd->writesize >> 2;
		//chip->ecc.steps    = 4; /* 4 regions within page */
		chip->ecc.bytes    = 8; /* !<TODO : ??? */

		break;

	case 0xC8: /* NAND_MFR_GIGADEVICE: */
		chip->ecc.strength = 8; /* 8 bits correction per page region (512 bytes) */
		chip->ecc.size     = mtd->writesize >> 2; /* page region (512 bytes) */
		//chip->ecc.steps    = 4; /* 4 regions within page, NOTE: removed here since it is calculated in nand_scan_tail */

		if (mtd->oobsize == 128) {
			chip->ecc.layout = &gd5f_ecc_layout_128;
			chip->ecc.bytes  = 16; /* 64 bytes ecc total so 16 bytes per 4 sub pages */
		}
		else if (mtd->oobsize == 256) {
			chip->ecc.layout = &gd5f_ecc_layout_256;
			chip->ecc.bytes  = 32; /* !<TODO : sorry i havent seen one chip like this, so had to assume 4 sub page so 128 / 4 = ???? */
		}

		info->options |= GIGADEVICE_DUMMY_TYPE;

		break;
	default:
		break;
	}

	return 0;
}

/*
 * Check if the NAND chip is SPI NAND flash, returns 1 if it is, 0 otherwise.
 */
int spinand_flash_detect(struct mtd_info *mtd, struct nand_chip *chip)
{
	int retval=0;
	u8 id_data[8];
	int i;
	struct nand_flash_dev *type = NULL;

	chip->cmdfunc(mtd, NAND_CMD_READID, 0x00, -1);
	for (i = 0; i < 3; i++)
		id_data[i] = chip->read_byte(mtd);

	if (!type)
		type = spinand_flash_ids;

	for (; type->name != NULL; type++)
		if ((id_data[0] == type->mfr_id) && (id_data[1] == type->dev_id))
	        	break;

	if (!type->name)
		goto probe_done;

	/* found */
	mtd->writesize = type->pagesize;
	mtd->erasesize = type->erasesize;
	mtd->oobsize   = type->oobsize;

	chip->chipsize = (type->chipsize) << 20;

	/* do we need it ? */
	chip->options |= type->options;

	/* manufacturer init */
	spi_nand_manufacture_init(mtd, chip, type);

	retval = 1;
probe_done:
	return retval;

};
EXPORT_SYMBOL(spinand_flash_detect);


/*============================================================================*/
/* internal functions */
/*============================================================================*/

/*
 * spinand_cmd - [INTERN] to process a command to send to the SPI Nand
 * @spi: spi device structure
 * @cmd: command structure
 * Description:
 *    Set up the command buffer to send to the SPI controller.
 *    The command buffer has to initialized to 0.
 */
static int spinand_cmd(struct spi_device *spi, struct spinand_cmd *cmd)
{
	struct spi_message message;
	struct spi_transfer x[4];
	u8 dummy = 0xff;

	spi_message_init(&message);
	memset(x, 0, sizeof(x));

	x[0].len = 1;
	x[0].tx_buf = &cmd->cmd;
	spi_message_add_tail(&x[0], &message);

	if (cmd->n_addr) {
		x[1].len = cmd->n_addr;
		x[1].tx_buf = cmd->addr;
		spi_message_add_tail(&x[1], &message);
	}

	if (cmd->n_dummy) {
		x[2].len = cmd->n_dummy;
		x[2].tx_buf = &dummy;
		spi_message_add_tail(&x[2], &message);
	}

	if (cmd->n_tx) {
		x[3].len = cmd->n_tx;
		x[3].tx_buf = cmd->tx_buf;
		spi_message_add_tail(&x[3], &message);
	}

	if (cmd->n_rx) {
		x[3].len = cmd->n_rx;
		x[3].rx_buf = cmd->rx_buf;
		spi_message_add_tail(&x[3], &message);
	}

	return spi_sync(spi, &message);
}

/*
 * spinand_read_id - [INTERN] Read SPI Nand ID
 * @spi: spi device structure
 * @id : 2 bytes result buffer
 * Description:
 *    Read ID: Generic read two ID bytes from the SPI Nand device, regardless
 *    of dummy bytes specific to manufacturer command
 */
static int spinand_read_id(struct spi_device *spi, u8 *id)
{
	int retval;
	u8 nand_id[3];
	struct spinand_cmd cmd = {0};

	cmd.cmd = CMD_READ_ID;
	cmd.n_rx = 3;
	cmd.rx_buf = &nand_id[0];

	retval = spinand_cmd(spi, &cmd);
	if (retval < 0) {
		dev_err(&spi->dev, "error %d reading id\n", retval);
		return retval;
	}

	id[0] = nand_id[0];
	id[1] = nand_id[1];
	if (nand_id[0] == 0 || nand_id[0] == 0xFF) {
		id[0] = nand_id[1];
		id[1] = nand_id[2];
	}

	return retval;
}

/*
 * spinand_read_status- [INTERN] send command 0xf to the SPI Nand status register
 * @spi: spi device structure
 * @status : content of status register result (1 byte)
 *
 * Description:
 *    After read, write, or erase, the Nand device is expected to set the
 *    busy status.
 *    This function is to allow reading the status of the command: read,
 *    write, and erase.
 *    Once the status turns to be ready, the other status bits also are
 *    valid status bits.
 */
static int spinand_read_status(struct spi_device *spi, uint8_t *status)
{
	struct spinand_cmd cmd = {0};
	int ret;

	cmd.cmd = CMD_READ_REG;
	cmd.n_addr = 1;
	cmd.addr[0] = REG_STATUS;
	cmd.n_rx = 1;
	cmd.rx_buf = status;

	ret = spinand_cmd(spi, &cmd);
	if (ret < 0)
		dev_err(&spi->dev, "err: %d read status register\n", ret);

	return ret;
}

/**
 * wait_till_ready - [INTERN] wait until SPI NAND chip report ready
 * @spi: the spi device.
 *
 * Description:
 *   Seem like this is used internally and seperate from spinand_wait
 *   which is NAND Interface wait, I don't like this. anyway for list this is
 *   used in:
 *    - spinand_read_page : to wait until spinand_read_page_to_cache ready
 *    - spinand_program_page : to wait until spinand_write_enable ready
 *    - spinand_erase_block : to wait until spinand_write_enable ready
 *    - spinand_reset : at the end to check if device is ready after reset + 1ms
 *    - spinand_cmdfunc : at NAND_CMD_RESET before calling spinand_reset
 *
 *   it is a concern since it is fixed value 40 ms for all diff kind situation ?
 *
 */
#define MAX_WAIT_MS  40
static int wait_till_ready(struct spi_device *spi)
{
	unsigned long deadline;
	int retval;
	u8 stat = 0;

	#ifdef NOTIMEOUT

	do {
		retval = spinand_read_status(spi, &stat);
		if (retval < 0)
			return -1;
		else if (!(stat & 0x1))
			break;

		cond_resched();
	} while (1);


	#else /* NOTIMEOUT */

	deadline = jiffies + msecs_to_jiffies(MAX_WAIT_MS);
	do {
		retval = spinand_read_status(spi, &stat);
		if (retval < 0)
			return -1;
		else if (!(stat & 0x1))
			break;

		cond_resched();
	} while (!time_after_eq(jiffies, deadline));

	#endif /* NOTIMEOUT */

	if ((stat & 0x1) == 0)
		return 0;

	return -1;
}

/**
 * spinand_get_otp - [INTERN] send command 0xf to read the SPI Nand OTP register
 * @spi: the spi device.
 * @otp: reg otp value 8bits
 *
 * Description:
 *   There is one bit( bit 0x10 ) to set or to clear the internal ECC.
 *   Enable chip internal ECC, set the bit to 1
 *   Disable chip internal ECC, clear the bit to 0
 */
static int spinand_get_otp(struct spi_device *spi, u8 *otp)
{
	struct spinand_cmd cmd = {0};
	int retval;

	cmd.cmd = CMD_READ_REG;
	cmd.n_addr = 1;
	cmd.addr[0] = REG_OTP;
	cmd.n_rx = 1;
	cmd.rx_buf = otp;

	retval = spinand_cmd(spi, &cmd);
	if (retval < 0)
		dev_err(&spi->dev, "error %d get otp\n", retval);
	return retval;
}

/**
 * spinand_set_otp - [INTERN] send command 0x1f to write the SPI Nand OTP register
 * @spi: the spi device.
 * @otp: reg otp value 8bits
 *
 * Description:
 *   There is one bit( bit 0x10 ) to set or to clear the internal ECC.
 *   Enable chip internal ECC, set the bit to 1
 *   Disable chip internal ECC, clear the bit to 0
 */
static int spinand_set_otp(struct spi_device *spi, u8 *otp)
{
	int retval;
	struct spinand_cmd cmd = {0};

	cmd.cmd = CMD_WRITE_REG,
	cmd.n_addr = 1,
	cmd.addr[0] = REG_OTP,
	cmd.n_tx = 1,
	cmd.tx_buf = otp,

	retval = spinand_cmd(spi, &cmd);
	if (retval < 0)
		dev_err(&spi->dev, "error %d set otp\n", retval);

	return retval;
}

/**
 * spinand_enable_ecc - [INTERN] send command 0x1f to write the SPI Nand OTP register
 * @spi: the spi device.
 *
 * Description:
 *   There is one bit( bit 0x10 ) to set or to clear the internal ECC.
 *   Enable chip internal ECC, set the bit to 1
 *   Disable chip internal ECC, clear the bit to 0
 */
static int spinand_enable_ecc(struct spi_device *spi)
{
	int retval;
	u8 otp = 0;

	retval = spinand_get_otp(spi, &otp);
	if (retval < 0)
		return retval;

	if ((otp & OTP_ECC_MASK) == OTP_ECC_MASK)
		return 0;
	otp |= OTP_ECC_MASK;
	retval = spinand_set_otp(spi, &otp);
	if (retval < 0)
		return retval;
	return spinand_get_otp(spi, &otp);
}

/**
 * spinand_disable_ecc - [INTERN] send command 0x1f to write the SPI Nand OTP register
 * @spi: the spi device.
 *-
 * Description:
 *   There is one bit( bit 0x10 ) to set or to clear the internal ECC.
 *   Enable chip internal ECC, set the bit to 1
 *   Disable chip internal ECC, clear the bit to 0
 */
static int spinand_disable_ecc(struct spi_device *spi)
{
	int retval;
	u8 otp = 0;

	retval = spinand_get_otp(spi, &otp);
	if (retval < 0)
		return retval;

	if ((otp & OTP_ECC_MASK) == OTP_ECC_MASK) {
		otp &= ~OTP_ECC_MASK;
		retval = spinand_set_otp(spi, &otp);
		if (retval < 0)
			return retval;
		return spinand_get_otp(spi, &otp);
	}
	return 0;
}

/**
 * spinand_write_enable - [INTERN] send command 0x06 to enable write or erase the
 * Nand cells
 * @spi: the spi device.
 *
 * Description:
 *   Before write and erase the Nand cells, the write enable has to be set.
 *   After the write or erase, the write enable bit is automatically
 *   cleared (status register bit 2)
 *   Set the bit 2 of the status register has the same effect
 */
static int spinand_write_enable(struct spi_device *spi)
{
	struct spinand_cmd cmd = {0};

	cmd.cmd = CMD_WR_ENABLE;
	return spinand_cmd(spi, &cmd);
}

/*
 * spinand_read_page_to_cache - [INTERN] to read a page with:
 * @spi: the spi device.
 * @page_id: the physical page number
 *
 * Description:
 *   The read commands to the Nand: 0x13 to read to SPI NAND chip internal cache
 *   Remember to Poll to read status to wait for tRD time.
 */
static int spinand_read_page_to_cache(struct spi_device *spi, int page_id)
{
	struct spinand_cmd cmd = {0};
	u16 row;

	row = page_id;
	cmd.cmd = CMD_READ;
	cmd.n_addr = 3;
	cmd.addr[0] = (u8) ((page_id & 0xff0000) >> 16);
	cmd.addr[1] = (u8)((page_id & 0xff00) >> 8);
	cmd.addr[2] = (u8)(page_id & 0x00ff);

	return spinand_cmd(spi, &cmd);
}

/*
 * spinand_read_from_cache - [INTERN] send command 0x03 to read out the data from the
 * cache register(2112 bytes max)
 * @spi: the spi device.
 * @page_id: the physical page number
 * @byte_id: column or offset within page
 * @len:     number of bytes to read
 * @rbuf:    read buffer to hold @len bytes
 *
 * Description:
 *   The read can specify 1 to 2112 bytes of data read at the corresponding
 *   locations.
 *   No tRd delay.
 */
static int spinand_read_from_cache(struct spi_device *spi, int page_id,
		u16 byte_id, u16 len, u8 *rbuf)
{
	struct mtd_info *mtd = (struct mtd_info *)dev_get_drvdata((const struct device *)&(spi->dev));
	struct nand_chip *chip = (struct nand_chip *)mtd->priv;
	struct spinand_info *info = (struct spinand_info *)chip->priv;
	struct spinand_cmd cmd = {0};
	u16 column;

	column = byte_id;
	cmd.cmd = CMD_READ_RDM;
	cmd.n_addr = 3;
	if (info->options & GIGADEVICE_DUMMY_TYPE) {
		cmd.addr[0] = 0;
		cmd.addr[1] = (u8)(column >> 8);
		cmd.addr[2] = (u8)column;
	} else {
		cmd.addr[0] = (u8)((column & 0xff00) >> 8);
		cmd.addr[1] = (u8)(column & 0x00ff);
		cmd.addr[2] = (u8)(0xff);
	}

	cmd.n_dummy = 0;
	cmd.n_rx = len;
	cmd.rx_buf = rbuf;

	return spinand_cmd(spi, &cmd);
}

/*
 * spinand_ecc_status - [INTERN] to check and report to mtd internal ecc status
 *                     after a page read:
 * @spi: the spi device.
 * @status:  REG STATUS value read from SPI NAND chip
 * @ecc_error: 0 for OK, 1 for error ?
 *
 * Description:
 *   to check and report to mtd internal ecc status after a page read
 */
static void spinand_ecc_status(struct spi_device *spi,
				     unsigned int status,
				     unsigned int *ecc_error)
{
	struct mtd_info *mtd = (struct mtd_info *)dev_get_drvdata((const struct device *)&(spi->dev));
	struct nand_chip *chip = (struct nand_chip *)mtd->priv;
	struct spinand_info *info = (struct spinand_info *)chip->priv;
	unsigned int ecc_status;

	if (info->options & GIGADEVICE_DUMMY_TYPE) {
		ecc_status = (status >> SPI_NAND_GD5F_ECC_SHIFT) &
				SPI_NAND_GD5F_ECC_MASK;
		*ecc_error = (ecc_status == SPI_NAND_GD5F_ECC_UNCORR);

	} else {
		ecc_status = (status >> SPI_NAND_MT29F_ECC_SHIFT) &
				SPI_NAND_MT29F_ECC_MASK;
		*ecc_error = (ecc_status == SPI_NAND_MT29F_ECC_UNCORR);
	}

	/*
	 * !<TODO: fix corrected bits, we can put this above and differentiate.
	 * gigadevice can straight away get num of error bit from status reg
	 * other manufacturer has a way to probe more detail e.g.:
	 *   - macronix with cmd 7Ch (For 1Gb only)
	 *   - Toshiba SPI NAND get feature from bit flip count */
	if (*ecc_error == 0) /* if not unrecoverable error */
		mtd->ecc_stats.corrected += ecc_status;
	else /* exceed correctable bits or error*/
		mtd->ecc_stats.failed++;

	return;

}

/*
 * spinand_read_page - [INTERN] to read a page with:
 * @spi: the spi device.
 * @page_id: the physical page number
 * @offset:  the location from 0 to 2111
 * @len:     number of bytes to read
 * @rbuf:    read buffer to hold @len bytes
 *
 * Description:
 *   The read includes two commands to the Nand: 0x13 and 0x03 commands
 *   Poll to read status to wait for tRD time.
 */
static int spinand_read_page(struct spi_device *spi, int page_id,
		u16 offset, u16 len, u8 *rbuf)
{
	int ret, ecc_error;
	u8 status = 0;

	ret = spinand_read_page_to_cache(spi, page_id);
	if (ret < 0)
		return ret;

	if (wait_till_ready(spi))
		dev_err(&spi->dev, "WAIT timedout!!!\n");

	while (1) {
		ret = spinand_read_status(spi, &status);
		if (ret < 0) {
			dev_err(&spi->dev,
					"err %d read status register\n", ret);
			return ret;
		}

		if ((status & STATUS_OIP_MASK) == STATUS_READY) {
			spinand_ecc_status(spi, status, &ecc_error);
			if (ecc_error) {
				dev_err(&spi->dev, "ecc error, page=%d\n",
						page_id);
				/* return on error ? or keep read ? it is a
				 * choice based on driver i saw*/
				// return 0;
			}
			break;
		}
	}

	ret = spinand_read_from_cache(spi, page_id, offset, len, rbuf);
	if (ret < 0) {
		dev_err(&spi->dev, "read from cache failed!!\n");
		return ret;
	}

	return ret;
}

/*
 * spinand_program_data_to_cache - [INTERN] to write a page to cache with:
 * @spi: the spi device.
 * @byte_id: the location to write to the cache
 * @len:     number of bytes to write
 * @rbuf:    read buffer to hold @len bytes
 *
 * Description:
 *   The write command used here is 0x84--indicating that the cache is
 *   not cleared first.
 *   Since it is writing the data to cache, there is no tPROG time.
 */
static int spinand_program_data_to_cache(struct spi_device *spi,
		int page_id, u16 byte_id, u16 len, u8 *wbuf)
{
	struct spinand_cmd cmd = {0};
	u16 column;

	column = byte_id;
	cmd.cmd = CMD_PROG_PAGE_CLRCACHE;
	cmd.n_addr = 2;
	cmd.addr[0] = (u8)((column & 0xff00) >> 8);
	cmd.addr[1] = (u8)(column & 0x00ff);
	cmd.n_tx = len;
	cmd.tx_buf = wbuf;

	return spinand_cmd(spi, &cmd);
}

/**
 * spinand_program_execute - [INTERN] to write a page from cache to the Nand array with
 * @spi: the spi device.
 * @page_id: the physical page location to write the page.
 *
 * Description:
 *   The write command used here is 0x10--indicating the cache is writing to
 *   the Nand array.
 *   Need to wait for tPROG time to finish the transaction.
 */
static int spinand_program_execute(struct spi_device *spi, int page_id)
{
	struct spinand_cmd cmd = {0};

	/* NOTE: this is changed so you can write above 128 MB */
	cmd.cmd = CMD_PROG_PAGE_EXC;
	cmd.n_addr = 3;
	cmd.addr[0] = (u8)((page_id & 0xff0000) >> 16);
	cmd.addr[1] = (u8)((page_id & 0xff00) >> 8);
	cmd.addr[2] = (u8)(page_id & 0x00ff);

	return spinand_cmd(spi, &cmd);
}


/**
 * spinand_program_page -[INTERN] to write a page with:
 * @spi: the spi device.
 * @page_id: the physical page location to write the page.
 * @offset:  the location from the cache starting from 0 to 2111
 * @len:     the number of bytes to write
 * @wbuf:    the buffer to hold the number of bytes
 *
 * Description:
 *   The commands used here are 0x06, 0x84, and 0x10--indicating that
 *   the write enable is first sent, the write cache command, and the
 *   write execute command.
 *   Poll to wait for the tPROG time to finish the transaction.
 */
static int spinand_program_page(struct spi_device *spi,
		int page_id, u16 offset, u16 len, u8 *buf)
{
	// struct mtd_info *mtd = (struct mtd_info *)dev_get_drvdata((const struct device *)&(spi->dev));
	int retval;
	u8 status = 0;
	uint8_t *wbuf;

	wbuf = buf;

	retval = spinand_write_enable(spi);
	if (retval < 0) {
		dev_err(&spi->dev, "write enable failed!!\n");
		return retval;
	}
	if (wait_till_ready(spi))
		dev_err(&spi->dev, "wait timedout!!!\n");

	retval = spinand_program_data_to_cache(spi, page_id,
			offset, len, wbuf);
	if (retval < 0)
		return retval;
	retval = spinand_program_execute(spi, page_id);
	if (retval < 0)
		return retval;
	while (1) {
		retval = spinand_read_status(spi, &status);
		if (retval < 0) {
			dev_err(&spi->dev,
					"error %d reading status register\n",
					retval);
			return retval;
		}

		if ((status & STATUS_OIP_MASK) == STATUS_READY) {
			if ((status & STATUS_P_FAIL_MASK) == STATUS_P_FAIL) {
				dev_err(&spi->dev,
					"program error, page %d\n", page_id);
				return -1;
			}
			break;
		}
	}

	return 0;
}


/**
 * spinand_erase_block_erase - [INTERN] to erase a page with:
 * @spi: the spi device.
 * @block_id: the physical block location to erase.
 *
 * Description:
 *   The command used here is 0xd8--indicating an erase command to erase
 *   one block--64 pages
 *   Need to wait for tERS.
 */
static int spinand_erase_block_erase(struct spi_device *spi, u32 block_id)
{
	struct spinand_cmd cmd = {0};
	u16 row;

	row = block_id;
	cmd.cmd = CMD_ERASE_BLK;
	cmd.n_addr = 3;
	cmd.addr[0] = (u8)((block_id & 0xff0000) >> 16);
	cmd.addr[1] = (u8)((block_id & 0xff00) >> 8);
	cmd.addr[2] = (u8)(block_id & 0x00ff);

	return spinand_cmd(spi, &cmd);
}

/**
 * spinand_erase_block - [INTERN] to erase a page with:
 * @spi: the spi device.
 * @block_id: the physical block location to erase.
 *
 * Description:
 *   The commands used here are 0x06 and 0xd8--indicating an erase
 *   command to erase one block--64 pages
 *   It will first to enable the write enable bit (0x06 command),
 *   and then send the 0xd8 erase command
 *   Poll to wait for the tERS time to complete the tranaction.
 */
static int spinand_erase_block(struct spi_device *spi, u32 block_id)
{
	int retval;
	u8 status = 0;

	retval = spinand_write_enable(spi);
	if (wait_till_ready(spi))
		dev_err(&spi->dev, "WAIT timedout!!!\n");

	retval = spinand_erase_block_erase(spi, block_id);
	while (1) {
		retval = spinand_read_status(spi, &status);
		if (retval < 0) {
			dev_err(&spi->dev,
					"error %d reading status register\n",
					(int) retval);
			return retval;
		}

		if ((status & STATUS_OIP_MASK) == STATUS_READY) {
			if ((status & STATUS_E_FAIL_MASK) == STATUS_E_FAIL) {
				dev_err(&spi->dev,
					"erase error, block %d\n", block_id);
				return -1;
			}
			break;
		}
	}
	return 0;
}

/**
 * spinand_lock_block- [INTERN] send write register 0x1f command to the Nand device
 * @spi: the spi device.
 * @lock: value to write (BL_ALL_UNLOCKED or BL_ALL_LOCKED)
 *
 * Description:
 *    After power up, all the Nand blocks are locked.  This function allows
 *    one to unlock the blocks, and so it can be written or erased.
 */
static int spinand_lock_block(struct spi_device *spi_nand, u8 lock)
{
	struct spinand_cmd cmd = {0};
	int ret;
	u8 otp = 0;

	ret = spinand_get_otp(spi_nand, &otp);

	cmd.cmd = CMD_WRITE_REG;
	cmd.n_addr = 1;
	cmd.addr[0] = REG_BLOCK_LOCK;
	cmd.n_tx = 1;
	cmd.tx_buf = &lock;

	ret = spinand_cmd(spi_nand, &cmd);
	if (ret < 0)
		dev_err(&spi_nand->dev, "error %d lock block\n", ret);

	return ret;
}

/**
 * spinand_reset - [INTERN] to issue reset cmd to chip
 * @spi: the spi device.
 *
 * Description:
 * SPI NAND reset function with cmd 0xFF
 */
static void spinand_reset(struct spi_device *spi)
{
	struct spinand_cmd cmd = {0};

	cmd.cmd = CMD_RESET;

	if (spinand_cmd(spi, &cmd) < 0)
		pr_info("spinand reset failed!\n");

	/* elapse 1ms before issuing any other command */
	udelay(1000);

	if (wait_till_ready(spi))
		dev_err(&spi->dev, "WAIT timedout!\n");

	/* safety try to unlock after reset */
	spinand_lock_block(spi, BL_ALL_UNLOCKED);

	if (wait_till_ready(spi))
		dev_err(&spi->dev, "WAIT timedout!\n");

	/* safety enable On-Die ECC again in case */
	spinand_enable_ecc(spi);

	return;
}

/*============================================================================*/
/* struct nand_ecc_ctrl - NAND Control structure for ECC */
/*============================================================================*/

/**
 * spinand_write_page_hwecc - [NAND ECC] hardware ECC based page write function
 * @mtd: mtd info structure
 * @chip: nand chip info structure
 * @buf: data buffer
 * @oob_required: must write chip->oob_poi to OOB
 */
static int spinand_write_page_hwecc(struct mtd_info *mtd,
		struct nand_chip *chip, const uint8_t *buf, int oob_required)
{
	const uint8_t *p = buf;
	int eccsize = chip->ecc.size;
	int eccsteps = chip->ecc.steps;

	chip->write_buf(mtd, p, eccsize * eccsteps);
	return 0;
}

/**
 * spinand_read_page_hwecc - [NAND ECC] hardware ECC based page read function
 * @mtd: mtd info structure
 * @chip: nand chip info structure
 * @buf: buffer to store read data
 * @oob_required: caller requires OOB data read to chip->oob_poi
 * @page: page number to read
 *
 * Not for syndrome calculating ECC controllers which need a special oob layout.
 */
static int spinand_read_page_hwecc(struct mtd_info *mtd, struct nand_chip *chip,
		uint8_t *buf, int oob_required, int page)
{
	u8 retval, status;
	uint8_t *p = buf;
	int eccsize = chip->ecc.size;
	int eccsteps = chip->ecc.steps;
	struct spinand_info *info = (struct spinand_info *)chip->priv;
	int ecc_error;

	chip->read_buf(mtd, p, eccsize * eccsteps);
	if (oob_required)
		chip->read_buf(mtd, chip->oob_poi, mtd->oobsize);

	while (1) {
		retval = spinand_read_status(info->spi, &status);
		if ((status & STATUS_OIP_MASK) == STATUS_READY) {
			spinand_ecc_status(info->spi, status, &ecc_error);
			break;
		}
	}
	return 0;

}

/*============================================================================*/
/* struct nand_chip - NAND Private Flash Chip Data Interface functions */
/*============================================================================*/

/**
 * spinand_select_chip - [NAND Interface] control CE line
 * @mtd: MTD device structure
 * @chipnr: chipnumber to select, -1 for deselect
 *
 * Default select function for 1 chip devices.
 */
static void spinand_select_chip(struct mtd_info *mtd, int dev)
{
	return;
}

/**
 * spinand_read_byte - [NAND Interface] read one byte from the chip
 * @mtd: MTD device structure
 *
 * Description:
 * SPI NAND read one byte function for 8bit buswidth
 */
static uint8_t spinand_read_byte(struct mtd_info *mtd)
{
	struct spinand_privbuf *state = mtd_to_privbuf(mtd);
	u8 data;

	data = state->buf[state->buf_ptr];
	state->buf_ptr++;
	return data;
}

/**
 * spinand_wait - [NAND Interface] wait until the command is done
 * @mtd: MTD device structure
 * @chip: NAND chip structure
 *
 * Description:
 * Wait for command done. This applies to erase and program only. Erase can
 * take up to 400ms and program up to 20ms according to general NAND and
 * SmartMedia specs.
 */
static int spinand_wait(struct mtd_info *mtd, struct nand_chip *chip)
{
	struct spinand_info *info = (struct spinand_info *)chip->priv;

	unsigned long timeo = jiffies;
	int retval, state = chip->state;
	u8 status;

	if (state == FL_ERASING)
		timeo += msecs_to_jiffies(400);
	else
		timeo += msecs_to_jiffies(20);

	while (time_before(jiffies, timeo)) {
		retval = spinand_read_status(info->spi, &status);
		if ((status & STATUS_OIP_MASK) == STATUS_READY)
			return 0;

		cond_resched();
	}
	return 0;
}

/**
 * spinand_write_buf - [NAND Interface] write buffer to chip
 * @mtd: MTD device structure
 * @buf: data buffer
 * @len: number of bytes to write
 *
 * Description:
 * SPI NAND write function for 8bit buswidth.
 */
static void spinand_write_buf(struct mtd_info *mtd, const uint8_t *buf, int len)
{

	struct spinand_privbuf *state = mtd_to_privbuf(mtd);

	memcpy(state->buf + state->buf_ptr, buf, len);
	state->buf_ptr += len;
}

/**
 * spinand_read_buf - [NAND Interface] read chip data into buffer
 * @mtd: MTD device structure
 * @buf: buffer to store date
 * @len: number of bytes to read
 *
 * Description:
 * SPI NAND read function for 8bit buswidth.
 */
static void spinand_read_buf(struct mtd_info *mtd, uint8_t *buf, int len)
{
	struct spinand_privbuf *state = mtd_to_privbuf(mtd);

	memcpy(buf, state->buf + state->buf_ptr, len);
	state->buf_ptr += len;
}

/*
 * spinand_cmdfunc - [NAND Interface] Translate NAND HW cmd into action
 *     command to SPI NAND chip
 * @mtd: MTD device structure
 * @command: the command to be sent
 * @column: the column address for this command, -1 if none
 * @page_addr: the page address for this command, -1 if none
 *
 * Description:
 *   Send command to SPI NAND device.
 */
static void spinand_cmdfunc(struct mtd_info *mtd, unsigned int command,
		int column, int page_addr)
{
	struct nand_chip *chip = (struct nand_chip *)mtd->priv;
	struct spinand_info *info = (struct spinand_info *)chip->priv;
	struct spinand_privbuf *state = (struct spinand_privbuf *)info->priv;

	switch (command) {
	/*
	 * READ0 - read in page + oob bytes
	 */
	case NAND_CMD_READ1:
	case NAND_CMD_READ0:
		/*
		 * !<NOTE: I have a choice , i implement here, or I emptied it
		 * and I do everything in chip->ecc.read_page, might be
		 * good idea since then i can do RAW mode without ECC on
		 * chip->ecc.read_page_raw
		 */
		state->buf_ptr = 0;
		spinand_read_page(info->spi, page_addr, 0x0, mtd->writesize + mtd->oobsize, state->buf);
		break;
	/* READOOB reads only the OOB because no ECC is performed. */
	case NAND_CMD_READOOB:
		/*
		 * !<NOTE: Another choices, i do it here or I overload related
		 * to oob interfaces like :
		 *   chip->block_bad
		 *   chip->ecc.read_oob
		 *   chip->ecc.write_oob
		 */
		state->buf_ptr = 0;
		spinand_read_page(info->spi, page_addr, mtd->writesize, mtd->oobsize, state->buf);
		break;
	case NAND_CMD_RNDOUT:
		state->buf_ptr = column;
		break;
	case NAND_CMD_READID:
		state->buf_ptr = 0;
		spinand_read_id(info->spi, (u8 *)state->buf);
		break;
	case NAND_CMD_PARAM:
		state->buf_ptr = 0;
		break;
	/* ERASE1 stores the block and page address */
	case NAND_CMD_ERASE1:
		spinand_erase_block(info->spi, page_addr);
		break;
	/* ERASE2 uses the block and page address from ERASE1 */
	case NAND_CMD_ERASE2:
		break;
	/* SEQIN sets up the addr buffer and all registers except the length */
	case NAND_CMD_SEQIN:
		state->col = column;
		state->row = page_addr;
		state->buf_ptr = 0;
		break;
	/* PAGEPROG reuses all of the setup from SEQIN and adds the length */
	case NAND_CMD_PAGEPROG:
		spinand_program_page(info->spi, state->row, state->col,
				state->buf_ptr, state->buf);
		break;
	case NAND_CMD_STATUS:
		spinand_get_otp(info->spi, state->buf);
		if (!(state->buf[0] & 0x80))
			state->buf[0] = 0x80;
		state->buf_ptr = 0;
		break;
	/* RESET command */
	case NAND_CMD_RESET:
		if (wait_till_ready(info->spi))
			dev_err(&info->spi->dev, "WAIT timedout!!!\n");
		/* a minimum of 250us must elapse before issuing RESET cmd*/
		udelay(250);
		spinand_reset(info->spi);
		break;
	default:
		dev_err(&mtd->dev, "Unknown CMD: 0x%x\n", command);
	}
}

/*============================================================================*/
/* struct spi_driver Interface functions */
/*============================================================================*/

/*
 * spinand_probe - [struct spi_driver Interface]
 * @spi: registered device driver.
 *
 * Description:
 *   To set up the device driver parameters to make the device available.
 *   Binds this driver to the spi device.  Drivers can verify
 *	 that the device is actually present, and may need to configure
 *	 characteristics (such as bits_per_word) which weren't needed for
 *	 the initial configuration done during system setup.
 */
static int spinand_probe(struct spi_device *spi)
{
	struct mtd_info *mtd;
	struct nand_chip *chip;
	struct spinand_info *info;
	struct spinand_privbuf *state;
	struct mtd_part_parser_data ppdata;
	const char __maybe_unused	*of_mtd_name = NULL;

	of_property_read_string(spi->dev.of_node,
				"linux,mtd-name", &of_mtd_name);

	info  = devm_kzalloc(&spi->dev, sizeof(struct spinand_info),
			GFP_KERNEL);

	if (!info)
		return -ENOMEM;

	/* back reference to spi_device */
	info->spi = spi;

	//spinand_lock_block(spi, BL_ALL_UNLOCKED);

	state = devm_kzalloc(&spi->dev, sizeof(struct spinand_privbuf),
			GFP_KERNEL);
	if (!state)
		return -ENOMEM;

	info->priv	= state;
	state->buf_ptr	= 0;
	state->buf	= devm_kzalloc(&spi->dev,
					NAND_MAX_PAGESIZE + NAND_MAX_OOBSIZE,
					GFP_KERNEL);

	if (!state->buf)
		return -ENOMEM;

	chip = devm_kzalloc(&spi->dev, sizeof(struct nand_chip),
				GFP_KERNEL);
	if (!chip)
		return -ENOMEM;

	/* --- setup and overload specific SPI NAND ECC functions --- */
	/* NOTE: Again NAND_ECC_HW is meant for HW ECC on NFC (NAND flash controller)
	 * There is actually an effort on the NAND framework itself to support the
	 * correct Internal or On-Die ECC mode called NAND_ECC_HW_ON_DIE but
	 * maybe haven't made it upstream
	 * https://patchwork.ozlabs.org/patch/454442/
	 */
	chip->ecc.mode	= NAND_ECC_HW;

	/* seem like i can only fill this if i hook a function spinand_probe
	 * inside nand_get_flash_type and then we do it according to read id
	 */
	//chip->ecc.size	= 0x200;
	//chip->ecc.bytes	= 0x6;
	//chip->ecc.steps	= 0x4;

	//chip->ecc.strength = 1;
	//chip->ecc.total	= chip->ecc.steps * chip->ecc.bytes;
	///chip->ecc.layout = &spinand_oob_64;
	chip->ecc.read_page = spinand_read_page_hwecc;
	chip->ecc.write_page = spinand_write_page_hwecc;

	/* -- replace and overload SPI NAND functions to NAND CHIP struct --- */
	chip->priv	= info;
	chip->read_buf	= spinand_read_buf;
	chip->write_buf	= spinand_write_buf;
	chip->read_byte	= spinand_read_byte;
	chip->cmdfunc	= spinand_cmdfunc;
	chip->waitfunc	= spinand_wait;
	chip->options	|= NAND_CACHEPRG;
	#ifdef NONANDSUBPAGEREAD
	chip->options	|= NAND_NO_SUBPAGE_WRITE;
	#endif /* NONANDSUBPAGEREAD */
	chip->bbt_options = NAND_BBT_USE_FLASH | NAND_BBT_CREATE_EMPTY;
	chip->select_chip = spinand_select_chip;

	mtd = devm_kzalloc(&spi->dev, sizeof(struct mtd_info), GFP_KERNEL);
	if (!mtd)
		return -ENOMEM;

	dev_set_drvdata(&spi->dev, mtd);

	mtd->priv = chip;
	if (of_mtd_name)
		mtd->name = of_mtd_name;
	else
		mtd->name = dev_name(&spi->dev);
	mtd->owner = THIS_MODULE;
	//mtd->oobsize = 64;

	if (nand_scan(mtd, 1))
		return -ENXIO;

	ppdata.of_node = spi->dev.of_node;

	/* type is null meaning use default parsers which usually are
	 * "cmdlinepart" and "ofparts" (mtdparts bootargs & device tree)*/
	return mtd_device_parse_register(mtd, NULL, &ppdata, NULL, 0);
}


/*
 * spinand_remove - [struct spi_driver Interface]
 * @spi: the spi device.
 *
 * Description:
 *   To remove the device driver parameters and free up allocated memories.
 *   Unbinds this driver from the spi device
 */
static int spinand_remove(struct spi_device *spi)
{
	mtd_device_unregister(dev_get_drvdata(&spi->dev));

	return 0;
}

static const struct of_device_id ltq_spinand_dt[] = {
	{ .compatible = "lantiq,generic-spinand", },
	{}
};

/*
 * SPI Driver name structure description
 */
static struct spi_driver ltq_spinand_driver = {
	.driver = {
		.name		= "ltq_spinand",
		.bus		= &spi_bus_type,
		.owner		= THIS_MODULE,
		.of_match_table	= ltq_spinand_dt,
	},
	.probe		= spinand_probe,
	.remove		= spinand_remove,
};

module_spi_driver(ltq_spinand_driver);

MODULE_DESCRIPTION("Lantiq Generic SPI NAND driver");
MODULE_AUTHOR("William Widjaja <w.widjaja@intel.com>");
MODULE_LICENSE("GPL v2");
