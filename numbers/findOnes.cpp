// Write a function to find out how many times one appears from 1 to N
// e.g. f(1) = 1, (1)
//      f(10) = 2, (1, 10)
//      f(21) = 13, (1, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 21)

#include <iostream>
using namespace std;

// hints:
// f(10^n) = n * 10^(n - 1) + 1
// f(10^n-1) = n * 10^(n - 1)
// f(a00) = a * f(99) + 10^2 (where a > 1)
// f(1ab) = f(99) + 1 + ab + f(ab)
// f(abc) = f(a00) + f(bc) (where a > 1)
// in the following code, f(10^n-1) is calculated by `index * base / 10` where
// the index is n and the base is 10^n

int findOnes(int n) {
  int base = 1, res = 0, index = 0;
  while (n >= base) {
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

int findOnes2(int n) {
  int base = 1, res = 0, index = 0;
  while (n >= base) {
    int quotient = n / base;
    int remain = n - quotient * base;
    int digit = quotient - quotient / 10 * 10;
    if (digit > 1)
      res += digit * index * base / 10 + base;
    else if (digit == 1)
      res += index * base / 10 + remain + 1;
    base *= 10;
    index++;
  }
  return res;
}

int main() {
  cout << findOnes(21) << endl;
  cout << findOnes2(21) << endl;
  return 0;
}