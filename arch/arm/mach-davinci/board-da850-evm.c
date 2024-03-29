/*
 * TI DA850/OMAP-L138 EVM board
 *
 * Copyright (C) 2009 Texas Instruments Incorporated - http://www.ti.com/
 *
 * Derived from: arch/arm/mach-davinci/board-da830-evm.c
 * Original Copyrights follow:
 *
 * 2007, 2009 (c) MontaVista Software, Inc. This file is licensed under
 * the terms of the GNU General Public License version 2. This program
 * is licensed "as is" without any warranty of any kind, whether express
 * or implied.
 */
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/console.h>
#include <linux/i2c.h>
#include <linux/i2c/at24.h>
#include <linux/i2c/pca953x.h>
#include <linux/input.h>
#include <linux/mfd/tps6507x.h>
#include <linux/gpio.h>
#include <linux/gpio_keys.h>
#include <linux/platform_device.h>
#include <linux/interrupt.h>
#include <linux/mtd/mtd.h>
#include <linux/mtd/nand.h>
#include <linux/mtd/partitions.h>
#include <linux/regulator/machine.h>
#include <linux/regulator/tps6507x.h>
#include <linux/input/tps6507x-ts.h>
#include <linux/spi/spi.h>
#include <linux/spi/flash.h>
#include <linux/delay.h>
#include <linux/i2c-gpio.h>
#include <linux/pwm_backlight.h>
#include <linux/wl12xx.h>

#include <asm/mach-types.h>
#include <asm/mach/arch.h>

#include <mach/cp_intc.h>
#include <mach/da8xx.h>
#include <mach/nand.h>
#include <mach/mux.h>
#include <mach/aemif.h>
#include <mach/spi.h>
#include <mach/flash.h>
#include <mach/usb.h>
#include <mach/vpif.h>
#include <media/davinci/videohd.h>

#include <media/tvp514x.h>

#define DA850_EVM_PHY_ID		"0:00"
#define DA850_LCD_PWR_PIN		GPIO_TO_PIN(2, 8)
#define DA850_LCD_BL_PIN		GPIO_TO_PIN(2, 15)

#define DA850_MMCSD_CD_PIN		GPIO_TO_PIN(4, 0)
#define DA850_MMCSD_WP_PIN		GPIO_TO_PIN(4, 1)

#define DA850_MII_MDIO_CLKEN_PIN	GPIO_TO_PIN(2, 6)

#define DA850_SD_ENABLE_PIN		GPIO_TO_PIN(0, 11)

#define DA850_WLAN_EN			GPIO_TO_PIN(6, 9)
#define DA850_WLAN_IRQ			GPIO_TO_PIN(6, 10)

#define DAVINCI_BACKLIGHT_MAX_BRIGHTNESS	250
#define DAVINVI_BACKLIGHT_DEFAULT_BRIGHTNESS	250
#define DAVINCI_PWM_PERIOD_NANO_SECONDS		(10000 * 10)

#define PWM_DEVICE_ID	"ehrpwm.1"


/* Enabling GPIO for WL1271's Bluetooth */
#define WL1271_BT_EN_GPIO GPIO_TO_PIN(0, 15)

/* Enabling GPIOs for WL1271's BT, FM, GPS respectively (-1 if not used) */
static int gpios[] = { WL1271_BT_EN_GPIO, -1, -1};

static struct platform_device wl1271_device = {
       .name           = "kim",
       .id             = -1,
       .dev.platform_data = &gpios,
};


static struct platform_pwm_backlight_data da850evm_backlight_data = {
	.pwm_id		= PWM_DEVICE_ID,
	.ch		= 0,
	.max_brightness	= DAVINCI_BACKLIGHT_MAX_BRIGHTNESS,
	.dft_brightness	= DAVINVI_BACKLIGHT_DEFAULT_BRIGHTNESS,
	.pwm_period_ns	= DAVINCI_PWM_PERIOD_NANO_SECONDS,
};

static struct platform_device da850evm_backlight = {
	.name		= "pwm-backlight",
	.id		= -1,
	.dev		= {
		.platform_data	= &da850evm_backlight_data,
	}
};

static struct davinci_spi_platform_data da850evm_spi1_pdata = {
	.version	= SPI_VERSION_2,
	.num_chipselect = 1,
	.intr_line      = 1,
};

static struct mtd_partition da850evm_spiflash_part[] = {
	[0] = {
		.name = "UBL",
		.offset = 0,
		.size = SZ_64K,
		.mask_flags = MTD_WRITEABLE,
	},
	[1] = {
		.name = "U-Boot",
		.offset = MTDPART_OFS_APPEND,
		.size = SZ_512K,
		.mask_flags = MTD_WRITEABLE,
	},
	[2] = {
		.name = "U-Boot-Env",
		.offset = MTDPART_OFS_APPEND,
		.size = SZ_64K,
		.mask_flags = MTD_WRITEABLE,
	},
	[3] = {
		.name = "Kernel",
		.offset = MTDPART_OFS_APPEND,
		.size = SZ_2M + SZ_512K,
		.mask_flags = 0,
	},
	[4] = {
		.name = "Filesystem",
		.offset = MTDPART_OFS_APPEND,
		.size = SZ_4M,
		.mask_flags = 0,
	},
	[5] = {
		.name = "MAC-Address",
		.offset = SZ_8M - SZ_64K,
		.size = SZ_64K,
		.mask_flags = MTD_WRITEABLE,
	},
};

static struct flash_platform_data da850evm_spiflash_data = {
	.name		= "m25p80",
	.parts		= da850evm_spiflash_part,
	.nr_parts	= ARRAY_SIZE(da850evm_spiflash_part),
};

static struct davinci_spi_config da850evm_spiflash_cfg = {
	.io_type	= SPI_IO_TYPE_DMA,
	.c2tdelay	= 8,
	.t2cdelay	= 8,
};

static struct spi_board_info da850evm_spi_info[] = {
	{
		.modalias		= "m25p80",
		.platform_data		= &da850evm_spiflash_data,
		.controller_data	= &da850evm_spiflash_cfg,
		.mode			= SPI_MODE_0,
		.max_speed_hz		= 30000000,
		.bus_num		= 1,
		.chip_select		= 0,
	},
};

static void m25p80_notify_add(struct mtd_info *mtd)
{
	char *mac_addr = davinci_soc_info.emac_pdata->mac_addr;
	size_t retlen;

	if (!strcmp(mtd->name, "MAC-Address")) {
		mtd->read(mtd, 0, ETH_ALEN, &retlen, mac_addr);
		if (retlen == ETH_ALEN)
			pr_info("Read MAC addr from SPI Flash: %pM\n",
					mac_addr);
	}
}

static struct mtd_notifier spi_notifier = {
	.add    = m25p80_notify_add,
};

static void __init da850evm_init_spi1(struct spi_board_info *info, unsigned len)
{
	int ret;

	ret = spi_register_board_info(info, len);
	if (ret)
		pr_warning("failed to register board info : %d\n", ret);

	ret = da8xx_register_spi(1, &da850evm_spi1_pdata);
	if (ret)
		pr_warning("failed to register spi 1 device : %d\n", ret);

	if (!(system_rev & 0x100))
		register_mtd_user(&spi_notifier);
}

#define TVP5147_CH0		"tvp514x-0"
#define TVP5147_CH1		"tvp514x-1"

#define VPIF_STATUS	(0x002C)
#define VPIF_STATUS_CLR	(0x0030)

static struct mtd_partition da850_evm_norflash_partition[] = {
	{
		.name           = "bootloaders + env",
		.offset         = 0,
		.size           = SZ_512K,
		.mask_flags     = MTD_WRITEABLE,
	},
	{
		.name           = "kernel",
		.offset         = MTDPART_OFS_APPEND,
		.size           = SZ_2M,
		.mask_flags     = 0,
	},
	{
		.name           = "filesystem",
		.offset         = MTDPART_OFS_APPEND,
		.size           = MTDPART_SIZ_FULL,
		.mask_flags     = 0,
	},
};

static struct davinci_aemif_timing da850_evm_norflash_timing = {
	.wsetup		= 10,
	.wstrobe	= 60,
	.whold		= 10,
	.rsetup		= 10,
	.rstrobe	= 110,
	.rhold		= 10,
	.ta		= 30,
};

static struct davinciflash_pdata da850_evm_norflash_data = {
	.width		= 2,
	.parts		= da850_evm_norflash_partition,
	.nr_parts	= ARRAY_SIZE(da850_evm_norflash_partition),
	.timing		= &da850_evm_norflash_timing,
};

static struct resource da850_evm_norflash_resource[] = {
	{
		.start	= DA8XX_AEMIF_CS2_BASE,
		.end	= DA8XX_AEMIF_CS2_BASE + SZ_32M - 1,
		.flags	= IORESOURCE_MEM,
	},
	{
		.start	= DA8XX_AEMIF_CTL_BASE,
		.end	= DA8XX_AEMIF_CTL_BASE + SZ_32K - 1,
		.flags	= IORESOURCE_MEM,
	},
};

static struct platform_device da850_evm_norflash_device = {
	.name		= "davinci-flash",
	.id		= 0,
	.dev		= {
		.platform_data  = &da850_evm_norflash_data,
	},
	.num_resources	= ARRAY_SIZE(da850_evm_norflash_resource),
	.resource	= da850_evm_norflash_resource,
};

static struct davinci_pm_config da850_pm_pdata = {
	.sleepcount = 128,
};

static struct platform_device da850_pm_device = {
	.name           = "pm-davinci",
	.dev = {
		.platform_data	= &da850_pm_pdata,
	},
	.id             = -1,
};

