/*
 * TimerTick.h
 *
 * Created: 6/5/2016 4:33:54 PM
 *  Author: btate
 */ 


#ifndef TIMERTICK_H_
#define TIMERTICK_H_


#define TC_COUNT_VALUE 55535

struct tc_module tc_instance;


//prototypes
void tc_callback_to_counter(struct tc_module *const module_inst);
void configure_TimerTick(void);
void configure_TimerTick_callbacks(void);

#endif /* TIMERTICK_H_ */