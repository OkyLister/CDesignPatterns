#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stddef.h>

// ITERATOR s begin a end (C++)

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

struct citizen_iter begin(void)
{
    struct citizen_iter iter = { .idx = 0 };

    return iter;
}

struct citizen_iter end(void)
{
    struct citizen_iter iter = { .idx = sizeof citizens / sizeof *citizens };

    return iter;
}

int main()
{
    struct citizen_iter start = begin();
    struct citizen_iter stop = end();
    for (struct citizen_iter iter = start; iter.idx != stop.idx; iter.idx++) {
        struct citizen *citizen = &citizens[iter.idx];

        printf("%d\n", citizen->age);
    }
}