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
	
	JoystickPtr LeftJoystick = createJoystick(ADC_POSITIVE_INPUT_PIN10); 

	system_interrupt_enable_global();

 }

 void remoteControl_TaskHandler(void){
	 
/*
	 uint16_t result0;
	 uint16_t result1;
	 static uint8_t dataBuffer[2];  //send buffer
*/
	 

/*
	if (timer_flag){
		
		timer_flag = 0;

		//read joystick
		joystick_read(ADC_JOYSTICK0, &result0);
		joystick_read(ADC_JOYSTICK1, &result1);		 
		 
		 dataBuffer[0] = (uint8_t *) result0;   //cast result to 8b truncating the upper 8bits
		 dataBuffer[1] = (uint8_t *) result1;   //cast result to 8b truncating the upper 8bits
//		 printf("result0 = %u\r\n", dataBuffer[0]);
//		 printf("result1 = %u\r\n", dataBuffer[1]);
		 
		 //if joystick is not in the "middle range"
//		 radioSendData(dataBuffer, 2);
		 //else do nothing
	 
	}
*/
	
/*
	if (port_pin_get_input_level(BUTTON_0_PIN) == BUTTON_0_ACTIVE) {
		/ * Yes, so turn LED on. * /
		port_pin_set_output_level(LED_0_PIN, LED_0_ACTIVE);

		//read joystick
//		joystick_read(LeftJoystick);
//		printf("Left Joystick val = %u", LeftJoystick->raw);

		
		//send ADC readings wirelessly to RC car
		dataBuffer[0] = (uint8_t *) result0;   //cast result to 8b truncating the upper 8bits
		dataBuffer[1] = (uint8_t *) result1;   //cast result to 8b truncating the upper 8bits
//		 printf("result0 = %u\r\n", dataBuffer[0]);
//		 printf("result1 = %u\r\n", dataBuffer[1]);
		radioSendData(dataBuffer, 2);
		
		} else {
		/ * No, so turn LED off. * /
		port_pin_set_output_level(LED_0_PIN, !LED_0_ACTIVE);
	}
	
*/
	if (port_pin_get_input_level(BUTTON_0_PIN) == BUTTON_0_ACTIVE) {
		/* Yes, so turn LED on. */
		port_pin_set_output_level(LED_0_PIN, LED_0_ACTIVE);

		//read joystick
		joystick_read(LeftJoystick);
		val = getJoystickValue(LeftJoystick);
		printf("val = %u\n\r", val);
		dir = getJoystickDirection(LeftJoystick);
		printf("dir = %d\n\r", dir);
				
	} else {
	/* No, so turn LED off. */
	port_pin_set_output_level(LED_0_PIN, !LED_0_ACTIVE);
	}

	 
 }
