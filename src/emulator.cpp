
#include "emulator.h"

Emulator::Emulator(Cpu& cpu): cpu(cpu){
    debug = true;
}

void Emulator::swap_cartridge(std::string filename) {

}

void Emulator::step() {
    cpu.clock_cpu();
    if (debug == true) 
    {
        cpu.print_state();
    }
}