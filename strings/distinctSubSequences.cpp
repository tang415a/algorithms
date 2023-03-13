/*
Given two strings s and t, return the number of distinct
subsequences of s which equals t.

The test cases are generated so that the answer fits on a 32-bit signed integer.

Example 1:

Input: s = "rabbbit", t = "rabbit"
Output: 3
Explanation:
As shown below, there are 3 ways you can generate "rabbit" from s.
rabbbit
rabbbit
rabbbit

Example 2:

Input: s = "babgbag", t = "bag"
Output: 5
Explanation:
As shown below, there are 5 ways you can generate "bag" from s.
babgbag
babgbag
babgbag
babgbag
babgbag

Constraints:

1 <= s.length, t.length <= 1000
s and t consist of English letters.
*/

#include <iostream>
#include <string>
#include <vector>

using namespace std;

int numDistinct__(string s, string t) {
  int n = s.length(), m = t.length();
  vector<int> a(m);
  for (int i = n - 1, j = m - 1; i >= 0; i--) {
    for (int k = j; k < m; k++) {
      if (s[i] == t[k]) {
        a[k] += k == m - 1 ? 1 : a[k + 1];
      }
    }
    if (s[i] == t[j] && j > 0) {
      j--;
    }
  }
  return a[0];
}

int numDistinct(string s, string t) {
  int n = s.length(), m = t.length();
  vector<long long> a(m);
  vector<int> v[52];
  for (int i = 0; i < m; i++) {
    if (t[i] >= 'a') {
      v[t[i] - 'a'].emplace_back(i);
    } else {
      v[t[i] - 'A' + 26].emplace_back(i);
    }
  }
  for (int i = n - 1, j = m - 1; i >= 0; i--) {
    if (s[i] >= 'a') {
      for (int k : v[s[i] - 'a']) {
        if (k >= j) {
          a[k] += k == m - 1 ? 1 : a[k + 1];
          if (k == j && j > 0) {
            j--;
          }
        }
      }
    } else {
      for (int k : v[s[i] - 'A' + 26]) {
        if (k >= j) {
          a[k] += k == m - 1 ? 1 : a[k + 1];
          if (k == j && j > 0) {
            j--;
          }
        }
      }
    }
  }
  return a[0];
}

int numDistinct2(string s, string t) {
  const int m = s.length();
  const int n = t.length();
  vector<long> dp(n + 1);
  dp[0] = 1;
  for (int i = 1; i <= m; ++i)
    for (int j = n; j >= 1; --j)
      if (s[i - 1] == t[j - 1])
        dp[j] += dp[j - 1];
  return dp[n];
}

int numDistinct3(string s, string t) {
  int m = s.length();
  int n = t.length();

  int **dp = new int *[m + 1];
  for (int i = 0; i <= m; i++) {
    dp[i] = new int[n + 1];
    memset(dp[i], 0, sizeof(int) * (n + 1));
  }

  for (int i = 0; i <= m; i++) {
    dp[i][0] = 1;
  }

  for (int i = 1; i <= m; i++) {
    for (int j = 1; j <= n; j++) {
      if (s[i - 1] == t[j - 1]) {
        dp[i][j] = dp[i - 1][j - 1] + dp[i - 1][j];
      } else {
        dp[i][j] = dp[i - 1][j];
      }
    }
  }

  int ans = dp[m][n];
  for (int i = 0; i <= m; i++)
    delete[] dp[i];
  delete[] dp;
  return ans;
}

int main() {
  cout << numDistinct("rabbbit", "rabbit") << endl;
  cout << numDistinct("RABBBIT", "RABBIT") << endl;
  cout << numDistinct("babgbag", "bag") << endl;
  cout << numDistinct("BABGBAG", "BAG") << endl;
  cout << numDistinct2("rabbbit", "rabbit") << endl;
  cout << numDistinct2("RABBBIT", "RABBIT") << endl;
  cout << numDistinct2("babgbag", "bag") << endl;
  cout << numDistinct2("BABGBAG", "BAG") << endl;
  return 0;
}