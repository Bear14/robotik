//
// Created by torben on 11/03/19.
//

#ifndef ROBOTIK_SPRITES_H
#define ROBOTIK_SPRITES_H

#include <inttypes.h>
#include "platform.h"

void printPlayer(int16_t x, int16_t y, int16_t lastY, char forceRedraw, enum Form form);

void printHeart(int16_t x, int16_t y);

void rePrintPlatform(struct platform toDraw, int16_t offsetX, int16_t speed);

void printPlatform(struct platform toDraw);

void printPowerUp(int16_t x, int16_t y, enum PowerUpType type, int16_t speed);

void clearPowerUp(int16_t x, int16_t y);

void printDragon();

#endif //ROBOTIK_SPRITES_H
