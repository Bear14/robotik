//
// Created by torben on 15/03/19.
//

#ifndef ROBOTIK_PLATFORM_H
#define ROBOTIK_PLATFORM_H

#include "inttypes.h"

#define PLATFORM_COUNT 3

#define PLATFORM_HEIGHT 8

#define POWER_UP_COUNT 3

#define POWER_UP_SIZE 8

#define POWER_UP_DROP_RATE 15

enum PowerUpType {
    none, live, death, knight, sorcerer,ranger,slow,speedUp,pointsUp,pointsDown
};

enum Form {
    _normal, _knight, _sorcerer, _ranger

};

struct PowerUp {
    int16_t x;
    int16_t y;
    enum PowerUpType type;

};

struct PowerUp powerUps[POWER_UP_COUNT];

struct platform {
    int16_t x;
    int16_t y;
    uint8_t length;
};

void initPowerUps();

struct platform platforms[PLATFORM_COUNT];

struct platform getPlatformFromIndex(uint8_t ind);

uint8_t getIndexMaxX();

uint8_t getIndexMinX();

void platformInit();

struct platform createNewPlatform(struct platform last, uint8_t platWidth,int16_t speed);

void checkIfPlatformOutOfFrame(int16_t playerPosX, uint8_t platWidth,int16_t speed);

#endif //ROBOTIK_PLATFORM_H
