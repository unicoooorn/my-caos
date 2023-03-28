//
// Created by Roman Gostilo on 11.03.2023.
//
#include <errno.h>
#include <stdio.h>
#include <sys/stat.h>

void classify_path(char *path) {
    errno = 0;
    struct stat buf;
    lstat(path, &buf);      // check return value
    if (errno == ENOENT) {  // TODO: any errno
        printf("%s (missing)\n", path);
    } else if ((buf.st_mode & S_IFMT) == S_IFLNK && stat(path, &buf) != 0) {
        printf("%s (broken symlink)\n", path);
    } else {
        printf("%s\n", path);
    }
}

int main(int argc, char **argv) {
    for (int i = 1; i < argc; i++) {
        classify_path(argv[1]);
    }
    return 0;
}
