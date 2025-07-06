/*
 * analog.h
 *
 * Created: 4/2/2019 5:58:39 AM
 *  Author: C41175
 * 
 * Wrapper for ADC to match Joystick interface
 *
 */ 


#ifndef ANALOG_H_
#define ANALOG_H_

#include <asf.h>

void ADC_init(void);
uint8_t ADC_ReadChannel4(void);
uint8_t ADC_ReadChannel5(void);
uint8_t ADC_ReadChannel8(void);
uint8_t ADC_ReadChannel9(void);
uint8_t ADC_ReadChannel10(void);
uint8_t ADC_ReadChannel11(void);

#endif /* ANALOG_H_ */