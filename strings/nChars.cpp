// Given a string of m chars, print out all the possible sequences of n chars
// from it. Note that the order of chars appearing in the sequence may not be
// switched. e.g. given a string "abc", all the combinations of two chars should
// be: "ab", "ac" and "bc".

#include <stdio.h>

void find(char *source, char *result, int n) {
  if (n == 0) {
    printf("%s\n", result);
  } else {
    int i = 0, j = 0;
    for (; source[i] != 0; i++)
      ;
    for (; result[j] != 0; j++)
      ;
    for (; i >= n; i--) {
      result[j] = *source++;
      result[j + 1] = '\0';
      find(source, result, n - 1);
    }
  }
}

int main() {
  const int n = 3;
  char src[] = "abcdefg";
  char res[n + 1] = {0};
  find(src, res, n);
  return 0;
}