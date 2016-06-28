/*
 * remoteControl.c
 *
 * Created: 5/23/2016 7:11:14 PM
 *  Author: brian.tate
 */ 
 #include "remoteControl.h"
 
 extern bool timer_flag;  //placeholder -- this should be set in the timer callback
 uint8_t val = 0;
 bool dir = 0;

 void remoteControl_init(void){
	delay_init();           //phy.c requires this...
	SYS_Init(); //LWMesh network stack initialization
	initAdc();
	radioInit();  //radio initialization
	configure_tc();
	configure_tc_callbacks();

	system_interrupt_enable_global();

 }

 void remoteControl_TaskHandler(void){
	 
	
 }
