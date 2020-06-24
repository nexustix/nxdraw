#ifndef NXDRAW_IMAGE_H
#define NXDRAW_IMAGE_H

#define STB_IMAGE_IMPLEMENTATION
#include "stb/stb_image.h"
#include "texture.h"

NxdrawTexture *nxdraw_image_load_png(const char *filepath) {
  int w, h, nrChannels;
  unsigned char *data = stbi_load(filepath, &w, &h, &nrChannels, 4);
  if (data != NULL) {
    NxdrawTexture *image = newNxdrawTexture(w, h);
    image->data = (NxdrawColour *)data;
    return image;
  }
  return NULL;
}

#endif