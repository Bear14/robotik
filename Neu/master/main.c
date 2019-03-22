/*
 *	Basis
 *	2009 Benjamin Reh und Joachim Schleicher
 */

/*
 * There is no bool in c
 */
typedef int bool;
#define true 1
#define false 0

#include <avr/interrupt.h>
#include <stdlib.h>
#include <avr/io.h>
#include <inttypes.h>
#include <util/delay.h>
#include "uart.h"
#include "adc.h"
#include "timer.h"
#include "buttons.h"
#include "display.h"
#include "draw.h"
#include "sprites.h"
#include "platform.h"


/*
 * Game logic turning knobs
 */
#define GRAVITY 1
#define JUMP_HEIGHT -8
#define INITIAL_SPEED 2
#define DASH_LENGTH 12
#define MAX_GAME_SPEED 8
#define PLAYER_HEIGHT 16
#define STEPS_BEFORE_RESET 3000

void init();

// volatile int16_t lastOffsetX = 5; TODO: delete

/*
 * Debounce
 */
volatile char buttonPressed = '0';
volatile uint32_t timePressed = 0;

/*
 * Actions
 */
volatile int8_t dashLen;
volatile int8_t dashCounter = 2;
volatile int8_t jumpCounter = 2;
volatile int8_t dashDist = DASH_LENGTH;

/*
 * Draw
 */
volatile int16_t offsetX = 5;
volatile int16_t lastPlayerPosY = 1;
volatile int16_t lastPlayerPosX = 0; // TODO: may be deleted

/*
 * Position
 */
volatile int16_t playerPosY = 0;
volatile int16_t playerPosX = 0;
volatile int8_t playerMovY = 0;

/*
 * Menu
 */
volatile uint8_t pfeilPosX = 35;
volatile uint8_t pfeilPosY = 35;

/*
 * Score and difficulty
 */
volatile int8_t platWidth = 5;
volatile int16_t gameSpeed = INITIAL_SPEED;
volatile uint32_t score = 0;
volatile uint32_t lastScore = 0;
volatile uint8_t lives = 3; // TODO: move to Init;


/*
 * State machines
 */
enum state {
    standing, dashing, jumping, falling
};
enum state playerState = falling; //TODO: move to Init;

enum gState {
    run, stop, set, menu_1, menu_2
};
enum gState gameState = set; //TODO: move to Init


enum Form playerForm = _normal; //TODO: move to Init

/*
 * To keep the player infinitely running we need to reset the position x integer before it overflows.
 * At every reset the difficulty is raised.
 *
 * @params void
 * @return void
 */
void reset() {

    if (playerPosX >= STEPS_BEFORE_RESET) {
        /*
         * Reset platforms, powerUps and the player
         */
        for (uint8_t i = 0; i < PLATFORM_COUNT; i++) {

            platforms[i].x -= playerPosX;

        }
        for (uint8_t j = 0; j < POWER_UP_COUNT; j++) {
            powerUps[j].x -= playerPosX;
        }

        offsetX = 5;
        playerPosX = 0;
        playerState = falling;

        /*
         * Raise difficulty
         */
        if(platWidth < 0) {
            platWidth--;
        }
        if (gameSpeed < MAX_GAME_SPEED) {
            gameSpeed += 1;
        }
    }
}

/*
 * @params void
 * @return void
 */
void dash() {

    if (dashCounter > 0) {
        playerState = dashing;
        playerMovY = 0;
        dashLen = dashDist;
        dashCounter--;
    }
}

/*
 * @params void
 * @return void
 */
void jump() {

    if (jumpCounter > 0) {
        playerState = jumping;
        playerMovY = JUMP_HEIGHT;
        dashLen = 0;
        jumpCounter--;
    }
}

/*
 * Basic collision detection of to rectangles
 *
 * @params takes to rectangles descried as { x, y, width, height}
 * @return bool
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

/*
 * @params void
 * @return bool
 */
bool dropCollision() {

    for (uint8_t i = 0; i < PLATFORM_COUNT; i++) {

        if (collisionRectangles(playerPosX, playerPosY + PLAYER_HEIGHT, PLATFORM_HEIGHT, 1, platforms[i].x,
                                platforms[i].y,
                                platforms[i].length,
                                PLATFORM_HEIGHT)) {
            return true;
        }

    }
    return false;
}

/*
 * @params void
 * @return void
 */
void collisionHandling() {


    for (uint8_t i = 0; i < PLATFORM_COUNT; i++) {

        if (collisionRectangles(playerPosX, playerPosY, PLAYER_HEIGHT, PLAYER_HEIGHT, platforms[i].x, platforms[i].y,
                                platforms[i].length,
                                PLATFORM_HEIGHT)) {

            if (lastPlayerPosY < platforms[i].y) {
                playerPosY = platforms[i].y - PLAYER_HEIGHT;
                playerState = standing;
            } else if (lastPlayerPosY > platforms[i].y) {
                playerPosY = platforms[i].y + PLATFORM_HEIGHT;
            }
        }
    }
}

/*
 * @params void
 * @return bool
 */
bool dashCollision() {

    for (uint8_t i = 0; i < PLATFORM_COUNT; i++) {
        if (collisionRectangles(playerPosX, playerPosY, PLAYER_HEIGHT, PLAYER_HEIGHT, platforms[i].x, platforms[i].y,
                                platforms[i].length, PLATFORM_HEIGHT)) {
            return true;
        }


    }
    return false;
}