/* DA850/OMAP-L138 EVM includes a 512 MByte large-page NAND flash
 * (128K blocks). It may be used instead of the (default) SPI flash
 * to boot, using TI's tools to install the secondary boot loader
 * (UBL) and U-Boot.
 */
static struct mtd_partition da850_evm_nandflash_partition[] = {
	{
		.name		= "u-boot env",
		.offset		= 0,
		.size		= SZ_128K,
		.mask_flags	= MTD_WRITEABLE,
	 },
	{
		.name		= "UBL",
		.offset		= MTDPART_OFS_APPEND,
		.size		= SZ_128K,
		.mask_flags	= MTD_WRITEABLE,
	},
	{
		.name		= "u-boot",
		.offset		= MTDPART_OFS_APPEND,
		.size		= 4 * SZ_128K,
		.mask_flags	= MTD_WRITEABLE,
	},
	{
		.name		= "kernel",
		.offset		= 0x200000,
		.size		= SZ_4M,
		.mask_flags	= 0,
	},
	{
		.name		= "filesystem",
		.offset		= MTDPART_OFS_APPEND,
		.size		= MTDPART_SIZ_FULL,
		.mask_flags	= 0,
	},
};

static struct davinci_aemif_timing da850_evm_nandflash_timing = {
	.wsetup		= 24,
	.wstrobe	= 21,
	.whold		= 14,
	.rsetup		= 19,
	.rstrobe	= 50,
	.rhold		= 0,
	.ta		= 20,
};

static struct davinci_nand_pdata da850_evm_nandflash_data = {
	.parts		= da850_evm_nandflash_partition,
	.nr_parts	= ARRAY_SIZE(da850_evm_nandflash_partition),
	.ecc_mode	= NAND_ECC_HW,
	.ecc_bits	= 4,
	.options	= NAND_USE_FLASH_BBT,
	.timing		= &da850_evm_nandflash_timing,
};

static struct resource da850_evm_nandflash_resource[] = {
	{
		.start	= DA8XX_AEMIF_CS3_BASE,
		.end	= DA8XX_AEMIF_CS3_BASE + SZ_512K + 2 * SZ_1K - 1,
		.flags	= IORESOURCE_MEM,
	},
	{
		.start	= DA8XX_AEMIF_CTL_BASE,
		.end	= DA8XX_AEMIF_CTL_BASE + SZ_32K - 1,
		.flags	= IORESOURCE_MEM,
	},
};

static struct platform_device da850_evm_nandflash_device = {
	.name		= "davinci_nand",
	.id		= 1,
	.dev		= {
		.platform_data	= &da850_evm_nandflash_data,
	},
	.num_resources	= ARRAY_SIZE(da850_evm_nandflash_resource),
	.resource	= da850_evm_nandflash_resource,
};

static struct platform_device *da850_evm_devices[] __initdata = {
	&da850_evm_nandflash_device,
	&da850_evm_norflash_device,
};

static const short da850_evm_nand_pins[] = {
	DA850_EMA_D_0, DA850_EMA_D_1, DA850_EMA_D_2, DA850_EMA_D_3,
	DA850_EMA_D_4, DA850_EMA_D_5, DA850_EMA_D_6, DA850_EMA_D_7,
	DA850_EMA_A_1, DA850_EMA_A_2, DA850_NEMA_CS_3, DA850_NEMA_CS_4,
	DA850_NEMA_WE, DA850_NEMA_OE,
	-1
};

static const short da850_evm_nor_pins[] = {
	DA850_EMA_BA_1, DA850_EMA_CLK, DA850_EMA_WAIT_1, DA850_NEMA_CS_2,
	DA850_NEMA_WE, DA850_NEMA_OE, DA850_EMA_D_0, DA850_EMA_D_1,
	DA850_EMA_D_2, DA850_EMA_D_3, DA850_EMA_D_4, DA850_EMA_D_5,
	DA850_EMA_D_6, DA850_EMA_D_7, DA850_EMA_D_8, DA850_EMA_D_9,
	DA850_EMA_D_10, DA850_EMA_D_11, DA850_EMA_D_12, DA850_EMA_D_13,
	DA850_EMA_D_14, DA850_EMA_D_15, DA850_EMA_A_0, DA850_EMA_A_1,
	DA850_EMA_A_2, DA850_EMA_A_3, DA850_EMA_A_4, DA850_EMA_A_5,
	DA850_EMA_A_6, DA850_EMA_A_7, DA850_EMA_A_8, DA850_EMA_A_9,
	DA850_EMA_A_10, DA850_EMA_A_11, DA850_EMA_A_12, DA850_EMA_A_13,
	DA850_EMA_A_14, DA850_EMA_A_15, DA850_EMA_A_16, DA850_EMA_A_17,
	DA850_EMA_A_18, DA850_EMA_A_19, DA850_EMA_A_20, DA850_EMA_A_21,
	DA850_EMA_A_22, DA850_EMA_A_23,
	-1
};

static u32 ui_card_detected;

#if defined(CONFIG_MMC_DAVINCI) || \
    defined(CONFIG_MMC_DAVINCI_MODULE)
#define HAS_MMC 1
#else
#define HAS_MMC 0
#endif

/* have_imager() - Check if we have support for imager interface */
static inline int have_imager(void)
{
#if defined(CONFIG_DA850_UI_CAMERA)
	return 1;
#else
	return 0;
#endif
}

static inline void da850_evm_setup_nor_nand(void)
{
	int ret = 0;

	if (ui_card_detected && !HAS_MMC) {
		ret = davinci_cfg_reg_list(da850_evm_nand_pins);
		if (ret)
			pr_warning("da850_evm_init: nand mux setup failed: "
					"%d\n", ret);

		ret = davinci_cfg_reg(DA850_GPIO0_11);
		if (ret)
			pr_warning("da850_evm_init:GPIO(0,11) mux setup "
					"failed\n");

		ret = gpio_request(DA850_SD_ENABLE_PIN, "mmc_sd_en");
		if (ret)
			pr_warning("Cannot open GPIO %d\n",
					DA850_SD_ENABLE_PIN);

		/* Driver GP0[11] low for NOR to work */
		gpio_direction_output(DA850_SD_ENABLE_PIN, 0);

		ret = davinci_cfg_reg_list(da850_evm_nor_pins);
		if (ret)
			pr_warning("da850_evm_init: nor mux setup failed: %d\n",
				ret);

		platform_add_devices(da850_evm_devices,
					ARRAY_SIZE(da850_evm_devices));
	} else if (ui_card_detected && HAS_MMC) {
		/*
		 * On Logic PD Rev.3 EVMs GP0[11] pin needs to be configured
		 * for MMC and NOR to work. When GP0[11] is low, the SD0
		 * interface will not work, but NOR flash will. When GP0[11]
		 * is high, SD0 will work but NOR flash will not. By default
		 * we are assuming that GP0[11] pin is driven high, when UI
		 * card is not connected. Hence we are not configuring the
		 * GP0[11] pin when MMC/SD is enabled and UI card is not
		 * connected. Not configuring the GPIO pin will enable the
		 * bluetooth to work on AM18x as it requires the GP0[11]
		 * pin for UART flow control.
		 */
		ret = davinci_cfg_reg(DA850_GPIO0_11);
		if (ret)
			pr_warning("da850_evm_init:GPIO(0,11) mux setup "
					"failed\n");

		ret = gpio_request(DA850_SD_ENABLE_PIN, "mmc_sd_en");
		if (ret)
			pr_warning("Cannot open GPIO %d\n",
					DA850_SD_ENABLE_PIN);

		/* Driver GP0[11] high for SD to work */
		gpio_direction_output(DA850_SD_ENABLE_PIN, 1);
	}
}

#ifdef CONFIG_DA850_UI_RMII
static inline void da850_evm_setup_emac_rmii(int rmii_sel)
{
	struct davinci_soc_info *soc_info = &davinci_soc_info;

	soc_info->emac_pdata->rmii_en = 1;
	gpio_set_value_cansleep(rmii_sel, 0);
}
#else
static inline void da850_evm_setup_emac_rmii(int rmii_sel) { }
#endif


#define DA850_KEYS_DEBOUNCE_MS	10
/*
 * At 200ms polling interval it is possible to miss an
 * event by tapping very lightly on the push button but most
 * pushes do result in an event; longer intervals require the
 * user to hold the button whereas shorter intervals require
 * more CPU time for polling.
 */
#define DA850_GPIO_KEYS_POLL_MS	200

enum da850_evm_ui_exp_pins {
	DA850_EVM_UI_EXP_SEL_C = 5,
	DA850_EVM_UI_EXP_SEL_B,
	DA850_EVM_UI_EXP_SEL_A,
	DA850_EVM_UI_EXP_PB8,
	DA850_EVM_UI_EXP_PB7,
	DA850_EVM_UI_EXP_PB6,
	DA850_EVM_UI_EXP_PB5,
	DA850_EVM_UI_EXP_PB4,
	DA850_EVM_UI_EXP_PB3,
	DA850_EVM_UI_EXP_PB2,
	DA850_EVM_UI_EXP_PB1,
};

