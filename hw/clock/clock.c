#include <stdio.h>
#include <stdint.h>
#include <time.h>
#include <stdlib.h>
#include <errno.h>

#include "common/mcu_config.h"
#include "common/compiler_attributes.h"
#include "common/signal.h"
#include "clock/clock.h"

SIGNAL_OUTPUT clk[NUM_CLK_INPUTS];

static inline signal_t clock_pulse(int clk_num) {
    clk[clk_num] = !clk[clk_num];
    return clk[clk_num];
}

static void delay_ns(uint64_t ns)
{
    struct timespec req, rem, *a, *b;
    const time_t ns_max = 999999999;
    req.tv_sec = 0;
    req.tv_nsec = (time_t)(ns > ns_max) ? ns_max : ns;
    a = &req;
    b = &rem;

    while(nanosleep(a, b) && errno==EINTR){
        struct timespec *tmp = a;
        a=b;
        b=tmp;
    }
}

static __noreturn void clock_loop(struct clk_info *clk_info)
{
    uint64_t t_high_ns = (clk_info->duty_cycle * clk_info->period_ns) / 100;
    uint64_t t_low_ns = clk_info->period_ns - t_high_ns;
    while (1) {
        signal_t clk_lvl_current = clock_pulse(clk_info->clk_num);
        if (clk_lvl_current == 1) {
            delay_ns(t_high_ns);
        } else {
            delay_ns(t_low_ns);
        }
    };
}

__noreturn void clock_reset(void *xclk_info)
{
    struct clk_info *clk_info = (struct clk_info *)xclk_info;

    clk[clk_info->clk_num] = clk_info->lvl_initial;
    delay_ns(clk_info->reset_delay_ns);
    clock_loop(clk_info);

    exit(1);
}
