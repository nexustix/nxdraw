#ifndef NXDRAW_COLOUR_H
#define NXDRAW_COLOUR_H

#include <stdint.h>

typedef struct {
  union {
    uint32_t n;
    struct {
      uint8_t r;
      uint8_t g;
      uint8_t b;
      uint8_t a;
    };
  };
} Colour;

Colour makeColour(unsigned char r, unsigned char g, unsigned char b,
                  unsigned char a) {
  Colour self;

  self.r = r;
  self.g = g;
  self.b = b;
  self.a = a;

  return self;
}

Colour makeColour_opaque(unsigned char r, unsigned char g, unsigned char b) {
  Colour self;

  self.r = r;
  self.g = g;
  self.b = b;
  self.a = 0xff;

  return self;
}

const Colour COLOUR_BLACK = {{0xff000000}};
const Colour COLOUR_WHITE = {{0xffffffff}};
const Colour COLOUR_RED = {{0xff0000ff}};
const Colour COLOUR_GREEN = {{0xff00ff00}};
const Colour COLOUR_BLUE = {{0xffff0000}};

#endif