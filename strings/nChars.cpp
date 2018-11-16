// Given a string of m chars, print out all the combinations of n chars from it.
// Note that the order of chars may not be changed.
// e.g. given a string "abc", all the combinations of two chars should be: "ab", "ac" and "bc".

#include <stdio.h>

void find(char *source, char *result, int n)
{
  if (n == 0)
  {
    printf("%s\n", result);
  }
  else
  {
    int i, j;
    for (i = 0; source[i] != 0; i++) ;
    for (j = 0; result[j] != 0; j++) ;
    for (; i >= n; i--)
    {
      result[j] = *source++;
      result[j + 1] = '\0';
      find(source, result, n - 1);
    }
  }
}

int main()
{
  const int n = 3;
  char* src = "abcdefg";
  char res[n + 1] = {0};
  find(src, res, n);
  return 0;
}