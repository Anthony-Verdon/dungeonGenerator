#include "t_texture.h"
#include <fcntl.h>
t_texture *openTexture(char *path) {
  int fd = open(path, O_RDONLY);
  if (fd == -1) {
  }
}