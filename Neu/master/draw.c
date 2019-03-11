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

typedef int bool;
#define true 1
#define false 0


void bufferInit() {
    // Set pointer to DrawingBuffer[0]


    struct pageToDraw *dPointer = drawingBuffer;
    struct pageToDraw *ePointer = eraseBuffer;

    for (int i = 0; i < DRAWING_BUFFER_SIZE; i++) {
        *dPointer = (struct pageToDraw) {255, 255, 255};
        *ePointer = (struct pageToDraw) {255, 255, 255};
        dPointer++;
        ePointer++;

    }

}

void flushBuffer(char which) {

    struct pageToDraw *pointer = 0;
    if (which == 'd') {
        pointer = drawingBuffer;
    } else if (which == 'e') {
        pointer = eraseBuffer;
    }

    for (int i = 0; i < DRAWING_BUFFER_SIZE; i++) {
        *pointer = (struct pageToDraw) {255, 255, 255};
        pointer++;
    }


}


bool pageInBuffer(struct pageToDraw page, char which) {
    struct pageToDraw *pointer;
    if (which == 'd') {
        pointer = drawingBuffer;
    } else if (which == 'e') {
        pointer = eraseBuffer;
    } else {
        return 0;
    }

    for (int i = 0; i < DRAWING_BUFFER_SIZE; i++) {
        if (page.x == pointer->x && page.y == pointer->y && page.h == pointer->h) {
            return true;
        }
        if (pointer->x == 255) {

            i = DRAWING_BUFFER_SIZE;
        }
        pointer++;

    }
    return 0;

}

void deletePageFromBuffer(struct pageToDraw page, char which) {
    struct pageToDraw *pointer = 0;
    if (which == 'd') {
        pointer = drawingBuffer;
    } else if (which == 'e') {
        pointer = eraseBuffer;
    }

    for (int i = 0; i < DRAWING_BUFFER_SIZE; i++) {
        if (page.x == pointer->x && page.y == pointer->y && page.h == pointer->h) {
            *pointer = (struct pageToDraw) {200, 200, 200};
        }
        if (pointer->x == 255) {

            i = DRAWING_BUFFER_SIZE;
        }
        pointer++;

    }

}

