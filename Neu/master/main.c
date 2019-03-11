/* 
 *	Basis
 *	2009 Benjamin Reh und Joachim Schleicher
 */
typedef int bool;
#define true 1
#define false 0

#include <stdlib.h>
#include <avr/io.h>
#include <inttypes.h>
#include <util/delay.h>
#include "uart.h"
#include "adc.h"
#include "timer.h"
#include "buttons.h"
#include "display.h"
#include <avr/interrupt.h>
#include "draw.h"


#define GRAVITY 1
#define JUMP_HEIGHT -8
#define SPEED 2
#define DASH_LENGTH 6
#define PLATFORM_COUNT 5

#define PLATFORM_HEIGHT 4

#define PANEL_SIZE 16

void init();

volatile int16_t posY = 0;
volatile int16_t posX = 0;
volatile int16_t offsetY = 52;
volatile int16_t offsetX = 5;
volatile char buttonPressed = '0';
volatile uint32_t timePressed = 0;


volatile int8_t dashLen;
volatile int8_t dashCounter = 2;
volatile int8_t jumpCounter = 2;


volatile int16_t playerPosY = 0;
volatile int16_t playerPosX = 0;
volatile int8_t playerMovY = 0;
volatile int8_t playerMovX = 0;
// Player height is 8!

#define PLAYER_HEIGHT 8


struct platform {
    int16_t x;
    int16_t y;
    uint8_t length;
};


struct platform platforms[PLATFORM_COUNT];
struct platform *platPtr;
uint8_t platformIndex = 0;

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
    *pointer = (struct platform) {0, 12, 80};
    pointer++;
    *pointer = (struct platform) {90, 30, 40};
    pointer++;
    *pointer = (struct platform) {200, 20, 50};
    pointer++;
    *pointer = (struct platform) {300, 30, 50};
    pointer++;
    *pointer = (struct platform) {400, 40, 50};

};

void drawPlatform(int16_t x, int16_t y, uint8_t length) {

    for (int16_t i = x; i < x + length; i++) {


        drawCorrect(i, y, 0xFF);


    }

}

void drawPlatforms() {

    struct platform *pointer = platforms;

    for (uint8_t i = 0; i < PLATFORM_COUNT; i++) {
        struct platform toDraw = *pointer;
        drawPlatform(toDraw.x + offsetX, toDraw.y + offsetY, toDraw.length);

        pointer++;

    }

}

struct platform createNewPlatform(struct platform last) {
    int random = rand() % 1024;

    uint8_t len = random % 70 + 30;

    int16_t newX = (last.x + last.length) + (int16_t)(random % 25 + 1);
    int16_t newY = last.y + (int16_t)(random % 100 - 50);

    return (struct platform) {(int16_t) newX, (int16_t) newY, (uint8_t) len};
}

void addPlatformAtIndex(uint8_t ind, struct platform newPlatform) {

    if (ind >= 0 && ind < PLATFORM_COUNT) {
        struct platform *pointer = platforms;
        pointer += ind;
        *pointer = newPlatform;
    }
}

void checkIfPlatformOutOfFrame() {

    uint8_t ind = getIndexMinX();

    struct platform farthestLeft = getPlatformFromIndex(ind);

    if (farthestLeft.x + farthestLeft.length < playerPosX) {

        struct platform toAdd = createNewPlatform(getPlatformFromIndex(getIndexMaxX()));

        addPlatformAtIndex(ind, toAdd); // make platform

    }


}

void reset() {

    // TODO: Fix reset and speed up

    if (playerPosX >= 15000) {
        struct platform *pointer = platforms;


        for (int i = 0; i < PLATFORM_COUNT; i++) {
            pointer->x -= playerPosX;

            pointer++;
        }

        playerPosX -= playerPosX;
        offsetX += playerPosX;
        page(0, 0, 255);
    }

}

//volatile struct platform platform_1 = (struct platform) {0, 12, 80};




void drawPlayer() {

    for (int i = 5; i < 5 + PLAYER_HEIGHT; i++) {
        drawCorrect(i, 52, 0xFF);
        drawCorrect(i, 56, 0xFF);
    }

};

