/*
Given an array of integers arr and an integer d. In one step you can jump from
index i to index:

i + x where: i + x < arr.length and 0 < x <= d.
i - x where: i - x >= 0 and 0 < x <= d.

In addition, you can only jump from index i to index j if arr[i] > arr[j] and
arr[i] > arr[k] for all indices k between i and j (More formally min(i, j) < k <
max(i, j)).

You can choose any index of the array and start jumping. Return the maximum
number of indices you can visit.

Notice that you can not jump outside of the array at any time.

Example 1:

Input: arr = [6,4,14,6,8,13,9,7,10,6,12], d = 2
Output: 4
Explanation: You can start at index 10. You can jump 10 --> 8 --> 6 --> 7 as
shown. Note that if you start at index 6 you can only jump to index 7. You
cannot jump to index 5 because 13 > 9. You cannot jump to index 4 because index
5 is between index 4 and 6 and 13 > 9. Similarly You cannot jump from index 3 to
index 2 or index 1.

Example 2:

Input: arr = [3,3,3,3,3], d = 3
Output: 1
Explanation: You can start at any index. You always cannot jump to any index.

Example 3:

Input: arr = [7,6,5,4,3,2,1], d = 1
Output: 7
Explanation: Start at index 0. You can visit all the indicies.

Constraints:

1 <= arr.length <= 1000
1 <= arr[i] <= 10^5
1 <= d <= arr.length
*/
#include <iostream>
#include <vector>

using namespace std;

int solve(const vector<int> &arr, int n, int d, int l, int r, int p,
          vector<int> &c) {
  if (c[p] > 0)
    return c[p];
  c[p] = 1;
  int t = min(d, r);
  for (int i = 1; i <= t; i++) {
    int j = p + i;
    if (arr[p] <= arr[j]) {
      break;
    }
    c[p] = max(c[p], solve(arr, n, d, i - 1, n - 1 - j, j, c) + 1);
  }
  t = min(d, l);
  for (int i = 1; i <= t; i++) {
    int j = p - i;
    if (arr[p] <= arr[j]) {
      break;
    }
    c[p] = max(c[p], solve(arr, n, d, j, i - 1, j, c) + 1);
  }
  return c[p];
}

int maxJumps(const vector<int> &arr, int d) {
  const int n = arr.size();
  vector<int> c(n);
  int res = 0;
  for (int i = 0; i < n; i++) {
    res = max(res, solve(arr, n, d, i, n - 1 - i, i, c));
  }
  return res;
}

