/*
 * runner.c
 *
 *  Created on: Dec 7, 2019
 *      Author: finnn
 */

#include "runner.h"
#include "gfx.h"

memory_t main_memory = {
    mem_lower_bound: 0,
    mem_upper_bound: MEM_SIZE-1,
	/*
	data: {
		0x83,0x13,0x00,0x52,0x00,0xb3,0x00,0x31,
		0x52,0xb3,0x40,0x41,0x50,0xb3,0x00,0x31,
		0x02,0x23,0x00,0x33,0x44,0x63,0x00,0x62,
		0x00,0x13,0x00,0x00,0x00,0x13,0x00,0x00,
		0x00,0x13,0x00,0x00,0x00,0x13,0x00,0x00,
		0x00,0x13,0x00,0x00
	}
	*/
	data: {
		0x80,0x93,0x00,0x10,0x01,0x13,0x00,0x21,
		0x81,0x93,0x00,0x31,0xf0,0x6f,0xff,0x5f
	}
};




core_state_t processor_state;

void init(){

	for(int i = 0; i < REGFILE_SIZE; i++){
		processor_state.regfile[i] = i;
	}
	processor_state.pc_reg = 0;

}

void run_tick(uint8_t* fb){

	int ypos = 0;
	char msg[128];

	for(int i = 0; i < 1024; i++){
        int result = execute_rv32i(&main_memory, &processor_state, &processor_state);
        

        if(result != 0){
            printf("Error!\n");
            break;
        }		
		ypos = 0;
        for(int j = 0; j < 8; j++){

			sprintf(msg, "  x%d: %04x", j, processor_state.regfile[j]);

            draw_string(msg, 128, 0, ypos,fb);
			ypos += 8;
            //if(j % 2 != 0 && j != 0) printf("\n");
        }

		for(int i = 0; i < 10000000; i++){}

    }
}



