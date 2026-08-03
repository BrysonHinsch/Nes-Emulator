
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
            case ops::AddressingMode::IMP:
                execute_instruction();
                masterClock++;
                return;
            case ops::AddressingMode::ACC:
                execute_instruction();
                masterClock++;
                return;
            case ops::AddressingMode::IMM:
                fetch_address();
                execute_instruction();
                masterClock++;
                return;
            case ops::AddressingMode::REL:
                execute_instruction();
                masterClock++;
                if (!opcodeReady) {return;}
                addressReady = true;
                localClock++;
                return;
            case ops::AddressingMode::UNQ:
                execute_instruction();
                masterClock++;
                if (!opcodeReady) {return;}
                addressReady = true;
                localClock++;
                return;
        }
        fetch_address();
        masterClock++;
        if (!addressReady) {localClock++;}
        return;
    }
    else
    {
        execute_instruction();
        masterClock++;
        if (!opcodeReady) {return;}
        localClock++;
        return;
    }
}

void Cpu::print_state()
{
    std::cout << std::hex << PC-1 << "  ";
    std::cout << ops::op_to_string(ops::pointerTable[opcode].op) << "                       ";
    std::cout << "A: " << std::hex << (int)A << " ";
    std::cout << "X: " << std::hex << (int)X << " ";
    std::cout << "Y: " << std::hex << (int)Y << " ";
    std::cout << "P: " << std::hex << (int)P << " ";
    std::cout << "SP: " << std::hex << (int)SP << "     ";
    std::cout << "CYC: " << std::dec << (int)masterClock+7 << "\n";
}

// Clears the state of the cpu to reset for the next instruction
void Cpu::clear_state()
{
    address = 0;
    localClock = 0;
    opcodeReady = false;
    addressReady = false;
}

void Cpu::power_on()
{
    A = 0;
    X = 0;
    Y = 0;
    SP = 0xFD;
    P = 0b00100100;

    // Set program counter
    // Eventually make this take cycles and not be instant
    // we're going for accuracy here!

    // It's currently being set to the nestest reset vector.
    // I can't seem to figure out why it doesn't work normally
    PC = 0;
    PC = 0xc000;
    //PC = bus.read(0xFFFC);
    //PC |= bus.read(0xFFFD) << 8;
}