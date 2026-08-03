
#include "ppu.h"

Ppu::Ppu(Renderer& renderer, Bus& bus): renderer(renderer), bus(bus) {}

uint8_t Ppu::get_coarse_x(int reg)
{
    return reg & 0x1F;
}
uint8_t Ppu::get_coarse_y(int reg)
{
    return (reg & 0x3E0) >> 5;
}
uint8_t Ppu::get_nametable(int reg)
{
    return (reg & 0xC00) >> 10;
}
uint8_t Ppu::get_fine_y(int reg)
{
    return (reg & 0x7000) >> 12;
}


uint8_t Ppu::register_read(uint16_t address)
{
    int reg = (address - 0x2000) % 8;
    if (reg == 2)
    {
        w = false;
        uint8_t temp = PPUSTATUS;
        PPUSTATUS &= 0x7F;
        return temp;
    }
    else if (reg == 4)
    {
        return OAM[OAMADDR];
    }
    else if (reg == 7)
    {
        
    }
    return 0;
}

uint8_t Ppu::register_write(uint16_t address, uint8_t value)
{
    int reg = (address - 0x2000) % 8;
    if (reg == 0)
    {
        t = (t & 0xF3FF) | ((value & 0x03) << 10);
        PPUCTRL = value;
        return PPUCTRL;
    }
    else if (reg == 1)
    {
        PPUMASK = value;
        return PPUMASK;
    }
    else if (reg == 3)
    {
        OAMADDR = value;
        return OAMADDR;
    }
    else if (reg == 4)
    {
        if (scanline <= 239) {return 0;}
        OAM[OAMADDR++] = value;
        return value;
    }
    else if (reg == 5)
    {
        if (!w) // write 1
        {
            PPUSCROLL = (PPUSCROLL & 0x00FF) | (value << 8);
            t = (t & 0xFFE0) | (value >> 3);
            x = value & 0x07;
            w = true;
            return PPUSCROLL;
        }
        else // write 2
        {
            PPUSCROLL = (PPUSCROLL & 0xFF00) | value;
            t = (t & 0x8C1F) | ((value & 0xF8) << 2) | ((value & 0x07) << 12);
            w = false;
            return PPUSCROLL;
        }
    }
    else if (reg == 6)
    {
        if (!w) // write 1
        {
            PPUADDR = (PPUADDR & 0x00FF) | ((value & 0x3F) << 8);
            w = true;
            return PPUADDR;
        }
        else // write 2
        {
            PPUADDR = (PPUADDR & 0xFF00) | value;
            w = false;
            return PPUADDR;
        }
    }
    else if (reg == 7)
    {

    }
    return 0;
}

uint8_t Ppu::read(uint16_t address)
{
    if (address >= 0x3F00 && address <= 0x3FFF) // Palette Ram
    {
        return palette_ram[(address - 0x3F00) % 20];
    }
    else
    {
        return bus.read_ppu(address);
    }
}

void Ppu::fetch_background(int local_clock)
{
    switch (local_clock)
    {
        case 0: // read nametable byte
            break;
        case 1: // read nametable byte
            nametable_byte = read(0x2000 | (v & 0x0FFF));
            break;
        case 2: // read attribute table byte
            break;
        case 3: { // read attribute table byte
            int cx = get_coarse_x(v);
            int cy = get_coarse_y(v);
            attribute_byte = read(0x23C0 | (v & 0x0C00) | ((cx >> 2)) | ((cy >> 2) << 3));
            break; }
        case 4: // read pattern table low byte
            break;
        case 5: { // read pattern table low byte
            int fy = get_fine_y(v);
            pattern_low = read(((PPUCTRL & 0x10) << 8) | (nametable_byte << 3) | fy);
            break; }
        case 6: // read pattern table high byte
            break;
        case 7: { // read pattern table high byte
            int fy = get_fine_y(v);
            pattern_low = read(((PPUCTRL & 0x10) << 8) | (nametable_byte << 3) | 0x08 | fy);
            // fill shift registers
            pattern_shift_low |= pattern_low;
            pattern_shift_high |= pattern_high;
            // increment horizontal scroll
            int cx = get_coarse_x(v);
            v = (v & 0xFFE0) | (cx + 1);
            // increment vertical scroll
            if (dot == 256) 
            {
                int cy = get_coarse_y(v);
                v = (v & 0xFC1F) | ((cy << 5) + 1);
            }
            // reset for next 8 bits
            local_clock = -1;
            break; }
    }
}

void Ppu::clock_ppu() {
    if (scanline >= 0 && scanline < 240) // rendering
    {
        if (dot == 0)
        {
            if (even_frame) {return;}
            

        }
        else if (dot <= 256) // background tiles
        {
            fetch_background(local_clock); // local clock starts scanline at -1
            local_clock++;

            // ########## Drawing Pixels ##########

            int color = (((pattern_shift_low << x) & 0x80) >> 16) | (((pattern_shift_low << x) & 0x80) >> 15);
            pattern_shift_low <<= 1;
            pattern_shift_high <<= 1;
            int index = scanline*256 + dot;
            switch(color)
            {
                case 0: buffer[index] = 0x000000FF; break;
                case 1: buffer[index] = 0x555555FF; break;
                case 2: buffer[index] = 0xAAAAAAFF; break;
                case 3: buffer[index] = 0xFFFFFFFF; break;
            }
        }
        else if (dot <= 320) // sprites
        {
            if (dot == 257) // set horizontal scroll to beginning of line
            {
                int cx = get_coarse_x(t);
                v = (v & 0xFFE0) | (cx + 1);
            }
            switch(local_clock)
            {
                case 0:
                    break;
                case 1:
                    break;
                case 2:
                    break;
                case 3:
                    break;
            }
        }
        else if (dot <= 336) // next scanline background tiles
        {
            fetch_background(local_clock);
        }
        else // unused nametable fetches
        {
            // Implement later
            // Certain mappers rely on the dummy reads
        }
    }
    else if (scanline == 240) // idle
    {
        if (dot == 0)
        {
            if (even_frame) {return;}
            
        }
        return;
    }
    else if (scanline > 240 && scanline <= 260) // v-blank
    {
        if (scanline == 241 && dot == 1)
        {
            PPUSTATUS |= 0x80;
        }
        return;
    }
    else if (scanline == 261) // pre-render
    {
        if (dot == 1)
        {
            PPUSTATUS &= 0x1F;
        }
        fetch_background(local_clock); // local clock starts scanline at -1
    }
    dot = (dot+1) % 341;
    if (dot == 0)
    {
        scanline = (scanline+1) % 261;
    }
}