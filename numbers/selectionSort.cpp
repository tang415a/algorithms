// Write a selection sort algorithm.

#include <stdio.h>

void selection_sort(int *arr, int siz)
{
  for(int i = 0; i < siz - 1; i++)
  {
    int min = i;
    for(int j = i + 1; j < siz; j++)
    {
      if(arr[min] > arr[j])
        min = j;
    }
    if (min != i)
    {
      int tmp = arr[i];
      arr[i] = arr[min];
      arr[min] = tmp;
    }
  }
}

int main()
{
  int arr[] = {2, 1, 0, -1, 3, 4, 2, 0, -5, 6, -3};
  selection_sort(arr, sizeof(arr) / sizeof(arr[0]));
  for (auto& a: arr) {
    printf("%d ", a);
  }
  return 0;
}