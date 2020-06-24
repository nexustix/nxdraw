#ifndef NXDRAW_SPRITE_H
#define NXDRAW_SPRITE_H

#include "colour.h"
#include <stdlib.h>

typedef struct {
  int width;
  int height;
  // unsigned char(*data);
  NxdrawColour(*data);
} NxdrawTexture;

NxdrawTexture *newNxdrawTexture(int width, int height) {
  NxdrawTexture *self = (NxdrawTexture *)calloc(1, sizeof(*self));
  self->width = width;
  self->height = height;
  self->data = (NxdrawColour *)calloc(self->width * self->height * 1,
                                      sizeof(NxdrawColour));
  return self;
}

// void texture_put_pixel(NxdrawTexture *self, int x, int y, unsigned char r,
// unsigned char g, unsigned char b, unsigned char a) void
// texture_put_pixel(NxdrawTexture *self, int x, int y, NxdrawColour colour)
//{
//    if (x < self->width && y < self->height)
//    {
//        self->data[self->width * y + x] = colour;
//    }
//}

void texture_set_pixel(NxdrawTexture *self, int x, int y, NxdrawColour colour) {
  if (x < self->width && y < self->height && x >= 0 && y >= 0) {
    self->data[self->width * y + x] = colour;
  }
}

NxdrawColour texture_get_pixel(NxdrawTexture *self, int x, int y) {
  if (x < self->width && y < self->height && x >= 0 && y >= 0) {
    return self->data[self->width * y + x];
  }
  return (NxdrawColour){0x00000000};
}

void texture_put_pixel_alpha(NxdrawTexture *self, int x, int y,
                             NxdrawColour colour) {
  if (x < self->width && y < self->height && x >= 0 && y >= 0) {
    NxdrawColour d = texture_get_pixel(self, x, y);
    // turn alpha to 0.0 1.0 range
    float a = (float)(colour.a / 255.0f);
    // flip alpha
    float c = 1.0f - a;
    // apply alpha
    float r = a * (float)colour.r + c * (float)d.r;
    float g = a * (float)colour.g + c * (float)d.g;
    float b = a * (float)colour.b + c * (float)d.b;
    texture_set_pixel(self, x, y,
                      makeNxdrawColour((unsigned char)r, (unsigned char)g,
                                       (unsigned char)b, (unsigned char)a));
  }
}

// void texture_blit(NxdrawTexture *self, NxdrawTexture *target, int sx, int sy,
// int sw, int sh, int tx, int ty, int tw, int th){
//
//}

void texture_blit(NxdrawTexture *target, NxdrawTexture *source, int tx, int ty,
                  int scale) {

  if (target == NULL) {
    return;
  }

  if (scale > 1) {
    for (int w = 0; w < source->width; w++) {
      for (int h = 0; h < source->height; h++) {
        for (int ww = 0; ww < scale; ww++) {
          for (int hh = 0; hh < scale; hh++) {
            texture_put_pixel_alpha(target, tx + (w * scale) + ww,
                                    ty + (h * scale) + hh,
                                    texture_get_pixel(source, w, h));
          }
        }
      }
    }
  } else {
    for (int w = 0; w < source->width; w++) {
      for (int h = 0; h < source->height; h++) {
        texture_put_pixel_alpha(target, tx + h, ty + w,
                                texture_get_pixel(source, w, h));
      }
    }
  }
}

//
void texture_fill(NxdrawTexture *self, NxdrawColour colour) {
  // FIXME iterates over every pixel and is therefore extremely wasteful
  // use memcpy ?
  // use a second "empty buffer" and bulk copy ? (wastes memory)
  for (int y = 0; y < self->height; y++) {
    for (int x = 0; x < self->width; x++) {
      texture_set_pixel(self, x, y, colour);
    }
  }
}

#endif