/*
 * Copyright 2023, 2024 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

/***********************************************************************************************************************
 * This file was generated by the MCUXpresso Config Tools. Any manual edits made to this file
 * will be overwritten if the respective MCUXpresso Config Tools is used to update this file.
 **********************************************************************************************************************/

/* clang-format off */
/*
 * TEXT BELOW IS USED AS SETTING FOR TOOLS *************************************
!!GlobalInfo
product: Pins v15.0
processor: LPC865
package_id: LPC865M201JBD64
mcu_data: ksdk2_0
processor_version: 0.16.2
board: LPCXpresso860MAX
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR TOOLS ***********
 */
/* clang-format on */

#include "fsl_common.h"
#include "fsl_gpio.h"
#include "fsl_iocon.h"
#include "fsl_swm.h"
#include "pin_mux.h"

/* FUNCTION ************************************************************************************************************
 *
 * Function Name : BOARD_InitBootPins
 * Description   : Calls initialization functions.
 *
 * END ****************************************************************************************************************/
void BOARD_InitBootPins(void)
{
    BOARD_InitPins();
    BOARD_InitDEBUG_UARTPins();
}

/* clang-format off */
/*
 * TEXT BELOW IS USED AS SETTING FOR TOOLS *************************************
BOARD_InitPins:
- options: {callFromInitBoot: 'true', coreID: core0, enableClock: 'true'}
- pin_list: []
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR TOOLS ***********
 */
/* clang-format on */

/* FUNCTION ************************************************************************************************************
 *
 * Function Name : BOARD_InitPins
 * Description   : Configures pin routing and optionally pin electrical features.
 *
 * END ****************************************************************************************************************/
/* Function assigned for the Cortex-M0P */
void BOARD_InitPins(void)
{
}

/* clang-format off */
/*
 * TEXT BELOW IS USED AS SETTING FOR TOOLS *************************************
BOARD_InitLEDsPins:
- options: {callFromInitBoot: 'false', coreID: core0, enableClock: 'true'}
- pin_list:
  - {pin_num: '4', peripheral: GPIO, signal: 'PIO0, 12', pin_signal: PIO0_12, identifier: LED_RED, direction: OUTPUT, gpio_init_state: 'true', mode: inactive, invert: disabled,
    hysteresis: enabled, opendrain: enabled, smode: bypass, clkdiv: div0}
  - {pin_num: '9', peripheral: GPIO, signal: 'PIO1, 12', pin_signal: PIO1_12, direction: OUTPUT, gpio_init_state: 'true', mode: inactive, invert: disabled, hysteresis: enabled,
    opendrain: enabled, smode: bypass, clkdiv: div0}
  - {pin_num: '10', peripheral: GPIO, signal: 'PIO0, 28', pin_signal: PIO0_28/WKTCLKIN, direction: OUTPUT, gpio_init_state: 'true', mode: inactive, invert: disabled,
    hysteresis: enabled, opendrain: enabled, smode: bypass, clkdiv: div0}
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR TOOLS ***********
 */
/* clang-format on */

/* FUNCTION ************************************************************************************************************
 *
 * Function Name : BOARD_InitLEDsPins
 * Description   : Configures pin routing and optionally pin electrical features.
 *
 * END ****************************************************************************************************************/
