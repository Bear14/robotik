//
// Created by torben on 11/03/19.
//

#ifndef ROBOTIK_SPRITES_H
#define ROBOTIK_SPRITES_H

#include <inttypes.h>
#include "platform.h"

/*
 * Figuren
 */
void clearPlayer(int16_t x, int16_t y);

void printNormal(uint8_t x, uint8_t y,uint8_t frameCounter);

void printSorcerer(uint8_t x, uint8_t y,uint8_t frameCounter);

void printRanger(uint8_t x, uint8_t y,uint8_t frameCounter);

void printKnight(uint8_t x, uint8_t y,uint8_t frameCounter);

void printDash(uint8_t x, uint8_t y);

void printHeart(int16_t x, int16_t y);


void rePrintPlatform(struct platform toDraw, int16_t offsetX, int16_t speed);

void printPlatform(struct platform toDraw);

/*
 * Power Ups
 */
void printPUlive(int16_t x, int16_t y);

void printPUdeath(int16_t x, int16_t y);

void printPUknight(int16_t x, int16_t y);

void printPUsorcerer(int16_t x, int16_t y);

void printPUranger(int16_t x, int16_t y);

void printPUslow(int16_t x, int16_t y);

void printPUspeedUp(int16_t x, int16_t y);

void printPUpointsUp(int16_t x, int16_t y);

void printPUpointsDown(int16_t x, int16_t y);

void clearPowerUp(int16_t x, int16_t y);

void printPause(uint8_t hex);

void printArrow(uint8_t x, uint8_t y);

void clearArrow(uint8_t x, uint8_t y);

void printGlyph(char glyph, uint8_t x, uint8_t y);

void clearDragon(int8_t x, int8_t y);

void printDragon(int8_t x, int8_t y);

void printTitel(uint8_t x, uint8_t y);

#endif //ROBOTIK_SPRITES_H
