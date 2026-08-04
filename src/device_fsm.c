#include <stddef.h>

#include "device_fsm.h"

typedef struct
{
    device_state_t current_state;
    device_event_t event;
    device_state_t next_state;
} device_transition_t;

static const device_transition_t transitions[] =
{
    {
        DEVICE_STATE_OFF,
        DEVICE_EVENT_POWER_ON,
        DEVICE_STATE_IDLE
    },
    {
        DEVICE_STATE_IDLE,
        DEVICE_EVENT_POWER_OFF,
        DEVICE_STATE_OFF
    },
    {
        DEVICE_STATE_IDLE,
        DEVICE_EVENT_START,
        DEVICE_STATE_RUNNING
    },
    {
        DEVICE_STATE_IDLE,
        DEVICE_EVENT_FAULT,
        DEVICE_STATE_ERROR
    },
    {
        DEVICE_STATE_RUNNING,
        DEVICE_EVENT_STOP,
        DEVICE_STATE_IDLE
    },
    {
        DEVICE_STATE_RUNNING,
        DEVICE_EVENT_POWER_OFF,
        DEVICE_STATE_OFF
    },
    {
        DEVICE_STATE_RUNNING,
        DEVICE_EVENT_FAULT,
        DEVICE_STATE_ERROR
    },
    {
        DEVICE_STATE_ERROR,
        DEVICE_EVENT_RESET,
        DEVICE_STATE_IDLE
    },
    {
        DEVICE_STATE_ERROR,
        DEVICE_EVENT_POWER_OFF,
        DEVICE_STATE_OFF
    }
};

void device_fsm_init(
    device_fsm_t *fsm
)
{
    if (fsm == NULL)
    {
        return;
    }

    fsm->state = DEVICE_STATE_OFF;
}

bool device_fsm_handle_event(
    device_fsm_t *fsm,
    device_event_t event
)
{
    size_t index;

    if (fsm == NULL)
    {
        return false;
    }

    for (index = 0U;
         index < sizeof(transitions) / sizeof(transitions[0]);
         index++)
    {
        if (transitions[index].current_state == fsm->state &&
            transitions[index].event == event)
        {
            fsm->state = transitions[index].next_state;
            return true;
        }
    }

    return false;
}

device_state_t device_fsm_get_state(
    const device_fsm_t *fsm
)
{
    if (fsm == NULL)
    {
        return DEVICE_STATE_INVALID;
    }

    return fsm->state;
}
