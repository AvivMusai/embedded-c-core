CC := gcc

CFLAGS := -std=c11 -Wall -Wextra -Werror -pedantic
CPPFLAGS := -Iinclude

TARGET := test_ring_buffer

SOURCES := \
	src/ring_buffer.c \
	tests/test_ring_buffer.c

.PHONY: all test clean

all: $(TARGET)

$(TARGET): $(SOURCES) include/ring_buffer.h
		$(CC) $(CFLAGS) $(CPPFLAGS) $(SOURCES) -o $(TARGET)

test: $(TARGET)
		./$(TARGET)

clean:
		rm -f $(TARGET)
