/*
There are N students in a class. Some of them are friends, while some are not. Their friendship is transitive in nature. For example, if A is a direct friend of B, and B is a direct friend of C, then A is an indirect friend of C. And we defined a friend circle is a group of students who are direct or indirect friends.

Given a N*N matrix M representing the friend relationship between students in the class. If M[i][j] = 1, then the ith and jth students are direct friends with each other, otherwise not. And you have to output the total number of friend circles among all the students.

Example 1:
Input: 
[[1,1,0],
 [1,1,0],
 [0,0,1]]

Output: 2
Explanation:The 0th and 1st students are direct friends, so they are in a friend circle. 
The 2nd student himself is in a friend circle. So return 2.

Example 2:
Input: 
[[1,1,0],
 [1,1,1],
 [0,1,1]]

Output: 1
Explanation:The 0th and 1st students are direct friends, the 1st and 2nd students are direct friends, 
so the 0th and 2nd students are indirect friends. All of them are in the same friend circle, so return 1.

Note:
N is in range [1,200].
M[i][i] = 1 for all students.
If M[i][j] = 1, then M[j][i] = 1.
*/
#include <stdio.h>
#include <vector>
#include <map>
using namespace std;

void initiate(map<int, int>& m, const vector<vector<int>>& matrix) {
  unsigned int N = matrix.size();
  for (unsigned int i = 1; i < N; i++) {
    for (unsigned int j = 0; j < i; j++) {
      if (matrix[i][j] > 0)
        m[i] = j;
    }
  }
}

bool isFriend(int i, int j, const map<int, int>& m) {
  while (m.find(i) != m.end()) {
    i = m.at(i);
  }
  while (m.find(j) != m.end()) {
    j = m.at(j);
  }
  return i == j;
}

bool isNewCircle(int i, const vector<int>& vec, const map<int, int>& m) {
  for (auto& v : vec) {
    if (isFriend(i, v, m))
      return false;
  }
  return true;
}

int findCircleNum(vector<vector<int>>& matrix) {
  map<int, int> m;
  initiate(m, matrix);
  unsigned int N = matrix.size();
  vector<int> vec;
  for (unsigned int i = 0; i < N; i++) {
    if (isNewCircle(i, vec, m))
      vec.push_back(i);
  }
  return vec.size();
}

int main() {
  vector<vector<int>> v = { { 1,1,0 },{ 1,1,0 },{ 0,0,1 } };
  int num = findCircleNum(v);
  printf("%d\n", num);
  v = { { 1,1,0 },{ 1,1,1 },{ 0,1,1 } };
  num = findCircleNum(v);
  printf("%d\n", num);
  getchar();
  return 0;
}