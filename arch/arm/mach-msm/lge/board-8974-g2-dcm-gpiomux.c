/* Copyright (c) 2012-2013, Code Aurora Forum. All rights reserved.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 and
 * only version 2 as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 */

#include <linux/init.h>
#include <linux/ioport.h>
#include <mach/board.h>
#include <mach/gpio.h>
#include <mach/gpiomux.h>
#include <mach/socinfo.h>
#include <mach/board_lge.h>

#define KS8851_IRQ_GPIO 94
/* soojung.lim@lge.com, 2013-05-23
 * To use 24MHz GP/GCC_GP clock for V2 H/W
 */
int g_is_tlmm_spare_reg_value = 0;

static struct gpiomux_setting ap2mdm_cfg = {
	.func = GPIOMUX_FUNC_GPIO,
	.drv = GPIOMUX_DRV_8MA,
	.pull = GPIOMUX_PULL_NONE,
};

static struct gpiomux_setting mdm2ap_status_cfg = {
	.func = GPIOMUX_FUNC_GPIO,
	.drv = GPIOMUX_DRV_8MA,
	.pull = GPIOMUX_PULL_DOWN,
	.dir = GPIOMUX_IN,
};

static struct gpiomux_setting mdm2ap_errfatal_cfg = {
	.func = GPIOMUX_FUNC_GPIO,
	.drv = GPIOMUX_DRV_8MA,
	.pull = GPIOMUX_PULL_DOWN,
	.dir = GPIOMUX_IN,
};

static struct gpiomux_setting mdm2ap_pblrdy = {
	.func = GPIOMUX_FUNC_GPIO,
	.drv = GPIOMUX_DRV_8MA,
	.pull = GPIOMUX_PULL_NONE,
	.dir = GPIOMUX_IN,
};


static struct gpiomux_setting ap2mdm_soft_reset_cfg = {
	.func = GPIOMUX_FUNC_GPIO,
	.drv = GPIOMUX_DRV_8MA,
	.pull = GPIOMUX_PULL_NONE,
};

static struct gpiomux_setting ap2mdm_wakeup = {
	.func = GPIOMUX_FUNC_GPIO,
	.drv = GPIOMUX_DRV_8MA,
	.pull = GPIOMUX_PULL_DOWN,
};

static struct msm_gpiomux_config mdm_configs[] __initdata = {
	/* AP2MDM_STATUS */
	{
		.gpio = 105,
		.settings = {
			[GPIOMUX_SUSPENDED] = &ap2mdm_cfg,
		}
	},
	/* MDM2AP_STATUS */
	{
		.gpio = 46,
		.settings = {
			[GPIOMUX_SUSPENDED] = &mdm2ap_status_cfg,
		}
	},
	/* MDM2AP_ERRFATAL */
	{
		.gpio = 82,
		.settings = {
			[GPIOMUX_SUSPENDED] = &mdm2ap_errfatal_cfg,
		}
	},
	/* AP2MDM_ERRFATAL */
	{
		.gpio = 106,
		.settings = {
			[GPIOMUX_SUSPENDED] = &ap2mdm_cfg,
		}
	},
	/* AP2MDM_SOFT_RESET, aka AP2MDM_PON_RESET_N */
	{
		.gpio = 24,
		.settings = {
			[GPIOMUX_SUSPENDED] = &ap2mdm_soft_reset_cfg,
		}
	},
	/* AP2MDM_WAKEUP */
	{
		.gpio = 104,
		.settings = {
			[GPIOMUX_SUSPENDED] = &ap2mdm_wakeup,
		}
	},
	/* MDM2AP_PBL_READY*/
	{
		.gpio = 80,
		.settings = {
			[GPIOMUX_SUSPENDED] = &mdm2ap_pblrdy,
		}
	},
};

#if defined(CONFIG_LGE_NFC_SONY_CXD2235AGG)
static struct gpiomux_setting gpio_uart_felica = {
	.func = GPIOMUX_FUNC_3,
	.drv = GPIOMUX_DRV_8MA,
	.pull = GPIOMUX_PULL_NONE,
};
static struct gpiomux_setting gpio_uart_felica_active = {
	.func = GPIOMUX_FUNC_3,
	.drv = GPIOMUX_DRV_8MA,
	.pull = GPIOMUX_PULL_UP,
};
static struct gpiomux_setting felica_pon_cfg = {
    .func = GPIOMUX_FUNC_GPIO,
    .drv = GPIOMUX_DRV_2MA,
    .pull = GPIOMUX_PULL_NONE,
    .dir = GPIOMUX_OUT_LOW,
};
static struct gpiomux_setting felica_int_cfg = {
    .func = GPIOMUX_FUNC_GPIO,
    .drv = GPIOMUX_DRV_2MA,
    .pull = GPIOMUX_PULL_UP,
};

static struct gpiomux_setting felica_rfs_cfg = {
    .func = GPIOMUX_FUNC_GPIO,
    .drv = GPIOMUX_DRV_2MA,
    .pull = GPIOMUX_PULL_UP,
};

static struct gpiomux_setting felica_lockcont_cfg = {
	.func = GPIOMUX_FUNC_GPIO,
	.drv = GPIOMUX_DRV_2MA,
    .pull = GPIOMUX_PULL_NONE,
    .dir = GPIOMUX_OUT_LOW,
};
static struct gpiomux_setting nfc_hsel_cfg = {
    .func = GPIOMUX_FUNC_GPIO,
    .drv = GPIOMUX_DRV_2MA,
    .pull = GPIOMUX_PULL_NONE,
    .dir = GPIOMUX_OUT_LOW,
};
static struct gpiomux_setting snfc_intu_cfg = {
    .func = GPIOMUX_FUNC_GPIO,
    .drv = GPIOMUX_DRV_2MA,
	.pull = GPIOMUX_PULL_NONE,
	.dir = GPIOMUX_IN,
};
static struct gpiomux_setting snfc_hvdd_cfg = {
    .func = GPIOMUX_FUNC_GPIO,
    .drv = GPIOMUX_DRV_2MA,
    .pull = GPIOMUX_PULL_NONE,
    .dir = GPIOMUX_OUT_LOW,
};
static struct gpiomux_setting snfc_uicc_cfg = {
    .func = GPIOMUX_FUNC_GPIO,
    .drv = GPIOMUX_DRV_2MA,
    .pull = GPIOMUX_PULL_NONE,
    .dir = GPIOMUX_OUT_HIGH,
};

#endif
static struct gpiomux_setting gpio_uart_config = {
	.func = GPIOMUX_FUNC_2,
	.drv = GPIOMUX_DRV_16MA,
	.pull = GPIOMUX_PULL_NONE,
	.dir = GPIOMUX_OUT_HIGH,
};

static struct gpiomux_setting slimbus = {
	.func = GPIOMUX_FUNC_1,
	.drv = GPIOMUX_DRV_8MA,
	.pull = GPIOMUX_PULL_KEEPER,
};

#if defined(CONFIG_KS8851) || defined(CONFIG_KS8851_MODULE)
static struct gpiomux_setting gpio_eth_config = {
	.pull = GPIOMUX_PULL_UP,
	.drv = GPIOMUX_DRV_2MA,
	.func = GPIOMUX_FUNC_GPIO,
};

static struct gpiomux_setting gpio_spi_cs2_config = {
	.func = GPIOMUX_FUNC_4,
	.drv = GPIOMUX_DRV_6MA,
	.pull = GPIOMUX_PULL_DOWN,
};

static struct gpiomux_setting gpio_spi_config = {
	.func = GPIOMUX_FUNC_1,
	.drv = GPIOMUX_DRV_12MA,
	.pull = GPIOMUX_PULL_NONE,
};

static struct gpiomux_setting gpio_spi_cs1_config = {
	.func = GPIOMUX_FUNC_GPIO,
	.drv = GPIOMUX_DRV_6MA,
	.pull = GPIOMUX_PULL_UP,
};

static struct msm_gpiomux_config msm_eth_configs[] = {
	{
		.gpio = KS8851_IRQ_GPIO,
		.settings = {
			[GPIOMUX_SUSPENDED] = &gpio_eth_config,
		}
	},
};
#endif

static struct gpiomux_setting gpio_suspend_config[] = {
	{
		.func = GPIOMUX_FUNC_GPIO,  /* IN-NP */
		.drv = GPIOMUX_DRV_2MA,
		.pull = GPIOMUX_PULL_NONE,
	},
	{
		.func = GPIOMUX_FUNC_GPIO,  /* O-LOW */
		.drv = GPIOMUX_DRV_2MA,
		.pull = GPIOMUX_PULL_NONE,
		.dir = GPIOMUX_OUT_LOW,
	},
};

static struct gpiomux_setting gpio_epm_config = {
	.func = GPIOMUX_FUNC_GPIO,
	.drv  = GPIOMUX_DRV_2MA,
	.pull = GPIOMUX_PULL_DOWN,
};

/* LGE_CHANGE_S, [WiFi][hayun.kim@lge.com], 2013-01-22, Wifi Bring Up */
#if defined (CONFIG_BCMDHD) || defined (CONFIG_BCMDHD_MODULE)
#else
#if !defined(CONFIG_LGE_NFC_SONY_CXD2235AGG)
static struct gpiomux_setting wcnss_5wire_suspend_cfg = {
	.func = GPIOMUX_FUNC_GPIO,
	.drv  = GPIOMUX_DRV_2MA,
	.pull = GPIOMUX_PULL_UP,
};

static struct gpiomux_setting wcnss_5wire_active_cfg = {
	.func = GPIOMUX_FUNC_1,
	.drv  = GPIOMUX_DRV_6MA,
	.pull = GPIOMUX_PULL_DOWN,
};
#endif
#endif
/* LGE_CHANGE_E, [WiFi][hayun.kim@lge.com], 2013-01-22, Wifi Bring Up */

#if defined (CONFIG_LGE_BROADCAST_ONESEG)
static struct gpiomux_setting lge_1seg_ctrl_pin_suspend = {
// 1SEG SPI INTERUPT, 1SEG POWER EN, 1SEG LDO EN
	.func = GPIOMUX_FUNC_GPIO,
	.drv = GPIOMUX_DRV_8MA,
	.pull = GPIOMUX_PULL_UP,
};

static struct gpiomux_setting lge_1seg_int_pin_suspend = {
// 1SEG SPI INTERUPT, 1SEG POWER EN, 1SEG LDO EN
	.func = GPIOMUX_FUNC_GPIO,
	.drv = GPIOMUX_DRV_8MA,
	.pull = GPIOMUX_PULL_NONE,
};


static struct gpiomux_setting lge_1seg_gpio_blsp8_spi_active_config = {
	/* 80-NA437-1B_MSM8274-MSM8674-MSM8974_GPIO_CONFIGURATION_SPREADSHEET.xlsm  */
	.func = GPIOMUX_FUNC_1, //Please look @ GPIO function table for correc function
	.drv = GPIOMUX_DRV_8MA, //Drive Strength
	.pull = GPIOMUX_PULL_NONE, //Should be PULL NONE
};

