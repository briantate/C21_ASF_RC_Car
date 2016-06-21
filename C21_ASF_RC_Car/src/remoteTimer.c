/*
 * remoteTimer.c
 *
 * Created: 5/25/2016 10:33:52 PM
 *  Author: btate
 */ 

#include "remoteTimer.h"
#include <asf.h>

struct tc_module tc_instance;
bool timer_flag = false;

static void tc_callback_overflow(struct tc_module *const module_inst)
{
	timer_flag = true;
	//port_pin_toggle_output_level(LED_0_PIN);
}

void configure_tc(void)
{
	struct tc_config config_tc;
	
	tc_get_config_defaults(&config_tc);
	config_tc.clock_source    = GCLK_GENERATOR_3;
	config_tc.clock_prescaler = TC_CLOCK_PRESCALER_DIV1024;
	config_tc.counter_size    = TC_COUNTER_SIZE_8BIT;
	config_tc.wave_generation = TC_WAVE_GENERATION_NORMAL_FREQ;
	config_tc.count_direction = TC_COUNT_DIRECTION_UP;
	
	tc_init(&tc_instance, TC4, &config_tc);
	tc_enable(&tc_instance);

}

void configure_tc_callbacks(void)
{

	tc_register_callback(&tc_instance, tc_callback_overflow, TC_CALLBACK_OVERFLOW);

	tc_enable_callback(&tc_instance, TC_CALLBACK_OVERFLOW);

}
