#pragma once

#include "SDL.h"

class Renderer {
    public:
        Renderer(const char* title, int width, int height, int scale);

        void update_texture(int* buffer);

        void advance_frame();

        SDL_WindowID get_window_id();
        SDL_Window* get_window();
    private:
        SDL_Window* window;
        SDL_Renderer* renderer;
        SDL_Texture* texture;

        int width;
        int height;
};