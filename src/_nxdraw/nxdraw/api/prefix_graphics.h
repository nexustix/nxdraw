#ifndef NXDRAW_GRAPHICS_H
#define NXDRAW_GRAPHICS_H

#include "../colour.h"
#include "../draw.h"
#include "../engine.h"
#include "../image.h"
#include "../texture.h"

#include "../event.h"
#include "../event_bridge.h"
#include "../event_buffer.h"
#include "nxdraw/fonts/ascii/thin.h"

#include <GLFW/glfw3.h>

#ifndef NXDRAW_EVENT_H
typedef enum NxdrawEventKind {
  NXDRAW_EVENT_VOID,
  NXDRAW_EVENT_UNKNOWN,
  NXDRAW_EVENT_KEY_DOWN,
  NXDRAW_EVENT_KEY_UP,
  NXDRAW_EVENT_KEY_HELT,
  NXDRAW_EVENT_TEXT,
  NXDRAW_EVENT_MOUSE_MOVE,
  NXDRAW_EVENT_MOUSE_DOWN,
  NXDRAW_EVENT_MOUSE_UP,
} NxdrawEventKind;
#endif

static NxdrawEngine *_nxdraw_graphics_engine;
static int _nxdraw_graphics_initialized = 0;
static NxdrawColour _nxdraw_graphics_palette[256];

static NxdrawTexture **_nxdraw_graphics_textures;
// static NxdrawTexture *_nxdraw_graphics_textures_target = NULL;
static int _nxdraw_graphics_textures_reserve = 0;
static int _nxdraw_graphics_textures_last = 1;

static NxdrawEvent _nxdraw_graphics_event;

int _nxdraw_enlarge_buffer(int size) {
  _nxdraw_graphics_textures = (NxdrawTexture **)realloc(
      _nxdraw_graphics_textures, sizeof(NxdrawTexture *) * size);
  _nxdraw_graphics_textures_reserve = size;
  return 0;
}

int _nxdraw_set_texture(NxdrawTexture *texture) {
  if (_nxdraw_graphics_textures_last >= _nxdraw_graphics_textures_reserve) {
    _nxdraw_enlarge_buffer(_nxdraw_graphics_textures_reserve + 8);
  }
  _nxdraw_graphics_textures[_nxdraw_graphics_textures_last] = texture;
  _nxdraw_graphics_textures_last += 1;
  return _nxdraw_graphics_textures_last - 1;
}

NxdrawTexture *_nxdraw_get_texture(int texture_id) {
  // FIXME assert if exists
  return _nxdraw_graphics_textures[texture_id];
}

// int nxdraw_set_target(unsigned int texture_id) {
//  _nxdraw_graphics_textures_target = _nxdraw_get_texture(texture_id);
//  if (!_nxdraw_graphics_textures_target) {
//    _nxdraw_graphics_textures_target = _nxdraw_graphics_textures[0];
//    return 0;
//  }
//  return 1;
//}

int nxdraw_width(int target) {
  return _nxdraw_graphics_textures[target]->width;
}
int nxdraw_height(int target) {
  return _nxdraw_graphics_textures[target]->height;
}

int nxdraw_graphics(int winW, int winH, int texW, int texH, int resizable) {
  _nxdraw_graphics_engine = newNxdrawEngine(winW, winH, texW, texH);
  nxdraw_engine_init(_nxdraw_graphics_engine, 0);
  _nxdraw_graphics_palette[0].n = 0;
  _nxdraw_graphics_palette[1].n = 0xffffffff;
  _nxdraw_graphics_palette[2].n = 0xff000000;
  _nxdraw_enlarge_buffer(1);
  _nxdraw_graphics_textures[0] = _nxdraw_graphics_engine->tex;
  //_nxdraw_graphics_textures_target = _nxdraw_graphics_textures[0];
  _nxdraw_graphics_event.kind = NXDRAW_EVENT_VOID;
  _nxdraw_graphics_initialized = 1;
  return 0;
}

int nxdraw_set_colour_rgba(int colour_id, unsigned char r, unsigned char g,
                           unsigned char b, unsigned char a) {
  _nxdraw_graphics_palette[colour_id].r = r;
  _nxdraw_graphics_palette[colour_id].g = g;
  _nxdraw_graphics_palette[colour_id].b = b;
  _nxdraw_graphics_palette[colour_id].a = a;
  return 0;
}

int nxdraw_set_colour_rgb(int colour_id, unsigned char r, unsigned char g,
                          unsigned char b) {
  nxdraw_set_colour_rgba(colour_id, r, g, b, 255);
  return 0;
}

int nxdraw_pset(int target, int x, int y, int colour_id) {
  texture_set_pixel(_nxdraw_graphics_textures[target], x, y,
                    _nxdraw_graphics_palette[colour_id]);
  return 0;
}
unsigned long nxdraw_pget(int target, int x, int y) {
  return texture_get_pixel(_nxdraw_graphics_textures[target], x, y).n;
}
int nxdraw_line(int target, int x1, int y1, int x2, int y2, int colour_id) {
  nxdraw_draw_line(_nxdraw_graphics_textures[target], x1, y1, x2, y2,
                   _nxdraw_graphics_palette[colour_id]);
  return 0;
}

