#ifndef BUTTONS_H
#define BUTTONS_H
inline void buttonsInit() {
	/*
	DDRD &=~( (1<<2) | (1<<3) | (1<<4) | (1<<5) | (1<<6) | (1<<7)); 
	PORTD |=( (1<<2) | (1<<3) | (1<<4) | (1<<5) | (1<<6) | (1<<7)); 

	DDRC &= ~( (1<<4) | (1<<5));
	PORTC |= ( (1<<4) | (1<<5));*/
}

#define B_UP "D2"//(!(PIND & (1<<2)))
#define B_DOWN "D3"//(!(PIND & (1<<3)))
#define B_LEFT "D4"//(!(PIND & (1<<4)))
#define B_RIGHT "D5"//(!(PIND & (1<<5)))
#define B_A "D6"//(!(PIND & (1<<6)))
#define B_B "D7"//(!(PIND & (1<<7)))

#define B_PAUSE "C4"//(!(PINC & (1<<4)))
#define B_SELECT "C5"//(!(PINC & (1<<5)))



#endif
