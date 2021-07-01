#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stddef.h>

#define container_of(type, list, list_) \
    (type*)((char *)list_ - offsetof(type, list))

// OBSERVER

struct subscriber_ops;

struct subscriber {
    struct subscriber *next;
    struct subscriber_ops *ops;
};

struct subscriber_ops {
    void (*receive)(struct subscriber *, const char *msg);
};

struct publisher {
    struct subscriber *subscribers;
};

void subscribe(struct publisher *p, struct subscriber *s)
{
    s->next = p->subscribers;
    p->subscribers = s;
}

void publish(struct publisher *p, const char *msg)
{
    for (struct subscriber *s = p->subscribers; s; s = s->next)
        if (s->ops && s->ops->receive)
            s->ops->receive(s, msg);
}

/* test subscriber */

struct test_subscriber {
    int id;
    struct subscriber subscriber;
};

static void test_receive(struct subscriber *s, const char *msg)
{
    struct test_subscriber *ts = container_of(struct test_subscriber, subscriber, s);
    printf("%d: %s\n", ts->id, msg);
}

static struct subscriber_ops test_subscriber_ops = {
    .receive = test_receive,
};

int main()
{
    struct publisher p = { .subscribers = NULL };
    struct test_subscriber s1 = { .id = 1, .subscriber = { .ops = &test_subscriber_ops } };
    struct test_subscriber s2 = { .id = 2, .subscriber = { .ops = &test_subscriber_ops } };

    subscribe(&p, &s1.subscriber);
    subscribe(&p, &s2.subscriber);

    publish(&p, "test");
}
