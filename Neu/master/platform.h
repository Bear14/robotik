//
// Created by torben on 15/03/19.
//

#ifndef ROBOTIK_PLATFORM_H
#define ROBOTIK_PLATFORM_H

#include "inttypes.h"

#define PLATFORM_COUNT 3

#define PLATFORM_HEIGHT 8


struct platform {
    int16_t x;
    int16_t y;
    uint8_t length;
};

struct platform platforms[PLATFORM_COUNT];
struct platform getPlatformFromIndex(uint8_t ind);
uint8_t getIndexMaxX();
uint8_t getIndexMinX();
void platformInit();
struct platform createNewPlatform(struct platform last,uint8_t platWidth);
void addPlatformAtIndex(uint8_t ind, struct platform newPlatform);
void checkIfPlatformOutOfFrame(int16_t playerPosX,uint8_t platWidth);

#endif //ROBOTIK_PLATFORM_H
