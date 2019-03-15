//
// Created by torben on 11/03/19.
//

#include "sprites.h"
#include "draw.h"

void printPlayer(int16_t x, int16_t y, int16_t lastY) {

    if (y != lastY) {

        drawCorrect(x + 0, lastY + 4, 0);
        drawCorrect(x + 0, lastY + 0, 0);
        drawCorrect(x + 1, lastY + 4, 0);
        drawCorrect(x + 1, lastY + 0, 0);
        drawCorrect(x + 2, lastY + 4, 0);
        drawCorrect(x + 2, lastY + 0, 0);
        drawCorrect(x + 3, lastY + 4, 0);
        drawCorrect(x + 3, lastY + 0, 0);
        drawCorrect(x + 4, lastY + 4, 0);
        drawCorrect(x + 4, lastY + 0, 0);
        drawCorrect(x + 5, lastY + 4, 0);
        drawCorrect(x + 5, lastY + 0, 0);
        drawCorrect(x + 6, lastY + 4, 0);
        drawCorrect(x + 6, lastY + 0, 0);
        drawCorrect(x + 7, lastY + 0, 0);
        drawCorrect(x + 7, lastY + 4, 0);


        drawCorrect(x + 0, y + 4, 0xF8);
        drawCorrect(x + 1, y + 0, 0x02);
        drawCorrect(x + 1, y + 4, 0x02);
        drawCorrect(x + 2, y + 0, 0xAA);
        drawCorrect(x + 2, y + 4, 0xAE);
        drawCorrect(x + 3, y + 0, 0x7A);
        drawCorrect(x + 3, y + 4, 0x2E);
        drawCorrect(x + 4, y + 0, 0x5A);
        drawCorrect(x + 4, y + 4, 0x2E);
        drawCorrect(x + 5, y + 0, 0x78);
        drawCorrect(x + 5, y + 4, 0xAE);
        drawCorrect(x + 6, y + 0, 0x03);
        drawCorrect(x + 6, y + 4, 0xC2);
        drawCorrect(x + 7, y + 0, 0xFC);
        drawCorrect(x + 7, y + 4, 0x3D);


    }
}

