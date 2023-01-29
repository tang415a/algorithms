/*
Let's define a function f(s) over a non-empty string s, which calculates the frequency of the smallest character in s. For example, if s = "dcce" then f(s) = 2 because the smallest character is "c" and its frequency is 2.

Now, given string arrays queries and words, return an integer array answer, where each answer[i] is the number of words such that f(queries[i]) < f(W), where W is a word in words.

Example 1:

Input: queries = ["cbd"], words = ["zaaaz"]
Output: [1]
Explanation: On the first query we have f("cbd") = 1, f("zaaaz") = 3 so f("cbd") < f("zaaaz").

Example 2:

Input: queries = ["bbb","cc"], words = ["a","aa","aaa","aaaa"]
Output: [1,2]

Explanation: On the first query only f("bbb") < f("aaaa"). On the second query both f("aaa") and f("aaaa") are both > f("cc").

Constraints:

1 <= queries.length <= 2000
1 <= words.length <= 2000
1 <= queries[i].length, words[i].length <= 10
queries[i][j], words[i][j] are English lowercase letters.
*/

#include <stdio.h>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

int f(const string& s) {
  if (s.empty())
    throw 0;
  char min = s[0];
  int r = 1;
  for(int i = 1; i < s.size(); i++) {
    if (s[i] < min) {
      min = s[i];
      r = 1;
    }
    else if (s[i] == min)
      r++;
  }
  return r;
}

int binary_search(vector<int>& frequency, int v) {
  int siz = frequency.size(), low = 0, high = siz - 1, mid;

  while(low < high) {
    mid = (low + high) / 2;
    if (frequency[mid] <= v)
      low = mid + 1;
    else
      high = mid - 1;
  }

  if (frequency[low] <= v) low++;
  return siz - low;
}

vector<int> numSmallerByFrequency(vector<string>& queries, vector<string>& words) {
  vector<int> frequency;
  for(auto& s: words) {
    frequency.push_back(f(s));
  }
  sort(frequency.begin(), frequency.end());

  vector<int> res;
  for(auto& s: queries) {
    res.push_back(binary_search(frequency, f(s)));
  }
  return res;
}

int main() {
  vector<string> queries = {"bbb","cc"}, words = {"a","aa","aaa","aaaa"};
  auto r = numSmallerByFrequency(queries, words);
  for(auto& v: r)
    printf("%d ", v);
  return 0;
}