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
    int &j = cache[c[i] - 'a'];
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
        ret[ans++] = m;
        isOdd = false;
      }
    }
  }
  if (ans == 0)
    return 0;
  return isOdd ? (2 * ans + 1) : (2 * ans);
}

int longestPalindrome2(const string &a, const string &b) {
  int n1 = a.length(), n2 = b.length(), n = n1 + n2;
  int **p = new int *[n];
  for (int i = 0; i < n; i++) {
    p[i] = new int[n];
    p[i][i] = 1;
  }

  string s = a + b;
  int ans = 0;
  for (int i = 0; i < n - 1; i++) {
    if (s[i] == s[i + 1]) {
      p[i][i + 1] = 2;
      if (i == n1 - 1)
        ans = 2;
    } else {
      p[i][i + 1] = 1;
    }
  }
  for (int i = 3; i <= n; i++) {
    for (int j = 0; j <= n - i; j++) {
      if (s[j] == s[j + i - 1]) {
        p[j][j + i - 1] = 2 + p[j + 1][j + i - 2];
        if (j < n1 && j + i - 1 >= n1 && ans < p[j][j + i - 1]) {
          ans = p[j][j + i - 1];
        }
      } else {
        p[j][j + i - 1] = max(p[j][j + i - 2], p[j + 1][j + i - 1]);
      }
    }
  }
  for (int i = 0; i < n; i++) {
    delete[] p[i];
  }
  delete[] p;
  return ans;
}

#include <algorithm>

// cm1[i] means the longest common subsequence between w1[0..i] and w2
// cm2[i] means the longest common subsequence between w2[0..i] and w1
// cm1[s1 - 1] == cm2[s2 - 1]
int cm1[1000], cm2[1000];
void build_common(const string &w1, const string &w2) {
  int s1 = size(w1), s2 = size(w2);

  // initiate cm1[0] and cm2[0]
  for (int j = 0, c = w1[0], prev = 0; j < s2; ++j) {
    // set true starting from when w2 has w1[0]
    cm2[j] = prev = prev || w2[j] == c;
  }

  // does w2 have w1[0]?
  cm1[0] = cm2[s2 - 1];

  for (int i = 1; i < s1; ++i) {
    int c = w1[i], prev = cm2[0]; // when i is 1, cm2[0] means w2[0] == w1[0]
    cm2[0] =
        prev || c == w2[0]; // now cm2[0] means w2[0] == w1[0] || w2[0] == w1[1]

    // compare w1[i] with w2[1..]
    for (int j = 1; j < s2; ++j) {
      // prev++ when w2[j] = w1[i], otherwise prev = max(cm2[j], cm2[j - 1])
      // swap cm2[j] and prev
      swap(cm2[j], prev = (w2[j] == c) ? 1 + prev : max(cm2[j], cm2[j - 1]));
    }
    // cm2[s2 - 1] records the longest common subsequence between w1[0..i] and
    // w2
    cm1[i] = cm2[s2 - 1];
  }
}

void build_pals(const string &w, int ps[]) {
  int s = size(w);
  // the idea is to calculate lps[i]: the longest palindrome in w[i..(s-1)]
  // update the common (ps) by adding the longest possible palindrome in
  // w[i..(s-1)]
  // v = 2 * common[i] + lps[i] (i < s - 1) or v = 2 * common[i] (i == s - 1)
  vector<int> pp(s);
  pp[s - 1] = 1;   // the first round: pp[s - 1] is the longest palindrome in
                   // w[(s-1)..(s-1)]
  ps[s - 1] <<= 1; // 2 * ps[s - 1]

  if (s > 1 && ps[s - 2]) {
    ps[s - 2] = (ps[s - 2] << 1) + 1;
  }

  for (int i = s - 2; i > 0; --i) {
    pp[i] = 1;

    for (int j = i + 1, prev = 0; j < s; ++j) {
      swap(pp[j], prev = (w[i] == w[j]) ? 2 + prev : max(pp[j], pp[j - 1]));
    }
    // each time pp[s-1] records the longest palindrome in w[i..(s-1)]
    // ps[i - 1] cannot be 0 as the substring from another string must be
    // non-empty
    if (ps[i - 1]) {
      ps[i - 1] = (ps[i - 1] << 1) + pp[s - 1];
    }
  }
}

int longestPalindrome3(string word1, string word2) {
  reverse(begin(word2), end(word2));
  build_common(word1, word2);
  build_pals(word1, cm1);
  build_pals(word2, cm2);
  return max(*max_element(cm1, cm1 + size(word1)),
             *max_element(cm2, cm2 + size(word2)));
}

int main() {
  cout << longestPalindrome3("abc", "cba") << endl;
  cout << longestPalindrome("bb", "b") << endl;
  cout << longestPalindrome2("bb", "b") << endl;
  cout << longestPalindrome3("bb", "b") << endl;
  cout << longestPalindrome("cacbbf", "gcac") << endl;
  cout << longestPalindrome2("cacbbf", "gcac") << endl;
  cout << longestPalindrome3("cacbbf", "gcac") << endl;
  cout << longestPalindrome("cacbbca", "bcbac") << endl;
  cout << longestPalindrome2("cacbbca", "bcbac") << endl;
  cout << longestPalindrome3("cacbbca", "bcbac") << endl;
  cout << longestPalindrome("cacb", "cbba") << endl;
  cout << longestPalindrome2("cacb", "cbba") << endl;
  cout << longestPalindrome3("cacb", "cbba") << endl;
  cout << longestPalindrome("ab", "ab") << endl;
  cout << longestPalindrome2("ab", "ab") << endl;
  cout << longestPalindrome3("ab", "ab") << endl;
  cout << longestPalindrome("aa", "bb") << endl;
  cout << longestPalindrome2("aa", "bb") << endl;
  cout << longestPalindrome3("aa", "bb") << endl;
  cout << longestPalindrome("abcd", "abcd") << endl;
  cout << longestPalindrome2("abcd", "abcd") << endl;
  cout << longestPalindrome3("abcd", "abcd") << endl;
  cout << longestPalindrome("abcd", "dcba") << endl;
  cout << longestPalindrome2("abcd", "dcba") << endl;
  cout << longestPalindrome3("abcd", "dcba") << endl;
  cout << longestPalindrome("aabaa", "aabb") << endl;
  cout << longestPalindrome2("aabaa", "aabb") << endl;
  cout << longestPalindrome3("aabaa", "aabb") << endl;
  cout << longestPalindrome("abcde", "edcig") << endl;
  cout << longestPalindrome2("abcde", "edcig") << endl;
  cout << longestPalindrome3("abcde", "edcig") << endl;
  cout << longestPalindrome("igdcef", "edcig") << endl;
  cout << longestPalindrome2("igdcef", "edcig") << endl;
  cout << longestPalindrome3("igdcef", "edcig") << endl;
  return 0;
}