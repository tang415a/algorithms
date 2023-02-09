/*
You are climbing a staircase. It takes n steps to reach the top.

Each time you can either climb 1 or 2 steps. In how many distinct ways can you
climb to the top?



Example 1:

Input: n = 2
Output: 2
Explanation: There are two ways to climb to the top.
1. 1 step + 1 step
2. 2 steps
Example 2:

Input: n = 3
Output: 3
Explanation: There are three ways to climb to the top.
1. 1 step + 1 step + 1 step
2. 1 step + 2 steps
3. 2 steps + 1 step


Constraints:

1 <= n <= 45
*/
#include <iostream>
using namespace std;

int calc(int n, int *p) {
  if (p[n - 1] > 0)
    return p[n - 1];
  return (p[n - 1] = calc(n - 1, p) + calc(n - 2, p));
}

int climbStairs(int n) {
  int p[45];
  memset(p, 0, sizeof(int) * 45);
  p[0] = 1;
  p[1] = 2;
  return calc(n, p);
}

// Fibnoacci
// F0 = 0
// F1 = 1
// Fn = 1/sqrt(5)*(((1+sqrt(5))/2)^n-((1-sqrt(5))/2)^n)
int main() {
  cout << climbStairs(2) << endl;
  cout << climbStairs(3) << endl;
  cout << climbStairs(45) << endl;
  return 0;
}