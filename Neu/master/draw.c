//
// Created by torben on 07/03/19.
//
#include <stdlib.h>
#include <inttypes.h>
#include "display.h"
#include "draw.h"
#include "sprites.h"
#include "platform.h"
#include <stdio.h>
#include "save.h"

struct pageToDraw old = (struct pageToDraw) {0, 0, 0};

volatile uint8_t frameCounter = 0;

void drawPlayer(int16_t x, int16_t y, int16_t lastY, char forceRedraw, enum Form form) {

    //if (y != lastY || forceRedraw == '1') {

        clearPlayer(x, lastY);

        switch (form) {
            case _normal:
                printNormal(x, y,frameCounter);
                break;
            case _sorcerer:
                printSorcerer(x, y,frameCounter);
                break;
            case _ranger:
                printRanger(x, y,frameCounter);
                break;
            case _knight:
                printKnight(x, y,frameCounter);
                break;
            case _dash:
                printDash(x,y);
                break;
        };
        if(frameCounter > 12){
            frameCounter = 0;
        }else {
            frameCounter++;
        }
   // }
}

void drawString(char text[], uint8_t x, uint8_t y) {
    char *pointer = text;
    uint8_t nex_x = 0, nex_y = 0;

    for (; *pointer != '\0'; pointer++) {
        if (nex_x + x >= 155) { // wenn der Dildrand überläufen würde
            printGlyph('-', x + nex_x, y + nex_y);
            nex_y += 9;
            nex_x = 0;
        }
        printGlyph(*pointer, x + nex_x, y + nex_y);
        nex_x += nextGlyph(*pointer, x + nex_x, y + nex_y) + 1;
    }
}

uint8_t nextGlyph(char glyph, uint8_t x, uint8_t y) {
    uint8_t glyph_ende = 0;

    switch (glyph) {
        case '0' ... '9':
            glyph_ende = 4;
            break;
        case 'A' ... 'H':
            glyph_ende = 5;
            break;
        case 'I':
            glyph_ende = 3;
            break;
        case 'J':
            glyph_ende = 4;
            break;
        case 'K' ... 'Z':
            glyph_ende = 5;
            break;
        case ' ':
            glyph_ende = 3;
            break;
        case '-':
            glyph_ende = 3;
            break;
        default:
            break;
    }
    return glyph_ende;
}


void drawPowerUp(int16_t x, int16_t y, enum PowerUpType type, int16_t speed) {

    for (int i = 0; i < speed; i++) {
        drawCorrect(x + 8 + i, y, 0);
        drawCorrect(x + 8 + i, y + 4, 0);


    }
    switch (type) {
        case none:
            break;
        case live:
            printPUlive(x, y);
            break;
        case death:
            printPUdeath(x, y);
            break;
        case knight:
            printPUknight(x, y);
            break;
        case sorcerer:
            printPUsorcerer(x, y);
            break;
        case ranger:
            printPUranger(x, y);
            break;
        case slow:
            printPUslow(x, y);
            break;
        case speedUp:
            printPUspeedUp(x, y);
            break;
        case pointsUp:
            printPUpointsUp(x, y);
            break;
        case pointsDown:
            printPUpointsDown(x, y);
            break;

    };


}

void drawScreen() {

    //Version 1 unbewegt
    printDragon(0, 40);

    printNormal(98, 65,0);
    printKnight(118, 45,0);
    printSorcerer(118, 85,0);
    printRanger(130, 65,0);

    //DragonQuest
    printTitel(0, 13);

}

