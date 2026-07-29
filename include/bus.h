#pragma once

#include <cstdint>
#include <array>

#include "cartridge.h"

class Bus
{
    public:
        // Constructors
        Bus(Cartridge& cart);
        // Member Functions
        // Reads and returns value for cpu
        uint8_t read(uint16_t address);
        // Writes to address for cpu
        uint8_t write(uint16_t address, uint8_t value);
        // Reads and returns value for ppu
        uint8_t read_ppu(uint16_t address);
        // Writes to address for ppu
        uint8_t write_ppu(uint16_t address, uint8_t value);

    private:
        // Busses
        uint8_t dataBus;
        uint16_t addressBus;
        // 2KB Internal RAM
        std::array<uint8_t, 2048> ram;
        // 2KB Internal VRAM
        std::array<uint8_t, 2048> vram;
        // Cartridge
        Cartridge& cartridge;
};