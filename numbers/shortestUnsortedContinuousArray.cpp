/*
Given an integer array nums, you need to find one continuous subarray that if
you only sort this subarray in ascending order, then the whole array will be
sorted in ascending order.

Return the shortest such subarray and output its length.

Example 1:

Input: nums = [2,6,4,8,10,9,15]
Output: 5
Explanation: You need to sort [6, 4, 8, 10, 9] in ascending order to make the
whole array sorted in ascending order.

Example 2:

Input: nums = [1,2,3,4]
Output: 0
Example 3:

Input: nums = [1]
Output: 0


Constraints:

1 <= nums.length <= 10^4
-10^5 <= nums[i] <= 10^5


Follow up: Can you solve it in O(n) time complexity?
*/

#include <iostream>
#include <vector>

using namespace std;

int findUnsortedSubarray(const vector<int> &nums) {
  int n = nums.size(), m = 0;
  vector<int> s(n);
  int j = n;
  for (int i = 0; i < n; i++) {
    while (m > 0 && nums[s[m - 1]] > nums[i]) {
      m--;
      j = min(j, m);
    }
    if (j == 0)
      break;
    if (m < j) {
      s[m++] = i;
    }
  }
  if (j == n)
    return 0;
  int k = n;
  m = 0;
  for (int i = n - 1; i >= 0; i--) {
    while (m > 0 && nums[s[m - 1]] < nums[i]) {
      m--;
      k = min(k, m);
    }
    if (k == 0)
      break;
    if (m < k) {
      s[m++] = i;
    }
  }
  return n - j - k;
}

int main() {
  cout << findUnsortedSubarray({2, 6, 4, 8, 10, 9, 15}) << endl;
  cout << findUnsortedSubarray({1, 2, 3, 4}) << endl;
  cout << findUnsortedSubarray({4, 2, 3, 1}) << endl;
  cout << findUnsortedSubarray({1}) << endl;
  return 0;
}