/*
 * hbridge.h
 *
 * Created: 4/12/2019 5:40:15 PM
 *  Author: Brian Tate
 */ 


#ifndef HBRIDGE_H_
#define HBRIDGE_H_

#include <stdint.h>
#include <stdbool.h>
#include "UserIO.h"

void Hbridge1Init(void);
void Hbridge1Drive(uint8_t dutyCycle, bool direction);
void Hbridge1Enable(bool enable);

void Hbridge2Init(void);
void Hbridge2Drive(uint8_t dutyCycle, bool direction);
void Hbridge2Enable(bool enable);

#endif /* HBRIDGE_H__H_ */