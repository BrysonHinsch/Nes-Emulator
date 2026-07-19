#pragma once

#include <cstdint>

#include "cartridge.h"

class Cartridge; // forward declaration

class Mapper
{
    public:

        Mapper(std::vector<uint8_t>& PRG_ROM): PRG_ROM(PRG_ROM) {}

        virtual uint8_t read(uint16_t address) = 0;

    protected:
        // used to refer to header information and ROM
        std::vector<uint8_t>& PRG_ROM;
};
