#include "nxdraw/colour.h"
//#include "nxdraw/draw.h"
#include "nxdraw/engine.h"
#include "nxdraw/graphics.h"
#include <stdio.h>

int main(int argc, const char *argv[]) {
  double dt;
  Engine *engine = graphics(320 * 4, 200 * 4, 320, 200);

  while (running(engine)) {
    dt = limit(60);
    printf("%lf\n", 1 / dt);
    clear(engine->tex, COLOUR_BLACK);
    rectangle(engine->tex, 10, 10, 10, 10, COLOUR_WHITE);
    rectangleb(engine->tex, 10, 10, 10, 10, COLOUR_RED);
    line(engine->tex, 10, 10, 40, 40, COLOUR_GREEN);
    triangle(engine->tex, 100, 150, 50, 50, 20, 100, COLOUR_RED);

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


void on_draw(Texture *screen) {
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


int main(int argc, const char *argv[]) {
  // Engine *engine = newEngine(320 * 4, 200 * 4, 320, 200);
  Engine *engine = newEngine(320, 200, 320, 200);
  engine_init(engine, 0);
  engine->on_draw = on_draw;
  engine->on_update = on_update;

  engine_run(engine);

  return 0;
}

// For legacy Microsoft Operating System support
int WinMain(int argc, const char *argv[]) { return main(argc, argv); }
*/