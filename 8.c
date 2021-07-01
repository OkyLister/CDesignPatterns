#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stddef.h>

#define container_of(type, list, list_) \
    (type*)((char *)list_ - offsetof(type, list))
	
// DECORATOR

/* abs */

struct computation_ops;

struct computation {
    struct computation_ops *ops;
};

struct computation_ops {
    int (*compute)(struct computation *computation, int x);
};

int compute(struct computation *computation, int x)
{
    return computation->ops->compute(computation, x);
}

/* twice */

static int twice_compute(struct computation *computation, int x)
{
    return x * 2;
}

static struct computation_ops twice_computation_ops = {
    .compute = twice_compute,
};

/* deco */

struct decorator {
    struct computation *inner;
    struct computation outer;
};

static int decorator_compute(struct computation *computation, int x)
{
    struct decorator *decorator = container_of(struct decorator, outer, computation);
    int y = compute(decorator->inner, x);
    printf("%d -> %d\n", x, y);
    return y;
}

static struct computation_ops decorator_ops = {
    .compute = decorator_compute,
};

struct computation *new_decorator(struct computation *inner)
{
    struct decorator *decorator;

    decorator = malloc(sizeof *decorator);
    if (!decorator)
        abort();

    decorator->inner = inner;
    decorator->outer.ops = &decorator_ops;

    return &decorator->outer;
}

/* test */

int main()
{
    struct computation twice = { .ops = &twice_computation_ops };

    struct computation *c = &twice;

    c = new_decorator(c);
    c = new_decorator(c);
    c = new_decorator(c);

    /* calling code */
    int y = compute(c, 5);

    printf("%d\n", y);
}