/* Function assigned for the Cortex-M0P */
void BOARD_InitLEDsPins(void)
{
    /* Enables clock for IOCON.: enable */
    CLOCK_EnableClock(kCLOCK_Iocon);
    /* Enables the clock for the GPIO0 module */
    CLOCK_EnableClock(kCLOCK_Gpio0);
    /* Enables the clock for the GPIO1 module */
    CLOCK_EnableClock(kCLOCK_Gpio1);

    gpio_pin_config_t LED_RED_config = {
        .pinDirection = kGPIO_DigitalOutput,
        .outputLogic = 1U,
    };
    /* Initialize GPIO functionality on pin PIO0_12 (pin 4)  */
    GPIO_PinInit(BOARD_INITLEDSPINS_LED_RED_GPIO, BOARD_INITLEDSPINS_LED_RED_PORT, BOARD_INITLEDSPINS_LED_RED_PIN, &LED_RED_config);

    gpio_pin_config_t LED_BLUE_config = {
        .pinDirection = kGPIO_DigitalOutput,
        .outputLogic = 1U,
    };
    /* Initialize GPIO functionality on pin PIO0_28 (pin 10)  */
    GPIO_PinInit(BOARD_INITLEDSPINS_LED_BLUE_GPIO, BOARD_INITLEDSPINS_LED_BLUE_PORT, BOARD_INITLEDSPINS_LED_BLUE_PIN, &LED_BLUE_config);

    gpio_pin_config_t LED_GREEN_config = {
        .pinDirection = kGPIO_DigitalOutput,
        .outputLogic = 1U,
    };
    /* Initialize GPIO functionality on pin PIO1_12 (pin 9)  */
    GPIO_PinInit(BOARD_INITLEDSPINS_LED_GREEN_GPIO, BOARD_INITLEDSPINS_LED_GREEN_PORT, BOARD_INITLEDSPINS_LED_GREEN_PIN, &LED_GREEN_config);

    const uint32_t LED_RED = (/* No addition pin function */
                              IOCON_PIO_MODE_INACT |
                              /* Enable hysteresis */
                              IOCON_PIO_HYS_EN |
                              /* Input not invert */
                              IOCON_PIO_INV_DI |
                              /* Enables Open-drain function */
                              IOCON_PIO_OD_EN |
                              /* Bypass input filter */
                              IOCON_PIO_SMODE_BYPASS |
                              /* IOCONCLKDIV0 */
                              IOCON_PIO_CLKDIV0);
    /* PIO0 PIN12 (coords: 4) is configured as GPIO, PIO0, 12. */
    IOCON_PinMuxSet(IOCON, IOCON_INDEX_PIO0_12, LED_RED);

    const uint32_t LED_BLUE = (/* No addition pin function */
                               IOCON_PIO_MODE_INACT |
                               /* Enable hysteresis */
                               IOCON_PIO_HYS_EN |
                               /* Input not invert */
                               IOCON_PIO_INV_DI |
                               /* Enables Open-drain function */
                               IOCON_PIO_OD_EN |
                               /* Bypass input filter */
                               IOCON_PIO_SMODE_BYPASS |
                               /* IOCONCLKDIV0 */
                               IOCON_PIO_CLKDIV0);
    /* PIO0 PIN28 (coords: 10) is configured as GPIO, PIO0, 28. */
    IOCON_PinMuxSet(IOCON, IOCON_INDEX_PIO0_28, LED_BLUE);

    const uint32_t LED_GREEN = (/* No addition pin function */
                                IOCON_PIO_MODE_INACT |
                                /* Enable hysteresis */
                                IOCON_PIO_HYS_EN |
                                /* Input not invert */
                                IOCON_PIO_INV_DI |
                                /* Enables Open-drain function */
                                IOCON_PIO_OD_EN |
                                /* Bypass input filter */
                                IOCON_PIO_SMODE_BYPASS |
                                /* IOCONCLKDIV0 */
                                IOCON_PIO_CLKDIV0);
    /* PIO1 PIN12 (coords: 9) is configured as GPIO, PIO1, 12. */
    IOCON_PinMuxSet(IOCON, IOCON_INDEX_PIO1_12, LED_GREEN);
}

