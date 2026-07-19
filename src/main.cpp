#include <stdio.h>
#include <windows.h>
#include "cartridge.h"
#include "cpu.h"
#include "emulator.h"

int main() 
{
    Cartridge cart("nestest.nes");
    cart.PrintHeader();

    Bus* bus = new Bus(cart);

    Cpu* cpu = new Cpu(*bus);

    Emulator* emu = new Emulator(*cpu);

    cpu->power_on();

    for (int i = 0; i < 100; i++) {
        emu->step();
        Sleep(100);
    }

    return 0;
}