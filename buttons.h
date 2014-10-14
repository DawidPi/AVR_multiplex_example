/*
 * buttons.h
 *
 *  Created on: Oct 14, 2014
 *      Author: dawid
 */

#ifndef BUTTONS_H_
#define BUTTONS_H_

#include <util/delay.h>
#include <stdbool.h>

#define PORT_BUTTONS PORTB
#define DDR_BUTTONS DDRB
#define PIN_BUTTONS PINB

#define SLOW_BUTTON (1<<PB0)
#define SPEED_BUTTTON (1<<PB1)

#define MASK_BUTTONS (SLOW_BUTTON | SPEED_BUTTTON)

inline void buttons_init()
{
	DDR_BUTTONS &= ~(SLOW_BUTTON | SPEED_BUTTTON);	//buttons out
	PORT_BUTTONS |= SLOW_BUTTON | SPEED_BUTTTON;	// Hi-Z
}

static inline bool buttons_slowPressed()
{
	if(0 == (PIN_BUTTONS & SLOW_BUTTON))
	{
		_delay_ms(80);
		if(0 == (PIN_BUTTONS & SLOW_BUTTON))
		{
			_delay_ms(150);
			return true;
		}
		else
			return false;
	}
	else
	{
		return false;
	}
}

static inline bool buttons_speedPressed()
{
	if(0 == (PIN_BUTTONS & SPEED_BUTTTON))
	{
		_delay_ms(80);
		if(0 == (PIN_BUTTONS & SPEED_BUTTTON))
		{
			_delay_ms(150);
			return true;
		}
		else
			return false;
	}
	else
	{
		return false;
	}
}

#endif /* BUTTONS_H_ */
