/*
Given a string s and an integer k, return the length of the longest substring of
s such that the frequency of each character in this substring is greater than or
equal to k.

Example 1:

Input: s = "aaabb", k = 3
Output: 3
Explanation: The longest substring is "aaa", as 'a' is repeated 3 times.

Example 2:

Input: s = "ababbc", k = 2
Output: 5
Explanation: The longest substring is "ababb", as 'a' is repeated 2 times and
'b' is repeated 3 times.

Constraints:

1 <= s.length <= 10^4
s consists of only lowercase English letters.
1 <= k <= 10^5
*/

#include <iostream>
#include <string>

using namespace std;

void longestSubString(int &ans, const string &s, int k, int start, int end) {
  if (end - start <= ans) {
    return;
  }
  int arr[26] = {0}, i = start;
  for (; i < end; i++) {
    arr[s[i] - 'a']++;
  }
  for (i = 0; i < 26; i++) {
    if (arr[i] > 0 && arr[i] < k)
      break;
  }
  if (i == 26) {
    ans = end - start;
    return;
  }
  int j = start;
  for (i = start; i < end; i++) {
    if (arr[s[i] - 'a'] < k) {
      if (ans < i - j) {
        longestSubString(ans, s, k, j, i);
      }
      j = i + 1;
      if (end - j <= ans) {
        break;
      }
    }
  }
  if (ans < end - j)
    longestSubString(ans, s, k, j, end);
}

int longestSubstring(const string &s, int k) {
  const int n = s.length();
  if (k == 1)
    return n;
  int ans = 0;
  longestSubString(ans, s, k, 0, n);
  return ans;
}

int main() {
  cout << longestSubstring("aaabb", 3) << endl;
  cout << longestSubstring("ababbc", 2) << endl;
  cout << longestSubstring("ababbcc", 2) << endl;
  return 0;
}