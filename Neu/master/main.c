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
#define INITIAL_SPEED 2
#define DASH_LENGTH 12
#define PLATFORM_COUNT 3

#define PLATFORM_HEIGHT 8

#define PANEL_SIZE 16

void init();

volatile int8_t platWidth = 6;

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
// Player height is 8!

#define PLAYER_HEIGHT 16

volatile uint64_t score = 0;
volatile uint8_t lives = 4;

struct platform {
    int16_t x;
    int16_t y;
    uint8_t length;
};


struct platform platforms[PLATFORM_COUNT];

struct platform getPlatformFromIndex(uint8_t ind) {
    struct platform *pointer = platforms;
    pointer += ind;
    return *pointer;
}

void printHeart(int16_t x, int16_t y) {
    drawCorrect(x + 0, y + 0, 0xFC);

    drawCorrect(x + 1, y + 0, 0xFF);
    drawCorrect(x + 1, y + 4, 0x03);
    drawCorrect(x + 2, y + 0, 0xFF);
    drawCorrect(x + 2, y + 4, 0x0F);
    drawCorrect(x + 3, y + 0, 0xFC);
    drawCorrect(x + 3, y + 4, 0x3F);
    drawCorrect(x + 4, y + 0, 0xF0);
    drawCorrect(x + 4, y + 4, 0xFF);
    drawCorrect(x + 5, y + 0, 0xFC);
    drawCorrect(x + 5, y + 4, 0x3F);
    drawCorrect(x + 6, y + 0, 0xFF);
    drawCorrect(x + 6, y + 4, 0x0F);
    drawCorrect(x + 7, y + 0, 0xFF);
    drawCorrect(x + 7, y + 4, 0x03);
    drawCorrect(x + 8, y + 0, 0xFC);
}

void printPlatform(int16_t x, int16_t y) {
    drawCorrect(x + 0, y + 0, 0xFF);
    drawCorrect(x + 0, y + 4, 0x56);
    drawCorrect(x + 1, y + 0, 0xBF);
    drawCorrect(x + 1, y + 4, 0x56);
    drawCorrect(x + 2, y + 0, 0xAF);
    drawCorrect(x + 2, y + 4, 0x55);
    drawCorrect(x + 3, y + 0, 0x6F);
    drawCorrect(x + 3, y + 4, 0x55);
    drawCorrect(x + 4, y + 0, 0xAF);
    drawCorrect(x + 4, y + 4, 0x55);
    drawCorrect(x + 5, y + 0, 0xBF);
    drawCorrect(x + 5, y + 4, 0x56);
    drawCorrect(x + 6, y + 0, 0xFF);
    drawCorrect(x + 6, y + 4, 0x6A);
    drawCorrect(x + 7, y + 0, 0xFF);
    drawCorrect(x + 7, y + 4, 0x6F);
    drawCorrect(x + 8, y + 0, 0xFF);
    drawCorrect(x + 8, y + 4, 0x6B);
    drawCorrect(x + 9, y + 0, 0xFF);
    drawCorrect(x + 9, y + 4, 0x5A);
    drawCorrect(x + 10, y + 0, 0xBF);
    drawCorrect(x + 10, y + 4, 0x56);
    drawCorrect(x + 11, y + 0, 0xAF);
    drawCorrect(x + 11, y + 4, 0x55);
    drawCorrect(x + 12, y + 0, 0x6F);
    drawCorrect(x + 12, y + 4, 0x55);
    drawCorrect(x + 13, y + 0, 0xAF);
    drawCorrect(x + 13, y + 4, 0x55);
    drawCorrect(x + 14, y + 0, 0xBF);
    drawCorrect(x + 14, y + 4, 0x56);
}

void clearPlayerColumn(uint8_t y, char direction) {
    for (int i = 5; i < PLAYER_HEIGHT + 5; i++) {

        if (direction == 'u') {

            for (int j = 0; j < 25; j++) {

                page(i, j, 0);
            }


        } else if (direction == 'd') {

            for (int j = y / 4; j < 25 - y / 4; j++) {

                page(i, j, 0);
            }


        }


    }
}


