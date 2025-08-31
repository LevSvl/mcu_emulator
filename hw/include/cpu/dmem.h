#ifndef DMEM_H
#define DMEM_H

#include "common/signal.h"

typedef struct dmem {
    input uint8_t we;
    input uint32_t a;
    input uint32_t wd;
    output uint32_t rd;

    char data[SRAM_SIZE];
} dmem_t;

void dmem_access(input_output dmem_t *dmem,
               input uint32_t d_addr,
               input uint8_t we,
               input uint32_t wd);

#endif // DMEM_H
