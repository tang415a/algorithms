/*
Calculate the sum of two integers a and b, but you are not allowed to use the operator + and -.

Example 1:

Input: a = 1, b = 2
Output: 3
Example 2:

Input: a = -2, b = 3
Output: 1
*/

#include <stdio.h>

int getSum(int a, int b) {
  int mask = 0x1;
  bool carry = false;
  int res = 0;
  do {
    int bit1 = a & mask, bit2 = b & mask;
    if (bit1 > 0 && bit2 > 0) {
      if (carry)
        res |= mask;
      else
        carry = true;
    }
    else if (bit1 == 0 && bit2 == 0) {
      if (carry) {
        res |= mask;
        carry = false;
      }
    }
    else if (!carry)
      res |= mask;
    mask <<= 1;
  } while (mask > 0);
  return res;
}

int main() {
  printf("%d\n", getSum(367, 209));
  printf("%d\n", getSum(-2, 3));
  getchar();
  return 0;
}
