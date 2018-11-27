/*
Given two strings, calculate the distance between them.

The distance between two strings is defined by the transformation times needed if we want to turn one string to another.
The possible transformations include:
1) add a character;
2) change a character;
3) delete a character.

Examples:
The distance between "abc" and "abe" is 1.
The distance between "abc" and "ab" is 2.
*/

#include <string>
#include <stdio.h>
using namespace std;

int doMeasure(const char *a, int la, const char *b, int lb, int** hash) {
  if (la == 0)
    return lb;
  if (lb == 0)
    return la;
  if (hash[la-1][lb-1] >= 0)
    return hash[la-1][lb-1];

  int m = doMeasure(a, la - 1, b, lb - 1, hash);
  if (a[la-1] == b[lb-1])
    return m;
  
  int m1 = doMeasure(a, la - 1, b, lb, hash),
    m2 = doMeasure(a, la, b, lb - 1, hash);
  
  if (m > m1) m = m1;
  if (m > m2) m = m2;
  return m + 1;
}

int measureDist(const string& a, const string& b) {
  int la = a.size(), lb = b.size();
  int** hash = new int*[la];
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

int main() {
  string a = "abcdefg", b = "abefc";
  printf("The dist is %d for %s and %s.", measureDist(a, b), a.c_str(), b.c_str());
  return 0;
}