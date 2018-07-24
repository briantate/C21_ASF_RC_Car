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
#include "main.h"
#include "DebugConsole.h"
#include "UserIO.h"
#include "remoteControl.h"
#include "motor.h"

int main (void)
{
	system_init();
	configure_pins();
	
	configure_console();
	puts(STRING_HEADER);
	printf("Address = %u\n\n\r", APP_ADDR);
	
	remoteControl_init();
	
	uint8_t val_a = 0;
	bool dir_a = 0;
	timer_instance_t timer_a;
	timer_a.forward_pin = MOTOR_A_FORWARD_PIN; 
	timer_a.forward_pin_mux  = MOTOR_A_FORWARD_PIN_MUX;
	timer_a.forward_pin_channel = MOTOR_A_FORWARD_PIN_CHANNEL;
	timer_a.backward_pin = MOTOR_A_BACKWARD_PIN;
	timer_a.backward_pin_mux = MOTOR_A_BACWARD_PIN_MUX;
	timer_a.backward_pin_channel = MOTOR_A_BACKWARD_PIN_CHANNEL;
	timer_a.timer_module = MOTOR_A_PWM_MODULE;
	timer_a.enable_pin = MOTOR_A_ENABLE_PIN;
	struct tc_module tc_instance_a;
	timer_a.tc_module_instance = &tc_instance_a;
	
	uint8_t val_b = 0;
	bool dir_b = 0;
	timer_instance_t timer_b;
	timer_b.forward_pin = MOTOR_B_FORWARD_PIN;
	timer_b.forward_pin_mux  = MOTOR_B_FORWARD_PIN_MUX;
	timer_b.forward_pin_channel = MOTOR_B_FORWARD_PIN_CHANNEL;
	timer_b.backward_pin = MOTOR_B_BACKWARD_PIN;
	timer_b.backward_pin_mux = MOTOR_B_BACWARD_PIN_MUX;
	timer_b.backward_pin_channel = MOTOR_B_BACKWARD_PIN_CHANNEL;
	timer_b.timer_module = MOTOR_B_PWM_MODULE;
	timer_b.enable_pin = MOTOR_B_ENABLE_PIN;
	struct tc_module tc_instance_b;
	timer_b.tc_module_instance = &tc_instance_b;
	
	volatile JoystickPtr LeftJoystick = createJoystick(ADC_POSITIVE_INPUT_PIN10);
	MotorPtr LeftMotor	= createMotor(timer_a);
	MotorPtr RightMotor	= createMotor(timer_b);
	
	while(1)
	{
			joystick_read(LeftJoystick);
			val_a = getJoystickValue(LeftJoystick);
			setMotorSpeed(LeftMotor, val_a);
			setMotorSpeed(RightMotor,val_a);
			dir_a = getJoystickDirection(LeftJoystick);
			setMotorDirection(LeftMotor, dir_a);
			setMotorDirection(RightMotor,dir_a);
			spinMotor(LeftMotor, timer_a);		
			spinMotor(RightMotor, timer_b);	
	}

}
