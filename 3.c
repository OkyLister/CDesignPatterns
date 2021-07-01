// https://pastebin.com/Ken2vpft

#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

// #define foreach(struct_name, list, data_) \
//   for (struct device_item *_item = list->first; _item ? (data_ = &item->data) : NULL; _item = _item->next)

/* user code */

struct list_head {
    struct list_head *next;
};

struct device {
    int id;
    struct list_head list;
};

// --device-- --id-- (int)
// struct list_head
#define container_of(type, list, list_) \
    (type*)((char *)list_ - offsetof(type, list))

void print_callback(struct device *device)
{
    printf("device %d\n", device->id);
}

void list_add(struct list_head **list, struct list_head *item)
{
    item->next = *list;
    *list = item;
}

int main()
{
    struct device d1 = { .id = 1, .list = { .next = NULL }};
    struct device d2 = { .id = 2, .list = { .next = NULL }};

    struct list_head *list = NULL;
    list_add(&list, &d1.list);
    list_add(&list, &d2.list);

    for (struct list_head *item = list; item; item = item->next) {
        struct device *dev = container_of(struct device, list, item);
        printf("device %d\n", dev->id);
    }
}
