#pragma once

#include <cstdint>

#include "../mapper.h"

class MapperNROM: public Mapper
{
    public:

        MapperNROM(std::vector<uint8_t>& PRG_ROM, std::vector<uint8_t>& CHR_ROM, uint8_t* header):
        Mapper(PRG_ROM, CHR_ROM, header) 
        {
            NROM128 = header[4] == 1;
        }

        uint8_t read(uint16_t address) override
        {
            if (address >= 0x8000)
            {
                if (NROM128)
                {
                    return PRG_ROM[(address - 0x8000) % 0x4000];
                }
                return PRG_ROM[address - 0x8000];
            }
            return 0;
        }
    private:
        bool NROM128 = false;
};