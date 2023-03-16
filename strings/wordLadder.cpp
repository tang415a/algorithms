/*Given two words (beginWord and endWord), and a dictionary's word list, find
the length of shortest transformation sequence from beginWord to endWord, such
that:

Only one letter can be changed at a time.
Each transformed word must exist in the word list. Note that beginWord is not a
transformed word. Note:

Return 0 if there is no such transformation sequence.
All words have the same length.
All words contain only lowercase alphabetic characters.
You may assume no duplicates in the word list.
You may assume beginWord and endWord are non-empty and are not the same.
Example 1:

Input:
beginWord = "hit",
endWord = "cog",
wordList = ["hot","dot","dog","lot","log","cog"]

Output: 5

Explanation: As one shortest transformation is "hit" -> "hot" -> "dot" -> "dog"
-> "cog", return its length 5.

Example 2:

Input:
beginWord = "hit"
endWord = "cog"
wordList = ["hot","dot","dog","lot","log"]

Output: 0

Explanation: The endWord "cog" is not in wordList, therefore no possible
transformation.
*/

#include <map>
#include <set>
#include <stdio.h>
#include <string>
#include <vector>

using namespace std;

int ladderLength(string beginWord, string endWord, vector<string> &wordList) {
  int l = beginWord.length();
  map<string, vector<string>> m;
  for (auto &word : wordList) {
    for (int i = 0; i < l; i++) {
      string key = word.substr(0, i) + "*" + word.substr(i + 1);
      if (m.find(key) != m.end())
        m[key].emplace_back(word);
      else
        m[key] = {word};
    }
  }
  set<string> visited;
  vector<string> found = {beginWord};
  int level = 1, start = 0;
  while (true) {
    int end = found.size();
    if (start >= end)
      break;
    for (; start < end; start++) {
      for (int i = 0; i < l; i++) {
        string key =
            found[start].substr(0, i) + "*" + found[start].substr(i + 1);
        if (m.find(key) != m.end()) {
          for (auto &f : m[key]) {
            if (visited.find(f) != visited.end())
              continue;
            if (f == endWord)
              return level + 1;
            visited.insert(f);
            found.emplace_back(f);
          }
        }
      }
    }
    level++;
  }
  return 0;
}

// Graph Node
struct GNode {
  int idx;
  vector<GNode *> neighbors;
};

int search(GNode *node, int target, vector<bool> &cache) {
  vector<GNode *> v = {node};
  for (int i = 0, depth = 1; i < v.size();) {
    int n = v.size();
    depth++;
    while (i < n) {
      for (auto pn : v[i]->neighbors) {
        if (pn->idx == target)
          return depth;
        if (!cache[pn->idx]) {
          cache[pn->idx] = true;
          v.push_back(pn);
        }
      }
      i++;
    }
  }
  return 0;
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

int ladderLength2(string beginWord, string endWord, vector<string> &wordList) {
  int target = -1, n = wordList.size();
  for (int i = 0; i < n; i++) {
    if (endWord == wordList[i]) {
      target = i;
      break;
    }
  }
  if (target == -1)
    return -1;
  wordList.emplace_back(beginWord);
  vector<GNode> graph;
  buildGraph(graph, wordList);
  vector<bool> cache(n + 1);
  cache[n] = true;
  return search(&graph[n], target, cache);
}

int main() {
  vector<string> wordList = {"hot", "dot", "dog", "lot", "log", "cog"};
  printf("length: %d\n", ladderLength("hit", "cog", wordList));
  printf("length: %d\n", ladderLength2("hit", "cog", wordList));
  return 0;
}