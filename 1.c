// https://pastebin.com/xJuj5YAn

#include <stdio.h>
#include <stdlib.h>

/* macro library */

#define DECLARE_LIST(struct_name) \
    struct struct_name##_list { \
        struct struct_name *items; \
        size_t length; \
    }; \
    static void new_##struct_name(struct struct_name##_list *list) \
    { \
        static int key = 0; \
        list->length++; \
        list->items = realloc(list->items, list->length * sizeof *list->items); \
        list->items[list->length-1].id = key++; \
    } \
    static inline void foreach_##struct_name(struct struct_name##_list *list, void (*callback)(struct struct_name *)) \
    { \
        for (struct struct_name *item = list->items; item != list->items + list->length; item++) \
            callback(item); \
    }

#define foreach(struct_name, list, item_) \
        for (item_ = (list).items; item_ != (list).items + (list).length; item_++)

// linked-list
// #define foreach(struct_name, list, data_) \
//   for (struct device_item *_item = list->first; _item ? (data_ = &item->data) : NULL; _item = _item->next)

/* user code */

struct device {
    int id;
};
DECLARE_LIST(device)

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

    struct device *device;
    foreach (device, list, device)
        print_callback(device);
}