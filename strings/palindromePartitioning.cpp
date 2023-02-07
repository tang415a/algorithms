/*
Given a string s, partition s such that every substring of the partition is a
palindrome. Return all possible palindrome partitioning of s.


Example 1:

Input: s = "aab"
Output: [["a","a","b"],["aa","b"]]

Example 2:

Input: s = "a"
Output: [["a"]]


Constraints:

1 <= s.length <= 16
s contains only lowercase English letters.
*/

#include <iostream>
#include <string>
#include <vector>

using namespace std;

void doPartition(vector<vector<string>> &v, vector<string> &r, const string &s,
                 bool **p, int i, int n) {
  if (i >= n) {
    v.push_back(r);
    return;
  }
  for (int j = i; j < n; j++) {
    if (p[i][j]) {
      r.push_back(s.substr(i, j - i + 1));
      doPartition(v, r, s, p, j + 1, n);
      r.pop_back();
    }
  }
}

vector<vector<string>> partition(const string &s) {
  int n = s.length();
  bool **p = new bool *[n];
  for (int i = 0; i < n; i++) {
    p[i] = new bool[n];
    p[i][i] = true;
  }
  for (int i = 0; i < n - 1; i++) {
    p[i][i + 1] = s[i] == s[i + 1] ? true : false;
  }
  for (int i = 3; i <= n; i++) {
    for (int j = 0; j <= n - i; j++) {
      p[j][j + i - 1] = p[j + 1][j + i - 2] && s[j] == s[j + i - 1];
    }
  }
  vector<vector<string>> v;
  vector<string> r;
  doPartition(v, r, s, p, 0, n);
  for (int i = 0; i < n; i++)
    delete[] p[i];
  delete[] p;
  return v;
}

int main() {
  auto v = partition("aab");
  for (auto &l : v) {
    for (auto &s : l) {
      cout << s << " ";
    }
    cout << endl;
  }
  cout << endl;
  v = partition("a");
  for (auto &l : v) {
    for (auto &s : l) {
      cout << s << " ";
    }
    cout << endl;
  }
  cout << endl;
  v = partition("aaaaaa");
  for (auto &l : v) {
    for (auto &s : l) {
      cout << s << " ";
    }
    cout << endl;
  }
  return 0;
}