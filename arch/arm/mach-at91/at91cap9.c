/*
 * arch/arm/mach-at91/at91cap9.c
 *
 *  Copyright (C) 2007 Stelian Pop <stelian.pop@leadtechdesign.com>
 *  Copyright (C) 2007 Lead Tech Design <www.leadtechdesign.com>
 *  Copyright (C) 2007 Atmel Corporation.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 */

#include <linux/module.h>
#include <linux/pm.h>

#include <asm/irq.h>
#include <asm/mach/arch.h>
#include <asm/mach/map.h>

#include <mach/cpu.h>
#include <mach/at91cap9.h>
#include <mach/at91_pmc.h>
#include <mach/at91_rstc.h>
#include <mach/at91_shdwc.h>

#include "soc.h"
#include "generic.h"
#include "clock.h"

/* --------------------------------------------------------------------
 *  Clocks
 * -------------------------------------------------------------------- */

/*
 * The peripheral clocks.
 */
static struct clk pioABCD_clk = {
	.name		= "pioABCD_clk",
	.pmc_mask	= 1 << AT91CAP9_ID_PIOABCD,
	.type		= CLK_TYPE_PERIPHERAL,
};
static struct clk mpb0_clk = {
	.name		= "mpb0_clk",
	.pmc_mask	= 1 << AT91CAP9_ID_MPB0,
	.type		= CLK_TYPE_PERIPHERAL,
};
static struct clk mpb1_clk = {
	.name		= "mpb1_clk",
	.pmc_mask	= 1 << AT91CAP9_ID_MPB1,
	.type		= CLK_TYPE_PERIPHERAL,
};
static struct clk mpb2_clk = {
	.name		= "mpb2_clk",
	.pmc_mask	= 1 << AT91CAP9_ID_MPB2,
	.type		= CLK_TYPE_PERIPHERAL,
};
static struct clk mpb3_clk = {
	.name		= "mpb3_clk",
	.pmc_mask	= 1 << AT91CAP9_ID_MPB3,
	.type		= CLK_TYPE_PERIPHERAL,
};
static struct clk mpb4_clk = {
	.name		= "mpb4_clk",
	.pmc_mask	= 1 << AT91CAP9_ID_MPB4,
	.type		= CLK_TYPE_PERIPHERAL,
};
static struct clk usart0_clk = {
	.name		= "usart0_clk",
	.pmc_mask	= 1 << AT91CAP9_ID_US0,
	.type		= CLK_TYPE_PERIPHERAL,
};
static struct clk usart1_clk = {
	.name		= "usart1_clk",
	.pmc_mask	= 1 << AT91CAP9_ID_US1,
	.type		= CLK_TYPE_PERIPHERAL,
};
static struct clk usart2_clk = {
	.name		= "usart2_clk",
	.pmc_mask	= 1 << AT91CAP9_ID_US2,
	.type		= CLK_TYPE_PERIPHERAL,
};
static struct clk mmc0_clk = {
	.name		= "mci0_clk",
	.pmc_mask	= 1 << AT91CAP9_ID_MCI0,
	.type		= CLK_TYPE_PERIPHERAL,
};
static struct clk mmc1_clk = {
	.name		= "mci1_clk",
	.pmc_mask	= 1 << AT91CAP9_ID_MCI1,
	.type		= CLK_TYPE_PERIPHERAL,
};
static struct clk can_clk = {
	.name		= "can_clk",
	.pmc_mask	= 1 << AT91CAP9_ID_CAN,
	.type		= CLK_TYPE_PERIPHERAL,
};
static struct clk twi_clk = {
	.name		= "twi_clk",
	.pmc_mask	= 1 << AT91CAP9_ID_TWI,
	.type		= CLK_TYPE_PERIPHERAL,
};
static struct clk spi0_clk = {
	.name		= "spi0_clk",
	.pmc_mask	= 1 << AT91CAP9_ID_SPI0,
	.type		= CLK_TYPE_PERIPHERAL,
};
static struct clk spi1_clk = {
	.name		= "spi1_clk",
	.pmc_mask	= 1 << AT91CAP9_ID_SPI1,
	.type		= CLK_TYPE_PERIPHERAL,
};
static struct clk ssc0_clk = {
	.name		= "ssc0_clk",
	.pmc_mask	= 1 << AT91CAP9_ID_SSC0,
	.type		= CLK_TYPE_PERIPHERAL,
};
static struct clk ssc1_clk = {
	.name		= "ssc1_clk",
	.pmc_mask	= 1 << AT91CAP9_ID_SSC1,
	.type		= CLK_TYPE_PERIPHERAL,
};
static struct clk ac97_clk = {
	.name		= "ac97_clk",
	.pmc_mask	= 1 << AT91CAP9_ID_AC97C,
	.type		= CLK_TYPE_PERIPHERAL,
};
static struct clk tcb_clk = {
	.name		= "tcb_clk",
	.pmc_mask	= 1 << AT91CAP9_ID_TCB,
	.type		= CLK_TYPE_PERIPHERAL,
};
static struct clk pwm_clk = {
	.name		= "pwm_clk",
	.pmc_mask	= 1 << AT91CAP9_ID_PWMC,
	.type		= CLK_TYPE_PERIPHERAL,
};
static struct clk macb_clk = {
	.name		= "macb_clk",
	.pmc_mask	= 1 << AT91CAP9_ID_EMAC,
	.type		= CLK_TYPE_PERIPHERAL,
};
static struct clk aestdes_clk = {
	.name		= "aestdes_clk",
	.pmc_mask	= 1 << AT91CAP9_ID_AESTDES,
	.type		= CLK_TYPE_PERIPHERAL,
};
static struct clk adc_clk = {
	.name		= "adc_clk",
	.pmc_mask	= 1 << AT91CAP9_ID_ADC,
	.type		= CLK_TYPE_PERIPHERAL,
};
static struct clk isi_clk = {
	.name		= "isi_clk",
	.pmc_mask	= 1 << AT91CAP9_ID_ISI,
	.type		= CLK_TYPE_PERIPHERAL,
};
static struct clk lcdc_clk = {
	.name		= "lcdc_clk",
	.pmc_mask	= 1 << AT91CAP9_ID_LCDC,
	.type		= CLK_TYPE_PERIPHERAL,
};
static struct clk dma_clk = {
	.name		= "dma_clk",
	.pmc_mask	= 1 << AT91CAP9_ID_DMA,
	.type		= CLK_TYPE_PERIPHERAL,
};
static struct clk udphs_clk = {
	.name		= "udphs_clk",
	.pmc_mask	= 1 << AT91CAP9_ID_UDPHS,
	.type		= CLK_TYPE_PERIPHERAL,
};
static struct clk ohci_clk = {
	.name		= "ohci_clk",
	.pmc_mask	= 1 << AT91CAP9_ID_UHP,
	.type		= CLK_TYPE_PERIPHERAL,
};