static struct gpiomux_setting lge_1seg_gpio_blsp8_spi_cs_suspend_config = {
	/* 80-NA437-1B_MSM8274-MSM8674-MSM8974_GPIO_CONFIGURATION_SPREADSHEET.xlsm  */
	.func = GPIOMUX_FUNC_1, //Please look @ GPIO function table for correc function
	.drv = GPIOMUX_DRV_2MA, //Drive Strength
	.pull = GPIOMUX_PULL_UP, //Should be PULL NONE
};

static struct gpiomux_setting lge_1seg_gpio_blsp8_spi_suspend_config = {
	/* 80-NA437-1B_MSM8274-MSM8674-MSM8974_GPIO_CONFIGURATION_SPREADSHEET.xlsm  */
	.func = GPIOMUX_FUNC_1, //Please look @ GPIO function table for correc function
	.drv = GPIOMUX_DRV_2MA, //Drive Strength
	.pull = GPIOMUX_PULL_DOWN, //Should be PULL NONE
};

#endif /* CONFIG_LGE_BROADCAST_ONESEG */
#if defined (CONFIG_LGE_BROADCAST_ONESEG)
static struct msm_gpiomux_config lge_1seg_blsp_configs[] __initdata = {
	{
		.gpio		= 45,				/* 1SEG_SPI_MOSI, BLSP8_3 */
		.settings = {
			[GPIOMUX_ACTIVE]	= &lge_1seg_gpio_blsp8_spi_active_config,
			[GPIOMUX_SUSPENDED] = &lge_1seg_gpio_blsp8_spi_suspend_config,
		},
	},
	{
		.gpio		= 46,				/* 1SEG_SPI_MISO, BLSP8_2 */
		.settings = {
			[GPIOMUX_ACTIVE]	= &lge_1seg_gpio_blsp8_spi_active_config,
			[GPIOMUX_SUSPENDED] = &lge_1seg_gpio_blsp8_spi_suspend_config,
		},
	},
	{
		.gpio		= 47,				/* 1SEG_SPI_CS, BLSP8_1 */
		.settings = {
			[GPIOMUX_ACTIVE]	= &lge_1seg_gpio_blsp8_spi_active_config,
			[GPIOMUX_SUSPENDED] = &lge_1seg_gpio_blsp8_spi_cs_suspend_config,
		},
	},
	{
		.gpio		= 48,				/* 1SEG_SPI_CLK, BLSP8_0 */
		.settings = {
			[GPIOMUX_ACTIVE]	= &lge_1seg_gpio_blsp8_spi_active_config,
			[GPIOMUX_SUSPENDED] = &lge_1seg_gpio_blsp8_spi_suspend_config,
		},
	},
	{
		.gpio	   = 75,					/* 1SEG_RESET_N */
		.settings = {
			[GPIOMUX_SUSPENDED] = &lge_1seg_ctrl_pin_suspend,
		},
	},
	{
		.gpio	   = 76,					/* 1SEG_LDO_EN */
		.settings = {
			[GPIOMUX_SUSPENDED] = &lge_1seg_ctrl_pin_suspend,
		},
	},
	{
		.gpio	   = 77,					/* 1SEG_INT_N */
		.settings = {
			[GPIOMUX_SUSPENDED] = &lge_1seg_int_pin_suspend,
		},
	},
};
#endif /* CONFIG_LGE_BROADCAST_ONESEG */

static struct gpiomux_setting gpio_i2c_config = {
	.func = GPIOMUX_FUNC_3,
	/*
	 * Please keep I2C GPIOs drive-strength at minimum (2ma). It is a
	 * workaround for HW issue of glitches caused by rapid GPIO current-
	 * change.
	 */
	.drv = GPIOMUX_DRV_2MA,
	.pull = GPIOMUX_PULL_NONE,
};

static struct gpiomux_setting lcd_en_act_cfg = {
	.func = GPIOMUX_FUNC_GPIO,
	.drv = GPIOMUX_DRV_8MA,
	.pull = GPIOMUX_PULL_NONE,
	.dir = GPIOMUX_OUT_HIGH,
};

static struct gpiomux_setting lcd_en_sus_cfg = {
	.func = GPIOMUX_FUNC_GPIO,
	.drv = GPIOMUX_DRV_2MA,
	.pull = GPIOMUX_PULL_DOWN,
	.dir = GPIOMUX_IN,
};

#ifdef CONFIG_MACH_LGE
#else
static struct gpiomux_setting atmel_resout_sus_cfg = {
	.func = GPIOMUX_FUNC_GPIO,
	.drv = GPIOMUX_DRV_6MA,
	.pull = GPIOMUX_PULL_DOWN,
};

static struct gpiomux_setting atmel_resout_act_cfg = {
	.func = GPIOMUX_FUNC_GPIO,
	.drv = GPIOMUX_DRV_6MA,
	.pull = GPIOMUX_PULL_UP,
};

static struct gpiomux_setting atmel_int_act_cfg = {
	.func = GPIOMUX_FUNC_GPIO,
	.drv = GPIOMUX_DRV_8MA,
	.pull = GPIOMUX_PULL_UP,
};

static struct gpiomux_setting atmel_int_sus_cfg = {
	.func = GPIOMUX_FUNC_GPIO,
	.drv = GPIOMUX_DRV_2MA,
	.pull = GPIOMUX_PULL_DOWN,
};
#endif

static struct gpiomux_setting taiko_reset = {
	.func = GPIOMUX_FUNC_GPIO,
	.drv = GPIOMUX_DRV_6MA,
	.pull = GPIOMUX_PULL_NONE,
	.dir = GPIOMUX_OUT_LOW,
};

static struct gpiomux_setting taiko_int = {
	.func = GPIOMUX_FUNC_GPIO,
	.drv = GPIOMUX_DRV_2MA,
	.pull = GPIOMUX_PULL_NONE,
};

#ifndef CONFIG_LGE_IRRC
/* NOT USED: GPIO 86 is used as IRRC_RxD in G2 board */
static struct gpiomux_setting hap_lvl_shft_suspended_config = {
	.func = GPIOMUX_FUNC_GPIO,
	.drv = GPIOMUX_DRV_2MA,
	.pull = GPIOMUX_PULL_DOWN,
};

static struct gpiomux_setting hap_lvl_shft_active_config = {
	.func = GPIOMUX_FUNC_GPIO,
	.drv = GPIOMUX_DRV_8MA,
	.pull = GPIOMUX_PULL_UP,
};
static struct msm_gpiomux_config hap_lvl_shft_config[] __initdata = {
	{
		.gpio = 86,
		.settings = {
			[GPIOMUX_SUSPENDED] = &hap_lvl_shft_suspended_config,
			[GPIOMUX_ACTIVE] = &hap_lvl_shft_active_config,
		},
	},
};
#endif

#if defined(CONFIG_BACKLIGHT_LM3630)
static struct gpiomux_setting lcd_bl_en_active_cfg = {
	.func = GPIOMUX_FUNC_GPIO,
	.drv  = GPIOMUX_DRV_8MA,
	.pull = GPIOMUX_PULL_NONE,
	.dir = GPIOMUX_OUT_HIGH,
};

static struct gpiomux_setting lcd_bl_en_suspend_cfg = {
	.func = GPIOMUX_FUNC_GPIO,
	.drv  = GPIOMUX_DRV_2MA,
	.pull = GPIOMUX_PULL_NONE,
	.dir = GPIOMUX_IN,
};
#endif

#ifdef CONFIG_MACH_LGE
#ifdef CONFIG_MAX17050_FUELGAUGE
static struct gpiomux_setting max17050_i2c_sda_config = {
	/* GPIO_2 */
	.func = GPIOMUX_FUNC_3,
	.drv = GPIOMUX_DRV_8MA,
	.pull = GPIOMUX_PULL_NONE,
};
static struct gpiomux_setting max17050_i2c_scl_config = {
	/* GPIO_3 */
	.func = GPIOMUX_FUNC_3,
	.drv = GPIOMUX_DRV_8MA,
	.pull = GPIOMUX_PULL_NONE,
};
static struct gpiomux_setting max17050_int_config = {
	.func = GPIOMUX_FUNC_GPIO,
	.drv = GPIOMUX_DRV_6MA,
	.dir = GPIOMUX_IN,
};
#endif

#ifdef CONFIG_MAX17048_FUELGAUGE
static struct gpiomux_setting max17048_i2c_sda_config = {
	/* GPIO_2 */
	.func = GPIOMUX_FUNC_3,
	.drv = GPIOMUX_DRV_8MA,
	.pull = GPIOMUX_PULL_NONE,
};
static struct gpiomux_setting max17048_i2c_scl_config = {
	/* GPIO_3 */
	.func = GPIOMUX_FUNC_3,
	.drv = GPIOMUX_DRV_8MA,
	.pull = GPIOMUX_PULL_NONE,
};
static struct gpiomux_setting max17048_int_config = {
	.func = GPIOMUX_FUNC_GPIO,
	.drv = GPIOMUX_DRV_6MA,
	.dir = GPIOMUX_IN,
};
#endif

#if 0
/* LGE_CHANGE
 * MAIN_CAM_RESET is changed from GPIO_90 to GPIO_4 - To fix build error after changing the function of GPIO_4
 * 2013-03-18, jinw.kim@lge.com
 */
static struct gpiomux_setting touch_id_act_cfg = {
	.func = GPIOMUX_FUNC_GPIO,
	.drv = GPIOMUX_DRV_6MA,
	.dir = GPIOMUX_IN,
};

static struct gpiomux_setting touch_id_sus_cfg = {
	.func = GPIOMUX_FUNC_GPIO,
	.drv = GPIOMUX_DRV_6MA,
	.dir = GPIOMUX_IN,
};
#endif

static struct gpiomux_setting touch_int_act_cfg = {
	.func = GPIOMUX_FUNC_GPIO,
	.drv = GPIOMUX_DRV_8MA,
	.dir = GPIOMUX_IN,
};

static struct gpiomux_setting touch_int_sus_cfg = {
	.func = GPIOMUX_FUNC_GPIO,
	.drv = GPIOMUX_DRV_2MA,
	.dir = GPIOMUX_IN,
};

static struct gpiomux_setting touch_i2c_act_cfg = {
	.func = GPIOMUX_FUNC_3,
	.drv = GPIOMUX_DRV_8MA,
	.pull = GPIOMUX_PULL_NONE,
};

static struct gpiomux_setting touch_i2c_sus_cfg = {
	.func = GPIOMUX_FUNC_3,
	.drv = GPIOMUX_DRV_2MA,
	.pull = GPIOMUX_PULL_DOWN,
	.dir = GPIOMUX_IN,
};

static struct gpiomux_setting touch_reset_sus_cfg = {
	.func = GPIOMUX_FUNC_GPIO,
	.drv = GPIOMUX_DRV_6MA,
	.dir = GPIOMUX_IN,
};

