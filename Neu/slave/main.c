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
const uint8_t allNotesSize = 18;
const struct note allNotes[] = {{C2S},
                                {C3S},
                                {G3S},
                                {C4S},
                                {D4S},
                                {E4S},
                                {F4S},
                                {G4S},
                                {A4S},
                                {B4S},
                                {C5S},
                                {E5S},
                                {F5S},
                                {G5S},
                                {A5S},
                                {B5S},
                                {C6S},
                                {E6S}};

const uint8_t colleSize = 10;
const struct note colle[10] = {{C4, 50},
                               {E3, 50},
                               {C4, 50},
                               {E3, 50},
                               {C4, 50},
                               {E3, 50},
                               {C4, 50},
                               {E3, 50},
                               {C4, 50},
                               {E3, 50}};

const uint8_t powerUpSize = 10;
const struct note powerUp[10] = {{E4, 40},
                                 {C5, 40},
                                 {F4, 40},
                                 {D5, 40},
                                 {A4, 40},
                                 {E5, 40},
                                 {B4, 40},
                                 {F5, 40},
                                 {C5, 40},
                                 {A5, 40}

};
const uint8_t powerDownSize = 10;
const struct note powerDown[10] = {{A5, 40},
                                   {C5, 40},
                                   {F5, 40},
                                   {B4, 40},
                                   {E5, 40},
                                   {A4, 40},
                                   {D5, 40},
                                   {F4, 40},
                                   {C5, 40},
                                   {E4, 40}

};
const uint8_t gameOverSize = 7;
const struct note gameOver[7]={{G4,250},{D4,250},{E4,25}, {D4,25},{E4,25}, {D4,25},{E4,25}, {D4,25},{E4,25}, {D4,25},{E4,25}, {E3,25}

};
void init();

void playNote(struct note ton) {
    uint64_t scale = 100000 / (ton.frequenz * 2);
    uint16_t counter = 0;

    while (scale) {

        for (uint8_t i = 0; i < scale; i++) {
            _delay_ms(1);
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

void playPWM(const struct note musik[], uint8_t length) {
    uint16_t pwm = 0;
    DDRB |= (1 << 1);// Sound-Ausgang einschalten

    for (uint32_t i = 0; i < length; ++i) {
        pwm = 65000 / (musik[i].frequenz * 2);
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
    while (1) {

        playPWM(gameOver, gameOverSize);
        //playPWM(allNotes, allNotesSize);

        _delay_ms(1000);

        switch (d) {
            case '1' :
                //playPWM(test, testSize);
                break;
            case '2':
                break;
            case '3':
                break;
            case '4':
                playPWM(colle, colleSize);
                break;
            case '5':
                playPWM(powerUp, powerUpSize);
                break;
            case '6':
                playPWM(powerDown, powerDownSize);
                break;
            case '7':
                break;
            case '8':
                break;
            default:
                break;


        }
        //playNote(a);
        if (uart_data_waiting())
            d = uart_getc();
    }

    uint16_t counter = 0;

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
