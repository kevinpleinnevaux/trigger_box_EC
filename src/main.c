#include "defines.h"
#include "util/delay.h"
#include <avr/io.h>
#include <avr/interrupt.h>
#include "ATmega328P_config.h"
#include "ATmega328P_uart.h"

int main(void)
{	
	cli();
	ext_int_config();
	io_config();
	timer1_config();
	uart_config();
	sei();
	uart_printf("config done!\n");
	PORTB |= 1 << 3;
	_delay_ms(100);
	PORTB &= ~(1<<3);
	_delay_ms(100);
	PORTB |= 1 <<4 ;
	_delay_ms(100);
	PORTB &= ~(1<<4);
	_delay_ms(100);
	PORTB |= 1 << 3;
	_delay_ms(100);
	PORTB &= ~(1<<3);
	_delay_ms(100);
	PORTB |= 1 <<4 ;
	_delay_ms(100);
	PORTB &= ~(1<<4);
	_delay_ms(100);
	while (1);
}