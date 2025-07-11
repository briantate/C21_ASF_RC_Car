/*
 * analog.c
 *
 * Created: 4/2/2019 5:58:19 AM
 *  Author: Brian Tate
 */ 

#include "analog.h"
#include <asf.h>

//variables
struct adc_module adc_instance;

 void ADC_init(void)
 {
	 struct adc_config config_adc;
	 adc_get_config_defaults(&config_adc);
	 
	 config_adc.reference = ADC_REFERENCE_INTVCC2; //ref = VDDANA
	 config_adc.resolution = ADC_RESOLUTION_8BIT;
	 config_adc.positive_input = ADC_POSITIVE_INPUT_PIN10;

	 adc_init(&adc_instance, ADC1, &config_adc);
	 adc_enable(&adc_instance);
 }

uint8_t ADC_ReadChannel4(void)
{
	uint16_t result;
	
	adc_set_positive_input(&adc_instance, ADC_POSITIVE_INPUT_PIN4);
	adc_start_conversion(&adc_instance);
	do {
		/* Wait for conversion to be done and read out result */
	} while (adc_read(&adc_instance, &result) == STATUS_BUSY);
	
	return (uint8_t)result; //cast result into 8b ToDo(discards higher bits?)
}

uint8_t ADC_ReadChannel5(void)
{
	uint16_t result;
	
	adc_set_positive_input(&adc_instance, ADC_POSITIVE_INPUT_PIN5);
	adc_start_conversion(&adc_instance);
	do {
		/* Wait for conversion to be done and read out result */
	} while (adc_read(&adc_instance, &result) == STATUS_BUSY);
	
	return (uint8_t)result; //cast result into 8b ToDo(discards higher bits?)
}

uint8_t ADC_ReadChannel8(void)
{
	uint16_t result;
	
	adc_set_positive_input(&adc_instance, ADC_POSITIVE_INPUT_PIN8);
	adc_start_conversion(&adc_instance);
	do {
		/* Wait for conversion to be done and read out result */
	} while (adc_read(&adc_instance, &result) == STATUS_BUSY);
	
	return (uint8_t)result; //cast result into 8b ToDo(discards higher bits?)
}

uint8_t ADC_ReadChannel9(void)
{
	uint16_t result;
	
	adc_set_positive_input(&adc_instance, ADC_POSITIVE_INPUT_PIN9);
	adc_start_conversion(&adc_instance);
	do {
		/* Wait for conversion to be done and read out result */
	} while (adc_read(&adc_instance, &result) == STATUS_BUSY);
	
	return (uint8_t)result; //cast result into 8b ToDo(discards higher bits?)
}

uint8_t ADC_ReadChannel10(void)
{
	uint16_t result;
	
	adc_set_positive_input(&adc_instance, ADC_POSITIVE_INPUT_PIN10); 
	adc_start_conversion(&adc_instance);
	do {
		/* Wait for conversion to be done and read out result */
	} while (adc_read(&adc_instance, &result) == STATUS_BUSY);
	
	return (uint8_t)result; //cast result into 8b ToDo(discards higher bits?)
}

uint8_t ADC_ReadChannel11(void)
{
	uint16_t result;
	
	adc_set_positive_input(&adc_instance, ADC_POSITIVE_INPUT_PIN11);
	adc_start_conversion(&adc_instance);
	do {
		/* Wait for conversion to be done and read out result */
	} while (adc_read(&adc_instance, &result) == STATUS_BUSY);
	
	return (uint8_t)result; //cast result into 8b ToDo(discards higher bits?)
}

