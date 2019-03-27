//
// Created by torben on 11/03/19.
//

#include <stdlib.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "sprites.h"
#include "draw.h"
#include "platform.h"

void clearPlayer(int16_t x, int16_t y) {

    for (uint8_t i = 0; i <= 16; i++) {
        for (uint8_t j = 0; j <= 12; j += 4) {
            drawCorrect(x + i, y + j, 0);
        }
    }
}

void printDash(uint8_t x, uint8_t y) {
    drawCorrect(x + 0, y + 4, 0x03);
    drawCorrect(x + 0, y + 8, 0xC0);
    drawCorrect(x + 1, y + 0, 0x04);
    drawCorrect(x + 1, y + 4, 0x33);
    drawCorrect(x + 1, y + 8, 0xC0);
    drawCorrect(x + 1, y + 12, 0x10);
    drawCorrect(x + 2, y + 0, 0x04);
    drawCorrect(x + 2, y + 4, 0x33);
    drawCorrect(x + 2, y + 8, 0xCC);
    drawCorrect(x + 2, y + 12, 0x10);
    drawCorrect(x + 3, y + 0, 0x34);
    drawCorrect(x + 3, y + 4, 0x33);
    drawCorrect(x + 3, y + 8, 0xCC);
    drawCorrect(x + 3, y + 12, 0x0C);
    drawCorrect(x + 4, y + 0, 0x30);
    drawCorrect(x + 4, y + 4, 0x03);
    drawCorrect(x + 4, y + 8, 0xCC);
    drawCorrect(x + 4, y + 12, 0x0C);
    drawCorrect(x + 5, y + 0, 0x30);
    drawCorrect(x + 5, y + 4, 0x43);
    drawCorrect(x + 5, y + 8, 0xC0);
    drawCorrect(x + 5, y + 12, 0x0C);
    drawCorrect(x + 6, y + 0, 0x30);
    drawCorrect(x + 6, y + 12, 0x0C);
    drawCorrect(x + 7, y + 4, 0x04);
    drawCorrect(x + 7, y + 8, 0x10);
    drawCorrect(x + 8, y + 0, 0x0C);
    drawCorrect(x + 8, y + 8, 0x41);
    drawCorrect(x + 8, y + 12, 0x30);
    drawCorrect(x + 9, y + 0, 0x0C);
    drawCorrect(x + 9, y + 8, 0x01);
    drawCorrect(x + 9, y + 12, 0x30);
    drawCorrect(x + 10, y + 0, 0x0C);
    drawCorrect(x + 10, y + 4, 0x02);
    drawCorrect(x + 10, y + 8, 0x80);
    drawCorrect(x + 10, y + 12, 0x30);
    drawCorrect(x + 11, y + 0, 0x30);
    drawCorrect(x + 11, y + 4, 0x02);
    drawCorrect(x + 11, y + 8, 0x80);
    drawCorrect(x + 11, y + 12, 0x0C);
    drawCorrect(x + 12, y + 0, 0x33);
    drawCorrect(x + 12, y + 4, 0x20);
    drawCorrect(x + 12, y + 8, 0x08);
    drawCorrect(x + 12, y + 12, 0xCC);
    drawCorrect(x + 13, y + 0, 0xC3);
    drawCorrect(x + 13, y + 12, 0xC3);
    drawCorrect(x + 14, y + 0, 0x0C);
    drawCorrect(x + 14, y + 4, 0x03);
    drawCorrect(x + 14, y + 8, 0xC0);
    drawCorrect(x + 14, y + 12, 0x30);
    drawCorrect(x + 15, y + 0, 0x30);
    drawCorrect(x + 15, y + 4, 0xFC);
    drawCorrect(x + 15, y + 8, 0x3F);
    drawCorrect(x + 15, y + 12, 0x0C);
}

#define SWITCH 6

void printNormal(uint8_t x, uint8_t y, uint8_t frameCounter) {
    if (frameCounter < SWITCH) {
        drawCorrect(x + 0, y + 4, 0x50);
        drawCorrect(x + 1, y + 4, 0x50);
        drawCorrect(x + 2, y + 4, 0x14);
        drawCorrect(x + 2, y + 12, 0xA8);
        drawCorrect(x + 3, y + 4, 0x14);
        drawCorrect(x + 3, y + 12, 0x28);
        drawCorrect(x + 4, y + 4, 0xA8);
        drawCorrect(x + 4, y + 8, 0x02);
        drawCorrect(x + 4, y + 12, 0x29);
        drawCorrect(x + 5, y + 4, 0xA8);
        drawCorrect(x + 5, y + 8, 0x7A);
        drawCorrect(x + 5, y + 12, 0x05);
        drawCorrect(x + 6, y + 0, 0xFC);
        drawCorrect(x + 6, y + 4, 0xAB);
        drawCorrect(x + 6, y + 8, 0x7A);
        drawCorrect(x + 6, y + 12, 0x01);
        drawCorrect(x + 7, y + 0, 0xFC);
        drawCorrect(x + 7, y + 4, 0xAB);
        drawCorrect(x + 7, y + 8, 0x7A);
        drawCorrect(x + 8, y + 0, 0xDC);
        drawCorrect(x + 8, y + 4, 0xAB);
        drawCorrect(x + 8, y + 8, 0x7A);
        drawCorrect(x + 9, y + 0, 0x5C);
        drawCorrect(x + 9, y + 4, 0xAB);
        drawCorrect(x + 9, y + 8, 0x7A);
        drawCorrect(x + 9, y + 12, 0xA9);
        drawCorrect(x + 10, y + 4, 0xA8);
        drawCorrect(x + 10, y + 8, 0x42);
        drawCorrect(x + 10, y + 12, 0xA9);
        drawCorrect(x + 11, y + 4, 0x14);
        drawCorrect(x + 11, y + 12, 0x80);
        drawCorrect(x + 12, y + 4, 0x14);
        drawCorrect(x + 13, y + 4, 0x05);
        drawCorrect(x + 14, y + 4, 0x05);
    } else {
        drawCorrect(x + 4, y + 4, 0x54);
        drawCorrect(x + 4, y + 8, 0x05);
        drawCorrect(x + 5, y + 4, 0x54);
        drawCorrect(x + 5, y + 8, 0x75);
        drawCorrect(x + 5, y + 12, 0xA9);
        drawCorrect(x + 6, y + 0, 0xFC);
        drawCorrect(x + 6, y + 4, 0xAB);
        drawCorrect(x + 6, y + 8, 0x7A);
        drawCorrect(x + 6, y + 12, 0xA9);
        drawCorrect(x + 7, y + 0, 0xFC);
        drawCorrect(x + 7, y + 4, 0xAB);
        drawCorrect(x + 7, y + 8, 0x7A);
        drawCorrect(x + 7, y + 12, 0x80);
        drawCorrect(x + 8, y + 0, 0xDC);
        drawCorrect(x + 8, y + 4, 0xAB);
        drawCorrect(x + 8, y + 8, 0x7A);
        drawCorrect(x + 8, y + 12, 0xA9);
        drawCorrect(x + 9, y + 0, 0x5C);
        drawCorrect(x + 9, y + 4, 0xAB);
        drawCorrect(x + 9, y + 8, 0x7A);
        drawCorrect(x + 9, y + 12, 0xA9);
        drawCorrect(x + 10, y + 4, 0x54);
        drawCorrect(x + 10, y + 8, 0x05);
        drawCorrect(x + 10, y + 12, 0x80);
    }
}

void printSorcerer(uint8_t x, uint8_t y, uint8_t frameCounter) {
    if (frameCounter < SWITCH) {
        drawCorrect(x + 0, y + 4, 0x50);
        drawCorrect(x + 1, y + 4, 0x50);
        drawCorrect(x + 2, y + 4, 0x14);
        drawCorrect(x + 2, y + 12, 0xA8);
        drawCorrect(x + 3, y + 4, 0x14);
        drawCorrect(x + 3, y + 12, 0x54);
        drawCorrect(x + 4, y + 4, 0xA8);
        drawCorrect(x + 4, y + 8, 0x02);
        drawCorrect(x + 4, y + 12, 0x55);
        drawCorrect(x + 5, y + 4, 0xA8);
        drawCorrect(x + 5, y + 8, 0x7A);
        drawCorrect(x + 5, y + 12, 0x55);
        drawCorrect(x + 6, y + 0, 0x54);
        drawCorrect(x + 6, y + 4, 0xA9);
        drawCorrect(x + 6, y + 8, 0x7A);
        drawCorrect(x + 6, y + 12, 0x55);
        drawCorrect(x + 7, y + 0, 0x54);
        drawCorrect(x + 7, y + 4, 0xA5);
        drawCorrect(x + 7, y + 8, 0x7A);
        drawCorrect(x + 7, y + 12, 0x55);
        drawCorrect(x + 8, y + 0, 0x44);
        drawCorrect(x + 8, y + 4, 0x95);
        drawCorrect(x + 8, y + 8, 0x7A);
        drawCorrect(x + 8, y + 12, 0x55);
        drawCorrect(x + 9, y + 0, 0x04);
        drawCorrect(x + 9, y + 4, 0x55);
        drawCorrect(x + 9, y + 8, 0x7A);
        drawCorrect(x + 9, y + 12, 0x55);
        drawCorrect(x + 10, y + 4, 0x98);
        drawCorrect(x + 10, y + 8, 0x42);
        drawCorrect(x + 10, y + 12, 0x95);
        drawCorrect(x + 11, y + 4, 0x14);
        drawCorrect(x + 11, y + 12, 0x80);
        drawCorrect(x + 12, y + 4, 0x14);
        drawCorrect(x + 13, y + 0, 0x3C);
        drawCorrect(x + 13, y + 4, 0x14);
        drawCorrect(x + 13, y + 8, 0x3F);
        drawCorrect(x + 14, y + 0, 0xC3);
        drawCorrect(x + 14, y + 4, 0xD7);
        drawCorrect(x + 14, y + 8, 0xC3);
        drawCorrect(x + 14, y + 12, 0x03);
        drawCorrect(x + 15, y + 0, 0x3C);

    } else {
        drawCorrect(x + 4, y + 4, 0x54);
        drawCorrect(x + 4, y + 8, 0x05);
        drawCorrect(x + 5, y + 4, 0x54);
        drawCorrect(x + 5, y + 8, 0x75);
        drawCorrect(x + 5, y + 12, 0x95);
        drawCorrect(x + 6, y + 0, 0x54);
        drawCorrect(x + 6, y + 4, 0xA9);
        drawCorrect(x + 6, y + 8, 0x7A);
        drawCorrect(x + 6, y + 12, 0x95);
        drawCorrect(x + 7, y + 0, 0x54);
        drawCorrect(x + 7, y + 4, 0xA5);
        drawCorrect(x + 7, y + 8, 0x7A);
        drawCorrect(x + 7, y + 12, 0x95);
        drawCorrect(x + 8, y + 0, 0x44);
        drawCorrect(x + 8, y + 4, 0x95);
        drawCorrect(x + 8, y + 8, 0x7A);
        drawCorrect(x + 8, y + 12, 0x95);
        drawCorrect(x + 9, y + 0, 0x04);
        drawCorrect(x + 9, y + 4, 0x55);
        drawCorrect(x + 9, y + 8, 0x7A);
        drawCorrect(x + 9, y + 12, 0x95);
        drawCorrect(x + 10, y + 4, 0x54);
        drawCorrect(x + 10, y + 8, 0x05);
        drawCorrect(x + 10, y + 12, 0x80);
        drawCorrect(x + 11, y + 8, 0x0C);
        drawCorrect(x + 12, y + 8, 0x0C);
        drawCorrect(x + 13, y + 8, 0x33);
        drawCorrect(x + 14, y + 8, 0x33);
        drawCorrect(x + 15, y + 8, 0x0C);

    }
}