static struct gpiomux_setting touch_reset_act_cfg = {
	.func = GPIOMUX_FUNC_GPIO,
	.drv = GPIOMUX_DRV_6MA,
	.dir = GPIOMUX_IN,
};

#if !defined(CONFIG_LGE_NFC_SONY_CXD2235AGG)
static struct gpiomux_setting touch_ldoen_act_cfg = {
	.func = GPIOMUX_FUNC_GPIO,
	.drv = GPIOMUX_DRV_8MA,
	.dir = GPIOMUX_IN,
};

static struct gpiomux_setting touch_ldoen_sus_cfg = {
	.func = GPIOMUX_FUNC_GPIO,
	.drv = GPIOMUX_DRV_2MA,
	.dir = GPIOMUX_IN,
};
#endif
#endif

static struct msm_gpiomux_config msm_touch_configs[] __initdata = {
	{
		.gpio      = 8,		/* TOUCH RESET */
		.settings = {
			[GPIOMUX_ACTIVE] = &touch_reset_act_cfg,
			[GPIOMUX_SUSPENDED] = &touch_reset_sus_cfg,
		},
	},
	{
		.gpio      = 5,		/* TOUCH IRQ */
		.settings = {
			[GPIOMUX_ACTIVE] = &touch_int_act_cfg,
			[GPIOMUX_SUSPENDED] = &touch_int_sus_cfg,
		},
	},

};

#ifdef CONFIG_MACH_LGE
static struct gpiomux_setting hsic_sus_cfg = {
	.func = GPIOMUX_FUNC_GPIO,
	.drv = GPIOMUX_DRV_2MA,
	.pull = GPIOMUX_PULL_DOWN,
	.dir = GPIOMUX_OUT_LOW,
};
#else /* qmc original */
static struct gpiomux_setting hsic_sus_cfg = {
	.func = GPIOMUX_FUNC_GPIO,
	.drv = GPIOMUX_DRV_2MA,
	.pull = GPIOMUX_PULL_DOWN,
};
#endif

#if 0
static struct gpiomux_setting hsic_act_cfg = {
	.func = GPIOMUX_FUNC_1,
	.drv = GPIOMUX_DRV_12MA,
	.pull = GPIOMUX_PULL_NONE,
};
#endif
static struct gpiomux_setting hsic_hub_act_cfg = {
	.func = GPIOMUX_FUNC_GPIO,
	.drv = GPIOMUX_DRV_2MA,
	.pull = GPIOMUX_PULL_UP,
	.dir = GPIOMUX_IN,
};

#ifndef CONFIG_MACH_LGE
static struct gpiomux_setting hsic_resume_act_cfg = {
	.func = GPIOMUX_FUNC_GPIO,
	.drv = GPIOMUX_DRV_2MA,
	.pull = GPIOMUX_PULL_DOWN,
	.dir = GPIOMUX_OUT_LOW,
};

static struct gpiomux_setting hsic_resume_susp_cfg = {
	.func = GPIOMUX_FUNC_GPIO,
	.drv = GPIOMUX_DRV_2MA,
	.pull = GPIOMUX_PULL_NONE,
};
#endif

#if 0	/* Camera will use gpio 145 */
static struct msm_gpiomux_config msm_hsic_configs[] = {
/* LGE_CHANGE
 * Camera bring up - DCM
 * 2013-03-14, jinw.kim@lge.com
 */
	{
		.gpio = 145,               /* HSIC_DATA */
		.settings = {
			[GPIOMUX_ACTIVE] = &hsic_act_cfg,
			[GPIOMUX_SUSPENDED] = &hsic_sus_cfg,
		},
	},
	{
		.gpio = 80,
		.settings = {
			[GPIOMUX_ACTIVE] = &hsic_resume_act_cfg,
			[GPIOMUX_SUSPENDED] = &hsic_resume_susp_cfg,
		},
	},
};
#endif

static struct msm_gpiomux_config msm_hsic_hub_configs[] = {
	{
		.gpio = 50,               /* HSIC_HUB_INT_N */
		.settings = {
			[GPIOMUX_ACTIVE] = &hsic_hub_act_cfg,
			[GPIOMUX_SUSPENDED] = &hsic_sus_cfg,
		},
	},
};

static struct gpiomux_setting hall_ic_act_cfg = {
	.func = GPIOMUX_FUNC_GPIO,
	.drv = GPIOMUX_DRV_2MA,
	.pull = GPIOMUX_PULL_UP,
	.dir = GPIOMUX_IN,
};

static struct msm_gpiomux_config msm_hall_ic_configs[] = {
	{
		.gpio = 102,
		.settings = {
			[GPIOMUX_ACTIVE] = &hall_ic_act_cfg,
		},
	},
	{
		.gpio = 144,
		.settings = {
			[GPIOMUX_ACTIVE] = &hall_ic_act_cfg,
		},
	},
};

static struct gpiomux_setting mhl_suspend_config = {
	.func = GPIOMUX_FUNC_GPIO,
	.drv = GPIOMUX_DRV_2MA,
	.pull = GPIOMUX_PULL_DOWN,
};

static struct gpiomux_setting mhl_active_1_cfg = {
	.func = GPIOMUX_FUNC_1,
	.drv = GPIOMUX_DRV_2MA,
	.pull = GPIOMUX_PULL_UP,
	.dir = GPIOMUX_OUT_HIGH,
};

static struct gpiomux_setting hdmi_suspend_1_cfg = {
	.func = GPIOMUX_FUNC_GPIO,
	.drv = GPIOMUX_DRV_2MA,
	.pull = GPIOMUX_PULL_UP,
};

static struct gpiomux_setting hdmi_suspend_2_cfg = {
	.func = GPIOMUX_FUNC_GPIO,
	.drv = GPIOMUX_DRV_2MA,
	.pull = GPIOMUX_PULL_DOWN,
};

static struct gpiomux_setting hdmi_active_1_cfg = {
	.func = GPIOMUX_FUNC_1,
	.drv = GPIOMUX_DRV_2MA,
	.pull = GPIOMUX_PULL_UP,
};

static struct gpiomux_setting hdmi_active_2_cfg = {
	.func = GPIOMUX_FUNC_1,
	.drv = GPIOMUX_DRV_16MA,
	.pull = GPIOMUX_PULL_DOWN,
};

#if defined(CONFIG_MACH_LGE)
#if defined(CONFIG_MAX17050_FUELGAUGE)
static struct msm_gpiomux_config
		msm_fuel_gauge_max17050_configs[] __initdata = {
		{
		.gpio      = 2,		/* BLSP1 QUP1 I2C_DAT */
		.settings = {
			[GPIOMUX_ACTIVE]    = &max17050_i2c_sda_config,
			[GPIOMUX_SUSPENDED] = &max17050_i2c_sda_config,
		},
	},
	{
		.gpio      = 3,		/* BLSP1 QUP1 I2C_CLK */
		.settings = {
			[GPIOMUX_ACTIVE]    = &max17050_i2c_scl_config,
			[GPIOMUX_SUSPENDED] = &max17050_i2c_scl_config,
		},
	},
	{
		.gpio      = 9,		/* FUEL_GAUGE_INT_N */
		.settings = {
			[GPIOMUX_ACTIVE]    = &max17050_int_config,
			[GPIOMUX_SUSPENDED] = &max17050_int_config,
		},
	},
};
#endif

#if defined(CONFIG_MAX17048_FUELGAUGE)
static struct msm_gpiomux_config msm_fuel_gauge_configs[] __initdata = {
		{
		.gpio      = 2,		/* BLSP1 QUP1 I2C_DAT */
		.settings = {
			[GPIOMUX_ACTIVE]    = &max17048_i2c_sda_config,
			[GPIOMUX_SUSPENDED] = &max17048_i2c_sda_config,
		},
	},
	{
		.gpio      = 3,		/* BLSP1 QUP1 I2C_CLK */
		.settings = {
			[GPIOMUX_ACTIVE]    = &max17048_i2c_scl_config,
			[GPIOMUX_SUSPENDED] = &max17048_i2c_scl_config,
		},
	},
	{
		.gpio      = 9,		/* FUEL_GAUGE_INT_N */
		.settings = {
			[GPIOMUX_ACTIVE]    = &max17048_int_config,
			[GPIOMUX_SUSPENDED] = &max17048_int_config,
		},
	},
};
#endif
#endif

static struct msm_gpiomux_config msm_mhl_configs[] __initdata = {
	{
		/* mhl-sii8334 pwr */
		.gpio = 12,
		.settings = {
			[GPIOMUX_SUSPENDED] = &mhl_suspend_config,
			[GPIOMUX_ACTIVE]    = &mhl_active_1_cfg,
		},
	},
	{
		/* mhl-sii8334 intr */
		.gpio = 82,
		.settings = {
			[GPIOMUX_SUSPENDED] = &mhl_suspend_config,
			[GPIOMUX_ACTIVE]    = &mhl_active_1_cfg,
		},
	},
};


static struct msm_gpiomux_config msm_hdmi_configs[] __initdata = {
	{
		.gpio = 31,
		.settings = {
			[GPIOMUX_ACTIVE]    = &hdmi_active_1_cfg,
			[GPIOMUX_SUSPENDED] = &hdmi_suspend_1_cfg,
		},
	},
	{
		.gpio = 32,
		.settings = {
			[GPIOMUX_ACTIVE]    = &hdmi_active_1_cfg,
			[GPIOMUX_SUSPENDED] = &hdmi_suspend_1_cfg,
		},
	},
	{
		.gpio = 33,
		.settings = {
			[GPIOMUX_ACTIVE]    = &hdmi_active_1_cfg,
			[GPIOMUX_SUSPENDED] = &hdmi_suspend_1_cfg,
		},
	},
	{
		.gpio = 34,
		.settings = {
			[GPIOMUX_ACTIVE]    = &hdmi_active_2_cfg,
			[GPIOMUX_SUSPENDED] = &hdmi_suspend_2_cfg,
		},
	},
};

#ifndef CONFIG_MACH_LGE
static struct gpiomux_setting gpio_uart7_active_cfg = {
	.func = GPIOMUX_FUNC_3,
	.drv = GPIOMUX_DRV_8MA,
	.pull = GPIOMUX_PULL_NONE,
};

static struct gpiomux_setting gpio_uart7_suspend_cfg = {
	.func = GPIOMUX_FUNC_GPIO,
	.drv = GPIOMUX_DRV_2MA,
	.pull = GPIOMUX_PULL_DOWN,
};

