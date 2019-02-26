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
