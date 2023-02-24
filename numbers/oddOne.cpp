// Given an integer array where each number appears twice except one number,
// find out this number. For example, the array is [1,3,5,3,5,4,6,1,7,7,4], then
// output 6.

#include <stdio.h>

int oddOne(int *arr, int siz) {
  int res = 0;
  for (int i = 0; i < siz; i++)
    res ^= arr[i];
  return res;
}

int main() {
  int arr[] = {1, 3, 5, 3, 5, 4, 6, 1, 7, 7, 4};
  printf("%d ", oddOne(arr, sizeof(arr) / sizeof(arr[0])));
  return 0;
}