static struct clk *periph_clocks[] __initdata = {
	&pioABCD_clk,
	&mpb0_clk,
	&mpb1_clk,
	&mpb2_clk,
	&mpb3_clk,
	&mpb4_clk,
	&usart0_clk,
	&usart1_clk,
	&usart2_clk,
	&mmc0_clk,
	&mmc1_clk,
	&can_clk,
	&twi_clk,
	&spi0_clk,
	&spi1_clk,
	&ssc0_clk,
	&ssc1_clk,
	&ac97_clk,
	&tcb_clk,
	&pwm_clk,
	&macb_clk,
	&aestdes_clk,
	&adc_clk,
	&isi_clk,
	&lcdc_clk,
	&dma_clk,
	&udphs_clk,
	&ohci_clk,
	// irq0 .. irq1
};

static struct clk_lookup periph_clocks_lookups[] = {
	CLKDEV_CON_DEV_ID("hclk", "atmel_usba_udc", &utmi_clk),
	CLKDEV_CON_DEV_ID("pclk", "atmel_usba_udc", &udphs_clk),
	CLKDEV_CON_DEV_ID("mci_clk", "at91_mci.0", &mmc0_clk),
	CLKDEV_CON_DEV_ID("mci_clk", "at91_mci.1", &mmc1_clk),
	CLKDEV_CON_DEV_ID("spi_clk", "atmel_spi.0", &spi0_clk),
	CLKDEV_CON_DEV_ID("spi_clk", "atmel_spi.1", &spi1_clk),
	CLKDEV_CON_DEV_ID("t0_clk", "atmel_tcb.0", &tcb_clk),
	CLKDEV_CON_DEV_ID("pclk", "ssc.0", &ssc0_clk),
	CLKDEV_CON_DEV_ID("pclk", "ssc.1", &ssc1_clk),
	/* fake hclk clock */
	CLKDEV_CON_DEV_ID("hclk", "at91_ohci", &ohci_clk),
};

static struct clk_lookup usart_clocks_lookups[] = {
	CLKDEV_CON_DEV_ID("usart", "atmel_usart.0", &mck),
	CLKDEV_CON_DEV_ID("usart", "atmel_usart.1", &usart0_clk),
	CLKDEV_CON_DEV_ID("usart", "atmel_usart.2", &usart1_clk),
	CLKDEV_CON_DEV_ID("usart", "atmel_usart.3", &usart2_clk),
};

/*
 * The four programmable clocks.
 * You must configure pin multiplexing to bring these signals out.
 */
static struct clk pck0 = {
	.name		= "pck0",
	.pmc_mask	= AT91_PMC_PCK0,
	.type		= CLK_TYPE_PROGRAMMABLE,
	.id		= 0,
};
static struct clk pck1 = {
	.name		= "pck1",
	.pmc_mask	= AT91_PMC_PCK1,
	.type		= CLK_TYPE_PROGRAMMABLE,
	.id		= 1,
};
static struct clk pck2 = {
	.name		= "pck2",
	.pmc_mask	= AT91_PMC_PCK2,
	.type		= CLK_TYPE_PROGRAMMABLE,
	.id		= 2,
};
static struct clk pck3 = {
	.name		= "pck3",
	.pmc_mask	= AT91_PMC_PCK3,
	.type		= CLK_TYPE_PROGRAMMABLE,
	.id		= 3,
};

