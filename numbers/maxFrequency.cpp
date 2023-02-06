/*
The frequency of an element is the number of times it occurs in an array.

You are given an integer array nums and an integer k. In one operation, you can
choose an index of nums and increment the element at that index by 1.

Return the maximum possible frequency of an element after performing at most k
operations.



Example 1:

Input: nums = [1,2,4], k = 5
Output: 3
Explanation: Increment the first element three times and the second element two
times to make nums = [4,4,4]. 4 has a frequency of 3. Example 2:

Input: nums = [1,4,8,13], k = 5
Output: 2
Explanation: There are multiple optimal solutions:
- Increment the first element three times to make nums = [4,4,8,13]. 4 has a
frequency of 2.
- Increment the second element four times to make nums = [1,8,8,13]. 8 has a
frequency of 2.
- Increment the third element five times to make nums = [1,4,13,13]. 13 has a
frequency of 2. Example 3:

Input: nums = [3,9,6], k = 2
Output: 1


Constraints:

1 <= nums.length <= 10^5
1 <= nums[i] <= 10^5
1 <= k <= 10^5
*/
#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

int maxFrequency(vector<int> &nums, int k) {
  sort(nums.begin(), nums.end());
  int sums = 0, i = 0, j = 0;
  for (int n = nums.size(); i < n; ++i) {
    sums += nums[i];
    if ((i - j + 1) * nums[i] - sums > k)
      sums -= nums[j++];
  }
  return i - j;
}

int maxFrequency2(vector<int> const &nums, int k) {
  auto cpy = nums;
  sort(cpy.begin(), cpy.end());
  int r = cpy[0], m = 2;
  for (int i = 1, n = cpy.size(); i < n; i++) {
    r += cpy[i];
    if (m * cpy[i] - r > k) {
      r -= cpy[i + 1 - m];
    } else {
      m++;
    }
  }
  return m - 1;
}

int main() {
  vector<int> nums = {1, 2, 4};
  cout << maxFrequency(nums, 5) << endl;
  cout << maxFrequency2(nums, 5) << endl;
  nums = {1, 4, 8, 13};
  cout << maxFrequency(nums, 5) << endl;
  cout << maxFrequency2(nums, 5) << endl;
  nums = {3, 9, 6};
  cout << maxFrequency(nums, 2) << endl;
  cout << maxFrequency2(nums, 2) << endl;
  return 0;
}
