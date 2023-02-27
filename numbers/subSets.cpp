/*
Given an integer array nums of unique elements, return all possible
subsets (the power set).

The solution set must not contain duplicate subsets. Return the solution in any
order.

Example 1:

Input: nums = [1,2,3]
Output: [[],[1],[2],[1,2],[3],[1,3],[2,3],[1,2,3]]

Example 2:

Input: nums = [0]
Output: [[],[0]]


Constraints:

1 <= nums.length <= 10
-10 <= nums[i] <= 10
All the numbers of nums are unique.
*/
#include <iostream>
#include <vector>


using namespace std;

vector<vector<int>> subsets(const vector<int> &nums) {
  int n = nums.size(), j = 1 << n;
  vector<vector<int>> res(j);
  for (int i = 0; i < j; i++) {
    for (int k = 0; k < n; k++) {
      if (i & (1 << k))
        res[i].emplace_back(nums[k]);
    }
  }
  return res;
}

int main() {
  auto r = subsets({1, 2, 3});
  for (auto &l : r) {
    cout << "[ ";
    for (int i : l) {
      cout << i << " ";
    }
    cout << "]" << endl;
  }
  r = subsets({0});
  for (auto &l : r) {
    cout << "[ ";
    for (int i : l) {
      cout << i << " ";
    }
    cout << "]" << endl;
  }
  return 0;
}
