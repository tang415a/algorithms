/*
Given an integer array. Find the kth element of the array.

Example 1:
Input: [9,3,2,7,6], k = 2
Output: 3
Explnation: 3 is the second smallest element of array.

Example 2:
Input: [9,7,5,2,1], k = 1
Output: 1
*/

#include <iostream>
#include <queue>
#include <vector>

using namespace std;

int kthElement(const vector<int> &arr, int k) {
  priority_queue<int, vector<int>, greater<int>> pq;
  for (int i : arr) {
    pq.push(i);
    while (k < pq.size()) {
      pq.pop();
    }
  }
  return pq.top();
}

int kthElement2(vector<int> &arr, int k) {
  int n = arr.size();
  if (k > (n + 1) / 2) {
    k = n - k + 1;
    for (int i = 0; i < k; i++) {
      int p = n / 2;
      while (--p >= 0) {
        int mChild = 2 * p + 1;
        if (mChild + 1 < n && arr[mChild] > arr[mChild + 1]) {
          mChild++;
        }
        if (arr[p] > arr[mChild]) {
          swap(arr[p], arr[mChild]);
        }
      }
      swap(arr[0], arr[--n]);
    }
  } else {
    for (int i = 0; i < k; i++) {
      int p = n / 2;
      while (--p >= 0) {
        int mChild = 2 * p + 1;
        if (mChild + 1 < n && arr[mChild] < arr[mChild + 1]) {
          mChild++;
        }
        if (arr[p] < arr[mChild]) {
          swap(arr[p], arr[mChild]);
        }
      }
      swap(arr[0], arr[--n]);
    }
  }
  return arr[n];
}

int main() {
  vector<int> arr = {9, 3, 2, 7, 6};
  cout << kthElement(arr, 2) << endl;
  cout << kthElement2(arr, 2) << endl;
  cout << kthElement(arr, 3) << endl;
  cout << kthElement2(arr, 3) << endl;
  cout << kthElement(arr, 4) << endl;
  cout << kthElement2(arr, 4) << endl;
  cout << kthElement(arr, 5) << endl;
  cout << kthElement2(arr, 5) << endl;
  arr = {9, 7, 5, 2, 1};
  cout << kthElement(arr, 1) << endl;
  cout << kthElement2(arr, 1) << endl;
  return 0;
}