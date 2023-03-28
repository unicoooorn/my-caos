#include <stdio.h>

int main(void) {
    FILE *file = fopen("./array_test", "wb");
    double arr[] = {1.2, 3., 5.5, 6.3, 7.};
    fwrite(arr, sizeof(arr[0]), sizeof(arr)/sizeof(arr[0]), file);
}