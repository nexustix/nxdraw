#ifndef NXDRAW_EVENT_BUFFER
#define NXDRAW_EVENT_BUFFER

#include "event.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
  unsigned int reserved;
  unsigned int next;
  unsigned int head;
  NxdrawEvent *buffer;
  int draining;

} NxdrawEventBuffer;

NxdrawEventBuffer *newEventBuffer(size_t size) {
  // unsigned int n = 1024;
  NxdrawEventBuffer *self = (NxdrawEventBuffer *)malloc(sizeof(*self));
  self->next = 0;
  self->head = 0;
  self->reserved = size;
  self->buffer = (NxdrawEvent *)malloc(sizeof(NxdrawEvent) * size);
  self->draining = 0;
  return self;
}

void nxdraw_event_buffer_push_event(NxdrawEventBuffer *self, NxdrawEvent e) {
  if (self->draining) {
    self->next = 0;
    self->head = 0;
    self->draining = 0;
  }
  if (self->next + 1 > self->reserved) {
    // FIXME resize me
    int buffer_large_enough = 0;
    assert(buffer_large_enough);
  }
  self->buffer[self->next] = e;
  self->next += 1;
}

NxdrawEvent nxdraw_event_buffer_pop_event(NxdrawEventBuffer *self) {
  assert(self);
  self->draining = 1;
  // printf("%i %i\n", self->next, self->head);
  if (self->head >= self->next) {
    // printf("nope\n");
    NxdrawEvent tmp = makeNxdrawEvent();
    tmp.kind = NXDRAW_EVENT_VOID;
    return tmp;
  }

  self->head += 1;
  return self->buffer[self->head - 1];
}

#endif