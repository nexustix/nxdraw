
//#include "nxdraw/draw.h"
//#include "nxdraw/image.h"
// 00001:E0 80 EA 2A EE 0A 0A 00
//        8 16    32          64

#include "nxdraw/api/graphics.h"
#include "nxdraw/colour.h"
#include "nxdraw/engine.h"
#include <stdio.h>

int main(int argc, const char *argv[]) {
  double dt;
  NxdrawEngine *engine = graphics(320 * 4, 200 * 4, 320, 200);
  NxdrawEvent e;
  NxdrawTexture *cake = load_image("assets/floor_a.png");
  double x = 10;
  unsigned int mx = 0;
  unsigned int my = 0;
  int ms = 0;

  while (running(engine)) {
    dt = limit(60);
    // printf("%lf\n", 1 / dt);
    // printf("%lfx%lf\n", engine->pixelWidth, engine->pixelHeight);
    x = (x + dt * 100);

    clear(engine->tex, COLOUR_BLACK);

    // pset(engine->tex, -100, -20, COLOUR_WHITE);

    rectangle(engine->tex, 10, 10, 10, 10, COLOUR_WHITE);
    rectangleb(engine->tex, 10, 10, 10, 10, COLOUR_RED);

    circle(engine->tex, 40, 40, 8, COLOUR_WHITE);
    circleb(engine->tex, 40, 40, 8, COLOUR_RED);

    triangle(engine->tex, 100, 150, 50, 50, 20, 100, COLOUR_WHITE);
    triangleb(engine->tex, 100, 150, 50, 50, 20, 100, COLOUR_RED);

    line(engine->tex, 10, 10, 40, 40, COLOUR_GREEN);
    hline(engine->tex, 10, 100, 5, COLOUR_WHITE);
    vline(engine->tex, 10, 100, 5, COLOUR_WHITE);

    blit(engine->tex, ((int)x) % 320, 50, cake);
    if (ms) {
      circle(engine->tex, mx, my, 3, COLOUR_RED);
    } else {
      circle(engine->tex, mx, my, 3, COLOUR_WHITE);
    }
    // rectangle(engine->tex, mx, my, 3, 3, COLOUR_WHITE);

    e = poll_event(engine);
    while (e.kind) {
      // printf("(%i)\n", e.kind);
      /*
      if (e.kind == NXDRAW_EVENT_KEY_DOWN) {
        // printf("%i\n", e.key);
      } else {
        // printf("%i h\n", e.kind);
        // printf("(%i) %i h\n", e.kind);
      }
      */
      if (e.kind == NXDRAW_EVENT_MOUSE_MOVE) {
        // printf("%lfx%lf\n", e.x, e.y);

        // circle(engine->tex, (int)e.x, (int)e.y, 3, COLOUR_WHITE);
        mx = (int)e.x;
        my = (int)e.y;
      } else if (e.kind == NXDRAW_EVENT_MOUSE_DOWN) {
        ms = 1;
      } else if (e.kind == NXDRAW_EVENT_MOUSE_UP) {
        ms = 0;
      }
      e = poll_event(engine);
    }

    show(engine);
  }
  return 0;
}

// For legacy Microsoft Operating System support
int WinMain(int argc, const char *argv[]) { return main(argc, argv); }

/*
void on_update(double dt) {
  static double counter = 0.0;
  static int fps;
  fps = (int)(1.0 / dt);
  counter = counter + dt;

  if (counter >= 0.5) {
    printf("%i\n", fps);
    counter = 0;
  }
}


void on_draw(NxdrawTexture *screen) {
  static int count = 0;
  static NxdrawColour cake;

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


int main(int argc, const char *argv[]) {
  // NxdrawEngine *engine = newNxdrawEngine(320 * 4, 200 * 4, 320, 200);
  NxdrawEngine *engine = newNxdrawEngine(320, 200, 320, 200);
  engine_init(engine, 0);
  engine->on_draw = on_draw;
  engine->on_update = on_update;

  engine_run(engine);

  return 0;
}

// For legacy Microsoft Operating System support
int WinMain(int argc, const char *argv[]) { return main(argc, argv); }
*/