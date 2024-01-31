#pragma once

#include <SDL2/SDL.h>

typedef struct s_sdl
{
    SDL_Window *window;
    SDL_Renderer *renderer;
} t_sdl;