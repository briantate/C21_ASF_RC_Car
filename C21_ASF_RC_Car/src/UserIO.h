/*
 * UserIO.h
 *
 * Created: 6/5/2016 4:45:53 PM
 *  Author: btate
 */ 


#ifndef USERIO_H_
#define USERIO_H_

	#include <asf.h>

	//motor definitions
	#define MOTOR_A_FORWARD_PIN          PIN_PA15E_TC4_WO1//PIN_PB09E_TC0_WO1//PIN_PB02E_TC2_WO0    //EXT2 Pin 17
	#define MOTOR_A_FORWARD_PIN_MUX      MUX_PA15E_TC4_WO1//MUX_PB09E_TC0_WO1//MUX_PB02E_TC2_WO0
	#define MOTOR_A_FORWARD_PIN_PINMUX   PINMUX_PA15E_TC4_WO1//PINMUX_PB09E_TC0_WO1//PINMUX_PB02E_TC2_WO0
	#define MOTOR_A_FORWARD_PIN_CHANNEL  1//0
	#define MOTOR_A_BACKWARD_PIN         PIN_PA14E_TC4_WO0//PIN_PB08E_TC0_WO0//PIN_PB03E_TC2_WO1    //EXT2 Pin 15
	#define MOTOR_A_BACWARD_PIN_MUX      MUX_PA14E_TC4_WO0//MUX_PB08E_TC0_WO0//MUX_PB03E_TC2_WO1
	#define MOTOR_A_BACKWARD_PIN_PINMUX  PINMUX_PA14E_TC4_WO0//PINMUX_PB08E_TC0_WO0//PINMUX_PB01E_TC3_WO1
	#define MOTOR_A_BACKWARD_PIN_CHANNEL 0//1
	#define MOTOR_A_PWM_MODULE           TC4//TC0//TC2
	#define MOTOR_A_ENABLE_PIN           PIN_PB31//PIN_PA22

	#define MOTOR_B_FORWARD_PIN          PIN_PB17E_TC2_WO1//PIN_PB01E_TC3_WO1
	#define MOTOR_B_FORWARD_PIN_MUX      MUX_PB17E_TC2_WO1//MUX_PB01E_TC3_WO1
	#define MOTOR_B_FORWARD_PIN_PINMUX   PINMUX_PB17E_TC2_WO1//PINMUX_PB01E_TC3_WO1
	#define MOTOR_B_FORWARD_PIN_CHANNEL  1
	#define MOTOR_B_BACKWARD_PIN         PIN_PB16E_TC2_WO0//PIN_PA20E_TC3_WO0
	#define MOTOR_B_BACWARD_PIN_MUX      MUX_PB16E_TC2_WO0//MUX_PA20E_TC3_WO0
	#define MOTOR_B_BACKWARD_PIN_PINMUX  PINMUX_PB16E_TC2_WO0//PINMUX_PA20E_TC3_WO0
	#define MOTOR_B_BACKWARD_PIN_CHANNEL 0
	#define MOTOR_B_PWM_MODULE           TC2//TC3
	#define MOTOR_B_ENABLE_PIN           PIN_PA27

void configure_pins(void);
void configure_eic_callback(void);
void configure_extint(void);


#endif /* USERIO_H_ */