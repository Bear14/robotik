//
// Created by torben on 15/03/19.
//

#include "platform.h"
#include "inttypes.h"
#include <stdlib.h>


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

    uint8_t len = 15 * (random % platWidth + 1);

    int16_t newX = (last.x + last.length) + (int16_t)(random % 45 + 30);

    int16_t newY = (int16_t)(random % 21 + 4);
    newY *= 4;

    //int16_t newY = (int16_t)(random % 82 + 18);

    return (struct platform) {(int16_t) newX, (int16_t) newY, (uint8_t) len};
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
