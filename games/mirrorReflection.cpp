/*
There is a special square room with mirrors on each of the four walls.  Except for the southwest corner, there are receptors on each of the remaining corners, numbered 0, 1, and 2.

The square room has walls of length p, and a laser ray from the southwest corner first meets the east wall at a distance q from the 0th receptor.

Return the number of the receptor that the ray meets first.  (It is guaranteed that the ray will meet a receptor eventually.)

Example 1:
Input: p = 2, q = 1
Output: 2
Explanation: The ray meets receptor 2 the first time it gets reflected back to the left wall.

Note:

1 <= p <= 1000
0 <= q <= p
*/
#include <stdio.h>

int gcd(int p, int q) {
  if (q == 0)
    return p;
  return gcd(q, p % q);
}

int getReceptor(int p, int q) {
  int s = p * q / gcd(p, q);
  if ((s / q) & 0x1) {
    if ((s / p) & 0x1)
      return 1;
    return 0;
  }
  return 2;
}

int main() {
  printf("%d\n", getReceptor(5, 1));
  printf("%d\n", getReceptor(5, 2));
  printf("%d\n", getReceptor(4, 1));
  return 0;
}