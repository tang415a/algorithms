/*
Given two strings A and B of lowercase letters, return true if and only if we
can swap two letters in A so that the result equals B.

Example 1:

Input: A = "ab", B = "ba"
Output: true

Example 2:

Input: A = "ab", B = "ab"
Output: false

Example 3:

Input: A = "aa", B = "aa"
Output: true

Example 4:

Input: A = "aaaaaaabc", B = "aaaaaaacb"
Output: true

Example 5:

Input: A = "", B = "aa"
Output: false

Note:

0 <= A.length <= 20000
0 <= B.length <= 20000
A and B consist only of lowercase letters.
*/

#include <stdio.h>
#include <string>
using namespace std;

bool buddyStrings(const string &A, const string &B) {
  int siz = A.size();
  if (siz != B.size())
    return false;
  char rec[26];
  memset(rec, 0, sizeof(char) * 26);
  char positions[2] = {};
  char diffs = 0;
  for (auto i = 0; i < siz; i++) {
    if (A[i] != B[i]) {
      if (diffs >= 2)
        return false;
      positions[diffs++] = i;
    } else
      rec[A[i] - 'a']++;
  }
  if (diffs == 2)
    return A[positions[0]] == B[positions[1]] &&
           A[positions[1]] == B[positions[0]];
  if (diffs == 0) {
    for (auto i = 0; i < 26; i++) {
      if (rec[i] > 1)
        return true;
    }
  }
  return false;
}

#include <unordered_set>

// a better approach
bool buddyStrings2(const string &s, const string &goal) {
  if (s == goal) {
    unordered_set<char> chars;
    for (char c : s) {
      if (chars.count(c) > 0) {
        return true;
      }
      chars.insert(c);
    }
    return false;
  }
  if (s.length() != goal.length()) {
    return false;
  }
  vector<int> diff;
  for (int i = 0; i < s.length(); ++i) {
    if (s[i] == goal[i])
      continue;
    if (diff.size() == 2) {
      return false; // 3+ diffs
    }
    diff.push_back(i);
  }
  return diff.size() == 2 && s[diff[0]] == goal[diff[1]] &&
         s[diff[1]] == goal[diff[0]];
}

int main() {
  string A = "", B = "aa";
  printf("%d", buddyStrings(A, B));
  return 0;
}