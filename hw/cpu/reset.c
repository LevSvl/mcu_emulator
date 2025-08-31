#include <stdio.h>
#include <stdint.h>
#include <time.h>
#include <stdlib.h>
#include <errno.h>


#include "common/mcu_config.h"
#include "common/signal.h"
#include "cpu/cpu.h"

// External signals
SIGNAL_INPUT clk[NUM_CLK_INPUTS];

// CPU internal signals
uint32_t pc_next;

void cpu_reset()
{
    pc_next = CPU_RESETVEC;

    cpu_sync_loop(input &clk[0]);
}
