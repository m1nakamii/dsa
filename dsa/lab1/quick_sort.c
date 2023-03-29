#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
void quick_sort(uint32_t arr[], int left, int right) {
  int i = left, j = right;
  int temp, pivot = arr[(left + right) / 2];

  while (i <= j) {
    while (arr[i] < pivot) {
      i++;
    }
    while (arr[j] > pivot) {
      j--;
    }
    if (i <= j) {
      temp = arr[i];
      arr[i] = arr[j];
      arr[j] = temp;
      i++;
      j--;
    }
  }

  if (left < j) {
    quick_sort(arr, left, j);
  }
  if (i < right) {
    quick_sort(arr, i, right);
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
  quick_sort(arr, 0, n - 1);
  clock_t end = clock();

  printf("Sorted array: ");
  for (int i = 0; i < n; i++) {
    printf("%" PRIu32 " ", arr[i]);
  }
  printf("\n");

  double time_spent = (double)(end - start) / CLOCKS_PER_SEC;
  printf("Time taken by quick sort: %f seconds\n", time_spent);

  return 0;
}