static const char const *da850_evm_ui_exp[] = {
	[DA850_EVM_UI_EXP_SEL_C]        = "sel_c",
	[DA850_EVM_UI_EXP_SEL_B]        = "sel_b",
	[DA850_EVM_UI_EXP_SEL_A]        = "sel_a",
	[DA850_EVM_UI_EXP_PB8]          = "pb8",
	[DA850_EVM_UI_EXP_PB7]          = "pb7",
	[DA850_EVM_UI_EXP_PB6]          = "pb6",
	[DA850_EVM_UI_EXP_PB5]          = "pb5",
	[DA850_EVM_UI_EXP_PB4]          = "pb4",
	[DA850_EVM_UI_EXP_PB3]          = "pb3",
	[DA850_EVM_UI_EXP_PB2]          = "pb2",
	[DA850_EVM_UI_EXP_PB1]          = "pb1",
};

#define DA850_N_UI_PB		8

static struct gpio_keys_button da850_evm_ui_keys[] = {
	[0 ... DA850_N_UI_PB - 1] = {
		.type			= EV_KEY,
		.active_low		= 1,
		.wakeup			= 0,
		.debounce_interval	= DA850_KEYS_DEBOUNCE_MS,
		.code			= -1, /* assigned at runtime */
		.gpio			= -1, /* assigned at runtime */
		.desc			= NULL, /* assigned at runtime */
	},
};

static struct gpio_keys_platform_data da850_evm_ui_keys_pdata = {
	.buttons = da850_evm_ui_keys,
	.nbuttons = ARRAY_SIZE(da850_evm_ui_keys),
	.poll_interval = DA850_GPIO_KEYS_POLL_MS,
};

static struct platform_device da850_evm_ui_keys_device = {
	.name = "gpio-keys-polled",
	.id = 0,
	.dev = {
		.platform_data = &da850_evm_ui_keys_pdata
	},
};

static void da850_evm_ui_keys_init(unsigned gpio)
{
	int i;
	struct gpio_keys_button *button;

	for (i = 0; i < DA850_N_UI_PB; i++) {
		button = &da850_evm_ui_keys[i];
		button->code = KEY_F8 - i;
		button->desc = (char *)
				da850_evm_ui_exp[DA850_EVM_UI_EXP_PB8 + i];
		button->gpio = gpio + DA850_EVM_UI_EXP_PB8 + i;
	}
}

#ifdef CONFIG_DA850_UI_CLCD
static inline void da850_evm_setup_char_lcd(int a, int b, int c)
{
	gpio_set_value_cansleep(a, 0);
	gpio_set_value_cansleep(b, 0);
	gpio_set_value_cansleep(c, 0);
}
#else
static inline void da850_evm_setup_char_lcd(int a, int b, int c) { }
#endif

static struct at24_platform_data da850_evm_i2c_eeprom_info = {
	.byte_len	= SZ_256K / 8,
	.page_size	= 64,
	.flags		= AT24_FLAG_ADDR16,
	.setup		= davinci_get_mac_addr,
	.context	= (void *)0x7f00,
};

#ifdef CONFIG_DA850_UI_SD_VIDEO_PORT
static inline void da850_evm_setup_video_port(int video_sel)
{
	gpio_set_value_cansleep(video_sel, 0);
}
#else
static inline void da850_evm_setup_video_port(int video_sel) { }
#endif

#ifdef CONFIG_DA850_UI_CAMERA
static inline void da850_evm_setup_camera(int camera_sel)
{
	gpio_set_value_cansleep(camera_sel, 0);
}
#else
static inline void da850_evm_setup_camera(int camera_sel) { }
#endif

static int da850_evm_ui_expander_setup(struct i2c_client *client, unsigned gpio,
						unsigned ngpio, void *c)
{
	int sel_a, sel_b, sel_c, ret;

	sel_a = gpio + DA850_EVM_UI_EXP_SEL_A;
	sel_b = gpio + DA850_EVM_UI_EXP_SEL_B;
	sel_c = gpio + DA850_EVM_UI_EXP_SEL_C;

	ret = gpio_request(sel_a, da850_evm_ui_exp[DA850_EVM_UI_EXP_SEL_A]);
	if (ret) {
		pr_warning("Cannot open UI expander pin %d\n", sel_a);
		goto exp_setup_sela_fail;
	}

	ret = gpio_request(sel_b, da850_evm_ui_exp[DA850_EVM_UI_EXP_SEL_B]);
	if (ret) {
		pr_warning("Cannot open UI expander pin %d\n", sel_b);
		goto exp_setup_selb_fail;
	}

	ret = gpio_request(sel_c, da850_evm_ui_exp[DA850_EVM_UI_EXP_SEL_C]);
	if (ret) {
		pr_warning("Cannot open UI expander pin %d\n", sel_c);
		goto exp_setup_selc_fail;
	}

	/* deselect all functionalities */
	gpio_direction_output(sel_a, 1);
	gpio_direction_output(sel_b, 1);
	gpio_direction_output(sel_c, 1);

	da850_evm_ui_keys_init(gpio);
	ret = platform_device_register(&da850_evm_ui_keys_device);
	if (ret) {
		pr_warning("Could not register UI GPIO expander push-buttons");
		goto exp_setup_keys_fail;
	}

	ui_card_detected = 1;
	pr_info("DA850/OMAP-L138 EVM UI card detected\n");

	da850_evm_setup_nor_nand();

	da850_evm_setup_emac_rmii(sel_a);

	da850_evm_setup_char_lcd(sel_a, sel_b, sel_c);

	da850_evm_setup_video_port(sel_c);

	da850_evm_setup_camera(sel_b);

	return 0;

exp_setup_keys_fail:
	gpio_free(sel_c);
exp_setup_selc_fail:
	gpio_free(sel_b);
exp_setup_selb_fail:
	gpio_free(sel_a);
exp_setup_sela_fail:
	return ret;
}

static int da850_evm_ui_expander_teardown(struct i2c_client *client,
					unsigned gpio, unsigned ngpio, void *c)
{
	platform_device_unregister(&da850_evm_ui_keys_device);

	/* deselect all functionalities */
	gpio_set_value_cansleep(gpio + DA850_EVM_UI_EXP_SEL_C, 1);
	gpio_set_value_cansleep(gpio + DA850_EVM_UI_EXP_SEL_B, 1);
	gpio_set_value_cansleep(gpio + DA850_EVM_UI_EXP_SEL_A, 1);

	gpio_free(gpio + DA850_EVM_UI_EXP_SEL_C);
	gpio_free(gpio + DA850_EVM_UI_EXP_SEL_B);
	gpio_free(gpio + DA850_EVM_UI_EXP_SEL_A);

	return 0;
}

/* assign the baseboard expander's GPIOs after the UI board's */
#define DA850_UI_EXPANDER_N_GPIOS ARRAY_SIZE(da850_evm_ui_exp)
#define DA850_BB_EXPANDER_GPIO_BASE (DAVINCI_N_GPIO + DA850_UI_EXPANDER_N_GPIOS)

enum da850_evm_bb_exp_pins {
	DA850_EVM_BB_EXP_DEEP_SLEEP_EN = 0,
	DA850_EVM_BB_EXP_SW_RST,
	DA850_EVM_BB_EXP_TP_23,
	DA850_EVM_BB_EXP_TP_22,
	DA850_EVM_BB_EXP_TP_21,
	DA850_EVM_BB_EXP_USER_PB1,
	DA850_EVM_BB_EXP_USER_LED2,
	DA850_EVM_BB_EXP_USER_LED1,
	DA850_EVM_BB_EXP_USER_SW1,
	DA850_EVM_BB_EXP_USER_SW2,
	DA850_EVM_BB_EXP_USER_SW3,
	DA850_EVM_BB_EXP_USER_SW4,
	DA850_EVM_BB_EXP_USER_SW5,
	DA850_EVM_BB_EXP_USER_SW6,
	DA850_EVM_BB_EXP_USER_SW7,
	DA850_EVM_BB_EXP_USER_SW8
};

static const char const *da850_evm_bb_exp[] = {
	[DA850_EVM_BB_EXP_DEEP_SLEEP_EN]	= "deep_sleep_en",
	[DA850_EVM_BB_EXP_SW_RST]		= "sw_rst",
	[DA850_EVM_BB_EXP_TP_23]		= "tp_23",
	[DA850_EVM_BB_EXP_TP_22]		= "tp_22",
	[DA850_EVM_BB_EXP_TP_21]		= "tp_21",
	[DA850_EVM_BB_EXP_USER_PB1]		= "user_pb1",
	[DA850_EVM_BB_EXP_USER_LED2]		= "user_led2",
	[DA850_EVM_BB_EXP_USER_LED1]		= "user_led1",
	[DA850_EVM_BB_EXP_USER_SW1]		= "user_sw1",
	[DA850_EVM_BB_EXP_USER_SW2]		= "user_sw2",
	[DA850_EVM_BB_EXP_USER_SW3]		= "user_sw3",
	[DA850_EVM_BB_EXP_USER_SW4]		= "user_sw4",
	[DA850_EVM_BB_EXP_USER_SW5]		= "user_sw5",
	[DA850_EVM_BB_EXP_USER_SW6]		= "user_sw6",
	[DA850_EVM_BB_EXP_USER_SW7]		= "user_sw7",
	[DA850_EVM_BB_EXP_USER_SW8]		= "user_sw8",
};

#define DA850_N_BB_USER_SW	8

static struct gpio_keys_button da850_evm_bb_keys[] = {
	[0] = {
		.type			= EV_KEY,
		.active_low		= 1,
		.wakeup			= 0,
		.debounce_interval	= DA850_KEYS_DEBOUNCE_MS,
		.code			= KEY_PROG1,
		.desc			= NULL, /* assigned at runtime */
		.gpio			= -1, /* assigned at runtime */
	},
	[1 ... DA850_N_BB_USER_SW] = {
		.type			= EV_SW,
		.active_low		= 1,
		.wakeup			= 0,
		.debounce_interval	= DA850_KEYS_DEBOUNCE_MS,
		.code			= -1, /* assigned at runtime */
		.desc			= NULL, /* assigned at runtime */
		.gpio			= -1, /* assigned at runtime */
	},
};

