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
#include <avr/interrupt.h>
#include "draw.h"


#define GRAVITY 1;

void init();

volatile int16_t posY = 0;
volatile int16_t posX = 0;

volatile char buttonPressed = '0';
volatile uint32_t timePressed = 0;

int16_t platformX = 0;
int16_t platformY = 100;
uint8_t platformLength = 60;


void drawPlayer() {
    for (int i = 5; i < 5 + 8; i++) {
        drawCorrect(i, 52, 0xFF);
        drawCorrect(i, 56, 0xFF);
    }

};

void drawGround(int16_t x,int16_t y,uint8_t length) {

    for (int16_t i = x; i < x + length; i++) {
        drawCorrect(i, y, 0xFF);


    }

}

volatile int16_t playerPosY = 40;
volatile int16_t playerPosX = 5;

void update() {

    playerPosX++;
    //platformX;


    if (playerPosY >= platformY) {
        playerPosY += GRAVITY;
    }

}


void getInput() {
    if (buttonPressed == '0') {
        if (B_SELECT) {
            //uart_putc(20);
            buttonPressed = '1';
            timePressed = getMsTimer();
        }
        if (B_PAUSE) {

            //uart_putc(30);
            buttonPressed = '1';
            timePressed = getMsTimer();
        }
        if (B_UP) {
            //uart_putc(50);
            buttonPressed = '1';
            timePressed = getMsTimer();
            //if (posY > 0) {
            posY--;
            //}
        }
        if (B_DOWN) {
            //uart_putc(60);
            buttonPressed = '1';
            timePressed = getMsTimer();
            // if (posY < 100) {
            posY++;
            // }
        }
        if (B_RIGHT) {
            //uart_putc(70);
            buttonPressed = '1';
            timePressed = getMsTimer();
            // if (posX < 159) {
            posX++;
            playerPosX++;
            //   }
        }
        if (B_LEFT) {
            //uart_putc(80);
            buttonPressed = '1';
            timePressed = getMsTimer();
            //if (posX > 0) {
            posX--;
            playerPosX--;
            //}
        }

        if (B_A) {
            buttonPressed = '1';
            //uart_putc(90);
            timePressed = getMsTimer();
        }
        if (B_B) {
            buttonPressed = '1';
            //uart_putc(100);
            timePressed = getMsTimer();
        }
    }
}

void draw() {
    drawCorrect(40, 30, 0xC3);
    drawCorrect(posX, posY, 0xC3);

    drawPlayer();
    //PlayerPosX start value;
    drawGround(platformX - (playerPosX-5),platformY - playerPosY,platformLength);

    combineCollidingPages();
    drawFromBuffer(); //HAS TO BE THE LAST CALL IN DRAW()!!!!!!!!
}


int main(void) {
    //Initialisierung ausfuehren

    init();

    uart_putc(80);
    _delay_ms(1000);

    uart_putc(10);
    _delay_ms(1000);

    posX = 40;
    posY = 40;


    while (1) {
/*
 * Set to approx 30 frames per second
 */
        if (getMsTimer() % 34 == 0) {
            update();
            getInput();
            draw();

        }
/*
 * Allow repress of buttons every 150 ms
 */
        if (timePressed + 150 <= getMsTimer()) {
            buttonPressed = '0';
        }
    }
}


//INIT
void init() {
    uartInit();   // serielle Ausgabe an PC
    ADCInit(0);   // Analoge Werte einlesen
    timerInit();  // "Systemzeit" initialisieren
    buttonsInit();
    displayInit();
    bufferInit();
}