// the only shit we need
void drawCorrect(int16_t x, int16_t y, uint8_t h) {

    if (x >= 0 && x <= 159 && y >= 0 && y <= 104) {
        int16_t nex = y / 4;

        if (y % 4 == 0) {
            page(x, nex, h);
        }
        if (y % 4 == 1) {
            uint16_t hex = h << 2;
            uint16_t del = 65280;

            uint8_t page_2 = hex >> 8;
            uint8_t page_1 = hex;
            page_1 &= ~(del);

            if (x == old.x && nex == old.y) {
                page_1 = old.h | page_1;
            }
            page(x, nex, page_1);

            old = (struct pageToDraw) {x, nex, page_1};

            if (x == old.x && nex + 1 == old.y) {
                page_2 = old.h | page_2;
            }
            page(x, nex + 1, page_2);

            old = (struct pageToDraw) {x, nex + 1, page_2};

        }
        if (y % 4 == 2) {
            uint16_t hex = h << 4;
            uint16_t del = 65280;

            uint8_t page_2 = hex >> 8;
            uint8_t page_1 = hex;
            page_1 &= ~(del);

            if (x == old.x && nex == old.y) {
                page_1 = old.h | page_1;
            }
            page(x, nex, page_1);

            old = (struct pageToDraw) {x, nex, page_1};

            if (x == old.x && nex + 1 == old.y) {
                page_2 = old.h | page_2;
            }
            page(x, nex + 1, page_2);

            old = (struct pageToDraw) {x, nex + 1, page_2};

        }
        if (y % 4 == 3) {
            uint16_t hex = h << 6;
            uint16_t del = 65280;

            uint8_t page_2 = hex >> 8;


            uint8_t page_1 = hex;
            page_1 &= ~(del);

            if (x == old.x && nex == old.y) {
                page_1 = old.h | page_1;
            }
            page(x, nex, page_1);

            old = (struct pageToDraw) {x, nex, page_1};

            if (x == old.x && nex + 1 == old.y) {
                page_2 = old.h | page_2;
            }
            page(x, nex + 1, page_2);

            old = (struct pageToDraw) {x, nex + 1, page_2};
        }
    }
}

void drawScore(uint32_t score) {
    char text[18];
    sprintf(text, "%010d", score);
    drawString(text, 109, 96);
}

void drawSpeed(int16_t speed) {
    char text[2];
    sprintf(text, "%d", speed);
    drawString(text, 50, 96);
}

void drawMenue1() {
    clear();
    printTitel(0, 0);
    printDragon(0, 40);

    drawString("HAUPTMENUE", 73, 24);
    drawString("NEUES SPIEL", 73, 44);
    drawString("RESET HIGHSCORE", 73, 52);
    drawScore(readScore());
    drawString("SCHWIERIGKEIT", 73, 60);
    drawString("POWER UPS", 73, 68);
}

void drawMenue2() {
    clear();
    printTitel(0, 0);
    printDragon(0, 40);

    drawString("SCHWIERIGKEIT", 73, 24);
    drawString("LEICHT", 73, 44);
    drawString("NORMAL", 73, 52);
    drawString("SCHWER", 73, 60);
}

void drawMenue3() {
    clear();
    printTitel(0, 0);

    printPUlive(80, 24);
    drawString("LIVE", 90, 24);

    printPUslow(80, 36);
    drawString("SPEED DOWN", 90, 36);

    printPUpointsUp(80, 48);
    drawString("POINTS UP", 90, 48);

    printPUknight(20, 64);
    drawString("KNIGHT", 10, 74);
    printKnight(15, 88,0);

    printPUsorcerer(70, 64);
    drawString("SORCERER", 56, 74);
    printSorcerer(65, 88,0);

    printPUranger(120, 64);
    drawString("RANGER", 110, 74);
    printRanger(115, 88,0);


    printPUdeath(5, 24);
    drawString("INST DEATH", 15, 24);

    printPUspeedUp(5, 36);
    drawString("SPEED UP", 15, 36);

    printPUpointsDown(5, 48);
    drawString("POINTS DOWN", 15, 48);
}


void drawLives(uint8_t live) {
    for (int i = 0; i < live; i++) {

        printHeart(65 + i * 8, 96);
    }
}

void drawPlatforms(int16_t offsetX) {


    for (uint8_t i = 0; i < PLATFORM_COUNT; i++) {


        printPlatform(platforms[i]);
    }
}

void reDrawPlatforms(int16_t offsetX, int16_t speed) {


    for (uint8_t i = 0; i < PLATFORM_COUNT; i++) {


        rePrintPlatform(platforms[i], offsetX, speed);
    }
}

void drawPowerUps(int16_t offsetX, int16_t speed) {

    for (uint8_t i = 0; i < POWER_UP_COUNT; i++) {

        drawPowerUp(powerUps[i].x + offsetX, powerUps[i].y, powerUps[i].type, speed);

    }
}