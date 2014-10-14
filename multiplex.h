/*
 * multiplex.h
 *
 *  Created on: Oct 14, 2014
 *      Author: dawid
 */

#ifndef MULTIPLEX_H_
#define MULTIPLEX_H_

#include <avr/io.h>

#define PORT_SEGMENTS PORTA
#define DDR_SEGMENTS DDRA

#define SEGMENT_A (1<<PA0)
#define SEGMENT_B (1<<PA1)
#define SEGMENT_C (1<<PA2)
#define SEGMENT_D (1<<PA3)
#define SEGMENT_E (1<<PA4)
#define SEGMENT_F (1<<PA5)
#define SEGMENT_G (1<<PA6)
#define SEGMENT_H (1<<PA7) // dot

#define PORT_DIGITS PORTD
#define DDR_DIGITS 	DDRD

#define DIGIT_ONE 	(1<<PD0)
#define DIGIT_TWO 	(1<<PD1)
#define DIGIT_THREE	(1<<PD2)
#define DIGIT_FOUR	(1<<PD3)

#define DIGITS_MASK (DIGIT_ONE | DIGIT_TWO | DIGIT_THREE | DIGIT_FOUR)

inline void multi_init()
{
	DDR_DIGITS |= DIGITS_MASK;	//digits out
	DDR_SEGMENTS = 0xFF;		//segments out
	PORT_SEGMENTS = 0xFF;		//off segments
	PORT_DIGITS = 0xFF;			//off digits
}

// DDR must be set properly in order for these functions to work

// set functions
inline void multi_setFirstDigit() { PORT_DIGITS &= ~DIGIT_ONE; }
inline void multi_setSecondDigit() { PORT_DIGITS &= ~DIGIT_TWO; }
inline void multi_setThirdDigit() { PORT_DIGITS &= ~DIGIT_THREE; }
inline void multi_setFourthDigit() { PORT_DIGITS &= ~DIGIT_FOUR; }

//clr functions
inline void multi_clrFirstDigit() { PORT_DIGITS |= DIGIT_ONE; }
inline void multi_clrSecondDigit() { PORT_DIGITS |= DIGIT_TWO; }
inline void multi_clrThirdDigit() { PORT_DIGITS |= DIGIT_THREE; }
inline void multi_clrFourthDigit() { PORT_DIGITS |= DIGIT_FOUR; }
inline void multi_clrAll() { PORT_DIGITS |= 0xFF & DIGITS_MASK; }

inline void multi_nextDigit()	//swap digit to next
{
	PORT_DIGITS = (~((~PORT_DIGITS & DIGITS_MASK) << 1)) & DIGITS_MASK;

	if(DIGITS_MASK == (PORT_DIGITS & DIGITS_MASK))
	{
		multi_setFirstDigit();
	}
}

inline void multi_setDot() { PORT_SEGMENTS &= ~SEGMENT_H; }
inline void multi_clrDot() { PORT_SEGMENTS |= SEGMENT_H; }

const uint8_t multi_numbersTab[10] =
{
	/* 0 */	~(SEGMENT_A | SEGMENT_B | SEGMENT_C | SEGMENT_D | SEGMENT_E | SEGMENT_F),
	/* 1 */ ~(SEGMENT_B | SEGMENT_C),
	/* 2 */ ~(SEGMENT_A | SEGMENT_B | SEGMENT_G | SEGMENT_E | SEGMENT_D),
	/* 3 */ ~(SEGMENT_A | SEGMENT_B | SEGMENT_G | SEGMENT_C | SEGMENT_D),
	/* 4 */ ~(SEGMENT_F | SEGMENT_G | SEGMENT_B | SEGMENT_C),
	/* 5 */ ~(SEGMENT_A | SEGMENT_F | SEGMENT_G | SEGMENT_C | SEGMENT_D),
	/* 6 */ ~(SEGMENT_A | SEGMENT_F | SEGMENT_E | SEGMENT_D | SEGMENT_C | SEGMENT_G),
	/* 7 */ ~(SEGMENT_A | SEGMENT_B | SEGMENT_C),
	/* 8 */ ~(SEGMENT_A | SEGMENT_B | SEGMENT_C | SEGMENT_D | SEGMENT_E | SEGMENT_F | SEGMENT_G),
	/* 9 */ ~(SEGMENT_A | SEGMENT_B | SEGMENT_G | SEGMENT_F | SEGMENT_C)
};

inline void multi_setNumber(const uint8_t number)
{
	//in case of wrong val
	if(9 < number)
		return;

	PORT_SEGMENTS = multi_numbersTab[number];
}

#endif /* MULTIPLEX_H_ */
