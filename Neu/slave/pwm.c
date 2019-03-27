/* 
 *	Basis
 *	2009 Benjamin Reh
 */

#include <avr/io.h>

//Pulsweite initialisieren
void PWMInit()
{
    DDRB |= (1 << 1); //Pin 1 an PORTB auf Ausgang stellen

    TCCR1A = (1 << COM1A0); //CTC Mode wechslenm wenn OCR1A erreicht
    TCCR1B = (1<<CS12) | (1 << WGM12); //PRESCALE 64
    /*
	DDRD |=  (1 << 6); //Pin 6 an PORTD auf Ausgang stellen
	TCCR0A = (1<<WGM00)|(1<<COM0A1); //  Timer/Counter als nicht invertierenden 8-Bit PWM
	TCCR0B = (1<<CS01) | (1<<CS00); //  Takt von CK / 64 generieren
     */
}

//Pulsweite setzen
void setPWM(uint8_t pwmWert)
{
	//Wert in das Register schreiben
	OCR1A = pwmWert;
    TCNT1 = 0;
}
