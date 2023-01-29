/*
Given a string which contains only lowercase letters, remove duplicate letters so that every letter appear once and only once. You must make sure your result is the smallest in lexicographical order among all possible results.

Example 1:

Input: "bcabc"
Output: "abc"
Example 2:

Input: "cbacdcbc"
Output: "acdb"

Example 3:

Input: "cedabcdesza"
Output: "abcdesz"

Example 4:

Input: "cbedddedc"
Output: "bdec"
*/

#include <stdio.h>
#include <string>

using namespace std;

string removeDuplicateLetters(string s)
{
  int hash[26] = {};
  for (int i = 0; i < s.size(); i++)
    hash[s[i] - 'a'] = i + 1;
  
  string res = "";
  for (int i = 0; i < s.size(); i++)
  {
    int idx = s[i] - 'a';
    bool shouldErase = true;
    if (hash[idx] > i + 1)
    {
      for (int j = i + 1; j < hash[idx] - 1; j++)
      {
        if (s[j] == s[i])
          break;

        if (hash[s[j] - 'a'] < hash[idx])
        {
          if (s[j] > s[i])
          {
            shouldErase = false;
            hash[idx] = 0;
          }
          break;
        }
      }
    }
    else if (hash[idx] > 0)
      shouldErase = false;
    if (!shouldErase)
      res.push_back(s[i]);
  }
  return res;
}

int main()
{
  string s = "cbedddedc";
  printf("%s", removeDuplicateLetters(s).c_str());
  return 0;
}
