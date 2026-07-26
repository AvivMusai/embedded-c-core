#include "ring_buffer.h"

bool ring_buffer_init(
    ring_buffer_t *ring_buffer,
    uint8_t *storage,
    size_t capacity
)
{
    if (ring_buffer == NULL ||
        storage == NULL ||
        capacity == 0U)
    {
        return false;
    }

    ring_buffer->buffer = storage;
    ring_buffer->capacity = capacity;
    ring_buffer->head = 0U;
    ring_buffer->tail = 0U;
    ring_buffer->count = 0U;

    return true;
}

bool ring_buffer_push(
    ring_buffer_t *ring_buffer,
    uint8_t value
)
{
    if (ring_buffer == NULL ||
        ring_buffer->buffer == NULL ||
        ring_buffer->capacity == 0U ||
        ring_buffer_is_full(ring_buffer))
    {
        return false;
    }

    ring_buffer->buffer[ring_buffer->head] = value;

    ring_buffer->head =
        (ring_buffer->head + 1U) % ring_buffer->capacity;

    ring_buffer->count++;

    return true;
}

bool ring_buffer_pop(
    ring_buffer_t *ring_buffer,
    uint8_t *value
)
{
    if (ring_buffer == NULL ||
        value == NULL ||
        ring_buffer->buffer == NULL ||
        ring_buffer->capacity == 0U ||
        ring_buffer_is_empty(ring_buffer))
    {
        return false;
    }

    *value = ring_buffer->buffer[ring_buffer->tail];

    ring_buffer->tail =
        (ring_buffer->tail + 1U) % ring_buffer->capacity;

    ring_buffer->count--;

    return true;
}

bool ring_buffer_is_empty(
    const ring_buffer_t *ring_buffer
)
{
    return ring_buffer != NULL &&
           ring_buffer->count == 0U;
}

bool ring_buffer_is_full(
    const ring_buffer_t *ring_buffer
)
{
    return ring_buffer != NULL &&
           ring_buffer->capacity > 0U &&
           ring_buffer->count == ring_buffer->capacity;
}

size_t ring_buffer_size(
    const ring_buffer_t *ring_buffer
)
{
    if (ring_buffer == NULL)
    {
        return 0U;
    }

    return ring_buffer->count;
}
