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
#include "sprites.h"
#include "platform.h"


#define GRAVITY 1
#define JUMP_HEIGHT -8
#define INITIAL_SPEED 2
#define DASH_LENGTH 12
#define MAX_GAME_SPEED 8

void init();

volatile int8_t platWidth = 5;

volatile int16_t gameSpeed = INITIAL_SPEED;

volatile int16_t lastOffsetX = 5;
volatile int16_t offsetX = 5;
volatile char buttonPressed = '0';
volatile uint32_t timePressed = 0;


volatile int8_t dashLen;
volatile int8_t dashCounter = 2;
volatile int8_t jumpCounter = 2;


volatile int16_t lastPlayerPosY = 1;
volatile int16_t lastPlayerPosX = 0;
volatile int16_t playerPosY = 0;
volatile int16_t playerPosX = 0;
volatile int8_t playerMovY = 0;

volatile uint8_t pfeilPosX = 35;
volatile uint8_t pfeilPosY = 35;

#define PLAYER_HEIGHT 16

volatile uint32_t score = 0;
volatile uint32_t lastScore = 0;
volatile uint8_t lives = 4;

enum state {
    standing, dashing, jumping, falling
};
enum state playerState = falling;


void reset() {

    if (playerPosX >= 3000) {

        cli();
        struct platform *pointer = platforms;


        for (int i = 0; i < PLATFORM_COUNT; i++) {
            pointer->x -= playerPosX;
            pointer++;
        }

        offsetX = 5;
        platWidth--;
        playerPosX = 0;
        if (gameSpeed < MAX_GAME_SPEED) {
            gameSpeed += 1;
        }
        playerState = falling;
        sei();

    }

}


enum gState {
    run, stop, set, menue1, menue2
};

enum gState gameState = set;


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


bool dropCollision() {
    struct platform *pointer = platforms;
    for (uint8_t i = 0; i < PLATFORM_COUNT; i++) {


        if (collisionRectangles(playerPosX, playerPosY + PLAYER_HEIGHT, PLATFORM_HEIGHT, 1, pointer->x, pointer->y,
                                pointer->length,
                                PLATFORM_HEIGHT)) {
            return true;
        }


        pointer++;
    }

    return false;

}


void collisionHandling() {

    struct platform *pointer = platforms;
    for (int i = 0; i < PLATFORM_COUNT; i++) {

        struct platform plat = *pointer;

        if (collisionRectangles(playerPosX, playerPosY, PLAYER_HEIGHT, PLAYER_HEIGHT, plat.x, plat.y, plat.length,
                                PLATFORM_HEIGHT)) {


            playerMovY = 0;
            if (lastPlayerPosY < plat.y) {
                playerPosY = plat.y - PLAYER_HEIGHT;
                playerState = standing;
            } else if (lastPlayerPosY > plat.y) {
                playerPosY = plat.y + PLATFORM_HEIGHT;
            }


        }


        pointer++;
    }


}

bool dashCollision() {
    struct platform *pointer = platforms;
    for (int i = 0; i < PLATFORM_COUNT; i++) {

        if (collisionRectangles(playerPosX, playerPosY, PLAYER_HEIGHT, PLAYER_HEIGHT, pointer->x, pointer->y,
                                pointer->length,
                                PLATFORM_HEIGHT)) {
            return true;
        }


        pointer++;
    }
    return false;

}


void collisionWithPowerUp() {
    for (int8_t j = 0; j < POWER_UP_COUNT; j++) {

        if (collisionRectangles(playerPosX, playerPosY, PLAYER_HEIGHT, PLAYER_HEIGHT, powerUps[j].x, powerUps[j].y,
                                1, POWER_UP_SIZE)) {

            if (playerState != dashing) {
                gameState = set;
            } else {

                switch (powerUps[j].type) {
                    case none:
                        break;
                    case live:
                        if (lives < 5) {
                            lives++;
                        }
                        powerUps[j].type = none;
                        break;
                    case death:
                        gameState = set;
                        powerUps[j].type = none;
                        break;
                    case speedUp:
                        gameSpeed += 1; // TODO: MAX GAME SPEED
                        powerUps[j].type = none;
                        break;
                    case slow:
                        if (gameSpeed <= 1) {
                            gameSpeed -= 1;
                        }
                        powerUps[j].type = none;
                        break;
                    case pointsUp:
                        score += 1000;
                        powerUps[j].type = none;
                        break;
                    case pointsDown:
                        score -= 500;
                        powerUps[j].type = none;
                        break;

                }

                clearPowerUp(powerUps[j].x + offsetX, powerUps[j].y, gameSpeed);
                powerUps[j].x = -10;
                powerUps[j].y = -10;
                printPlayer(playerPosX, playerPosY, lastPlayerPosY);
                lastPlayerPosY = 0;
                printPlayer(playerPosX, playerPosY, lastPlayerPosY);
            }

        }


    }


}


