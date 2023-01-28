/*
Given a non-empty array of integers, return the third maximum number in this
array. If it does not exist, return the maximum number. The time complexity must
be in O(n).

Example 1:
Input: [3, 2, 1]

Output: 1

Explanation: The third maximum is 1.
Example 2:
Input: [1, 2]

Output: 2

Explanation: The third maximum does not exist, so the maximum (2) is returned
instead. Example 3: Input: [2, 2, 3, 1]

Output: 1

Explanation: Note that the third maximum here means the third maximum distinct
number. Both numbers with value 2 are both considered as second maximum.
*/

#include <set>
#include <stdio.h>
#include <vector>

using namespace std;

int nthMax(const vector<int> &nums, int n) {
  set<int> s;
  for (auto &num : nums) {
    s.insert(num);
    if (s.size() > n)
      s.erase(s.begin());
  }
  return s.size() < n ? *s.rbegin() : *s.begin();
}

int thirdMax(const vector<int> &nums) { return nthMax(nums, 3); }

int thirdMax2(const vector<int> &nums) {
  int arr[3];
  bool valid[3] = {false, false, false};
  for (int n : nums) {
    for (int i = 0; i < 3; ++i) {
      if (!valid[i]) {
        valid[i] = true;
        arr[i] = n;
        break;
      }
      if (n == arr[i])
        break;
      if (n < arr[i])
        continue;
      for (int j = 2; j > i; --j) {
        if (!valid[j - 1])
          continue;
        arr[j] = arr[j - 1];
        if (!valid[j])
          valid[j] = true;
      }
      arr[i] = n;
      break;
    }
  }
  return valid[2] ? arr[2] : arr[0];
}

int main() {
  printf("%d\n", thirdMax({3, 2, 1}));
  printf("%d\n", thirdMax2({3, 2, 1}));
  printf("%d\n", thirdMax({1, 2}));
  printf("%d\n", thirdMax2({1, 2}));
  printf("%d\n", thirdMax({2, 2, 3, 1}));
  printf("%d\n", thirdMax2({2, 2, 3, 1}));
  printf("%d\n", thirdMax({2, 3, 1, 4}));
  printf("%d\n", thirdMax2({2, 3, 1, 4}));
  printf("%d\n", thirdMax({2, 2, 3, 1, 4}));
  printf("%d\n", thirdMax2({2, 2, 3, 1, 4}));
  printf("%d\n", thirdMax({2, 2, 3, 1, 1, 4}));
  printf("%d\n", thirdMax2({2, 2, 3, 1, 1, 4}));
  printf("%d\n", thirdMax({2, 2, 3, 4, 1, 4}));
  printf("%d\n", thirdMax2({2, 2, 3, 4, 1, 4}));
  printf("%d\n", thirdMax({2, 2, 4, 3, 1, 4}));
  printf("%d\n", thirdMax2({2, 2, 4, 3, 1, 4}));
  return 0;
}