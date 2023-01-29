/*
There are N students in a class. Some of them are friends, while some are not.
Their friendship is transitive in nature. For example, if A is a direct friend
of B, and B is a direct friend of C, then A is an indirect friend of C. And we
defined a friend circle is a group of students who are direct or indirect
friends.

Given a N*N matrix M representing the friend relationship between students in
the class. If M[i][j] = 1, then the ith and jth students are direct friends with
each other, otherwise not. And you have to output the total number of friend
circles among all the students.

Example 1:
Input:
[[1,1,0],
 [1,1,0],
 [0,0,1]]

Output: 2
Explanation:The 0th and 1st students are direct friends, so they are in a friend
circle. The 2nd student himself is in a friend circle. So return 2.

Example 2:
Input:
[[1,1,0],
 [1,1,1],
 [0,1,1]]

Output: 1
Explanation:The 0th and 1st students are direct friends, the 1st and 2nd
students are direct friends, so the 0th and 2nd students are indirect friends.
All of them are in the same friend circle, so return 1.

Note:
N is in range [1,200].
M[i][i] = 1 for all students.
If M[i][j] = 1, then M[j][i] = 1.
*/
#include <map>
#include <stdio.h>
#include <vector>

using namespace std;

int findCircleNum(vector<vector<int>> &matrix) {
  int N = matrix.size();
  map<int, int> m;
  int p = 0;
  for (int i = 1; i < N; i++) {
    // we should iterate over lower triangle matrix other than upper triangle
    // because in this way we can detect circular friendship and filter it out
    for (int j = 0; j < i; j++) {
      if (matrix[i][j] == 0)
        continue;
      int k = j;
      while (m.find(k) != m.end())
        k = m.at(k);
      if (i > k) { // k cannot be greater than i and definitely not equal to i
        m[k] = i;
        p++;
      }
    }
  }
  return N - p;
}

int findCircleNum2(vector<vector<int>> &matrix) {
  int r = 1;
  for (int i = 1, n = static_cast<int>(matrix.size()); i < n; ++i) {
    int j = 0;
    while (j < i) {
      if (matrix[i][j] != 0) {
        break;
      }
      ++j;
    }
    if (j == i) {
      r++;
    }
  }
  return r;
}

int main() {
  vector<vector<int>> v = {{1, 1, 0, 0, 1},
                           {1, 1, 0, 0, 0},
                           {0, 0, 1, 0, 0},
                           {0, 0, 0, 1, 0},
                           {1, 0, 0, 0, 1}};
  printf("%d\n", findCircleNum(v));
  printf("%d\n", findCircleNum2(v));
  
  return 0;
}