#include <stdio.h>
#include <stdint.h>
#include <time.h>
#include <stdlib.h>
#include <errno.h>


#include "common/mcu_config.h"
#include "common/signal.h"
#include "cpu/instr.h"
#include "cpu/alu.h"
#include "cpu/cpu.h"

void cpu_alu_write(input_output alu_t *alu,
                   input uint32_t src_a,
                   input uint32_t src_b)
{
    switch (alu->control)
    {
    case 0x0:
        alu->result = src_a + src_b;
        break;

    case 0x1:
        alu->result = src_a - src_b;
        break;

    case 0x2:
        alu->result = src_a & src_b;
        break;

    case 0x3:
        alu->result = src_a | src_b;
        break;
    
    case 0x5:
        alu->result = src_a < src_b;
        break;  

    default:
        break;
    }
}
