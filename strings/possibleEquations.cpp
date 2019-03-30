/*
Given an array equations of strings that represent relationships between variables, each string equations[i] has length 4 and takes one of two different forms: "a==b" or "a!=b".  Here, a and b are lowercase letters (not necessarily different) that represent one-letter variable names.

Return true if and only if it is possible to assign integers to variable names so as to satisfy all the given equations.

Example 1:

Input: ["a==b","b!=a"]
Output: false
Explanation: If we assign say, a = 1 and b = 1, then the first equation is satisfied, but not the second.  There is no way to assign the variables to satisfy both equations.

Example 2:

Input: ["b==a","a==b"]
Output: true
Explanation: We could assign a = 1 and b = 1 to satisfy both equations.

Example 3:

Input: ["a==b","b==c","a==c"]
Output: true

Example 4:

Input: ["a==b","b!=c","c==a"]
Output: false
Example 5:

Input: ["c==c","b==d","x!=z"]
Output: true

Note:

1 <= equations.length <= 500
equations[i].length == 4
equations[i][0] and equations[i][3] are lowercase letters
equations[i][1] is either '=' or '!'
equations[i][2] is '='
*/

#include <string>
#include <vector>
using namespace std;

void insertEqual(vector<vector<char>>& equals, char a, char b) {
  for(auto& e: equals) {
    bool found_a = false, found_b = false;
    for(auto& c: e) {
      if (c == a)
        found_a = true;
      else if (c == b)
        found_b = true;
    }
    if (found_a && found_b)
      return;
    if (found_a && !found_b) {
      e.push_back(b);
      return;
    }
    if (!found_a && found_b) {
      e.push_back(a);
      return;
    }
  }
  equals.push_back({a, b});
}

bool foundEqual(vector<vector<char>> equals, char a, char b) {
  for(auto& e: equals) {
    bool found_a = false, found_b = false;
    for(auto& c: e) {
      if (c == a)
        found_a = true;
      else if (c == b)
        found_b = true;
    }
    if (found_a && found_b)
      return true;
  }
  return false;
}

bool equationPossible(const vector<string> &equations) {
  vector<vector<char>> equals;
  for (auto& s: equations) {
    if (s[1] == '=') { // equal
      insertEqual(equals, s[0], s[3]);
    }
  }
  for (auto& s: equations) {
    if (s[1] == '!') { // non equal
      if (s[0] == s[3] || foundEqual(equals, s[0], s[3]))
        return false;
    }
  }
  return true;
}

int main() {
  vector<string> equations = {"c==c","b==d","x!=z"};
  if (equationPossible(equations))
    printf("They are possible.");
  else
    printf("They are not possible.");
  getchar();  
  return 0;
}