//
// Created by torben on 11/03/19.
//

#include "sprites.h"
#include "draw.h"

void printPlayer(int16_t x, int16_t y, int16_t lastY) {

    if (y != lastY) {

        drawCorrect(x + 0, lastY + 8, 0);
        drawCorrect(x + 1, lastY + 4, 0);
        drawCorrect(x + 1, lastY + 8, 0);
        drawCorrect(x + 1, lastY + 12, 0);
        drawCorrect(x + 2, lastY + 4, 0);
        drawCorrect(x + 2, lastY + 8, 0);
        drawCorrect(x + 2, lastY + 12, 0);
        drawCorrect(x + 3, lastY + 4, 0);
        drawCorrect(x + 3, lastY + 8, 0);
        drawCorrect(x + 3, lastY + 12, 0);
        drawCorrect(x + 4, lastY + 0, 0);
        drawCorrect(x + 4, lastY + 4, 0);
        drawCorrect(x + 4, lastY + 8, 0);
        drawCorrect(x + 4, lastY + 12, 0);
        drawCorrect(x + 5, lastY + 0, 0);
        drawCorrect(x + 5, lastY + 4, 0);
        drawCorrect(x + 5, lastY + 8, 0);
        drawCorrect(x + 5, lastY + 12, 0);
        drawCorrect(x + 6, lastY + 0, 0);
        drawCorrect(x + 6, lastY + 4, 0);
        drawCorrect(x + 6, lastY + 8, 0);
        drawCorrect(x + 6, lastY + 12, 0);
        drawCorrect(x + 7, lastY + 0, 0);
        drawCorrect(x + 7, lastY + 4, 0);
        drawCorrect(x + 7, lastY + 8, 0);
        drawCorrect(x + 7, lastY + 12, 0);
        drawCorrect(x + 8, lastY + 0, 0);
        drawCorrect(x + 8, lastY + 4, 0);
        drawCorrect(x + 8, lastY + 8, 0);
        drawCorrect(x + 8, lastY + 12, 0);
        drawCorrect(x + 9, lastY + 4, 0);
        drawCorrect(x + 9, lastY + 8, 0);
        drawCorrect(x + 9, lastY + 12, 0);
        drawCorrect(x + 10, lastY + 0, 0);
        drawCorrect(x + 10, lastY + 4, 0);
        drawCorrect(x + 10, lastY + 8, 0);
        drawCorrect(x + 11, lastY + 0, 0);
        drawCorrect(x + 11, lastY + 4, 0);
        drawCorrect(x + 11, lastY + 8, 0);
        drawCorrect(x + 11, lastY + 12, 0);
        drawCorrect(x + 12, lastY + 0, 0);
        drawCorrect(x + 12, lastY + 4, 0);
        drawCorrect(x + 12, lastY + 8, 0);
        drawCorrect(x + 12, lastY + 12, 0);
        drawCorrect(x + 13, lastY + 0, 0);
        drawCorrect(x + 13, lastY + 4, 0);
        drawCorrect(x + 13, lastY + 8, 0);
        drawCorrect(x + 13, lastY + 12, 0);
        drawCorrect(x + 14, lastY + 0, 0);
        drawCorrect(x + 14, lastY + 4, 0);
        drawCorrect(x + 14, lastY + 8, 0);
        drawCorrect(x + 14, lastY + 12, 0);
        drawCorrect(x + 15, lastY + 0, 0);
        drawCorrect(x + 15, lastY + 4, 0);
        drawCorrect(x + 15, lastY + 8, 0);
        drawCorrect(x + 15, lastY + 12, 0);

        drawCorrect(x + 0, y + 8, 0x02);
        drawCorrect(x + 1, y + 4, 0xF0);
        drawCorrect(x + 1, y + 8, 0x0B);
        drawCorrect(x + 1, y + 12, 0x02);
        drawCorrect(x + 2, y + 4, 0xFC);
        drawCorrect(x + 2, y + 8, 0xBF);
        drawCorrect(x + 2, y + 12, 0xF0);
        drawCorrect(x + 3, y + 4, 0x3F);
        drawCorrect(x + 3, y + 8, 0xA0);
        drawCorrect(x + 3, y + 12, 0xFD);
        drawCorrect(x + 4, y + 0, 0x03);
        drawCorrect(x + 4, y + 4, 0xFF);
        drawCorrect(x + 4, y + 8, 0x7B);
        drawCorrect(x + 4, y + 12, 0x35);
        drawCorrect(x + 5, y + 0, 0xFF);
        drawCorrect(x + 5, y + 4, 0xFA);
        drawCorrect(x + 5, y + 8, 0xFF);
        drawCorrect(x + 5, y + 12, 0x15);
        drawCorrect(x + 6, y + 0, 0xFF);
        drawCorrect(x + 6, y + 4, 0xA7);
        drawCorrect(x + 6, y + 8, 0xFE);
        drawCorrect(x + 6, y + 12, 0x54);
        drawCorrect(x + 7, y + 0, 0xDF);
        drawCorrect(x + 7, y + 4, 0x57);
        drawCorrect(x + 7, y + 8, 0xFE);
        drawCorrect(x + 7, y + 12, 0x53);
        drawCorrect(x + 8, y + 0, 0x5C);
        drawCorrect(x + 8, y + 4, 0x57);
        drawCorrect(x + 8, y + 8, 0xFD);
        drawCorrect(x + 8, y + 12, 0xFF);
        drawCorrect(x + 9, y + 4, 0xFF);
        drawCorrect(x + 9, y + 8, 0x03);
        drawCorrect(x + 9, y + 12, 0xFF);
        drawCorrect(x + 10, y + 0, 0xC0);
        drawCorrect(x + 10, y + 4, 0xFF);
        drawCorrect(x + 10, y + 8, 0xFF);
        drawCorrect(x + 11, y + 0, 0xF0);
        drawCorrect(x + 11, y + 4, 0xAA);
        drawCorrect(x + 11, y + 8, 0xAA);
        drawCorrect(x + 11, y + 12, 0x03);
        drawCorrect(x + 12, y + 0, 0xAC);
        drawCorrect(x + 12, y + 4, 0x55);
        drawCorrect(x + 12, y + 8, 0x95);
        drawCorrect(x + 12, y + 12, 0x0E);
        drawCorrect(x + 13, y + 0, 0x6C);
        drawCorrect(x + 13, y + 4, 0x75);
        drawCorrect(x + 13, y + 8, 0x55);
        drawCorrect(x + 13, y + 12, 0x0E);
        drawCorrect(x + 14, y + 0, 0x6C);
        drawCorrect(x + 14, y + 4, 0xFD);
        drawCorrect(x + 14, y + 8, 0x5F);
        drawCorrect(x + 14, y + 12, 0x0E);
        drawCorrect(x + 15, y + 0, 0xF0);
        drawCorrect(x + 15, y + 4, 0xFF);
        drawCorrect(x + 15, y + 8, 0xFF);
        drawCorrect(x + 15, y + 12, 0x03);


    }
}

