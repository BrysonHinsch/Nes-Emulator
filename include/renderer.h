#pragma once

#include "SDL.h"

class Renderer {
    public:
        Renderer(int width, int height);

        void update_texture(int* buffer);

        void advance_frame();
    private:
        SDL_Window* window;
        SDL_Renderer* renderer;
        SDL_Texture* texture;

        int width;
        int height;
};