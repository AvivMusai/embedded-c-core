#include <assert.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

#include "bit_utils.h"

int main(void)
{
    uint8_t value;

    value = 0U;
    value = bit_set(value, 2U);
    assert(value == 4U);

    value = 12U;
    value = bit_clear(value, 3U);
    assert(value == 4U);

    value = 6U;
    value = bit_toggle(value, 1U);
    assert(value == 4U);

    assert(bit_is_set(10U, 3U) == true);
    assert(bit_is_set(10U, 2U) == false);
    value = 5U;
    assert(bit_set(value, 8U) == value);
    assert(bit_clear(value, 8U) == value);
    assert(bit_toggle(value, 8U) == value);
    assert(bit_is_set(value, 8U) == false);
    printf("All bit utils tests passed.\n");

    return 0;
}