static struct msm_gpiomux_config msm_blsp2_uart7_configs[] __initdata = {
	{
		.gpio	= 41,	/* BLSP2 UART7 TX */
		.settings = {
			[GPIOMUX_ACTIVE]    = &gpio_uart7_active_cfg,
			[GPIOMUX_SUSPENDED] = &gpio_uart7_suspend_cfg,
		},
	},
	{
		.gpio	= 42,	/* BLSP2 UART7 RX */
		.settings = {
			[GPIOMUX_ACTIVE]    = &gpio_uart7_active_cfg,
			[GPIOMUX_SUSPENDED] = &gpio_uart7_suspend_cfg,
		},
	},
	{
		.gpio	= 43,	/* BLSP2 UART7 CTS */
		.settings = {
			[GPIOMUX_ACTIVE]    = &gpio_uart7_active_cfg,
			[GPIOMUX_SUSPENDED] = &gpio_uart7_suspend_cfg,
		},
	},
	{
		.gpio	= 44,	/* BLSP2 UART7 RFR */
		.settings = {
			[GPIOMUX_ACTIVE]    = &gpio_uart7_active_cfg,
			[GPIOMUX_SUSPENDED] = &gpio_uart7_suspend_cfg,
		},
	},
};
#endif

static struct msm_gpiomux_config msm_rumi_blsp_configs[] __initdata = {
	{
		.gpio      = 45,	/* BLSP2 UART8 TX */
		.settings = {
			[GPIOMUX_SUSPENDED] = &gpio_uart_config,
		},
	},
	{
		.gpio      = 46,	/* BLSP2 UART8 RX */
		.settings = {
			[GPIOMUX_SUSPENDED] = &gpio_uart_config,
		},
	},
};

static struct msm_gpiomux_config msm_lcd_configs[] __initdata = {
	{
		.gpio = 58,
		.settings = {
			[GPIOMUX_ACTIVE]    = &lcd_en_act_cfg,
			[GPIOMUX_SUSPENDED] = &lcd_en_sus_cfg,
		},
	},
#if defined(CONFIG_BACKLIGHT_LM3630)
	{
		.gpio = 49, /* LCD_BL_EN */
		.settings = {
			[GPIOMUX_ACTIVE]    = &lcd_bl_en_active_cfg,
			[GPIOMUX_SUSPENDED] = &lcd_bl_en_suspend_cfg,
		},
	},
#endif

};

#if defined(CONFIG_LGE_NFC_SONY_CXD2235AGG)
static struct msm_gpiomux_config msm8974_nfc_configs_rev_c[] __initdata ={
		/* FELICA PON */
		{
			.gpio = 40,
			.settings = {
				[GPIOMUX_SUSPENDED] = &felica_pon_cfg,
			},
		},
	
		/* FELICA RFS */
		{
			.gpio = 94,
			.settings = {
				[GPIOMUX_SUSPENDED] = &felica_rfs_cfg,
			},
		},
	
		/* FELICA INT */
		{
			.gpio = 38,
			.settings = {
				[GPIOMUX_SUSPENDED] = &felica_int_cfg,
			},
		},
	
		/* FELICA CEN */
		{
			.gpio = 37,
			.settings = {
				[GPIOMUX_SUSPENDED] = &felica_lockcont_cfg,
			},
		},
		/* NFC HSEL */
		{
			.gpio = 59,
			.settings = {
				[GPIOMUX_SUSPENDED] = &nfc_hsel_cfg,
			},
		},
		/* SNFC INTU */
		{
			.gpio = 36,
			.settings = {
				[GPIOMUX_SUSPENDED] = &snfc_intu_cfg,
			},
		},	
		/* NFC HVDD */
		{
			.gpio = 35,
			.settings = {
				[GPIOMUX_SUSPENDED] = &snfc_hvdd_cfg,
			},
		},
		/* NFC UICC_VCC_CONTROL */
		{
			.gpio = 39,
			.settings = {
				[GPIOMUX_SUSPENDED] = &snfc_uicc_cfg,
			},
		},		
};	
#endif
#if defined(CONFIG_LGE_NFC_SONY_CXD2235AGG)
static struct msm_gpiomux_config msm8974_nfc_configs_rev_d[] __initdata ={
		/* FELICA PON */
		{
			.gpio = 40,
			.settings = {
				[GPIOMUX_SUSPENDED] = &felica_pon_cfg,
			},
		},
	
		/* FELICA RFS */
		{
			.gpio = 59,
			.settings = {
				[GPIOMUX_SUSPENDED] = &felica_rfs_cfg,
			},
		},
	
		/* FELICA INT */
		{
			.gpio = 37,
			.settings = {
				[GPIOMUX_SUSPENDED] = &felica_int_cfg,
			},
		},
	
		/* FELICA CEN */
		{
			.gpio = 38,
			.settings = {
				[GPIOMUX_SUSPENDED] = &felica_lockcont_cfg,
			},
		},
		/* NFC HSEL */
		{
			.gpio = 94,
			.settings = {
				[GPIOMUX_SUSPENDED] = &nfc_hsel_cfg,
			},
		},
		/* SNFC INTU */
		{
			.gpio = 35,
			.settings = {
				[GPIOMUX_SUSPENDED] = &snfc_intu_cfg,
			},
		},	
		/* NFC HVDD */
		{
			.gpio = 36,
			.settings = {
				[GPIOMUX_SUSPENDED] = &snfc_hvdd_cfg,
			},
		},
		/* NFC UICC_VCC_CONTROL */
		{
			.gpio = 39,
			.settings = {
				[GPIOMUX_SUSPENDED] = &snfc_uicc_cfg,
			},
		},		
};	
#endif

static struct msm_gpiomux_config msm_blsp_configs[] __initdata = {
#if defined(CONFIG_KS8851) || defined(CONFIG_KS8851_MODULE)
	{
		.gpio      = 0,		/* BLSP1 QUP SPI_DATA_MOSI */
		.settings = {
			[GPIOMUX_SUSPENDED] = &gpio_spi_config,
		},
	},
	{
		.gpio      = 1,		/* BLSP1 QUP SPI_DATA_MISO */
		.settings = {
			[GPIOMUX_SUSPENDED] = &gpio_spi_config,
		},
	},
	{
		.gpio      = 3,		/* BLSP1 QUP SPI_CLK */
		.settings = {
			[GPIOMUX_SUSPENDED] = &gpio_spi_config,
		},
	},
	{
		.gpio      = 9,		/* BLSP1 QUP SPI_CS2A_N */
		.settings = {
			[GPIOMUX_SUSPENDED] = &gpio_spi_cs2_config,
		},
	},
	{
		.gpio      = 8,		/* BLSP1 QUP SPI_CS1_N */
		.settings = {
			[GPIOMUX_SUSPENDED] = &gpio_spi_cs1_config,
		},
	},
#endif

#ifdef CONFIG_MACH_LGE
	{
		.gpio      = 6,		/* BLSP1 QUP2 I2C_DAT */
		.settings = {
			[GPIOMUX_ACTIVE]    = &touch_i2c_act_cfg,
			[GPIOMUX_SUSPENDED] = &touch_i2c_sus_cfg,
		},
	},
	{
		.gpio      = 7,		/* BLSP1 QUP2 I2C_CLK */
		.settings = {
			[GPIOMUX_ACTIVE]    = &touch_i2c_act_cfg,
			[GPIOMUX_SUSPENDED] = &touch_i2c_sus_cfg,
		},
	},
#else
	{
		.gpio      = 6,		/* BLSP1 QUP2 I2C_DAT */
		.settings = {
			[GPIOMUX_SUSPENDED] = &gpio_i2c_config,
		},
	},
	{
		.gpio      = 7,		/* BLSP1 QUP2 I2C_CLK */
		.settings = {
			[GPIOMUX_SUSPENDED] = &gpio_i2c_config,
		},
	},
#endif
	{
		.gpio      = 83,		/* BLSP11 QUP I2C_DAT */
		.settings = {
			[GPIOMUX_SUSPENDED] = &gpio_i2c_config,
		},
	},
	{
		.gpio      = 84,		/* BLSP11 QUP I2C_CLK */
		.settings = {
			[GPIOMUX_SUSPENDED] = &gpio_i2c_config,
		},
	},
#if 0
/* LGE_CHANGE
 * MAIN_CAM_RESET is changed from GPIO_90 to GPIO_4
 * 2013-03-18, jinw.kim@lge.com
 */
#ifdef CONFIG_MACH_LGE
	{
		.gpio      = 4,			/* BLSP2 UART TX */
		.settings = {
			[GPIOMUX_ACTIVE]    = &touch_id_act_cfg,
			[GPIOMUX_SUSPENDED] = &touch_id_sus_cfg,
		},
	},
#else
	{
		.gpio      = 4,			/* BLSP2 UART TX */
		.settings = {
			[GPIOMUX_SUSPENDED] = &gpio_uart_config,
		},
	},
#endif
#endif	//#if 0

#ifdef CONFIG_MACH_LGE
#else
	{
		.gpio      = 5,			/* BLSP2 UART RX */
		.settings = {
			[GPIOMUX_SUSPENDED] = &gpio_uart_config,
		},
	},
#endif
#ifdef CONFIG_MACH_LGE
	{
		.gpio      = 0,			/* BLSP2 UART TX */
		.settings = {
			[GPIOMUX_SUSPENDED] = &gpio_uart_config,
		},
	},
	{
		.gpio      = 1,			/* BLSP2 UART RX */
		.settings = {
			[GPIOMUX_SUSPENDED] = &gpio_uart_config,
		},
	},
#endif
#ifdef CONFIG_LGE_IRRC
	{
		.gpio	   = 85, 		/* BLSP2 UART TX */
		.settings = {
			[GPIOMUX_SUSPENDED] = &gpio_uart_config,
		},
	},
	{
		.gpio	   = 86, 		/* BLSP2 UART RX */
		.settings = {
			[GPIOMUX_SUSPENDED] = &gpio_uart_config,
		},
	},
#endif

/* LGE_CHANGE_S, [BT][younghyun.kwon@lge.com], 2013-01-29 */
#ifndef CONFIG_LGE_BLUETOOTH
	{
		.gpio      = 53,		/* BLSP2 QUP4 SPI_DATA_MOSI */
		.settings = {
			[GPIOMUX_ACTIVE] = &gpio_spi_config,
			[GPIOMUX_SUSPENDED] = &gpio_suspend_config[1],
		},
	},
	{
		.gpio      = 54,		/* BLSP2 QUP4 SPI_DATA_MISO */
		.settings = {
			[GPIOMUX_ACTIVE] = &gpio_spi_config,
			[GPIOMUX_SUSPENDED] = &gpio_suspend_config[1],
		},
	},
	{
		.gpio      = 56,		/* BLSP2 QUP4 SPI_CLK */
		.settings = {
			[GPIOMUX_ACTIVE] = &gpio_spi_config,
			[GPIOMUX_SUSPENDED] = &gpio_suspend_config[0],
		},
	},
	{
		.gpio      = 55,		/* BLSP2 QUP4 SPI_CS0_N */
		.settings = {
			[GPIOMUX_ACTIVE] = &gpio_spi_config,
			[GPIOMUX_SUSPENDED] = &gpio_suspend_config[0],
		},
	},
#endif /* CONFIG_LGE_BLUETOOTH */
/* LGE_CHANGE_S, [BT][younghyun.kwon@lge.com], 2013-01-29 */
	{
		.gpio      = 81,		/* EPM enable */
		.settings = {
			[GPIOMUX_SUSPENDED] = &gpio_epm_config,
		},
	},
};

