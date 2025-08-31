#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#include "clock/clock.h"
#include "cpu/imem.h"
#include "cpu/cpu.h"

struct clk_info clk1_info = {
    .clk_num = 0, .frequency_per_sec = 1, .period_ns = 1 * 1000000000 / 1, .duty_cycle = 30, .lvl_initial = 0, .reset_delay_ns = 30
};

int main(int argc, char const *argv[])
{
    const char *program_filename;
    pthread_t clk1_thread;

    if (argc == 1) {
      printf("USAGE:\n");
      printf("  %s -f FILE \n", argv[0]);
      printf("  Example: %s example.bin\n", argv[0]);

      exit(EXIT_FAILURE);
    }

    program_filename = argv[1]; 

    printf("Starting MCU...\n");

    printf("Creating clock1 generator: ");
    
    if (pthread_create(&clk1_thread, NULL, (void*(*)(void *))clock_reset, (void *)&clk1_info) != 0) {
        printf("FAILED\n");
        exit(1);
    } else {
        printf("OK\n");
    }

    printf("Initializing memory: ");
    if (imem_init(program_filename) != 0) {
        printf("FAILED\n");
        exit(1);
    } else {
        printf("OK\n");
    }

    printf("Enable CPU...\n");
    cpu_reset();

    return 0;
}
