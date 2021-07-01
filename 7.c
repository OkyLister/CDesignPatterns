#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stddef.h>

#define container_of(type, list, list_) \
    (type*)((char *)list_ - offsetof(type, list))

// https://pastebin.com/giuVKxUL

/* abstract interfaces */

struct turtle;

struct turtle_ops {
    /* right */
    void (*forward)(struct turtle *turtle, int pixels);
    void (*left)(struct turtle *turtle, int degrees);
    void (*right)(struct turtle *turtle, int degrees);
};

struct turtle {
    struct turtle_ops *ops;
};

struct draw;

struct draw_ops {
    /* 0 = right, degrees counter-clockwise */
    void (*draw)(struct draw *draw, int steps, int direction);
};

struct draw {
    struct draw_ops *ops;
};

/* public */
void draw_line(struct draw *draw_object, int steps, int direction)
{
    draw_object->ops->draw(draw_object, steps, direction);
}

/* concrete turtle */

struct test_turtle {
    // data
    struct turtle turtle;
};

static void test_forward(struct turtle *turtle, int pixels)
{
    // container_of
    printf("forward %d\n", pixels);
}

static void test_left(struct turtle *turtle, int degrees)
{
    // container_of
    printf("left %d\n", degrees);
}

static void test_right(struct turtle *turtle, int degrees)
{
    // container_of
    printf("right %d\n", degrees);
}

static struct turtle_ops test_turtle_ops = {
    .forward = test_forward,
    .left = test_left,
    .right = test_right,
};

/* public */
struct turtle *new_test_turtle()
{
    struct test_turtle *turtle;

    turtle = malloc(sizeof *turtle);
    if (!turtle)
        abort();

    turtle->turtle.ops = &test_turtle_ops;

    return &turtle->turtle;
}

/* adapter */

struct adapter {
    struct turtle *turtle;
    int direction;
    int pixels_per_step;
    struct draw draw;
};

static void adapter_draw(struct draw *draw, int steps, int direction)
{
    struct adapter *adapter = container_of(struct adapter, draw, draw);
    struct turtle *turtle = adapter->turtle;

    turtle->ops->left(turtle, direction - adapter->direction);
    adapter->direction = direction;
    turtle->ops->forward(turtle, steps * adapter->pixels_per_step);
}

static struct draw_ops adapter_draw_ops = {
    .draw = adapter_draw,
};

/* public */
struct draw *new_adapter(struct turtle *turtle)
{
    struct adapter *adapter;

    adapter = malloc(sizeof *adapter);
    if (!adapter)
        abort();

    adapter->turtle = turtle;
    adapter->direction = 0;
    adapter->pixels_per_step = 20;
    adapter->draw.ops = &adapter_draw_ops;

    return &adapter->draw;
}

/* test */

int main()
{
    struct turtle *turtle = new_test_turtle();
    struct draw *adapter = new_adapter(turtle);

    draw_line(adapter, 5, 0); /* three steps right */
    draw_line(adapter, 3, 90);
    draw_line(adapter, 5, 180);
    draw_line(adapter, 2, 270);
}