void printRanger(uint8_t x, uint8_t y, uint8_t frameCounter) {
    if (frameCounter < SWITCH) {
        drawCorrect(x + 0, y + 4, 0x50);
        drawCorrect(x + 1, y + 4, 0x50);
        drawCorrect(x + 2, y + 4, 0x14);
        drawCorrect(x + 2, y + 12, 0xA8);
        drawCorrect(x + 3, y + 4, 0x3C);
        drawCorrect(x + 3, y + 12, 0x28);
        drawCorrect(x + 4, y + 0, 0xC0);
        drawCorrect(x + 4, y + 4, 0xFF);
        drawCorrect(x + 4, y + 8, 0x03);
        drawCorrect(x + 4, y + 12, 0x29);
        drawCorrect(x + 5, y + 0, 0xF0);
        drawCorrect(x + 5, y + 4, 0xFF);
        drawCorrect(x + 5, y + 8, 0x7F);
        drawCorrect(x + 5, y + 12, 0x05);
        drawCorrect(x + 6, y + 0, 0xFC);
        drawCorrect(x + 6, y + 4, 0xFF);
        drawCorrect(x + 6, y + 8, 0x7F);
        drawCorrect(x + 6, y + 12, 0x01);
        drawCorrect(x + 7, y + 0, 0xFC);
        drawCorrect(x + 7, y + 4, 0xFF);
        drawCorrect(x + 7, y + 8, 0x7F);
        drawCorrect(x + 8, y + 0, 0xDC);
        drawCorrect(x + 8, y + 4, 0xFF);
        drawCorrect(x + 8, y + 8, 0x7F);
        drawCorrect(x + 9, y + 0, 0x5C);
        drawCorrect(x + 9, y + 4, 0xFF);
        drawCorrect(x + 9, y + 8, 0x7F);
        drawCorrect(x + 9, y + 12, 0xA9);
        drawCorrect(x + 10, y + 4, 0xFC);
        drawCorrect(x + 10, y + 8, 0x43);
        drawCorrect(x + 10, y + 12, 0xA9);
        drawCorrect(x + 11, y + 4, 0x3C);
        drawCorrect(x + 11, y + 12, 0x80);
        drawCorrect(x + 12, y + 0, 0x03);
        drawCorrect(x + 12, y + 4, 0x14);
        drawCorrect(x + 12, y + 8, 0xC0);
        drawCorrect(x + 13, y + 0, 0x0C);
        drawCorrect(x + 13, y + 4, 0x14);
        drawCorrect(x + 13, y + 8, 0x30);
        drawCorrect(x + 14, y + 0, 0x0C);
        drawCorrect(x + 14, y + 4, 0x14);
        drawCorrect(x + 14, y + 8, 0x30);
        drawCorrect(x + 15, y + 0, 0xF0);
        drawCorrect(x + 15, y + 4, 0xC3);
        drawCorrect(x + 15, y + 8, 0x0F);

    } else {
        drawCorrect(x + 4, y + 0, 0xC0);
        drawCorrect(x + 4, y + 4, 0x5F);
        drawCorrect(x + 4, y + 8, 0x05);
        drawCorrect(x + 5, y + 0, 0xF0);
        drawCorrect(x + 5, y + 4, 0x5F);
        drawCorrect(x + 5, y + 8, 0x75);
        drawCorrect(x + 5, y + 12, 0xA9);
        drawCorrect(x + 6, y + 0, 0xFC);
        drawCorrect(x + 6, y + 4, 0xFF);
        drawCorrect(x + 6, y + 8, 0x7F);
        drawCorrect(x + 6, y + 12, 0xA9);
        drawCorrect(x + 7, y + 0, 0xFC);
        drawCorrect(x + 7, y + 4, 0xFF);
        drawCorrect(x + 7, y + 8, 0x7F);
        drawCorrect(x + 7, y + 12, 0x80);
        drawCorrect(x + 8, y + 0, 0xDC);
        drawCorrect(x + 8, y + 4, 0xFF);
        drawCorrect(x + 8, y + 8, 0x7F);
        drawCorrect(x + 8, y + 12, 0xA9);
        drawCorrect(x + 9, y + 0, 0x5C);
        drawCorrect(x + 9, y + 4, 0xFF);
        drawCorrect(x + 9, y + 8, 0x7F);
        drawCorrect(x + 9, y + 12, 0xA9);
        drawCorrect(x + 10, y + 4, 0x5C);
        drawCorrect(x + 10, y + 8, 0x05);
        drawCorrect(x + 10, y + 12, 0x80);
        drawCorrect(x + 11, y + 8, 0x30);
        drawCorrect(x + 12, y + 8, 0x30);
        drawCorrect(x + 13, y + 8, 0x30);
        drawCorrect(x + 14, y + 8, 0x0F);
        drawCorrect(x + 15, y + 4, 0xC0);

    }
}

void printKnight(uint8_t x, uint8_t y,uint8_t frameCounter) {
    if (frameCounter < SWITCH) {
        drawCorrect(x + 0, y + 8, 0x02);
        drawCorrect(x + 1, y + 4, 0x40);
        drawCorrect(x + 1, y + 8, 0x05);
        drawCorrect(x + 1, y + 12, 0x02);
        drawCorrect(x + 2, y + 4, 0x68);
        drawCorrect(x + 2, y + 8, 0xA5);
        drawCorrect(x + 2, y + 12, 0xFC);
        drawCorrect(x + 3, y + 4, 0x28);
        drawCorrect(x + 3, y + 8, 0x60);
        drawCorrect(x + 3, y + 12, 0x3D);
        drawCorrect(x + 4, y + 4, 0xFC);
        drawCorrect(x + 4, y + 8, 0x4B);
        drawCorrect(x + 4, y + 12, 0x35);
        drawCorrect(x + 5, y + 0, 0x03);
        drawCorrect(x + 5, y + 4, 0xFC);
        drawCorrect(x + 5, y + 8, 0xBF);
        drawCorrect(x + 5, y + 12, 0x15);
        drawCorrect(x + 6, y + 0, 0xFF);
        drawCorrect(x + 6, y + 4, 0xFF);
        drawCorrect(x + 6, y + 8, 0xBF);
        drawCorrect(x + 6, y + 12, 0x56);
        drawCorrect(x + 7, y + 0, 0xFF);
        drawCorrect(x + 7, y + 4, 0xFF);
        drawCorrect(x + 7, y + 8, 0xBF);
        drawCorrect(x + 7, y + 12, 0x50);
        drawCorrect(x + 8, y + 0, 0xDF);
        drawCorrect(x + 8, y + 4, 0xFF);
        drawCorrect(x + 8, y + 8, 0xBF);
        drawCorrect(x + 9, y + 0, 0x5C);
        drawCorrect(x + 9, y + 4, 0xFF);
        drawCorrect(x + 9, y + 8, 0xBF);
        drawCorrect(x + 9, y + 12, 0xFE);
        drawCorrect(x + 10, y + 4, 0xFC);
        drawCorrect(x + 10, y + 8, 0x83);
        drawCorrect(x + 10, y + 12, 0xFE);
        drawCorrect(x + 11, y + 0, 0xC0);
        drawCorrect(x + 11, y + 4, 0xFF);
        drawCorrect(x + 11, y + 8, 0xFF);
        drawCorrect(x + 11, y + 12, 0xC0);
        drawCorrect(x + 12, y + 0, 0xB0);
        drawCorrect(x + 12, y + 4, 0xAA);
        drawCorrect(x + 12, y + 8, 0xAA);
        drawCorrect(x + 12, y + 12, 0x03);
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

    } else {

        drawCorrect(x + 3, y + 4, 0x80);
        drawCorrect(x + 4, y + 4, 0x68);
        drawCorrect(x + 4, y + 8, 0x85);
        drawCorrect(x + 5, y + 0, 0x03);
        drawCorrect(x + 5, y + 4, 0x68);
        drawCorrect(x + 5, y + 8, 0xA9);
        drawCorrect(x + 5, y + 12, 0xFE);
        drawCorrect(x + 6, y + 0, 0xFF);
        drawCorrect(x + 6, y + 4, 0xFF);
        drawCorrect(x + 6, y + 8, 0x5B);
        drawCorrect(x + 6, y + 12, 0xFE);
        drawCorrect(x + 7, y + 0, 0xFF);
        drawCorrect(x + 7, y + 4, 0xFF);
        drawCorrect(x + 7, y + 8, 0x5E);
        drawCorrect(x + 7, y + 12, 0xC1);
        drawCorrect(x + 8, y + 0, 0xDF);
        drawCorrect(x + 8, y + 4, 0xFF);
        drawCorrect(x + 8, y + 8, 0x7F);
        drawCorrect(x + 8, y + 12, 0xF5);
        drawCorrect(x + 9, y + 0, 0x5C);
        drawCorrect(x + 9, y + 4, 0xFF);
        drawCorrect(x + 9, y + 8, 0xBF);
        drawCorrect(x + 9, y + 12, 0xD5);
        drawCorrect(x + 10, y + 0, 0xC0);
        drawCorrect(x + 10, y + 4, 0xFF);
        drawCorrect(x + 10, y + 8, 0xFF);
        drawCorrect(x + 10, y + 12, 0xD4);
        drawCorrect(x + 11, y + 0, 0xB0);
        drawCorrect(x + 11, y + 4, 0xAA);
        drawCorrect(x + 11, y + 8, 0xAA);
        drawCorrect(x + 11, y + 12, 0x03);
        drawCorrect(x + 12, y + 0, 0x6C);
        drawCorrect(x + 12, y + 4, 0x75);
        drawCorrect(x + 12, y + 8, 0x55);
        drawCorrect(x + 12, y + 12, 0x0E);
        drawCorrect(x + 13, y + 0, 0x6C);
        drawCorrect(x + 13, y + 4, 0xFD);
        drawCorrect(x + 13, y + 8, 0x5F);
        drawCorrect(x + 13, y + 12, 0x0E);
        drawCorrect(x + 14, y + 0, 0xF0);
        drawCorrect(x + 14, y + 4, 0xFF);
        drawCorrect(x + 14, y + 8, 0xFF);
        drawCorrect(x + 14, y + 12, 0x03);

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

        drawCorrect(toDraw.x + i + 0, toDraw.y + 0, 0xFF);
        drawCorrect(toDraw.x + i + 0, toDraw.y + 4, 0x57);
        drawCorrect(toDraw.x + i + 1, toDraw.y + 0, 0xFF);
        drawCorrect(toDraw.x + i + 1, toDraw.y + 4, 0x55);
        drawCorrect(toDraw.x + i + 2, toDraw.y + 0, 0x7F);
        drawCorrect(toDraw.x + i + 2, toDraw.y + 4, 0x55);
        drawCorrect(toDraw.x + i + 3, toDraw.y + 0, 0xFF);
        drawCorrect(toDraw.x + i + 3, toDraw.y + 4, 0x57);
        drawCorrect(toDraw.x + i + 4, toDraw.y + 0, 0xFF);
        drawCorrect(toDraw.x + i + 4, toDraw.y + 4, 0x55);
        drawCorrect(toDraw.x + i + 5, toDraw.y + 0, 0x7F);
        drawCorrect(toDraw.x + i + 5, toDraw.y + 4, 0x55);
        drawCorrect(toDraw.x + i + 6, toDraw.y + 0, 0xFF);
        drawCorrect(toDraw.x + i + 6, toDraw.y + 4, 0x57);
        drawCorrect(toDraw.x + i + 7, toDraw.y + 0, 0xFF);
        drawCorrect(toDraw.x + i + 7, toDraw.y + 4, 0x55);
        drawCorrect(toDraw.x + i + 8, toDraw.y + 0, 0x7F);
        drawCorrect(toDraw.x + i + 8, toDraw.y + 4, 0x55);
        drawCorrect(toDraw.x + i + 9, toDraw.y + 0, 0xFF);
        drawCorrect(toDraw.x + i + 9, toDraw.y + 4, 0x57);
        drawCorrect(toDraw.x + i + 10, toDraw.y + 0, 0xFF);
        drawCorrect(toDraw.x + i + 10, toDraw.y + 4, 0x55);
        drawCorrect(toDraw.x + i + 11, toDraw.y + 0, 0x7F);
        drawCorrect(toDraw.x + i + 11, toDraw.y + 4, 0x55);
        drawCorrect(toDraw.x + i + 12, toDraw.y + 0, 0xFF);
        drawCorrect(toDraw.x + i + 12, toDraw.y + 4, 0x57);
        drawCorrect(toDraw.x + i + 13, toDraw.y + 0, 0xFF);
        drawCorrect(toDraw.x + i + 13, toDraw.y + 4, 0x55);
        drawCorrect(toDraw.x + i + 14, toDraw.y + 0, 0x7F);
        drawCorrect(toDraw.x + i + 14, toDraw.y + 4, 0x55);

/*
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
*/

    }

}

void clearPause() {
    drawCorrect(0, 96, 0);
    drawCorrect(0, 100, 0);
    drawCorrect(1, 96, 0);
    drawCorrect(1, 100, 0);

    drawCorrect(3, 96, 0);
    drawCorrect(3, 100, 0);
    drawCorrect(4, 96, 0);
    drawCorrect(4, 100, 0);
}

void printPause() {
    drawCorrect(0, 96, 0xFF);
    drawCorrect(0, 100, 0xFF);
    drawCorrect(1, 96, 0xFF);
    drawCorrect(1, 100, 0xFF);

    drawCorrect(3, 96, 0xFF);
    drawCorrect(3, 100, 0xFF);
    drawCorrect(4, 96, 0xFF);
    drawCorrect(4, 100, 0xFF);
}


