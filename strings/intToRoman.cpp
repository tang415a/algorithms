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
For example, 2 is written as II in Roman numeral, just two one's added together.
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
Given an integer, convert it to a roman numeral.

Example 1:

Input: num = 3
Output: "III"
Explanation: 3 is represented as 3 ones.

Example 2:

Input: num = 58
Output: "LVIII"
Explanation: L = 50, V = 5, III = 3.

Example 3:

Input: num = 1994
Output: "MCMXCIV"
Explanation: M = 1000, CM = 900, XC = 90 and IV = 4.

Constraints:

1 <= num <= 3999
*/
#include <iostream>
#include <string>
#include <vector>

using namespace std;

string intToRoman(int num) {
  vector<vector<string>> v = {
      {"I", "II", "III", "IV", "V", "VI", "VII", "VIII", "IX"},
      {"X", "XX", "XXX", "XL", "L", "LX", "LXX", "LXXX", "XC"},
      {"C", "CC", "CCC", "CD", "D", "DC", "DCC", "DCCC", "CM"},
      {"M", "MM", "MMM"}};
  string res;
  int i = 0;
  while (num > 0) {
    int r = num / 10, d = num - r * 10;
    if (d > 0)
      res = v[i][d - 1] + res;
    i++;
    num = r;
  }
  return res;
}

// two better approaches below
string intToRoman2(int num) {
  string ans = "";
  string map[] = {"M",  "CM", "D",  "CD", "C",  "XC", "L",
                  "XL", "X",  "IX", "V",  "IV", "I"};
  int nums[] = {1000, 900, 500, 400, 100, 90, 50, 40, 10, 9, 5, 4, 1};
  for (int i = 0; i < 13; i++) {
    while (num >= nums[i]) {
      ans += map[i];
      num -= nums[i];
    }
  }
  return ans;
}

string intToRoman3(int num) {
  int binler = num / 1000;
  int yuzler = num / 100 - binler * 10;
  int onlar = num / 10 - binler * 100 - yuzler * 10;
  int birler = num - binler * 1000 - yuzler * 100 - onlar * 10;

  string result;
  while (binler--)
    result.push_back('M');

  if (yuzler == 9) {
    result.push_back('C');
    result.push_back('M');
  } else if (yuzler >= 5) {
    result.push_back('D');
    while (yuzler-- - 5)
      result.push_back('C');
  } else if (yuzler == 4) {
    result.push_back('C');
    result.push_back('D');
  } else {
    while (yuzler--)
      result.push_back('C');
  }

  if (onlar == 9) {
    result.push_back('X');
    result.push_back('C');
  } else if (onlar >= 5) {
    result.push_back('L');
    while (onlar-- - 5)
      result.push_back('X');
  } else if (onlar == 4) {
    result.push_back('X');
    result.push_back('L');
  } else {
    while (onlar--)
      result.push_back('X');
  }

  if (birler == 9) {
    result.push_back('I');
    result.push_back('X');
  } else if (birler >= 5) {
    result.push_back('V');
    while (birler-- - 5)
      result.push_back('I');
  } else if (birler == 4) {
    result.push_back('I');
    result.push_back('V');
  } else {
    while (birler--)
      result.push_back('I');
  }
  return result;
}

string intToRoman4(int num) {
  int binler = num / 1000;
  int yuzler = num / 100 - binler * 10;
  int onlar = num / 10 - binler * 100 - yuzler * 10;
  int birler = num - binler * 1000 - yuzler * 100 - onlar * 10;

  string result;
  while (binler--)
    result.push_back('M');

  auto f = [](string &r, int i, char a, char b, char c) {
    if (i == 9) {
      r.push_back(a);
      r.push_back(b);
    } else if (i >= 5) {
      r.push_back(c);
      while (i-- - 5)
        r.push_back(a);
    } else if (i == 4) {
      r.push_back(a);
      r.push_back(c);
    } else {
      while (i--)
        r.push_back(a);
    }
  };

  f(result, yuzler, 'C', 'M', 'D');
  f(result, onlar, 'X', 'C', 'L');
  f(result, birler, 'I', 'X', 'V');
  return result;
}

int main() {
  cout << intToRoman(3) << endl;
  cout << intToRoman(58) << endl;
  cout << intToRoman(1994) << endl;
  cout << intToRoman(80) << endl;
  cout << intToRoman4(3) << endl;
  cout << intToRoman4(58) << endl;
  cout << intToRoman4(1994) << endl;
  cout << intToRoman4(80) << endl;
  return 0;
}