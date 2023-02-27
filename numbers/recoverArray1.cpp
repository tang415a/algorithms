/*
You are given an integer n representing the length of an unknown array that you
are trying to recover. You are also given an array sums containing the values of
all 2n subset sums of the unknown array (in no particular order).

Return the array ans of length n representing the unknown array. If multiple
answers exist, return any of them.

An array sub is a subset of an array arr if sub can be obtained from arr by
deleting some (possibly zero or all) elements of arr. The sum of the elements in
sub is one possible subset sum of arr. The sum of an empty array is considered
to be 0.

Note: Test cases are generated such that there will always be at least one
correct answer.

Example 1:

Input: n = 3, sums = [-3,-2,-1,0,0,1,2,3]
Output: [1,2,-3]
Explanation: [1,2,-3] is able to achieve the given subset sums:
- []: sum is 0
- [1]: sum is 1
- [2]: sum is 2
- [1,2]: sum is 3
- [-3]: sum is -3
- [1,-3]: sum is -2
- [2,-3]: sum is -1
- [1,2,-3]: sum is 0
Note that any permutation of [1,2,-3] and also any permutation of [-1,-2,3] will
also be accepted.

Example 2:

Input: n = 2, sums = [0,0,0,0]
Output: [0,0]
Explanation: The only correct answer is [0,0].
Example 3:

Input: n = 4, sums = [0,0,5,5,4,-1,4,9,9,-1,4,3,4,8,3,8]
Output: [0,-1,4,5]
Explanation: [0,-1,4,5] is able to achieve the given subset sums.


Constraints:

1 <= n <= 15
sums.length == 2n
-10^4 <= sums[i] <= 10^4
*/
#include <iostream>
#include <set>
#include <vector>

using namespace std;

// https://leetcode.cn/problems/find-array-given-subset-sums/solution/-by-ustcyyw-1yop/
// observations:
// if all of the elements is non-negative:
// 1. we exclude 0 among the sums then the minimum number of the rest i is the
// min element of the original array;
// 2. we exclude i among the sums then the minimum number of the rest j is the
// second smallest element of the original array
// but we cannot continue doing the same thing in step 3 because it is possible
// i + j < k (k is the third smallest element of the original array)
// 3. we exclude j, i + j among the sums then the minimum number of the rest is
// k, the third smallest element of the original array
// 4. we exclude k, i + k, ..., i + j + k, all of the permutation of [i, j, k]
// among the sums then the minimal element of the rest is the fourth smallest
// element l
// remove the sum of permutation of input array
int remove(multiset<int> &set, vector<int> &arr) {
  int n = arr.size(), u = (1 << n) - 1;
  for (int s = u; s; s = u & (s - 1)) {
    // if the highest bit is not set, then the newly added element is not chosen
    // this is the case we have processed before (the permutation of first n - 1
    // elements in array)
    if (!((1 << (n - 1)) & s))
      continue;
    int sum = 0;
    for (int j = 0; j < n; j++)
      if ((1 << j) & s)
        sum += arr[j];
    set.erase(set.find(sum));
  }
  return *set.begin(); // the minimal sum after removing the elements
}

vector<int> recoverNoneNegArray(int n, vector<int> &sums) {
  // Multisets are a type of associative containers similar to the set, with the
  // exception that multiple elements can have the same values.
  multiset<int> set;
  for (int sum : sums)
    set.insert(sum);
  set.erase(set.begin()); // erase 0
  vector<int> res;
  while (res.size() < n)
    res.push_back(remove(set, res));
  return res;
}

// hints:
// t is the sum of all of the negative elements in the array
// if all of the sums subtract t, it means:
// a) if the current sum includes the negative element i, then it becomes 0
// after subtraction, i.e. doesn't include |i| (the absolute value of i)
// b) if the current sum doesn't include the negative element i, then it becomes
// -i after subtraction, i.e. include |i| (the absolute value of i)
// therefore, after subtraction we transform the sums of the permutations of
// original elements to the sums of the permutations of absolute values of
// original elements
// we can find t by iterating the possible permutations of negative values of
// elements, then we know they should be negative
vector<int> recoverArray(int n, vector<int> &sums) {
  int t = 1e5;
  for (int num : sums)
    t = min(t, num);
  if (t >= 0)
    return recoverNoneNegArray(n, sums);
  for (int &sum : sums)
    sum -= t;
  vector<int> res = recoverNoneNegArray(n, sums);
  int u = (1 << n) - 1, s = u;
  // find the t by reverting the positive i to negative -i
  // s is the bit set status we iterate each time
  for (; s; s = u & (s - 1)) {
    int sum = 0;
    for (int j = 0; j < n; j++)
      if ((1 << j) & s)
        sum -= res[j];
    if (sum == t) // we found t: s is the bit set status
      break;
  }
  for (int j = 0; j < n; j++)
    if ((1 << j) & s)
      res[j] = -res[j]; // res[j] should be negative; revert it
  return res;
}

// check if the answer is correct, i.e. to be able to achieve the given subset
// sums
bool check(const vector<int> &sums, const vector<int> &ans) {
  multiset<int> set;
  for (int sum : sums)
    set.insert(sum);
  int n = ans.size(), s = (1 << n) - 1, u = s;
  for (; u; u = s & (u - 1)) {
    int sum = 0;
    for (int i = 0; i < n; i++) {
      if ((1 << i) & u) {
        sum += ans[i];
      }
    }
    auto iter = set.find(sum);
    if (iter == set.end())
      return false;
    set.erase(iter);
  }
  return true;
}

int main() {
  vector<int> sums = {-3, -2, -1, 0, 0, 1, 2, 3}, cpy = sums;
  auto r = recoverArray(3, cpy);
  for (int i : r) {
    cout << i << " ";
  }
  cout << endl << check(sums, r) << endl;
  sums = cpy = {0, 0, 5, 5, 4, -1, 4, 9, 9, -1, 4, 3, 4, 8, 3, 8};
  r = recoverArray(4, cpy);
  for (int i : r) {
    cout << i << " ";
  }
  cout << endl << check(sums, r) << endl;
  return 0;
}