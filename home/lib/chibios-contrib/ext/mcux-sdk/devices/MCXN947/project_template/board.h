/*
 * Copyright 2022 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef _BOARD_H_
#define _BOARD_H_

#include "clock_config.h"
#include "fsl_gpio.h"
/*******************************************************************************
 * Definitions
 ******************************************************************************/
/*! @brief The board name */
#define BOARD_NAME "MCX-N9XX-EVK"

/*! @brief The UART to use for debug messages. */
#define BOARD_DEBUG_UART_TYPE       kSerialPort_Uart
#define BOARD_DEBUG_UART_BASEADDR   (uint32_t) LPUART4
#define BOARD_DEBUG_UART_INSTANCE   4U
#define BOARD_DEBUG_UART_CLK_FREQ   12000000U
#define BOARD_DEBUG_UART_CLK_ATTACH kFRO12M_to_FLEXCOMM4
#define BOARD_DEBUG_UART_RST        kFC4_RST_SHIFT_RSTn
#define BOARD_DEBUG_UART_CLKSRC     kCLOCK_FlexComm4
#define BOARD_UART_IRQ_HANDLER      LP_FLEXCOMM4_IRQHandler
#define BOARD_UART_IRQ              LP_FLEXCOMM4_IRQn

#define BOARD_DEBUG_UART_TYPE_CORE1       kSerialPort_Uart
#define BOARD_DEBUG_UART_BASEADDR_CORE1   (uint32_t) USART1
#define BOARD_DEBUG_UART_INSTANCE_CORE1   1U
#define BOARD_DEBUG_UART_CLK_FREQ_CORE1   12000000U
#define BOARD_DEBUG_UART_CLK_ATTACH_CORE1 kFRO12M_to_FLEXCOMM1
#define BOARD_DEBUG_UART_RST_CORE1        kFC1_RST_SHIFT_RSTn
#define BOARD_DEBUG_UART_CLKSRC_CORE1     kCLOCK_Flexcomm1
#define BOARD_UART_IRQ_HANDLER_CORE1      FLEXCOMM1_IRQHandler
#define BOARD_UART_IRQ_CORE1              FLEXCOMM1_IRQn

#ifndef BOARD_DEBUG_UART_BAUDRATE
#define BOARD_DEBUG_UART_BAUDRATE 115200U
#endif /* BOARD_DEBUG_UART_BAUDRATE */

#ifndef BOARD_DEBUG_UART_BAUDRATE_CORE1
#define BOARD_DEBUG_UART_BAUDRATE_CORE1 115200U
#endif /* BOARD_DEBUG_UART_BAUDRATE_CORE1 */

/*! @brief The UART to use for Bluetooth M.2 interface. */
#define BOARD_BT_UART_INSTANCE 2
#define BOARD_BT_UART_BAUDRATE 3000000
#define BOARD_BT_UART_CLK_FREQ 12000000U

/*! @brief The ENET PHY address. */
#define BOARD_ENET0_PHY_ADDRESS (0x00U) /* Phy address of enet port 0. */

/*! @brief Memory ranges not usable by the ENET DMA. */
#ifndef BOARD_ENET_NON_DMA_MEMORY_ARRAY
#define BOARD_ENET_NON_DMA_MEMORY_ARRAY                                                     \
    {                                                                                       \
        {0x00000000U, 0x0007FFFFU}, {0x10000000U, 0x17FFFFFFU}, {0x80000000U, 0xDFFFFFFFU}, \
            {0x00000000U, 0x00000000U},                                                     \
    }
#endif /* BOARD_ENET_NON_DMA_MEMORY_ARRAY */

#define BOARD_ACCEL_I2C_BASEADDR   LPI2C2
#define BOARD_ACCEL_I2C_CLOCK_FREQ 12000000

#define BOARD_CODEC_I2C_BASEADDR   LPI2C2
#define BOARD_CODEC_I2C_CLOCK_FREQ 12000000
#define BOARD_CODEC_I2C_INSTANCE   2

#ifndef BOARD_LED_RED_GPIO
#define BOARD_LED_RED_GPIO GPIO3
#endif
#ifndef BOARD_LED_RED_GPIO_PIN
#define BOARD_LED_RED_GPIO_PIN 4U
#endif

