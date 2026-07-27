
#include "ppu.h"

void Ppu::clock_ppu() {
    if (scanline == -1) // pre-render
    {
        
    }
    else if (scanline > -1 && scanline < 240) // rendering
    {
        if (dot == 0)
        {

        }
        else if (dot <= 256)
        {

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