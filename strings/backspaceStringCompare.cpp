/*
Given two strings S and T, return if they are equal when both are typed into
empty text editors. # means a backspace character.

Example 1:

Input: S = "ab#c", T = "ad#c"
Output: true
Explanation: Both S and T become "ac".
Example 2:

Input: S = "ab##", T = "c#d#"
Output: true
Explanation: Both S and T become "".
Example 3:

Input: S = "a##c", T = "#a#c"
Output: true
Explanation: Both S and T become "c".
Example 4:

Input: S = "a#c", T = "b"
Output: false
Explanation: S becomes "c" while T becomes "b".
Note:

1 <= S.length <= 200
1 <= T.length <= 200
S and T only contain lowercase letters and '#' characters.
Follow up:

Can you solve it in O(N) time and O(1) space?
*/

#include <stdio.h>
#include <string>
using namespace std;

char getLastChar(string str, int &pos, int backspaces) {
  if (pos < 0)
    return '#';
  if (str[pos] != '#')
    return backspaces == 0 ? str[pos--]
                           : getLastChar(str, --pos, backspaces - 1);
  return getLastChar(str, --pos, backspaces + 1);
}

bool backspaceCompare(string S, string T) {
  int i = S.size() - 1, j = T.size() - 1;
  do {
    if (getLastChar(S, i, 0) != getLastChar(T, j, 0))
      return false;
  } while (i >= 0 || j >= 0);
  return true;
}

int main() {
  const string S = "a##c", T = "#a#c";
  printf("%d", backspaceCompare(S, T));
  return 0;
}