#ifndef ENGINE_IMAGE_H
#define ENGINE_IMAGE_H

#define STB_IMAGE_IMPLEMENTATION
#include "texture.h"
#include "trd/stb_image.h"

Texture *image_load_png(char *filepath) {
  int w, h, nrChannels;
  unsigned char *data = stbi_load(filepath, &w, &h, &nrChannels, 4);
  if (data != NULL) {
    Texture *image = newTexture(w, h);
    image->data = (Colour *)data;
    return image;
  }
  return NULL;
}

#endif