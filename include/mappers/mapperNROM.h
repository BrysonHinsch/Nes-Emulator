#pragma once

#include <cstdint>

#include "../mapper.h"

class MapperNROM: public Mapper
{
    public:

        MapperNROM(std::vector<uint8_t>& PRG_ROM, std::vector<uint8_t>& CHR_ROM):
        Mapper(PRG_ROM, CHR_ROM) {}

        uint8_t read(uint16_t address) override
        {
            if (NROM128)
            {
                return PRG_ROM[(address - 0x8000) % 0x4000];
            }
            return PRG_ROM[address - 0x8000];
        }
    private:
        bool NROM128 = true;
};