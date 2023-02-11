/*
Given a positive integer n, find the smallest integer which has exactly the same
digits existing in the integer n and is greater in value than n. If no such
positive integer exists, return -1.

Note that the returned integer should fit in 32-bit integer, if there is a valid
answer but it does not fit in 32-bit integer, return -1.

Example 1:

Input: n = 12
Output: 21

Example 2:

Input: n = 21
Output: -1

Constraints:

1 <= n <= 2^31 - 1
*/

#include <iostream>
using namespace std;

int nextGreaterElement(int n) {
  int d = 0x7fffffff - n, m = 0, c = n;
  int st[10];
  while (c > 0) {
    int j = c / 10, i = c - j * 10, k = m - 1;
    while (k >= 0 && i >= st[k]) {
      k--;
    }
    if (k >= 0) {
      int base1 = 1, x = 0;
      for (; x < k; x++) {
        base1 *= 10;
      }
      int base2 = base1;
      for (; x < m; x++) {
        base2 *= 10;
      }
      x = (base2 - base1) * (st[k] - i);
      return d < x ? -1 : x + n;
    }
    st[m++] = i;
    c = j;
  }
  return -1;
}

int main() {
  cout << nextGreaterElement(12) << endl;
  cout << nextGreaterElement(21) << endl;
  cout << nextGreaterElement(1122) << endl;
  cout << nextGreaterElement(2147483647) << endl;
  cout << nextGreaterElement(2147483634) << endl;
  return 0;
}