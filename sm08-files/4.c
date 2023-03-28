//
// Created by Roman Gostilo on 05.03.2023.
//
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

struct Node {
    int32_t key;
    int32_t left_idx;
    int32_t right_idx;
};

void print_tree_inorder(int fd, int32_t idx) {
    struct Node buf;
    lseek(fd, idx * sizeof(buf), SEEK_SET);
    errno = 0;
    if (read(fd, &buf, sizeof(buf)) == -1 || errno) {
        exit(1);
    }
    if (buf.right_idx) {
        print_tree_inorder(fd, buf.right_idx);
    }
    printf("%d ", buf.key);
    if (buf.left_idx) {
        print_tree_inorder(fd, buf.left_idx);
    }
}

int main(int argc, char **argv) {
    int fd = open(argv[1], O_RDONLY);
    print_tree_inorder(fd, 0);
    puts("\n");
}