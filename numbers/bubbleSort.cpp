// Write a bubble sort algorithm.

#include <stdio.h>

void bubble(int *arr, int siz) {
  for(int i = siz - 1; i > 0; i--) {
    for(int j = 0; j < i; j++) {
      if (arr[j] > arr[j + 1]) {
        int tmp = arr[j];
        arr[j] = arr[j + 1];
        arr[j + 1] = tmp;
      }
    }
  }
}

int main() {
  int arr[] = {2, 1, 0, -1, 3, 4, 2, 0, -5, 6, -3};
  bubble(arr, sizeof(arr) / sizeof(arr[0]));
  for (auto& a: arr) {
    printf("%d ", a);
  }
  return 0;
}