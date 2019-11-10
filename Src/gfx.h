/*
 * sim.h
 *
 *  Created on: Nov 10, 2019
 *      Author: finnn
 */

#ifndef GFX_H_
#define GFX_H_

uint8_t draw_char(uint8_t character, uint16_t pos_x, uint16_t pos_y, uint8_t* fb);
void draw_string(uint8_t* str, uint16_t n, uint16_t pos_x, uint16_t pos_y, uint8_t* fb);

#endif /* GFX_H_ */
