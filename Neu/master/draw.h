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



/*
void flushDrawingBuffer();
void flushEraseBuffer();
void bufferInit();
void toDrawingBuffer(uint8_t x, uint8_t y, uint8_t h);
void drawFromBuffer();*/
void drawCorrect(int16_t x, int16_t y, uint8_t h);
void drawString(char text[],uint8_t x,uint8_t y);
uint8_t nextGlyph(char glyph, uint8_t x, uint8_t y);
void drawGlyph(char glyph, uint8_t x, uint8_t y);
void drawPfeil(uint8_t x, uint8_t y);
void drawLives(uint8_t live);
#endif //ROBOTIK_DRAW_H
