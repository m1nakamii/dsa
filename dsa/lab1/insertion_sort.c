#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void insertion_sort(uint32_t arr[], int size) {
  int i, j, temp;
  for (i = 1; i < size; i++) {
    temp = arr[i];
    j = i - 1;
    while (j >= 0 && arr[j] > temp) {
      arr[j + 1] = arr[j];
      j--;
    }
    arr[j + 1] = temp;
  }
}

int main() {

  const int k = 50000;
  uint32_t arr[k];
  for (int i = 0; i < k; i++) {
    arr[i] = rand() % 100000;
  }

  int n = sizeof(arr) / sizeof(arr[0]);

  clock_t start = clock();
  insertion_sort(arr, n);
  clock_t end = clock();

  printf("Sorted array: ");
  for (int i = 0; i < n; i++) {
    printf("%" PRIu32 " ", arr[i]);
  }
  printf("\n");

  double time_spent = (double)(end - start) / CLOCKS_PER_SEC;
  printf("Time taken by insertion sort: %f seconds\n", time_spent);

  return 0;
}
