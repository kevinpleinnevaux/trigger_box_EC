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
	if (DEBUG) uart_printf("Out 2");
}

ISR(INT1_vect)
{
	in1 = true;
	TIMSK1 |= 1 << OCIE1A;
	TCNT1 = 0;
	EIMSK &= ~(1 << 1);
	count1 = 0;
	PORTB |= 1 << 4;
	if (DEBUG) uart_printf("Out 1");
}

ISR(TIMER1_COMPA_vect)
{
	if (in1 == true)
	{
		//in1 = false;
		if (count1 == 0) PORTB ^= 1 << 4;
		else if (count1 == 2) EIMSK |= 1 << 1;
		count1++;
	}
	if (in2 == true)
	{
		//in2 = false;
		if (count2 == 0) PORTB ^= 1 << 3;
		else if (count2 == 2) EIMSK |= 1 << 0;
		count2++;
	}
}