void drawPlayerZero() {
    for (int i = playerPosX; i < playerPosX + PLAYER_HEIGHT; i++) {
        drawCorrect(i, playerPosY, 0xFF);
        drawCorrect(i, playerPosY + 4, 0xFF);
    }

};




enum state {
    standing, dashing, jumping, falling
};
enum state playerState = falling;

enum gState {run,stop,reset};


void dash() {


    page(159, 25, 0xFF);
    if (dashCounter > 0) {
        playerState = dashing;
        playerMovY = 0;
        dashLen = DASH_LENGTH;
        dashCounter--;
    }


}

void jump() {
    //page(159, 25, 0xFF);
    if (jumpCounter > 0) {
        playerState = jumping;
        playerMovY = JUMP_HEIGHT;
        dashLen = 0;
        jumpCounter--;
    }

}

/*
 * Apply every change to playerPosX and playerPosY to offsetX and offsetY but in reverse;
 */

bool collisionRectangles(int16_t x1, int16_t y1, uint8_t w1, uint8_t h1, int16_t x2, int16_t y2, uint8_t w2,
                         uint8_t h2) {

    if (x1 < x2 + w2 &&
        x1 + w1 > x2 &&
        y1 < y2 + h2 &&
        y1 + h1 > y2) {
        return true;
    }
    return false;

}

struct platform panelCollisionWithPlatform(uint8_t pX, uint8_t pY) {

    struct platform *pointer = platforms;

    for (uint8_t i = 0; i < PLATFORM_COUNT; i++) {

        if (collisionRectangles(pX, pY, PANEL_SIZE, PANEL_SIZE, pointer->x + offsetX, pointer->y + offsetY,
                                pointer->length,
                                PLATFORM_HEIGHT)) {

            return *pointer;

        }
        pointer++;

    }
    return (struct platform) {-1, -1, 0};


}

void clearPanel(uint8_t x, uint8_t y) {


/*
 *  Iterate panel 0 - panelsize -1 with stepsize 1 and from 0 - panelsize -4 with stepsize 4
 *
 */

    for (int i = x; i < x + PANEL_SIZE; i++) {

        for (int j = y; j < y + PANEL_SIZE; j += 4) {
            drawCorrect(i, j, 0);


        }
    }


}

void clearColliding() {


    for (int i = 0; i < 160; i += PANEL_SIZE) {


        for (int j = 0; j < 104; j += PANEL_SIZE) {


            struct platform may = panelCollisionWithPlatform(i, j);
            if (may.x != -1) {

                clearPanel(i, j);

            }

        }


    }


}


bool collisionFromTopOrBottom(int16_t x1, int16_t y1, uint8_t w1, uint8_t h1, int16_t x2, int16_t y2, uint8_t w2,
                              uint8_t h2) {

    if (
            y1 < y2 + h2 &&
            y1 + h1 > y2) {
        return true;
    }
    return false;


}


bool collisionWithPlatform() {

    for (uint8_t i = 0; i < PLATFORM_COUNT; i++) {


        // Set pointer to first platform

        platPtr = platforms + platformIndex;

        if (collisionRectangles(playerPosX, playerPosY, PLAYER_HEIGHT, PLAYER_HEIGHT, platPtr->x, platPtr->y,
                                platPtr->length,
                                PLATFORM_HEIGHT)) {
            playerState = standing;
            playerMovY = 0;

            if (collisionFromTopOrBottom(playerPosX, playerPosY, PLAYER_HEIGHT, PLAYER_HEIGHT, platPtr->x, platPtr->y,
                                         platPtr->length,
                                         PLATFORM_HEIGHT)) {
                int8_t calc = (platPtr->y - (playerPosY + PLAYER_HEIGHT));
                playerPosY += calc; //calc
                offsetY -= calc;
            }
            return true;
        }

        platformIndex++;
        if (platformIndex > 4) {
            platformIndex = 0;
        }
    }
    playerState = falling;
    return false;

}
// If platform is more than 10 behind the player it gets reset;



