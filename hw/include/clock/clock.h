#ifndef CLOCK_H
#define CLOCK_H

#include <stdint.h>

#include "common/compiler_attributes.h"
#include "common/signal.h"

struct clk_info {
    int clk_num;
    uint64_t reset_delay_ns;
    uint64_t frequency_per_sec; 
    uint64_t period_ns;
    uint8_t duty_cycle;
    signal_t lvl_initial; 
};

__noreturn void clock_reset(void *xclk_info);

#endif // CLOCK_H