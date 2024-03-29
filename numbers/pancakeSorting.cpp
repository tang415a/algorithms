/*
Given an array A, we can perform a pancake flip: We choose some positive integer
k <= A.length, then reverse the order of the first k elements of A.  We want to
perform zero or more pancake flips (doing them one after another in succession)
to sort the array A.

Return the k-values corresponding to a sequence of pancake flips that sort A.
Any valid answer that sorts the array within 10 * A.length flips will be judged
as correct.

Example 1:

Input: [3,2,4,1]
Output: [4,2,4,3]

Explanation:
We perform 4 pancake flips, with k values 4, 2, 4, and 3.
Starting state: A = [3, 2, 4, 1]
After 1st flip (k=4): A = [1, 4, 2, 3]
After 2nd flip (k=2): A = [4, 1, 2, 3]
After 3rd flip (k=4): A = [3, 2, 1, 4]
After 4th flip (k=3): A = [1, 2, 3, 4], which is sorted.

Example 2:

Input: [1,2,3]
Output: []

Explanation: The input is already sorted, so there is no need to flip anything.
Note that other answers, such as [3, 3], would also be accepted.

Note:

1 <= A.length <= 100
A[i] is a permutation of [1, 2, ..., A.length]
*/

#include <vector>
using namespace std;

void flip(vector<int> &A, int m) {
  for (int i = 0; 2 * i < m; i++) {
    int tmp = A[i];
    A[i] = A[m - i];
    A[m - i] = tmp;
  }
}

void pancakeSortHelper(vector<int> &A, int max, vector<int> &oper) {
  int i = 0;
  for (; i < max; i++) {
    if (A[i] == max)
      break;
  }
  if (i == max - 1)
    return;
  if (i == 0) {
    flip(A, max - 1);
    oper.push_back(max);
    return;
  }
  flip(A, i);
  flip(A, max - 1);
  oper.push_back(i + 1);
  oper.push_back(max);
}

vector<int> pancakeSort(vector<int> &A) {
  vector<int> res;
  int siz = A.size();
  while (siz > 1) {
    pancakeSortHelper(A, siz, res);
    siz--;
  }
  return res;
}

int main() {
  vector<int> A = {1, 2, 3};
  vector<int> res = pancakeSort(A);
  for (auto &v : res) {
    printf("%d ", v);
  }
  return 0;
}