void rePrintPlatform(struct platform toDraw, int16_t offsetX, int16_t speed) {


    // Clear behind platform
    for (int i = 0; i < speed; i++) {
        drawCorrect(toDraw.x + offsetX + toDraw.length + i, toDraw.y, 0);
        drawCorrect(toDraw.x + offsetX + toDraw.length + i, toDraw.y + 4, 0);

    }


    drawCorrect(toDraw.x + offsetX + 0, toDraw.y + 0, 0xFF);
    drawCorrect(toDraw.x + offsetX + 0, toDraw.y + 4, 0x57);
    drawCorrect(toDraw.x + offsetX + 1, toDraw.y + 0, 0xFF);
    drawCorrect(toDraw.x + offsetX + 1, toDraw.y + 4, 0x55);
    drawCorrect(toDraw.x + offsetX + 2, toDraw.y + 0, 0x7F);
    drawCorrect(toDraw.x + offsetX + 2, toDraw.y + 4, 0x55);
    drawCorrect(toDraw.x + offsetX + 3, toDraw.y + 0, 0xFF);
    drawCorrect(toDraw.x + offsetX + 3, toDraw.y + 4, 0x57);
    drawCorrect(toDraw.x + offsetX + 4, toDraw.y + 0, 0xFF);
    drawCorrect(toDraw.x + offsetX + 4, toDraw.y + 4, 0x55);
    drawCorrect(toDraw.x + offsetX + 5, toDraw.y + 0, 0x7F);
    drawCorrect(toDraw.x + offsetX + 5, toDraw.y + 4, 0x55);
    drawCorrect(toDraw.x + offsetX + 6, toDraw.y + 0, 0xFF);
    drawCorrect(toDraw.x + offsetX + 6, toDraw.y + 4, 0x57);
    drawCorrect(toDraw.x + offsetX + 7, toDraw.y + 0, 0xFF);
    drawCorrect(toDraw.x + offsetX + 7, toDraw.y + 4, 0x55);
    drawCorrect(toDraw.x + offsetX + 8, toDraw.y + 0, 0x7F);
    drawCorrect(toDraw.x + offsetX + 8, toDraw.y + 4, 0x55);
    drawCorrect(toDraw.x + offsetX + 9, toDraw.y + 0, 0xFF);
    drawCorrect(toDraw.x + offsetX + 9, toDraw.y + 4, 0x57);
    drawCorrect(toDraw.x + offsetX + 10, toDraw.y + 0, 0xFF);
    drawCorrect(toDraw.x + offsetX + 10, toDraw.y + 4, 0x55);
    drawCorrect(toDraw.x + offsetX + 11, toDraw.y + 0, 0x7F);
    drawCorrect(toDraw.x + offsetX + 11, toDraw.y + 4, 0x55);
    drawCorrect(toDraw.x + offsetX + 12, toDraw.y + 0, 0xFF);
    drawCorrect(toDraw.x + offsetX + 12, toDraw.y + 4, 0x57);
    drawCorrect(toDraw.x + offsetX + 13, toDraw.y + 0, 0xFF);
    drawCorrect(toDraw.x + offsetX + 13, toDraw.y + 4, 0x55);
    drawCorrect(toDraw.x + offsetX + 14, toDraw.y + 0, 0x7F);
    drawCorrect(toDraw.x + offsetX + 14, toDraw.y + 4, 0x55);


    drawCorrect(toDraw.x + offsetX + toDraw.length - 15 + 0, toDraw.y + 0, 0xFF);
    drawCorrect(toDraw.x + offsetX + toDraw.length - 15 + 0, toDraw.y + 4, 0x57);
    drawCorrect(toDraw.x + offsetX + toDraw.length - 15 + 1, toDraw.y + 0, 0xFF);
    drawCorrect(toDraw.x + offsetX + toDraw.length - 15 + 1, toDraw.y + 4, 0x55);
    drawCorrect(toDraw.x + offsetX + toDraw.length - 15 + 2, toDraw.y + 0, 0x7F);
    drawCorrect(toDraw.x + offsetX + toDraw.length - 15 + 2, toDraw.y + 4, 0x55);
    drawCorrect(toDraw.x + offsetX + toDraw.length - 15 + 3, toDraw.y + 0, 0xFF);
    drawCorrect(toDraw.x + offsetX + toDraw.length - 15 + 3, toDraw.y + 4, 0x57);
    drawCorrect(toDraw.x + offsetX + toDraw.length - 15 + 4, toDraw.y + 0, 0xFF);
    drawCorrect(toDraw.x + offsetX + toDraw.length - 15 + 4, toDraw.y + 4, 0x55);
    drawCorrect(toDraw.x + offsetX + toDraw.length - 15 + 5, toDraw.y + 0, 0x7F);
    drawCorrect(toDraw.x + offsetX + toDraw.length - 15 + 5, toDraw.y + 4, 0x55);
    drawCorrect(toDraw.x + offsetX + toDraw.length - 15 + 6, toDraw.y + 0, 0xFF);
    drawCorrect(toDraw.x + offsetX + toDraw.length - 15 + 6, toDraw.y + 4, 0x57);
    drawCorrect(toDraw.x + offsetX + toDraw.length - 15 + 7, toDraw.y + 0, 0xFF);
    drawCorrect(toDraw.x + offsetX + toDraw.length - 15 + 7, toDraw.y + 4, 0x55);
    drawCorrect(toDraw.x + offsetX + toDraw.length - 15 + 8, toDraw.y + 0, 0x7F);
    drawCorrect(toDraw.x + offsetX + toDraw.length - 15 + 8, toDraw.y + 4, 0x55);
    drawCorrect(toDraw.x + offsetX + toDraw.length - 15 + 9, toDraw.y + 0, 0xFF);
    drawCorrect(toDraw.x + offsetX + toDraw.length - 15 + 9, toDraw.y + 4, 0x57);
    drawCorrect(toDraw.x + offsetX + toDraw.length - 15 + 10, toDraw.y + 0, 0xFF);
    drawCorrect(toDraw.x + offsetX + toDraw.length - 15 + 10, toDraw.y + 4, 0x55);
    drawCorrect(toDraw.x + offsetX + toDraw.length - 15 + 11, toDraw.y + 0, 0x7F);
    drawCorrect(toDraw.x + offsetX + toDraw.length - 15 + 11, toDraw.y + 4, 0x55);
    drawCorrect(toDraw.x + offsetX + toDraw.length - 15 + 12, toDraw.y + 0, 0xFF);
    drawCorrect(toDraw.x + offsetX + toDraw.length - 15 + 12, toDraw.y + 4, 0x57);
    drawCorrect(toDraw.x + offsetX + toDraw.length - 15 + 13, toDraw.y + 0, 0xFF);
    drawCorrect(toDraw.x + offsetX + toDraw.length - 15 + 13, toDraw.y + 4, 0x55);
    drawCorrect(toDraw.x + offsetX + toDraw.length - 15 + 14, toDraw.y + 0, 0x7F);
    drawCorrect(toDraw.x + offsetX + toDraw.length - 15 + 14, toDraw.y + 4, 0x55);
}

void printPUlive(int16_t x, int16_t y) {
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
}

void printPUdeath(int16_t x, int16_t y) {
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
}

void printPUknight(int16_t x, int16_t y) {
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
}

void printPUsorcerer(int16_t x, int16_t y) {
    drawCorrect(x + 0, y + 0, 0x54);
    drawCorrect(x + 0, y + 4, 0x15);
    drawCorrect(x + 1, y + 0, 0x5D);
    drawCorrect(x + 1, y + 4, 0xFD);
    drawCorrect(x + 2, y + 0, 0x77);
    drawCorrect(x + 2, y + 4, 0xF7);
    drawCorrect(x + 3, y + 0, 0x77);
    drawCorrect(x + 3, y + 4, 0xDD);
    drawCorrect(x + 4, y + 0, 0x77);
    drawCorrect(x + 4, y + 4, 0xD5);
    drawCorrect(x + 5, y + 0, 0x5D);
    drawCorrect(x + 5, y + 4, 0xD5);
    drawCorrect(x + 6, y + 0, 0xF7);
    drawCorrect(x + 6, y + 4, 0xFF);
    drawCorrect(x + 7, y + 0, 0x54);
    drawCorrect(x + 7, y + 4, 0x15);
}

void printPUranger(int16_t x, int16_t y) {
    drawCorrect(x + 0, y + 0, 0x74);
    drawCorrect(x + 0, y + 4, 0x15);
    drawCorrect(x + 1, y + 0, 0xDD);
    drawCorrect(x + 1, y + 4, 0x55);
    drawCorrect(x + 2, y + 0, 0xF5);
    drawCorrect(x + 2, y + 4, 0xFF);
    drawCorrect(x + 3, y + 0, 0x55);
    drawCorrect(x + 3, y + 4, 0xD5);
    drawCorrect(x + 4, y + 0, 0x55);
    drawCorrect(x + 4, y + 4, 0xD5);
    drawCorrect(x + 5, y + 0, 0x55);
    drawCorrect(x + 5, y + 4, 0xD5);
    drawCorrect(x + 6, y + 0, 0xFF);
    drawCorrect(x + 6, y + 4, 0xFF);
    drawCorrect(x + 7, y + 0, 0x54);
    drawCorrect(x + 7, y + 4, 0x15);
}

void printPUslow(int16_t x, int16_t y) {
    drawCorrect(x + 0, y + 0, 0xFC);
    drawCorrect(x + 0, y + 4, 0x3F);
    drawCorrect(x + 1, y + 0, 0x57);
    drawCorrect(x + 1, y + 4, 0xD5);
    drawCorrect(x + 2, y + 0, 0x57);
    drawCorrect(x + 2, y + 4, 0x77);
    drawCorrect(x + 3, y + 0, 0xDD);
    drawCorrect(x + 3, y + 4, 0x5D);
    drawCorrect(x + 4, y + 0, 0x57);
    drawCorrect(x + 4, y + 4, 0x57);
    drawCorrect(x + 5, y + 0, 0x57);
    drawCorrect(x + 5, y + 4, 0x55);
    drawCorrect(x + 6, y + 0, 0xFD);
    drawCorrect(x + 6, y + 4, 0x7F);
    drawCorrect(x + 7, y + 0, 0x54);
    drawCorrect(x + 7, y + 4, 0x15);
}

void printPUspeedUp(int16_t x, int16_t y) {
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
}

void printPUpointsUp(int16_t x, int16_t y) {
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
}

void printPUpointsDown(int16_t x, int16_t y) {
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
}


void clearPowerUp(int16_t x, int16_t y) {
    for (uint8_t i = 0; i <= 7; i++) {
        drawCorrect(x + i, y + 0, 0);
        drawCorrect(x + i, y + 4, 0);
    }
}

void printArrow(uint8_t x, uint8_t y) {
    drawCorrect(x + 0, y + 0, 0xC0);
    drawCorrect(x + 0, y + 4, 0x0C);
    drawCorrect(x + 1, y + 0, 0xC0);
    drawCorrect(x + 1, y + 4, 0x0C);
    drawCorrect(x + 2, y + 0, 0xC0);
    drawCorrect(x + 2, y + 4, 0x0C);
    drawCorrect(x + 3, y + 0, 0xC0);
    drawCorrect(x + 3, y + 4, 0x0C);
    drawCorrect(x + 4, y + 0, 0xC0);
    drawCorrect(x + 4, y + 4, 0x0C);
    drawCorrect(x + 5, y + 0, 0x0C);
    drawCorrect(x + 5, y + 4, 0xC0);
    drawCorrect(x + 6, y + 0, 0x3C);
    drawCorrect(x + 6, y + 4, 0xF0);
    drawCorrect(x + 7, y + 0, 0xF0);
    drawCorrect(x + 7, y + 4, 0x3C);
    drawCorrect(x + 8, y + 0, 0xC0);
    drawCorrect(x + 8, y + 4, 0x0F);
    drawCorrect(x + 9, y + 4, 0x03);

}

void clearArrow(uint8_t x, uint8_t y) {
    drawCorrect(x + 0, y + 0, 0x00);
    drawCorrect(x + 0, y + 4, 0x00);
    drawCorrect(x + 1, y + 0, 0x00);
    drawCorrect(x + 1, y + 4, 0x00);
    drawCorrect(x + 2, y + 0, 0x00);
    drawCorrect(x + 2, y + 4, 0x00);
    drawCorrect(x + 3, y + 0, 0x00);
    drawCorrect(x + 3, y + 4, 0x00);
    drawCorrect(x + 4, y + 0, 0x00);
    drawCorrect(x + 4, y + 4, 0x00);
    drawCorrect(x + 5, y + 0, 0x00);
    drawCorrect(x + 5, y + 4, 0x00);
    drawCorrect(x + 6, y + 0, 0x00);
    drawCorrect(x + 6, y + 4, 0x00);
    drawCorrect(x + 7, y + 0, 0x00);
    drawCorrect(x + 7, y + 4, 0x00);
    drawCorrect(x + 8, y + 0, 0x00);
    drawCorrect(x + 8, y + 4, 0x00);
    drawCorrect(x + 9, y + 4, 0x00);
}

