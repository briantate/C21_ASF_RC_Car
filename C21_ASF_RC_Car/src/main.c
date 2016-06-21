/**
 *
 *
 * SAMC21 212B RC Car project
 * 
 * This project is a learning project for using LWMesh to develop an RC Car
 * 
 * 
 */

#include <asf.h>
#include "DebugConsole.h"
#include "UserIO.h"
#include "remoteControl.h"

#define STRING_HEADER "C21 212B RC Car\r\n"

int main (void)
{
	system_init();
	configure_pins();
	
	configure_console();
	puts(STRING_HEADER);
	printf("Address = %u\n\n\r", APP_ADDR);
	
	remoteControl_init();
//	JoystickPtr LeftJoystick = createJoystick(ADC_POSITIVE_INPUT_PIN10);
	
	uint8_t val = 0;
	bool dir = 0;
	
	while(1)
	{
		SYS_TaskHandler();
		//remoteControl_TaskHandler();
/*
		if (port_pin_get_input_level(BUTTON_0_PIN) == BUTTON_0_ACTIVE) {
			/ * Yes, so turn LED on. * /
			port_pin_set_output_level(LED_0_PIN, LED_0_ACTIVE);

			//read joystick
			joystick_read(LeftJoystick);
			val = getJoystickValue(LeftJoystick);
			printf("val = %u\n\r", val);
			dir = getJoystickDirection(LeftJoystick);
			printf("dir = %d\n\r", dir);
			
		} else {
		/ * No, so turn LED off. * /
		port_pin_set_output_level(LED_0_PIN, !LED_0_ACTIVE);
		}
*/
	}


}
