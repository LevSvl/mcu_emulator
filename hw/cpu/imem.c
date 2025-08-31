#include <stdio.h>
#include <stdint.h>
#include <time.h>
#include <stdlib.h>
#include <errno.h>

#include "common/mcu_config.h"
#include "common/signal.h"
#include "cpu/instr.h"
#include "cpu/imem.h"

extern imem_t imem;

void imem_read(input const uint32_t pc,
               output instr_t * instr)
{
    instr->instr_word = ((uint32_t *)imem.base)[pc];
}
