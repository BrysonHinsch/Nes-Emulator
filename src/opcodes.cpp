
#include <cstdint>

#include "opcodes.h"
#include "cpu.h"

namespace ops
{
    // OPCODE POINTER TABLE
    const Opcode pointerTable [256] {
    /* 00 */ {mode_imp, op_brk, AddressingMode::IMP, Instruction::BRK},
    /* 01 */ {mode_inx, op_ora, AddressingMode::INX, Instruction::ORA},
    /* 02 */ {nullptr, nullptr, AddressingMode::IMP, Instruction::NOP},
    /* 03 */ {nullptr, nullptr, AddressingMode::IMP, Instruction::NOP},
    /* 04 */ {nullptr, nullptr, AddressingMode::IMP, Instruction::NOP},
    /* 05 */ {mode_zpg, op_ora, AddressingMode::ZPG, Instruction::ORA},
    /* 06 */ {mode_zpg, op_asl, AddressingMode::ZPG, Instruction::ASL},
    /* 07 */ {nullptr, nullptr, AddressingMode::IMP, Instruction::NOP},
    /* 08 */ {mode_imp, op_php, AddressingMode::IMP, Instruction::PHP},
    /* 09 */ {mode_imm, op_ora, AddressingMode::IMM, Instruction::ORA},
    /* 0A */ {mode_acc, op_asl, AddressingMode::ACC, Instruction::ASL},
    /* 0B */ {nullptr, nullptr, AddressingMode::IMP, Instruction::NOP},
    /* 0C */ {nullptr, nullptr, AddressingMode::IMP, Instruction::NOP},
    /* 0D */ {mode_abs, op_ora, AddressingMode::ABS, Instruction::ORA},
    /* 0E */ {mode_abs, op_asl, AddressingMode::ABS, Instruction::ASL},
    /* 0F */ {nullptr, nullptr, AddressingMode::IMP, Instruction::NOP},

    /* 10 */ {nullptr,  op_bpl, AddressingMode::REL, Instruction::BPL},
    /* 11 */ {mode_iny, op_ora, AddressingMode::INY, Instruction::ORA},
    /* 12 */ {nullptr, nullptr, AddressingMode::IMP, Instruction::NOP},
    /* 13 */ {nullptr, nullptr, AddressingMode::IMP, Instruction::NOP},
    /* 14 */ {nullptr, nullptr, AddressingMode::IMP, Instruction::NOP},
    /* 15 */ {mode_zpx, op_ora, AddressingMode::ZPX, Instruction::ORA},
    /* 16 */ {mode_zpx, op_asl, AddressingMode::ZPX, Instruction::ASL},
    /* 17 */ {nullptr, nullptr, AddressingMode::IMP, Instruction::NOP},
    /* 18 */ {mode_imp, op_clc, AddressingMode::IMP, Instruction::CLC},
    /* 19 */ {mode_aby, op_ora, AddressingMode::ABY, Instruction::ORA},
    /* 1A */ {nullptr, nullptr, AddressingMode::IMP, Instruction::NOP},
    /* 1B */ {nullptr, nullptr, AddressingMode::IMP, Instruction::NOP},
    /* 1C */ {nullptr, nullptr, AddressingMode::IMP, Instruction::NOP},
    /* 1D */ {mode_abx, op_ora, AddressingMode::ABX, Instruction::ORA},
    /* 1E */ {mode_abx, op_asl, AddressingMode::ABX, Instruction::ASL},
    /* 1F */ {nullptr, nullptr, AddressingMode::IMP, Instruction::NOP},

    /* 20 */ {mode_abs, op_jsr, AddressingMode::UNQ, Instruction::JSR},
    /* 21 */ {mode_inx, op_and, AddressingMode::INX, Instruction::AND},
    /* 22 */ {nullptr, nullptr, AddressingMode::IMP, Instruction::NOP},
    /* 23 */ {nullptr, nullptr, AddressingMode::IMP, Instruction::NOP},
    /* 24 */ {mode_zpg, op_bit, AddressingMode::ZPG, Instruction::BIT},
    /* 25 */ {mode_zpg, op_and, AddressingMode::ZPG, Instruction::AND},
    /* 26 */ {mode_zpg, op_rol, AddressingMode::ZPG, Instruction::ROL},
    /* 27 */ {nullptr, nullptr, AddressingMode::IMP, Instruction::NOP},
    /* 28 */ {mode_imp, op_plp, AddressingMode::IMP, Instruction::PLP},
    /* 29 */ {mode_imm, op_and, AddressingMode::IMM, Instruction::AND},
    /* 2A */ {mode_acc, op_rol, AddressingMode::ACC, Instruction::ROL},
    /* 2B */ {nullptr, nullptr, AddressingMode::IMP, Instruction::NOP},
    /* 2C */ {mode_abs, op_bit, AddressingMode::ABS, Instruction::BIT},
    /* 2D */ {mode_abs, op_and, AddressingMode::ABS, Instruction::AND},
    /* 2E */ {mode_abs, op_rol, AddressingMode::ABS, Instruction::ROL},
    /* 2F */ {nullptr, nullptr, AddressingMode::IMP, Instruction::NOP},

    /* 30 */ {nullptr,  op_bmi, AddressingMode::REL, Instruction::BMI},
    /* 31 */ {mode_iny, op_and, AddressingMode::INY, Instruction::AND},
    /* 32 */ {nullptr, nullptr, AddressingMode::IMP, Instruction::NOP},
    /* 33 */ {nullptr, nullptr, AddressingMode::IMP, Instruction::NOP},
    /* 34 */ {nullptr, nullptr, AddressingMode::IMP, Instruction::NOP},
    /* 35 */ {mode_zpx, op_and, AddressingMode::ZPX, Instruction::AND},
    /* 36 */ {mode_zpx, op_rol, AddressingMode::ZPX, Instruction::ROL},
    /* 37 */ {nullptr, nullptr, AddressingMode::IMP, Instruction::NOP},
    /* 38 */ {mode_imp, op_sec, AddressingMode::IMP, Instruction::SEC},
    /* 39 */ {mode_aby, op_and, AddressingMode::ABY, Instruction::AND},
    /* 3A */ {nullptr, nullptr, AddressingMode::IMP, Instruction::NOP},
    /* 3B */ {nullptr, nullptr, AddressingMode::IMP, Instruction::NOP},
    /* 3C */ {nullptr, nullptr, AddressingMode::IMP, Instruction::NOP},
    /* 3D */ {mode_abx, op_and, AddressingMode::ABX, Instruction::AND},
    /* 3E */ {mode_abx, op_rol, AddressingMode::ABX, Instruction::ROL},
    /* 3F */ {nullptr, nullptr, AddressingMode::IMP, Instruction::NOP},

    /* 40 */ {mode_imp, op_rti, AddressingMode::IMP, Instruction::RTI},
    /* 41 */ {mode_inx, op_eor, AddressingMode::INX, Instruction::EOR},
    /* 42 */ {nullptr, nullptr, AddressingMode::IMP, Instruction::NOP},
    /* 43 */ {nullptr, nullptr, AddressingMode::IMP, Instruction::NOP},
    /* 44 */ {nullptr, nullptr, AddressingMode::IMP, Instruction::NOP},
    /* 45 */ {mode_zpg, op_eor, AddressingMode::ZPG, Instruction::EOR},
    /* 46 */ {mode_zpg, op_lsr, AddressingMode::ZPG, Instruction::LSR},
    /* 47 */ {nullptr, nullptr, AddressingMode::IMP, Instruction::NOP},
    /* 48 */ {mode_imp, op_pha, AddressingMode::IMP, Instruction::PHA},
    /* 49 */ {mode_imm, op_eor, AddressingMode::IMM, Instruction::EOR},
    /* 4A */ {mode_acc, op_lsr, AddressingMode::ACC, Instruction::LSR},
    /* 4B */ {nullptr, nullptr, AddressingMode::IMP, Instruction::NOP},
    /* 4C */ {mode_abs, op_jmp, AddressingMode::ABS, Instruction::JMP},
    /* 4D */ {mode_abs, op_eor, AddressingMode::ABS, Instruction::EOR},
    /* 4E */ {mode_abs, op_lsr, AddressingMode::ABS, Instruction::LSR},
    /* 4F */ {nullptr, nullptr, AddressingMode::IMP, Instruction::NOP},

    /* 50 */ {nullptr,  op_bvc, AddressingMode::REL, Instruction::BVC},
    /* 51 */ {mode_iny, op_eor, AddressingMode::INY, Instruction::EOR},
    /* 52 */ {nullptr, nullptr, AddressingMode::IMP, Instruction::NOP},
    /* 53 */ {nullptr, nullptr, AddressingMode::IMP, Instruction::NOP},
    /* 54 */ {nullptr, nullptr, AddressingMode::IMP, Instruction::NOP},
    /* 55 */ {mode_zpx, op_eor, AddressingMode::ZPX, Instruction::EOR},
    /* 56 */ {mode_zpx, op_lsr, AddressingMode::ZPX, Instruction::LSR},
    /* 57 */ {nullptr, nullptr, AddressingMode::IMP, Instruction::NOP},
    /* 58 */ {mode_imp, op_cli, AddressingMode::IMP, Instruction::CLI},
    /* 59 */ {mode_aby, op_eor, AddressingMode::ABY, Instruction::EOR},
    /* 5A */ {nullptr, nullptr, AddressingMode::IMP, Instruction::NOP},
    /* 5B */ {nullptr, nullptr, AddressingMode::IMP, Instruction::NOP},
    /* 5C */ {nullptr, nullptr, AddressingMode::IMP, Instruction::NOP},
    /* 5D */ {mode_abx, op_eor, AddressingMode::ABX, Instruction::EOR},
    /* 5E */ {mode_abx, op_lsr, AddressingMode::ABX, Instruction::LSR},
    /* 5F */ {nullptr, nullptr, AddressingMode::IMP, Instruction::NOP},

    /* 60 */ {mode_imp, op_rts, AddressingMode::IMP, Instruction::RTS},
    /* 61 */ {mode_inx, op_adc, AddressingMode::INX, Instruction::ADC},
    /* 62 */ {nullptr, nullptr, AddressingMode::IMP, Instruction::NOP},
    /* 63 */ {nullptr, nullptr, AddressingMode::IMP, Instruction::NOP},
    /* 64 */ {nullptr, nullptr, AddressingMode::IMP, Instruction::NOP},
    /* 65 */ {mode_zpg, op_adc, AddressingMode::ZPG, Instruction::ADC},
    /* 66 */ {mode_zpg, op_ror, AddressingMode::ZPG, Instruction::ROR},
    /* 67 */ {nullptr, nullptr, AddressingMode::IMP, Instruction::NOP},
    /* 68 */ {mode_imp, op_pla, AddressingMode::IMP, Instruction::PLA},
    /* 69 */ {mode_imm, op_adc, AddressingMode::IMM, Instruction::ADC},
    /* 6A */ {mode_acc, op_ror, AddressingMode::ACC, Instruction::ROR},
    /* 6B */ {nullptr, nullptr, AddressingMode::IMP, Instruction::NOP},
    /* 6C */ {mode_ind, op_jmp, AddressingMode::IND, Instruction::JMP},
    /* 6D */ {mode_abs, op_adc, AddressingMode::ABS, Instruction::ADC},
    /* 6E */ {mode_abs, op_ror, AddressingMode::ABS, Instruction::ROR},
    /* 6F */ {nullptr, nullptr, AddressingMode::IMP, Instruction::NOP},

    /* 70 */ {nullptr,  op_bvs, AddressingMode::REL, Instruction::BVS},
    /* 71 */ {mode_iny, op_adc, AddressingMode::INY, Instruction::ADC},
    /* 72 */ {nullptr, nullptr, AddressingMode::IMP, Instruction::NOP},
    /* 73 */ {nullptr, nullptr, AddressingMode::IMP, Instruction::NOP},
    /* 74 */ {nullptr, nullptr, AddressingMode::IMP, Instruction::NOP},
    /* 75 */ {mode_zpx, op_adc, AddressingMode::ZPX, Instruction::ADC},
    /* 76 */ {mode_zpx, op_ror, AddressingMode::ZPX, Instruction::ROR},
    /* 77 */ {nullptr, nullptr, AddressingMode::IMP, Instruction::NOP},
    /* 78 */ {mode_imp, op_sei, AddressingMode::IMP, Instruction::SEI},
    /* 79 */ {mode_aby, op_adc, AddressingMode::ABY, Instruction::ADC},
    /* 7A */ {nullptr, nullptr, AddressingMode::IMP, Instruction::NOP},
    /* 7B */ {nullptr, nullptr, AddressingMode::IMP, Instruction::NOP},
    /* 7C */ {nullptr, nullptr, AddressingMode::IMP, Instruction::NOP},
    /* 7D */ {mode_abx, op_adc, AddressingMode::ABX, Instruction::ADC},
    /* 7E */ {mode_abx, op_ror, AddressingMode::ABX, Instruction::ROR},
    /* 7F */ {nullptr, nullptr, AddressingMode::IMP, Instruction::NOP},

    /* 80 */ {mode_imm, op_nop, AddressingMode::IMM, Instruction::NOP},
    /* 81 */ {mode_inx, op_sta, AddressingMode::INX, Instruction::STA},
    /* 82 */ {nullptr, nullptr, AddressingMode::IMP, Instruction::NOP},
    /* 83 */ {nullptr, nullptr, AddressingMode::IMP, Instruction::NOP},
    /* 84 */ {mode_zpg, op_sty, AddressingMode::ZPG, Instruction::STY},
    /* 85 */ {mode_zpg, op_sta, AddressingMode::ZPG, Instruction::STA},
    /* 86 */ {mode_zpg, op_stx, AddressingMode::ZPG, Instruction::STX},
    /* 87 */ {nullptr, nullptr, AddressingMode::IMP, Instruction::NOP},
    /* 88 */ {mode_imp, op_dey, AddressingMode::IMP, Instruction::DEY},
    /* 89 */ {mode_imm, op_nop, AddressingMode::IMM, Instruction::NOP},
    /* 8A */ {mode_imp, op_txa, AddressingMode::IMP, Instruction::TXA},
    /* 8B */ {nullptr, nullptr, AddressingMode::IMP, Instruction::NOP},
    /* 8C */ {mode_abs, op_sty, AddressingMode::ABS, Instruction::STY},
    /* 8D */ {mode_abs, op_sta, AddressingMode::ABS, Instruction::STA},
    /* 8E */ {mode_abs, op_stx, AddressingMode::ABS, Instruction::STX},
    /* 8F */ {nullptr, nullptr, AddressingMode::IMP, Instruction::NOP},

    /* 90 */ {nullptr,  op_bcc, AddressingMode::REL, Instruction::BCC},
    /* 91 */ {mode_iny, op_sta, AddressingMode::INY, Instruction::STA},
    /* 92 */ {nullptr, nullptr, AddressingMode::IMP, Instruction::NOP},
    /* 93 */ {nullptr, nullptr, AddressingMode::IMP, Instruction::NOP},
    /* 94 */ {mode_zpx, op_sty, AddressingMode::ZPX, Instruction::STY},
    /* 95 */ {mode_zpx, op_sta, AddressingMode::ZPX, Instruction::STA},
    /* 96 */ {mode_zpy, op_stx, AddressingMode::ZPY, Instruction::STX},
    /* 97 */ {nullptr, nullptr, AddressingMode::IMP, Instruction::NOP},
    /* 98 */ {mode_imp, op_tya, AddressingMode::IMP, Instruction::TYA},
    /* 99 */ {mode_aby, op_sta, AddressingMode::ABY, Instruction::STA},
    /* 9A */ {mode_imp, op_txs, AddressingMode::IMP, Instruction::TXS},
    /* 9B */ {nullptr, nullptr, AddressingMode::IMP, Instruction::NOP},
    /* 9C */ {nullptr, nullptr, AddressingMode::IMP, Instruction::NOP},
    /* 9D */ {mode_abx, op_sta, AddressingMode::ABX, Instruction::STA},
    /* 9E */ {nullptr, nullptr, AddressingMode::IMP, Instruction::NOP},
    /* 9F */ {nullptr, nullptr, AddressingMode::IMP, Instruction::NOP},

    /* A0 */ {mode_imm, op_ldy, AddressingMode::IMM, Instruction::LDY},
    /* A1 */ {mode_inx, op_lda, AddressingMode::INX, Instruction::LDA},
    /* A2 */ {mode_imm, op_ldx, AddressingMode::IMM, Instruction::LDX},
    /* A3 */ {nullptr, nullptr, AddressingMode::IMP, Instruction::NOP},
    /* A4 */ {mode_zpg, op_ldy, AddressingMode::ZPG, Instruction::LDY},
    /* A5 */ {mode_zpg, op_lda, AddressingMode::ZPG, Instruction::LDA},
    /* A6 */ {mode_zpg, op_ldx, AddressingMode::ZPG, Instruction::LDX},
    /* A7 */ {nullptr, nullptr, AddressingMode::IMP, Instruction::NOP},
    /* A8 */ {mode_imp, op_tay, AddressingMode::IMP, Instruction::TAY},
    /* A9 */ {mode_imm, op_lda, AddressingMode::IMM, Instruction::LDA},
    /* AA */ {mode_imp, op_tax, AddressingMode::IMP, Instruction::TAX},
    /* AB */ {nullptr, nullptr, AddressingMode::IMP, Instruction::NOP},
    /* AC */ {mode_abs, op_ldy, AddressingMode::ABS, Instruction::LDY},
    /* AD */ {mode_abs, op_lda, AddressingMode::ABS, Instruction::LDA},
    /* AE */ {mode_abs, op_ldx, AddressingMode::ABS, Instruction::LDX},
    /* AF */ {nullptr, nullptr, AddressingMode::IMP, Instruction::NOP},

    /* B0 */ {nullptr,  op_bcs, AddressingMode::REL, Instruction::BCS},
    /* B1 */ {mode_iny, op_lda, AddressingMode::INY, Instruction::LDA},
    /* B2 */ {nullptr, nullptr, AddressingMode::IMP, Instruction::NOP},
    /* B3 */ {nullptr, nullptr, AddressingMode::IMP, Instruction::NOP},
    /* B4 */ {mode_zpx, op_ldy, AddressingMode::ZPX, Instruction::LDY},
    /* B5 */ {mode_zpx, op_lda, AddressingMode::ZPX, Instruction::LDA},
    /* B6 */ {mode_zpy, op_ldx, AddressingMode::ZPY, Instruction::LDX},
    /* B7 */ {nullptr, nullptr, AddressingMode::IMP, Instruction::NOP},
    /* B8 */ {mode_imp, op_clv, AddressingMode::IMP, Instruction::CLV},
    /* B9 */ {mode_aby, op_lda, AddressingMode::ABY, Instruction::LDA},
    /* BA */ {mode_imp, op_tsx, AddressingMode::IMP, Instruction::TSX},
    /* BB */ {nullptr, nullptr, AddressingMode::IMP, Instruction::NOP},
    /* BC */ {mode_abx, op_ldy, AddressingMode::ABX, Instruction::LDY},
    /* BD */ {mode_abx, op_lda, AddressingMode::ABX, Instruction::LDA},
    /* BE */ {mode_aby, op_ldx, AddressingMode::ABY, Instruction::LDX},
    /* BF */ {nullptr, nullptr, AddressingMode::IMP, Instruction::NOP},

    /* C0 */ {mode_imm, op_cpy, AddressingMode::IMM, Instruction::CPY},
    /* C1 */ {mode_inx, op_cmp, AddressingMode::INX, Instruction::CMP},
    /* C2 */ {nullptr, nullptr, AddressingMode::IMP, Instruction::NOP},
    /* C3 */ {nullptr, nullptr, AddressingMode::IMP, Instruction::NOP},
    /* C4 */ {mode_zpg, op_cpy, AddressingMode::ZPG, Instruction::CPY},
    /* C5 */ {mode_zpg, op_cmp, AddressingMode::ZPG, Instruction::CMP},
    /* C6 */ {mode_zpg, op_dec, AddressingMode::ZPG, Instruction::DEC},
    /* C7 */ {nullptr, nullptr, AddressingMode::IMP, Instruction::NOP},
    /* C8 */ {mode_imp, op_iny, AddressingMode::IMP, Instruction::INY},
    /* C9 */ {mode_imm, op_cmp, AddressingMode::IMM, Instruction::CMP},
    /* CA */ {mode_imp, op_dex, AddressingMode::IMP, Instruction::DEX},
    /* CB */ {nullptr, nullptr, AddressingMode::IMP, Instruction::NOP},
    /* CC */ {mode_abs, op_cpy, AddressingMode::ABS, Instruction::CPY},
    /* CD */ {mode_abs, op_cmp, AddressingMode::ABS, Instruction::CMP},
    /* CE */ {mode_abs, op_dec, AddressingMode::ABS, Instruction::DEC},
    /* CF */ {nullptr, nullptr, AddressingMode::IMP, Instruction::NOP},

    /* D0 */ {nullptr,  op_bne, AddressingMode::REL, Instruction::BNE},
    /* D1 */ {mode_iny, op_cmp, AddressingMode::INY, Instruction::CMP},
    /* D2 */ {nullptr, nullptr, AddressingMode::IMP, Instruction::NOP},
    /* D3 */ {nullptr, nullptr, AddressingMode::IMP, Instruction::NOP},
    /* D4 */ {nullptr, nullptr, AddressingMode::IMP, Instruction::NOP},
    /* D5 */ {mode_zpx, op_cmp, AddressingMode::ZPX, Instruction::CMP},
    /* D6 */ {mode_zpx, op_dec, AddressingMode::ZPX, Instruction::DEC},
    /* D7 */ {nullptr, nullptr, AddressingMode::IMP, Instruction::NOP},
    /* D8 */ {mode_imp, op_cld, AddressingMode::IMP, Instruction::CLD},
    /* D9 */ {mode_aby, op_cmp, AddressingMode::ABY, Instruction::CMP},
    /* DA */ {nullptr, nullptr, AddressingMode::IMP, Instruction::NOP},
    /* DB */ {nullptr, nullptr, AddressingMode::IMP, Instruction::NOP},
    /* DC */ {nullptr, nullptr, AddressingMode::IMP, Instruction::NOP},
    /* DD */ {mode_abx, op_cmp, AddressingMode::ABX, Instruction::CMP},
    /* DE */ {mode_abx, op_dec, AddressingMode::ABX, Instruction::DEC},
    /* DF */ {nullptr, nullptr, AddressingMode::IMP, Instruction::NOP},

    /* E0 */ {mode_imm, op_cpx, AddressingMode::IMM, Instruction::CPX},
    /* E1 */ {mode_inx, op_sbc, AddressingMode::INX, Instruction::SBC},
    /* E2 */ {nullptr, nullptr, AddressingMode::IMP, Instruction::NOP},
    /* E3 */ {nullptr, nullptr, AddressingMode::IMP, Instruction::NOP},
    /* E4 */ {mode_zpg, op_cpx, AddressingMode::ZPG, Instruction::CPX},
    /* E5 */ {mode_zpg, op_sbc, AddressingMode::ZPG, Instruction::SBC},
    /* E6 */ {mode_zpg, op_inc, AddressingMode::ZPG, Instruction::INC},
    /* E7 */ {nullptr, nullptr, AddressingMode::IMP, Instruction::NOP},
    /* E8 */ {mode_imp, op_inx, AddressingMode::IMP, Instruction::INX},
    /* E9 */ {mode_imm, op_sbc, AddressingMode::IMM, Instruction::SBC},
    /* EA */ {mode_imp, op_nop, AddressingMode::IMP, Instruction::NOP},
    /* EB */ {nullptr, nullptr, AddressingMode::IMP, Instruction::NOP},
    /* EC */ {mode_abs, op_cpx, AddressingMode::ABS, Instruction::CPX},
    /* ED */ {mode_abs, op_sbc, AddressingMode::ABS, Instruction::SBC},
    /* EE */ {mode_abs, op_inc, AddressingMode::ABS, Instruction::INC},
    /* EF */ {nullptr, nullptr, AddressingMode::IMP, Instruction::NOP},

    /* F0 */ {nullptr,  op_beq, AddressingMode::REL, Instruction::BEQ},
    /* F1 */ {mode_iny, op_sbc, AddressingMode::INY, Instruction::SBC},
    /* F2 */ {nullptr, nullptr, AddressingMode::IMP, Instruction::NOP},
    /* F3 */ {nullptr, nullptr, AddressingMode::IMP, Instruction::NOP},
    /* F4 */ {nullptr, nullptr, AddressingMode::IMP, Instruction::NOP},
    /* F5 */ {mode_zpx, op_sbc, AddressingMode::ZPX, Instruction::SBC},
    /* F6 */ {mode_zpx, op_inc, AddressingMode::ZPX, Instruction::INC},
    /* F7 */ {nullptr, nullptr, AddressingMode::IMP, Instruction::NOP},
    /* F8 */ {mode_imp, op_sed, AddressingMode::IMP, Instruction::SED},
    /* F9 */ {mode_aby, op_sbc, AddressingMode::ABY, Instruction::SBC},
    /* FA */ {nullptr, nullptr, AddressingMode::IMP, Instruction::NOP},
    /* FB */ {nullptr, nullptr, AddressingMode::IMP, Instruction::NOP},
    /* FC */ {nullptr, nullptr, AddressingMode::IMP, Instruction::NOP},
    /* FD */ {mode_abx, op_sbc, AddressingMode::ABX, Instruction::SBC},
    /* FE */ {mode_abx, op_inc, AddressingMode::ABX, Instruction::INC},
    /* FF */ {nullptr, nullptr, AddressingMode::IMP, Instruction::NOP}
    };

