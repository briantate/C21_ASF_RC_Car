/**
 * \file
 *
 * \brief User board definition template
 *
 */

 /* This file is intended to contain definitions and configuration details for
 * features and devices that are available on the board, e.g., frequency and
 * startup time for an external crystal, external memory devices, LED and USART
 * pins.
 */
/*
 * Support and FAQ: visit <a href="http://www.atmel.com/design-support/">Atmel Support</a>
 */

#ifndef USER_BOARD_H
#define USER_BOARD_H

#include <conf_board.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \ingroup group_common_boards
 * \defgroup user_board_group User board
 *
 * @{
 */

void system_board_init(void);

/** Name string macro */
#define BOARD_NAME                "USER_BOARD"

#define DEBUG_PIN      PIN_PB30
#define DEBUG_PIN_HIGH true
#define DEBUG_PIN_LOW  false

#define EDBG_CDC_MODULE              SERCOM4
#define EDBG_CDC_SERCOM_MUX_SETTING  USART_RX_3_TX_2_XCK_3
#define EDBG_CDC_SERCOM_PINMUX_PAD0  PINMUX_UNUSED
#define EDBG_CDC_SERCOM_PINMUX_PAD1  PINMUX_UNUSED
#define EDBG_CDC_SERCOM_PINMUX_PAD2  PINMUX_PB10D_SERCOM4_PAD2
#define EDBG_CDC_SERCOM_PINMUX_PAD3  PINMUX_PB11D_SERCOM4_PAD3
#define EDBG_CDC_SERCOM_DMAC_ID_TX   SERCOM4_DMAC_ID_TX
#define EDBG_CDC_SERCOM_DMAC_ID_RX   SERCOM4_DMAC_ID_RX
#define EDBG_CDC_SERCOM_BAUDRATE 115200

#define LED_0_NAME                "LED0 (yellow)"
#define LED_0_PIN                 LED0_PIN
#define LED_0_ACTIVE              LED0_ACTIVE
#define LED_0_INACTIVE            LED0_INACTIVE
#define LED0_GPIO                 LED0_PIN
#define LED0                      LED0_PIN

#define LED0_PIN                  PIN_PA15
#define LED0_ACTIVE               false
#define LED0_INACTIVE             !LED0_ACTIVE

#define BUTTON_0_NAME             "SW0"
#define BUTTON_0_PIN              SW0_PIN
#define BUTTON_0_ACTIVE           SW0_ACTIVE
#define BUTTON_0_INACTIVE         SW0_INACTIVE
#define BUTTON_0_EIC_PIN          SW0_EIC_PIN
#define BUTTON_0_EIC_MUX          SW0_EIC_MUX
#define BUTTON_0_EIC_PINMUX       SW0_EIC_PINMUX
#define BUTTON_0_EIC_LINE         SW0_EIC_LINE

#define SW0_PIN                   PIN_PA28
#define SW0_ACTIVE                false
#define SW0_INACTIVE              !SW0_ACTIVE
#define SW0_EIC_PIN               PIN_PA28A_EIC_EXTINT8
#define SW0_EIC_MUX               MUX_PA28A_EIC_EXTINT8
#define SW0_EIC_PINMUX            PINMUX_PA28A_EIC_EXTINT8
#define SW0_EIC_LINE              8

#define EXT1_PIN_3                PIN_PB09
#define EXT1_PIN_4                PIN_PB08
#define EXT1_PIN_5                PIN_PA20
#define EXT1_PIN_6                PIN_PA21
#define EXT1_PIN_7                PIN_PB12
#define EXT1_PIN_8                PIN_PB13
#define EXT1_PIN_9                PIN_PB14
#define EXT1_PIN_10               PIN_PB15
#define EXT1_PIN_11               PIN_PA12
#define EXT1_PIN_12               PIN_PA13
#define EXT1_PIN_13               PIN_PA23
#define EXT1_PIN_14               PIN_PA22
#define EXT1_PIN_15               PIN_PA17
#define EXT1_PIN_16               PIN_PA18
#define EXT1_PIN_17               PIN_PA16
#define EXT1_PIN_18               PIN_PA19

#define EXT1_SPI_MODULE              SERCOM1
#define EXT1_SPI_SERCOM_MUX_SETTING  SPI_SIGNAL_MUX_SETTING_E
#define EXT1_SPI_SERCOM_PINMUX_PAD0  PINMUX_PA16C_SERCOM1_PAD0
#define EXT1_SPI_SERCOM_PINMUX_PAD1  PINMUX_PA17C_SERCOM1_PAD1
#define EXT1_SPI_SERCOM_PINMUX_PAD2  PINMUX_PA18C_SERCOM1_PAD2
#define EXT1_SPI_SERCOM_PINMUX_PAD3  PINMUX_PA19C_SERCOM1_PAD3
#define EXT1_SPI_SERCOM_DMAC_ID_TX   SERCOM1_DMAC_ID_TX
#define EXT1_SPI_SERCOM_DMAC_ID_RX   SERCOM1_DMAC_ID_RX

#define EXT1_IRQ_MODULE           EIC
#define EXT1_IRQ_INPUT            14
#define EXT1_IRQ_PIN              PIN_PB14A_EIC_EXTINT14
#define EXT1_IRQ_MUX              MUX_PB14A_EIC_EXTINT14
#define EXT1_IRQ_PINMUX           PINMUX_PB14A_EIC_EXTINT14

#define EXT2_PIN_3                PIN_PA08  //Radio RSTN
#define EXT2_PIN_4                PIN_PA09
#define EXT2_PIN_5                PIN_PA10
#define EXT2_PIN_6                PIN_PA11
#define EXT2_PIN_7                PIN_PB30
#define EXT2_PIN_8                PIN_PB31
#define EXT2_PIN_9                PIN_PB16  //Radio IRQ
#define EXT2_PIN_10               PIN_PB17  //Radio SLP_TR
#define EXT2_PIN_11               PIN_PA12
#define EXT2_PIN_12               PIN_PA13
#define EXT2_PIN_13               PIN_PA23
#define EXT2_PIN_14               PIN_PA22
#define EXT2_PIN_15               PIN_PB03  //Radio SPI SEL
#define EXT2_PIN_16               PIN_PB00  //Radio SPI MOSI
#define EXT2_PIN_17               PIN_PB02  //Radio SPI MISO
#define EXT2_PIN_18               PIN_PB01  //Radio SPI CLK

#define EXT2_PIN_ADC_0            EXT2_PIN_3
#define EXT2_PIN_ADC_1            EXT2_PIN_4
#define EXT2_PIN_GPIO_0           EXT2_PIN_5
#define EXT2_PIN_GPIO_1           EXT2_PIN_6
#define EXT2_PIN_PWM_0            EXT2_PIN_7
#define EXT2_PIN_PWM_1            EXT2_PIN_8
#define EXT2_PIN_IRQ              EXT2_PIN_9
#define EXT2_PIN_I2C_SDA          EXT2_PIN_11
#define EXT2_PIN_I2C_SCL          EXT2_PIN_12
#define EXT2_PIN_UART_RX          EXT2_PIN_13
#define EXT2_PIN_UART_TX          EXT2_PIN_14
#define EXT2_PIN_SPI_SS_1         EXT2_PIN_10
#define EXT2_PIN_SPI_SS_0         EXT2_PIN_15
#define EXT2_PIN_SPI_MOSI         EXT2_PIN_16
#define EXT2_PIN_SPI_MISO         EXT2_PIN_17
#define EXT2_PIN_SPI_SCK          EXT2_PIN_18

#define EXT2_IRQ_MODULE           EIC
#define EXT2_IRQ_INPUT            16
#define EXT2_IRQ_PIN              PIN_PB16A_EIC_EXTINT0
#define EXT2_IRQ_MUX              MUX_PB16A_EIC_EXTINT0
#define EXT2_IRQ_PINMUX           PINMUX_PB16A_EIC_EXTINT0

#define EXT2_SPI_MODULE              SERCOM5
#define EXT2_SPI_SERCOM_MUX_SETTING  SPI_SIGNAL_MUX_SETTING_E
#define EXT2_SPI_SERCOM_PINMUX_PAD0  PINMUX_PB02D_SERCOM5_PAD0
#define EXT2_SPI_SERCOM_PINMUX_PAD1  PINMUX_UNUSED
#define EXT2_SPI_SERCOM_PINMUX_PAD2  PINMUX_PB00D_SERCOM5_PAD2
#define EXT2_SPI_SERCOM_PINMUX_PAD3  PINMUX_PB01D_SERCOM5_PAD3
#define EXT2_SPI_SERCOM_DMAC_ID_TX   SERCOM5_DMAC_ID_TX
#define EXT2_SPI_SERCOM_DMAC_ID_RX   SERCOM5_DMAC_ID_RX

/** @} */

#ifdef __cplusplus
}
#endif

#endif // USER_BOARD_H
