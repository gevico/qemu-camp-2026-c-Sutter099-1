#include "simple_tree.h"

#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

Queue *create_queue() {
    Queue *q = (Queue *)malloc(sizeof(Queue));
    q->front = q->rear = NULL;
    return q;
}

void enqueue(Queue *q, TreeNode *tree_node) {
    QueueNode *item;

    if (!q || !tree_node) return;

    item = malloc(sizeof(struct QueueNode));
    item->next = NULL;
    item->tree_node = tree_node;

    if (!q->front) {
        q->front = item;
        q->rear = item;
    } else {
        q->rear->next = item;
        q->rear = q->rear->next;
    }
}

TreeNode *dequeue(Queue *q) {
    TreeNode *tree_node;
    QueueNode *item;

    if (!q || is_empty(q)) return NULL;

    item = q->front;
    tree_node = item->tree_node;
    q->front = q->front->next;
    free(item);

    if (!q->front) q->rear = NULL;

    return tree_node;
}

bool is_empty(Queue *q) { return q->front == NULL; }

void free_queue(Queue *q) {
    while (!is_empty(q)) {
        dequeue(q);
    }
    free(q);
}

TreeNode *build_tree_by_level(int *level_order, int size) {
    if (size == 0 || level_order[0] == INT_MIN)
        return NULL;

    TreeNode *root = malloc(sizeof(TreeNode));
    root->val = level_order[0];
    root->left = root->right = NULL;

    Queue *q = create_queue();
    enqueue(q, root);

    int i = 1;
    while (i < size && !is_empty(q)) {
        TreeNode *parent = dequeue(q);

        if (i < size) {
            if (level_order[i] != INT_MIN) {
                TreeNode *node = malloc(sizeof(TreeNode));
                node->val = level_order[i];
                node->left = node->right = NULL;
                parent->left = node;
                enqueue(q, node);
            }
            i++;
        }

        if (i < size) {
            if (level_order[i] != INT_MIN) {
                TreeNode *node = malloc(sizeof(TreeNode));
                node->val = level_order[i];
                node->left = node->right = NULL;
                parent->right = node;
                enqueue(q, node);
            }
            i++;
        }
    }

    free_queue(q);
    return root;
}

void preorder_traversal(TreeNode *root) {
    if (!root)
        return;

    printf("%d ", root->val);
    preorder_traversal(root->left);
    preorder_traversal(root->right);
}

void preorder_traversal_iterative(TreeNode *root) {
    TreeNode *stack[256];
    int top = -1;

    if (!root)
        return;

    stack[++top] = root;
    while (top >= 0) {
        TreeNode *node = stack[top--];

        printf("%d ", node->val);
        if (node->right)
            stack[++top] = node->right;
        if (node->left)
            stack[++top] = node->left;
    }
}

void free_tree(TreeNode *root) {
    if (root == NULL) {
        return;
    }
    free_tree(root->left);
    free_tree(root->right);
    free(root);
}
