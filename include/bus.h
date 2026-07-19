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
        // Reads and returns value from address determined by mapper (eventually)
        uint8_t read(uint16_t address);
        // Writes to address. Behaviour determined by mapper (also eventually)
        uint8_t write(uint16_t address, uint8_t value);

    private:
        // Busses
        uint8_t dataBus;
        uint16_t addressBus;
        // 2KB Internal RAM
        std::array<uint8_t, 2048> ram;
        // Cartridge
        Cartridge& cartridge;
};