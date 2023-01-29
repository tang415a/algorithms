/*
Given a non negative integer number num. For every numbers i in the range 0 ≤ i ≤ num calculate the number of 1's in their binary representation and return them as an array.

Example 1:

Input: 2
Output: [0,1,1]
Example 2:

Input: 5
Output: [0,1,1,2,1,2]
Follow up:

It is very easy to come up with a solution with run time O(n*sizeof(integer)). But can you do it in linear time O(n) /possibly in a single pass?
Space complexity should be O(n).
Can you do it like a boss? Do it without using any builtin function like __builtin_popcount in c++ or in any other language.
*/

/*
0
1
1 2
1 2 2 3
1 2 2 3 2 3 3 4
1 2 2 3 2 3 3 4 2 3 3 4 3 4 4 5
1 ...
*/
#include <stdio.h>
#include <vector>
using namespace std;

vector<int> countBits(int num) {
  vector<int> res = {0};
  if (num == 0)
    return res;
  vector<int> base = {1};
  int cnt = 1, st = 0;
  while(cnt <= num) {
    if (!(cnt & (cnt - 1)))
      st = 0;
    else
      st++;
    res.push_back(base[st]);
    base.push_back(base[st] + 1);
    cnt++;
  }
  return res;
}

int main() {
  auto res = countBits(32);
  for(auto& r: res)
    printf("%d ", r);
  return 0;
}