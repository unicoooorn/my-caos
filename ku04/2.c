#include <fcntl.h>
#include <unistd.h>

int separate(int fd_in, int fd_out_even, int fd_out_odd) {
    int buf;
    void *buf_ptr = &buf;
    ssize_t bytes_count;
    while (1) {
        bytes_count = read(fd_in, buf_ptr, sizeof(buf));
        if (bytes_count < 0) {
            return -1;
        } else if (bytes_count == 0) {
            break;
        }

        if (0 >
            write((buf & 1 ? fd_out_odd : fd_out_even), buf_ptr, sizeof(buf))) {
            return -1;
        }
    }
    return 0;
}

int main(int argc, char **argv) {
    int fd_in = open("test_in", O_RDWR);
    int fd_out_even = open("test_out_even", O_RDWR);
    int fd_out_odd = open("test_out_odd", O_RDWR);
    separate(fd_in, fd_out_even, fd_out_odd);
}