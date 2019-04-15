/**
 *
 *
 * SAMC21 212B RC Car project
 * 
 * This is a personal learning project:
 * -Learn to use MiWi for remote control
 * -Learn to use object oriented design patterns and principles
 *   -using C language (not an "object oriented" language)
 *   -SOLID principles
 *     -dependency inversion 
 * 
 * 
 */

#include <asf.h>
#include "main.h"
#include "DebugConsole.h"
#include "UserIO.h"
#include "remoteControl.h"
#include "hbridge.h"
#include "motor.h"
#include "analog.h"
#include "joystick.h"
#include "config.h"

int main (void)
{
	system_init();
	configure_pins();
	
	configure_console();
	puts(STRING_HEADER);
	printf("Address = %u\n\n\r", APP_ADDR);
	
	remoteControl_init();
	
	uint8_t jstkLeftVertVal = 0;
	bool jstkLeftVertDir = 0;
	uint8_t jstkRightVertVal = 0;
	bool jstkRightVertDir = 0;
	
	ADC_init(); //initialize the ADC used for joysticks
	Hbridge1Init();
	Hbridge2Init();
	
	volatile joystickPtr LeftJoystick = Joystick_Create(ADC_ReadChannel10, ADC_ReadChannel11);
	volatile joystickPtr RightJoystick = Joystick_Create(ADC_ReadChannel9, ADC_ReadChannel8);
	MotorPtr LeftMotor	= createMotor(Hbridge1Drive, Hbridge1Enable);
	MotorPtr RightMotor	= createMotor(Hbridge2Drive, Hbridge2Enable);
	
	while(1)
	{
			Joystick_Measure(LeftJoystick);
			jstkLeftVertVal = Joystick_GetVert(LeftJoystick);
			jstkLeftVertDir = Joystick_GetVertDirection(LeftJoystick);
			Joystick_Measure(RightJoystick);
			jstkRightVertVal = Joystick_GetVert(RightJoystick);
			jstkRightVertDir = Joystick_GetVertDirection(RightJoystick);

			setMotorSpeed(LeftMotor, jstkLeftVertVal);
			setMotorSpeed(RightMotor,jstkRightVertVal);
			setMotorDirection(LeftMotor, !jstkLeftVertDir);
			setMotorDirection(RightMotor,!jstkRightVertDir);

			spinMotor(LeftMotor);		
 			spinMotor(RightMotor);	
	}
}
