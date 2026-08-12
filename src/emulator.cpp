
#include "emulator.h"

Emulator::Emulator(Cpu& cpu, Ppu& ppu, Renderer& renderer): 
    cpu(cpu), ppu(ppu) , renderer(renderer)
{
    debug = false;
}

void Emulator::swap_cartridge(std::string filename) 
{

}

void Emulator::step() 
{
    cpu.clock_cpu();
    if (debug == true) 
    {
        cpu.print_state();
    }
    // 3 PPU clocks per CPU clock
    ppu.clock_ppu();
    ppu.clock_ppu();
    ppu.clock_ppu();
}

void Emulator::frame()
{
    // simplified fix later
    for (int i = 0; i < 29781; i++)
    {
        step();
    }
    renderer.update_texture(ppu.buffer);
}