static void __init at91cap9_register_clocks(void)
{
	int i;

	for (i = 0; i < ARRAY_SIZE(periph_clocks); i++)
		clk_register(periph_clocks[i]);

	clkdev_add_table(periph_clocks_lookups,
			 ARRAY_SIZE(periph_clocks_lookups));
	clkdev_add_table(usart_clocks_lookups,
			 ARRAY_SIZE(usart_clocks_lookups));

	clk_register(&pck0);
	clk_register(&pck1);
	clk_register(&pck2);
	clk_register(&pck3);
}

static struct clk_lookup console_clock_lookup;

void __init at91cap9_set_console_clock(int id)
{
	if (id >= ARRAY_SIZE(usart_clocks_lookups))
		return;

	console_clock_lookup.con_id = "usart";
	console_clock_lookup.clk = usart_clocks_lookups[id].clk;
	clkdev_add(&console_clock_lookup);
}

/* --------------------------------------------------------------------
 *  GPIO
 * -------------------------------------------------------------------- */

static struct at91_gpio_bank at91cap9_gpio[] = {
	{
		.id		= AT91CAP9_ID_PIOABCD,
		.offset		= AT91_PIOA,
		.clock		= &pioABCD_clk,
	}, {
		.id		= AT91CAP9_ID_PIOABCD,
		.offset		= AT91_PIOB,
		.clock		= &pioABCD_clk,
	}, {
		.id		= AT91CAP9_ID_PIOABCD,
		.offset		= AT91_PIOC,
		.clock		= &pioABCD_clk,
	}, {
		.id		= AT91CAP9_ID_PIOABCD,
		.offset		= AT91_PIOD,
		.clock		= &pioABCD_clk,
	}
};

static void at91cap9_restart(char mode, const char *cmd)
{
	at91_sys_write(AT91_RSTC_CR, AT91_RSTC_KEY | AT91_RSTC_PROCRST | AT91_RSTC_PERRST);
}

static void at91cap9_poweroff(void)
{
	at91_sys_write(AT91_SHDW_CR, AT91_SHDW_KEY | AT91_SHDW_SHDW);
}


/* --------------------------------------------------------------------
 *  AT91CAP9 processor initialization
 * -------------------------------------------------------------------- */

static void __init at91cap9_map_io(void)
{
	at91_init_sram(0, AT91CAP9_SRAM_BASE, AT91CAP9_SRAM_SIZE);
}

static void __init at91cap9_initialize(void)
{
	arm_pm_restart = at91cap9_restart;
	pm_power_off = at91cap9_poweroff;
	at91_extern_irq = (1 << AT91CAP9_ID_IRQ0) | (1 << AT91CAP9_ID_IRQ1);

	/* Register GPIO subsystem */
	at91_gpio_init(at91cap9_gpio, 4);

	/* Remember the silicon revision */
	if (cpu_is_at91cap9_revB())
		system_rev = 0xB;
	else if (cpu_is_at91cap9_revC())
		system_rev = 0xC;
}

/* --------------------------------------------------------------------
 *  Interrupt initialization
 * -------------------------------------------------------------------- */

/*
 * The default interrupt priority levels (0 = lowest, 7 = highest).
 */
static unsigned int at91cap9_default_irq_priority[NR_AIC_IRQS] __initdata = {
	7,	/* Advanced Interrupt Controller (FIQ) */
	7,	/* System Peripherals */
	1,	/* Parallel IO Controller A, B, C and D */
	0,	/* MP Block Peripheral 0 */
	0,	/* MP Block Peripheral 1 */
	0,	/* MP Block Peripheral 2 */
	0,	/* MP Block Peripheral 3 */
	0,	/* MP Block Peripheral 4 */
	5,	/* USART 0 */
	5,	/* USART 1 */
	5,	/* USART 2 */
	0,	/* Multimedia Card Interface 0 */
	0,	/* Multimedia Card Interface 1 */
	3,	/* CAN */
	6,	/* Two-Wire Interface */
	5,	/* Serial Peripheral Interface 0 */
	5,	/* Serial Peripheral Interface 1 */
	4,	/* Serial Synchronous Controller 0 */
	4,	/* Serial Synchronous Controller 1 */
	5,	/* AC97 Controller */
	0,	/* Timer Counter 0, 1 and 2 */
	0,	/* Pulse Width Modulation Controller */
	3,	/* Ethernet */
	0,	/* Advanced Encryption Standard, Triple DES*/
	0,	/* Analog-to-Digital Converter */
	0,	/* Image Sensor Interface */
	3,	/* LCD Controller */
	0,	/* DMA Controller */
	2,	/* USB Device Port */
	2,	/* USB Host port */
	0,	/* Advanced Interrupt Controller (IRQ0) */
	0,	/* Advanced Interrupt Controller (IRQ1) */
};

struct at91_init_soc __initdata at91cap9_soc = {
	.map_io = at91cap9_map_io,
	.default_irq_priority = at91cap9_default_irq_priority,
	.register_clocks = at91cap9_register_clocks,
	.init = at91cap9_initialize,
};
