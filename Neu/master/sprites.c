//
// Created by torben on 11/03/19.
//

#include <stdlib.h>
#include <avr/interrupt.h>
#include "sprites.h"
#include "draw.h"
#include "platform.h"

void clearPlayer(int16_t x, int16_t y) {

    drawCorrect(x + 0, y + 0, 0);
    drawCorrect(x + 0, y + 4, 0);
    drawCorrect(x + 0, y + 8, 0);
    drawCorrect(x + 0, y + 12, 0);
    drawCorrect(x + 1, y + 0, 0);
    drawCorrect(x + 1, y + 4, 0);
    drawCorrect(x + 1, y + 8, 0);
    drawCorrect(x + 1, y + 12, 0);
    drawCorrect(x + 2, y + 0, 0);
    drawCorrect(x + 2, y + 4, 0);
    drawCorrect(x + 2, y + 8, 0);
    drawCorrect(x + 2, y + 12, 0);
    drawCorrect(x + 3, y + 0, 0);
    drawCorrect(x + 3, y + 4, 0);
    drawCorrect(x + 3, y + 8, 0);
    drawCorrect(x + 3, y + 12, 0);
    drawCorrect(x + 4, y + 0, 0);
    drawCorrect(x + 4, y + 4, 0);
    drawCorrect(x + 4, y + 8, 0);
    drawCorrect(x + 4, y + 12, 0);
    drawCorrect(x + 5, y + 0, 0);
    drawCorrect(x + 5, y + 4, 0);
    drawCorrect(x + 5, y + 8, 0);
    drawCorrect(x + 5, y + 12, 0);
    drawCorrect(x + 6, y + 0, 0);
    drawCorrect(x + 6, y + 4, 0);
    drawCorrect(x + 6, y + 8, 0);
    drawCorrect(x + 6, y + 12, 0);
    drawCorrect(x + 7, y + 0, 0);
    drawCorrect(x + 7, y + 4, 0);
    drawCorrect(x + 7, y + 8, 0);
    drawCorrect(x + 7, y + 12, 0);
    drawCorrect(x + 8, y + 0, 0);
    drawCorrect(x + 8, y + 4, 0);
    drawCorrect(x + 8, y + 8, 0);
    drawCorrect(x + 8, y + 12, 0);
    drawCorrect(x + 9, y + 0, 0);
    drawCorrect(x + 9, y + 4, 0);
    drawCorrect(x + 9, y + 8, 0);
    drawCorrect(x + 9, y + 12, 0);
    drawCorrect(x + 10, y + 0, 0);
    drawCorrect(x + 10, y + 4, 0);
    drawCorrect(x + 10, y + 8, 0);
    drawCorrect(x + 10, y + 12, 0);
    drawCorrect(x + 11, y + 0, 0);
    drawCorrect(x + 11, y + 4, 0);
    drawCorrect(x + 11, y + 8, 0);
    drawCorrect(x + 11, y + 12, 0);
    drawCorrect(x + 12, y + 0, 0);
    drawCorrect(x + 12, y + 4, 0);
    drawCorrect(x + 12, y + 8, 0);
    drawCorrect(x + 12, y + 12, 0);
    drawCorrect(x + 13, y + 0, 0);
    drawCorrect(x + 13, y + 4, 0);
    drawCorrect(x + 13, y + 8, 0);
    drawCorrect(x + 13, y + 12, 0);
    drawCorrect(x + 14, y + 0, 0);
    drawCorrect(x + 14, y + 4, 0);
    drawCorrect(x + 14, y + 8, 0);
    drawCorrect(x + 14, y + 12, 0);
    drawCorrect(x + 15, y + 0, 0);
    drawCorrect(x + 15, y + 4, 0);
    drawCorrect(x + 15, y + 8, 0);
    drawCorrect(x + 15, y + 12, 0);


}

