/*
Given a string S, return the “reversed” string where all characters that are not a letter stay in the same place, and all letters reverse their positions.

Example 1:

Input: "ab-cd"
Output: "dc-ba"

Example 2:

Input: "a-bC-dEf-ghIj"
Output: "j-Ih-gfE-dCba"

Example 3:

Input: "Test1ng-Leet=code-Q!"
Output: "Qedo1ct-eeLg=ntse-T!"

Note:
S.length <= 100
33 <= S[i].ASCIIcode <= 122
S doesn’t contain \ or "
*/

#include <stdio.h>
#include <string>
using namespace std;

bool isLetter(char c) {
  return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
}

void reverseOnlyLetters(string& str) {
  string reversed = "";
  for(auto& c: str) {
    if (isLetter(c))
      reversed.push_back(c);
  }
  int i = reversed.size();
  for(auto& c: str) {
    if (isLetter(c))
      c = reversed[--i];
  }
}

int main() {
  string str = "Test1ng-Leet=code-Q!";
  reverseOnlyLetters(str);
  printf("%s", str.c_str());
  return 0;
}