/*
 * sim.c
 *
 *    Created on: Nov 10, 2019
 *            Author: finnn and aditya
 */

#include "font.h"
#include "gfx.h"

uint8_t draw_char(uint8_t character, uint16_t pos_x, uint16_t pos_y, uint8_t* fb){
    uint16_t x,y;

    if(character == 0x20){
        for(y = 0; y < 9; y++){
            for(x = 0; x < 4; x++){
                fb[pos_x + x + (pos_y + y) * 480] = 0xFF;
            }
        }

        return 4;
    }

    uint8_t charIndex = character - 0x21;
    uint16_t startpos = NeoSans_charpos[charIndex];
    uint8_t width = NeoSans_charpos[charIndex + 1] - startpos;

    for(y = 0; y < 9; y++){
        for(x = 0; x < width; x++){
            fb[pos_x + x + (pos_y + y) * 480] = NeoSans[x + startpos + 551*y];
        }
    }

    return width;
}

uint8_t draw_char_scaled(uint8_t character, uint16_t pos_x, uint16_t pos_y, uint8_t* fb, int16_t scale){
    uint16_t x,y;

    if(character == 0x20){
        for(y = 0; y < 9*scale; y++){
            for(x = 0; x < 4*scale; x++){
                fb[pos_x + x + (pos_y + y) * 480] = 0xFF;
            }
        }

        return 4*scale;
    }

    uint8_t charIndex = character - 0x21;
    uint16_t startpos = NeoSans_charpos[charIndex];
    uint8_t width = NeoSans_charpos[charIndex + 1] - startpos;

    uint8_t pixel;

    for(y = 0; y < 9*scale; y++){
        for(x = 0; x < width*scale; x++){
            pixel = NeoSans[(x>>scale-1) + startpos + 551*(y>>scale-1)];
            fb[pos_x + x + (pos_y + y) * 480] = pixel;
        }
    }
    //TODO: Convert mult to bit shifting
    return width*scale;
}


void draw_string(uint8_t* str, uint16_t n, uint16_t pos_x, uint16_t pos_y, uint8_t* fb){
    int i;
    uint16_t horiz_pos = pos_x;

    for(i = 0; i < n; i++){
        if(str[i] == '\0')
            break;
        horiz_pos += draw_char(str[i], horiz_pos, pos_y, fb);
    }
}

void draw_string_scaled(uint8_t* str, uint16_t n, uint16_t pos_x, uint16_t pos_y, uint8_t* fb, int16_t scale){
    int i;
    uint16_t horiz_pos = pos_x;

    for(i = 0; i < n; i++){
        if(str[i] == '\0')
            break;
        horiz_pos += (uint16_t)(draw_char_scaled(str[i], horiz_pos, pos_y, fb, scale) * 0.9);
    }
}

void draw_vert_line(uint16_t pos_x, uint16_t pos_y1, uint16_t pos_y2, uint8_t color, uint8_t* fb)
{
    if (pos_y2 < pos_y1)//swap if needed
    {
        uint16_t temp = pos_y1;
        pos_y1 = pos_y2;
        pos_y2 = temp;
    }
    for (int i = pos_y1; i <=pos_y2; i++)
    {
        fb[pos_x + (i) * SCREEN_WIDTH] = color;
    }
}

void draw_hor_line(uint16_t pos_x1, uint16_t pos_x2, uint16_t pos_y, uint8_t color, uint8_t* fb)
{
    if (pos_x2 < pos_x1)//swap if needed
    {
        uint16_t temp = pos_x1;
        pos_x1 = pos_x2;
        pos_x2 = temp;
    }
    for (int i = pos_x1; i <=pos_x2; i++)
    {
        fb[i + (pos_y) * SCREEN_WIDTH] = color;
    }
}

void draw_rect(uint16_t pos_x, uint16_t pos_y, uint16_t width, uint16_t height, uint8_t color, uint8_t* fb)
{
    for (int x = pos_x; x < pos_x + width; x++)
    {
        for (int y = pos_y; y < pos_y + height; y++)
        {
            fb[x + (y) * SCREEN_WIDTH] = color;
        }
    }
}

void draw_rect_unfilled(uint16_t pos_x, uint16_t pos_y, uint16_t width, uint16_t height, uint8_t thickness, uint8_t color, uint8_t* fb)
{
    for (int i = 0; i < thickness; i++)
    {
        draw_hor_line(pos_x, pos_x + width, pos_y+i, color, fb);
        draw_hor_line(pos_x, pos_x + width, pos_y+height-i, color, fb);
        draw_vert_line(pos_x+i, pos_y, pos_y + height, color, fb);
        draw_vert_line(pos_x+width-i, pos_y, pos_y + height, color, fb);
    }
}

void draw_sprite_scaled(uint16_t pos_x, uint16_t pos_y, uint16_t width, uint16_t height, uint8_t* sprite, uint8_t* fb, int16_t scale)
{
    int16_t scaled_width = width << (scale-1);
    int16_t scaled_height = height << (scale-1);
    for (int x = pos_x; x < pos_x + scaled_width; x++)
    {
        for (int y = pos_y; y < pos_y + scaled_height; y++)
        {
            fb[x + (y) * SCREEN_WIDTH] = sprite[((x - pos_x) >> (scale-1)) + (width * ((y - pos_y) >> (scale-1)))];
        }
    }
}

/**
    * @brief    Wipes frame buffer
    * @retval none
    */
 void ClearScreen(uint8_t* currentFB)
 {
     for(int y = 0; y < 272; y++){
        for(int x = 0; x < 480; x++){
            currentFB[x + 480*y] = 0xFF;
        }
    }
 }
