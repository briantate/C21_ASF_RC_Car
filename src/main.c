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
#include "car_protocol.h"
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
#include "sysTimer.h"

/*************************************************************************/
/*                          definitions and macros                       */
/*************************************************************************/

/************************************************************************/
/*                          Prototypes                                  */
/************************************************************************/
void ReceivedDataIndication(RECEIVED_MESSAGE *ind);
static void heartbeat_timer_handler(struct SYS_Timer_t *timer);

/*************************************************************************/
/*                          local variables                              */
/*************************************************************************/

uint8_t payloadBuffer[RX_BUFFER_SIZE] = {0};
bool dataReady = 0;

extern bool rc_timeoutFlag;

volatile uint32_t counter = 0;
bool isTimeForHeartbeat = false;

static SYS_Timer_t heartbeat_timer = {
  .interval = 1000, //ms
  .mode = SYS_TIMER_PERIODIC_MODE,
  .handler = heartbeat_timer_handler
};

/*************************************************************************/
/*                          public API                                   */
/*************************************************************************/

int main (void)
{
	system_init();
	configure_pins();
	
	configure_console();
	puts(STRING_HEADER);
	printf("Address = %u\n\n\r", APP_ADDR);
	printf("CPU Frequency: %ld \r\n", system_gclk_gen_get_hz(GCLK_GENERATOR_0));

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

	SYS_TimerStart(&heartbeat_timer);
	
	//create objects
	RcPtr_t  miwiRc     = RC_Create();
	MotorPtr LeftMotor	= Motor_Create(Hbridge1Drive, Hbridge1Enable);
	MotorPtr RightMotor	= Motor_Create(Hbridge2Drive, Hbridge2Enable);
	
	while(1)
	{
			
		NetworkTasks();  //allow the network stack to process data

		if(isTimeForHeartbeat)
		{
			isTimeForHeartbeat = false;
			port_pin_toggle_output_level(LED_0_PIN);
		}

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


/*************************************************************************/
/*                          private implementations                      */
/*************************************************************************/

void ReceivedDataIndication (RECEIVED_MESSAGE *ind)
{
	dataReady = 1; //flag to indicate data is ready to parse
		
	//reset timeout timer
	RC_resetTimeout();
	car_drive_packet_t *packet = (car_drive_packet_t *)ind;
	DEBUG_OUTPUT(printf("type: %02x ",packet->header.type));
	DEBUG_OUTPUT(printf("len: %02x ",packet->header.payload_length));
	DEBUG_OUTPUT(printf("lx: %02x ",packet->left_x_speed));
	DEBUG_OUTPUT(printf("ly: %02x ",packet->left_y_speed));
	DEBUG_OUTPUT(printf("rx: %02x ",packet->right_x_speed));
	DEBUG_OUTPUT(printf("ry: %02x ",packet->right_y_speed));
	DEBUG_OUTPUT(printf("bpl: %02x\r\n",packet->polarity_buttons.reg));
	
//	DEBUG_OUTPUT(printf("data received: ")); 		
	for(uint8_t i=0; i<rxMessage.PayloadSize;i++)
	{
//		DEBUG_OUTPUT(printf("%03i ",ind->Payload[i]));
		payloadBuffer[i] = ind->Payload[i];
	}
//	DEBUG_OUTPUT(printf("\r\n"));			
}

static void heartbeat_timer_handler(struct SYS_Timer_t *timer){
  isTimeForHeartbeat = true;
}
