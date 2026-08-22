
#include "debug.h"

Debug::Debug(Bus& bus):
    bus(bus) {}

void Debug::open_debug_window(int index)
{
    debug_window* win = &debug_window_array[index];

    // check if debug window is already active
    if (win->active) {return;}

    const debug_window_info* info = &debug_window_info_array[index];
    win->width = info->width;
    win->height = info->height;
    win->active = true;

    win->window = SDL_CreateWindow(info->window_title, win->width, win->height, 0);
    win->renderer = SDL_CreateRenderer(win->window, "opengl");
    win->texture = SDL_CreateTexture(win->renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STREAMING, win->width, win->height);
    SDL_SetTextureScaleMode(win->texture, SDL_SCALEMODE_NEAREST);
}

bool Debug::close_debug_window(SDL_WindowID window_id)
{
    // Iterate over window array to find corresponding window
    SDL_Window* window = nullptr;
    for (int i = 0; i < debug_types; i++)
    {
        window = debug_window_array[i].window;
        if (SDL_GetWindowID(window) == window_id)
        {
            debug_window& d = debug_window_array[i];

            SDL_DestroyTexture(d.texture);
            SDL_DestroyRenderer(d.renderer);
            SDL_DestroyWindow(d.window);
            
            d.texture, d.renderer, d.window = nullptr;
            d.active = false;
            
            return true;
        }
    }
    return false;
}

void Debug::update_pattern_table_window()
{
    
}
