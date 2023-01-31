/*
You want to build n new buildings in a city. The new buildings will be built in a line and are labeled from 1 to n.

However, there are city restrictions on the heights of the new buildings:

The height of each building must be a non-negative integer.
The height of the first building must be 0.
The height difference between any two adjacent buildings cannot exceed 1.
Additionally, there are city restrictions on the maximum height of specific buildings. These restrictions are given as a 2D integer array restrictions where restrictions[i] = [idi, maxHeighti] indicates that building idi must have a height less than or equal to maxHeighti.

It is guaranteed that each building will appear at most once in restrictions, and building 1 will not be in restrictions.

Return the maximum possible height of the tallest building.



Example 1:


Input: n = 5, restrictions = [[2,1],[4,1]]
Output: 2
Explanation: The green area in the image indicates the maximum allowed height for each building.
We can build the buildings with heights [0,1,2,1,2], and the tallest building has a height of 2.

Example 2:


Input: n = 6, restrictions = []
Output: 5
Explanation: The green area in the image indicates the maximum allowed height for each building.
We can build the buildings with heights [0,1,2,3,4,5], and the tallest building has a height of 5.

Example 3:


Input: n = 10, restrictions = [[5,3],[2,5],[7,4],[10,3]]
Output: 5
Explanation: The green area in the image indicates the maximum allowed height for each building.
We can build the buildings with heights [0,1,2,3,3,4,4,5,4,3], and the tallest building has a height of 5.


Constraints:

2 <= n <= 10^9
0 <= restrictions.length <= min(n - 1, 10^5)
2 <= idi <= n
idi is unique.
0 <= maxHeighti <= 10^9

*/

#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

int maxBuilding(int n, vector<vector<int>> &restrictions)
{
  sort(begin(restrictions), end(restrictions));
  for (int s = restrictions.size(), i = s - 1; i >= 0; --i) {
    if (restrictions[i][1] >= restrictions[i][0] - 1)
      restrictions.erase(restrictions.begin() + i);
  }
  if (restrictions.empty())
    return n - 1;
  for (int i = 1, s = restrictions.size(); i < s; ) {
    int d = restrictions[i][0] - restrictions[i - 1][0];
    if (restrictions[i][1] - restrictions[i - 1][1] > d) {
      restrictions[i][1] = restrictions[i - 1][1] + d;
    }
    else if (restrictions[i - 1][1] - restrictions[i][1] > d) {
      restrictions[i - 1][1] = restrictions[i][1] + d;
      if (i > 1) {
        --i;
        continue;
      }
    }
    ++i;
  }

  int r = 0, x = 1, y = 0;
  for (auto& i : restrictions) {
    int ym = (i[0] - x + i[1] + y) / 2;
    if (r < ym) r = ym;
    x = i[0];
    y = i[1];
  }
  int ym = y + n - x;
  if (r < ym) return ym;
  return r;
}

int main() {
  vector<vector<int>> restrictions = {{2,1},{4,1}};
  cout << maxBuilding(5, restrictions) << endl;
  restrictions = {};
  cout << maxBuilding(6, restrictions) << endl;
  restrictions = {{5,3},{2,5},{7,4},{10,3}};
  cout << maxBuilding(10, restrictions) << endl;
  restrictions = {{10,8},{12,5},{15,1}};
  cout << maxBuilding(20, restrictions) << endl;
  return 0;
}