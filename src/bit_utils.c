#include "bit_utils.h"

uint8_t bit_set(
    uint8_t value,
    uint8_t bit
)
{
    if (bit >= 8U)
    {
        return value;
    }

    return (uint8_t)(value | (1U << bit));
}

uint8_t bit_clear(
    uint8_t value,
    uint8_t bit
)
{
    if (bit >= 8U)
    {
        return value;
    }

    return (uint8_t)(value & ~(1U << bit));
}

uint8_t bit_toggle(
    uint8_t value,
    uint8_t bit
)
{
    if (bit >= 8U)
    {
        return value;
    }

    return (uint8_t)(value ^ (1U << bit));
}

bool bit_is_set(
    uint8_t value,
    uint8_t bit
)
{
    if (bit >= 8U)
    {
        return false;
    }

    return (value & (1U << bit)) != 0U;
}
