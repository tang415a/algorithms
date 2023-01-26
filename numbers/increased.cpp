// Given an integer array, pick the most integers which constitute an increased
// sequence Note that the order of integers appearing in the sequence may not be
// switched. e.g. given an array: 1,5,2,8,3,7,4,6,0 then it will output
// 1,2,3,4,6
#include <iostream>
using namespace std;

int maxIncrSubSeq(int *p, int size) {
  int *cache = new int[size];
  cache[0] = p[0];
  int n = 1;
  for (int i = 1; i < size; ++i) {
    if (p[i] > cache[n - 1]) {
      cache[n] = p[i];
      ++n;
    }
    for (int j = n; j >= 0; --j) {
      if (p[i] < cache[j] && (j == 0 || p[i] > cache[j - 1])) {
        cache[j] = p[i];
        break;
      }
    }
  }
  delete[] cache;
  return n;
}

// if you also want the sequence array
int maxIncrSubSeq(int *p, int *g, int size) {
  int *cache = new int[size];
  cache[0] = p[0];
  int n = 1;
  for (int i = 1; i < size; ++i) {
    if (p[i] > cache[n - 1]) {
      cache[n] = p[i];
      ++n;
      for (int j = 0; j < n; ++j)
        g[j] = cache[j];
    }
    for (int j = n; j >= 0; --j) {
      if (p[i] < cache[j] && (j == 0 || p[i] > cache[j - 1])) {
        cache[j] = p[i];
        break;
      }
    }
  }
  delete[] cache;
  return n;
}

int main() {
  int arr[] = {1, 5, 2, 8, 3, 7, 4, 6, 0};
  int size = sizeof(arr) / sizeof(arr[0]);
  cout << maxIncrSubSeq(arr, size) << endl;
  int *gathering = new int[size];
  int n = maxIncrSubSeq(arr, gathering, size);
  for (int i = 0; i < n; ++i) {
    cout << gathering[i] << " ";
  }
  delete[] gathering;
  return 0;
}