static struct gpio_keys_platform_data da850_evm_bb_keys_pdata = {
	.buttons = da850_evm_bb_keys,
	.nbuttons = ARRAY_SIZE(da850_evm_bb_keys),
	.poll_interval = DA850_GPIO_KEYS_POLL_MS,
};

static struct platform_device da850_evm_bb_keys_device = {
	.name = "gpio-keys-polled",
	.id = 1,
	.dev = {
		.platform_data = &da850_evm_bb_keys_pdata
	},
};

static void da850_evm_bb_keys_init(unsigned gpio)
{
	int i;
	struct gpio_keys_button *button;

	button = &da850_evm_bb_keys[0];
	button->desc = (char *)
		da850_evm_bb_exp[DA850_EVM_BB_EXP_USER_PB1];
	button->gpio = gpio + DA850_EVM_BB_EXP_USER_PB1;

	for (i = 0; i < DA850_N_BB_USER_SW; i++) {
		button = &da850_evm_bb_keys[i + 1];
		button->code = SW_LID + i;
		button->desc = (char *)
				da850_evm_bb_exp[DA850_EVM_BB_EXP_USER_SW1 + i];
		button->gpio = gpio + DA850_EVM_BB_EXP_USER_SW1 + i;
	}
}

#define DA850_N_BB_USER_LED	2

static struct gpio_led da850_evm_bb_leds[] = {
	[0 ... DA850_N_BB_USER_LED - 1] = {
		.active_low = 1,
		.gpio = -1, /* assigned at runtime */
		.name = NULL, /* assigned at runtime */
	},
};

static struct gpio_led_platform_data da850_evm_bb_leds_pdata = {
	.leds = da850_evm_bb_leds,
	.num_leds = ARRAY_SIZE(da850_evm_bb_leds),
};

static struct platform_device da850_evm_bb_leds_device = {
	.name		= "leds-gpio",
	.id		= -1,
	.dev = {
		.platform_data = &da850_evm_bb_leds_pdata
	}
};

static void da850_evm_bb_leds_init(unsigned gpio)
{
	int i;
	struct gpio_led *led;

	for (i = 0; i < DA850_N_BB_USER_LED; i++) {
		led = &da850_evm_bb_leds[i];

		led->gpio = gpio + DA850_EVM_BB_EXP_USER_LED2 + i;
		led->name =
			da850_evm_bb_exp[DA850_EVM_BB_EXP_USER_LED2 + i];
	}
}

static int da850_evm_bb_expander_setup(struct i2c_client *client,
						unsigned gpio, unsigned ngpio,
						void *c)
{
	int ret;

	/*
	 * Register the switches and pushbutton on the baseboard as a gpio-keys
	 * device.
	 */
	da850_evm_bb_keys_init(gpio);
	ret = platform_device_register(&da850_evm_bb_keys_device);
	if (ret) {
		pr_warning("Could not register baseboard GPIO expander keys");
		goto io_exp_setup_sw_fail;
	}

	da850_evm_bb_leds_init(gpio);
	ret = platform_device_register(&da850_evm_bb_leds_device);
	if (ret) {
		pr_warning("Could not register baseboard GPIO expander LEDS");
		goto io_exp_setup_leds_fail;
	}

	return 0;

io_exp_setup_leds_fail:
	platform_device_unregister(&da850_evm_bb_keys_device);
io_exp_setup_sw_fail:
	return ret;
}

static int da850_evm_bb_expander_teardown(struct i2c_client *client,
					unsigned gpio, unsigned ngpio, void *c)
{
	platform_device_unregister(&da850_evm_bb_leds_device);
	platform_device_unregister(&da850_evm_bb_keys_device);

	return 0;
}

static struct pca953x_platform_data da850_evm_ui_expander_info = {
	.gpio_base	= DAVINCI_N_GPIO,
	.setup		= da850_evm_ui_expander_setup,
	.teardown	= da850_evm_ui_expander_teardown,
	.names		= da850_evm_ui_exp,
};

static struct pca953x_platform_data da850_evm_bb_expander_info = {
	.gpio_base	= DA850_BB_EXPANDER_GPIO_BASE,
	.setup		= da850_evm_bb_expander_setup,
	.teardown	= da850_evm_bb_expander_teardown,
	.names		= da850_evm_bb_exp,
};

/*
 * USB1 VBUS is controlled by GPIO2[4], over-current is reported on GPIO6[13].
 */
#define ON_BD_USB_DRV	GPIO_TO_PIN(2, 4)
#define ON_BD_USB_OVC	GPIO_TO_PIN(6, 13)

static const short da850_evm_usb11_pins[] = {
	DA850_GPIO2_4, DA850_GPIO6_13,
	-1
};

static da8xx_ocic_handler_t da850_evm_usb_ocic_handler;

static int da850_evm_usb_set_power(unsigned port, int on)
{
	gpio_set_value(ON_BD_USB_DRV, on);
	return 0;
}

static int da850_evm_usb_get_power(unsigned port)
{
	return gpio_get_value(ON_BD_USB_DRV);
}

static int da850_evm_usb_get_oci(unsigned port)
{
	return !gpio_get_value(ON_BD_USB_OVC);
}

static irqreturn_t da850_evm_usb_ocic_irq(int, void *);

static int da850_evm_usb_ocic_notify(da8xx_ocic_handler_t handler)
{
	int irq		= gpio_to_irq(ON_BD_USB_OVC);
	int error	= 0;

	if (handler != NULL) {
		da850_evm_usb_ocic_handler = handler;

		error = request_irq(irq, da850_evm_usb_ocic_irq, IRQF_DISABLED |
				    IRQF_TRIGGER_RISING | IRQF_TRIGGER_FALLING,
				    "OHCI over-current indicator", NULL);
		if (error)
			printk(KERN_ERR "%s: could not request IRQ to watch "
			       "over-current indicator changes\n", __func__);
	} else
		free_irq(irq, NULL);

	return error;
}

static struct da8xx_ohci_root_hub da850_evm_usb11_pdata = {
	.set_power	= da850_evm_usb_set_power,
	.get_power	= da850_evm_usb_get_power,
	.get_oci	= da850_evm_usb_get_oci,
	.ocic_notify	= da850_evm_usb_ocic_notify,

	/* TPS2065 switch @ 5V */
	.potpgt		= (3 + 1) / 2,	/* 3 ms max */
};

static irqreturn_t da850_evm_usb_ocic_irq(int irq, void *dev_id)
{
	da850_evm_usb_ocic_handler(&da850_evm_usb11_pdata, 1);
	return IRQ_HANDLED;
}

static __init void da850_evm_usb_init(void)
{
	u32 cfgchip2;
	int ret;

	/*
	 * Set up USB clock/mode in the CFGCHIP2 register.
	 * FYI:  CFGCHIP2 is 0x0000ef00 initially.
	 */
	cfgchip2 = __raw_readl(DA8XX_SYSCFG0_VIRT(DA8XX_CFGCHIP2_REG));

	/* USB2.0 PHY reference clock is 24 MHz */
	cfgchip2 &= ~CFGCHIP2_REFFREQ;
	cfgchip2 |=  CFGCHIP2_REFFREQ_24MHZ;

	/*
	 * Select internal reference clock for USB 2.0 PHY
	 * and use it as a clock source for USB 1.1 PHY
	 * (this is the default setting anyway).
	 */
	cfgchip2 &= ~CFGCHIP2_USB1PHYCLKMUX;
	cfgchip2 |=  CFGCHIP2_USB2PHYCLKMUX;

	/*
	 * We have to override VBUS/ID signals when MUSB is configured into the
	 * host-only mode -- ID pin will float if no cable is connected, so the
	 * controller won't be able to drive VBUS thinking that it's a B-device.
	 * Otherwise, we want to use the OTG mode and enable VBUS comparators.
	 */
	cfgchip2 &= ~CFGCHIP2_OTGMODE;
#ifdef	CONFIG_USB_MUSB_HOST
	cfgchip2 |=  CFGCHIP2_FORCE_HOST;
#else
	cfgchip2 |=  CFGCHIP2_SESENDEN | CFGCHIP2_VBDTCTEN;
#endif

	__raw_writel(cfgchip2, DA8XX_SYSCFG0_VIRT(DA8XX_CFGCHIP2_REG));

	/*
	 * TPS2065 switch @ 5V supplies 1 A (sustains 1.5 A),
	 * with the power on to power good time of 3 ms.
	 */
	ret = da8xx_register_usb20(1000, 3);
	if (ret)
		pr_warning("%s: USB 2.0 registration failed: %d\n",
			   __func__, ret);

	ret = davinci_cfg_reg_list(da850_evm_usb11_pins);
	if (ret) {
		pr_warning("%s: USB 1.1 PinMux setup failed: %d\n",
			   __func__, ret);
		return;
	}

	ret = gpio_request(ON_BD_USB_DRV, "ON_BD_USB_DRV");
	if (ret) {
		printk(KERN_ERR "%s: failed to request GPIO for USB 1.1 port "
		       "power control: %d\n", __func__, ret);
		return;
	}
	gpio_direction_output(ON_BD_USB_DRV, 0);

	ret = gpio_request(ON_BD_USB_OVC, "ON_BD_USB_OVC");
	if (ret) {
		printk(KERN_ERR "%s: failed to request GPIO for USB 1.1 port "
		       "over-current indicator: %d\n", __func__, ret);
		return;
	}
	gpio_direction_input(ON_BD_USB_OVC);

	ret = da8xx_register_usb11(&da850_evm_usb11_pdata);
	if (ret)
		pr_warning("%s: USB 1.1 registration failed: %d\n",
			   __func__, ret);
}

