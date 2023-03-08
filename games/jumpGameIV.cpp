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
#include <unordered_map>
#include <vector>

using namespace std;
// dynamic programming, without recursive search
// it is inefficient, however, the way of thinking may be of some value
void propagate(vector<int> &c, int l, int n, int i, int v, const vector<int> &a,
               unordered_map<int, vector<int>> &m, bool b) {
  if (b) {
    auto it = m.find(a[i]);
    if (it != m.end()) {
      if (it->second[0] > v) {
        it->second[0] = v;
      }
      for (int k = 1, h = it->second.size(); k < h; k++) {
        const int &j = it->second[k];
        if (c[j] > v + 1) {
          c[j] = v + 1;
          propagate(c, l, n, j, c[j], a, m, false);
        }
      }
    }
  }

  if (i - 1 > l && c[i - 1] > v + 1) {
    c[i - 1] = v + 1;
    propagate(c, l, n, i - 1, v + 1, a, m, true);
  }

  if (i + 1 < n && c[i + 1] > v + 1) {
    c[i + 1] = v + 1;
    propagate(c, l, n, i + 1, v + 1, a, m, true);
  }
}

int minJumps(const vector<int> &arr) {
  const int n = arr.size();
  vector<int> c(n);
  unordered_map<int, vector<int>> m = {{arr[n - 1], vector<int>{0, n - 1}}};
  for (int i = n - 2; i >= 0; i--) {
    c[i] = c[i + 1] + 1;
    bool b = true;
    auto it = m.find(arr[i]);
    if (it != m.end()) {
      int t = it->second[0] + 1;
      if (t < c[i]) {
        c[i] = t;
        b = false;
      } else if (t == c[i] || t == c[i] + 1) {
        b = false;
      }
    }
    if (i > 0) {
      propagate(c, i, n, i, c[i], arr, m, b);

      if (it != m.end()) {
        it->second.emplace_back(i);
      } else {
        m.insert(make_pair(arr[i], vector<int>{c[i], i}));
      }
    }
  }
  return c[0];
}

// a better approach: use recursive search!
int minJumps2(const vector<int> &arr) {
  const int n = arr.size();
  if (n == 1)
    return 0;
  unordered_map<int, vector<int>> m;
  for (int i = 1; i < n; i++) {
    auto it = m.find(arr[i]);
    if (it == m.end()) {
      m.insert(make_pair(arr[i], vector<int>{0, i}));
    } else {
      it->second.emplace_back(i);
    }
  }
  vector<bool> visited(n);
  visited[0] = true;
  vector<int> cur = {0};
  int steps = 0, l = 0;
  while (l < cur.size()) {
    steps++;
    int h = cur.size();
    while (l < h) {
      if (cur[l] > 0 && !visited[cur[l] - 1]) {
        visited[cur[l] - 1] = true;
        cur.emplace_back(cur[l] - 1);
      }
      if (cur[l] + 1 == n - 1) {
        return steps;
      }
      if (!visited[cur[l] + 1]) {
        visited[cur[l] + 1] = true;
        cur.emplace_back(cur[l] + 1);
      }
      auto it = m.find(arr[cur[l]]);
      if (it != m.end() && it->second[0] == 0) {
        it->second[0] = 1;
        for (int j = 1, x = it->second.size(); j < x; j++) {
          if (it->second[j] == n - 1)
            return steps;
          if (!visited[it->second[j]]) {
            visited[it->second[j]] = true;
            cur.emplace_back(it->second[j]);
          }
        }
      }
      l++;
    }
  }
  return -1;
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
  cout << minJumps({7, 7, 2, 1, 7, 7, 7, 3, 4, 1}) << endl; // 3
  cout << minJumps({-68, 59,  59, 25,  -38, 25,  -56, -77, -17, -17, 72,  -76,
                    -74, -38, 12, -96, -74, -38, 72,  -96, 1,   81,  -17, 66,
                    -76, -17, 70, 16,  -17, 36,  -68, 70,  1,   -68, 25,  -12,
                    12,  -74, 36, -56, 16,  82,  72,  -96, -17, 45,  -12, -12,
                    -38, -17, 25, -76, -17, 35,  76,  76,  45,  -76, -17, -96,
                    70,  -38, 35, -17, 1,   81,  -38, -17, -17, -56, -38, 25,
                    16,  12,  57, -74, -74, -76, 57,  -17, 1,   12,  -96, -38,
                    70,  -38, 16, 25,  -17})
       << endl; // 4
  cout << "=====================================================" << endl;
  cout << minJumps2({100, -23, -23, 404, 100, 23, 23, 23, 3, 404}) << endl; // 3
  cout << minJumps2({7}) << endl;                                           // 0
  cout << minJumps2({7, 6, 9, 6, 9, 6, 9, 7}) << endl;                      // 1
  cout << minJumps2({2, 6, 9, 5, 7, 6, 9, 6, 8, 9, 7}) << endl;             // 4
  cout << minJumps2({2, 9, 3, 5, 2, 6, 1, 8, 9, 0, 0, 0, 0, 8, 7}) << endl; // 5
  cout << minJumps2(                                                        // 5
              {3, 7, 8, 9, 6, 2, 5, 1, 4, -3, -5, 2, 3, -8, -2, 10, -9, -7, 5})
       << endl;
  cout << minJumps2({7, 7, 2, 1, 7, 7, 7, 3, 4, 1}) << endl; // 3
  cout << minJumps2({-68, 59,  59, 25,  -38, 25,  -56, -77, -17, -17, 72,  -76,
                    -74, -38, 12, -96, -74, -38, 72,  -96, 1,   81,  -17, 66,
                    -76, -17, 70, 16,  -17, 36,  -68, 70,  1,   -68, 25,  -12,
                    12,  -74, 36, -56, 16,  82,  72,  -96, -17, 45,  -12, -12,
                    -38, -17, 25, -76, -17, 35,  76,  76,  45,  -76, -17, -96,
                    70,  -38, 35, -17, 1,   81,  -38, -17, -17, -56, -38, 25,
                    16,  12,  57, -74, -74, -76, 57,  -17, 1,   12,  -96, -38,
                    70,  -38, 16, 25,  -17})
       << endl; // 4
  return 0;
}