// Find the maximum length of a substring with non-repeated characters inside a string.
// input: "foobaa"
// output: 3

#include <stdio.h>
#include <string>
using namespace std;

int nonRepeatedChars(const string &input)
{
  if (input.empty())
    return 0;
  int count[26] = {-1};
  count[input[0] - 'a'] = 0;
  int start = 0, max = 1, len = 1;
  for (unsigned int i = 1; i < input.length(); i++)
  {
    char a = input[i];
    int cnt = count[a - 'a'];
    if (cnt >= 0 && start <= cnt)
    {
      start = cnt + 1;
    }
    len = i - start + 1;
    if (len > max)
      max = len;
    count[a - 'a'] = i;
  }
  return max;
}

int main()
{
  string s = "foobaa";
  printf("%d\n", nonRepeatedChars(s));
  getchar();
}