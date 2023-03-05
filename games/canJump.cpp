/*
You are given an integer array nums. You are initially positioned at the array's
first index, and each element in the array represents your maximum jump length
at that position.

Return true if you can reach the last index, or false otherwise.

Example 1:

Input: nums = [2,3,1,1,4]
Output: true
Explanation: Jump 1 step from index 0 to 1, then 3 steps to the last index.

Example 2:

Input: nums = [3,2,1,0,4]
Output: false
Explanation: You will always arrive at index 3 no matter what. Its maximum jump
length is 0, which makes it impossible to reach the last index.

Constraints:

1 <= nums.length <= 10^4
0 <= nums[i] <= 10^5
*/

#include <iostream>
#include <vector>

using namespace std;

bool canJump(const vector<int> &nums) {
  for (int i = 1, m = nums[0], n = nums.size(); i < n; i++) {
    if (m < i)
      return false;
    m = max(m, nums[i] + i);
  }
  return true;
}

int main() {
  cout << canJump({2, 3, 1, 1, 4}) << endl; // 1
  cout << canJump({3, 2, 1, 0, 4}) << endl; // 0
  cout << canJump({4, 0, 0, 0, 0}) << endl; // 1
  cout << canJump({3, 0, 0, 0, 0}) << endl; // 0
  cout << canJump({0, 4}) << endl;          // 0
  cout << canJump({0}) << endl;             // 1
  cout << canJump({1, 0, 0}) << endl;       // 0
  cout << canJump({2, 0, 1, 0, 4}) << endl; // 0
  cout << canJump({3, 0, 1, 0, 4}) << endl; // 0
  cout << canJump({4, 0, 1, 0, 4}) << endl; // 1
  return 0;
}
