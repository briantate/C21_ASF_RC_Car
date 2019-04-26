/**
 *
 *
 * SAMC21 212B RC Car project
 * 
 * This is a personal learning project:
 * -Learn to use MiWi for remote control
 * -Learn to use object oriented design patterns and principles
 *   -using C language (not an "object oriented" language)
 *     -First Class Abstract Data Type (ADT to create objects)
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
//#include "joystick.h"
#include "config.h"
#include "rf_transceiver.h"
#include "network_management.h"
#include "miwi_api.h"

uint8_t rxBuffer[RX_BUFFER_SIZE] = {0};
bool dataReady = 0;

/************************************************************************/
/*                          Prototypes                                  */
/************************************************************************/
void ReceivedDataIndication(RECEIVED_MESSAGE *ind);

int main (void)
{
	system_init();
	configure_pins();
	
	configure_console();
	puts(STRING_HEADER);
	printf("Address = %u\n\n\r", APP_ADDR);

	delay_init(); //used to to initialize radio interface
	SYS_TimerInit(); //used as a symbol timer by the MiWi stack
	TransceiverConfig(); //initialize pins to the radio
	NetworkInit(NETWORK_FREEZER_OFF, NETWORK_ROLE, ReceivedDataIndication); //Network role is coordinator
	
	system_interrupt_enable_global(); 
	
// 	uint8_t jstkLeftVertVal = 0;
// 	bool jstkLeftVertDir = 0;
// 	uint8_t jstkRightVertVal = 0;
// 	bool jstkRightVertDir = 0;
	
//	ADC_init(); //initialize the ADC used for joysticks

	Hbridge1Init();
	Hbridge2Init();
	
// 	volatile joystickPtr LeftJoystick = Joystick_Create(ADC_ReadChannel10, ADC_ReadChannel11);
// 	volatile joystickPtr RightJoystick = Joystick_Create(ADC_ReadChannel9, ADC_ReadChannel8);

	//create objects
	RcPtr_t  miwiRc     = RC_Create();
	MotorPtr LeftMotor	= Motor_Create(Hbridge1Drive, Hbridge1Enable);
	MotorPtr RightMotor	= Motor_Create(Hbridge2Drive, Hbridge2Enable);
	
	while(1)
	{
// 			Joystick_Measure(LeftJoystick);
// 			jstkLeftVertVal = Joystick_GetVert(LeftJoystick);
// 			jstkLeftVertDir = Joystick_GetVertDirection(LeftJoystick);
// 			Joystick_Measure(RightJoystick);
// 			jstkRightVertVal = Joystick_GetVert(RightJoystick);
// 			jstkRightVertDir = Joystick_GetVertDirection(RightJoystick);
			
		NetworkTasks();

		if(dataReady)
		{
			dataReady = 0;
			RC_RxData(miwiRc, rxBuffer,6);
		}

		if(RC_GetTimeout(miwiRc)) //haven't received a packet so stop the car
		{
			Motor_Stop(LeftMotor);
			Motor_Stop(RightMotor);
			Motor_SetSpeed(LeftMotor, 0);
			Motor_SetSpeed(RightMotor,0);
			Motor_SetDirection(LeftMotor, 0);
			Motor_SetDirection(RightMotor,0);
		}
		else
		{
			Motor_SetSpeed(LeftMotor, RC_GetLeftY(miwiRc));
			Motor_SetSpeed(RightMotor,RC_GetRightY(miwiRc));
			Motor_SetDirection(LeftMotor, !RC_GetLeftYdir(miwiRc));
			Motor_SetDirection(RightMotor,!RC_GetRightYdir(miwiRc));
// 			Motor_Spin(LeftMotor);
//  		Motor_Spin(RightMotor);
		}

	}
}

void ReceivedDataIndication (RECEIVED_MESSAGE *ind)
{
	uint8_t startPayloadIndex = 0;
	/*******************************************************************/
	// If a packet has been received, handle the information available
	// in rxMessage.
	/*******************************************************************/
	DEBUG_OUTPUT(printf("data received: "));
	
	// Toggle LED to indicate receiving a packet.
	DEBUG_OUTPUT(port_pin_toggle_output_level(LED0));
	
	for(uint8_t i=startPayloadIndex; i<rxMessage.PayloadSize;i++)
	{
		DEBUG_OUTPUT(printf("%03i ",ind->Payload[i]));
		rxBuffer[i] = ind->Payload[i];
	}
	DEBUG_OUTPUT(printf("\r\n"));
	
	dataReady = 1;
		
}
