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

void init();
void run_tick(uint8_t* fb);



#endif /* RUNNER_H_ */
