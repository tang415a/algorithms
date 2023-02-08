/*
Given an array of integers heights representing the histogram's bar height where
the width of each bar is 1, return the area of the largest rectangle in the
histogram.

Example 1:

Input: heights = [2,1,5,6,2,3]
Output: 10

Explanation: The above is a histogram where width of each bar is 1.
The largest rectangle is shown in the red area, which has an area = 10 units.

Example 2:

Input: heights = [2,4]
Output: 4


Constraints:

1 <= heights.length <= 10^5
0 <= heights[i] <= 10^4
*/

#include <iostream>
#include <vector>

using namespace std;

int largestRectangleArea(const vector<int> &heights) {
  int ans = 0;
  vector<int> st;
  for (int i = 0, n = heights.size(); i <= n; ++i) {
    while (!st.empty() && (i == n || heights[i] < heights[st.back()])) {
      int j = st.back();
      st.pop_back();
      ans = max(ans, heights[j] * (st.empty() ? i : (i - st.back() - 1)));
      // if the stack is empty, then heights[j] is the min of first i elements
      // (i.e. heights[0..(i-1)]); else heights[j] is the min of
      // heights[back(st)+1..(i-1)] because it is a monotonic stack
    }
    st.push_back(i);
  }
  return ans;
}

int hgt [100001]; // mono stack
int pos [100001]; // the index inside array
int largestRectangleArea2(vector<int> &heights) {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  heights.push_back(0); // safety guard
  int ans = heights[0], n = heights.size(), m = 0;
  hgt[0] = heights[0];
  pos[0] = 0;
  for (int i = 1; i < n; ++i) {
    pos[m + 1] = i;
    for (; m >= 0 && heights[i] < hgt[m]; --m) {
      // cout<<hgt[m]<<":["<<pos[m]<<","<<i<<")\n";
      ans = max(ans, hgt[m] * (i - pos[m]));
    }
    // heights[i] corresponds to pos[m]
    // pos[m + 1] assigned at Ln. 58 becomes invalid if m has changed from the above for loop
    hgt[++m] = heights[i];
  }
  return ans;
}

int main() {
  cout << largestRectangleArea({2, 1, 5, 6, 2, 3}) << endl;
  cout << largestRectangleArea({2, 4}) << endl;
  vector<int> h = {2, 1, 5, 6, 2, 3};
  cout << largestRectangleArea2(h) << endl;
  return 0;
}