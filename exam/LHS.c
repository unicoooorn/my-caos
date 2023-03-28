//
// Created by Roman Gostilo on 25.03.2023.
//

#include <dirent.h>
#include <err.h>
#include <stdio.h>
#include <sys/stat.h>
#include <string.h>

/*
После имени поддиректорий должен выводиться символ '/'.
После имени обычных (regular) файлов, ATTENTION -> исполнимых для их владельца, должен выводиться символ '*'.
После имени символических ссылок должен выводиться символ '@'.
 */

void classify_path(char *path) {
    if (!strcmp(path, "..") || !strcmp(path, ".")) {
        return;
    }
    struct stat st;
    lstat(path, &st);
    switch (st.st_mode & S_IFMT) {
        case S_IFLNK:
            printf("%s@\n", path);
            return;
        case S_IFDIR:
            printf("%s/\n", path);
            return;
        case S_IFREG:
            if (st.st_mode & S_IXUSR) {
                printf("%s*\n", path);
            } else {
                printf("%s\n", path);
            }
            return;
        default:
            printf("%s\n", path);
            return;
    }
}


int main(int argc, char** argv) {
    DIR *dir;
    struct dirent *dp;
    if ((dir = opendir (argv[1])) == NULL) {
        printf("cannot open");
        return 1;
    }
    while ((dp = readdir (dir)) != NULL) {
        classify_path(dp->d_);
    }
}