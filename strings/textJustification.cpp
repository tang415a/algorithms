/*
Given an array of strings words and a width maxWidth, format the text such that
each line has exactly maxWidth characters and is fully (left and right)
justified.

You should pack your words in a greedy approach; that is, pack as many words as
you can in each line. Pad extra spaces ' ' when necessary so that each line has
exactly maxWidth characters.

Extra spaces between words should be distributed as evenly as possible. If the
number of spaces on a line does not divide evenly between words, the empty slots
on the left will be assigned more spaces than the slots on the right.

For the last line of text, it should be left-justified, and no extra space is
inserted between words.

Note:

A word is defined as a character sequence consisting of non-space characters
only. Each word's length is guaranteed to be greater than 0 and not exceed
maxWidth. The input array words contains at least one word.


Example 1:

Input: words = ["This", "is", "an", "example", "of", "text", "justification."],
maxWidth = 16

Output:
[
   "This    is    an",
   "example  of text",
   "justification.  "
]
Example 2:

Input: words = ["What","must","be","acknowledgment","shall","be"], maxWidth = 16
Output:
[
  "What   must   be",
  "acknowledgment  ",
  "shall be        "
]
Explanation: Note that the last line is "shall be    " instead of "shall be",
because the last line must be left-justified instead of fully-justified. Note
that the second line is also left-justified because it contains only one word.

Example 3:

Input: words =
["Science","is","what","we","understand","well","enough","to","explain","to","a",
"computer.","Art","is","everything","else","we","do"],
maxWidth = 20

Output:
[
  "Science  is  what we",
  "understand      well",
  "enough to explain to",
  "a  computer.  Art is",
  "everything  else  we",
  "do                  "
]

Constraints:

1 <= words.length <= 300
1 <= words[i].length <= 20
words[i] consists of only English letters and symbols.
1 <= maxWidth <= 100
words[i].length <= maxWidth
*/

#include <iostream>
#include <string>
#include <vector>

using namespace std;

vector<string> fullJustify(const vector<string> &words, int maxWidth) {
  vector<string> ans;
  for (int i = 0, n = words.size(); i < n;) {
    int j = 0, k = 0, m = maxWidth;
    while (i + k < n && j + words[i + k].length() <= m) {
      j += words[i + k].length();
      k++;
      m--;
    }
    if (k == 0)
      break;
    i += k;
    string s;
    if (i < n) {
      int ns = maxWidth - j;
      if (k == 1) {
        s += words[i - 1];
        while (ns-- > 0) {
          s += " ";
        }
      } else {
        int x = ns / (k - 1), y = ns - x * (k - 1);
        string spaces(x, ' ');
        for (int z = 0; z < k - 1; z++) {
          s += words[i - k + z] + spaces;
          if (z < y) {
            s += " ";
          }
        }
        s += words[i - 1];
      }
    } else {
      int ns = maxWidth - j;
      for (int z = 0; z < k - 1; z++) {
        s += words[i - k + z] + " ";
        ns--;
      }
      s += words[i - 1];
      s += string(ns, ' ');
    }
    ans.emplace_back(s);
  }
  return ans;
}

int main() {
  auto r = fullJustify(
      {"This", "is", "an", "example", "of", "text", "justification."}, 16);
  for (auto &s : r) {
    cout << s << endl;
    if (s.length() != 16)
      return 1;
  }
  r = fullJustify({"What", "must", "be", "acknowledgment", "shall", "be"}, 16);
  for (auto &s : r) {
    cout << s << endl;
    if (s.length() != 16)
      return 1;
  }
  r = fullJustify({"Science", "is", "what", "we", "understand", "well",
                   "enough", "to", "explain", "to", "a", "computer.", "Art",
                   "is", "everything", "else", "we", "do"},
                  20);
  for (auto &s : r) {
    cout << s << endl;
    if (s.length() != 20)
      return 1;
  }
  r = fullJustify({"Dot", "dog", "git", "tag."}, 4);
  for (auto &s : r) {
    cout << s << endl;
    if (s.length() != 4)
      return 1;
  }
  r = fullJustify({"town", "yawn", "foot", "tag."}, 4);
  for (auto &s : r) {
    cout << s << endl;
    if (s.length() != 4)
      return 1;
  }
  return 0;
}