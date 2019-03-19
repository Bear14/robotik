//
// Created by torben on 15/03/19.
//

#include "platform.h"
#include "inttypes.h"
#include <stdlib.h>


void initPowerUps() {
    for (int i = 0; i < POWER_UP_COUNT; i++) {

        powerUps[i] = (struct PowerUp) {-10 + i, -10 + i, none};

    }
}

int8_t getMinXPowerUp() {

    int16_t min = 32767;
    uint8_t ind = 0;

    for(int i = 0; i < POWER_UP_COUNT; i++){
        if(powerUps[i].x < min){
            min = powerUps[i].x;
            ind = i;
        }

    }
    return ind;
}

void createPowerUp(struct platform base, int16_t random) {

    powerUps[getMinXPowerUp()] = (struct PowerUp) {base.x +random % base.length, base.y - 8, random%10};

}

uint8_t getIndexMaxX() {

    uint8_t ind = 0;
    int16_t max = -32767;

    for (int i = 0; i < PLATFORM_COUNT; i++) {
        if (platforms[i].x + platforms[i].length > max) {
            max = platforms[i].x + platforms[i].length;
            ind = i;
        }

    }
    return ind;
}

uint8_t getIndexMinX() {

    uint8_t ind = 0;
    int16_t min = 32767;

    for (int i = 0; i < PLATFORM_COUNT; i++) {
        if (platforms[i].x + platforms[i].length < min) {
            min = platforms[i].x + platforms[i].length;
            ind = i;
        }
    }
    return ind;
}

void platformInit() {
    platforms[0] = (struct platform) {0, 52, 90};
    platforms[1] = (struct platform) {100, 20, 60};
    platforms[2] = (struct platform) {200, 80, 90};
};

struct platform createNewPlatform(struct platform last, uint8_t platWidth, int16_t speed) {
    int random = rand() % 1024;


    int16_t minJump = 8 * 2 * speed;       // make dependant

    int16_t maxJump = 8 * 2 * speed * 2;

    uint8_t len = 15 * (random % (1 + platWidth) + 2);

    int16_t newX = (last.x + last.length) + (int16_t)(random % (maxJump + 1 - minJump) + minJump);

    int16_t newY = (int16_t)(random % 19 + 4);
    newY *= 4;

    //int16_t newY = (int16_t)(random % 82 + 18);
    struct platform newPlat = (struct platform) {(int16_t) newX, (int16_t) newY, (uint8_t) len};

    int8_t power = random % 20;
    //if (power == 0) {
        createPowerUp(newPlat, random);
   // }


    return newPlat;
}

void checkIfPlatformOutOfFrame(int16_t playerPosX, uint8_t platWidth, int16_t speed) {

    uint8_t ind = getIndexMinX();

    struct platform farthestLeft = platforms[ind];

    if (farthestLeft.x + farthestLeft.length < playerPosX - 5) {

        platforms[ind] = createNewPlatform(platforms[getIndexMaxX()], platWidth, speed);

    }
}
