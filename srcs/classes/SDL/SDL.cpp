#include "SDL.hpp"
#include "../Texture/Texture.hpp"
#include <SDL2/SDL.h>
#include <stdexcept>

#define SCREEN_WIDTH 960
#define SCREEN_HEIGHT 720
SDL::SDL()
{
    window = NULL;
    renderer = NULL;

    if (SDL_Init(SDL_INIT_VIDEO) != 0)
        throw(std::runtime_error("SDL constructor: SDL_Init failed"));

    window = SDL_CreateWindow("DungeonGenerator", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH,
                              SCREEN_HEIGHT, 0);
    if (!window)
        throw(std::runtime_error("SDL constructor: SDL_CreateWindow failed"));

    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer)
        throw(std::runtime_error("SDL constructor: SDL_CreateRenderer failed"));

    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
    SDL_ShowCursor(SDL_DISABLE);
}

SDL::~SDL()
{
    if (renderer)
        SDL_DestroyRenderer(renderer);
    if (window)
        SDL_DestroyWindow(window);
}

void SDL::drawPixel(int x, int y, int color[3])
{
    SDL_SetRenderDrawColor(renderer, color[0], color[1], color[2], 255);
    SDL_RenderDrawPoint(renderer, x, y);
}

void SDL::drawTexture(const Texture &texture, int startX, int startY)
{
    for (int x = 0; x < texture.getWidth(); x++)
    {
        if (x + startX < 0 || (int)x + startX >= SCREEN_WIDTH)
            continue;
        for (int y = 0; y < texture.getHeight(); y++)
        {
            if (y + startY < 0 || x + startY >= SCREEN_WIDTH)
                continue;
            int color[3] = {texture.getData()[y * 3 * texture.getWidth() + x * 3],
                            texture.getData()[y * 3 * texture.getWidth() + x * 3 + 1],
                            texture.getData()[y * 3 * texture.getWidth() + x * 3 + 2]};
            drawPixel(x + startX, y + startY, color);
        }
    }
}

void SDL::updateLoop()
{
    Texture newTexture("assets/fourDoor.ppm");
    while (true)
    {
        checkInput();
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);
        drawTexture(newTexture, 0, 0);
        SDL_RenderPresent(renderer);
    }
}

void SDL::checkInput()
{
    SDL_Event event;

    while (SDL_PollEvent(&event))
    {
        switch (event.type)
        {
        case SDL_QUIT:
            exit(0);
        case SDL_KEYDOWN:
            if (event.key.keysym.sym == SDLK_ESCAPE)
                exit(0);
        }
    }
}

SDL_Window *SDL::getWindow()
{
    return (window);
}

SDL_Renderer *SDL::getRenderer()
{
    return (renderer);
}