void addPageToBuffer(struct pageToDraw page, char which) {

    // page fitting on screen

    if (page.x >= 0 && page.x <= 159 && page.y >= 0 && page.y <= 100) {


        //page not already in buffer
        if (!(pageInBuffer(page, which))) {

            struct pageToDraw *pointer = 0;
            if (which == 'd') {
                pointer = drawingBuffer;
            } else if (which == 'e') {
                pointer = eraseBuffer;
            }

            /*
             * No redrawing
             */
            if (pageInBuffer(page, 'e')) {

                deletePageFromBuffer(page, 'e');


            } else {


                for (int i = 0; i < DRAWING_BUFFER_SIZE; i++) {
                    if (pointer->x == 255 || pointer->x == 200) {

                        *pointer = page;
                        i = DRAWING_BUFFER_SIZE;
                    }

                    pointer++;
                }

            }
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


    struct pageToDraw *ePointer = eraseBuffer;


    for (int e = 0; e < DRAWING_BUFFER_SIZE; e++) {

        //skip empty
        if (ePointer->x != 255 && ePointer->x != 200) {

            page(ePointer->x, ePointer->y, 0);
            ePointer++;

        } else if (ePointer->x == 200) {
            ePointer++;
        } else {
            e = DRAWING_BUFFER_SIZE;
        }


    }

    flushBuffer('e');


    struct pageToDraw *dPointer = drawingBuffer;
    ePointer = eraseBuffer;

    for (int d = 0; d < DRAWING_BUFFER_SIZE; d++) {

        if (dPointer->x != 255 && dPointer->x != 200) {

            page(dPointer->x, dPointer->y, dPointer->h);
            *ePointer = (struct pageToDraw) {dPointer->x, dPointer->y, dPointer->h};
            dPointer++;
            ePointer++;

        } else if (dPointer->x == 200) {
            dPointer++;
        } else {
            d = DRAWING_BUFFER_SIZE;
        }


    }

    flushBuffer('d');


}

/*
 * Known bug: It is not possible to draw half pages at y = 0.
 *
 *
 */
void drawCorrect_old(int16_t x, int16_t y, uint8_t h) {

    if (x >= 0 && x <= 159 && y >= 0 && y <= 104) {
        int16_t nex = y / 4;

        if (y % 4 == 0) {
            addPageToBuffer((struct pageToDraw) {x, nex, h}, 'd');
        }
        if (y % 4 == 1) {
            uint16_t hex = h << 2;
            uint16_t del = 65280;

            uint8_t page_2 = hex >> 8;


            uint8_t page_1 = hex;
            page_1 &= ~(del);

            addPageToBuffer((struct pageToDraw) {x, nex, page_1}, 'd');
            addPageToBuffer((struct pageToDraw) {x, nex + 1, page_2}, 'd');
        }
        if (y % 4 == 2) {
            uint16_t hex = h << 4;
            uint16_t del = 65280;

            uint8_t page_2 = hex >> 8;


            uint8_t page_1 = hex;
            page_1 &= ~(del);

            addPageToBuffer((struct pageToDraw) {x, nex, page_1}, 'd');
            addPageToBuffer((struct pageToDraw) {x, nex + 1, page_2}, 'd');
        }
        if (y % 4 == 3) {
            uint16_t hex = h << 6;
            uint16_t del = 65280;

            uint8_t page_2 = hex >> 8;


            uint8_t page_1 = hex;
            page_1 &= ~(del);

            addPageToBuffer((struct pageToDraw) {x, nex, page_1}, 'd');
            addPageToBuffer((struct pageToDraw) {x, nex + 1, page_2}, 'd');
        }
    }
}

struct pageToDraw old = (struct pageToDraw) {0,0,0};
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

            if (x == old.x && nex == old.y){
              page_1 = old.h | page_1;
            }
            page(x, nex, page_1);

            old =(struct pageToDraw) {x, nex, page_1};

            if (x == old.x && nex+1 == old.y){
              page_2 = old.h | page_2;
            }
            page(x, nex + 1, page_2);

            old =(struct pageToDraw) {x, nex+1, page_2};

        }
        if (y % 4 == 2) {
            uint16_t hex = h << 4;
            uint16_t del = 65280;

            uint8_t page_2 = hex >> 8;
            uint8_t page_1 = hex;
            page_1 &= ~(del);

            if (x == old.x && nex == old.y){
              page_1 = old.h | page_1;
            }
            page(x, nex, page_1);

            old =(struct pageToDraw) {x, nex, page_1};

            if (x == old.x && nex+1 == old.y){
              page_2 = old.h | page_2;
            }
            page(x, nex + 1, page_2);

            old =(struct pageToDraw) {x, nex+1, page_2};

        }
        if (y % 4 == 3) {
            uint16_t hex = h << 6;
            uint16_t del = 65280;

            uint8_t page_2 = hex >> 8;


            uint8_t page_1 = hex;
            page_1 &= ~(del);

            if (x == old.x && nex == old.y){
              page_1 = old.h | page_1;
            }
            page(x, nex, page_1);

            old =(struct pageToDraw) {x, nex, page_1};

            if (x == old.x && nex+1 == old.y){
              page_2 = old.h | page_2;
            }
            page(x, nex + 1, page_2);

            old =(struct pageToDraw) {x, nex+1, page_2};
        }
    }
}

void combineCollidingPages() {
    struct pageToDraw *pivotPtr;
    struct pageToDraw *searchPtr;

    pivotPtr = drawingBuffer;
    searchPtr = pivotPtr + 1;

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
                        *searchPtr = (struct pageToDraw) {200, 200, 200};
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
