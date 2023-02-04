/*
You are given a string s. You can convert s to a palindrome by adding characters
in front of it.

Return the shortest palindrome you can find by performing this transformation.


Example 1:

Input: s = "aacecaaa"
Output: "aaacecaaa"

Example 2:

Input: s = "abcd"
Output: "dcbabcd"


Constraints:

0 <= s.length <= 5 * 10^4
s consists of lowercase English letters only.
*/

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

// some immature thoughts..
bool compare(const char *a, const char *b, int l) {
  for (int i = 0; i < l; ++i) {
    if (*a++ != *b++)
      return false;
  }
  return true;
}

string shortestPalindrome__(string s) {
  if (s.empty())
    return s;
  string c = s.substr(1);
  reverse(begin(c), end(c));
  const char *l = c.c_str(), *m = s.c_str();
  for (int i = 0, n = c.length(); i < n; i++) {
    if (compare(l + i, m, n - i)) {
      return c.substr(0, i) + s;
    }
  }
  return c + s;
}

// find the longest prefix suffix, i.e. the substring that is the prefix and
// also suffix in the mean time. note it does not include the string itself
// (otherwise the problem is meaningless), thus lps[0] is always 0
// the meaning of lps:
// when lps[i] > 0, it means s{[0]..[lps[i]-1]} = s{[i-lps[i]+1]..[i]}
// next time we should compare s[lps[i]] and s[i+1]
int find_lps(const string &str) {
  int n = str.length();
  vector<int> lps(
      n, 0); // the longest prefix suffix for substring n; initialized with 0

  int len = 0; // length of previous longest prefix suffix
  // the loop calculates lps[i] for i = 1 to n-1
  int i = 1;
  while (i < n) {
    if (str[len] == str[i]) {
      lps[i++] = ++len;
    } else {
      if (len != 0)
        len = lps[len - 1];
      else
        lps[i++] = 0;
    }
  }
  return lps[n - 1];
}

string shortestPalindrome(string s) {
  int n = s.length();
  if (n < 2)
    return s;
  string c = s, r = s;
  reverse(s.begin(), s.end());
  c += ("*" + s);
  auto len = find_lps(c);
  return len == n ? r : (s.substr(0, n - len) + r);
}

string shortestPalindrome2(string s) {
  string rev_s = s;
  reverse(rev_s.begin(), rev_s.end());
  string l = s + "#" + rev_s;

  vector<int> p(l.size(), 0);
  for (int i = 1; i < l.size(); i++) {
    int j = p[i - 1];
    while (j > 0 && l[i] != l[j])
      j = p[j - 1];
    p[i] = (j += l[i] == l[j]);
  }

  return rev_s.substr(0, s.size() - p[l.size() - 1]) + s;
}

int main() {
  string s = "aacecaaa";
  cout << shortestPalindrome(s) << endl;
  s = "abcd";
  cout << shortestPalindrome(s) << endl;
  s = "aa";
  cout << shortestPalindrome(s) << endl;
  s = "abba";
  cout << shortestPalindrome(s) << endl;
  s = "abcba";
  cout << shortestPalindrome(s) << endl;
  s = "adcba";
  cout << shortestPalindrome(s) << endl;
  s = "abbacde";
  cout << shortestPalindrome(s) << endl;
  s = "";
  cout << shortestPalindrome(s) << endl;
  s = "aaa";
  cout << shortestPalindrome(s) << endl;
  return 0;
}
