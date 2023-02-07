/*
A phrase is a palindrome if, after converting all uppercase letters into
lowercase letters and removing all non-alphanumeric characters, it reads the
same forward and backward. Alphanumeric characters include letters and numbers.

Given a string s, return true if it is a palindrome, or false otherwise.


Example 1:

Input: s = "A man, a plan, a canal: Panama"
Output: true
Explanation: "amanaplanacanalpanama" is a palindrome.
Example 2:

Input: s = "race a car"
Output: false
Explanation: "raceacar" is not a palindrome.
Example 3:

Input: s = " "
Output: true
Explanation: s is an empty string "" after removing non-alphanumeric characters.
Since an empty string reads the same forward and backward, it is a palindrome.


Constraints:

1 <= s.length <= 2 * 10^5
s consists only of printable ASCII characters.
*/

#include <iostream>
#include <string>

using namespace std;

bool isLetter(char &c) {
  if (c >= 'A' && c <= 'Z') {
    c += ('a' - 'A');
    return true;
  }
  if (c >= 'a' && c <= 'z') {
    return true;
  }
  return false;
}

bool isPalindrome(string s) {
  for (int i = 0, j = s.length() - 1; i < j; i++, j--) {
    while (!isLetter(s[i]) && ++i < j) ;
    while (!isLetter(s[j]) && i < --j) ;
    if (i >= j)
      return true;
    if (s[i] != s[j])
      return false;
  }
  return true;
}

int main() {
  cout << isPalindrome("A man, a plan, a canal: Panama") << endl;
  cout << isPalindrome("race a car") << endl;
  cout << isPalindrome("") << endl;
  return 0;
}