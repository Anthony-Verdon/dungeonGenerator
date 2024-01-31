#include <SDL2/SDL.h>
#include <stdbool.h>
#include <stdio.h>

#define SCREEN_WIDTH 960
#define SCREEN_HEIGHT 720

typedef struct s_sdl {
  SDL_Window *window;
  SDL_Renderer *renderer;
} t_sdl;

void quitSDL(t_sdl *app) {
  if (app->renderer)
    SDL_DestroyRenderer(app->renderer);
  if (app->window)
    SDL_DestroyWindow(app->window);
}

void checkInput(t_sdl *app) {
  SDL_Event event;

  while (SDL_PollEvent(&event)) {
    switch (event.type) {
    case SDL_QUIT:
      quitSDL(app);
      exit(0);
    }
  }
}

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

void updateLoop(t_sdl *app) {
  while (true) {
    checkInput(app);
    SDL_SetRenderDrawColor(app->renderer, 255, 255, 255, 255);
    SDL_RenderClear(app->renderer);
    SDL_RenderPresent(app->renderer);
  }
}

int main() {
  t_sdl app;
  initSDL(&app);
  updateLoop(&app);
}