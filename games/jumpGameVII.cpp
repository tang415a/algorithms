/*
You are given a 0-indexed binary string s and two integers minJump and maxJump.
In the beginning, you are standing at index 0, which is equal to '0'. You can
move from index i to index j if the following conditions are fulfilled:

i + minJump <= j <= min(i + maxJump, s.length - 1), and
s[j] == '0'.
Return true if you can reach index s.length - 1 in s, or false otherwise.

Example 1:

Input: s = "011010", minJump = 2, maxJump = 3
Output: true
Explanation:
In the first step, move from index 0 to index 3.
In the second step, move from index 3 to index 5.
Example 2:

Input: s = "01101110", minJump = 2, maxJump = 3
Output: false


Constraints:

2 <= s.length <= 105
s[i] is either '0' or '1'.
s[0] == '0'
1 <= minJump <= maxJump < s.length
*/

#include <iostream>
using namespace std;

bool jump(string s, int minJump, int maxJump, bool *cache, int cur) {
  if (cur == s.length() - 1)
    return true;
  for (int i = minJump; i <= maxJump; ++i) {
    int n = cur + i;
    if (n >= s.length())
        return false;
    if (s[n] == '0' && !cache[n]) {
      cache[n] = true;
      if (jump(s, minJump, maxJump, cache, n))
        return true;
    }
  }
  return false;
}

bool canReach(string s, int minJump, int maxJump) {
  size_t siz = s.length();
  if (s[siz - 1] != '0')
    return false;
  bool *cache = new bool[siz];
  memset(cache, false, siz * sizeof(bool));
  cache[0] = true;
  bool ret = jump(s, minJump, maxJump, cache, 0);
  delete[] cache;
  return ret;
}

int main() {
  cout << canReach("011010", 2, 3) << endl;
  cout << canReach("01101110", 2, 3) << endl;
  return 0;
}