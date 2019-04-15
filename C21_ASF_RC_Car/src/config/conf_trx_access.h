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
	
	#include "user_board.h"
	
	#define AT86RFX_SPI                  EXT2_SPI_MODULE
	#define AT86RFX_RST_PIN              EXT2_PIN_7  //Radio 8-RSTN -- ToDo: conflicts... need to choose another pin
	#define AT86RFX_MISC_PIN             EXT2_PIN_12 //Radio EEPROM SCL - ToDo:Is this used??
	#define AT86RFX_IRQ_PIN              EXT2_PIN_9  //Radio 24-IRQ - Interrupt request line to uC
	#define AT86RFX_SLP_PIN              EXT2_PIN_10 //Radio 11-SLP_TR - Wake up interrupt to RF
	#define AT86RFX_SPI_CS               EXT2_PIN_15 //Radio 23-SEL
	#define AT86RFX_SPI_MOSI             EXT2_PIN_16 //Radio 22-MOSI
	#define AT86RFX_SPI_MISO             EXT2_PIN_17 //Radio 20-MISO
	#define AT86RFX_SPI_SCK              EXT2_PIN_18 //Radio 19-SCLK
	#define AT86RFX_CSD                  EXT2_PIN_5  //Radio NC --ToDo: what is CSD?
	#define AT86RFX_CPS                  EXT2_PIN_8  //Radio CPS U2 - FEM_SEL, disable AMP to save power
	#define AT86RFX_CLKM                 EXT2_PIN_6  //Radio 17-CLKM - ToDo: is this used?
	#define AT86RFX_DIG2                 EXT2_PIN_4  //Radio 10-DIG2 - ToDo: Is this used for anything?
	#define AT86RFX_EEPROM_SDA           EXT2_PIN_11 //Radio EEPROM - ToDo:Is this used?? 

	#define AT86RFX_SPI_SERCOM_MUX_SETTING   EXT2_SPI_SERCOM_MUX_SETTING
	#define AT86RFX_SPI_SERCOM_PINMUX_PAD0   EXT2_SPI_SERCOM_PINMUX_PAD0
	#define AT86RFX_SPI_SERCOM_PINMUX_PAD1   EXT2_SPI_SERCOM_PINMUX_PAD1
	#define AT86RFX_SPI_SERCOM_PINMUX_PAD2   EXT2_SPI_SERCOM_PINMUX_PAD2
	#define AT86RFX_SPI_SERCOM_PINMUX_PAD3   EXT2_SPI_SERCOM_PINMUX_PAD3

	#define AT86RFX_IRQ_CHAN       EXT2_IRQ_INPUT
	#define AT86RFX_IRQ_PINMUX     EXT2_IRQ_PINMUX

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
