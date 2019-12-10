#ifndef DAUGHTER_H
#define DAUGHTER_H

#include "main.h"

// D11
#define REGFILE_BANK    GPIOB
#define REGFILE_PIN     GPIO_PIN_5

// D10
#define RS1_BANK        GPIOD
#define RS1_PIN         GPIO_PIN_14

// D9
#define RS2_BANK        GPIOD
#define RS2_PIN         GPIO_PIN_15

// D8
#define MEMORY_BANK     GPIOF
#define MEMORY_PIN      GPIO_PIN_3

// D7
#define ALU_BANK        GPIOG
#define ALU_PIN         GPIO_PIN_12

// D3
#define IMM_BANK        GPIOE
#define IMM_PIN         GPIO_PIN_13

typedef struct daughter_board_t {
  // Set to 0 to disable; 1 to enable these lighting zones
  int regfile;
  int rs1;
  int rs2;
  int memory;
  int alu;
  int imm;
} daughter_board_t;

void set_daughter_state(daughter_board_t* board);

#endif