/* clang-format off */
/*
 * TEXT BELOW IS USED AS SETTING FOR TOOLS *************************************
BOARD_InitDEBUG_UARTPins:
- options: {callFromInitBoot: 'true', coreID: core0, enableClock: 'true'}
- pin_list:
  - {pin_num: '36', peripheral: USART0, signal: RXD, pin_signal: PIO1_16, mode: inactive, invert: disabled, hysteresis: enabled, opendrain: disabled, smode: bypass,
    clkdiv: div0}
  - {pin_num: '37', peripheral: USART0, signal: TXD, pin_signal: PIO1_17, mode: inactive, invert: disabled, hysteresis: enabled, opendrain: disabled, smode: bypass,
    clkdiv: div0}
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR TOOLS ***********
 */
/* clang-format on */

/* FUNCTION ************************************************************************************************************
 *
 * Function Name : BOARD_InitDEBUG_UARTPins
 * Description   : Configures pin routing and optionally pin electrical features.
 *
 * END ****************************************************************************************************************/
/* Function assigned for the Cortex-M0P */
void BOARD_InitDEBUG_UARTPins(void)
{
    /* Enables clock for IOCON.: enable */
    CLOCK_EnableClock(kCLOCK_Iocon);
    /* Enables clock for switch matrix.: enable */
    CLOCK_EnableClock(kCLOCK_Swm);

    const uint32_t DEBUG_UART_RX = (/* No addition pin function */
                                    IOCON_PIO_MODE_INACT |
                                    /* Enable hysteresis */
                                    IOCON_PIO_HYS_EN |
                                    /* Input not invert */
                                    IOCON_PIO_INV_DI |
                                    /* Disables Open-drain function */
                                    IOCON_PIO_OD_DI |
                                    /* Bypass input filter */
                                    IOCON_PIO_SMODE_BYPASS |
                                    /* IOCONCLKDIV0 */
                                    IOCON_PIO_CLKDIV0);
    /* PIO1 PIN16 (coords: 36) is configured as USART0, TXD. */
    IOCON_PinMuxSet(IOCON, IOCON_INDEX_PIO1_16, DEBUG_UART_RX);

    const uint32_t DEBUG_UART_TX = (/* No addition pin function */
                                    IOCON_PIO_MODE_INACT |
                                    /* Enable hysteresis */
                                    IOCON_PIO_HYS_EN |
                                    /* Input not invert */
                                    IOCON_PIO_INV_DI |
                                    /* Disables Open-drain function */
                                    IOCON_PIO_OD_DI |
                                    /* Bypass input filter */
                                    IOCON_PIO_SMODE_BYPASS |
                                    /* IOCONCLKDIV0 */
                                    IOCON_PIO_CLKDIV0);
    /* PIO1 PIN17 (coords: 37) is configured as USART0, TXD. */
    IOCON_PinMuxSet(IOCON, IOCON_INDEX_PIO1_17, DEBUG_UART_TX);

    /* USART0_TXD connect to P1_17 */
    SWM_SetMovablePinSelect(SWM0, kSWM_USART0_TXD, kSWM_PortPin_P1_17);

    /* USART0_RXD connect to P1_16 */
    SWM_SetMovablePinSelect(SWM0, kSWM_USART0_RXD, kSWM_PortPin_P1_16);

    /* Disable clock for switch matrix. */
    CLOCK_DisableClock(kCLOCK_Swm);
}

/* clang-format off */
/*
 * TEXT BELOW IS USED AS SETTING FOR TOOLS *************************************
BOARD_InitSWD_DEBUGPins:
- options: {callFromInitBoot: 'false', coreID: core0, enableClock: 'true'}
- pin_list:
  - {pin_num: '12', peripheral: SWD, signal: SWCLK, pin_signal: SWCLK/PIO0_3, mode: pullUp, invert: disabled, hysteresis: enabled, opendrain: disabled, smode: bypass,
    clkdiv: div0}
  - {pin_num: '14', peripheral: SWD, signal: SWDIO, pin_signal: SWDIO/PIO0_2, mode: pullUp, invert: disabled, hysteresis: enabled, opendrain: disabled, smode: bypass,
    clkdiv: div0}
  - {pin_num: '5', peripheral: SYSCON, signal: RESET, pin_signal: RESET/PIO0_5, mode: pullUp, invert: disabled, hysteresis: enabled, opendrain: disabled, smode: bypass,
    clkdiv: div0}
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR TOOLS ***********
 */
