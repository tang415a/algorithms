/*
Given an integer n, return 1 - n in lexicographical order.

For example, given 13, return: [1,10,11,12,13,2,3,4,5,6,7,8,9].

Please optimize your algorithm to use less time and space. The input size may be as large as 5,000,000.
*/

#include <stdio.h>
#include <vector>
using namespace std;

bool addOneMoreDigit(int n, vector<int>& res, int& st) {
  int last = res.size() - 1;
  for(int i = st; i <= last; i++) {
    int v = res[i] * 10;
    for(int j = 0; j <= 9; j++){
      int nv = v + j;
      if (nv > n)
          return false;
      res.push_back(nv);
    }
  }
  st = last + 1;
  return true;
}

void printNext(int n, int i, vector<int>& res) {
  if (i > n) return;
  res.push_back(i);
  int start = res.size() - 1;
  while(addOneMoreDigit(n, res, start));
}

vector<int> lexicalOrder(int n) {
  vector<int> res;
  for(int i = 1; i <= 9; i++)
    printNext(n, i, res);
  return res;
}

int main() {
  const int n = 13;
  auto r = lexicalOrder(n);
  for(auto& v : r)
    printf("%d ", v);
  return 0;
}