// Write a function to find out how many times one appears from 1 to N
// e.g. f(1) = 1, (1)
//      f(10) = 2, (1, 10)
//      f(21) = 13, (1, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 21)

#include <stdio.h>
#include <math.h>

int findOnes(int n) {
  int base = 1, res = 0, index = 0;
  while(n >= base) {
    int digit = (n / base) % 10;
    if (digit > 1)
      res += digit * index * base / 10 + base;
    else if (digit == 1)
      res += index * base / 10 + n % base + 1;    
    base *= 10;
    index++;
  }
  return res;
}

int main() {
  printf("%d", findOnes(21));
  return 0;
}