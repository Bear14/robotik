//
// Created by torben on 15/03/19.
//

#include "platform.h"
#include "inttypes.h"
#include <stdlib.h>


void initPowerUps(){
    for(int i = 0; i < POWER_UP_COUNT; i++){

        powerUps[i] = (struct PowerUp){-10+i,-10+i,none};

    }
}

int8_t getMinXPowerUp(){

    struct PowerUp *pointer = powerUps;

    int16_t min = 9000;
    uint8_t ind = 0;

    for(int i = 0; i < POWER_UP_COUNT; i++){

        if(pointer->x < min){
            min = pointer->x;
            ind = i;
        }
        pointer++;
    }
    return ind;

}

void createPowerUp(struct platform base){

    int random = rand() % 10;


    powerUps[getMinXPowerUp()] = (struct PowerUp){base.x+base.length/2,base.y - 12,random};

}

struct platform getPlatformFromIndex(uint8_t ind) {
    struct platform *pointer = platforms;
    pointer += ind;
    return *pointer;
}
uint8_t getIndexMaxX() {
    struct platform *pointer = platforms;

    struct platform max = (struct platform) {
            -32767, 0, 0
    };

    uint8_t ind = 5;
    for (int i = 0; i < PLATFORM_COUNT; i++) {
        struct platform compare = *pointer;


        //
        if ((compare.x + compare.length) > (max.x + max.length)) {
            max = compare;
            ind = i;
        }

        pointer++;

    }
    return ind;

}
uint8_t getIndexMinX() {
    struct platform *pointer = platforms;

    struct platform min = (struct platform) {
            32767, 0, 0
    };

    uint8_t ind = 5;
    for (int i = 0; i < PLATFORM_COUNT; i++) {
        struct platform compare = *pointer;


        if (compare.x + compare.length < min.x + min.length) {
            min = compare;
            ind = i;

        }

        pointer++;

    }
    return ind;


}
void platformInit() {
    struct platform *pointer = platforms;
    *pointer = (struct platform) {0, 52, 90};
    pointer++;
    *pointer = (struct platform) {40, 20, 60};
    pointer++;
    *pointer = (struct platform) {200, 80, 90};
    pointer++;
};
struct platform createNewPlatform(struct platform last,uint8_t platWidth) {
    int random = rand() % 1024;






    int16_t maxJump = 8 * 2 * 2 + 12;       // make dependant


    uint8_t len = 15 * (random % (platWidth-4) + 5);

    int16_t newX = (last.x + last.length) + (int16_t)(random % (maxJump+1 - 30) + 30);

    int16_t newY = (int16_t)(random % 21 + 4);
    newY *= 4;

    //int16_t newY = (int16_t)(random % 82 + 18);
    struct platform newPlat = (struct platform){(int16_t) newX, (int16_t) newY, (uint8_t) len};

    int8_t power = random % 10;
    if(power == 0){
        createPowerUp(newPlat);
    }


    return newPlat;
}
void addPlatformAtIndex(uint8_t ind, struct platform newPlatform) {

    if (ind >= 0 && ind < PLATFORM_COUNT) {
        struct platform *pointer = platforms;
        pointer += ind;
        *pointer = newPlatform;
    }
}

void checkIfPlatformOutOfFrame(int16_t playerPosX,uint8_t platWidth) {

    uint8_t ind = getIndexMinX();

    struct platform farthestLeft = getPlatformFromIndex(ind);

    if (farthestLeft.x + farthestLeft.length < playerPosX - 5) {

        struct platform toAdd = createNewPlatform(getPlatformFromIndex(getIndexMaxX()),platWidth);

        addPlatformAtIndex(ind, toAdd); // make platform

    }


}
