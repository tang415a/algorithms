/*
Roman numerals are represented by seven different symbols: I, V, X, L, C, D and
M.

Symbol       Value
I             1
V             5
X             10
L             50
C             100
D             500
M             1000
For example, 2 is written as II in Roman numeral, just two ones added together.
12 is written as XII, which is simply X + II. The number 27 is written as XXVII,
which is XX + V + II.

Roman numerals are usually written largest to smallest from left to right.
However, the numeral for four is not IIII. Instead, the number four is written
as IV. Because the one is before the five we subtract it making four. The same
principle applies to the number nine, which is written as IX. There are six
instances where subtraction is used:

I can be placed before V (5) and X (10) to make 4 and 9.
X can be placed before L (50) and C (100) to make 40 and 90.
C can be placed before D (500) and M (1000) to make 400 and 900.
Given a roman numeral, convert it to an integer.

Example 1:

Input: s = "III"
Output: 3
Explanation: III = 3.
Example 2:

Input: s = "LVIII"
Output: 58
Explanation: L = 50, V= 5, III = 3.
Example 3:

Input: s = "MCMXCIV"
Output: 1994
Explanation: M = 1000, CM = 900, XC = 90 and IV = 4.

Constraints:

1 <= s.length <= 15
s contains only the characters ('I', 'V', 'X', 'L', 'C', 'D', 'M').
It is guaranteed that s is a valid roman numeral in the range [1, 3999].
*/
#include <iostream>
#include <map>
#include <string>

using namespace std;

int romanToInt(const string &s) {
  int res = 0;
  for (int i = 0, n = s.length(); i < n; i++) {
    switch (s[i]) {
    case 'I':
      if (s[i + 1] == 'V') {
        res += 4;
        i++;
      } else if (s[i + 1] == 'X') {
        res += 9;
        i++;
      } else {
        res++;
      }
      break;
    case 'V':
      res += 5;
      break;
    case 'X':
      if (s[i + 1] == 'L') {
        res += 40;
        i++;
      } else if (s[i + 1] == 'C') {
        res += 90;
        i++;
      } else {
        res += 10;
      }
      break;
    case 'L':
      res += 50;
      break;
    case 'C':
      if (s[i + 1] == 'D') {
        res += 400;
        i++;
      } else if (s[i + 1] == 'M') {
        res += 900;
        i++;
      } else {
        res += 100;
      }
      break;
    case 'D':
      res += 500;
      break;
    case 'M':
      res += 1000;
      break;
    }
  }
  return res;
}

int romanToInt2(string s) {
  int ans = 0;
  for (int i = 0; i < s.size(); i++) {
    char ch = s[i];
    switch (ch) {
    case 'I':
      if (s[i + 1] == 'V' || s[i + 1] == 'X') {
        ans = ans - 1;
        break;
      }
      ans = ans + 1;
      break;
    case 'V':
      ans = ans + 5;
      break;
    case 'X':
      if (s[i + 1] == 'L' || s[i + 1] == 'C') {
        ans = ans - 10;
        break;
      }
      ans = ans + 10;
      break;
    case 'L':
      if (s[i + 1] == 'D' || s[i + 1] == 'M') {
        ans = ans - 50;
        break;
      }
      ans = ans + 50;
      break;
    case 'C':
      if (s[i + 1] == 'D' || s[i + 1] == 'M') {
        ans = ans - 100;
        break;
      }
      ans = ans + 100;
      break;
    case 'D':
      ans = ans + 500;
      break;
    case 'M':
      ans = ans + 1000;
      break;
    }
  }
  return ans;
}

int main() {
  cout << romanToInt("III") << endl;
  cout << romanToInt("LVIII") << endl;
  cout << romanToInt("MCMXCIV") << endl;
  return 0;
}