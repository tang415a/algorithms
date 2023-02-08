/*
The min-product of an array is equal to the minimum value in the array
multiplied by the array's sum.

For example, the array [3,2,5] (minimum value is 2) has a min-product of 2 *
(3+2+5) = 2 * 10 = 20. Given an array of integers nums, return the maximum
min-product of any non-empty subarray of nums. Since the answer may be large,
return it modulo 10^9 + 7.

Note that the min-product should be maximized before performing the modulo
operation. Testcases are generated such that the maximum min-product without
modulo will fit in a 64-bit signed integer.

A subarray is a contiguous part of an array.



Example 1:

Input: nums = [1,2,3,2]
Output: 14
Explanation: The maximum min-product is achieved with the subarray [2,3,2]
(minimum value is 2). 2 * (2+3+2) = 2 * 7 = 14.

Example 2:

Input: nums = [2,3,3,1,2]
Output: 18
Explanation: The maximum min-product is achieved with the subarray [3,3]
(minimum value is 3). 3 * (3+3) = 3 * 6 = 18.

Example 3:

Input: nums = [3,1,5,6,4,2]
Output: 60
Explanation: The maximum min-product is achieved with the subarray [5,6,4]
(minimum value is 4). 4 * (5+6+4) = 4 * 15 = 60.


Constraints:

1 <= nums.length <= 10^5
1 <= nums[i] <= 10^7
*/

#include <iostream>
#include <vector>

using namespace std;

// some immature thoughts..
int maxSumMinProduct__(const vector<int> &nums) {
  long long int ret = nums[0], sum = nums[0];
  int l = -1, h = 1, n = nums.size();
  while (h < n && nums[h] >= nums[0]) {
    sum += nums[h++];
  }
  ret = sum * nums[0];
  for (int i = 1; i < n; ++i) {
    if (nums[i] == nums[i - 1])
      continue;
    if (nums[i] > nums[i - 1]) {
      l = i - 1;
      sum = nums[i];
      for (int k = i + 1; k < h; k++) {
        if (nums[k] < nums[i]) {
          h = k;
          break;
        }
        sum += nums[k];
      }
    } else {
      while (l >= 0 && nums[l] >= nums[i]) {
        sum += nums[l--];
      }
      while (h < n && nums[h] >= nums[i]) {
        sum += nums[h++];
      }
    }
    long long int tmp = sum * nums[i];
    if (tmp > ret)
      ret = tmp;
  }

  return ret % 1000000007;
}

// https://leetcode.com/problems/maximum-subarray-min-product/solutions/1198896/O(n)-Monostack-with-picture/
// When we need to pop back from the stack, it means for the back element j:
// * Elements from j to i - 1 are all greater than j
// * Elements before j to the stack front are all less than j
// which makes j is the min of the sub array
// After the insertion, the elements begin to rise from the insertion position
// whose value is greater than j
// To make it simple, we will store indexes of elements, as we can get their
// values from the original array. Another trick is sum[i, j) = sum[0, j) -
// sum[0, i).
int maxSumMinProduct(const vector<int> &n) {
  long long int res = 0;
  vector<long long int> dp(n.size() + 1), st;
  for (int i = 0; i < n.size(); ++i)
    dp[i + 1] = dp[i] + n[i];
  for (int i = 0; i <= n.size(); ++i) {
    while (!st.empty() && (i == n.size() || n[st.back()] > n[i])) {
      int j = st.back();
      st.pop_back();
      res = max(res, n[j] * (dp[i] - dp[st.empty() ? 0 : st.back() + 1]));
    }
    st.push_back(i);
  }
  return res % 1000000007;
}

int main() {
  cout << maxSumMinProduct({1, 2, 3, 2}) << endl;
  cout << maxSumMinProduct({2, 3, 3, 1, 2}) << endl;
  cout << maxSumMinProduct({3, 1, 5, 6, 4, 2}) << endl;
  return 0;
}