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
  vector<int> prev;
  vector<GNode *> neighbors;
};

void buildPaths(vector<vector<string>> &res, const vector<GNode> &graph,
                const vector<string> &wordList, int curr, int source,
                bool create) {
  if (create) {
    res.emplace_back(vector<string>());
    create = false;
  }
  if (source == curr) {
    res.back().emplace_back(wordList[curr]);
    return;
  }
  int start = res.size() - 1;
  for (int i : graph[curr].prev) {
    // need to create a new path except the first time
    buildPaths(res, graph, wordList, i, source, create);
    create = true;
  }
  while (start < res.size()) {
    res[start++].emplace_back(wordList[curr]);
  }
}

void search(vector<vector<string>> &res, vector<GNode> &graph, int source,
            int target, const vector<string> &wordList) {
  vector<GNode *> v = {&graph[source]};
  vector<char> cache(graph.size());
  cache[source] = 2;
  for (int i = 0, n = v.size(); i < n;) {
    bool found = false;
    while (i < n) {
      for (GNode *pn : v[i]->neighbors) {
        if (pn->idx == target) {
          found = true;
          pn->prev.emplace_back(v[i]->idx);
        } else if (!found && cache[pn->idx] != 2) {
          // the shortest path to the pn (could be multiple)
          pn->prev.emplace_back(v[i]->idx);
          if (cache[pn->idx] == 0) {
            v.push_back(pn);
            cache[pn->idx] = 1; // no need to push pn to v again
          }
        }
      }
      i++;
    }
    if (found) {
      buildPaths(res, graph, wordList, target, source, true);
      return;
    }
    while (n < v.size()) {
      cache[v[n]->idx] = 2;
      n++;
    }
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
  int target = -1, source = -1, n = wordList.size();
  for (int i = 0; i < n; i++) {
    if (endWord == wordList[i]) {
      target = i;
    } else if (beginWord == wordList[i]) {
      source = i;
    }
    if (source >= 0 && target >= 0) {
      break;
    }
  }
  if (target == -1)
    return res;
  if (source == -1) {
    wordList.emplace_back(beginWord);
    source = n++;
  }
  vector<GNode> graph;
  buildGraph(graph, wordList);
  search(res, graph, source, target, wordList);
  return res;
}

// second solution
#include <unordered_set>
bool isAdjacent(const std::string &s, const std::string &p) {
  int cnt = 0;
  for (size_t i = 0; i < s.size(); ++i) {
    cnt += s[i] != p[i];
  }
  return cnt == 1;
}

void dfs(int i, const std::vector<std::vector<std::string>> &levels,
         std::vector<std::string> *path,
         std::vector<std::vector<std::string>> *paths) {
  if (i < 0) {
    paths->emplace_back(path->rbegin(), path->rend());
    return;
  }

  const auto s = path->back();
  for (const auto &p : levels[i]) {
    if (isAdjacent(s, p)) {
      path->push_back(p);
      dfs(i - 1, levels, path, paths);
      path->pop_back();
    }
  }
}

std::vector<std::string>
getNextLevel(const std::vector<std::string> &prev_level,
             std::unordered_set<std::string> *words) {
  std::vector<std::string> level;
  for (const auto &s : prev_level) {
    for (auto it = words->begin(); it != words->end();) {
      if (isAdjacent(s, *it)) {
        level.push_back(*it);
        it = words->erase(it);
      } else {
        ++it;
      }
    }
  }
  return level;
}

std::vector<std::vector<std::string>>
findLadders2(std::string begin_word, std::string end_word,
             std::vector<std::string> &word_list) {
  std::unordered_set<std::string> words{word_list.begin(), word_list.end()};
  if (!words.count(end_word)) {
    return {};
  }

  std::vector<std::vector<std::string>> levels{{begin_word}};
  words.erase(begin_word);

  while (words.count(end_word)) {
    levels.push_back(getNextLevel(levels.back(), &words));
    if (levels.back().empty()) {
      return {};
    }
  }

  std::vector<std::vector<std::string>> paths;
  std::vector<std::string> path{end_word};
  dfs(levels.size() - 2, levels, &path, &paths);
  return paths;
}

int main() {
  vector<string> wordList = {"hot", "dot", "dog", "lot", "log", "cog"};
  auto r = findLadders("hit", "cog", wordList);
  for (auto &l : r) {
    string arrow;
    for (auto &s : l) {
      cout << arrow << s;
      arrow = " -> ";
    }
    cout << endl;
  }
  cout << endl;
  wordList = {"hot", "dot", "dog", "lot", "log"};
  r = findLadders("hit", "cog", wordList);
  for (auto &l : r) {
    string arrow;
    for (auto &s : l) {
      cout << arrow << s;
      arrow = " -> ";
    }
    cout << endl;
  }
  cout << endl;
  /*
  red -> ted -> tex -> tax
  red -> rex -> tex -> tax
  red -> ted -> tad -> tax
  */
  wordList = {"ted", "tex", "red", "tax", "tad", "den", "rex", "pee"};
  r = findLadders("red", "tax", wordList);
  for (auto &l : r) {
    string arrow;
    for (auto &s : l) {
      cout << arrow << s;
      arrow = " -> ";
    }
    cout << endl;
  }
  cout << endl;
  return 0;
}