#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>

// TOVARNA?

#define ARRAY_SIZE(array) (sizeof array / sizeof *array)

/* abstract animal */

struct animal_ops;

struct animal {
    struct animal_ops *ops;
};

struct animal_ops {
    const char *name;
    void (*make_sound)(struct animal *animal);
    struct animal_ops *next;
};

struct animal_ops *types = NULL;

struct animal *new_animal(const char *spec)
{
    struct animal *animal;

    animal = malloc(sizeof *animal);
    if (!animal)
        abort();

    for (struct animal_ops *type = types; type; type = type->next) {
        if (strcmp(spec, type->name) == 0) {
            animal->ops = type;
            return animal;
        }
    }

    abort();
}

void register_animal_type(struct animal_ops *type)
{
    type->next = types;
    types = type;
}

/* cat */

static void cat_make_sound(struct animal *animal)
{
    printf("Miaow!\n");
}

static struct animal_ops cat_ops = {
    .name = "cat",
    .make_sound = cat_make_sound,
};

__attribute__((constructor))
void cat_register()
{
    register_animal_type(&cat_ops);
}

/* dog */

static void dog_make_sound(struct animal *animal)
{
    printf("Whoof!\n");
}

static struct animal_ops dog_ops = {
    .name = "dog",
    .make_sound = dog_make_sound,
    // .next = NULL
};

__attribute__((constructor))
void dog_register()
{
    register_animal_type(&dog_ops);
}

/* test */

int main()
{
    struct animal *animal[] = {
        new_animal("cat"),
        new_animal("dog"),
        new_animal("dog"),
    };

    for (int i = 0; i < ARRAY_SIZE(animal); i++)
        animal[i]->ops->make_sound(animal[i]);
}