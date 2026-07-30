#ifndef COMMAND_PARSER_H
#define COMMAND_PARSER_H

#include <stdbool.h>
#include <stddef.h>

#define COMMAND_PARSER_MAX_ARGUMENTS 4U

typedef struct
{
    const char *command;
    const char *arguments[COMMAND_PARSER_MAX_ARGUMENTS];
    size_t argument_count;
} parsed_command_t;

bool command_parser_parse(
    char *input,
    parsed_command_t *parsed_command
);

#endif
