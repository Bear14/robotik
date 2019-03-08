/*
 *	Basis
 *	2009 Benjamin Reh
 */

#include <avr/io.h>

//Pulsweite initialisieren
void PWMInit()
{
	DDRB |=  (1 << 1); //Pin 1 an PORTB auf Ausgang stellen
	TCCR0A = (1<<WGM00)|(WGM01)|(1<<COM0A1); //FastPWM 8-bit nicht invertiert
	TCCR0B = (1<<CS02) | (1<<CS00); //  Takt von CK / 256 generieren
}

//Pulsweite setzen
void setPWM(uint8_t pwmWert)
{
	//Wert in das Register schreiben
	OCR0A = pwmWert;
}
