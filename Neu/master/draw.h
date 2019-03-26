//
// Created by torben on 07/03/19.
//

#ifndef ROBOTIK_DRAW_H
#define ROBOTIK_DRAW_H

#define DRAWING_BUFFER_SIZE 300

#include "platform.h"

struct pageToDraw {
    uint8_t x;
    uint8_t y;
    uint8_t h;
};

void drawPlayer(int16_t x, int16_t y, int16_t lastY, char forceRedraw, enum Form form);

void drawPowerUp(int16_t x, int16_t y, enum PowerUpType type, int16_t speed);

void drawScreen();

void drawCorrect(int16_t x, int16_t y, uint8_t h);

void drawString(char text[], uint8_t x, uint8_t y);

uint8_t nextGlyph(char glyph, uint8_t x, uint8_t y);

void drawMenue1();

void drawMenue2();

void drawMenue3();

void drawLives(uint8_t live);

void reDrawPlatforms(int16_t offsetX, int16_t speed);

void drawPlatforms(int16_t offsetX);

void drawPowerUps(int16_t offsetX, int16_t speed);

void drawScore(uint32_t score);

void drawSpeed(int16_t speed);

#endif //ROBOTIK_DRAW_H