int nxdraw_hline(int target, int x1, int y1, int w, int colour_id) {
  nxdraw_draw_hline(_nxdraw_graphics_textures[target], x1, y1, w,
                    _nxdraw_graphics_palette[colour_id]);
  return 0;
}
int nxdraw_vline(int target, int x1, int y1, int h, int colour_id) {
  nxdraw_draw_vline(_nxdraw_graphics_textures[target], x1, y1, h,
                    _nxdraw_graphics_palette[colour_id]);
  return 0;
}

int nxdraw_rectangle(int target, int x, int y, int w, int h, int colour_id) {
  nxdraw_draw_filled_rectangle(_nxdraw_graphics_textures[target], x, y, w, h,
                               _nxdraw_graphics_palette[colour_id]);

  return 0;
}
int nxdraw_rectangleb(int target, int x, int y, int w, int h, int colour_id) {
  nxdraw_draw_rectangle(_nxdraw_graphics_textures[target], x, y, w, h,
                        _nxdraw_graphics_palette[colour_id]);
  return 0;
}

int nxdraw_circle(int target, int x, int y, int r, int colour_id) {
  nxdraw_draw_filled_circle(_nxdraw_graphics_textures[target], x, y, r, 0xff,
                            _nxdraw_graphics_palette[colour_id]);
  return 0;
}
int nxdraw_circleb(int target, int x, int y, int r, int colour_id) {
  nxdraw_draw_circle(_nxdraw_graphics_textures[target], x, y, r, 0xff,
                     _nxdraw_graphics_palette[colour_id]);
  return 0;
}

int nxdraw_triangle(int target, int x1, int y1, int x2, int y2, int x3, int y3,
                    int colour_id) {
  nxdraw_draw_filled_triangle(_nxdraw_graphics_textures[target], x1, y1, x2, y2,
                              x3, y3, _nxdraw_graphics_palette[colour_id]);
  return 0;
}
int nxdraw_triangleb(int target, int x1, int y1, int x2, int y2, int x3, int y3,
                     int colour_id) {
  nxdraw_draw_triangle(_nxdraw_graphics_textures[target], x1, y1, x2, y2, x3,
                       y3, _nxdraw_graphics_palette[colour_id]);
  return 0;
}

int nxdraw_clear(int target, int colour_id) {
  texture_fill(_nxdraw_graphics_textures[target],
               _nxdraw_graphics_palette[colour_id]);
  return 0;
}

int nxdraw_load_image(const char *path) {
  return _nxdraw_set_texture(nxdraw_image_load_png(path));
}

int nxdraw_texture(int width, int height) {
  return _nxdraw_set_texture(newNxdrawTexture(width, height));
}

int nxdraw_blit(int target, int x, int y, unsigned int source) {
  texture_blit(_nxdraw_graphics_textures[target],
               _nxdraw_graphics_textures[source], x, y, 1);
  return 0;
}

int nxdraw_printchar_ascii(int target, int x, int y, unsigned char c,
                           unsigned int colour_fg, unsigned int colour_bg) {
  nxdraw_draw_bitmap_8_8(_nxdraw_graphics_textures[target], x, y, ascii_thin[c],
                         _nxdraw_graphics_palette[colour_fg],
                         _nxdraw_graphics_palette[colour_bg]);
  return 0;
}

int nxdraw_printstring_ascii(int target, int x, int y, char *str,
                             unsigned int colour_fg, unsigned int colour_bg) {
  for (int i = 0; i < strlen(str); i++) {
    nxdraw_printchar_ascii(target, x + (8 * i), y, str[i], colour_fg,
                           colour_bg);
  }
  return 0;
}

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
int nxdraw_show() {
  nxdraw_engine_draw(_nxdraw_graphics_engine);
  glfwPollEvents();
  return 0;
  return 0;
}

int nxdraw_running() {
  return !glfwWindowShouldClose(_nxdraw_graphics_engine->window);
}

int nxdraw_poll_event() {
  _nxdraw_graphics_event = nxdraw_event_bridge_pop();
  if (_nxdraw_graphics_event.kind == NXDRAW_EVENT_MOUSE_MOVE) {
    _nxdraw_graphics_event.x =
        _nxdraw_graphics_event.x / _nxdraw_graphics_engine->pixelWidth;
    _nxdraw_graphics_event.y =
        _nxdraw_graphics_event.y / _nxdraw_graphics_engine->pixelHeight;
  }
  return _nxdraw_graphics_event.kind;
}

int nxdraw_event_kind() { return _nxdraw_graphics_event.kind; }
int nxdraw_event_key() { return _nxdraw_graphics_event.key; }
int nxdraw_event_button() { return _nxdraw_graphics_event.button; }
int nxdraw_event_mods() { return _nxdraw_graphics_event.mods; }
unsigned int nxdraw_event_codepoint() {
  return _nxdraw_graphics_event.codepoint;
}
double nxdraw_event_x() { return _nxdraw_graphics_event.x; }
double nxdraw_event_y() { return _nxdraw_graphics_event.y; }

#endif