/*
Given a paragraph and a list of banned words, return the most frequent word that is not in the list of banned words.  It is guaranteed there is at least one word that isn't banned, and that the answer is unique.

Words in the list of banned words are given in lowercase, and free of punctuation.  Words in the paragraph are not case sensitive.  The answer is in lowercase.

Example:

Input: 
paragraph = "Bob hit a ball, the hit BALL flew far after it was hit."
banned = ["hit"]

Output: "ball"

Explanation: 
"hit" occurs 3 times, but it is a banned word.
"ball" occurs twice (and no other word does), so it is the most frequent non-banned word in the paragraph. 
Note that words in the paragraph are not case sensitive,
that punctuation is ignored (even if adjacent to words, such as "ball,"), 
and that "hit" isn't the answer even though it occurs more because it is banned.
 

Note:

1. 1 <= paragraph.length <= 1000.
2. 1 <= banned.length <= 100.
3. 1 <= banned[i].length <= 10.

4. The answer is unique, and written in lowercase (even if its occurrences in paragraph may have uppercase symbols, and even if it is a proper noun.)
paragraph only consists of letters, spaces, or the punctuation symbols !?',;.
There are no hyphens or hyphenated words.

5. Words only consist of letters, never apostrophes or other punctuation symbols.
*/

#include <stdio.h>
#include <map>
#include <vector>
#include <string>
using namespace std;

bool isLowercase(char c) {
  return c >= 'a' && c <= 'z';
}

bool isUppercase(char c) {
  return c >= 'A' && c <= 'Z';
}

bool isLetter(char c) {
  return isLowercase(c) || isUppercase(c);
}

void processStr(const string& text, int st, int len, map<string, bool>& bannedMap, map<string, int>& rec) {
  string key = text.substr(st, len);
  for (auto& c: key) {
    if (isUppercase(c))
      c += ('a' - 'A');
  }
  if (bannedMap[key])
    return;
  rec[key]++;
}

string mostCommon(const string& text, const vector<string>& banned) {
  map<string, int> rec;
  map<string, bool> bannedMap;

  for(auto& s: banned)
    bannedMap[s] = true;
    
  int st = 0, len = text.size();
  for (int i = 0; i < len; i++) {
    if (!isLetter(text[i]) && i > st){
      processStr(text, st, i - st, bannedMap, rec);
      st = i + 1;
    }
  }
  if (len > st)
    processStr(text, st, len, bannedMap, rec);

  int max = 0;
  string res;
  for (auto& k: rec) {
    if(max < k.second) {
      max = k.second;
      res = k.first;
    }
  }
  return res;
}

int main() {
  string paragraph = "Bob hit a ball, the hit BALL flew far after it was hit.";
  vector<string> banned({"hit"});
  printf("The most common word is %s.\n", mostCommon(paragraph, banned).c_str());
  return 0;
}