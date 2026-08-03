#pragma once

#include <cstdint>
#include <string>

class Cpu;

namespace ops
{
    enum class AddressingMode
    {
        IMP, //Implicit
        ACC, //Accumulator
        IMM, //Immediate
        ZPG, //Zero Page
        ZPX, //Zero Page Indexed X
        ZPY, //Zero Page Indexed Y
        ABS, //Absolute
        ABX, //Absolute Indexed X
        ABY, //Absolute Indexed Y
        IND, //Indirect
        INX, //Indirect Indexed X
        INY, //Indirect Indexed Y
        REL, //Relative
        UNQ, //Unique
            // Unique isnt a real addressing mode on hardware.
            // Its purpose is to keep the code modular while allowing instructions 
            // that dont follow the normal op -> address -> execute control flow.
            // If an opcode has the unique addressing mode, it will just skip the
            // address retrieval step and jump to the execution which is where the
            // retreival will be implemented instead
    };

    enum class Instruction {
        ADC, AND, ASL, BCC, BCS, BEQ, BIT, BMI,
        BNE, BPL, BRK, BVC, BVS, CLC, CLD, CLI,
        CLV, CMP, CPX, CPY, DEC, DEX, DEY, EOR,
        INC, INX, INY, JMP, JSR, LDA, LDX, LDY,
        LSR, NOP, ORA, PHA, PHP, PLA, PLP, ROL,
        ROR, RTI, RTS, SBC, SEC, SED, SEI, STA,
        STX, STY, TAX, TAY, TSX, TXA, TXS, TYA
    };
    
    struct Opcode
    {
        void (*fetchAddress)(Cpu&); // Addressing Mode Function
        void (*execute)(Cpu&); // Opcode Function
        AddressingMode mode; // Addressing Mode
        Instruction op; // Opcode
    };

    extern const Opcode pointerTable [256];

    // DEBUGGING FUNCTIONS
    std::string op_to_string(Instruction op);

    // FLAG FUNCTIONS
    void set_flag_carry(Cpu& cpu, bool set);
    void set_flag_zero(Cpu& cpu, uint8_t result);
    void set_flag_interrupt_disable(Cpu& cpu, bool set);
    void set_flag_decimal(Cpu& cpu, bool set);
    void set_flag_b(Cpu& cpu, bool set);
    void set_flag_overflow(Cpu& cpu, bool set);
    void set_flag_negative(Cpu& cpu, uint8_t result);

    // ADDRESSING MODE FUNCTIONS
    void mode_imp(Cpu& cpu);
    void mode_acc(Cpu& cpu);
    void mode_imm(Cpu& cpu);
    void mode_zpg(Cpu& cpu);
    void mode_zpx(Cpu& cpu);
    void mode_zpy(Cpu& cpu);
    void mode_abs(Cpu& cpu);
    void mode_abx(Cpu& cpu);
    void mode_aby(Cpu& cpu);
    void mode_ind(Cpu& cpu);
    void mode_inx(Cpu& cpu);
    void mode_iny(Cpu& cpu);

    // OPCODE FUNCTIONS
    // Access
    void op_lda(Cpu& cpu); // Official
    void op_lda_imm(Cpu& cpu); // Official
    void op_sta(Cpu& cpu); // Official
    void op_ldx(Cpu& cpu); // Official
    void op_ldx_imm(Cpu& cpu); // Official
    void op_stx(Cpu& cpu); // Official
    void op_ldy(Cpu& cpu); // Official
    void op_ldy_imm(Cpu& cpu); // Official
    void op_sty(Cpu& cpu); // Official
    // Transfer
    void op_tax(Cpu& cpu); // Official
    void op_txa(Cpu& cpu); // Official
    void op_tay(Cpu& cpu); // Official
    void op_tya(Cpu& cpu); // Official
    // Arithmetic
    void op_adc(Cpu& cpu); // Official
    void op_adc_imm(Cpu& cpu); // Official
    void op_sbc(Cpu& cpu); // Official
    void op_sbc_imm(Cpu& cpu); // Official
    void op_inc(Cpu& cpu); // Official
    void op_dec(Cpu& cpu); // Official
    void op_inx(Cpu& cpu); // Official
    void op_dex(Cpu& cpu); // Official
    void op_iny(Cpu& cpu); // Official
    void op_dey(Cpu& cpu); // Official
    // Shift
    void op_asl(Cpu& cpu); // Official
    void op_asl_acc(Cpu& cpu); // Official
    void op_lsr(Cpu& cpu); // Official
    void op_lsr_acc(Cpu& cpu); // Official
    void op_rol(Cpu& cpu); // Official
    void op_rol_acc(Cpu& cpu); // Official
    void op_ror(Cpu& cpu); // Official
    void op_ror_acc(Cpu& cpu); // Official
    // Bitwise
    void op_and(Cpu& cpu); // Official
    void op_and_imm(Cpu& cpu); // Official
    void op_ora(Cpu& cpu); // Official
    void op_ora_imm(Cpu& cpu); // Official
    void op_eor(Cpu& cpu); // Official
    void op_eor_imm(Cpu& cpu); // Official
    void op_bit(Cpu& cpu); // Official
    // Compare
    void op_cmp(Cpu& cpu); // Official
    void op_cmp_imm(Cpu& cpu); // Official
    void op_cpx(Cpu& cpu); // Official
    void op_cpx_imm(Cpu& cpu); // Official
    void op_cpy(Cpu& cpu); // Official
    void op_cpy_imm(Cpu& cpu); // Official
    // Branch
    void op_bcc(Cpu& cpu); // Official
    void op_bcs(Cpu& cpu); // Official
    void op_beq(Cpu& cpu); // Official
    void op_bne(Cpu& cpu); // Official
    void op_bpl(Cpu& cpu); // Official
    void op_bmi(Cpu& cpu); // Official
    void op_bvc(Cpu& cpu); // Official
    void op_bvs(Cpu& cpu); // Official
    // Jump
    void op_jmp(Cpu& cpu); // Official
    void op_jmp_ind(Cpu& cpu); // Official
    void op_jsr(Cpu& cpu); // Official
    void op_rts(Cpu& cpu); // Official
    void op_brk(Cpu& cpu); // Official
    void op_rti(Cpu& cpu); // Official
    // Stack
    void op_pha(Cpu& cpu); // Official
    void op_pla(Cpu& cpu); // Official
    void op_php(Cpu& cpu); // Official
    void op_plp(Cpu& cpu); // Official
    void op_txs(Cpu& cpu); // Official
    void op_tsx(Cpu& cpu); // Official
    // Flags
    void op_clc(Cpu& cpu); // Official
    void op_sec(Cpu& cpu); // Official
    void op_cli(Cpu& cpu); // Official
    void op_sei(Cpu& cpu); // Official
    void op_cld(Cpu& cpu); // Official
    void op_sed(Cpu& cpu); // Official
    void op_clv(Cpu& cpu); // Official
    // Other
    void op_nop(Cpu& cpu); // Official
}