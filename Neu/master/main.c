/* 
 *	Basis
 *	2009 Benjamin Reh und Joachim Schleicher
 */
#include <avr/io.h>
#include <inttypes.h>
#include <util/delay.h>
#include "uart.h"
#include "adc.h"
#include "timer.h"
#include "buttons.h"
#include "display.h"
#include <avr/interrupt.h>


#define DRAWING_BUFFER_SIZE 100

void init();

struct pageToDraw {
    uint8_t x;
    uint8_t y;
    uint8_t h;
};

volatile uint8_t pageCount = 0;

struct pageToDraw dummy = (struct pageToDraw) {255, 255, 255};

struct pageToDraw drawingBuffer[DRAWING_BUFFER_SIZE];
struct pageToDraw eraseBuffer[DRAWING_BUFFER_SIZE];

struct pageToDraw *ptr; // = drawingBuffer;
struct pageToDraw *erasePtr; // = eraseBuffer;

/*
 *  @param x and y where to draw the page
 *  @return void
 *
 *  This functions draws inside the lcd panel.
 *  Because if you draw outside of the pixel range
 *  the screen goes funky
 *
 */

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
        if (pageCount >= 101) {
            page(0, 0, 0xFF);
        }
    }
}


void drawFromBuffer() {

    erasePtr = eraseBuffer; //reset pointer
    for (int j = 0; j < DRAWING_BUFFER_SIZE; j++) {
        struct pageToDraw toErase = *erasePtr;
        if (toErase.x != 255) {
            page(toErase.x, toErase.y, 0);
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

volatile int16_t posY = 0;
volatile int16_t posX = 0;

volatile char buttonPressed = '0';
volatile uint32_t timePressed = 0;

void getInput() {
    if (buttonPressed == '0') {
        if (B_SELECT) {
            //uart_putc(20);
            buttonPressed = '1';
            timePressed = getMsTimer();
        }
        if (B_PAUSE) {

            //uart_putc(30);
            buttonPressed = '1';
            timePressed = getMsTimer();
        }
        if (B_UP) {
            //uart_putc(50);
            buttonPressed = '1';
            timePressed = getMsTimer();
            //if (posY > 0) {
            posY--;
            //}
        }
        if (B_DOWN) {
            //uart_putc(60);
            buttonPressed = '1';
            timePressed = getMsTimer();
            // if (posY < 100) {
            posY++;
            // }
        }
        if (B_RIGHT) {
            //uart_putc(70);
            buttonPressed = '1';
            timePressed = getMsTimer();
            // if (posX < 159) {
            posX++;
            //   }
        }
        if (B_LEFT) {
            //uart_putc(80);
            buttonPressed = '1';
            timePressed = getMsTimer();
            //if (posX > 0) {
            posX--;
            //}
        }

        if (B_A) {
            buttonPressed = '1';
            //uart_putc(90);
            timePressed = getMsTimer();
        }
        if (B_B) {
            buttonPressed = '1';
            //uart_putc(100);
            timePressed = getMsTimer();
        }
    }
}

void draw() {
    drawCorrect(posX, posY,0xC3);

    drawFromBuffer(); //HAS TO BE THE LAST CALL IN DRAW()!!!!!!!!
}


int main(void) {
    //Initialisierung ausfuehren

    init();

    uart_putc(80);
    _delay_ms(1000);

    uart_putc(10);
    _delay_ms(1000);

    posX = 40;
    posY = 40;


    while (1) {
/*
 * Set to approx 30 frames per second
 */
        if (getMsTimer() % 34 == 0) {
            getInput();
            draw();

        }
/*
 * Allow repress of buttons every 150 ms
 */
        if (timePressed + 150 <= getMsTimer()) {
            buttonPressed = '0';
        }
    }
}


//INIT
void init() {
    uartInit();   // serielle Ausgabe an PC
    ADCInit(0);   // Analoge Werte einlesen
    timerInit();  // "Systemzeit" initialisieren
    buttonsInit();
    displayInit();
    bufferInit();
}