/* clang-format on */

/* FUNCTION ************************************************************************************************************
 *
 * Function Name : BOARD_InitSWD_DEBUGPins
 * Description   : Configures pin routing and optionally pin electrical features.
 *
 * END ****************************************************************************************************************/
/* Function assigned for the Cortex-M0P */
void BOARD_InitSWD_DEBUGPins(void)
{
    /* Enables clock for IOCON.: enable */
    CLOCK_EnableClock(kCLOCK_Iocon);
    /* Enables clock for switch matrix.: enable */
    CLOCK_EnableClock(kCLOCK_Swm);

    const uint32_t DEBUG_SWD_SWDIO = (/* Selects pull-up function */
                                      IOCON_PIO_MODE_PULLUP |
                                      /* Enable hysteresis */
                                      IOCON_PIO_HYS_EN |
                                      /* Input not invert */
                                      IOCON_PIO_INV_DI |
                                      /* Disables Open-drain function */
                                      IOCON_PIO_OD_DI |
                                      /* Bypass input filter */
                                      IOCON_PIO_SMODE_BYPASS |
                                      /* IOCONCLKDIV0 */
                                      IOCON_PIO_CLKDIV0);
    /* PIO0 PIN2 (coords: 14) is configured as SWD, SWDIO. */
    IOCON_PinMuxSet(IOCON, IOCON_INDEX_PIO0_2, DEBUG_SWD_SWDIO);

    const uint32_t DEBUG_SWD_SWCLK = (/* Selects pull-up function */
                                      IOCON_PIO_MODE_PULLUP |
                                      /* Enable hysteresis */
                                      IOCON_PIO_HYS_EN |
                                      /* Input not invert */
                                      IOCON_PIO_INV_DI |
                                      /* Disables Open-drain function */
                                      IOCON_PIO_OD_DI |
                                      /* Bypass input filter */
                                      IOCON_PIO_SMODE_BYPASS |
                                      /* IOCONCLKDIV0 */
                                      IOCON_PIO_CLKDIV0);
    /* PIO0 PIN3 (coords: 12) is configured as SWD, SWCLK. */
    IOCON_PinMuxSet(IOCON, IOCON_INDEX_PIO0_3, DEBUG_SWD_SWCLK);

    const uint32_t DEBUG_SWD_RESETN = (/* Selects pull-up function */
                                       IOCON_PIO_MODE_PULLUP |
                                       /* Enable hysteresis */
                                       IOCON_PIO_HYS_EN |
                                       /* Input not invert */
                                       IOCON_PIO_INV_DI |
                                       /* Disables Open-drain function */
                                       IOCON_PIO_OD_DI |
                                       /* Bypass input filter */
                                       IOCON_PIO_SMODE_BYPASS |
                                       /* IOCONCLKDIV0 */
                                       IOCON_PIO_CLKDIV0);
    /* PIO0 PIN5 (coords: 5) is configured as SYSCON, RESET. */
    IOCON_PinMuxSet(IOCON, IOCON_INDEX_PIO0_5, DEBUG_SWD_RESETN);

    /* SWCLK connect to P0_3 */
    SWM_SetFixedPinSelect(SWM0, kSWM_SWCLK, true);

    /* SWDIO connect to P0_2 */
    SWM_SetFixedPinSelect(SWM0, kSWM_SWDIO, true);

    /* RESETN connect to P0_5 */
    SWM_SetFixedPinSelect(SWM0, kSWM_RESETN, true);

    /* Disable clock for switch matrix. */
    CLOCK_DisableClock(kCLOCK_Swm);
}

