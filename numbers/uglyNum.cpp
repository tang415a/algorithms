// A number is an ugly number if its divisors contain only one, two, three or
// five. The first ugly number is 1. Write an algorithm to print out the N-th
// ugly number.

#include <stdio.h>
#include <vector>
using namespace std;

int ugly(int n) {
  vector<int> rec;
  rec.push_back(1);
  int b[3] = {0, 0, 0}, m[3] = {2, 3, 5};
  while (rec.size() < n) {
    int min = 0, minVal = rec[b[0]] * m[0];
    for (int i = 1; i < 3; i++) {
      int curVal = rec[b[i]] * m[i];
      if (curVal < minVal) {
        minVal = curVal;
        min = i;
      } else if (curVal == minVal)
        ++b[i];
    }
    rec.push_back(rec[b[min]++] * m[min]);
  }
  return rec[n - 1];
}

int main() {
  for (int i = 1; i <= 20; i++)
    printf("%d\n", ugly(i));
  return 0;
}