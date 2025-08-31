#ifndef CPU_H
#define CPU_H

#include "common/compiler_attributes.h"
#include "common/signal.h"
#include "cpu/instr.h"
#include "cpu/regfile.h"
#include "cpu/alu.h"

#define get_field(reg, mask) (((reg) & \
                 (uint64_t)(mask)) / ((mask) & ~((mask) << 1)))
#define set_field(reg, mask, val) (((reg) & ~(uint64_t)(mask)) | \
                 (((uint64_t)(val) * ((mask) & ~((mask) << 1))) & \
                 (uint64_t)(mask)))

extern void cpu_reset(void);

extern void cpu_tick(void);

void cpu_decode(input_output instr_t * instr);

extern void cpu_sync_loop(input const SIGNAL_T *clk);

int32_t cpu_sign_extend(input uint32_t instr_word);

void cpu_reg_file_write(input uint8_t a1, input uint8_t a2, input uint8_t a3,
                        input uint8_t we3, input uint32_t wd3,
                        output regfile_t * regfile);

void cpu_alu_write(input_output alu_t *alu,
                   input uint32_t src_a,
                   input uint32_t src_b);

#endif // CPU_H
