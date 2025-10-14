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
	#define MOTOR_A_DIR_PIN              PIN_PB02
	#define MOTOR_A_PWM_PIN              PIN_PB13E_TC0_WO1
	#define MOTOR_A_PWM_MUX              MUX_PB13E_TC0_WO1
	#define MOTOR_A_PWM_PINMUX           PINMUX_PB13E_TC0_WO1
	#define MOTOR_A_PWM_CHANNEL          1
	#define MOTOR_A_BRAKE_PIN            PIN_PB31
	#define MOTOR_A_PWM_MODULE           TC0

	#define MOTOR_B_DIR_PIN              PIN_PB01
	#define MOTOR_B_PWM_PIN              PIN_PB00E_TC3_WO0
	#define MOTOR_B_PWM_MUX              MUX_PB00E_TC3_WO0
	#define MOTOR_B_PWM_PINMUX           PINMUX_PB00E_TC3_WO0
	#define MOTOR_B_PWM_CHANNEL          0
	#define MOTOR_B_BRAKE_PIN            PIN_PB05
	#define MOTOR_B_PWM_MODULE           TC3



void configure_pins(void);
void configure_eic_callback(void);
void configure_extint(void);


#endif /* USERIO_H_ */