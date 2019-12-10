/*
 * runner.h
 *
 *  Created on: Dec 7, 2019
 *      Author: finnn
 */

#ifndef RUNNER_H_
#define RUNNER_H_


#include "simulator/simulator.h"
#include "simulator/opcodes.h"
#include "simulator/decode.h"
#include "simulator/core.h"
#include "main.h"

void init(I2C_HandleTypeDef* i2c, uint8_t* fb);
void run_forwards(I2C_HandleTypeDef* i2c, uint8_t* fb);
void run_backwards(I2C_HandleTypeDef* i2c, uint8_t* fb);



#endif /* RUNNER_H_ */
