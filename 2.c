#include <stdio.h>
#include <stdlib.h>

struct device {
    int id;
};

struct device_list {
    struct device *items;
    size_t length;
};

void new_device(struct device_list *list)
{
    static int key = 0;

    list->length++;
    list->items = realloc(list->items, list->length * sizeof *list->items);
    list->items[list->length-1].id = key++;
}

void foreach_device(struct device_list *list, void (*callback)(struct device *))
{
    for (struct device *item = list->items; item != list->items + list->length; item++)
        callback(item);
}

void print_callback(struct device *device)
{
    printf("device %d\n", device->id);
}

int main()
{
    struct device_list list = { .items = NULL, .length = 0 };

    new_device(&list);
    new_device(&list);
    new_device(&list);
    foreach_device(&list, print_callback);
}