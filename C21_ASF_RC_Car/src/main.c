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
#include "analog.h"

int main (void)
{
	system_init();
	configure_pins();
	
	configure_console();
	puts(STRING_HEADER);
	printf("Address = %u\n\n\r", APP_ADDR);
	
	remoteControl_init();
	
	uint8_t jstkLeftHorzVal = 0;
	bool jstkLeftHorzDir = 0;
	uint8_t jstkLeftVertVal = 0;
	bool jstkLeftVertDir = 0;
	uint8_t jstkRightHorzVal = 0;
	bool jstkRightHorzDir = 0;
	uint8_t jstkRightVertVal = 0;
	bool jstkRightVertDir = 0;
	
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
	ADC_init();
	
	volatile joystickPtr LeftJoystick = Joystick_Create(ADC_ReadChannel10, ADC_ReadChannel11);
	volatile joystickPtr RightJoystick = Joystick_Create(ADC_ReadChannel9, ADC_ReadChannel8);
	MotorPtr LeftMotor	= createMotor(timer_a);
	MotorPtr RightMotor	= createMotor(timer_b);
	
	while(1)
	{
			Joystick_Measure(LeftJoystick);
			jstkLeftHorzVal = Joystick_GetHorz(LeftJoystick);		
			jstkLeftHorzDir = Joystick_GetHorzDirection(LeftJoystick);
			jstkLeftVertVal = Joystick_GetVert(LeftJoystick);
			jstkLeftVertDir = Joystick_GetVertDirection(LeftJoystick);
			Joystick_Measure(RightJoystick);
			jstkRightHorzVal = Joystick_GetHorz(RightJoystick);
			jstkRightHorzDir = Joystick_GetHorzDirection(RightJoystick);
			jstkRightVertVal = Joystick_GetVert(RightJoystick);
			jstkRightVertDir = Joystick_GetVertDirection(RightJoystick);
			printf("L H:%03i, D: %01i, V:%03i, D: %01i, R H:%03i, D: %01i, V:%03i, D: %01i\r\n",
				jstkLeftHorzVal, jstkLeftHorzDir, 
				jstkLeftVertVal, jstkLeftVertDir, 
				jstkRightHorzVal, jstkRightHorzDir, 
				jstkRightVertVal, jstkRightVertDir);
			setMotorSpeed(LeftMotor, jstkLeftHorzVal);
			setMotorSpeed(RightMotor,jstkLeftHorzVal);
			setMotorDirection(LeftMotor, jstkLeftHorzDir);
			setMotorDirection(RightMotor,jstkLeftHorzDir);
			spinMotor(LeftMotor, timer_a);		
			spinMotor(RightMotor, timer_b);	
	}

}
