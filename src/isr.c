#include "defines.h"
#include "ATmega328P_uart.h"
#include <avr/io.h>
#include <avr/interrupt.h>
#include "stdbool.h"

bool in1 = false, in2 = false;

ISR(INT0_vect)
{
	in2 = true;
	TCNT1 = 0;
	EIMSK &= ~(1 << 0);
	PORTB |= 1 << 3;
}

ISR(INT1_vect)
{
	in1 = true;
	TCNT1 = 0;
	EIMSK &= ~(1 << 1);
	PORTB |= 1 << 4;
}

ISR(TIMER1_COMPA_vect)
{
	if (in1 == true)
	{
		PORTB ^= 1 << 4;
		EIMSK |= 1 << 1;
		in1 = false;
	}
	if (in2 == true)
	{
		PORTB ^= 1 << 3;
		EIMSK |= 1 << 0;
		in2 = false;
	}
}