#include <ctype.h>
#include <errno.h>
#include <fcntl.h>
#include <float.h>
#include <math.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <unistd.h>

/*
Программе в аргументе командной строки задается имя непустого бинарного файла,
содержащего массив вещественных чисел двойной точности.

На стандартный поток вывода напечатайте в шестнадцатеричном виде (%a) среднее
арифметическое чисел в файле.

Используйте mmap для обработки входного файла. Предполагайте, что входной файл
целиком помещается в память.
*/

int main(int argc, char **argv) {
    int fd = open(argv[1], O_RDONLY);

    off_t filesize = lseek(fd, 0, SEEK_END);

    void *mp = mmap(NULL, filesize, PROT_READ, MAP_PRIVATE, fd, 0);
    double *mp_c = mp;

    double dbl_sum = 0;
    int dbl_count = filesize / sizeof(double);
    for (int i = 0; i < dbl_count; i++) {
        dbl_sum += mp_c[i];
    }
    printf("%a\n", dbl_sum / dbl_count);
}