static struct msm_gpiomux_config msm8974_slimbus_config[] __initdata = {
	{
		.gpio	= 70,		/* slimbus clk */
		.settings = {
			[GPIOMUX_SUSPENDED] = &slimbus,
		},
	},
	{
		.gpio	= 71,		/* slimbus data */
		.settings = {
			[GPIOMUX_SUSPENDED] = &slimbus,
		},
	},
};

static struct gpiomux_setting cam_settings[] = {
	{
		.func = GPIOMUX_FUNC_1, /*active 1*/ /* 0 */
		.drv = GPIOMUX_DRV_2MA,
		.pull = GPIOMUX_PULL_NONE,
	},

	{
		.func = GPIOMUX_FUNC_1, /*suspend*/ /* 1 */
		.drv = GPIOMUX_DRV_2MA,
		.pull = GPIOMUX_PULL_DOWN,
	},

	{
		.func = GPIOMUX_FUNC_1, /*i2c suspend*/ /* 2 */
		.drv = GPIOMUX_DRV_2MA,
		.pull = GPIOMUX_PULL_KEEPER,
	},

	{
		.func = GPIOMUX_FUNC_GPIO, /*active 0*/ /* 3 */
		.drv = GPIOMUX_DRV_2MA,
		.pull = GPIOMUX_PULL_NONE,
	},

	{
		.func = GPIOMUX_FUNC_GPIO, /*suspend 0*/ /* 4 */
		.drv = GPIOMUX_DRV_2MA,
		.pull = GPIOMUX_PULL_DOWN,
	},
};

static struct gpiomux_setting sd_card_det_active_config = {
	.func = GPIOMUX_FUNC_GPIO,
	.drv = GPIOMUX_DRV_2MA,
	.pull = GPIOMUX_PULL_NONE,
	.dir = GPIOMUX_IN,
};

static struct gpiomux_setting sd_card_det_sleep_config = {
	.func = GPIOMUX_FUNC_GPIO,
	.drv = GPIOMUX_DRV_2MA,
	.pull = GPIOMUX_PULL_UP,
	.dir = GPIOMUX_IN,
};
static struct msm_gpiomux_config sd_card_det __initdata = {
	.gpio = 62,
	.settings = {
		[GPIOMUX_ACTIVE]    = &sd_card_det_active_config,
		[GPIOMUX_SUSPENDED] = &sd_card_det_sleep_config,
	},
};

#if defined(CONFIG_LGE_NFC_SONY_CXD2235AGG)
static struct msm_gpiomux_config msm8974_felica_uart_blsp1_configs[] __initdata = {
	{
		.gpio      = 23,		/* BLSP1 UART5 TX */
		.settings = {
			[GPIOMUX_ACTIVE] = &gpio_uart_felica_active,
			[GPIOMUX_SUSPENDED] = &gpio_uart_felica,
		},
	},
	{
		.gpio      = 24,		/* BLSP1 UART5 RX */
		.settings = {
			[GPIOMUX_ACTIVE] = &gpio_uart_felica_active,
			[GPIOMUX_SUSPENDED] = &gpio_uart_felica,
		},
	},
};
#endif
static struct msm_gpiomux_config msm_sensor_configs[] __initdata = {
	{
		.gpio = 15, /* CAM_MCLK0 */
		.settings = {
			[GPIOMUX_ACTIVE]    = &cam_settings[0],
			[GPIOMUX_SUSPENDED] = &cam_settings[1],
		},
	},
	{
		.gpio = 16, /* CAM_MCLK1 */
		.settings = {
			[GPIOMUX_ACTIVE]    = &cam_settings[3],
			[GPIOMUX_SUSPENDED] = &cam_settings[4],
		},
	},
	{
		.gpio = 17, /* CAM_MCLK2 */
		.settings = {
			[GPIOMUX_ACTIVE]    = &cam_settings[0],
			[GPIOMUX_SUSPENDED] = &cam_settings[1],
		},
	},
	{
		.gpio = 18, /* WEBCAM1_RESET_N / CAM_MCLK3 */
		.settings = {
			[GPIOMUX_ACTIVE]    = &cam_settings[3],
			[GPIOMUX_SUSPENDED] = &cam_settings[4],
		},
	},
	{
		.gpio = 19, /* CCI_I2C_SDA0 */
		.settings = {
			[GPIOMUX_ACTIVE]    = &cam_settings[0],
			[GPIOMUX_SUSPENDED] = &gpio_suspend_config[0],
		},
	},
	{
		.gpio = 20, /* CCI_I2C_SCL0 */
		.settings = {
			[GPIOMUX_ACTIVE]    = &cam_settings[0],
			[GPIOMUX_SUSPENDED] = &gpio_suspend_config[0],
		},
	},
	{
		.gpio = 21, /* CCI_I2C_SDA1 */
		.settings = {
			[GPIOMUX_ACTIVE]    = &cam_settings[0],
			[GPIOMUX_SUSPENDED] = &gpio_suspend_config[0],
		},
	},
	{
		.gpio = 22, /* CCI_I2C_SCL1 */
		.settings = {
			[GPIOMUX_ACTIVE]    = &cam_settings[0],
			[GPIOMUX_SUSPENDED] = &gpio_suspend_config[0],
		},
	},
#if !defined(CONFIG_LGE_NFC_SONY_CXD2235AGG)	
	{
		.gpio = 23, /* FLASH_LED_EN */
		.settings = {
			[GPIOMUX_ACTIVE]    = &touch_ldoen_act_cfg,
			[GPIOMUX_SUSPENDED] = &touch_ldoen_sus_cfg,
		},
	},
	{
		.gpio = 24, /* FLASH_LED_NOW */
		.settings = {
			[GPIOMUX_ACTIVE]    = &cam_settings[0],
			[GPIOMUX_SUSPENDED] = &gpio_suspend_config[1],
		},
	},
#endif
	{
		.gpio = 25, /* WEBCAM2_RESET_N */
		.settings = {
			[GPIOMUX_ACTIVE]    = &cam_settings[0],
			[GPIOMUX_SUSPENDED] = &gpio_suspend_config[1],
		},
	},
	{
		.gpio = 26, /* CAM_IRQ */
		.settings = {
			[GPIOMUX_ACTIVE]    = &cam_settings[0],
			[GPIOMUX_SUSPENDED] = &cam_settings[1],
		},
	},
#ifdef CONFIG_MACH_LGE
	/* NULL - GPIO_27 : used with Motor PWM pin
		GPIO_28 : used with SlimPort IRQ pin */
#else /* QCT original */
	{
		.gpio = 27, /* OIS_SYNC */
		.settings = {
			[GPIOMUX_ACTIVE]    = &cam_settings[0],
			[GPIOMUX_SUSPENDED] = &gpio_suspend_config[1],
		},

	},
	{
		.gpio = 28, /* WEBCAM1_STANDBY */
		.settings = {
			[GPIOMUX_ACTIVE]    = &cam_settings[0],
			[GPIOMUX_SUSPENDED] = &gpio_suspend_config[1],
		},
	},
#endif
/* TSIF1 GPIO 89~92 is used for 1seg tsif */
#if !defined (CONFIG_LGE_BROADCAST_ONESEG)
	{
		.gpio = 89, /* CAM1_STANDBY_N */
		.settings = {
			[GPIOMUX_ACTIVE]    = &cam_settings[0],
			[GPIOMUX_SUSPENDED] = &cam_settings[1],
		},
	},
#endif  /* CONFIG_LGE_BROADCAST_ONESEG */
#if defined(CONFIG_MACH_LGE)
/* LGE_CHANGE
 * MAIN_CAM_RESET is changed from GPIO_90 to GPIO_4
 * 2013-03-18, jinw.kim@lge.com
 */
	{
		.gpio = 4, /* CAM1_RST_N */
		.settings = {
			[GPIOMUX_ACTIVE]    = &cam_settings[3],
			[GPIOMUX_SUSPENDED] = &cam_settings[4],
		},
	},
#else //Original
/* TSIF1 GPIO 89~92 is used for 1seg tsif */
#if !defined (CONFIG_LGE_BROADCAST_ONESEG)
	{
		.gpio = 90, /* CAM1_RST_N */
		.settings = {
			[GPIOMUX_ACTIVE]    = &cam_settings[0],
			[GPIOMUX_SUSPENDED] = &cam_settings[1],
		},
	},
#endif  /* CONFIG_LGE_BROADCAST_ONESEG */
#endif

#if defined(CONFIG_BACKLIGHT_LM3630)
#else
/* TSIF1 GPIO 89~92 is used for 1seg tsif */
#if !defined (CONFIG_LGE_BROADCAST_ONESEG)
	{
		.gpio = 91, /* CAM2_STANDBY_N */
		.settings = {
			[GPIOMUX_ACTIVE]    = &cam_settings[0],
			[GPIOMUX_SUSPENDED] = &cam_settings[1],
		},
	},
#endif  /* CONFIG_LGE_BROADCAST_ONESEG */
#endif
/* TSIF1 GPIO 89~92 is used for 1seg tsif */
#if !defined (CONFIG_LGE_BROADCAST_ONESEG)
	{
		.gpio = 92, /* CAM2_RST_N */
		.settings = {
			[GPIOMUX_ACTIVE]    = &cam_settings[0],
			[GPIOMUX_SUSPENDED] = &cam_settings[1],
		},
	},
#endif  /* CONFIG_LGE_BROADCAST_ONESEG */
#if defined(CONFIG_MACH_LGE)
/* LGE_CHANGE_S
 * Camera bring up - DCM
 * 2013-03-14, jinw.kim@lge.com
 */
	{
		.gpio = 57, /* 13M_VCM_EN */
		.settings = {
			[GPIOMUX_ACTIVE]    = &cam_settings[3],
			[GPIOMUX_SUSPENDED] = &cam_settings[4],
		},
	},
	{
		.gpio = 145, /* OIS_LDO_EN */
		.settings = {
			[GPIOMUX_ACTIVE]    = &cam_settings[3],
			[GPIOMUX_SUSPENDED] = &cam_settings[4],
		},
	},
	{
		.gpio = 29, /* OIS_RESET */
		.settings = {
			[GPIOMUX_ACTIVE]    = &cam_settings[3],
			[GPIOMUX_SUSPENDED] = &cam_settings[4],
		},
	},
	{
		.gpio = 96, /* 13M_VIO */
		.settings = {
			[GPIOMUX_ACTIVE]    = &cam_settings[3],
			[GPIOMUX_SUSPENDED] = &cam_settings[4],
		},
	},
	{
		.gpio = 30, /* VT_LDO_EN */
		.settings = {
			[GPIOMUX_ACTIVE]    = &cam_settings[3],
			[GPIOMUX_SUSPENDED] = &cam_settings[4],
		},
	},
 #endif
};

