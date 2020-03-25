/*
Given a word, you need to judge whether the usage of capitals in it is right or not.

We define the usage of capitals in a word to be right when one of the following cases holds:

All letters in this word are capitals, like "USA".
All letters in this word are not capitals, like "leetcode".
Only the first letter in this word is capital, like "Google".
Otherwise, we define that this word doesn't use capitals in a right way.
 

Example 1:

Input: "USA"
Output: True
 

Example 2:

Input: "FlaG"
Output: False
 

Note: The input will be a non-empty word consisting of uppercase and lowercase latin letters.
*/

#include <stdio.h>
#include <string>
using namespace std;

bool detectCapitalUse(const string& word) {
  bool continued = true;
  unsigned int len = word.length();
  for (unsigned int i = 0; i < len; i++) {
    if (word[i] >= 'a' && word[i] <= 'z') { // lowercase  
      if (i > 1 && continued)
        return false;
      continued = false;
    }
    else if (!continued)
      return false;
  }
  return true;
}

int main() {
  string w[] = {"USA", "FlaG", "TItanic"};
  for (int i = 0; i < sizeof(w)/sizeof(w[0]); i++) {
    if (detectCapitalUse(w[i]))
      printf("%d true\n", i);
    else
      printf("%d false\n", i);
  }
  getchar();
  return 0;
}