static struct davinci_uart_config da850_evm_uart_config __initdata = {
	.enabled_uarts = 0x7,
};

/* davinci da850 evm audio machine driver */
static u8 da850_iis_serializer_direction[] = {
	INACTIVE_MODE,	INACTIVE_MODE,	INACTIVE_MODE,	INACTIVE_MODE,
	INACTIVE_MODE,	INACTIVE_MODE,	INACTIVE_MODE,	INACTIVE_MODE,
	INACTIVE_MODE,	INACTIVE_MODE,	INACTIVE_MODE,	TX_MODE,
	RX_MODE,	INACTIVE_MODE,	INACTIVE_MODE,	INACTIVE_MODE,
};

static struct snd_platform_data da850_evm_snd_data = {
	.tx_dma_offset	= 0x2000,
	.rx_dma_offset	= 0x2000,
	.op_mode	= DAVINCI_MCASP_IIS_MODE,
	.num_serializer	= ARRAY_SIZE(da850_iis_serializer_direction),
	.tdm_slots	= 2,
	.serial_dir	= da850_iis_serializer_direction,
	.asp_chan_q	= EVENTQ_1,
	.version	= MCASP_VERSION_2,
	.txnumevt	= 1,
	.rxnumevt	= 1,
};

static struct davinci_mcbsp_platform_data da850_mcbsp0_config = {
	.inst	= 0,
};

static struct davinci_mcbsp_platform_data da850_mcbsp1_config = {
	.inst	= 1,
};

static int da850_evm_mmc_get_ro(int index)
{
	return gpio_get_value(DA850_MMCSD_WP_PIN);
}

static int da850_evm_mmc_get_cd(int index)
{
	return !gpio_get_value(DA850_MMCSD_CD_PIN);
}

static int wl12xx_set_power(int slot, int power_on)
{
	static int power_state;

	pr_debug("Powering %s wifi", (power_on ? "on" : "off"));

	if (power_on == power_state)
		return 0;
	power_state = power_on;

	if (power_on) {
		gpio_set_value(DA850_WLAN_EN, 1);
		mdelay(15);
		gpio_set_value(DA850_WLAN_EN, 0);
		mdelay(1);
		gpio_set_value(DA850_WLAN_EN, 1);
		mdelay(70);
	} else {
		gpio_set_value(DA850_WLAN_EN, 0);
	}

	return 0;
}

static struct davinci_mmc_config da850_mmc_config[] = {
	{
		.get_ro		= da850_evm_mmc_get_ro,
		.get_cd		= da850_evm_mmc_get_cd,
		.wires		= 4,
		.max_freq	= 50000000,
		.caps		= MMC_CAP_MMC_HIGHSPEED | MMC_CAP_SD_HIGHSPEED,
		.version	= MMC_CTLR_VERSION_2,
	},
	{
		.get_ro		= NULL,
		.get_cd		= NULL,
		.set_power	= wl12xx_set_power,
		.wires		= 4,
		.max_freq	= 25000000,
		.caps		= MMC_CAP_4_BIT_DATA | MMC_CAP_NONREMOVABLE |
				  MMC_CAP_POWER_OFF_CARD,
		.version	= MMC_CTLR_VERSION_2,
	},
	{}	/* Terminator */
};

static void da850_panel_power_ctrl(int val)
{
	/* lcd power */
	gpio_set_value(DA850_LCD_PWR_PIN, val);

	mdelay(200);

	/* lcd backlight */
	gpio_set_value(DA850_LCD_BL_PIN, val);
}

static int da850_lcd_hw_init(void)
{
	void __iomem *cfg_mstpri2_base;
	int status;
	u32 val;

	/*
	 * Reconfigure the LCDC priority to the highest to ensure that
	 * the throughput/latency requirements for the LCDC are met.
	 */
	cfg_mstpri2_base = DA8XX_SYSCFG0_VIRT(DA8XX_MSTPRI2_REG);

	val = __raw_readl(cfg_mstpri2_base);
	val &= 0x0fffffff;
	__raw_writel(val, cfg_mstpri2_base);

	status = gpio_request(DA850_LCD_BL_PIN, "lcd bl\n");
	if (status < 0)
		return status;

	status = gpio_request(DA850_LCD_PWR_PIN, "lcd pwr\n");
	if (status < 0) {
		gpio_free(DA850_LCD_BL_PIN);
		return status;
	}

	gpio_direction_output(DA850_LCD_BL_PIN, 0);
	gpio_direction_output(DA850_LCD_PWR_PIN, 0);

	return 0;
}

/* TPS65070 voltage regulator support */

/* 3.3V */
static struct regulator_consumer_supply tps65070_dcdc1_consumers[] = {
	{
		.supply = "usb0_vdda33",
	},
	{
		.supply = "usb1_vdda33",
	},
};

/* 3.3V or 1.8V */
static struct regulator_consumer_supply tps65070_dcdc2_consumers[] = {
	{
		.supply = "dvdd3318_a",
	},
	{
		.supply = "dvdd3318_b",
	},
	{
		.supply = "dvdd3318_c",
	},
};

/* 1.2V */
static struct regulator_consumer_supply tps65070_dcdc3_consumers[] = {
	{
		.supply = "cvdd",
	},
};

/* 1.8V LDO */
static struct regulator_consumer_supply tps65070_ldo1_consumers[] = {
	{
		.supply = "sata_vddr",
	},
	{
		.supply = "usb0_vdda18",
	},
	{
		.supply = "usb1_vdda18",
	},
	{
		.supply = "ddr_dvdd18",
	},
};

/* 1.2V LDO */
static struct regulator_consumer_supply tps65070_ldo2_consumers[] = {
	{
		.supply = "sata_vdd",
	},
	{
		.supply = "pll0_vdda",
	},
	{
		.supply = "pll1_vdda",
	},
	{
		.supply = "usbs_cvdd",
	},
	{
		.supply = "vddarnwa1",
	},
};

/* We take advantage of the fact that both defdcdc{2,3} are tied high */
static struct tps6507x_reg_platform_data tps6507x_platform_data = {
	.defdcdc_default = true,
};

static struct regulator_init_data tps65070_regulator_data[] = {
	/* dcdc1 */
	{
		.constraints = {
			.min_uV = 3150000,
			.max_uV = 3450000,
			.valid_ops_mask = (REGULATOR_CHANGE_VOLTAGE |
				REGULATOR_CHANGE_STATUS),
			.boot_on = 1,
		},
		.num_consumer_supplies = ARRAY_SIZE(tps65070_dcdc1_consumers),
		.consumer_supplies = tps65070_dcdc1_consumers,
	},

	/* dcdc2 */
	{
		.constraints = {
			.min_uV = 1710000,
			.max_uV = 3450000,
			.valid_ops_mask = (REGULATOR_CHANGE_VOLTAGE |
				REGULATOR_CHANGE_STATUS),
			.boot_on = 1,
		},
		.num_consumer_supplies = ARRAY_SIZE(tps65070_dcdc2_consumers),
		.consumer_supplies = tps65070_dcdc2_consumers,
		.driver_data = &tps6507x_platform_data,
	},

	/* dcdc3 */
	{
		.constraints = {
			.min_uV = 950000,
			.max_uV = 1350000,
			.valid_ops_mask = (REGULATOR_CHANGE_VOLTAGE |
				REGULATOR_CHANGE_STATUS),
			.boot_on = 1,
		},
		.num_consumer_supplies = ARRAY_SIZE(tps65070_dcdc3_consumers),
		.consumer_supplies = tps65070_dcdc3_consumers,
		.driver_data = &tps6507x_platform_data,
	},

	/* ldo1 */
	{
		.constraints = {
			.min_uV = 1710000,
			.max_uV = 1890000,
			.valid_ops_mask = (REGULATOR_CHANGE_VOLTAGE |
				REGULATOR_CHANGE_STATUS),
			.boot_on = 1,
		},
		.num_consumer_supplies = ARRAY_SIZE(tps65070_ldo1_consumers),
		.consumer_supplies = tps65070_ldo1_consumers,
	},

	/* ldo2 */
	{
		.constraints = {
			.min_uV = 1140000,
			.max_uV = 1320000,
			.valid_ops_mask = (REGULATOR_CHANGE_VOLTAGE |
				REGULATOR_CHANGE_STATUS),
			.boot_on = 1,
		},
		.num_consumer_supplies = ARRAY_SIZE(tps65070_ldo2_consumers),
		.consumer_supplies = tps65070_ldo2_consumers,
	},
};

static struct touchscreen_init_data tps6507x_touchscreen_data = {
	.poll_period =  30,	/* ms between touch samples */
	.min_pressure = 0x30,	/* minimum pressure to trigger touch */
	.vref = 0,		/* turn off vref when not using A/D */
	.vendor = 0,		/* /sys/class/input/input?/id/vendor */
	.product = 65070,	/* /sys/class/input/input?/id/product */
	.version = 0x100,	/* /sys/class/input/input?/id/version */
};

static struct tps6507x_board tps_board = {
	.tps6507x_pmic_init_data = &tps65070_regulator_data[0],
	.tps6507x_ts_init_data = &tps6507x_touchscreen_data,
};

