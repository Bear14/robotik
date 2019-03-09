/* 
 *	Basis
 *	2009 Benjamin Reh und Joachim Schleicher
 */
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

typedef int bool;
#define true 1
#define false 0

void init();

volatile int16_t posY = 0;
volatile int16_t posX = 0;
volatile int16_t offsetY = 52;
volatile int16_t offsetX = 5;
volatile char buttonPressed = '0';
volatile uint32_t timePressed = 0;
/*
int16_t platformX = 0;
int16_t platformY = 12;
uint8_t platformLength = 80;
*/




struct platform {
    int16_t x;
    int16_t y;
    uint8_t length;
};


struct platform platforms[PLATFORM_COUNT];
struct platform *platPtr;
uint8_t platformIndex = 0;


volatile struct platform platform_1 = (struct platform) {0, 12, 80};


void addPlatform(int16_t x, int16_t y, uint8_t length) {
    platPtr = platforms;
    platPtr += platformIndex;

    *platPtr = (struct platform) {0, 0, 0};


    platformIndex++;
    if (platformIndex > 4) {
        platformIndex = 0;
    }
    platPtr = platforms;
}

void platformInit() {
    platPtr = platforms;
    *platPtr = (struct platform) {0, 12, 80};
    platPtr++;
    *platPtr = (struct platform) {90, 30, 40};
    platPtr++;
    *platPtr = (struct platform) {200, 20, 50};
    platPtr++;
    *platPtr = (struct platform) {300, 30, 50};
    platPtr++;
    *platPtr = (struct platform) {400, 40, 50};
    platPtr = platforms;

};

void drawPlatform(int16_t x, int16_t y, uint8_t length) {

    for (int16_t i = x; i < x + length; i++) {
        drawCorrect(i, y, 0xFF);


    }

}

void drawPlatforms() {
    platPtr = platforms;
    for (uint8_t i = 0; i < PLATFORM_COUNT; i++) {
        struct platform toDraw = *platPtr;
        drawPlatform(toDraw.x + offsetX, toDraw.y + offsetY, toDraw.length);
        platPtr++;
    }
    platPtr = platforms;

}

volatile int8_t dashLen;
volatile int8_t dashCounter = 3;
volatile int8_t jumpCounter = 2;


volatile int16_t playerPosY = 0;
volatile int16_t playerPosX = 0;
volatile int8_t playerMovY = 0;
volatile int8_t playerMovX = 0;
// Player height is 8!

void drawPlayer() {

    for (int i = 5; i < 5 + 8; i++) {
        drawCorrect(i, 52, 0xFF);
        drawCorrect(i, 56, 0xFF);
    }

};

void drawPlayerZero() {
    for (int i = playerPosX; i < playerPosX + 8; i++) {
        drawCorrect(i, playerPosY, 0xFF);
        drawCorrect(i, playerPosY + 4, 0xFF);
    }

};




enum state {
    standing, dashing, jumping, falling
};
enum state playerState = falling;

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

bool
collisionRectangles(int16_t x1, int16_t y1, uint8_t w1, uint8_t h1, int16_t x2, int16_t y2, uint8_t w2, uint8_t h2) {

    if (x1 < x2 + w2 &&
        x1 + w1 > x2 &&
        y1 < y2 + h2 &&
        y1 + h1 > y2) {
        return true;
    }
    return false;

}


/*

void collisionWithGround() {
    playerState = falling;

    platPtr = platforms;
    for (uint8_t i = 0; i < PLATFORM_COUNT; i++) {

        if (playerPosX + 8 >= platPtr->x) {

            if (((playerPosY + 8) + playerMovY) >= platPtr->y) {

                int8_t calc = (platPtr->y - (playerPosY + 8));
                playerPosY += calc; //calc
                offsetY -= calc;

                playerState = standing;
                dashCounter = 4;
                jumpCounter = 2;



                //playerMovY = 0;

            } else {
                playerState = falling;
            }

        } else if((platPtr->x + platPtr->length) < playerPosX){
            playerState = falling;
           // playerState = falling;
        }


        platPtr++;

    }
    platPtr = platforms;

    if (playerPosY + playerMovY >= platform_1.y) {

        //playerPosY = platformY - 8;
        offsetY -= ((platform_1.y - playerPosY) - 8);
        playerPosY += ((platform_1.y - playerPosY) - 8);
        //
        // offsetY = ;
        playerState = standing;
        dashCounter = 4;
        jumpCounter = 2;

    } else {

        // If  not colliding apply gravity and jump;

        playerPosY += playerMovY;
        offsetY -= playerMovY;

        playerMovY += GRAVITY;
    }
}
*/

// If platform is more than 10 behind the player it gets reset;

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

        if (collisionRectangles(playerPosX, playerPosY, 8, 8, platPtr->x, platPtr->y, platPtr->length,
                                PLATFORM_HEIGHT)) {
            playerState = standing;
            playerMovY = 0;

            if (collisionFromTopOrBottom(playerPosX, playerPosY, 8, 8, platPtr->x, platPtr->y, platPtr->length,
                                         PLATFORM_HEIGHT)) {
                int8_t calc = (platPtr->y - (playerPosY + 8));
                playerPosY += calc; //calc
                offsetY -= calc;
            }

            /*
            int8_t calc = (platPtr->y - (playerPosY + 8));
            playerPosY += calc; //calc
            offsetY -= calc;
             */
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


void checkPlatform() {
    platPtr = platforms;
    platPtr += platformIndex;
    struct platform check = *platPtr;
    if ((check.x + check.length) < (playerPosX - 10)) {
        // *platPtr = (struct platform) {0,0,0};
        addPlatform(1, 1, 1);
    }
    platPtr = platforms;

}

void update() {

    checkPlatform();

    if (playerState == standing) {
        jumpCounter = 2;
        dashCounter = 3;
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

    //playerPosX += SPEED;
    //offsetX -= SPEED;

/*
    if(playerPosY >= platformY){
        page(159,13,0xFF);
    }
*/

    //
    // playerPosX+=SPEED;
    //offsetX-=SPEED;
/*
    if (playerState == jumping || playerState == standing) {
        collisionWithGround();
    }
    if (dashLen > 0 && playerState == dashing) {
        dashLen--;
        playerPosX += SPEED * 2;
        offsetX -= SPEED * 2;
    } else if (dashLen == 0 && playerState == dashing) {
        collisionWithGround();
    }


    if(playerState == falling){

        collisionWithGround();
        if(playerState == falling) {
            playerPosY += playerMovY;
            offsetY -= playerMovY;
            playerMovY += GRAVITY;
        }
    }

    // playerPosX += SPEED;
    // offsetX -= SPEED;

*/
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


    //drawCorrect(40, 30, 0xC3);
    //drawCorrect(posX, posY, 0xC3);

    //drawGround(playerPosX,playerPosY,8);
    //drawGround(playerPosX,playerPosY+4,8);
    drawPlayerZero();
    //drawGround(platformX, platformY, platformLength);
    drawPlayer();
    //PlayerPosX start value;
    drawPlatforms();
    //drawGround(platform_1.x + offsetX, platform_1.y + offsetY, platform_1.length);

    combineCollidingPages();
    drawFromBuffer(); //HAS TO BE THE LAST CALL IN DRAW()!!!!!!!!
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
    ADCInit(0);   // Analoge Werte einlesen
    timerInit();  // "Systemzeit" initialisieren
    buttonsInit();
    displayInit();
    bufferInit();
    platformInit();
}
