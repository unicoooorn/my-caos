#include <stdio.h>
#include <stdlib.h>

void sort_by_abs(short int* arr, int length);

int main() {
  int n;
  scanf("%d", &n);

  short int *array = (short int*)malloc(n * sizeof(short int));
  
  for (int i = 0; i < n; ++i)
    scanf("%hd", &array[i]);

  sort_by_abs(array, n);
  
  for (int i = 0; i < n; ++i)
    printf("%hd ", array[i]);
  printf("\n");

  return 0;
}
