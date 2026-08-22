
#include <windows.h>

#include "emulator.h"

Emulator::Emulator():
    cartridge("roms/dk.nes"),
    bus(&cartridge),
    renderer(title, 256, 240, 2),
    cpu(bus),
    ppu(bus, renderer),
    debug(bus)
{
    bus.set_cpu(&cpu);
    bus.set_ppu(&ppu);

    cpu.power_on();
    ppu.power_on();
}

void Emulator::swap_cartridge(std::string filename) 
{

}

void Emulator::step() 
{
    cpu.clock_cpu();
    // 3 PPU clocks per CPU clock
    ppu.clock_ppu();
    ppu.clock_ppu();
    ppu.clock_ppu();
}

void Emulator::run_frame()
{
    // simplified fix later
    for (int i = 0; i < 29781; i++)
    {
        step();
    }
}

void Emulator::start_emulator()
{
    SDL_Event event;
    running = true;

    while (running)
    {
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_EVENT_QUIT: // no debug windows open
                    running = false;
                    break;
                case SDL_EVENT_WINDOW_CLOSE_REQUESTED: // debug window(s) open
                    handle_window_close(event);
                    break;
                case SDL_EVENT_KEY_DOWN:
                    handle_keypress(event, true);
                    break;
                case SDL_EVENT_KEY_UP:
                    //handle_keypress(event, false);
                    break;
                default:
                    break;
            }
        }
        debug.update_windows();
        Sleep(1000/60);
    }
    SDL_Quit();
    return;
}

void Emulator::handle_window_close(SDL_Event& event)
{
    if (event.window.windowID == renderer.get_window_id()) // main window
        {
            running = false;
        }
    else
        {
            debug.close_debug_window(event.window.windowID);
        }
}

void Emulator::handle_keypress(SDL_Event& event, bool pressed)
{
    switch (event.key.scancode)
    {
        // Debug window keybinds
        case 19: // P
            debug.open_debug_window(window_types::PATTERN_TABLE);
            break;
        case 18: // O
            run_frame();
            break;
        // Program control keybinds

        // Controller inputs

    }
}