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
    int j = c / 10, i = c - j * 10, k = m;
    while (k > 0 && i < st[k - 1]) {
      k--;
    }
    if (k < m) {
      int x = st[k] - i, z = st[k];
      st[k] = i;
      for (int y = m - 1; y >= 0; y--) {
        int a = st[m - 1 - y] - (y == k ? z : st[y]);
        if (d - a < 10 * x)
          return -1;
        x = 10 * x + a;
      }
      return d < x ? -1 : x + n;
    }
    st[m++] = i;
    c = j;
  }
  return -1;
}

int main() {
  cout << nextGreaterElement(12) << endl;         // 21
  cout << nextGreaterElement(21) << endl;         // -1
  cout << nextGreaterElement(1122) << endl;       // 1212
  cout << nextGreaterElement(147532) << endl;     // 152347
  cout << nextGreaterElement(230241) << endl;     // 230412
  cout << nextGreaterElement(2147483647) << endl; // -1
  cout << nextGreaterElement(2147483634) << endl; // 2147483643
  cout << nextGreaterElement(1999999999) << endl; // -1
  cout << nextGreaterElement(1299999999) << endl; // 1929999999
  return 0;
}