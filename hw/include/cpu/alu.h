#ifndef ALU_H
#define ALU_H

#include <stdint.h>

typedef struct alu {
    input uint8_t control;
    output uint32_t result;
} alu_t;

#endif // ALU_H
