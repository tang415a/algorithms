/*
Given an unsorted array of integers, sort the array into a wave array. An array
arr[0..n-1] is sorted in wave form if: arr[0] >= arr[1] <= arr[2] >= arr[3] <=
arr[4] >= …..

Examples:

Input:  arr[] = {10, 5, 6, 3, 2, 20, 100, 80}
Output: arr[] = {10, 5, 6, 2, 20, 3, 100, 80}
Explanation:
here you can see {10, 5, 6, 2, 20, 3, 100, 80} first element is larger than the
second and the same thing is repeated again and again. large element – small
element-large element -small element and so on .it can be small element-larger
element – small element-large element -small element too. all you need to
maintain is the up-down fashion which represents a wave. there can be multiple
answers.

Input: arr[] = {20, 10, 8, 6, 4, 2}
Output: arr[] = {20, 8, 10, 4, 6, 2}
*/

#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

// A utility method to swap two numbers.
void swap(int *x, int *y) {
  int temp = *x;
  *x = *y;
  *y = temp;
}

// This function sorts arr[0..n-1] in wave form, i.e.,
// arr[0] >= arr[1] <= arr[2] >= arr[3] <= arr[4] >= arr[5]..
void sortInWave(int arr[], int n) {
  // Sort the input array
  sort(arr, arr + n);

  // Swap adjacent elements
  for (int i = 0; i < n - 1; i += 2)
    swap(&arr[i], &arr[i + 1]);
}

// Driver program to test above function
int main() {
  int arr[] = {10, 90, 49, 2, 1, 5, 23};
  int n = sizeof(arr) / sizeof(arr[0]);
  sortInWave(arr, n);
  for (int i = 0; i < n; i++)
    cout << arr[i] << " ";
  return 0;
}