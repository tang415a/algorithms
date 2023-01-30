/*
Given two strings, calculate the distance between them.

The distance between two strings is defined by the transformation times needed
if we want to turn one string to another. The possible transformations include:
1) add a character;
2) change a character;
3) delete a character.

Examples:
The distance between "abc" and "abe" is 1.
The distance between "abc" and "ab" is 1.
*/

#include <iostream>
#include <string>

using namespace std;

int doMeasure(const char *a, int la, const char *b, int lb, int **hash) {
  if (la == 0)
    return lb;
  if (lb == 0)
    return la;
  if (hash[la - 1][lb - 1] >= 0)
    return hash[la - 1][lb - 1];

  int m = doMeasure(a, la - 1, b, lb - 1, hash);
  if (a[la - 1] == b[lb - 1])
    return m;

  int m1 = doMeasure(a, la - 1, b, lb, hash),
      m2 = doMeasure(a, la, b, lb - 1, hash);

  if (m > m1)
    m = m1;
  if (m > m2)
    m = m2;
  return m + 1;
}

int measureDist(const string &a, const string &b) {
  int la = a.size(), lb = b.size();
  int **hash = new int *[la];
  for (int i = 0; i < la; i++) {
    hash[i] = new int[lb];
    memset(hash[i], -1, sizeof(int) * lb);
  }

  int res = doMeasure(a.c_str(), la, b.c_str(), lb, hash);

  for (int i = 0; i < la; i++)
    delete[] hash[i];
  delete[] hash;

  return res;
}

int measureDist2(const string &a, const string &b) {
  int la = a.length(), lb = b.length();
  int **cache = new int *[la + 1];
  for (int i = 0; i <= la; ++i) {
    cache[i] = new int[lb + 1];
    cache[i][0] = i;
  }
  for (int i = 1; i <= lb; ++i) {
    cache[0][i] = i;
  }
  for (int i = 1; i <= la; ++i) {
    for (int j = 1; j <= lb; ++j) {
      if (a[i] == b[j]) {
        cache[i][j] = cache[i - 1][j - 1];
      } else {
        cache[i][j] =
            min(min(cache[i - 1][j - 1], cache[i][j - 1]), cache[i - 1][j]) + 1;
      }
    }
  }
  int ret = cache[la][lb];
  for (int i = 0; i <= la; ++i) {
    delete[] cache[i];
  }
  delete[] cache;
  return ret;
}

int main() {
  string a = "abcdefg", b = "abefc";
  cout << "The dist from '" << a << "' to '" << b << "' is " << measureDist(a, b) << endl;
  cout << "The dist from '" << a << "' to '" << b << "' is " << measureDist2(a, b) << endl;
  return 0;
}