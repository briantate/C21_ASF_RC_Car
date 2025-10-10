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
#include "debug_interface.h"
#include "UserIO.h"
#include "remoteControl.h"
#include "hbridge.h"
#include "motor.h"
#include "config.h"
#include "rf_transceiver.h"
#include "network_interface.h"
#include "miwi_api.h"
#include "remoteTimer.h"
#include "sysTimer.h"

/*************************************************************************/
/*                          definitions and macros                       */
/*************************************************************************/
#define ADDR_LENGTH 8

/************************************************************************/
/*                          Prototypes                                  */
/************************************************************************/
void ReceivedDataIndication(RECEIVED_MESSAGE *ind);
static void heartbeat_timer_handler(struct SYS_Timer_t *timer);
static void net_event_cb(const net_event_t* event, void* user_data);

/*************************************************************************/
/*                          local variables                              */
/*************************************************************************/

uint8_t payloadBuffer[RX_BUFFER_SIZE] = {0};
uint8_t send_buffer[100] = {0};
bool dataReady = 0;
static bool last_sw_state = true;

extern bool rc_timeoutFlag; //ToDo: refactor to use SW timer and reduce resource usage

volatile uint32_t counter = 0;
volatile bool isTimeForHeartbeat = false;

static SYS_Timer_t heartbeat_timer = {
  .interval = 1000, //ms
  .mode = SYS_TIMER_PERIODIC_MODE,
  .handler = heartbeat_timer_handler
};

static net_api_t* net = NULL; 

/*************************************************************************/
/*                          public API                                   */
/*************************************************************************/

int main (void)
{
	system_init();
	configure_pins();
	
	configure_console();
	puts(STRING_HEADER);
	printf("CPU Frequency: %ld \r\n", system_gclk_gen_get_hz(GCLK_GENERATOR_0));

	delay_init(); //used to to initialize radio interface
	SYS_TimerInit(); //used as a 1MHz symbol timer by the MiWi stack
	TransceiverConfig(); //initialize pins to the radio
	
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

	//initialize the network
	net = network_get_interface();

	net->init(NULL);

	//ToDo - move into state machine
	net->register_callback(NULL, net_event_cb);
  	net->up(NULL);
	
	while(1)
	{
			
		if(net != NULL){
			if(net->status != UNINITIALIZED){
				net->run_tasks();
			}
    	}

		if(isTimeForHeartbeat)
		{
			isTimeForHeartbeat = false;
			port_pin_toggle_output_level(LED_0_PIN);
		}

		bool sw_state = port_pin_get_input_level(SW0_PIN);
		if(!sw_state){
			if(last_sw_state){
				printf(".");
				//ToDo: anything needed to send to RC?
				send_buffer[0] = 'h';
				send_buffer[1] = 'e';
				send_buffer[2] = 'l';
				send_buffer[3] = 'l';
				send_buffer[4] = 'o';
				send_buffer[5] = '0';
				net->send(NULL,send_buffer,6 );
			}
		}
		last_sw_state = sw_state;


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

static void net_event_cb(const net_event_t* event, void* user_data){
  if(event->code == NWK_EVENT_CONNECTED) {
    DEBUG_OUTPUT(printf("app connected!\r\n"));
  }
  else if(event->code == NWK_EVENT_CUSTOM){
	DEBUG_OUTPUT(printf("App network created!\r\n"));
  }
  else if(event->code == NWK_EVENT_DATA_RECEIVED){
    uint8_t start_payload_index = 0;

    for(uint8_t i = 0; i < ADDR_LENGTH; i++){
        DEBUG_OUTPUT(printf("%02x",event->data.source_address[ADDR_LENGTH-1-i]));
    }
    DEBUG_OUTPUT(printf(": "));
    for (uint8_t i = start_payload_index; i < event->data.payload_size; i++) {
      DEBUG_OUTPUT(printf("%02x ", event->data.payload[i]));
    }
    DEBUG_OUTPUT(printf("\r\n"));
  }
  else if(event->code == NWK_EVENT_DISCONNECTED){
    DEBUG_OUTPUT(printf("app disconnected!\r\n"));
  }
  else if (event->code == NWK_EVENT_ERROR){
    DEBUG_OUTPUT(printf("network error!\r\n"));
  }
  else{
    DEBUG_OUTPUT(printf("unknown network event!\r\n"));
  }
}