void printHeart(int16_t x, int16_t y) {
    drawCorrect(x + 0, y + 0, 0xFC);

    drawCorrect(x + 1, y + 0, 0xFF);
    drawCorrect(x + 1, y + 4, 0x03);
    drawCorrect(x + 2, y + 0, 0xFF);
    drawCorrect(x + 2, y + 4, 0x0F);
    drawCorrect(x + 3, y + 0, 0xFC);
    drawCorrect(x + 3, y + 4, 0x3F);
    drawCorrect(x + 4, y + 0, 0xF0);
    drawCorrect(x + 4, y + 4, 0xFF);
    drawCorrect(x + 5, y + 0, 0xFC);
    drawCorrect(x + 5, y + 4, 0x3F);
    drawCorrect(x + 6, y + 0, 0xFF);
    drawCorrect(x + 6, y + 4, 0x0F);
    drawCorrect(x + 7, y + 0, 0xFF);
    drawCorrect(x + 7, y + 4, 0x03);
    drawCorrect(x + 8, y + 0, 0xFC);
}

void printPlatform(int16_t x, int16_t y) {
    drawCorrect(x + 0, y + 0, 0xFF);
    drawCorrect(x + 0, y + 4, 0x56);
    drawCorrect(x + 1, y + 0, 0xBF);
    drawCorrect(x + 1, y + 4, 0x56);
    drawCorrect(x + 2, y + 0, 0xAF);
    drawCorrect(x + 2, y + 4, 0x55);
    drawCorrect(x + 3, y + 0, 0x6F);
    drawCorrect(x + 3, y + 4, 0x55);
    drawCorrect(x + 4, y + 0, 0xAF);
    drawCorrect(x + 4, y + 4, 0x55);
    drawCorrect(x + 5, y + 0, 0xBF);
    drawCorrect(x + 5, y + 4, 0x56);
    drawCorrect(x + 6, y + 0, 0xFF);
    drawCorrect(x + 6, y + 4, 0x6A);
    drawCorrect(x + 7, y + 0, 0xFF);
    drawCorrect(x + 7, y + 4, 0x6F);
    drawCorrect(x + 8, y + 0, 0xFF);
    drawCorrect(x + 8, y + 4, 0x6B);
    drawCorrect(x + 9, y + 0, 0xFF);
    drawCorrect(x + 9, y + 4, 0x5A);
    drawCorrect(x + 10, y + 0, 0xBF);
    drawCorrect(x + 10, y + 4, 0x56);
    drawCorrect(x + 11, y + 0, 0xAF);
    drawCorrect(x + 11, y + 4, 0x55);
    drawCorrect(x + 12, y + 0, 0x6F);
    drawCorrect(x + 12, y + 4, 0x55);
    drawCorrect(x + 13, y + 0, 0xAF);
    drawCorrect(x + 13, y + 4, 0x55);
    drawCorrect(x + 14, y + 0, 0xBF);
    drawCorrect(x + 14, y + 4, 0x56);
}

