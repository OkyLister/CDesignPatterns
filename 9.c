#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stddef.h>

// ITERATOR

struct citizen {
    int age;
};

static struct citizen citizens[] = {
    { .age = 22, },
    { .age = 64, },
    { .age = 47, },
};

/* iterator */

struct citizen_iter {
    int idx;
};

struct citizen_iter *get_citizens(void)
{
    struct citizen_iter *iter;

    iter = malloc(sizeof *iter);
    if (!iter)
        abort();

    iter->idx = 0;

    return iter;
}

struct citizen *next_citizen(struct citizen_iter *iter)
{
    if (iter->idx < 3)
        return &citizens[iter->idx++];
    else
        return NULL;
}

int main()
{
    struct citizen_iter *iter = get_citizens();

    while (1) {
        struct citizen *citizen = next_citizen(iter);

        if (!citizen)
            break;

        printf("%d\n", citizen->age);
    }
}