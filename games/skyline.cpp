/*
A city's skyline is the outer contour of the silhouette formed by all the
buildings in that city when viewed from a distance. Given the locations and
heights of all the buildings, return the skyline formed by these buildings
collectively.

The geometric information of each building is given in the array buildings where
buildings[i] = [lefti, righti, heighti]:

lefti is the x coordinate of the left edge of the ith building.
righti is the x coordinate of the right edge of the ith building.
heighti is the height of the ith building.
You may assume all buildings are perfect rectangles grounded on an absolutely
flat surface at height 0.

The skyline should be represented as a list of "key points" sorted by their
x-coordinate in the form [[x1,y1],[x2,y2],...]. Each key point is the left
endpoint of some horizontal segment in the skyline except the last point in the
list, which always has a y-coordinate 0 and is used to mark the skyline's
termination where the rightmost building ends. Any ground between the leftmost
and rightmost buildings should be part of the skyline's contour.

Note: There must be no consecutive horizontal lines of equal height in the
output skyline. For instance, [...,[2 3],[4 5],[7 5],[11 5],[12 7],...] is not
acceptable; the three lines of height 5 should be merged into one in the final
output as such: [...,[2 3],[4 5],[12 7],...]

Example 1:

Input: buildings = [[2,9,10],[3,7,15],[5,12,12],[15,20,10],[19,24,8]]
Output: [[2,10],[3,15],[7,12],[12,0],[15,10],[20,8],[24,0]]
Explanation:
Figure A shows the buildings of the input.
Figure B shows the skyline formed by those buildings. The red points in figure B
represent the key points in the output list.

Example 2:

Input: buildings = [[0,2,3],[2,5,3]]
Output: [[0,3],[5,0]]


Constraints:

1 <= buildings.length <= 10^4
0 <= lefti < righti <= 2^31 - 1
1 <= heighti <= 2^31 - 1
buildings is sorted by lefti in non-decreasing order.
*/

// the principle of this problem is similar to min interval

#include <algorithm>
#include <iostream>
#include <set>
#include <vector>

using namespace std;

vector<vector<int>> getSkyline(const vector<vector<int>> &buildings) {
  set<vector<int>> s;
  for (int n = buildings.size(), i = 0; i < n; i++) {
    s.insert(vector<int>{buildings[i][0], i + 1});
    s.insert(vector<int>{buildings[i][1], -i - 1});
  }
  vector<vector<int>> res;
  auto comp = [&buildings](int i, int j) {
    return buildings[i][2] > buildings[j][2] ||
           (buildings[i][2] == buildings[j][2] && i < j);
  };
  set<int, decltype(comp)> curr(comp);
  while (!s.empty()) {
    int l = s.begin()->front();
    do {
      auto it = s.begin();
      if ((*it)[1] > 0)
        curr.insert((*it)[1] - 1);
      else
        curr.erase(curr.find(-(*it)[1] - 1));
      s.erase(it);
    } while (!s.empty() && s.begin()->front() == l);
    int h = curr.empty() ? 0 : buildings[*curr.begin()][2];
    if (res.empty() || res.back()[1] != h) {
      res.push_back(vector<int>{l, h});
    }
  }
  return res;
}

#include <queue>
vector<vector<int>> getSkyline2(const vector<vector<int>> &buildings) {
  int edge_idx = 0;
  vector<pair<int, int>> edges;
  priority_queue<pair<int, int>> pq;
  vector<vector<int>> skyline;

  for (int i = 0; i < buildings.size(); ++i) {
    const auto &b = buildings[i];
    // emplace all of the edges (starting and ending points)
    edges.emplace_back(b[0], i);
    edges.emplace_back(b[1], i);
  }

  // sort the edges in the ascending order of x (could be start or end)
  sort(edges.begin(), edges.end());

  while (edge_idx < edges.size()) {
    int curr_height;
    // the current x could be start or end
    const auto &[curr_x, _] = edges[edge_idx];
    // collect all the edges that start or end at current x
    while (edge_idx < edges.size() && curr_x == edges[edge_idx].first) {
      const auto &[_, building_idx] = edges[edge_idx];
      const auto &b = buildings[building_idx];
      // if the building starts at the current x, i.e. it is a start, bring it
      // in
      if (b[0] == curr_x)
        pq.emplace(b[2], b[1]); // the building comes in with height and end
      ++edge_idx;
    }
    // find the first building that has not ended at current x
    // as it is a priority queue, it is the maximum height
    while (!pq.empty() && pq.top().second <= curr_x)
      pq.pop();
    curr_height = pq.empty() ? 0 : pq.top().first;
    // check if the height has changed
    if (skyline.empty() || skyline.back()[1] != curr_height)
      skyline.push_back({curr_x, curr_height});
  }
  return skyline;
}

// helper function
void print(const vector<vector<int>> &skyline) {
  cout << "[";
  for (int n = skyline.size(), i = 0; i < n; i++) {
    cout << "[";
    for (int m = skyline[i].size(), j = 0; j < m - 1; j++) {
      cout << skyline[i][j] << ",";
    }
    cout << skyline[i].back() << "]";
    if (i < n - 1)
      cout << ",";
  }
  cout << "]";
}

int main() {
  vector<vector<int>> b = {
      {2, 9, 10}, {3, 7, 15}, {5, 12, 12}, {15, 20, 10}, {19, 24, 8}};
  auto skyline = getSkyline2(b);
  print(skyline);
  cout << endl;

  b = {{0, 2, 3}, {2, 5, 3}};
  skyline = getSkyline2(b);
  print(skyline);
  cout << endl;

  b = {{0, 3, 3}, {1, 5, 3}, {2, 4, 3}, {3, 7, 3}};
  skyline = getSkyline2(b);
  print(skyline);
  cout << endl;
  return 0;
}