/*
 * remoteControl.c
 *
 * Created: 5/23/2016 7:11:14 PM
 *  Author: brian.tate
 */ 
#include "remoteControl.h"
#include "car_protocol.h"
#include "debug_interface.h"

//Needed for MiWi
// #include "rf_transceiver.h"
// #include "network_management.h"
#include <stdio.h>

#define L_XDIR_MASK 1<<0
#define L_YDIR_MASK 1<<1
#define R_XDIR_MASK 1<<2
#define R_YDIR_MASK 1<<3
#define L_BUTTON_MASK 1<<0
#define R_BUTTON_MASK 1<<1
#define A_BUTTON_MASK 1<<2
#define B_BUTTON_MASK 1<<3
 
typedef enum 
{
	SUCCESS = 0,
	FAILURE
}status_t;

typedef struct 
{
	uint8_t X;
	bool    Xdir;
	uint8_t Y;
	bool    Ydir;
	bool    button;
}joystick_t;
 
struct RemoteControl
{
//	RC_RxHandler_t RcRxHandler;
	joystick_t joystick_R;
	joystick_t joystick_L;
	bool buttonA;
	bool buttonB;
	//trigger 1
	//trigger 2
	//Dpad
	bool rxTimeout; //ToDo: add a timeout
};

#define MAX_RCS 1 //only allow 1 remote control object to minimize resource usage
static struct RemoteControl RcPool[MAX_RCS];
static uint8_t numberOfRcs = 0;

 /************************************************************************/
 /*               Public Methods                                         */
 /************************************************************************/
RcPtr_t RC_Create(void)
{
	RcPtr_t RcInstance = NULL;

	//create an object if there are sufficient resources in the pool
	if(numberOfRcs < MAX_RCS)
	{
		RcInstance = &RcPool[numberOfRcs++];
		//initialize the object
		RcInstance->joystick_L.button = false;
		RcInstance->joystick_L.X = 0;
		RcInstance->joystick_L.Xdir = false;
		RcInstance->joystick_L.Y = 0;
		RcInstance->joystick_L.Ydir = false;
		RcInstance->joystick_R.button = false;
		RcInstance->joystick_R.X = 0;
		RcInstance->joystick_R.Xdir = false;
		RcInstance->joystick_R.Y = 0;
		RcInstance->joystick_R.Ydir = false;
		RcInstance->buttonA = 0;
		RcInstance->buttonB = 0;
		RcInstance->rxTimeout = false;
	}	 
	return RcInstance;	 
}


	
//Left Joystick states
uint8_t RC_GetLeftX(RcPtr_t RcInstance)
{
	return RcInstance->joystick_L.X;
}
uint8_t RC_GetLeftXdir(RcPtr_t RcInstance)
{
	return RcInstance->joystick_L.Xdir;
}
uint8_t RC_GetLeftY(RcPtr_t RcInstance)
{
	return RcInstance->joystick_L.Y;
}
uint8_t RC_GetLeftYdir(RcPtr_t RcInstance)
{
	return RcInstance->joystick_L.Ydir;
}
uint8_t RC_GetLeftButton(RcPtr_t RcInstance)
{
	return RcInstance->joystick_L.button;
}
//Right Joystick states
uint8_t RC_GetRightX(RcPtr_t RcInstance)
{
	return RcInstance->joystick_R.X;
}
uint8_t RC_GetRightXdir(RcPtr_t RcInstance)
{
	return RcInstance->joystick_R.Xdir;
}
uint8_t RC_GetRightY(RcPtr_t RcInstance)
{
	return RcInstance->joystick_R.Y;
}
uint8_t RC_GetRightYdir(RcPtr_t RcInstance)
{
	return RcInstance->joystick_R.Ydir;
}
uint8_t RC_GetRightButton(RcPtr_t RcInstance)
{
	return RcInstance->joystick_L.button;
}
//button states
bool    RC_getAbutton(RcPtr_t RcInstance)
{
	return RcInstance->buttonA;
}

bool    RC_getBbutton(RcPtr_t RcInstance)
{
	return RcInstance->buttonB;
}

bool    RC_GetTimeout(RcPtr_t RcInstance)
{
	return RcInstance->rxTimeout;
}

void    RC_ParsePayload(RcPtr_t RcInstance, uint8_t *payload, uint8_t payloadSize)
{
	//Make sure that payload is not overwritten during this process
	car_drive_packet_t *drive_packet = (car_drive_packet_t *)payload;
	if(drive_packet->header.type == CMD_DRIVE)
	{
		RcInstance->joystick_L.X      = drive_packet->left_x_speed;
		RcInstance->joystick_L.Y      = drive_packet->left_y_speed;
		RcInstance->joystick_R.X      = drive_packet->right_x_speed;
		RcInstance->joystick_R.Y      = drive_packet->right_y_speed;
		RcInstance->joystick_L.Xdir   = drive_packet->polarity_buttons.bits.l_x_direction;
		RcInstance->joystick_L.Ydir   = drive_packet->polarity_buttons.bits.l_y_direction;
		RcInstance->joystick_R.Xdir   = drive_packet->polarity_buttons.bits.r_x_direction;
		RcInstance->joystick_R.Ydir   = !drive_packet->polarity_buttons.bits.r_y_direction; //invert due to motors facing a different direction
		RcInstance->joystick_L.button = drive_packet->polarity_buttons.bits.l_button;
		RcInstance->joystick_R.button = drive_packet->polarity_buttons.bits.r_button;
		RcInstance->buttonA           = 0;
		RcInstance->buttonB           = 0;
	}
}
