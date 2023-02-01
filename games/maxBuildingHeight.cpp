/*
You want to build n new buildings in a city. The new buildings will be built in
a line and are labeled from 1 to n.

However, there are city restrictions on the heights of the new buildings:

The height of each building must be a non-negative integer.
The height of the first building must be 0.
The height difference between any two adjacent buildings cannot exceed 1.
Additionally, there are city restrictions on the maximum height of specific
buildings. These restrictions are given as a 2D integer array restrictions where
restrictions[i] = [idi, maxHeighti] indicates that building idi must have a
height less than or equal to maxHeighti.

It is guaranteed that each building will appear at most once in restrictions,
and building 1 will not be in restrictions.

Return the maximum possible height of the tallest building.



Example 1:


Input: n = 5, restrictions = [[2,1],[4,1]]
Output: 2
Explanation: The green area in the image indicates the maximum allowed height
for each building. We can build the buildings with heights [0,1,2,1,2], and the
tallest building has a height of 2.

Example 2:


Input: n = 6, restrictions = []
Output: 5
Explanation: The green area in the image indicates the maximum allowed height
for each building. We can build the buildings with heights [0,1,2,3,4,5], and
the tallest building has a height of 5.

Example 3:


Input: n = 10, restrictions = [[5,3],[2,5],[7,4],[10,3]]
Output: 5
Explanation: The green area in the image indicates the maximum allowed height
for each building. We can build the buildings with heights
[0,1,2,3,3,4,4,5,4,3], and the tallest building has a height of 5.


Constraints:

2 <= n <= 10^9
0 <= restrictions.length <= min(n - 1, 10^5)
2 <= idi <= n
idi is unique.
0 <= maxHeighti <= 10^9

*/

#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

int maxBuilding(int n, vector<vector<int>> &restrictions)
{
  sort(begin(restrictions), end(restrictions));
  for (int s = restrictions.size(), i = s - 1; i >= 0; --i)
  {
    if (restrictions[i][1] >= restrictions[i][0] - 1)
      restrictions.erase(restrictions.begin() + i);
  }
  if (restrictions.empty())
    return n - 1;
  for (int i = 1, s = restrictions.size(); i < s; ++i)
  {
    int d = restrictions[i][0] - restrictions[i - 1][0];
    if (restrictions[i][1] - restrictions[i - 1][1] > d)
    {
      restrictions[i][1] = restrictions[i - 1][1] + d;
    }
    else if (restrictions[i - 1][1] - restrictions[i][1] > d)
    {
      // restrictions[i - 1][1] = restrictions[i][1] + d;
      // if (i > 1) {
      //   --i;
      //   continue;
      // }
      do
      {
        restrictions[i - 1][1] = restrictions[i][1] + d;
      } while (--i > 0 && (restrictions[i - 1][1] - restrictions[i][1] >
                           (d = restrictions[i][0] - restrictions[i - 1][0])));
    }
  }

  int r = 0, x = 1, y = 0;
  for (auto &i : restrictions)
  {
    int ym = (i[0] - x + i[1] + y) / 2;
    if (r < ym)
      r = ym;
    x = i[0];
    y = i[1];
  }
  int ym = y + n - x;
  if (r < ym)
    return ym;
  return r;
}

struct RData
{
  int d = 0, s = 0;
};

int maxBuilding2(int n, vector<vector<int>> &restrictions)
{
  sort(begin(restrictions), end(restrictions));
  int s = restrictions.size();
  vector<RData> c(s);
  int k = -1;
  for (int i = 0; i < s; i++)
  {
    int d = restrictions[i][1] - restrictions[i][0];
    if (d >= k)
      continue;
    c[i].d = k = d;
  }
  k = n << 1;
  for (int i = s - 1; i >= 0; i--)
  {
    if (c[i].d == 0)
      continue;
    int d = restrictions[i][0] + restrictions[i][1];
    if (d >= k)
      continue;
    c[i].s = k = d;
  }
  k = -1;
  int ans = 0;
  for (int i = 0; i < s; i++)
  {
    if (c[i].s == 0)
      continue;
    int ym = (k + c[i].s) / 2;
    if (ans < ym)
      ans = ym;
    k = c[i].d;
  }
  int ym = n + k;
  if (ans < ym)
    return ym;
  return ans;
}

int maxBuilding3(int n, vector<vector<int>> restrictions)
{
  vector<pair<int, int>> segments;
  for (const auto &r : restrictions)
  {
    segments.push_back(make_pair(r[0], r[1]));
  }
  segments.push_back(make_pair(1, 0));
  segments.push_back(make_pair(n, n));
  sort(segments.begin(), segments.end());

  int m = segments.size();

  vector<int> lcaps(m);
  lcaps[0] = 0;
  for (int k = 1; k < m; ++k)
  {
    lcaps[k] = min(segments[k].second, lcaps[k - 1] + segments[k].first - segments[k - 1].first);
  }

  vector<int> rcaps(m);
  rcaps[m - 1] = n;
  for (int k = m - 2; k >= 0; --k)
  {
    rcaps[k] = min(segments[k].second, rcaps[k + 1] + segments[k + 1].first - segments[k].first);
  }

  int tallest = 0;
  for (int k = 0; k < m - 1; ++k)
  {
    int x1 = segments[k].first;
    int h1 = min(lcaps[k], rcaps[k]);

    int x2 = segments[k + 1].first;
    int h2 = min(lcaps[k + 1], rcaps[k + 1]);

    tallest = max(tallest, max(h1, h2) + (int)ceil(((x2 - x1) - abs(h2 - h1)) / 2));
  }
  return tallest;
}

int main()
{
  // {
  //   vector<vector<int>> restrictions = {{10, 8}, {12, 5}, {15, 1}};
  // cout << maxBuilding(20, restrictions) << endl;
  // restrictions = {{15, 1}};
  // cout << maxBuilding(20, restrictions) << endl;
  // return 0;
  // }
  vector<vector<int>> restrictions = {{2, 1}, {4, 1}};
  int n = 5;
  if (maxBuilding2(n, restrictions) != maxBuilding(n, restrictions))
  {
    cout << "err" << endl;
    return 1;
  }
  restrictions = {};
  n = 6;
  if (maxBuilding2(n, restrictions) != maxBuilding(n, restrictions))
  {
    cout << "err" << endl;
    return 1;
  }
  restrictions = {{5, 3}, {2, 5}, {7, 4}, {10, 3}};
  n = 10;
  if (maxBuilding2(n, restrictions) != maxBuilding(n, restrictions))
  {
    cout << "err" << endl;
    return 1;
  }
  restrictions = {{10, 8}, {12, 5}, {15, 1}};
  n = 20;
  if (maxBuilding2(n, restrictions) != maxBuilding(n, restrictions))
  {
    cout << "err" << endl;
    return 1;
  }
  restrictions = {{10, 9}, {15, 5}};
  if (maxBuilding2(n, restrictions) != maxBuilding(n, restrictions))
  {
    cout << "err" << endl;
    return 1;
  }
  restrictions = {{10, 5}, {12, 7}, {15, 1}};
  if (maxBuilding2(n, restrictions) != maxBuilding(n, restrictions))
  {
    cout << "err" << endl;
    return 1;
  }
  restrictions = {{1, 7}, {2, 7}, {3, 7}, {4, 7}, {5, 7}, {7, 7}, {8, 7}, {9, 7}, {10, 7}};
  n = 10;
  if (maxBuilding2(n, restrictions) != maxBuilding(n, restrictions))
  {
    cout << "err" << endl;
    return 1;
  }
  return 0;
}