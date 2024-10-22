#include <avr/io.h>
#include "..\..\include\defines.h"

void io_config(void)
{
	/* IO direction definition - 1 for output*/
	DDRB = 0b00111000;
	DDRC = 0b00000000;
	DDRD = 0b00000010;
	
	/* Input pull-up control - 0 to disable*/
	/* Output value control - pull-up always disabled in this case */
	PORTB &= 0x00;
	PORTC &= 0x00;
	PORTD &= 0x00;
	
	/* Input value */
	/* Output: Writing a 1 toggle PORTx value */
	PINB = 0x00;
	PINC = 0x00;
	PIND = 0x00;
	
	/* Global pull-up control on inputs - 0x01 to disable*/
	MCUCR = 0x00;
}

void timer1_config()
{
	TCCR1A = 0x00;		
	TCCR1B |= (1 << WGM12);		// CTC Mode
	TCCR1B |= 1 << CS12;		// 256 prescaler
	TCCR1C = 0x00;
	OCR1A = 3125; // Compare match A @ 50ms
	TIMSK1 |= 1 << OCIE1A;
}

void ext_int_config()
{
	EIMSK = 0x03;	// INT0 enabled, INT1 enabled
	EICRA = 0x0F;	// rising edge of INT0, rising edge of INT1
	PCICR = 0x00;	// Pin change INT enable: none enabled
	PCMSK0 = 0x00;	// Pin change enable PCINT 7.. 0: none enabled
	PCMSK1 = 0x00;	// Pin change enable PCINT15.. 8: none enabled
	PCMSK2 = 0x00;	// Pin change enable PCINT23..16: none enabled
}