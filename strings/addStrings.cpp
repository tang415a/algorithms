/*
Given two non-negative integers num1 and num2 represented as string, return the sum of num1 and num2.

Note:

1. The length of both num1 and num2 is < 5100.
2. Both num1 and num2 contains only digits 0-9.
3. Both num1 and num2 does not contain any leading zero.
4. You must not use any built-in BigInteger library or convert the inputs to integer directly.
*/

#include "stdio.h"
#include <string>
using namespace std;

string addStrings(string num1, string num2) {
  string& shortStr = (num1.size() < num2.size() ? num1 : num2);
  string& longStr = (num1.size() < num2.size() ? num2 : num1);

  int longSize = longStr.size(), shortSize= shortStr.size();

  char carry = 0;
  string result = "";
  for (int i = longSize - 1, j = shortSize - 1; i >= 0; i--, j--) {
    char digit = j >= 0 ? longStr[i] - '0' + shortStr[j] - '0' + carry : longStr[i] - '0' + carry;
    carry = digit / 10;
    digit = digit % 10 + '0';
    result = digit + result;
  }
  if (carry)
    result = '1' + result;

  return result;
}

int main() {
  printf(addStrings("92345", "12789").c_str());
  return 0;
}