#ifndef DAUGHTER_H
#define DAUGHTER_H

#include "main.h"

#define REGFILE_BANK    GPIOC
#define REGFILE_PIN     GPIO_PIN_8

#define RS1_BANK        GPIOC
#define RS1_PIN         GPIO_PIN_9

#define RS2_BANK        GPIOA
#define RS2_PIN         GPIO_PIN_8

#define MEMORY_BANK     GPIOA
#define MEMORY_PIN      GPIO_PIN_9

#define ALU_BANK        GPIOA
#define ALU_PIN         GPIO_PIN_11

#define IMM_BANK        GPIOA
#define IMM_PIN         GPIO_PIN_12

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