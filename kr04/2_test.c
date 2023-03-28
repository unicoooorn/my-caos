#include <stdio.h>

int main() {
    FILE *in;
    int res[6];
    in = fopen("test_in","wb");  // w for write, b for binary
    int buf[] = {1, 4, 3, 6, 2, 7};
    fwrite(buf,sizeof(int),6,in);
    rewind(in);
    fread(res, sizeof(int), 6, in);
    printf("Result\n");
    for (int i = 0; i < 10; i++)
        printf("%d = %d\n", i, (int)res[i]);
}