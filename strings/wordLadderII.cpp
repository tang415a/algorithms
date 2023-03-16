/*
A transformation sequence from word beginWord to word endWord using a dictionary
wordList is a sequence of words beginWord -> s1 -> s2 -> ... -> sk such that:

Every adjacent pair of words differs by a single letter.
Every si for 1 <= i <= k is in wordList. Note that beginWord does not need to be
in wordList.
sk == endWord.

Given two words, beginWord and endWord, and a dictionary wordList, return all
the shortest transformation sequences from beginWord to endWord, or an empty
list if no such sequence exists. Each sequence should be returned as a list of
the words [beginWord, s1, s2, ..., sk].

Example 1:

Input: beginWord = "hit", endWord = "cog", wordList =
["hot","dot","dog","lot","log","cog"]
Output:
[["hit","hot","dot","dog","cog"],["hit","hot","lot","log","cog"]]
Explanation:
There are 2 shortest transformation sequences: "hit" -> "hot" -> "dot" -> "dog"
-> "cog" "hit" -> "hot" -> "lot" -> "log" -> "cog"

Example 2:

Input: beginWord = "hit", endWord = "cog", wordList =
["hot","dot","dog","lot","log"]
Output: []
Explanation: The endWord "cog" is not in wordList, therefore there is no valid
transformation sequence.

Constraints:

1 <= beginWord.length <= 5
endWord.length == beginWord.length
1 <= wordList.length <= 500
wordList[i].length == beginWord.length
beginWord, endWord, and wordList[i] consist of lowercase English letters.
beginWord != endWord
All the words in wordList are unique.
The sum of all shortest transformation sequences does not exceed 10^5.
*/

#include <iostream>
#include <string>
#include <vector>

using namespace std;

// Graph Node
struct GNode {
  int idx = -1;
  int prev = -1;
  vector<GNode *> neighbors;
};

void search(vector<vector<string>> &res, vector<GNode> &graph, int source,
            int target, vector<bool> &cache, const vector<string> &wordList) {
  vector<GNode *> v = {&graph[source]};
  for (int i = 0; i < v.size();) {
    int n = v.size();
    bool found = false;
    while (i < n) {
      for (GNode *pn : v[i]->neighbors) {
        if (pn->idx == target) {
          found = true;
          vector<string> path;
          path.emplace_back(wordList[target]);
          path.emplace_back(wordList[v[i]->idx]);
          pn = v[i];
          while (pn->prev != -1) {
            pn = &graph[pn->prev];
            path.emplace_back(wordList[pn->idx]);
          }
          reverse(begin(path), end(path));
          res.emplace_back(path);
        } else if (!cache[pn->idx]) {
          cache[pn->idx] = true;
          pn->prev = v[i]->idx;
          v.push_back(pn);
        }
      }
      i++;
    }
    if (found)
      return;
  }
}

bool oneCharDiff(const string &left, const string &right) {
  int diff = 0;
  for (int i = 0, l = left.length(); i < l; ++i) {
    if (left[i] != right[i] && ++diff > 1) {
      return false;
    }
  }
  return diff == 1;
}

void buildGraph(vector<GNode> &graph, const vector<string> &wordList) {
  size_t s = wordList.size();
  graph.resize(s);
  for (size_t i = 0; i < s; ++i) {
    graph[i].idx = i;
  }
  for (size_t i = 0; i < s - 1; ++i) {
    for (size_t j = i + 1; j < s; ++j) {
      const auto &left = wordList[graph[i].idx];
      const auto &right = wordList[graph[j].idx];
      if (oneCharDiff(left, right)) {
        graph[i].neighbors.emplace_back(&graph[j]);
        graph[j].neighbors.emplace_back(&graph[i]);
      }
    }
  }
}

vector<vector<string>> findLadders(string beginWord, string endWord,
                                   vector<string> &wordList) {
  vector<vector<string>> res;
  int target = -1, n = wordList.size();
  for (int i = 0; i < n; i++) {
    if (endWord == wordList[i]) {
      target = i;
      break;
    }
  }
  if (target == -1)
    return res;
  wordList.emplace_back(beginWord);
  vector<GNode> graph;
  buildGraph(graph, wordList);
  vector<bool> cache(n + 1);
  cache[n] = true;
  search(res, graph, n, target, cache, wordList);
  return res;
}

int main() {
  vector<string> wordList = {"hot", "dot", "dog", "lot", "log", "cog"};
  auto r = findLadders("hit", "cog", wordList);
  for (auto &l : r) {
    for (auto &s : l) {
      cout << s << " ";
    }
    cout << endl;
  }
  cout << endl;
  wordList = {"hot", "dot", "dog", "lot", "log"};
  r = findLadders("hit", "cog", wordList);
  for (auto &l : r) {
    for (auto &s : l) {
      cout << s << " ";
    }
    cout << endl;
  }
  cout << endl;
  return 0;
}