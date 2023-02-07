/*
A string is considered beautiful if it satisfies the following conditions:

Each of the 5 English vowels ('a', 'e', 'i', 'o', 'u') must appear at least once
in it. The letters must be sorted in alphabetical order (i.e. all 'a's before
'e's, all 'e's before 'i's, etc.). For example, strings "aeiou" and
"aaaaaaeiiiioou" are considered beautiful, but "uaeio", "aeoiu", and "aaaeeeooo"
are not beautiful.

Given a string word consisting of English vowels, return the length of the
longest beautiful substring of word. If no such substring exists, return 0.

A substring is a contiguous sequence of characters in a string.


Example 1:

Input: word = "aeiaaioaaaaeiiiiouuuooaauuaeiu"
Output: 13
Explanation: The longest beautiful substring in word is "aaaaeiiiiouuu" of
length 13. Example 2:

Input: word = "aeeeiiiioooauuuaeiou"
Output: 5
Explanation: The longest beautiful substring in word is "aeiou" of length 5.
Example 3:

Input: word = "a"
Output: 0
Explanation: There is no beautiful substring, so return 0.


Constraints:

1 <= word.length <= 5 * 10^5
word consists of characters 'a', 'e', 'i', 'o', and 'u'.
*/
#include <iostream>
#include <vector>
using namespace std;
int longestBeautifulSubstring(const string &word) {
  int charFreq = 0, currLen = 0, maxLen = 0;
  for (int i = 1, n = word.length(); i < n; ++i) {
    if (word[i] == word[i - 1]) {
      currLen++;
    } else if (word[i] > word[i - 1]) {
      currLen++;
      charFreq++;
    } else {
      charFreq = 1;
      currLen = 1;
    }

    if (charFreq == 5 && currLen > maxLen) {
      maxLen = currLen;
    }
  }
  return maxLen;
}

int main() {
  cout << longestBeautifulSubstring("aeiaaioaaaaeiiiiouuuooaauuaeiu") << endl;
  cout << longestBeautifulSubstring("aeeeiiiioooauuuaeiou") << endl;
  cout << longestBeautifulSubstring("a") << endl;
  return 0;
}