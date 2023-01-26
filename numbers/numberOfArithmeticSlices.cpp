/*
A sequence of number is called arithmetic if it consists of at least three
elements and if the difference between any two consecutive elements is the same.

For example, these are arithmetic sequence:

1, 3, 5, 7, 9
7, 7, 7, 7
3, -1, -5, -9
The following sequence is not arithmetic.

1, 1, 2, 5, 7

A zero-indexed array A consisting of N numbers is given. A slice of that array
is any pair of integers (P, Q) such that 0 <= P < Q < N.

A slice (P, Q) of array A is called arithmetic if the sequence:
A[P], A[p + 1], ..., A[Q - 1], A[Q] is arithmetic. In particular, this means
that P + 1 < Q.

The function should return the number of arithmetic slices in the array A.


Example:

A = [1, 2, 3, 4]

return: 3, for 3 arithmetic slices in A: [1, 2, 3], [2, 3, 4] and [1, 2, 3, 4]
itself.
*/

#include <vector>
using namespace std;

int numberOfArithmeticSlices(vector<int> &A) {
  int siz = static_cast<int>(A.size());
  int count = 0;
  for (int i = 0; i < siz - 2;) {
    int interval = A[i + 1] - A[i];
    int k = i + 2;
    while (k < siz) {
      if (A[k] - A[k - 1] != interval)
        break;
      ++k;
    }
    if (k > i + 2) {
      if (interval == 0) {
        count += (k - i - 2);
      } else {
        count += (k - i - 1) * (k - i - 2) / 2;
      }
    }
    i = k - 1;
  }
  return count;
}

int main() {
  {
    vector<int> A = {1, 2, 3, 4};
    printf("%d\n", numberOfArithmeticSlices(A));
  }
  {
    vector<int> A = {1, 1, 1, 2, 3};
    printf("%d\n", numberOfArithmeticSlices(A));
  }
  {
    vector<int> A = {1, 1, 1, 1, 2, 3};
    printf("%d\n", numberOfArithmeticSlices(A));
  }
  {
    vector<int> A = {1, 1, 1, 1, 1, 2, 3, 4};
    printf("%d\n", numberOfArithmeticSlices(A));
  }
  return 0;
}