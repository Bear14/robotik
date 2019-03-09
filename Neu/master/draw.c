//
// Created by torben on 07/03/19.
//
#include <inttypes.h>
#include "display.h"
#include "draw.h"

/*
 *  @param x and y where to draw the page
 *  @return void
 *
 *  This functions draws inside the lcd panel.
 *  Because if you draw outside of the pixel range
 *  the screen goes funky
 *
 */

/*
 * TODO: make function hat checks if page would be redrawn and if so dont delete it and dont draw again
 */
/*
typedef int bool;
#define true 1
#define false 0
*/


struct pageToDraw dummy = (struct pageToDraw) {255, 255, 255};
volatile uint8_t pageCount = 0;

void flushDrawingBuffer() {
    // Set pointer to DrawingBuffer[0]
    ptr = drawingBuffer;

    // Fill array with dummy elements
    for (int i = 0; i < DRAWING_BUFFER_SIZE; i++) {
        *ptr = dummy;
        ptr++;


    }
    // Reset pointer to beginning of array
    ptr = drawingBuffer;
}

void flushEraseBuffer() {
    // Set pointer to DrawingBuffer[0]

    erasePtr = eraseBuffer;
    // Fill array with dummy elements
    for (int i = 0; i < DRAWING_BUFFER_SIZE; i++) {

        *erasePtr = dummy;
        ptr++;


    }
    // Reset pointer to beginning of array
    erasePtr = eraseBuffer;
}


void bufferInit() {
    // Set pointer to DrawingBuffer[0]
    ptr = drawingBuffer;
    erasePtr = eraseBuffer;
    // Fill array with dummy elements
    for (int i = 0; i < DRAWING_BUFFER_SIZE; i++) {
        *ptr = dummy;
        *erasePtr = dummy;
        ptr++;
        erasePtr++;

    }
    // Reset pointer to beginning of array
    ptr = drawingBuffer;
    erasePtr = eraseBuffer;
}

void toDrawingBuffer(uint8_t x, uint8_t y, uint8_t h) {
    if (x >= 0 && x <= 159 && y >= 0 && y <= 100) {
        *ptr = (struct pageToDraw) {x, y, h};
        ptr++;
        pageCount++;
        if (pageCount >= DRAWING_BUFFER_SIZE +1) {
            page(0, 0, 0xFF);
        }
    }
}

/*
bool inDrawBuffer(struct pageToDraw check){
    ptr = drawingBuffer;

    for(int i = 0; i < DRAWING_BUFFER_SIZE; i++){

        if(check.x == ptr->x && check.y == ptr->y && check.h == ptr->h){
            return true;
        }
        ptr++;

    }
    ptr = drawingBuffer;

    return false;
}
*/
void drawFromBuffer() {

    erasePtr = eraseBuffer; //reset pointer
    for (int j = 0; j < DRAWING_BUFFER_SIZE; j++) {
        struct pageToDraw toErase = *erasePtr;
        if (toErase.x != 255) {

            //if(!(inDrawBuffer(toErase))){

                page(toErase.x, toErase.y, 0);
          //  }

            erasePtr++;
        } else {
            j = DRAWING_BUFFER_SIZE;
        }


    }
    erasePtr = eraseBuffer; //reset pointer
    flushEraseBuffer();


    ptr = drawingBuffer; //reset pointer
    for (int i = 0; i < DRAWING_BUFFER_SIZE; i++) {
        struct pageToDraw toDraw = *ptr;

        if (toDraw.x != 255) {
            page(toDraw.x, toDraw.y, toDraw.h);
            *erasePtr = toDraw;
            erasePtr++;
            ptr++;
        } else {
            i = DRAWING_BUFFER_SIZE; //
        }
    }
    ptr = drawingBuffer; //reset pointer
    erasePtr = eraseBuffer;

    flushDrawingBuffer();
    pageCount = 0;

}
/*
 * Known bug: It is not possible to draw half pages at y = 0.
 *
 *
 */
void drawCorrect(int16_t x, int16_t y, uint8_t h) {

    if (x >= 0 && x <= 159 && y >= 0 && y <= 104) {
        int16_t nex = y / 4;

        if (y % 4 == 0) {
            toDrawingBuffer(x, nex, h);
        }
        if (y % 4 == 1) {
            uint16_t hex = h << 2;
            uint16_t del = 65280;

            uint8_t page_2 = hex >> 8;



            uint8_t page_1 = hex;
            page_1 &= ~(del);

            toDrawingBuffer(x, nex, page_1);
            toDrawingBuffer(x, nex + 1, page_2);
        }
        if (y % 4 == 2) {
            uint16_t hex = h << 4;
            uint16_t del = 65280;

            uint8_t page_2 = hex >> 8;



            uint8_t page_1 = hex;
            page_1 &= ~(del);

            toDrawingBuffer(x, nex, page_1);
            toDrawingBuffer(x, nex + 1, page_2);
        }
        if (y % 4 == 3) {
            uint16_t hex = h << 6;
            uint16_t del = 65280;

            uint8_t page_2 = hex >> 8;



            uint8_t page_1 = hex;
            page_1 &= ~(del);

            toDrawingBuffer(x, nex, page_1);
            toDrawingBuffer(x, nex + 1, page_2);
        }
    }
}

void combineCollidingPages() {
    struct pageToDraw *pivotPtr;
    struct pageToDraw *searchPtr;

    pivotPtr = drawingBuffer;
    searchPtr = pivotPtr +1;

    for (int i = 0; i < DRAWING_BUFFER_SIZE; i++) {

        struct pageToDraw pivot = *pivotPtr;
        if (pivot.x != 255) {

            for (int j = i; j < DRAWING_BUFFER_SIZE; j++) {

                struct pageToDraw compare = *searchPtr;


                if (compare.x != 255) {

                    if (pivot.x == compare.x && pivot.y == compare.y) {



                        uint8_t newPage = pivot.h;
                        newPage |= compare.h;

                        struct pageToDraw dummy = (struct pageToDraw) {
                                pivot.x, pivot.y, newPage
                        };
                        *pivotPtr = dummy;
                        *searchPtr = dummy;
                        pivot = *pivotPtr;

                    }


                    searchPtr++;
                } else {
                    j = DRAWING_BUFFER_SIZE;
                }

            }

            pivotPtr++;
            searchPtr = pivotPtr + 1;
        } else {
            i = DRAWING_BUFFER_SIZE;
        }

    }
    pivotPtr = drawingBuffer;

}