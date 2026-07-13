#include <stdio.h>
#include "cartridge.h"
#include "cpu.h"

int main() 
{
    Cartridge cart("nestest.nes");
    cart.PrintHeader();

    Bus bus;
    Cpu cpu(bus);

    cpu.print_state();

    return 0;
}