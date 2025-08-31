#include <stdio.h>
#include <stdint.h>
#include <time.h>
#include <stdlib.h>
#include <errno.h>

#include "common/mcu_config.h"
#include "common/signal.h"
#include "cpu/instr.h"
#include "cpu/dmem.h"

#define is_write_access(we) (we > 0)

#define dmem32_access_r(addr) (*(uint32_t *)((uint8_t *)&dmem->data[addr]))

void dmem_access(input_output dmem_t *dmem,
               input uint32_t d_addr,
               input uint8_t we,
               input uint32_t wd)
{
    if (is_write_access(we)) {
        /* Write data */
    } else {
        /* Read data */
        dmem->rd = dmem32_access_r(d_addr);
    }
}
