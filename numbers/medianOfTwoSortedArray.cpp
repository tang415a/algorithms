/*
Given two sorted arrays nums1 and nums2 of size m and n respectively, return the
median of the two sorted arrays.

The overall run time complexity should be O(log (m+n)).

Example 1:

Input: nums1 = [1,3], nums2 = [2]
Output: 2.00000
Explanation: merged array = [1,2,3] and median is 2.
Example 2:

Input: nums1 = [1,2], nums2 = [3,4]
Output: 2.50000
Explanation: merged array = [1,2,3,4] and median is (2 + 3) / 2 = 2.5.


Constraints:

nums1.length == m
nums2.length == n
0 <= m <= 1000
0 <= n <= 1000
1 <= m + n <= 2000
-10^6 <= nums1[i], nums2[i] <= 10^6
*/

#include <iostream>
#include <vector>

using namespace std;

// https://www.tutorialcup.com/leetcode-solutions/median-of-two-sorted-arrays-leetcode-solution.htm
// https://codewithgeeks.com/median-of-two-sorted-arrays-leetcode-solution/

/*
To solve this problem, we need to first understand what actually does the median
do. It is the partitioning of set into two equal length subsets such that one
subset is greater than the other. i.e., partition the set into two subsets such
that every element of one subset is greater than every element of the other
subset.

Can we find a partition for array A and B, such that the length of subsets
obtained by adding left of both partitions and right of both partitions are
equal?

Partitioning an array at the ith position also denotes the number of elements
from that array that are present in the left subset.

And as we know that the length of subsets obtained should be equal, hence
partitionA + partitionB = (length(A) +length(B)+1)/2

Note: partition is from 0 to length(array): [0...size].

e.g.:
i = 2, j = 3, m = 6, n = 4
        |i
A: A0 A1 A2 A3 A4 A5
B: B0 B1 B2 B3
           |j

(If the length of the final merged sorted array is odd then, left subset would
have more elements)

Now the only thing left is to check how to partition the given two arrays such
that the right subset is greater than the left subset.

Let’s define the perfect partition of sorted arrays:We have partitioned A at i
and B at j, then a perfect partition is when:

* i+j = (n+m+1)/2 (subsets are of equal length)
* A[i-1]<=B[j] (elements of A in the left of i will come in the left subset)
* B[j-1]<=A[i] (elements of B in the left of j will come in left subset)

* If A[i-1]>B[j] that means there are some elements in the left of A’s partition
that should be placed in the greater(right) subset. In that case, we will move i
towards left and j towards the right.

* If B[j-1]>A[i] that means there are some elements in the left of B’s partition
which should be placed in the greater(right) subset. In that case, we will move
j towards the left and i toward the right.
*/

double findMedianSortedArrays(const vector<int> &A, const vector<int> &B) {
  const int n = A.size(), m = B.size(), t = (n + m + 1) >> 1;// (n + m + 1) / 2;
  if (n > m)
    return findMedianSortedArrays(B, A);
  if (n == 0)
    return m & 0x1 == 0 ? (double)(B[m / 2 - 1] + B[m / 2]) / 2 : B[m / 2];
  if (m == 0)
    return n & 0x1 == 0 ? (double)(A[n / 2 - 1] + A[n / 2]) / 2 : A[n / 2];
  int left = 0, right = n;
  while (left <= right) {
    // partitionA + partitionB = (n+m+1)/2
    int partitionA = left + ((right - left) >> 1); // i.e. left + (right - left) / 2 or (left + right) / 2
    int partitionB = t - partitionA;
    // if partitionA is 0 then take INT_MIN for maxLeftA (nothing is left in the
    // left of partition)
    double maxLeftA = partitionA == 0 ? INT_MIN : A[partitionA - 1];

    // if partitionA is n then take INT_MAX for minRightA (nothing is left in
    // the right of partition)
    double minRightA = partitionA == n ? INT_MAX : A[partitionA];

    // Similarly for maxLeftB and minRightB
    double maxLeftB = partitionB == 0 ? INT_MIN : B[partitionB - 1];

    double minRightB = partitionB == m ? INT_MAX : B[partitionB];

    // check weather it's a perfect partition or not
    if (maxLeftA <= minRightB && maxLeftB <= minRightA) {
      if (((n + m) & 0x1) == 0) {
        // if the sorted merged array is of even length
        return (max(maxLeftA, maxLeftB) + min(minRightA, minRightB)) / 2.0;
      } else {
        return max(maxLeftA, maxLeftB);
      }
    } else if (maxLeftA > minRightB) { // move left side.
      right = partitionA - 1;
    } else { // move right side
      left = partitionA + 1;
    }
  }
  return 0.0; // we can't find the median if input is invalid i.e., arrays are
              // not sorted
}

int main() {
  cout << findMedianSortedArrays({1, 3}, {2}) << endl;
  cout << findMedianSortedArrays({1, 2}, {3, 4}) << endl;
  return 0;
}