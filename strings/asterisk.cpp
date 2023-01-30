// A string contains some asterisks (*) and other characters.
// Write a function that can put all the asterisks inside the string ahead of
// other characters with least time complexity. For example, given a string
// "ab*cd*ef*gh", it will output "***abcdefgh".

#include <stdio.h>
#include <string.h>

/*
  <----- i       j
           * * * *
   _ _ _ _ _ _ _ _
*/
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

// while you may also iterate from the beginning of string to the end, however,
// it is not stable, i.e. the order between non-asterisk characters may be
// switched. But this way works for the case when we want to move the asterisks
// behind the other characters.
/*
           j   i ----->
   * * * *     *
   _ _ _ _ _ _ _ _ _ _ _
*/
int moveAsterisks(char *str) {
  int j = 0;
  for (int i = 0, n = strlen(str); i < n; ++i) {
    if (str[i] == '*') {
      if (i > j) {
        str[i] = str[j];
        str[j] = '*';
      }
      j++;
    }
  }
  return j;
}

// if we want to move asterisks behind the other characters, then iterating from
// begining to the end is a good choice as it will not switch the orders of
// non-asterisk characters.
/*
     j         i ----->
     * * * * *  
   _ _ _ _ _ _ _ _ _ _ _
*/
int moveAsterisksBackwards(char *str) {
  int j = 0, n = strlen(str);
  for (int i = 0; i < n; ++i) {
    if (str[i] != '*') {
      if (i > j) {
        str[j] = str[i];
        str[i] = '*';
      }
      j++;
    }
  }
  return n - j;
}

int main() {
  char str[] = "ab*cd*ef*g**h";
  int num = moveStarInStr(str);
  printf("%s, altogether %d asterisks.\n", str, num);
  char str2[] = "ab*cd*ef*g**h";
  num = moveAsterisks(str2);
  printf("%s, altogether %d asterisks.\n", str2, num);
  char str3[] = "ab*cd*ef*g**h";
  num = moveAsterisksBackwards(str3);
  printf("%s, altogether %d asterisks.\n", str3, num);
  return 0;
}