static struct i2c_board_info __initdata da850_evm_i2c_devices[] = {
	{
		I2C_BOARD_INFO("24c256", 0x50),
		.platform_data = &da850_evm_i2c_eeprom_info,
	},
	{
		I2C_BOARD_INFO("tlv320aic3x", 0x18),
	},
	{
		I2C_BOARD_INFO("tca6416", 0x20),
		.platform_data = &da850_evm_ui_expander_info,
	},
	{
		I2C_BOARD_INFO("tca6416", 0x21),
		.platform_data = &da850_evm_bb_expander_info,
	},
	{
		I2C_BOARD_INFO("tps6507x", 0x48),
		.platform_data = &tps_board,
	},
	{
		I2C_BOARD_INFO("cdce913", 0x65),
	},
	{
		I2C_BOARD_INFO("PCA9543A", 0x73),
	},
};

static const short da850_evm_lcdc_pins[] = {
	DA850_GPIO2_8, DA850_GPIO2_15,
	-1
};

static struct i2c_client *pca9543a;

static int pca9543a_probe(struct i2c_client *client,
		const struct i2c_device_id *id)
{
	pr_info("pca9543a_probe");
	pca9543a = client;
	return 0;
}

static int pca9543a_remove(struct i2c_client *client)
{
	pca9543a = NULL;
	return 0;
}

static const struct i2c_device_id pca9543a_ids[] = {
	{ "PCA9543A", 0, },
	{ /* end of list */ },
};

/* This is for i2c driver for the MT9T031 header i2c switch */
static struct i2c_driver pca9543a_driver = {
	.driver.name	= "PCA9543A",
	.id_table	= pca9543a_ids,
	.probe		= pca9543a_probe,
	.remove		= pca9543a_remove,
};

/**
 * da850_enable_pca9543a() - Enable/Disable I2C switch PCA9543A for sensor
 * @en: enable/disable flag
 */
static int da850_enable_pca9543a(int en)
{
	static char val = 1;
	int status = 1;
	struct i2c_msg msg = {
			.flags = 0,
			.len = 1,
			.buf = &val,
		};

	pr_info("da850evm_enable_pca9543a\n");
	if (!en)
		val = 0;

	if (!pca9543a)
		return -ENXIO;

	msg.addr = pca9543a->addr;
	/* turn i2c switch, pca9543a, on/off */
	status = i2c_transfer(pca9543a->adapter, &msg, 1);
	if (status == 1)
		status = 0;

	return status;
}

static const short da850_evm_mii_pins[] = {
	DA850_MII_TXEN, DA850_MII_TXCLK, DA850_MII_COL, DA850_MII_TXD_3,
	DA850_MII_TXD_2, DA850_MII_TXD_1, DA850_MII_TXD_0, DA850_MII_RXER,
	DA850_MII_CRS, DA850_MII_RXCLK, DA850_MII_RXDV, DA850_MII_RXD_3,
	DA850_MII_RXD_2, DA850_MII_RXD_1, DA850_MII_RXD_0, DA850_MDIO_CLK,
	DA850_MDIO_D,
	-1
};

static const short da850_evm_rmii_pins[] = {
	DA850_RMII_TXD_0, DA850_RMII_TXD_1, DA850_RMII_TXEN,
	DA850_RMII_CRS_DV, DA850_RMII_RXD_0, DA850_RMII_RXD_1,
	DA850_RMII_RXER, DA850_RMII_MHZ_50_CLK, DA850_MDIO_CLK,
	DA850_MDIO_D,
	-1
};

static int __init da850_evm_config_emac(void)
{
	void __iomem *cfg_chip3_base;
	int ret;
	u32 val;
	struct davinci_soc_info *soc_info = &davinci_soc_info;
	u8 rmii_en = soc_info->emac_pdata->rmii_en;

	if (!machine_is_davinci_da850_evm())
		return 0;

	cfg_chip3_base = DA8XX_SYSCFG0_VIRT(DA8XX_CFGCHIP3_REG);

	val = __raw_readl(cfg_chip3_base);

	if (rmii_en) {
		val |= BIT(8);
		ret = davinci_cfg_reg_list(da850_evm_rmii_pins);
		pr_info("EMAC: RMII PHY configured, MII PHY will not be"
							" functional\n");
	} else {
		val &= ~BIT(8);
		ret = davinci_cfg_reg_list(da850_evm_mii_pins);
		pr_info("EMAC: MII PHY configured, RMII PHY will not be"
							" functional\n");
	}

	if (ret)
		pr_warning("da850_evm_init: cpgmac/rmii mux setup failed: %d\n",
				ret);

	/* configure the CFGCHIP3 register for RMII or MII */
	__raw_writel(val, cfg_chip3_base);

	ret = davinci_cfg_reg(DA850_GPIO2_6);
	if (ret)
		pr_warning("da850_evm_init:GPIO(2,6) mux setup "
							"failed\n");

	ret = gpio_request(DA850_MII_MDIO_CLKEN_PIN, "mdio_clk_en");
	if (ret) {
		pr_warning("Cannot open GPIO %d\n",
					DA850_MII_MDIO_CLKEN_PIN);
		return ret;
	}

	/* Enable/Disable MII MDIO clock */
	gpio_direction_output(DA850_MII_MDIO_CLKEN_PIN, rmii_en);

	soc_info->emac_pdata->phy_id = DA850_EVM_PHY_ID;

	ret = da8xx_register_emac();
	if (ret)
		pr_warning("da850_evm_init: emac registration failed: %d\n",
				ret);

	return 0;
}
device_initcall(da850_evm_config_emac);

static const struct vpif_input da850_ch2_inputs[] = {
		{
		.input = {
			.index = 0,
			.name = "Camera",
			.type = V4L2_INPUT_TYPE_CAMERA,
			.std = V4L2_STD_BAYER_ALL
		},
		.subdev_name = "mt9t031",
	},
};

/*
 * The following EDMA channels/slots are not being used by drivers (for
 * example: Timer, GPIO, UART events etc) on da850/omap-l138 EVM, hence
 * they are being reserved for codecs on the DSP side.
 */
static const s16 da850_dma0_rsv_chans[][2] = {
	/* (offset, number) */
	{ 8,  6},
	{24,  4},
	{30,  2},
	{-1, -1}
};

static const s16 da850_dma0_rsv_slots[][2] = {
	/* (offset, number) */
	{ 8,  6},
	{24,  4},
	{30, 50},
	{-1, -1}
};

static const s16 da850_dma1_rsv_chans[][2] = {
	/* (offset, number) */
	{ 0, 28},
	{30,  2},
	{-1, -1}
};

static const s16 da850_dma1_rsv_slots[][2] = {
	/* (offset, number) */
	{ 0, 28},
	{30, 90},
	{-1, -1}
};

static struct edma_rsv_info da850_edma_cc0_rsv = {
	.rsv_chans	= da850_dma0_rsv_chans,
	.rsv_slots	= da850_dma0_rsv_slots,
};

static struct edma_rsv_info da850_edma_cc1_rsv = {
	.rsv_chans	= da850_dma1_rsv_chans,
	.rsv_slots	= da850_dma1_rsv_slots,
};

static struct edma_rsv_info *da850_edma_rsv[2] = {
	&da850_edma_cc0_rsv,
	&da850_edma_cc1_rsv,
};

#ifdef CONFIG_CPU_FREQ
static __init int da850_evm_init_cpufreq(void)
{
	switch (system_rev & 0xF) {
	case 3:
		da850_max_speed = 456000;
		break;
	case 2:
		da850_max_speed = 408000;
		break;
	case 1:
		da850_max_speed = 372000;
		break;
	}

	return da850_register_cpufreq("pll0_sysclk3");
}
#else
static __init int da850_evm_init_cpufreq(void) { return 0; }
#endif

static struct i2c_gpio_platform_data da850_gpio_i2c_pdata = {
	.sda_pin	= GPIO_TO_PIN(1, 4),
	.scl_pin	= GPIO_TO_PIN(1, 5),
	.udelay		= 2,			/* 250 KHz */
};

static struct platform_device da850_gpio_i2c = {
	.name		= "i2c-gpio",
	.id		= 1,
	.dev		= {
		.platform_data	= &da850_gpio_i2c_pdata,
	},
};

/* Retaining these APIs, since the VPIF drivers do not check NULL handlers */
static int da850_set_vpif_clock(int mux_mode, int hd)
{
	return 0;
}

static int da850_setup_vpif_input_channel_mode(int mux_mode)
{
	return 0;
}

/*Enable mt9t031 by configuring pca9543a i2c switch on sensor
 */
int da850_vpif_setup_input_path(int ch, const char *name)
{
	int ret = 0;

	if (have_imager())
		ret = da850_enable_pca9543a(1);

	return ret;
}

static int da850_vpif_intr_status(void __iomem *vpif_base, int channel)
{
	int status = 0;
	int mask;

	if (channel < 0 || channel > 3)
		return 0;

	mask = 1 << channel;
	status = __raw_readl((vpif_base + VPIF_STATUS)) & mask;
	__raw_writel(status, (vpif_base + VPIF_STATUS_CLR));

	return status;
}

#if defined(CONFIG_DA850_UI_SD_VIDEO_PORT)
/* VPIF capture configuration */
static struct tvp514x_platform_data tvp5146_pdata = {
	.clk_polarity = 0,
	.hs_polarity = 1,
	.vs_polarity = 1
};
#endif

#define TVP514X_STD_ALL (V4L2_STD_NTSC | V4L2_STD_PAL)

