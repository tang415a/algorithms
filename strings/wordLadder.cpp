/*Given two words (beginWord and endWord), and a dictionary's word list, find the length of shortest transformation sequence from beginWord to endWord, such that:

Only one letter can be changed at a time.
Each transformed word must exist in the word list. Note that beginWord is not a transformed word.
Note:

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

Explanation: As one shortest transformation is "hit" -> "hot" -> "dot" -> "dog" -> "cog",
return its length 5.
Example 2:

Input:
beginWord = "hit"
endWord = "cog"
wordList = ["hot","dot","dog","lot","log"]

Output: 0

Explanation: The endWord "cog" is not in wordList, therefore no possible transformation.
*/

#include <stdio.h>
#include <vector>
#include <map>
#include <string>
using namespace std;

int ladderLength(string beginWord, string endWord, vector<string>& wordList) {
  int l = beginWord.length();
  map<string, vector<string>> m;
  for(auto& word: wordList) {
    for(int i = 0; i < l; i++) {
      string key = word.substr(0, i) + "*" + word.substr(i + 1);
      if (m.find(key) != m.end())
        m[key].push_back(word);
      else
        m[key] = { word };
    }
  }
  map<string, bool> visited;
  vector<string> found = { beginWord };
  int level = 1, start = 0;
  while(true) {
    int end = found.size();
    if (start >= end)
      break;
    for(; start < end; start++) {
      for(int i = 0; i < l; i++) {
        string key = found[start].substr(0, i) + "*" + found[start].substr(i + 1);
        if (m.find(key) != m.end()) {
          for (auto& f: m[key]) {
            if (visited[f])
              continue;
            if (f == endWord)
              return level + 1;
            visited[f] = true;
            found.push_back(f);
          }
        }
      }
    }
    level++;
  }
  return 0;
}

int main() {
  vector<string> wordList = {"hot","dot","dog","lot","log","cog"};
  printf("%d", ladderLength("hit", "cog", wordList));
  getchar();
  return 0;
}