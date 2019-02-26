/* 
 *	Basis
 *	2009 Benjamin Reh
 */

  

#include <avr/io.h>
#include "adc.h"

//Initialisierung
void ADCInit(uint8_t kanal)
{
	// Hier wird der gewuenschte Pin auf Eingang geschaltet.  
	//Sollen mehrere Pins verwendet werden, diese Funktion mehrfach aufrufen oder manuell die entsprechenden Pins als Eingang setzen
	DDRC &=~(1<<kanal); 
	
	// Frequenzvorteiler setzen auf 128 und ADC aktivieren
	// Frequenz des ADC = Frequenz des Controllers (16 Mhz) geteilt durch Frequenzteiler
	// Bereich bitte im Datenblatt nachlesen
	ADCSRA = (1<<ADEN) | (1<<ADPS2) | (1<<ADPS1) | (1<<ADPS0);    
 	// AVCC als Referenz nutzen 
	//  d.h. Digitalwerte entsprechen Spannungen von 0 bis 5V (=AVCC)
	//  alternativ kann auch eine externe Spannungreferenz verwenden werden (siehe Datenblatt)
	ADMUX = (1<<REFS0) | kanal;  // den richtigen Kanal auswaehlen
	

	// nach Aktivieren des ADC wird ein "Dummy-Readout" empfohlen, man liest
    // also einen Wert und verwirft diesen, um den ADC "warmlaufen zu lassen" 
  	ADCSRA |= (1<<ADSC);              // eine ADC-Wandlung 
    while ( ADCSRA & (1<<ADSC) ) {
		// auf Abschluss der Konvertierung warten 
  	}

}

//Wert auslesen
uint16_t getADCValue(uint8_t kanal)
{
	ADMUX  &= ~0x0F; 				// Kanal auf 0 setzen
	ADMUX  |= (kanal & 0x0F);  		// den richtigen Kanal auswaehlen
	ADCSRA |= (1<<ADSC);            // eine Wandlung "single conversion"
	while ( ADCSRA & (1<<ADSC) ){}  // auf Abschluss der Konvertierung warten
	
	return ADCW;

}
#include <util/delay.h>
#include <avr/io.h>
#include <inttypes.h>
#include "display.h"

void displayInit(void)
{
	DDRB |= (1<<5);//SCK
	DDRB |= (1<<3);//SDA
	DDRB |= (1<<4);//RST
	DDRB |= (1<<1);//CD
	DDRB |= (1<<0);//CS0
	PORTB |= (1<<4);//kein RST
	PORTB &= ~(1<<1);//CD auf low
	PORTB &= ~(1<<5);//SCK auf low
	PORTB |= (1<<0);_delay_us(10);PORTB &= ~(1<<0);//CS0 auf low
	sendbyte(241,0);
	sendbyte(103,0);
	sendbyte(198,0);//LCD mapping Hierum
	//~ sendbyte(192,0);//LCD mapping Hierum
	sendbyte(64,0);
	sendbyte(80,0);
	sendbyte(43,0);
	sendbyte(235,0);
	sendbyte(129,0);
	sendbyte(95,0);
	sendbyte(137,0);
	uint16_t i;
	for(i=0;i<4160;i++)//RAM-Ausspühlen, alles weiß
	{
		sendbyte(0,1);
	}
	//~ DDRC |= 1;//Debug-LED
	sendbyte(0,0);//RAM-Zeigerpostition zurück auf 0/0
	sendbyte(16,0);
	sendbyte(96,0);
	sendbyte(175,0);//Bildschirm an
	//~ PORTC |= 1;//Debug-LED an==Init zu Ende
}

void clear(void)
{
	uint16_t i;
	sendbyte(0,0);//RAM-Zeigerpostition zurück auf 0/0
	sendbyte(16,0);
	sendbyte(96,0);
	for(i=0;i<4160;i++)//RAM-Ausspühlen, alles weiß
	{
		sendbyte(0,1);
	}
	sendbyte(0,0);//RAM-Zeigerpostition zurück auf 0/0
	sendbyte(16,0);
	sendbyte(96,0);
}

void sendbyte(uint8_t byte,uint8_t cd)
{
	int8_t i;
	if(cd)
		PORTB |= (1<<1);
	for(i=7;i>-1;i--)
	{
		PORTB &= ~(1<<5);
		if((1<<i)&byte)
			PORTB |= (1<<3);
		else
		{
			PORTB &= ~(1<<3);
		}
		PORTB |= (1<<5);
	}
	PORTB &= ~(1<<1);
}

void page(uint8_t x,uint8_t y,uint8_t h)//alle Pixel einer Page beschreiben
{
	sendbyte(15&x,0);//Adressentranslation
	sendbyte(16+(x>>4),0);
	sendbyte(96+y,0);
	sendbyte(h,1);
}
/* 
 *	Basis
 *	2009 Benjamin Reh
 */
#include <avr/interrupt.h>
#include "timer.h"

volatile uint32_t ms_timer;

void timerInit(void)
{
	TCNT2  = 0x00;			// TIMER vorladen
	TCCR2A = 1<<WGM21;		// CTC Mode
		
	TCCR2B = (1<<CS22) | (1<<CS20); //prescaler auf 128 setzen
	OCR2A = OCR2A_VAL; 			//Wert für Vergleichregister setzen (kleiner bedeutet schneller)
	TIMSK2  |= 1<<OCIE2A;		// TIMER2 Output Compare Match A Interrupt an
	
	sei();				// enable interrupts

	
	
}

SIGNAL (TIMER2_COMPA_vect)
{

//	hier koennen weitere Befehle ergaenzt werden, die jede Millisekunde ausgefuehrt werden sollen

	ms_timer++;  // Die "Systemzeit" inkrementieren


}

uint32_t getMsTimer() {
	uint32_t ret;
	cli(); // interrupts aus
	ret = ms_timer; // Wert aus volatile Variable kopieren
	sei(); // interrupts wieder an
	return ret;
}
/* 
 *	Basis
 *	2009 Benjamin Reh und Joachim Schleicher
 */

#include <avr/io.h>
#include <stdlib.h> // enthaelt itoa, ltoa
#include "uart.h"

//Schnittstelle initialisieren:
// USART-Init
void uartInit()
{
	UCSR0B |= (1 << TXEN0 )|(1 << RXEN0 );	// UART Senden und empfangen einschalten
	UBRR0 = UBRR_VAL;				//Baudrate einstellen, die im Header-File definiert wurde
}

// Ein Zeichen senden
int uart_putc(unsigned char c)
{
	while(!(UCSR0A & (1 << UDRE0))); 	// warte, bis UDR bereit ist, d.h. letztes Zeichen den Sendepuffer verlassen hat
	UDR0 = c;				//Zeichen senden
	return 0;
}

//ganze Zeichenkette senden
void uart_puts (char *s)
{
	while (*s)
	{   				// so lange *s != '\0' also ungleich dem "String-Endezeichen" 
		uart_putc(*s);
		s++;
	}
}

//ganze Zeichenkette aus program space senden
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

//Zahl ausgeben
void uart_puti (int16_t i) 
{
	char buffer[10];
	itoa(i, buffer, 10);
	uart_puts(buffer);
}


//Ein Zeichen empfangen
unsigned char uart_getc(void)
{
	while (!(UCSR0A & (1<<RXC0)));	// warten bis Zeichen verfuegbar
		return UDR0;		// Zeichen aus UDR an Aufrufer zurueckgeben
}
