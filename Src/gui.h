/*
 * gui.h
 *
 *  Created on: Nov 13, 2019
 *      Author: finnn
 */

#ifndef GUI_H_
#define GUI_H_

#include "main.h"

enum InterfacePage {startup, home, settings, registers, error};

void DrawMenu(enum InterfacePage currentPage, I2C_HandleTypeDef* i2c, uint8_t* currentFB, uint16_t counter);

#endif /* GUI_H_ */
