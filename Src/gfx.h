/*
 * sim.h
 *
 *  Created on: Nov 10, 2019
 *      Author: finnn
 */

#ifndef GFX_H_
#define GFX_H_

#define SCREEN_WIDTH 480

void ClearScreen(uint8_t* currentFB);

uint8_t draw_char(uint8_t character, uint16_t pos_x, uint16_t pos_y, uint8_t* fb);
uint8_t draw_char_scaled(uint8_t character, uint16_t pos_x, uint16_t pos_y, uint8_t* fb, int16_t scale);

void draw_string(uint8_t* str, uint16_t n, uint16_t pos_x, uint16_t pos_y, uint8_t* fb);
void draw_string_scaled(uint8_t* str, uint16_t n, uint16_t pos_x, uint16_t pos_y, uint8_t* fb, int16_t scale);

void draw_vert_line(uint16_t pos_x, uint16_t pos_y1, uint16_t pos_y2, uint8_t color, uint8_t* fb);
void draw_hor_line(uint16_t pos_x1, uint16_t pos_x2, uint16_t pos_y, uint8_t color, uint8_t* fb);

void draw_rect(uint16_t pos_x, uint16_t pos_y, uint16_t width, uint16_t height, uint8_t color, uint8_t* fb);
void draw_sprite_scaled(uint16_t pos_x, uint16_t pos_y, uint16_t width, uint16_t height, uint8_t* sprite, uint8_t* fb, int16_t scale);

#endif /* GFX_H_ */
