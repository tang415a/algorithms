/*
Given an integer array nums, return the sum of floor(nums[i] / nums[j]) for all
pairs of indices 0 <= i, j < nums.length in the array. Since the answer may be
too large, return it modulo 10^9 + 7.

The floor() function returns the integer part of the division.


Example 1:

Input: nums = [2,5,9]
Output: 10
Explanation:
floor(2 / 5) = floor(2 / 9) = floor(5 / 9) = 0
floor(2 / 2) = floor(5 / 5) = floor(9 / 9) = 1
floor(5 / 2) = 2
floor(9 / 2) = 4
floor(9 / 5) = 1
We calculate the floor of the division for every pair of indices in the array
then sum them up.

Example 2:

Input: nums = [7,7,7,7,7,7,7]
Output: 49


Constraints:

1 <= nums.length <= 10^5
1 <= nums[i] <= 10^5

*/

#include <iostream>
#include <vector>
using namespace std;

int sumOfFlooredPairs(const vector<int> &nums) {
  const int kMod = 10e9 + 7;
  const int kMax = 10e5;
  int *count = new int[kMax];
  memset(count, 0, sizeof(int) * kMax);
  int n = nums.size();
  for (int i = 0; i < n; ++i) {
    ++count[nums[i] - 1];
  }
  int *value = new int[kMax];
  int m = 0;
  for (int i = 0; i < kMax; ++i) {
    if (count[i] > 0) {
      value[m++] = i + 1;
    }
  }

  long long res = n;
  for (int i = 0; i < m; ++i) {
    long long c = count[value[i] - 1];
    if (c > 1) {
      res += c * (c - 1);
    }
    for (int j = i + 1; j < m; ++j) {
      long long c1 = count[value[j] - 1];
      res += c * c1 * value[j] / value[i];
    }
  }
  delete[] value;
  delete[] count;
  return res % kMod;
}

int main() {
  cout << sumOfFlooredPairs({2, 5, 9}) << endl;
  cout << sumOfFlooredPairs({7, 7, 7, 7, 7, 7, 7}) << endl;
  vector<int> vec(10e5);
  for (int i = 0; i < 10e5; ++i)
    vec[i] = 21;
  cout << sumOfFlooredPairs(vec) << endl;
  for (int i = 0; i < 10e5; ++i)
    vec[i] = 12;
  cout << sumOfFlooredPairs(vec) << endl;
  return 0;
}