/*
 * joystick.c
 *
 * Created: 5/23/2016 5:41:28 PM
 *  Author: brian.tate
 */ 

 #include "joystick.h"
 #include <asf.h>
 //variables
 struct adc_module adc_instance;
 
  #define GUARD_BAND 10
  #define CENTER_VAL 128
  #define FORWARD_VAL CENTER_VAL + GUARD_BAND
  #define BACKWARD_VAL CENTER_VAL - GUARD_BAND
  #define MAX_VAL 127
  #define FORWARD true
  #define BACKWARD false
  
  //private prototypes
  void joystick_filter(JoystickPtr joystickInstance);
  
  struct Joystick{
	  enum adc_positive_input channel;
	  uint8_t raw;
	  uint8_t filtered;
	  bool direction;
  };
  
   #define MAX_JOYSTICKS 4 //arbitrary limit -- I have seen game controllers with 4 joysticks
   static struct Joystick JoystickPool[MAX_JOYSTICKS];
   static uint8_t numberOfJoysticks = 0;
  
  JoystickPtr createJoystick(enum adc_positive_input channel){
	  JoystickPtr joystick = NULL;
	  if(numberOfJoysticks < MAX_JOYSTICKS){
		  joystick = &JoystickPool[numberOfJoysticks++];
		  //initialize the object
		  joystick->channel = channel;
		  joystick->direction = FORWARD;
		  joystick->filtered = 0;
		  joystick->raw = CENTER_VAL;
	  }
	  
	  return joystick;
  }
  
  void deleteJoystick(JoystickPtr joystickInstance){
	  //to do -- shouldn't really ever need to delete a joystick...
  }
  
   uint8_t getJoystickValue( JoystickPtr joystickInstance){
	   return joystickInstance->filtered;
   }
   
   bool getJoystickDirection(JoystickPtr joystickInstance){
	   return joystickInstance->direction;
   }
   
   void initAdc(void)
    {
	    struct adc_config config_adc;
	    adc_get_config_defaults(&config_adc);
	    
	    config_adc.reference = ADC_REFERENCE_INTVCC2; //ref = VDDANA
	    config_adc.resolution = ADC_RESOLUTION_8BIT;
	    config_adc.positive_input = ADC_POSITIVE_INPUT_PIN10;

	    adc_init(&adc_instance, ADC0, &config_adc);
	    adc_enable(&adc_instance);
    }
	
	 void joystick_read(JoystickPtr joystickInstance){
		 uint16_t result;
		 adc_set_positive_input(&adc_instance, joystickInstance->channel);
		 adc_start_conversion(&adc_instance);
		 do {
			 /* Wait for conversion to be done and read out result */
		 } while (adc_read(&adc_instance, &result) == STATUS_BUSY);
		 joystickInstance->raw = (uint8_t) result;
		 
		 joystick_filter(joystickInstance);
		 
	 }
   




/************************************************************************/
/*			Private Functions                                           */
/************************************************************************/

  void joystick_filter(JoystickPtr joystickInstance){
	  if (joystickInstance->raw > FORWARD_VAL){
		  joystickInstance->filtered = joystickInstance->raw - FORWARD_VAL; 
		  joystickInstance->direction = FORWARD;
	  }
	  else if (joystickInstance->raw < BACKWARD_VAL){
		  joystickInstance->filtered = BACKWARD_VAL - joystickInstance->raw;
		  joystickInstance->direction = BACKWARD;
	  }
	  else{
		  joystickInstance->filtered = 0;
		  joystickInstance->direction = FORWARD;
	  }
	  
	  //make sure it doesn't overflow...
	  if(joystickInstance->filtered > MAX_VAL){
		  joystickInstance->filtered = MAX_VAL;
	  }
	  
	  joystickInstance->filtered = 2*joystickInstance->filtered; //multiply by 2 since we only get half the resolution
  }
 


 