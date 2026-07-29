
#include "renderer.h"
#include <iostream>

Renderer::Renderer(int width, int height)
{
    this->width = width;
    this->height = height;

    window = SDL_CreateWindow("Nes Emulator", width, height, 0);
    renderer = SDL_CreateRenderer(window, "opengl");
    texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STREAMING, width, height);
}

void Renderer::update_texture(int* buffer)
{
    SDL_UpdateTexture(texture, NULL, buffer, width * sizeof(int));
    
    SDL_RenderClear(renderer);
    SDL_RenderTexture(renderer, texture, NULL, NULL);
    SDL_RenderPresent(renderer);
}