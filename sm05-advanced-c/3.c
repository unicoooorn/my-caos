#include <stdio.h>
#include <stdlib.h>

struct Node {
    struct Node *next;
    int val;
};

struct Node *new_node(int t_val, struct Node *t_next) {
    struct Node *new = calloc(1, sizeof(*new));
    new->next = t_next;
    new->val = t_val;
    return new;
}

int main(void) {
    int cur;
    if (1 != scanf("%d", &cur)) {
        return 0;
    }

    struct Node *cur_node = new_node(cur, NULL);
    while (scanf("%d", &cur) != EOF) {
        cur_node = new_node(cur, cur_node);
    }

    struct Node *root = cur_node;
    while (cur_node) {
        printf("%d\n", cur_node->val);
        cur_node = cur_node->next;
    }

    while (root) {
        struct Node *tmp = root->next;
        free(root);
        root = tmp;
    }
}