/*
 * motor.h
 *
 * Created: 6/13/2016 9:56:26 PM
 *  Author: btate
 */ 


#ifndef MOTOR_H_
#define MOTOR_H_
	
	#include <asf.h>

	
	typedef struct{
		uint32_t forward_pin;
		uint32_t forward_pin_mux;
		uint32_t forward_pin_channel;
		uint32_t backward_pin;
		uint32_t backward_pin_mux;
		uint32_t backward_pin_channel;
		uint32_t enable_pin;
//		uint32_t timer_module;
		struct tc_module *tc_module_instance;
		Tc *timer_module;
		
		}timer_instance_t;

	typedef struct Motor* MotorPtr; //Motor struct
	
	typedef enum{
		BACKWARD,
		FORWARD
	}direction_t;

	//prototypes
	
	MotorPtr createMotor(timer_instance_t timer);
	void deleteMotor(MotorPtr motorInstance);
	
	uint8_t getMotorSpeed( MotorPtr motorInstance);
	bool getMotorDirection(MotorPtr motorInstance);
	
	void setMotorSpeed(MotorPtr motorInstance, uint8_t speed);
	void setMotorDirection(MotorPtr motorInstance, direction_t direction);
	
	void spinMotor(MotorPtr motorInstance, timer_instance_t timer);

#endif /* MOTOR_H_ */