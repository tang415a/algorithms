// Write a heap sort algorithm.

#include <stdio.h>

void heap(int *arr, int bottom) {
  int top = (bottom - 1) / 2;
  while (top >= 0) {
    int maxChild = 2 * top + 1;
    if (maxChild < bottom && arr[maxChild] < arr[maxChild + 1]) maxChild++;
    if (arr[maxChild] > arr[top]) {
      int tmp = arr[maxChild];
      arr[maxChild] = arr[top];
      arr[top] = tmp;
    }
    top--;
  }
}

void heap_sort(int *arr, int siz) {
  while (siz > 1) {
    heap(arr, siz - 1);
    int tmp = arr[0];
    arr[0] = arr[siz - 1];
    arr[siz - 1] = tmp;
    siz--;
  }
}

int main() {
  int arr[] = {2, 1, 0, -1, 3, 4, 2, 0, -5, 6, -3};
  heap_sort(arr, sizeof(arr) / sizeof(arr[0]));
  for (auto& a: arr) {
    printf("%d ", a);
  }
  return 0;
}