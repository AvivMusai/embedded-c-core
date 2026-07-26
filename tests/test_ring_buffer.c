#include <assert.h>
#include <stdint.h>
#include <stdio.h>

#include "ring_buffer.h"

static void test_basic_fifo(void)
{
    uint8_t storage[3];
    ring_buffer_t ring_buffer;
    uint8_t value = 0U;

    assert(ring_buffer_init(
        &ring_buffer,
        storage,
        3U
    ));

    assert(ring_buffer_is_empty(&ring_buffer));
    assert(!ring_buffer_is_full(&ring_buffer));
    assert(ring_buffer_size(&ring_buffer) == 0U);

    assert(ring_buffer_push(&ring_buffer, 10U));
    assert(ring_buffer_push(&ring_buffer, 20U));
    assert(ring_buffer_push(&ring_buffer, 30U));

    assert(ring_buffer_is_full(&ring_buffer));
    assert(ring_buffer_size(&ring_buffer) == 3U);

    assert(!ring_buffer_push(&ring_buffer, 40U));

    assert(ring_buffer_pop(&ring_buffer, &value));
    assert(value == 10U);

    assert(ring_buffer_pop(&ring_buffer, &value));
    assert(value == 20U);

    assert(ring_buffer_pop(&ring_buffer, &value));
    assert(value == 30U);

    assert(ring_buffer_is_empty(&ring_buffer));
    assert(!ring_buffer_pop(&ring_buffer, &value));
}

static void test_wraparound(void)
{
    uint8_t storage[3];
    ring_buffer_t ring_buffer;
    uint8_t value = 0U;

    assert(ring_buffer_init(
        &ring_buffer,
        storage,
        3U
    ));

    assert(ring_buffer_push(&ring_buffer, 1U));
    assert(ring_buffer_push(&ring_buffer, 2U));
    assert(ring_buffer_push(&ring_buffer, 3U));

    assert(ring_buffer_pop(&ring_buffer, &value));
    assert(value == 1U);

    assert(ring_buffer_push(&ring_buffer, 4U));

    assert(ring_buffer_pop(&ring_buffer, &value));
    assert(value == 2U);

    assert(ring_buffer_pop(&ring_buffer, &value));
    assert(value == 3U);

    assert(ring_buffer_pop(&ring_buffer, &value));
    assert(value == 4U);

    assert(ring_buffer_is_empty(&ring_buffer));
}

int main(void)
{
    test_basic_fifo();
    test_wraparound();

    printf("All ring buffer tests passed.\n");

    return 0;
}
