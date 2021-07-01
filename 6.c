#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

// BUILDER


// > test.txt ... command = NULL



/* builder.h */

struct builder;
struct process;
struct builder *new_builder(void);
void set_command(struct builder *builder, const char *command);
void set_capture_output(struct builder *builder, bool capture_output);
struct process *build(struct builder *builder);

/* builder.c */

struct builder {
    const char *command;
    bool capture_output;
};

struct process {
    int pid;
};

struct builder *new_builder(void)
{
    struct builder *builder;

    builder = malloc(sizeof *builder);
    if (!builder)
        abort();

    builder->command = NULL;
    builder->capture_output = false;

    return builder;
}

void set_command(struct builder *builder, const char *command)
{
    builder->command = command;
}

void set_capture_output(struct builder *builder, bool capture_output)
{
    builder->capture_output = capture_output;
}

struct process *build(struct builder *builder)
{
    struct process *process;

    process = malloc(sizeof *process);
    if (!process)
        abort();

    printf("command: %s (capture=%d)\n", builder->command, builder->capture_output);

    return process;
}

/* test */

int main()
{
    struct builder *builder = new_builder();
    set_command(builder, "ls -ls");
    set_capture_output(builder, true);
    struct process *process = build(builder);
}