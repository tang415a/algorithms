/*
Given an array A of positive lengths, return the largest perimeter of a triangle with non-zero area, formed from 3 of these lengths.

If it is impossible to form any triangle of non-zero area, return 0.

Example 1:
Input: [2,1,2]
Output: 5

Example 2:
Input: [1,2,1]
Output: 0

Example 3:
Input: [3,2,3,4]
Output: 10

Example 4:
Input: [3,6,2,3]
Output: 8 

Note:

3 <= A.length <= 10000
1 <= A[i] <= 10^6
*/

#include <stdio.h>
#include <vector>
using namespace std;

void do_qsort(vector<int>& arr, int lo, int hi) {
  if (lo >= hi)
    return;
  int item = arr[lo], low = lo, high = hi + 1;
  while(true) {
    while(++low <= hi && arr[low] <= item);
    while(--high > lo && arr[high] >= item);
    if (low < high) {
      int tmp = arr[low];
      arr[low] = arr[high];
      arr[high] = tmp;
    }
    else
      break;
  }
  if (high > lo){
    arr[lo] = arr[high];
    arr[high] = item;
  }
  do_qsort(arr, lo, high - 1);
  do_qsort(arr, high + 1, hi);
}

void quickSort(vector<int>& arr) {
  do_qsort(arr, 0, arr.size() - 1);
}

int largestPerimeter(vector<int>& A) {
  int siz = A.size();
  if (siz < 3)
    return 0;
  quickSort(A);
  for(auto i = siz - 1; i > 1; i--) {
    if (A[i] < A[i-1] + A[i-2])
      return A[i] + A[i-1] + A[i-2];
  }
  return 0;
}

int main() {
  vector<int> A = {3,2,3,4};
  printf("%d", largestPerimeter(A));
  return 0;
}