void printPlayer(int16_t x, int16_t y, int16_t lastY) {

    if (y != lastY) {

        drawCorrect(x + 0, lastPlayerPosY + 4, 0);
        drawCorrect(x + 0, lastPlayerPosY + 0, 0);
        drawCorrect(x + 1, lastPlayerPosY + 4, 0);
        drawCorrect(x + 1, lastPlayerPosY + 0, 0);
        drawCorrect(x + 2, lastPlayerPosY + 4, 0);
        drawCorrect(x + 2, lastPlayerPosY + 0, 0);
        drawCorrect(x + 3, lastPlayerPosY + 4, 0);
        drawCorrect(x + 3, lastPlayerPosY + 0, 0);
        drawCorrect(x + 4, lastPlayerPosY + 4, 0);
        drawCorrect(x + 4, lastPlayerPosY + 0, 0);
        drawCorrect(x + 5, lastPlayerPosY + 4, 0);
        drawCorrect(x + 5, lastPlayerPosY + 0, 0);
        drawCorrect(x + 6, lastPlayerPosY + 4, 0);
        drawCorrect(x + 6, lastPlayerPosY + 0, 0);
        drawCorrect(x + 7, lastPlayerPosY + 0, 0);
        drawCorrect(x + 7, lastPlayerPosY + 4, 0);


        drawCorrect(x + 0, y + 4, 0xF8);
        drawCorrect(x + 1, y + 0, 0x02);
        drawCorrect(x + 1, y + 4, 0x02);
        drawCorrect(x + 2, y + 0, 0xAA);
        drawCorrect(x + 2, y + 4, 0xAE);
        drawCorrect(x + 3, y + 0, 0x7A);
        drawCorrect(x + 3, y + 4, 0x2E);
        drawCorrect(x + 4, y + 0, 0x5A);
        drawCorrect(x + 4, y + 4, 0x2E);
        drawCorrect(x + 5, y + 0, 0x78);
        drawCorrect(x + 5, y + 4, 0xAE);
        drawCorrect(x + 6, y + 0, 0x03);
        drawCorrect(x + 6, y + 4, 0xC2);
        drawCorrect(x + 7, y + 0, 0xFC);
        drawCorrect(x + 7, y + 4, 0x3D);


    }
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

void drawLives() {
    for (int i = 0; i < lives; i++) {

        printHeart(100 + i * 8, 4);

    }


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

void drawPlatform(int16_t x, int16_t y, uint8_t length) {


    for (int16_t i = x; i < x + length; i += 15) {


        //printPlatform(i,y);

        printPlatform(i, y);
        //printPlayer(i,y);
        //drawCorrect(i,y,0x1F);
        //drawCorrect(i,y,0xFF);
    }

}


void reDrawPlatform(int16_t x, int16_t y, uint8_t length) {

    drawCorrect(x + length + 1, y, 0);
    drawCorrect(x + length + 1, y + 4, 0);
    drawCorrect(x + length + 2, y, 0);
    drawCorrect(x + length + 2, y + 4, 0);
    drawCorrect(x + length + 3, y, 0);
    drawCorrect(x + length + 3, y + 4, 0);
    drawCorrect(x + length + 4, y, 0);
    drawCorrect(x + length + 4, y + 4, 0);
    drawCorrect(x + length + 5, y, 0);
    drawCorrect(x + length + 5, y + 4, 0);
    drawCorrect(x + length + 6, y, 0);
    drawCorrect(x + length + 6, y + 4, 0);
    drawCorrect(x + length + 7, y, 0);
    drawCorrect(x + length + 7, y + 4, 0);
    drawCorrect(x + length + 8, y, 0);
    drawCorrect(x + length + 8, y + 4, 0);
    drawCorrect(x + length + 9, y, 0);
    drawCorrect(x + length + 9, y + 4, 0);
    drawCorrect(x + length + 10, y, 0);
    drawCorrect(x + length + 10, y + 4, 0);
    drawCorrect(x + length + 11, y, 0);
    drawCorrect(x + length + 11, y + 4, 0);
    drawCorrect(x + length + 12, y, 0);
    drawCorrect(x + length + 12, y + 4, 0);


    printPlatform(x, y);

}

void reDrawPlatforms() {
    struct platform *pointer = platforms;

    for (uint8_t i = 0; i < PLATFORM_COUNT; i++) {
        struct platform toDraw = *pointer;
        reDrawPlatform(toDraw.x + offsetX, toDraw.y, toDraw.length);

        pointer++;

    }
}

void drawPlatforms() {

    struct platform *pointer = platforms;

    for (uint8_t i = 0; i < PLATFORM_COUNT; i++) {
        struct platform toDraw = *pointer;
        drawPlatform(toDraw.x + offsetX, toDraw.y, toDraw.length);

        pointer++;

    }

}

struct platform createNewPlatform(struct platform last) {
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

void checkIfPlatformOutOfFrame() {

    uint8_t ind = getIndexMinX();

    struct platform farthestLeft = getPlatformFromIndex(ind);

    if (farthestLeft.x + farthestLeft.length < playerPosX - 5) {

        struct platform toAdd = createNewPlatform(getPlatformFromIndex(getIndexMaxX()));

        addPlatformAtIndex(ind, toAdd); // make platform

    }


}

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
        gameSpeed += 1;
        playerState = falling;
        sei();

    }

}




enum gState {
    run, stop, set, menue
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

        if (collisionRectangles(playerPosX,playerPosY,PLAYER_HEIGHT,PLAYER_HEIGHT,plat.x,plat.y,plat.length,PLATFORM_HEIGHT)) {


            playerMovY = 0;
            if (lastPlayerPosY < plat.y) {
                playerPosY = plat.y - PLAYER_HEIGHT;
                playerState = standing;
            } else if (lastPlayerPosY > plat.y) {
                playerPosY = plat.y +PLATFORM_HEIGHT;
            }


        }


        pointer++;
    }


}



