/*
You are given two identical eggs and you have access to a building with n floors
labeled from 1 to n.

You know that there exists a floor f where 0 <= f <= n such that any egg dropped
at a floor higher than f will break, and any egg dropped at or below floor f
will not break.

In each move, you may take an unbroken egg and drop it from any floor x (where 1
<= x <= n). If the egg breaks, you can no longer use it. However, if the egg
does not break, you may reuse it in future moves.

Return the minimum number of moves that you need to determine with certainty
what the value of f is.



Example 1:

Input: n = 2
Output: 2
Explanation: We can drop the first egg from floor 1 and the second egg from
floor 2. If the first egg breaks, we know that f = 0. If the second egg breaks
but the first egg didn't, we know that f = 1. Otherwise, if both eggs survive,
we know that f = 2. Example 2:

Input: n = 100
Output: 14
Explanation: One optimal strategy is:
- Drop the 1st egg at floor 9. If it breaks, we know f is between 0 and 8. Drop
the 2nd egg starting from floor 1 and going up one at a time to find f within 8
more drops. Total drops is 1 + 8 = 9.
- If the 1st egg does not break, drop the 1st egg again at floor 22. If it
breaks, we know f is between 9 and 21. Drop the 2nd egg starting from floor 10
and going up one at a time to find f within 12 more drops. Total drops is 2 + 12
= 14.
- If the 1st egg does not break again, follow a similar process dropping the 1st
egg from floors 34, 45, 55, 64, 72, 79, 85, 90, 94, 97, 99, and 100. Regardless
of the outcome, it takes at most 14 drops to determine f.


Constraints:

1 <= n <= 1000
*/

#include <iostream>
using namespace std;

int twoEggDrop(int n) {
  int i = 1;
  while (i * (i + 1) < 2 * n) {
    ++i;
  }
  return i;
}

int twoEggDrop2(int n) {
  int c = 1, i = 1;
  while (c < n) {
    c += ++i;
  }
  return i;
}

int twoEggDrop3(int n) {
  int c = 1, i = 1;
  while (c < n) {
    c += i;
    i++;
  }
  return c == n ? i : i - 1;
}

int main() {
  cout << twoEggDrop(1) << endl;
  cout << twoEggDrop2(1) << endl;
  cout << twoEggDrop3(1) << endl;
  cout << twoEggDrop(2) << endl;
  cout << twoEggDrop2(2) << endl;
  cout << twoEggDrop3(2) << endl;
  cout << twoEggDrop(3) << endl;
  cout << twoEggDrop2(3) << endl;
  cout << twoEggDrop3(3) << endl;
  cout << twoEggDrop(10) << endl;
  cout << twoEggDrop2(10) << endl;
  cout << twoEggDrop3(10) << endl;
  cout << twoEggDrop(100) << endl;
  cout << twoEggDrop2(100) << endl;
  cout << twoEggDrop3(100) << endl;
  cout << twoEggDrop(1000) << endl;
  cout << twoEggDrop2(1000) << endl;
  cout << twoEggDrop3(1000) << endl;
  return 0;
}