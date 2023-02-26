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
  priority_queue<int, vector<int>, greater<int>> pq;
  vector<int> p(n);
  for (int i = 0; i < m; i++) {
    for (int j = 0, prev = 0; j < n; j++) {
      p[j] ^= prev ^= matrix[i][j];
      pq.push(p[j]);
      while (pq.size() > k) {
        pq.pop();
      }
    }
  }
  return pq.top();
}

/*
std::nth_element() is an STL algorithm which rearranges the list in such a way
such that the element at the nth position is the one which should be at that
position if we sort the list.

template
void nth_element (RandomAccessIterator first, RandomAccessIterator nth,
                  RandomAccessIterator last);

first: Random-access iterator to the first element in the list.
last: Random-access iterator to the last element in the list.
nth: Random-access iterator pointing to the position in the list,
which should be sorted.
If it points to end, then this function will do nothing.

Return Value: Since, return type is void, so it doesnot return any value.
*/
// a better approach
int vals[100'0000];
int kthLargestValue(vector<vector<int>> &matrix, int k) {
  int n = size(matrix[0]), *v = vals, buf[1000]{};

  for (const auto &row : matrix) {
    for (int j = 0, prev = 0; j < n; ++j) {
      *v++ = buf[j] ^= prev ^= row[j];
    }
  }

  nth_element(vals, v - k, v);
  return *(v - k);
}

int main() {
  cout << kthLargestValue({{5, 2}, {1, 6}}, 1) << endl;
  cout << kthLargestValue({{5, 2}, {1, 6}}, 2) << endl;
  cout << kthLargestValue({{5, 2}, {1, 6}}, 3) << endl;
  return 0;
}