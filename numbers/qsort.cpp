// Write a quick sort algorithm.

#include <stdio.h>

void do_qsort(int arr[], int low, int high) {
  if (low >= high)
    return;
  
  int lo = low, hi = high + 1, item = arr[low];
  while(true){
    while(++lo <= high && arr[lo] <= item) ;
    while(--hi > low && arr[hi] >= item) ;
    if (lo < hi) {
      int tmp = arr[lo];
      arr[lo] = arr[hi];
      arr[hi] = tmp;
    }
    else
      break;
  }
  arr[low] = arr[hi];
  arr[hi] = item;
  do_qsort(arr, low, hi - 1);
  do_qsort(arr, hi + 1, high);
}

void qsort(int arr[], int siz) {
  do_qsort(arr, 0, siz - 1);
}

int main() {
  int arr[] = {2, 1, 0, -1, 3, 4, 2, 0, -5, 6, -3};
  qsort(arr, sizeof(arr) / sizeof(arr[0]));
  for (auto& a: arr) {
    printf("%d ", a);
  }
  return 0;
}