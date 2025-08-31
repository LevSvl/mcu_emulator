#include <stdio.h>
#include <stdint.h>
#include <time.h>
#include <stdlib.h>
#include <errno.h>

#include "common/mcu_config.h"
#include "common/signal.h"
#include "cpu/regfile.h"
#include "cpu/cpu.h"

#define input_changed(input) (input > 0)

void cpu_reg_file_write(input uint8_t a1, input uint8_t a2, input uint8_t a3,
                        input uint8_t we3, input uint32_t wd3,
                        output regfile_t * regfile)
{
    if (input_changed(a1)) {
        regfile->a1 = a1;
    }
    if (input_changed(a2)) {
        regfile->a2 = a2;
    }
    if (input_changed(a3)) {
        regfile->a3 = a3;
    }
    if (input_changed(we3)) {
        regfile->wd3 = wd3;
        regfile->gpr[regfile->a3] = wd3;
    }

    regfile->rd1 = regfile->gpr[a1];
}
