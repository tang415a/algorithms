/*
Given a string s, return true if the s can be palindrome after deleting at most
one character from it.

Example 1:

Input: s = "aba"
Output: true
Example 2:

Input: s = "abca"
Output: true
Explanation: You could delete the character 'c'.
Example 3:

Input: s = "abc"
Output: false


Constraints:

1 <= s.length <= 10^5
s consists of lowercase English letters.
*/

#include <iostream>
#include <string>

using namespace std;

bool validCheck(const string &s, int i, int j, bool tol) {
  while (i < j) {
    if (s[i] != s[j]) {
      return tol ? (validCheck(s, i + 1, j, false) ||
                    validCheck(s, i, j - 1, false))
                 : false;
    }
    i++;
    j--;
  }
  return true;
}

bool validPalindrome(const string &s) {
  return validCheck(s, 0, s.length() - 1, true);
}

int main() {
  cout << validPalindrome("aba") << endl;
  cout << validPalindrome("abca") << endl;
  cout << validPalindrome("abc") << endl;
  return 0;
}