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
#include "config.h"
#include "rf_transceiver.h"
#include "network_management.h"
#include "miwi_api.h"
#include "remoteTimer.h"

uint8_t payloadBuffer[RX_BUFFER_SIZE] = {0};
bool dataReady = 0;

extern bool rc_timeoutFlag;

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
	SYS_TimerInit(); //used as a 1MHz symbol timer by the MiWi stack
	TransceiverConfig(); //initialize pins to the radio
	NetworkInit(NETWORK_FREEZER_OFF, NETWORK_ROLE, ReceivedDataIndication);
	
	//configure timeout for remote control receive
  	RC_configure_tc(); 
   	RC_configure_tc_callbacks();
	
	system_interrupt_enable_global(); 
	
	//initialize motor HBridges
	Hbridge1Init();
	Hbridge2Init();
	
	//create objects
	RcPtr_t  miwiRc     = RC_Create();
	MotorPtr LeftMotor	= Motor_Create(Hbridge1Drive, Hbridge1Enable);
	MotorPtr RightMotor	= Motor_Create(Hbridge2Drive, Hbridge2Enable);
	
	while(1)
	{
			
		NetworkTasks();  //allow the network stack to process data

		if(dataReady)
		{
			dataReady = 0;
			RC_ParsePayload(miwiRc, payloadBuffer ,6); //ToDo - make this cleaner
		}

		if(rc_timeoutFlag) //haven't received a packet so stop the car
		{
			Motor_Stop(LeftMotor);
			Motor_Stop(RightMotor);
			Motor_SetSpeed(LeftMotor, 0);
			Motor_SetSpeed(RightMotor, 0);
			Motor_SetDirection(LeftMotor, 0);
			Motor_SetDirection(RightMotor, 0);
		}
		else
		{
			Motor_SetSpeed(LeftMotor, RC_GetLeftY(miwiRc));
			Motor_SetSpeed(RightMotor,RC_GetRightY(miwiRc));
			Motor_SetDirection(LeftMotor , RC_GetLeftYdir(miwiRc));
			Motor_SetDirection(RightMotor, RC_GetRightYdir(miwiRc));
 			Motor_Spin(LeftMotor);
  			Motor_Spin(RightMotor);
		}

	}
}

void ReceivedDataIndication (RECEIVED_MESSAGE *ind)
{
	dataReady = 1; //flag to indicate data is ready to parse
		
	//reset timeout timer
	RC_resetTimeout();
	
//	DEBUG_OUTPUT(printf("data received: ")); 		
	for(uint8_t i=0; i<rxMessage.PayloadSize;i++)
	{
//		DEBUG_OUTPUT(printf("%03i ",ind->Payload[i]));
		payloadBuffer[i] = ind->Payload[i];
	}
//	DEBUG_OUTPUT(printf("\r\n"));			
}
