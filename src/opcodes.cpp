
#include <cstdint>

#include "opcodes.h"
#include "cpu.h"

namespace ops
{
    // OPCODE POINTER TABLE
    const Opcode pointerTable [256] {
    /* 00 */ {mode_imp, op_brk, AddressingMode::IMP, Instruction::BRK},
    /* 01 */ {mode_inx, op_ora, AddressingMode::INX, Instruction::ORA},
    /* 02 */ {mode_imp, op_hlt, AddressingMode::IMP, Instruction::HLT},
    /* 03 */ {mode_inx, op_slo, AddressingMode::INX, Instruction::SLO},
    /* 04 */ {mode_zpg, op_nop_uof, AddressingMode::ZPG, Instruction::NOP},
    /* 05 */ {mode_zpg, op_ora, AddressingMode::ZPG, Instruction::ORA},
    /* 06 */ {mode_zpg, op_asl, AddressingMode::ZPG, Instruction::ASL},
    /* 07 */ {mode_zpg, op_slo, AddressingMode::ZPG, Instruction::SLO},
    /* 08 */ {mode_imp, op_php, AddressingMode::IMP, Instruction::PHP},
    /* 09 */ {mode_imm, op_ora_imm, AddressingMode::IMM, Instruction::ORA},
    /* 0A */ {mode_acc, op_asl_acc, AddressingMode::ACC, Instruction::ASL},
    /* 0B */ {mode_imm, op_anc, AddressingMode::IMM, Instruction::ANC},
    /* 0C */ {mode_abs, op_nop_uof, AddressingMode::ABS, Instruction::NOP},
    /* 0D */ {mode_abs, op_ora, AddressingMode::ABS, Instruction::ORA},
    /* 0E */ {mode_abs, op_asl, AddressingMode::ABS, Instruction::ASL},
    /* 0F */ {mode_abs, op_slo, AddressingMode::ABS, Instruction::SLO},

    /* 10 */ {nullptr,  op_bpl, AddressingMode::REL, Instruction::BPL},
    /* 11 */ {mode_iny, op_ora, AddressingMode::INY, Instruction::ORA},
    /* 12 */ {mode_imp, op_hlt, AddressingMode::IMP, Instruction::HLT},
    /* 13 */ {mode_iny, op_slo, AddressingMode::INY, Instruction::SLO},
    /* 14 */ {mode_zpx, op_nop_uof, AddressingMode::ZPX, Instruction::NOP},
    /* 15 */ {mode_zpx, op_ora, AddressingMode::ZPX, Instruction::ORA},
    /* 16 */ {mode_zpx, op_asl, AddressingMode::ZPX, Instruction::ASL},
    /* 17 */ {mode_zpx, op_slo, AddressingMode::ZPX, Instruction::SLO},
    /* 18 */ {mode_imp, op_clc, AddressingMode::IMP, Instruction::CLC},
    /* 19 */ {mode_aby, op_ora, AddressingMode::ABY, Instruction::ORA},
    /* 1A */ {mode_imp, op_nop, AddressingMode::IMP, Instruction::NOP},
    /* 1B */ {mode_aby, op_slo, AddressingMode::ABY, Instruction::SLO},
    /* 1C */ {mode_abx, op_nop_uof, AddressingMode::ABX, Instruction::NOP},
    /* 1D */ {mode_abx, op_ora, AddressingMode::ABX, Instruction::ORA},
    /* 1E */ {mode_abx, op_asl, AddressingMode::ABX, Instruction::ASL},
    /* 1F */ {mode_abx, op_slo, AddressingMode::ABX, Instruction::SLO},

    /* 20 */ {mode_abs, op_jsr, AddressingMode::UNQ, Instruction::JSR},
    /* 21 */ {mode_inx, op_and, AddressingMode::INX, Instruction::AND},
    /* 22 */ {mode_imp, op_hlt, AddressingMode::IMP, Instruction::HLT},
    /* 23 */ {mode_inx, op_rla, AddressingMode::INX, Instruction::RLA},
    /* 24 */ {mode_zpg, op_bit, AddressingMode::ZPG, Instruction::BIT},
    /* 25 */ {mode_zpg, op_and, AddressingMode::ZPG, Instruction::AND},
    /* 26 */ {mode_zpg, op_rol, AddressingMode::ZPG, Instruction::ROL},
    /* 27 */ {mode_zpg, op_rla, AddressingMode::ZPG, Instruction::RLA},
    /* 28 */ {mode_imp, op_plp, AddressingMode::IMP, Instruction::PLP},
    /* 29 */ {mode_imm, op_and_imm, AddressingMode::IMM, Instruction::AND},
    /* 2A */ {mode_acc, op_rol_acc, AddressingMode::ACC, Instruction::ROL},
    /* 2B */ {mode_imm, op_anc, AddressingMode::IMM, Instruction::ANC},
    /* 2C */ {mode_abs, op_bit, AddressingMode::ABS, Instruction::BIT},
    /* 2D */ {mode_abs, op_and, AddressingMode::ABS, Instruction::AND},
    /* 2E */ {mode_abs, op_rol, AddressingMode::ABS, Instruction::ROL},
    /* 2F */ {mode_abs, op_rla, AddressingMode::ABS, Instruction::RLA},

    /* 30 */ {nullptr,  op_bmi, AddressingMode::REL, Instruction::BMI},
    /* 31 */ {mode_iny, op_and, AddressingMode::INY, Instruction::AND},
    /* 32 */ {mode_imp, op_hlt, AddressingMode::IMP, Instruction::HLT},
    /* 33 */ {mode_iny, op_rla, AddressingMode::INY, Instruction::RLA},
    /* 34 */ {mode_zpx, op_nop_uof, AddressingMode::ZPX, Instruction::NOP},
    /* 35 */ {mode_zpx, op_and, AddressingMode::ZPX, Instruction::AND},
    /* 36 */ {mode_zpx, op_rol, AddressingMode::ZPX, Instruction::ROL},
    /* 37 */ {mode_zpx, op_rla, AddressingMode::ZPX, Instruction::RLA},
    /* 38 */ {mode_imp, op_sec, AddressingMode::IMP, Instruction::SEC},
    /* 39 */ {mode_aby, op_and, AddressingMode::ABY, Instruction::AND},
    /* 3A */ {mode_imp, op_nop, AddressingMode::IMP, Instruction::NOP},
    /* 3B */ {mode_aby, op_rla, AddressingMode::ABY, Instruction::RLA},
    /* 3C */ {mode_abx, op_nop_uof, AddressingMode::ABX, Instruction::NOP},
    /* 3D */ {mode_abx, op_and, AddressingMode::ABX, Instruction::AND},
    /* 3E */ {mode_abx, op_rol, AddressingMode::ABX, Instruction::ROL},
    /* 3F */ {mode_abx, op_rla, AddressingMode::ABX, Instruction::RLA},

    /* 40 */ {mode_imp, op_rti, AddressingMode::IMP, Instruction::RTI},
    /* 41 */ {mode_inx, op_eor, AddressingMode::INX, Instruction::EOR},
    /* 42 */ {mode_imp, op_hlt, AddressingMode::IMP, Instruction::HLT},
    /* 43 */ {mode_inx, op_sre, AddressingMode::INX, Instruction::SRE},
    /* 44 */ {mode_zpg, op_nop_uof, AddressingMode::ZPG, Instruction::NOP},
    /* 45 */ {mode_zpg, op_eor, AddressingMode::ZPG, Instruction::EOR},
    /* 46 */ {mode_zpg, op_lsr, AddressingMode::ZPG, Instruction::LSR},
    /* 47 */ {mode_zpg, op_sre, AddressingMode::ZPG, Instruction::SRE},
    /* 48 */ {mode_imp, op_pha, AddressingMode::IMP, Instruction::PHA},
    /* 49 */ {mode_imm, op_eor_imm, AddressingMode::IMM, Instruction::EOR},
    /* 4A */ {mode_acc, op_lsr_acc, AddressingMode::ACC, Instruction::LSR},
    /* 4B */ {mode_imm, op_asr, AddressingMode::IMM, Instruction::ASR},
    /* 4C */ {mode_abs, op_jmp, AddressingMode::UNQ, Instruction::JMP},
    /* 4D */ {mode_abs, op_eor, AddressingMode::ABS, Instruction::EOR},
    /* 4E */ {mode_abs, op_lsr, AddressingMode::ABS, Instruction::LSR},
    /* 4F */ {mode_abs, op_sre, AddressingMode::ABS, Instruction::SRE},

    /* 50 */ {nullptr,  op_bvc, AddressingMode::REL, Instruction::BVC},
    /* 51 */ {mode_iny, op_eor, AddressingMode::INY, Instruction::EOR},
    /* 52 */ {mode_imp, op_hlt, AddressingMode::IMP, Instruction::HLT},
    /* 53 */ {mode_iny, op_sre, AddressingMode::INY, Instruction::SRE},
    /* 54 */ {mode_zpx, op_nop_uof, AddressingMode::ZPX, Instruction::NOP},
    /* 55 */ {mode_zpx, op_eor, AddressingMode::ZPX, Instruction::EOR},
    /* 56 */ {mode_zpx, op_lsr, AddressingMode::ZPX, Instruction::LSR},
    /* 57 */ {mode_zpx, op_sre, AddressingMode::ZPX, Instruction::SRE},
    /* 58 */ {mode_imp, op_cli, AddressingMode::IMP, Instruction::CLI},
    /* 59 */ {mode_aby, op_eor, AddressingMode::ABY, Instruction::EOR},
    /* 5A */ {mode_imp, op_nop, AddressingMode::IMP, Instruction::NOP},
    /* 5B */ {mode_aby, op_sre, AddressingMode::ABY, Instruction::SRE},
    /* 5C */ {mode_abx, op_nop_uof, AddressingMode::ABX, Instruction::NOP},
    /* 5D */ {mode_abx, op_eor, AddressingMode::ABX, Instruction::EOR},
    /* 5E */ {mode_abx, op_lsr, AddressingMode::ABX, Instruction::LSR},
    /* 5F */ {mode_abx, op_sre, AddressingMode::ABX, Instruction::SRE},

    /* 60 */ {mode_imp, op_rts, AddressingMode::IMP, Instruction::RTS},
    /* 61 */ {mode_inx, op_adc, AddressingMode::INX, Instruction::ADC},
    /* 62 */ {mode_imp, op_hlt, AddressingMode::IMP, Instruction::HLT},
    /* 63 */ {mode_inx, op_rra, AddressingMode::INX, Instruction::RRA},
    /* 64 */ {mode_zpg, op_nop_uof, AddressingMode::ZPG, Instruction::NOP},
    /* 65 */ {mode_zpg, op_adc, AddressingMode::ZPG, Instruction::ADC},
    /* 66 */ {mode_zpg, op_ror, AddressingMode::ZPG, Instruction::ROR},
    /* 67 */ {mode_zpg, op_rra, AddressingMode::ZPG, Instruction::RRA},
    /* 68 */ {mode_imp, op_pla, AddressingMode::IMP, Instruction::PLA},
    /* 69 */ {mode_imm, op_adc_imm, AddressingMode::IMM, Instruction::ADC},
    /* 6A */ {mode_acc, op_ror_acc, AddressingMode::ACC, Instruction::ROR},
    /* 6B */ {mode_imm, op_arr, AddressingMode::IMM, Instruction::ARR},
    /* 6C */ {nullptr, op_jmp_ind, AddressingMode::UNQ, Instruction::JMP}, // this makes me so sad
    /* 6D */ {mode_abs, op_adc, AddressingMode::ABS, Instruction::ADC},
    /* 6E */ {mode_abs, op_ror, AddressingMode::ABS, Instruction::ROR},
    /* 6F */ {mode_abs, op_rra, AddressingMode::ABS, Instruction::RRA},

    /* 70 */ {nullptr,  op_bvs, AddressingMode::REL, Instruction::BVS},
    /* 71 */ {mode_iny, op_adc, AddressingMode::INY, Instruction::ADC},
    /* 72 */ {mode_imp, op_hlt, AddressingMode::IMP, Instruction::HLT},
    /* 73 */ {mode_iny, op_rra, AddressingMode::INY, Instruction::RRA},
    /* 74 */ {mode_zpx, op_nop_uof, AddressingMode::ZPX, Instruction::NOP},
    /* 75 */ {mode_zpx, op_adc, AddressingMode::ZPX, Instruction::ADC},
    /* 76 */ {mode_zpx, op_ror, AddressingMode::ZPX, Instruction::ROR},
    /* 77 */ {mode_zpx, op_rra, AddressingMode::ZPX, Instruction::RRA},
    /* 78 */ {mode_imp, op_sei, AddressingMode::IMP, Instruction::SEI},
    /* 79 */ {mode_aby, op_adc, AddressingMode::ABY, Instruction::ADC},
    /* 7A */ {mode_imp, op_nop, AddressingMode::IMP, Instruction::NOP},
    /* 7B */ {mode_aby, op_rra, AddressingMode::ABY, Instruction::RRA},
    /* 7C */ {mode_abx, op_nop_uof, AddressingMode::ABX, Instruction::NOP},
    /* 7D */ {mode_abx, op_adc, AddressingMode::ABX, Instruction::ADC},
    /* 7E */ {mode_abx, op_ror, AddressingMode::ABX, Instruction::ROR},
    /* 7F */ {mode_abx, op_rra, AddressingMode::ABX, Instruction::RRA},

    /* 80 */ {mode_imm, op_nop_uof, AddressingMode::IMM, Instruction::NOP},
    /* 81 */ {mode_inx, op_sta, AddressingMode::INX, Instruction::STA},
    /* 82 */ {mode_imm, op_nop_uof, AddressingMode::IMM, Instruction::NOP},
    /* 83 */ {nullptr, nullptr, AddressingMode::IMP, Instruction::NOP},
    /* 84 */ {mode_zpg, op_sty, AddressingMode::ZPG, Instruction::STY},
    /* 85 */ {mode_zpg, op_sta, AddressingMode::ZPG, Instruction::STA},
    /* 86 */ {mode_zpg, op_stx, AddressingMode::ZPG, Instruction::STX},
    /* 87 */ {nullptr, nullptr, AddressingMode::IMP, Instruction::NOP},
    /* 88 */ {mode_imp, op_dey, AddressingMode::IMP, Instruction::DEY},
    /* 89 */ {mode_imm, op_nop_uof, AddressingMode::IMM, Instruction::NOP},
    /* 8A */ {mode_imp, op_txa, AddressingMode::IMP, Instruction::TXA},
    /* 8B */ {nullptr, nullptr, AddressingMode::IMP, Instruction::NOP},
    /* 8C */ {mode_abs, op_sty, AddressingMode::ABS, Instruction::STY},
    /* 8D */ {mode_abs, op_sta, AddressingMode::ABS, Instruction::STA},
    /* 8E */ {mode_abs, op_stx, AddressingMode::ABS, Instruction::STX},
    /* 8F */ {nullptr, nullptr, AddressingMode::IMP, Instruction::NOP},

    /* 90 */ {nullptr,  op_bcc, AddressingMode::REL, Instruction::BCC},
    /* 91 */ {mode_iny, op_sta, AddressingMode::INY, Instruction::STA},
    /* 92 */ {mode_imp, op_hlt, AddressingMode::IMP, Instruction::HLT},
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

    /* A0 */ {mode_imm, op_ldy_imm, AddressingMode::IMM, Instruction::LDY},
    /* A1 */ {mode_inx, op_lda, AddressingMode::INX, Instruction::LDA},
    /* A2 */ {mode_imm, op_ldx_imm, AddressingMode::IMM, Instruction::LDX},
    /* A3 */ {nullptr, nullptr, AddressingMode::IMP, Instruction::NOP},
    /* A4 */ {mode_zpg, op_ldy, AddressingMode::ZPG, Instruction::LDY},
    /* A5 */ {mode_zpg, op_lda, AddressingMode::ZPG, Instruction::LDA},
    /* A6 */ {mode_zpg, op_ldx, AddressingMode::ZPG, Instruction::LDX},
    /* A7 */ {nullptr, nullptr, AddressingMode::IMP, Instruction::NOP},
    /* A8 */ {mode_imp, op_tay, AddressingMode::IMP, Instruction::TAY},
    /* A9 */ {mode_imm, op_lda_imm, AddressingMode::IMM, Instruction::LDA},
    /* AA */ {mode_imp, op_tax, AddressingMode::IMP, Instruction::TAX},
    /* AB */ {nullptr, nullptr, AddressingMode::IMP, Instruction::NOP},
    /* AC */ {mode_abs, op_ldy, AddressingMode::ABS, Instruction::LDY},
    /* AD */ {mode_abs, op_lda, AddressingMode::ABS, Instruction::LDA},
    /* AE */ {mode_abs, op_ldx, AddressingMode::ABS, Instruction::LDX},
    /* AF */ {nullptr, nullptr, AddressingMode::IMP, Instruction::NOP},

    /* B0 */ {nullptr,  op_bcs, AddressingMode::REL, Instruction::BCS},
    /* B1 */ {mode_iny, op_lda, AddressingMode::INY, Instruction::LDA},
    /* B2 */ {mode_imp, op_hlt, AddressingMode::IMP, Instruction::HLT},
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

    /* C0 */ {mode_imm, op_cpy_imm, AddressingMode::IMM, Instruction::CPY},
    /* C1 */ {mode_inx, op_cmp, AddressingMode::INX, Instruction::CMP},
    /* C2 */ {mode_imm, op_nop_uof, AddressingMode::IMM, Instruction::NOP},
    /* C3 */ {nullptr, nullptr, AddressingMode::IMP, Instruction::NOP},
    /* C4 */ {mode_zpg, op_cpy, AddressingMode::ZPG, Instruction::CPY},
    /* C5 */ {mode_zpg, op_cmp, AddressingMode::ZPG, Instruction::CMP},
    /* C6 */ {mode_zpg, op_dec, AddressingMode::ZPG, Instruction::DEC},
    /* C7 */ {nullptr, nullptr, AddressingMode::IMP, Instruction::NOP},
    /* C8 */ {mode_imp, op_iny, AddressingMode::IMP, Instruction::INY},
    /* C9 */ {mode_imm, op_cmp_imm, AddressingMode::IMM, Instruction::CMP},
    /* CA */ {mode_imp, op_dex, AddressingMode::IMP, Instruction::DEX},
    /* CB */ {nullptr, nullptr, AddressingMode::IMP, Instruction::NOP},
    /* CC */ {mode_abs, op_cpy, AddressingMode::ABS, Instruction::CPY},
    /* CD */ {mode_abs, op_cmp, AddressingMode::ABS, Instruction::CMP},
    /* CE */ {mode_abs, op_dec, AddressingMode::ABS, Instruction::DEC},
    /* CF */ {nullptr, nullptr, AddressingMode::IMP, Instruction::NOP},

    /* D0 */ {nullptr,  op_bne, AddressingMode::REL, Instruction::BNE},
    /* D1 */ {mode_iny, op_cmp, AddressingMode::INY, Instruction::CMP},
    /* D2 */ {mode_imp, op_hlt, AddressingMode::IMP, Instruction::HLT},
    /* D3 */ {nullptr, nullptr, AddressingMode::IMP, Instruction::NOP},
    /* D4 */ {mode_zpx, op_nop_uof, AddressingMode::ZPX, Instruction::NOP},
    /* D5 */ {mode_zpx, op_cmp, AddressingMode::ZPX, Instruction::CMP},
    /* D6 */ {mode_zpx, op_dec, AddressingMode::ZPX, Instruction::DEC},
    /* D7 */ {nullptr, nullptr, AddressingMode::IMP, Instruction::NOP},
    /* D8 */ {mode_imp, op_cld, AddressingMode::IMP, Instruction::CLD},
    /* D9 */ {mode_aby, op_cmp, AddressingMode::ABY, Instruction::CMP},
    /* DA */ {mode_imp, op_nop, AddressingMode::IMP, Instruction::NOP},
    /* DB */ {nullptr, nullptr, AddressingMode::IMP, Instruction::NOP},
    /* DC */ {mode_abx, op_nop_uof, AddressingMode::ABX, Instruction::NOP},
    /* DD */ {mode_abx, op_cmp, AddressingMode::ABX, Instruction::CMP},
    /* DE */ {mode_abx, op_dec, AddressingMode::ABX, Instruction::DEC},
    /* DF */ {nullptr, nullptr, AddressingMode::IMP, Instruction::NOP},

    /* E0 */ {mode_imm, op_cpx_imm, AddressingMode::IMM, Instruction::CPX},
    /* E1 */ {mode_inx, op_sbc, AddressingMode::INX, Instruction::SBC},
    /* E2 */ {mode_imm, op_nop_uof, AddressingMode::IMM, Instruction::NOP},
    /* E3 */ {nullptr, nullptr, AddressingMode::IMP, Instruction::NOP},
    /* E4 */ {mode_zpg, op_cpx, AddressingMode::ZPG, Instruction::CPX},
    /* E5 */ {mode_zpg, op_sbc, AddressingMode::ZPG, Instruction::SBC},
    /* E6 */ {mode_zpg, op_inc, AddressingMode::ZPG, Instruction::INC},
    /* E7 */ {nullptr, nullptr, AddressingMode::IMP, Instruction::NOP},
    /* E8 */ {mode_imp, op_inx, AddressingMode::IMP, Instruction::INX},
    /* E9 */ {mode_imm, op_sbc_imm, AddressingMode::IMM, Instruction::SBC},
    /* EA */ {mode_imp, op_nop, AddressingMode::IMP, Instruction::NOP},
    /* EB */ {nullptr, nullptr, AddressingMode::IMP, Instruction::NOP},
    /* EC */ {mode_abs, op_cpx, AddressingMode::ABS, Instruction::CPX},
    /* ED */ {mode_abs, op_sbc, AddressingMode::ABS, Instruction::SBC},
    /* EE */ {mode_abs, op_inc, AddressingMode::ABS, Instruction::INC},
    /* EF */ {nullptr, nullptr, AddressingMode::IMP, Instruction::NOP},

    /* F0 */ {nullptr,  op_beq, AddressingMode::REL, Instruction::BEQ},
    /* F1 */ {mode_iny, op_sbc, AddressingMode::INY, Instruction::SBC},
    /* F2 */ {mode_imp, op_hlt, AddressingMode::IMP, Instruction::HLT},
    /* F3 */ {nullptr, nullptr, AddressingMode::IMP, Instruction::NOP},
    /* F4 */ {mode_zpx, op_nop_uof, AddressingMode::ZPX, Instruction::NOP},
    /* F5 */ {mode_zpx, op_sbc, AddressingMode::ZPX, Instruction::SBC},
    /* F6 */ {mode_zpx, op_inc, AddressingMode::ZPX, Instruction::INC},
    /* F7 */ {nullptr, nullptr, AddressingMode::IMP, Instruction::NOP},
    /* F8 */ {mode_imp, op_sed, AddressingMode::IMP, Instruction::SED},
    /* F9 */ {mode_aby, op_sbc, AddressingMode::ABY, Instruction::SBC},
    /* FA */ {mode_imp, op_nop, AddressingMode::IMP, Instruction::NOP},
    /* FB */ {nullptr, nullptr, AddressingMode::IMP, Instruction::NOP},
    /* FC */ {mode_abx, op_nop_uof, AddressingMode::ABX, Instruction::NOP},
    /* FD */ {mode_abx, op_sbc, AddressingMode::ABX, Instruction::SBC},
    /* FE */ {mode_abx, op_inc, AddressingMode::ABX, Instruction::INC},
    /* FF */ {nullptr, nullptr, AddressingMode::IMP, Instruction::NOP}
    };