#ifndef CONFIG_MACH_LGE
static struct gpiomux_setting pri_auxpcm_act_cfg = {
	.func = GPIOMUX_FUNC_1,
	.drv = GPIOMUX_DRV_8MA,
	.pull = GPIOMUX_PULL_NONE,
};


static struct gpiomux_setting pri_auxpcm_sus_cfg = {
	.func = GPIOMUX_FUNC_1,
	.drv = GPIOMUX_DRV_2MA,
	.pull = GPIOMUX_PULL_DOWN,
};

static struct msm_gpiomux_config msm8974_pri_auxpcm_configs[] __initdata = {
	{
		.gpio = 65,
		.settings = {
			[GPIOMUX_SUSPENDED] = &pri_auxpcm_sus_cfg,
			[GPIOMUX_ACTIVE] = &pri_auxpcm_act_cfg,
		},
	},
	{
		.gpio = 66,
		.settings = {
			[GPIOMUX_SUSPENDED] = &pri_auxpcm_sus_cfg,
			[GPIOMUX_ACTIVE] = &pri_auxpcm_act_cfg,
		},
	},
	{
		.gpio = 67,
		.settings = {
			[GPIOMUX_SUSPENDED] = &pri_auxpcm_sus_cfg,
			[GPIOMUX_ACTIVE] = &pri_auxpcm_act_cfg,
		},
	},
	{
		.gpio = 68,
		.settings = {
			[GPIOMUX_SUSPENDED] = &pri_auxpcm_sus_cfg,
			[GPIOMUX_ACTIVE] = &pri_auxpcm_act_cfg,
		},
	},
};
#endif

/* LGE_CHANGE_S, [WiFi][hayun.kim@lge.com], 2013-01-22, Wifi Bring Up */
#if defined (CONFIG_BCMDHD) || defined (CONFIG_BCMDHD_MODULE)
#else
static struct msm_gpiomux_config wcnss_5wire_interface[] = {
#if !defined(CONFIG_LGE_NFC_SONY_CXD2235AGG)
	{
		.gpio = 36,
		.settings = {
			[GPIOMUX_ACTIVE]    = &wcnss_5wire_active_cfg,
			[GPIOMUX_SUSPENDED] = &wcnss_5wire_suspend_cfg,
		},
	},
	{
		.gpio = 37,
		.settings = {
			[GPIOMUX_ACTIVE]    = &wcnss_5wire_active_cfg,
			[GPIOMUX_SUSPENDED] = &wcnss_5wire_suspend_cfg,
		},
	},

	{
		.gpio = 38,
		.settings = {
			[GPIOMUX_ACTIVE]    = &wcnss_5wire_active_cfg,
			[GPIOMUX_SUSPENDED] = &wcnss_5wire_suspend_cfg,
		},
	},
	{
		.gpio = 39,
		.settings = {
			[GPIOMUX_ACTIVE]    = &wcnss_5wire_active_cfg,
			[GPIOMUX_SUSPENDED] = &wcnss_5wire_suspend_cfg,
		},
	},
	{
		.gpio = 40,
		.settings = {
			[GPIOMUX_ACTIVE]    = &wcnss_5wire_active_cfg,
			[GPIOMUX_SUSPENDED] = &wcnss_5wire_suspend_cfg,
		},
	},
#endif
};
#endif
/* LGE_CHANGE_E, [WiFi][hayun.kim@lge.com], 2013-01-22, Wifi Bring Up */

static struct msm_gpiomux_config msm_taiko_config[] __initdata = {
	{
		.gpio	= 63,		/* SYS_RST_N */
		.settings = {
			[GPIOMUX_SUSPENDED] = &taiko_reset,
		},
	},
	{
		.gpio	= 72,		/* CDC_INT */
		.settings = {
			[GPIOMUX_SUSPENDED] = &taiko_int,
		},
	},
};
#ifdef CONFIG_SLIMPORT_ANX7808
static struct gpiomux_setting slimport_reset_act_cfg = {
	.func = GPIOMUX_FUNC_GPIO,
	.drv = GPIOMUX_DRV_8MA,
	.pull = GPIOMUX_PULL_UP,
};

static struct gpiomux_setting slimport_int_act_cfg = {
	.func = GPIOMUX_FUNC_GPIO,
	.drv = GPIOMUX_DRV_8MA,
	.pull = GPIOMUX_PULL_UP,
	.dir = GPIOMUX_IN,
};

static struct gpiomux_setting slimport_reset_cfg = {
	.func = GPIOMUX_FUNC_GPIO,
	.drv = GPIOMUX_DRV_2MA,
	.pull = GPIOMUX_PULL_NONE,
};

static struct gpiomux_setting slimport_int_cfg = {
	.func = GPIOMUX_FUNC_GPIO,
	.drv = GPIOMUX_DRV_2MA,
	.pull = GPIOMUX_PULL_NONE,
	.dir = GPIOMUX_IN,
};

static struct msm_gpiomux_config slimport_configs[] __initdata = {
	{
		.gpio      = 68,		/* SLIMPORT RESET */
		.settings = {
			[GPIOMUX_ACTIVE] = &slimport_reset_act_cfg,
			[GPIOMUX_SUSPENDED] = &slimport_reset_cfg,
		},
	},
	{
		.gpio      = 28,		/* SLIMPORT IRQ */
		.settings = {
			[GPIOMUX_ACTIVE] = &slimport_int_act_cfg,
			[GPIOMUX_SUSPENDED] = &slimport_int_cfg,
		},
	},

};
#endif

#ifdef CONFIG_MACH_LGE
static struct gpiomux_setting headset_active_cfg_gpio65 ={
	.func = GPIOMUX_FUNC_GPIO,
	.drv = GPIOMUX_DRV_2MA,
	.pull = GPIOMUX_PULL_UP,
	.dir  = GPIOMUX_IN,
};

static struct gpiomux_setting headset_active_cfg_gpio64 ={
	.func = GPIOMUX_FUNC_GPIO,
	.drv = GPIOMUX_DRV_2MA,
	.pull = GPIOMUX_PULL_UP,
	.dir  = GPIOMUX_IN,
};

static struct msm_gpiomux_config headset_configs[] ={
	{
		.gpio = 64,
		.settings = {
			[GPIOMUX_ACTIVE]    = &headset_active_cfg_gpio64,
		},
	},

	{
		.gpio = 65,
		.settings = {
			[GPIOMUX_ACTIVE]    = &headset_active_cfg_gpio65,
		},
	},
};

/* sensor GPIO setting for LGPS11, TODO: Need change APDS config*/
#if 0  /*sensor disable */
static struct gpiomux_setting sensor_int_config = {
	.func = GPIOMUX_FUNC_GPIO,
	.drv  = GPIOMUX_DRV_2MA,
	.pull = GPIOMUX_PULL_NONE,
	.dir  = GPIOMUX_IN,
};

static struct gpiomux_setting sensor_en_config = {
	.func = GPIOMUX_FUNC_GPIO,
	.drv  = GPIOMUX_DRV_2MA,
	.pull = GPIOMUX_PULL_NONE,
	.dir  = GPIOMUX_OUT_HIGH,
};

static struct msm_gpiomux_config sensor_configs[] __initdata = {
	{
		.gpio      = 87,    /* BLSP12 QUP I2C_DAT */
		.settings = {
			[GPIOMUX_SUSPENDED] = &gpio_i2c_config,
		},
	},
	{
		.gpio      = 88,    /* BLSP12 QUP I2C_CLK */
		.settings = {
			[GPIOMUX_SUSPENDED] = &gpio_i2c_config,
		},
	},
	{
		.gpio      = 10,    /* BLSP3 QUP I2C_DAT */
		.settings = {
			[GPIOMUX_SUSPENDED] = &gpio_i2c_config,
		},
	},
	{
		.gpio      = 11,    /* BLSP3 QUP I2C_CLK */
		.settings = {
			[GPIOMUX_SUSPENDED] = &gpio_i2c_config,
		},
	},
	{
		.gpio      = 3,    /* GYRO_DATA_EN */
		.settings = {
			[GPIOMUX_ACTIVE] = &sensor_en_config,
			[GPIOMUX_SUSPENDED] = &sensor_en_config,
		},
	},
	{
		.gpio      = 65,    /*ACCL_INT2 */
		.settings = {
			[GPIOMUX_ACTIVE] = &sensor_int_config,
			[GPIOMUX_SUSPENDED] = &sensor_int_config,
		},
	},
	{
		.gpio      = 66,    /* GYRO_INT2*/
		.settings = {
			[GPIOMUX_ACTIVE] = &sensor_int_config,
			[GPIOMUX_SUSPENDED] = &sensor_int_config,
		},
	},
/*
	{
		.gpio      = 67,    //TODO : COMPASS_DRDY
		.settings = {
			[GPIOMUX_ACTIVE] = &sensor_int_config,
			[GPIOMUX_SUSPENDED] = &sensor_int_config,
		},
	},
*/
	{
		.gpio      = 73,    /* ACCL_INT1*/
		.settings = {
			[GPIOMUX_ACTIVE] = &sensor_int_config,
			[GPIOMUX_SUSPENDED] = &sensor_int_config,
		},
	},
	{
		.gpio      = 74,    /* PROXIMITY_INT */
		.settings = {
			[GPIOMUX_ACTIVE] = &sensor_int_config,
			[GPIOMUX_SUSPENDED] = &sensor_int_config,
		},
	},
	{
		.gpio      = 102,    /* GYRO_int2 (DRDY)*/
		.settings = {
			[GPIOMUX_ACTIVE] = &sensor_int_config,
			[GPIOMUX_SUSPENDED] = &sensor_int_config,
		},
	},

};
#endif
#endif

#if defined(CONFIG_LGE_SM100) || defined(CONFIG_TSPDRV)
static struct gpiomux_setting vibrator_suspend_cfg = {
       .func = GPIOMUX_FUNC_GPIO,
       .drv = GPIOMUX_DRV_2MA,
       .pull = GPIOMUX_PULL_DOWN,
};

static struct gpiomux_setting vibrator_active_cfg_gpio27 = {
       .func = GPIOMUX_FUNC_6,
       .drv = GPIOMUX_DRV_2MA,
       .pull = GPIOMUX_PULL_NONE,
};

static struct gpiomux_setting vibrator_active_cfg_gpio60 = {
       .func = GPIOMUX_FUNC_GPIO,
       .drv = GPIOMUX_DRV_2MA,
       .pull = GPIOMUX_PULL_NONE,
};

