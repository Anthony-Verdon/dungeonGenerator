#pragma once

#include "../Texture/Texture.hpp"
#include <SDL2/SDL.h>

class SDL
{
  public:
    SDL();
    ~SDL();

    void updateLoop();
    SDL_Window *getWindow();
    SDL_Renderer *getRenderer();

  private:
    SDL_Window *window;
    SDL_Renderer *renderer;

    SDL(const SDL &copy) = delete;
    SDL &operator=(const SDL &copy) = delete;

    void checkInput();
    void drawTexture(const Texture &texture, int startX, int startY, float scaleX, float scaleY);
    void drawPixel(int x, int y, int color[3]);
};