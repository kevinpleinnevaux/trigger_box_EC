#include "defines.h"
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
	uart_config(true);
	sei();
	uart_printf("config done!");

    while (1);
}