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

static void test_invalid_initialization(void)
{
    uint8_t storage[3];
    ring_buffer_t ring_buffer;

    assert(!ring_buffer_init(
        NULL,
        storage,
        3U
    ));

    assert(!ring_buffer_init(
        &ring_buffer,
        NULL,
        3U
    ));

    assert(!ring_buffer_init(
        &ring_buffer,
        storage,
        0U
    ));
}

static void test_invalid_operations(void)
{
    uint8_t storage[3];
    ring_buffer_t ring_buffer;
    uint8_t value = 0U;

    assert(ring_buffer_init(
        &ring_buffer,
        storage,
        3U
    ));

    assert(!ring_buffer_push(NULL, 10U));

    assert(!ring_buffer_pop(
        NULL,
        &value
    ));

    assert(!ring_buffer_pop(
        &ring_buffer,
        NULL
    ));

    assert(!ring_buffer_pop(
        &ring_buffer,
        &value
    ));

    assert(ring_buffer_size(NULL) == 0U);
    assert(!ring_buffer_is_empty(NULL));
    assert(!ring_buffer_is_full(NULL));
}

int main(void)
{
    test_basic_fifo();
    test_wraparound();
    test_invalid_initialization();
    test_invalid_operations();

    printf("All ring buffer tests passed.\n");

    return 0;
}
