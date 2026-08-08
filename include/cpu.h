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
        // prints the current state of the cpu
        void print_state();
        // clears opcode, addresss, and cycle variable to reset state
        void clear_state();
        // sets default state for console power on
        void power_on();
        
        // PROGRAM VARIABLES
        // Has HLT occured?
        bool hlt_triggered = false;
        // Temporary Values
        uint8_t temp8 = 0; // general purpose 8-bit temporary variable
        uint16_t temp16 = 0; // general purpose 16-bit temporary variable
        bool wrapped = false; // for tracking page wrapping for indirect addressing
        uint8_t opcode = 0;
        bool opcodeReady = false;
        uint8_t value = 0;
        uint16_t address = 0;
        bool addressReady = false;
        // Cycle Counters
        int cyclesSincePower = 0;
        int masterClock = 0;
        int localClock = 0;
        // SYSTEM VARIABLES
        // Registers
        uint8_t A = 0;
        uint8_t X = 0;
        uint8_t Y = 0;
        // Program Counter
        uint16_t PC = 0;
        // Stack Pointer
        uint8_t SP = 0;
        // Status Register
        uint8_t P = 0;
        // System Bus
        Bus &bus;

        private:
        // Will move anything that should be private over later
        // For now everything will be public for simplicity
};