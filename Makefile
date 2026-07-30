CC := gcc

CFLAGS := -std=c11 -Wall -Wextra -Werror -pedantic
CPPFLAGS := -Iinclude

RING_BUFFER_TEST := test_ring_buffer
COMMAND_PARSER_TEST := test_command_parser

TEST_TARGETS := \
	$(RING_BUFFER_TEST) \
	$(COMMAND_PARSER_TEST)

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

test: $(TEST_TARGETS)
	./$(RING_BUFFER_TEST)
	./$(COMMAND_PARSER_TEST)

clean:
	rm -f $(TEST_TARGETS)