    // opcode enum to string for debugging
    std::string op_to_string(Instruction op)
    {
        switch(op)
        {
            case Instruction::ADC: return "ADC";
            case Instruction::AND: return "AND";
            case Instruction::ASL: return "ASL";
            case Instruction::BCC: return "BCC";
            case Instruction::BCS: return "BCS";
            case Instruction::BEQ: return "BEQ";
            case Instruction::BIT: return "BIT";
            case Instruction::BMI: return "BMI";
            case Instruction::BNE: return "BNE";
            case Instruction::BPL: return "BPL";
            case Instruction::BRK: return "BRK";
            case Instruction::BVC: return "BVC";
            case Instruction::BVS: return "BVS";
            case Instruction::CLC: return "CLC";
            case Instruction::CLD: return "CLD";
            case Instruction::CLI: return "CLI";
            case Instruction::CLV: return "CLV";
            case Instruction::CMP: return "CMP";
            case Instruction::CPX: return "CPX";
            case Instruction::CPY: return "CPY";
            case Instruction::DEC: return "DEC";
            case Instruction::DEX: return "DEX";
            case Instruction::DEY: return "DEY";
            case Instruction::EOR: return "EOR";
            case Instruction::INC: return "INC";
            case Instruction::INX: return "INX";
            case Instruction::INY: return "INY";
            case Instruction::JMP: return "JMP";
            case Instruction::JSR: return "JSR";
            case Instruction::LDA: return "LDA";
            case Instruction::LDX: return "LDX";
            case Instruction::LDY: return "LDY";
            case Instruction::LSR: return "LSR";
            case Instruction::NOP: return "NOP";
            case Instruction::ORA: return "ORA";
            case Instruction::PHA: return "PHA";
            case Instruction::PHP: return "PHP";
            case Instruction::PLA: return "PLA";
            case Instruction::PLP: return "PLP";
            case Instruction::ROL: return "ROL";
            case Instruction::ROR: return "ROR";
            case Instruction::RTI: return "RTI";
            case Instruction::RTS: return "RTS";
            case Instruction::SBC: return "SBC";
            case Instruction::SEC: return "SEC";
            case Instruction::SED: return "SED";
            case Instruction::SEI: return "SEI";
            case Instruction::STA: return "STA";
            case Instruction::STX: return "STX";
            case Instruction::STY: return "STY";
            case Instruction::TAX: return "TAX";
            case Instruction::TAY: return "TAY";
            case Instruction::TSX: return "TSX";
            case Instruction::TXA: return "TXA";
            case Instruction::TXS: return "TXS";
            case Instruction::TYA: return "TYA";
        }
        return "UNKNOWN";
    }

