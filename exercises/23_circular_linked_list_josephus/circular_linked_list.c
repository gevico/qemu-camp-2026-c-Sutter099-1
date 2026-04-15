#include "circular_linked_list.h"

#include <stdio.h>
#include <stdlib.h>

Node* create_circular_list(int n) {
    Node *head, *item, *prev;

    if (n <= 0)
        return NULL;

    head = malloc(sizeof(struct Node));
    head->id = 1;
    head->next = head;
    prev = head;

    for (int i = 2; i <= n; ++i) {
        item = malloc(sizeof(struct Node));
        item->id = i;
        item->next = head;
        prev->next = item;
        prev = item;
    }

    return head;
}

void free_list(Node* head) {
    Node *item = head, *next;

    if (!head)
        return;

    while (item) {
        next = item->next;
        free(item);
        item = next;
    }
}
