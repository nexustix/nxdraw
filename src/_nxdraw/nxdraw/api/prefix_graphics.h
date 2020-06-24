#ifndef NXDRAW_PREFIX_GRAPHICS_H
#define NXDRAW_PREFIX_GRAPHICS_H

#include "../colour.h"
#include "../draw.h"
#include "../engine.h"
#include "../image.h"
#include "../texture.h"

#include "../event.h"
#include "../event_bridge.h"
#include "../event_buffer.h"
#include "nxdraw/fonts/ascii/thin.h"

//#include <GLFW/glfw3.h>

// static NxdrawEngine *engine;

// initialize graphics
NxdrawEngine *nxdraw_graphics(int winW, int winH, int texW, int texH) {
  NxdrawEngine *engine = newNxdrawEngine(winW, winH, texW, texH);
  nxdraw_engine_init(engine, 0);

  return engine;
}

// set pixel
int nxdraw_pset(NxdrawTexture *target, int x, int y, NxdrawColour colour) {
  texture_set_pixel(target, x, y, colour);
  return 0;
}

// get pixel
NxdrawColour nxdraw_pget(NxdrawTexture *target, int x, int y) {
  return texture_get_pixel(target, x, y);
}

// draw line
int nxdraw_line(NxdrawTexture *target, int x1, int y1, int x2, int y2,
                NxdrawColour colour) {
  nxdraw_draw_line(target, x1, y1, x2, y2, colour);
  return 0;
}
int nxdraw_hline(NxdrawTexture *target, int x1, int y1, int w,
                 NxdrawColour colour) {
  nxdraw_draw_hline(target, x1, y1, w, colour);
  return 0;
}
int nxdraw_vline(NxdrawTexture *target, int x1, int y1, int h,
                 NxdrawColour colour) {
  nxdraw_draw_vline(target, x1, y1, h, colour);
  return 0;
}

// draw rectangle
int nxdraw_rectangle(NxdrawTexture *target, int x, int y, int w, int h,
                     NxdrawColour colour) {
  nxdraw_draw_filled_rectangle(target, x, y, w, h, colour);
  return 0;
}

// draw rectangle border
int nxdraw_rectangleb(NxdrawTexture *target, int x, int y, int w, int h,
                      NxdrawColour colour) {
  nxdraw_draw_rectangle(target, x, y, w, h, colour);
  return 0;
}

// draw circle
int nxdraw_circle(NxdrawTexture *target, int x, int y, int r,
                  NxdrawColour colour) {
  nxdraw_draw_filled_circle(target, x, y, r, 0xff, colour);
  return 0;
}

// draw cicrle border
int nxdraw_circleb(NxdrawTexture *target, int x, int y, int r,
                   NxdrawColour colour) {
  nxdraw_draw_circle(target, x, y, r, 0xff, colour);
  return 0;
}

// draw triangle
int nxdraw_triangle(NxdrawTexture *target, int x1, int y1, int x2, int y2,
                    int x3, int y3, NxdrawColour colour) {
  nxdraw_draw_filled_triangle(target, x1, y1, x2, y2, x3, y3, colour);
  return 0;
}

// draw triangle border
int nxdraw_triangleb(NxdrawTexture *target, int x1, int y1, int x2, int y2,
                     int x3, int y3, NxdrawColour colour) {
  nxdraw_draw_triangle(target, x1, y1, x2, y2, x3, y3, colour);
  return 0;
}

// clear texture with colour
int nxdraw_clear(NxdrawTexture *target, NxdrawColour colour) {
  texture_fill(target, colour);
  return 0;
}

// draw textured triangle
// int textriangle() { return 0; }

NxdrawTexture *nxdraw_load_image(const char *path) {
  return nxdraw_image_load_png(path);
}

// blit texture
int nxdraw_blit(NxdrawTexture *target, int x, int y, NxdrawTexture *source) {
  texture_blit(target, source, x, y, 1);
  return 0;
}

// put text onto screen
int nxdraw_printchar_ascii(NxdrawTexture *target, int x, int y, unsigned char c,
                           NxdrawColour fg, NxdrawColour bg) {
  nxdraw_draw_bitmap_8_8(target, x, y, ascii_thin[c], fg, bg);
  return 0;
}

int nxdraw_printstring_ascii(NxdrawTexture *target, int x, int y, char *str,
                             NxdrawColour fg, NxdrawColour bg) {
  for (int i = 0; i < strlen(str); i++) {
    nxdraw_printchar_ascii(target, x + (8 * i), y, str[i], fg, bg);
  }
  return 0;
}

// FIXME limit FPS, implementation currently uses vsync
double nxdraw_limit(int fps_target) {
  static double lastTime = 0;
  static double dt = 0;
  static double nowTime = 0;
  nowTime = glfwGetTime();
  dt = (nowTime - lastTime);
  lastTime = nowTime;
  // TODO do FPS limiting voodoo here
  return dt;
}

int nxdraw_show(NxdrawEngine *engine) {
  nxdraw_engine_draw(engine);
  glfwPollEvents();
  return 0;
}

int nxdraw_running(NxdrawEngine *engine) {
  return !glfwWindowShouldClose(engine->window);
}

NxdrawEvent nxdraw_poll_event(NxdrawEngine *engine) {
  NxdrawEvent e = nxdraw_event_bridge_pop();
  if (e.kind == NXDRAW_EVENT_MOUSE_MOVE) {
    e.x = e.x / engine->pixelWidth;
    e.y = e.y / engine->pixelHeight;
  }
  return e;
}

#endif