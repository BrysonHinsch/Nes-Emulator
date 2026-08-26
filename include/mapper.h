#pragma once

#include <cstdint>

#include "cartridge.h"

class Cartridge; // forward declaration

class Mapper
{
    public:

        Mapper(std::vector<uint8_t>& PRG_ROM, std::vector<uint8_t>& CHR_ROM, uint8_t* header):
        PRG_ROM(PRG_ROM),
        CHR_ROM(CHR_ROM) 
        {
            this->header = header;
        }

        virtual uint8_t read(uint16_t address) = 0;

    protected:
        // used to refer to header information and ROM
        uint8_t* header = nullptr;
        std::vector<uint8_t>& PRG_ROM;
        std::vector<uint8_t>& CHR_ROM;
};
