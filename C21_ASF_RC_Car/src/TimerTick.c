/*
 * TimerTick.c
 *
 * Created: 6/5/2016 4:33:34 PM
 *  Author: btate
 */ 

#include "TimerTick.h"
#include <asf.h>

/** TC Callback function.
 */
void tc_callback_to_counter(struct tc_module *const module_inst)
{
	static uint32_t count = 0;
	count ++;
	if(count%800 == 0){
		printf("The output is triggered by TC counter\r\n");
	}

	tc_set_count_value(module_inst,TC_COUNT_VALUE);
}

/** Configures  TC function with the  driver.
 */
void configure_TimerTick(void)
{
	struct tc_config config_tc;

	tc_get_config_defaults(&config_tc);
	config_tc.counter_size    = TC_COUNTER_SIZE_16BIT;
	config_tc.counter_16_bit.value = TC_COUNT_VALUE;

	tc_init(&tc_instance, TC3, &config_tc);
	tc_enable(&tc_instance);
}

/** Registers TC callback function with the  driver.
 */
void configure_TimerTick_callbacks(void)
{
	tc_register_callback(
			&tc_instance,
			tc_callback_to_counter,
			TC_CALLBACK_OVERFLOW);
	tc_enable_callback(&tc_instance, TC_CALLBACK_OVERFLOW);
}
