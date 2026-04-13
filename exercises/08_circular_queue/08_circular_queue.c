#include <stdio.h>
#include <stdbool.h>

#define MAX_PEOPLE 50

typedef struct {
    int id;
} People;

typedef struct {
    People data[MAX_PEOPLE];
    int head;
    int tail;
    int count;
} Queue;

int main() {
    Queue q;
    int total_people=50;
    int report_interval=5;
    People tmp;
    unsigned long counter = 1;

    q.head = 0;
    q.tail = total_people - 1;
    q.count = total_people;
    for (int i = 0; i < 50; ++i) {
        tmp.id = i + 1;
        q.data[i] = tmp;
    }

    while (q.count > 1) {
        // dequeue and enqueue
        tmp = q.data[q.head];
        q.head = (q.head + 1) % MAX_PEOPLE;
        if (0 == counter % report_interval) {
            printf("淘汰: %d\n", tmp.id);
            q.count--;
        } else {
            q.tail = (q.tail + 1) % MAX_PEOPLE;
            q.data[q.tail] = tmp;
        }

        // only enqueue
        ++counter;
    }
    printf("最后剩下的人是: %d\n", q.data[q.head].id);

    return 0;
}
