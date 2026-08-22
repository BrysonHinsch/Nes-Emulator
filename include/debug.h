#pragma once

#include <cstdint>

#include "bus.h"
#include "SDL.h"

// Constant for how many types of debug windows there are
const uint8_t debug_types = 1;

// Contains information for updating window
struct debug_window
{
    SDL_Window* window;
    SDL_Renderer* renderer;
    SDL_Texture* texture;

    int width;
    int height;

    bool active = false;
};

// Contains information for creating window
struct debug_window_info
{
    char* window_title;

    int width;
    int height;
};

// List of information for each debug window type
const debug_window_info debug_window_info_array[debug_types] =
{
    {"Pattern Tables", 512, 256} // 0
};

// Enum of window types for indexing in emulator
enum window_types
{
    PATTERN_TABLE // 0
};

class Debug
{
    public:
        Debug(Bus& bus);

        void open_debug_window(int index);
        bool close_debug_window(SDL_WindowID window_id); // returns true if window is successfully closed
        void update_pattern_table_window();

    private:
        // array of debug windows for tracking which are active
        debug_window debug_window_array[debug_types];
        // reference to bus for accessing ROM and RAM
        Bus& bus;
};