    // FLAG FUNCTIONS
    void set_flag_carry(Cpu& cpu, bool set) // bit 0
    {
        if (set) { cpu.P |= 0b00000001; }
        else { cpu.P &= 0b11111110; }
    }
    void set_flag_zero(Cpu& cpu, uint8_t result) // bit 1
    {
        if (result == 0) { cpu.P |= 0b00000010; }
        else { cpu.P &= 0b11111101; }
    }
    void set_flag_interrupt_disable(Cpu& cpu, bool set) // bit 2
    {
        if (set) { cpu.P |= 0b00000100; }
        else { cpu.P &= 0b11111011; }
    }
    void set_flag_decimal(Cpu& cpu, bool set) // bit 3
    {
        if (set) { cpu.P |= 0b00001000; }
        else { cpu.P &= 0b11110111; }
    }
    void set_flag_b(Cpu& cpu, bool set) // bit 4
    {
        if (set) { cpu.P |= 0b00010000; }
        else { cpu.P &= 0b11101111; }
    }
    void set_flag_overflow(Cpu& cpu, bool set) // bit 6
    {
        if (set) { cpu.P |= 0b01000000; }
        else { cpu.P &= 0b10111111; }
    }
    void set_flag_negative(Cpu& cpu, uint8_t result) // bit 7
    {
        uint8_t mask = (result & 0x80);
        cpu.P = ((cpu.P & 0x7F) ^ mask);
    }

