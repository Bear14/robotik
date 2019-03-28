/*
 *	Basis
 *	2009 Benjamin Reh und Joachim Schleicher
 */
#include <avr/io.h>
#include <inttypes.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <stdio.h>
#include "uart.h"
#include "adc.h"
#include "pwm.h"
#include "timer.h"
#include "servo.h"
#include "mynote.h"
volatile musikOn =0;
volatile uint8_t d = 0;
struct note {
    uint16_t frequenz;
    uint16_t lenght;
};

const uint8_t allNotesSize = 18;
const struct note allNotes[] = {{C2, 4},
                                {C3, 4},
                                {G3, 4},
                                {C4, 4},
                                {D4, 4},
                                {E4, 4},
                                {F4, 4},
                                {G4, 4},
                                {A4, 4},
                                {B4, 4},
                                {C5, 4},
                                {E5, 4},
                                {F5, 4},
                                {G5, 4},
                                {A5, 4},
                                {B5, 4},
                                {C4, 4},
                                {E4, 4}};

const uint8_t dashSize = 7;
const struct note dash[7] = {{C4, 1},
                             {E4, 1},
                             {C5, 1},
                             {E4, 1},
                             {C5, 1},
                             {E4, 1},
                             {C5, 1}};
const uint8_t blub2Size = 3;
const struct note blub2[3] = {{C1, 2},
                              {A1, 2},
                              {C1, 1}};
const uint8_t powerUpSize = 10;
const struct note powerUp[10] = {{E4, 2},
                                 {C5, 2},
                                 {F4, 2},
                                 {D5, 2},
                                 {A4, 2},
                                 {E5, 2},
                                 {B4, 2},
                                 {F5, 2},
                                 {C5, 2},
                                 {A5, 2}

};
const uint8_t powerDownSize = 10;
const struct note powerDown[10] = {{A5, 2},
                                   {C5, 2},
                                   {F5, 2},
                                   {B4, 2},
                                   {E5, 2},
                                   {A4, 2},
                                   {D5, 2},
                                   {F4, 2},
                                   {C5, 2},
                                   {E4, 2}

};
const uint8_t colleSize = 3;
const struct note colle[3] = {{G2, 1},
                              {D2, 1},
                              {C1, 1}};
const uint8_t gameOverSize = 6;
const struct note gameOver[6] = {{G4, 4},
                                 {D4, 4},
                                 {E4, 4},
                                 {G3, 4},
                                 {A3, 4},
                                 {E3, 6}

};
const uint8_t jumpSize = 4;
const struct note jump[4] = {{C3, 1},
                             {G3, 1},
                             {D3, 1},
                             {E4, 1}

};
const uint8_t highscoreSize = 6;
const struct note highscore[6] = {{C5, 2},
                                  {E5, 2},
                                  {G5, 2},
                                  {A5, 2},
                                  {C6, 3},
                                  {A5, 4}
};
const uint8_t musikeSize = 12;
const struct note musik[12] = {{E3, 8},
                               {G3, 8},
                               {D3, 16},
                               {C3, 16},
                               {G3, 16},
                               {E3, 8},
                               {D3, 8},
                               {G3, 16},
                               {E3, 8},
                               {G3, 8},
                               {E3, 8},
                               {D3, 8}};

void init();

/* Alte Version
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
}*/

void playMusik(const struct note effect[], uint8_t length) {
    uint16_t pwm = 0;

    for (uint32_t i = 0; i < length; ++i) {
        pwm = 65000 / (effect[i].frequenz * 2);
        setPWM(pwm);

        if(musikOn ==0){
            break;
        }

        for (int16_t j = 0; j < effect[i].lenght; ++j) {
            _delay_ms(50);
        }
    }
    setPWM(0);

}

void playEffect(const struct note effect[], uint8_t length) {
    uint16_t pwm = 0;

    for (uint32_t i = 0; i < length; ++i) {
        pwm = 65000 / (effect[i].frequenz * 2);
        setPWM(pwm);
        for (int16_t j = 0; j < effect[i].lenght; ++j) {
            _delay_ms(50);
        }
    }
    setPWM(0);

}

ISR ( USART_RX_vect ) {

        d = uart_getc();

        switch (d) {
            case 0:
                musikOn =0;

                break;
            case 1 :
                playEffect(jump, jumpSize);
                d = 0;
                break;
            case 2:
                playEffect(dash, dashSize);
                d = 0;
                break;
            case 3:   //musik
                musikOn = 1;
                break;
            case 4:
                playEffect(colle, colleSize);
                d = 0;
                break;
            case 5:
                playEffect(powerUp, powerUpSize);
                d = 0;
                break;
            case 6:
                playEffect(powerDown, powerDownSize);
                d = 0;
                break;
            case 7:
                playEffect(gameOver, gameOverSize);
                d = 0;
                break;
            case 8:
                playEffect(highscore, highscoreSize);
                d = 0;
                break;
            default:
                break;
        }

}

int main(void) {
    //Initialisierung ausfuehren

    init();

    // DDRB |= (1 << 1); //in Init PWM()
    //PORTB |= (1 << 1);

    setPWM(0);

    //uint16_t counter = 0;
    while (1) {

        if(musikOn){
            playMusik(musik, musikeSize);

        }

        //playPWM(allNotes, allNotesSize);

        //_delay_ms(1000);


        //playNote(a);

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
