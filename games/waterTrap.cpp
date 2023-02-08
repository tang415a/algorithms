/*
Given n non-negative integers representing an elevation map where the width of
each bar is 1, compute how much water it can trap after raining.

Example 1:

Input: height = [0,1,0,2,1,0,1,3,2,1,2,1]
Output: 6
Explanation: The above elevation map (black section) is represented by array
[0,1,0,2,1,0,1,3,2,1,2,1]. In this case, 6 units of rain water (blue section)
are being trapped.

Example 2:

Input: height = [4,2,0,3,2,5]
Output: 9


Constraints:

n == height.length
1 <= n <= 2 * 10^4
0 <= height[i] <= 10^5
*/

#include <iostream>
#include <vector>

using namespace std;
int trap(const vector<int> &height) {
  int ans = 0, n = height.size(), m = 0;
  vector<int> st(n);  // mono stack
  for (int i = 0, n = height.size(); i < n; ++i) {
    if (m > 0 && height[i] > st.back()) {
      if (st[0] <= height[i]) {
        while (--m > 0) {
          ans += st[0] - st[m];
        }
        st[m++] = height[i];
      } else {
        int j = m;
        while (st[--j] < height[i]) {
          ans += height[i] - st[j];
          st[j] = height[i];
        }
      }
    }
    st[m++] = height[i];
  }
  return ans;
}

// left[i]: the max height among the bars left to bar i and bar i
// right[i]: the max height among the bars right to bar i and bar i
// height[i] will become min(left[i], right[i]) after raining
int trap2(const vector<int> &height) {
  vector<int> right(height.size());
  vector<int> left(height.size());

  right[0] = height[0];
  left[height.size() - 1] = height[height.size() - 1];

  for (int i = 1; i < height.size(); i++) {
    right[i] = max(right[i - 1], height[i]);
  }

  for (int i = height.size() - 2; i >= 0; i--) {
    left[i] = max(left[i + 1], height[i]);
  }

  int ans = 0;

  for (int i = 0; i < height.size(); i++) {
    ans = ans + (min(right[i], left[i])) - height[i];
  }
  return ans;
}

int main() {
  cout << trap({0, 1, 0, 2, 1, 0, 1, 3, 2, 1, 2, 1}) << endl;
  cout << trap2({0, 1, 0, 2, 1, 0, 1, 3, 2, 1, 2, 1}) << endl;
  cout << trap({4, 2, 0, 3, 2, 5}) << endl;
  cout << trap2({4, 2, 0, 3, 2, 5}) << endl;
  cout << trap({3, 1, 6, 2, 5, 4, 7}) << endl;
  cout << trap2({3, 1, 6, 2, 5, 4, 7}) << endl;
  return 0;
}