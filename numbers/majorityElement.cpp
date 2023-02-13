/*
Given an array nums of size n, return the majority element.

The majority element is the element that appears more than ⌊n / 2⌋ times. You
may assume that the majority element always exists in the array.



Example 1:

Input: nums = [3,2,3]
Output: 3
Example 2:

Input: nums = [2,2,1,1,1,2,2]
Output: 2


Constraints:

n == nums.length
1 <= n <= 5 * 10^4
-10^9 <= nums[i] <= 10^9


Follow-up: Could you solve the problem in linear time and in O(1) space?
*/

#include <iostream>
#include <vector>

using namespace std;
int majorityElement(const vector<int> &nums) {
  int ans = nums[0], life = 1;
  for (int i = 1, n = nums.size(); i < n; i++) {
    if (nums[i] == ans) {
      if (++life > n / 2)
        break;
    } else if (life == 1) {
      ans = nums[i];
    } else {
      life--;
    }
  }
  return ans;
}

int majorityElement2(const vector<int> &nums) {
  int ans = 0, life = 0;
  for (auto i : nums) {
    if (life == 0) {
      ans = i;
    } else if (ans == i) {
      life++;
    } else {
      life--;
    }
  }
  return ans;
}

int main() {
  cout << majorityElement({3, 2, 3}) << endl;
  cout << majorityElement({2, 2, 1, 1, 1, 2, 2}) << endl;
  cout << majorityElement2({3, 2, 3}) << endl;
  cout << majorityElement2({2, 2, 1, 1, 1, 2, 2}) << endl;
  return 0;
}