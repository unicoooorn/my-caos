#include <setjmp.h>
#include <stdio.h>
#include <stdlib.h>

enum { MAX_JMP_STACK_DEPTH = 10, NO_HANDLER_FOUND_ERROR = 13 };

jmp_buf handler_buf[MAX_JMP_STACK_DEPTH];
int exception_buf[MAX_JMP_STACK_DEPTH];
int cur_ptr_buf = 0;

jmp_buf *try(int exception) {
    exception_buf[cur_ptr_buf] = exception;
    jmp_buf *cur_stack = &(handler_buf[cur_ptr_buf]);
    cur_ptr_buf++;
    return cur_stack;
}

void endtry() {
    cur_ptr_buf--;
}

void throw(int exception) {
    cur_ptr_buf--;
    while (exception_buf[cur_ptr_buf] != exception) {
        if (cur_ptr_buf == -1) {
            exit(NO_HANDLER_FOUND_ERROR);
        }
        cur_ptr_buf--;
    }
    longjmp(handler_buf[cur_ptr_buf], 1);
}

int main(void) {
    if (!setjmp(*try(42))) {
        puts("level 1");
        if (!setjmp(*try(1))) {
            puts("level 2");
            throw(42);
            puts("this string is not displayed");
            endtry();
        } else {
            puts("handle exception 1");
        }
        endtry();
    } else {
        puts("handle exception 42");
    }
}