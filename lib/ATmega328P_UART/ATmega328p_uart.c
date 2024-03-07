#include <avr/io.h>
#include <stdio.h>
#include <stdlib.h>
#include "..\..\include\defines.h"

void uart_config()
{
	// resets control and status register A
	UCSR0A = 0x00;									
	//Rx int ON - Tx int OFF - RX enable - TX enable
	UCSR0B |= (1 << RXCIE0) | (1 << RXEN0) | (1 << TXEN0);				
	// character size: 9-bit
	UCSR0C |= (1 << UCSZ02) | (1 << UCSZ01) | (1 << UCSZ00);							
	// baudrate: 9600bps
	UBRR0 = 103;									
}

void char_to_uart(char data)
{
	UDR0 = data;
	
	while(!(UCSR0A & 0x40));
	
	UCSR0A |= 0x40;
	
}

void uart_printf(char *a)
{
	for(int i = 0; a[i] != '\0'; i++) char_to_uart(a[i]);
}

void byte_to_uart(char byte, char *byteName)
{
	char temp = 0;
	char byteBin[8] = "";
	
	uart_printf(byteName);
	uart_printf(" = ");

	// print 1st nibble
	for (int i=0; i<4; i++)
	{
		temp = 0;
		if (byte & (1 << (7-i))) temp = 1;
		byteBin[i] = temp + 48;
		char_to_uart(byteBin[i]);
	}

	// mark space between nibbles
	char_to_uart(32);

	// print 2nd nibble
	for (int i=4; i<8; i++)
	{
		temp = 0;
		if (byte & (1 << (7-i))) temp = 1;
		byteBin[i] = temp + 48;
		char_to_uart(byteBin[i]);
	}
	uart_printf("\r\n");
}