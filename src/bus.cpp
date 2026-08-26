
#include <cstdint>

#include "bus.h"
#include "cartridge.h"
#include "cpu.h"
#include "ppu.h"

Bus::Bus(Cartridge* cart) : cartridge(cart) {}

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
        return PPU->register_read(address);
    }
    else if (address < 0x4018) // APU and IO Registers
    {
        if (address == 0x4016) // controller 1 polling
        {
            int return_val = CPU->controller_1 & 0x01;
            CPU->controller_1 >>= 1;
            return return_val;
        }
        if (address == 0x4017) {return 0;} // controller 2 polling
        return 0;
    }
    else if (address < 0x4020) // CPU Test Mode
    {
        return 0;
    }
    else // Unmapped memory. Functionality determined by mapper
    {
        dataBus = cartridge->read(address);
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
        return PPU->register_write(address, value);
    }
    else if (address < 0x4018) // APU and IO Registers
    {
        if (address == 0x4014) // OAMDMA
        {
            // set cpu to oamdma mode
            CPU->oam_dma = true;
            CPU->oam_dma_addr = value;
            CPU->oam_delay = ((CPU->masterClock % 2) != 0) ? true : false;
            PPU->OAMDMA = value;
            return 0;
        }
        if (address == 0x4016) // controller 1 polling
        {
            if (value == 0)
            {
                CPU->controller_input_requested = false;
            }
            else if (value == 1)
            {
                CPU->controller_input_requested = true;
            }
        }
        return 0;
    }
    else if (address < 0x4020) // CPU Test Mode
    {
        return 0;
    }
    else // Unmapped memory. Functionality determined by mapper
    {
        return cartridge->write(address, value);
    }
}

uint8_t Bus::read_ppu(uint16_t address)
{
    if (address < 0x2000) // CHR ROM
    {
        return cartridge->read_ppu(address);
    }
    else if (address < 0x3000) // Nametables in VRAM
    {
        int n = cartridge->header[6];
        if ((n & 0x08) == 0x08) // alternative nametable layout
        {
            // TODO
            return 0;
        }
        else if ((n & 0x01) == 0) // horizontal mirroring
        {
            int temp = address - 0x2000;
            if (temp < 0x800) // nametable A
            {
                return vram[temp % 0x400];
            }
            else // nametable B
            {
                return vram[(temp % 0x400)+0x400];
            }
        }
        else // vertical mirroring
        {
            return vram[(address - 0x2000) % 0x800];
        }
    }
    else
    {
        return 0;
    }
}

uint8_t Bus::write_ppu(uint16_t address, uint8_t value)
{
    if (address < 0x2000) // ROM, don't write
    {
        return 0;
    }
    if (address < 0x3000) // Nametables in VRAM
    {
        int n = cartridge->header[6];
        if ((n & 0x08) == 0x08) // alternative nametable layout
        {
            // TODO
            return 0;
        }
        else if ((n & 0x01) == 0) // horizontal mirroring
        {
            int temp = address - 0x2000;
            if (temp < 0x800) // nametable A
            {
                vram[temp % 0x400] = value;
            }
            else // nametable B
            {
                vram[(temp % 0x400)+0x400] = value;
            }
        }
        else // vertical mirroring
        {
            vram[(address - 0x2000) % 0x800] = value;
        }
        return 0;
    }
    return 0;
}

void Bus::write_oam(uint8_t index, uint8_t value)
{
    PPU->write_oam(index, value);
}

void Bus::set_cpu(Cpu* cpu)
{
    CPU = cpu;
}
        
void Bus::set_ppu(Ppu* ppu)
{
    PPU = ppu;
}

void Bus::set_nmi_flag()
{
    CPU->nmi_pending = true;
}

std::vector<uint8_t>& Bus::get_chr_rom()
{
    return cartridge->CHR_ROM;
}
