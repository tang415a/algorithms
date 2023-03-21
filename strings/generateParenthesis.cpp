/*
Given n pairs of parentheses, write a function to generate all combinations of
well-formed parentheses.

Example 1:

Input: n = 3
Output: ["((()))","(()())","(())()","()(())","()()()"]
Example 2:

Input: n = 1
Output: ["()"]

Constraints:

1 <= n <= 8
*/

#include <iostream>
#include <string>
#include <vector>

using namespace std;

void solve(vector<string> &ans, string &s, int i, int j) {
  if (i == 0 && j == 0) {
    ans.emplace_back(s);
    return;
  }
  if (i > 0) {
    s.push_back('(');
    solve(ans, s, i - 1, j + 1);
    s.pop_back();
  }
  if (j > 0) {
    s.push_back(')');
    solve(ans, s, i, j - 1);
    s.pop_back();
  }
}

vector<string> generateParenthesis(int n) {
  vector<string> ans;
  string s;
  solve(ans, s, n, 0);
  return ans;
}

int main() {
  auto r = generateParenthesis(3);
  string comma;
  for (auto &s : r) {
    cout << comma << s;
    if (comma.empty())
      comma = ", ";
  }
  cout << endl;
  r = generateParenthesis(1);
  comma = "";
  for (auto &s : r) {
    cout << comma << s;
    if (comma.empty())
      comma = ", ";
  }
  cout << endl;
  return 0;
}
