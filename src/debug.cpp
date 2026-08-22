
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
    SDL_SetTextureBlendMode(win->texture, SDL_BLENDMODE_NONE);
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

    for (int i = 0; i < d.width / 8; i++)
    {
        for (int j = 0; j < d.height / 8; j++)
        {
            display_pattern_table_tile(CHR_ROM, buffer, i % 16, j % 16, (i >> 4) & 0x01);
        }
    }
    update_texture(d, buffer.data());
}

void Debug::update_nametable_window()
{
    // get reference to pattern tables
    std::vector<uint8_t>& CHR_ROM = bus.get_chr_rom();
    // get reference to debug window object
    debug_window& d = debug_window_array[window_types::NAMETABLE];
    int size = d.width * d.height;
    std::vector<int> buffer(size, 0);

    for (int i = 0; i < 30; i++)
    {
        for (int j = 0; j < 32; j++)
        {
            int address = 0x2000 + (32 * i) + j;
            uint8_t pattern_index = bus.read_ppu(address);
            display_pattern_table_tile(CHR_ROM, buffer, 0, 0, 0);
        }
    }

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
    if (debug_window_array[window_types::NAMETABLE].active) {update_nametable_window();}
}

void Debug::display_pattern_table_tile(std::vector<uint8_t>& CHR_ROM, std::vector<int>& buffer, int x, int y, int half)
{
    for (int i = 0; i < 8; i++)
    {
        int tile_offset = (half * 0x1000) + (x * 16) + (y * 256);
        uint8_t low_byte = CHR_ROM[tile_offset + i];
        uint8_t high_byte = CHR_ROM[tile_offset + i + 8];
        for (int j = 0; j < 8; j++)
        {
            int color = ((low_byte & 0x80) >> 7) | ((high_byte & 0x80) >> 6);
            int x_offset = (half * 128) + (x * 8) + j;
            int y_offset = (y * 8) + i;
            int address = (y_offset * 256 + x_offset);
            switch(color)
            {
                case 0: buffer[address] = 0x222222FF; break;
                case 1: buffer[address] = 0x666666FF; break;
                case 2: buffer[address] = 0xAAAAAAFF; break;
                case 3: buffer[address] = 0xEEEEEEFF; break;
            }
            low_byte <<= 1;
            high_byte <<= 1;
        }
    }
}