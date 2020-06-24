#ifndef NXDRAW_GRAPHICS_H
#define NXDRAW_GRAPHICS_H

#include "colour.h"
#include "draw.h"
#include "engine.h"
#include "image.h"
#include "texture.h"

#include "event.h"
#include "event_bridge.h"
#include "event_buffer.h"

//#include <GLFW/glfw3.h>

// static Engine *engine;

// initialize graphics
Engine *graphics(int winW, int winH, int texW, int texH) {
  Engine *engine = newEngine(winW, winH, texW, texH);
  engine_init(engine, 0);

  return engine;
}

// set pixel
int pset(Texture *target, int x, int y, Colour colour) {
  texture_set_pixel(target, x, y, colour);
  return 0;
}

// get pixel
Colour pget(Texture *target, int x, int y) {
  return texture_get_pixel(target, x, y);
}

// draw line
int line(Texture *target, int x1, int y1, int x2, int y2, Colour colour) {
  draw_line(target, x1, y1, x2, y2, colour);
  return 0;
}
int hline(Texture *target, int x1, int y1, int w, Colour colour) {
  draw_hline(target, x1, y1, w, colour);
  return 0;
}
int vline(Texture *target, int x1, int y1, int h, Colour colour) {
  draw_vline(target, x1, y1, h, colour);
  return 0;
}

// draw rectangle
int rectangle(Texture *target, int x, int y, int w, int h, Colour colour) {
  draw_filled_rectangle(target, x, y, w, h, colour);
  return 0;
}

// draw rectangle border
int rectangleb(Texture *target, int x, int y, int w, int h, Colour colour) {
  draw_rectangle(target, x, y, w, h, colour);
  return 0;
}

// draw circle
int circle(Texture *target, int x, int y, int r, Colour colour) {
  draw_filled_circle(target, x, y, r, 0xff, colour);
  return 0;
}

// draw cicrle border
int circleb(Texture *target, int x, int y, int r, Colour colour) {
  draw_circle(target, x, y, r, 0xff, colour);
  return 0;
}

// draw triangle
int triangle(Texture *target, int x1, int y1, int x2, int y2, int x3, int y3,
             Colour colour) {
  draw_filled_triangle(target, x1, y1, x2, y2, x3, y3, colour);
  return 0;
}

// draw triangle border
int triangleb(Texture *target, int x1, int y1, int x2, int y2, int x3, int y3,
              Colour colour) {
  draw_triangle(target, x1, y1, x2, y2, x3, y3, colour);
  return 0;
}

// clear texture with colour
int clear(Texture *target, Colour colour) {
  texture_fill(target, colour);
  return 0;
}

// draw textured triangle
// int textriangle() { return 0; }

Texture *load_image(const char *path) { return image_load_png(path); }

// blit texture
int blit(Texture *target, int x, int y, Texture *source) {
  texture_blit(target, source, x, y, 1);
  return 0;
}

// put text onto screen
// int putchar_ascii(Texture *target, int x, int y, Colour fg, Colour bg) {
//  return 0;
//}

// FIXME limit FPS, implementation currently uses vsync
double limit(int fps_target) {
  static double lastTime = 0;
  static double dt = 0;
  static double nowTime = 0;
  nowTime = glfwGetTime();
  dt = (nowTime - lastTime);
  lastTime = nowTime;
  // TODO do FPS limiting voodoo here
  return dt;
}

int show(Engine *engine) {
  engine_draw(engine);
  glfwPollEvents();
  return 0;
}

int running(Engine *engine) { return !glfwWindowShouldClose(engine->window); }

NxdrawEvent poll_event(Engine *engine) {
  NxdrawEvent e = event_bridge_pop();
  if (e.kind == NXDRAW_EVENT_MOUSE_MOVE) {
    e.x = e.x / engine->pixelWidth;
    e.y = e.y / engine->pixelHeight;
  }
  return e;
}

#endif