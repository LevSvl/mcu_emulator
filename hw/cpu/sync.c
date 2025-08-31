#include <stdio.h>
#include <stdint.h>
#include <time.h>
#include <stdlib.h>
#include <errno.h>


#include "common/compiler_attributes.h"
#include "common/signal.h"
#include "cpu/cpu.h"


__always_inline int wait_clk_posedge(const SIGNAL_T *clk)
{
    while (*clk != 0);
    while (*clk != 1);

    return 1;
}

void cpu_sync_loop(const SIGNAL_T *clk)
{
    /*
     * TODO: cpu_sync_loop must catch every clock posedge but this code can miss ticks
     */

    while (1) {
        if (wait_clk_posedge(clk)) {
            cpu_tick();
        }
    }
}
