//
// Created by torben on 11/03/19.
//

#include "sprites.h"
#include "draw.h"

void printPlayer(uint8_t x, uint8_t y){


    drawCorrect(x + 0, y + 0, 0x3C);
    drawCorrect(x + 0, y + 4, 0x3F);
    drawCorrect(x + 1, y + 0, 0x08);
    drawCorrect(x + 1, y + 4, 0x57);
    drawCorrect(x + 2, y + 0, 0x0A);
    drawCorrect(x + 2, y + 4, 0x57);
    drawCorrect(x + 3, y + 0, 0x0A);
    drawCorrect(x + 3, y + 4, 0x57);
    drawCorrect(x + 4, y + 0, 0x0A);
    drawCorrect(x + 4, y + 4, 0x5B);
    drawCorrect(x + 5, y + 0, 0xEA);
    drawCorrect(x + 5, y + 4, 0x57);
    drawCorrect(x + 6, y + 0, 0xC2);
    drawCorrect(x + 6, y + 4, 0x03);
    drawCorrect(x + 7, y + 0, 0x02);


}