static struct msm_gpiomux_config vibrator_configs[] = {
	{
		.gpio = 27,
		.settings = {
			[GPIOMUX_ACTIVE]    = &vibrator_active_cfg_gpio27,
			[GPIOMUX_SUSPENDED] = &vibrator_suspend_cfg,
		},
	},
	{
		.gpio = 60,
		.settings = {
			[GPIOMUX_ACTIVE]    = &vibrator_active_cfg_gpio60,
			[GPIOMUX_SUSPENDED] = &vibrator_suspend_cfg,
		},
	},
};
#endif

#if !defined(CONFIG_LGE_NFC_SONY_CXD2235AGG)
static struct gpiomux_setting sdc3_clk_actv_cfg = {
	.func = GPIOMUX_FUNC_2,
	.drv = GPIOMUX_DRV_8MA,
	.pull = GPIOMUX_PULL_NONE,
};

static struct gpiomux_setting sdc3_cmd_data_0_3_actv_cfg = {
	.func = GPIOMUX_FUNC_2,
	.drv = GPIOMUX_DRV_8MA,
	.pull = GPIOMUX_PULL_UP,
};

static struct gpiomux_setting sdc3_suspend_cfg = {
	.func = GPIOMUX_FUNC_GPIO,
	.drv = GPIOMUX_DRV_2MA,
	.pull = GPIOMUX_PULL_DOWN,
};

static struct gpiomux_setting sdc3_data_1_suspend_cfg = {
	.func = GPIOMUX_FUNC_GPIO,
	.drv = GPIOMUX_DRV_8MA,
	.pull = GPIOMUX_PULL_UP,
};
#endif

static struct msm_gpiomux_config msm8974_sdc3_configs[] __initdata = {
#if !defined(CONFIG_LGE_NFC_SONY_CXD2235AGG)
	{
		/* DAT3 */
		.gpio      = 35,
		.settings = {
			[GPIOMUX_ACTIVE]    = &sdc3_cmd_data_0_3_actv_cfg,
			[GPIOMUX_SUSPENDED] = &sdc3_suspend_cfg,
		},
	},
	{
		/* DAT2 */
		.gpio      = 36,
		.settings = {
			[GPIOMUX_ACTIVE]    = &sdc3_cmd_data_0_3_actv_cfg,
			[GPIOMUX_SUSPENDED] = &sdc3_suspend_cfg,
		},
	},
	{
		/* DAT1 */
		.gpio      = 37,
		.settings = {
			[GPIOMUX_ACTIVE]    = &sdc3_cmd_data_0_3_actv_cfg,
			[GPIOMUX_SUSPENDED] = &sdc3_data_1_suspend_cfg,
		},
	},

	{
		/* DAT0 */
		.gpio      = 38,
		.settings = {
			[GPIOMUX_ACTIVE]    = &sdc3_cmd_data_0_3_actv_cfg,
			[GPIOMUX_SUSPENDED] = &sdc3_suspend_cfg,
		},
	},
	{
		/* CMD */
		.gpio      = 39,
		.settings = {
			[GPIOMUX_ACTIVE]    = &sdc3_cmd_data_0_3_actv_cfg,
			[GPIOMUX_SUSPENDED] = &sdc3_suspend_cfg,
		},
	},
	{
		/* CLK */
		.gpio      = 40,
		.settings = {
			[GPIOMUX_ACTIVE]    = &sdc3_clk_actv_cfg,
			[GPIOMUX_SUSPENDED] = &sdc3_suspend_cfg,
		},
	},
#endif
};

static void msm_gpiomux_sdc3_install(void)
{
	msm_gpiomux_install(msm8974_sdc3_configs,
			    ARRAY_SIZE(msm8974_sdc3_configs));
}

#ifdef CONFIG_MMC_MSM_SDC4_SUPPORT
static struct gpiomux_setting sdc4_clk_actv_cfg = {
	.func = GPIOMUX_FUNC_2,
	.drv = GPIOMUX_DRV_8MA,
	.pull = GPIOMUX_PULL_NONE,
};

static struct gpiomux_setting sdc4_cmd_data_0_3_actv_cfg = {
	.func = GPIOMUX_FUNC_2,
	.drv = GPIOMUX_DRV_8MA,
	.pull = GPIOMUX_PULL_UP,
};

static struct gpiomux_setting sdc4_suspend_cfg = {
	.func = GPIOMUX_FUNC_GPIO,
	.drv = GPIOMUX_DRV_2MA,
	.pull = GPIOMUX_PULL_DOWN,
};

static struct gpiomux_setting sdc4_data_1_suspend_cfg = {
	.func = GPIOMUX_FUNC_GPIO,
	.drv = GPIOMUX_DRV_8MA,
	.pull = GPIOMUX_PULL_UP,
};

static struct msm_gpiomux_config msm8974_sdc4_configs[] __initdata = {
/* TSIF1 GPIO 89~92 is used for 1seg tsif */
#if !defined (CONFIG_LGE_BROADCAST_ONESEG)
	{
		/* DAT3 */
		.gpio      = 92,
		.settings = {
			[GPIOMUX_ACTIVE]    = &sdc4_cmd_data_0_3_actv_cfg,
			[GPIOMUX_SUSPENDED] = &sdc4_suspend_cfg,
		},
	},
#endif  /* CONFIG_LGE_BROADCAST_ONESEG */
#if !defined(CONFIG_LGE_NFC_SONY_CXD2235AGG)
	{
		/* DAT2 */
		.gpio      = 94,
		.settings = {
			[GPIOMUX_ACTIVE]    = &sdc4_cmd_data_0_3_actv_cfg,
			[GPIOMUX_SUSPENDED] = &sdc4_suspend_cfg,
		},
	},
#endif
	{
		/* DAT1 */
		.gpio      = 95,
		.settings = {
			[GPIOMUX_ACTIVE]    = &sdc4_cmd_data_0_3_actv_cfg,
			[GPIOMUX_SUSPENDED] = &sdc4_data_1_suspend_cfg,
		},
	},
#if 0	/* Camera will use gpio 96 */
/* LGE_CHANGE_S
 * Camera bring up - DCM
 * 2013-03-14, jinw.kim@lge.com
 */
	{
		/* DAT0 */
		.gpio      = 96,
		.settings = {
			[GPIOMUX_ACTIVE]    = &sdc4_cmd_data_0_3_actv_cfg,
			[GPIOMUX_SUSPENDED] = &sdc4_suspend_cfg,
		},
	},
#endif
/* TSIF1 GPIO 89~92 is used for 1seg tsif */
#if !defined (CONFIG_LGE_BROADCAST_ONESEG)
	{
		/* CMD */
		.gpio      = 91,
		.settings = {
			[GPIOMUX_ACTIVE]    = &sdc4_cmd_data_0_3_actv_cfg,
			[GPIOMUX_SUSPENDED] = &sdc4_suspend_cfg,
		},
	},
#endif /* CONFIG_LGE_BROADCAST_ONESEG */
	{
		/* CLK */
		.gpio      = 93,
		.settings = {
			[GPIOMUX_ACTIVE]    = &sdc4_clk_actv_cfg,
			[GPIOMUX_SUSPENDED] = &sdc4_suspend_cfg,
		},
	},
};

static void msm_gpiomux_sdc4_install(void)
{
	msm_gpiomux_install(msm8974_sdc4_configs,
			    ARRAY_SIZE(msm8974_sdc4_configs));
}
#else
static void msm_gpiomux_sdc4_install(void) {}
#endif /* CONFIG_MMC_MSM_SDC4_SUPPORT */

/* LGE_CHANGE_S, [BT][younghyun.kwon@lge.com], 2013-01-29 */
#ifdef CONFIG_LGE_BLUETOOTH
static struct gpiomux_setting bt_gpio_uart_active_config = {
    .func = GPIOMUX_FUNC_2,
    .drv = GPIOMUX_DRV_8MA,
    .pull = GPIOMUX_PULL_NONE, /* Should be PULL NONE */
};

static struct gpiomux_setting bt_gpio_uart_suspend_config = {
    .func = GPIOMUX_FUNC_GPIO,
    .drv = GPIOMUX_DRV_2MA,
    .pull = GPIOMUX_PULL_NONE, /* PULL Configuration */
};

static struct gpiomux_setting bt_rfkill_active_config = {
	.func = GPIOMUX_FUNC_GPIO,
	.drv  = GPIOMUX_DRV_6MA,
	.pull = GPIOMUX_PULL_NONE,
};

static struct gpiomux_setting bt_rfkill_suspend_config = {
	.func = GPIOMUX_FUNC_GPIO,
	.drv  = GPIOMUX_DRV_2MA,
	.pull = GPIOMUX_PULL_NONE,
};

static struct gpiomux_setting bt_host_wakeup_active_config = {
	.func = GPIOMUX_FUNC_GPIO,
	.drv = GPIOMUX_DRV_2MA,
	.pull = GPIOMUX_PULL_NONE,
	.dir = GPIOMUX_IN,
};

static struct gpiomux_setting bt_host_wakeup_suspend_config = {
	.func = GPIOMUX_FUNC_GPIO,
	.drv = GPIOMUX_DRV_2MA,
	.pull = GPIOMUX_PULL_NONE,
	.dir = GPIOMUX_IN,
};

static struct gpiomux_setting bt_wakeup_active_config = {
	.func = GPIOMUX_FUNC_GPIO,
	.drv = GPIOMUX_DRV_2MA,
	.pull = GPIOMUX_PULL_NONE,
};

static struct gpiomux_setting bt_wakeup_suspend_config = {
	.func = GPIOMUX_FUNC_GPIO,
	.drv = GPIOMUX_DRV_2MA,
	.pull = GPIOMUX_PULL_NONE,
};

static struct gpiomux_setting bt_pcm_active_config = {
	.func = GPIOMUX_FUNC_1,
	.drv = GPIOMUX_DRV_8MA,
	.pull = GPIOMUX_PULL_NONE,
};

static struct gpiomux_setting bt_pcm_suspend_config = {
	.func = GPIOMUX_FUNC_1,
	.drv = GPIOMUX_DRV_2MA,
	.pull = GPIOMUX_PULL_DOWN,
};

static struct msm_gpiomux_config bt_msm_blsp_configs[] __initdata = {
	{
		.gpio = 53, /* BLSP2 UART10 TX */
		.settings = {
			[GPIOMUX_ACTIVE] = &bt_gpio_uart_active_config ,
			[GPIOMUX_SUSPENDED] = &bt_gpio_uart_suspend_config ,
		},
	},
	{
		.gpio = 54, /* BLSP2 UART10 RX */
		.settings = {
			[GPIOMUX_ACTIVE] = &bt_gpio_uart_active_config ,
			[GPIOMUX_SUSPENDED] = &bt_gpio_uart_suspend_config ,
		},
	},
	{
		.gpio = 55, /* BLSP2 UART10 CTS */
		.settings = {
			[GPIOMUX_ACTIVE] = &bt_gpio_uart_active_config ,
			[GPIOMUX_SUSPENDED] = &bt_gpio_uart_suspend_config ,
		},
	},
	{
		.gpio = 56, /* BLSP2 UART10 RFR */
		.settings = {
			[GPIOMUX_ACTIVE] = &bt_gpio_uart_active_config ,
			[GPIOMUX_SUSPENDED] = &bt_gpio_uart_suspend_config ,
		},
	},
};