/* clang-format off */
/*
 * TEXT BELOW IS USED AS SETTING FOR TOOLS *************************************
BOARD_InitBUTTONsPins:
- options: {callFromInitBoot: 'false', coreID: core0, enableClock: 'true'}
- pin_list:
  - {pin_num: '4', peripheral: GPIO, signal: 'PIO0, 12', pin_signal: PIO0_12, identifier: SW1, direction: INPUT, mode: pullUp, invert: disabled, hysteresis: enabled,
    opendrain: disabled, smode: bypass, clkdiv: div0}
  - {pin_num: '6', peripheral: GPIO, signal: 'PIO0, 4', pin_signal: PIO0_4/ADC_11, direction: INPUT, mode: pullUp, invert: disabled, hysteresis: enabled, opendrain: disabled,
    smode: bypass, clkdiv: div0}
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR TOOLS ***********
 */
/* clang-format on */

/* FUNCTION ************************************************************************************************************
 *
 * Function Name : BOARD_InitBUTTONsPins
 * Description   : Configures pin routing and optionally pin electrical features.
 *
 * END ****************************************************************************************************************/
/* Function assigned for the Cortex-M0P */
void BOARD_InitBUTTONsPins(void)
{
    /* Enables clock for IOCON.: enable */
    CLOCK_EnableClock(kCLOCK_Iocon);
    /* Enables the clock for the GPIO0 module */
    CLOCK_EnableClock(kCLOCK_Gpio0);

    gpio_pin_config_t SW2_config = {
        .pinDirection = kGPIO_DigitalInput,
        .outputLogic = 0U,
    };
    /* Initialize GPIO functionality on pin PIO0_4 (pin 6)  */
    GPIO_PinInit(BOARD_INITBUTTONSPINS_SW2_GPIO, BOARD_INITBUTTONSPINS_SW2_PORT, BOARD_INITBUTTONSPINS_SW2_PIN, &SW2_config);

    gpio_pin_config_t SW1_config = {
        .pinDirection = kGPIO_DigitalInput,
        .outputLogic = 0U,
    };
    /* Initialize GPIO functionality on pin PIO0_12 (pin 4)  */
    GPIO_PinInit(BOARD_INITBUTTONSPINS_SW1_GPIO, BOARD_INITBUTTONSPINS_SW1_PORT, BOARD_INITBUTTONSPINS_SW1_PIN, &SW1_config);

    const uint32_t SW1 = (/* Selects pull-up function */
                          IOCON_PIO_MODE_PULLUP |
                          /* Enable hysteresis */
                          IOCON_PIO_HYS_EN |
                          /* Input not invert */
                          IOCON_PIO_INV_DI |
                          /* Disables Open-drain function */
                          IOCON_PIO_OD_DI |
                          /* Bypass input filter */
                          IOCON_PIO_SMODE_BYPASS |
                          /* IOCONCLKDIV0 */
                          IOCON_PIO_CLKDIV0);
    /* PIO0 PIN12 (coords: 4) is configured as GPIO, PIO0, 12. */
    IOCON_PinMuxSet(IOCON, IOCON_INDEX_PIO0_12, SW1);

    const uint32_t SW2 = (/* Selects pull-up function */
                          IOCON_PIO_MODE_PULLUP |
                          /* Enable hysteresis */
                          IOCON_PIO_HYS_EN |
                          /* Input not invert */
                          IOCON_PIO_INV_DI |
                          /* Disables Open-drain function */
                          IOCON_PIO_OD_DI |
                          /* Bypass input filter */
                          IOCON_PIO_SMODE_BYPASS |
                          /* IOCONCLKDIV0 */
                          IOCON_PIO_CLKDIV0);
    /* PIO0 PIN4 (coords: 6) is configured as GPIO, PIO0, 4. */
    IOCON_PinMuxSet(IOCON, IOCON_INDEX_PIO0_4, SW2);

    /* Disable clock for switch matrix. */
    CLOCK_DisableClock(kCLOCK_Swm);
}
/***********************************************************************************************************************
 * EOF
 **********************************************************************************************************************/