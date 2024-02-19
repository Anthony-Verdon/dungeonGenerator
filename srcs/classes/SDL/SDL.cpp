#include "SDL.hpp"
#include "../../define.hpp"
#include "../Texture/Texture.hpp"
#include "../fileGenerator/fileGenerator.hpp"
#include "../ruleFileParser/ruleFileParser.hpp"
#include <SDL2/SDL.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_keyboard.h>
#include <SDL2/SDL_keycode.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_surface.h>
#include <iostream>
#include <stdexcept>

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

    if (TTF_Init() != 0)
        throw(std::runtime_error("SDL constructor: TTF_Init failed"));
    font = TTF_OpenFont("fonts/ThaleahFat.ttf", 25);
    if (!font)
        throw(std::runtime_error("SDL constructor: TTF_OpenFont failed"));

    SDL_StartTextInput();
    start();
    updateLoop();
}

SDL::~SDL()
{
    SDL_StopTextInput();
    if (renderer)
        SDL_DestroyRenderer(renderer);
    if (window)
        SDL_DestroyWindow(window);
    if (font)
        TTF_CloseFont(font);
    TTF_Quit();
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

void SDL::start()
{
    data.scale = 1;
    data.rulepath = "assets/roads/rules.json";
    data.map = DungeonGenerator::generateMap(20, 20, "assets/roads/rules.json");
}

void SDL::renderText(const std::string &text, int x, int y)
{
    SDL_Color color = {0, 0, 0, 255};
    SDL_Surface *surface = TTF_RenderText_Solid(font, text.c_str(), color);
    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
    int texW;
    int texH;
    SDL_QueryTexture(texture, NULL, NULL, &texW, &texH);
    SDL_Rect rect = {x, y, texW, texH};
    SDL_RenderCopy(renderer, texture, NULL, &rect);
    SDL_DestroyTexture(texture);
    SDL_FreeSurface(surface);
}

void SDL::updateLoop()
{
    while (true)
    {
        checkInput();
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderClear(renderer);
        for (int y = 0; y < data.map.height; y++)
        {
            for (int x = 0; x < data.map.width; x++)
            {
                std::shared_ptr<Texture> texture =
                    data.map.tileset[data.map.data[y][x].possiblesTilesID[0]].getTexture();
                drawTexture(*texture, x * 16 * data.scale, y * 16 * data.scale, data.scale, data.scale);
            }
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
            break;
        case SDL_KEYDOWN:
            parseKeyDown(event.key.keysym.sym);
            break;
        default:
            break;
        }
    }
}

void SDL::askRulePath()
{
    std::string entry;
    std::cout << "enter rule path" << std::endl;
    getline(std::cin, entry);
    if (ruleFileParser::isRuleFileValid(entry))
    {
        std::cout << "rule path saved" << std::endl;
        data.rulepath = entry;
    }
}

void SDL::parseKeyDown(int keydown)
{
    switch (keydown)
    {
    case SDLK_ESCAPE:
        exit(0);
        break;
    case SDLK_g:
        data.map = DungeonGenerator::generateMap(20, 20, data.rulepath);
        break;
    case SDLK_z:
        data.map = DungeonGenerator::generateMap("initMap.txt");
        break;
    case SDLK_f:
        fileGenerator::generateFile(data.map);
        break;
    case SDLK_r:
        askRulePath();
        break;
    default:
        break;
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