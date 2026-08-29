
#include <windows.h>

#include "emulator.h"

Emulator::Emulator():
    cartridge("roms/smb.nes"),
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
    /*
    if (cpu.masterClock > 70000)
    {
        cpu.print_state();
    }
    */
    poll_controller_input();
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

    const int FPS = 60;
    const int frame_delay = 1000/FPS;

    uint64_t frame_start;
    uint64_t frame_time;

    while (running)
    {

        // Get miliseconds since init on frame start
        frame_start = SDL_GetTicks();

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
                    handle_keypress(event, false);
                    break;
                default:
                    break;
            }
        }
        // runs cpu and ppu for one frame's worth of cycles
        run_frame();
        // updates opened debug windows with graphics data
        debug.update_windows();

        frame_time = SDL_GetTicks() - frame_start;

        if (frame_delay > frame_time)
        {
            SDL_Delay(frame_delay - frame_time);
        }
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
            if (pressed) {debug.open_debug_window(window_types::PATTERN_TABLE);}
            break;
        case 17: // N
            if (pressed) {debug.open_debug_window(window_types::NAMETABLE);}
            break;
        // Program control keybinds

        // Controller inputs
        case 26: // W = up
            controller_latch = (pressed) ? controller_latch | 0x10 : controller_latch & 0xEF;
            break;
        case 4: // A = left
            controller_latch = (pressed) ? controller_latch | 0x40 : controller_latch & 0xBF;
            break;
        case 22: // S = down
            controller_latch = (pressed) ? controller_latch | 0x20 : controller_latch & 0xDF;
            break;
        case 7: // D = right
            controller_latch = (pressed) ? controller_latch | 0x80 : controller_latch & 0x7F;
            break;
        case 13: // J = B
            controller_latch = (pressed) ? controller_latch | 0x02 : controller_latch & 0xFD;
            break;
        case 14: // K = A
            controller_latch = (pressed) ? controller_latch | 0x01 : controller_latch & 0xFE;
            break;
        case 20: // Q = select
            controller_latch = (pressed) ? controller_latch | 0x04 : controller_latch & 0xFB;
            break;
        case 8: // E = start
            controller_latch = (pressed) ? controller_latch | 0x08 : controller_latch & 0xF7;
            break;
    }
}

void Emulator::poll_controller_input()
{
    if (cpu.controller_input_requested)
    {
        cpu.controller_1 = controller_latch;
    }
}