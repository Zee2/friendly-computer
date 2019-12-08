/*
 * runner.c
 *
 *  Created on: Dec 7, 2019
 *      Author: finnn
 */

#include "runner.h"

memory_t main_memory = {
    mem_lower_bound: 0,
    mem_upper_bound: MEM_SIZE-1,
	data: {
		0x83,0x13,0x00,0x52,0x00,0xb3,0x00,0x31,
		0x52,0xb3,0x40,0x41,0x50,0xb3,0x00,0x31,
		0x02,0x23,0x00,0x33,0x44,0x63,0x00,0x62,
		0x00,0x13,0x00,0x00,0x00,0x13,0x00,0x00,
		0x00,0x13,0x00,0x00,0x00,0x13,0x00,0x00,
		0x00,0x13,0x00,0x00
	}
};




core_state_t processor_state;

void init(){


	for(int i = 0; i < REGFILE_SIZE; i++){
		processor_state.regfile[i] = i;
	}
	processor_state.pc_reg = 0;
}



