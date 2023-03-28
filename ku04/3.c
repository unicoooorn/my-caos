//
// Created by Roman Gostilo on 11.03.2023.
//
#include <fcntl.h>
#include <stdint.h>
#include <stdio.h>
#include <sys/mman.h>
#include <unistd.h>

struct Node {
    int32_t key;
    int32_t left_idx;
    int32_t right_idx;
};

void print_tree_inorder(struct Node arr[], int32_t idx) {
    struct Node buf = arr[idx];
    if (buf.right_idx) {
        print_tree_inorder(arr, buf.right_idx);
    }
    printf("%d ", buf.key);
    if (buf.left_idx) {
        print_tree_inorder(arr, buf.left_idx);
    }
}

int main(int argc, char **argv) {
    int fd = open(argv[1], O_RDONLY);
    off_t filesize = lseek(fd, 0, SEEK_END);
    struct Node *node_arr =
        (struct Node *)mmap(NULL, filesize, PROT_READ, MAP_PRIVATE, fd, 0);
    print_tree_inorder(node_arr, 0);
    puts("\n");
}
