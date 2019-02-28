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

void updatePlayerPos(int8_t next){

    if(next > 25){
        playerPos = 25;
    } else if (next < 0){
        playerPos = 0;
    } else {
        lastPlayerPos = playerPos;
        playerPos = next;
    }
}

void logic(){
    if(playerPos != 23){
        updatePlayerPos(playerPos + gravity);
    }


}

void full(uint8_t x) {
    page(x, 5, 0xFF);
    page(x, 5 + 1, 0xFf);
    page(x + 1, 5, 0xFF);
    page(x + 1, 5 + 1, 0xFf);
}

void empty(uint8_t x) {
    page(x, 5, 0xF0);
    page(x, 5 + 1, 0xF0);
    page(x + 1, 5, 0xF0);
    page(x + 1, 5 + 1, 0xF0);
}

void batteryMeter() {
    uint8_t x = 0;
    uint16_t adc = getADCValue(0);
    uint16_t low = 696;//778; // (1024.*34./50.);
    uint16_t high = 962; //(1024.*47./50.);
    uint8_t bars = 50 * (adc - low) / (high - low);
    //~ bars=adc/20;
    for (x = 0; x < 50; x++) {
        if (x < bars) {
            full(x * 3);
        } else {
            empty(x * 3);
        }
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

void drawPlayer(uint8_t pos) {

    page(5, pos, 0xFF);
    page(6, pos, 0xFF);
    page(7, pos, 0xFF);
    page(8, pos, 0xFF);
}

void removePlayer(uint8_t pos) {
    page(5, pos, 0);
    page(6, pos, 0);
    page(7, pos, 0);
    page(8, pos, 0);
}


void draw() {
    if (lastPlayerPos != playerPos) {
        removePlayer(lastPlayerPos);
        drawPlayer(playerPos);
    }
    drawPlatforms();
}

void run() {

}

void getInput() {



    if(B_LEFT && B_A){
        _delay_ms(20);
        updatePlayerPos(25);
    }

    if (B_SELECT) {
        //uart_putc(20);
    }
    if (B_PAUSE) {
        //uart_putc(30);
    }

    if (B_UP) {
        _delay_ms(40);
        //uart_putc(50);
        //updatePlayerPos(playerPos -1 );
    }
    if (B_DOWN) {
        _delay_ms(40);
        updatePlayerPos(playerPos + 1);
        //uart_putc(60);
    }
    if (B_RIGHT) {
        //uart_putc(70);
    }
    if (B_LEFT) {

        //uart_putc(80);
    }
    if (B_A) {

        lastPlayerPos = playerPos;
        playerPos = 10;
    }
    //uart_putc(90);
    if (B_B) {

        lastPlayerPos = playerPos;
        playerPos = 23;
    }
    //uart_putc(100);


}


int main(void) {
    //Initialisierung ausfuehren

    init();


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
        getInput();

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