void drawPlaceHolder(int16_t x, int16_t y) {

    drawCorrect(x + 0, y + 0, 0xFF);
    drawCorrect(x + 0, y + 4, 0xFF);
    drawCorrect(x + 0, y + 8, 0xFF);
    drawCorrect(x + 0, y + 12, 0xFF);
    drawCorrect(x + 1, y + 0, 0xFF);
    drawCorrect(x + 1, y + 4, 0xFF);
    drawCorrect(x + 1, y + 8, 0xFF);
    drawCorrect(x + 1, y + 12, 0xFF);
    drawCorrect(x + 2, y + 0, 0xFF);
    drawCorrect(x + 2, y + 4, 0xFF);
    drawCorrect(x + 2, y + 8, 0xFF);
    drawCorrect(x + 2, y + 12, 0xFF);
    drawCorrect(x + 3, y + 0, 0xFF);
    drawCorrect(x + 3, y + 4, 0xFF);
    drawCorrect(x + 3, y + 8, 0xFF);
    drawCorrect(x + 3, y + 12, 0xFF);
    drawCorrect(x + 4, y + 0, 0xFF);
    drawCorrect(x + 4, y + 4, 0xFF);
    drawCorrect(x + 4, y + 8, 0xFF);
    drawCorrect(x + 4, y + 12, 0xFF);
    drawCorrect(x + 5, y + 0, 0xFF);
    drawCorrect(x + 5, y + 4, 0xFF);
    drawCorrect(x + 5, y + 8, 0xFF);
    drawCorrect(x + 5, y + 12, 0xFF);
    drawCorrect(x + 6, y + 0, 0xFF);
    drawCorrect(x + 6, y + 4, 0xFF);
    drawCorrect(x + 6, y + 8, 0xFF);
    drawCorrect(x + 6, y + 12, 0xFF);
    drawCorrect(x + 7, y + 0, 0xFF);
    drawCorrect(x + 7, y + 4, 0xFF);
    drawCorrect(x + 7, y + 8, 0xFF);
    drawCorrect(x + 7, y + 12, 0xFF);
    drawCorrect(x + 8, y + 0, 0xFF);
    drawCorrect(x + 8, y + 4, 0xFF);
    drawCorrect(x + 8, y + 8, 0xFF);
    drawCorrect(x + 8, y + 12, 0xFF);
    drawCorrect(x + 9, y + 0, 0xFF);
    drawCorrect(x + 9, y + 4, 0xFF);
    drawCorrect(x + 9, y + 8, 0xFF);
    drawCorrect(x + 9, y + 12, 0xFF);
    drawCorrect(x + 10, y + 0, 0xFF);
    drawCorrect(x + 10, y + 4, 0xFF);
    drawCorrect(x + 10, y + 8, 0xFF);
    drawCorrect(x + 10, y + 12, 0xFF);
    drawCorrect(x + 11, y + 0, 0xFF);
    drawCorrect(x + 11, y + 4, 0xFF);
    drawCorrect(x + 11, y + 8, 0xFF);
    drawCorrect(x + 11, y + 12, 0xFF);
    drawCorrect(x + 12, y + 0, 0xFF);
    drawCorrect(x + 12, y + 4, 0xFF);
    drawCorrect(x + 12, y + 8, 0xFF);
    drawCorrect(x + 12, y + 12, 0xFF);
    drawCorrect(x + 13, y + 0, 0xFF);
    drawCorrect(x + 13, y + 4, 0xFF);
    drawCorrect(x + 13, y + 8, 0xFF);
    drawCorrect(x + 13, y + 12, 0xFF);
    drawCorrect(x + 14, y + 0, 0xFF);
    drawCorrect(x + 14, y + 4, 0xFF);
    drawCorrect(x + 14, y + 8, 0xFF);
    drawCorrect(x + 14, y + 12, 0xFF);
    drawCorrect(x + 15, y + 0, 0xFF);
    drawCorrect(x + 15, y + 4, 0xFF);
    drawCorrect(x + 15, y + 8, 0xFF);
    drawCorrect(x + 15, y + 12, 0xFF);


}
void printNormal(uint8_t x, uint8_t y){
    drawCorrect(x+0,y+4,0x40);
    drawCorrect(x+0,y+8,0x01);
    drawCorrect(x+1,y+4,0x40);
    drawCorrect(x+1,y+8,0x01);
    drawCorrect(x+2,y+4,0xC0);
    drawCorrect(x+2,y+8,0x03);
    drawCorrect(x+3,y+4,0xF0);
    drawCorrect(x+3,y+12,0xFC);
    drawCorrect(x+4,y+4,0xF0);
    drawCorrect(x+4,y+12,0x14);
    drawCorrect(x+5,y+0,0xA0);
    drawCorrect(x+5,y+4,0xF2);
    drawCorrect(x+5,y+12,0x15);
    drawCorrect(x+6,y+0,0xA8);
    drawCorrect(x+6,y+4,0xFE);
    drawCorrect(x+6,y+8,0x5F);
    drawCorrect(x+6,y+12,0x05);
    drawCorrect(x+7,y+0,0x5A);
    drawCorrect(x+7,y+4,0xFD);
    drawCorrect(x+7,y+8,0x5F);
    drawCorrect(x+7,y+12,0x01);
    drawCorrect(x+8,y+0,0xDA);
    drawCorrect(x+8,y+4,0xFD);
    drawCorrect(x+8,y+8,0x5F);
    drawCorrect(x+9,y+0,0x5A);
    drawCorrect(x+9,y+4,0xFD);
    drawCorrect(x+9,y+8,0x5F);
    drawCorrect(x+10,y+0,0xDA);
    drawCorrect(x+10,y+4,0xFD);
    drawCorrect(x+10,y+8,0x5F);
    drawCorrect(x+10,y+12,0xD5);
    drawCorrect(x+11,y+0,0x02);
    drawCorrect(x+11,y+4,0xF0);
    drawCorrect(x+11,y+8,0x40);
    drawCorrect(x+11,y+12,0xD5);
    drawCorrect(x+12,y+4,0xF0);
    drawCorrect(x+12,y+12,0xC0);
    drawCorrect(x+13,y+4,0x3C);
    drawCorrect(x+14,y+4,0x14);
    drawCorrect(x+15,y+4,0x14);
}
void printSorcerer(uint8_t x, uint8_t y){
    drawCorrect(x+0,y+12,0xC0);
    drawCorrect(x+1,y+4,0xF0);
    drawCorrect(x+1,y+8,0x5F);
    drawCorrect(x+1,y+12,0xF0);
    drawCorrect(x+2,y+0,0x03);
    drawCorrect(x+2,y+4,0xFC);
    drawCorrect(x+2,y+8,0x1F);
    drawCorrect(x+2,y+12,0xFC);
    drawCorrect(x+3,y+0,0x0F);
    drawCorrect(x+3,y+4,0x3F);
    drawCorrect(x+3,y+12,0xFF);
    drawCorrect(x+4,y+0,0x3F);
    drawCorrect(x+4,y+4,0xFF);
    drawCorrect(x+4,y+8,0xFF);
    drawCorrect(x+4,y+12,0xFF);
    drawCorrect(x+5,y+0,0xFF);
    drawCorrect(x+5,y+4,0xFF);
    drawCorrect(x+5,y+8,0xFF);
    drawCorrect(x+5,y+12,0xFF);
    drawCorrect(x+6,y+0,0x9F);
    drawCorrect(x+6,y+4,0xFD);
    drawCorrect(x+6,y+8,0xFF);
    drawCorrect(x+6,y+12,0xFF);
    drawCorrect(x+7,y+0,0x5F);
    drawCorrect(x+7,y+4,0xFD);
    drawCorrect(x+7,y+8,0xFF);
    drawCorrect(x+7,y+12,0xFF);
    drawCorrect(x+8,y+0,0x9C);
    drawCorrect(x+8,y+4,0xFD);
    drawCorrect(x+8,y+8,0xFF);
    drawCorrect(x+8,y+12,0xFF);
    drawCorrect(x+9,y+4,0xFC);
    drawCorrect(x+9,y+8,0xFF);
    drawCorrect(x+9,y+12,0xFF);
    drawCorrect(x+10,y+4,0xFC);
    drawCorrect(x+11,y+4,0x3C);
    drawCorrect(x+12,y+4,0x3C);
    drawCorrect(x+13,y+0,0xBF);
    drawCorrect(x+13,y+4,0xF0);
    drawCorrect(x+13,y+8,0xA8);
    drawCorrect(x+13,y+12,0xA0);
    drawCorrect(x+14,y+0,0xB7);
    drawCorrect(x+14,y+4,0x5A);
    drawCorrect(x+14,y+8,0xAA);
    drawCorrect(x+14,y+12,0xAA);
    drawCorrect(x+15,y+0,0x3F);
    drawCorrect(x+15,y+4,0x9A);
    drawCorrect(x+15,y+8,0x8A);
    drawCorrect(x+15,y+12,0x0A);
}
void printRanger(uint8_t x, uint8_t y){
    drawCorrect(x+0,y+8,0x30);
    drawCorrect(x+1,y+4,0x80);
    drawCorrect(x+1,y+8,0x5A);
    drawCorrect(x+2,y+4,0xA0);
    drawCorrect(x+2,y+8,0xDA);
    drawCorrect(x+2,y+12,0xFC);
    drawCorrect(x+3,y+4,0x28);
    drawCorrect(x+3,y+12,0xFF);
    drawCorrect(x+4,y+4,0xA8);
    drawCorrect(x+4,y+8,0xBA);
    drawCorrect(x+4,y+12,0x2E);
    drawCorrect(x+5,y+0,0xFC);
    drawCorrect(x+5,y+4,0xAB);
    drawCorrect(x+5,y+8,0xBA);
    drawCorrect(x+5,y+12,0x3A);
    drawCorrect(x+6,y+0,0x9F);
    drawCorrect(x+6,y+4,0xB9);
    drawCorrect(x+6,y+8,0x3B);
    drawCorrect(x+7,y+0,0x5F);
    drawCorrect(x+7,y+4,0xFD);
    drawCorrect(x+7,y+8,0x3F);
    drawCorrect(x+8,y+0,0x9C);
    drawCorrect(x+8,y+4,0xB9);
    drawCorrect(x+8,y+8,0xBB);
    drawCorrect(x+8,y+12,0xEA);
    drawCorrect(x+9,y+4,0xA8);
    drawCorrect(x+9,y+8,0xBA);
    drawCorrect(x+9,y+12,0xEA);
    drawCorrect(x+10,y+4,0x28);
    drawCorrect(x+10,y+12,0xC0);
    drawCorrect(x+11,y+4,0x28);
    drawCorrect(x+12,y+0,0x5F);
    drawCorrect(x+12,y+4,0x69);
    drawCorrect(x+12,y+8,0x55);
    drawCorrect(x+12,y+12,0xF5);
    drawCorrect(x+13,y+0,0x3C);
    drawCorrect(x+13,y+4,0xA0);
    drawCorrect(x+13,y+12,0x3C);
    drawCorrect(x+14,y+0,0xF0);
    drawCorrect(x+14,y+4,0x50);
    drawCorrect(x+14,y+12,0x0F);
    drawCorrect(x+15,y+0,0xC0);
    drawCorrect(x+15,y+4,0xDF);
    drawCorrect(x+15,y+8,0xFF);
    drawCorrect(x+15,y+12,0x03);
}
void printKnight(uint8_t x, uint8_t y){
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

void printPlayer(int16_t x, int16_t y, int16_t lastY, char forceRedraw, enum Form form) {

    if (y != lastY || forceRedraw == '1') {

        clearPlayer(x, lastY);

        switch (form) {
            case _normal:
                printNormal(x,y);
                break;
            case _sorcerer:
               printSorcerer(x, y);
                break;
            case _ranger:
                printRanger(x, y);
                break;
            case _knight:
                printKnight(x, y);
                break;
        };

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

void printPlatform(struct platform toDraw) {

    for (uint16_t i = 0; i < toDraw.length; i += 15) {

        drawCorrect(toDraw.x + 0 + i, toDraw.y + 0, 0xFF);
        drawCorrect(toDraw.x + 0 + i, toDraw.y + 4, 0x56);
        drawCorrect(toDraw.x + 1 + i, toDraw.y + 0, 0xBF);
        drawCorrect(toDraw.x + 1 + i, toDraw.y + 4, 0x56);
        drawCorrect(toDraw.x + 2 + i, toDraw.y + 0, 0xAF);
        drawCorrect(toDraw.x + 2 + i, toDraw.y + 4, 0x55);
        drawCorrect(toDraw.x + 3 + i, toDraw.y + 0, 0x6F);
        drawCorrect(toDraw.x + 3 + i, toDraw.y + 4, 0x55);
        drawCorrect(toDraw.x + 4 + i, toDraw.y + 0, 0xAF);
        drawCorrect(toDraw.x + 4 + i, toDraw.y + 4, 0x55);
        drawCorrect(toDraw.x + 5 + i, toDraw.y + 0, 0xBF);
        drawCorrect(toDraw.x + 5 + i, toDraw.y + 4, 0x55);
        drawCorrect(toDraw.x + 6 + i, toDraw.y + 0, 0xBF);
        drawCorrect(toDraw.x + 6 + i, toDraw.y + 4, 0x56);
        drawCorrect(toDraw.x + 7 + i, toDraw.y + 0, 0xFF);
        drawCorrect(toDraw.x + 7 + i, toDraw.y + 4, 0x5A);
        drawCorrect(toDraw.x + 8 + i, toDraw.y + 0, 0xFF);
        drawCorrect(toDraw.x + 8 + i, toDraw.y + 4, 0x56);
        drawCorrect(toDraw.x + 9 + i, toDraw.y + 0, 0xBF);
        drawCorrect(toDraw.x + 9 + i, toDraw.y + 4, 0x56);
        drawCorrect(toDraw.x + 10 + i, toDraw.y + 0, 0xBF);
        drawCorrect(toDraw.x + 10 + i, toDraw.y + 4, 0x55);
        drawCorrect(toDraw.x + 11 + i, toDraw.y + 0, 0x6F);
        drawCorrect(toDraw.x + 11 + i, toDraw.y + 4, 0x55);
        drawCorrect(toDraw.x + 12 + i, toDraw.y + 0, 0x6F);
        drawCorrect(toDraw.x + 12 + i, toDraw.y + 4, 0x55);
        drawCorrect(toDraw.x + 13 + i, toDraw.y + 0, 0xAF);
        drawCorrect(toDraw.x + 13 + i, toDraw.y + 4, 0x55);
        drawCorrect(toDraw.x + 14 + i, toDraw.y + 0, 0xBF);
        drawCorrect(toDraw.x + 14 + i, toDraw.y + 4, 0x56);

    }

}

void rePrintPlatform(struct platform toDraw, int16_t offsetX, int16_t speed) {


    // Clear behind platform
    for (int i = 0; i < speed; i++) {
        drawCorrect(toDraw.x + offsetX + toDraw.length + i, toDraw.y, 0);
        drawCorrect(toDraw.x + offsetX + toDraw.length + i, toDraw.y + 4, 0);

    }

    drawCorrect(toDraw.x+offsetX+0,toDraw.y+0,0xFF);
    drawCorrect(toDraw.x+offsetX+0,toDraw.y+4,0x56);
    drawCorrect(toDraw.x+offsetX+1,toDraw.y+0,0xBF);
    drawCorrect(toDraw.x+offsetX+1,toDraw.y+4,0x56);
    drawCorrect(toDraw.x+offsetX+2,toDraw.y+0,0xAF);
    drawCorrect(toDraw.x+offsetX+2,toDraw.y+4,0x55);
    drawCorrect(toDraw.x+offsetX+3,toDraw.y+0,0x6F);
    drawCorrect(toDraw.x+offsetX+3,toDraw.y+4,0x55);
    drawCorrect(toDraw.x+offsetX+4,toDraw.y+0,0xAF);
    drawCorrect(toDraw.x+offsetX+4,toDraw.y+4,0x55);
    drawCorrect(toDraw.x+offsetX+5,toDraw.y+0,0xBF);
    drawCorrect(toDraw.x+offsetX+5,toDraw.y+4,0x55);
    drawCorrect(toDraw.x+offsetX+6,toDraw.y+0,0xBF);
    drawCorrect(toDraw.x+offsetX+6,toDraw.y+4,0x56);
    drawCorrect(toDraw.x+offsetX+7,toDraw.y+0,0xFF);
    drawCorrect(toDraw.x+offsetX+7,toDraw.y+4,0x5A);
    drawCorrect(toDraw.x+offsetX+8,toDraw.y+0,0xFF);
    drawCorrect(toDraw.x+offsetX+8,toDraw.y+4,0x56);
    drawCorrect(toDraw.x+offsetX+9,toDraw.y+0,0xBF);
    drawCorrect(toDraw.x+offsetX+9,toDraw.y+4,0x56);
    drawCorrect(toDraw.x+offsetX+10,toDraw.y+0,0xBF);
    drawCorrect(toDraw.x+offsetX+10,toDraw.y+4,0x55);
    drawCorrect(toDraw.x+offsetX+11,toDraw.y+0,0x6F);
    drawCorrect(toDraw.x+offsetX+11,toDraw.y+4,0x55);
    drawCorrect(toDraw.x+offsetX+12,toDraw.y+0,0x6F);
    drawCorrect(toDraw.x+offsetX+12,toDraw.y+4,0x55);
    drawCorrect(toDraw.x+offsetX+13,toDraw.y+0,0xAF);
    drawCorrect(toDraw.x+offsetX+13,toDraw.y+4,0x55);
    drawCorrect(toDraw.x+offsetX+14,toDraw.y+0,0xBF);
    drawCorrect(toDraw.x+offsetX+14,toDraw.y+4,0x56);


    drawCorrect(toDraw.x+offsetX+toDraw.length-15+0,toDraw.y+0,0xFF);
    drawCorrect(toDraw.x+offsetX+toDraw.length-15+0,toDraw.y+4,0x56);
    drawCorrect(toDraw.x+offsetX+toDraw.length-15+1,toDraw.y+0,0xBF);
    drawCorrect(toDraw.x+offsetX+toDraw.length-15+1,toDraw.y+4,0x56);
    drawCorrect(toDraw.x+offsetX+toDraw.length-15+2,toDraw.y+0,0xAF);
    drawCorrect(toDraw.x+offsetX+toDraw.length-15+2,toDraw.y+4,0x55);
    drawCorrect(toDraw.x+offsetX+toDraw.length-15+3,toDraw.y+0,0x6F);
    drawCorrect(toDraw.x+offsetX+toDraw.length-15+3,toDraw.y+4,0x55);
    drawCorrect(toDraw.x+offsetX+toDraw.length-15+4,toDraw.y+0,0xAF);
    drawCorrect(toDraw.x+offsetX+toDraw.length-15+4,toDraw.y+4,0x55);
    drawCorrect(toDraw.x+offsetX+toDraw.length-15+5,toDraw.y+0,0xBF);
    drawCorrect(toDraw.x+offsetX+toDraw.length-15+5,toDraw.y+4,0x55);
    drawCorrect(toDraw.x+offsetX+toDraw.length-15+6,toDraw.y+0,0xBF);
    drawCorrect(toDraw.x+offsetX+toDraw.length-15+6,toDraw.y+4,0x56);
    drawCorrect(toDraw.x+offsetX+toDraw.length-15+7,toDraw.y+0,0xFF);
    drawCorrect(toDraw.x+offsetX+toDraw.length-15+7,toDraw.y+4,0x5A);
    drawCorrect(toDraw.x+offsetX+toDraw.length-15+8,toDraw.y+0,0xFF);
    drawCorrect(toDraw.x+offsetX+toDraw.length-15+8,toDraw.y+4,0x56);
    drawCorrect(toDraw.x+offsetX+toDraw.length-15+9,toDraw.y+0,0xBF);
    drawCorrect(toDraw.x+offsetX+toDraw.length-15+9,toDraw.y+4,0x56);
    drawCorrect(toDraw.x+offsetX+toDraw.length-15+10,toDraw.y+0,0xBF);
    drawCorrect(toDraw.x+offsetX+toDraw.length-15+10,toDraw.y+4,0x55);
    drawCorrect(toDraw.x+offsetX+toDraw.length-15+11,toDraw.y+0,0x6F);
    drawCorrect(toDraw.x+offsetX+toDraw.length-15+11,toDraw.y+4,0x55);
    drawCorrect(toDraw.x+offsetX+toDraw.length-15+12,toDraw.y+0,0x6F);
    drawCorrect(toDraw.x+offsetX+toDraw.length-15+12,toDraw.y+4,0x55);
    drawCorrect(toDraw.x+offsetX+toDraw.length-15+13,toDraw.y+0,0xAF);
    drawCorrect(toDraw.x+offsetX+toDraw.length-15+13,toDraw.y+4,0x55);
    drawCorrect(toDraw.x+offsetX+toDraw.length-15+14,toDraw.y+0,0xBF);
    drawCorrect(toDraw.x+offsetX+toDraw.length-15+14,toDraw.y+4,0x56);

}

void printPowerUp(int16_t x, int16_t y, enum PowerUpType type, int16_t speed) {

    for (int i = 0; i < speed; i++) {
        drawCorrect(x + 8 + i, y, 0);
        drawCorrect(x + 8 + i, y + 4, 0);


    }
    switch (type) {
        case none:
            break;
        case live:
            drawCorrect(x + 0, y + 0, 0x74);
            drawCorrect(x + 0, y + 4, 0x17);
            drawCorrect(x + 1, y + 0, 0xDD);
            drawCorrect(x + 1, y + 4, 0x55);
            drawCorrect(x + 2, y + 0, 0x57);
            drawCorrect(x + 2, y + 4, 0x55);
            drawCorrect(x + 3, y + 0, 0xD7);
            drawCorrect(x + 3, y + 4, 0x7F);
            drawCorrect(x + 4, y + 0, 0x7D);
            drawCorrect(x + 4, y + 4, 0x75);
            drawCorrect(x + 5, y + 0, 0x55);
            drawCorrect(x + 5, y + 4, 0x75);
            drawCorrect(x + 6, y + 0, 0xFD);
            drawCorrect(x + 6, y + 4, 0x7F);
            drawCorrect(x + 7, y + 0, 0x54);
            drawCorrect(x + 7, y + 4, 0x15);
            break;
        case death:
            drawCorrect(x + 0, y + 0, 0xFC);
            drawCorrect(x + 0, y + 4, 0x3F);
            drawCorrect(x + 1, y + 0, 0x7F);
            drawCorrect(x + 1, y + 4, 0xFF);
            drawCorrect(x + 2, y + 0, 0x7F);
            drawCorrect(x + 2, y + 4, 0xF5);
            drawCorrect(x + 3, y + 0, 0xFF);
            drawCorrect(x + 3, y + 4, 0xD7);
            drawCorrect(x + 4, y + 0, 0x57);
            drawCorrect(x + 4, y + 4, 0xDF);
            drawCorrect(x + 5, y + 0, 0x77);
            drawCorrect(x + 5, y + 4, 0xDF);
            drawCorrect(x + 6, y + 0, 0x57);
            drawCorrect(x + 6, y + 4, 0xD5);
            drawCorrect(x + 7, y + 0, 0xFC);
            drawCorrect(x + 7, y + 4, 0x3F);
            break;
        case knight:
            drawCorrect(x + 0, y + 0, 0x74);
            drawCorrect(x + 0, y + 4, 0x15);
            drawCorrect(x + 1, y + 0, 0xDD);
            drawCorrect(x + 1, y + 4, 0x55);
            drawCorrect(x + 2, y + 0, 0xFD);
            drawCorrect(x + 2, y + 4, 0x7F);
            drawCorrect(x + 3, y + 0, 0x55);
            drawCorrect(x + 3, y + 4, 0x75);
            drawCorrect(x + 4, y + 0, 0x55);
            drawCorrect(x + 4, y + 4, 0x5F);
            drawCorrect(x + 5, y + 0, 0xD5);
            drawCorrect(x + 5, y + 4, 0x55);
            drawCorrect(x + 6, y + 0, 0x7D);
            drawCorrect(x + 6, y + 4, 0x55);
            drawCorrect(x + 7, y + 0, 0xFC);
            drawCorrect(x + 7, y + 4, 0x3F);
            break;
        case sorcerer:

            break;
        case ranger:

            break;
        case slow:

            break;
        case speedUp:
            drawCorrect(x + 0, y + 0, 0xF4);
            drawCorrect(x + 0, y + 4, 0x37);
            drawCorrect(x + 1, y + 0, 0xDD);
            drawCorrect(x + 1, y + 4, 0xDD);
            drawCorrect(x + 2, y + 0, 0x57);
            drawCorrect(x + 2, y + 4, 0xF5);
            drawCorrect(x + 3, y + 0, 0xFF);
            drawCorrect(x + 3, y + 4, 0xF7);
            drawCorrect(x + 4, y + 0, 0xFF);
            drawCorrect(x + 4, y + 4, 0xF7);
            drawCorrect(x + 5, y + 0, 0xFF);
            drawCorrect(x + 5, y + 4, 0xDF);
            drawCorrect(x + 6, y + 0, 0x57);
            drawCorrect(x + 6, y + 4, 0xD5);
            drawCorrect(x + 7, y + 0, 0xFC);
            drawCorrect(x + 7, y + 4, 0x3F);
            break;
        case pointsUp:
            drawCorrect(x + 0, y + 0, 0x54);
            drawCorrect(x + 0, y + 4, 0x15);
            drawCorrect(x + 1, y + 0, 0x75);
            drawCorrect(x + 1, y + 4, 0x55);
            drawCorrect(x + 2, y + 0, 0xDD);
            drawCorrect(x + 2, y + 4, 0x55);
            drawCorrect(x + 3, y + 0, 0xDD);
            drawCorrect(x + 3, y + 4, 0x55);
            drawCorrect(x + 4, y + 0, 0xDD);
            drawCorrect(x + 4, y + 4, 0x75);
            drawCorrect(x + 5, y + 0, 0xDD);
            drawCorrect(x + 5, y + 4, 0xDD);
            drawCorrect(x + 6, y + 0, 0x57);
            drawCorrect(x + 6, y + 4, 0x7F);
            drawCorrect(x + 7, y + 0, 0x54);
            drawCorrect(x + 7, y + 4, 0x15);
            break;
        case pointsDown:
            drawCorrect(x + 0, y + 0, 0xDC);
            drawCorrect(x + 0, y + 4, 0x3F);
            drawCorrect(x + 1, y + 0, 0x77);
            drawCorrect(x + 1, y + 4, 0xFF);
            drawCorrect(x + 2, y + 0, 0x5F);
            drawCorrect(x + 2, y + 4, 0xD5);
            drawCorrect(x + 3, y + 0, 0xFF);
            drawCorrect(x + 3, y + 4, 0xDF);
            drawCorrect(x + 4, y + 0, 0xFF);
            drawCorrect(x + 4, y + 4, 0xDF);
            drawCorrect(x + 5, y + 0, 0xFF);
            drawCorrect(x + 5, y + 4, 0xDF);
            drawCorrect(x + 6, y + 0, 0x55);
            drawCorrect(x + 6, y + 4, 0xD5);
            drawCorrect(x + 7, y + 0, 0xFC);
            drawCorrect(x + 7, y + 4, 0x3F);
            break;

    };


}

void clearPowerUp(int16_t x, int16_t y) {
    drawCorrect(x + 0, y + 0, 0);
    drawCorrect(x + 0, y + 4, 0);
    drawCorrect(x + 1, y + 0, 0);
    drawCorrect(x + 1, y + 4, 0);
    drawCorrect(x + 2, y + 0, 0);
    drawCorrect(x + 2, y + 4, 0);
    drawCorrect(x + 3, y + 0, 0);
    drawCorrect(x + 3, y + 4, 0);
    drawCorrect(x + 4, y + 0, 0);
    drawCorrect(x + 4, y + 4, 0);
    drawCorrect(x + 5, y + 0, 0);
    drawCorrect(x + 5, y + 4, 0);
    drawCorrect(x + 6, y + 0, 0);
    drawCorrect(x + 6, y + 4, 0);
    drawCorrect(x + 7, y + 0, 0);
    drawCorrect(x + 7, y + 4, 0);

}

void printDragon() {
    drawCorrect(18, 32, 0x0C);
    drawCorrect(19, 32, 0x03);
    drawCorrect(20, 32, 0x03);
    drawCorrect(21, 32, 0x03);
    drawCorrect(21, 40, 0x3C);
    drawCorrect(22, 28, 0xC0);
    drawCorrect(22, 32, 0x03);
    drawCorrect(22, 36, 0xC0);
    drawCorrect(22, 40, 0x0F);
    drawCorrect(22, 48, 0x0F);
    drawCorrect(22, 52, 0xFC);
    drawCorrect(22, 56, 0xFF);
    drawCorrect(23, 28, 0xC0);
    drawCorrect(23, 36, 0xF0);
    drawCorrect(23, 40, 0x03);
    drawCorrect(23, 44, 0xFC);
    for (uint8_t i = 52; i <= 60; i += 4) {
        drawCorrect(23, i, 0xFF);
    }
    drawCorrect(24, 28, 0xF0);
    drawCorrect(24, 36, 0xFF);
    drawCorrect(24, 40, 0xF0);
    drawCorrect(24, 44, 0x0F);
    drawCorrect(24, 56, 0xFC);
    drawCorrect(24, 60, 0xFF);
    drawCorrect(24, 64, 0x3F);
    drawCorrect(25, 28, 0xF0);
    drawCorrect(25, 32, 0xC0);
    drawCorrect(25, 36, 0x3F);
    drawCorrect(25, 40, 0x3F);
    drawCorrect(25, 48, 0x0F);
    drawCorrect(25, 64, 0xFC);
    drawCorrect(25, 68, 0x03);
    drawCorrect(26, 28, 0xF0);
    drawCorrect(26, 32, 0xC0);
    drawCorrect(26, 36, 0xFF);
    drawCorrect(26, 40, 0x0F);
    drawCorrect(26, 44, 0xF0);
    drawCorrect(26, 48, 0xCF);
    for (uint8_t i = 52; i <= 60; i += 4) {
        drawCorrect(26, i, 0xFF);
    }
    drawCorrect(26, 64, 0x3F);
    drawCorrect(26, 68, 0x3F);
    drawCorrect(27, 28, 0xF0);
    drawCorrect(27, 32, 0xF0);
    drawCorrect(27, 36, 0xFF);
    drawCorrect(27, 40, 0x30);
    for (uint8_t i = 44; i <= 68; i += 4) {
        drawCorrect(27, i, 0xFF);
    }
    drawCorrect(28, 28, 0xF0);
    drawCorrect(28, 32, 0xFC);
    drawCorrect(28, 36, 0x3F);
    drawCorrect(28, 40, 0xFC);
    for (uint8_t i = 44; i <= 68; i += 4) {
        drawCorrect(28, i, 0xFF);
    }
    drawCorrect(28, 72, 0x0F);
    drawCorrect(29, 28, 0xFC);
    drawCorrect(29, 32, 0xFC);
    drawCorrect(29, 36, 0xCF);
    for (uint8_t i = 40; i <= 64; i += 4) {
        drawCorrect(29, i, 0xFF);
    }
    drawCorrect(29, 68, 0x3F);
    drawCorrect(29, 72, 0x3F);
    drawCorrect(30, 28, 0xFC);
    drawCorrect(30, 32, 0xFF);
    drawCorrect(30, 36, 0xF3);
    for (uint8_t i = 40; i <= 68; i += 4) {
        drawCorrect(30, i, 0xFF);
    }
    drawCorrect(30, 72, 0xF0);
    drawCorrect(31, 28, 0xFC);
    for (uint8_t i = 32; i <= 68; i += 4) {
        drawCorrect(31, i, 0xFF);
    }
    drawCorrect(31, 72, 0xC3);
    drawCorrect(31, 76, 0x03);
    drawCorrect(32, 20, 0x30);
    for (uint8_t i = 28; i <= 68; i += 4) {
        drawCorrect(32, i, 0xFF);
    }
    drawCorrect(32, 72, 0x03);
    drawCorrect(32, 76, 0x0C);
    drawCorrect(33, 20, 0x30);
    for (uint8_t i = 28; i <= 68; i += 4) {
        drawCorrect(33, i, 0xFF);
    }
    drawCorrect(33, 72, 0x0F);
    drawCorrect(33, 76, 0x30);
    drawCorrect(34, 20, 0x0C);
    drawCorrect(34, 24, 0xC0);
    drawCorrect(34, 28, 0xCF);
    for (uint8_t i = 32; i <= 68; i += 4) {
        drawCorrect(34, i, 0xFF);
    }
    drawCorrect(34, 72, 0x3F);
    drawCorrect(35, 20, 0x0C);
    drawCorrect(35, 24, 0xF0);
    drawCorrect(35, 28, 0xF3);
    for (uint8_t i = 32; i <= 68; i += 4) {
        drawCorrect(35, i, 0xFF);
    }
    drawCorrect(35, 72, 0x3F);
    drawCorrect(36, 20, 0x0F);
    drawCorrect(36, 24, 0xF0);
    drawCorrect(36, 28, 0xFC);
    for (uint8_t i = 32; i <= 72; i += 4) {
        drawCorrect(36, i, 0xFF);
    }
    drawCorrect(37, 20, 0x0F);
    drawCorrect(37, 24, 0x3C);
    for (uint8_t i = 28; i <= 72; i += 4) {
        drawCorrect(37, i, 0xFF);
    }
    drawCorrect(38, 16, 0xC0);
    drawCorrect(38, 20, 0x0F);
    drawCorrect(38, 24, 0x3F);
    for (uint8_t i = 28; i <= 72; i += 4) {
        drawCorrect(38, i, 0xFF);
    }
    drawCorrect(38, 76, 0x03);
    drawCorrect(39, 16, 0xC0);
    drawCorrect(39, 20, 0xFF);
    drawCorrect(39, 24, 0xCF);
    for (uint8_t i = 28; i <= 72; i += 4) {
        drawCorrect(39, i, 0xFF);
    }
    drawCorrect(39, 76, 0x03);
    drawCorrect(40, 16, 0xC0);
    drawCorrect(40, 20, 0xFF);
    drawCorrect(40, 24, 0xCF);
    for (uint8_t i = 28; i <= 72; i += 4) {
        drawCorrect(40, i, 0xFF);
    }
    drawCorrect(40, 76, 0x0F);
    drawCorrect(41, 16, 0xFC);
    drawCorrect(41, 20, 0xFF);
    drawCorrect(41, 24, 0xC3);
    for (uint8_t i = 28; i <= 72; i += 4) {
        drawCorrect(41, i, 0xFF);
    }
    drawCorrect(41, 76, 0x0F);
    drawCorrect(42, 16, 0xFC);
    drawCorrect(42, 20, 0xFF);
    drawCorrect(42, 24, 0xF3);
    for (uint8_t i = 28; i <= 72; i += 4) {
        drawCorrect(42, i, 0xFF);
    }
    drawCorrect(42, 76, 0x0F);
    drawCorrect(43, 16, 0xFC);
    drawCorrect(43, 20, 0xFF);
    drawCorrect(43, 24, 0xFC);
    drawCorrect(43, 28, 0xFF);
    drawCorrect(43, 32, 0xFF);
    drawCorrect(43, 36, 0xFF);
    drawCorrect(43, 40, 0xFF);
    drawCorrect(43, 44, 0x03);
    drawCorrect(43, 48, 0x3F);
    drawCorrect(43, 56, 0xF0);
    drawCorrect(43, 60, 0xCF);
    for (uint8_t i = 64; i <= 72; i += 4) {
        drawCorrect(43, i, 0xFF);
    }
    drawCorrect(43, 76, 0x3F);
    drawCorrect(44, 16, 0xFC);
    drawCorrect(44, 20, 0xF3);
    drawCorrect(44, 24, 0xFC);
    for (uint8_t i = 28; i <= 40; i += 4) {
        drawCorrect(44, i, 0xFF);
    }
    drawCorrect(44, 48, 0xF0);
    drawCorrect(44, 56, 0xC0);
    for (uint8_t i = 60; i <= 72; i += 4) {
        drawCorrect(44, i, 0xFF);
    }
    drawCorrect(44, 76, 0x3F);
    drawCorrect(45, 16, 0xFC);
    drawCorrect(45, 20, 0x33);
    for (uint8_t i = 24; i <= 40; i += 4) {
        drawCorrect(45, i, 0xFF);
    }
    drawCorrect(45, 56, 0xC0);
    drawCorrect(45, 60, 0x3F);
    drawCorrect(45, 64, 0xFC);
    for (uint8_t i = 68; i <= 76; i += 4) {
        drawCorrect(45, i, 0xFF);
    }
    drawCorrect(46, 16, 0xFC);
    drawCorrect(46, 20, 0x33);
    for (uint8_t i = 24; i <= 36; i += 4) {
        drawCorrect(46, i, 0xFF);
    }
    drawCorrect(46, 40, 0x3F);
    drawCorrect(46, 60, 0x3F);
    drawCorrect(46, 64, 0xFC);
    for (uint8_t i = 68; i <= 76; i += 4) {
        drawCorrect(46, i, 0xFF);
    }
    drawCorrect(47, 16, 0xF0);
    drawCorrect(47, 20, 0x03);
    for (uint8_t i = 24; i <= 36; i += 4) {
        drawCorrect(47, i, 0xFF);
    }
    drawCorrect(47, 40, 0x3F);
    drawCorrect(47, 60, 0x3F);
    drawCorrect(47, 64, 0xF0);
    for (uint8_t i = 68; i <= 76; i += 4) {
        drawCorrect(47, i, 0xFF);
    }
    drawCorrect(47, 80, 0x03);
    drawCorrect(48, 16, 0xF0);
    drawCorrect(48, 20, 0xC3);
    for (uint8_t i = 24; i <= 40; i += 4) {
        drawCorrect(48, i, 0xFF);
    }
    drawCorrect(48, 60, 0x3F);
    drawCorrect(48, 64, 0x03);
    drawCorrect(48, 68, 0xFC);
    drawCorrect(48, 72, 0xFF);
    drawCorrect(48, 76, 0xFF);
    drawCorrect(48, 80, 0x03);
    drawCorrect(49, 16, 0xCC);
    drawCorrect(49, 20, 0xC3);
    for (uint8_t i = 24; i <= 40; i += 4) {
        drawCorrect(49, i, 0xFF);
    }
    drawCorrect(49, 60, 0x3E);
    drawCorrect(49, 64, 0x03);
    for (uint8_t i = 68; i <= 76; i += 4) {
        drawCorrect(49, i, 0xFF);
    }
    drawCorrect(49, 80, 0x0F);
    drawCorrect(50, 16, 0xFC);
    drawCorrect(50, 20, 0xC3);
    for (uint8_t i = 24; i <= 32; i += 4) {
        drawCorrect(50, i, 0xFF);
    }
    drawCorrect(50, 36, 0xCF);
    drawCorrect(50, 40, 0xFF);
    drawCorrect(50, 60, 0xFC);
    drawCorrect(50, 64, 0x13);
    for (uint8_t i = 68; i <= 76; i += 4) {
        drawCorrect(50, i, 0xFF);
    }
    drawCorrect(50, 80, 0x0F);
    drawCorrect(51, 16, 0xF0);
    drawCorrect(51, 20, 0xC0);
    for (uint8_t i = 24; i <= 32; i += 4) {
        drawCorrect(51, i, 0xFF);
    }
    drawCorrect(51, 36, 0xCF);
    drawCorrect(51, 40, 0xFF);
    drawCorrect(51, 60, 0xFC);
    drawCorrect(51, 64, 0x33);
    for (uint8_t i = 68; i <= 76; i += 4) {
        drawCorrect(51, i, 0xFF);
    }
    drawCorrect(51, 80, 0x3F);
    drawCorrect(52, 16, 0xFF);
    drawCorrect(52, 20, 0xCF);
    drawCorrect(52, 24, 0xFF);
    drawCorrect(52, 28, 0xFF);
    drawCorrect(52, 32, 0xCF);
    drawCorrect(52, 36, 0xF3);
    drawCorrect(52, 40, 0xF3);
    drawCorrect(52, 60, 0xFC);
    drawCorrect(52, 64, 0x33);
    for (uint8_t i = 68; i <= 76; i += 4) {
        drawCorrect(52, i, 0xFF);
    }
    drawCorrect(52, 80, 0x3F);
    drawCorrect(53, 16, 0xFC);
    drawCorrect(53, 20, 0xC3);
    drawCorrect(53, 24, 0xFF);
    drawCorrect(53, 28, 0xFF);
    drawCorrect(53, 32, 0xF3);
    drawCorrect(53, 36, 0x30);
    drawCorrect(53, 40, 0xFC);
    drawCorrect(53, 60, 0xF0);
    drawCorrect(53, 64, 0x3F);
    for (uint8_t i = 68; i <= 80; i += 4) {
        drawCorrect(53, i, 0xFF);
    }
    drawCorrect(54, 16, 0xF0);
    drawCorrect(54, 20, 0xC3);
    drawCorrect(54, 24, 0xFF);
    drawCorrect(54, 28, 0xFF);
    drawCorrect(54, 32, 0x33);
    drawCorrect(54, 40, 0xFF);
    drawCorrect(54, 44, 0x03);
    drawCorrect(54, 60, 0xF0);
    drawCorrect(54, 64, 0x3F);
    for (uint8_t i = 68; i <= 80; i += 4) {
        drawCorrect(54, i, 0xFF);
    }
    drawCorrect(54, 84, 0x03);
    drawCorrect(55, 12, 0x30);
    drawCorrect(55, 16, 0xC0);
    drawCorrect(55, 20, 0xCF);
    drawCorrect(55, 24, 0xFF);
    drawCorrect(55, 28, 0xFF);
    drawCorrect(55, 32, 0xC0);
    drawCorrect(55, 36, 0xF3);
    drawCorrect(55, 40, 0xFF);
    drawCorrect(55, 44, 0x03);
    drawCorrect(55, 60, 0xC0);
    drawCorrect(55, 64, 0x3F);
    for (uint8_t i = 68; i <= 80; i += 4) {
        drawCorrect(55, i, 0xFF);
    }
    drawCorrect(55, 84, 0x0F);
    drawCorrect(56, 12, 0xC0);
    drawCorrect(56, 16, 0xC0);
    drawCorrect(56, 20, 0xCF);
    for (uint8_t i = 24; i <= 40; i += 4) {
        drawCorrect(56, i, 0xFF);
    }
    drawCorrect(56, 44, 0x0F);
    drawCorrect(56, 60, 0xC0);
    drawCorrect(56, 64, 0x3F);
    for (uint8_t i = 68; i <= 80; i += 4) {
        drawCorrect(56, i, 0xFF);
    }
    drawCorrect(56, 84, 0x3F);
    drawCorrect(57, 12, 0xC0);
    drawCorrect(57, 16, 0x03);
    for (uint8_t i = 20; i <= 40; i += 4) {
        drawCorrect(57, i, 0xFF);
    }
    drawCorrect(57, 44, 0x3F);
    drawCorrect(57, 60, 0x40);
    drawCorrect(57, 64, 0x7F);
    for (uint8_t i = 68; i <= 84; i += 4) {
        drawCorrect(57, i, 0xFF);
    }
    drawCorrect(57, 88, 0x03);
    for (uint8_t i = 16; i <= 44; i += 4) {
        drawCorrect(58, i, 0xFF);
    }
    drawCorrect(58, 48, 0x03);
    for (uint8_t i = 64; i <= 76; i += 4) {
        drawCorrect(58, i, 0xFF);
    }
    drawCorrect(58, 80, 0x03);
    drawCorrect(58, 84, 0xFF);
    drawCorrect(58, 88, 0x0F);
    drawCorrect(59, 4, 0x3F);
    drawCorrect(59, 16, 0xFC);
    for (uint8_t i = 20; i <= 44; i += 4) {
        drawCorrect(59, i, 0xFF);
    }
    drawCorrect(59, 48, 0x0F);
    drawCorrect(59, 64, 0xFD);
    drawCorrect(59, 68, 0xFD);
    drawCorrect(59, 72, 0xFF);
    drawCorrect(59, 76, 0xFF);
    drawCorrect(59, 80, 0x03);
    drawCorrect(59, 84, 0xC0);
    drawCorrect(59, 88, 0xFF);
    drawCorrect(60, 4, 0xFF);
    drawCorrect(60, 8, 0x03);
    drawCorrect(60, 16, 0xF0);
    for (uint8_t i = 20; i <= 44; i += 4) {
        drawCorrect(60, i, 0xFF);
    }
    drawCorrect(60, 48, 0x3F);
    drawCorrect(60, 64, 0xFC);
    drawCorrect(60, 68, 0xFC);
    drawCorrect(60, 72, 0xFF);
    drawCorrect(60, 76, 0xFF);
    drawCorrect(60, 80, 0x0F);
    drawCorrect(60, 88, 0xF0);
    drawCorrect(60, 92, 0x3F);
    drawCorrect(61, 4, 0xF0);
    drawCorrect(61, 8, 0x3F);
    for (uint8_t i = 20; i <= 48; i += 4) {
        drawCorrect(61, i, 0xFF);
    }
    drawCorrect(61, 56, 0x80);
    drawCorrect(61, 64, 0xF0);
    for (uint8_t i = 68; i <= 80; i += 4) {
        drawCorrect(61, i, 0xFF);
    }
    drawCorrect(61, 92, 0xF0);
    drawCorrect(61, 96, 0xFF);
    drawCorrect(62, 8, 0xFF);
    drawCorrect(62, 12, 0x03);
    for (uint8_t i = 20; i <= 36; i += 4) {
        drawCorrect(62, i, 0xFF);
    }
    drawCorrect(62, 40, 0x80);
    drawCorrect(62, 44, 0x0A);
    drawCorrect(62, 48, 0xFF);
    drawCorrect(62, 52, 0x03);
    drawCorrect(62, 56, 0x80);
    drawCorrect(62, 64, 0xF0);
    drawCorrect(62, 68, 0xFF);
    drawCorrect(62, 72, 0xFF);
    drawCorrect(62, 76, 0x0F);
    drawCorrect(63, 8, 0xF0);
    drawCorrect(63, 12, 0x3F);
    drawCorrect(63, 20, 0xFC);
    for (uint8_t i = 24; i <= 32; i += 4) {
        drawCorrect(63, i, 0xFF);
    }
    drawCorrect(63, 36, 0x3F);
    drawCorrect(63, 44, 0x2A);
    drawCorrect(63, 48, 0xFC);
    drawCorrect(63, 52, 0x3F);
    drawCorrect(63, 56, 0xBC);
    drawCorrect(63, 60, 0x08);
    drawCorrect(63, 64, 0xC0);
    drawCorrect(63, 68, 0xFF);
    drawCorrect(63, 72, 0xFF);
    drawCorrect(63, 76, 0x0F);
    for (uint8_t i = 12; i <= 32; i += 4) {
        drawCorrect(64, i, 0xFF);
    }
    drawCorrect(64, 36, 0x3F);
    drawCorrect(64, 44, 0x28);
    drawCorrect(64, 48, 0xF0);
    drawCorrect(64, 52, 0xFF);
    drawCorrect(64, 56, 0x3F);
    drawCorrect(64, 60, 0x08);
    drawCorrect(64, 64, 0xC0);
    drawCorrect(64, 68, 0xFF);
    drawCorrect(64, 72, 0xF3);
    drawCorrect(64, 76, 0x3F);
    drawCorrect(65, 12, 0xFC);
    for (uint8_t i = 16; i <= 32; i += 4) {
        drawCorrect(65, i, 0xFF);
    }
    drawCorrect(65, 36, 0x3F);
    drawCorrect(65, 44, 0x28);
    drawCorrect(65, 48, 0xC0);
    drawCorrect(65, 52, 0xFF);
    drawCorrect(65, 56, 0xFF);
    drawCorrect(65, 60, 0x02);
    drawCorrect(65, 68, 0xFF);
    drawCorrect(65, 72, 0xC3);
    drawCorrect(65, 76, 0x0F);
    drawCorrect(66, 16, 0xC0);
    for (uint8_t i = 20; i <= 32; i += 4) {
        drawCorrect(66, i, 0xFF);
    }
    drawCorrect(66, 36, 0x3F);
    drawCorrect(66, 44, 0x20);
    drawCorrect(66, 52, 0xFF);
    drawCorrect(66, 56, 0xFF);
    drawCorrect(66, 60, 0x23);
    drawCorrect(66, 68, 0xFC);
    drawCorrect(66, 72, 0x0F);
    drawCorrect(67, 24, 0xFF);
    drawCorrect(67, 28, 0xFF);
    drawCorrect(67, 32, 0xF0);
    drawCorrect(67, 36, 0xFF);
    drawCorrect(67, 44, 0xA0);
    drawCorrect(67, 52, 0xFC);
    drawCorrect(67, 56, 0xFF);
    drawCorrect(67, 60, 0x28);
    drawCorrect(67, 68, 0xF0);
    drawCorrect(67, 72, 0x0F);
    drawCorrect(68, 20, 0xFC);
    drawCorrect(68, 24, 0xFF);
    drawCorrect(68, 28, 0xFF);
    drawCorrect(68, 32, 0xC0);
    drawCorrect(68, 36, 0xFF);
    drawCorrect(68, 44, 0xA0);
    drawCorrect(68, 48, 0x02);
    drawCorrect(68, 52, 0xF0);
    drawCorrect(68, 56, 0xFF);
    drawCorrect(68, 60, 0x02);
    drawCorrect(68, 68, 0xF0);
    drawCorrect(68, 72, 0x3F);
    drawCorrect(69, 16, 0xF0);
    drawCorrect(69, 20, 0xFF);
    drawCorrect(69, 24, 0xFF);
    drawCorrect(69, 28, 0xFF);
    drawCorrect(69, 32, 0xC3);
    drawCorrect(69, 36, 0xFF);
    drawCorrect(69, 44, 0x80);
    drawCorrect(69, 48, 0x02);
    drawCorrect(69, 52, 0xC0);
    drawCorrect(69, 56, 0xFF);
    drawCorrect(69, 60, 0x20);
    drawCorrect(69, 68, 0xC0);
    drawCorrect(69, 72, 0xFF);
    drawCorrect(70, 28, 0xC0);
    drawCorrect(70, 32, 0x0F);
    drawCorrect(70, 36, 0xFF);
    drawCorrect(70, 40, 0x03);
    drawCorrect(70, 48, 0x02);
    drawCorrect(70, 52, 0xF0);
    drawCorrect(70, 56, 0xFF);
    drawCorrect(70, 60, 0x0A);
    drawCorrect(70, 72, 0xFF);
    drawCorrect(71, 32, 0xFC);
    drawCorrect(71, 36, 0xFF);
    drawCorrect(71, 40, 0x03);
    drawCorrect(71, 48, 0x08);
    drawCorrect(71, 52, 0xF0);
    drawCorrect(71, 56, 0x3F);
    drawCorrect(71, 72, 0xFC);
    drawCorrect(71, 76, 0x03);
    drawCorrect(72, 32, 0xF0);
    drawCorrect(72, 36, 0xFF);
    drawCorrect(72, 40, 0x0F);
    drawCorrect(72, 48, 0x20);
    drawCorrect(72, 72, 0xC0);
    drawCorrect(72, 76, 0x0F);
    drawCorrect(73, 32, 0xC0);
    drawCorrect(73, 36, 0xFF);
    drawCorrect(73, 40, 0x0F);
    drawCorrect(73, 76, 0xFF);
    drawCorrect(74, 36, 0xFF);
    drawCorrect(74, 40, 0x3F);
    drawCorrect(74, 76, 0xF0);
    drawCorrect(74, 80, 0x03);
    drawCorrect(75, 36, 0xF0);
    drawCorrect(75, 40, 0x3F);
    drawCorrect(75, 80, 0x3F);
    drawCorrect(76, 36, 0xF0);
    drawCorrect(76, 40, 0x3F);
    drawCorrect(76, 80, 0xF0);
    drawCorrect(76, 84, 0x03);
    drawCorrect(77, 36, 0xC0);
    drawCorrect(77, 40, 0xFF);
    drawCorrect(78, 36, 0xC0);
    drawCorrect(78, 40, 0xFF);
    drawCorrect(79, 40, 0xFF);
    drawCorrect(79, 44, 0x03);
    drawCorrect(80, 40, 0xFF);
    drawCorrect(80, 44, 0x03);
    drawCorrect(81, 40, 0xFF);
    drawCorrect(81, 44, 0xCF);
    drawCorrect(81, 48, 0x03);
    drawCorrect(82, 40, 0xFC);
    drawCorrect(82, 44, 0xFF);
    drawCorrect(83, 40, 0xFC);
    drawCorrect(83, 44, 0xFF);
    drawCorrect(84, 40, 0xFC);
    drawCorrect(84, 44, 0x3F);
    drawCorrect(85, 40, 0xFC);
    drawCorrect(85, 44, 0x0F);
    drawCorrect(86, 40, 0xF0);
}