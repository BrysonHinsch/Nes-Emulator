
#include <cstdint>
#include <bitset>
#include <iostream>

#include "cpu.h"
#include "bus.h"
#include "opcodes.h"

Cpu::Cpu(Bus& bus): bus(bus) {}

void Cpu::fetch_opcode()
{
    opcode = bus.read(PC);
    opcodeReady = true;
    PC++;
}

void Cpu::fetch_address()
{
    if (ops::pointerTable[opcode].fetchAddress == nullptr) {return;}
    ops::pointerTable[opcode].fetchAddress(*this);
}

void Cpu::execute_instruction()
{
    if (ops::pointerTable[opcode].execute == nullptr) {return;}
    ops::pointerTable[opcode].execute(*this);
}

void Cpu::clock_cpu()
{
    if (opcodeReady != true)
    {
        fetch_opcode();
        masterClock++;
        return;
    }
    else if (addressReady != true)
    {
        switch(ops::pointerTable[opcode].mode)
        {
            case ops::AddressingMode::IMM:
                fetch_address();
                execute_instruction();
                masterClock++;
                return;
            case ops::AddressingMode::IMP:
            case ops::AddressingMode::ACC:
            case ops::AddressingMode::REL:
            case ops::AddressingMode::UNQ:
                execute_instruction();
                masterClock++;
                return;
        }
        fetch_address();
        masterClock++;
        return;
    }
    else
    {
        execute_instruction();
        masterClock++;
        return;
    }
}

void Cpu::print_state()
{
    std::cout << std::hex << PC-1 << "  ";
    std::cout << std::uppercase << ops::op_to_string(ops::pointerTable[opcode].op) << "                       ";
    std::cout << "A: " << std::hex << (int)A << " ";
    std::cout << "X: " << std::hex << (int)X << " ";
    std::cout << "Y: " << std::hex << (int)Y << " ";
    std::cout << "P: " << std::hex << (int)P << " ";
    std::cout << "SP: " << std::hex << (int)SP << "     ";
    std::cout << "CYC: " << std::dec << (int)masterClock+6 << "     ";
    std::cout << "ADDRESS: " << std::dec << (int)address << "\n";

}

// Clears the state of the cpu to reset for the next instruction
void Cpu::clear_state()
{
    address = 0;
    localClock = 0;
    opcodeReady = false;
    addressReady = false;
    wrapped = false;
}

void Cpu::power_on()
{
    A = 0;
    X = 0;
    Y = 0;
    SP = 0xFD;
    P = 0b00100100;

    PC = 0;
    PC = 0xc000;
    // PC = bus.read(0xFFFC);
    // PC |= bus.read(0xFFFD) << 8;
}