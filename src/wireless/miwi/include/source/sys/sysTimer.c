/**
* \file  sysTimer.c
*
* \brief System timer implementation
*
* Copyright (c) 2018 Microchip Technology Inc. and its subsidiaries. 
*
* \asf_license_start
*
* \page License
*
* Subject to your compliance with these terms, you may use Microchip
* software and any derivatives exclusively with Microchip products. 
* It is your responsibility to comply with third party license terms applicable 
* to your use of third party software (including open source software) that 
* may accompany Microchip software.
*
* THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS".  NO WARRANTIES, 
* WHETHER EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, 
* INCLUDING ANY IMPLIED WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, 
* AND FITNESS FOR A PARTICULAR PURPOSE. IN NO EVENT WILL MICROCHIP BE 
* LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, INCIDENTAL OR CONSEQUENTIAL 
* LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND WHATSOEVER RELATED TO THE 
* SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS BEEN ADVISED OF THE 
* POSSIBILITY OR THE DAMAGES ARE FORESEEABLE.  TO THE FULLEST EXTENT 
* ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS IN ANY WAY 
* RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF ANY, 
* THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.
*
* \asf_license_stop
*
*/

/*- Includes ---------------------------------------------------------------*/
#include "compiler.h"
#include "common_hw_timer.h"
#include "sysTimer.h"
#include "hw_timer.h"
#include "port.h"
#include "tc.h"
#include "tc_interrupt.h"
#include <asf.h>

/*****************************************************************************
*****************************************************************************/
static void placeTimer(SYS_Timer_t *timer);
//static void SYS_HwExpiry_Cb(void);
static void SYS_HwExpiry_Cb(struct tc_module *const module);
//static void SYS_HwOverflow_Cb(void);
static void SYS_HwOverflow_Cb(struct tc_module *const module);

/*- Variables --------------------------------------------------------------*/
static SYS_Timer_t *timers;
volatile uint8_t SysTimerIrqCount;

volatile uint8_t timerExtension1,timerExtension2;
struct tc_module tc_instance;
/*- Implementations --------------------------------------------------------*/

/*************************************************************************//**
*****************************************************************************/
void SYS_TimerInit(void)
{
	SysTimerIrqCount = 0;
    timerExtension1 = 0;
    timerExtension2 = 0;

	timers = NULL;
		struct tc_config config_tc;
		tc_get_config_defaults(&config_tc);
		config_tc.clock_prescaler = TC_CLOCK_PRESCALER_DIV8;
		tc_init(&tc_instance, TC2, &config_tc);
		
		tc_register_callback(&tc_instance, SYS_HwExpiry_Cb,
		TC_CALLBACK_CC_CHANNEL0);
		tc_register_callback(&tc_instance, SYS_HwOverflow_Cb,
		TC_CALLBACK_OVERFLOW);
		tc_enable_callback(&tc_instance, TC_CALLBACK_CC_CHANNEL0);
		tc_enable_callback(&tc_instance, TC_CALLBACK_OVERFLOW);
		
		tc_enable(&tc_instance);
}

/*************************************************************************//**
*****************************************************************************/
void SYS_TimerStart(SYS_Timer_t *timer)
{
	if (!SYS_TimerStarted(timer)) {
		placeTimer(timer);
	}
}

/*************************************************************************//**
*****************************************************************************/
void SYS_TimerStop(SYS_Timer_t *timer)
{
	SYS_Timer_t *prev = NULL;

	for (SYS_Timer_t *t = timers; t; t = t->next) {
		if (t == timer) {
			if (prev) {
				prev->next = t->next;
			} else {
				timers = t->next;
			}

			if (t->next) {
				t->next->timeout += timer->timeout;
			}

			break;
		}

		prev = t;
	}
}

/*************************************************************************//**
*****************************************************************************/
bool SYS_TimerStarted(SYS_Timer_t *timer)
{
	for (SYS_Timer_t *t = timers; t; t = t->next) {
		if (t == timer) {
			return true;
		}
	}
	return false;
}

/*************************************************************************//**
*****************************************************************************/
void SYS_TimerTaskHandler(void)
{
	uint32_t elapsed;
	uint8_t cnt;
	irqflags_t flags;

	if (0 == SysTimerIrqCount) {
		return;
	}

	/* Enter a critical section */
	flags = cpu_irq_save();
	cnt = SysTimerIrqCount;
	SysTimerIrqCount = 0;
	/* Leave the critical section */
	cpu_irq_restore(flags);

	elapsed = cnt * SYS_TIMER_INTERVAL;

	while (timers && (timers->timeout <= elapsed)) {
		SYS_Timer_t *timer = timers;

		elapsed -= timers->timeout;
		timers = timers->next;
		if (SYS_TIMER_PERIODIC_MODE == timer->mode) {
			placeTimer(timer);
		}

		if (timer->handler) {
			timer->handler(timer);
		}
	}

	if (timers) {
		timers->timeout -= elapsed;
	}
}

/*************************************************************************//**
*****************************************************************************/
static void placeTimer(SYS_Timer_t *timer)
{
	if (timers) {
		SYS_Timer_t *prev = NULL;
		uint32_t timeout = timer->interval;

		for (SYS_Timer_t *t = timers; t; t = t->next) {
			if (timeout < t->timeout) {
				t->timeout -= timeout;
				break;
			} else {
				timeout -= t->timeout;
			}

			prev = t;
		}

		timer->timeout = timeout;

		if (prev) {
			timer->next = prev->next;
			prev->next = timer;
		} else {
			timer->next = timers;
			timers = timer;
		}
	} else {
		timer->next = NULL;
		timer->timeout = timer->interval;
		timers = timer;
	}
}

