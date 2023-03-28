//
// Created by Roman Gostilo on 03.03.2023.
//
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

#ifndef SM08_READ_FILE_H
#define SM08_READ_FILE_H


struct FileContent {
    ssize_t size;
    char *data;
};

#endif //SM08_READ_FILE_H
