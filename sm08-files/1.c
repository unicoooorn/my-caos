#include <ctype.h>
#include <errno.h>
#include <math.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void relax(const char *buf, int32_t *p_max_int_val, double *p_min_dbl_val,
           bool *round_found, bool *real_found) {
    enum { MAX_WORD_SIZE = 63 };

    if (isspace(buf[0])) {
        return;
    }

    bool is_round = true;
    if (!isdigit(buf[0]) && buf[0] != '-' && buf[0] != '+') {
        is_round = false;
    }
    if ((buf[0] == '-' || buf[0] == '+') && isspace(buf[1])) {
        is_round = false;
    }
    int ptr = 1;
    while (is_round && !isspace(buf[ptr])) {
        if (!isdigit(buf[ptr++])) {
            is_round = false;
        }
    }

    if (is_round) {
        long int_val = strtol(buf, NULL, 10);
        if (INT32_MIN <= int_val && int_val <= INT32_MAX &&
            *p_max_int_val <= int_val) {
            *round_found = true;
            *p_max_int_val = int_val;
        }
        return;
    }

    char *end;
    errno = 0;
    double dbl_val = strtod(buf, &end);
    if (errno == 0 && isspace(*end)) {
        *real_found = true;
        if (isnan(dbl_val) || *p_min_dbl_val >= dbl_val) {
            *p_min_dbl_val = dbl_val;
        }
    }
}

void kill_program_with_error(const char *error_str) {
    perror(error_str);
    exit(1);
}

void check_errno(const char *error_str) {
    if (errno != 0) {
        kill_program_with_error(error_str);
    }
}

int main(int argc, char *argv[]) {
    enum { MAX_WORD_SIZE = 63 };

    if (argc > 2) {
        kill_program_with_error("Too much arguments\n");
    } else if (argc == 0) {
        kill_program_with_error("Not enought arguments\n");
    }
    errno = 0;
    FILE *file = (argc == 1 ? stdin : fopen(argv[1], "r+"));
    check_errno("Can't open the file\n");
    int c;
    char buf[MAX_WORD_SIZE + 1];
    double min_dbl_val = INFINITY;
    int32_t max_int_val = INT32_MIN;
    int sym_count = 0;
    bool real_found = false, round_found = false;
    while ((c = getc_unlocked(file)) != EOF) {
        if (ferror(file) != 0) {
            kill_program_with_error("Unable to scan symbol\n");
        }
        if (iscntrl(c) && c != '\t' && !('\n' <= c && c <= '\r')) {
            kill_program_with_error("Unexpected symbol in input data\n");
        }
        if (isspace(c)) {
            buf[sym_count] = c;
            relax(buf, &max_int_val, &min_dbl_val, &round_found, &real_found);
            sym_count = 0;
        } else {
            buf[sym_count++] = (isascii(c) ? c : 'b');
            if (sym_count == MAX_WORD_SIZE + 1) {
                kill_program_with_error("Word length limit exceeded\n");
            }
        }
        errno = 0;
    }
    if (ferror(file) != 0) {
        kill_program_with_error("Unable to scan symbol\n");
    }
    buf[sym_count] = ' ';
    relax(buf, &max_int_val, &min_dbl_val, &round_found, &real_found);
    // closing the file
    if (file != stdin) {
        errno = 0;
        fclose(file);
        check_errno("Can't close the file\n");
    }
    if (!real_found || !round_found) {
        kill_program_with_error(
            "There is no real/integer value in input data\n");
    }
    errno = 0;
    printf("%d %.10g\n", max_int_val, min_dbl_val);
    check_errno("Unable to print the ans\n");
}