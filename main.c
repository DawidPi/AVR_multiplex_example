/*
 * main.c
 *
 *  Created on: Oct 14, 2014
 *      Author: dawid
 */

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <util/atomic.h>
#include "7_segm_led/multiplex.h"
#include "buttons.h"

#define ALWAYS 1

inline void timer_init();
uint16_t jump;

void main()
{
	timer_init();

	ATOMIC_BLOCK(ATOMIC_RESTORESTATE)
	{
		buttons_init();
		multi_init();
		multi_setFirstDigit();
		multi_setNumber(7);
	}

	while(ALWAYS)
	{
		if(OCR1A > 0x0FFF)
			jump = 100;
		else
			jump = 20;

		if(buttons_slowPressed())
		{
			multi_setDot();
			if(OCR1A < 0xFFFF-1000)
			OCR1A += jump;
		}
		else
			multi_clrDot();


		if(buttons_speedPressed())
		{
			multi_setDot();
			if(OCR1A > 25)
			OCR1A -= jump;
		}
		else
			multi_clrDot();

		if(OCR1A < TCNT1)
		{
			multi_nextDigit();
			TCNT1 =0;
		}
	}
}

inline void timer_init()
{
	TCCR1B |= (1<<WGM12); //timer on CTC
	TCCR1B |= (1<<CS12) | (1<<CS10); //prescaller 1024
	OCR1A = 0x0F0F; //some low mode
	TIMSK |= (1<<OCIE1A); //allow for interrupts

	sei();
}

ISR(TIMER1_COMPA_vect)
{
	multi_nextDigit();
}

