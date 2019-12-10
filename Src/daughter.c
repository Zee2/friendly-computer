#include "daughter.h"

// Sets the daughter board LED state
void set_daughter_state(daughter_board_t* board) {
    HAL_GPIO_WritePin(REGFILE_BANK, REGFILE_PIN, (board->regfile) ? GPIO_PIN_SET : GPIO_PIN_RESET);

    HAL_GPIO_WritePin(RS1_BANK, RS1_PIN, (board->rs1) ? GPIO_PIN_SET : GPIO_PIN_RESET);

    HAL_GPIO_WritePin(RS2_BANK, RS2_PIN, (board->rs2) ? GPIO_PIN_SET : GPIO_PIN_RESET);

    HAL_GPIO_WritePin(MEMORY_BANK, MEMORY_PIN, (board->memory) ? GPIO_PIN_SET : GPIO_PIN_RESET);

    HAL_GPIO_WritePin(ALU_BANK, ALU_PIN, (board->alu) ? GPIO_PIN_SET : GPIO_PIN_RESET);

    HAL_GPIO_WritePin(IMM_BANK, IMM_PIN, (board->imm) ? GPIO_PIN_SET : GPIO_PIN_RESET);
}