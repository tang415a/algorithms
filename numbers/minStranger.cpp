// Given an array of positive integers, find out the minimum positive integer
// that has not been included in the array. For example, for [1, 5, 7, 2, 8],
// the output is 3. For [5, 3, 2, 7], the output is 1.

#include <memory.h>
#include <stdio.h>

// algorithm 1
int minStranger(int *arr, int siz) {
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

// algorithm 2
int minStranger2(int *arr, int siz) {
  bool *flags = new bool[siz];
  memset(flags, false, sizeof(bool) * siz);
  int i = 0;
  for (; i < siz; i++) {
    if (arr[i] <= 0 || arr[i] > siz)
      continue;
    flags[arr[i] - 1] = true;
  }
  i = 0;
  for (; i < siz; i++) {
    if (!flags[i])
      break;
  }
  delete[] flags;
  return i + 1;
}

int main() {
  int arr[] = {2, 1, 2, 5, 3, 16, 10, 9, 4, 8, 7};
  printf("%d", minStranger2(arr, sizeof(arr) / sizeof(arr[0])));
  getchar();
  return 0;
}