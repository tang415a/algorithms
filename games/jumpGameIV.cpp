/*
Given an array of integers arr, you are initially positioned at the first index
of the array.

In one step you can jump from index i to index:

i + 1 where: i + 1 < arr.length.
i - 1 where: i - 1 >= 0.
j where: arr[i] == arr[j] and i != j.
Return the minimum number of steps to reach the last index of the array.

Notice that you can not jump outside of the array at any time.

Example 1:

Input: arr = [100,-23,-23,404,100,23,23,23,3,404]
Output: 3
Explanation: You need three jumps from index 0 --> 4 --> 3 --> 9. Note that
index 9 is the last index of the array.

Example 2:
Input: arr = [7]
Output: 0
Explanation: Start index is the last index. You do not need to jump.
Example 3:

Input: arr = [7,6,9,6,9,6,9,7]
Output: 1
Explanation: You can jump directly from index 0 to index 7 which is last index
of the array.

Constraints:

1 <= arr.length <= 5 * 10^4
-10^8 <= arr[i] <= 10^8
*/
#include <iostream>
#include <map>
#include <numeric>
#include <set>
#include <vector>

using namespace std;

void propagate(vector<int> &c, int l, int i, int v, int n, const vector<int> &a,
               map<int, vector<int>> const &m) {
  auto it = m.find(a[i]);
  if (it != m.end()) {
    for (int j : it->second) {
      if (c[j] > v + 1) {
        c[j] = v + 1;
        propagate(c, l, j, c[j], n, a, m);
      }
    }
  }

  if (i - 1 > l && c[i - 1] > v + 1) {
    c[i - 1] = v + 1;
    propagate(c, l, i - 1, v + 1, n, a, m);
  }

  if (i + 1 < n && c[i + 1] > v + 1) {
    c[i + 1] = v + 1;
    propagate(c, l, i + 1, v + 1, n, a, m);
  }
}

int minJumps(const vector<int> &arr) {
  const int n = arr.size();
  vector<int> c(n);
  map<int, vector<int>> m = {{arr[n - 1], vector<int>{n - 1}}};
  for (int i = n - 2; i >= 0; i--) {
    c[i] = c[i + 1] + 1;
    auto it = m.find(arr[i]);
    if (it != m.end()) {
      c[i] = min(c[i], c[it->second.back()] + 1);
    }
    if (i > 0) {
      propagate(c, i, i, c[i], n, arr, m);

      if (it != m.end()) {
        it->second.emplace_back(i);
      } else {
        m.insert(make_pair(arr[i], vector<int>{i}));
      }
    }
  }
  return c[0];
}

int minJumps__(const vector<int> &arr) {
  const int n = arr.size();
  vector<int> c(n);
  //   map<int, set<int>> m;
  //   for (int i = 1; i < n; i++) {
  //     auto it = m.find(arr[i]);
  //     if (it == m.end()) {
  //       m.insert(make_pair(arr[i], set<int>{i}));
  //     } else {
  //       it->second.insert(i);
  //     }
  //   }
  map<int, int> m;
  m.insert(make_pair(arr[0], 0));
  for (int i = 1; i < n; i++) {
    c[i] = min(i, c[i - 1] + 1);
    auto it = m.find(arr[i]);
    if (it != m.end()) {
      c[i] = min(c[i], c[it->second] + 1);
    }
    m[arr[i]] = i;
  }
  m.clear();
  m.insert(make_pair(arr[n - 1], 0));
  vector<int> d(n);
  for (int i = n - 2; i >= 0; i--) {
    d[i] = min(n - 1 - i, d[i + 1] + 1);
    auto it = m.find(arr[i]);
    if (it != m.end()) {
      d[i] = min(d[i], d[it->second] + 1);
    }
    m[arr[i]] = i;
  }
  int ans = min(d[0], c[n - 1]);
  for (int i = 1; i < n - 1; i++) {
    ans = min(ans, c[i] + d[i]);
  }
  return ans;
}

int minJumps___(const vector<int> &arr) {
  int ans = 0;
  map<int, set<int>> m = {{0, set<int>{arr.back()}}};
  for (int n = arr.size(), i = n - 2; i >= 0; i--) {
    ans++;
    for (int j = 0; j < ans - 1; j++) {
      auto it = m.find(j);
      if (it != m.end() && it->second.find(arr[i]) != it->second.end()) {
        ans = min(ans, j + 1);
        break;
      }
    }
    for (int j = 1; j < min(ans - 1, i); j++) {
      int x = i - j;
      for (int k = 0; k < ans - 1 - j; k++) {
        auto it = m.find(k);
        if (it != m.end() && it->second.find(arr[x]) != it->second.end()) {
          ans = min(ans, j + k + 1);
          break;
        }
      }
    }
    auto it = m.find(ans);
    if (it != m.end()) {
      it->second.insert(arr[i]);
    } else {
      m.insert(make_pair(ans, set<int>{arr[i]}));
    }
  }
  return ans;
}

int minJumps____(const vector<int> &arr) {
  int ans = 0;
  map<int, int> m = {{arr.back(), 0}};
  for (int n = arr.size(), i = n - 2; i >= 0; i--) {
    ans++;
    auto it = m.find(arr[i]);
    if (it != m.end()) {
      ans = min(ans, it->second + 1);
    }
    for (int j = 1; j < min(ans - 1, i); j++) {
      it = m.find(arr[i - j]);
      if (it != m.end()) {
        ans = min(ans, j + it->second + 1);
      }
    }
    it = m.find(arr[i]);
    if (it != m.end()) {
      it->second = min(it->second, ans);
    } else {
      m.insert(make_pair(arr[i], ans));
    }
  }
  return ans;
}

int main() {
  cout << minJumps({100, -23, -23, 404, 100, 23, 23, 23, 3, 404}) << endl; // 3
  cout << minJumps({7}) << endl;                                           // 0
  cout << minJumps({7, 6, 9, 6, 9, 6, 9, 7}) << endl;                      // 1
  cout << minJumps({2, 6, 9, 5, 7, 6, 9, 6, 8, 9, 7}) << endl;             // 4
  cout << minJumps({2, 9, 3, 5, 2, 6, 1, 8, 9, 0, 0, 0, 0, 8, 7}) << endl; // 5
  cout << minJumps(                                                        // 5
              {3, 7, 8, 9, 6, 2, 5, 1, 4, -3, -5, 2, 3, -8, -2, 10, -9, -7, 5})
       << endl;
  return 0;
}