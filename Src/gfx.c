/*
 * sim.c
 *
 *  Created on: Nov 10, 2019
 *      Author: finnn and aditya
 */

#include "font.h"
#include "gfx.h"

uint8_t draw_char(uint8_t character, uint16_t pos_x, uint16_t pos_y, uint8_t* fb){
  uint16_t x,y;

  if(character == 0x20){
    for(y = 0; y < 9; y++){
      for(x = 0; x < 4; x++){
        fb[pos_x + x + (pos_y + y) * 480] = 0xFF;
      }
    }

    return 4;
  }

  uint8_t charIndex = character - 0x21;
  uint16_t startpos = NeoSans_charpos[charIndex];
  uint8_t width = NeoSans_charpos[charIndex + 1] - startpos;

  for(y = 0; y < 9; y++){
    for(x = 0; x < width; x++){
      fb[pos_x + x + (pos_y + y) * 480] = NeoSans[x + startpos + 551*y];
    }
  }

	return width;
}

uint8_t draw_char_scaled(uint8_t character, uint16_t pos_x, uint16_t pos_y, uint8_t* fb, int16_t scale){
  uint16_t x,y;

  if(character == 0x20){
    for(y = 0; y < 9*scale; y++){
      for(x = 0; x < 4*scale; x++){
        fb[pos_x + x + (pos_y + y) * 480] = 0xFF;
      }
    }

    return 4*scale;
  }

  uint8_t charIndex = character - 0x21;
  uint16_t startpos = NeoSans_charpos[charIndex];
  uint8_t width = NeoSans_charpos[charIndex + 1] - startpos;

  for(y = 0; y < 9*scale; y++){
    for(x = 0; x < width*scale; x++){
      fb[pos_x + x + (pos_y + y) * 480] = NeoSans[(x>>scale-1) + startpos + 551*(y>>scale-1)];
    }
  }

	return width*scale;
}


void draw_string(uint8_t* str, uint16_t n, uint16_t pos_x, uint16_t pos_y, uint8_t* fb){
  int i;
  uint16_t horiz_pos = pos_x;

  for(i = 0; i < n; i++){
    horiz_pos += draw_char(str[i], horiz_pos, pos_y, fb);
  }
}

void draw_string_scaled(uint8_t* str, uint16_t n, uint16_t pos_x, uint16_t pos_y, uint8_t* fb, int16_t scale){
  int i;
  uint16_t horiz_pos = pos_x;

  for(i = 0; i < n; i++){
    horiz_pos += draw_char_scaled(str[i], horiz_pos, pos_y, fb, scale);
  }
}

void draw_vert_line(uint16_t pos_x, uint16_t pos_y1, uint16_t pos_y2, uint8_t color, uint8_t* fb)
{
  if (pos_y2 < pos_y1)//swap if needed
  {
    uint16_t temp = pos_y1;
    pos_y1 = pos_y2;
    pos_y2 = temp;
  }
  for (int i = pos_y1; i <=pos_y2; i++)
  {
    fb[pos_x + (i) * SCREEN_WIDTH] = color;
  }
}

void draw_hor_line(uint16_t pos_x1, uint16_t pos_x2, uint16_t pos_y, uint8_t color, uint8_t* fb)
{
  if (pos_x2 < pos_x1)//swap if needed
  {
    uint16_t temp = pos_x1;
    pos_x1 = pos_x2;
    pos_x2 = temp;
  }
  for (int i = pos_x1; i <=pos_x2; i++)
  {
    fb[i + (pos_y) * SCREEN_WIDTH] = color;
  }
}

/**
  * @brief  Wipes frame buffer
  * @retval none
  */
 void ClearScreen(uint8_t* currentFB)
 {
   for(int y = 0; y < 272; y++){
    for(int x = 0; x < 480; x++){
      currentFB[x + 480*y] = 0xFF;
    }
  }
 }
