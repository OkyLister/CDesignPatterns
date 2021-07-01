#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

//https://pastebin.com/0WhUrCSP

/* utilities */

#define container_of(type, member_name, member) \
    (type*)((char *)member - offsetof(type, member_name))

/* shape.h */

struct shape;
int shape_area(const struct shape *shape);
void shape_free(struct shape *shape);

/* shape-plugin.h */

struct shape_ops;

struct shape {
    struct shape_ops *ops;
    /* common data */
};

struct shape_ops {
    int (*area)(const struct shape *shape);
    void (*free)(struct shape *shape);
    /* more functions */
};

/* shape.c */

int shape_area(const struct shape *shape)
{
    if (!shape->ops->area)
        abort();
    return shape->ops->area(shape);
}

void shape_free(struct shape *shape)
{
    shape->ops->free(shape);
}

/* square.h */

struct shape *new_square(int side);

/* square.c */

struct square {
    int side;
    struct shape shape;
};

static int square_area(const struct shape *shape)
{
    const struct square *square = container_of(const struct square, shape, shape);

    return square->side * square->side;
}

static void square_free(struct shape *shape)
{
    struct square *square = container_of(struct square, shape, shape);

    free(square);
}

static struct shape_ops square_ops = {
    .area = square_area,
    .free = square_free,
};

struct shape *new_square(int side)
{
    struct square *square;

    square = malloc(sizeof *square);
    if (!square)
        abort();

    /* init */
    square->side = side;

    square->shape.ops = &square_ops;

    return &square->shape;
}

/* test */

int main()
{
    struct shape *shape = new_square(5);

    printf("area = %d\n", shape_area(shape));

    shape_free(shape);
}