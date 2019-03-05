/* 
 *	Basis
 *	2009 Benjamin Reh und Joachim Schleicher
 */
//#include <avr/io.h>
#include <inttypes.h>
//#include <util/delay.h>
#include "uart.c"
#include "adc.c"
//#include "timer.h"
#include "buttons.h"
#include "display.c"
#include <stdio.h>
#include <iostream>

#include "socket.cpp"


void _delay_ms(int ms) {
    std::this_thread::sleep_for(std::chrono::milliseconds(ms));
}

#define DASHLENGTH 6
#define JUMPHEIGHT -5
#define GRAVITY 1

enum state{ falling,standing,dashing0,jumping,dashing1,doubleJumping,dashing2};


uint8_t cloudX = 150;
uint8_t cloudY = 52;
uint8_t cloudLen = 20;
uint8_t lastCloudX = 150;
uint8_t lastCloudY = 52;

int8_t playerPos = 52; //change to 0 - 103
int8_t lastPlayerPos = 56;
//float gravity = 1;
uint32_t speed = 1;

uint8_t groundPos = 100;

enum state playerState;

char inJump = '0';
char inDoubleJump = '0';
double playerMov = 0;

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
        playerPos = groundPos - 4;
        playerState = standing;
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
        std::cout << "<-" << (int)playerPos << "\n";

    } else if(playerState == jumping || playerState == doubleJumping){

        lastPlayerPos = playerPos;
        playerMov += GRAVITY;
        playerPos += playerMov;


    } else if(playerState == falling){
        lastPlayerPos = playerPos;
        playerPos += GRAVITY;
        std::cout << "->" << (int) playerPos  << (int) playerPos + GRAVITY<< "\n";
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

/*
    lastPlayerPos = playerPos;
    if (dashing > 0) {

        dashing--;


    } else {


        if (inJump == '1') {
            playerMov -= gravity;
            playerPos -= playerMov;
        } else if (inJump == '0') {

        }
    }

*/
}



void updateCloud() {
    cloudX -= speed;
}

void update() {
    if (dashing > 0) {
        speed *= 2;
    } else {
        speed = 1;
    }
    updateCloud();
    updatePlayerPos();

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


void drawRect(uint8_t pos,uint8_t lastPos) {
    if(pos == lastPos){

    }
    else {

        if (pos % 4 == 0) {
            uint8_t nex = playerPos / 4;

            page(5, nex - 2, 0);
            page(6, nex - 2, 0);
            page(7, nex - 2, 0);
            page(8, nex - 2, 0);
            page(5, nex - 1, 0);
            page(6, nex - 1, 0);
            page(7, nex - 1, 0);
            page(8, nex - 1, 0);
            page(5, nex + 1, 0);
            page(6, nex + 1, 0);
            page(7, nex + 1, 0);
            page(8, nex + 1, 0);

            //         clearPlayerColumn();

            //draw
            page(5, nex, 0xFF);
            page(6, nex, 0xFF);
            page(7, nex, 0xFF);
            page(8, nex, 0xFF);


        } else if (pos % 4 == 1) {
            uint8_t nex = playerPos / 4;

            page(5, nex - 2, 0);
            page(6, nex - 2, 0);
            page(7, nex - 2, 0);
            page(8, nex - 2, 0);
            page(5, nex, 0);
            page(6, nex, 0);
            page(7, nex, 0);
            page(8, nex, 0);
            page(5, nex + 1, 0);
            page(6, nex + 1, 0);
            page(7, nex + 1, 0);
            page(8, nex + 1, 0);


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


            page(5, nex - 2, 0);
            page(6, nex - 2, 0);
            page(7, nex - 2, 0);
            page(8, nex - 2, 0);
            page(5, nex, 0);
            page(6, nex, 0);
            page(7, nex, 0);
            page(8, nex, 0);
            page(5, nex + 1, 0);
            page(6, nex + 1, 0);
            page(7, nex + 1, 0);
            page(8, nex + 1, 0);

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


            page(5, nex - 2, 0);
            page(6, nex - 2, 0);
            page(7, nex - 2, 0);
            page(8, nex - 2, 0);
            page(5, nex, 0);
            page(6, nex, 0);
            page(7, nex, 0);
            page(8, nex, 0);
            page(5, nex + 1, 0);
            page(6, nex + 1, 0);
            page(7, nex + 1, 0);
            page(8, nex + 1, 0);

            //clearPlayerColumn();

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

    if (B_SELECT) {
        //uart_putc(20);
    }
    if (B_PAUSE) {
        //uart_putc(30);
    }

    if (B_UP) {
        _delay_ms(40);
        lastPlayerPos--;
        playerPos--;
        //uart_putc(50);
        //updatePlayerPos(playerPos -1 );
    }
    if (B_DOWN) {
        _delay_ms(40);
        lastPlayerPos++;
        playerPos++;
        //updatePlayerPos(playerPos + 1);
        //uart_putc(60);
    }
    if (B_RIGHT) {
        _delay_ms(40);
        playerState = standing;
        //uart_putc(70);
    }
    if (B_LEFT) {

        //uart_putc(80);
    }
    if (B_A) {
        _delay_ms(40);
        dash();
        uart_putc(90);
    }
    //
    if (B_B) {
        _delay_ms(40);
        jump();
        uart_putc(100);
    }
    //uart_putc(100);


}


int main(void) {

    //init();

    int count = 0;

    playerState = standing;

    while (1) {
        //getInput();
        collision();
        update();
        draw();
        count++;
        if(count == 10){
            //playerState = falling;
            jump();
        }
        if(count == 20){
            jump();
        }
        std::cout << (int) playerState << "\n";

    }
}




