/*
 * hbridge.c
 *
 * Created: 4/12/2019 5:39:50 PM
 *  Author: C41175
 */ 
#include "hbridge.h"

#define FORWARD 1
#define BACKWARD 0

typedef struct{
	uint32_t forward_pin;
	uint32_t forward_pin_mux;
	uint32_t forward_pin_channel;
	uint32_t backward_pin;
	uint32_t backward_pin_mux;
	uint32_t backward_pin_channel;
 	uint32_t enable_pin;
	struct tc_module *tc_module_instance;
	Tc *timer_module;

}hbridge_instance_t;
	
hbridge_instance_t hbridge1;
hbridge_instance_t hbridge2;

struct tc_module tc_instance_a;
struct tc_module tc_instance_b;

//Private prototypes:
void hbridge_configure_enable_pin(hbridge_instance_t hbridge);
void hbridge_configure_tc(hbridge_instance_t hbridge);
void HbridgeDrive(uint8_t dutyCycle, bool direction, hbridge_instance_t hbridge);


/************************************************************************/
/*                       Public functions                               */
/************************************************************************/
void Hbridge1Init(void)
{
	hbridge1.forward_pin = MOTOR_B_FORWARD_PIN;
	hbridge1.forward_pin_mux  = MOTOR_B_FORWARD_PIN_MUX;
	hbridge1.forward_pin_channel = MOTOR_B_FORWARD_PIN_CHANNEL;
	hbridge1.backward_pin = MOTOR_B_BACKWARD_PIN;
	hbridge1.backward_pin_mux = MOTOR_B_BACWARD_PIN_MUX;
	hbridge1.backward_pin_channel = MOTOR_B_BACKWARD_PIN_CHANNEL;
	hbridge1.timer_module = MOTOR_B_PWM_MODULE;
	hbridge1.enable_pin = MOTOR_B_ENABLE_PIN;
	hbridge1.tc_module_instance = &tc_instance_b;
		
	hbridge_configure_enable_pin(hbridge1);
	hbridge_configure_tc(hbridge1);
}
//adapter for H-Bridge Drive
void Hbridge1Drive(uint8_t dutyCycle, bool direction)
{
	HbridgeDrive(dutyCycle, direction, hbridge1);
}

void Hbridge1Enable(bool enable)
{
	port_pin_set_output_level(hbridge1.enable_pin, enable);
}

void Hbridge2Init(void)
{
	hbridge2.forward_pin = MOTOR_A_FORWARD_PIN;
	hbridge2.forward_pin_mux  = MOTOR_A_FORWARD_PIN_MUX;
	hbridge2.forward_pin_channel = MOTOR_A_FORWARD_PIN_CHANNEL;
	hbridge2.backward_pin = MOTOR_A_BACKWARD_PIN;
	hbridge2.backward_pin_mux = MOTOR_A_BACWARD_PIN_MUX;
	hbridge2.backward_pin_channel = MOTOR_A_BACKWARD_PIN_CHANNEL;
	hbridge2.timer_module = MOTOR_A_PWM_MODULE;
	hbridge2.enable_pin = MOTOR_A_ENABLE_PIN;
	hbridge2.tc_module_instance = &tc_instance_a;
	
	hbridge_configure_enable_pin(hbridge2);
	hbridge_configure_tc(hbridge2);
}
//adapter for H-Bridge Drive
void Hbridge2Drive(uint8_t dutyCycle, bool direction)
{
	HbridgeDrive(dutyCycle, direction, hbridge2);
}

void Hbridge2Enable(bool enable)
{
	port_pin_set_output_level(hbridge2.enable_pin, enable);
}


/************************************************************************/
/*                      Private functions                               */
/************************************************************************/
void hbridge_configure_enable_pin(hbridge_instance_t hbridge){
	//set up the enable_pin
	struct port_config pin_conf;
	port_get_config_defaults(&pin_conf);

	// Configure LEDs as outputs, turn them off
	pin_conf.direction  = PORT_PIN_DIR_OUTPUT;
	port_pin_set_config(hbridge.enable_pin, &pin_conf);
}

void hbridge_configure_tc(hbridge_instance_t hbridge)
{
	struct tc_config config_motor_tc;
	
	tc_get_config_defaults(&config_motor_tc);
	
	config_motor_tc.counter_size    = TC_COUNTER_SIZE_8BIT;
	config_motor_tc.wave_generation = TC_WAVE_GENERATION_NORMAL_PWM;
	config_motor_tc.counter_8_bit.period = 255;
	config_motor_tc.counter_8_bit.compare_capture_channel[0] = (0);
	config_motor_tc.counter_8_bit.compare_capture_channel[1] = (0);

	config_motor_tc.pwm_channel[0].enabled = true;
	config_motor_tc.pwm_channel[0].pin_out = hbridge.forward_pin;
	config_motor_tc.pwm_channel[0].pin_mux = hbridge.forward_pin_mux;
	
	config_motor_tc.pwm_channel[1].enabled = true;
	config_motor_tc.pwm_channel[1].pin_out = hbridge.backward_pin;
	config_motor_tc.pwm_channel[1].pin_mux = hbridge.backward_pin_mux;

	tc_init(hbridge.tc_module_instance,hbridge.timer_module,&config_motor_tc);

	tc_enable(hbridge.tc_module_instance);
}

void HbridgeDrive(uint8_t dutyCycle, bool direction, hbridge_instance_t hbridge)
{
	uint8_t forward_pin,backward_pin;
	
	//set the drive signals based on direction
	if(direction == FORWARD){
		//set waveform out to be the forward pin
		forward_pin = dutyCycle;
		//		printf("forward speed %u\r\n",motorInstance->speed);
		backward_pin = LOW;
		tc_set_compare_value(hbridge.tc_module_instance, hbridge.forward_pin_channel, backward_pin);
		tc_set_compare_value(hbridge.tc_module_instance, hbridge.backward_pin_channel, forward_pin);
	}
	else{
		//set waveform out to be the backward pin
		forward_pin = LOW;
		//		printf("backward speed %u\r\n",motorInstance->speed);
		backward_pin = dutyCycle;
		tc_set_compare_value(hbridge.tc_module_instance, hbridge.backward_pin_channel, forward_pin);
		tc_set_compare_value(hbridge.tc_module_instance, hbridge.forward_pin_channel, backward_pin);
	}
}