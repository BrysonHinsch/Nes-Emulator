#pragma once

#include "cpu.h"

class Emulator
{
    public:

    // Constructor
    Emulator(Cpu& cpu);

    // Member functions
    void swap_cartridge(std::string filename);
    void step();

    // Member variables
    Cpu& cpu;

    bool debug;
};