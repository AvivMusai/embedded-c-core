#include <assert.h>
#include <stdio.h>
#include <string.h>

#include "command_parser.h"

static void test_basic_command(void)
{
    char input[] = "set speed 120";
    parsed_command_t parsed_command;

    assert(command_parser_parse(
        input,
        &parsed_command
    ));

    assert(strcmp(parsed_command.command, "set") == 0);
    assert(parsed_command.argument_count == 2U);

    assert(strcmp(
        parsed_command.arguments[0],
        "speed"
    ) == 0);

    assert(strcmp(
        parsed_command.arguments[1],
        "120"
    ) == 0);
}

static void test_whitespace_and_no_arguments(void)
{
    char input[] = " \t status\r\n";
    parsed_command_t parsed_command;

    assert(command_parser_parse(
        input,
        &parsed_command
    ));

    assert(strcmp(
        parsed_command.command,
        "status"
    ) == 0);

    assert(parsed_command.argument_count == 0U);
}

static void test_invalid_input(void)
{
    char empty_input[] = "";
    char separators_only[] = "   \t\r\n";
    parsed_command_t parsed_command;

    assert(!command_parser_parse(
        NULL,
        &parsed_command
    ));

    assert(!command_parser_parse(
        empty_input,
        NULL
    ));

    assert(!command_parser_parse(
        empty_input,
        &parsed_command
    ));

    assert(!command_parser_parse(
        separators_only,
        &parsed_command
    ));
}

static void test_maximum_arguments(void)
{
    char input[] = "set a b c d";
    parsed_command_t parsed_command;

    assert(command_parser_parse(
        input,
        &parsed_command
    ));

    assert(strcmp(
        parsed_command.command,
        "set"
    ) == 0);

    assert(
        parsed_command.argument_count ==
        COMMAND_PARSER_MAX_ARGUMENTS
    );

    assert(strcmp(parsed_command.arguments[0], "a") == 0);
    assert(strcmp(parsed_command.arguments[1], "b") == 0);
    assert(strcmp(parsed_command.arguments[2], "c") == 0);
    assert(strcmp(parsed_command.arguments[3], "d") == 0);
}

static void test_too_many_arguments(void)
{
    char input[] = "set a b c d e";
    parsed_command_t parsed_command;

    assert(!command_parser_parse(
        input,
        &parsed_command
    ));

    assert(parsed_command.command == NULL);
    assert(parsed_command.argument_count == 0U);
}

int main(void)
{
    test_basic_command();
    test_whitespace_and_no_arguments();
    test_invalid_input();
    test_maximum_arguments();
    test_too_many_arguments();

    printf("All command parser tests passed.\n");

    return 0;
}
