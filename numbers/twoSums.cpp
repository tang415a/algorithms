/*
Given an integer array and a number N. Find if there are two integers inside the
array whose sum equals N.
*/

#include <iostream>
using namespace std;

void do_qsort(int *arr, int low, int high) {
  if (low >= high)
    return;
  int hi = high + 1, lo = low;
  int item = arr[lo];
  while (true) {
    while (++lo <= high && arr[lo] <= item)
      ;
    while (--hi > low && arr[hi] >= item)
      ;
    if (lo < hi) {
      int tmp = arr[lo];
      arr[lo] = arr[hi];
      arr[hi] = tmp;
    } else
      break;
  }
  if (low != hi) {
    arr[low] = arr[hi];
    arr[hi] = item;
  }
  do_qsort(arr, low, hi - 1);
  do_qsort(arr, hi + 1, high);
}

bool possibleSum(int *arr, int siz, int N) {
  if (siz < 2)
    return false;
  do_qsort(arr, 0, siz - 1);
  if (N > arr[siz - 2] + arr[siz - 1] || N < arr[0] + arr[1])
    return false;
  int lo = 0, hi = siz - 1;
  while (lo < hi) {
    int sum = arr[lo] + arr[hi];
    if (sum == N)
      return true;
    sum < N ? lo++ : hi--;
  }
  return false;
}

#include <unordered_map>
#include <vector>

vector<int> twoSum(vector<int> &nums, int target) {
  vector<int> ans;
  unordered_map<int, int> mymap;

  for (int i = 0; i < nums.size(); i++) {
    int v = target - nums[i];
    if (mymap.count(v) > 0) {
      ans.emplace_back(mymap[v]);
      ans.emplace_back(i);
      break;
    }
    mymap[nums[i]] = i;
  }

  return ans;
}

int main() {
  int arr[] = {4, 5, 8, 2};
  int N = 11;
  if (possibleSum(arr, sizeof(arr) / sizeof(arr[0]), N))
    cout << "it is possible" << endl;
  else
    cout << "it is not possible" << endl;

  vector<int> v = {4, 5, 8, 2};
  int target = 10;
  auto r = twoSum(v, target);
  if (r.empty()) {
    cout << "it is impossible" << endl;
  } else {
    cout << v[r[0]] << " + " << v[r[1]] << " = " << target << endl;
  }
  return 0;
}