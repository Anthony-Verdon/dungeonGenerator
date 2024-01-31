#include "sdlFunctions.h"

void quitSDL(t_sdl *app) {
  if (app->renderer)
    SDL_DestroyRenderer(app->renderer);
  if (app->window)
    SDL_DestroyWindow(app->window);
}