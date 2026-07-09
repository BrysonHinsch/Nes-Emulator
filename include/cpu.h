#pragma once

#include <cstdint>

#include "bus.h"
#include "opcodes.h"

class Cpu
{
    public:
        // Constructors
        Cpu(Bus &bus);

        // Member Functions
        // fetches opcode and updates opcode variable and opcodeReady variable
        void fetch_opcode();
        // fetches 1 byte of address
        void fetch_address();
        // Executes the current instruction for one cycle
        void execute_instruction();
        // clocks the cpu for one cycle
        void clock_cpu();
        // clears opcode, addresss, and cycle variable to reset state
        void clear_state();
        
        // PROGRAM VARIABLES
        // Temporary Values
        uint8_t temp8; // general purpose 8-bit temporary variable
        uint16_t temp16; // general purpose 16-bit temporary variable
        uint8_t opcode;
        bool opcodeReady;
        uint8_t value;
        uint16_t address;
        bool addressReady;
        // Cycle Counters
        int cyclesSincePower;
        int masterClock;
        int localClock;
        // SYSTEM VARIABLES
        // Registers
        uint8_t A;
        uint8_t X;
        uint8_t Y;
        // Program Counter
        uint16_t PC;
        // Stack Pointer
        uint8_t SP;
        // Status Register
        uint8_t P;
        // System Bus
        Bus &bus;

        private:
        // Will move anything that should be private over later
        // For now everything will be public for simplicity
};