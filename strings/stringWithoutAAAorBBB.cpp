/*
Given two integers A and B, return any string S such that:

S has length A + B and contains exactly A 'a' letters, and exactly B 'b' letters;
The substring 'aaa' does not occur in S;
The substring 'bbb' does not occur in S.


Example 1:

Input: A = 1, B = 2
Output: "abb"
Explanation: "abb", "bab" and "bba" are all correct answers.
Example 2:

Input: A = 4, B = 1
Output: "aabaa"
*/

#include "stdio.h"
#include <string>
using namespace std;

string strWithout3a3b(int A, int B) {
  string res = "";
  int i = 0, j = 0;
  if (A < 3 && B < 3) {
      while (++i <= A) res += "a";
      while (++j <= B) res += "b";
      return res;
  }
  int max = A > B ? A : B,
      min = A > B ? B : A;
  int spaces = (max - 1) / 2;
  if (min < spaces)
      throw 0;
  i = 0;
  j = 0;
  int over = min - spaces;
  while (i < max) {
      for (int k = 0; k < 2; k++) {
          if (++i <= max) res += A > B ? "a" : "b";
          else break;
      }
      if (++j <= min) {
          res += A > B ? "b" : "a";
          if (--over >= 0 && ++j <= min)
              res += A > B ? "b" : "a";
      }
  }
  return res;
}

int main() {
  printf("%s\n", strWithout3a3b(8, 5).c_str());
  return 0;
}