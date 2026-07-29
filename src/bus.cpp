
#include <cstdint>

#include "bus.h"
#include "cartridge.h"

Bus::Bus(Cartridge& cart) : cartridge(cart) {}

uint8_t Bus::read(uint16_t address)
{
    if (address < 0x2000) // Internal RAM
    {
        dataBus = ram[address % 0x800];
        addressBus = address;
        return dataBus;
    }
    else if (address < 0x4000) // PPU Registers
    {
        return 0;
    }
    else if (address < 0x4018) // APU and IO Registers
    {
        return 0;
    }
    else if (address < 0x4020) // CPU Test Mode
    {
        return 0;
    }
    else // Unmapped memory. Functionality determined by mapper
    {
        dataBus = cartridge.read(address);
        return dataBus;
    }
}

uint8_t Bus::write(uint16_t address, uint8_t value)
{
    if (address < 0x2000) // Internal RAM
    {
        dataBus = value;
        addressBus = address;
        ram[address] = value;
        return value;
    }
    else if (address < 0x4000) // PPU Registers
    {
        return 0;
    }
    else if (address < 0x4018) // APU and IO Registers
    {
        return 0;
    }
    else if (address < 0x4020) // CPU Test Mode
    {
        return 0;
    }
    else // Unmapped memory. Functionality determined by mapper
    {
        return 0;
    }
}

uint8_t Bus::read_ppu(uint16_t address)
{
    if (address < 0x2000) // CHR ROM
    {
        return cartridge.read_ppu(address);
    }
    else if (address < 0x3000) // Nametables in VRAM
    {
        return vram[(address - 0x2000) % 0x800];
    }
    else
    {
        return 0;
    }
}

uint8_t Bus::write_ppu(uint16_t address, uint8_t value)
{
    return 0;
}