static struct vpif_subdev_info da850_vpif_capture_sdev_info[] = {
#if defined(CONFIG_DA850_UI_CAMERA)
	{
		.name	= "mt9t031",
		.board_info = {
			I2C_BOARD_INFO("mt9t031", 0x5d),
			.platform_data = (void *)1,
		},
		.vpif_if = {
			.if_type = VPIF_IF_RAW_BAYER,
			.hd_pol = 0,
			.vd_pol = 0,
			.fid_pol = 0,
		},
	},
#elif defined(CONFIG_DA850_UI_SD_VIDEO_PORT)
	{
		.name	= TVP5147_CH0,
		.board_info = {
			I2C_BOARD_INFO("tvp5146", 0x5d),
			.platform_data = &tvp5146_pdata,
		},
		.input = INPUT_CVBS_VI2B,
		.output = OUTPUT_10BIT_422_EMBEDDED_SYNC,
		.can_route = 1,
		.vpif_if = {
			.if_type = VPIF_IF_BT656,
			.hd_pol = 1,
			.vd_pol = 1,
			.fid_pol = 0,
		},
	},
	{
		.name	= TVP5147_CH1,
		.board_info = {
			I2C_BOARD_INFO("tvp5146", 0x5c),
			.platform_data = &tvp5146_pdata,
		},
		.input = INPUT_SVIDEO_VI2C_VI1C,
		.output = OUTPUT_10BIT_422_EMBEDDED_SYNC,
		.can_route = 1,
		.vpif_if = {
			.if_type = VPIF_IF_BT656,
			.hd_pol = 1,
			.vd_pol = 1,
			.fid_pol = 0,
		},
	},
#endif
};

static const struct vpif_input da850_ch0_inputs[] = {
	{
		.input = {
			.index = 0,
			.name = "Composite",
			.type = V4L2_INPUT_TYPE_CAMERA,
			.std = TVP514X_STD_ALL,
		},
		.subdev_name = TVP5147_CH0,
	},
};

static const struct vpif_input da850_ch1_inputs[] = {
       {
		.input = {
			.index = 0,
			.name = "S-Video",
			.type = V4L2_INPUT_TYPE_CAMERA,
			.std = TVP514X_STD_ALL,
		},
		.subdev_name = TVP5147_CH1,
	},
};

static struct vpif_capture_config da850_vpif_capture_config = {
	.setup_input_channel_mode = da850_setup_vpif_input_channel_mode,
	.setup_input_path = da850_vpif_setup_input_path,
	.intr_status = da850_vpif_intr_status,
	.subdev_info = da850_vpif_capture_sdev_info,
	.subdev_count = ARRAY_SIZE(da850_vpif_capture_sdev_info),
#if defined(CONFIG_DA850_UI_SD_VIDEO_PORT)
	.chan_config[0] = {
		.inputs = da850_ch0_inputs,
		.input_count = ARRAY_SIZE(da850_ch0_inputs),
	},
	.chan_config[1] = {
		.inputs = da850_ch1_inputs,
		.input_count = ARRAY_SIZE(da850_ch1_inputs),
	},
#elif defined(CONFIG_DA850_UI_CAMERA)
	.chan_config[0] = {
		.inputs = da850_ch2_inputs,
		.input_count = ARRAY_SIZE(da850_ch2_inputs),
	},
#endif
	.card_name      = "DA850/OMAP-L138 Video Capture",
};

/* VPIF display configuration */
static struct vpif_subdev_info da850_vpif_subdev[] = {
	{
		.name	= "adv7343",
		.board_info = {
			I2C_BOARD_INFO("adv7343", 0x2a),
		},
	},
};

static const char *vpif_output[] = {
	"Composite",
	"Component",
	"S-Video",
};

static struct vpif_display_config da850_vpif_display_config = {
	.set_clock	= da850_set_vpif_clock,
	.intr_status	= da850_vpif_intr_status,
	.subdevinfo	= da850_vpif_subdev,
	.subdev_count	= ARRAY_SIZE(da850_vpif_subdev),
	.output		= vpif_output,
	.output_count	= ARRAY_SIZE(vpif_output),
	.card_name	= "DA850/OMAP-L138 Video Display",
};

#if defined(CONFIG_DAVINCI_MCBSP0)
#define HAS_MCBSP0 1
#else
#define HAS_MCBSP0 0
#endif

#if defined(CONFIG_DAVINCI_MCBSP1)
#define HAS_MCBSP1 1
#else
#define HAS_MCBSP1 0
#endif

#if defined(CONFIG_TI_DAVINCI_EMAC) || \
	defined(CONFIG_TI_DAVINCI_EMAC_MODULE)
#define HAS_EMAC 1
#else
#define HAS_EMAC 0
#endif

#if defined(CONFIG_SND_DA850_SOC_EVM) || \
	defined(CONFIG_SND_DA850_SOC_EVM_MODULE)
#define HAS_MCASP 1
#else
#define HAS_MCASP 0
#endif

#if defined(CONFIG_DAVINCI_UART1_AFE)
#define HAS_UART1_AFE 1
#else
#define HAS_UART1_AFE 0
#endif

#if defined(CONFIG_DA850_UI_RMII) && (HAS_EMAC)
#define HAS_RMII 1
#else
#define HAS_RMII 0
#endif

#if defined(CONFIG_DA850_UI_LCD) && defined(CONFIG_FB_DA8XX) ||\
		defined(CONFIG_FB_DA8XX_MODULE)
#define HAS_GLCD 1
#else
#define HAS_GLCD 0
#endif

#if defined(CONFIG_VIDEO_DAVINCI_VPIF_DISPLAY) ||\
		defined(CONFIG_VIDEO_DAVINCI_VPIF_DISPLAY_MODULE)
#define HAS_VPIF_DISPLAY 1
#else
#define HAS_VPIF_DISPLAY 0
#endif

#if defined(CONFIG_VIDEO_DAVINCI_VPIF_CAPTURE) ||\
		defined(CONFIG_VIDEO_DAVINCI_VPIF_CAPTURE_MODULE)
#define HAS_VPIF_CAPTURE 1
#else
#define HAS_VPIF_CAPTURE 0
#endif

#if defined(CONFIG_VIDEO_DAVINCI_VPIF_CAPTURE) ||\
		defined(CONFIG_VIDEO_DAVINCI_VPIF_CAPTURE_MODULE)
#define HAS_VPIF_CAPTURE 1
#else
#define HAS_VPIF_CAPTURE 0
#endif

#define DA850EVM_SATA_REFCLKPN_RATE	(100 * 1000 * 1000)

#if defined(CONFIG_SPI_DAVINCI)
#define HAS_SPI 1
#else
#define HAS_SPI 0
#endif

#if defined(CONFIG_FB_DA8XX)
#define HAS_LCD	1
#else
#define HAS_LCD	0
#endif

#ifdef CONFIG_DA850_MISTRAL_WL12XX

static struct wl12xx_platform_data da850_wl12xx_wlan_data __initdata = {
	.irq = -1,
	.board_ref_clock = CONFIG_DA850_MISTRAL_WL12XX_REFCLOCK,
	.platform_quirks = WL12XX_PLATFORM_QUIRK_EDGE_IRQ,
};

static void da850_wl12xx_set_platform_data(void)
{
	da850_wl12xx_wlan_data.irq = gpio_to_irq(DA850_WLAN_IRQ);
	if (wl12xx_set_platform_data(&da850_wl12xx_wlan_data))
		pr_err("Error setting wl12xx data\n");
}

#else

static void da850_wl12xx_set_platform_data(void) { }

#endif

static void da850_wl12xx_init(void)
{
	if (gpio_request(DA850_WLAN_EN, "wl12xx") ||
	    gpio_direction_output(DA850_WLAN_EN, 0))
		pr_err("Error initializing the wl12xx enable gpio\n");

	if (gpio_request(DA850_WLAN_IRQ, "wl12xx_irq") ||
	    gpio_direction_input(DA850_WLAN_IRQ))
		pr_err("Error initializing the wl12xx irq gpio\n");
	if (gpio_request(WL1271_BT_EN_GPIO, "wl1271 BT Enable") ||
	    gpio_direction_output(WL1271_BT_EN_GPIO,0))
		pr_err("Failed to request BT_EN GPIO\n");

	da850_wl12xx_set_platform_data();
}

