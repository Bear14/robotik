//
// Created by torben on 25/03/19.
//

#include "save.h"
#include <stdlib.h>
#include <avr/eeprom.h>


void writeScore(uint32_t score){

    eeprom_write_dword((uint32_t*)0x00,score);

}

uint32_t readScore(){

    return  eeprom_read_dword((uint32_t*)0x00);

}