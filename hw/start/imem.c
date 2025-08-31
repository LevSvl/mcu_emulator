#include <stdio.h>
#include <stdint.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <unistd.h>
#include <errno.h>
#include "common/mcu_config.h"
#include "common/signal.h"
#include "cpu/imem.h"

imem_t imem;

int imem_init(const char * program_filename)
{
    int program_fd;
    uintptr_t imem_base;

    if ((program_fd = open(program_filename, O_RDONLY)) < 0) {
        return 1;
    };

    if ((imem_base = (uintptr_t)mmap(NULL, IMEM_SIZE,
         PROT_READ, MAP_PRIVATE, program_fd, 0)) == (uintptr_t)MAP_FAILED) {
        close(program_fd);
        return 1;
    }

    imem.base = imem_base;
    imem.size = IMEM_SIZE;
    imem.offset = 0;

    return 0;
}
