#include <stdio.h>
#include <stdint.h>
#include <time.h>
#include <stdlib.h>
#include <errno.h>


#include "common/mcu_config.h"
#include "common/signal.h"
#include "cpu/instr.h"
#include "cpu/cpu.h"

#define SIGNEX(v, sb) ((v) | (((v) & (1 << (sb))) ? ~((1 << (sb))-1) : 0))

int32_t cpu_sign_extend(input uint32_t instr_word)
{
    const int sign_bit_num = 11;
    int32_t imm_ext = SIGNEX(get_field(instr_word, I_INSTR_IMM), sign_bit_num);
    return imm_ext;
}
