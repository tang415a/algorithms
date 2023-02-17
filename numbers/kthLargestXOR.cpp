/*
You are given a 2D matrix of size m x n, consisting of non-negative integers.
You are also given an integer k.

The value of coordinate (a, b) of the matrix is the XOR of all matrix[i][j]
where 0 <= i <= a < m and 0 <= j <= b < n (0-indexed).

Find the kth largest value (1-indexed) of all the coordinates of matrix.

Example 1:

Input: matrix = [[5,2],[1,6]], k = 1
Output: 7
Explanation: The value of coordinate (0,1) is 5 XOR 2 = 7, which is the largest
value.

Example 2:

Input: matrix = [[5,2],[1,6]], k = 2
Output: 5
Explanation: The value of coordinate (0,0) is 5 = 5, which is the 2nd largest
value.

Example 3:

Input: matrix = [[5,2],[1,6]], k = 3
Output: 4
Explanation: The value of coordinate (1,0) is 5 XOR 1 = 4, which is the 3rd
largest value.

Constraints:

m == matrix.length
n == matrix[i].length
1 <= m, n <= 1000
0 <= matrix[i][j] <= 10^6
1 <= k <= m * n
*/

#include <iostream>
#include <queue>
#include <vector>

using namespace std;

int kthLargestValue(const vector<vector<int>> &matrix, int k) {
  int m = matrix.size(), n = matrix[0].size();
  vector<vector<int>> p(m);
  for (int i = 0; i < m; i++) {
    p[i].resize(n);
    p[i][0] = matrix[i][0];
    for (int j = 1; j < n; j++) {
      p[i][j] = p[i][j - 1] ^ matrix[i][j];
    }
  }
  priority_queue<int, vector<int>, greater<int>> pq;
  for (int i = 0; i < m; i++) {
    for (int j = 0; j < n; j++) {
      pq.push(p[0][j]);
      while (pq.size() > k) {
        pq.pop();
      }
    }
    if (i == m - 1)
      break;
    for (int j = 0; j < n; j++) {
      p[0][j] ^= p[i + 1][j];
    }
  }
  return pq.top();
}

int main() {
  cout << kthLargestValue({{5, 2}, {1, 6}}, 1) << endl;
  cout << kthLargestValue({{5, 2}, {1, 6}}, 2) << endl;
  cout << kthLargestValue({{5, 2}, {1, 6}}, 3) << endl;
  return 0;
}