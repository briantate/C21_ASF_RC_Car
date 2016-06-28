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
#include "motor.h"

#define STRING_HEADER "C21 212B RC Car\r\n"

//motor definitions
#define MOTOR_A_FORWARD_PIN          PIN_PB02E_TC2_WO0    //EXT2 Pin 17
#define MOTOR_A_FORWARD_PIN_MUX      MUX_PB02E_TC2_WO0
#define MOTOR_A_FORWARD_PIN_PINMUX   PINMUX_PB02E_TC2_WO0
#define MOTOR_A_FORWARD_PIN_CHANNEL  0
#define MOTOR_A_BACKWARD_PIN         PIN_PB03E_TC2_WO1    //EXT2 Pin 15
#define MOTOR_A_BACWARD_PIN_MUX      MUX_PB03E_TC2_WO1
#define MOTOR_A_BACKWARD_PIN_PINMUX  PINMUX_PB01E_TC3_WO1
#define MOTOR_A_BACKWARD_PIN_CHANNEL 1
#define MOTOR_A_PWM_MODULE TC2
#define MOTOR_A_ENABLE_PIN           PIN_PA22


int main (void)
{
	system_init();
	configure_pins();
	
	configure_console();
	puts(STRING_HEADER);
	printf("Address = %u\n\n\r", APP_ADDR);
	
	remoteControl_init();

	
	uint8_t val = 0;
	bool dir = 0;
	timer_instance_t timer_a;
	timer_a.forward_pin = MOTOR_A_FORWARD_PIN; 
	timer_a.forward_pin_mux  = MOTOR_A_FORWARD_PIN_MUX;
	timer_a.forward_pin_channel = MOTOR_A_FORWARD_PIN_CHANNEL;
	timer_a.backward_pin = MOTOR_A_BACKWARD_PIN;
	timer_a.backward_pin_mux = MOTOR_A_BACWARD_PIN_MUX;
	timer_a.backward_pin_channel = MOTOR_A_BACKWARD_PIN_CHANNEL;
	timer_a.timer_module = MOTOR_A_PWM_MODULE;
	timer_a.enable_pin = MOTOR_A_ENABLE_PIN;
	
	JoystickPtr LeftJoystick = createJoystick(ADC_POSITIVE_INPUT_PIN10);
	MotorPtr LeftMotor	= createMotor(timer_a/*timer instance*/);
	
	while(1)
	{
		SYS_TaskHandler();
		remoteControl_TaskHandler();

		if (port_pin_get_input_level(BUTTON_0_PIN) == BUTTON_0_ACTIVE) {
			/* Yes, so turn LED on. */
			port_pin_set_output_level(LED_0_PIN, LED_0_ACTIVE);

			//read joystick
			joystick_read(LeftJoystick);
			val = getJoystickValue(LeftJoystick);
			printf("val = %u\n\r", val);
			setMotorSpeed(LeftMotor, val);
			dir = getJoystickDirection(LeftJoystick);
			setMotorDirection(LeftMotor, dir);
			printf("dir = %d\n\r", dir);
//			spinMotor(LeftMotor);
			spinMotor(LeftMotor, timer_a);
			
		} else {
			/* No, so turn LED off. */
			port_pin_set_output_level(LED_0_PIN, !LED_0_ACTIVE);
		}

	}

}
