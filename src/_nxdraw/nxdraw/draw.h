#ifndef NXDRAW_DRAW_H
#define NXDRAW_DRAW_H

#include "colour.h"
#include "texture.h"

void nxdraw_draw_pixel(NxdrawTexture *texture, int x, int y,
                       NxdrawColour colour) {
  // texture_put_pixel(texture, x, y, c.r, c.g, c.b, c.a);
  if (colour.a == 0xff) {
    texture_set_pixel(texture, x, y, colour);
  } else {
    texture_put_pixel_alpha(texture, x, y, colour);
  }
}

void nxdraw_draw_hline(NxdrawTexture *texture, int x1, int y1, int w,
                       NxdrawColour colour) {
  for (int ix = x1; ix < x1 + w; ix++) {
    nxdraw_draw_pixel(texture, ix, y1, colour);
  }
}
void nxdraw_draw_vline(NxdrawTexture *texture, int x1, int y1, int h,
                       NxdrawColour colour) {
  for (int iy = y1; iy < y1 + h; iy++) {
    nxdraw_draw_pixel(texture, x1, iy, colour);
  }
}

void nxdraw_draw_line(NxdrawTexture *texture, int x1, int y1, int x2, int y2,
                      NxdrawColour colour) {
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

  nxdraw_draw_pixel(texture, x1, y1, colour);

  if (dxabs >= dyabs) {
    for (i = 0; i < dxabs; i++) {
      y += dyabs;
      if (y >= dxabs) {
        y -= dxabs;
        py += sdy;
      }
      px += sdx;
      nxdraw_draw_pixel(texture, px, py, colour);
    }
  } else {
    for (i = 0; i < dyabs; i++) {
      x += dxabs;
      if (x >= dyabs) {
        x -= dyabs;
        px += sdx;
      }
      py += sdy;
      nxdraw_draw_pixel(texture, px, py, colour);
    }
  }
}

void nxdraw_draw_circle(NxdrawTexture *texture, int x, int y, int r,
                        unsigned char mask, NxdrawColour colour) {
  int x0 = 0;
  int y0 = r;
  int d = 3 - 2 * r;
  if (r > 0) {

    while (y0 >= x0) {
      // select wich octants to draw by mask
      if (mask & 0x01) {
        nxdraw_draw_pixel(texture, x + x0, y - y0, colour);
      }
      if (mask & 0x02) {
        nxdraw_draw_pixel(texture, x + y0, y - x0, colour);
      }
      if (mask & 0x04) {
        nxdraw_draw_pixel(texture, x + y0, y + x0, colour);
      }
      if (mask & 0x08) {
        nxdraw_draw_pixel(texture, x + x0, y + y0, colour);
      }
      if (mask & 0x10) {
        nxdraw_draw_pixel(texture, x - x0, y + y0, colour);
      }
      if (mask & 0x20) {
        nxdraw_draw_pixel(texture, x - y0, y + x0, colour);
      }
      if (mask & 0x40) {
        nxdraw_draw_pixel(texture, x - y0, y - x0, colour);
      }
      if (mask & 0x80) {
        nxdraw_draw_pixel(texture, x - x0, y - y0, colour);
      }
      if (d < 0)
        d += 4 * x0++ + 6;
      else
        d += 4 * (x0++ - y0--) + 10;
    }
  } else {
    nxdraw_draw_pixel(texture, x, y, colour);
  }
}

/*
  adapted from:
  https://github.com/OneLoneCoder/olcPixelGameNxdrawEngine/blob/master/olcPixelGameNxdrawEngine.h#L1620
*/
void nxdraw_draw_filled_circle(NxdrawTexture *texture, int x, int y, int r,
                               unsigned char mask, NxdrawColour colour) {
  if (r > 0) {
    int x0 = 0;
    int y0 = r;
    int d = 3 - 2 * r;

    while (y0 >= x0) {
      nxdraw_draw_line(texture, x - y0, y - x0, x + y0, y - x0, colour);
      if (x0 > 0)
        nxdraw_draw_line(texture, x - y0, y + x0, x + y0, y + x0, colour);

      if (d < 0)
        d += 4 * x0++ + 6;
      else {
        if (x0 != y0) {
          nxdraw_draw_line(texture, x - x0, y - y0, x + x0, y - y0, colour);
          nxdraw_draw_line(texture, x - x0, y + y0, x + x0, y + y0, colour);
        }
        d += 4 * (x0++ - y0--) + 10;
      }
    }
  } else {
    nxdraw_draw_pixel(texture, x, y, colour);
  }
}

