/*
Given an array of integers nums, return the number of good pairs.

A pair (i, j) is called good if nums[i] == nums[j] and i < j.

Example 1:

Input: nums = [1,2,3,1,1,3]
Output: 4
Explanation: There are 4 good pairs (0,3), (0,4), (3,4), (2,5) 0-indexed.

Example 2:

Input: nums = [1,1,1,1]
Output: 6
Explanation: Each pair in the array are good.

Example 3:

Input: nums = [1,2,3]
Output: 0

Constraints:

1 <= nums.length <= 100
1 <= nums[i] <= 100
*/

#include <iostream>
#include <vector>

using namespace std;

int numIdenticalPairs(const vector<int> &nums) {
  int c[100];
  memset(c, 0, sizeof(int) * 100);
  int ans = 0;
  for (int i = 0, n = nums.size(); i < n; i++) {
    ans += c[nums[i] - 1];
    c[nums[i] - 1]++;
  }
  return ans;
}

int main() {
  cout << numIdenticalPairs({1, 2, 3, 1, 1, 3}) << endl;
  cout << numIdenticalPairs({1, 1, 1, 1}) << endl;
  cout << numIdenticalPairs({1, 2, 3}) << endl;
  return 0;
}