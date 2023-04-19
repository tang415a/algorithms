/*
Given an array nums of n integers, return an array of all the unique quadruplets
[nums[a], nums[b], nums[c], nums[d]] such that:

0 <= a, b, c, d < n
a, b, c, and d are distinct.
nums[a] + nums[b] + nums[c] + nums[d] == target
You may return the answer in any order.

Example 1:

Input: nums = [1,0,-1,0,-2,2], target = 0
Output: [[-2,-1,1,2],[-2,0,0,2],[-1,0,0,1]]

Example 2:

Input: nums = [2,2,2,2,2], target = 8
Output: [[2,2,2,2]]


Constraints:

1 <= nums.length <= 200
-10^9 <= nums[i] <= 10^9
-10^9 <= target <= 10^9
*/

#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

vector<vector<int>> fourSum(const vector<int> &nums, int target) {
  vector<vector<int>> total;
  int n = nums.size();
  if (n < 4)
    return total;
  vector<int> cpy = nums;
  sort(cpy.begin(), cpy.end());
  for (int i = 0; i < n - 3; i++) {
    // if i is greater than i and elem i is equal to elem i - 1 (elem i - 1 has
    // been processed in the last iteration), skip it
    if (i > 0 && cpy[i] == cpy[i - 1])
      continue;
    // the minimum sum of quadruplet from i is larger than target
    if (cpy[i] + cpy[i + 1] + cpy[i + 2] + cpy[i + 3] > target)
      break;
    // the maximum sum of quadruplet from i is smaller than target
    if (cpy[i] + cpy[n - 3] + cpy[n - 2] + cpy[n - 1] < target)
      continue;
    for (int j = i + 1; j < n - 2; j++) {
      // if j is greater than i + 1 and elem j is equal to elem j - 1 (elem j -
      // 1 has been processed in the last iteration), skip it
      if (j > i + 1 && cpy[j] == cpy[j - 1])
        continue;
      // the minimum of sum of quadruplet from (i, j) is greater than target
      if (cpy[i] + cpy[j] + cpy[j + 1] + cpy[j + 2] > target)
        break;
      // the maximum of sum of quadruplet from (i, j) is smaller than target
      if (cpy[i] + cpy[j] + cpy[n - 2] + cpy[n - 1] < target)
        continue;
      // find the last two elements
      int left = j + 1, right = n - 1;
      while (left < right) {
        int sum = cpy[left] + cpy[right] + cpy[i] + cpy[j];
        if (sum < target)
          left++;
        else if (sum > target)
          right--;
        else {
          total.push_back(vector<int>{cpy[i], cpy[j], cpy[left], cpy[right]});
          // move left up to the next unequal element
          do {
            left++;
          } while (cpy[left] == cpy[left - 1] && left < right);
          // move right down to the next unequal element
          do {
            right--;
          } while (cpy[right] == cpy[right + 1] && left < right);
        }
      }
    }
  }
  return total;
}

#include <set>

struct Point {
  int a[4];
  int sum(const int *p) const { return p[a[0]] + p[a[1]] + p[a[2]] + p[a[3]]; }
  void emplace(vector<vector<int>> &ans, const int *p, set<vector<int>> &c) {
    vector<int> v = {p[a[0]], p[a[1]], p[a[2]], p[a[3]]};
    if (c.find(v) == c.end()) {
      c.insert(v);
      ans.emplace_back(v);
    }
  }
  bool moveUp(vector<Point> &pts, int i) {
    if (a[i] < a[i + 1] - 1) {
      Point pt = *this;
      pt.a[i]++;
      pts.emplace_back(pt);
      return true;
    }
    return false;
  }
  bool moveDown(vector<Point> &pts, int i) {
    if (a[i - 1] < a[i] - 1) {
      Point pt = *this;
      pt.a[i]--;
      pts.emplace_back(pt);
      return true;
    }
    return false;
  }
};

// NOTE: this algorithm is incorrect; some quadruplets are possibly MISSED by
// this algorithm
vector<vector<int>> fourSum2(const vector<int> &nums, int target) {
  vector<vector<int>> ans;
  const int n = nums.size();
  if (n < 4)
    return ans;
  auto cpy = nums;
  sort(cpy.begin(), cpy.end());
  set<vector<int>> c;
  vector<Point> pts = {Point{{0, 1, n - 2, n - 1}}};
  for (int i = 0; i < pts.size(); i++) {
    int sum = pts[i].sum(cpy.data());
    if (sum == target) {
      pts[i].emplace(ans, cpy.data(), c);
      if (pts[i].moveUp(pts, 0))
        continue;
      if (pts[i].moveUp(pts, 1))
        continue;
      if (pts[i].moveDown(pts, 2))
        continue;
      if (pts[i].moveDown(pts, 3))
        continue;
    } else if (sum < target) {
      pts[i].moveUp(pts, 0);
      pts[i].moveUp(pts, 1);
    } else {
      pts[i].moveDown(pts, 2);
      pts[i].moveDown(pts, 3);
    }
  }
  return ans;
}

int main() {
  auto vec = fourSum({1, 0, -1, 0, -2, 2}, 0);
  for (auto &v : vec) {
    const char *comma = "";
    for (int i : v) {
      cout << comma << i;
      comma = ", ";
    }
    cout << endl;
  }
  cout << endl;
  vec = fourSum({1, 1, 2, 2, 2, 2, 2}, 8);
  for (auto &v : vec) {
    const char *comma = "";
    for (int i : v) {
      cout << comma << i;
      comma = ", ";
    }
    cout << endl;
  }
  cout << endl;
  vec = fourSum({-3, -2, -1, 0, 0, 1, 2, 3}, 0);
  for (auto &v : vec) {
    const char *comma = "";
    for (int i : v) {
      cout << comma << i;
      comma = ", ";
    }
    cout << endl;
  }
  return 0;
}
