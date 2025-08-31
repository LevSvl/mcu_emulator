#ifndef IMEM_H
#define IMEM_H

#include "cpu/instr.h"

typedef struct imem {
    uintptr_t base;
    uint32_t offset;
    uint32_t size;
} imem_t;

int imem_init(const char * program_filename);

void imem_read(input const uint32_t pc,
               output instr_t * instr);

#endif // IMEM_H
