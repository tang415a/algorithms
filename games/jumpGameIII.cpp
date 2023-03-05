/*
Given an array of non-negative integers arr, you are initially positioned at
start index of the array. When you are at index i, you can jump to i + arr[i] or
i - arr[i], check if you can reach to any index with value 0.

Notice that you can not jump outside of the array at any time.

Example 1:

Input: arr = [4,2,3,0,3,1,2], start = 5
Output: true
Explanation:
All possible ways to reach at index 3 with value 0 are:
index 5 -> index 4 -> index 1 -> index 3
index 5 -> index 6 -> index 4 -> index 1 -> index 3

Example 2:

Input: arr = [4,2,3,0,3,1,2], start = 0
Output: true
Explanation:
One possible way to reach at index 3 with value 0 is:
index 0 -> index 4 -> index 1 -> index 3

Example 3:

Input: arr = [3,0,2,1,2], start = 2
Output: false
Explanation: There is no way to reach at index 1 with value 0.


Constraints:

1 <= arr.length <= 5 * 10^4
0 <= arr[i] < arr.length
0 <= start < arr.length
*/
#include <iostream>
#include <vector>

using namespace std;

bool canReach(const vector<int> &arr, int start) {
  int n = arr.size();
  vector<bool> c(n, false);
  vector<int> opts = {start};
  int i = 0;
  while (i < opts.size()) {
    int j = opts[i] + arr[opts[i]];
    if (j < n) {
      if (arr[j] == 0)
        return true;
      if (!c[j]) {
        opts.emplace_back(j);
        c[j] = true;
      }
    }
    j = opts[i] - arr[opts[i]];
    if (j >= 0) {
      if (arr[j] == 0)
        return true;
      if (!c[j]) {
        opts.emplace_back(j);
        c[j] = true;
      }
    }
    i++;
  }
  return false;
}

// a better approach : use recursion
int solve(int ind, int n, vector<int> &a, vector<int> &dp) {
  if (ind < 0 || ind >= n)
    return 0;
  if (dp[ind] != -1)
    return dp[ind];

  if (a[ind] == 0)
    return dp[ind] = 1;
  else
    dp[ind] = 0;

  int left = solve(ind - a[ind], n, a, dp);
  int right = solve(ind + a[ind], n, a, dp);

  return dp[ind] = left | right;
}

bool canReach2(vector<int> &arr, int start) {
  int n = arr.size();

  vector<int> dp(n, -1);
  int ans = solve(start, n, arr, dp);
  return ans;
}

int main() {
  cout << canReach({4, 2, 3, 0, 3, 1, 2}, 5) << endl;
  cout << canReach({4, 2, 3, 0, 3, 1, 2}, 0) << endl;
  cout << canReach({3, 0, 2, 1, 2}, 2) << endl;
  return 0;
}