#ifndef BOARD_LED_BLUE_GPIO
#define BOARD_LED_BLUE_GPIO GPIO3
#endif
#ifndef BOARD_LED_BLUE_GPIO_PIN
#define BOARD_LED_BLUE_GPIO_PIN 3U
#endif

#ifndef BOARD_LED_GREEN_GPIO
#define BOARD_LED_GREEN_GPIO GPIO3
#endif
#ifndef BOARD_LED_GREEN_GPIO_PIN
#define BOARD_LED_GREEN_GPIO_PIN 2U
#endif

#ifndef BOARD_SW2_GPIO
#define BOARD_SW2_GPIO GPIO0
#endif
#ifndef BOARD_SW2_GPIO_PIN
#define BOARD_SW2_GPIO_PIN 29U
#endif
#define BOARD_SW2_NAME        "SW2"
#define BOARD_SW2_IRQ         GPIO00_IRQn
#define BOARD_SW2_IRQ_HANDLER GPIO00_IRQHandler

#ifndef BOARD_SW3_GPIO
#define BOARD_SW3_GPIO GPIO0
#endif
#ifndef BOARD_SW3_GPIO_PIN
#define BOARD_SW3_GPIO_PIN 6U
#endif
#define BOARD_SW3_NAME        "SW3"
#define BOARD_SW3_IRQ         GPIO00_IRQn
#define BOARD_SW3_IRQ_HANDLER GPIO00_IRQHandler

#ifndef BOARD_SW4_GPIO
#define BOARD_SW4_GPIO GPIO1
#endif
#ifndef BOARD_SW4_GPIO_PIN
#define BOARD_SW4_GPIO_PIN 3U
#endif
#define BOARD_SW4_NAME        "SW4"
#define BOARD_SW4_IRQ         GPIO10_IRQn
#define BOARD_SW4_IRQ_HANDLER GPIO10_IRQHandler

/* USB PHY condfiguration */
#define BOARD_USB_PHY_D_CAL     (0x04U)
#define BOARD_USB_PHY_TXCAL45DP (0x07U)
#define BOARD_USB_PHY_TXCAL45DM (0x07U)

/* Board led color mapping */
#define LOGIC_LED_ON  1U
#define LOGIC_LED_OFF 0U

#define LED_RED_INIT(output)                                           \
    GPIO_PinWrite(BOARD_LED_RED_GPIO, BOARD_LED_RED_GPIO_PIN, output); \
    BOARD_LED_RED_GPIO->PDDR |= (1U << BOARD_LED_RED_GPIO_PIN)                         /*!< Enable target LED_RED */
#define LED_RED_ON()  GPIO_PortSet(BOARD_LED_RED_GPIO, 1U << BOARD_LED_RED_GPIO_PIN)   /*!< Turn on target LED_RED */
#define LED_RED_OFF() GPIO_PortClear(BOARD_LED_RED_GPIO, 1U << BOARD_LED_RED_GPIO_PIN) /*!< Turn off target LED_RED */
#define LED_RED_TOGGLE() \
    GPIO_PortToggle(BOARD_LED_RED_GPIO, 1U << BOARD_LED_RED_GPIO_PIN) /*!< Toggle on target LED_RED */

#define LED_BLUE_INIT(output)                                            \
    GPIO_PinWrite(BOARD_LED_BLUE_GPIO, BOARD_LED_BLUE_GPIO_PIN, output); \
    BOARD_LED_BLUE_GPIO->PDDR |= (1U << BOARD_LED_BLUE_GPIO_PIN)                       /*!< Enable target LED_BLUE */
#define LED_BLUE_ON() GPIO_PortSet(BOARD_LED_BLUE_GPIO, 1U << BOARD_LED_BLUE_GPIO_PIN) /*!< Turn on target LED_BLUE */
#define LED_BLUE_OFF() \
    GPIO_PortClear(BOARD_LED_BLUE_GPIO, 1U << BOARD_LED_BLUE_GPIO_PIN) /*!< Turn off target LED_BLUE */
#define LED_BLUE_TOGGLE() \
    GPIO_PortToggle(BOARD_LED_BLUE_GPIO, 1U << BOARD_LED_BLUE_GPIO_PIN) /*!< Toggle on target LED_BLUE */

