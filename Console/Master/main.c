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

<<<<<<< HEAD
struct platform{
    uint8_t posY;
    uint8_t posX;
    uint8_t length;
};

uint8_t playerPos = 23;
uint8_t lastPlayerPos = 0;
float gravity = 1;
uint32_t speed = 1;

uint8_t groundPos = 24;

struct platform platforms[10];
uint8_t platformCount = 0;



void addPlatform(uint8_t x,uint8_t y,uint8_t l){
    struct platform p;
    p.posX = x;
    p.posY = y;
    p.length = l;
    platforms[platformCount] = p;   //search free spot
    platformCount++;
}

void drawPlatforms(){

    for(int i = 0; i < 10; i++){
        if(platforms[i].posX){
            for(int x = platforms[i].posX; x < ( platforms[i].posX + platforms[i].length);x++){
                page(x,platforms[i].posY,0xFF);
            }
        }
    }

};
=======
#define DASHLENGTH 6
#define JUMPHEIGHT -5
#define GRAVITY 1

enum state{ falling,standing,dashing0,jumping,dashing1,doubleJumping,dashing2};
>>>>>>> d05c97e1d33b5cad72afc5013441e470fcdb7862


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
int8_t playerMov = 0;

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

<<<<<<< HEAD
void logic(){
    if(playerPos != 23){
        updatePlayerPos(playerPos + gravity);
    }


}
=======
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
>>>>>>> d05c97e1d33b5cad72afc5013441e470fcdb7862

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

<<<<<<< HEAD
=======
void update() {
    if (dashing > 0) {
        speed *= 2;
    } else {
        speed = 1;
    }
    updateCloud();
    updatePlayerPos();

}


>>>>>>> d05c97e1d33b5cad72afc5013441e470fcdb7862

void pageTest() {

    for (int i = 0; i < 256; ++i) {
        page(100, 10, i);

        page(102, 10, i);

        page(104, 10, i);

        page(106, 10, i);
        _delay_ms(200);

    }

}

<<<<<<< HEAD
void drawPlayer(uint8_t pos) {

    page(5, pos, 0xFF);
    page(6, pos, 0xFF);
    page(7, pos, 0xFF);
    page(8, pos, 0xFF);
}
=======

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
>>>>>>> d05c97e1d33b5cad72afc5013441e470fcdb7862

}


void draw() {
<<<<<<< HEAD
    if (lastPlayerPos != playerPos) {
        removePlayer(lastPlayerPos);
        drawPlayer(playerPos);
    }
    drawPlatforms();
=======
    drawRect(playerPos,lastPlayerPos);
    //drawCloud();
>>>>>>> d05c97e1d33b5cad72afc5013441e470fcdb7862
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

    init();

<<<<<<< HEAD

    uart_putc(80);
    _delay_ms(1000);

    uart_putc(10);
    _delay_ms(1000);

    addPlatform(100,20,40);
    addPlatform(20,10,100);

    while (1) {
        batteryMeter();
        //pageTest();
        draw();
        logic();
=======
    playerState = standing;

    while (1) {
>>>>>>> d05c97e1d33b5cad72afc5013441e470fcdb7862
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
