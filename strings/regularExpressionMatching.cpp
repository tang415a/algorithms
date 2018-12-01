/*
Given an input string (s) and a pattern (p), implement regular expression matching with support for '.' and '*'.

'.' Matches any single character.
'*' Matches zero or more of the preceding element.

The matching should cover the entire input string (not partial).

Note:

s could be empty and contains only lowercase letters a-z.
p could be empty and contains only lowercase letters a-z, and characters like . or *.

Example 1:

Input:
s = "aa"
p = "a"
Output: false
Explanation: "a" does not match the entire string "aa".

Example 2:

Input:
s = "aa"
p = "a*"
Output: true
Explanation: '*' means zero or more of the precedeng element, 'a'. Therefore, by repeating 'a' once, it becomes "aa".

Example 3:

Input:
s = "ab"
p = ".*"
Output: true
Explanation: ".*" means "zero or more (*) of any character (.)".

Example 4:

Input:
s = "aab"
p = "c*a*b"
Output: true
Explanation: c can be repeated 0 times, a can be repeated 1 time. Therefore it matches "aab".

Example 5:

Input:
s = "mississippi"
p = "mis*is*p*."
Output: false
*/

#include <stdio.h>
#include <string>
using namespace std;

bool doMatch(const char* s, const char* p) {
  int i = 0, j = 0;
  int ls = strlen(s), lp = strlen(p);
  while (i < ls && j < lp) {
    if (j + 1 < lp && p[j + 1] == '*') {
      if (doMatch(s + i, p + j + 2))
        return true;
      if (s[i] == p[j] || p[j] == '.') i++;
      else return false;
    }
    else {
      if (s[i] != p[j] && p[j] != '.')
        return false;
      i++;
      j++;
    }
  }
  if (i < ls) return false;
  while (j < lp) {
    if (j < lp - 1 && p[j + 1] == '*') j += 2;
    else return false;
  }
  return true;
}

bool match(const string& s, const string& p) {
  return doMatch(s.c_str(), p.c_str());
}

int main() {
  string s = "aa", p = "a";
  printf("%s, %s: %d\n", s, p, match(s, p));

  s = "aa";
  p = "a*";
  printf("%s, %s: %d\n", s, p, match(s, p));

  s = "ab";
  p = ".*";
  printf("%s, %s: %d\n", s, p, match(s, p));

  s = "aab";
  p = "c*a*b";
  printf("%s, %s: %d\n", s, p, match(s, p));

  s = "mississippi";
  p = "mis*is*p*.";
  printf("%s, %s: %d\n", s, p, match(s, p));
  
  s = "mississippi";
  p = ".*";
  printf("%s, %s: %d\n", s, p, match(s, p));

  s = "m";
  p = "p";
  printf("%s, %s: %d\n", s, p, match(s, p));

  s = "aaab";
  p = "a*ab";
  printf("%s, %s: %d\n", s, p, match(s, p));

  s = "aabb";
  p = "c*.*b";
  printf("%s, %s: %d\n", s, p, match(s, p));

  s = "aabbc";
  p = "c*.*bce*f*";
  printf("%s, %s: %d\n", s, p, match(s, p));

  return 0;
}