#include <stdio.h>
#include <ctype.h>

void strip_spaces(char *buf_ptr) {
    char *new_buf_ptr = buf_ptr;
    while (isspace(*(buf_ptr))) {
        ++buf_ptr;
    }
    char prev_symb = *(buf_ptr);
    while (*buf_ptr != '\0') {
        if (!isspace(*buf_ptr) && isspace(prev_symb)) {
            *(new_buf_ptr++) = ' ';
            *(new_buf_ptr++) = *buf_ptr;
        } else if (!isspace(*buf_ptr)) {
            *(new_buf_ptr++) = *buf_ptr;
        }
        prev_symb = *(buf_ptr++);
    }
    *new_buf_ptr = '\0';
}


int main(void) {
    char buf[] = "    s   s    ";
    strip_spaces(buf);
    printf("%s\n", buf);
}
