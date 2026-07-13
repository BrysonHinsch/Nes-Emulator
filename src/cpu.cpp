
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
    ops::pointerTable[opcode].fetchAddress(*this);
}

void Cpu::execute_instruction()
{
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
        if (ops::pointerTable[opcode].mode == ops::AddressingMode::UNQ) {
            addressReady == true;
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
    std::cout << "A: " << std::hex << A << " ";
    std::cout << "X: " << std::hex << X << " ";
    std::cout << "Y: " << std::hex << Y << " ";
    std::cout << "PC: " << std::hex << PC << " ";
    std::cout << "SP: " << std::hex << SP << " ";
    std::cout << "P: " << std::bitset<8>(P) << " ";
}

// Clears the state of the cpu to reset for the next instruction
void Cpu::clear_state()
{
    opcode = 0;
    address = 0;
    localClock = 0;
    opcodeReady = false;
    addressReady = false;
}