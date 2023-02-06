/*
Given a string s, find the longest palindromic subsequence's length in s.

A subsequence is a sequence that can be derived from another sequence by deleting some or no elements without changing the order of the remaining elements.


Example 1:

Input: s = "bbbab"
Output: 4
Explanation: One possible longest palindromic subsequence is "bbbb".

Example 2:

Input: s = "cbbd"
Output: 2
Explanation: One possible longest palindromic subsequence is "bb".


Constraints:

1 <= s.length <= 1000
s consists only of lowercase English letters.
*/

#include <string>
#include <iostream>
#include <vector>
using namespace std;

int longestPalindromeSubseq(const string &s)
{
  int cache[26];
  memset(cache, -1, sizeof(int) * 26);
  int n = s.length();
  vector<int> p(n, 0);
  for (int i = 0; i < n; ++i) {
    int &j = cache[s[i] - 'a'];
    if (j >= 0) {
      p[j] = i;
    }
    j = i;
  }
  int ans = 0;
  vector<int> res(n, 0);
  bool odd = true;
  for (int i = 0; i < n; ++i) {
    if (!odd && ans > 0 && res[ans - 1] > i) {
      odd = true;
    }
    int m = i;
    while (p[m] > 0) {
      m = p[m];
      int j = 0;
      for (; j < ans; ++j) {
        if (res[j] < m) {
          res[j] = m;
          break;
        }
        if (res[j] == m)
          break;
      }
      if (j == ans) {
        res[ans++] = m;
        odd = false;
      }
    }
  }
  return odd ? (2 * ans + 1) : (2 * ans);
}

int longestPalindromeSubseq2(const string &s) {
  int n = s.length();
  int **p= new int*[n];
  for (int i = 0; i < n; ++i) {
    p[i] = new int[n];
    p[i][i] = 1;
  }
  for (int i = 0; i < n - 1; ++i) {
    p[i][i + 1] = s[i] == s[i + 1] ? 2 : 1;
  }
  for (int i = 3; i <= n; ++i) {
    for (int j = 0; j <= n - i; ++j) {
      if (s[j] == s[j + i - 1]) {
        p[j][j + i - 1] = 2 + p[j + 1][j + i - 2];
      } else {
        p[j][j + i - 1] = max(p[j][j + i - 2], p[j + 1][j + i - 1]);
      }
    }
  }
  int ans = p[0][n - 1];
  for (int i = 0; i < n; ++i) {
    delete[] p[i];
  }
  delete[] p;
  return ans;
}

int main()
{
  cout << longestPalindromeSubseq2("bbbab") << endl;
  cout << longestPalindromeSubseq2("cbbd") << endl;
  return 0;
}