static struct msm_gpiomux_config bt_rfkill_configs[] = {
	{
		.gpio = 41,
		.settings = {
			[GPIOMUX_ACTIVE]    = &bt_rfkill_active_config,
			[GPIOMUX_SUSPENDED] = &bt_rfkill_suspend_config,
		},
	},
};

static struct msm_gpiomux_config bt_host_wakeup_configs[] __initdata = {
	{
		.gpio = 42,
		.settings = {
			[GPIOMUX_ACTIVE]    = &bt_host_wakeup_active_config,
			[GPIOMUX_SUSPENDED] = &bt_host_wakeup_suspend_config,
		},
	},
};

static struct msm_gpiomux_config bt_wakeup_configs[] __initdata = {
	{
		.gpio = 62,
		.settings = {
			[GPIOMUX_ACTIVE]    = &bt_wakeup_active_config,
			[GPIOMUX_SUSPENDED] = &bt_wakeup_suspend_config,
		},
	},
};

static struct msm_gpiomux_config bt_pcm_configs[] __initdata = {
	{
		.gpio	   = 79,	/* BT_PCM_CLK */
		.settings = {
			[GPIOMUX_ACTIVE]	= &bt_pcm_active_config,
			[GPIOMUX_SUSPENDED] = &bt_pcm_suspend_config,
		},
	},
	{
		.gpio	   = 80,	/* BT_PCM_SYNC */
		.settings = {
			[GPIOMUX_ACTIVE]	= &bt_pcm_active_config,
			[GPIOMUX_SUSPENDED] = &bt_pcm_suspend_config,
		},
	},
	{
		.gpio	   = 81,	/* BT_PCM_DIN */
		.settings = {
			[GPIOMUX_ACTIVE]	= &bt_pcm_active_config,
			[GPIOMUX_SUSPENDED] = &bt_pcm_suspend_config,
		},
	},
	{
		.gpio	   = 82,	/* BT_PCM_DOUT */
		.settings = {
			[GPIOMUX_ACTIVE]	= &bt_pcm_active_config,
			[GPIOMUX_SUSPENDED] = &bt_pcm_suspend_config,
		},
	}
};

static void bluetooth_msm_gpiomux_install(void)
{
    /* UART */
    msm_gpiomux_install(bt_msm_blsp_configs, ARRAY_SIZE(bt_msm_blsp_configs));

    /* RFKILL */
    msm_gpiomux_install(bt_rfkill_configs, ARRAY_SIZE(bt_rfkill_configs));

    /* HOST WAKE-UP */
    msm_gpiomux_install(bt_host_wakeup_configs, ARRAY_SIZE(bt_host_wakeup_configs));

    /* BT WAKE-UP */
    msm_gpiomux_install(bt_wakeup_configs, ARRAY_SIZE(bt_wakeup_configs));

    /* PCM I/F */
    msm_gpiomux_install(bt_pcm_configs, ARRAY_SIZE(bt_pcm_configs));
}
#endif /* CONFIG_LGE_BLUETOOTH */
/* LGE_CHANGE_E, [BT][younghyun.kwon@lge.com], 2013-01-29 */


static struct msm_gpiomux_config apq8074_dragonboard_ts_config[] __initdata = {
	{
		/* BLSP1 QUP I2C_DATA */
		.gpio      = 2,
		.settings = {
			[GPIOMUX_SUSPENDED] = &gpio_i2c_config,
		},
	},
	{
		/* BLSP1 QUP I2C_CLK */
		.gpio      = 3,
		.settings = {
			[GPIOMUX_SUSPENDED] = &gpio_i2c_config,
		},
	},
};

void __init msm_8974_init_gpiomux(void)
{
	int rc;

	rc = msm_gpiomux_init_dt();
	if (rc) {
		pr_err("%s failed %d\n", __func__, rc);
		return;
	}

/* soojung.lim@lge.com, 2013-05-23
 * To use 24MHz GP/GCC_GP clock for V2 H/W
 */
if (socinfo_get_version() >= 0x20000) {
 g_is_tlmm_spare_reg_value = 0x7;
 msm_tlmm_misc_reg_write(TLMM_SPARE_REG, 0x7);
}

#if defined (CONFIG_LGE_BROADCAST_ONESEG)
    msm_gpiomux_install(lge_1seg_blsp_configs, ARRAY_SIZE(lge_1seg_blsp_configs));
#endif  /* CONFIG_LGE_BROADCAST_ONESEG */

#if defined(CONFIG_LGE_NFC_SONY_CXD2235AGG)
	if (lge_get_board_revno() <= HW_REV_C) {
		msm_gpiomux_install(msm8974_nfc_configs_rev_c, ARRAY_SIZE(msm8974_nfc_configs_rev_c));
	} else {
		msm_gpiomux_install(msm8974_nfc_configs_rev_d, ARRAY_SIZE(msm8974_nfc_configs_rev_d));
	}
		msm_gpiomux_install(msm8974_felica_uart_blsp1_configs,
				ARRAY_SIZE(msm8974_felica_uart_blsp1_configs));
#endif

#if defined(CONFIG_KS8851) || defined(CONFIG_KS8851_MODULE)
	msm_gpiomux_install(msm_eth_configs, ARRAY_SIZE(msm_eth_configs));
#endif
	msm_gpiomux_install(msm_blsp_configs, ARRAY_SIZE(msm_blsp_configs));

#ifndef CONFIG_MACH_LGE
	msm_gpiomux_install(msm_blsp2_uart7_configs,
			 ARRAY_SIZE(msm_blsp2_uart7_configs));
#endif

#if defined(CONFIG_MACH_LGE)
#if defined(CONFIG_MAX17048_FUELGAUGE) || defined(CONFIG_MAX17050_FUELGAUGE)
#if defined(CONFIG_MACH_MSM8974_G2_DCM)
	/* [Power] junnyoung.jang@lge.com*/
	if (HW_REV_A < lge_get_board_revno()) {
		msm_gpiomux_install(msm_fuel_gauge_max17050_configs,
				ARRAY_SIZE(msm_fuel_gauge_max17050_configs));
	} else {
		msm_gpiomux_install(msm_fuel_gauge_configs,
				ARRAY_SIZE(msm_fuel_gauge_configs));
	}
#else
	/* [Power] yeonhwa.so@lge.com
	 * If MAX17048 is removed, we modify and use it*/
	if (HW_REV_A <= lge_get_board_revno()) {
		msm_gpiomux_install(msm_fuel_gauge_configs,
				ARRAY_SIZE(msm_fuel_gauge_configs));
	}
#endif
#endif
#endif
/* LGE_CHANGE_S, [WiFi][hayun.kim@lge.com], 2013-01-22, Wifi Bring Up */
#if defined (CONFIG_BCMDHD) || defined (CONFIG_BCMDHD_MODULE)
#else
	msm_gpiomux_install(wcnss_5wire_interface,
				ARRAY_SIZE(wcnss_5wire_interface));
#endif
/* LGE_CHANGE_E, [WiFi][hayun.kim@lge.com], 2013-01-22, Wifi Bring Up */

	msm_gpiomux_install(msm8974_slimbus_config,
			ARRAY_SIZE(msm8974_slimbus_config));

	msm_gpiomux_install(msm_touch_configs, ARRAY_SIZE(msm_touch_configs));

#ifndef CONFIG_LGE_IRRC
	msm_gpiomux_install(hap_lvl_shft_config,
			ARRAY_SIZE(hap_lvl_shft_config));
#endif

	msm_gpiomux_install(msm_sensor_configs, ARRAY_SIZE(msm_sensor_configs));

	msm_gpiomux_install(&sd_card_det, 1);

	if (machine_is_apq8074() && (of_board_is_liquid() || \
	    of_board_is_dragonboard()))
		msm_gpiomux_sdc3_install();

	msm_gpiomux_sdc4_install();

	msm_gpiomux_install(msm_taiko_config, ARRAY_SIZE(msm_taiko_config));

	//msm_gpiomux_install(msm_hsic_configs, ARRAY_SIZE(msm_hsic_configs));
	msm_gpiomux_install(msm_hsic_hub_configs,
				ARRAY_SIZE(msm_hsic_hub_configs));

	msm_gpiomux_install(msm_hdmi_configs, ARRAY_SIZE(msm_hdmi_configs));
	if (of_board_is_fluid())
		msm_gpiomux_install(msm_mhl_configs,
				    ARRAY_SIZE(msm_mhl_configs));
#ifndef CONFIG_MACH_LGE
	msm_gpiomux_install(msm8974_pri_auxpcm_configs,
				 ARRAY_SIZE(msm8974_pri_auxpcm_configs));
#endif
	msm_gpiomux_install_nowrite(msm_lcd_configs,
			ARRAY_SIZE(msm_lcd_configs));

	if (of_board_is_rumi())
		msm_gpiomux_install(msm_rumi_blsp_configs,
				    ARRAY_SIZE(msm_rumi_blsp_configs));

	if (socinfo_get_platform_subtype() == PLATFORM_SUBTYPE_MDM)
		msm_gpiomux_install(mdm_configs,
			ARRAY_SIZE(mdm_configs));

#ifdef CONFIG_SLIMPORT_ANX7808
		msm_gpiomux_install(slimport_configs,
					ARRAY_SIZE(slimport_configs));
#endif
#if defined(CONFIG_MACH_LGE)
//msm_gpiomux_install(msm_display_configs, ARRAY_SIZE(msm_display_configs));
	msm_gpiomux_install(msm_hall_ic_configs, ARRAY_SIZE(msm_hall_ic_configs));

	if (lge_get_board_revno() > HW_REV_A)
   	msm_gpiomux_install(headset_configs,ARRAY_SIZE(headset_configs));
#endif
#if 0 /* disable sensor GPIO setting (enable ADSP)*/
	msm_gpiomux_install(sensor_configs, ARRAY_SIZE(sensor_configs));
#endif
#if defined(CONFIG_LGE_SM100) || defined(CONFIG_TSPDRV)
       msm_gpiomux_install(vibrator_configs, ARRAY_SIZE(vibrator_configs));
#endif
/* LGE_CHANGE_S, [BT][younghyun.kwon@lge.com], 2013-01-29 */
#ifdef CONFIG_LGE_BLUETOOTH
    bluetooth_msm_gpiomux_install();
#endif /* CONFIG_LGE_BLUETOOTH */
/* LGE_CHANGE_E, [BT][younghyun.kwon@lge.com], 2013-01-29 */

	if (of_board_is_dragonboard() && machine_is_apq8074())
		msm_gpiomux_install(apq8074_dragonboard_ts_config,
			ARRAY_SIZE(apq8074_dragonboard_ts_config));
}