    // ADDRESSING MODE FUNCTIONS
    void mode_imp(Cpu& cpu)
    {
        // Value isn't used in any way so it's thrown away.
        // On hardware, theres a read here, so it needs to be read here for the data bus.
        cpu.bus.read(cpu.PC);
        cpu.addressReady = true;
        cpu.clock_cpu();
    }
    void mode_acc(Cpu& cpu)
    {
        // Value isn't used in any way so it's thrown away.
        // On hardware, theres a read here, so it needs to be read here for the data bus.
        cpu.bus.read(cpu.PC);
        cpu.addressReady = true;
        cpu.clock_cpu();
    }
    void mode_imm(Cpu& cpu)
    {
        cpu.value = cpu.bus.read(cpu.PC);
        cpu.PC++;
        cpu.addressReady = true;
        cpu.clock_cpu();
    }
    void mode_zpg(Cpu& cpu)
    {
        cpu.address = cpu.bus.read(cpu.PC);
        cpu.PC++;
        cpu.addressReady = true;
    }
    void mode_zpx(Cpu& cpu)
    {
        switch(cpu.localClock)
        {
            case 0:
                cpu.address = cpu.bus.read(cpu.PC);
                cpu.PC++;
            case 1:
                cpu.address %= (cpu.address + cpu.X);
                cpu.localClock = 0;
                cpu.addressReady = true;
        }
    }
    void mode_zpy(Cpu& cpu)
    {
        switch(cpu.localClock)
        {
            case 0:
                cpu.address = cpu.bus.read(cpu.PC);
                cpu.PC++;
            case 1:
                cpu.address %= (cpu.address + cpu.Y);
                cpu.localClock = 0;
                cpu.addressReady = true;
        }
    }
    void mode_abs(Cpu& cpu)
    {
        switch(cpu.localClock)
        {
            case 0:
                cpu.address = cpu.bus.read(cpu.PC);
                cpu.PC++;
            case 1:
                cpu.address += (cpu.bus.read(cpu.PC) << 8);
                cpu.localClock = 0;
                cpu.addressReady = true;
        }
    }
    void mode_abx(Cpu& cpu)
    {
        switch(cpu.localClock)
        {
            case 0:
                cpu.address = cpu.bus.read(cpu.PC);
                cpu.PC++;
            case 1:
                uint8_t lowByte = cpu.address;
                uint8_t wrap = lowByte+cpu.X;
                cpu.address = wrap;
                cpu.address += (cpu.bus.read(cpu.PC) << 8);
                if (wrap >= lowByte) { // if it doesn't wrap (no extra cycle)
                    cpu.localClock = 0;
                    cpu.addressReady = true;
                }
            case 2:
                cpu.address += 0x100;
                cpu.localClock = 0;
                cpu.addressReady = true;
        }
    }
    void mode_aby(Cpu& cpu)
    {
        switch(cpu.localClock)
        {
            case 0:
                cpu.address = cpu.bus.read(cpu.PC);
                cpu.PC++;
            case 1:
                uint8_t lowByte = cpu.address;
                uint8_t wrap = lowByte+cpu.Y;
                cpu.address = wrap;
                cpu.address += (cpu.bus.read(cpu.PC) << 8);
                if (wrap >= lowByte) { // if it doesn't wrap (no extra cycle)
                    cpu.localClock = 0;
                    cpu.addressReady = true;
                }
            case 2:
                cpu.address += 0x100;
                cpu.localClock = 0;
                cpu.addressReady = true;
        }
    }
    void mode_ind(Cpu& cpu)
    {
        switch(cpu.localClock)
        {
            case 0:
                cpu.address = cpu.bus.read(cpu.PC);
                cpu.PC++;
            case 1:
                cpu.address += (cpu.bus.read(cpu.PC) << 8);
                cpu.PC++;
            case 2:
                cpu.temp8 = cpu.bus.read(cpu.address);
            case 3:
                if (static_cast<uint8_t>(cpu.address) + 1 == 0) 
                {
                    cpu.PC = cpu.bus.read(cpu.address & 0xFF00) << 8;
                }
                else 
                {
                    cpu.PC = cpu.bus.read(cpu.address + 1) << 8;
                }
                cpu.PC += cpu.temp8;
        }
    }
    void mode_inx(Cpu& cpu)
    {
        switch(cpu.localClock)
        {
            case 0:
                cpu.temp8 = cpu.bus.read(cpu.PC);
                cpu.PC++;
            case 1:
                cpu.temp8 = (cpu.bus.read(cpu.temp8) + cpu.X);
            case 2:
                cpu.address = cpu.bus.read(cpu.temp8);
            case 3:
                cpu.address += (cpu.bus.read(cpu.temp8 + 1) << 8);
                cpu.localClock = 0;
                cpu.addressReady = true;
        }
    }
    void mode_iny(Cpu& cpu)
    {
        switch(cpu.localClock)
        {
            case 0:
                cpu.temp8 = cpu.bus.read(cpu.PC);
                cpu.PC++;
            case 1:
                cpu.address = cpu.bus.read(cpu.temp8);
            case 2:
                uint8_t lowByte = cpu.address;
                uint8_t wrap = lowByte+cpu.Y;
                cpu.address = wrap;
                cpu.address += (cpu.bus.read(cpu.temp8 + 1) << 8);
                if (wrap >= lowByte) { // if it doesn't wrap (no extra cycle)
                    cpu.localClock = 0;
                    cpu.addressReady = true;
                }
            case 3:
                cpu.address += 0x100;
                cpu.localClock = 0;
                cpu.addressReady = true;
        }
    }

