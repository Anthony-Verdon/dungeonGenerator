#include "../dungeonGenerator.h"
#include "sdlFunctions.h"
#include <stdio.h>

void initSDL(t_sdl *app) {
  app->window = NULL;
  app->renderer = NULL;

  if (SDL_Init(SDL_INIT_VIDEO) != 0)
    goto INIT_ERROR;

  app->window =
      SDL_CreateWindow("DungeonGenerator", SDL_WINDOWPOS_UNDEFINED,
                       SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, 0);
  if (!app->window)
    goto INIT_ERROR;

  SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
  app->renderer = SDL_CreateRenderer(app->window, -1, SDL_RENDERER_ACCELERATED);
  if (!app->renderer)
    goto INIT_ERROR;

  SDL_SetRenderDrawBlendMode(app->renderer, SDL_BLENDMODE_BLEND);
  SDL_ShowCursor(SDL_DISABLE);
  return;

INIT_ERROR:
  printf("%s\n", SDL_GetError());
  quitSDL(app);
}