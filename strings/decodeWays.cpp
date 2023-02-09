/*
A message containing letters from A-Z can be encoded into numbers using the
following mapping:

'A' -> "1"
'B' -> "2"
...
'Z' -> "26"

To decode an encoded message, all the digits must be grouped then mapped back
into letters using the reverse of the mapping above (there may be multiple
ways). For example, "11106" can be mapped into:

"AAJF" with the grouping (1 1 10 6)
"KJF" with the grouping (11 10 6)
Note that the grouping (1 11 06) is invalid because "06" cannot be mapped into
'F' since "6" is different from "06".

Given a string s containing only digits, return the number of ways to decode it.

The test cases are generated so that the answer fits in a 32-bit integer.

Example 1:

Input: s = "12"
Output: 2
Explanation: "12" could be decoded as "AB" (1 2) or "L" (12).

Example 2:

Input: s = "226"
Output: 3
Explanation: "226" could be decoded as "BZ" (2 26), "VF" (22 6), or "BBF" (2 2
6).

Example 3:

Input: s = "06"
Output: 0
Explanation: "06" cannot be mapped to "F" because of the leading zero ("6" is
different from "06").


Constraints:

1 <= s.length <= 100
s contains only digits and may contain leading zero(s).
*/

#include <iostream>
#include <string>

using namespace std;

int calc(const string &s, int i, int n, int *p) {
  if (p[i] >= 0)
    return p[i];
  if (s[i] == '0')
    return (p[i] = 0);
  if (i == n - 1)
    return (p[i] = 1);
  p[i] = calc(s, i + 1, n, p);
  if (s[i] == '1' || (s[i] == '2' && s[i + 1] < '7')) {
    p[i] += i < n - 2 ? calc(s, i + 2, n, p) : 1;
  }
  return p[i];
}

int numDecodings(const string &s) {
  int p[100];
  memset(p, -1, sizeof(int) * 100);
  return calc(s, 0, s.length(), p);
}

int main() {
  cout << numDecodings("12") << endl;
  cout << numDecodings("226") << endl;
  cout << numDecodings("06") << endl;
  cout << numDecodings("120") << endl;
  cout << numDecodings("130") << endl;
  cout << numDecodings("136") << endl;
  cout << numDecodings("30") << endl;
  cout << numDecodings("111111111111111111111111111111111111111111111") << endl;
  cout << numDecodings("111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111") << endl;
  return 0;
}