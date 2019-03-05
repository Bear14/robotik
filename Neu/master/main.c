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

volatile int count = 0;

//enum pressedButton {select,pause,up,down,right,left,a,b};
char buttonPressed = '0';

void getInput() {
    if (buttonPressed == '0') {
        if (B_SELECT) {
            uart_putc(20);
            buttonPressed = '1';
        }
        if (B_PAUSE) {

            uart_putc(30);
            buttonPressed = '1';
        }
        if (B_UP) {
            uart_putc(50);
            buttonPressed = '1';
        }
        if (B_DOWN) {
            uart_putc(60);
            buttonPressed = '1';
        }
        if (B_RIGHT) {
            uart_putc(70);
            buttonPressed = '1';
        }
        if (B_LEFT) {
            uart_putc(80);
            buttonPressed = '1';
        }

        if (B_A) {
            count--;
            buttonPressed = '1';
            uart_putc(90);
        }
        if (B_B) {
            count++;
            buttonPressed = '1';
            uart_putc(100);
        }
    }
}

void draw() {
    drawRec(count);
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

    count = 50;

    while (1) {
        //batteryMeter();

        if (getMsTimer() % 34 == 0) {
            getInput();
            getUpdate();
            draw();

        }
        if (getMsTimer() % 100 == 0) {
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
}
