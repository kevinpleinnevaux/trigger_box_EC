#include "defines.h"
#include <avr/io.h>
#include <avr/interrupt.h>

int in1 = false, in2 = false;
int count1 = 0, count2 = 0;

ISR(INT0_vect)
{
	in2 = true;
	TIMSK1 |= 1 << OCIE1A;
	TCNT1 = 0;
	EIMSK &= ~(1 << 0);
	count2 = 0;
	PORTB |= 1 << 3;
}

ISR(INT1_vect)
{
	in1 = true;
	TIMSK1 |= 1 << OCIE1A;
	TCNT1 = 0;
	EIMSK &= ~(1 << 1);
	count1 = 0;
	PORTB |= 1 << 4;
}

ISR(TIMER1_COMPA_vect)
{
	if (in1 == true)
	{
		if (count1 == 0) PORTB ^= 1 << 4;
		else if (count1 == 2) EIMSK |= 1 << 1;
		count1++;
	}
	if (in2 == true)
	{
		if (count2 == 0) PORTB ^= 1 << 3;
		else if (count2 == 2) EIMSK |= 1 << 0;
		count2++;
	}
}