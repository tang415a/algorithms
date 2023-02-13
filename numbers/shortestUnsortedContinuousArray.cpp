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
      j = --m;
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
      k = --m;
    }
    if (k == 0)
      break;
    if (m < k) {
      s[m++] = i;
    }
  }
  return n - j - k;
}

/*
  nums:   [ _ _ _ _ _ _ _ _ _ _ _ ]
 ----->(greater)|       |end -> ascending
ascending ->    |start  <-----(less)
*/
int findUnsortedSubarray2(const vector<int> &nums) {
  int ans = 0;
  int i = 0;
  int j = nums.size() - 1;
  int curr_min = INT_MAX;
  int curr_max = INT_MIN;
  int start = 0, end = -1;
  while (j >= 0) {
    if (nums[i] >= curr_max)
      curr_max = nums[i]; // from `end` + 1 to n - 1, it is ascending to the max
    else
      end = i;
    if (nums[j] <= curr_min)
      curr_min = nums[j]; // from 0 to `start` - 1, it is ascending from the min
    else
      start = j;
    ++i;
    --j;
  }
  // [start, end] whose values are between [min', max'] needs to be sorted
  return end - start + 1;
}

int main() {
  cout << findUnsortedSubarray2({2, 6, 4, 8, 10, 9, 15}) << endl;
  cout << findUnsortedSubarray2({1, 2, 3, 4}) << endl;
  cout << findUnsortedSubarray2({4, 2, 3, 1}) << endl;
  cout << findUnsortedSubarray2({1}) << endl;
  return 0;
}