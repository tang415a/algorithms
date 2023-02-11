/*
Given a circular integer array nums (i.e., the next element of nums[nums.length
- 1] is nums[0]), return the next greater number for every element in nums.

The next greater number of a number x is the first greater number to its
traversing-order next in the array, which means you could search circularly to
find its next greater number. If it doesn't exist, return -1 for this number.

Example 1:

Input: nums = [1,2,1]
Output: [2,-1,2]
Explanation: The first 1's next greater number is 2;
The number 2 can't find next greater number.
The second 1's next greater number needs to search circularly, which is also 2.

Example 2:

Input: nums = [1,2,3,4,3]
Output: [2,3,4,-1,4]


Constraints:

1 <= nums.length <= 10^4
-10^9 <= nums[i] <= 10^9

*/

#include <iostream>
#include <vector>

using namespace std;

vector<int> nextGreaterElements(const vector<int> &nums) {
  int n = nums.size(), s = 0;
  vector<int> st(n), res(n, -1);
  for (int i = 0; i < n; i++) {
    while (s > 0 && nums[st[s - 1]] < nums[i]) {
      res[st[--s]] = nums[i];
    }
    st[s++] = i;
  }
  int i = 0;
  while (s > 1 && i < n) {
    while (s > 1 && nums[st[s - 1]] < nums[i]) {
      res[st[--s]] = nums[i];
    }
    i++;
  }
  return res;
}

/*
stack           nums[n - 1]       stack
nums[0]              |            nums[n-1]   ---- circular searching order
nums[1]              |            nums[i]
...                \ | /          ...
nums[n-1]           \|/           nums[n-1]

nums[0..i-1] smaller than nums[n-1] erased and nums[i] is greater than nums[n-1]

When pushing an item j to the stack, the items smaller than j and also behind j
in the circular searching order will be erased since with the presence of j,
these items are useless. In the next round, j will be the first item to compare.
*/
#include <stack>
vector<int> nextGreaterElements2(const vector<int> &nums) {
  stack<int> st;
  vector<int> ans;

  for (int i = nums.size() - 1; i >= 0; i--) {
    st.push(nums[i]);
  }

  for (int i = nums.size() - 1; i >= 0; i--) {
    while (!st.empty() && nums[i] >= st.top()) {
      st.pop();
    }

    if (!st.empty()) {
      ans.push_back(st.top());
    } else {
      ans.push_back(-1);
    }

    st.push(nums[i]);
  }

  reverse(ans.begin(), ans.end());

  return ans;
}

int main() {
  auto r = nextGreaterElements({1, 2, 1});
  for (int i : r)
    cout << i << " ";
  cout << endl;
  r = nextGreaterElements({1, 2, 3, 4, 3});
  for (int i : r)
    cout << i << " ";
  cout << endl;
  r = nextGreaterElements2({1, 2, 1});
  for (int i : r)
    cout << i << " ";
  cout << endl;
  r = nextGreaterElements2({1, 2, 3, 4, 3});
  for (int i : r)
    cout << i << " ";
  cout << endl;
  return 0;
}