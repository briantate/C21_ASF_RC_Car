/*
 * motor.c
 *
 * Created: 6/13/2016 9:55:52 PM
 *  Author: btate
 */ 

#include "motor.h"
#include <asf.h>



struct Motor{
	/*Timer instance*/
	uint8_t speed;
	direction_t direction;
	};

 #define MAX_MOTORS 4 //arbitrary limit
 static struct Motor MotorPool[MAX_MOTORS];
 static uint8_t numberOfMotors = 0;
 struct tc_module tc_motor_a_instance;

//private prototypes
void configure_motor_tc(timer_instance_t timer);
void configure_motor_enable(timer_instance_t timer);
void initPWM(timer_instance_t timer); //does this belong here? This is a concretion... refactor with setter injection?


//functions
void configure_motor_enable(timer_instance_t timer){
	//set up the enable_pin
	//timer.enable_pin;
}

void configure_motor_tc(timer_instance_t timer)
{
	struct tc_config config_motor_tc;
	
	tc_get_config_defaults(&config_motor_tc);
	
	config_motor_tc.counter_size    = TC_COUNTER_SIZE_8BIT;
	config_motor_tc.wave_generation = TC_WAVE_GENERATION_NORMAL_PWM;
//	config_motor_a_tc.counter_16_bit.compare_capture_channel[0] = (0xFFFF / 4);	
	config_motor_tc.counter_8_bit.period = 255;
	config_motor_tc.counter_8_bit.compare_capture_channel[0] = (0); //start with PWM off
	config_motor_tc.counter_8_bit.compare_capture_channel[1] = (0); //start with PWM off

	config_motor_tc.pwm_channel[0].enabled = true;
	config_motor_tc.pwm_channel[0].pin_out = timer.forward_pin;  //MOTOR_A_FORWARD_PIN;
	config_motor_tc.pwm_channel[0].pin_mux = timer.forward_pin_mux; //MOTOR_A_FORWARD_PIN_MUX;
	
	config_motor_tc.pwm_channel[1].enabled = true;
	config_motor_tc.pwm_channel[1].pin_out = timer.backward_pin;//MOTOR_A_BACKWARD_PIN;
	config_motor_tc.pwm_channel[1].pin_mux = timer.backward_pin_mux;//MOTOR_A_BACWARD_PIN_MUX;

	tc_init(&tc_motor_a_instance, /*MOTOR_A_PWM_MODULE*/timer.timer_module, &config_motor_tc);

	tc_enable(&tc_motor_a_instance);
}

void initPWM(timer_instance_t timer){
	configure_motor_enable(timer);
	configure_motor_tc(timer);	
}

MotorPtr createMotor(timer_instance_t timer){
	MotorPtr MotorInstance = NULL;
	if(numberOfMotors < MAX_MOTORS){
		MotorInstance = &MotorPool[numberOfMotors++];
		//initialize the object
		MotorInstance->speed = 0;
		MotorInstance->direction = FORWARD;
	}
	
	initPWM((timer_instance_t)timer);
	
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

void setMotorDirection(MotorPtr motorInstance, direction_t direction){
	motorInstance->direction = direction;
}

void spinMotor(MotorPtr motorInstance, timer_instance_t timer){
	
	uint8_t forward_pin,backward_pin;
	
	//set the drive signals based on direction
	if(motorInstance->direction == FORWARD){
		//set waveform out to be the forward pin
		forward_pin = motorInstance->speed;
//		forward_pin = 50;
		backward_pin = LOW;
		tc_set_compare_value(&tc_motor_a_instance, timer.forward_pin_channel/*MOTOR_A_FORWARD_PIN_CHANNEL*/, backward_pin);
		tc_set_compare_value(&tc_motor_a_instance, timer.backward_pin_channel/*MOTOR_A_BACKWARD_PIN_CHANNEL*/, forward_pin);
	}
	else{
		//set waveform out to be the backward pin
		forward_pin = LOW;
		backward_pin = motorInstance->speed;
//		backward_pin = 50;
		tc_set_compare_value(&tc_motor_a_instance, timer.backward_pin_channel/*MOTOR_A_BACKWARD_PIN_CHANNEL*/, forward_pin);
		tc_set_compare_value(&tc_motor_a_instance, timer.forward_pin_channel/*MOTOR_A_FORWARD_PIN_CHANNEL*/, backward_pin);
	}
	
	//set Enable Pin
	
	//drive PWM

	
}
