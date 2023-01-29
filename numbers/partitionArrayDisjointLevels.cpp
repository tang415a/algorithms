/*
Given an array A, partition it into two (contiguous) subarrays left and right so that:

Every element in left is less than or equal to every element in right.
left and right are non-empty.
left has the smallest possible size.
Return the length of left after such a partitioning.  It is guaranteed that such a partitioning exists.

Example 1:

Input: [5,0,3,8,6]
Output: 3
Explanation: left = [5,0,3], right = [8,6]
Example 2:

Input: [1,1,1,0,6,12]
Output: 4
Explanation: left = [1,1,1,0], right = [6,12]
Note:

2 <= A.length <= 30000
0 <= A[i] <= 10^6
It is guaranteed there is at least one way to partition A as described.
*/

#include <stdio.h>
#include <vector>
using namespace std;

int partitionDisjoint(vector<int>& A) {
  if (A.empty())
    return -1;
  int len = 1, maxLeft = A[0], maxAll = A[0];
  for(int i = 1; i < A.size(); i++) {
    if (A[i] > maxAll)
      maxAll = A[i];
    else if (A[i] < maxLeft) {
      len = i + 1;
      maxLeft = maxAll;
    }
  }
  return len;
}

int main() {
  vector<int> A = {5,0,3,8,6};
  printf("%d", partitionDisjoint(A));
  return 0;
}