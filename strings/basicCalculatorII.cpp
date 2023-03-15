/*
Given a string s which represents an expression, evaluate this expression and
return its value.

The integer division should truncate toward zero.

You may assume that the given expression is always valid. All intermediate
results will be in the range of [-2^31, 2^31 - 1].

Note: You are not allowed to use any built-in function which evaluates strings
as mathematical expressions, such as eval().

Example 1:

Input: s = "3+2*2"
Output: 7

Example 2:

Input: s = " 3/2 "
Output: 1

Example 3:

Input: s = " 3+5 / 2 "
Output: 5

Constraints:

1 <= s.length <= 3 * 10^5
s consists of integers and operators ('+', '-', '*', '/') separated by some
number of spaces. s represents a valid expression. All the integers in the
expression are non-negative integers in the range [0, 2^31 - 1]. The answer is
guaranteed to fit in a 32-bit integer.
*/

#include <iostream>
#include <string>
#include <vector>

using namespace std;
int calc(int a, int b, char c) {
  switch (c) {
  case '+':
    return a + b;
  case '-':
    return a - b;
  case '*':
    return a * b;
  case '/':
    return a / b;
  default:
    throw 0;
  }
}

int calc(const vector<int> &operands, const vector<char> &opers) {
  if (operands.empty())
    return 0;
  int ans = operands[0];
  for (int i = 1, n = operands.size(); i < n; i++) {
    ans = calc(ans, operands[i], opers[i - 1]);
  }
  return ans;
}

int calculate(const string &s) {
  vector<int> operands;
  vector<char> opers;
  for (int i = 0, tmp = 0, n = s.length(); i <= n; i++) {
    switch (s[i]) {
    case '+':
    case '-':
    case '*':
    case '/':
    case 0:
      if (!opers.empty()) {
        if (char c = opers.back(); c == '*' || c == '/') {
          tmp = calc(operands.back(), tmp, c);
          opers.pop_back();
          operands.pop_back();
        }
      }
      operands.push_back(tmp);
      if (s[i] > 0)
        opers.push_back(s[i]);
      tmp = 0;
      break;
    default:
      if (s[i] >= '0' && s[i] <= '9') {
        // note that the parenthesis can prevent sign integer overflow
        tmp = tmp * 10 + (s[i] - '0');
      }
      break;
    }
  }
  return calc(operands, opers);
}

int readNextSuper(const string &s, int &k, int n) {
  int ans = 0;
  for (; k < n; k++) {
    switch (s[k]) {
    case '+':
    case '-':
    case '*':
    case '/':
      return ans;
    default:
      if (s[k] >= '0' && s[k] <= '9') {
        // note that the parenthesis can prevent sign integer overflow
        ans = ans * 10 + (s[k] - '0');
      }
      break;
    }
  }
  return ans;
}

int readNext(const string &s, int &k, int n) {
  int ans = 0;
  while (k < n) {
    switch (s[k]) {
    case '+':
    case '-':
      return ans;
    case '*':
      ans *= readNextSuper(s, ++k, n);
      break;
    case '/':
      ans /= readNextSuper(s, ++k, n);
      break;
    default:
      if (s[k] >= '0' && s[k] <= '9') {
        // note that the parenthesis can prevent sign integer overflow
        ans = ans * 10 + (s[k] - '0');
      }
      k++;
      break;
    }
  }
  return ans;
}

int calculate2(const string &s) {
  const int n = s.length();
  int k = 0, ans = readNext(s, k, n);
  while (k < n) {
    switch (s[k]) {
    case '+':
      ans += readNext(s, ++k, n);
      break;
    case '-':
      ans -= readNext(s, ++k, n);
      break;
    default:
      k++;
      break;
    }
  }
  return ans;
}

int calculate3(string s) {
  int ans = 0;
  int prevNum = 0;
  int currNum = 0;
  char op = '+';

  for (int i = 0; i < s.length(); ++i) {
    const char c = s[i];
    if (isdigit(c)) {
      // note that the parenthesis can prevent sign integer overflow
      currNum = currNum * 10 + (c - '0');
    }
    if (!isdigit(c) && !isspace(c) || i == s.length() - 1) {
      if (op == '+' || op == '-') {
        ans += prevNum;
        prevNum = op == '+' ? currNum : -currNum;
      } else if (op == '*') {
        prevNum *= currNum;
      } else if (op == '/') {
        prevNum /= currNum;
      }
      op = c;
      currNum = 0;
    }
  }

  return ans + prevNum;
}

int main() {
  cout << calculate("3+2*2") << endl;                               // 7
  cout << calculate(" 3/2 ") << endl;                               // 1
  cout << calculate(" 3+5 / 2 ") << endl;                           // 5
  cout << calculate(" 3+2 - 5 * 0 ") << endl;                       // 5
  cout << calculate("3 + 5 * 2 / 4 * 6 - 8 * 2 - 9") << endl;       // -10
  cout << calculate("2*3*2/4 - 5 * 2 / 4 * 6 - 8 * 2 - 9") << endl; // -34
  cout << calculate("3/4 * 2 - 5") << endl;                         // -5
  cout << "=========================================" << endl;
  cout << calculate2("3+2*2") << endl;                               // 7
  cout << calculate2(" 3/2 ") << endl;                               // 1
  cout << calculate2(" 3+5 / 2 ") << endl;                           // 5
  cout << calculate2(" 3+2 - 5 * 0 ") << endl;                       // 5
  cout << calculate2("3 + 5 * 2 / 4 * 6 - 8 * 2 - 9") << endl;       // -10
  cout << calculate2("2*3*2/4 - 5 * 2 / 4 * 6 - 8 * 2 - 9") << endl; // -34
  cout << calculate2("3/4 * 2 - 5") << endl;                         // -5
  return 0;
}