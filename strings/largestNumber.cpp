/*
Given a list of non-negative integers nums, arrange them such that they form the
largest number and return it.

Since the result may be very large, so you need to return a string instead of an
integer.

Example 1:

Input: nums = [10,2]
Output: "210"
Example 2:

Input: nums = [3,30,34,5,9]
Output: "9534330"

Constraints:

1 <= nums.length <= 100
0 <= nums[i] <= 10^9
*/
#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

bool doCompare(const string &l, int p0, const string &r, int p1) {
  int s0 = p0, s1 = p1;
  while (p0 < l.length() && p1 < r.length()) {
    if (l[p0] < r[p1]) {
      return false;
    }
    if (l[p0] > r[p1]) {
      return true;
    }
    p0++;
    p1++;
  }
  if (p0 < l.length()) {
    return doCompare(l, p0, r, s1);
  }
  if (p1 < r.length()) {
    return doCompare(l, s0, r, p1);
  }
  return false;
}

bool compare(const string &l, const string &r) { return doCompare(l, 0, r, 0); }

string largestNumber(const vector<int> &nums) {
  int n = nums.size();
  vector<string> v(n);
  for (int i = 0; i < n; i++) {
    int j = nums[i];
    if (j == 0) {
      v[i] = "0";
    } else {
      while (j > 0) {
        int r = j / 10;
        v[i].push_back('0' + j - 10 * r);
        j = r;
      }
      reverse(v[i].begin(), v[i].end());
    }
  }
  sort(v.begin(), v.end(), compare);

  if (v[0] == "0")
    n = 1;
  string ans;
  for (int i = 0; i < n; i++) {
    ans += v[i];
  }
  return ans;
}

bool comparator(string a, string b) {
  if (a + b > b + a) { // Ex:- ["3", "30"] --> 330 OR 303
    return true;
  }
  return false;
}

string largestNumber2(const vector<int> &nums) {
  int n = nums.size();
  vector<string> vStr;
  string ans = "";

  for (auto x : nums) {
    vStr.push_back(to_string(x));
  }

  sort(vStr.begin(), vStr.end(), comparator);

  for (auto x : vStr) {
    ans += x;
  }

  int i = 0;
  while (ans[i] == '0' && i < ans.size() - 1) {
    i++;
  }

  return ans.substr(i);
}

int main() {
  cout << largestNumber({10, 2}) << endl;
  cout << largestNumber({3, 30, 34, 5, 9}) << endl;
  cout << largestNumber({432, 43243}) << endl;
  cout << largestNumber({43243, 432}) << endl;
  return 0;
}