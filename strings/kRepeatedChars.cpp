/*
Find the length of the longest substring T of a given string (consists of lowercase letters only) such that every character in T appears no less than k times.

Example 1:

Input:
s = "aaabb", k = 3

Output:
3

The longest substring is "aaa", as 'a' is repeated 3 times.
Example 2:

Input:
s = "ababbc", k = 2

Output:
5

The longest substring is "ababb", as 'a' is repeated 2 times and 'b' is repeated 3 times.
*/

#include <stdio.h>
#include <string.h>

int longestRepeated(const char* s, int len, int k) {
  int frequency[26] = {0}, i;
  for (i = 0; i < len; i++)
    frequency[s[i] - 'a']++;

  int res = 0, st = 0, tmp;
  for (i = 0; i < len; i++) {
    if (frequency[s[i] - 'a'] < k) {
      if (st < i) {
        tmp = longestRepeated(s + st, i - st, k);
        if (res < tmp) res = tmp;
      }
      st = i + 1;
    }
  }
  if (st == 0)
    return len;
  if (st < len) {
    tmp = longestRepeated(s + st, len - st, k);
    if (res < tmp) res = tmp;
  }
  return res;
}

int longestRepeated(const char* s, int k) {
  return longestRepeated(s, strlen(s), k);
}

int main() {
  printf("%d\n", longestRepeated("abacbbcdedeee", 3));
  return 0;
}