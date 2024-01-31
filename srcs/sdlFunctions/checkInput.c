#include "sdlFunctions.h"

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