void nxdraw_draw_rectangle(NxdrawTexture *texture, int x, int y, int w, int h,
                           NxdrawColour colour) {
  w = w - 1;
  h = h - 1;
  nxdraw_draw_line(texture, x, y, x + w, y, colour);
  nxdraw_draw_line(texture, x, y, x, y + h, colour);
  nxdraw_draw_line(texture, x + w, y + h, x + w, y, colour);
  nxdraw_draw_line(texture, x + w, y + h, x, y + h, colour);
}

// FIXME use something like memcpy ?
void nxdraw_draw_filled_rectangle(NxdrawTexture *texture, int x, int y, int w,
                                  int h, NxdrawColour colour) {
  for (int iy = y; iy < w + y; iy++) {
    for (int ix = x; ix < h + x; ix++) {
      nxdraw_draw_pixel(texture, ix, iy, colour);
    }
  }
}

void nxdraw_draw_triangle(NxdrawTexture *texture, int x1, int y1, int x2,
                          int y2, int x3, int y3, NxdrawColour colour) {
  nxdraw_draw_line(texture, x1, y1, x2, y2, colour);
  nxdraw_draw_line(texture, x2, y2, x3, y3, colour);
  nxdraw_draw_line(texture, x3, y3, x1, y1, colour);
}

void nxdraw_draw_quad(NxdrawTexture *texture, int x1, int y1, int x2, int y2,
                      int x3, int y3, int x4, int y4, NxdrawColour colour) {
  nxdraw_draw_line(texture, x1, y1, x2, y2, colour);
  nxdraw_draw_line(texture, x2, y2, x3, y3, colour);
  nxdraw_draw_line(texture, x3, y3, x4, y4, colour);
  nxdraw_draw_line(texture, x4, y4, x1, y1, colour);
}

/*
  adapted from:
  http://www.sunshine2k.de/coding/java/TriangleRasterization/TriangleRasterization.html
*/

int nxdraw_draw_filled_triangle_bottom(NxdrawTexture *target, int x1, int y1,
                                       int x2, int y2, int x3, int y3,
                                       NxdrawColour colour) {
  float invslope1 = ((float)x2 - (float)x1) / ((float)y2 - (float)y1);
  float invslope2 = ((float)x3 - (float)x1) / ((float)y3 - (float)y1);

  float curx1 = x1;
  float curx2 = x1;

  for (int scanlineY = y1 + 1; scanlineY <= y2; scanlineY++) {
    nxdraw_draw_line(target, (int)curx1, scanlineY, (int)curx2, scanlineY,
                     colour);
    curx1 += invslope1;
    curx2 += invslope2;
  }
  return 0;
}

int nxdraw_draw_filled_triangle_top(NxdrawTexture *target, int x1, int y1,
                                    int x2, int y2, int x3, int y3,
                                    NxdrawColour colour) {
  float invslope1 = ((float)x3 - (float)x1) / ((float)y3 - (float)y1);
  float invslope2 = ((float)x3 - (float)x2) / ((float)y3 - (float)y2);

  float curx1 = x3;
  float curx2 = x3;

  for (int scanlineY = y3; scanlineY >= y1; scanlineY--) {
    nxdraw_draw_line(target, (int)curx1, scanlineY, (int)curx2, scanlineY,
                     colour);
    curx1 -= invslope1;
    curx2 -= invslope2;
  }

  return 0;
}

int nxdraw_draw_filled_triangle(NxdrawTexture *target, int x1, int y1, int x2,
                                int y2, int x3, int y3, NxdrawColour colour) {

  int t;
  if (y1 > y2) {
    t = y1;
    y1 = y2;
    y2 = t;
    t = x1;
    x1 = x2;
    x2 = t;
  }
  if (y1 > y3) {
    t = y1;
    y1 = y3;
    y3 = t;
    t = x1;
    x1 = x3;
    x3 = t;
  }
  if (y2 > y3) {
    t = y2;
    y2 = y3;
    y3 = t;
    t = x2;
    x2 = x3;
    x3 = t;
  }

  if (y2 == y3) {
    nxdraw_draw_filled_triangle_bottom(target, x1, y1, x2, y2, x3, y3, colour);
  } else if (y1 == y2) {
    nxdraw_draw_filled_triangle_top(target, x1, y1, x2, y2, x3, y3, colour);
  } else {
    // fallback, split triangle in a top-flat and bottom-flat daw calls
    int x4 = (int)(x1 + ((float)(y2 - y1) / (float)(y3 - y1)) * (x3 - x1));
    int y4 = y2;
    nxdraw_draw_filled_triangle_bottom(target, x1, y1, x2, y2, x4, y4, colour);
    nxdraw_draw_filled_triangle_top(target, x2, y2, x4, y4, x3, y3, colour);
  }
  return 0;
}

#endif