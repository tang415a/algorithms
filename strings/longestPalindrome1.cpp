/*
You are given two strings, word1 and word2. You want to construct a string in
the following manner:

Choose some non-empty subsequence subsequence1 from word1.
Choose some non-empty subsequence subsequence2 from word2.
Concatenate the subsequences: subsequence1 + subsequence2, to make the string.
Return the length of the longest palindrome that can be constructed in the
described manner. If no palindromes can be constructed, return 0.

A subsequence of a string s is a string that can be made by deleting some
(possibly none) characters from s without changing the order of the remaining
characters.

A palindrome is a string that reads the same forward as well as backward.

Example 1:

Input: word1 = "cacb", word2 = "cbba"
Output: 5
Explanation: Choose "ab" from word1 and "cba" from word2 to make "abcba", which
is a palindrome.

Example 2:

Input: word1 = "ab", word2 = "ab"
Output: 3
Explanation: Choose "ab" from word1 and "a" from word2 to make "aba", which is a
palindrome. Example 3:

Input: word1 = "aa", word2 = "bb"
Output: 0
Explanation: You cannot construct a palindrome from the described method, so
return 0.

Constraints:

1 <= word1.length, word2.length <= 1000
word1 and word2 consist of lowercase English letters.
*/
#include <iostream>
#include <string>
#include <vector>

using namespace std;
int longestPalindrome(const string &word1, const string &word2) {
  int n1 = word1.length(), n2 = word2.length(), sum = n1 + n2;
  string c = word1 + word2;
  vector<int> p(sum, 0);
  int cache[26];
  memset(cache, -1, sizeof(int) * 26);
  for (int i = 0; i < sum; i++) {
    int& j = cache[c[i] - 'a'];
    if (j >= 0) {
      p[j] = i;
    }
    j = i;
  }
  int ans = 0;
  vector<int> ret(sum);
  bool isOdd = false;
  for (int i = 0; i < sum; i++) {
    if (!isOdd && ans > 0 && ret[ans - 1] > i) {
      isOdd = true;
    }
    int m = i;
    while (p[m] > 0) {
      m = p[m];
      int j = 0;
      for (; j < ans; ++j) {
        if (m > ret[j]) {
          if ((j == 0 && m >= n1 && i < n1) || j > 0)
            ret[j] = m;
          break;
        } else if (m == ret[j]) {
          break;
        }
      }
      if (j == ans && (ans > 0 || (ans == 0 && m >= n1 && i < n1))) {
        ret[ans] = m;
        ans++;
        isOdd = false;
      }
    }
  }
  if (ans == 0)
    return 0;
  return isOdd ? (2 * ans + 1) : (2 * ans);
}

int main() {
  cout << longestPalindrome("bb", "b") << endl;
  cout << longestPalindrome("cacbbf", "gcac") << endl;
  cout << longestPalindrome("cacbbca", "bcbac") << endl;
  cout << longestPalindrome("cacb", "cbba") << endl;
  cout << longestPalindrome("ab", "ab") << endl;
  cout << longestPalindrome("aa", "bb") << endl;
  cout << longestPalindrome("abcd", "abcd") << endl;
  cout << longestPalindrome("abcd", "dcba") << endl;
  cout << longestPalindrome("aabaa", "aabb") << endl;
  cout << longestPalindrome("abcde", "edcig") << endl;
  cout << longestPalindrome("igdcef", "edcig") << endl;
  return 0;
}