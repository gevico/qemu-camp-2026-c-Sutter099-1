#include "doubly_circular_queue.h"

#include <stdlib.h>

// 头尾哨兵
static struct node tailsentinel;
static struct node headsentinel = {0, NULL, &tailsentinel};
static struct node tailsentinel = {0, &headsentinel, NULL};

static link head = &headsentinel;
static link tail = &tailsentinel;

link make_node(int data) {
    link item = malloc(sizeof(struct node));

    item->data = data;
    item->prev = NULL;
    item->next = NULL;

    return item;
}

void free_node(link p) {
    link prev = p->prev, next = p->next;

    if (p == head || p == tail)
        return;

    prev->next = next;
    next->prev = prev;

    free(p);
}

link search(int key) {
    link item = head->next;

    while (item != tail) {
        if (item->data == key)
            return item;

        item = item->next;
    }

    return NULL;
}

void insert(link p) {
    if (!p)
        return;

    p->next = head->next;
    p->prev = head;
    head->next = p;
    p->next->prev = p;
}

void delete(link p) {
    free_node(p);
}

void traverse(void (*visit)(link)) {
    link it = head->next;

    while (it != tail) {
        visit(it);
        it = it->next;
    }
}

void destroy(void) {
    link it = head->next, next;

    while (it != tail) {
        next = it->next;
        free(it);
        it = next;
    }

    head->next = tail;
    tail->prev = head;
}
