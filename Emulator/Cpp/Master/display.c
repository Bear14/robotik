//#include <util/delay.h>
//#include <avr/io.h>
#include <inttypes.h>
#include "display.h"
#include "socket.cpp"
#include <stdlib.h>
#include <stdio.h>




#define DISPLAY_PORT 5005



void displayInit(void)
{
    /*
	DDRB |= (1<<5);//SCK
	DDRB |= (1<<3);//SDA
	DDRB |= (1<<4);//RST
	DDRB |= (1<<1);//CD
	DDRB |= (1<<0);//CS0
	PORTB |= (1<<4);//kein RST
	PORTB &= ~(1<<1);//CD auf low
	PORTB &= ~(1<<5);//SCK auf low
	PORTB |= (1<<0);_delay_us(10);PORTB &= ~(1<<0);//CS0 auf low
	sendbyte(241,0);
	sendbyte(103,0);
	sendbyte(198,0);//LCD mapping Hierum
	//~ sendbyte(192,0);//LCD mapping Hierum
	sendbyte(64,0);
	sendbyte(80,0);
	sendbyte(43,0);
	sendbyte(235,0);
	sendbyte(129,0);
	sendbyte(95,0);
	sendbyte(137,0);
	uint16_t i;
	for(i=0;i<4160;i++)//RAM-Aussp�hlen, alles wei�
	{
		sendbyte(0,1);
	}
	//~ DDRC |= 1;//Debug-LED
	sendbyte(0,0);//RAM-Zeigerpostition zur�ck auf 0/0
	sendbyte(16,0);
	sendbyte(96,0);
	sendbyte(175,0);//Bildschirm an
	//~ PORTC |= 1;//Debug-LED an==Init zu Ende*/
}

void clear(void)
{
    /*
	uint16_t i;
	sendbyte(0,0);//RAM-Zeigerpostition zur�ck auf 0/0
	sendbyte(16,0);
	sendbyte(96,0);
	for(i=0;i<4160;i++)//RAM-Aussp�hlen, alles wei�
	{
		sendbyte(0,1);
	}
	sendbyte(0,0);//RAM-Zeigerpostition zur�ck auf 0/0
	sendbyte(16,0);
	sendbyte(96,0);
     */
}

void sendbyte(uint8_t byte,uint8_t cd)
{
    /*
	int8_t i;
	if(cd)
		PORTB |= (1<<1);
	for(i=7;i>-1;i--)
	{
		PORTB &= ~(1<<5);
		if((1<<i)&byte)
			PORTB |= (1<<3);
		else
		{
			PORTB &= ~(1<<3);
		}
		PORTB |= (1<<5);
	}
	PORTB &= ~(1<<1);
     */
}

void page(uint8_t x,uint8_t y,uint8_t h)//alle Pixel einer Page beschreiben
{
    char buffer1[5];
    char buffer2[5];
    char buffer3[5];
    //itoa(i, buffer, 10);
    snprintf(buffer1,sizeof(buffer1),"%d",x);
    snprintf(buffer2, sizeof(buffer2),"%d",y);
    snprintf(buffer3, sizeof(buffer3),"%d",h);

    //char* _buffer1 = strcat(x,",");

    char* end = strcat(strcat(buffer1,","),strcat(strcat(buffer2,","),buffer3));//  + buffer3;
/*
    strcat(end,buffer1);
    strcat(end,buffer2);
    strcat(end,buffer3);
*/

    //printf("Out: %c",buffer);




    Sender(end,DISPLAY_PORT);

    /*
	sendbyte(15&x,0);//Adressentranslation
	sendbyte(16+(x>>4),0);
	sendbyte(96+y,0);
	sendbyte(h,1);
     */
}
