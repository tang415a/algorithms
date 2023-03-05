/*
You are given a 0-indexed binary string s and two integers minJump and maxJump.
In the beginning, you are standing at index 0, which is equal to '0'. You can
move from index i to index j if the following conditions are fulfilled:

i + minJump <= j <= min(i + maxJump, s.length - 1), and
s[j] == '0'.
Return true if you can reach index s.length - 1 in s, or false otherwise.

Example 1:

Input: s = "011010", minJump = 2, maxJump = 3
Output: true
Explanation:
In the first step, move from index 0 to index 3.
In the second step, move from index 3 to index 5.
Example 2:

Input: s = "01101110", minJump = 2, maxJump = 3
Output: false


Constraints:

2 <= s.length <= 10^5
s[i] is either '0' or '1'.
s[0] == '0'
1 <= minJump <= maxJump < s.length
*/

#include <iostream>
using namespace std;

bool jump(string s, int minJump, int maxJump, bool *cache, int cur) {
  if (cur == s.length() - 1)
    return true;
  for (int i = minJump; i <= maxJump; ++i) {
    int n = cur + i;
    if (n >= s.length())
      return false;
    if (s[n] == '0' && !cache[n]) {
      cache[n] = true;
      if (jump(s, minJump, maxJump, cache, n))
        return true;
    }
  }
  return false;
}

bool canReach(const string &s, int minJump, int maxJump) {
  size_t siz = s.length();
  if (s[siz - 1] != '0')
    return false;
  bool *cache = new bool[siz];
  memset(cache, false, siz * sizeof(bool));
  cache[0] = true;
  bool ret = jump(s, minJump, maxJump, cache, 0);
  delete[] cache;
  return ret;
}

// a better approach
#include <vector>
bool canReach2(const string &s, int minJump, int maxJump) {
  const int n = s.length();
  if (s[n - 1] != '0')
    return false;
  vector<int> c = {0};
  int m = 0, x = 0;
  while (x < c.size()) {
    int y = max(m + 1, c[x] + minJump);
    m = c[x] + maxJump;
    while (y < n && y <= m) {
      if (s[y] == '0') {
        if (y == n - 1)
          return true;
        c.push_back(y);
      }
      y++;
    }
    x++;
  }
  return false;
}

// another approach using dynamic programming
const int max_n = 1E5;
bool dp[max_n];
bool canReach3(const string &s, int minJump, int maxJump) {
  const int n = s.size();
  dp[0] = 1;
  for (int i = 1, j = 0; i < n; i++) {
    dp[i] = 0;
    if (s[i] == '0') {
      while (j + minJump <= i) {
        if (dp[j] && j + minJump <= i && i <= j + maxJump) {
          dp[i] = 1;
          break;
        }
        j++;
      }
    }
  }
  return dp[n - 1];
}

int main() {
  cout << canReach("011010", 2, 3) << endl;
  cout << canReach("01101110", 2, 3) << endl;
  cout << canReach("00111010", 3, 5) << endl;
  cout << canReach2("011010", 2, 3) << endl;
  cout << canReach2("01101110", 2, 3) << endl;
  cout << canReach2("00111010", 3, 5) << endl;
  cout << canReach2("0001", 3, 5) << endl;
  return 0;
}