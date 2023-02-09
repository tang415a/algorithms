/*
Given an integer n, return the number of structurally unique BST's (binary
search trees) which has exactly n nodes of unique values from 1 to n.

Example 1:

Input: n = 3
Output: 5
Explanation:
1           1             2             3           3
  3           2         1   3         2           1
2               3                   1               2

Example 2:

Input: n = 1
Output: 1

Constraints:

1 <= n <= 19
*/

#include <iostream>
using namespace std;

int calNum(int n, int *p) {
  if (p[n - 1] > 0)
    return p[n - 1];
  p[n - 1] += 2 * calNum(n - 1, p);
  for (int i = 1; i < n - 1; ++i) {
    p[n - 1] += calNum(i, p) * calNum(n - i - 1, p);
  }
  return p[n - 1];
}

int numTrees(int n) {
  int p[19];
  memset(p, 0, sizeof(int) * 19);
  p[0] = 1;
  return calNum(n, p);
}

int main() {
  cout << numTrees(19) << endl;
  cout << numTrees(3) << endl;
  cout << numTrees(2) << endl;
  cout << numTrees(1) << endl;
  return 0;
}