/*
 *	Basis
 *	2009 Benjamin Reh
 */

#include <avr/io.h>

//Pulsweite initialisieren
void PWMInit()
{
	DDRB |=  (1 << 1); //Pin B1  auf Ausgang stellen
	//FastPWM 8-bit nicht invertiert, troggle Toggle OC0A on Compare Match
	TCCR0A = (1<<WGM00)|(1<<WGM01)|(1<<COM0A0)|(1<<WGM02);
	TCCR0B = (1<<CS02); //  Takt von CK / 256 generieren


}

//Pulsweite setzen
void setPWM(uint8_t pwmWert)
{
	//Wert in das Register schreiben
	OCR0A = pwmWert;
}
