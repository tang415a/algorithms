/*
Given a non negative integer number num. For every numbers i in the range 0 ≤ i
≤ num calculate the number of 1's in their binary representation and return them
as an array.

Example 1:

Input: 2
Output: [0,1,1]
Example 2:

Input: 5
Output: [0,1,1,2,1,2]
Follow up:

It is very easy to come up with a solution with run time O(n*sizeof(integer)).
But can you do it in linear time O(n) /possibly in a single pass? Space
complexity should be O(n). Can you do it like a boss? Do it without using any
builtin function like __builtin_popcount in c++ or in any other language.
*/

/*
Given an integer n, return an array ans of length n + 1 such that for each i (0
<= i <= n), ans[i] is the number of 1's in the binary representation of i.



Example 1:

Input: n = 2
Output: [0,1,1]
Explanation:
0 --> 0
1 --> 1
2 --> 10

Example 2:

Input: n = 5
Output: [0,1,1,2,1,2]
Explanation:
0 --> 0
1 --> 1
2 --> 10
3 --> 11
4 --> 100
5 --> 101


Constraints:

0 <= n <= 10^5


Follow up:

It is very easy to come up with a solution with a runtime of O(n log n). Can you
do it in linear time O(n) and possibly in a single pass? Can you do it without
using any built-in function (i.e., like __builtin_popcount in C++)?
*/

#include <iostream>
#include <vector>
using namespace std;
/*
0
1
1 2
1 2 2 3
1 2 2 3 2 3 3 4
1 2 2 3 2 3 3 4 2 3 3 4 3 4 4 5
1 ...
*/
vector<int> countBits(int num) {
  vector<int> res(num + 1, 0);
  if (num == 0)
    return res;
  vector<int> base(num + 1, 1);
  int cnt = 1, st = 0;
  while (cnt <= num) {
    if (!(cnt & (cnt - 1)))
      st = 0;
    else
      st++;
    res[cnt] = base[st];
    base[cnt] = base[st] + 1;
    cnt++;
  }
  return res;
}

/*
                            0
                            1
              1                               2
        1           2               2                 3
    1       2     2     3       2       3         3       4
  1   2   2   3 2   3 3   4   2   3   3    4    3   4   4   5
1 ...
*/
vector<int> countBits2(int n) {
  vector<int> bits(n + 1);

  for (int i = 0; i <= n; i++) {
    bits[i] = bits[i >> 1] + i % 2;
  }

  return bits;
}

int main() {
  auto res = countBits(32);
  for (int r : res)
    cout << r << " ";
  cout << endl;
  res = countBits2(32);
  for (int r : res)
    cout << r << " ";
  return 0;
}