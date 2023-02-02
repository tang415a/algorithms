/*
Given a string s, return the length of the longest palindrome substring of s.
*/

#include <iostream>
#include <string>

using namespace std;

// Manacher's Algorithm
char *preProcess(char *s) {
  size_t len = strlen(s), i;
  char *ret = new char[2 * len + 3];
  memset(ret, '#', 2 * len + 3);
  // use a special character as guard to indicate this is the first character
  ret[0] = '^';
  for (i = 1; i <= len; ++i)
    ret[2 * i] = s[i - 1];
  ret[2 * len + 2] = 0;

  return ret;
}

char *longestPalindrome(char *s, size_t &max) {
  size_t len = strlen(s);
  if (len < 2)
    return s;

  char *ptr = preProcess(s);
  int *P = new int[2 * len + 2];

  size_t center = 0; /* the center of palindrome */
  size_t right = 0;  /* the right bound of palindrome */
  for (size_t i = 1; i < 2 * len + 2; ++i) {
    size_t mirror = 2 * center - i; /* center - (i - center) */

    // P[i] is the length of palindrome centering at i
    // it is the smaller value between right - i and P[mirror]
    P[i] = (right > i) ? min(right - i, P[mirror]) : 0;

    // extend the palindrome centering at i as possible
    // it will stop if it meets the guard (^ and \0)
    while (ptr[i + P[i] + 1] == ptr[i - P[i] - 1])
      ++P[i];

    // update center and right
    if (i + P[i] > right) {
      center = i;
      right = i + P[i];
    }
  }
  // get the longest palindrome
  max = 0;
  for (size_t i = 1; i < 2 * len + 2; ++i) {
    if (P[i] > max) {
      max = P[i];
      center = i;
    }
  }
  delete[] P;
  delete[] ptr;
  s[(center + max) / 2] = 0;
  return &s[(center - max) / 2];
}

int longestPalindrome2(const string &s) {
  int n = s.length();
  int **p = new int *[n];
  // odd
  for (int i = 0; i < n; ++i) {
    p[i] = new int[n];
    memset(p[i], 0, sizeof(int) * n);
    p[i][i] = 1;
  }

  int ans = 1;
  // even
  for (int i = 0; i < n - 1; ++i) {
    if (s[i] == s[i + 1]) {
      p[i][i + 1] = 2;
      if (ans < 2)
        ans = 2;
    }
  }

  for (int i = 3; i <= n; ++i) {
    for (int j = i - 1; j < n; ++j) {
      if (s[j - i + 1] == s[j] && p[j - i + 2][j - 1] > 0) {
        p[j - i + 1][j] = i;
        if (ans < i)
          ans = i;
      }
    }
  }

  for (int i = 0; i < n; ++i)
    delete[] p[i];
  delete[] p;
  return ans;
}

int main() {
  size_t max = 0;
  char s[] = "abcdeedcig";
  cout << longestPalindrome(s, max) << endl;
  cout << max << endl;
  cout << longestPalindrome2(s) << endl;
  cout << longestPalindrome2("abcdcba") << endl;
  cout << longestPalindrome2("aiabcddcjlbae") << endl;
  return 0;
}