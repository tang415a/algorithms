/*
Given a string which contains only lowercase letters, remove duplicate letters
so that every letter appear once and only once. You must make sure your result
is the smallest in lexicographical order among all possible results.

Example 1:

Input: "bcabc"
Output: "abc"
Example 2:

Input: "cbacdcbc"
Output: "acdb"

Example 3:

Input: "cedabcdesza"
Output: "abcdesz"

Example 4:

Input: "cbedddedc"
Output: "bdec"

Constraints:
1 <= s.length <= 10^4
s consists of lowercase English letters.
*/
#include <stdio.h>
#include <string>

using namespace std;

// use monotonic stack but pay attention to the equal elements in the stack
string removeDuplicateLetters(const string &s) {
  int hash[26] = {};
  const int n = s.length();
  for (int i = 0; i < n; i++)
    hash[s[i] - 'a'] = i + 1;
  string ans, t(n, 0);
  for (int i = 0, l = 0, h = 0; i < n; i++) {
    // if this is the last occurrence of s[i]
    if (hash[s[i] - 'a'] == i + 1) {
      hash[s[i] - 'a'] = 0;
      // push all the characters less than s[i] into result
      while (l < h && t[l] < s[i]) {
        hash[t[l] - 'a'] = 0;
        ans.push_back(t[l]);
        l++;
      }
      // if there are still characters in the stack
      if (l < h) {
        // if s[i] is already in the stack, remain the elements from l + 1
        if (t[l] == s[i]) {
          l++;
        } else {
          l = h; // clear the stack
        }
      }
      ans.push_back(s[i]);
    } else if (hash[s[i] - 'a'] > 0) {
      int x = h;
      while (l < h && s[i] <= t[h - 1]) {
        h--;
      }
      // h < x means t[h] is the first element that is greater than or equal to
      // s[i]. if t[h] is equal to s[i], we need to keep everything as it is
      // (restore h to the original value); otherwise all the elements greater
      // than s[i] should be discarded and put s[i] at position h
      if (h < x && t[h] == s[i]) {
        h = x;
        continue;
      }
      t[h++] = s[i];
    }
  }
  return ans;
}

int main() {
  printf("%s\n", removeDuplicateLetters("bcabc").c_str());       // "abc"
  printf("%s\n", removeDuplicateLetters("cbacdcbc").c_str());    // "acdb"
  printf("%s\n", removeDuplicateLetters("cedabcdesza").c_str()); // "abcdesz"
  printf("%s\n", removeDuplicateLetters("cbedddedc").c_str());   // "bdec"
  printf("%s\n", removeDuplicateLetters("abacb").c_str());       // "abc"
  printf("%s\n", removeDuplicateLetters("thesqtitxyetpxloeevdeqifkz")
                     .c_str()); // "hesitxyplovdqfkz"
  return 0;
}
