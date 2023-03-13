/*
A valid number can be split up into these components (in order):

A decimal number or an integer.
(Optional) An 'e' or 'E', followed by an integer.
A decimal number can be split up into these components (in order):

(Optional) A sign character (either '+' or '-').
One of the following formats:
One or more digits, followed by a dot '.'.
One or more digits, followed by a dot '.', followed by one or more digits.
A dot '.', followed by one or more digits.
An integer can be split up into these components (in order):

(Optional) A sign character (either '+' or '-').
One or more digits.
For example, all the following are valid numbers: ["2", "0089", "-0.1", "+3.14",
"4.", "-.9", "2e10", "-90E3", "3e+7", "+6e-1", "53.5e93", "-123.456e789"], while
the following are not valid numbers: ["abc", "1a", "1e", "e3", "99e2.5", "--6",
"-+3", "95a54e53"].

Given a string s, return true if s is a valid number.

Example 1:

Input: s = "0"
Output: true
Example 2:

Input: s = "e"
Output: false
Example 3:

Input: s = "."
Output: false

Constraints:

1 <= s.length <= 20
s consists of only English letters (both uppercase and lowercase), digits (0-9),
plus '+', minus '-', or dot '.'.
*/
#include <iostream>
#include <string>

using namespace std;

bool isDigit(char c) { return c >= '0' && c <= '9'; }

bool isInteger(const string &s, int k) {
  int n = s.length();
  if (k >= n)
    return false;
  if (s[k] == '+' || s[k] == '-') {
    k++;
  }
  if (k >= n)
    return false;
  while (k < n) {
    if (!isDigit(s[k]))
      return false;
    k++;
  }
  return true;
}

bool isDecimal(const string &s, int k) {
  int n = s.length();
  if (k >= n)
    return false;
  if (s[k] == '+' || s[k] == '-') {
    k++;
  }
  if (k >= n)
    return false;
  // next character could be '.'
  bool digits = false, requireDigits = false, dot = false;
  for (; k < n; k++) {
    if (isDigit(s[k])) {
      requireDigits = false;
      digits = true;
    } else if (s[k] == '.') {
      // dot can appear only once
      if (dot)
        return false;
      dot = true;
      // if no digit appears before '.'
      if (!digits) {
        requireDigits = true;
      }
    } else if (s[k] == 'E' || s[k] == 'e') {
      // no digits appear before...
      if (!digits)
        return false;
      return isInteger(s, k + 1);
    } else {
      return false;
    }
  }
  return !requireDigits;
}

bool isNumber(string s) { return isDecimal(s, 0) || isInteger(s, 0); }

int main() {
  string valid[] = {"-.9",   "0",     "2",       "0089",         "-0.1",
                    "+3.14", "4.",    "-.9",     "2e10",         "-90E3",
                    "3e+7",  "+6e-1", "53.5e93", "-123.456e789", "2.e3"};
  for (string s : valid) {
    if (!isNumber(s)) {
      cout << "err: " << s << "should be valid." << endl;
    }
  }
  string invalid[] = {"abc", "1a",   "1e",       "e3",     "99e2.5",
                      "--6", "-+3",  "95a54e53", "e",      ".",
                      "2.e", "-",    "+e-3",     "1.e2e3", "..2",
                      ".e2", "3.5.", "",         "5..2"};
  for (string s : invalid) {
    if (isNumber(s)) {
      cout << "err: " << s << "should be invalid." << endl;
    }
  }
  return 0;
}