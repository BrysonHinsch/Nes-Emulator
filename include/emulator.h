#pragma once

#include "cpu.h"
#include "ppu.h"
#include "renderer.h"

class Emulator
{
    public:

    // Constructor
    Emulator(Cpu& cpu, Ppu& ppu, Renderer& renderer);

    // Member functions
    void swap_cartridge(std::string filename);
    void step();
    void frame();

    // Member variables
    Cpu& cpu;
    Ppu& ppu;
    Renderer& renderer;

    // Debugging
    bool debug;
};