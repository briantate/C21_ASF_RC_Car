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
