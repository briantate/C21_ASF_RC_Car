/**
 * \file
 *
 * \brief User board initialization template
 *
 */
/*
 * Support and FAQ: visit <a href="http://www.atmel.com/design-support/">Atmel Support</a>
 */

#include <asf.h>
#include <board.h>
#include <conf_board.h>
#include "conf_trx_access.h"
#include "user_board.h"

#if defined(__GNUC__)
void board_init(void) WEAK __attribute__((alias("system_board_init")));
#elif defined(__ICCARM__)
void board_init(void);
#  pragma weak board_init=system_board_init
#endif

void system_board_init(void)
{
	/* This function is meant to contain board-specific initialization code
	 * for, e.g., the I/O pins. The initialization can rely on application-
	 * specific board configuration, found in conf_board.h.
	 */
		struct port_config pin_conf;
		port_get_config_defaults(&pin_conf);

		/* Configure LEDs as outputs, turn them off */
		pin_conf.direction  = PORT_PIN_DIR_OUTPUT;
		port_pin_set_config(LED_0_PIN, &pin_conf);
		port_pin_set_output_level(LED_0_PIN, LED_0_INACTIVE);
		port_pin_set_config(DEBUG_PIN, &pin_conf);
		port_pin_set_output_level(DEBUG_PIN, DEBUG_PIN_HIGH);

		/* Set buttons as inputs */
		pin_conf.direction  = PORT_PIN_DIR_INPUT;
		pin_conf.input_pull = PORT_PIN_PULL_UP;
		port_pin_set_config(BUTTON_0_PIN, &pin_conf);
		
// 		#ifdef CONF_BOARD_AT86RFX  //handled in TransceiverConfig
// 		port_get_config_defaults(&pin_conf);
// 		pin_conf.direction  = PORT_PIN_DIR_OUTPUT;
// 		port_pin_set_config(AT86RFX_SPI_SCK, &pin_conf);
// 		port_pin_set_config(AT86RFX_SPI_MOSI, &pin_conf);
// 		port_pin_set_config(AT86RFX_SPI_CS, &pin_conf);
// 		port_pin_set_config(AT86RFX_RST_PIN, &pin_conf);
// 		port_pin_set_config(AT86RFX_SLP_PIN, &pin_conf);
// 		port_pin_set_output_level(AT86RFX_SPI_SCK, true);
// 		port_pin_set_output_level(AT86RFX_SPI_MOSI, true);
// 		port_pin_set_output_level(AT86RFX_SPI_CS, true);
// 		port_pin_set_output_level(AT86RFX_RST_PIN, true);
// 		port_pin_set_output_level(AT86RFX_SLP_PIN, true);
// 		pin_conf.direction  = PORT_PIN_DIR_INPUT;
// 		port_pin_set_config(AT86RFX_SPI_MISO, &pin_conf);
// 		#endif
}