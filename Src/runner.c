/*
 * runner.c
 *
 *  Created on: Dec 7, 2019
 *      Author: finnn
 */

#include "runner.h"
#include "gfx.h"
#include <stdio.h>
#include <string.h>

#define MODULO(i,n) ((i % n + n) % n)

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
		0x93,0x80,0x10,0x00,
		0x13,0x01,0x21,0x00,
		0x93,0x81,0x31,0x00,
		0x6f,0xf0,0x5f,0xff
	}
};

uint8_t led_data[] = {
		  0x0,
		  0x0,
		  0x0,
		  0x0,
		  0x0,
		  0x0,
		  0x0,
		  0x0,
		  0x0,
		  0x0,
		  0x0,
		  0x0,
		  0x0,
		  0x0,
		  0x0,
		  0x0
  };

// Array of proc_state
core_state_t processor_states[128];

char printed[32*128];

int cursor;

void init(I2C_HandleTypeDef* i2c, uint8_t* fb){

	for(int i = 0; i < REGFILE_SIZE; i++){
		processor_states[0].regfile[i] = 0;
	}
	for(int i = 0; i < 128; i++){

		processor_states[i].pc_reg = 0;
	}

	update_display(i2c, fb);

}

void update_display(I2C_HandleTypeDef* i2c, uint8_t* fb){

	int ypos = 0;
	int ins_scroll = 0;
	char msg[128];
	ypos = 70;
	for(int j = 0; j < 8; j++){

		sprintf(msg, "  x%d: %04x", j, processor_states[MODULO((cursor+1),128)].regfile[j]);

		draw_string_scaled(msg, 128, 0, ypos,fb,2);
		ypos += 20;
		
		//if(j % 2 != 0 && j != 0) printf("\n");
	}

	for(int line = 0; line < 9; line++){
		if(strlen(&printed[32*((line + cursor - 4)%128)]) == 0)
			sprintf(msg, " 0x%x:                          ", processor_states[MODULO((line + cursor-4),128)].pc_reg);
		else
			sprintf(msg, " 0x%x: %s  ", processor_states[MODULO((line + cursor-4),128)].pc_reg, &printed[32*MODULO((line + cursor-4),128)]);
		if(line == 4) {
			draw_string_scaled(msg, 32, 200, 50 + line * 20,fb,2);
			draw_rect_unfilled(180, 44 + line * 20, 260, 31, 2, 0, fb);
		}
		else if(line > 4)
			draw_string_scaled(msg, 32, 200, 60 + line * 20,fb,2);
		else
			draw_string_scaled(msg, 32, 200, 40 + line * 20,fb,2);
	}

	//draw_string_scaled(&printed[32*(cursor+1)], 128, 300, ins_scroll,fb,2);
	ins_scroll += 18;
	if(ins_scroll > 200) ins_scroll = 0;

	

	for(int k = 0; k < 16; k++){
		led_data[k] = 0;
	}
	//processor_states[(cursor+1) % 128].regfile[m]
	int bit = 0;
	for(int k = 0; k < 16; k+=2){
		for(int m = 0; m < 8; m++){
			led_data[k] |= ((processor_states[MODULO((cursor+1), 128)].regfile[m] >> bit) & 0x1) << m;
		}
		//led_data[k] = 1 << bit;
		bit++;
	}
	for(int k = 1; k < 16; k+=2){
		for(int m = 0; m < 8; m++){
			led_data[k] |= ((processor_states[MODULO((cursor+1), 128)].regfile[m] >> bit) & 0x1) << m;
		}
		//led_data[k] = 1 << bit;
		bit++;
	}

	HAL_I2C_Mem_Write(i2c, 0x70 << 1, 0x0, 1, &(led_data[0]), 16, 1000);
	//HAL_I2C_Mem_Write(i2c, 0x72 << 1, 0x0, 1, &(led_data[0]), 16, 1000);

}

void run_forwards(I2C_HandleTypeDef* i2c, uint8_t* fb, daughter_board_t* board){

	int ypos = 0;
	int ins_scroll = 0;
	char msg[128];

	int counter = 0;

	char pretty_printed[128];
	int result = execute_rv32i(&main_memory, &processor_states[MODULO(cursor, 128)], &processor_states[MODULO(cursor+1, 128)], &printed[32*MODULO(cursor, 128)], board);

	if(result != 0){
		printf("Error!\n");
		return;
	}
	

	//ClearScreen(fb);
	update_display(i2c, fb);
	
	cursor++;
}

void run_backwards(I2C_HandleTypeDef* i2c, uint8_t* fb){
	cursor = (cursor-1);
	if(cursor < 0)
		cursor = 127;
	update_display(i2c, fb);
}



