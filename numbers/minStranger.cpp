// Given an array of positive integers, find out the minimum positive integer that has not been included in the array.
// For example, for [1, 5, 7, 2, 8], the output is 3.
// For [5, 3, 2, 7], the output is 1.

#include <stdio.h>

int minStranger (int*arr, int siz){
  int l = 0, r = siz;
  while (l < r) {
    if (arr[l] == l + 1)
      l++;
    else if (arr[l] <= l || arr[l] > r || arr[arr[l] - 1] == arr[l])
      arr[l] = arr[--r];
    else {
      int tmp = arr[l];
      arr[l] = arr[tmp - 1];
      arr[tmp - 1] = tmp;
    }
  }
  return l + 1;
}

int main() {
  int arr[] = {2, 1, 2, 5, 3, 16, 10, 9, 4, 8, 7};
  printf("%d", minStranger(arr, sizeof(arr) / sizeof(arr[0])));
  return 0;
}