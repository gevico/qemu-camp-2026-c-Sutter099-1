#include "singly_linked_list.h"

#include <stdio.h>
#include <stdlib.h>

// 全局头指针
static link head = NULL;

// 创建新节点
link make_node(unsigned char item) {
    link n = malloc(sizeof(struct node));

    n->item = item;

    return n;
}

// 释放节点
void free_node(link p) { free(p); }

// 查找节点
link search(unsigned char key) {
    link it = head;

    while (it) {
        if (it->item == key)
            return it;

        it = it->next;
    }

    return NULL;
}

// 在链表头部插入节点
void insert(link p) {
    push(p);
}

// 删除指定节点
void delete(link p) {
    link it = head, prev = NULL;

    if (!p || !head)
        return;

    while (it) {
        if (it == p)
            break;

        prev = it;
        it = it->next;
    }

    if (!prev) {
        head = head->next;
        free_node(it);
        return;
    }

    prev->next = it->next;
    it->next = NULL;
    free_node(it);
}

// 遍历链表
void traverse(void (*visit)(link)) {
    link it = head;

    while (it) {
        visit(it);
        it = it->next;
    }
}

// 销毁整个链表
void destroy(void) {
    free_list(head);
    head = NULL;
}

// 在链表头部推入节点
void push(link p) { 
    link old_head = head;

    p->next = old_head;
    head = p;
 }

// 从链表头部弹出节点
link pop(void) {
    link it = head;

    if (!head)
        return NULL;

    head = head->next;
    it->next = NULL;

    return it;
}

// 释放链表内存
void free_list(link list_head) {
    link it = list_head, tmp = NULL;

    while (it) {
        tmp = it;
        it = it->next;

        free_node(tmp);
    }
}
