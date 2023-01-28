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
-> "cog", return its length 5. Example 2:

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
  string str;
  vector<GNode *> neighbours;
};

bool moveNext(GNode *node, const string &target, set<string> &cache,
              int &depth) {
  if (node->str == target)
    return true;
  for (auto pn : node->neighbours) {
    if (cache.find(pn->str) == cache.end()) {
      cache.insert(pn->str);
      depth++;
      if (moveNext(pn, target, cache, depth))
        return true;
      depth--;
    }
  }
  return false;
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

void initGraph(GNode *&graph, const string &beginWord,
               const vector<string> &wordList) {
  size_t s = wordList.size();
  graph = new GNode[s + 1];
  graph[0].str = beginWord;
  for (size_t i = 1; i <= s; ++i) {
    graph[i].str = wordList[i - 1];
  }
  for (size_t i = 0; i < s; ++i) {
    for (size_t j = i + 1; j < s + 1; ++j) {
      if (oneCharDiff(graph[i].str, graph[j].str)) {
        graph[i].neighbours.emplace_back(graph + j);
        graph[j].neighbours.emplace_back(graph + i);
      }
    }
  }
}

int ladderLength2(string beginWord, string endWord, vector<string> &wordList) {
  GNode *graph = nullptr;
  initGraph(graph, beginWord, wordList);
  set<string> cache = {beginWord};
  int depth = 0;
  if (moveNext(graph, endWord, cache, depth)) {
    delete[] graph;
    return depth;
  }
  delete[] graph;
  return 0;
}

int main() {
  vector<string> wordList = {"hot", "dot", "dog", "lot", "log", "cog"};
  printf("length: %d\n", ladderLength("hit", "cog", wordList));
  printf("length: %d\n", ladderLength2("hit", "cog", wordList));
  return 0;
}