#ifndef RING_BUFFER_H
#define RING_BUFFER_H

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

typedef struct
{
    uint8_t *buffer;
    size_t capacity;
    size_t head;
    size_t tail;
    size_t count;
} ring_buffer_t;

bool ring_buffer_init(
    ring_buffer_t *ring_buffer,
    uint8_t *storage,
    size_t capacity
);

bool ring_buffer_push(
    ring_buffer_t *ring_buffer,
    uint8_t value
);

bool ring_buffer_pop(
    ring_buffer_t *ring_buffer,
    uint8_t *value
);

void ring_buffer_clear(
    ring_buffer_t *ring_buffer
);

bool ring_buffer_is_empty(
    const ring_buffer_t *ring_buffer
);

bool ring_buffer_is_full(
    const ring_buffer_t *ring_buffer
);

size_t ring_buffer_size(
    const ring_buffer_t *ring_buffer
);

#endif
