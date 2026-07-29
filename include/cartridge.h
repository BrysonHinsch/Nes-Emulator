#pragma once

#include <iostream>
#include <cstdint>
#include <fstream>
#include <vector>

#include "mapper.h"

class Cartridge
{
    public:
        // Constructor
        Cartridge(std::string filename);
        // Prints Header for Debugging
        void PrintHeader();
        // Reads from the PRG ROM
        uint8_t read(uint16_t address);
        // Writes to PRG ROM
        uint8_t write(uint16_t address, uint8_t value);
        // Reads from CHR ROM
        uint8_t read_ppu(uint16_t address);
        
        uint8_t header[16] = {0};
        std::vector<uint8_t> trainer;
        std::vector<uint8_t> PRG_ROM;
        std::vector<uint8_t> CHR_ROM;
        
        Mapper* mapper;
};