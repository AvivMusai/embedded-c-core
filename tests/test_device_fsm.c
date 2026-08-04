#include <assert.h>
#include <stdio.h>

#include "device_fsm.h"

static void test_initialization(void)
{
    device_fsm_t fsm;

    device_fsm_init(&fsm);

    assert(
        device_fsm_get_state(&fsm) ==
        DEVICE_STATE_OFF
    );
}

static void test_normal_lifecycle(void)
{
    device_fsm_t fsm;

    device_fsm_init(&fsm);

    assert(device_fsm_handle_event(
        &fsm,
        DEVICE_EVENT_POWER_ON
    ));

    assert(
        device_fsm_get_state(&fsm) ==
        DEVICE_STATE_IDLE
    );

    assert(device_fsm_handle_event(
        &fsm,
        DEVICE_EVENT_START
    ));

    assert(
        device_fsm_get_state(&fsm) ==
        DEVICE_STATE_RUNNING
    );

    assert(device_fsm_handle_event(
        &fsm,
        DEVICE_EVENT_STOP
    ));

    assert(
        device_fsm_get_state(&fsm) ==
        DEVICE_STATE_IDLE
    );

    assert(device_fsm_handle_event(
        &fsm,
        DEVICE_EVENT_POWER_OFF
    ));

    assert(
        device_fsm_get_state(&fsm) ==
        DEVICE_STATE_OFF
    );
}

static void test_power_off_while_running(void)
{
    device_fsm_t fsm;

    device_fsm_init(&fsm);

    assert(device_fsm_handle_event(
        &fsm,
        DEVICE_EVENT_POWER_ON
    ));

    assert(device_fsm_handle_event(
        &fsm,
        DEVICE_EVENT_START
    ));

    assert(device_fsm_handle_event(
        &fsm,
        DEVICE_EVENT_POWER_OFF
    ));

    assert(
        device_fsm_get_state(&fsm) ==
        DEVICE_STATE_OFF
    );
}

static void test_fault_transitions(void)
{
    device_fsm_t fsm;

    device_fsm_init(&fsm);

    assert(device_fsm_handle_event(
        &fsm,
        DEVICE_EVENT_POWER_ON
    ));

    assert(device_fsm_handle_event(
        &fsm,
        DEVICE_EVENT_FAULT
    ));

    assert(
        device_fsm_get_state(&fsm) ==
        DEVICE_STATE_ERROR
    );

    assert(device_fsm_handle_event(
        &fsm,
        DEVICE_EVENT_RESET
    ));

    assert(
        device_fsm_get_state(&fsm) ==
        DEVICE_STATE_IDLE
    );

    assert(device_fsm_handle_event(
        &fsm,
        DEVICE_EVENT_START
    ));

    assert(device_fsm_handle_event(
        &fsm,
        DEVICE_EVENT_FAULT
    ));

    assert(
        device_fsm_get_state(&fsm) ==
        DEVICE_STATE_ERROR
    );

    assert(device_fsm_handle_event(
        &fsm,
        DEVICE_EVENT_POWER_OFF
    ));

    assert(
        device_fsm_get_state(&fsm) ==
        DEVICE_STATE_OFF
    );
}

static void test_invalid_transitions(void)
{
    device_fsm_t fsm;

    device_fsm_init(&fsm);

    assert(!device_fsm_handle_event(
        &fsm,
        DEVICE_EVENT_START
    ));

    assert(
        device_fsm_get_state(&fsm) ==
        DEVICE_STATE_OFF
    );

    assert(device_fsm_handle_event(
        &fsm,
        DEVICE_EVENT_POWER_ON
    ));

    assert(!device_fsm_handle_event(
        &fsm,
        DEVICE_EVENT_STOP
    ));

    assert(
        device_fsm_get_state(&fsm) ==
        DEVICE_STATE_IDLE
    );

    assert(device_fsm_handle_event(
        &fsm,
        DEVICE_EVENT_START
    ));

    assert(!device_fsm_handle_event(
        &fsm,
        DEVICE_EVENT_START
    ));

    assert(
        device_fsm_get_state(&fsm) ==
        DEVICE_STATE_RUNNING
    );

    assert(device_fsm_handle_event(
        &fsm,
        DEVICE_EVENT_FAULT
    ));

    assert(!device_fsm_handle_event(
        &fsm,
        DEVICE_EVENT_STOP
    ));

    assert(
        device_fsm_get_state(&fsm) ==
        DEVICE_STATE_ERROR
    );

    assert(!device_fsm_handle_event(
        &fsm,
        (device_event_t)99
    ));

    assert(
        device_fsm_get_state(&fsm) ==
        DEVICE_STATE_ERROR
    );
}

static void test_null_pointer_handling(void)
{
    device_fsm_init(NULL);

    assert(!device_fsm_handle_event(
        NULL,
        DEVICE_EVENT_POWER_ON
    ));

    assert(
        device_fsm_get_state(NULL) ==
        DEVICE_STATE_INVALID
    );
}

int main(void)
{
    test_initialization();
    test_normal_lifecycle();
    test_power_off_while_running();
    test_fault_transitions();
    test_invalid_transitions();
    test_null_pointer_handling();

    printf("All device FSM tests passed.\n");

    return 0;
}