void update() {

    if (playerPosY >= 110) {
        gameState = set;
    }

    lastPlayerPosY = playerPosY;
    lastPlayerPosX = playerPosX;
    lastOffsetX = offsetX;

    checkIfPlatformOutOfFrame(playerPosX, platWidth, gameSpeed);
    reset();

    collisionWithPowerUp();
    if (playerState == standing) {
        jumpCounter = 2;
        dashCounter = 2;

        if (!dropCollision()) {
            playerState = falling;
        }
    }
    if (playerState == jumping) {

        playerState = falling;
        collisionHandling();
    }
    if (dashLen > 0 && playerState == dashing) {
        dashLen -= gameSpeed;
        playerPosX += gameSpeed * 2;
        offsetX -= gameSpeed * 2;
        if (dashCollision()) {
            gameState = set;
        }
    }
    if (dashLen <= 0 && playerState == dashing) {

        if (!dropCollision()) {
            playerState = falling;
        }
    }
    if (playerState == falling) {

        playerPosY += playerMovY;
        if (playerMovY < 5) {
            playerMovY += GRAVITY;
        }

        collisionHandling();


    }

    if (playerPosX % 100 == 0) {
        score += 1;
        drawScore(score);
    }
    playerPosX += gameSpeed;
    offsetX -= gameSpeed;


}


