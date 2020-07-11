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
} NxdrawColour;

NxdrawColour makeNxdrawColour(unsigned char r, unsigned char g, unsigned char b,
                              unsigned char a) {
  NxdrawColour self;

  self.r = r;
  self.g = g;
  self.b = b;
  self.a = a;

  return self;
}

NxdrawColour makeNxdrawColour_opaque(unsigned char r, unsigned char g,
                                     unsigned char b) {
  NxdrawColour self;

  self.r = r;
  self.g = g;
  self.b = b;
  self.a = 0xff;

  return self;
}

const NxdrawColour NXDRAW_COLOUR_BLACK = {{0xff000000}};
const NxdrawColour NXDRAW_COLOUR_WHITE = {{0xffffffff}};
const NxdrawColour NXDRAW_COLOUR_RED = {{0xff0000ff}};
const NxdrawColour NXDRAW_COLOUR_GREEN = {{0xff00ff00}};
const NxdrawColour NXDRAW_COLOUR_BLUE = {{0xffff0000}};

const NxdrawColour NXDRAW_COLOUR_CYAN = {{0xffffff00}};
const NxdrawColour NXDRAW_COLOUR_MAGENTA = {{0xffff00ff}};
const NxdrawColour NXDRAW_COLOUR_YELLOW = {{0xff00ffff}};

const NxdrawColour NXDRAW_COLOUR_AMBER = {{0xff0073ff}};

const NxdrawColour NXDRAW_COLOUR_NONE = {{0x00000000}};

#endif