    // OPCODE FUNCTIONS
    // Access
    void op_lda(Cpu& cpu)
    {
        cpu.A = cpu.bus.read(cpu.address);
        set_flag_zero(cpu, cpu.A);
        set_flag_negative(cpu, cpu.A);
        cpu.clear_state();
    }
    void op_sta(Cpu& cpu)
    {
        cpu.bus.write(cpu.address, cpu.A);
        cpu.clear_state();
    }
    void op_ldx(Cpu& cpu)
    {
        cpu.X = cpu.bus.read(cpu.address);
        set_flag_zero(cpu, cpu.X);
        set_flag_negative(cpu, cpu.X);
        cpu.clear_state();
    }
    void op_stx(Cpu& cpu)
    {
        cpu.bus.write(cpu.address, cpu.X);
        cpu.clear_state();
    }
    void op_ldy(Cpu& cpu)
    {
        cpu.Y = cpu.bus.read(cpu.address);
        set_flag_zero(cpu, cpu.Y);
        set_flag_negative(cpu, cpu.Y);
        cpu.clear_state();
    }
    void op_sty(Cpu& cpu)
    {
        cpu.bus.write(cpu.address, cpu.Y);
        cpu.clear_state();
    }
    // Transfer
    void op_tax(Cpu& cpu)
    {
        cpu.X = cpu.A;
        set_flag_zero(cpu, cpu.X);
        set_flag_negative(cpu, cpu.X);
        cpu.clear_state();
    }
    void op_txa(Cpu& cpu)
    {
        cpu.A = cpu.X;
        set_flag_zero(cpu, cpu.A);
        set_flag_negative(cpu, cpu.A);
        cpu.clear_state();
    }
    void op_tay(Cpu& cpu)
    {
        cpu.Y = cpu.A;
        set_flag_zero(cpu, cpu.Y);
        set_flag_negative(cpu, cpu.Y);
        cpu.clear_state();
    }
    void op_tya(Cpu& cpu)
    {
        cpu.A = cpu.Y;
        set_flag_zero(cpu, cpu.A);
        set_flag_negative(cpu, cpu.A);
        cpu.clear_state();
    }
    // Arithmetic
    void op_adc(Cpu& cpu)
    {
        cpu.value = cpu.bus.read(cpu.address);
        uint16_t result = cpu.A + cpu.value + (cpu.P & 0x01);
        set_flag_carry(cpu, result > 0xFF);
        set_flag_zero(cpu, result);
        set_flag_overflow(cpu, ((result ^ cpu.A) & (result ^ cpu.value) & 0x80));
        set_flag_negative(cpu, result);
        cpu.A = (result % 256);
        cpu.clear_state();
    }
    void op_sbc(Cpu& cpu)
    {
        cpu.value = cpu.bus.read(cpu.address);
        uint16_t result = cpu.A - cpu.value - (~cpu.P & 0x01);
        set_flag_carry(cpu, result > 0xFF);
        set_flag_zero(cpu, result);
        set_flag_overflow(cpu, ((result ^ cpu.A) & (result ^ ~cpu.value) & 0x80));
        set_flag_negative(cpu, result);
        cpu.A = (result % 256);
        cpu.clear_state();
    }
    void op_inc(Cpu& cpu)
    {
        switch(cpu.localClock)
        {
            case 0:
                cpu.value = cpu.bus.read(cpu.address);
                break;
            case 1:
                cpu.bus.write(cpu.address, cpu.value);
                cpu.value++;
                set_flag_zero(cpu, cpu.value);
                set_flag_negative(cpu, cpu.value);
                break;
            case 2:
                cpu.bus.write(cpu.address, cpu.value);
                cpu.clear_state();
                break;
        }
    }
    void op_dec(Cpu& cpu)
    {
        switch(cpu.localClock)
        {
            case 0:
                cpu.value = cpu.bus.read(cpu.address);
                break;
            case 1:
                cpu.bus.write(cpu.address, cpu.value);
                cpu.value--;
                set_flag_zero(cpu, cpu.value);
                set_flag_negative(cpu, cpu.value);
                break;
            case 2:
                cpu.bus.write(cpu.address, cpu.value);
                cpu.clear_state();
                break;
        }
    }
    void op_inx(Cpu& cpu)
    {
        cpu.X++;
        set_flag_zero(cpu, cpu.X);
        set_flag_negative(cpu, cpu.X);
        cpu.clear_state();
    }
    void op_dex(Cpu& cpu)
    {
        cpu.X--;
        set_flag_zero(cpu, cpu.X);
        set_flag_negative(cpu, cpu.X);
        cpu.clear_state();
    }
    void op_iny(Cpu& cpu)
    {
        cpu.Y++;
        set_flag_zero(cpu, cpu.Y);
        set_flag_negative(cpu, cpu.Y);
        cpu.clear_state();
    }
    void op_dey(Cpu& cpu)
    {
        cpu.Y--;
        set_flag_zero(cpu, cpu.Y);
        set_flag_negative(cpu, cpu.Y);
        cpu.clear_state();
    }
    // Shift
    void op_asl(Cpu& cpu)
    {
        switch(cpu.localClock)
        {
            case 0:
                cpu.value = cpu.bus.read(cpu.address);
                break;
            case 1:
                cpu.bus.write(cpu.address, cpu.value);
                set_flag_carry(cpu, ((cpu.value & 0b10000000) == 0b10000000));
                cpu.value<<=1;
                set_flag_zero(cpu, cpu.value);
                set_flag_negative(cpu, cpu.value);
                break;
            case 2:
                cpu.bus.write(cpu.address, cpu.value);
                cpu.clear_state();
                break;
        }
    }
    void op_lsr(Cpu& cpu)
    {
        switch(cpu.localClock)
        {
            case 0:
                cpu.value = cpu.bus.read(cpu.address);
                break;
            case 1:
                cpu.bus.write(cpu.address, cpu.value);
                set_flag_carry(cpu, ((cpu.value & 0b00000001) == 0b00000001));
                cpu.value>>=1;
                set_flag_zero(cpu, cpu.value);
                set_flag_negative(cpu, cpu.value);
                break;
            case 2:
                cpu.bus.write(cpu.address, cpu.value);
                cpu.clear_state();
                break;
        }
    }
    void op_rol(Cpu& cpu)
    {
        switch(cpu.localClock)
        {
            case 0:
                cpu.value = cpu.bus.read(cpu.address);
                break;
            case 1:
                cpu.bus.write(cpu.address, cpu.value);
                set_flag_carry(cpu, ((cpu.value & 0b10000000) == 0b10000000));
                cpu.value<<=1;
                cpu.value |= cpu.P;
                set_flag_zero(cpu, cpu.value);
                set_flag_negative(cpu, cpu.value);
                break;
            case 2:
                cpu.bus.write(cpu.address, cpu.value);
                cpu.clear_state();
                break;
        }
    }
    void op_ror(Cpu& cpu)
    {
        switch(cpu.localClock)
        {
            case 0:
                cpu.value = cpu.bus.read(cpu.address);
                break;
            case 1:
                cpu.bus.write(cpu.address, cpu.value);
                set_flag_carry(cpu, ((cpu.value & 0b00000001) == 0b00000001));
                cpu.value>>=1;
                cpu.value |= (cpu.P << 7);
                set_flag_zero(cpu, cpu.value);
                set_flag_negative(cpu, cpu.value);
                break;
            case 2:
                cpu.bus.write(cpu.address, cpu.value);
                cpu.clear_state();
                break;
        }
    }
    // Bitwise
    void op_and(Cpu& cpu)
    {
        cpu.A &= cpu.bus.read(cpu.address);
        set_flag_zero(cpu, cpu.A);
        set_flag_negative(cpu, cpu.A);
        cpu.clear_state();
    }
    void op_ora(Cpu& cpu)
    {
        cpu.A |= cpu.bus.read(cpu.address);
        set_flag_zero(cpu, cpu.A);
        set_flag_negative(cpu, cpu.A);
        cpu.clear_state();
    }
    void op_eor(Cpu& cpu)
    {
        cpu.A ^= cpu.bus.read(cpu.address);
        set_flag_zero(cpu, cpu.A);
        set_flag_negative(cpu, cpu.A);
        cpu.clear_state();
    }
    void op_bit(Cpu& cpu)
    {
        uint8_t memory = cpu.bus.read(cpu.address);
        uint8_t result = cpu.A & memory;
        set_flag_zero(cpu, result);
        set_flag_overflow(cpu, ((memory & 0b01000000) == 0b01000000));
        set_flag_negative(cpu, ((memory & 0b10000000) == 0b10000000));
        cpu.clear_state();
    }
    // Compare
    void op_cmp(Cpu& cpu)
    {
        uint8_t memory = cpu.bus.read(cpu.address);
        set_flag_carry(cpu, cpu.A>=memory);
        set_flag_zero(cpu, cpu.A==memory);
        uint8_t result = (cpu.A - memory);
        set_flag_negative(cpu, result);
        cpu.clear_state();
    }
    void op_cpx(Cpu& cpu)
    {
        uint8_t memory = cpu.bus.read(cpu.address);
        set_flag_carry(cpu, cpu.X>=memory);
        set_flag_zero(cpu, cpu.X==memory);
        uint8_t result = (cpu.X - memory);
        set_flag_negative(cpu, result);
        cpu.clear_state();
    }
    void op_cpy(Cpu& cpu)
    {
        uint8_t memory = cpu.bus.read(cpu.address);
        set_flag_carry(cpu, cpu.Y>=memory);
        set_flag_zero(cpu, cpu.Y==memory);
        uint8_t result = (cpu.Y - memory);
        set_flag_negative(cpu, result);
        cpu.clear_state();
    }
    // Branch
    void op_bcc(Cpu& cpu)
    {
        // Unfinished
        switch(cpu.localClock)
        {
            case 0:
                cpu.value = cpu.bus.read(cpu.PC++);
                if (cpu.P & 0x01 == 0x01) 
                {
                    cpu.clear_state();
                }
            case 1:

            case 2:
            
        }
        
    }
    void op_bcs(Cpu& cpu)
    {

    }
    void op_beq(Cpu& cpu)
    {

    }
    void op_bne(Cpu& cpu)
    {

    }
    void op_bpl(Cpu& cpu)
    {

    }
    void op_bmi(Cpu& cpu)
    {

    }
    void op_bvc(Cpu& cpu)
    {

    }
    void op_bvs(Cpu& cpu)
    {

    }
    // Jump
    void op_jmp(Cpu& cpu)
    {

    }
    void op_jsr(Cpu& cpu)
    {

    }
    void op_rts(Cpu& cpu)
    {

    }
    void op_brk(Cpu& cpu)
    {

    }
    void op_rti(Cpu& cpu)
    {

    }
    // Stack
    void op_pha(Cpu& cpu)
    {
        cpu.bus.write(0x0100 + cpu.SP, cpu.A);
        cpu.SP--;
        cpu.clear_state();
    }
    void op_pla(Cpu& cpu)
    {
        switch(cpu.localClock)
        {
            case 0:
                cpu.SP++;
                break;
            case 1:
                cpu.A = cpu.bus.read(0x0100 + cpu.SP);
                set_flag_zero(cpu, cpu.A);
                set_flag_negative(cpu, cpu.A);
                cpu.clear_state();
                break;
        }
    }
    void op_php(Cpu& cpu)
    {
        cpu.bus.write(0x0100 + cpu.SP, cpu.P | 0b00110000);
        cpu.SP--;
    }
    void op_plp(Cpu& cpu)
    {
        switch(cpu.localClock)
        {
            case 0:
                cpu.SP++;
                break;
            case 1:
                cpu.P |= (cpu.bus.read(0x0100 + cpu.SP) & 0b11001111);
                set_flag_zero(cpu, cpu.A);
                set_flag_negative(cpu, cpu.A);
                cpu.clear_state();
                break;
        }
    }
    void op_txs(Cpu& cpu)
    {
        cpu.SP = cpu.X;
        set_flag_zero(cpu, cpu.SP);
        set_flag_negative(cpu, cpu.SP);
        cpu.clear_state();
    }
    void op_tsx(Cpu& cpu)
    {
        cpu.X = cpu.SP;
        set_flag_zero(cpu, cpu.X);
        set_flag_negative(cpu, cpu.X);
        cpu.clear_state();
    }
    // Flags
    void op_clc(Cpu& cpu)
    {
        set_flag_carry(cpu, false);
        cpu.clear_state();
    }
    void op_sec(Cpu& cpu)
    {
        set_flag_carry(cpu, true);
        cpu.clear_state();
    }
    void op_cli(Cpu& cpu)
    {
        set_flag_interrupt_disable(cpu, false);
        cpu.clear_state();
    }
    void op_sei(Cpu& cpu)
    {
        set_flag_interrupt_disable(cpu, true);
        cpu.clear_state();
    }
    void op_cld(Cpu& cpu)
    {
        set_flag_decimal(cpu, false);
        cpu.clear_state();
    }
    void op_sed(Cpu& cpu)
    {
        set_flag_decimal(cpu, true);
        cpu.clear_state();
    }
    void op_clv(Cpu& cpu)
    {
        set_flag_overflow(cpu, false);
        cpu.clear_state();
    }
    // Other
    void op_nop(Cpu& cpu)
    {
        cpu.clear_state();
    }
}