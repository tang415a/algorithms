// Write a merge sort algorithm.

#include <stdio.h>

void merge_arr(int *arr, int low, int mid, int high) {
  int* temp = new int[high - low + 1];
  int i = low, j = mid + 1, k = 0;
  while(i <= mid && j <= high) {
    if (arr[i] < arr[j])
      temp[k++] = arr[i++];
    else
      temp[k++] = arr[j++];    
  }
  while(i <= mid) temp[k++] = arr[i++];
  while(j <= high) temp[k++] = arr[j++];
  for (i = low; i <= high; i++)
    arr[i] = temp[i - low];
  delete[] temp;
}

void merge_sort(int *arr, int low, int high) {
  if (low >= high)
    return;
  int mid = low + (high - low) / 2;
  merge_sort(arr, low, mid);
  merge_sort(arr, mid + 1, high);
  merge_arr(arr, low, mid, high);
}

void mergeSort(int *arr, int siz) {
  merge_sort(arr, 0, siz - 1);
}

int main() {
  int arr[] = {2, 1, 2, 5, 3, 16, 10, 9, 4, 8, 7};
  mergeSort(arr, sizeof(arr) / sizeof(arr[0]));
  for(auto& d: arr) {
    printf("%d ", d);
  }
  return 0;
}