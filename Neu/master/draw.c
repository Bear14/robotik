//
// Created by torben on 07/03/19.
//
#include <inttypes.h>
#include "display.h"
#include "draw.h"
#include "sprites.h"

void drawString(char text[],uint8_t x,uint8_t y){
  char *pointer =text;
  uint8_t nex_x = 0, nex_y=0;

  for (; *pointer != '\0' ; pointer++){
    if (nex_x+x >=155){ // wenn der Dildrand überläufen würde
      drawGlyph('-', x+nex_x, y+nex_y);
      nex_y += 9;
      nex_x = 0;
    }
    drawGlyph(*pointer, x+nex_x, y+nex_y);
    nex_x += nextGlyph(*pointer, x+nex_x, y+nex_y)+1;
  }
}

uint8_t nextGlyph(char glyph, uint8_t x, uint8_t y){
  uint8_t glyph_ende = 0;

  switch (glyph) {
    case '0': glyph_ende =4; break;
    case '1': glyph_ende =3; break;
    case '2': glyph_ende =4; break;
    case '3': glyph_ende =4; break;
    case '4': glyph_ende =4; break;
    case '5': glyph_ende =4; break;
    case '6': glyph_ende =4; break;
    case '7': glyph_ende =4; break;
    case '8': glyph_ende =4; break;
    case '9': glyph_ende =4; break;
    case 'A': glyph_ende =5; break;
    case 'B': glyph_ende =5; break;
    case 'C': glyph_ende =5; break;
    case 'D': glyph_ende =5; break;
    case 'E': glyph_ende =5; break;
    case 'F': glyph_ende =5; break;
    case 'G': glyph_ende =5; break;
    case 'H': glyph_ende =5; break;
    case 'I': glyph_ende =3; break;
    case 'J': glyph_ende =4; break;
    case 'K': glyph_ende =5; break;
    case 'L': glyph_ende =5; break;
    case 'M': glyph_ende =5; break;
    case 'N': glyph_ende =5; break;
    case 'O': glyph_ende =5; break;
    case 'P': glyph_ende =5; break;
    case 'R': glyph_ende =5; break;
    case 'Q': glyph_ende =5; break;
    case 'S': glyph_ende =5; break;
    case 'T': glyph_ende =5; break;
    case 'U': glyph_ende =5; break;
    case 'W': glyph_ende =5; break;
    case 'X': glyph_ende =5; break;
    case 'Y': glyph_ende =5; break;
    case 'Z': glyph_ende =5; break;
    case ' ': glyph_ende =3; break;
    case '-': glyph_ende =3; break;
    default:  break;
  }
  return glyph_ende;
}
void drawGlyph(char glyph, uint8_t x, uint8_t y){
  switch (glyph) {
    case '0':  drawCorrect(x+0,y+0,0xF0);drawCorrect(x+0,y+4,0x3F);drawCorrect(x+1,y+0,0x0C);drawCorrect(x+1,y+4,0xCC);drawCorrect(x+2,y+0,0x0C);drawCorrect(x+2,y+4,0xC3);drawCorrect(x+3,y+0,0xF0);drawCorrect(x+3,y+4,0x3F);  break;
    case '1':  drawCorrect(x+0,y+0,0x30);drawCorrect(x+0,y+4,0xC0);drawCorrect(x+1,y+0,0xFC);drawCorrect(x+1,y+4,0xFF);drawCorrect(x+2,y+0,0x00);drawCorrect(x+2,x+4,0xC0);  break;
    case '2':  drawCorrect(x+0,y+0,0x30);drawCorrect(x+0,y+4,0xF0);drawCorrect(x+1,y+0,0x0C);drawCorrect(x+1,y+4,0xCC);drawCorrect(x+2,y+0,0x0C);drawCorrect(x+2,y+4,0xC3);drawCorrect(x+3,y+0,0xF0);drawCorrect(x+3,y+4,0xC0);  break;
    case '3':  drawCorrect(x+0,y+0,0x30);drawCorrect(x+0,y+4,0x30);drawCorrect(x+1,y+0,0x0C);drawCorrect(x+1,y+4,0xC0);drawCorrect(x+2,y+0,0x0C);drawCorrect(x+2,y+4,0xC3);drawCorrect(x+3,y+0,0xF0);drawCorrect(x+3,y+4,0x3C);  break;
    case '4':  drawCorrect(x+0,y+0,0xC0);drawCorrect(x+0,y+4,0x0F);drawCorrect(x+1,y+0,0x30);drawCorrect(x+1,y+4,0x0C);drawCorrect(x+2,y+0,0xFC);drawCorrect(x+2,y+4,0xFF);drawCorrect(x+3,y+4,0x0C);  break;
    case '5':  drawCorrect(x+0,y+0,0xFC);drawCorrect(x+0,y+4,0xC3);drawCorrect(x+1,y+0,0x0C);drawCorrect(x+1,y+4,0xC3);drawCorrect(x+2,y+0,0x0C);drawCorrect(x+2,y+4,0xC3);drawCorrect(x+3,y+0,0x0C);drawCorrect(x+3,y+4,0xFF);  break;
    case '6':  drawCorrect(x+0,y+0,0xC0);drawCorrect(x+0,y+4,0x3F);drawCorrect(x+1,y+0,0x30);drawCorrect(x+1,y+4,0xC3);drawCorrect(x+2,y+0,0x0C);drawCorrect(x+2,y+4,0xC3);drawCorrect(x+3,y+0,0x0C);drawCorrect(x+3,y+4,0x3C);  break;
    case '7':  drawCorrect(x+0,y+0,0x3C);drawCorrect(x+1,y+0,0x0C);drawCorrect(x+1,y+4,0xFC);drawCorrect(x+2,y+0,0x0C);drawCorrect(x+2,y+4,0x03);drawCorrect(x+3,y+0,0xFC);  break;
    case '8':  drawCorrect(x+0,y+0,0xF0);drawCorrect(x+0,y+4,0x3C);drawCorrect(x+1,y+0,0x0C);drawCorrect(x+1,y+4,0xC3);drawCorrect(x+2,y+0,0x0C);drawCorrect(x+2,y+4,0xC3);drawCorrect(x+3,y+0,0xF0);drawCorrect(x+3,y+4,0x3C);  break;
    case '9':  drawCorrect(x+0,y+0,0xF0);drawCorrect(x+1,y+0,0x0C);drawCorrect(x+1,y+4,0xC3);drawCorrect(x+2,y+0,0x0C);drawCorrect(x+2,y+4,0xC3);drawCorrect(x+3,y+0,0xF0);drawCorrect(x+3,y+4,0x3F);  break;
    case 'A':  drawCorrect(x+0,y+0,0xF0);drawCorrect(x+0,y+4,0xFF);drawCorrect(x+1,y+0,0x0C);drawCorrect(x+1,y+4,0x03);drawCorrect(x+2,y+0,0x0C);drawCorrect(x+2,y+4,0x03);drawCorrect(x+3,y+0,0x0C);drawCorrect(x+3,y+4,0x03);drawCorrect(x+4,y+0,0xF0);drawCorrect(x+4,y+4,0xFF);  break;
    case 'B':  drawCorrect(x+0,y+0,0xFC);drawCorrect(x+0,y+4,0xFF);drawCorrect(x+1,y+0,0x0C);drawCorrect(x+1,y+4,0xC3);drawCorrect(x+2,y+0,0x0C);drawCorrect(x+2,y+4,0xC3);drawCorrect(x+3,y+0,0x0C);drawCorrect(x+3,y+4,0xC3);drawCorrect(x+4,y+0,0xF0);drawCorrect(x+4,y+4,0x3C);  break;
    case 'C':  drawCorrect(x+0,y+0,0xF0);drawCorrect(x+0,y+4,0x3F);drawCorrect(x+1,y+0,0x0C);drawCorrect(x+1,y+4,0xC0);drawCorrect(x+2,y+0,0x0C);drawCorrect(x+2,y+4,0xC0);drawCorrect(x+3,y+0,0x0C);drawCorrect(x+3,y+4,0xC0);drawCorrect(x+4,y+0,0x30);drawCorrect(x+4,y+4,0x30);  break;
    case 'D':  drawCorrect(x+0,y+0,0xFC);drawCorrect(x+0,y+4,0xFF);drawCorrect(x+1,y+0,0x0C);drawCorrect(x+1,y+4,0xC0);drawCorrect(x+2,y+0,0x0C);drawCorrect(x+2,y+4,0xC0);drawCorrect(x+3,y+0,0x0C);drawCorrect(x+3,y+4,0xC0);drawCorrect(x+4,y+0,0xF0);drawCorrect(x+4,y+4,0x3F);  break;
    case 'E':  drawCorrect(x+0,y+0,0xFC);drawCorrect(x+0,y+4,0xFF);drawCorrect(x+1,y+0,0x0C);drawCorrect(x+1,y+4,0xC3);drawCorrect(x+2,y+0,0x0C);drawCorrect(x+2,y+4,0xC3);drawCorrect(x+3,y+0,0x0C);drawCorrect(x+3,y+4,0xC3);drawCorrect(x+4,y+0,0x0C);drawCorrect(x+4,y+4,0xC0);  break;
    case 'F':  drawCorrect(x+0,y+0,0xFC);drawCorrect(x+0,y+4,0xFF);drawCorrect(x+1,y+0,0x0C);drawCorrect(x+1,y+4,0x03);drawCorrect(x+2,y+0,0x0C);drawCorrect(x+2,y+4,0x03);drawCorrect(x+3,y+0,0x0C);drawCorrect(x+3,y+4,0x03);drawCorrect(x+4,y+0,0x0C);  break;
    case 'G':  drawCorrect(x+0,y+0,0xF0);drawCorrect(x+0,y+4,0x3F);drawCorrect(x+1,y+0,0x0C);drawCorrect(x+1,y+4,0xC0);drawCorrect(x+2,y+0,0x0C);drawCorrect(x+2,y+4,0xC3);drawCorrect(x+3,y+0,0x0C);drawCorrect(x+3,y+4,0xC3);drawCorrect(x+4,y+0,0x30);drawCorrect(x+4,y+4,0x3C);  break;
    case 'H':  drawCorrect(x+0,y+0,0xFC);drawCorrect(x+0,y+4,0xFF);drawCorrect(x+1,y+4,0x03);drawCorrect(x+2,y+4,0x03);drawCorrect(x+3,y+4,0x03);drawCorrect(x+4,y+0,0xFC);drawCorrect(x+4,y+4,0xFF);  break;
    case 'I':  drawCorrect(x+0,y+0,0x0C);drawCorrect(x+0,y+4,0xC0);drawCorrect(x+1,y+0,0xFC);drawCorrect(x+1,y+4,0xFF);drawCorrect(x+2,y+0,0x0C);drawCorrect(x+2,y+4,0xC0);  break;
    case 'J':  drawCorrect(x+0,y+0,0x0C);drawCorrect(x+0,y+4,0x30);drawCorrect(x+1,y+0,0x0C);drawCorrect(x+1,y+4,0xC0);drawCorrect(x+2,y+0,0x0C);drawCorrect(x+2,y+4,0xC0);drawCorrect(x+3,y+0,0xFC);drawCorrect(x+3,y+4,0x3F);  break;
    case 'K':  drawCorrect(x+0,y+0,0xFC);drawCorrect(x+0,y+4,0xFF);drawCorrect(x+1,y+0,0x03);drawCorrect(x+1,y+4,0x03);drawCorrect(x+2,y+0,0xC0);drawCorrect(x+2,y+4,0x0C);drawCorrect(x+3,y+0,0x3C);drawCorrect(x+3,y+4,0xF0);  break;
    case 'L':  drawCorrect(x+0,y+0,0xFC);drawCorrect(x+0,y+4,0xFF);drawCorrect(x+1,y+4,0xC0);drawCorrect(x+2,y+4,0xC0);drawCorrect(x+3,y+4,0xC0);drawCorrect(x+4,y+4,0xC0);  break;
    case 'M':  drawCorrect(x+0,y+0,0xFC);drawCorrect(x+0,y+4,0xFF);drawCorrect(x+1,y+0,0x30);drawCorrect(x+2,y+0,0xC0);drawCorrect(x+3,y+0,0x30);drawCorrect(x+4,y+0,0xFC);drawCorrect(x+4,y+4,0xFF);  break;
    case 'N':  drawCorrect(x+0,y+0,0xFC);drawCorrect(x+0,y+4,0xFF);drawCorrect(x+1,y+0,0x30);drawCorrect(x+2,y+0,0xC0);drawCorrect(x+3,y+4,0x03);drawCorrect(x+4,y+0,0xFC);drawCorrect(x+4,y+4,0xFF);  break;
    case 'O':  drawCorrect(x+0,y+0,0xF0);drawCorrect(x+0,y+4,0x3F);drawCorrect(x+1,y+0,0x0C);drawCorrect(x+1,y+4,0xC0);drawCorrect(x+2,y+0,0x0C);drawCorrect(x+2,y+4,0xC0);drawCorrect(x+3,y+0,0x0C);drawCorrect(x+3,y+4,0xC0);drawCorrect(x+4,y+0,0xF0);drawCorrect(x+4,y+4,0x3F);  break;
    case 'P':  drawCorrect(x+0,y+0,0xFC);drawCorrect(x+0,y+4,0xFF);drawCorrect(x+1,y+0,0x0C);drawCorrect(x+1,y+4,0x03);drawCorrect(x+2,y+0,0x0C);drawCorrect(x+2,y+4,0x03);drawCorrect(x+3,y+0,0x0C);drawCorrect(x+3,y+4,0x03);drawCorrect(x+4,y+0,0xF0);  break;
    case 'Q':  drawCorrect(x+0,y+0,0xF0);drawCorrect(x+0,y+4,0x3F);drawCorrect(x+1,y+0,0x0C);drawCorrect(x+1,y+4,0xC0);drawCorrect(x+2,y+0,0x0C);drawCorrect(x+2,y+4,0xCC);drawCorrect(x+3,y+0,0x0C);drawCorrect(x+3,y+4,0x30);drawCorrect(x+4,y+0,0xF0);drawCorrect(x+4,y+4,0xCF);  break;
    case 'R':  drawCorrect(x+0,y+0,0xF0);drawCorrect(x+0,y+4,0xFF);drawCorrect(x+1,y+0,0x0C);drawCorrect(x+1,y+4,0x03);drawCorrect(x+2,y+0,0x0C);drawCorrect(x+2,y+4,0x0F);drawCorrect(x+3,y+0,0x0C);drawCorrect(x+3,y+4,0x33);drawCorrect(x+4,y+0,0xF0);drawCorrect(x+4,y+4,0xC0);  break;
    case 'S':  drawCorrect(x+0,y+0,0xF0);drawCorrect(x+0,y+4,0xC0);drawCorrect(x+1,y+0,0x0C);drawCorrect(x+1,y+4,0xC3);drawCorrect(x+2,y+0,0x0C);drawCorrect(x+2,y+4,0xC3);drawCorrect(x+3,y+0,0x0C);drawCorrect(x+3,y+4,0xC3);drawCorrect(x+4,y+0,0x0C);drawCorrect(x+4,y+4,0x3C);  break;
    case 'T':  drawCorrect(x+0,y+0,0x0C);drawCorrect(x+1,y+0,0x0C);drawCorrect(x+2,y+0,0xFC);drawCorrect(x+2,y+4,0xFF);drawCorrect(x+3,y+0,0x0C);drawCorrect(x+4,y+0,0x0C);  break;
    case 'U':  drawCorrect(x+0,y+0,0xFC);drawCorrect(x+0,y+4,0x3F);drawCorrect(x+1,y+4,0xC0);drawCorrect(x+2,y+4,0xC0);drawCorrect(x+3,y+4,0xC0);drawCorrect(x+4,y+0,0xFC);drawCorrect(x+4,y+4,0x3F);  break;
    case 'V':  drawCorrect(x+0,y+0,0xFC);drawCorrect(x+1,y+4,0x0F);drawCorrect(x+2,y+4,0xF0);drawCorrect(x+3,y+4,0x0F);drawCorrect(x+4,y+0,0xFC);  break;
    case 'W':  drawCorrect(x+0,y+0,0xFC);drawCorrect(x+0,y+4,0xFF);drawCorrect(x+1,y+4,0x30);drawCorrect(x+2,y+4,0x0C);drawCorrect(x+3,y+4,0x30);drawCorrect(x+4,y+0,0xFC);drawCorrect(x+4,y+4,0xFF);  break;
    case 'X':  drawCorrect(x+0,y+0,0x3C);drawCorrect(x+0,y+4,0xF0);drawCorrect(x+1,y+0,0xC0);drawCorrect(x+1,y+4,0x0C);drawCorrect(x+2,y+4,0x03);drawCorrect(x+3,y+0,0xC0);drawCorrect(x+3,y+4,0x0C);drawCorrect(x+4,y+0,0x3C);drawCorrect(x+4,y+4,0xF0);  break;
    case 'Y':  drawCorrect(x+0,y+0,0x3C);drawCorrect(x+1,y+0,0xC0);drawCorrect(x+2,y+4,0xFF);drawCorrect(x+3,y+0,0xC0);drawCorrect(x+4,y+0,0x3C);  break;
    case 'Z':  drawCorrect(x+0,y+0,0x0C);drawCorrect(x+0,y+4,0xF0);drawCorrect(x+1,y+0,0x0C);drawCorrect(x+1,y+4,0xCC);drawCorrect(x+2,y+0,0x0C);drawCorrect(x+2,y+4,0xC3);drawCorrect(x+3,y+0,0xCC);drawCorrect(x+3,y+4,0xC0);drawCorrect(x+4,y+0,0x3C);drawCorrect(x+4,y+4,0xC0); break;
    case ' ':  break;
    case '-':  drawCorrect(x+0,y+4,0x03);drawCorrect(x+1,y+4,0x03);drawCorrect(x+2,y+4,0x03);  break;
    default:  break;

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

void menue(){
  drawString("HAUPTMENUE", 55, 15);
  drawString("NEUES SPIEL", 55, 35);
  drawString("HIGHSCORE", 55, 45);
  drawString("SCHWIRIGKEIT", 55, 55);

  drawPfeil(40, 35);
}
void drawPfeil(uint8_t x, uint8_t y){
  drawCorrect(x+0,y+0,0xC0);drawCorrect(x+0,y+4,0x0C);drawCorrect(x+1,y+0,0xC0);drawCorrect(x+1,y+4,0x0C);drawCorrect(x+2,y+0,0xC0);drawCorrect(x+2,y+4,0x0C);drawCorrect(x+3,y+0,0xC0);drawCorrect(x+3,y+4,0x0C);drawCorrect(x+4,y+0,0xC0);drawCorrect(x+4,y+4,0x0C);drawCorrect(x+5,y+0,0x0C);drawCorrect(x+5,y+4,0xC0);drawCorrect(x+6,y+0,0x3C);drawCorrect(x+6,y+4,0xF0);drawCorrect(x+7,y+0,0xF0);drawCorrect(x+7,y+4,0x3C);drawCorrect(x+8,y+0,0xC0);drawCorrect(x+8,y+4,0x0F);drawCorrect(x+9,y+4,0x03);

}

void drawLives(uint8_t live) {
    for (int i = 0; i < live; i++) {

        printHeart(100 + i * 8, 4);

    }


}
