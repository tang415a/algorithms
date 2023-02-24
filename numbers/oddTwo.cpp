// Given an integer array where each number appears twice except two numbers,
// find out these two numbers. For example, the array is
// [1,3,2,5,3,5,4,6,1,7,7,4], then output 2, 6.

#include <stdio.h>

bool oddTwo(int *arr, int siz, int &one, int &two) {
  int res = 0;
  for (int i = 0; i < siz; i++)
    res ^= arr[i];
  int i = 0, base = 1;
  for (; i < 32; i++) {
    if (res & base)
      break;
    base <<= 1;
  }
  if (i >= 32)
    return false;

  one = 0;
  two = 0;
  for (int i = 0; i < siz; i++) {
    if (arr[i] & base)
      one ^= arr[i];
    else
      two ^= arr[i];
  }
  return true;
}

int main() {
  int arr[] = {1, 3, 2, 5, 3, 5, 4, 6, 1, 7, 7, 4};
  int one, two;
  oddTwo(arr, sizeof(arr) / sizeof(arr[0]), one, two);
  printf("%d %d ", one, two);
  return 0;
}