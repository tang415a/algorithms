/*
Given a binary string s ​​​​​without leading zeros, return
true​​​ if s contains at most one contiguous segment of ones. Otherwise,
return false.

Example 1:

Input: s = "1001"
Output: false
Explanation: The ones do not form a contiguous segment.
Example 2:

Input: s = "110"
Output: true


Constraints:

1 <= s.length <= 100
s[i]​​​​ is either '0' or '1'.
s[0] is '1'.
*/

#include <iostream>
#include <string>

using namespace std;

bool checkOnesSegment(const string &s) { return s.find("01") == string::npos; }

bool checkOnesSegment1(const string &s) {
  bool flag = true;
  for (int i = 0, n = s.length(); i < n; ++i) {
    if (s[i] == '0')
      flag = false;
    else {
      if (flag == false)
        return false;
    }
  }
  return true;
}

int main() {
  cout << checkOnesSegment("1001") << endl;
  cout << checkOnesSegment("110") << endl;
  return 0;
}
