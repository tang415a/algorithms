// Given a string, find out the first char that appears only once in the string
// For example, input string "abcdecbba", then it outputs 'd'.

#include <stdio.h>
#include <string>

using namespace std;

char firstSingleChar(const string& str) {
  char hash[256] = {0};
  for(auto& c: str) {
    if (hash[c] < 2)
      hash[c]++;
  }
  for(auto& c: str) {
    if (hash[c] == 1)
      return c;
  }
  return 0;
}

int main() {
  printf("%c", firstSingleChar("abcdecbba"));
  return 0;
}