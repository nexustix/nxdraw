#include "engine/engine.h"
#include <stdio.h>

int main(int argc, const char *argv[]) {

  // printf("Aloha, edit \"src/main.c\" to get started\n");
  // Engine *engine = newEngine(800, 600, 400, 300);
  Engine *engine = newEngine(320 * 4, 200 * 4, 320, 200);

  // int cake[10];

  // cake[2,2] = 8;

  engine_init(engine, 0);
  engine_run(engine);

  return 0;
}

// For legacy Microsoft Operating System support
int WinMain(int argc, const char *argv[]) { return main(argc, argv); }