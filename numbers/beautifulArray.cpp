/*
An array nums of length n is beautiful if:

nums is a permutation of the integers in the range [1, n].
For every 0 <= i < j < n, there is no index k with i < k < j where 2 * nums[k]
== nums[i] + nums[j]. Given the integer n, return any beautiful array nums of
length n. There will be at least one valid answer for the given n.

Example 1:

Input: n = 4
Output: [2,1,4,3]

Example 2:

Input: n = 5
Output: [3,1,2,5,4]

Constraints:

1 <= n <= 1000
*/

#include <iostream>
#include <map>
#include <vector>

using namespace std;

// hints:
// https://leetcode.com/problems/beautiful-array/solutions/186841/official-solution/
// Patterns:
// * if an array Ni is "arithmetic-free", then a * Ni + b is also
//   "arithmetic-free"
// * the sum of odd element and even element is odd
// * a permutation of the integers in the range [1, n] consists of (n + 1) / 2
//   odd numbers and n / 2 even numbers
vector<int> beautifulArray(int n, map<int, vector<int>> &memo) {
  auto iter = memo.find(n);
  if (iter != memo.end())
    return iter->second;
  vector<int> ans(n);
  if (n == 1) {
    ans[0] = 1;
  } else {
    vector<int> arr1 = beautifulArray((n + 1) / 2, memo),
                arr2 = beautifulArray(n / 2, memo);
    int i = 0;
    // map [1..n] to [1,3,5,..,2 * n - 1]
    for (int m = arr1.size(); i < m; i++) {
      ans[i] = 2 * arr1[i] - 1;
    }
    // map [1..n] to [2,4,6,..,2 * n]
    for (int j = 0, m = arr2.size(); j < m; j++) {
      ans[i + j] = 2 * arr2[j];
    }
  }
  memo.insert(make_pair(n, ans));
  memo.insert(make_pair(n, ans));
  return ans;
}

vector<int> beautifulArray(int n) {
  map<int, vector<int>> memo;
  return beautifulArray(n, memo);
}

int main() {
  auto arr = beautifulArray(4);
  for (int i : arr)
    cout << i << " ";
  cout << endl;
  arr = beautifulArray(5);
  for (int i : arr)
    cout << i << " ";
  cout << endl;
  arr = beautifulArray(10);
  for (int i : arr)
    cout << i << " ";
  cout << endl;
  return 0;
}