void printPowerUp(int16_t x, int16_t y,enum PowerUpType type,int16_t speed){

    for(int i = 0; i < speed; i++){
        drawCorrect(x+8+i,y,0);
        drawCorrect(x+8+i,y+4,0);


    }



    drawCorrect(x+0,y+0,0x3C);
    drawCorrect(x+0,y+4,0x3F);
    drawCorrect(x+1,y+0,0x08);
    drawCorrect(x+1,y+4,0x57);
    drawCorrect(x+2,y+0,0x0A);
    drawCorrect(x+2,y+4,0x57);
    drawCorrect(x+3,y+0,0x0A);
    drawCorrect(x+3,y+4,0x57);
    drawCorrect(x+4,y+0,0x0A);
    drawCorrect(x+4,y+4,0x5B);
    drawCorrect(x+5,y+0,0xEA);
    drawCorrect(x+5,y+4,0x57);
    drawCorrect(x+6,y+0,0xC2);
    drawCorrect(x+6,y+4,0x03);
    drawCorrect(x+7,y+0,0x02);
}
void clearPowerUp(int16_t x , int16_t y,int16_t speed){
    for(int i = 0; i < speed; i++){
        drawCorrect(x+8+i,y,0);
        drawCorrect(x+8+i,y+4,0);


    }

    drawCorrect(x+0,y+0,0);
    drawCorrect(x+0,y+4,0);
    drawCorrect(x+1,y+0,0);
    drawCorrect(x+1,y+4,0);
    drawCorrect(x+2,y+0,0);
    drawCorrect(x+2,y+4,0);
    drawCorrect(x+3,y+0,0);
    drawCorrect(x+3,y+4,0);
    drawCorrect(x+4,y+0,0);
    drawCorrect(x+4,y+4,0);
    drawCorrect(x+5,y+0,0);
    drawCorrect(x+5,y+4,0);
    drawCorrect(x+6,y+0,0);
    drawCorrect(x+6,y+4,0);
    drawCorrect(x+7,y+0,0);

}