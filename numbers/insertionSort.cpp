// Write an insertion sort algorithm.

#include <stdio.h>

void insertion_sort(int *arr, int siz)
{
  for (int i = 1; i < siz; i++)
  {
    int j = i, item = arr[j];
    while (j > 0 && item < arr[j - 1])
    {
      arr[j] = arr[j - 1];
      j--;
    }
    if (j != i)
      arr[j] = item;
  }
}

int main()
{
  int arr[] = {2, 3, 1, 0, 8, 5, 6, 4, 7};
  insertion_sort(arr, sizeof(arr) / sizeof(arr[0]));
  for (auto& d: arr)
    printf("%d ", d);
  return 0;
}