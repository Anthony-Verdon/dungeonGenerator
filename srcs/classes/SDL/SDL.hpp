#pragma once

#include "../DungeonGenerator/DungeonGenerator.hpp"
#include "../Texture/Texture.hpp"
#include <SDL2/SDL.h>

typedef struct s_data
{
    int scale;
    t_map map;
} t_data;

class SDL
{
  public:
    SDL();
    ~SDL();

    SDL_Window *getWindow();
    SDL_Renderer *getRenderer();

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
};