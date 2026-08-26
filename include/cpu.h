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
        // handles NMI
        void handle_nmi();
        // polls for NMI near the end of instructions
        void poll_nmi();
        // handles oam_dma
        void handle_oam_dma();
        // writes to oam memory in ppu
        void write_oam(uint8_t index, uint8_t value);
        // clocks the cpu for one cycle
        void clock_cpu();
        // prints the current state of the cpu
        void print_state();
        // clears opcode, addresss, and cycle variable to reset state
        void clear_state();
        // sets default state for console power on
        void power_on();
        
        // PROGRAM VARIABLES
        // Controller latches
        uint8_t controller_1 = 0;
        uint8_t controller_2 = 0; // always set to 0
        bool controller_input_requested = false; // set true when 0x4016 is written to
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
        // NMI Detection
        bool nmi_pending = false;
        bool service_nmi = false;
        // OAMDMA Handling
        bool oam_dma = false;
        uint8_t oam_dma_addr = 0;
        uint8_t oam_dma_index = 0;
        bool oam_delay = false; // 1 cycle offset on odd cycle counts
        bool oam_dummy_done = false; // 1 cycle offset for dummy read
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