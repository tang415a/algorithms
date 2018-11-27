/*
Given an array which consists of non-negative integers and an integer m, you can split the array into m non-empty continuous subarrays. Write an algorithm to minimize the largest sum among these m subarrays.

Note:
If n is the length of array, assume the following constraints are satisfied:

1 ≤ n ≤ 1000
1 ≤ m ≤ min(50, n)
Examples:

Input:
nums = [7,2,5,10,8]
m = 2

Output:
18

Explanation:
There are four ways to split nums into two subarrays.
The best way is to split it into [7,2,5] and [10,8],
where the largest sum among the two subarrays is only 18.
*/

#include <stdio.h>
#include <vector>
using namespace std;

bool isPossible(const vector<int>& arr, int m, int minSum) {
  int s = 0, cnt = 1;
  for (auto& d: arr) {
    s += d;
    if (s > minSum) {
      cnt++;
      if (cnt > m) return false;
      s = d;
    }
  }
  return true;
}

int minSumSubArr(const vector<int>& arr, int m) {
  int min = 0, max = 0;
  for (auto& d: arr) {
    max += d;
    if (min > d)
      min = d;
  }

  while (min < max) {
    int mid = min + (max - min) / 2;
    if (isPossible(arr, m, mid))
      max = mid;
    else
      min = mid + 1;
  }
  return max;
}

int main() {
  const vector<int> arr = {1,2,3,4,5,6,7,8};
  printf("%d ", minSumSubArr(arr, 4));
  return 0;
}