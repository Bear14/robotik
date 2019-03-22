//
// Created by torben on 07/03/19.
//

#ifndef ROBOTIK_DRAW_H
#define ROBOTIK_DRAW_H

#define DRAWING_BUFFER_SIZE 300

struct pageToDraw {
    uint8_t x;
    uint8_t y;
    uint8_t h;
};

void drawCorrect(int16_t x, int16_t y, uint8_t h);

void drawString(char text[], uint8_t x, uint8_t y);

uint8_t nextGlyph(char glyph, uint8_t x, uint8_t y);

void drawGlyph(char glyph, uint8_t x, uint8_t y);

void drawMenue1();

void drawMenue2();

void drawPfeil(uint8_t x, uint8_t y);

void deletePfeil(uint8_t x, uint8_t y);

void drawLives(uint8_t live);

//void drawPlatform(int16_t x, int16_t y, uint8_t length);

//void reDrawPlatform(int16_t x, int16_t y, uint8_t length);

void reDrawPlatforms(int16_t offsetX, int16_t speed);

void drawPlatforms(int16_t offsetX);

void drawPowerUps(int16_t offsetX, int16_t speed);

void drawScore(uint32_t score);

#endif //ROBOTIK_DRAW_H
