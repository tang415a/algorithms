/*
Given two integers A and B, check if A is greater than B， but you are not allowed to use the operator >, < or ?, or if statement.
*/

#include <stdio.h>

bool greaterThan(int A, int B) {
  int subtract = A - B, mask = 1 << (sizeof(int) - 1);
  return (subtract != 0 && (subtract & mask) == 0);
}

int main() {
  printf("%d\n", greaterThan(2, 1));
  printf("%d\n", greaterThan(1, 1));
  printf("%d\n", greaterThan(0, 1));
  getchar();
  return 0;
}