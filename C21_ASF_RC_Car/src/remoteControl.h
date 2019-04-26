/*
 * remoteControl.h
 *
 * Created: 5/23/2016 7:11:45 PM
 *  Author: brian.tate
 */ 


#ifndef REMOTECONTROL_H_
#define REMOTECONTROL_H_
	//includes
	#include <stdint.h>
	#include <stdbool.h>
	#include <stddef.h>

	typedef struct RemoteControl* RcPtr_t;
//	typedef void  (*RC_RxHandler_t)(void); //callback for when data is received
	
	//prototypes
	RcPtr_t RC_Create(void); //handle for Remote Control Object
	
	//Left Joystick states
	uint8_t RC_GetLeftX(RcPtr_t RcInstance);
	uint8_t RC_GetLeftXdir(RcPtr_t RcInstance);
	uint8_t RC_GetLeftY(RcPtr_t RcInstance);
	uint8_t RC_GetLeftYdir(RcPtr_t RcInstance);
	uint8_t RC_GetLeftButton(RcPtr_t RcInstance);
	//Right Joystick states
	uint8_t RC_GetRightX(RcPtr_t RcInstance);
	uint8_t RC_GetRightXdir(RcPtr_t RcInstance);
	uint8_t RC_GetRightY(RcPtr_t RcInstance);
	uint8_t RC_GetRightYdir(RcPtr_t RcInstance);
	uint8_t RC_GetRightButton(RcPtr_t RcInstance);
	//button states
	bool    RC_getAbutton(RcPtr_t RcInstance);
	bool    RC_getBbutton(RcPtr_t RcInstance);
	
	//timeout status
	bool    RC_GetTimeout(RcPtr_t RcInstance);

	//Send payload to the RC object
	void    RC_RxData(RcPtr_t RcInstance, uint8_t *payload, uint8_t payloadSize);

#endif /* REMOTECONTROL_H_ */