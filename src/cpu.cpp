
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
    if (ops::pointerTable[opcode].execute == nullptr)
    {
        PC++;
        return;
    }
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

void Cpu::handle_nmi()
{
    switch(localClock)
    {
        case 0:
            bus.read(PC); // dummy read
            break;
        case 1:
            bus.read(PC); // dummy read
            break;
        case 2:
            bus.write(0x100 + SP--, static_cast<uint8_t>(PC >> 8));
            break;
        case 3:
            bus.write(0x100 + SP--, static_cast<uint8_t>(PC));
            break;
        case 4:
            bus.write(0x100 + SP--, ((P & 0b11101111) | 0b00100000));
            break;
        case 5:
            temp8 = bus.read(0xFFFA);
            P |= 0b00000100; // set interrupt disable
            break;
        case 6:
            PC = bus.read(0xFFFB) << 8;
            PC |= temp8;
            service_nmi = false;
            clear_state();
            return;
    }
    localClock++;
}

void Cpu::poll_nmi()
{
    if (nmi_pending)
    {
        nmi_pending = false;
        service_nmi = true;
        return;
    }
}

void Cpu::handle_oam_dma()
{
    if (oam_delay) // oam hit on odd cycle
    {
        oam_delay = false;
        return;
    }
    if (!oam_dummy_done) // 1 cycle delay
    {
        oam_dummy_done = true;
        return;
    }
    if (localClock == 0) // fetch data
    {
        uint16_t address = (oam_dma_addr << 8) | oam_dma_index;
        value = bus.read(address);
        localClock = 1;
    }
    else // write to oam
    {
        write_oam(oam_dma_index++, value);
        localClock = 0;

        if (oam_dma_index == 0) // wrapped to 0, oam_dma complete
        {
            oam_dma = false;
            oam_dummy_done = false;
        }
    }
}

void Cpu::write_oam(uint8_t index, uint8_t value)
{
    bus.write_oam(index, value);
}

void Cpu::clock_cpu()
{
    if (oam_dma)
    {
        handle_oam_dma();
        masterClock++;
        return;
    }
    if (service_nmi)
    {
        handle_nmi();
        masterClock++;
        return;
    }
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
    std::cout << std::hex << "0x" << (int)opcode << "  ";
    std::cout << std::uppercase << ops::op_to_string(ops::pointerTable[opcode].op) << "                       ";
    std::cout << "A: " << std::hex << (int)A << " ";
    std::cout << "X: " << std::hex << (int)X << " ";
    std::cout << "Y: " << std::hex << (int)Y << " ";
    std::cout << "P: " << std::hex << (int)P << " ";
    std::cout << "SP: " << std::hex << (int)SP << "     ";
    std::cout << "CYC: " << std::dec << (int)masterClock+6 << "     ";
    std::cout << "ADDRESS: " << std::hex << "0x" <<(int)address << "\n";

}

// Clears the state of the cpu to reset for the next instruction
void Cpu::clear_state()
{
    temp8 = 0;
    temp16 = 0;
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

    // for nestest
    //PC = 0;
    //PC = 0xc000;

    PC = bus.read(0xFFFC);
    PC |= bus.read(0xFFFD) << 8;
}