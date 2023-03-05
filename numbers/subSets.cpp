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

void solve(vector<vector<int>> &ans, int i, const vector<int> &ip, vector<int> op) {
  if (ip.size() == i) {
    ans.push_back(op);
    return;
  }
  // do not select ip[i]
  solve(ans, i + 1, ip, op);
  op.push_back(ip[i]);
  // select ip[i]
  solve(ans, i + 1, ip, op);
  return;
}

vector<vector<int>> subsets2(const vector<int> &ip) {
  vector<vector<int>> ans;
  vector<int> op;
  solve(ans, 0, ip, op);
  return ans;
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
  r = subsets2({1, 2, 3});
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
