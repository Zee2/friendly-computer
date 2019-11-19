/*
 * gui.c
 *
 *    Created on: Nov 13, 2019
 *            Author: finnn
 */

#include <stdint.h>
#include <string.h>
#include "gui.h"
#include "gfx.h"
#include "smile.h"
#include <math.h>

/**
  * @brief    Draws appropriate menu page
  * @retval none
  */
void DrawMenu(enum InterfacePage currentPage, uint8_t* currentFB, uint16_t counter) {
    char teststring1[64];
    char* startupmessage = "Welcome to the friendly computer!";

	if (currentPage == startup) 
    {
        draw_sprite_scaled(480/2 - (64 << 1)/2, -fabs((sin(counter * 0.05) * 10.0)) + 40, 64, 64, &smiley_face_hires, currentFB, 2);
		draw_string_scaled(startupmessage, strlen(startupmessage), 95, 180, currentFB, 2);
	} 
    else if (currentPage == home)
    {
        draw_string_scaled("Home", strlen("Home"), 65, 20, currentFB, 2);
        draw_sprite_scaled(0, 0, 32, 32, &smiley_face, currentFB, 2);

        draw_string_scaled("addi R3, R6, 45", strlen("ADDI R3, R6, 45"), 255, 80, currentFB, 2);
        draw_string_scaled("xor  R3, R6, R1", strlen("XOR  R3, R6, R1"), 255, 100, currentFB, 2);
        draw_string_scaled("bne  R3, R6, 10", strlen("BNE  R3, R6, 10"), 255, 120, currentFB, 2);
        draw_string_scaled("and  R1, R2, R3", strlen("AND  R1, R2, R3"), 255, 140, currentFB, 2);

        /*
        draw_hor_line(10, 100, 40, 0x00, currentFB);
        draw_vert_line(10, 20, 100, 0x00, currentFB);
        draw_rect(40, 50, 100, 100, 0x00, currentFB);
        */
	}
}