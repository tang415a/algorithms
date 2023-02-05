/*
 Print out the possibility of the sum for throwing a certain number of dices.
 Given the number of dices and the range of the numbers on each dice.

 void printAllPossibilities(int m, int n), where m means the dice number range
 is from 1 to m and n is the number of dices.

 For example, there are six dices and the numbers on each dice are from 1 to 6.
 printAllPossibilites(6, 6);
 */

#include <iostream>
using namespace std;

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

void printAllPossibilities(int m, int n) {
  int total = 1;
  for (int i = 0; i < n; i++)
    total *= m;
  for (int i = n; i <= m * n; i++) {
    int res = numOf(1, m, i, n);
    cout << i << " " << res * 1.0 / total << endl;
  }
}

void iterate(int n, int m, int base, int min, int *p) {
  if (n <= 0) {
    p[base - min]++;
    return;
  }
  for (int i = 0; i < m; i++) {
    base += (i + 1);
    iterate(n - 1, m, base, min, p);
    base -= (i + 1);
  }
}

void printAllPossibilities2(int m, int n) {
  int s = (m - 1) * n + 1;
  int *p = new int[s];
  memset(p, 0, sizeof(int) * s);
  iterate(n, m, 0, n, p);
  int total = 1;
  for (int i = 0; i < n; ++i)
    total *= m;
  for (int i = 0; i < s; ++i) {
    cout << i + n << " " << static_cast<float>(p[i]) / total << endl;
  }
  delete[] p;
}

int main() {
  printAllPossibilities(6, 6);
  printAllPossibilities2(6, 6);
  return 0;
}