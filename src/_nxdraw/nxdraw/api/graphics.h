#ifndef NXDRAW_GRAPHICS_H
#define NXDRAW_GRAPHICS_H

/*
#include "../colour.h"
#include "../draw.h"
#include "../engine.h"
#include "../image.h"
#include "../texture.h"

#include "../event.h"
#include "../event_bridge.h"
#include "../event_buffer.h"
*/

#include "prefix_graphics.h"

//#include <GLFW/glfw3.h>

// static NxdrawEngine *engine;

// initialize graphics
NxdrawEngine *graphics(int winW, int winH, int texW, int texH) {
  return nxdraw_graphics(winW, winH, texW, texH);
}

// set pixel
int pset(NxdrawTexture *target, int x, int y, NxdrawColour colour) {
  return nxdraw_pset(target, x, y, colour);
}

// get pixel
NxdrawColour pget(NxdrawTexture *target, int x, int y) {
  return nxdraw_pget(target, x, y);
}

// draw line
int line(NxdrawTexture *target, int x1, int y1, int x2, int y2,
         NxdrawColour colour) {
  return nxdraw_line(target, x1, y1, x2, y2, colour);
}
// draw horizontal line
int hline(NxdrawTexture *target, int x1, int y1, int w, NxdrawColour colour) {
  return nxdraw_hline(target, x1, y1, w, colour);
}
// draw vertical line
int vline(NxdrawTexture *target, int x1, int y1, int h, NxdrawColour colour) {
  return nxdraw_vline(target, x1, y1, h, colour);
}

// draw rectangle
int rectangle(NxdrawTexture *target, int x, int y, int w, int h,
              NxdrawColour colour) {
  return nxdraw_rectangle(target, x, y, w, h, colour);
}

// draw rectangle border
int rectangleb(NxdrawTexture *target, int x, int y, int w, int h,
               NxdrawColour colour) {
  return nxdraw_rectangleb(target, x, y, w, h, colour);
}

// draw circle
int circle(NxdrawTexture *target, int x, int y, int r, NxdrawColour colour) {
  return nxdraw_circle(target, x, y, r, colour);
}

// draw cicrle border
int circleb(NxdrawTexture *target, int x, int y, int r, NxdrawColour colour) {
  return nxdraw_circleb(target, x, y, r, colour);
}

// draw triangle
int triangle(NxdrawTexture *target, int x1, int y1, int x2, int y2, int x3,
             int y3, NxdrawColour colour) {
  return nxdraw_triangle(target, x1, y1, x2, y2, x3, y3, colour);
}

// draw triangle border
int triangleb(NxdrawTexture *target, int x1, int y1, int x2, int y2, int x3,
              int y3, NxdrawColour colour) {
  return nxdraw_triangleb(target, x1, y1, x2, y2, x3, y3, colour);
}

// clear texture with colour
int clear(NxdrawTexture *target, NxdrawColour colour) {
  return nxdraw_clear(target, colour);
}

// draw textured triangle
// int textriangle() { return 0; }

// load image as texture
NxdrawTexture *load_image(const char *path) { return nxdraw_load_image(path); }

// blit texture
int blit(NxdrawTexture *target, int x, int y, NxdrawTexture *source) {
  return nxdraw_blit(target, x, y, source);
}

// put text onto screen
// int putchar_ascii(NxdrawTexture *target, int x, int y, NxdrawColour fg,
// NxdrawColour bg) {
//  return 0;
//}

// FIXME limit FPS, implementation currently uses vsync
double limit(int fps_target) { return nxdraw_limit(fps_target); }

// draw rendering buffer to screen
int show(NxdrawEngine *engine) { return nxdraw_show(engine); }

// check if program still running (quitting not requested)
int running(NxdrawEngine *engine) { return nxdraw_running(engine); }

// poll event
NxdrawEvent poll_event(NxdrawEngine *engine) {
  return nxdraw_poll_event(engine);
}

#endif