#ifndef NXDRAw_EVENT_BRIDGE_H
#define NXDRAw_EVENT_BRIDGE_H

#include "event.h"
#include "event_buffer.h"
#include <GLFW/glfw3.h>
#include <assert.h>
#include <stdio.h>

static int _event_buffer_initialized = 0;
static NxdrawEventBuffer *_event_buffer;

void nxdraw_event_bridge_init() {
  _event_buffer_initialized = 1;
  _event_buffer = newEventBuffer(1024);
  //_event_buffer = newEventBuffer(2);
  assert(_event_buffer);
}

NxdrawEvent nxdraw_event_bridge_pop() {
  return nxdraw_event_buffer_pop_event(_event_buffer);
}

void nxdraw_event_bridge_push(NxdrawEvent e) {
  nxdraw_event_buffer_push_event(_event_buffer, e);
}

// handles key events
void nxdraw_event_bridge_key(GLFWwindow *window, int key, int scancode,
                             int action, int mods) {
  NxdrawEvent tmp = makeNxdrawEvent();
  switch (action) {
  case GLFW_PRESS:
    tmp.kind = NXDRAW_EVENT_KEY_DOWN;
    break;
  case GLFW_RELEASE:
    tmp.kind = NXDRAW_EVENT_KEY_UP;
    break;
  case GLFW_REPEAT:
    tmp.kind = NXDRAW_EVENT_KEY_HELT;
    break;
  default:
    tmp.kind = NXDRAW_EVENT_UNKNOWN;
    break;
  }
  tmp.key = key;
  tmp.button = scancode;
  tmp.mods = mods;
  assert(_event_buffer_initialized);
  // event_buffer_push_event(_event_buffer, tmp);
  nxdraw_event_bridge_push(tmp);
}

// handles text input events
void nxdraw_event_bridge_character(GLFWwindow *window, unsigned int codepoint) {
  NxdrawEvent tmp = makeNxdrawEvent();
  tmp.codepoint = codepoint;
  // event_buffer_push_event(_event_buffer, tmp);
  nxdraw_event_bridge_push(tmp);
}

// handles mouse cursor movement
void nxdraw_event_bridge_mousepos(GLFWwindow *window, double xpos,
                                  double ypos) {
  NxdrawEvent tmp = makeNxdrawEvent();
  tmp.kind = NXDRAW_EVENT_MOUSE_MOVE;
  tmp.x = xpos;
  tmp.y = ypos;
  nxdraw_event_bridge_push(tmp);
}

// handles mousebuttons
void nxdraw_event_bridge_mousebutton(GLFWwindow *window, int button, int action,
                                     int mods) {
  NxdrawEvent tmp = makeNxdrawEvent();
  switch (action) {
  case GLFW_PRESS:
    tmp.kind = NXDRAW_EVENT_MOUSE_DOWN;
    break;
  case GLFW_RELEASE:
    tmp.kind = NXDRAW_EVENT_MOUSE_UP;
    break;
  default:
    tmp.kind = NXDRAW_EVENT_UNKNOWN;
    break;
  }
  tmp.button = button;
  tmp.mods = mods;
  nxdraw_event_bridge_push(tmp);
}

#endif