/*
You are given a very large integer n, represented as a string,​​​​​​
and an integer digit x. The digits in n and the digit x are in the inclusive
range [1, 9], and n may represent a negative number.

You want to maximize n's numerical value by inserting x anywhere in the decimal
representation of n​​​​​​. You cannot insert x to the left of the
negative sign.

For example, if n = 73 and x = 6, it would be best to insert it between 7 and 3,
making n = 763. If n = -55 and x = 2, it would be best to insert it before the
first 5, making n = -255. Return a string representing the maximum value of
n​​​​​​ after the insertion.



Example 1:

Input: n = "99", x = 9
Output: "999"
Explanation: The result is the same regardless of where you insert 9.
Example 2:

Input: n = "-13", x = 2
Output: "-123"
Explanation: You can make n one of {-213, -123, -132}, and the largest of those
three is -123.


Constraints:

1 <= n.length <= 105
1 <= x <= 9
The digits in n​​​ are in the range [1, 9].
n is a valid representation of an integer.
In the case of a negative n,​​​​​​ it will begin with '-'.

*/

#include <iostream>
#include <string>
using namespace std;

string maxValue(string n, int x) {
  bool isNegative = n[0] == '-';
  int i = isNegative ? 1 : 0;
  const int len = n.length();
  if (isNegative) {
    for (; i < len; ++i) {
      if (n[i] - '0' > x)
        break;
    }
  } else {
    for (; i < len; ++i) {
      if (n[i] - '0' < x)
        break;
    }
  }
  char c = static_cast<char>('0' + x);
  if (i == len)
    n.push_back(c);
  else
    n.insert(n.begin() + i, c);
  return n;
}

int main() {
  cout << maxValue("99", 9) << endl;
  cout << maxValue("839", 4) << endl;
  cout << maxValue("39", 4) << endl;
  cout << maxValue("-13", 2) << endl;
  cout << maxValue("-73", 2) << endl;
  cout << maxValue("-123", 4) << endl;
  return 0;
}