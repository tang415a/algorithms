/*
Given a list of unique words, find all pairs of distinct indices (i, j) in the given list, so that the concatenation of the two words, i.e. words[i] + words[j] is a palindrome.

Example 1:

Input: ["abcd","dcba","lls","s","sssll"]
Output: [[0,1],[1,0],[3,2],[2,4]] 
Explanation: The palindromes are ["dcbaabcd","abcddcba","slls","llssssll"]
Example 2:

Input: ["bat","tab","cat"]
Output: [[0,1],[1,0]] 
Explanation: The palindromes are ["battab","tabbat"]
*/

#include <string>
#include <vector>
#include <map>
using namespace std;

bool isPalindrome(const string& one, int st, int ed){
  int total = st + ed;
  for(int i = st; ; i++) {
    if(total <= 2 * i)
      return true;
    if (one[total - i] != one[i])
      return false;
  }
}

vector<vector<int>> palindromePairs(const vector<string>& words) {
  vector<vector<int>> res;
  map<string, vector<int>> wordMap;
  for(int i = 0; i < words.size(); i++) {
    auto s = words[i];
    std::reverse(s.begin(), s.end());
    auto it = wordMap.find(s);
    if(it != wordMap.end()) {
      it->second.push_back(i);
    }
    else {
      wordMap[s] = {i}; 
    }
  }

  for(int i = 0; i < words.size(); i++) {
    auto& s = words[i];
    int st = 1, ed = s.size() - 1;
    while(st <= ed) {
      if (isPalindrome(s, st, ed)) {
        auto it = wordMap.find(s.substr(0, st));
        if (it != wordMap.end()) {
          for(auto& idx: it->second) {
            res.push_back({i, idx});
          }
        }
      }
      st++;
    }
    st = 0, ed = s.size() - 2;
    while(st <= ed) {
      if (isPalindrome(s, st, ed)) {
        auto it = wordMap.find(s.substr(ed + 1));
        if (it != wordMap.end()) {
          for(auto& idx: it->second) {
            res.push_back({idx, i});
          }
        }
      }
      ed--;
    }
    auto it = wordMap.find(s);
    if (it != wordMap.end()) {
      for(auto& idx: it->second) {
        if (idx != i)
          res.push_back({i, idx});
      }
    }
  }
  return res;
}

int main() {
  const vector<string> words = {"abcd","dcba","lls","s","sssll"}; 
  auto res = palindromePairs(words);
  printf("[");
  for(int i = 0; i < res.size(); i++){
    if(i != 0)
      printf(",");
    printf("[%d,%d]", res[i][0], res[i][1]);
  }
  printf("]");
  getchar();
  return 0;
}