void getInput() {
    if (buttonPressed == '0') {
        switch (gameState) {
            case menue1:
                if (B_DOWN) {
                    //uart_putc(60);
                    buttonPressed = '1';
                    timePressed = getMsTimer();
                    deletePfeil(pfeilPosX, pfeilPosY);
                    if (pfeilPosY + 10 <= 65) {
                        pfeilPosY += 10;
                    } else {
                        pfeilPosY = 45;
                    }
                    drawPfeil(pfeilPosX, pfeilPosY);
                }
                if (B_UP) {
                    //uart_putc(50);
                    buttonPressed = '1';
                    timePressed = getMsTimer();
                    deletePfeil(pfeilPosX, pfeilPosY);
                    if (pfeilPosY - 10 >= 45) {
                        pfeilPosY -= 10;
                    } else {
                        pfeilPosY = 65;
                    }
                    drawPfeil(pfeilPosX, pfeilPosY);
                }
                if (B_A) {
                    //uart_putc(90);
                    buttonPressed = '1';
                    timePressed = getMsTimer();
                    if (pfeilPosY == 45) { // Neues Game
                        gameState = set;
                    }
                    if (pfeilPosY == 55) {

                    }
                    if (pfeilPosY == 65) { //SCHWIRIGKEIT Menue2
                        clear();
                        drawMenue2();
                        gameState = menue2;
                        pfeilPosY = 55;
                        drawPfeil(pfeilPosX, pfeilPosY);
                    }
                }
                break;
            case menue2:
                if (B_DOWN) {
                    //uart_putc(60);
                    buttonPressed = '1';
                    timePressed = getMsTimer();
                    deletePfeil(pfeilPosX, pfeilPosY);
                    if (pfeilPosY + 10 <= 65) {
                        pfeilPosY += 10;
                    } else {
                        pfeilPosY = 45;
                    }
                    drawPfeil(pfeilPosX, pfeilPosY);
                }
                if (B_UP) {
                    //uart_putc(50);
                    buttonPressed = '1';
                    timePressed = getMsTimer();
                    deletePfeil(pfeilPosX, pfeilPosY);
                    if (pfeilPosY - 10 >= 45) {
                        pfeilPosY -= 10;
                    } else {
                        pfeilPosY = 65;
                    }
                    drawPfeil(pfeilPosX, pfeilPosY);
                }
                if (B_A) {
                    //uart_putc(90);
                    buttonPressed = '1';
                    timePressed = getMsTimer();
                    if (pfeilPosY == 45) { // Neues Game
                        gameSpeed = INITIAL_SPEED - 1;
                    }
                    if (pfeilPosY == 55) {
                        gameSpeed = INITIAL_SPEED;
                    }
                    if (pfeilPosY == 65) { //SCHWIRIGKEIT Menue2
                        gameSpeed = INITIAL_SPEED + 5;
                    }
                    clear();
                    drawMenue1();
                    gameState = menue1;
                    pfeilPosY = 45;
                    drawPfeil(pfeilPosX, pfeilPosY);
                }
                break;
            case run:
                if (B_UP) {
                    //uart_putc(50);
                    buttonPressed = '1';
                    timePressed = getMsTimer();
                    playerPosY -= gameSpeed;
                    //offsetY += gameSpeed;

                }
                if (B_DOWN) {
                    //uart_putc(60);
                    buttonPressed = '1';
                    timePressed = getMsTimer();
                    playerPosY += gameSpeed;
                    //offsetY -= gameSpeed;
                }
                if (B_RIGHT) {
                    //uart_putc(70);
                    buttonPressed = '1';
                    timePressed = getMsTimer();
                    playerPosX += gameSpeed;
                    offsetX -= gameSpeed;

                }
                if (B_LEFT) {
                    //uart_putc(80);
                    buttonPressed = '1';
                    timePressed = getMsTimer();
                    playerPosX -= gameSpeed;
                    offsetX += gameSpeed;
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
                if (B_SELECT) {
                    //uart_putc(20);
                    buttonPressed = '1';
                    timePressed = getMsTimer();
                    //gameState = run;
                    gameState = menue1;
                    clear();
                    drawMenue1();
                    pfeilPosX = 45;
                    pfeilPosY = 45;
                    drawPfeil(pfeilPosX, pfeilPosY);
                }
                if (B_PAUSE) {

                    //uart_putc(30);
                    buttonPressed = '1';
                    timePressed = getMsTimer();
                    if (gameState == run) {
                        gameState = stop;
                    } else {
                        gameState = run;
                    }
                }
                break;
            default:
                if (B_SELECT) {
                    //uart_putc(20);
                    buttonPressed = '1';
                    timePressed = getMsTimer();
                    //gameState = run;
                    gameState = menue1;
                    clear();
                    drawMenue1();
                    pfeilPosX = 45;
                    pfeilPosY = 45;
                    drawPfeil(pfeilPosX, pfeilPosY);
                }
                if (B_PAUSE) {

                    //uart_putc(30);
                    buttonPressed = '1';
                    timePressed = getMsTimer();
                    if (gameState == run) {
                        gameState = stop;
                    } else {
                        gameState = run;
                    }
                }
                break;
        }
    }
}

void draw() {

    //drawLives(lives);
    if (lastScore != score) {
       // drawScore(score);
    }
    drawPowerUps(offsetX, playerPosX - lastPlayerPosX);
    reDrawPlatforms(offsetX);
    printPlayer(5, playerPosY, lastPlayerPosY);
}


void setGame() {
    lives--;
    if (lives == 0) {

        score = 0;
        lives = 3;
    }

    //gameSpeed = 4;

    clear();
    platformInit();
    initPowerUps();
    drawLives(lives);
    drawScore(score);
    offsetX = 5;
    drawPlatforms(offsetX);
    lastPlayerPosY = 1;
    printPlayer(5, 0, lastPlayerPosY);

    playerPosX = 0;
    playerPosY = 0;
    playerMovY = 0;
    playerState = falling;
    gameState = stop;
}

int main(void) {
    //Initialisierung ausfuehren

    init();

    uart_putc(80);
    _delay_ms(1000);

    uart_putc(10);
    _delay_ms(1000);

    printDragon();
    _delay_ms(5000);

    clear();
    gameState = menue1;
    pfeilPosX = 40;
    pfeilPosY = 45;
    drawMenue1();
    drawPfeil(pfeilPosX, pfeilPosY);

    while (1) {
/*
 * Set to approx 30 frames per second
 */
        if (getMsTimer() % 34 == 0) {
            if (gameState == set) {
                /*
                 * If Lifes = 0 --> scores = 0;
                 *
                 */

                setGame();

            }
            getInput();
            if (gameState == run) {

                //clearPlatforms();
                //clearColliding();
                update();
                //printPlatform(10,12);
                draw();

            }

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
    //bufferInit();
    platformInit();
    initPowerUps();
}
