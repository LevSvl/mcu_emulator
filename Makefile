COMPILE ?= 

CC = ${COMPILE}gcc
LD = ${COMPILE}ld
OBJCOPY = ${COMPILE}objcopy
OBJDUMP = ${COMPILE}objdump


# Files and directories
MCU_DIR = ./hw
SOFT_DIR = ./sw
TOOLS_DIR = ./tools


BUILD_DIR ?= build

MCU_BUILD_DIR = $(BUILD_DIR)/mcu
MCU_SOURCES = $(shell find -path "$(MCU_DIR)/*.c")
MCU_INCLUDE += $(MCU_DIR)/include

MCU_TARGET_ELF = $(MCU_BUILD_DIR)/mcu
MCU_TARGET_BIN = $(MCU_BUILD_DIR)/mcu.bin
MCU_TARGET_SYM = $(MCU_BUILD_DIR)/mcu.sym
MCU_TARGET_LST = $(MCU_BUILD_DIR)/mcu.lst

# Compiler and linker options
CCFLAGS += -Wall -g


# Build rules
$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)
$(BUILD_DIR)/%: $(BUILD_DIR)
	mkdir -p $@

$(BUILD_DIR)/%.o: %.c
	${CC} ${CCFLAGS} -c $< -o $@

$(MCU_TARGET_ELF): $(MCU_SOURCES)
	${CC} ${CCFLAGS} $(MCU_SOURCES) -I$(MCU_INCLUDE) -o $@

$(MCU_TARGET_LST): $(MCU_TARGET_ELF)
	$(OBJDUMP) -d $< > $@

$(MCU_TARGET_SYM): $(MCU_TARGET_ELF)
	$(OBJDUMP) -t $< > $@

$(MCU_TARGET_BIN): $(MCU_TARGET_ELF)
	$(OBJCOPY) -O binary $< $@

mcu: $(MCU_BUILD_DIR) $(MCU_TARGET_ELF) $(MCU_TARGET_BIN) $(MCU_TARGET_LST) $(MCU_TARGET_SYM)

.PHONY: clean

clean:
	rm -rf $(BUILD_DIR)
