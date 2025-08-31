#include <stdio.h>
#include <stdint.h>
#include <time.h>
#include <stdlib.h>
#include <errno.h>

#include "common/mcu_config.h"
#include "common/compiler_attributes.h"
#include "common/signal.h"
#include "cpu/instr.h"
#include "cpu/imem.h"
#include "cpu/dmem.h"
#include "cpu/regfile.h"
#include "cpu/alu.h"
#include "cpu/cpu.h"

extern uint32_t pc_next;
uint32_t pc;
extern imem_t imem;

void cpu_tick()
{
    instr_t instr;
    regfile_t regfile;
    alu_t alu;
    dmem_t dmem;

    pc = pc_next;

    /* Get instruction by address, decode and put it into reg file */
    imem_read(input (const uint32_t)pc,
              output &instr);
    cpu_decode(input_output &instr);
    cpu_reg_file_write(input (uint8_t)instr_rs1(instr.instr_word),
                       input 0, input (uint8_t)instr_rd(instr.instr_word), input 0, input 0,
                       input_output &regfile);
    /* Put operands into alu */
    uint32_t imm_ext_sign = cpu_sign_extend(input instr.instr_word);
    cpu_alu_write(input_output &alu,
                  input regfile.rd1,
                  input imm_ext_sign);

    /* Make a data memory access */
    uint32_t d_addr = alu.result;
    dmem_access(input_output &dmem,
               input d_addr,
               input 0,
               input 0);

    /* Make a regfile access again */
    uint32_t read_data = dmem.rd;
    cpu_reg_file_write(input 0, input 0,
                       input 0, input 1,
                       input read_data,
                       input_output &regfile);

    pc_next += 4;
}
