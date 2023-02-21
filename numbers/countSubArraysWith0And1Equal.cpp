/*
You are given a binary array nums containing only the integers 0 and 1. Return
the number of subarrays in nums that have equal 1's than 0's. Since the answer
may be very large, return it modulo 10^9 + 7.

A subarray is a contiguous sequence of elements within an array.

Example 1:

Input: nums = [1,0,0,1]
Output: 3
Explanation:
There are 3 subarrays with equal numbers of zeros and ones: [1,0], [1,0,0,1] and
[0,1].

Example 2:

Input: nums = [0]
Output: 0
Explanation:
No subarrays have equal ones and zeros.

Example 3:

Input: nums = [1,0,1,0,0,1]
Output: 7
Explanation:
[1,0],[0,1],[1,0],[0,1],[1,0,1,0],[1,0,0,1],[1,0,1,0,0,1] are the subarrays with
equal ones and zeros.
*/
#include <iostream>
#include <vector>

using namespace std;
int subarraysWithOnesAndZerosEqual(const vector<int> &nums) {
  int n = nums.size();
  vector<int> s(n);
  s[0] = nums[0] == 0 ? -1 : 1;
  for (int i = 1; i < n; i++) {
    s[i] = nums[i] == 1 ? (s[i - 1] + 1) : (s[i - 1] - 1);
  }
  vector<int> c(2 * n + 1, 0);
  for (int i : s) {
    c[i + n]++;
  }
  int ans = c[n];
  constexpr int kMod = 1'000'000'007;
  for (int i : c) {
    ans += i * (i - 1) / 2;
    ans %= kMod;
  }
  return ans;
}

int main() {
  cout << subarraysWithOnesAndZerosEqual({1, 0, 0, 1}) << endl;
  cout << subarraysWithOnesAndZerosEqual({0}) << endl;
  cout << subarraysWithOnesAndZerosEqual({1, 0, 1, 0, 0, 1}) << endl;
  return 0;
}