static __init void da850_evm_init(void)
{
	int ret;
	char mask = 0;
	struct davinci_soc_info *soc_info = &davinci_soc_info;

	u8 rmii_en = soc_info->emac_pdata->rmii_en;
	ret = da850_register_edma(da850_edma_rsv);
	if (ret)
		pr_warning("da850_evm_init: edma registration failed: %d\n",
				ret);

	ret = davinci_cfg_reg_list(da850_i2c0_pins);
	if (ret)
		pr_warning("da850_evm_init: i2c0 mux setup failed: %d\n",
				ret);

	platform_device_register(&da850_gpio_i2c);

	/* Register PRUSS device */
	da8xx_register_pruss();

	ret = da8xx_register_watchdog();
	if (ret)
		pr_warning("da830_evm_init: watchdog registration failed: %d\n",
				ret);

	/* Support for UART 1 */
	ret = davinci_cfg_reg_list(da850_uart1_pins);
	if (ret)
		pr_warning("da850_evm_init: UART 1 mux setup failed:"
						" %d\n", ret);

	ret = da850_register_sata(DA850EVM_SATA_REFCLKPN_RATE);
	if (ret)
		pr_warning("da850_evm_init: sata registration failed: %d\n",
				ret);

	if (HAS_MMC) {
		ret = davinci_cfg_reg_list(da850_mmcsd0_pins);
		if (ret)
			pr_warning("da850_evm_init: mmcsd0 mux setup failed:"
					" %d\n", ret);

		ret = davinci_cfg_reg_list(da850_mmcsd1_pins);
		if (ret)
			pr_warning("da850_evm_init: mmcsd1 mux setup failed:"
					" %d\n", ret);

		ret = gpio_request(DA850_MMCSD_CD_PIN, "MMC CD\n");
		if (ret)
			pr_warning("da850_evm_init: can not open GPIO %d\n",
					DA850_MMCSD_CD_PIN);
		gpio_direction_input(DA850_MMCSD_CD_PIN);

		ret = gpio_request(DA850_MMCSD_WP_PIN, "MMC WP\n");
		if (ret)
			pr_warning("da850_evm_init: can not open GPIO %d\n",
					DA850_MMCSD_WP_PIN);
		gpio_direction_input(DA850_MMCSD_WP_PIN);

		ret = da8xx_register_mmcsd0(&da850_mmc_config[0]);
		if (ret)
			pr_warning("da850_evm_init: mmcsd0 registration failed:"
					" %d\n", ret);
		ret = da850_register_mmcsd1(&da850_mmc_config[1]);
		if (ret)
			pr_warning("da850_evm_init: mmcsd0 registration failed:"
					" %d\n", ret);

		da850_wl12xx_init();
	}

	davinci_serial_init(&da850_evm_uart_config);

	if (have_imager())
		i2c_add_driver(&pca9543a_driver);

	i2c_register_board_info(1, da850_evm_i2c_devices,
			ARRAY_SIZE(da850_evm_i2c_devices));

	/*
	 * shut down uart 0 and 1; they are not used on the board and
	 * accessing them causes endless "too much work in irq53" messages
	 * with arago fs
	 */
	__raw_writel(0, IO_ADDRESS(DA8XX_UART0_BASE) + 0x30);

	if (HAS_MCBSP0) {
		if (HAS_EMAC)
			pr_warning("WARNING: both MCBSP0 and EMAC are "
				"enabled, but they share pins.\n"
				"\tDisable one of them.\n");

		ret = davinci_cfg_reg_list(da850_mcbsp0_pins);
		if (ret)
			pr_warning("da850_evm_init: mcbsp0 mux setup failed:"
					" %d\n", ret);

		ret = da850_init_mcbsp(&da850_mcbsp0_config);
		if (ret)
			pr_warning("da850_evm_init: mcbsp0 registration"
					"failed: %d\n",	ret);
	}

	if (HAS_MCBSP1) {
		ret = davinci_cfg_reg_list(da850_mcbsp1_pins);
		if (ret)
			pr_warning("da850_evm_init: mcbsp1 mux setup failed:"
					" %d\n", ret);

		ret = da850_init_mcbsp(&da850_mcbsp1_config);
		if (ret)
			pr_warning("da850_evm_init: mcbsp1 registration"
					" failed: %d\n", ret);
	}
	 
	if (HAS_MCASP) {
		if ((HAS_MCBSP0 || HAS_MCBSP1))
			pr_warning("WARNING: both McASP and McBSP are enabled, "
					"but they share pins.\n"
					"\tOnly McASP will work. If you want "
					"McBSP support, disable McASP.\n");
		if (HAS_UART1_AFE)
			pr_warning("WARNING: both McASP and UART1_AFE are "
				"enabled, but they share pins.\n"
					"\tDisable one of them.\n");

		ret = davinci_cfg_reg_list(da850_mcasp_pins);
		if (ret)
			pr_warning("da850_evm_init: mcasp mux setup failed:"
					"%d\n", ret);

		da8xx_register_mcasp(0, &da850_evm_snd_data);
	}

	ret = davinci_cfg_reg_list(da850_lcdcntl_pins);
	if (ret)
		pr_warning("da850_evm_init: lcdcntl mux setup failed: %d\n",
				ret);

	/* Handle board specific muxing for LCD here */
	ret = davinci_cfg_reg_list(da850_evm_lcdc_pins);
	if (ret)
		pr_warning("da850_evm_init: evm specific lcd mux setup "
				"failed: %d\n",	ret);

	ret = da850_lcd_hw_init();
	if (ret)
		pr_warning("da850_evm_init: lcd initialization failed: %d\n",
				ret);

	sharp_lk043t1dg01_pdata.panel_power_ctrl = da850_panel_power_ctrl,
	ret = da8xx_register_lcdc(&sharp_lk043t1dg01_pdata);
	if (ret)
		pr_warning("da850_evm_init: lcdc registration failed: %d\n",
				ret);

	ret = da8xx_register_rtc();
	if (ret)
		pr_warning("da850_evm_init: rtc setup failed: %d\n", ret);

	ret = da850_evm_init_cpufreq();
	if (ret)
		pr_warning("da850_evm_init: cpufreq registration failed: %d\n",
				ret);

	ret = da8xx_register_cpuidle();
	if (ret)
		pr_warning("da850_evm_init: cpuidle registration failed: %d\n",
				ret);

	ret = da850_register_pm(&da850_pm_device);
	if (ret)
		pr_warning("da850_evm_init: suspend registration failed: %d\n",
				ret);

	if (system_rev & 0x100) {
		((struct flash_platform_data *)da850evm_spi_info[0] \
		.platform_data)->type = "w25x64";
	} else {
		((struct flash_platform_data *)da850evm_spi_info[0] \
		.platform_data)->type = "m25p64";
	}

	da850evm_init_spi1(da850evm_spi_info, ARRAY_SIZE(da850evm_spi_info));

	if (HAS_VPIF_DISPLAY || HAS_VPIF_CAPTURE) {
		ret = da850_register_vpif();
		if (ret)
			pr_warning("da850_evm_init: VPIF registration failed: "
					"%d\n",	ret);
	}

	if (!HAS_RMII && HAS_VPIF_CAPTURE) {
		ret = davinci_cfg_reg_list(da850_vpif_capture_pins);
		if (ret)
			pr_warning("da850_evm_init: vpif capture mux failed: "
					"%d\n",	ret);

		ret = da850_register_vpif_capture(&da850_vpif_capture_config);
		if (ret)
			pr_warning("da850_evm_init: VPIF registration failed: "
					"%d\n",	ret);

	}

	if (!HAS_GLCD && HAS_VPIF_DISPLAY) {
		ret = davinci_cfg_reg_list(da850_vpif_display_pins);
		if (ret)
			pr_warning("da850_evm_init: vpif capture mux failed: "
					"%d\n",	ret);

		ret = da850_register_vpif_display(&da850_vpif_display_config);
		if (ret)
			pr_warning("da850_evm_init: VPIF registration failed: "
					"%d\n",	ret);

	}

	if (rmii_en) {
		ret = davinci_cfg_reg_list(da850_ehrpwm0_pins);
		if (ret)
			pr_warning("da850_evm_init: ehrpwm0 mux setup failed:"
			       "%d\n",	ret);
		else
			mask = BIT(0) | BIT(1);
	} else {
		pr_warning("da850_evm_init: eHRPWM module 0 cannot be used"
			" since it is being used by MII interface\n");
		mask = 0;
	}

	if (!HAS_LCD) {
		ret = davinci_cfg_reg_list(da850_ehrpwm1_pins);
		if (ret)
			pr_warning("da850_evm_init: eHRPWM module1 output A mux"
			" setup failed %d\n", ret);
		else
			mask = mask | BIT(2);
	} else {
		pr_warning("da850_evm_init: eHRPWM module1 outputA cannot be"
			" used since it is being used by LCD\n");
	}

	if (!HAS_SPI) {
		ret = davinci_cfg_reg(DA850_EHRPWM1_B);
		if (ret)
			pr_warning("da850_evm_init: eHRPWM module1 outputB mux"
				" setup failed %d\n", ret);
		else
			mask =  mask  | BIT(3);
	} else {
		pr_warning("da850_evm_init: eHRPWM module1 outputB cannot be"
			" used since it is being used by spi1\n");
	}

	da850_register_ehrpwm(mask);

	ret = platform_device_register(&da850evm_backlight);
	if (ret)
		pr_warning("da850_evm_init: backlight device registration"
				" failed: %d\n", ret);

	ret = davinci_cfg_reg(DA850_ECAP2_APWM2);
	if (ret)
		pr_warning("da850_evm_init:ecap mux failed: %d\n", ret);

	ret = da850_register_ecap(2);
	if (ret)
		pr_warning("da850_evm_init: eCAP registration failed: %d\n",
			       ret);
	ret = davinci_cfg_reg_list(da850_wl1271_pins);
	if (ret)
		pr_warning("da850_evm_init: wl1271 mux setup failed:"
		       "%d\n",	ret);
 
	ret = platform_device_register(&wl1271_device);
	if (ret)
		pr_warning("da850_evm_init: wl1271 device registration"
				" failed: %d\n", ret);
	/* initilaize usb module */
	da850_evm_usb_init();
}

#ifdef CONFIG_SERIAL_8250_CONSOLE
static int __init da850_evm_console_init(void)
{
	if (!machine_is_davinci_da850_evm())
		return 0;

	return add_preferred_console("ttyS", 2, "115200");
}
console_initcall(da850_evm_console_init);
#endif

static void __init da850_evm_map_io(void)
{
	da850_init();
}

MACHINE_START(DAVINCI_DA850_EVM, "DaVinci DA850/OMAP-L138/AM18x EVM")
	.boot_params	= (DA8XX_DDR_BASE + 0x100),
	.map_io		= da850_evm_map_io,
	.init_irq	= cp_intc_init,
	.timer		= &davinci_timer,
	.init_machine	= da850_evm_init,
MACHINE_END
