/* 
 *	Basis
 *	2009 Benjamin Reh
 */
 
#ifndef ADC_H
#define ADC_H
#include <inttypes.h>

//initialize ADC
void ADCInit(uint8_t kanal );

//Read adc-value (10 bit)
uint16_t getADCValue(uint8_t kanal);

#endif
#ifndef BUTTONS_H
#define BUTTONS_H
inline void buttonsInit() {
	DDRD &=~( (1<<2) | (1<<3) | (1<<4) | (1<<5) | (1<<6) | (1<<7)); 
	PORTD |=( (1<<2) | (1<<3) | (1<<4) | (1<<5) | (1<<6) | (1<<7)); 

	DDRC &= ~( (1<<4) | (1<<5));
	PORTC |= ( (1<<4) | (1<<5));
}

#define B_UP (!(PIND & (1<<2)))
#define B_DOWN (!(PIND & (1<<3)))
#define B_LEFT (!(PIND & (1<<4)))
#define B_RIGHT (!(PIND & (1<<5)))
#define B_A (!(PIND & (1<<6)))
#define B_B (!(PIND & (1<<7)))

#define B_PAUSE (!(PINC & (1<<4)))
#define B_SELECT (!(PINC & (1<<5)))



#endif
#ifndef DISPLAY_H
#define DISPLAY_H


void displayInit(void);
void clear(void);
void sendbyte(uint8_t byte,uint8_t cd);
void page(uint8_t x,uint8_t y,uint8_t h);

#endif
/*/* 
 *	Basis
 *	2009 Benjamin Reh
 */
#ifndef TIMER_H
#define TIMER_H

#ifndef F_CPU
#warning "adjust OCR2A and set F_CPU"
#define F_CPU 16000000UL
#endif
#define OCR2A_VAL (F_CPU/(128000UL)) // 1 Millisekunde bei 128-Prescaler


void timerInit(void);
uint32_t getMsTimer();

#endif
/* 
 *	Basis
 *	2009 Benjamin Reh und Joachim Schleicher
 */
#ifndef UART_H
#define UART_H

#include <avr/pgmspace.h>

//USART
#define BAUD 9600UL          // Baudrate

// F_CPU muss gesetzt sein.
#ifndef F_CPU
#warning "F_CPU war noch nicht definiert, wird nun nachgeholt mit 16000000"
#define F_CPU 16000000UL    // Systemtakt in Hz - Definition als unsigned long beachten >> Ohne ergeben Fehler in der Berechnung
#endif

// Baud Berechnungen
#define UBRR_VAL ((F_CPU+BAUD*8)/(BAUD*16)-1)   // clever runden
#define BAUD_REAL (F_CPU/(16*(UBRR_VAL+1)))     // Reale Baudrate
#define BAUD_ERROR ((BAUD_REAL*1000)/BAUD) // Fehler in Promille, 1000 = kein Fehler.

#if ((BAUD_ERROR<990) || (BAUD_ERROR>1010))
  #error "Systematischer Fehler der Baudrate groesser 1% und damit zu hoch!"
#endif


//Schnittstelle initialisieren
void uartInit();

//ein Zeichen (char) senden
int uart_putc(unsigned char c);

//eine Zeichenkette senden (char*)
//eine Neue Zeile wird mit dem Zeilenumruch '\n' begonnen. 
//z.B. uart_puts("\r\n");
void uart_puts(char *s);

// Zeichenkette aus Program-Space senden (verbraucht keinen SRAM Speicherplatz fuer die Strings)
// Beispiel: uart_puts_pgm(PSTR("Hello World!\r\n");
void uart_puts_pgm (const char* PROGMEM  str);

//eine 16bit-Zahl ausgeben
void uart_puti(int16_t i);

//ein einzelnes Zeichen empfangen
unsigned char uart_getc();

//Liegt ein Zeichen im Eingangspuffer?
#define uart_data_waiting() (UCSR0A & (1<<RXC0))


// eine Art uart_gets kann man sich noch ausdenken, sollte dann nicht mehr schwer sein

#endif
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
/* 
 *	Basis
 *	2009 Benjamin Reh und Joachim Schleicher
 */
#include <avr/io.h>
#include <inttypes.h>
#include <util/delay.h>
#include "uart.h"
#include "adc.h"
#include "timer.h"
#include "buttons.h"
#include "display.h"


void init();


void full(uint8_t x) {
	page(x,5,0xFF);
	page(x,5+1,0xFf);
	page(x+1,5,0xFF);
	page(x+1,5+1,0xFf);
}
void empty(uint8_t x) {
	page(x,5,0xF0);
	page(x,5+1,0xF0);
	page(x+1,5,0xF0);
	page(x+1,5+1,0xF0);
}

void batteryMeter() {
	uint8_t x=0; 
	uint16_t adc=getADCValue(0);
	uint16_t low=696;//778; // (1024.*34./50.);
	uint16_t high=962; //(1024.*47./50.);
	uint8_t bars = 50 *(adc-low)/(high-low);
	//~ bars=adc/20;
	for(x=0; x< 50; x++)
	{
		if (x < bars) {
			full (x*3);
		} else {
			empty(x*3);
		}
	}
	
}



int main(void)
{
	//Initialisierung ausfuehren
	
	init();

	uart_putc(80);
	_delay_ms(1000);
		
	uart_putc(10);
	_delay_ms(1000);

	
	while (1) {
		//batteryMeter();
		if(B_SELECT)
			delay()
			uart_putc(20);
		if(B_PAUSE)
			uart_putc(30);
		if(B_UP)
			uart_putc(50);
		if(B_DOWN)
			uart_putc(60);
		if(B_RIGHT)
			uart_putc(70);
		if(B_LEFT)
			uart_putc(80);
		if(B_A)
			uart_putc(90);
		if(B_B)
			uart_putc(100);

	}	
}


//INIT
void init()
{
	uartInit();   // serielle Ausgabe an PC
	ADCInit(0);   // Analoge Werte einlesen
	timerInit();  // "Systemzeit" initialisieren
	buttonsInit();
	displayInit();
}
