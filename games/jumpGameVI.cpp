/*
You are given a 0-indexed integer array nums and an integer k.

You are initially standing at index 0. In one move, you can jump at most k steps
forward without going outside the boundaries of the array. That is, you can jump
from index i to any index in the range [i + 1, min(n - 1, i + k)] inclusive.

You want to reach the last index of the array (index n - 1). Your score is the
sum of all nums[j] for each index j you visited in the array.

Return the maximum score you can get.

Example 1:

Input: nums = [1,-1,-2,4,-7,3], k = 2
Output: 7
Explanation: You can choose your jumps forming the subsequence [1,-1,4,3]
(underlined above). The sum is 7.

Example 2:

Input: nums = [10,-5,-2,4,0,3], k = 3
Output: 17
Explanation: You can choose your jumps forming the subsequence [10,4,3]
(underlined above). The sum is 17.

Example 3:

Input: nums = [1,-5,-20,4,-1,3,-6,-3], k = 2
Output: 0

Constraints:

1 <= nums.length, k <= 10^5
-10^4 <= nums[i] <= 10^4
*/
#include <iostream>
#include <vector>

using namespace std;

int maxResult__(const vector<int> &nums, int k) {
  const int n = nums.size();
  vector<int> c(n);
  c[0] = nums[0];
  for (int i = 1; i < n; i++) {
    int t = -10001;
    for (int j = max(0, i - k); j < i; j++) {
      t = max(t, c[j]);
    }
    c[i] = t + nums[i];
  }
  return c[n - 1];
}

int maxResult(const vector<int> &nums, int k) {
  const int n = nums.size();
  if (n == 1)
    return nums[0];
  vector<int> s(n), t(n);
  s[0] = nums[0];
  t[0] = 0;
  int l = 0;
  for (int i = 1, h = 1; i < n - 1; i++, h++) {
    if (t[l] < i - k) {
      l++;
    }
    int y = s[l] + nums[i];
    for (; h > l && s[h - 1] < y; h--) {
    }
    s[h] = y;
    t[h] = i;
  }
  return (t[l] < n - 1 - k ? s[l + 1] : s[l]) + nums[n - 1];
}

int main() {
  cout << maxResult__({1, -1, -2, 4, -7, 3}, 2) << endl;
  cout << maxResult__({10, -5, -2, 4, 0, 3}, 3) << endl;
  cout << maxResult__({1, -5, -20, 4, -1, 3, -6, -3}, 2) << endl;
  cout << maxResult__({100, -1, -100, -1, 100}, 2) << endl;
  cout << maxResult({1, -1, -2, 4, -7, 3}, 2) << endl;
  cout << maxResult({10, -5, -2, 4, 0, 3}, 3) << endl;
  cout << maxResult({1, -5, -20, 4, -1, 3, -6, -3}, 2) << endl;
  cout << maxResult({1, 5, 20, 4, 1, 3, 6, 3}, 2) << endl;
  cout << maxResult({100, -1, -100, -1, 100}, 2) << endl;
  return 0;
}