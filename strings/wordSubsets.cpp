/*
We are given two arrays A and B of words.  Each word is a string of lowercase letters.

Now, say that word b is a subset of word a if every letter in b occurs in a, including multiplicity.  For example, "wrr" is a subset of "warrior", but is not a subset of "world".

Now say a word a from A is universal if for every b in B, b is a subset of a.

Return a list of all universal words in A.  You can return the words in any order.

Example 1:

Input: A = ["amazon","apple","facebook","google","leetcode"], B = ["e","o"]
Output: ["facebook","google","leetcode"]

Example 2:

Input: A = ["amazon","apple","facebook","google","leetcode"], B = ["l","e"]
Output: ["apple","google","leetcode"]

Example 3:

Input: A = ["amazon","apple","facebook","google","leetcode"], B = ["e","oo"]
Output: ["facebook","google"]

Example 4:

Input: A = ["amazon","apple","facebook","google","leetcode"], B = ["lo","eo"]
Output: ["google","leetcode"]

Example 5:

Input: A = ["amazon","apple","facebook","google","leetcode"], B = ["ec","oc","ceo"]
Output: ["facebook","leetcode"]

Note:
1 <= A.length, B.length <= 10000
1 <= A[i].length, B[i].length <= 10
A[i] and B[i] consist only of lowercase letters.
All words in A[i] are unique: there isn’t i != j with A[i] == A[j].
*/

#include <stdio.h>
#include <vector>
#include <string>
using namespace std;

bool check(string& one, char* criterion) {
  char arr[26];
  memset(arr, 0, sizeof(char) * 26);
  for (auto& c: one) {
    if (criterion[c-'a'] == 0)
      continue;
    arr[c-'a']++;
  }
  for (int i = 0; i < 26; i++) {
    if (arr[i] < criterion[i])
      return false;
  }
  return true;
}

vector<string> wordSubsets(vector<string>& A, vector<string>& B) {
  char criterion[26];
  memset(criterion, 0, sizeof(char) * 26);
  for(auto& s: B) {
    char arr[26];
    memset(arr, 0, sizeof(char) * 26);
    for(auto& c: s) {
      arr[c-'a']++;
      if (arr[c-'a'] > criterion[c-'a'])
        criterion[c-'a'] = arr[c-'a'];
    }
  }
  vector<string> res;
  for(auto& s: A) {
    if (check(s, criterion))
      res.push_back(s);
  }
  return res;
}

int main() {
  vector<string> A = {"amazon","apple","facebook","google","leetcode"}, B = {"o","e"};
  auto r = wordSubsets(A, B);
  for(auto& s: r)
    printf("%s ", s);
  return 0;
}