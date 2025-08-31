#ifndef INSTR_H
#define INSTR_H

/*
 * Got instructions set from https://five-embeddev.com/riscv-user-isa-manual/Priv-v1.12/instr-table.html
 */

enum instr_type {R, I, S, B, U};

typedef struct instr {
    /*
     * instr_word is used for quick access to full instruction word
    */
    uint32_t instr_word;

    enum instr_type type;
    /*
     * imm size depends on instruction type and is controlled by additive mask
    */
    uint32_t imm;
    /*
     * rd as well as rs1 and rs2 may not be used, in that case
     * empty instruction fields are expected to be filled with NULL
    */
    uint8_t rs1;
    uint8_t rs2;
    uint8_t rd;

    uint8_t opcode;
    /*
     * func3, func7 are also optional fields and also can be filled with NULL
    */
    uint8_t func3;
    uint8_t func7;
} instr_t;

#define instr_rs1_mask      (0x000F8000U)
#define instr_rd_mask       (0x00000F80U)

#define instr_rs1(instr)    (get_field(instr, instr_rs1_mask))
#define instr_rd(instr)     (get_field(instr, instr_rd_mask))

#define I_INSTR_IMM (0xFFF00000U)

#endif // INSTR_H
