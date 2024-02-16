#include "SDL.hpp"
#include "../Texture/Texture.hpp"
#include <SDL2/SDL.h>
#include <memory>
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

void SDL::drawTexture(const Texture &texture, int startX, int startY, float scaleX, float scaleY)
{
    float texX = 0;
    float stepX = 1.0 / scaleX;
    for (int x = 0; x < texture.getWidth() * scaleX; x++)
    {
        if (x + startX < 0 || (int)x + startX >= SCREEN_WIDTH)
            continue;

        float texY = 0;
        float stepY = 1.0 / scaleY;
        for (int y = 0; y < texture.getHeight() * scaleY; y++)
        {
            if (y + startY < 0 || x + startY >= SCREEN_HEIGHT)
                continue;

            std::vector<int> data = texture.getData();
            int pixel = (int)texY * 3 * texture.getWidth() + (int)texX * 3;
            int color[3] = {data[pixel + 0], data[pixel + 1], data[pixel + 2]};
            drawPixel(x + startX, y + startY, color);
            texY += stepY;
        }
        texX += stepX;
    }
}

// maybe modify the code so SDL isn't a class
void SDL::updateLoop(t_map map)
{
    int scale = 2;
    while (true)
    {
        checkInput();
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderClear(renderer);
        for (int y = 0; y < map.height; y++)

            for (int x = 0; x < map.width; x++)
            {
                std::shared_ptr<Texture> texture = map.tileset[map.data[y][x].possiblesTilesID[0]].getTexture();
                drawTexture(*texture, x * 16 * scale, y * 16 * scale, scale, scale);
            }
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