void printGlyph(char glyph, uint8_t x, uint8_t y) {
    switch (glyph) {
        case '0':
            drawCorrect(x + 0, y + 0, 0xF0);
            drawCorrect(x + 0, y + 4, 0x3F);
            drawCorrect(x + 1, y + 0, 0x0C);
            drawCorrect(x + 1, y + 4, 0xCC);
            drawCorrect(x + 2, y + 0, 0x0C);
            drawCorrect(x + 2, y + 4, 0xC3);
            drawCorrect(x + 3, y + 0, 0xF0);
            drawCorrect(x + 3, y + 4, 0x3F);
            break;
        case '1':
            drawCorrect(x + 0, y + 0, 0x30);
            drawCorrect(x + 0, y + 4, 0xC0);
            drawCorrect(x + 1, y + 0, 0xFC);
            drawCorrect(x + 1, y + 4, 0xFF);
            drawCorrect(x + 2, y + 0, 0x00);
            drawCorrect(x + 2, y + 4, 0xC0);
            drawCorrect(x + 3, y + 0, 0);
            drawCorrect(x + 3, y + 4, 0);

            break;
        case '2':
            drawCorrect(x + 0, y + 0, 0x30);
            drawCorrect(x + 0, y + 4, 0xF0);
            drawCorrect(x + 1, y + 0, 0x0C);
            drawCorrect(x + 1, y + 4, 0xCC);
            drawCorrect(x + 2, y + 0, 0x0C);
            drawCorrect(x + 2, y + 4, 0xC3);
            drawCorrect(x + 3, y + 0, 0xF0);
            drawCorrect(x + 3, y + 4, 0xC0);
            break;
        case '3':
            drawCorrect(x + 0, y + 0, 0x30);
            drawCorrect(x + 0, y + 4, 0x30);
            drawCorrect(x + 1, y + 0, 0x0C);
            drawCorrect(x + 1, y + 4, 0xC0);
            drawCorrect(x + 2, y + 0, 0x0C);
            drawCorrect(x + 2, y + 4, 0xC3);
            drawCorrect(x + 3, y + 0, 0xF0);
            drawCorrect(x + 3, y + 4, 0x3C);
            break;
        case '4':
            drawCorrect(x + 0, y + 0, 0xC0);
            drawCorrect(x + 0, y + 4, 0x0F);
            drawCorrect(x + 1, y + 0, 0x30);
            drawCorrect(x + 1, y + 4, 0x0C);
            drawCorrect(x + 2, y + 0, 0xFC);
            drawCorrect(x + 2, y + 4, 0xFF);
            drawCorrect(x + 3, y + 4, 0x0C);
            drawCorrect(x + 3, y + 0, 0);
            break;
        case '5':
            drawCorrect(x + 0, y + 0, 0xFC);
            drawCorrect(x + 0, y + 4, 0xC3);
            drawCorrect(x + 1, y + 0, 0x0C);
            drawCorrect(x + 1, y + 4, 0xC3);
            drawCorrect(x + 2, y + 0, 0x0C);
            drawCorrect(x + 2, y + 4, 0xC3);
            drawCorrect(x + 3, y + 0, 0x0C);
            drawCorrect(x + 3, y + 4, 0xFF);
            break;
        case '6':
            drawCorrect(x + 0, y + 0, 0xC0);
            drawCorrect(x + 0, y + 4, 0x3F);
            drawCorrect(x + 1, y + 0, 0x30);
            drawCorrect(x + 1, y + 4, 0xC3);
            drawCorrect(x + 2, y + 0, 0x0C);
            drawCorrect(x + 2, y + 4, 0xC3);
            drawCorrect(x + 3, y + 0, 0x0C);
            drawCorrect(x + 3, y + 4, 0x3C);
            break;
        case '7':
            drawCorrect(x + 0, y + 0, 0x3C);
            drawCorrect(x + 1, y + 0, 0x0C);
            drawCorrect(x + 1, y + 4, 0xFC);
            drawCorrect(x + 2, y + 0, 0x0C);
            drawCorrect(x + 2, y + 4, 0x03);
            drawCorrect(x + 3, y + 0, 0xFC);
            drawCorrect(x + 0, y + 4, 0);
            drawCorrect(x + 3, y + 4, 0);
            break;
        case '8':
            drawCorrect(x + 0, y + 0, 0xF0);
            drawCorrect(x + 0, y + 4, 0x3C);
            drawCorrect(x + 1, y + 0, 0x0C);
            drawCorrect(x + 1, y + 4, 0xC3);
            drawCorrect(x + 2, y + 0, 0x0C);
            drawCorrect(x + 2, y + 4, 0xC3);
            drawCorrect(x + 3, y + 0, 0xF0);
            drawCorrect(x + 3, y + 4, 0x3C);
            break;
        case '9':
            drawCorrect(x + 0, y + 0, 0xF0);
            drawCorrect(x + 1, y + 0, 0x0C);
            drawCorrect(x + 1, y + 4, 0xC3);
            drawCorrect(x + 2, y + 0, 0x0C);
            drawCorrect(x + 2, y + 4, 0xC3);
            drawCorrect(x + 3, y + 0, 0xF0);
            drawCorrect(x + 3, y + 4, 0x3F);
            drawCorrect(x + 0, y + 4, 0);
            break;
        case 'A':
            drawCorrect(x + 0, y + 0, 0xF0);
            drawCorrect(x + 0, y + 4, 0xFF);
            drawCorrect(x + 1, y + 0, 0x0C);
            drawCorrect(x + 1, y + 4, 0x03);
            drawCorrect(x + 2, y + 0, 0x0C);
            drawCorrect(x + 2, y + 4, 0x03);
            drawCorrect(x + 3, y + 0, 0x0C);
            drawCorrect(x + 3, y + 4, 0x03);
            drawCorrect(x + 4, y + 0, 0xF0);
            drawCorrect(x + 4, y + 4, 0xFF);
            break;
        case 'B':
            drawCorrect(x + 0, y + 0, 0xFC);
            drawCorrect(x + 0, y + 4, 0xFF);
            drawCorrect(x + 1, y + 0, 0x0C);
            drawCorrect(x + 1, y + 4, 0xC3);
            drawCorrect(x + 2, y + 0, 0x0C);
            drawCorrect(x + 2, y + 4, 0xC3);
            drawCorrect(x + 3, y + 0, 0x0C);
            drawCorrect(x + 3, y + 4, 0xC3);
            drawCorrect(x + 4, y + 0, 0xF0);
            drawCorrect(x + 4, y + 4, 0x3C);
            break;
        case 'C':
            drawCorrect(x + 0, y + 0, 0xF0);
            drawCorrect(x + 0, y + 4, 0x3F);
            drawCorrect(x + 1, y + 0, 0x0C);
            drawCorrect(x + 1, y + 4, 0xC0);
            drawCorrect(x + 2, y + 0, 0x0C);
            drawCorrect(x + 2, y + 4, 0xC0);
            drawCorrect(x + 3, y + 0, 0x0C);
            drawCorrect(x + 3, y + 4, 0xC0);
            drawCorrect(x + 4, y + 0, 0x30);
            drawCorrect(x + 4, y + 4, 0x30);
            break;
        case 'D':
            drawCorrect(x + 0, y + 0, 0xFC);
            drawCorrect(x + 0, y + 4, 0xFF);
            drawCorrect(x + 1, y + 0, 0x0C);
            drawCorrect(x + 1, y + 4, 0xC0);
            drawCorrect(x + 2, y + 0, 0x0C);
            drawCorrect(x + 2, y + 4, 0xC0);
            drawCorrect(x + 3, y + 0, 0x0C);
            drawCorrect(x + 3, y + 4, 0xC0);
            drawCorrect(x + 4, y + 0, 0xF0);
            drawCorrect(x + 4, y + 4, 0x3F);
            break;
        case 'E':
            drawCorrect(x + 0, y + 0, 0xFC);
            drawCorrect(x + 0, y + 4, 0xFF);
            drawCorrect(x + 1, y + 0, 0x0C);
            drawCorrect(x + 1, y + 4, 0xC3);
            drawCorrect(x + 2, y + 0, 0x0C);
            drawCorrect(x + 2, y + 4, 0xC3);
            drawCorrect(x + 3, y + 0, 0x0C);
            drawCorrect(x + 3, y + 4, 0xC3);
            drawCorrect(x + 4, y + 0, 0x0C);
            drawCorrect(x + 4, y + 4, 0xC0);
            break;
        case 'F':
            drawCorrect(x + 0, y + 0, 0xFC);
            drawCorrect(x + 0, y + 4, 0xFF);
            drawCorrect(x + 1, y + 0, 0x0C);
            drawCorrect(x + 1, y + 4, 0x03);
            drawCorrect(x + 2, y + 0, 0x0C);
            drawCorrect(x + 2, y + 4, 0x03);
            drawCorrect(x + 3, y + 0, 0x0C);
            drawCorrect(x + 3, y + 4, 0x03);
            drawCorrect(x + 4, y + 0, 0x0C);
            break;
        case 'G':
            drawCorrect(x + 0, y + 0, 0xF0);
            drawCorrect(x + 0, y + 4, 0x3F);
            drawCorrect(x + 1, y + 0, 0x0C);
            drawCorrect(x + 1, y + 4, 0xC0);
            drawCorrect(x + 2, y + 0, 0x0C);
            drawCorrect(x + 2, y + 4, 0xC3);
            drawCorrect(x + 3, y + 0, 0x0C);
            drawCorrect(x + 3, y + 4, 0xC3);
            drawCorrect(x + 4, y + 0, 0x30);
            drawCorrect(x + 4, y + 4, 0x3C);
            break;
        case 'H':
            drawCorrect(x + 0, y + 0, 0xFC);
            drawCorrect(x + 0, y + 4, 0xFF);
            drawCorrect(x + 1, y + 4, 0x03);
            drawCorrect(x + 2, y + 4, 0x03);
            drawCorrect(x + 3, y + 4, 0x03);
            drawCorrect(x + 4, y + 0, 0xFC);
            drawCorrect(x + 4, y + 4, 0xFF);
            break;
        case 'I':
            drawCorrect(x + 0, y + 0, 0x0C);
            drawCorrect(x + 0, y + 4, 0xC0);
            drawCorrect(x + 1, y + 0, 0xFC);
            drawCorrect(x + 1, y + 4, 0xFF);
            drawCorrect(x + 2, y + 0, 0x0C);
            drawCorrect(x + 2, y + 4, 0xC0);
            break;
        case 'J':
            drawCorrect(x + 0, y + 0, 0x0C);
            drawCorrect(x + 0, y + 4, 0x30);
            drawCorrect(x + 1, y + 0, 0x0C);
            drawCorrect(x + 1, y + 4, 0xC0);
            drawCorrect(x + 2, y + 0, 0x0C);
            drawCorrect(x + 2, y + 4, 0xC0);
            drawCorrect(x + 3, y + 0, 0xFC);
            drawCorrect(x + 3, y + 4, 0x3F);
            break;
        case 'K':
            drawCorrect(x + 0, y + 0, 0xFC);
            drawCorrect(x + 0, y + 4, 0xFF);
            drawCorrect(x + 1, y + 0, 0x00);
            drawCorrect(x + 1, y + 4, 0x03);
            drawCorrect(x + 2, y + 0, 0xC0);
            drawCorrect(x + 2, y + 4, 0x0C);
            drawCorrect(x + 3, y + 0, 0x3C);
            drawCorrect(x + 3, y + 4, 0xF0);
            break;
        case 'L':
            drawCorrect(x + 0, y + 0, 0xFC);
            drawCorrect(x + 0, y + 4, 0xFF);
            drawCorrect(x + 1, y + 4, 0xC0);
            drawCorrect(x + 2, y + 4, 0xC0);
            drawCorrect(x + 3, y + 4, 0xC0);
            drawCorrect(x + 4, y + 4, 0xC0);
            break;
        case 'M':
            drawCorrect(x + 0, y + 0, 0xFC);
            drawCorrect(x + 0, y + 4, 0xFF);
            drawCorrect(x + 1, y + 0, 0x30);
            drawCorrect(x + 2, y + 0, 0xC0);
            drawCorrect(x + 3, y + 0, 0x30);
            drawCorrect(x + 4, y + 0, 0xFC);
            drawCorrect(x + 4, y + 4, 0xFF);
            break;
        case 'N':
            drawCorrect(x + 0, y + 0, 0xFC);
            drawCorrect(x + 0, y + 4, 0xFF);
            drawCorrect(x + 1, y + 0, 0x30);
            drawCorrect(x + 2, y + 0, 0xC0);
            drawCorrect(x + 3, y + 4, 0x03);
            drawCorrect(x + 4, y + 0, 0xFC);
            drawCorrect(x + 4, y + 4, 0xFF);
            break;
        case 'O':
            drawCorrect(x + 0, y + 0, 0xF0);
            drawCorrect(x + 0, y + 4, 0x3F);
            drawCorrect(x + 1, y + 0, 0x0C);
            drawCorrect(x + 1, y + 4, 0xC0);
            drawCorrect(x + 2, y + 0, 0x0C);
            drawCorrect(x + 2, y + 4, 0xC0);
            drawCorrect(x + 3, y + 0, 0x0C);
            drawCorrect(x + 3, y + 4, 0xC0);
            drawCorrect(x + 4, y + 0, 0xF0);
            drawCorrect(x + 4, y + 4, 0x3F);
            break;
        case 'P':
            drawCorrect(x + 0, y + 0, 0xFC);
            drawCorrect(x + 0, y + 4, 0xFF);
            drawCorrect(x + 1, y + 0, 0x0C);
            drawCorrect(x + 1, y + 4, 0x03);
            drawCorrect(x + 2, y + 0, 0x0C);
            drawCorrect(x + 2, y + 4, 0x03);
            drawCorrect(x + 3, y + 0, 0x0C);
            drawCorrect(x + 3, y + 4, 0x03);
            drawCorrect(x + 4, y + 0, 0xF0);
            break;
        case 'Q':
            drawCorrect(x + 0, y + 0, 0xF0);
            drawCorrect(x + 0, y + 4, 0x3F);
            drawCorrect(x + 1, y + 0, 0x0C);
            drawCorrect(x + 1, y + 4, 0xC0);
            drawCorrect(x + 2, y + 0, 0x0C);
            drawCorrect(x + 2, y + 4, 0xCC);
            drawCorrect(x + 3, y + 0, 0x0C);
            drawCorrect(x + 3, y + 4, 0x30);
            drawCorrect(x + 4, y + 0, 0xF0);
            drawCorrect(x + 4, y + 4, 0xCF);
            break;
        case 'R':
            drawCorrect(x + 0, y + 0, 0xF0);
            drawCorrect(x + 0, y + 4, 0xFF);
            drawCorrect(x + 1, y + 0, 0x0C);
            drawCorrect(x + 1, y + 4, 0x03);
            drawCorrect(x + 2, y + 0, 0x0C);
            drawCorrect(x + 2, y + 4, 0x0F);
            drawCorrect(x + 3, y + 0, 0x0C);
            drawCorrect(x + 3, y + 4, 0x33);
            drawCorrect(x + 4, y + 0, 0xF0);
            drawCorrect(x + 4, y + 4, 0xC0);
            break;
        case 'S':
            drawCorrect(x + 0, y + 0, 0xF0);
            drawCorrect(x + 0, y + 4, 0xC0);
            drawCorrect(x + 1, y + 0, 0x0C);
            drawCorrect(x + 1, y + 4, 0xC3);
            drawCorrect(x + 2, y + 0, 0x0C);
            drawCorrect(x + 2, y + 4, 0xC3);
            drawCorrect(x + 3, y + 0, 0x0C);
            drawCorrect(x + 3, y + 4, 0xC3);
            drawCorrect(x + 4, y + 0, 0x0C);
            drawCorrect(x + 4, y + 4, 0x3C);
            break;
        case 'T':
            drawCorrect(x + 0, y + 0, 0x0C);
            drawCorrect(x + 1, y + 0, 0x0C);
            drawCorrect(x + 2, y + 0, 0xFC);
            drawCorrect(x + 2, y + 4, 0xFF);
            drawCorrect(x + 3, y + 0, 0x0C);
            drawCorrect(x + 4, y + 0, 0x0C);
            break;
        case 'U':
            drawCorrect(x + 0, y + 0, 0xFC);
            drawCorrect(x + 0, y + 4, 0x3F);
            drawCorrect(x + 1, y + 4, 0xC0);
            drawCorrect(x + 2, y + 4, 0xC0);
            drawCorrect(x + 3, y + 4, 0xC0);
            drawCorrect(x + 4, y + 0, 0xFC);
            drawCorrect(x + 4, y + 4, 0x3F);
            break;
        case 'V':
            drawCorrect(x + 0, y + 0, 0xFC);
            drawCorrect(x + 1, y + 4, 0x0F);
            drawCorrect(x + 2, y + 4, 0xF0);
            drawCorrect(x + 3, y + 4, 0x0F);
            drawCorrect(x + 4, y + 0, 0xFC);
            break;
        case 'W':
            drawCorrect(x + 0, y + 0, 0xFC);
            drawCorrect(x + 0, y + 4, 0xFF);
            drawCorrect(x + 1, y + 4, 0x30);
            drawCorrect(x + 2, y + 4, 0x0C);
            drawCorrect(x + 3, y + 4, 0x30);
            drawCorrect(x + 4, y + 0, 0xFC);
            drawCorrect(x + 4, y + 4, 0xFF);
            break;
        case 'X':
            drawCorrect(x + 0, y + 0, 0x3C);
            drawCorrect(x + 0, y + 4, 0xF0);
            drawCorrect(x + 1, y + 0, 0xC0);
            drawCorrect(x + 1, y + 4, 0x0C);
            drawCorrect(x + 2, y + 4, 0x03);
            drawCorrect(x + 3, y + 0, 0xC0);
            drawCorrect(x + 3, y + 4, 0x0C);
            drawCorrect(x + 4, y + 0, 0x3C);
            drawCorrect(x + 4, y + 4, 0xF0);
            break;
        case 'Y':
            drawCorrect(x + 0, y + 0, 0x3C);
            drawCorrect(x + 1, y + 0, 0xC0);
            drawCorrect(x + 2, y + 4, 0xFF);
            drawCorrect(x + 3, y + 0, 0xC0);
            drawCorrect(x + 4, y + 0, 0x3C);
            break;
        case 'Z':
            drawCorrect(x + 0, y + 0, 0x0C);
            drawCorrect(x + 0, y + 4, 0xF0);
            drawCorrect(x + 1, y + 0, 0x0C);
            drawCorrect(x + 1, y + 4, 0xCC);
            drawCorrect(x + 2, y + 0, 0x0C);
            drawCorrect(x + 2, y + 4, 0xC3);
            drawCorrect(x + 3, y + 0, 0xCC);
            drawCorrect(x + 3, y + 4, 0xC0);
            drawCorrect(x + 4, y + 0, 0x3C);
            drawCorrect(x + 4, y + 4, 0xC0);
            break;
        case ' ':
            break;
        case '-':
            drawCorrect(x + 0, y + 4, 0x03);
            drawCorrect(x + 1, y + 4, 0x03);
            drawCorrect(x + 2, y + 4, 0x03);
            break;
        default:
            break;
    }
}

