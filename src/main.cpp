#include <stdio.h>
#include <windows.h>
#include "cartridge.h"
#include "cpu.h"
#include "emulator.h"
#include "renderer.h"
#include "SDL.h"

int main() 
{
    Cartridge cart("roms/color_test.nes");

    Bus* bus = new Bus(cart);

    Cpu* cpu = new Cpu(*bus);

    Renderer* rend = new Renderer(256, 240, 4);
    Ppu* ppu = new Ppu(*rend, *bus);

    bus->set_cpu(cpu);
    bus->set_ppu(ppu);

    Emulator* emu = new Emulator(*cpu, *ppu, *rend);

    cpu->power_on();
    ppu->power_on();

    SDL_Init(SDL_INIT_VIDEO);

    int *buffer = new int[256*240];
    
    rend->update_texture(buffer);

    for (int i = 0; i <300; i++)
    {
        emu->frame();
        Sleep(1000/60);
    }
    
    std::cout << "Returned with error code 0";
    return 0;
}