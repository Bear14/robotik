/* 
 *	Basis
 *	2009 Benjamin Reh und Joachim Schleicher
 */

#include <stdlib.h> // enthaelt itoa, ltoa

#include "socket.cpp"
#define SLAVE_PORT 5006

//Schnittstelle initialisieren:
// USART-Init
void uartInit()
{

}

// Ein Zeichen senden
int uart_putc(unsigned char c)
{
	char a[1];
	a[0] = c;
	Sender(a,SLAVE_PORT);
	return 0;
}

//ganze Zeichenkette senden
void uart_puts (char *s)
{
	Sender(s,SLAVE_PORT);
}

//ganze Zeichenkette aus program space senden
/*
void uart_puts_pgm (const char* PROGMEM  str)
{

	while (1)
	{   				// so lange c != '\0' also ungleich dem "String-Endezeichen" 
		char c = (char) pgm_read_byte (str);
		uart_putc(c);
		if ('\0' == c)
			return;
		str++;
	}
}
*/

//Zahl ausgeben
void uart_puti (int16_t i) 
{
	char buffer[10];
	//itoa(i, buffer, 10);
	snprintf(buffer,sizeof(buffer),"%d",i);
	Sender(buffer,SLAVE_PORT);
}


//Ein Zeichen empfangen
unsigned char uart_getc(void)
{
	/*
	while (!(UCSR0A & (1<<RXC0)));	// warten bis Zeichen verfuegbar
		return UDR0;		// Zeichen aus UDR an Aufrufer zurueckgeben
	 */
}