void clearDragon(int8_t x, int8_t y) {
    for (uint8_t i = 0; i <= 60; i += 4) {
        for (uint8_t j = 0; j <= 159; j++) {
            drawCorrect(x + j, y + i, 0x00);
        }
    }
}

void printDragon(int8_t x, int8_t y) {

    for (uint8_t i = 22; i <= 26; ++i) {
        drawCorrect(x + i, y + 20, 0xFF);
    }/*
    for (uint8_t i = 40; i <= 45; ++i) {
        for (uint8_t j = 20; j <= 36; j += 4) {
            drawCorrect(x + i, y + j, 0xFF);
        }
    }
    for (uint8_t i = 28; i <= 39; ++i) {
        for (uint8_t j = 24; j <= 28; j += 4) {
            drawCorrect(x + i, y + j, 0xFF);
        }
    }
    for (uint8_t i = 14; i <= 28; ++i) {
        for (uint8_t j = 32; j <= 40; j += 4) {
            drawCorrect(x + i, y + j, 0xFF);
        }
    }
    for (uint8_t i = 10; i <= 23; ++i) {
        for (uint8_t j = 44; j <= 60; j += 4) {
            drawCorrect(x + i, y + j, 0xFF);
        }
    }
    for (uint8_t i = 46; i <= 52; ++i) {
        for (uint8_t j = 24; j <= 28; j += 4) {
            drawCorrect(x + i, y + j, 0xFF);
        }
    }
    for (uint8_t i = 29; i <= 32; ++i) {
        for (uint8_t j = 32; j <= 36; j += 4) {
            drawCorrect(x + i, y + j, 0xFF);
        }
    }
    for (uint8_t i = 32; i <= 35; ++i) {
        drawCorrect(x + i, y + 40, 0xFF);
    }
    for (uint8_t i = 37; i <= 44; ++i) {
        drawCorrect(x + i, y + 40, 0xFF);
    }
    for (uint8_t i = 20; i <= 27; ++i) {
        drawCorrect(x + i, y + 28, 0xFF);
    }
    for (uint8_t i = 60; i <= 64; ++i) {
        drawCorrect(x + i, y + 40, 0xFF);
    }
    for (uint8_t i = 50; i <= 57; ++i) {
        drawCorrect(x + i, y + 36, 0xFF);
    }
    for (uint8_t i = 57; i <= 59; ++i) {
        drawCorrect(x + i, y + 40, 0x3F);
    }
    for (uint8_t i = 46; i <= 49; ++i) {
        drawCorrect(x + i, y + 36, 0x3F);
    }
    for (uint8_t i = 24; i <= 29; ++i) {
        drawCorrect(x + i, y + 16, 0xFC);
    }
    for (uint8_t i = 47; i <= 52; ++i) {
        drawCorrect(x + i, y + 56, 0xFF);
    }
    for (int i = 46; i <= 49; ++i) {
        drawCorrect(x + i, y + 32, 0xFF);
    }
    drawCorrect(x + 1, y + 32, 0x0C);
    drawCorrect(x + 2, y + 32, 0x03);
    drawCorrect(x + 3, y + 32, 0x03);
    drawCorrect(x + 4, y + 32, 0x03);
    drawCorrect(x + 4, y + 40, 0x3C);
    drawCorrect(x + 5, y + 28, 0xC0);
    drawCorrect(x + 5, y + 32, 0x03);
    drawCorrect(x + 5, y + 36, 0xC0);
    drawCorrect(x + 5, y + 40, 0x0F);
    drawCorrect(x + 5, y + 48, 0x0F);
    drawCorrect(x + 5, y + 52, 0xFC);
    drawCorrect(x + 5, y + 56, 0xFF);
    drawCorrect(x + 6, y + 28, 0xC0);
    drawCorrect(x + 6, y + 36, 0xF0);
    drawCorrect(x + 6, y + 40, 0x03);
    drawCorrect(x + 6, y + 44, 0xFC);
    drawCorrect(x + 6, y + 48, 0xC0);
    drawCorrect(x + 6, y + 52, 0xFF);
    drawCorrect(x + 6, y + 56, 0xFF);
    drawCorrect(x + 6, y + 60, 0xFF);
    drawCorrect(x + 7, y + 28, 0xF0);
    drawCorrect(x + 7, y + 36, 0xFF);
    drawCorrect(x + 7, y + 40, 0xF0);
    drawCorrect(x + 7, y + 44, 0x0F);
    drawCorrect(x + 7, y + 48, 0xFC);
    drawCorrect(x + 7, y + 52, 0xFF);
    drawCorrect(x + 7, y + 56, 0xFF);
    drawCorrect(x + 7, y + 60, 0xFF);
    drawCorrect(x + 8, y + 28, 0xF0);
    drawCorrect(x + 8, y + 32, 0xC0);
    drawCorrect(x + 8, y + 36, 0x3F);
    drawCorrect(x + 8, y + 40, 0x3F);
    drawCorrect(x + 8, y + 44, 0xF0);
    drawCorrect(x + 8, y + 48, 0xFF);
    drawCorrect(x + 8, y + 52, 0xFF);
    drawCorrect(x + 8, y + 56, 0xFF);
    drawCorrect(x + 8, y + 60, 0xFF);
    drawCorrect(x + 9, y + 28, 0xF0);
    drawCorrect(x + 9, y + 32, 0xC0);
    drawCorrect(x + 9, y + 36, 0xFF);
    drawCorrect(x + 9, y + 40, 0x0F);
    drawCorrect(x + 9, y + 44, 0xFC);
    drawCorrect(x + 9, y + 48, 0xFF);
    drawCorrect(x + 9, y + 52, 0xFF);
    drawCorrect(x + 9, y + 56, 0xFF);
    drawCorrect(x + 9, y + 60, 0xFF);
    drawCorrect(x + 10, y + 28, 0xF0);
    drawCorrect(x + 10, y + 32, 0xF0);
    drawCorrect(x + 10, y + 36, 0xFF);
    drawCorrect(x + 10, y + 40, 0x30);
    drawCorrect(x + 11, y + 28, 0xF0);
    drawCorrect(x + 11, y + 32, 0xFC);
    drawCorrect(x + 11, y + 36, 0x3F);
    drawCorrect(x + 11, y + 40, 0xFC);
    drawCorrect(x + 12, y + 28, 0xFC);
    drawCorrect(x + 12, y + 32, 0xFC);
    drawCorrect(x + 12, y + 36, 0xCF);
    drawCorrect(x + 12, y + 40, 0xFF);
    drawCorrect(x + 13, y + 28, 0xFC);
    drawCorrect(x + 13, y + 32, 0xFF);
    drawCorrect(x + 13, y + 36, 0xF3);
    drawCorrect(x + 13, y + 40, 0xFF);
    drawCorrect(x + 14, y + 28, 0xFC);
    drawCorrect(x + 15, y + 20, 0x30);
    drawCorrect(x + 15, y + 28, 0xFF);
    drawCorrect(x + 16, y + 20, 0x30);
    drawCorrect(x + 16, y + 28, 0xFF);
    drawCorrect(x + 17, y + 20, 0x0C);
    drawCorrect(x + 17, y + 24, 0xC0);
    drawCorrect(x + 17, y + 28, 0xCF);
    drawCorrect(x + 18, y + 20, 0x0C);
    drawCorrect(x + 18, y + 24, 0xF0);
    drawCorrect(x + 18, y + 28, 0xF3);
    drawCorrect(x + 19, y + 20, 0x0F);
    drawCorrect(x + 19, y + 24, 0xF0);
    drawCorrect(x + 19, y + 28, 0xFC);
    drawCorrect(x + 20, y + 20, 0x0F);
    drawCorrect(x + 20, y + 24, 0x3C);
    drawCorrect(x + 21, y + 16, 0xC0);
    drawCorrect(x + 21, y + 20, 0x0F);
    drawCorrect(x + 21, y + 24, 0x3F);
    drawCorrect(x + 22, y + 16, 0xC0);
    drawCorrect(x + 22, y + 24, 0xCF);
    drawCorrect(x + 23, y + 16, 0xC0);
    drawCorrect(x + 23, y + 24, 0xCF);
    drawCorrect(x + 24, y + 24, 0xC3);
    drawCorrect(x + 24, y + 44, 0xFF);
    drawCorrect(x + 24, y + 48, 0x3F);
    drawCorrect(x + 24, y + 56, 0xFF);
    drawCorrect(x + 24, y + 60, 0xCF);
    drawCorrect(x + 25, y + 24, 0xF3);
    drawCorrect(x + 25, y + 44, 0xFF);
    drawCorrect(x + 25, y + 48, 0x0F);
    drawCorrect(x + 25, y + 56, 0xFC);
    drawCorrect(x + 25, y + 60, 0xCF);
    drawCorrect(x + 26, y + 24, 0xFC);
    drawCorrect(x + 26, y + 44, 0x03);
    drawCorrect(x + 26, y + 48, 0x3F);
    drawCorrect(x + 26, y + 56, 0xF0);
    drawCorrect(x + 26, y + 60, 0xCF);
    drawCorrect(x + 27, y + 20, 0xF3);
    drawCorrect(x + 27, y + 24, 0xFC);
    drawCorrect(x + 27, y + 48, 0xF0);
    drawCorrect(x + 27, y + 56, 0xC0);
    drawCorrect(x + 27, y + 60, 0xFF);
    drawCorrect(x + 28, y + 20, 0x33);
    drawCorrect(x + 28, y + 56, 0xC0);
    drawCorrect(x + 28, y + 60, 0x3F);
    drawCorrect(x + 29, y + 20, 0x33);
    drawCorrect(x + 29, y + 40, 0x3F);
    drawCorrect(x + 29, y + 60, 0x3F);
    drawCorrect(x + 30, y + 16, 0xF0);
    drawCorrect(x + 30, y + 20, 0x03);
    drawCorrect(x + 30, y + 40, 0x3F);
    drawCorrect(x + 30, y + 60, 0x3F);
    drawCorrect(x + 31, y + 16, 0xF0);
    drawCorrect(x + 31, y + 20, 0xC3);
    drawCorrect(x + 31, y + 60, 0x3F);
    drawCorrect(x + 32, y + 16, 0xCC);
    drawCorrect(x + 32, y + 20, 0xC3);
    drawCorrect(x + 32, y + 60, 0x3E);
    drawCorrect(x + 33, y + 16, 0xFC);
    drawCorrect(x + 33, y + 20, 0xC3);
    drawCorrect(x + 33, y + 32, 0xFF);
    drawCorrect(x + 33, y + 36, 0xCF);
    drawCorrect(x + 33, y + 60, 0xFC);
    drawCorrect(x + 34, y + 16, 0xF0);
    drawCorrect(x + 34, y + 20, 0xC0);
    drawCorrect(x + 34, y + 32, 0xFF);
    drawCorrect(x + 34, y + 36, 0xCF);
    drawCorrect(x + 34, y + 60, 0xFC);
    drawCorrect(x + 35, y + 16, 0xFF);
    drawCorrect(x + 35, y + 20, 0xCF);
    drawCorrect(x + 35, y + 32, 0xCF);
    drawCorrect(x + 35, y + 36, 0xF3);
    drawCorrect(x + 35, y + 40, 0xF3);
    drawCorrect(x + 35, y + 60, 0xFC);
    drawCorrect(x + 36, y + 16, 0xFC);
    drawCorrect(x + 36, y + 20, 0xC3);
    drawCorrect(x + 36, y + 32, 0xF3);
    drawCorrect(x + 36, y + 36, 0x30);
    drawCorrect(x + 36, y + 40, 0xFC);
    drawCorrect(x + 36, y + 60, 0xF0);
    drawCorrect(x + 37, y + 16, 0xF0);
    drawCorrect(x + 37, y + 20, 0xC3);
    drawCorrect(x + 37, y + 32, 0x33);
    drawCorrect(x + 37, y + 44, 0x03);
    drawCorrect(x + 37, y + 60, 0xF0);
    drawCorrect(x + 38, y + 12, 0x30);
    drawCorrect(x + 38, y + 16, 0xC0);
    drawCorrect(x + 38, y + 20, 0xCF);
    drawCorrect(x + 38, y + 32, 0xC0);
    drawCorrect(x + 38, y + 36, 0xF3);
    drawCorrect(x + 38, y + 44, 0x03);
    drawCorrect(x + 38, y + 60, 0xC0);
    drawCorrect(x + 39, y + 12, 0xC0);
    drawCorrect(x + 39, y + 16, 0xC0);
    drawCorrect(x + 39, y + 20, 0xCF);
    drawCorrect(x + 39, y + 32, 0xFF);
    drawCorrect(x + 39, y + 36, 0xFF);
    drawCorrect(x + 39, y + 44, 0x0F);
    drawCorrect(x + 39, y + 60, 0xC0);
    drawCorrect(x + 40, y + 12, 0xC0);
    drawCorrect(x + 40, y + 16, 0x03);
    drawCorrect(x + 40, y + 44, 0x3F);
    drawCorrect(x + 40, y + 60, 0x40);
    drawCorrect(x + 41, y + 16, 0xFF);
    drawCorrect(x + 41, y + 44, 0xFF);
    drawCorrect(x + 41, y + 48, 0x03);
    drawCorrect(x + 42, y + 4, 0x3F);
    drawCorrect(x + 42, y + 16, 0xFC);
    drawCorrect(x + 42, y + 44, 0xFF);
    drawCorrect(x + 42, y + 48, 0x0F);
    drawCorrect(x + 43, y + 4, 0xFF);
    drawCorrect(x + 43, y + 8, 0x03);
    drawCorrect(x + 43, y + 16, 0xF0);
    drawCorrect(x + 43, y + 44, 0xFF);
    drawCorrect(x + 43, y + 48, 0x3F);
    drawCorrect(x + 44, y + 4, 0xF0);
    drawCorrect(x + 44, y + 8, 0x3F);
    drawCorrect(x + 44, y + 44, 0xFF);
    drawCorrect(x + 44, y + 48, 0xFF);
    drawCorrect(x + 44, y + 56, 0x80);
    drawCorrect(x + 45, y + 8, 0xFF);
    drawCorrect(x + 45, y + 12, 0x03);
    drawCorrect(x + 45, y + 40, 0x80);
    drawCorrect(x + 45, y + 44, 0x0A);
    drawCorrect(x + 45, y + 48, 0xFF);
    drawCorrect(x + 45, y + 52, 0x03);
    drawCorrect(x + 45, y + 56, 0x80);
    drawCorrect(x + 46, y + 8, 0xF0);
    drawCorrect(x + 46, y + 12, 0x3F);
    drawCorrect(x + 46, y + 20, 0xFC);
    drawCorrect(x + 46, y + 36, 0x3F);
    drawCorrect(x + 46, y + 44, 0x2A);
    drawCorrect(x + 46, y + 48, 0xFC);
    drawCorrect(x + 46, y + 52, 0x3F);
    drawCorrect(x + 46, y + 56, 0xBC);
    drawCorrect(x + 46, y + 60, 0x08);
    drawCorrect(x + 47, y + 12, 0xFF);
    drawCorrect(x + 47, y + 16, 0xFF);
    drawCorrect(x + 47, y + 20, 0xFF);
    drawCorrect(x + 47, y + 36, 0x3F);
    drawCorrect(x + 47, y + 44, 0x28);
    drawCorrect(x + 47, y + 48, 0xF0);
    drawCorrect(x + 47, y + 52, 0xFF);
    drawCorrect(x + 47, y + 56, 0x3F);
    drawCorrect(x + 47, y + 60, 0x08);
    drawCorrect(x + 48, y + 12, 0xFC);
    drawCorrect(x + 48, y + 16, 0xFF);
    drawCorrect(x + 48, y + 20, 0xFF);
    drawCorrect(x + 48, y + 36, 0x3F);
    drawCorrect(x + 48, y + 44, 0x28);
    drawCorrect(x + 48, y + 48, 0xC0);
    drawCorrect(x + 48, y + 52, 0xFF);
    drawCorrect(x + 48, y + 60, 0x02);
    drawCorrect(x + 49, y + 16, 0xC0);
    drawCorrect(x + 49, y + 20, 0xFF);
    drawCorrect(x + 49, y + 36, 0x3F);
    drawCorrect(x + 49, y + 44, 0x20);
    drawCorrect(x + 49, y + 52, 0xFF);
    drawCorrect(x + 49, y + 60, 0x23);
    drawCorrect(x + 50, y + 32, 0xF0);
    drawCorrect(x + 50, y + 44, 0xA0);
    drawCorrect(x + 50, y + 52, 0xFC);
    drawCorrect(x + 50, y + 60, 0x28);
    drawCorrect(x + 51, y + 20, 0xFC);
    drawCorrect(x + 51, y + 32, 0xC0);
    drawCorrect(x + 51, y + 44, 0xA0);
    drawCorrect(x + 51, y + 48, 0x02);
    drawCorrect(x + 51, y + 52, 0xF0);
    drawCorrect(x + 51, y + 60, 0x02);
    drawCorrect(x + 52, y + 16, 0xF0);
    drawCorrect(x + 52, y + 20, 0xFF);
    drawCorrect(x + 52, y + 32, 0xC3);
    drawCorrect(x + 52, y + 44, 0x80);
    drawCorrect(x + 52, y + 48, 0x02);
    drawCorrect(x + 52, y + 52, 0xC0);
    drawCorrect(x + 52, y + 60, 0x20);
    drawCorrect(x + 53, y + 28, 0xC0);
    drawCorrect(x + 53, y + 32, 0x0F);
    drawCorrect(x + 53, y + 40, 0x03);
    drawCorrect(x + 53, y + 48, 0x02);
    drawCorrect(x + 53, y + 52, 0xF0);
    drawCorrect(x + 53, y + 60, 0x0A);
    drawCorrect(x + 54, y + 32, 0xFC);
    drawCorrect(x + 54, y + 40, 0x03);
    drawCorrect(x + 54, y + 48, 0x08);
    drawCorrect(x + 54, y + 52, 0xF0);
    drawCorrect(x + 54, y + 56, 0x3F);
    drawCorrect(x + 55, y + 32, 0xF0);
    drawCorrect(x + 55, y + 40, 0x0F);
    drawCorrect(x + 55, y + 48, 0x20);
    drawCorrect(x + 56, y + 32, 0xC0);
    drawCorrect(x + 56, y + 40, 0x0F);
    drawCorrect(x + 58, y + 36, 0xF0);
    drawCorrect(x + 59, y + 36, 0xF0);
    drawCorrect(x + 60, y + 36, 0xC0);
    drawCorrect(x + 61, y + 36, 0xC0);
    drawCorrect(x + 62, y + 44, 0x03);
    drawCorrect(x + 63, y + 44, 0x03);
    drawCorrect(x + 64, y + 44, 0xCF);
    drawCorrect(x + 64, y + 48, 0x03);
    drawCorrect(x + 65, y + 40, 0xFC);
    drawCorrect(x + 65, y + 44, 0xFF);
    drawCorrect(x + 66, y + 40, 0xFC);
    drawCorrect(x + 66, y + 44, 0xFF);
    drawCorrect(x + 67, y + 40, 0xFC);
    drawCorrect(x + 67, y + 44, 0x3F);
    drawCorrect(x + 68, y + 40, 0xFC);
    drawCorrect(x + 68, y + 44, 0x0F);
    drawCorrect(x + 69, y + 40, 0xF0);*/
}

