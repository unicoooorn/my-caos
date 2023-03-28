#include "read_file.h"  // подключить при сдаче!!!
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

struct FileContent read_file(int fd) {
    struct FileContent fc = {-1, NULL};

    enum { BUF_SIZE = 4096 };

    ssize_t cur_size = 0;
    char *buf = calloc(BUF_SIZE, sizeof(*buf));
    if (!buf) {
        return fc;
    }
    char *cur_data = calloc(1, sizeof(*buf));
    if (!cur_data) {
        free(buf);
        return fc;
    }
    ssize_t char_read_count;
    errno = 0;
    int pivot = 0;
    while ((char_read_count = read(fd, buf, BUF_SIZE - 1))) {
        if (char_read_count < 0 || errno) {
            free(cur_data);
            cur_data = NULL;
            free(buf);
            buf = NULL;
            return fc;
        }
        char *tmp = realloc(cur_data, cur_size + char_read_count + 1);
        if (!tmp) {
            free(cur_data);
            cur_data = NULL;
            free(buf);
            buf = NULL;
            return fc;
        }
        cur_data = tmp;
        for (int i = 0; i < char_read_count; i++) {
            cur_data[pivot++] = buf[i];
        }
        cur_size += char_read_count;
        errno = 0;
    }
    free(buf);
    fc.data = cur_data;
    fc.size = cur_size;
    fc.data[pivot] = '\0';
    return fc;
}

int main() {
    int fd = open("test", O_RDWR);
    struct FileContent fc = read_file(fd);
    puts(fc.data);
    free(fc.data);
    printf("%ld\n", fc.size);
}