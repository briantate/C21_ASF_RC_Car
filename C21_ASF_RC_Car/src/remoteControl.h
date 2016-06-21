/*
 * remoteControl.h
 *
 * Created: 5/23/2016 7:11:45 PM
 *  Author: brian.tate
 */ 


#ifndef REMOTECONTROL_H_
#define REMOTECONTROL_H_
	//includes
	#include <asf.h>
	#include "radio.h"
	#include "joystick.h"
	#include "DebugConsole.h"
	#include "sys.h"
	#include "remoteTimer.h"

	//prototypes
	void remoteControl_init(void);
	void remoteControl_TaskHandler(void);



#endif /* REMOTECONTROL_H_ */