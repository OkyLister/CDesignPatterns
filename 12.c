#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stddef.h>

#define container_of(type, list, list_) \
    (type*)((char *)list_ - offsetof(type, list))

// https://pastebin.com/i9zW1XmV

struct file {
    const char *name;
};

struct directory {
    const char *name;
    struct file *files;
    size_t nfiles;
    struct directory *directories;
    size_t ndirectories;
};

#define ARRAY_SIZE(array) (sizeof array / sizeof *array)

void print_file(struct file *file, int indent);

void print_directory(struct directory *dir, int indent)
{
    for (int i = 0; i < indent; i++)
        printf("  ");
    printf("dir %s\n", dir->name);
    for (int i = 0; i < dir->ndirectories; i++)
        print_directory(&dir->directories[i], indent + 1);
    for (int i = 0; i < dir->nfiles; i++)
        print_file(&dir->files[i], indent + 1);
}

void print_file(struct file *file, int indent)
{
    for (int i = 0; i < indent; i++)
        printf("  ");
    printf("file %s\n", file->name);
}

int main()
{
    struct file files[] = {
        { .name = "alpha" },
        { .name = "beta" },
    };
    struct directory dirs[] = {
        {
            .name = "a",
            .files = files,
            .nfiles = ARRAY_SIZE(files),
        },
        { .name = "b" },
    };
    struct directory root = {
        .name = "root",
        .directories = dirs,
        .ndirectories = ARRAY_SIZE(dirs),
    };

    print_directory(&root, 0);
}