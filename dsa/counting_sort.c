#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void counting_sort(uint32_t arr[], int n) {
  int i, max = arr[0];
  for (i = 1; i < n; i++) {
    if (arr[i] > max) {
      max = arr[i];
    }
  }
  int *count = (int *)malloc((max + 1) * sizeof(int));
  for (i = 0; i <= max; i++) {
    count[i] = 0;
  }
  for (i = 0; i < n; i++) {
    count[arr[i]]++;
  }
  for (i = 1; i <= max; i++) {
    count[i] += count[i - 1];
  }
  int output[n];
  for (i = n - 1; i >= 0; i--) {
    output[count[arr[i]] - 1] = arr[i];
    count[arr[i]]--;
  }
  for (int i = 0; i < n; i++) {
    arr[i] = output[i];
  }
  free(count);
}

int main() {

  const int k = 1000000;
  uint32_t arr[k];
  for (int i = 0; i < k; i++) {
    arr[i] = rand() % 100000;
  }

  int n = sizeof(arr) / sizeof(arr[0]);

  clock_t start = clock();
  counting_sort(arr, n);
  clock_t end = clock();

  printf("Sorted array: ");
  for (int i = 0; i < n; i++) {
    printf("%" PRIu32 " ", arr[i]);
  }
  printf("\n");

  double time_spent = (double)(end - start) / CLOCKS_PER_SEC;
  printf("Time taken by counting sort: %f seconds\n", time_spent);

  return 0;
}
