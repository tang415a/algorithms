/*
You are given three positive integers n, index and maxSum. You want to construct
an array nums (0-indexed) that satisfies the following conditions:

* nums.length == n
* nums[i] is a positive integer where 0 <= i < n.
* abs(nums[i] - nums[i+1]) <= 1 where 0 <= i < n-1.
* The sum of all the elements of nums does not exceed maxSum.
* nums[index] is maximized.

Return nums[index] of the constructed array.

Note that abs(x) equals x if x >= 0, and -x otherwise.

Example 1:

Input: n = 4, index = 2,  maxSum = 6
Output: 2
Explanation: The arrays [1,1,2,1] and [1,2,2,1] satisfy all the conditions.
There are no other valid arrays with a larger value at the given index.

Example 2:

Input: n = 6, index = 1,  maxSum = 10
Output: 3

Constraints:

1 <= n <= maxSum <= 10^9
0 <= index < n
*/

#include <iostream>

using namespace std;

bool possible(int n, int i, int maxSum, int m) {
  if (m > i && m > n - 1 - i) {
    return m * n - i * (i + 1) / 2 - (n - i) * (n - i - 1) / 2 <= maxSum;
  }
  if (m > i) {
    return m * (m + 1) / 2 + n - i - m + i * (2 * m - 1 - i) / 2 <= maxSum;
  }
  if (m > n - 1 - i) {
    return m * (m + 1) / 2 + i - m + (n - 1 - i) * (2 * m - n + i) / 2 <= maxSum;
  }
  return m * m <= maxSum;
}

int maxValAtBoundedArr(int n, int index, int maxSum) {
  if (maxSum < n)
    return -1;
  int l = 1, h = maxSum;
  while (l <= h) {
    int m = l + (h - l) / 2;
    if (possible(n, index, maxSum, m)) {
      l = m + 1;
    } else {
      h = m - 1;
    }
  }
  return h;
}

int main() {
  cout << maxValAtBoundedArr(4, 2, 6) << endl;
  cout << maxValAtBoundedArr(6, 1, 10) << endl;
  cout << maxValAtBoundedArr(3, 1, 4) << endl;
  cout << maxValAtBoundedArr(5, 1, 2) << endl;
  cout << maxValAtBoundedArr(5, 1, 5) << endl;
  return 0;
}