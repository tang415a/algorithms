/*
Let's call an array A a mountain if the following properties hold:

A.length >= 3
There exists some 0 < i < A.length - 1 such that A[0] < A[1] < ... A[i-1] < A[i] > A[i+1] > ... > A[A.length - 1]
Given an array that is definitely a mountain, return any i such that A[0] < A[1] < ... A[i-1] < A[i] > A[i+1] > ... > A[A.length - 1].

Example 1:

Input: [0,1,0]
Output: 1
Example 2:

Input: [0,2,1,0]
Output: 1
Note:

1. 3 <= A.length <= 10000
2. 0 <= A[i] <= 10^6
3. A is a mountain, as defined above.
*/

#include <stdio.h>

int peakIndex(int arr[], int siz)
{
  int left = 0, right = siz - 1;
  while(left < right) {
    int mid = left + (right - left) / 2;
    if (arr[mid] > arr[mid - 1] && arr[mid] > arr[mid + 1])
      return mid;
    if (arr[mid] > arr[mid - 1] && arr[mid] < arr[mid + 1])
      left = mid + 1;
    if (arr[mid] < arr[mid - 1] && arr[mid] > arr[mid + 1])
      right = mid - 1;
  }
  return -1;
}

int main() 
{
  int arr[] = {0,1,2,1,0};
  printf("Peak index: %d\n", peakIndex(arr, sizeof(arr) / sizeof(arr[0])));
  return 0;
}