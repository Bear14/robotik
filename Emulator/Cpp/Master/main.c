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

int counter = 0;

uint32_t getMsTimer(){
    counter++;
    return counter;
}

void _delay_ms(int ms) {
    std::this_thread::sleep_for(std::chrono::milliseconds(ms));
}

#define DASHLENGTH 6
#define JUMPHEIGHT -8
#define GRAVITY 1
#define SPEED 3

enum state{ falling,standing,dashing0,jumping,dashing1,doubleJumping,dashing2};


int16_t cloudX = 150;
int16_t cloudY = 52;
int16_t cloudLen = 20;
int16_t lastCloudX = 150;
int16_t lastCloudY = 52;

int16_t playerPos = 52; //change to 0 - 103
int16_t lastPlayerPos = 52;
//float gravity = 1;
//int32_t speed = 1;


uint16_t groundPos = 100;

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
    /*
    if(cloudY + playerMov >= groundPos){
        cloudY = groundPos -4;
        playerState = standing;
    } else if(cloudX - playerMov <= 0){
        cloudY = 0 + 4;
        playerState = standing;
    }
*/


    if(playerPos + playerMov >= groundPos || playerPos <= 0){
        playerPos = groundPos -4;
        playerState = standing;
        // playerPos = groundPos +4;
    }
}

void drawCloud() {

    for (int i = lastCloudX; i < (lastCloudX + cloudLen); i++) {
        page(i, lastCloudY / 4, 0);
    }

    for (int i = cloudX; i < (cloudX + cloudLen); i++) {
        page(i, cloudY / 4, 0xFF);    //85
    }
}


void updatePlayerPos() {

    if(playerState == standing){

    } else if(playerState == jumping || playerState == doubleJumping || playerState == falling){

        lastPlayerPos = playerPos;
        playerMov += GRAVITY;
        //playerPos += playerMov;

        // move everything in y direction
        lastCloudY = cloudY;
        cloudY -= playerMov;
        if(cloudY <= 0){
            lastCloudY = cloudY;
            cloudY = 255;
            playerState = standing;
        }


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
    lastCloudX = cloudX;
    //lastCloudY = cloudY;
    //cloudY -= playerMov;
    cloudX -= SPEED;
    if(cloudX <= 0){
        lastCloudX = cloudX;
        cloudX = 255;
        playerState = standing;
    }/*
    if(cloudY <= 0){
        lastCloudY = cloudY;
        cloudY = 255;
        playerState = standing;
    }*/
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

        int8_t last = lastPos /4;
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

        int8_t nex = playerPos / 4;

        if (pos % 4 == 0) {

            page(5, nex, 0xFF);
            page(6, nex, 0xFF);
            page(7, nex, 0xFF);
            page(8, nex, 0xFF);


        } else if (pos % 4 == 1) {

            page(5, nex, 0xFC);
            page(6, nex, 0xFC);
            page(7, nex, 0xFC);
            page(8, nex, 0xFC);
            page(5, nex + 1, 0x3);
            page(6, nex + 1, 0x3);
            page(7, nex + 1, 0x3);
            page(8, nex + 1, 0x3);

        } else if (pos % 4 == 2) {

            page(5, nex, 0xF0);
            page(6, nex, 0xF0);
            page(7, nex, 0xF0);
            page(8, nex, 0xF0);
            page(5, nex + 1, 0xF);
            page(6, nex + 1, 0xF);
            page(7, nex + 1, 0xF);
            page(8, nex + 1, 0xF);


        } else if (pos % 4 == 3) {

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
void update() {

    if(getMsTimer() % 34 == 0) {
        updateCloud();
        updatePlayerPos();
        draw();
    }


}

int main(void) {

    //init();

    playerState = standing;

    while (1) {
        getInput();
        collision();
        update();
        //draw();


    }
}




