#ifndef ENGINE_ENGINE_H
#define ENGINE_ENGINE_H

#include <GLFW/glfw3.h>
#include <stdio.h>
#include <stdlib.h>

#include "colour.h"
#include "draw.h"
#include "texture.h"
//#include "event.h"

#include "image.h"

//#include "callback.h"

void _engine_on_update(double dt) {
  static double counter = 0.0;
  static int fps;
  fps = (int)(1.0 / dt);
  counter = counter + dt;

  if (counter >= 0.5) {
    printf("%i\n", fps);
    counter = 0;
  }
}

void _engine_on_draw(Texture *screen) {
  static int count = 0;
  static Colour cake;

  count += 1;

  for (int x = 0; x < screen->width; x++) {
    for (int y = 0; y < screen->height; y++) {
      for (int z = 0; z < 4; z++) {

        cake.r = (x % 256);
        cake.g = (y % 256);
        cake.b = (x + y - count) % 256;
        texture_set_pixel(screen, x, y, cake);
      }
    }
  }
}

typedef struct {
  GLFWwindow *window;
  int screenWidth;
  int screenHeight;
  char *title;
  unsigned int texID;
  unsigned int texWidth;
  unsigned int texHeight;
  // unsigned char(*tex);
  Texture *tex;
  // Texture *stamp;
  // int (*on_event)(Event event);
  void (*on_update)(double dt);
  void (*on_draw)(Texture *screen);
  void (*callback_window_size)(GLFWwindow *window, int width, int height);
  void (*callback_key)(GLFWwindow *window, int key, int scancode, int action,
                       int mods);
  void (*callback_text_input)(GLFWwindow *window, unsigned int codepoint);
  void (*callback_cursor_position)(GLFWwindow *window, double xpos,
                                   double ypos);
} Engine;

Engine *newEngine(int winW, int winH, int texW, int texH) {
  // Engine *self = malloc(sizeof(*self));
  Engine *self = (Engine *)calloc(1, sizeof(*self));
  self->screenWidth = winW;
  self->screenHeight = winH;
  self->texWidth = texW;
  self->texHeight = texH;

  self->tex = newTexture(self->texWidth, self->texHeight);

  self->title = "testing";
  // engine_init(self);
  return self;
}

/*
void engine_testdraw(Engine *self)
{
    static int count = 0;
    static Colour cake;

    count += 1;

    for (int x = 0; x < self->texWidth; x++)
    {
        for (int y = 0; y < self->texHeight; y++)
        {
            for (int z = 0; z < 4; z++)
            {

                cake.r = (x % 256);
                cake.g = (y % 256);
                cake.b = (x + y - count) % 256;
                texture_set_pixel(self->tex, x, y, cake);
            }
        }
    }

    draw_line(self->tex, 3, 1, 1, 3, COLOUR_WHITE);
    draw_line(self->tex, 64, 64, 128, 100, COLOUR_WHITE);
    draw_circle(self->tex, 32, 32, 8, 0377, COLOUR_WHITE);
    draw_rectangle(self->tex, 16, 16, 8, 8, COLOUR_WHITE);
    draw_triangle(self->tex, 10,10, 20,20, 10, 20, COLOUR_WHITE);

    //texture_stamp(self->stamp, self->tex, 3,3,1);
    //texture_stamp(self->tex, self->stamp, (count)%(self->texWidth), 48,1);
}
*/

int engine_init(Engine *self, int resizable) {

  if (!glfwInit())
    return -1;

  if (resizable) {
    glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);
  } else {
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
  }

  // glfwWindowHint(GLFW_DOUBLEBUFFER, GL_FALSE );
  // glfwWindowHint(GLFW_REFRESH_RATE, 60);
  // glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 1);
  // glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);

  self->window = glfwCreateWindow(self->screenWidth, self->screenHeight,
                                  self->title, NULL, NULL);
  if (!self->window) {
    glfwTerminate();
    return -1;
  }

  glfwSetWindowSizeCallback(self->window, self->callback_window_size);
  glfwSetKeyCallback(self->window, self->callback_key);
  glfwSetCharCallback(self->window, self->callback_text_input);
  glfwSetCursorPosCallback(self->window, self->callback_cursor_position);

  self->on_update = _engine_on_update;
  self->on_draw = _engine_on_draw;

  // Texture* cake = image_load_png("kprey.png");
  // if (cake != NULL){
  //    self->stamp = cake;
  //}else{
  //    self->stamp = newTexture(16,16);
  //    draw_triangle(self->stamp, 1,1,14,14,1,14, COLOUR_GREEN);
  //}

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

void engine_draw(Engine *self) {
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

void engine_tick(Engine *self) {
  static double lastTime = 0;
  static double dt = 0;
  static double nowTime = 0;
  // static int fps = 0;

  // static double counter = 0.0;

  // counter = counter + dt;

  nowTime = glfwGetTime();
  dt = (nowTime - lastTime);
  lastTime = nowTime;

  /*
  fps = (int)(1.0 / dt);

  //printf("%f\n", dt);
  if (counter >= 0.5)
  {
      printf("%i\n", fps);
      counter = 0;
  }
  */

  self->on_update(dt);
  engine_draw(self);

  glfwPollEvents();
}

void engine_run(Engine *self) {
  while (!glfwWindowShouldClose(self->window)) {
    engine_tick(self);
  }

  glfwTerminate();
}

#endif
