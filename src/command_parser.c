#include "command_parser.h"

static bool is_separator(
    char character
)
{
    return character == ' '  ||
           character == '\t' ||
           character == '\r' ||
           character == '\n';
}

static void parsed_command_reset(
    parsed_command_t *parsed_command
)
{
    size_t index;

    parsed_command->command = NULL;
    parsed_command->argument_count = 0U;

    for (index = 0U;
         index < COMMAND_PARSER_MAX_ARGUMENTS;
         index++)
    {
        parsed_command->arguments[index] = NULL;
    }
}

bool command_parser_parse(
    char *input,
    parsed_command_t *parsed_command
)
{
    char *cursor;

    if (input == NULL ||
        parsed_command == NULL)
    {
        return false;
    }

    parsed_command_reset(parsed_command);

    cursor = input;

    while (is_separator(*cursor))
    {
        cursor++;
    }

    if (*cursor == '\0')
    {
        return false;
    }

    parsed_command->command = cursor;

    while (*cursor != '\0' &&
           !is_separator(*cursor))
    {
        cursor++;
    }

    while (*cursor != '\0')
    {
        *cursor = '\0';
        cursor++;

        while (is_separator(*cursor))
        {
            cursor++;
        }

        if (*cursor == '\0')
        {
            break;
        }

        if (parsed_command->argument_count >=
            COMMAND_PARSER_MAX_ARGUMENTS)
        {
            parsed_command_reset(parsed_command);
            return false;
        }

        parsed_command->arguments[
            parsed_command->argument_count
        ] = cursor;

        parsed_command->argument_count++;

        while (*cursor != '\0' &&
               !is_separator(*cursor))
        {
            cursor++;
        }
    }

    return true;
}
