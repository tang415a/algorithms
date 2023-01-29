// A string contains some asterisks (*) and other characters.
// Write a function that can put all the asterisks inside the string ahead of
// other characters with least time complexity. For example, given a string
// "ab*cd*ef*gh", it will output "***abcdefgh".

#include <stdio.h>
#include <string.h>

int moveStarInStr(char *str) {
  int i, j = strlen(str) - 1;
  for (i = j; j >= 0; j--) {
    if (str[j] != '*') {
      if (i > j) {
        str[i] = str[j];
        str[j] = '*';
      }
      i--;
    }
  }
  return i + 1;
}

int main() {
  char str[] = "ab*cd*ef*g**h";
  int num = moveStarInStr(str);
  printf("%s, altogether %d asterisks.", str, num);
  return 0;
}