    bool is_read_instruction(Instruction op)
    {
        switch (op)
        {
            case Instruction::LDA:
            case Instruction::LDX:
            case Instruction::LDY:
            case Instruction::EOR:
            case Instruction::AND:
            case Instruction::ORA:
            case Instruction::ADC:
            case Instruction::SBC:
            case Instruction::CMP:
            case Instruction::BIT:
            //case Instruction::LAX:
            //case Instruction::LAE:
            //case Instruction::SHS:
            case Instruction::NOP:
                return true;
        }
        return false;
    }

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
    }
    void mode_acc(Cpu& cpu)
    {
        // Value isn't used in any way so it's thrown away.
        // On hardware, theres a read here, so it needs to be read here for the data bus.
        cpu.bus.read(cpu.PC);
        cpu.addressReady = true;
    }
    void mode_imm(Cpu& cpu)
    {
        cpu.value = cpu.bus.read(cpu.PC);
        cpu.PC++;
        cpu.addressReady = true;
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
                break;
            case 1:
                cpu.bus.read(cpu.address); // dummy read
                cpu.address = (cpu.address + cpu.X) & 0xFF;
                cpu.localClock = 0;
                cpu.addressReady = true;
                return;
        }
        cpu.localClock++;
    }
    void mode_zpy(Cpu& cpu)
    {
        switch(cpu.localClock)
        {
            case 0:
                cpu.address = cpu.bus.read(cpu.PC);
                cpu.PC++;
                break;
            case 1:
                cpu.bus.read(cpu.address); // dummy read
                cpu.address = (cpu.address + cpu.Y) & 0xFF;
                cpu.localClock = 0;
                cpu.addressReady = true;
                return;
        }
        cpu.localClock++;
    }
    void mode_abs(Cpu& cpu)
    {
        switch(cpu.localClock)
        {
            case 0:
                cpu.address = cpu.bus.read(cpu.PC++);
                break;
            case 1:
                cpu.address += (cpu.bus.read(cpu.PC++) << 8);
                cpu.localClock = 0;
                cpu.addressReady = true;
                return;
        }
        cpu.localClock++;
    }
    void mode_abx(Cpu& cpu)
    {
        switch(cpu.localClock)
        {
            case 0:
                cpu.address = cpu.bus.read(cpu.PC++);
                break;
            case 1: {
                uint8_t lowByte = static_cast<uint8_t>(cpu.address);
                uint8_t wrap = lowByte+cpu.X;
                cpu.address = wrap;
                cpu.address |= (cpu.bus.read(cpu.PC++) << 8);
                cpu.wrapped = (wrap < lowByte);
                if (!cpu.wrapped && is_read_instruction(pointerTable[cpu.opcode].op)) { // if it doesn't wrap (no extra cycle)
                    cpu.localClock = 0;
                    cpu.addressReady = true;
                    return;
                }
                break; }
            case 2:
                cpu.bus.read(cpu.address); // dummy read
                if (cpu.wrapped) {cpu.address += 0x100;}
                cpu.localClock = 0;
                cpu.addressReady = true;
                return;
        }
        cpu.localClock++;
    }
    void mode_aby(Cpu& cpu)
    {
        switch(cpu.localClock)
        {
            case 0:
                cpu.address = cpu.bus.read(cpu.PC++);
                break;
            case 1: {
                uint8_t lowByte = static_cast<uint8_t>(cpu.address);
                uint8_t wrap = lowByte+cpu.Y;
                cpu.address = wrap;
                cpu.address += (cpu.bus.read(cpu.PC++) << 8);
                cpu.wrapped = (wrap < lowByte);
                if (!cpu.wrapped && is_read_instruction(pointerTable[cpu.opcode].op)) { // if it doesn't wrap (no extra cycle)
                    cpu.localClock = 0;
                    cpu.addressReady = true;
                    return;
                }
                break; }
            case 2:
                cpu.bus.read(cpu.address); // dummy read
                if (cpu.wrapped) {cpu.address += 0x100;}
                cpu.localClock = 0;
                cpu.addressReady = true;
                return;
        }
        cpu.localClock++;
    }
    void mode_ind(Cpu& cpu)
    {
        switch(cpu.localClock)
        {
            case 0:
                cpu.address = cpu.bus.read(cpu.PC);
                cpu.PC++;
                break;
            case 1:
                cpu.address += (cpu.bus.read(cpu.PC) << 8);
                cpu.PC++;
                break;
            case 2:
                cpu.temp8 = cpu.bus.read(cpu.address);
                break;
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
                return;
        }
        cpu.localClock++;
    }
    void mode_inx(Cpu& cpu)
    {
        switch(cpu.localClock)
        {
            case 0:
                cpu.temp8 = cpu.bus.read(cpu.PC);
                cpu.PC++;
                break;
            case 1:
                cpu.bus.read(cpu.temp8);
                cpu.temp8 = static_cast<uint8_t>(cpu.temp8 + cpu.X);
                break;
            case 2:
                cpu.address = cpu.bus.read(cpu.temp8);
                break;
            case 3:
                cpu.address += (cpu.bus.read(static_cast<uint8_t>(cpu.temp8 + 1)) << 8);
                cpu.localClock = 0;
                cpu.addressReady = true;
                return;
        }
        cpu.localClock++;
    }
    void mode_iny(Cpu& cpu)
    {
        switch(cpu.localClock)
        {
            case 0:
                cpu.temp8 = cpu.bus.read(cpu.PC);
                cpu.PC++;
                break;
            case 1:
                cpu.address = cpu.bus.read(cpu.temp8);
                break;
            case 2: {
                uint8_t lowByte = static_cast<uint8_t>(cpu.address);
                uint8_t wrap = lowByte+cpu.Y;
                cpu.address = wrap;
                cpu.address += (cpu.bus.read(static_cast<uint8_t>(cpu.temp8 + 1)) << 8);
                cpu.wrapped = (wrap < lowByte);
                if (!cpu.wrapped && is_read_instruction(pointerTable[cpu.opcode].op)) { // if it doesn't wrap (no extra cycle)
                    cpu.localClock = 0;
                    cpu.addressReady = true;
                    return;
                }
                break; }
            case 3:
                cpu.bus.read(cpu.address); // dummy read
                if (cpu.wrapped) {cpu.address += 0x100;}
                cpu.localClock = 0;
                cpu.addressReady = true;
                return;
        }
        cpu.localClock++;
    }

    // OPCODE FUNCTIONS
    // Access
    void op_lda(Cpu& cpu)
    {
        cpu.A = cpu.bus.read(cpu.address);
        set_flag_zero(cpu, cpu.A);
        set_flag_negative(cpu, cpu.A);
        cpu.clear_state();
        cpu.poll_nmi();
    }
    void op_lda_imm(Cpu& cpu)
    {
        cpu.A = cpu.value;
        set_flag_zero(cpu, cpu.A);
        set_flag_negative(cpu, cpu.A);
        cpu.clear_state();
        cpu.poll_nmi();
    }
    void op_sta(Cpu& cpu)
    {
        cpu.bus.write(cpu.address, cpu.A);
        cpu.clear_state();
        cpu.poll_nmi();
    }
    void op_ldx(Cpu& cpu)
    {
        cpu.X = cpu.bus.read(cpu.address);
        set_flag_zero(cpu, cpu.X);
        set_flag_negative(cpu, cpu.X);
        cpu.clear_state();
        cpu.poll_nmi();
    }
    void op_ldx_imm(Cpu& cpu)
    {
        cpu.X = cpu.value;
        set_flag_zero(cpu, cpu.X);
        set_flag_negative(cpu, cpu.X);
        cpu.clear_state();
        cpu.poll_nmi();
    }
    void op_stx(Cpu& cpu)
    {
        cpu.bus.write(cpu.address, cpu.X);
        cpu.clear_state();
        cpu.poll_nmi();
    }
    void op_ldy(Cpu& cpu)
    {
        cpu.Y = cpu.bus.read(cpu.address);
        set_flag_zero(cpu, cpu.Y);
        set_flag_negative(cpu, cpu.Y);
        cpu.clear_state();
        cpu.poll_nmi();
    }
    void op_ldy_imm(Cpu& cpu)
    {
        cpu.Y = cpu.value;
        set_flag_zero(cpu, cpu.Y);
        set_flag_negative(cpu, cpu.Y);
        cpu.clear_state();
        cpu.poll_nmi();
    }
    void op_sty(Cpu& cpu)
    {
        cpu.bus.write(cpu.address, cpu.Y);
        cpu.clear_state();
        cpu.poll_nmi();
    }
    // Transfer
    void op_tax(Cpu& cpu)
    {
        cpu.X = cpu.A;
        set_flag_zero(cpu, cpu.X);
        set_flag_negative(cpu, cpu.X);
        cpu.clear_state();
        cpu.poll_nmi();
    }
    void op_txa(Cpu& cpu)
    {
        cpu.A = cpu.X;
        set_flag_zero(cpu, cpu.A);
        set_flag_negative(cpu, cpu.A);
        cpu.clear_state();
        cpu.poll_nmi();
    }
    void op_tay(Cpu& cpu)
    {
        cpu.Y = cpu.A;
        set_flag_zero(cpu, cpu.Y);
        set_flag_negative(cpu, cpu.Y);
        cpu.clear_state();
        cpu.poll_nmi();
    }
    void op_tya(Cpu& cpu)
    {
        cpu.A = cpu.Y;
        set_flag_zero(cpu, cpu.A);
        set_flag_negative(cpu, cpu.A);
        cpu.clear_state();
        cpu.poll_nmi();
    }
    // Arithmetic
    void op_adc(Cpu& cpu)
    {
        cpu.value = cpu.bus.read(cpu.address);
        uint16_t result = cpu.A + cpu.value + (cpu.P & 0x01);
        set_flag_carry(cpu, result > 0xFF);
        set_flag_zero(cpu, result);
        set_flag_overflow(cpu, ((result ^ cpu.A) & (result ^ cpu.value) & 0x80) == 0x80);
        set_flag_negative(cpu, result);
        cpu.A = (result % 256);
        cpu.clear_state();
        cpu.poll_nmi();
    }
    void op_adc_imm(Cpu& cpu)
    {
        uint16_t result = cpu.A + cpu.value + (cpu.P & 0x01);
        set_flag_carry(cpu, result > 0xFF);
        set_flag_zero(cpu, result);
        set_flag_overflow(cpu, ((result ^ cpu.A) & (result ^ cpu.value) & 0x80) == 0x80);
        set_flag_negative(cpu, result);
        cpu.A = (result % 256);
        cpu.clear_state();
        cpu.poll_nmi();
    }
    void op_sbc(Cpu& cpu)
    {
        cpu.value = cpu.bus.read(cpu.address);
        uint16_t result = cpu.A - cpu.value - (~cpu.P & 0x01);
        set_flag_carry(cpu, result <= 0xFF);
        set_flag_zero(cpu, result);
        set_flag_overflow(cpu, ((result ^ cpu.A) & (result ^ ~cpu.value) & 0x80) == 0x80);
        set_flag_negative(cpu, result);
        cpu.A = (result % 256);
        cpu.clear_state();
        cpu.poll_nmi();
    }
    void op_sbc_imm(Cpu& cpu)
    {
        uint16_t result = cpu.A - cpu.value - (~cpu.P & 0x01);
        set_flag_carry(cpu, result <= 0xFF);
        set_flag_zero(cpu, result);
        set_flag_overflow(cpu, ((result ^ cpu.A) & (result ^ ~cpu.value) & 0x80) == 0x80);
        set_flag_negative(cpu, result);
        cpu.A = (result % 256);
        cpu.clear_state();
        cpu.poll_nmi();
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
                cpu.poll_nmi();
                return;
        }
        cpu.localClock++;
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
                cpu.poll_nmi();
                return;
        }
        cpu.localClock++;
    }
    void op_inx(Cpu& cpu)
    {
        cpu.X++;
        set_flag_zero(cpu, cpu.X);
        set_flag_negative(cpu, cpu.X);
        cpu.clear_state();
        cpu.poll_nmi();
    }
    void op_dex(Cpu& cpu)
    {
        cpu.X--;
        set_flag_zero(cpu, cpu.X);
        set_flag_negative(cpu, cpu.X);
        cpu.clear_state();
        cpu.poll_nmi();
    }
    void op_iny(Cpu& cpu)
    {
        cpu.Y++;
        set_flag_zero(cpu, cpu.Y);
        set_flag_negative(cpu, cpu.Y);
        cpu.clear_state();
        cpu.poll_nmi();
    }
    void op_dey(Cpu& cpu)
    {
        cpu.Y--;
        set_flag_zero(cpu, cpu.Y);
        set_flag_negative(cpu, cpu.Y);
        cpu.clear_state();
        cpu.poll_nmi();
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
                cpu.poll_nmi();
                return;
        }
        cpu.localClock++;
    }
    void op_asl_acc(Cpu& cpu)
    {
        set_flag_carry(cpu, (cpu.A & 0x80) == 0x80);
        cpu.A<<=1;
        set_flag_zero(cpu, cpu.A);
        set_flag_negative(cpu, cpu.A);
        cpu.clear_state();
        cpu.poll_nmi();
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
                set_flag_negative(cpu, 0);
                break;
            case 2:
                cpu.bus.write(cpu.address, cpu.value);
                cpu.clear_state();
                cpu.poll_nmi();
                return;
        }
        cpu.localClock++;
    }
    void op_lsr_acc(Cpu& cpu)
    {
        set_flag_carry(cpu, (cpu.A & 0x01) == 0x01);
        cpu.A>>=1;
        set_flag_zero(cpu, cpu.A);
        set_flag_negative(cpu, 0);
        cpu.clear_state();
        cpu.poll_nmi();
    }
    void op_rol(Cpu& cpu)
    {
        switch(cpu.localClock)
        {
            case 0:
                cpu.value = cpu.bus.read(cpu.address);
                break;
            case 1: {
                uint8_t oldCarry = cpu.P & 0x01;
                cpu.bus.write(cpu.address, cpu.value);
                set_flag_carry(cpu, ((cpu.value & 0b10000000) == 0b10000000));
                cpu.value<<=1;
                cpu.value |= oldCarry;
                set_flag_zero(cpu, cpu.value);
                set_flag_negative(cpu, cpu.value);
                break; }
            case 2:
                cpu.bus.write(cpu.address, cpu.value);
                cpu.clear_state();
                cpu.poll_nmi();
                return;
        }
        cpu.localClock++;
    }
    void op_rol_acc(Cpu& cpu)
    {
        uint8_t oldCarry = cpu.P & 0x01;
        set_flag_carry(cpu, (cpu.A & 0x80) == 0x80);
        cpu.A<<=1;
        cpu.A |= oldCarry;
        set_flag_zero(cpu, cpu.A);
        set_flag_negative(cpu, cpu.A);
        cpu.clear_state();
        cpu.poll_nmi();
    }
    void op_ror(Cpu& cpu)
    {
        switch(cpu.localClock)
        {
            case 0:
                cpu.value = cpu.bus.read(cpu.address);
                break;
            case 1: {
                uint8_t oldCarry = cpu.P << 7;
                cpu.bus.write(cpu.address, cpu.value);
                set_flag_carry(cpu, ((cpu.value & 0b00000001) == 0b00000001));
                cpu.value>>=1;
                cpu.value |= oldCarry;
                set_flag_zero(cpu, cpu.value);
                set_flag_negative(cpu, cpu.value);
                break; }
            case 2:
                cpu.bus.write(cpu.address, cpu.value);
                cpu.clear_state();
                cpu.poll_nmi();
                return;
        }
        cpu.localClock++;
    }
    void op_ror_acc(Cpu& cpu)
    {
        uint8_t oldCarry = cpu.P << 7;
        set_flag_carry(cpu, (cpu.A & 0x01) == 0x01);
        cpu.A>>=1;
        cpu.A |= oldCarry;
        set_flag_zero(cpu, cpu.A);
        set_flag_negative(cpu, cpu.A);
        cpu.clear_state();
        cpu.poll_nmi();
    }
    // Bitwise
    void op_and(Cpu& cpu)
    {
        cpu.A &= cpu.bus.read(cpu.address);
        set_flag_zero(cpu, cpu.A);
        set_flag_negative(cpu, cpu.A);
        cpu.clear_state();
        cpu.poll_nmi();
    }
    void op_and_imm(Cpu& cpu)
    {
        cpu.A &= cpu.value;
        set_flag_zero(cpu, cpu.A);
        set_flag_negative(cpu, cpu.A);
        cpu.clear_state();
        cpu.poll_nmi();
    }
    void op_ora(Cpu& cpu)
    {
        cpu.A |= cpu.bus.read(cpu.address);
        set_flag_zero(cpu, cpu.A);
        set_flag_negative(cpu, cpu.A);
        cpu.clear_state();
        cpu.poll_nmi();
    }
    void op_ora_imm(Cpu& cpu)
    {
        cpu.A |= cpu.value;
        set_flag_zero(cpu, cpu.A);
        set_flag_negative(cpu, cpu.A);
        cpu.clear_state();
        cpu.poll_nmi();
    }
    void op_eor(Cpu& cpu)
    {
        cpu.A ^= cpu.bus.read(cpu.address);
        set_flag_zero(cpu, cpu.A);
        set_flag_negative(cpu, cpu.A);
        cpu.clear_state();
        cpu.poll_nmi();
    }
    void op_eor_imm(Cpu& cpu)
    {
        cpu.A ^= cpu.value;
        set_flag_zero(cpu, cpu.A);
        set_flag_negative(cpu, cpu.A);
        cpu.clear_state();
        cpu.poll_nmi();
    }
    void op_bit(Cpu& cpu)
    {
        uint8_t memory = cpu.bus.read(cpu.address);
        uint8_t result = cpu.A & memory;
        set_flag_zero(cpu, result);
        set_flag_overflow(cpu, ((memory & 0b01000000) == 0b01000000));
        set_flag_negative(cpu, memory);
        cpu.clear_state();
        cpu.poll_nmi();
    }
    // Compare
    void op_cmp(Cpu& cpu)
    {
        uint8_t memory = cpu.bus.read(cpu.address);
        set_flag_carry(cpu, cpu.A>=memory);
        set_flag_zero(cpu, cpu.A - memory);
        uint8_t result = (cpu.A - memory);
        set_flag_negative(cpu, result);
        cpu.clear_state();
        cpu.poll_nmi();
    }
    void op_cmp_imm(Cpu& cpu)
    {
        uint8_t memory = cpu.value;
        set_flag_carry(cpu, cpu.A>=memory);
        set_flag_zero(cpu, cpu.A - memory);
        uint8_t result = (cpu.A - memory);
        set_flag_negative(cpu, result);
        cpu.clear_state();
        cpu.poll_nmi();
    }
    void op_cpx(Cpu& cpu)
    {
        uint8_t memory = cpu.bus.read(cpu.address);
        set_flag_carry(cpu, cpu.X>=memory);
        set_flag_zero(cpu, cpu.X - memory);
        uint8_t result = (cpu.X - memory);
        set_flag_negative(cpu, result);
        cpu.clear_state();
        cpu.poll_nmi();
    }
    void op_cpx_imm(Cpu& cpu)
    {
        uint8_t memory = cpu.value;
        set_flag_carry(cpu, cpu.X>=memory);
        set_flag_zero(cpu, cpu.X - memory);
        uint8_t result = (cpu.X - memory);
        set_flag_negative(cpu, result);
        cpu.clear_state();
        cpu.poll_nmi();
    }
    void op_cpy(Cpu& cpu)
    {
        uint8_t memory = cpu.bus.read(cpu.address);
        set_flag_carry(cpu, cpu.Y>=memory);
        set_flag_zero(cpu, cpu.Y - memory);
        uint8_t result = (cpu.Y - memory);
        set_flag_negative(cpu, result);
        cpu.clear_state();
        cpu.poll_nmi();
    }
    void op_cpy_imm(Cpu& cpu)
    {
        uint8_t memory = cpu.value;
        set_flag_carry(cpu, cpu.Y>=memory);
        set_flag_zero(cpu, cpu.Y - memory);
        uint8_t result = (cpu.Y - memory);
        set_flag_negative(cpu, result);
        cpu.clear_state();
        cpu.poll_nmi();
    }
    // Branch
    void op_bcc(Cpu& cpu)
    {
        switch(cpu.localClock)
        {
            case 0:
                cpu.value = cpu.bus.read(cpu.PC++);
                if ((cpu.P & 0x01) == 0x01) 
                {
                    cpu.clear_state();
                    cpu.poll_nmi();
                    return;
                }
                break;
            case 1: {
                int8_t offset = static_cast<int8_t>(cpu.value);
                uint16_t temp = static_cast<uint16_t>(cpu.PC + offset);
                if ((cpu.PC & 0xFF00) == (temp & 0xFF00)) 
                {
                    cpu.PC = temp;
                    cpu.clear_state();
                    cpu.poll_nmi();
                    return;
                }
                cpu.PC = temp;
                break; }
            case 2:
                // Fix PCH
                cpu.clear_state();
                cpu.poll_nmi();
                return;
        }
        cpu.localClock++;
    }
    void op_bcs(Cpu& cpu)
    {
        switch(cpu.localClock)
        {
            case 0:
                cpu.value = cpu.bus.read(cpu.PC++);
                if ((cpu.P & 0x01) == 0x00) 
                {
                    cpu.clear_state();
                    cpu.poll_nmi();
                    return;
                }
                break;
            case 1: {
                int8_t offset = static_cast<int8_t>(cpu.value);
                uint16_t temp = static_cast<uint16_t>(cpu.PC + offset);
                if ((cpu.PC & 0xFF00) == (temp & 0xFF00)) {
                    cpu.PC = temp;
                    cpu.clear_state();
                    cpu.poll_nmi();
                    return;
                }
                cpu.PC = temp;
                break; }
            case 2:
                // Fix PCH
                cpu.clear_state();
                cpu.poll_nmi();
                return;
        }
        cpu.localClock++;
    }
    void op_beq(Cpu& cpu)
    {
        switch(cpu.localClock)
        {
            case 0:
                cpu.value = cpu.bus.read(cpu.PC++);
                if ((cpu.P & 0x02) == 0x00) 
                {
                    cpu.clear_state();
                    cpu.poll_nmi();
                    return;
                }
                break;
            case 1: {
                int8_t offset = static_cast<int8_t>(cpu.value);
                uint16_t temp = static_cast<uint16_t>(cpu.PC + offset);
                if ((cpu.PC & 0xFF00) == (temp & 0xFF00)) {
                    cpu.PC = temp;
                    cpu.clear_state();
                    cpu.poll_nmi();
                    return;
                }
                cpu.PC = temp;
                break; }
            case 2:
                // Fix PCH
                cpu.clear_state();
                cpu.poll_nmi();
                return;
        }
        cpu.localClock++;
    }
    void op_bne(Cpu& cpu)
    {
        switch(cpu.localClock)
        {
            case 0:
                cpu.value = cpu.bus.read(cpu.PC++);
                if ((cpu.P & 0x02) == 0x02) 
                {
                    cpu.clear_state();
                    cpu.poll_nmi();
                    return;
                }
                break;
            case 1: {
                int8_t offset = static_cast<int8_t>(cpu.value);
                uint16_t temp = static_cast<uint16_t>(cpu.PC + offset);
                if ((cpu.PC & 0xFF00) == (temp & 0xFF00)) {
                    cpu.PC = temp;
                    cpu.clear_state();
                    cpu.poll_nmi();
                    return;
                }
                cpu.PC = temp;
                break; }
            case 2:
                // Fix PCH
                cpu.clear_state();
                cpu.poll_nmi();
                return;
        }
        cpu.localClock++;
    }
    void op_bpl(Cpu& cpu)
    {
        switch(cpu.localClock)
        {
            case 0:
                cpu.value = cpu.bus.read(cpu.PC++);
                if ((cpu.P & 0x80) == 0x80) 
                {
                    cpu.clear_state();
                    cpu.poll_nmi();
                    return;
                }
                break;
            case 1: {
                int8_t offset = static_cast<int8_t>(cpu.value);
                uint16_t temp = static_cast<uint16_t>(cpu.PC + offset);
                if ((cpu.PC & 0xFF00) == (temp & 0xFF00)) {
                    cpu.PC = temp;
                    cpu.clear_state();
                    cpu.poll_nmi();
                    return;
                }
                cpu.PC = temp;
                break; }
            case 2:
                // Fix PCH
                cpu.clear_state();
                cpu.poll_nmi();
                return;
        }
        cpu.localClock++;
    }
    void op_bmi(Cpu& cpu)
    {
        switch(cpu.localClock)
        {
            case 0:
                cpu.value = cpu.bus.read(cpu.PC++);
                if ((cpu.P & 0x80) == 0x00) 
                {
                    cpu.clear_state();
                    cpu.poll_nmi();
                    return;
                }
                break;
            case 1: {
                int8_t offset = static_cast<int8_t>(cpu.value);
                uint16_t temp = static_cast<uint16_t>(cpu.PC + offset);
                if ((cpu.PC & 0xFF00) == (temp & 0xFF00)) {
                    cpu.PC = temp;
                    cpu.clear_state();
                    cpu.poll_nmi();
                    return;
                }
                cpu.PC = temp;
                break; }
            case 2:
                // Fix PCH
                cpu.clear_state();
                cpu.poll_nmi();
                return;
        }
        cpu.localClock++;
    }
    void op_bvc(Cpu& cpu)
    {
        switch(cpu.localClock)
        {
            case 0:
                cpu.value = cpu.bus.read(cpu.PC++);
                if ((cpu.P & 0x40) == 0x40) 
                {
                    cpu.clear_state();
                    cpu.poll_nmi();
                    return;
                }
                break;
            case 1: {
                int8_t offset = static_cast<int8_t>(cpu.value);
                uint16_t temp = static_cast<uint16_t>(cpu.PC + offset);
                if ((cpu.PC & 0xFF00) == (temp & 0xFF00)) {
                    cpu.PC = temp;
                    cpu.clear_state();
                    cpu.poll_nmi();
                    return;
                }
                cpu.PC = temp;
                break; }
            case 2:
                // Fix PCH
                cpu.clear_state();
                cpu.poll_nmi();
                return;
        }
        cpu.localClock++;
    }
    void op_bvs(Cpu& cpu)
    {
        switch(cpu.localClock)
        {
            case 0:
                cpu.value = cpu.bus.read(cpu.PC++);
                if ((cpu.P & 0x40) == 0x00) 
                {
                    cpu.clear_state();
                    cpu.poll_nmi();
                    return;
                }
                break;
            case 1: {
                int8_t offset = static_cast<int8_t>(cpu.value);
                uint16_t temp = static_cast<uint16_t>(cpu.PC + offset);
                if ((cpu.PC & 0xFF00) == (temp & 0xFF00)) {
                    cpu.PC = temp;
                    cpu.clear_state();
                    cpu.poll_nmi();
                    return;
                }
                cpu.PC = temp;
                break; }
            case 2:
                // Fix PCH
                cpu.clear_state();
                cpu.poll_nmi();
                return;
        }
        cpu.localClock++;
    }
    // Jump
    void op_jmp(Cpu& cpu)
    {
        switch(cpu.localClock)
        {
            case 0:
                cpu.temp8 = cpu.bus.read(cpu.PC++);
                break;
            case 1:
                cpu.PC = cpu.bus.read(cpu.PC) << 8;
                cpu.PC |= cpu.temp8;
                cpu.clear_state();
                cpu.poll_nmi();
                return;
        }
        cpu.localClock++;
    }
    void op_jmp_ind(Cpu& cpu)
    {
        switch(cpu.localClock)
        {
            case 0:
                cpu.address = cpu.bus.read(cpu.PC++);
                break;
            case 1:
                cpu.address += cpu.bus.read(cpu.PC++) << 8;
                break;
            case 2:
                cpu.temp8 = cpu.bus.read(cpu.address);
                break;
            case 3:
                if ((cpu.address & 0x00FF) == 0x00FF)
                {
                    // can't cross a page so we decrement the page number
                    // when adding one it will go to the next page at address 0x00
                    cpu.address -= 0x0100;
                }
                cpu.PC = cpu.bus.read(cpu.address+1) << 8;
                cpu.PC |= cpu.temp8;
                cpu.clear_state();
                cpu.poll_nmi();
                return;
        }
        cpu.localClock++;
    }
    void op_jsr(Cpu& cpu)
    {
        switch(cpu.localClock)
        {
            case 0:
                cpu.temp8 = cpu.bus.read(cpu.PC++);
                break;
            case 1:
                cpu.bus.read(cpu.PC); // dummy read
                break;
            case 2: {
                uint8_t PCH = static_cast<uint8_t>(cpu.PC >> 8);
                cpu.bus.write(0x100 + cpu.SP--, PCH);
                break; }
            case 3: {
                uint8_t PCL = static_cast<uint8_t>(cpu.PC & 0xFF);
                cpu.bus.write(0x100 + cpu.SP--, PCL);
                break; }
            case 4:
                cpu.PC = static_cast<uint16_t>(cpu.bus.read(cpu.PC)) << 8;
                cpu.PC |= cpu.temp8;
                cpu.clear_state();
                cpu.poll_nmi();
                return;
        }
        cpu.localClock++;
    }
    void op_rts(Cpu& cpu)
    {
        switch(cpu.localClock)
        {
            case 0:
                cpu.bus.read(cpu.PC); // open bus
                break;
            case 1:
                cpu.SP++;
                break;
            case 2:
                cpu.PC = static_cast<uint16_t>(cpu.bus.read(0x100 + cpu.SP++));
                break;
            case 3:
                cpu.PC += static_cast<uint16_t>(cpu.bus.read(0x100 + cpu.SP) << 8);
                break;
            case 4:
                cpu.PC++;
                cpu.clear_state();
                cpu.poll_nmi();
                return;
        }
        cpu.localClock++;
    }
    void op_brk(Cpu& cpu)
    {
        switch(cpu.localClock)
        {
            case 0:
                cpu.bus.read(cpu.PC); // open bus
                cpu.PC++;
                break;
            case 1: {
                uint8_t PCH = static_cast<uint8_t>(cpu.PC >> 8);
                cpu.bus.write(0x100 + cpu.SP--, PCH);
                break; }
            case 2: {
                uint8_t PCL = static_cast<uint8_t>(cpu.PC);
                cpu.bus.write(0x100 + cpu.SP--, PCL);
                break; }
            case 3:
                cpu.bus.write(0x100 + cpu.SP--, cpu.P | 0b00110000);
                set_flag_interrupt_disable(cpu, true);
                break;
            case 4:
                cpu.PC = static_cast<uint16_t>(cpu.bus.read(0xFFFE));
                break;
            case 5:
                cpu.PC += static_cast<uint16_t>(cpu.bus.read(0xFFFF)) << 8;
                cpu.clear_state();
                cpu.poll_nmi();
                return;
        }
        cpu.localClock++;
    }
    void op_rti(Cpu& cpu)
    {
        switch(cpu.localClock)
        {
            case 0:
                cpu.bus.read(cpu.PC); // open bus
                break;
            case 1:
                cpu.bus.read(0x0100 + cpu.SP); // dummy read
                cpu.SP++;
                break;
            case 2: {
                uint8_t pulled = cpu.bus.read(0x0100 + cpu.SP++);
                cpu.P = (pulled & 0b11001111) | (cpu.P & 0b00110000);
                break; }
            case 3:
                cpu.PC = static_cast<uint16_t>(cpu.bus.read(0x100 + cpu.SP++));
                break;
            case 4:
                cpu.PC += static_cast<uint16_t>(cpu.bus.read(0x100 + cpu.SP) << 8);
                cpu.clear_state();
                cpu.poll_nmi();
                return;
        }
        cpu.localClock++;
    }
    // Stack
    void op_pha(Cpu& cpu)
    {
        switch(cpu.localClock)
        {
            case 0:
                cpu.bus.read(cpu.PC); // dummy read
                break;
            case 1:
                cpu.bus.write(0x0100 + cpu.SP--, cpu.A);
                cpu.clear_state();
                cpu.poll_nmi();
                return;
        }
        cpu.localClock++;
    }
    void op_pla(Cpu& cpu)
    {
        switch(cpu.localClock)
        {
            case 0:
                cpu.bus.read(cpu.PC); // dummy read
                break;
            case 1:
                cpu.SP++;
                break;
            case 2:
                cpu.A = cpu.bus.read(0x0100 + cpu.SP);
                set_flag_zero(cpu, cpu.A);
                set_flag_negative(cpu, cpu.A);
                cpu.clear_state();
                cpu.poll_nmi();
                return;
        }
        cpu.localClock++;
    }
    void op_php(Cpu& cpu)
    {
        switch(cpu.localClock)
        {
            case 0:
                cpu.bus.read(cpu.PC); // dummy read
                break;
            case 1:
                cpu.bus.write(0x0100 + cpu.SP--, cpu.P | 0b00110000);
                cpu.clear_state();
                cpu.poll_nmi();
                return;
        }
        cpu.localClock++;
    }
    void op_plp(Cpu& cpu)
    {
        switch(cpu.localClock)
        {
            case 0:
                cpu.bus.read(cpu.PC); // dummy read
                break;
            case 1:
                cpu.SP++;
                break;
            case 2:
                uint8_t pulled = cpu.bus.read(0x0100 + cpu.SP);
                cpu.P = (pulled & 0b11001111) | (cpu.P & 0b00110000);
                cpu.clear_state();
                cpu.poll_nmi();
                return;
        }
        cpu.localClock++;
    }
    void op_txs(Cpu& cpu)
    {
        cpu.SP = cpu.X;
        cpu.clear_state();
        cpu.poll_nmi();
    }
    void op_tsx(Cpu& cpu)
    {
        cpu.X = cpu.SP;
        set_flag_zero(cpu, cpu.X);
        set_flag_negative(cpu, cpu.X);
        cpu.clear_state();
        cpu.poll_nmi();
    }
    // Flags
    void op_clc(Cpu& cpu)
    {
        set_flag_carry(cpu, false);
        cpu.clear_state();
        cpu.poll_nmi();
    }
    void op_sec(Cpu& cpu)
    {
        set_flag_carry(cpu, true);
        cpu.clear_state();
        cpu.poll_nmi();
    }
    void op_cli(Cpu& cpu)
    {
        set_flag_interrupt_disable(cpu, false);
        cpu.clear_state();
        cpu.poll_nmi();
    }
    void op_sei(Cpu& cpu)
    {
        set_flag_interrupt_disable(cpu, true);
        cpu.clear_state();
        cpu.poll_nmi();
    }
    void op_cld(Cpu& cpu)
    {
        set_flag_decimal(cpu, false);
        cpu.clear_state();
        cpu.poll_nmi();
    }
    void op_sed(Cpu& cpu)
    {
        set_flag_decimal(cpu, true);
        cpu.clear_state();
        cpu.poll_nmi();
    }
    void op_clv(Cpu& cpu)
    {
        set_flag_overflow(cpu, false);
        cpu.clear_state();
        cpu.poll_nmi();
    }
    // Other
    void op_nop(Cpu& cpu)
    {
        cpu.clear_state();
        cpu.poll_nmi();
    }
    // Unofficial
    void op_nop_uof(Cpu& cpu)
    {
        cpu.bus.read(cpu.address);
        cpu.clear_state();
        cpu.poll_nmi();
    }
    void op_hlt(Cpu& cpu)
    {
        // Freezes the cpu indefinitely
        cpu.hlt_triggered = true;
    }
    void op_slo(Cpu& cpu)
    {
        switch(cpu.localClock)
        {
            case 0:
                cpu.value = cpu.bus.read(cpu.address);
                break;
            case 1:
                // ASL
                cpu.bus.write(cpu.address, cpu.value);
                set_flag_carry(cpu, ((cpu.value & 0b10000000) == 0b10000000));
                cpu.value<<=1;
                break;
            case 2:
                cpu.bus.write(cpu.address, cpu.value);
                // ORA
                cpu.A |= cpu.value;
                set_flag_zero(cpu, cpu.A);
                set_flag_negative(cpu, cpu.A);
                cpu.clear_state();
                cpu.poll_nmi();
                return;
        }
        cpu.localClock++;
    }
    void op_anc(Cpu& cpu)
    {
        cpu.A &= cpu.value;
        set_flag_zero(cpu, cpu.A);
        set_flag_negative(cpu, cpu.A);
        set_flag_carry(cpu, ((cpu.A & 0xF0) == 0xF0));
        cpu.clear_state();
        cpu.poll_nmi();
    }
    void op_rla(Cpu& cpu)
    {
        switch(cpu.localClock)
        {
            case 0:
                cpu.value = cpu.bus.read(cpu.address);
                break;
            case 1: {
                // ROL
                uint8_t oldCarry = cpu.P & 0x01;
                cpu.bus.write(cpu.address, cpu.value); // dummy write
                set_flag_carry(cpu, ((cpu.value & 0b10000000) == 0b10000000));
                cpu.value<<=1;
                cpu.value |= oldCarry;
                break; }
            case 2:
                cpu.bus.write(cpu.address, cpu.value);
                // AND
                cpu.A &= cpu.value;
                set_flag_zero(cpu, cpu.A);
                set_flag_negative(cpu, cpu.A);
                cpu.clear_state();
                cpu.poll_nmi();
                return;
        }
        cpu.localClock++;
    }
    void op_sre(Cpu& cpu)
    {
        switch(cpu.localClock)
        {
            case 0:
                cpu.value = cpu.bus.read(cpu.address);
                break;
            case 1:
                // LSR
                cpu.bus.write(cpu.address, cpu.value);
                set_flag_carry(cpu, ((cpu.value & 0b00000001) == 0b00000001));
                cpu.value>>=1;
                break;
            case 2:
                cpu.bus.write(cpu.address, cpu.value);
                // EOR
                cpu.A ^= cpu.value;
                set_flag_zero(cpu, cpu.A);
                set_flag_negative(cpu, cpu.A);
                cpu.clear_state();
                cpu.poll_nmi();
                return;
        }
        cpu.localClock++;
    }
    void op_asr(Cpu& cpu)
    {
        // AND
        cpu.A &= cpu.value;
        // LSR
        set_flag_carry(cpu, (cpu.A & 0x01) == 0x01);
        cpu.A>>=1;
        set_flag_zero(cpu, cpu.A);
        set_flag_negative(cpu, cpu.A);
        cpu.clear_state();
        cpu.poll_nmi();
    }
    void op_rra(Cpu& cpu)
    {
        switch(cpu.localClock)
        {
            case 0:
                cpu.value = cpu.bus.read(cpu.address);
                break;
            case 1: {
                // ROR
                uint8_t oldCarry = cpu.P << 7;
                cpu.bus.write(cpu.address, cpu.value);
                set_flag_carry(cpu, ((cpu.value & 0b00000001) == 0b00000001));
                cpu.value>>=1;
                cpu.value |= oldCarry;
                break; }
            case 2:
                // ADC
                uint16_t result = cpu.A + cpu.value + (cpu.P & 0x01);
                set_flag_carry(cpu, result > 0xFF);
                set_flag_zero(cpu, result);
                set_flag_overflow(cpu, ((result ^ cpu.A) & (result ^ cpu.value) & 0x80) == 0x80);
                set_flag_negative(cpu, result);
                cpu.A = (result % 256);
                cpu.bus.write(cpu.address, cpu.value);
                cpu.clear_state();
                cpu.poll_nmi();
                return;
        }
        cpu.localClock++;
    }
    void op_arr(Cpu& cpu)
    {
        // AND
        uint8_t value = cpu.bus.read(cpu.address);
        cpu.A &= cpu.bus.read(value);
        set_flag_overflow(cpu, (cpu.A + value) > 255);
        // ROR
        uint8_t oldCarry = cpu.P << 7;
        set_flag_carry(cpu, (cpu.A & 0x01) == 0x01);
        cpu.A>>=1;
        cpu.A |= oldCarry;
        set_flag_zero(cpu, cpu.A);
        set_flag_negative(cpu, cpu.A);
        cpu.clear_state();
        cpu.poll_nmi();
    }
    void op_sax(Cpu& cpu)
    {
        cpu.bus.write(cpu.address, cpu.A & cpu.X);
        cpu.clear_state();
        cpu.poll_nmi();
    }
    void op_ane(Cpu& cpu)
    {

    }
    void op_tas(Cpu& cpu)
    {

    }
    void op_sha(Cpu& cpu)
    {

    }
    void op_shx(Cpu& cpu)
    {

    }
    void op_shy(Cpu& cpu)
    {

    }
    void op_lax(Cpu& cpu)
    {
        cpu.A = cpu.bus.read(cpu.address);
        cpu.X = cpu.bus.read(cpu.address);
        set_flag_zero(cpu, cpu.A);
        set_flag_negative(cpu, cpu.A);
        cpu.clear_state();
        cpu.poll_nmi();
    }
    void op_lxa(Cpu& cpu)
    {

    }
    void op_las(Cpu& cpu)
    {

    }
    void op_dcp(Cpu& cpu)
    {

    }
    void op_isc(Cpu& cpu)
    {

    }
}