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





struct pageToDraw drawingBuffer[DRAWING_BUFFER_SIZE];
struct pageToDraw eraseBuffer[DRAWING_BUFFER_SIZE];

struct pageToDraw *ptr; // = drawingBuffer;
struct pageToDraw *erasePtr; // = eraseBuffer;
/*
void flushDrawingBuffer();
void flushEraseBuffer();
void bufferInit();
void toDrawingBuffer(uint8_t x, uint8_t y, uint8_t h);
void drawFromBuffer();*/
void drawCorrect(int16_t x, int16_t y, uint8_t h);
void drawString(char text[],uint8_t x,uint8_t y);
uint8_t drawGlyph(char glyph, uint8_t x, uint8_t y);
//void combineCollidingPages();

#endif //ROBOTIK_DRAW_H
