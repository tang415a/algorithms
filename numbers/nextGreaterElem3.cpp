/*
You are given a 0-indexed array of non-negative integers nums. For each integer
in nums, you must find its respective second greater integer.

The second greater integer of nums[i] is nums[j] such that:

j > i
nums[j] > nums[i]
There exists exactly one index k such that nums[k] > nums[i] and i < k < j.
If there is no such nums[j], the second greater integer is considered to be -1.

For example, in the array [1, 2, 4, 3], the second greater integer of 1 is 4, 2
is 3, and that of 3 and 4 is -1. Return an integer array answer, where answer[i]
is the second greater integer of nums[i].

Example 1:

Input: nums = [2,4,0,9,6]
Output: [9,6,6,-1,-1]
Explanation:
0th index: 4 is the first integer greater than 2, and 9 is the second integer
greater than 2, to the right of 2. 1st index: 9 is the first, and 6 is the
second integer greater than 4, to the right of 4. 2nd index: 9 is the first, and
6 is the second integer greater than 0, to the right of 0. 3rd index: There is
no integer greater than 9 to its right, so the second greater integer is
considered to be -1. 4th index: There is no integer greater than 6 to its right,
so the second greater integer is considered to be -1. Thus, we return
[9,6,6,-1,-1].

Example 2:

Input: nums = [3,3]
Output: [-1,-1]
Explanation:
We return [-1,-1] since neither integer has any integer greater than it.


Constraints:

1 <= nums.length <= 10^5
0 <= nums[i] <= 10^9
*/

#include <iostream>
#include <vector>

using namespace std;

#include <set>
vector<int> secondGreaterElement(const vector<int> &nums) {
  int n = nums.size();
  vector<int> res(n, -1);
  auto compare = [&nums](int i, int j) { return nums[i] < nums[j]; };
  set<int, decltype(compare)> s(compare);
  for (int i = 0; i < n; i++) {
    if (!s.empty()) {
      auto it = s.upper_bound(i);
      while (it != s.begin()) {
        --it;
        if (res[*it] == -2) {
          res[*it] = nums[i];
          it = s.erase(it);
        } else {
          res[*it] = -2;
        }
      }
    }
    s.insert(i);
  }
  for (int i : s) {
    res[i] = -1;
  }
  return res;
}

int main() {
  auto r = secondGreaterElement({2, 4, 0, 9, 6});
  for (int i : r)
    cout << i << " ";
  cout << endl;
  r = secondGreaterElement({3, 3});
  for (int i : r)
    cout << i << " ";
  cout << endl;
  return 0;
}