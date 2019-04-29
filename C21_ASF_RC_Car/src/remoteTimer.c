/*
 * remoteTimer.c
 *
 * Created: 5/25/2016 10:33:52 PM
 *  Author: btate
 */ 

#include "remoteTimer.h"
#include <asf.h>

struct tc_module RC_tc_instance;
bool rc_timeoutFlag = false;

static void RC_tc_callback_overflow(struct tc_module *const module_inst)
{
	rc_timeoutFlag = true;
	port_pin_set_output_level(DEBUG_PIN, DEBUG_PIN_HIGH);
//	port_pin_toggle_output_level(DEBUG_PIN);
}

void RC_configure_tc(void)
{
	struct tc_config rc_config_tc;
	
	tc_get_config_defaults(&rc_config_tc);
	rc_config_tc.clock_source    = GCLK_GENERATOR_3;
	rc_config_tc.clock_prescaler = TC_CLOCK_PRESCALER_DIV8;
	rc_config_tc.counter_size    = TC_COUNTER_SIZE_16BIT;
//	config_tc.wave_generation = TC_WAVE_GENERATION_NORMAL_FREQ;
	rc_config_tc.count_direction = TC_COUNT_DIRECTION_UP;
	
	tc_init(&RC_tc_instance, TC1, &rc_config_tc);
	tc_enable(&RC_tc_instance);

}

void RC_configure_tc_callbacks(void)
{

	tc_register_callback(&RC_tc_instance, RC_tc_callback_overflow, TC_CALLBACK_OVERFLOW);

	tc_enable_callback(&RC_tc_instance, TC_CALLBACK_OVERFLOW);

}

void RC_resetTimeout(void)
{
	port_pin_set_output_level(DEBUG_PIN, DEBUG_PIN_LOW);
	rc_timeoutFlag = false;
	tc_set_count_value(&RC_tc_instance, 0);
}
