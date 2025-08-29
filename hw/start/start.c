#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#include "clock/clock.h"

struct clk_info clk1_info = {
    .clk_num = 0, .frequency_per_sec = 1, .period_ns = 1 * 1000000000 / 1, .duty_cycle = 30, .lvl_initial = 0, .reset_delay_ns = 30
};

int main(int argc, char const *argv[])
{
    printf("Starting MCU...\n");
    
    pthread_t clk1_thread;

    printf("Creating clock1 generator: ");
    
    if (pthread_create(&clk1_thread, NULL, (void*(*)(void *))clock_reset, (void *)&clk1_info) != 0) {
        printf("FAILED\n");
        exit(1);
    } else {
        printf("OK\n");
    }

    while (1) {} ;

    return 0;
}
