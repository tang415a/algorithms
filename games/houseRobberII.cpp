/*
You are a professional robber planning to rob houses along a street. Each house
has a certain amount of money stashed. All houses at this place are arranged in
a circle. That means the first house is the neighbor of the last one. Meanwhile,
adjacent houses have a security system connected, and it will automatically
contact the police if two adjacent houses were broken into on the same night.

Given an integer array nums representing the amount of money of each house,
return the maximum amount of money you can rob tonight without alerting the
police.


Example 1:

Input: nums = [2,3,2]
Output: 3
Explanation: You cannot rob house 1 (money = 2) and then rob house 3 (money =
2), because they are adjacent houses.

Example 2:

Input: nums = [1,2,3,1]
Output: 4
Explanation: Rob house 1 (money = 1) and then rob house 3 (money = 3).
Total amount you can rob = 1 + 3 = 4.

Example 3:

Input: nums = [1,2,3]
Output: 3

Constraints:

1 <= nums.length <= 100
0 <= nums[i] <= 1000
*/

#include <iostream>
#include <vector>

using namespace std;

int rob(const vector<int> &nums) {
  int c[2] = {nums[0], 0};
  bool includeFirst[2] = {true, false};
  const int n = nums.size();
  int a = 1;
  for (int i = 1; i < n - 1; i++) {
    int t = nums[i] + c[a];
    if (c[1 - a] < t) {
      c[a] = t;
    } else if (c[1 - a] == t) {
      c[a] = t;
      if (includeFirst[a] && !includeFirst[1 - a])
        includeFirst[a] = false;
    } else {
      c[a] = c[1 - a];
      includeFirst[a] = includeFirst[1 - a];
    }
    a = 1 - a;
  }
  if (n < 3 || !includeFirst[a]) {
    return max(nums[n - 1] + c[a], c[1 - a]);
  }
  int tmp = c[1 - a];
  c[0] = nums[1];
  c[1] = 0;
  a = 1;
  for (int i = 2; i < n; i++) {
    c[a] = max(nums[i] + c[a], c[1 - a]);
    a = 1 - a;
  }
  return max(tmp, c[1 - a]);
}

int rob2(const vector<int> &nums) {
  const int n = nums.size();
  if (n == 1)
    return nums[0];
  int c[2] = {nums[0], 0};
  int a = 1;
  for (int i = 1; i < n - 1; i++) {
    c[a] = max(nums[i] + c[a], c[1 - a]);
    a = 1 - a;
  }
  int tmp = c[1 - a];
  c[0] = nums[1];
  c[1] = 0;
  a = 1;
  for (int i = 2; i < n; i++) {
    c[a] = max(nums[i] + c[a], c[1 - a]);
    a = 1 - a;
  }
  return max(tmp, c[1 - a]);
}

int main() {
  cout << rob({2, 3, 2}) << endl;
  cout << rob({1, 2, 3, 1}) << endl;
  cout << rob({1, 2, 3}) << endl;
  cout << rob({100, 3, 2, 101}) << endl;
  cout << rob({100}) << endl;
  cout << rob({100, 3}) << endl;
  cout << rob({2, 4, 2, 1}) << endl;
  cout << "----------------------------" << endl;
  cout << rob2({2, 3, 2}) << endl;
  cout << rob2({1, 2, 3, 1}) << endl;
  cout << rob2({1, 2, 3}) << endl;
  cout << rob2({100, 3, 2, 101}) << endl;
  cout << rob2({100}) << endl;
  cout << rob2({100, 3}) << endl;
  cout << rob2({2, 4, 2, 1}) << endl;
  cout << rob2({0}) << endl;
  return 0;
}
