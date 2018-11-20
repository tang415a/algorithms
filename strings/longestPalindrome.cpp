/*
Given a string which consists of lowercase or uppercase letters, find the length of the longest palindromes that can be built with those letters.

This is case sensitive, for example "Aa" is not considered a palindrome here.

Note:
Assume the length of given string will not exceed 1,010.

Example:

Input:
"abccccdd"

Output:
7

Explanation:
One longest palindrome that can be built is "dccaccd", whose length is 7.
*/

#include <stdio.h>
#include <string.h>

using namespace std;

int longestPalindrome(char* str) {
  if (str == NULL)
    return 0;
  int len = strlen(str);
  if (len == 0)
    return 0;
  int frequency[52] = {0};
  for(int i = 0; i < len; i++) {
    if (str[i] >= 'A' && str[i] <= 'Z')
      frequency[str[i] - 'A']++;
    else if (str[i] >= 'a' && str[i] <= 'z')
      frequency[str[i] - 'a' + 26]++;
  }
  int res = 0;
  bool hasOdd = false;
  for(auto& f: frequency){
    if (f & 0x1) {
      hasOdd = true;
      res += (f - 1);
    }
    else
      res += f;
  }
  return hasOdd ? 1 + res : res;
}

int main() {
  printf("%d\n", longestPalindrome("abccccdd"));
  return 0;
}