/**
 * \file *********************************************************************
 *
 * \brief Common TRX Access Configuration
 *
 * Copyright (c) 2013-2015 Atmel Corporation. All rights reserved.
 *
 * \asf_license_start
 *
 * \page License
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 *
 * 3. The name of Atmel may not be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * 4. This software may only be redistributed and used in connection with an
 *    Atmel microcontroller product.
 *
 * THIS SOFTWARE IS PROVIDED BY ATMEL "AS IS" AND ANY EXPRESS OR IMPLIED
 * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT ARE
 * EXPRESSLY AND SPECIFICALLY DISCLAIMED. IN NO EVENT SHALL ATMEL BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
 * STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
 * ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 * \asf_license_stop
 */

#ifndef CONF_TRX_ACCESS_H_INCLUDED 
	#define CONF_TRX_ACCESS_H_INCLUDED

	#include <parts.h>
	#include "board.h"
	/*
	#warning \
		"Enable CONF_BOARD_AT86RFX Macro in conf_board.h for spi init routine in case of Atmel Board."
	*/

	#ifndef AT86RFX_SPI_BAUDRATE
	#define AT86RFX_SPI_BAUDRATE         (4000000)
	#endif 
	
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
	
	
	#define AT86RFX_SPI                  EXT1_SPI_MODULE
	#define AT86RFX_RST_PIN              EXT1_PIN_7
	#define AT86RFX_MISC_PIN             EXT1_PIN_12
	#define AT86RFX_IRQ_PIN              EXT1_PIN_9
	#define AT86RFX_SLP_PIN              EXT1_PIN_10
	#define AT86RFX_SPI_CS               EXT1_PIN_15
	#define AT86RFX_SPI_MOSI             EXT1_PIN_16
	#define AT86RFX_SPI_MISO             EXT1_PIN_17
	#define AT86RFX_SPI_SCK              EXT1_PIN_18
	#define AT86RFX_CSD                  EXT1_PIN_5
	#define AT86RFX_CPS                  EXT1_PIN_8

	#define AT86RFX_SPI_SERCOM_MUX_SETTING   EXT1_SPI_SERCOM_MUX_SETTING
	#define AT86RFX_SPI_SERCOM_PINMUX_PAD0   EXT1_SPI_SERCOM_PINMUX_PAD0
	#define AT86RFX_SPI_SERCOM_PINMUX_PAD1   PINMUX_UNUSED
	#define AT86RFX_SPI_SERCOM_PINMUX_PAD2   EXT1_SPI_SERCOM_PINMUX_PAD2
	#define AT86RFX_SPI_SERCOM_PINMUX_PAD3   EXT1_SPI_SERCOM_PINMUX_PAD3

	#define AT86RFX_IRQ_CHAN       EXT1_IRQ_INPUT
	#define AT86RFX_IRQ_PINMUX     EXT1_IRQ_PINMUX

	/** Enables the transceiver main interrupt. */
	#define ENABLE_TRX_IRQ()                extint_chan_enable_callback( \
			AT86RFX_IRQ_CHAN, EXTINT_CALLBACK_TYPE_DETECT)

	/** Disables the transceiver main interrupt. */
	#define DISABLE_TRX_IRQ()               extint_chan_disable_callback( \
			AT86RFX_IRQ_CHAN, EXTINT_CALLBACK_TYPE_DETECT)

	/** Clears the transceiver main interrupt. */
	#define CLEAR_TRX_IRQ()                 extint_chan_clear_detected( \
			AT86RFX_IRQ_CHAN);

	/*
	 * This macro saves the trx interrupt status and disables the trx interrupt.
	 */
	#define ENTER_TRX_REGION()   { extint_chan_disable_callback(AT86RFX_IRQ_CHAN, \
							   EXTINT_CALLBACK_TYPE_DETECT)

	/*
	 *  This macro restores the transceiver interrupt status
	 */
	#define LEAVE_TRX_REGION()   extint_chan_enable_callback(AT86RFX_IRQ_CHAN, \
			EXTINT_CALLBACK_TYPE_DETECT); \
		}

#endif /* CONF_TRX_ACCESS_H_INCLUDED */
