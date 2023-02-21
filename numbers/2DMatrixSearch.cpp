/*
Write an efficient algorithm that searches for a value target in an m x n
integer matrix matrix. This matrix has the following properties:

Integers in each row are sorted in ascending from left to right.
Integers in each column are sorted in ascending from top to bottom.

Example 1:

Input: matrix =
[[1,4,7,11,15],[2,5,8,12,19],[3,6,9,16,22],[10,13,14,17,24],[18,21,23,26,30]],
target = 5

Output: true

Example 2:

Input: matrix =
[[1,4,7,11,15],[2,5,8,12,19],[3,6,9,16,22],[10,13,14,17,24],[18,21,23,26,30]],
target = 20

Output: false

Constraints:

m == matrix.length
n == matrix[i].length
1 <= n, m <= 300
-10^9 <= matrix[i][j] <= 10^9
All the integers in each row are sorted in ascending order.
All the integers in each column are sorted in ascending order.
-10^9 <= target <= 10^9
*/

#include <iostream>
#include <vector>

using namespace std;

bool searchBlock(const vector<vector<int>> &matrix, int target, int i0, int i1,
                 int j0, int j1) {
  if (i0 > i1 || j0 > j1)
    return false;
  if (i0 == i1 && j0 == j1)
    return matrix[i0][j0] == target;
  int m0 = i0 + (i1 - i0) / 2, m1 = j0 + (j1 - j0) / 2;
  if (matrix[m0][m1] == target)
    return true;
  if (matrix[m0][m1] < target) {
    return searchBlock(matrix, target, m0 + 1, i1, m1 + 1, j1) ||
           searchBlock(matrix, target, i0, m0, m1 + 1, j1) ||
           searchBlock(matrix, target, m0 + 1, i1, j0, m1);
  }
  return searchBlock(matrix, target, i0, m0 - 1, j0, m1 - 1) ||
         searchBlock(matrix, target, i0, m0 - 1, m1, j1) ||
         searchBlock(matrix, target, m0, i1, j0, m1 - 1);
}

bool searchMatrix(const vector<vector<int>> &matrix, int target) {
  int m = matrix.size(), n = matrix[0].size();
  return searchBlock(matrix, target, 0, m - 1, 0, n - 1);
}

// a better approach
bool searchMatrix2(const vector<vector<int>> &matrix, int target) {
  int m = matrix.size();
  int n = matrix[0].size();

  int i = 0;
  int j = n - 1;

  while (i < m && j >= 0) {
    if (matrix[i][j] == target) {
      return true;
    } else if (matrix[i][j] > target) {
      j--;
    } else {
      i++;
    }
  }
  return false;
}
int main() {
  cout << searchMatrix2({{1, 4, 7, 11, 15},
                         {2, 5, 8, 12, 19},
                         {3, 6, 9, 16, 22},
                         {10, 13, 14, 17, 24},
                         {18, 21, 23, 26, 30}},
                        5)
       << endl;
  cout << searchMatrix2({{1, 4, 7, 11, 15},
                         {2, 5, 8, 12, 19},
                         {3, 6, 9, 16, 22},
                         {10, 13, 14, 17, 24},
                         {18, 21, 23, 26, 30}},
                        20)
       << endl;
  return 0;
}