#define LED_GREEN_INIT(output)                                             \
    GPIO_PinWrite(BOARD_LED_GREEN_GPIO, BOARD_LED_GREEN_GPIO_PIN, output); \
    BOARD_LED_GREEN_GPIO->PDDR |= (1U << BOARD_LED_GREEN_GPIO_PIN) /*!< Enable target LED_GREEN */
#define LED_GREEN_ON() \
    GPIO_PortSet(BOARD_LED_GREEN_GPIO, 1U << BOARD_LED_GREEN_GPIO_PIN) /*!< Turn on target LED_GREEN */
#define LED_GREEN_OFF() \
    GPIO_PortClear(BOARD_LED_GREEN_GPIO, 1U << BOARD_LED_GREEN_GPIO_PIN) /*!< Turn off target LED_GREEN */
#define LED_GREEN_TOGGLE() \
    GPIO_PortToggle(BOARD_LED_GREEN_GPIO, 1U << BOARD_LED_GREEN_GPIO_PIN) /*!< Toggle on target LED_GREEN */

/* Display. */
#define BOARD_LCD_DC_GPIO      GPIO
#define BOARD_LCD_DC_GPIO_PORT 1U
#define BOARD_LCD_DC_GPIO_PIN  5U

/* Serial MWM WIFI */
#define BOARD_SERIAL_MWM_PORT_CLK_FREQ CLOCK_GetFlexCommClkFreq(2)
#define BOARD_SERIAL_MWM_PORT          USART2
#define BOARD_SERIAL_MWM_PORT_IRQn     FLEXCOMM2_IRQn
#define BOARD_SERIAL_MWM_RST_WRITE(output)

/*! @brief The EMVSIM SMARTCARD PHY configuration. */
#define BOARD_SMARTCARD_MODULE                (EMVSIM0)      /*!< SMARTCARD communicational module instance */
#define BOARD_SMARTCARD_MODULE_IRQ            (EMVSIM0_IRQn) /*!< SMARTCARD communicational module IRQ handler */
#define BOARD_SMARTCARD_CLOCK_MODULE_CLK_FREQ (CLOCK_GetEmvsimClkFreq(0U))
#define BOARD_SMARTCARD_CLOCK_VALUE           (4000000U) /*!< SMARTCARD clock frequency */

#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */

/*******************************************************************************
 * API
 ******************************************************************************/

void BOARD_InitDebugConsole(void);
void BOARD_InitDebugConsole_Core1(void);
#if defined(SDK_I2C_BASED_COMPONENT_USED) && SDK_I2C_BASED_COMPONENT_USED
void BOARD_LPI2C_Init(LPI2C_Type *base, uint32_t clkSrc_Hz);
status_t BOARD_LPI2C_Send(LPI2C_Type *base,
                          uint8_t deviceAddress,
                          uint32_t subAddress,
                          uint8_t subaddressSize,
                          uint8_t *txBuff,
                          uint8_t txBuffSize);
status_t BOARD_LPI2C_Receive(LPI2C_Type *base,
                             uint8_t deviceAddress,
                             uint32_t subAddress,
                             uint8_t subaddressSize,
                             uint8_t *rxBuff,
                             uint8_t rxBuffSize);
void BOARD_Accel_I2C_Init(void);
status_t BOARD_Accel_I2C_Send(uint8_t deviceAddress, uint32_t subAddress, uint8_t subaddressSize, uint32_t txBuff);
status_t BOARD_Accel_I2C_Receive(
    uint8_t deviceAddress, uint32_t subAddress, uint8_t subaddressSize, uint8_t *rxBuff, uint8_t rxBuffSize);
void BOARD_Codec_I2C_Init(void);
status_t BOARD_Codec_I2C_Send(
    uint8_t deviceAddress, uint32_t subAddress, uint8_t subAddressSize, const uint8_t *txBuff, uint8_t txBuffSize);
status_t BOARD_Codec_I2C_Receive(
    uint8_t deviceAddress, uint32_t subAddress, uint8_t subAddressSize, uint8_t *rxBuff, uint8_t rxBuffSize);
#endif /* SDK_I2C_BASED_COMPONENT_USED */

#if defined(__cplusplus)
}
#endif /* __cplusplus */

#endif /* _BOARD_H_ */
