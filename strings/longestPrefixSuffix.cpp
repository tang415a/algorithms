/*
Given a string. Find out the longest substring that is a prefix and also a
suffix of the string. Note that both the prefix and suffix doesn't include the
string itself.

Example:
s = "abcdeijihabcde"

Output:
5

Explanation:
abcde is the longest prefix suffix of s.
*/

#include <iostream>
#include <string>

using namespace std;

int longestPrefixSuffix(const std::string &s) {
  int n = s.length();
  int *p = new int[n];
  p[0] = 0;
  int len = 0;
  for (int i = 1; i < n;) {
    if (s[i] == s[len]) {
      p[i++] = ++len;
    } else {
      // len is the prefix-suffix of s[0..i-1], which means s[0..len-1] =
      // s[i-len..i-1] then try with the prefix-suffix in s[0..len-1]. the
      // prefix-suffix in s[0..len-1] also works in s[i-len..i-1], therefore is
      // also a prefix-suffix of s[0..i-1].
      if (len > 0) {
        len = p[len - 1];
      } else {
        p[i++] = 0;
      }
    }
  }
  delete[] p;
  return len;
}

int main() {
  cout << longestPrefixSuffix("abcdeijihabcde") << endl;
  cout << longestPrefixSuffix("aaaaijihaaaa") << endl;
  cout << longestPrefixSuffix("abac") << endl;
  return 0;
}