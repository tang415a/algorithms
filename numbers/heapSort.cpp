// Write a heap sort algorithm.

#include <stdio.h>

void heap(int *arr, int bottom) {
  int top = (bottom - 1) / 2;
  while (top >= 0) {
    int maxChild = 2 * top + 1;
    if (maxChild < bottom && arr[maxChild] < arr[maxChild + 1])
      maxChild++;
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

// second solution - minor tweaks
void heap_sort0(int *arr, int size) {
  int top = size / 2 - 1;
  while (top >= 0) {
    int maxChild = 2 * top + 1;
    if (maxChild + 1 < size && arr[maxChild] < arr[maxChild + 1])
      maxChild++;
    if (arr[maxChild] > arr[top]) {
      int tmp = arr[top];
      arr[top] = arr[maxChild];
      arr[maxChild] = tmp;
    }
    --top;
  }
  int tmp = arr[0];
  arr[0] = arr[size - 1];
  arr[size - 1] = tmp;
}

void heapSort(int *arr, int size) {
  for (int i = size; i > 1; --i) {
    heap_sort0(arr, i);
  }
}

int main() {
  // int arr[] = {2, 1, 0, -1, 3, 4, 2, 0, -5, 6, -3};
  // heap_sort(arr, sizeof(arr) / sizeof(arr[0]));
  int arr[] = {1,5,4,3,2,8,6,7};
  heapSort(arr, sizeof(arr) / sizeof(arr[0]));
  for (auto &a : arr) {
    printf("%d ", a);
  }
  return 0;
}