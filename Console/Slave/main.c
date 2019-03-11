/*
 *	Basis
 *	2009 Benjamin Reh und Joachim Schleicher
 */
#include <avr/io.h>
#include <inttypes.h>
#include <util/delay.h>
#include "uart.h"
#include "adc.h"
#include "pwm.h"
#include "timer.h"
#include "servo.h"
#include "note.h"
#include "tone.h"

void init();

int main(void)
{
	//Initialisierung ausfuehren

	init();

	DDRB|=(1<<1);
	PORTB|=(1<<1);

	//uint8_t d=0;

	//uint16_t counter=0;
	uint8_t tone_nr =10; // Note A
	uint16_t offset = toneOffset [ tone_nr ];
	uint16_t t ;

	for ( t =0; t < toneLength [ tone_nr ]; t ++) {
		uint8_t pwm = pgm_read_byte (&tones[t+offset]) ;
		setPWM(pwm);// PWM Ausgeben
	}
	/*	if (d==0) {
			PORTB|=(1<<1);
		} else {
			uint8_t i;
			for(i=0; i < d; i++) {
				_delay_us(10);
			}
			PORTB^=(1<<1);
			counter++;
			if (counter > 100) {
				d=0;
				counter=0;
			}

		}
		if (uart_data_waiting())
			d = uart_getc();
	}*/
}


//INIT
void init()
{
	uartInit();   // serielle Ausgabe an PC
	ADCInit(0);   // Analoge Werte einlesen
	PWMInit();    // Pulsweite auf B1 ausgeben
	timerInit();  // "Systemzeit" initialisieren
	//servoInit();  // Servoansteuerung initialisieren
}
