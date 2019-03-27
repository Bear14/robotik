/*
 *	Basis
 *	2009 Benjamin Reh und Joachim Schleicher
 */
#include <avr/io.h>
#include <inttypes.h>
#include <util/delay.h>
#include <stdio.h>
#include "uart.h"
#include "adc.h"
#include "pwm.h"
#include "timer.h"
#include "servo.h"
#include "mynote.h"

struct note {
    uint16_t frequenz;
    uint16_t lenght;
};

const uint8_t winSize = 6;
const struct note win[] = {{E5S},
                           {G5S},
                           {A5S},
                           {C6S},
                           {A5S},
                           {C6V}};
const uint8_t allNotesSize = 22;
const struct note allNotes[] = {{C2S},
                                {C3S},
                                {G3S},
                                {C4S},
                                {D4S},
                                {E4S},
                                {F4S},
                                {FIS4S},
                                {G4S},
                                {GIS4S},
                                {A4S},
                                {H4S},
                                {C5S},
                                {DES5S},
                                {E5S},
                                {F5S},
                                {G5S},
                                {A5S},
                                {H5S},
                                {C6S},
                                {DIS6S},
                                {E6S}};

const uint8_t testSize = 1;
const struct note test[] ={{C4V}};

void init();

void playNote(struct note ton) {
    uint64_t scale = 100000 / (ton.frequenz * 2);
    uint16_t counter = 0;

    while (scale) {

        for (uint8_t i = 0; i < scale; i++) {
            _delay_us(10);
        }

        PORTB ^= (1 << 1);
        counter++;

        if (counter >= ton.lenght) {
            scale = 0;
        }

    }

    PORTB |= (1 << 1);

}

void playMusik(const struct note musik[]) {


    for (uint16_t j = 0; j < 21; ++j) {
        playNote(musik[j]);
    }
}

void playPWM(const struct note musik[],uint8_t length) {
    uint16_t pwm = 0;
    DDRB |= (1 << 1);// Sound-Ausgang einschalten

    for (uint32_t i = 0; i < length; ++i) {
        pwm = 62500 / (musik[i].frequenz * 2);
        setPWM(pwm);
        for (int16_t j = 0; j < musik[i].lenght; ++j) {
            _delay_ms(1);
        }
    }
    DDRB &= (0 << 1);  //Sound-Ausgang ausschalten

}

int main(void) {
    //Initialisierung ausfuehren

    init();

   // DDRB |= (1 << 1); //in Init PWM()
    //PORTB |= (1 << 1);

    uint8_t d = 0;

    //uint16_t counter = 0;
    while (1){

        playPWM(test, testSize);

        //playPWM(allNotes, allNotesSize);

        //_delay_ms(1000);

        //playNote(a);
    }

    uint16_t counter=0;

    while (1) {

        if (d == 0) {
            PORTB |= (1 << 1);
        } else {
            uint8_t i;
            for (i = 0; i < d; i++) {
                _delay_us(10);
            }
            PORTB ^= (1 << 1);
            counter++;
            if (counter > 100) {
                d = 0;
                counter = 0;
            }


        }
        if (uart_data_waiting())
            d = uart_getc();


    }
}


//INIT
void init() {
    uartInit();   // serielle Ausgabe an PC
    ADCInit(0);   // Analoge Werte einlesen
    PWMInit();    // Pulsweite auf B1 ausgeben
    timerInit();  // "Systemzeit" initialisieren
    //servoInit();  // Servoansteuerung initialisieren
}
