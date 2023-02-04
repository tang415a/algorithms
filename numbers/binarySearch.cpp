// Write a binary search algorithm.

#include <iostream>
using namespace std;

int search(int target, int arr[], int siz) {
  if (siz <= 0)
    return -1;

  int left = 0, right = siz - 1;
  while (left <= right) {
    int mid = left + (right - left) / 2;
    if (arr[mid] == target)
      return mid;
    if (arr[mid] > target)
      right = mid - 1;
    else
      left = mid + 1;
  }
  return -1;
}

int upper_bound(int target, int *arr, int size) {
  if (size <= 0)
    return -1;
  int low = 0, high = size - 1;
  while (low <= high) {
    int mid = low + (high - low) / 2;
    if (arr[mid] < target) {
      low = mid + 1;
    } else if (arr[mid] > target) {
      high = mid - 1;
    } else {
      return mid;
    }
  }
  return low;
}

int lower_bound(int target, int *arr, int size) {
  if (size <= 0)
    return -1;
  int low = 0, high = size - 1;
  while (low <= high) {
    int mid = low + (high - low) / 2;
    if (arr[mid] < target) {
      low = mid + 1;
    } else if (arr[mid] > target) {
      high = mid - 1;
    } else {
      return mid;
    }
  }
  return high;
}

int main() {
  int arr[] = {0, 1, 2, 5, 7};
  cout << search(1, arr, sizeof(arr) / sizeof(arr[0])) << endl;
  cout << upper_bound(3, arr, sizeof(arr) / sizeof(arr[0])) << endl;
  cout << upper_bound(1, arr, sizeof(arr) / sizeof(arr[0])) << endl;
  cout << upper_bound(9, arr, sizeof(arr) / sizeof(arr[0])) << endl;
  cout << upper_bound(-1, arr, sizeof(arr) / sizeof(arr[0])) << endl;
  cout << upper_bound(0, arr, sizeof(arr) / sizeof(arr[0])) << endl;

  cout << lower_bound(3, arr, sizeof(arr) / sizeof(arr[0])) << endl;
  cout << lower_bound(1, arr, sizeof(arr) / sizeof(arr[0])) << endl;
  cout << lower_bound(9, arr, sizeof(arr) / sizeof(arr[0])) << endl;
  cout << lower_bound(-1, arr, sizeof(arr) / sizeof(arr[0])) << endl;
  cout << lower_bound(0, arr, sizeof(arr) / sizeof(arr[0])) << endl;
  return 0;
}