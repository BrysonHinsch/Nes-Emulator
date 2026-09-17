#include <iostream>
#include <cstdint>
#include <fstream>

#include "cartridge.h"
#include "mappers/mapperNROM.h"

Cartridge::Cartridge() {}

uint8_t Cartridge::read(uint16_t address)
{
    return mapper->read(address);
}

uint8_t Cartridge::write(uint16_t address, uint8_t value)
{
    return 0;
}
// DEBUGGING #################################################

void Cartridge::PrintHeader()
{
    for (int i = 0; i < 16; i++)
    { 
        std::cout << (int)header[i] << std::endl;
    }
}

uint8_t Cartridge::read_ppu(uint16_t address)
{
    return CHR_ROM[address % 0x2000];
}

void Cartridge::load_rom(std::string filepath)
{
    std::ifstream file(filepath, std::ios::binary);
    // read file header
    file.read(reinterpret_cast<char*>(header), sizeof(header));
    // read trainer data
    if ((header[6] & 0x04) == 0x04)
    {
        // will eventually read trainer data
        // either 0 or 512 bytes
    }
    // read PRG_ROM
    int prg_size = header[4] * 0x4000;
    PRG_ROM.resize(prg_size);
    file.read(reinterpret_cast<char*>(PRG_ROM.data()), prg_size);

    // read CHR_ROM
    int chr_size = header[5] * 0x2000;
    CHR_ROM.resize(chr_size);
    file.read(reinterpret_cast<char*>(CHR_ROM.data()), chr_size);
    
    // set mapper
    switch (((header[6] & 0xF0) >> 4) + (header[7] & 0xF0))
    {
        case 0:
            mapper = new MapperNROM(PRG_ROM, CHR_ROM, header);
            break;
        default:
            mapper = new MapperNROM(PRG_ROM, CHR_ROM, header);
            break;
    }
    game_loaded = true;
}