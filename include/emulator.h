#pragma once

#include "cartridge.h"
#include "bus.h"
#include "renderer.h"
#include "cpu.h"
#include "ppu.h"
#include "debug.h"

inline const char* title = "Nes Emulator";

class Emulator
{
    public:

    // Constructor
    Emulator();

    // Member functions

    // Load a new game
    void swap_cartridge(std::string filename);

    // Game execution
    void step(); // steps ahead one cpu cycle
    void run_scanline(); // steps ahead one scanline
    void run_frame(); // steps ahead one frame

    void start_emulator(); // starts the main emulator loop

    // Event loop handling
    void handle_window_close(SDL_Event& event); // handles closing with multiple windows
    void handle_keypress(SDL_Event& event, bool pressed);

    // Member variables

    // State
    bool running = false;
    bool paused = false;

    // Program Main Objects
    Cartridge cartridge;
    Bus bus;
    Renderer renderer;
    Cpu cpu;
    Ppu ppu;
    Debug debug;
};