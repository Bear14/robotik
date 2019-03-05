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

#define DASHLENGTH 6
#define JUMPHEIGHT -8
#define GRAVITY 1

enum state{ falling,standing,dashing0,jumping,dashing1,doubleJumping,dashing2};


int8_t cloudX = 150;
int8_t cloudY = 52;
int8_t cloudLen = 20;
int8_t lastCloudX = 150;
int8_t lastCloudY = 52;

int8_t playerPos = 52; //change to 0 - 103
int8_t lastPlayerPos = 52;
//float gravity = 1;
int32_t speed = 1;


uint8_t groundPos = 100;

enum state playerState;

char inJump = '0';
char inDoubleJump = '0';
int8_t playerMov = 0;
char b_pressed = '0';
int32_t b_time = 0;

int8_t dashing;


void init();

void jump() {

    if(playerState == standing || playerState == dashing0){
        playerState = jumping;
        playerMov = JUMPHEIGHT;
    }
    else if(playerState == jumping || playerState == dashing1){
        playerState = doubleJumping;
        playerMov = JUMPHEIGHT;
    }
    else if(playerState == doubleJumping || playerState == dashing2){
        playerState = falling;
    }
    else if(playerState == falling){

    }

}

void dash() {
    if(playerState == standing){
        playerState = dashing0;
        dashing = DASHLENGTH;
    }
    else if(playerState == jumping){
        playerState = dashing1;
        dashing = DASHLENGTH;
    }
    else if(playerState == doubleJumping){
        playerState = dashing2;
        dashing = DASHLENGTH;
    } else{

    }

}

void collision() {
    if(playerPos + playerMov >= groundPos || playerPos <= 0){
        playerPos = groundPos -4;
        playerState = standing;
       // playerPos = groundPos +4;
    }
}

void drawCloud() {

    for (int i = cloudX; i < (cloudX + cloudLen); i++) {
        page(i, cloudY / 4, 85);
    }
    page(cloudX + cloudLen + 1, cloudY / 4, 0);
}

void updatePlayerPos() {

    if(playerState == standing){

    } else if(playerState == jumping || playerState == doubleJumping || playerState == falling){

        lastPlayerPos = playerPos;
        playerMov += GRAVITY;
        playerPos += playerMov;


    }
    if(dashing > 0 && (playerState == dashing0 || playerState == dashing1 || playerState == dashing2)){
        dashing--;
    } else if(dashing == 0 && playerState == dashing0){
        playerState = jumping;
    } else if(dashing == 0 && playerState == dashing1){
        playerState = doubleJumping;
    } else if (dashing == 0 && playerState == dashing2){
        playerState = falling;
    }

}



void updateCloud() {
    cloudX -= speed;
}

void update() {

    if(getMsTimer() % 14 == 0) {
        updateCloud();
        updatePlayerPos();

    }


}



void pageTest() {

    for (int i = 0; i < 256; ++i) {
        page(100, 10, i);

        page(102, 10, i);

        page(104, 10, i);

        page(106, 10, i);
        _delay_ms(200);

    }

}


void drawRect(int8_t pos,int8_t lastPos) {
    if(pos == lastPos){

    }
    else {

        //clear

        uint8_t last = lastPos /4;
        page(5,last-1,0);
        page(6,last-1,0);
        page(7,last-1,0);
        page(8,last-1,0);
        page(5,last,0);
        page(6,last,0);
        page(7,last,0);
        page(8,last,0);
        page(5,last+1,0);
        page(6,last+1,0);
        page(7,last+1,0);
        page(8,last+1,0);


        if (pos % 4 == 0) {
            uint8_t nex = playerPos / 4;

   //         clearPlayerColumn();

            //draw
            page(5, nex, 0xFF);
            page(6, nex, 0xFF);
            page(7, nex, 0xFF);
            page(8, nex, 0xFF);


        } else if (pos % 4 == 1) {
            uint8_t nex = playerPos / 4;
   //         clearPlayerColumn();
            //draw
            page(5, nex, 0xFC);
            page(6, nex, 0xFC);
            page(7, nex, 0xFC);
            page(8, nex, 0xFC);
            page(5, nex + 1, 0x3);
            page(6, nex + 1, 0x3);
            page(7, nex + 1, 0x3);
            page(8, nex + 1, 0x3);

        } else if (pos % 4 == 2) {
            uint8_t nex = playerPos / 4;

   //         clearPlayerColumn();
            //draw
            page(5, nex, 0xF0);
            page(6, nex, 0xF0);
            page(7, nex, 0xF0);
            page(8, nex, 0xF0);
            page(5, nex + 1, 0xF);
            page(6, nex + 1, 0xF);
            page(7, nex + 1, 0xF);
            page(8, nex + 1, 0xF);


        } else if (pos % 4 == 3) {
            uint8_t nex = playerPos / 4;


            //draw
            page(5, nex, 0xC0);
            page(6, nex, 0xC0);
            page(7, nex, 0xC0);
            page(8, nex, 0xC0);
            page(5, nex + 1, 0x3F);
            page(6, nex + 1, 0x3F);
            page(7, nex + 1, 0x3F);
            page(8, nex + 1, 0x3F);

        }
    }

}


void draw() {
    drawRect(playerPos,lastPlayerPos);
    drawCloud();
}



void getInput() {

    if(b_time + 40 == getMsTimer()){
        b_pressed = '0';
    }

        if (B_SELECT) {
            //uart_putc(20);
        }
        if (B_PAUSE) {
            //uart_putc(30);
        }

        if (B_UP) {
            if (b_pressed == '0') {
                b_pressed = '1';
                b_time = getMsTimer();
            }
            lastPlayerPos--;
            playerPos--;
            //uart_putc(50);
            //updatePlayerPos(playerPos -1 );
        }
        if (B_DOWN) {
            if (b_pressed == '0') {
                b_pressed = '1';
                b_time = getMsTimer();
            }
            lastPlayerPos++;
            playerPos++;
            //updatePlayerPos(playerPos + 1);
            //uart_putc(60);
        }
        if (B_RIGHT) {
            if (b_pressed == '0') {
                b_pressed = '1';
                b_time = getMsTimer();
            }
            playerState = standing;
            //uart_putc(70);
        }
        if (B_LEFT) {
            if (b_pressed == '0') {
                b_pressed = '1';
                b_time = getMsTimer();
            }
            //uart_putc(80);
        }
        if (B_A) {
            if (b_pressed == '0') {
                b_pressed = '1';
                b_time = getMsTimer();
            }
            dash();
            uart_putc(90);
        }
        //
        if (B_B) {
            if (b_pressed == '0') {
                b_pressed = '1';
                b_time = getMsTimer();
            }
            jump();
            uart_putc(100);
        }
        //uart_putc(100);


}


int main(void) {

    init();

    playerState = standing;

    while (1) {
        getInput();
        collision();
        update();
        draw();


    }
}


//INIT
void init() {
    uartInit();   // serielle Ausgabe an PC
    ADCInit(0);   // Analoge Werte einlesen
    timerInit();  // "Systemzeit" initialisieren
    buttonsInit();
    displayInit();
}
