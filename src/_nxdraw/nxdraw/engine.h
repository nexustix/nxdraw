#ifndef NXDRAW_ENGINE_H
#define NXDRAW_ENGINE_H

#include <GLFW/glfw3.h>
#include <stdio.h>
#include <stdlib.h>

#include "colour.h"
#include "draw.h"
#include "texture.h"
//#include "event.h"

#include "event_bridge.h"
#include "image.h"

//#include "callback.h"

void _nxdraw_engine_on_update(double dt) {}

void _nxdraw_engine_on_draw(NxdrawTexture *screen) {}

typedef struct {
  GLFWwindow *window;
  int screenWidth;
  int screenHeight;
  char *title;
  unsigned int texID;
  unsigned int texWidth;
  unsigned int texHeight;
  double pixelWidth;
  double pixelHeight;
  NxdrawTexture *tex;
  // NxdrawTexture *stamp;
  // int (*on_event)(Event event);
  void (*on_update)(double dt);
  void (*on_draw)(NxdrawTexture *screen);
} NxdrawEngine;

NxdrawEngine *newNxdrawEngine(int winW, int winH, int texW, int texH) {
  // NxdrawEngine *self = malloc(sizeof(*self));
  NxdrawEngine *self = (NxdrawEngine *)calloc(1, sizeof(*self));
  self->screenWidth = winW;
  self->screenHeight = winH;
  self->texWidth = texW;
  self->texHeight = texH;

  self->tex = newNxdrawTexture(self->texWidth, self->texHeight);

  self->title = "nxdraw test";

  self->on_update = _nxdraw_engine_on_update;
  self->on_draw = _nxdraw_engine_on_draw;
  // engine_init(self);
  return self;
}

int nxdraw_engine_init(NxdrawEngine *self, int resizable) {

  if (!glfwInit())
    return -1;

  if (resizable) {
    glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);
  } else {
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
  }

  // glfwWindowHint(GLFW_DOUBLEBUFFER, GL_FALSE );
  // glfwWindowHint(GLFW_REFRESH_RATE, 60);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 1);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);

  self->window = glfwCreateWindow(self->screenWidth, self->screenHeight,
                                  self->title, NULL, NULL);
  if (!self->window) {
    glfwTerminate();
    return -1;
  }

  nxdraw_event_bridge_init();
  glfwSetKeyCallback(self->window, nxdraw_event_bridge_key);
  glfwSetCharCallback(self->window, nxdraw_event_bridge_character);
  glfwSetCursorPosCallback(self->window, nxdraw_event_bridge_mousepos);
  glfwSetMouseButtonCallback(self->window, nxdraw_event_bridge_mousebutton);

  glfwMakeContextCurrent(self->window);

  glEnable(GL_TEXTURE_2D);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  // glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);

  glGenTextures(1, &self->texID);
  // glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, self->texWidth, self->screenHeight,
  // 0, GL_RGBA, GL_UNSIGNED_BYTE, self->tex);

  glfwSwapInterval(1);
  return 0;
}

void nxdraw_engine_draw(NxdrawEngine *self) {
  // FIXME put into screen resolution change handler
  self->pixelWidth = (double)self->screenWidth / (double)self->texWidth;
  self->pixelHeight = (double)self->screenHeight / (double)self->texHeight;

  glClear(GL_COLOR_BUFFER_BIT);

  // engine_testdraw(self);
  self->on_draw(self->tex);

  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, self->texWidth, self->texHeight, 0,
               GL_RGBA, GL_UNSIGNED_BYTE, self->tex->data);

  // glColor3d(0.5f, 0.25f, 0.0f);

  glBegin(GL_TRIANGLES);
  glTexCoord2f(0.0, 1.0); // 01
  glVertex2f(-1.0f, -1.0f);
  glTexCoord2f(0.0, 0.0); // 00
  glVertex2f(-1.0f, 1.0f);
  glTexCoord2f(1.0, 1.0); // 11
  glVertex2f(1.0f, -1.0f);
  glTexCoord2f(1.0, 1.0); // 11
  glVertex2f(1.0f, -1.0f);
  glTexCoord2f(0.0, 0.0); // 00
  glVertex2f(-1.0f, 1.0f);
  glTexCoord2f(1.0, 0.0); // 10
  glVertex2f(1.0f, 1.0f);
  glEnd();

  glfwSwapBuffers(self->window);
  // glFlush();
}

void nxdraw_engine_tick(NxdrawEngine *self) {
  static double lastTime = 0;
  static double dt = 0;
  static double nowTime = 0;

  nowTime = glfwGetTime();
  dt = (nowTime - lastTime);
  lastTime = nowTime;

  self->on_update(dt);
  nxdraw_engine_draw(self);

  glfwPollEvents();
}

void nxdraw_engine_run(NxdrawEngine *self) {
  while (!glfwWindowShouldClose(self->window)) {
    nxdraw_engine_tick(self);
  }

  glfwTerminate();
}

#endif
