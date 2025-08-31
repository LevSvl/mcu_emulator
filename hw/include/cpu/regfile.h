#ifndef REGFILE_H
#define REGFILE_H

#include <stdint.h>

#include "common/signal.h"

typedef unsigned int gpr_t;

typedef struct regfile {
    gpr_t gpr[32];

    output uint32_t rd1;
    output uint32_t rd2;

    input uint8_t a1;
    input uint8_t a2;
    input uint8_t a3;
    
    input uint32_t wd3;
    input uint8_t we3;

} regfile_t;

#endif // REGFILE_H
