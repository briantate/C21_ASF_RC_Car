/*
 * motor.c
 *
 * Created: 6/13/2016 9:55:52 PM
 *  Author: btate
 */ 

#include "motor.h"

#define FORWARD 1
#define BACKWARD 0

struct Motor
{
	uint8_t speed;
	bool direction;
	HBRIDGE_Drive_t HbridgeDrive;
	HBRIDGE_Enable_t HbridgeEnable;
};

 #define MAX_MOTORS 4 //arbitrary limit
 static struct Motor MotorPool[MAX_MOTORS];
 static uint8_t numberOfMotors = 0;

//functions
MotorPtr Motor_Create(HBRIDGE_Drive_t HbridgeDrive, HBRIDGE_Enable_t HbridgeEnable)
{
	MotorPtr MotorInstance = NULL;
	if(numberOfMotors < MAX_MOTORS){
		MotorInstance = &MotorPool[numberOfMotors++];
		//initialize the object
		MotorInstance->speed = 0;
		MotorInstance->direction = FORWARD;
		MotorInstance->HbridgeDrive = HbridgeDrive;
		MotorInstance->HbridgeEnable = HbridgeEnable;
	}
	
	return MotorInstance;
}

void Motor_Delete(MotorPtr motorInstance){
	// probably don't need to do this
}

uint8_t Motor_GetSpeed( MotorPtr motorInstance){
	return motorInstance->speed;
}

bool Motor_GetDirection(MotorPtr motorInstance){
	return motorInstance->direction;
}

void Motor_SetSpeed(MotorPtr motorInstance, uint8_t speed){
	motorInstance->speed = speed;
}

void Motor_SetDirection(MotorPtr motorInstance, bool direction){
	motorInstance->direction = direction;
}

void Motor_Spin(MotorPtr motorInstance)
{	
	//h-bridge callback functions
	motorInstance->HbridgeDrive(motorInstance->speed, motorInstance->direction); //drive H-bridge PWM signals
	motorInstance->HbridgeEnable(true);  //enable the h-bridge
	
}

void Motor_Stop(MotorPtr motorInstance)
{
	motorInstance->HbridgeEnable(false);	//disable the h-bridge
	
}
