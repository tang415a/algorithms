// Write a binary search algorithm.

#include <stdio.h>

int search(int target, int arr[], int siz)
{
  if (siz <= 0)
    return -1;
  
  int left = 0, right = siz - 1;
  while(left <= right)
  {
    int mid = left + (right - left) / 2;
    if (arr[mid] == target) return mid;
    if (arr[mid] > target)
      right = mid - 1;
    else
      left = mid + 1;
  }
  return -1;
}

int main() {
  int arr[] = {1,2};
  printf("%d\n", search(1, arr, sizeof(arr) / sizeof(arr[0])));
  getchar();
  return 0;
}