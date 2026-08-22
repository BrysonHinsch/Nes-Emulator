
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

    win->window = SDL_CreateWindow(info->window_title, win->width * info->scale, win->height * info->scale, 0);
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
    // get reference to pattern tables
    std::vector<uint8_t>& CHR_ROM = bus.get_chr_rom();
    // get reference to debug window object
    debug_window& d = debug_window_array[window_types::PATTERN_TABLE];
    int size = d.width * d.height;
    std::vector<int> buffer(size, 0);

    /*
    for (int i = 0; i < size; i++)
    {
        int shift = 7 - (i % 8);
        int index = i / 8;
        int low = ((CHR_ROM[index] >> shift) & 0x01);
        int high = ((CHR_ROM[index] >> (shift-1)) & 0x02);
        int color = low | high;
        switch(color)
        {
            case 0: buffer[i] = 0x222222FF; break;
            case 1: buffer[i] = 0x666666FF; break;
            case 2: buffer[i] = 0xAAAAAAFF; break;
            case 3: buffer[i] = 0xEEEEEEFF; break;
        }
    }
    */
    update_texture(d, buffer.data());
}

void Debug::update_texture(debug_window& window, int* buffer)
{
    SDL_UpdateTexture(window.texture, NULL, buffer, window.width * sizeof(int));
    
    SDL_RenderClear(window.renderer);
    SDL_RenderTexture(window.renderer, window.texture, NULL, NULL);
    SDL_RenderPresent(window.renderer);
}

void Debug::update_windows()
{
    if (debug_window_array[window_types::PATTERN_TABLE].active) {update_pattern_table_window();}
}