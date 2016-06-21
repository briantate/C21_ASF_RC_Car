/*
 * joystick.h
 *
 * Created: 5/23/2016 5:42:01 PM
 *  Author: brian.tate
 */ 


#ifndef JOYSTICK_H_
#define JOYSTICK_H_
	
	#include <asf.h>
	
	typedef struct Joystick* JoystickPtr; //joystick struct
	
	//prototypes
	void initAdc(void); //does this belong here? This is a concretion... refactor with setter injection?
	JoystickPtr createJoystick(enum adc_positive_input channel);
	void deleteJoystick(JoystickPtr j);
	void joystick_read(JoystickPtr j);
	uint8_t getJoystickValue( JoystickPtr j);
	bool getJoystickDirection(JoystickPtr j);



#endif /* JOYSTICK_H_ */