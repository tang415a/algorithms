/*
You are given a string s, an integer k, a letter letter, and an integer
repetition.

Return the lexicographically smallest subsequence of s of length k that has the
letter letter appear at least repetition times. The test cases are generated so
that the letter appears in s at least repetition times.

A subsequence is a string that can be derived from another string by deleting
some or no characters without changing the order of the remaining characters.

A string a is lexicographically smaller than a string b if in the first position
where a and b differ, string a has a letter that appears earlier in the alphabet
than the corresponding letter in b.

Example 1:

Input: s = "leet", k = 3, letter = "e", repetition = 1
Output: "eet"
Explanation: There are four subsequences of length 3 that have the letter 'e'
appear at least 1 time:
- "lee" (from "leet")
- "let" (from "leet")
- "let" (from "leet")
- "eet" (from "leet")
The lexicographically smallest subsequence among them is "eet".

Example 2:

example-2
Input: s = "leetcode", k = 4, letter = "e", repetition = 2
Output: "ecde"
Explanation: "ecde" is the lexicographically smallest subsequence of length 4
that has the letter "e" appear at least 2 times.

Example 3:

Input: s = "bb", k = 2, letter = "b", repetition = 2
Output: "bb"
Explanation: "bb" is the only subsequence of length 2 that has the letter "b"
appear at least 2 times.


Constraints:

1 <= repetition <= k <= s.length <= 5 * 10^4
s consists of lowercase English letters.
letter is a lowercase English letter, and appears in s at least repetition
times.
*/

#include <iostream>
#include <string>
using namespace std;

string smallestSubsequence(const string &s, int k, char letter,
                           int repetition) {
  string ret;
  if (k == repetition) {
    ret.resize(k, letter);
    return ret;
  }
  const int n = s.length();
  int r = 0;
  for (int i = 0; i < n; ++i) {
    if (s[i] == letter)
      ++r;
  }
  ret.resize(k);
  int m = 0;
  for (int i = 0; i < n; i++) {
    // if remaining letters are not all required
    while (m > 0 && k - m < n - i && s[i] < ret[m - 1]) {
      if (ret[m - 1] == letter) {
        // we cannot lose this `letter`
        if (r == repetition)
          break;
        repetition++;
      }
      m--;
    }
    if (m >= k) {
      if (s[i] == letter) {
        // if we require all the remaining `letter`s, add all of them in
        if (r == repetition) {
          // find first non `letter` letter
          while (ret[--k] == letter)
            ;
          while (repetition-- > 0) {
            ret[k--] = letter;
          }
          break;
        }
        r--;
      }
      // skip the characters outside k
      continue;
    }
    if (s[i] == letter) {
      r--;
      repetition--;
    }
    ret[m++] = s[i];
  }
  return ret;
}

void expect(const string &a, const string &b) {
  if (a != b) {
    cout << "err: " << a << " is not equal to " << b << endl;
  }
}

int main() {
  expect(smallestSubsequence("leet", 3, 'e', 1), "eet");
  expect(smallestSubsequence("leetcode", 4, 'e', 2), "ecde");
  expect(smallestSubsequence("bb", 2, 'b', 2), "bb");
  expect(smallestSubsequence("leetc", 3, 'e', 2), "eec");
  expect(smallestSubsequence("leetecea", 3, 'e', 2), "ece");
  expect(smallestSubsequence("tscbabea", 3, 'a', 2), "aba");
  expect(smallestSubsequence("tscbaa", 3, 'a', 2), "baa");
  expect(smallestSubsequence("aabaa", 3, 'a', 2), "aaa");
  expect(smallestSubsequence("aaaaa", 3, 'a', 2), "aaa");
  expect(smallestSubsequence("abcdecfa", 3, 'c', 2), "acc");
  expect(smallestSubsequence("abcdbcfaceadces", 4, 'c', 2), "aacc");
  expect(smallestSubsequence("bbcabcffceadcecs", 4, 'c', 2), "aacc");
  expect(smallestSubsequence("bbcabcffceadces", 4, 'c', 2), "abcc");
  return 0;
}