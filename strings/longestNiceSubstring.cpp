/*
A string s is nice if, for every letter of the alphabet that s contains, it
appears both in uppercase and lowercase. For example, "abABB" is nice because
'A' and 'a' appear, and 'B' and 'b' appear. However, "abA" is not because 'b'
appears, but 'B' does not.

Given a string s, return the longest substring of s that is nice. If there are
multiple, return the substring of the earliest occurrence. If there are none,
return an empty string.


Example 1:

Input: s = "YazaAay"
Output: "aAa"
Explanation: "aAa" is a nice string because 'A/a' is the only letter of the
alphabet in s, and both 'A' and 'a' appear. "aAa" is the longest nice substring.

Example 2:

Input: s = "Bb"
Output: "Bb"
Explanation: "Bb" is a nice string because both 'B' and 'b' appear. The whole
string is a substring.

Example 3:

Input: s = "c"
Output: ""
Explanation: There are no nice substrings.


Constraints:

1 <= s.length <= 100
s consists of uppercase and lowercase English letters.
*/

#include <iostream>
#include <string>
#include <unordered_set>

using namespace std;

string longestNiceSubstring(const string &s) {
  if (s.size() < 2)
    return "";
  unordered_set<char> st(begin(s), end(s));
  for (int i = 0; i < s.size(); i++) {
    if (st.find((char)toupper(s[i])) == end(st) ||
        st.find((char)tolower(s[i])) == end(st)) {
      string s1 = longestNiceSubstring(s.substr(0, i));
      string s2 = longestNiceSubstring(s.substr(i + 1));
      return s1.size() >= s2.size() ? s1 : s2;
    }
  }
  return s;
}

string longestNiceSubstring2(const string &s) {
  int n = s.length();
  if (n < 2)
    return "";
  bool c[256];
  memset(c, false, sizeof(bool) * 256);
  for (int i = 0; i < n; i++) {
    c[s[i]] = true;
  }
  vector<int> p = {-1};
  const char d = 'a' - 'A';
  for (int i = 0; i < n; i++) {
    char x = s[i] >= 'a' ? (s[i] - d) : (s[i] + d);
    if (!c[x]) {
      p.emplace_back(i);
    }
  }
  int k = p.size();
  if (k == 1)
    return s;
  p.emplace_back(n);
  string r;
  for (int i = 1, m = 0; i <= k; i++) {
    string y =
        longestNiceSubstring2(s.substr(p[i - 1] + 1, p[i] - p[i - 1] - 1));
    int l = y.length();
    if (m < l) {
      m = l;
      r = y;
    }
  }
  return r;
}

int main() {
  cout << longestNiceSubstring("YazaAay") << endl;
  cout << longestNiceSubstring("Bb") << endl;
  cout << longestNiceSubstring("c") << endl;
  cout << longestNiceSubstring2("YazaAay") << endl;
  cout << longestNiceSubstring2("Bb") << endl;
  cout << longestNiceSubstring2("c") << endl;
  return 0;
}
