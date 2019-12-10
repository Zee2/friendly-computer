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

#define SENSITIVITY 4

int last_encoder = 0;

/**
  * @brief    Draws appropriate menu page
  * @retval none
  */
void DrawMenu(enum InterfacePage currentPage, I2C_HandleTypeDef* i2c, uint8_t* currentFB, uint16_t counter) {
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

        int new = -TIM1->CNT/SENSITIVITY;
        
        if(new > last_encoder)
            run_forwards(i2c, currentFB);
        else if(new < last_encoder)
            run_backwards(i2c, currentFB);

        last_encoder = new;


        //draw_rect_unfilled(100, 100, 50, 60, 3, 0, currentFB);

        /*
        draw_hor_line(10, 100, 40, 0x00, currentFB);
        draw_vert_line(10, 20, 100, 0x00, currentFB);
        draw_rect(40, 50, 100, 100, 0x00, currentFB);
        */
	}
}
