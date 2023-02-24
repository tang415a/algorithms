// Given an integer array where each number appears twice except three numbers,
// find out these three numbers. For example, the array is
// [1,3,2,5,3,8,5,4,6,1,7,7,4], then output 2, 6, 8.

#include <stdio.h>

bool oddThree(int *arr, int siz, int &one, int &two, int &three) {
  int res = 0, i = 0;
  for (; i < siz; i++)
    res ^= arr[i];
  int base = 1;
  for (i = 0; i < 32; i++) {
    one = 0;
    two = 0;
    for (int j = 0; j < siz; j++) {
      if (arr[j] & base)
        one ^= arr[j];
      else
        two ^= arr[j];
    }
    if (one != res && two != res)
      break;
    base <<= 1;
  }
  if (i >= 32)
    return false;

  int cnt1 = 0, cnt2 = 0;
  for (i = 0; i < siz; i++) {
    if (arr[i] == one)
      cnt1++;
    if (arr[i] == two)
      cnt2++;
  }
  if (cnt2 & 0x1) {
    int tmp = one;
    one = two;
    two = tmp;
  }

  res = 0;
  for (int i = 0; i < siz; i++)
    res ^= arr[i];
  res ^= one;

  base = 1;
  for (i = 0; i < 32; i++) {
    if (res & base)
      break;
    base <<= 1;
  }
  if (i >= 32)
    return false;

  two = 0;
  three = 0;
  for (i = 0; i < siz; i++) {
    if (arr[i] & base)
      two ^= arr[i];
    else
      three ^= arr[i];
  }
  if (one & base)
    two ^= one;
  else
    three ^= one;
  return true;
}

int main() {
  int arr[] = {1, 3, 2, 5, 3, 8, 5, 4, 6, 1, 7, 7, 4};
  int one, two, three;
  oddThree(arr, sizeof(arr) / sizeof(arr[0]), one, two, three);
  printf("%d %d %d ", one, two, three);
  return 0;
}