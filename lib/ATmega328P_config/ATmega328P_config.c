#include <avr/io.h>
#include "..\..\include\defines.h"

void io_config(void)
{
	/* IO direction definition - 1 for output*/
	DDRB = 0b00100000;
	DDRC = 0b00000000;
	DDRD = 0b01000010;
	
	/* Input pull-up control - 0 to disable*/
	/* Output value control - pull-up always disabled in this case */
	PORTB = 0x00;
	PORTC = 0x00;
	PORTD = 0x00;
	
	/* Input value */
	/* Output: Writing a 1 toggle PORTx value */
	PINB = 0x00;
	PINC = 0x00;
	PIND = 0x00;
	
	/* Global pull-up control on inputs - 0x01 to disable*/
	MCUCR = 0x01;
}

void timer1_config(void)
{
	// Clear OC1A on compare match, set OC1A/OC1B at BOTTOM
	TCCR1A |= 1 << COM1A1;
	// Fast PWM, (TOP @ ICR1)
	TCCR1A |= 1 << WGM11; 	 	
	TCCR1B |= 1 << WGM12;
	TCCR1B |= 1 << WGM13;
	// no prescaling
	TCCR1B |= 1 << CS10;
	// defines duty cycle
	OCR1A = 0;
	// defines TOP
	ICR1 = 153;
	// disabling timer 1 interrupts
	TIMSK1 = 0x00;
}

void timer0_config(void)
{
	// Clear OC0A on compare match, set OC0A at BOTTOM
	TCCR0A |= 1 << COM0A1;
	TCCR0A |= 1 << WGM01;
	TCCR0A |= 1 << WGM00;
	// 1024 prescaling
	TCCR0B |= 1 << CS02;
	TCCR0B |= 1 << CS00;
	// DEFINE OCR0A in servo_init function !!!
	// disabling timer 0 interrupts
	TIMSK0 = 0x00;
}

void ext_int_config()
{
	// INT0/1 disabled
	EIMSK = 0x01;
	// INT0/1 mode: rising edge of INT0/1
	EICRA |= (1 << ISC01) | (1 << ISC00) | (1 << ISC11) | (1 << ISC10);
	// Pin change INT enable: no PCINT enabled
	PCICR &= 0x00;
	// Pin change enable PCINT 7.. 0: none enabled
	PCMSK0  &= 0x00;
	// Pin change enable PCINT15.. 8: none enabled
	PCMSK1  &= 0x00;
	// Pin change enable PCINT23..16: none enabled
	PCMSK2  &= 0x00;
}