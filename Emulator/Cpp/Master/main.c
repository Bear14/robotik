/* 
 *	Basis
 *	2009 Benjamin Reh und Joachim Schleicher
 */
//#include <avr/io.h>
#include <inttypes.h>
//#include <util/delay.h>
#include "uart.c"
#include "adc.c"
//#include "timer.h"
#include "buttons.h"
#include "display.c"
#include <stdio.h>

#include "socket.cpp"

void _delay_ms(int ms){
	std::this_thread::sleep_for(std::chrono::milliseconds(ms));
}


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

void pageTest(){

    for(int i=0; i<256; ++i){
        page(100,10,i);

        page(102,10,i);

        page(104,10,i);

        page(106,10,i);
        _delay_ms(200);

    }

}
uint8_t playerPos = 23;
uint8_t lastPlayerPos = 0;

void drawPlayer(uint8_t pos) {

	page(5, pos, 0xFF);
	page(6, pos, 0xFF);
	page(7, pos, 0xFF);
	page(8, pos, 0xFF);
}

void removePlayer(uint8_t pos) {
	page(5, pos, 0);
	page(6, pos, 0);
	page(7, pos, 0);
	page(8, pos, 0);
}


void draw() {
	if (lastPlayerPos != playerPos) {
		removePlayer(lastPlayerPos);
		drawPlayer(playerPos);
	}
}

void run() {

}

void getInput() {
	if (B_SELECT) {
		//uart_putc(20);
	}
	if (B_PAUSE) {
		//uart_putc(30);
	}
	if (B_UP) {
		//uart_putc(50);
		lastPlayerPos = playerPos;
		playerPos = lastPlayerPos + 1;
	}
	if (B_DOWN) {
		lastPlayerPos = playerPos;
		playerPos = lastPlayerPos + 1;
		//uart_putc(60);
	}
	if (B_RIGHT) {
		//uart_putc(70);
	}
	if (B_LEFT) {

		//uart_putc(80);
	}
	if (B_A) {
		//page(50, 15, 255);
		// drawPlayer(23);
		lastPlayerPos = playerPos;
		playerPos = 10;
	}
	//uart_putc(90);
	if (B_B) {
		// removePlayer(23);
		//page(50, 15, 0);
		lastPlayerPos = playerPos;
		playerPos = 23;
	}
	//uart_putc(100);

}


int main(void) {
	//Initialisierung ausfuehren

	//init();


	uart_putc(80);
	_delay_ms(1000);

	uart_putc(10);
	_delay_ms(1000);


	while (1) {
		//batteryMeter();
		//pageTest();
		draw();
		getInput();

	}
}


//INIT
void init()
{

	uartInit();   // serielle Ausgabe an PC
	ADCInit(0);   // Analoge Werte einlesen
	//timerInit();  // "Systemzeit" initialisieren
	buttonsInit();
	displayInit();

}
