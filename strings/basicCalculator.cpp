/*
Given a string s representing a valid expression, implement a basic calculator
to evaluate it, and return the result of the evaluation.

Note: You are not allowed to use any built-in function which evaluates strings
as mathematical expressions, such as eval().

Example 1:

Input: s = "1 + 1"
Output: 2

Example 2:

Input: s = " 2-1 + 2 "
Output: 3

Example 3:

Input: s = "(1+(4+5+2)-3)+(6+8)"
Output: 23

Constraints:

1 <= s.length <= 3 * 10^5
s consists of digits, '+', '-', '(', ')', and ' '.
s represents a valid expression.
'+' is not used as a unary operation (i.e., "+1" and "+(2 + 3)" is invalid).
'-' could be used as a unary operation (i.e., "-1" and "-(2 + 3)" is valid).
There will be no two consecutive operators in the input.
Every number and running calculation will fit in a signed 32-bit integer.
*/

#include <iostream>
#include <string>

using namespace std;

int readNext(const string &s, int &k, int n);

int calculate(const string &s, int k, int n) {
  int ans = readNext(s, k, n);
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

int readNext(const string &s, int &k, int n) {
  int ans = 0;
  while (k < n) {
    switch (s[k]) {
    case '+':
    case '-':
      return ans;
    case '(': {
      int j = k + 1, p = 1;
      while (j < n) {
        if (s[j] == ')') {
          if (--p == 0)
            break;
        } else if (s[j] == '(') {
          p++;
        }
        j++;
      }
      ans = calculate(s, ++k, j);
      k = j + 1;
      return ans;
    }
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

int calculate(const string &s) { return calculate(s, 0, s.length()); }

#include <stack>

// a better solution
int calculate2(const string &s) {
  stack<int> st;
  int ans = 0;
  int sign = 1;
  for (int i = 0, n = s.length(); i < n; i++) {
    switch (s[i]) {
    case '+':
      sign = 1;
      break;
    case '-':
      sign = -1;
      break;
    case '(':
      // push the operand to the stack
      st.push(ans);
      // push the sign
      st.push(sign);
      ans = 0;
      sign = 1;
      break;
    case ')':
      // the top of stack should be the sign
      ans *= st.top();
      st.pop();
      // do the op with the operand
      ans += st.top();
      st.pop();
      break;
    default:
      if (isdigit(s[i])) {
        int tmp = 0;
        while (isdigit(s[i])) {
          // note that the parenthesis can prevent sign integer overflow
          tmp = tmp * 10 + (s[i] - '0');
          i++;
        }
        // do the op for the current number with ans
        ans += tmp * sign;
        i--;
      }
      break;
    }
  }
  return ans;
}

int main() {
  cout << calculate("- 1") << endl;                 // -1
  cout << calculate("1 + 1") << endl;               // 2
  cout << calculate(" 2-1 + 2 ") << endl;           // 3
  cout << calculate("(1+(4+5+2)-3)+(6+8)") << endl; // 23
  cout << calculate("5-(-3-5)") << endl;            // 13
  cout << calculate("5-(-3+5)-2") << endl;          // 1
  cout << calculate("-2+ 1") << endl;               // -1

  cout << calculate2("- 1") << endl;                 // -1
  cout << calculate2("1 + 1") << endl;               // 2
  cout << calculate2(" 2-1 + 2 ") << endl;           // 3
  cout << calculate2("(1+(4+5+2)-3)+(6+8)") << endl; // 23
  cout << calculate2("5-(-3-5)") << endl;            // 13
  cout << calculate2("5-(-3+5)-2") << endl;          // 1
  cout << calculate2("-2+ 1") << endl;               // -1
  return 0;
}
