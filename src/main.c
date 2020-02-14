#include <stdio.h>
#include "engine/engine.h"


int main(int argc, const char *argv[]) {

  //printf("Aloha, edit \"src/main.c\" to get started\n");
  Engine *engine = newEngine();

  //int cake[10];

  //cake[2,2] = 8;

  engine_init(engine);
  engine_run(engine);

  return 0;
}

// For legacy Microsoft Operating System support
int WinMain(int argc, const char *argv[]) { return main(argc, argv); }