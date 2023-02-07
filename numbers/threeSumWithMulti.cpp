/*
Given an integer array A, and an integer target, return the number of tuples i,
j, k  such that i < j < k and A[i] + A[j] + A[k] == target.

As the answer can be very large, return it modulo 10^9 + 7.

Example 1:

Input: A = [1,1,2,2,3,3,4,4,5,5], target = 8
Output: 20
Explanation:
Enumerating by the values (A[i], A[j], A[k]):
(1, 2, 5) occurs 8 times;
(1, 3, 4) occurs 8 times;
(2, 2, 4) occurs 2 times;
(2, 3, 3) occurs 2 times.

Example 2:

Input: A = [1,1,2,2,2,2], target = 5
Output: 12
Explanation:
A[i] = 1, A[j] = A[k] = 2 occurs 12 times:
We choose one 1 from [1,1] in 2 ways,
and two 2s from [2,2,2,2] in 6 ways.

Note:

3 <= A.length <= 3000
0 <= A[i] <= 100
0 <= target <= 300
*/

#include <iostream>
#include <vector>
using namespace std;

int threeSumMulti(const vector<int> &A, int target) {
  const int kMaxN = 100;
  const int kMod = 1e9 + 7;
  vector<int> vec(kMaxN + 1, 0);
  for (auto &v : A) {
    vec[v]++;
  }
  long long int res = 0;
  for (int i = 0; i <= target / 3; i++) {
    if (vec[i] == 0)
      continue;
    for (int j = i; j <= (target - i) / 2; j++) {
      if (vec[j] == 0)
        continue;
      int k = target - j - i;
      if (vec[k] == 0)
        continue;
      if (i == j) {
        res += (j == k ? vec[i] * (vec[i] - 1) * (vec[i] - 2) / 6
                       : vec[i] * (vec[i] - 1) * vec[k] / 2);
      } else {
        res += (j == k ? vec[i] * vec[j] * (vec[j] - 1) / 2
                       : vec[i] * vec[j] * vec[k]);
      }
    }
  }
  return res % kMod;
}

int main() {
  cout << threeSumMulti({1, 1, 2, 2, 3, 3, 4, 4, 5, 5}, 8) << endl;
  cout << threeSumMulti({1, 1, 2, 2, 2, 2}, 5) << endl;
  return 0;
}