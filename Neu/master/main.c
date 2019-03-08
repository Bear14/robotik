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
#define JUMP_HEIGHT 8
#define SPEED 1

void init();

volatile int16_t posY = 0;
volatile int16_t posX = 0;

volatile char buttonPressed = '0';
volatile uint32_t timePressed = 0;

int16_t platformX = 0;
int16_t platformY = 12;
uint8_t platformLength = 60;

volatile int16_t playerPosY = 0;
volatile int16_t playerPosX = 0;
volatile int8_t playerMovY = 0;
volatile  int8_t playerMovX = 0;
// Player height is 8!

void drawPlayer() {
    for (int i = 5; i < 5 + 8; i++) {
        drawCorrect(i, 52, 0xFF);
        drawCorrect(i, 56, 0xFF);
    }

};void drawPlayerZero() {
    for (int i = playerPosX; i < playerPosX + 8; i++) {
        drawCorrect(i, playerPosY, 0xFF);
        drawCorrect(i, playerPosY+4, 0xFF);
    }

};

void drawGround(int16_t x,int16_t y,uint8_t length) {

    for (int16_t i = x; i < x + length; i++) {
        drawCorrect(i, y, 0xFF);


    }

}



enum state{ falling,standing,dashing0,jumping,dashing1,doubleJumping,dashing2};
enum state playerState;

void jump() {
    if(playerState == standing){
        playerState = jumping;
        playerMovY = JUMP_HEIGHT;
    } else if(playerState == jumping){
        playerState = doubleJumping;
        playerMovY = JUMP_HEIGHT;
    }


}
int16_t offsetY = 52;
int16_t offsetX = 5;
void update() {

    playerPosX += SPEED;
    offsetX -= SPEED;
    //playerPosY += playerMovY;


    // Collision with ground

    if (playerPosY + 8  <= platformY) {
        playerPosY += GRAVITY;
        offsetY -= GRAVITY;
        //playerPosY += playerMovY;
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
            playerPosY--;
            //}
        }
        if (B_DOWN) {
            //uart_putc(60);
            buttonPressed = '1';
            timePressed = getMsTimer();
            // if (posY < 100) {
            posY++;
            playerPosY++;
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
            jump();
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

    //drawGround(playerPosX,playerPosY,8);
    //drawGround(playerPosX,playerPosY+4,8);
    drawPlayerZero();
    drawGround(platformX,platformY,platformLength);
    drawPlayer();
    //PlayerPosX start value;
    drawGround(platformX + offsetX ,platformY + offsetY,platformLength);

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
