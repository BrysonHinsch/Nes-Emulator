
#include <cstdint>

#include "opcodes.h"
#include "cpu.h"

namespace ops
{
    // OPCODE POINTER TABLE
    const Opcode pointerTable [256] {
        {nullptr, nullptr, AddressingMode::IMP, Instruction::BRK}
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