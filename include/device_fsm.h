#ifndef DEVICE_FSM_H
#define DEVICE_FSM_H

#include <stdbool.h>

typedef enum
{
    DEVICE_STATE_OFF,
    DEVICE_STATE_IDLE,
    DEVICE_STATE_RUNNING,
    DEVICE_STATE_ERROR,
    DEVICE_STATE_INVALID
} device_state_t;

typedef enum
{
    DEVICE_EVENT_POWER_ON,
    DEVICE_EVENT_POWER_OFF,
    DEVICE_EVENT_START,
    DEVICE_EVENT_STOP,
    DEVICE_EVENT_FAULT,
    DEVICE_EVENT_RESET
} device_event_t;

typedef struct
{
    device_state_t state;
} device_fsm_t;

void device_fsm_init(
    device_fsm_t *fsm
);

bool device_fsm_handle_event(
    device_fsm_t *fsm,
    device_event_t event
);

device_state_t device_fsm_get_state(
    const device_fsm_t *fsm
);

#endif
