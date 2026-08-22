#pragma once

#include <cstdint>
#include <array>

#include "cartridge.h"

class Ppu; // forward declaration
class Cpu; // forward declaration

class Bus
{
    public:
        // Constructors
        Bus(Cartridge* cart);
        // Member Functions
        // Reads and returns value for cpu
        uint8_t read(uint16_t address);
        // Writes to address for cpu
        uint8_t write(uint16_t address, uint8_t value);
        // Reads and returns value for ppu
        uint8_t read_ppu(uint16_t address);
        // Writes to address for ppu
        uint8_t write_ppu(uint16_t address, uint8_t value);
        // writes to ppu oam data
        void write_oam(uint8_t index, uint8_t value);
        // Sets CPU pointer
        void set_cpu(Cpu* cpu);
        // Sets PPU pointer
        void set_ppu(Ppu* ppu);
        // sets nmi flag in cpu
        void set_nmi_flag();

        // Getters for debugging
        std::vector<uint8_t>& get_chr_rom();

    private:
        // Busses
        uint8_t dataBus = 0;
        uint16_t addressBus = 0;
        // 2KB Internal RAM
        std::array<uint8_t, 2048> ram = {0};
        // 2KB Internal VRAM
        std::array<uint8_t, 2048> vram = {0};
        // Cartridge pointer
        Cartridge* cartridge;
        // CPU pointer for accessing registers
        Cpu* CPU;
        // PPU pointer for accessing registers
        Ppu* PPU;
};