void update() {

    checkIfPlatformOutOfFrame();
    reset();

    if (playerState == standing) {
        jumpCounter = 2;
        dashCounter = 2;
        collisionWithPlatform();
    }
    if (playerState == jumping) {
        collisionWithPlatform();
    }
    if (dashLen > 0 && playerState == dashing) {
        dashLen--;
        playerPosX += SPEED * 2;
        offsetX -= SPEED * 2;
    }
    if (dashLen == 0 && playerState == dashing) {
        collisionWithPlatform();
    }
    if (playerState == falling) {

        playerPosY += playerMovY;
        offsetY -= playerMovY;
        playerMovY += GRAVITY;

        collisionWithPlatform();

    }

    playerPosX += SPEED;
    offsetX -= SPEED;


}


void getInput() {
    if (buttonPressed == '0') {
        if (B_SELECT) {
            //uart_putc(20);
            buttonPressed = '1';
            timePressed = getMsTimer();
        }
        if (B_PAUSE) {

            //uart_putc(30);
            buttonPressed = '1';
            timePressed = getMsTimer();
        }
        if (B_UP) {
            //uart_putc(50);
            buttonPressed = '1';
            timePressed = getMsTimer();
            playerPosY -= SPEED;
            offsetY += SPEED;

        }
        if (B_DOWN) {
            //uart_putc(60);
            buttonPressed = '1';
            timePressed = getMsTimer();
            playerPosY += SPEED;
            offsetY -= SPEED;


        }
        if (B_RIGHT) {
            //uart_putc(70);
            buttonPressed = '1';
            timePressed = getMsTimer();
            playerPosX += SPEED;
            offsetX -= SPEED;

        }
        if (B_LEFT) {
            //uart_putc(80);
            buttonPressed = '1';
            timePressed = getMsTimer();
            playerPosX -= SPEED;
            offsetX += SPEED;

        }

        if (B_A) {
            //uart_putc(90);
            buttonPressed = '1';
            jump();
            timePressed = getMsTimer();
        }
        if (B_B) {
            //uart_putc(100);
            buttonPressed = '1';
            dash();
            timePressed = getMsTimer();
        }
    }
}

void draw() {
/*
    drawPlayerZero();
    drawPlayer();
    drawPlatforms();

*/
    //printPlayer(playerPosX, playerPosY);
    printPlayer(5, 52);


    drawPlatforms();

    /*
    combineCollidingPages();
    drawFromBuffer();
*/
    //HAS TO BE THE LAST CALL IN DRAW()!!!!!!!!
}


void printPlayer(uint8_t x, uint8_t y) {


    drawCorrect(x + 0, y + 0, 0x3C);
    drawCorrect(x + 0, y + 4, 0x3F);
    drawCorrect(x + 1, y + 0, 0x08);
    drawCorrect(x + 1, y + 4, 0x57);
    drawCorrect(x + 2, y + 0, 0x0A);
    drawCorrect(x + 2, y + 4, 0x57);
    drawCorrect(x + 3, y + 0, 0x0A);
    drawCorrect(x + 3, y + 4, 0x57);
    drawCorrect(x + 4, y + 0, 0x0A);
    drawCorrect(x + 4, y + 4, 0x5B);
    drawCorrect(x + 5, y + 0, 0xEA);
    drawCorrect(x + 5, y + 4, 0x57);
    drawCorrect(x + 6, y + 0, 0xC2);
    drawCorrect(x + 6, y + 4, 0x03);
    drawCorrect(x + 7, y + 0, 0x02);


}


int main(void) {
    //Initialisierung ausfuehren

    init();

    uart_putc(80);
    _delay_ms(1000);

    uart_putc(10);
    _delay_ms(1000);

    posX = 40;
    posY = 40;


    while (1) {
/*
 * Set to approx 30 frames per second
 */

        if (getMsTimer() % 34 == 0) {
            getInput();
            clearColliding();
            update();
            draw();

        }

/*
 * Allow repress of buttons every 100 ms TODO: find nice value
 */
        if (timePressed + 150 <= getMsTimer()) {
            buttonPressed = '0';
        }
    }
}


//INIT
void init() {
    uartInit();   // serielle Ausgabe an PC
    ADCInit(4);   // Analoge Werte einlesen
    srand(getADCValue(4));
    timerInit();  // "Systemzeit" initialisieren
    buttonsInit();
    displayInit();
    bufferInit();
    platformInit();
}
