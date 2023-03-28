#include "dlist.h"
#include <stdlib.h>

/*
Функция push создает новую Node со значением value и вставляет ее перед вершиной
place. Функция возвращает созданную на куче вершину.

Если place == NULL, то список пустой.

В случае неуспешной аллокации возвращайте NULL

Функция pop вынимает вершину из списка, высвобождает память вершины и возвращает
число из этой вершины

Пример использования:
Node * head = NULL;
head = push(head, 1);
head = push(head, 2);
pop(head->next) == 1;
pop(head) == 2;

typedef struct Node {
    struct Node *prev;
    struct Node *next;
    int value;
} Node;
*/

Node *push(Node *place, int value) {
    Node *new_node = calloc(1, sizeof(*new_node));
    if (!new_node) {
        return NULL;
    }
    new_node->value = value;
    if (place) {  // list isn't empty
        new_node->next = place;
        new_node->prev = place->prev;  // new_node is done
        if (new_node->prev) {
            new_node->prev->next = new_node;  // next is done
        }
        place->prev = new_node;  // prev is done
    } else {       // list is empty
        new_node->prev = 0;
        new_node->next = 0;
    }
    return new_node;
}

int pop(Node *node) {
    if (!node) {
        return 0;
    }
    if (node->prev) {
        node->prev->next = node->next;
    }
    if (node->next) {
        node->next->prev = node->prev;
    }
    int ret = node->value;
    free(node);
    return ret;
}