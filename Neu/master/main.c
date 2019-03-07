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


void init();

/*
void full(uint8_t x) {
	page(x,5,0xFF);
	page(x,5+1,0xFf);
	page(x+1,5,0xFF);
	page(x+1,5+1,0xFf);
}
void empty(uint8_t x) {
	page(x,5,0xF0);
	page(x,5+1,0xF0);
	page(x+1,5,0xF0);
	page(x+1,5+1,0xF0);
}

void batteryMeter() {
	uint8_t x=0; 
	uint16_t adc=getADCValue(0);
	uint16_t low=696;//778; // (1024.*34./50.);
	uint16_t high=962; //(1024.*47./50.);
	uint8_t bars = 50 *(adc-low)/(high-low);
	//~ bars=adc/20;
	for(x=0; x< 50; x++)
	{
		if (x < bars) {
			full (x*3);
		} else {
			empty(x*3);
		}
	}
	
}
*/
void pageTest() {

    for (int i = 0; i < 256; i++) {
        page(100, 10, i);

        page(102, 10, i);

        page(104, 10, i);

        page(106, 10, i);

    }
}

void drawRec(uint8_t x) {
    page(x, 13, 0xFF);
/*
    page(x + 1, 13, 0xFF);
    page(x + 2, 13, 0xFF);
    page(x + 3, 13, 0xFF);
*/

}

void eraseRec(uint8_t x) {
    page(x, 13, 0);

    page(x + 1, 13, 0);
    page(x + 2, 13, 0);
    page(x + 3, 13, 0);

}

/*
 *  @param x and y where to draw the page
 *  @return void
 *
 *  This functions draws inside the lcd panel.
 *  Because if you draw outside of the pixel range
 *  the screen goes funky
 *
 */


void drawCorrect(uint8_t x, uint8_t y) {

    if (x >= 0 && x <= 159 && y >= 0 && y <= 100) {

        uint8_t nex = y / 4;

        if (nex != 0) {
            page(x, nex - 1, 0);  // Display goes funky you write at a page with y == -1
        }
        page(x, nex, 0);
        page(x, nex + 1, 0);


        if (y % 4 == 0) {
            page(x, nex, 0xFF);
        }
        if (y % 4 == 1) {
            page(x, nex, 0xFC);
            page(x, nex + 1, 0x3);
        }
        if (y % 4 == 2) {
            page(x, nex, 0xF0);
            page(x, nex + 1, 0xF);
        }
        if (y % 4 == 3) {
            page(x, nex, 0xC0);
            page(x, nex + 1, 0x3F);
        }


    }
    else {

    }




}


volatile uint8_t nextPosY = 0;
volatile uint8_t nextPosX = 0;

volatile uint8_t posY = 0;
volatile uint8_t posX = 0;

volatile char buttonPressed = '0';
volatile int timePressed = 0;

void getInput() {
    if (buttonPressed == '0') {
        if (B_SELECT) {
            uart_putc(20);
            buttonPressed = '1';
            timePressed = getMsTimer();
        }
        if (B_PAUSE) {

            uart_putc(30);
            buttonPressed = '1';
            timePressed = getMsTimer();
        }
        if (B_UP) {
            uart_putc(50);
            buttonPressed = '1';
            timePressed = getMsTimer();
            if (posY > 0) {
                posY--;
            }
        }
        if (B_DOWN) {
            uart_putc(60);
            buttonPressed = '1';
            timePressed = getMsTimer();
            if (posY < 100) {
                posY++;
            }
        }
        if (B_RIGHT) {
            uart_putc(70);
            buttonPressed = '1';
            timePressed = getMsTimer();
           // if (posX < 159) {
                posX++;
         //   }
        }
        if (B_LEFT) {
            uart_putc(80);
            buttonPressed = '1';
            timePressed = getMsTimer();
            if (posX > 0) {
                posX--;
            }
        }

        if (B_A) {
            buttonPressed = '1';
            uart_putc(90);
            timePressed = getMsTimer();
        }
        if (B_B) {
            buttonPressed = '1';
            uart_putc(100);
            timePressed = getMsTimer();
        }
    }
}

void draw() {
    drawCorrect(posX, posY);
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

    posX = 52;
    posY = 52;

    drawCorrect(52, 100);
    while (1) {
        //batteryMeter();

        if (getMsTimer() % 34 == 0) {
            getInput();
            guard();
            getUpdate();
            draw();

        }
        if (timePressed + 150 == getMsTimer()) {
            buttonPressed = '0';
        }

/*  Find reason for random stop
 *  && collision with border
 *
 */
    }
}


//INIT
void init() {
    uartInit();   // serielle Ausgabe an PC
    ADCInit(0);   // Analoge Werte einlesen
    timerInit();  // "Systemzeit" initialisieren
    buttonsInit();
    displayInit();
}
