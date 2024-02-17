#pragma once

#include "../../../libs/SDL2_ttf/SDL_ttf.h"
#include "../DungeonGenerator/DungeonGenerator.hpp"
#include "../Texture/Texture.hpp"
#include <SDL2/SDL.h>
#include <SDL2/SDL_keycode.h>
#include <SDL2/SDL_surface.h>
#include <string>
#include "../../structs/t_data.hpp"

class SDL
{
  public:
    SDL();
    ~SDL();

    SDL_Window *getWindow();
    SDL_Renderer *getRenderer();
    TTF_Font *font;

  private:
    SDL_Window *window;
    SDL_Renderer *renderer;
    t_data data;

    SDL(const SDL &copy) = delete;
    SDL &operator=(const SDL &copy) = delete;

    void start();
    void updateLoop();
    void checkInput();
    void parseKeyDown(int keydown);
    void drawTexture(const Texture &texture, int startX, int startY, float scaleX, float scaleY);
    void drawPixel(int x, int y, int color[3]);
    void renderText(const std::string &text, int x, int y);

    void askRulePath();
};