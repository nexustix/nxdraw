#ifndef ENGINE_DRAW_H
#define ENGINE_DRAW_H

#include "colour.h"
#include "texture.h"

void draw_pixel(Texture *texture, int x, int y, Colour colour) {
  // texture_put_pixel(texture, x, y, c.r, c.g, c.b, c.a);
  texture_set_pixel(texture, x, y, colour);
}

void draw_line(Texture *texture, int x1, int y1, int x2, int y2,
               Colour colour) {
  int i, dx, dy, sdx, sdy, dxabs, dyabs, x, y, px, py;

  dx = x2 - x1;            // Delta x
  dy = y2 - y1;            // Delta y
  dxabs = abs(dx);         // Absolute delta
  dyabs = abs(dy);         // Absolute delta
  sdx = (dx > 0) ? 1 : -1; // signum function
  sdy = (dy > 0) ? 1 : -1; // signum function
  x = dyabs >> 1;
  y = dxabs >> 1;
  px = x1;
  py = y1;

  draw_pixel(texture, x1, y1, colour);

  if (dxabs >= dyabs) {
    for (i = 0; i < dxabs; i++) {
      y += dyabs;
      if (y >= dxabs) {
        y -= dxabs;
        py += sdy;
      }
      px += sdx;
      draw_pixel(texture, px, py, colour);
    }
  } else {
    for (i = 0; i < dyabs; i++) {
      x += dxabs;
      if (x >= dyabs) {
        x -= dyabs;
        px += sdx;
      }
      py += sdy;
      draw_pixel(texture, px, py, colour);
    }
  }
}

void draw_circle(Texture *texture, int x, int y, int r, unsigned char mask,
                 Colour colour) {
  int x0 = 0;
  int y0 = r;
  int d = 3 - 2 * r;
  if (r <= 0)
    return;

  while (y0 >= x0) {
    // select wich octants to draw by mask
    if (mask & 0x01) {
      draw_pixel(texture, x + x0, y - y0, colour);
    }
    if (mask & 0x02) {
      draw_pixel(texture, x + y0, y - x0, colour);
    }
    if (mask & 0x04) {
      draw_pixel(texture, x + y0, y + x0, colour);
    }
    if (mask & 0x08) {
      draw_pixel(texture, x + x0, y + y0, colour);
    }
    if (mask & 0x10) {
      draw_pixel(texture, x - x0, y + y0, colour);
    }
    if (mask & 0x20) {
      draw_pixel(texture, x - y0, y + x0, colour);
    }
    if (mask & 0x40) {
      draw_pixel(texture, x - y0, y - x0, colour);
    }
    if (mask & 0x80) {
      draw_pixel(texture, x - x0, y - y0, colour);
    }
    if (d < 0)
      d += 4 * x0++ + 6;
    else
      d += 4 * (x0++ - y0--) + 10;
  }
}

void draw_rectangle(Texture *texture, int x, int y, int w, int h,
                    Colour colour) {
  draw_line(texture, x, y, x + w, y, colour);
  draw_line(texture, x, y, x, y + h, colour);
  draw_line(texture, x + w, y + h, x + w, y, colour);
  draw_line(texture, x + w, y + h, x, y + h, colour);
}

void draw_triangle(Texture *texture, int x1, int y1, int x2, int y2, int x3,
                   int y3, Colour colour) {
  draw_line(texture, x1, y1, x2, y2, colour);
  draw_line(texture, x2, y2, x3, y3, colour);
  draw_line(texture, x3, y3, x1, y1, colour);
}

void draw_quad(Texture *texture, int x1, int y1, int x2, int y2, int x3, int y3,
               int x4, int y4, Colour colour) {
  draw_line(texture, x1, y1, x2, y2, colour);
  draw_line(texture, x2, y2, x3, y3, colour);
  draw_line(texture, x3, y3, x4, y4, colour);
  draw_line(texture, x4, y4, x1, y1, colour);
}

#endif