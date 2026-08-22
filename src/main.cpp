#include <stdio.h>

#include "emulator.h"
#include "SDL.h"

int main() 
{
    // Initialize SDL library
    SDL_Init(SDL_INIT_VIDEO);

    // Create main emulator object
    Emulator* emu = new Emulator();

    // Start main emulator loop
    emu->start_emulator();

    // Program termination
    std::cout << "Returned with error code 0";
    return 0;
}