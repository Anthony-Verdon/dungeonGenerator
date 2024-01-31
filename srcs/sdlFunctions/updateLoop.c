#include "sdlFunctions.h"
#include <stdbool.h>

void updateLoop(t_sdl *app) {
  while (true) {
    checkInput(app);
    SDL_SetRenderDrawColor(app->renderer, 255, 255, 255, 255);
    SDL_RenderClear(app->renderer);
    SDL_RenderPresent(app->renderer);
  }
}