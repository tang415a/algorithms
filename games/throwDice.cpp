/*
 Print out the possibility of the sum for throwing a certain number of dices. 
 Given the number of dices and the range of the numbers on each dice.

 void printAllPossibilities(int *p, int siz, int n)

 For example, there are six dices and the numbers on each dice are from 1 to 6.
 printAllPossibilites({1,2,3,4,5,6}, 6, 6);
 */

#include <stdio.h>
#include <math.h>

int numOf(int min, int max, int rc, int rn) {
  if (rn < 0 || rn * min > rc || rn * max < rc)
    return 0;
  if (rn == 0 && rc == 0)
    return 1;
  int res = 0;
  for (int i = min; i <= max; i++) {
    res += numOf(min, max, rc - i, rn - 1);
  }
  return res;
}

void printAllPossibilities(int *p, int siz, int n) {
  int min = p[0], max = p[0];
  for (int i = 1; i < siz; i++) {
    if (p[i] > max) max = p[i];
    if (p[i] < min) min = p[i];
  }

  int total = pow(max - min + 1, n);
  for (int i = min * n; i <= max * n; i++) {
    int res = numOf(min, max, i, n);
    printf("%d %f\n", i, res * 1.0 / total);
  }
}

int main() {
  printAllPossibilities({1,2,3,4,5,6}, 6, 6);
  return 0;
}