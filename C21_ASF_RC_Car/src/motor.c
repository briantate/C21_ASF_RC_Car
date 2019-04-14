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
MotorPtr createMotor(HBRIDGE_Drive_t HbridgeDrive, HBRIDGE_Enable_t HbridgeEnable)
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

void deleteMotor(MotorPtr motorInstance){
	// probably don't need to do this
}

uint8_t getMotorSpeed( MotorPtr motorInstance){
	return motorInstance->speed;
}

bool getMotorDirection(MotorPtr motorInstance){
	return motorInstance->direction;
}

void setMotorSpeed(MotorPtr motorInstance, uint8_t speed){
	motorInstance->speed = speed;
}

void setMotorDirection(MotorPtr motorInstance, bool direction){
	motorInstance->direction = direction;
}

void spinMotor(MotorPtr motorInstance)
{	
	//h-bridge callback functions
	motorInstance->HbridgeDrive(motorInstance->speed, motorInstance->direction); //drive H-bridge PWM signals
	motorInstance->HbridgeEnable(true);  //enable the h-bridge
	
}

void stopMotor(MotorPtr motorInstance)
{
	motorInstance->HbridgeEnable(false);	//disable the h-bridge
	
}