void printTitel(uint8_t x, uint8_t y) {
    drawCorrect(x + 11, y + 0, 0x30);
    drawCorrect(x + 12, y + 0, 0x30);
    drawCorrect(x + 13, y + 0, 0xF0);
    for (uint8_t i = 4; i <= 12; i += 4) {
        drawCorrect(x + 13, y + i, 0xFF);
    }
    for (uint8_t i = 13; i <= 15; i += 4) {
        drawCorrect(x + i, y + 16, 0x0F);
    }
    drawCorrect(x + 14, y + 0, 0xF0);
    for (uint8_t i = 4; i <= 12; i += 4) {
        drawCorrect(x + 14, y + i, 0xFF);
    }
    drawCorrect(x + 15, y + 0, 0xF0);
    for (uint8_t i = 4; i <= 12; i += 4) {
        drawCorrect(x + 15, y + i, 0xFF);
    }
    for (uint8_t i = 16; i <= 19; i++) {
        drawCorrect(x + i, y + 0, 0x30);
    }
    for (uint8_t i = 16; i <= 19; i++) {
        drawCorrect(x + i, y + 16, 0x0C);
    }/*
    drawCorrect(x + 20, y + 0, 0x70);
    drawCorrect(x + 20, y + 16, 0x0D);
    drawCorrect(x + 21, y + 0, 0xE0);
    drawCorrect(x + 21, y + 16, 0x0B);
    drawCorrect(x + 22, y + 0, 0xD0);
    drawCorrect(x + 22, y + 4, 0x07);
    drawCorrect(x + 22, y + 12, 0xC0);
    drawCorrect(x + 22, y + 16, 0x03);
    drawCorrect(x + 23, y + 0, 0xC0);
    drawCorrect(x + 23, y + 4, 0xFF);
    drawCorrect(x + 23, y + 8, 0xAA);
    drawCorrect(x + 23, y + 12, 0xFF);
    drawCorrect(x + 23, y + 16, 0x02);
    for (uint8_t i = 4; i <= 12; i += 4) {
        drawCorrect(x + 24, y + i, 0xFF);
    }
    drawCorrect(x + 25, y + 4, 0xF4);
    drawCorrect(x + 25, y + 8, 0xFF);
    drawCorrect(x + 25, y + 12, 0x1F);
    drawCorrect(x + 26, y + 8, 0x55);
    drawCorrect(x + 27, y + 4, 0x40);
    drawCorrect(x + 27, y + 16, 0x04);
    drawCorrect(x + 28, y + 4, 0xC0);
    drawCorrect(x + 28, y + 8, 0x01);
    drawCorrect(x + 28, y + 16, 0x0C);
    drawCorrect(x + 29, y + 4, 0xC0);
    drawCorrect(x + 29, y + 8, 0xFF);
    drawCorrect(x + 29, y + 12, 0xFF);
    drawCorrect(x + 29, y + 16, 0x0F);
    drawCorrect(x + 30, y + 4, 0xC0);
    drawCorrect(x + 30, y + 8, 0xFF);
    drawCorrect(x + 30, y + 12, 0xFF);
    drawCorrect(x + 30, y + 16, 0x0F);
    drawCorrect(x + 31, y + 4, 0x40);
    drawCorrect(x + 31, y + 8, 0xFE);
    drawCorrect(x + 31, y + 12, 0xAB);
    drawCorrect(x + 31, y + 16, 0x0E);
    drawCorrect(x + 32, y + 8, 0x0B);
    drawCorrect(x + 32, y + 16, 0x0C);
    drawCorrect(x + 33, y + 4, 0x80);
    drawCorrect(x + 33, y + 8, 0x02);
    drawCorrect(x + 33, y + 16, 0x08);
    drawCorrect(x + 34, y + 4, 0xC0);
    drawCorrect(x + 34, y + 8, 0x0B);
    drawCorrect(x + 35, y + 4, 0xC0);
    drawCorrect(x + 35, y + 8, 0x0F);
    drawCorrect(x + 36, y + 4, 0x40);
    drawCorrect(x + 36, y + 8, 0x07);
    drawCorrect(x + 38, y + 8, 0x04);
    drawCorrect(x + 38, y + 12, 0xF0);
    drawCorrect(x + 38, y + 16, 0x0B);
    drawCorrect(x + 39, y + 8, 0x3F);
    drawCorrect(x + 39, y + 12, 0xFC);
    drawCorrect(x + 39, y + 16, 0x2F);
    drawCorrect(x + 40, y + 4, 0x80);
    drawCorrect(x + 40, y + 8, 0x3F);
    drawCorrect(x + 40, y + 12, 0x7E);
    drawCorrect(x + 40, y + 16, 0x3D);
    drawCorrect(x + 41, y + 4, 0xC0);
    drawCorrect(x + 41, y + 12, 0x1F);
    drawCorrect(x + 41, y + 16, 0x30);
    drawCorrect(x + 42, y + 4, 0xC0);
    drawCorrect(x + 42, y + 8, 0x40);
    drawCorrect(x + 42, y + 12, 0x0F);
    drawCorrect(x + 42, y + 16, 0x30);
    drawCorrect(x + 43, y + 4, 0xC0);
    drawCorrect(x + 43, y + 8, 0xC0);
    drawCorrect(x + 43, y + 12, 0x0B);
    drawCorrect(x + 43, y + 16, 0x04);
    drawCorrect(x + 44, y + 4, 0xC0);
    drawCorrect(x + 44, y + 8, 0xC2);
    drawCorrect(x + 44, y + 12, 0x07);
    drawCorrect(x + 44, y + 16, 0x01);
    drawCorrect(x + 45, y + 4, 0x80);
    drawCorrect(x + 45, y + 8, 0xFF);
    drawCorrect(x + 45, y + 12, 0xFF);
    drawCorrect(x + 45, y + 16, 0x07);
    drawCorrect(x + 46, y + 8, 0xFF);
    drawCorrect(x + 46, y + 12, 0xFF);
    drawCorrect(x + 46, y + 16, 0x0F);
    drawCorrect(x + 47, y + 16, 0x0D);
    drawCorrect(x + 48, y + 16, 0x0C);
    drawCorrect(x + 50, y + 16, 0x40);
    drawCorrect(x + 50, y + 20, 0x01);
    drawCorrect(x + 51, y + 8, 0xA4);
    drawCorrect(x + 51, y + 12, 0xC1);
    drawCorrect(x + 51, y + 16, 0xD7);
    drawCorrect(x + 51, y + 20, 0x0F);
    drawCorrect(x + 52, y + 8, 0xFF);
    drawCorrect(x + 52, y + 12, 0xEF);
    drawCorrect(x + 52, y + 16, 0xBF);
    drawCorrect(x + 52, y + 20, 0x2E);
    drawCorrect(x + 53, y + 4, 0x40);
    drawCorrect(x + 53, y + 8, 0x5B);
    drawCorrect(x + 53, y + 12, 0x3E);
    drawCorrect(x + 53, y + 16, 0x1C);
    drawCorrect(x + 53, y + 20, 0x34);
    drawCorrect(x + 54, y + 4, 0xC0);
    drawCorrect(x + 54, y + 8, 0x01);
    drawCorrect(x + 54, y + 12, 0x34);
    drawCorrect(x + 54, y + 16, 0x0C);
    drawCorrect(x + 54, y + 20, 0x30);
    drawCorrect(x + 55, y + 4, 0xC0);
    drawCorrect(x + 55, y + 12, 0x30);
    drawCorrect(x + 55, y + 16, 0x0C);
    drawCorrect(x + 55, y + 20, 0x30);
    drawCorrect(x + 56, y + 4, 0xC0);
    drawCorrect(x + 56, y + 12, 0x30);
    drawCorrect(x + 56, y + 16, 0x0C);
    drawCorrect(x + 56, y + 20, 0x30);
    drawCorrect(x + 57, y + 4, 0xC0);
    drawCorrect(x + 57, y + 8, 0x07);
    drawCorrect(x + 57, y + 12, 0x3D);
    drawCorrect(x + 57, y + 16, 0x0C);
    drawCorrect(x + 57, y + 20, 0x34);
    drawCorrect(x + 58, y + 4, 0x40);
    drawCorrect(x + 58, y + 8, 0xFF);
    drawCorrect(x + 58, y + 12, 0x0F);
    drawCorrect(x + 58, y + 16, 0x1C);
    drawCorrect(x + 58, y + 20, 0x2C);
    drawCorrect(x + 59, y + 4, 0xC0);
    drawCorrect(x + 59, y + 8, 0xFD);
    drawCorrect(x + 59, y + 12, 0x03);
    drawCorrect(x + 59, y + 16, 0xFC);
    drawCorrect(x + 59, y + 20, 0x0F);
    drawCorrect(x + 60, y + 4, 0xC0);
    drawCorrect(x + 60, y + 8, 0x02);
    drawCorrect(x + 60, y + 16, 0xF0);
    drawCorrect(x + 60, y + 20, 0x07);
    drawCorrect(x + 61, y + 4, 0xC0);
    drawCorrect(x + 61, y + 8, 0x03);
    drawCorrect(x + 63, y + 8, 0xF4);
    drawCorrect(x + 63, y + 12, 0x7F);
    drawCorrect(x + 64, y + 8, 0xFF);
    drawCorrect(x + 64, y + 12, 0xFF);
    drawCorrect(x + 64, y + 16, 0x03);
    drawCorrect(x + 65, y + 4, 0x40);
    drawCorrect(x + 65, y + 8, 0x1B);
    drawCorrect(x + 65, y + 12, 0x90);
    drawCorrect(x + 65, y + 16, 0x07);
    drawCorrect(x + 66, y + 4, 0xC0);
    drawCorrect(x + 66, y + 8, 0x01);
    drawCorrect(x + 66, y + 16, 0x0D);
    drawCorrect(x + 67, y + 4, 0xC0);
    drawCorrect(x + 67, y + 16, 0x0C);
    drawCorrect(x + 68, y + 4, 0xC0);
    drawCorrect(x + 68, y + 16, 0x0D);
    drawCorrect(x + 69, y + 4, 0x80);
    drawCorrect(x + 69, y + 8, 0x07);
    drawCorrect(x + 69, y + 12, 0x40);
    drawCorrect(x + 69, y + 16, 0x0B);
    drawCorrect(x + 70, y + 8, 0xFF);
    drawCorrect(x + 70, y + 12, 0xFF);
    drawCorrect(x + 70, y + 16, 0x03);
    drawCorrect(x + 71, y + 8, 0xFC);
    drawCorrect(x + 71, y + 12, 0xFF);
    drawCorrect(x + 72, y + 8, 0x40);
    drawCorrect(x + 72, y + 12, 0x05);
    drawCorrect(x + 73, y + 16, 0x04);
    drawCorrect(x + 74, y + 4, 0x80);
    drawCorrect(x + 74, y + 8, 0x02);
    drawCorrect(x + 74, y + 16, 0x0C);
    drawCorrect(x + 75, y + 4, 0x80);
    drawCorrect(x + 75, y + 8, 0xAB);
    drawCorrect(x + 75, y + 12, 0xAA);
    drawCorrect(x + 75, y + 16, 0x0F);
    drawCorrect(x + 76, y + 4, 0x80);
    drawCorrect(x + 76, y + 8, 0xFF);
    drawCorrect(x + 76, y + 12, 0xFF);
    drawCorrect(x + 76, y + 16, 0x0F);
    drawCorrect(x + 77, y + 4, 0x40);
    drawCorrect(x + 77, y + 8, 0xBE);
    drawCorrect(x + 77, y + 12, 0xAA);
    drawCorrect(x + 77, y + 16, 0x0E);
    drawCorrect(x + 78, y + 8, 0x0F);
    drawCorrect(x + 78, y + 16, 0x0C);
    drawCorrect(x + 79, y + 4, 0xC0);
    drawCorrect(x + 79, y + 8, 0x03);
    drawCorrect(x + 79, y + 16, 0x04);
    drawCorrect(x + 80, y + 4, 0xC0);
    drawCorrect(x + 80, y + 8, 0x03);
    drawCorrect(x + 80, y + 16, 0x04);
    drawCorrect(x + 81, y + 4, 0xC0);
    drawCorrect(x + 81, y + 8, 0x07);
    drawCorrect(x + 81, y + 16, 0x0C);
    drawCorrect(x + 82, y + 4, 0xC0);
    drawCorrect(x + 82, y + 8, 0xBF);
    drawCorrect(x + 82, y + 12, 0xAA);
    drawCorrect(x + 82, y + 16, 0x0F);
    drawCorrect(x + 83, y + 8, 0xFF);
    drawCorrect(x + 83, y + 12, 0xFF);
    drawCorrect(x + 83, y + 16, 0x0F);
    drawCorrect(x + 84, y + 8, 0xA4);
    drawCorrect(x + 84, y + 12, 0xAA);
    drawCorrect(x + 84, y + 16, 0x0F);
    drawCorrect(x + 85, y + 16, 0x0C);
    drawCorrect(x + 86, y + 16, 0x04);
    drawCorrect(x + 88, y + 4, 0xD0);
    drawCorrect(x + 88, y + 8, 0xFF);
    drawCorrect(x + 88, y + 12, 0x02);
    drawCorrect(x + 89, y + 4, 0xFE);
    drawCorrect(x + 89, y + 8, 0xFF);
    drawCorrect(x + 89, y + 12, 0x2F);
    drawCorrect(x + 90, y + 0, 0xC0);
    for (uint8_t i = 4; i <= 12; i += 4) {
        drawCorrect(x + 90, y + i, 0xFF);
    }
    drawCorrect(x + 91, y + 0, 0xE0);
    drawCorrect(x + 91, y + 4, 0x1B);
    drawCorrect(x + 91, y + 12, 0xF4);
    drawCorrect(x + 91, y + 16, 0x02);
    drawCorrect(x + 92, y + 0, 0xB4);
    drawCorrect(x + 92, y + 12, 0xE4);
    drawCorrect(x + 92, y + 16, 0x03);
    drawCorrect(x + 93, y + 0, 0x28);
    drawCorrect(x + 93, y + 12, 0x5D);
    drawCorrect(x + 93, y + 16, 0x0B);
    drawCorrect(x + 94, y + 0, 0x0C);
    drawCorrect(x + 94, y + 12, 0x07);
    drawCorrect(x + 94, y + 16, 0x0C);
    drawCorrect(x + 95, y + 0, 0x0C);
    drawCorrect(x + 95, y + 12, 0x03);
    drawCorrect(x + 95, y + 16, 0x0C);
    drawCorrect(x + 96, y + 0, 0x0C);
    drawCorrect(x + 96, y + 12, 0x07);
    drawCorrect(x + 96, y + 16, 0x0C);
    drawCorrect(x + 97, y + 0, 0x1C);
    drawCorrect(x + 97, y + 12, 0x6D);
    drawCorrect(x + 97, y + 16, 0x0E);
    drawCorrect(x + 98, y + 0, 0x34);
    drawCorrect(x + 98, y + 12, 0xF8);
    drawCorrect(x + 98, y + 16, 0xFF);
    drawCorrect(x + 98, y + 20, 0x01);
    drawCorrect(x + 99, y + 0, 0xF0);
    drawCorrect(x + 99, y + 4, 0x01);
    drawCorrect(x + 99, y + 12, 0xD0);
    drawCorrect(x + 99, y + 16, 0xFF);
    drawCorrect(x + 99, y + 20, 0x0B);
    drawCorrect(x + 100, y + 0, 0xD0);
    drawCorrect(x + 100, y + 4, 0xBF);
    drawCorrect(x + 100, y + 8, 0xA6);
    drawCorrect(x + 100, y + 12, 0xFE);
    drawCorrect(x + 100, y + 16, 0xE4);
    drawCorrect(x + 100, y + 20, 0x0F);
    drawCorrect(x + 101, y + 0, 0x40);
    drawCorrect(x + 101, y + 4, 0xFF);
    drawCorrect(x + 101, y + 8, 0xFF);
    drawCorrect(x + 101, y + 12, 0x3F);
    drawCorrect(x + 101, y + 16, 0x40);
    drawCorrect(x + 101, y + 20, 0x0F);
    drawCorrect(x + 102, y + 4, 0xF8);
    drawCorrect(x + 102, y + 8, 0xFF);
    drawCorrect(x + 102, y + 12, 0x0B);
    drawCorrect(x + 102, y + 16, 0x90);
    drawCorrect(x + 102, y + 20, 0x0B);
    drawCorrect(x + 103, y + 4, 0x40);
    drawCorrect(x + 103, y + 8, 0x19);
    drawCorrect(x + 103, y + 16, 0xB0);
    drawCorrect(x + 103, y + 20, 0x01);
    drawCorrect(x + 104, y + 8, 0x01);
    drawCorrect(x + 105, y + 8, 0x07);
    drawCorrect(x + 106, y + 8, 0xFF);
    drawCorrect(x + 106, y + 12, 0xFF);
    drawCorrect(x + 106, y + 16, 0x06);
    drawCorrect(x + 107, y + 8, 0xFF);
    drawCorrect(x + 107, y + 12, 0xFF);
    drawCorrect(x + 107, y + 16, 0x1F);
    drawCorrect(x + 108, y + 8, 0x55);
    drawCorrect(x + 108, y + 12, 0x55);
    drawCorrect(x + 108, y + 16, 0x3F);
    drawCorrect(x + 109, y + 16, 0x3C);
    drawCorrect(x + 110, y + 16, 0x3C);
    drawCorrect(x + 111, y + 8, 0x03);
    drawCorrect(x + 111, y + 16, 0x1D);
    drawCorrect(x + 112, y + 8, 0x03);
    drawCorrect(x + 112, y + 12, 0x40);
    drawCorrect(x + 112, y + 16, 0x07);
    drawCorrect(x + 113, y + 8, 0xFF);
    drawCorrect(x + 113, y + 12, 0xFF);
    drawCorrect(x + 113, y + 16, 0x1F);
    drawCorrect(x + 114, y + 8, 0xFF);
    drawCorrect(x + 114, y + 12, 0xFF);
    drawCorrect(x + 114, y + 16, 0x1F);
    drawCorrect(x + 115, y + 8, 0x55);
    drawCorrect(x + 115, y + 12, 0x55);
    drawCorrect(x + 115, y + 16, 0x0E);
    drawCorrect(x + 116, y + 16, 0x0C);
    drawCorrect(x + 117, y + 16, 0x04);
    drawCorrect(x + 119, y + 8, 0xF4);
    drawCorrect(x + 119, y + 12, 0xBF);
    drawCorrect(x + 120, y + 8, 0xFE);
    drawCorrect(x + 120, y + 12, 0xFF);
    drawCorrect(x + 120, y + 16, 0x03);
    drawCorrect(x + 121, y + 4, 0x40);
    drawCorrect(x + 121, y + 8, 0x1F);
    drawCorrect(x + 121, y + 12, 0xD3);
    drawCorrect(x + 121, y + 16, 0x0B);
    drawCorrect(x + 122, y + 4, 0xC0);
    drawCorrect(x + 122, y + 8, 0x02);
    drawCorrect(x + 122, y + 12, 0x03);
    drawCorrect(x + 122, y + 16, 0x0E);
    drawCorrect(x + 123, y + 4, 0xC0);
    drawCorrect(x + 123, y + 12, 0x03);
    drawCorrect(x + 123, y + 16, 0x0C);
    drawCorrect(x + 124, y + 4, 0xC0);
    drawCorrect(x + 124, y + 12, 0x03);
    drawCorrect(x + 124, y + 16, 0x0C);
    drawCorrect(x + 125, y + 4, 0x80);
    drawCorrect(x + 125, y + 8, 0x07);
    drawCorrect(x + 125, y + 12, 0x03);
    drawCorrect(x + 125, y + 16, 0x0D);
    drawCorrect(x + 126, y + 8, 0xFF);
    drawCorrect(x + 126, y + 12, 0x03);
    drawCorrect(x + 126, y + 16, 0x07);
    drawCorrect(x + 127, y + 8, 0xFC);
    drawCorrect(x + 127, y + 12, 0xC3);
    drawCorrect(x + 127, y + 16, 0x01);
    drawCorrect(x + 128, y + 8, 0x40);
    drawCorrect(x + 128, y + 12, 0x01);
    drawCorrect(x + 130, y + 8, 0x68);
    drawCorrect(x + 130, y + 12, 0xF4);
    drawCorrect(x + 130, y + 16, 0x0F);
    drawCorrect(x + 131, y + 4, 0x40);
    drawCorrect(x + 131, y + 8, 0xFF);
    drawCorrect(x + 131, y + 12, 0xD2);
    drawCorrect(x + 131, y + 16, 0x07);
    drawCorrect(x + 132, y + 4, 0xC0);
    drawCorrect(x + 132, y + 8, 0xD1);
    drawCorrect(x + 132, y + 12, 0x03);
    drawCorrect(x + 132, y + 16, 0x0B);
    drawCorrect(x + 133, y + 4, 0xC0);
    drawCorrect(x + 133, y + 8, 0xC0);
    drawCorrect(x + 133, y + 12, 0x07);
    drawCorrect(x + 133, y + 16, 0x0D);
    drawCorrect(x + 134, y + 4, 0xC0);
    drawCorrect(x + 134, y + 8, 0xC0);
    drawCorrect(x + 134, y + 12, 0x0B);
    drawCorrect(x + 134, y + 16, 0x0C);
    drawCorrect(x + 135, y + 4, 0xC0);
    drawCorrect(x + 135, y + 8, 0x82);
    drawCorrect(x + 135, y + 12, 0x0F);
    drawCorrect(x + 135, y + 16, 0x0C);
    drawCorrect(x + 136, y + 4, 0x80);
    drawCorrect(x + 136, y + 8, 0x0F);
    drawCorrect(x + 136, y + 12, 0x1F);
    drawCorrect(x + 136, y + 16, 0x0A);
    drawCorrect(x + 137, y + 4, 0xC0);
    drawCorrect(x + 137, y + 8, 0x3F);
    drawCorrect(x + 137, y + 12, 0xFE);
    drawCorrect(x + 137, y + 16, 0x03);
    drawCorrect(x + 138, y + 12, 0x50);
    drawCorrect(x + 139, y + 8, 0x02);
    drawCorrect(x + 140, y + 4, 0x40);
    drawCorrect(x + 140, y + 8, 0x03);
    drawCorrect(x + 141, y + 4, 0xD0);
    drawCorrect(x + 141, y + 8, 0xFF);
    drawCorrect(x + 141, y + 12, 0xFF);
    drawCorrect(x + 141, y + 16, 0x0B);
    drawCorrect(x + 142, y + 0, 0x80);
    drawCorrect(x + 142, y + 4, 0xFF);
    drawCorrect(x + 142, y + 8, 0xFF);
    drawCorrect(x + 142, y + 12, 0xFF);
    drawCorrect(x + 142, y + 16, 0x2F);
    drawCorrect(x + 143, y + 0, 0x40);
    drawCorrect(x + 143, y + 4, 0x55);
    drawCorrect(x + 143, y + 8, 0x57);
    drawCorrect(x + 143, y + 12, 0x55);
    drawCorrect(x + 143, y + 16, 0x3F);
    drawCorrect(x + 144, y + 8, 0x03);
    drawCorrect(x + 144, y + 16, 0x3C);
    drawCorrect(x + 145, y + 8, 0x03);
    drawCorrect(x + 145, y + 16, 0x2D);
    drawCorrect(x + 146, y + 8, 0x03);
    drawCorrect(x + 146, y + 12, 0xE0);
    drawCorrect(x + 146, y + 16, 0x0B);
    drawCorrect(x + 147, y + 12, 0x50);
    */
}