void update() {

    if (playerPosY >= 110) {
        gameState = set;
    }

    lastPlayerPosY = playerPosY;
    lastPlayerPosX = playerPosX;
    lastOffsetX = offsetX;

    checkIfPlatformOutOfFrame();
    reset();

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
    }
    if (dashLen == 0 && playerState == dashing) {

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
    score += gameSpeed;
    playerPosX += gameSpeed;
    offsetX -= gameSpeed;


}


void getInput() {
    if (buttonPressed == '0') {
      if(gameState = menue){
        if (B_DOWN) {
            //uart_putc(60);
            buttonPressed = '1';
            timePressed = getMsTimer();
            pfeilPosY += 10;
        }
        if (B_UP) {
            //uart_putc(50);
            buttonPressed = '1';
            timePressed = getMsTimer();
            pfeilPosY -=10;
        }
        if (B_A) {
            //uart_putc(90);
            buttonPressed = '1';
            timePressed = getMsTimer();

        }
      }
        if (B_SELECT) {
            //uart_putc(20);
            buttonPressed = '1';
            timePressed = getMsTimer();
            //gameState = run;
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
        if (gameState == run) {
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
        }
    }
}

void draw() {

    drawLives();

    reDrawPlatforms();
    printPlayer(5, playerPosY, lastPlayerPosY);
}


void setGame() {
    lives--;
    if (lives == 0) {

        score = 0;
        lives = 3;
    }

    gameSpeed = INITIAL_SPEED;

    clear();
    platformInit();
    drawLives();
    offsetX = 5;
    drawPlatforms();
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
            if(gameState == menue){
<<<<<<< HEAD
              drawmenue();
=======
              menue()
>>>>>>> dc6b81f62d043fd586baf356b37ab4eb909a5ba2
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
}
