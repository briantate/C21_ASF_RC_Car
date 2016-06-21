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
  #define FORWARD true
  #define BACKWARD false
  
  //private prototypes
//  void joystick_read(JoystickPtr j);
  void joystick_filter(JoystickPtr j);
  
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
  
  void deleteJoystick(JoystickPtr j){
	  //to do -- shouldn't really ever need to delete a joystick...
  }
  
   uint8_t getJoystickValue( JoystickPtr j){
	   return j->filtered;
   }
   
   bool getJoystickDirection(JoystickPtr j){
	   return j->direction;
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
	
	 void joystick_read(JoystickPtr j){
		 uint16_t result;
		 adc_set_positive_input(&adc_instance, j->channel);
		 adc_start_conversion(&adc_instance);
		 do {
			 /* Wait for conversion to be done and read out result */
		 } while (adc_read(&adc_instance, &result) == STATUS_BUSY);
		 j->raw = (uint8_t) result;
		 
		 joystick_filter(j);
		 
	 }
   




/************************************************************************/
/*			Private Functions                                           */
/************************************************************************/

  void joystick_filter(JoystickPtr j){
	  if (j->raw > FORWARD_VAL){
		  j->filtered = j->raw - FORWARD_VAL;
		  j->direction = FORWARD;
	  }
	  else if (j->raw < BACKWARD_VAL){
		  j->filtered = BACKWARD_VAL - j->raw;
		  j->direction = BACKWARD;
	  }
	  else{
		  j->filtered = 0;
		  j->direction = FORWARD;
	  }
  }
 


 