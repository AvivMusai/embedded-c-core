CC := gcc

CFLAGS := -std=c11 -Wall -Wextra -Werror -pedantic
CPPFLAGS := -Iinclude

RING_BUFFER_TEST := test_ring_buffer
COMMAND_PARSER_TEST := test_command_parser
DEVICE_FSM_TEST := test_device_fsm
BIT_UTILS_TEST := test_bit_utils

TEST_TARGETS := \
        $(RING_BUFFER_TEST) \
        $(COMMAND_PARSER_TEST) \
        $(DEVICE_FSM_TEST) \
        $(BIT_UTILS_TEST)

.PHONY: all test clean

all: $(TEST_TARGETS)

$(RING_BUFFER_TEST): \
	src/ring_buffer.c \
	tests/test_ring_buffer.c \
	include/ring_buffer.h
	$(CC) $(CFLAGS) $(CPPFLAGS) \
	src/ring_buffer.c \
	tests/test_ring_buffer.c \
	-o $(RING_BUFFER_TEST)

$(COMMAND_PARSER_TEST): \
	src/command_parser.c \
	tests/test_command_parser.c \
	include/command_parser.h
	$(CC) $(CFLAGS) $(CPPFLAGS) \
	src/command_parser.c \
	tests/test_command_parser.c \
	-o $(COMMAND_PARSER_TEST)

$(DEVICE_FSM_TEST): \
	src/device_fsm.c \
	tests/test_device_fsm.c \
	include/device_fsm.h
	$(CC) $(CFLAGS) $(CPPFLAGS) \
	src/device_fsm.c \
	tests/test_device_fsm.c \
	-o $(DEVICE_FSM_TEST)

$(BIT_UTILS_TEST): \
        src/bit_utils.c \
        tests/test_bit_utils.c \
        include/bit_utils.h
	$(CC) $(CFLAGS) $(CPPFLAGS) \
        src/bit_utils.c \
        tests/test_bit_utils.c \
        -o $(BIT_UTILS_TEST)

test: $(TEST_TARGETS)
	./$(RING_BUFFER_TEST)
	./$(COMMAND_PARSER_TEST)
	./$(DEVICE_FSM_TEST)
	./$(BIT_UTILS_TEST)

clean:
	rm -f $(TEST_TARGETS)