int solve2(const vector<vector<int>> &l, const vector<vector<int>> &r, int p,
           vector<int> &t) {
  if (t[p] > 0)
    return t[p];
  t[p] = 1;
  for (int i : l[p]) {
    t[p] = max(t[p], solve2(l, r, i, t) + 1);
  }
  for (int i : r[p]) {
    t[p] = max(t[p], solve2(l, r, i, t) + 1);
  }
  return t[p];
}
/*
  e.g.
   8 6 5 4 7
   then 6 is in left set (l) of 7 while 5 is in right set (r) of 6,
   4 is in the right set (r) of 5, etc.
   note that say at the end of array we have:
   8 6 5 4
   then 6 is in the right set (r) of 8, 5 is in the right set (r) of 6, etc.
  must take care of the situation with equal elements. it is complex; nothing
  comes for free.
*/
int maxJumps2(const vector<int> &arr, int d) {
  const int n = arr.size();
  vector<int> t(n);
  vector<vector<int>> l(n), r(n);
  int x = 1, y = 0;
  for (int i = 1; i < n; i++) {
    if (t[y] < i - d) {
      if (arr[t[y]] > arr[t[y + 1]]) {
        r[t[y]].emplace_back(t[y + 1]);
        int z = y + 1;
        while (++z < x && arr[t[z - 1]] == arr[t[z]]) {
          r[t[y]].emplace_back(t[z]);
        }
      }
      y++;
    }
    if (arr[i] > arr[i - 1]) {
      int z = x;
      do {
        x--;
      } while (x > y && arr[t[x - 1]] < arr[i]);
      bool equal = (x > y && arr[t[x - 1]] == arr[i]);
      if (equal) {
        r[t[x - 1]].emplace_back(t[x]);
      }
      l[i].emplace_back(t[x]);
      int j = x + 1;
      for (; j < z; j++) {
        if (arr[t[j]] == arr[t[x]]) {
          l[i].emplace_back(t[j]);
          if (equal) {
            r[t[x - 1]].emplace_back(t[j]);
          }
        } else {
          break;
        }
      }
      while (j < z) {
        int p = t[j - 1];
        r[p].emplace_back(t[j]);
        while (++j < z && arr[t[j]] == arr[t[j - 1]]) {
          r[p].emplace_back(t[j]);
        }
      }
    }
    t[x++] = i;
  }
  if (y < x) {
    while (++y < x && arr[t[y - 1]] == arr[t[y]]) {
    }
    while (y < x) {
      int p = t[y - 1];
      r[p].emplace_back(t[y]);
      while (++y < x && arr[t[y - 1]] == arr[t[y]]) {
        r[p].emplace_back(t[y]);
      }
    }
  }
  memset(&t[0], 0, sizeof(int) * n);
  int ans = 0;
  for (int i = 0; i < n; i++) {
    ans = max(ans, solve2(l, r, i, t));
  }
  return ans;
}

int maxJumps2__(const vector<int> &arr, int d) {
  const int n = arr.size();
  vector<int> t(n);
  vector<vector<int>> l(n), r(n);
  for (int i = 1, x = 1, y = 0; i < n; i++) {
    if (t[y] < i - d) {
      y++;
    }
    if (arr[i] > arr[i - 1]) {
      int z = x;
      do {
        x--;
      } while (x > y && arr[t[x - 1]] < arr[i]);
      l[i].emplace_back(t[x]);
      for (int j = x + 1; j < z; j++) {
        if (arr[t[j]] == arr[t[x]]) {
          l[i].emplace_back(t[j]);
        } else {
          break;
        }
      }
    }
    t[x++] = i;
  }
  t[0] = n - 1;
  for (int i = n - 2, x = 1, y = 0; i >= 0; i--) {
    if (t[y] > i + d) {
      y++;
    }
    if (arr[i + 1] < arr[i]) {
      int z = x;
      do {
        x--;
      } while (x > y && arr[t[x - 1]] < arr[i]);
      r[i].emplace_back(t[x]);
      for (int j = x + 1; j < z; j++) {
        if (arr[t[j]] == arr[t[x]]) {
          r[i].emplace_back(t[j]);
        } else {
          break;
        }
      }
    }
    t[x++] = i;
  }
  memset(&t[0], 0, sizeof(int) * n);
  int ans = 0;
  for (int i = 0; i < n; i++) {
    ans = max(ans, solve2(l, r, i, t));
  }
  return ans;
}

// a better approach: full use of monotonic stack and dynamic programming
int maxJumps3(const vector<int> &arr, int d) {
  vector<int> dp(arr.size() + 1, 1);
  vector<int> stack1, stack2;
  for (int i = 0; i <= arr.size(); i++) {
    // pop out all the elements for the last iteration
    while (stack1.size() && (i == arr.size() || arr[i] > arr[stack1.back()])) {
      int pre_value = arr[stack1.back()];
      // use `while` here not `if` in case there are equal elements
      while (stack1.size() && pre_value == arr[stack1.back()]) {
        int back = stack1.back();
        stack1.pop_back();
        // stack 1 is a descending (not strict) stack
        // the elements poped out from stack 1 is a descending (not strict)
        // queue less than arr[i]
        // we can utilize this in backward checking
        stack2.push_back(back);
        // check forward: to the right of i
        if (i - back <= d) {
          dp[i] = max(dp[i], dp[back] + 1);
        }
      }
      while (stack2.size()) {
        // check backward: to the left of i
        if (stack1.size() && stack2.back() - stack1.back() <= d) {
          dp[stack1.back()] = max(dp[stack1.back()], dp[stack2.back()] + 1);
        }
        stack2.pop_back();
      }
    }
    stack1.push_back(i);
  }
  int output = 0;
  dp.pop_back();
  for (auto i : dp)
    output = max(output, i);
  return output;
}

