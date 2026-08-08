#ifndef BIT_UTILS_H
#define BIT_UTILS_H

#include <stdbool.h>
#include <stdint.h>

uint8_t bit_set(
    uint8_t value,
    uint8_t bit
);

uint8_t bit_clear(
    uint8_t value,
    uint8_t bit
);

uint8_t bit_toggle(
    uint8_t value,
    uint8_t bit
);

bool bit_is_set(
    uint8_t value,
    uint8_t bit
);

#endif
