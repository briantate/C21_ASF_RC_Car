/*
 * UserIO.c
 *
 * Created: 6/5/2016 4:45:10 PM
 *  Author: btate
 */ 

#include <asf.h>
#include "UserIO.h"

/*Configures PORT for LED0*/
struct port_config pin;

void configure_pins(void){
	port_get_config_defaults(&pin);
	pin.direction = PORT_PIN_DIR_OUTPUT;
	port_pin_set_config(LED_0_PIN, &pin);
	
	pin.direction = PORT_PIN_DIR_INPUT;
	port_pin_set_config(BUTTON_0_PIN, &pin);

	port_pin_set_output_level(LED_0_PIN, LED_0_INACTIVE);
}


static void update_led_state(void)
{
	bool pin_state = port_pin_get_input_level(BUTTON_0_PIN);
	if (pin_state) {
		port_pin_set_output_level(LED_0_PIN, LED_0_INACTIVE);
		} else {
		port_pin_set_output_level(LED_0_PIN, LED_0_ACTIVE);
	}
}

static void extint_callback(void)
{
	update_led_state();
}

/** Configures and registers the External Interrupt callback function with the
 *  driver.
 */
void configure_eic_callback(void)
{
	extint_register_callback(extint_callback,
			BUTTON_0_EIC_LINE,
			EXTINT_CALLBACK_TYPE_DETECT);
	extint_chan_enable_callback(BUTTON_0_EIC_LINE,
			EXTINT_CALLBACK_TYPE_DETECT);
}

/** Configures the External Interrupt Controller to detect changes in the board
 *  button state.
 */
void configure_extint(void)
{
	struct extint_chan_conf eint_chan_conf;
	extint_chan_get_config_defaults(&eint_chan_conf);

	eint_chan_conf.gpio_pin           = BUTTON_0_EIC_PIN;
	eint_chan_conf.gpio_pin_mux       = BUTTON_0_EIC_MUX;
	eint_chan_conf.detection_criteria = EXTINT_DETECT_BOTH;
	eint_chan_conf.filter_input_signal = true;
	extint_chan_set_config(BUTTON_0_EIC_LINE, &eint_chan_conf);
}
