// Find how many bits with 1 for an integer.
// e.g. for 15 (0b1111), it returns 4.

#include <stdio.h>

int oneBits(int num) {
  int res = 0;
  while(num) {
    num &= (num - 1);
    res++;
  }
  return res;
}

int main() {
  const int num = 15;
  printf("%d bits with 1 in %d", oneBits(num), num);
  return 0;
}