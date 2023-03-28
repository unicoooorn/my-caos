#include <asm/unistd_32.h>
#include <sys/syscall.h>
#include <sys/unistd.h>

enum { BUF_SIZE = 4 };

struct FileWriteState {
    int fd;
    unsigned char *buf;
    int bufsize;
    unsigned char *pivot;
};

unsigned char write_buf[BUF_SIZE];
struct FileWriteState stout_fws = {1, write_buf, BUF_SIZE, write_buf};
struct FileWriteState *stout = &stout_fws;

void flush(struct FileWriteState *out) {
    if (out->pivot - out->buf) {
        ssize_t written_count;
        asm volatile("int $0x80"
                     : "=m"(written_count)
                     : "a"(SYS_write), "b"(out->fd), "c"(out->buf),
                       "d"(out->pivot - out->buf));
    }
    out->pivot = out->buf;
}

void writechar(int c, struct FileWriteState *out) {
    if (!out) {
        return;
    }
    *(out->pivot++) = c;
    if (out->pivot - out->buf >= out->bufsize) {
        flush(out);
    }
}

int main() {
    writechar('a', stout);
    writechar('a', stout);
    writechar('a', stout);
    writechar('\n', stout);
    //    flush(stout);
}