/*********************************************************************
* Function:         void MiWi_TickGet()
*
* PreCondition:     none
*
* Input:		    none
*
* Output:		    MIWI_TICK - the current symbol time
*
* Side Effects:	    The timer interrupt is disabled
*                   for several instruction cycles while the 
*                   timer value is grabbed.  This is to prevent a
*                   rollover from incrementing the timer extenders
*                   during the read of their values
*
* Overview:		    This function returns the current time
*
* Note:			    This function should never be called 
*                   when interrupts are disabled if interrupts are 
*                   disabled when this is called then the timer 
*                   might rollover and the byte extension would not 
*                   get updated.
********************************************************************/
uint32_t MiWi_TickGet(void)
{
    MIWI_TICK currentTime;
	irqflags_t flags;
//	uint8_t current_timerExtension1 = timerExtension1; //BT - this is unused, what was it's intention?
    
 	/* Enter a critical section */
	flags = cpu_irq_save();

	currentTime.word.w0 = tc_get_count_value(&tc_instance);
	/* Leave the critical section */
	cpu_irq_restore(flags);

    //wait until overflow interrupt occurs if current time count is greater than 0xFF00 , because we are expecting interrupt to occur soon
	if (currentTime.word.w0 > 0xFF00)
	{
		flags = cpu_irq_save();
		while(!(tc_instance.hw->COUNT16.INTFLAG.bit.OVF));
		//call overflow interrupt callback
//		SYS_HwOverflow_Cb();
		SYS_HwOverflow_Cb(&tc_instance); //why is this here? shouldn't this happen via callback?
		currentTime.word.w0 = tc_get_count_value(&tc_instance);
		//clear over flow interrupt flag
		tc_instance.hw->COUNT16.INTFLAG.reg = TC_INTFLAG_OVF;
		/* Leave the critical section */
		cpu_irq_restore(flags);
	}
	//copy byte extension 
	currentTime.byte.b2 = timerExtension1;
	currentTime.byte.b3 = timerExtension2;
    return currentTime.Val;
}

/*********************************************************************
* Function:         MIWI_TICK MiWi_TickGetDiff()
*
* PreCondition:     none
*
* Input:		    current_tick  - Recent tick read from MiWi_TickGet
*                   previous_tick - Tick read prior to current_tick for 
*                                   calculation.
*
* Output:		    uint32_t - Difference in current_tick to previous_tick
*
* Side Effects:	    none
*
* Overview:		    This function returns difference between current_tick
*                   and previous_tick
*
* Note:			    none
********************************************************************/
uint32_t MiWi_TickGetDiff(MIWI_TICK current_tick, MIWI_TICK previous_tick)
{
	uint32_t ret_val;
	if (current_tick.Val > previous_tick.Val)
	{
		/* If current > previous, no overflow in running timer*/
		ret_val = current_tick.Val - previous_tick.Val;
	}
	else
	{
		/* Handling Overflow as current tick < previous tick */
		ret_val = (0xFFFFFFFF - previous_tick.Val) + current_tick.Val;
	}
	return ret_val;
}


/*****************************************************************************
*****************************************************************************/
volatile uint32_t cntDelay = 0;

//static void (*tc_callback_t)(struct tc_module *const module)
//static void SYS_HwExpiry_Cb(void)
static void SYS_HwExpiry_Cb(struct tc_module *const module)
{
	SysTimerIrqCount++;
	cntDelay++;
	if(500000 == cntDelay){
		// port_pin_toggle_output_level(LED0);
		cntDelay = 0;
	}
// 	uint32_t value = tc_get_count_value(&tc_instance);
// 	tc_set_compare_value(&tc_instance, 0, value + 10000);
	uint32_t value = tc_get_count_value(module);
	tc_set_compare_value(module, 0, value + 10000);
}

//static void SYS_HwOverflow_Cb(void)
static void SYS_HwOverflow_Cb(struct tc_module *const module)
{
	timerExtension1++;
	if(timerExtension1 == 0)
	{
		timerExtension2++;
	}
}

void SYS_TimerAdjust_SleptTime(uint32_t sleeptime)
{
	SYS_Timer_t* timer = timers;
    /* Synchornise timers based on sleep time */
	while (timer)
	{
		if (timer->timeout > sleeptime)
		{
			timer->timeout -= sleeptime;
		}
		else
		{
			timer->timeout = 0;
		}
		timer = timer->next;
	}
//     /* Stop and Start Timers */
	tc_disable_callback(&tc_instance, TC_CALLBACK_CC_CHANNEL0);
	tc_disable_callback(&tc_instance, TC_CALLBACK_OVERFLOW);
	struct tc_config config_tc;
	tc_get_config_defaults(&config_tc);
	config_tc.clock_prescaler = TC_CLOCK_PRESCALER_DIV8;
	tc_init(&tc_instance, TC0, &config_tc);

	tc_register_callback(&tc_instance, SYS_HwExpiry_Cb,
	TC_CALLBACK_CC_CHANNEL0);
	tc_register_callback(&tc_instance, SYS_HwOverflow_Cb,
	TC_CALLBACK_OVERFLOW);
	tc_enable_callback(&tc_instance, TC_CALLBACK_CC_CHANNEL0);
	tc_enable_callback(&tc_instance, TC_CALLBACK_OVERFLOW);

	tc_enable(&tc_instance);
}