
#include "renderer.h"

Renderer::Renderer(const char* title, int width, int height, int scale)
{
    this->width = width;
    this->height = height;

    window = SDL_CreateWindow(title, width * scale, height * scale, 0);
    renderer = SDL_CreateRenderer(window, "opengl");
    texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STREAMING, width, height);
    SDL_SetTextureScaleMode(texture, SDL_SCALEMODE_NEAREST);
}

void Renderer::update_texture(int* buffer)
{
    SDL_UpdateTexture(texture, NULL, buffer, width * sizeof(int));
    
    SDL_RenderClear(renderer);
    SDL_RenderTexture(renderer, texture, NULL, NULL);
    SDL_RenderPresent(renderer);
}

SDL_WindowID Renderer::get_window_id()
{
    return SDL_GetWindowID(window);
}