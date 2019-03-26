//
// Created by torben on 11/03/19.
//

#ifndef ROBOTIK_SPRITES_H
#define ROBOTIK_SPRITES_H

#include <inttypes.h>
#include "platform.h"
void printNormal(uint8_t x, uint8_t y);
void printSorcerer(uint8_t x, uint8_t y);
void printRanger(uint8_t x, uint8_t y);
void printKnight(uint8_t x, uint8_t y);

void printPlayer(int16_t x, int16_t y, int16_t lastY, char forceRedraw, enum Form form);

void printHeart(int16_t x, int16_t y);

void rePrintPlatform(struct platform toDraw, int16_t offsetX, int16_t speed);

void printPlatform(struct platform toDraw);

void printPUlive(int16_t x, int16_t y);
void printPUdeath(int16_t x, int16_t y);
void printPUknight(int16_t x, int16_t y);
void printPUsorcerer(int16_t x, int16_t y);
void printPUranger(int16_t x, int16_t y);
void printPUslow(int16_t x, int16_t y);
void printPUspeedUp(int16_t x, int16_t y);
void printPUpointsUp(int16_t x, int16_t y);
void printPUpointsDown(int16_t x, int16_t y);

void printPowerUp(int16_t x, int16_t y, enum PowerUpType type, int16_t speed);

void clearPowerUp(int16_t x, int16_t y);

void clearDragon(int8_t x, int8_t y);

void printDragon(int8_t x, int8_t y);

void printTitel(uint8_t x, uint8_t y);

void printScreen();

#endif //ROBOTIK_SPRITES_H
