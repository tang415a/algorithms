/*
You are given a 0-indexed array of unique strings words.

A palindrome pair is a pair of integers (i, j) such that:

0 <= i, j < words.length,
i != j, and
words[i] + words[j] (the concatenation of the two strings) is a
palindrome
.
Return an array of all the palindrome pairs of words.

Example 1:

Input: words = ["abcd","dcba","lls","s","sssll"]
Output: [[0,1],[1,0],[3,2],[2,4]]
Explanation: The palindromes are ["abcddcba","dcbaabcd","slls","llssssll"]

Example 2:

Input: words = ["bat","tab","cat"]
Output: [[0,1],[1,0]]
Explanation: The palindromes are ["battab","tabbat"]
Example 3:

Input: words = ["a",""]
Output: [[0,1],[1,0]]
Explanation: The palindromes are ["a","a"]


Constraints:

1 <= words.length <= 5000
0 <= words[i].length <= 300
words[i] consists of lowercase English letters.
*/

#include <iostream>
#include <map>
#include <string>
#include <vector>

using namespace std;

bool isPalindrome(const string &one, int st, int ed) {
  int total = st + ed;
  for (int i = st;; i++) {
    if (total <= 2 * i)
      return true;
    if (one[total - i] != one[i])
      return false;
  }
}

vector<vector<int>> palindromePairs(const vector<string> &words) {
  vector<vector<int>> res;
  map<string, vector<int>> wordMap;
  int n = words.size();
  for (int i = 0; i < n; i++) {
    auto s = words[i];
    reverse(s.begin(), s.end());
    auto it = wordMap.find(s);
    if (it != wordMap.end()) {
      it->second.push_back(i);
    } else {
      wordMap[s] = {i};
    }
  }

  auto iter = wordMap.find("");
  if (iter != wordMap.end()) {
    for (int i = 0; i < n; i++) {
      if (!words[i].empty() && isPalindrome(words[i], 0, words[i].size() - 1)) {
        for (int idx: iter->second) {
          res.push_back({i, idx});
          res.push_back({idx, i});
        }
      }
    }
  }

  for (int i = 0; i < n; i++) {
    auto &s = words[i];
    int st = 1, ed = s.size() - 1;
    while (st <= ed) {
      if (isPalindrome(s, st, ed)) {
        auto it = wordMap.find(s.substr(0, st));
        if (it != wordMap.end()) {
          for (int idx : it->second) {
            res.push_back({i, idx});
          }
        }
      }
      st++;
    }
    st = 0, ed = s.size() - 2;
    while (st <= ed) {
      if (isPalindrome(s, st, ed)) {
        auto it = wordMap.find(s.substr(ed + 1));
        if (it != wordMap.end()) {
          for (int idx : it->second) {
            res.push_back({idx, i});
          }
        }
      }
      ed--;
    }
    auto it = wordMap.find(s);
    if (it != wordMap.end()) {
      for (int idx : it->second) {
        if (idx != i)
          res.push_back({i, idx});
      }
    }
  }
  return res;
}

int main() {
  auto res = palindromePairs({"abcd", "dcba", "lls", "s", "sssll"});
  cout << "[";
  for (int i = 0; i < res.size(); i++) {
    if (i != 0)
      cout << ",";
    cout << "[" << res[i][0] << "," << res[i][1] << "]";
  }
  cout << "]" << endl;
  res = palindromePairs({"bat", "tab", "cat"});
  cout << "[";
  for (int i = 0; i < res.size(); i++) {
    if (i != 0)
      cout << ",";
    cout << "[" << res[i][0] << "," << res[i][1] << "]";
  }
  cout << "]" << endl;
  res = palindromePairs({"aa", ""});
  cout << "[";
  for (int i = 0; i < res.size(); i++) {
    if (i != 0)
      cout << ",";
    cout << "[" << res[i][0] << "," << res[i][1] << "]";
  }
  cout << "]" << endl;
  return 0;
}