int main() {
  cout << maxJumps2({79, 50, 41, 88, 35, 29, 69, 73, 59, 73, 84, 21, 43, 32, 25,
                     14, 5,  60, 48, 80, 86, 40, 30, 7,  80, 94, 32, 12, 20, 39,
                     92, 41, 85, 45, 85, 84, 65, 53, 6,  37, 39, 52, 49, 84, 64,
                     57, 81, 38, 20, 45, 43, 23, 35, 78, 95, 29, 66, 22, 30, 23,
                     40, 37, 76, 66, 12, 84, 67, 59, 82, 35, 53, 25, 95, 75, 81,
                     39, 95, 83, 38, 39, 15, 31, 53, 30, 31, 98, 67, 25, 66, 4,
                     88, 89, 10, 50, 3,  12, 21, 32, 88, 58, 62, 69, 25, 91, 78,
                     94, 41, 11, 9,  38, 49, 27, 90, 37, 17, 56, 30, 72, 28, 99,
                     68, 22, 75, 87, 10, 59, 84, 43, 81, 77},
                    8)
       << endl;
  cout << maxJumps({6, 4, 14, 6, 8, 13, 9, 7, 10, 6, 12}, 2) << endl;
  cout << maxJumps({3, 3, 3, 3, 3}, 3) << endl;
  cout << maxJumps({7, 6, 5, 4, 3, 2, 1}, 1) << endl;
  cout << maxJumps({10, 8, 6, 4, 2, 1, 3, 5, 7, 9}, 9) << endl;
  cout << maxJumps2({6, 4, 14, 6, 8, 13, 9, 7, 10, 6, 12}, 2) << endl;
  cout << maxJumps2({3, 3, 3, 3, 3}, 3) << endl;
  cout << maxJumps2({7, 6, 5, 4, 3, 2, 1}, 1) << endl;
  cout << maxJumps2({10, 8, 6, 4, 2, 1, 3, 5, 7, 9}, 9) << endl;
  cout << maxJumps3({20, 9, 9, 1, 17}, 4) << endl;
  cout << maxJumps2({39, 1,  1,   19, 40, 34, 87, 44, 30, 3,  89, 55, 81, 97,
                     84, 52, 10,  8,  96, 69, 17, 48, 93, 84, 10, 48, 1,  93,
                     65, 24, 100, 26, 24, 33, 52, 17, 15, 26, 8,  87, 69, 47,
                     61, 58, 78,  52, 2,  72, 23, 9,  3,  27, 36, 38, 88, 20,
                     21, 79, 5,   67, 22, 24, 39, 7,  17, 29, 3,  97, 36, 51,
                     91, 53, 98,  48, 83, 52, 14, 71, 91, 46, 42, 88, 44, 52,
                     74, 8,  39,  11, 48, 59, 98, 34, 43, 94, 46, 20, 26, 62,
                     6,  36, 59,  77, 23, 93, 6,  93, 64, 18, 33, 69, 56, 48,
                     54, 98, 98,  53, 14, 97, 47, 50, 33, 87, 10, 51, 92, 1,
                     14, 27, 19,  34, 83, 65, 48, 44, 82, 51, 81, 83, 23, 8,
                     63, 70, 76,  83, 46, 84, 20, 7,  37, 4,  69, 63, 84, 71,
                     91, 78, 58,  25, 63, 85, 98, 78, 21},
                    62)
       << endl;
  return 0;
}