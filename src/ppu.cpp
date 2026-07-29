
#include "ppu.h"

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

void Ppu::clock_ppu() {
    if (scanline == -1) // pre-render
    {
        
    }
    else if (scanline >= 0 && scanline < 240) // rendering
    {
        if (dot == 0)
        {
            if (even_frame) {return;}
            

        }
        else if (dot <= 256)
        {
            // ########## Fetching tile data ##########
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
                    v = (v & 0xFFE0) | cx;
                    // reset for next 8 bits
                    local_clock = -1;
                    break; }
            }
            local_clock++;

            // ########## Drawing Pixels ##########

            int color = (((pattern_shift_low << x) & 0x80) >> 16) | (((pattern_shift_low << x) & 0x80) >> 15);
            pattern_shift_low <<= 1;
            pattern_shift_high <<= 1;
            int index = scanline*256 + dot;
            switch(color)
            {
                case 0: buffer[index] = 0x000000FF;
                case 1: buffer[index] = 0x555555FF;
                case 2: buffer[index] = 0xAAAAAAFF;
                case 3: buffer[index] = 0xFFFFFFFF;
            }
        }
        else if (dot <= 320)
        {

        }
        else if (dot <= 336)
        {

        }
        else
        {
            
        }
    }
    else if (scanline == 240) {return;} // idle
    else if (scanline > 240 && scanline <= 260) // v-blank
    {

    }
}