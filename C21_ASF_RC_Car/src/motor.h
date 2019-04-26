/*
 * motor.h
 *
 * Created: 6/13/2016 9:56:26 PM
 *  Author: btate
 */ 


#ifndef MOTOR_H_
#define MOTOR_H_
	
	#include <stdint.h>
	#include <stdbool.h>
	#include <stddef.h>
	
	typedef struct Motor* MotorPtr; //Motor struct
		
	//function to drive PWM
	typedef void (*HBRIDGE_Drive_t)(uint8_t dutyCycle, bool direction); // direction: 1 = forward, 0 = backward
	//function type to set enable pin
	typedef void (*HBRIDGE_Enable_t)(bool enable); //1 = on, 0 = off
	

	//prototypes	
	MotorPtr Motor_Create(HBRIDGE_Drive_t PwmDrive, HBRIDGE_Enable_t PwmEnable);
	void Motor_Delete(MotorPtr motorInstance);
	
	uint8_t Motor_GetSpeed( MotorPtr motorInstance);
	bool Motor_GetDirection(MotorPtr motorInstance);  // 1 = forward, 0 = backward
	
	void Motor_SetSpeed(MotorPtr motorInstance, uint8_t speed);
	void Motor_SetDirection(MotorPtr motorInstance, bool direction); // 1 = forward, 0 = backward
	
	void Motor_Spin(MotorPtr motorInstance);
	void Motor_Stop(MotorPtr motorInstance);

#endif /* MOTOR_H_ */