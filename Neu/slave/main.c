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
#include "note.h"

struct note {
    uint16_t frequenz;
    uint16_t lenght;
};

const struct note win[] = {{E5S},{G5S},{A5S},{C6S},{A5S},{C6V}};
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

void init();

void playNote(struct note ton) {
    uint64_t scale = 100000 / (ton.frequenz * 2);
    uint16_t counter = 0;

    while (scale) {

        for (uint8_t i = 0; i < scale; i++) {
            _delay_us(7);
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

    for (uint16_t j = 0; j < 6; ++j) {
        playNote(musik[j]);
    }
}

int main(void) {
    //Initialisierung ausfuehren

    init();

    DDRB |= (1 << 1); //in Init PWM()
    PORTB |= (1 << 1);

    uint8_t d = 0;

    //uint16_t counter = 0;



    while (1) {
        playNote((struct note){E6V});
        //playNote((struct note){E5V});
        /*
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


        }*/
        if (uart_data_waiting())
            d = uart_getc();


    }
}


//INIT
void init() {
    uartInit();   // serielle Ausgabe an PC
    ADCInit(0);   // Analoge Werte einlesen
    //PWMInit();    // Pulsweite auf B1 ausgeben
    timerInit();  // "Systemzeit" initialisieren
    //servoInit();  // Servoansteuerung initialisieren
}
