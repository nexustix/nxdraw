
//#include "nxdraw/draw.h"
//#include "nxdraw/image.h"
// 00001:E0 80 EA 2A EE 0A 0A 00
//        8 16    32          64

//#include "nxdraw/api/graphics.h"
//#include "nxdraw/colour.h"
//#include "nxdraw/engine.h"
#include "nxdraw/api/prefix_graphics.h"
#include <stdio.h>

typedef enum {
  COLOUR_NONE,
  COLOUR_WHITE,
  COLOUR_BLACK,
  COLOUR_RED,
  COLOUR_GREEN,
  COLOUR_AMBER,
} Colours;

int main(int argc, const char *argv[]) {
  double dt;
  double x = 10;
  int ms = 0;
  unsigned int mx = 0;
  unsigned int my = 0;

  int screen = nxdraw_graphics(320 * 4, 200 * 4, 320, 200, 0);
  int block = nxdraw_load_image("assets/floor_a.png");

  nxdraw_set_colour_rgb(COLOUR_RED, 255, 0, 0);
  nxdraw_set_colour_rgb(COLOUR_GREEN, 0, 255, 0);
  nxdraw_set_colour_rgb(COLOUR_AMBER, 255, 0x73, 0);

  while (nxdraw_running()) {
    dt = nxdraw_limit(60);
    // printf("%lf\n", dt);
    x = (x + dt * 100);

    while (nxdraw_poll_event()) {
      switch (nxdraw_event_kind()) {
      case NXDRAW_EVENT_MOUSE_MOVE:
        mx = (int)nxdraw_event_x();
        my = (int)nxdraw_event_y();
        break;
      case NXDRAW_EVENT_MOUSE_DOWN:
        ms = 1;
        break;
      case NXDRAW_EVENT_MOUSE_UP:
        ms = 0;
        break;
      default:
        break;
      }
    }

    nxdraw_clear(screen, COLOUR_BLACK);

    nxdraw_rectangle(screen, 10, 10, 10, 10, COLOUR_WHITE);
    nxdraw_rectangleb(screen, 10, 10, 10, 10, COLOUR_RED);

    nxdraw_circle(screen, 40, 40, 8, COLOUR_WHITE);
    nxdraw_circleb(screen, 40, 40, 8, COLOUR_RED);

    nxdraw_triangle(screen, 100, 150, 50, 50, 20, 100, COLOUR_WHITE);
    nxdraw_triangleb(screen, 100, 150, 50, 50, 20, 100, COLOUR_RED);

    nxdraw_line(screen, 10, 10, 40, 40, COLOUR_GREEN);
    nxdraw_hline(screen, 10, 100, 5, COLOUR_WHITE);
    nxdraw_vline(screen, 10, 100, 5, COLOUR_WHITE);

    nxdraw_blit(screen, ((int)x) % 320, 50, block);

    if (ms) {
      nxdraw_circle(screen, mx, my, 3, COLOUR_RED);
    } else {
      nxdraw_circle(screen, mx, my, 3, COLOUR_WHITE);
    }

    nxdraw_printstring_ascii(screen, 20, 20 + (8 * 0),
                             "the quick brown fox jumps over the", COLOUR_AMBER,
                             COLOUR_NONE);
    nxdraw_printstring_ascii(screen, 20, 20 + (8 * 2),
                             "lazy dog THE QUICK BROWN FOX JUMPS", COLOUR_AMBER,
                             COLOUR_NONE);
    nxdraw_printstring_ascii(screen, 20, 20 + (8 * 4),
                             "OVER THE LAZY DOG *-+/,.\\?!{}()[]", COLOUR_AMBER,
                             COLOUR_NONE);
    nxdraw_printstring_ascii(screen, 20, 20 + (8 * 6), "@#$%^&~|'\"';:<>",
                             COLOUR_AMBER, COLOUR_NONE);

    nxdraw_show();
  }
}

// For legacy Microsoft Operating System support
int WinMain(int argc, const char *argv[]) { return main(argc, argv); }

/*
int main(int argc, const char *argv[]) {
  // printf("the cake is a lie\n");

  nxdraw_graphics(320 * 4, 200 * 4, 320, 200, 0);

  while (nxdraw_running()) {
    while (nxdraw_poll_event()) {
      // printf("the cake is a lie %i\n", nxdraw_event_kind());
    }
    nxdraw_vline(20, 20, 100);
    nxdraw_printstring_ascii(20, 40, "this is a text");
    nxdraw_show();
  }
}
*/

/*
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

    printstring_ascii(engine->tex, 20, 20 + (8 * 0),
                      "the quick brown fox jumps over the", COLOUR_AMBER,
                      COLOUR_NONE);
    printstring_ascii(engine->tex, 20, 20 + (8 * 2),
                      "lazy dog THE QUICK BROWN FOX JUMPS", COLOUR_AMBER,
                      COLOUR_NONE);
    printstring_ascii(engine->tex, 20, 20 + (8 * 4),
                      "OVER THE LAZY DOG *-+/,.\\?!{}()[]", COLOUR_AMBER,
                      COLOUR_NONE);
    printstring_ascii(engine->tex, 20, 20 + (8 * 6), "@#$%^&~|'\"';:<>",
                      COLOUR_AMBER, COLOUR_NONE);

    e = poll_event(engine);
    while (e.kind) {
      // printf("(%i)\n", e.kind);
      //
      //if (e.kind == NXDRAW_EVENT_KEY_DOWN) {
      //  // printf("%i\n", e.key);
      //} else {
      //  // printf("%i h\n", e.kind);
      //  // printf("(%i) %i h\n", e.kind);
      //}
      //
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
*/