/*
 * @params void
 * @return void
 */
void collisionWithPowerUp() {
    for (uint8_t j = 0; j < POWER_UP_COUNT; j++) {

        if (collisionRectangles(playerPosX, playerPosY, PLAYER_HEIGHT, PLAYER_HEIGHT, powerUps[j].x, powerUps[j].y,
                                1, POWER_UP_SIZE)) {


            switch (powerUps[j].type) {
                case none:
                    break;
                case live:
                    if (lives < 5) {
                        lives++;
                        drawLives(lives);
                    }
                    powerUps[j].type = none;
                    break;
                case death:
                    gameState = set;
                    powerUps[j].type = none;
                    break;
                case speedUp:
                    if (gameSpeed < MAX_GAME_SPEED) {
                        gameSpeed += 1;
                    }
                    powerUps[j].type = none;
                    break;
                case slow:
                    if (gameSpeed <= 1) {
                        gameSpeed -= 1;
                    }
                    powerUps[j].type = none;
                    break;
                case pointsUp:
                    score += gameSpeed * 50;
                    drawScore(score);
                    powerUps[j].type = none;
                    break;
                case pointsDown:
                    if (score <= gameSpeed * 20) {
                        score = 0;
                    } else {
                        score -= gameSpeed * 20;
                    }
                    drawScore(score);
                    powerUps[j].type = none;
                    break;
                case knight:
                    playerForm = _knight;
                    powerUps[j].type = none;
                            break;
                case sorcerer:
                    playerForm = _sorcerer;
                    powerUps[j].type = none;
                    break;
                case ranger:
                    playerForm = _ranger;
                    powerUps[j].type = none;
                    break;

            }

            clearPowerUp(powerUps[j].x + offsetX, powerUps[j].y);
            powerUps[j].x = -100;
            powerUps[j].y = -100;
            printPlayer(5, playerPosY, lastPlayerPosY, '1',playerForm);

        }


    }


}


/*
 * @params void
 * @return void
 */
void update() {

    if (playerPosY >= 110) {
        lives--;
        gameState = set;
    }

    reset();

    lastPlayerPosY = playerPosY;
    lastPlayerPosX = playerPosX;
    // lastOffsetX = offsetX; TODO: delete

    checkIfPlatformOutOfFrame(playerPosX, platWidth, gameSpeed);


    collisionWithPowerUp();
    if (playerState == standing) {

        switch (playerForm){
            case _normal:
                jumpCounter = 2;
                dashCounter = 2;
                dashDist = DASH_LENGTH;
                break;
            case _knight:
                jumpCounter = 2;
                dashCounter = 2;
                dashDist = 24;
                break;
            case _sorcerer:
                jumpCounter = 2;
                dashCounter = 3;
                dashDist = DASH_LENGTH;
                break;
            case _ranger:
                jumpCounter = 3;
                dashCounter = 2;
                dashDist = DASH_LENGTH;
                break;

        };

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

/*
 * @params void
 * @return void
 */
void getInput() {
    if (buttonPressed == '0') {
        switch (gameState) {
            case menu_1:
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
                        gameState = menu_2;
                        pfeilPosY = 55;
                        drawPfeil(pfeilPosX, pfeilPosY);
                    }
                }
                break;
            case menu_2:
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
                        gameSpeed = 2;
                        platWidth = 5;
                    }
                    if (pfeilPosY == 55) {
                        gameSpeed = 4;
                        platWidth = 3;
                    }
                    if (pfeilPosY == 65) { //SCHWIRIGKEIT Menue2
                        gameSpeed = 8;
                        platWidth = 1;
                    }
                    clear();
                    drawMenue1();
                    gameState = menu_1;
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
                    gameState = menu_1;
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
                    gameState = menu_1;
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

/*
 * @params void
 * @return void
 */
void draw() {

    drawPowerUps(offsetX, playerPosX - lastPlayerPosX);
    reDrawPlatforms(offsetX,playerPosX -lastPlayerPosX);
    printPlayer(5, playerPosY, lastPlayerPosY, '0',playerForm);
}
/*
 * @params void
 * @return void
 */
void setGame() {
    if (lives == 0) {

        score = 0;
        lives = 3;
        gameSpeed = INITIAL_SPEED;
    }

    clear();
    platformInit();
    initPowerUps();
    drawLives(lives);
    drawScore(score);
    offsetX = 5;
    drawPlatforms(offsetX);
    lastPlayerPosY = 1;
    printPlayer(5, 0, lastPlayerPosY, '0',playerForm);

    playerPosX = 0;
    playerPosY = 0;
    playerMovY = 0;
    playerState = falling;
    gameState = stop;
}

/*
 * @params void
 * @return void
 */
int main(void) {
    //Initialisierung ausfuehren

    init();

    uart_putc(80);
    _delay_ms(1000);

    uart_putc(10);
    _delay_ms(1000);

    printDragon();
    _delay_ms(1000);

    clear();
    gameState = menu_1;
    pfeilPosX = 40;
    pfeilPosY = 45;
    drawMenue1();
    drawPfeil(pfeilPosX, pfeilPosY);

    while (1) {
/*
 * Smooth frames
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

                update();
                draw();

            }

        }

/*
 * Allow repress of buttons every 150 ms TODO: find nice value
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
    platformInit();
    initPowerUps();
}
