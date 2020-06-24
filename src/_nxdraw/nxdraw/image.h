#ifndef NXDRAW_IMAGE_H
#define NXDRAW_IMAGE_H

#define STB_IMAGE_IMPLEMENTATION
#include "stb/stb_image.h"
#include "texture.h"

Texture *image_load_png(const char *filepath) {
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