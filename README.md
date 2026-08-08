# Embedded C Core

A collection of low-level C components designed to practice and demonstrate
embedded software development concepts.

## Ring Buffer

The first component is a fixed-capacity byte ring buffer implemented without
dynamic memory allocation.

### Features

- FIFO data handling
- Caller-provided static storage
- Full and empty state detection
- Index wraparound
- Input validation
- Unit tests using `assert`
- Strict compiler warnings
- Logical buffer clearing and reuse

## Command Parser

A fixed-capacity command parser that separates a mutable input string into a
command and arguments without dynamic memory allocation.

### Features

- In-place parsing
- Up to four command arguments
- Space, tab, carriage-return, and newline handling
- Empty-input validation
- Maximum-argument validation
- Caller-owned input storage
- Unit tests using `assert`

## Device Finite State Machine

A table-driven finite state machine that models device states, events, valid
transitions, fault handling, and invalid-event rejection.

### Features

- Explicit device states and events using enums
- Table-driven state transitions
- Normal power and execution lifecycle
- Fault and reset handling
- Invalid-transition rejection
- State preservation after invalid events
- Null-pointer validation
- Unit tests covering every valid transition

## Bit Utilities

A reusable set of 8-bit bit-manipulation utilities for setting, clearing,
toggling, and testing individual bits.

### Features

- Set individual bits
- Clear individual bits
- Toggle individual bits
- Test whether a bit is set
- Bit-mask generation using left shifts
- Invalid bit-index validation
- Fixed-width `uint8_t` operations
- Unit tests covering normal and invalid inputs

## Project Structure

```text
embedded-c-core/
├── include/
│   ├── bit_utils.h
│   ├── command_parser.h
│   ├── device_fsm.h
│   └── ring_buffer.h
├── src/
│   ├── bit_utils.c
│   ├── command_parser.c
│   ├── device_fsm.c
│   └── ring_buffer.c
├── tests/
│   ├── test_bit_utils.c
│   ├── test_command_parser.c
│   ├── test_device_fsm.c
│   └── test_ring_buffer.c
├── Makefile
├── README.md
└── .gitignore
```

## Build

```bash
make
```

## Run Tests

```bash
make test
```

Expected output:

```text
All ring buffer tests passed.
All command parser tests passed.
All device FSM tests passed.
All bit utils tests passed.
```

## Clean Build Files

```bash
make clean
```

## Ring Buffer API

```c
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
```
## Command Parser API

```c
bool command_parser_parse(
    char *input,
    parsed_command_t *parsed_command
);
```

## Device FSM API

```c
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
```

## Bit Utilities API

```c
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
```

## Concepts Demonstrated

- Pointers
- Structures
- Fixed-width integer types
- Output parameters
- Caller-provided fixed-size storage
- No dynamic memory allocation
- FIFO data structures
- Modular arithmetic
- Header and source file separation
- Defensive input validation
- Automated builds with Make
- In-place string parsing
- String tokenization
- Fixed-capacity argument handling
- Boundary testing
- Enumerations for states and events
- Finite state machine design
- Table-driven state transitions
- Valid and invalid transition handling
- State preservation after rejected events
- Bitwise AND, OR, XOR, and NOT
- Bit masks
- Left-shift operations
- Set, clear, toggle, and test bit operations
- Invalid bit-index handling
