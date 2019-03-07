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

struct pageToDraw *ptr; // = drawingBuffer;

/*
 *  @param x and y where to draw the page
 *  @return void
 *
 *  This functions draws inside the lcd panel.
 *  Because if you draw outside of the pixel range
 *  the screen goes funky
 *
 */

void bufferInit() {
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

void toDrawingBuffer(uint8_t x, uint8_t y, uint8_t h) {
    if (x >= 0 && x <= 159 && y >= 0 && y <= 100) {
        *ptr = (struct pageToDraw) {x, y, h};
        ptr++;
        pageCount++;
        if(pageCount >= 101){
            page(0,0,0xFF);
        }
    }
}


void drawFromBuffer(){
    ptr = drawingBuffer;

    for(int i = 0; i < DRAWING_BUFFER_SIZE; i++){
        struct pageToDraw toDraw = *ptr;

        if(toDraw.x != 255){
            page(toDraw.x,toDraw.y,toDraw.h);
            ptr++;
        } else{
            i = DRAWING_BUFFER_SIZE;
        }
    }
    ptr = drawingBuffer;

    bufferInit();
    pageCount = 0;

}

void drawCorrect(uint8_t x, uint8_t y) {


    if (x >= 0 && x <= 159 && y >= 0 && y <= 100) {

        uint8_t nex = y / 4;

        // Remove

        if (nex != 0) {
            toDrawingBuffer(x, nex - 1, 0);
        }
        toDrawingBuffer(x, nex, 0);
        toDrawingBuffer(x, nex + 1, 0);


        // Draw

        if (y % 4 == 0) {
            if (nex != 0) {
                toDrawingBuffer(x, nex - 1, 0x0);
            }
            toDrawingBuffer(x, nex, 0xFF);
            toDrawingBuffer(x, nex + 1, 0x0);
        }
        if (y % 4 == 1) {
            toDrawingBuffer(x, nex, 0xFC);
            toDrawingBuffer(x, nex + 1, 0x3);
        }
        if (y % 4 == 2) {
            toDrawingBuffer(x, nex, 0xF0);
            toDrawingBuffer(x, nex + 1, 0xF);
        }
        if (y % 4 == 3) {
            toDrawingBuffer(x, nex, 0xC0);
            toDrawingBuffer(x, nex + 1, 0x3F);
        }
    }


}

volatile uint8_t posY = 0;
volatile uint8_t posX = 0;

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

    drawCorrect(posX, posY);
    drawFromBuffer();
}

void guard() {
}

void getUpdate() {


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

        if (getMsTimer() % 34 == 0) {
            getInput();
            guard();
            getUpdate();
            draw();

        }
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
