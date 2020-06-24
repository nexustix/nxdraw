#ifndef NXDRAW_EVENT_H
#define NXDRAW_EVENT_H

#include <stdlib.h>

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

typedef struct NxdrawEvent {
  NxdrawEventKind kind;
  int key;    // character related
  int button; // scancode related
  int mods;   // modifier keys
  unsigned int codepoint;
  double x;
  double y;
} NxdrawEvent;

/*
static NxdrawEvent *event_buffer;
static unsigned int event_buffer_reserved;
static unsigned int event_buffer_next;

void event_init() {
  unsigned int n = 1024;
  event_buffer = (NxdrawEvent *)realloc(event_buffer, sizeof(NxdrawEvent) * n);
  event_buffer_reserved = n;
  event_buffer_next = 0;
}
*/
/*
void key_callback(GLFWwindow *window, int key, int scancode, int action,
                  int mods) {}
*/

NxdrawEvent makeNxdrawEvent() {
  NxdrawEvent tmp;
  tmp.kind = NXDRAW_EVENT_VOID;
  return tmp;
}
#endif