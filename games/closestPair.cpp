/*
We are given an array of n points in the plane, and the problem is to find out
the closest pair of points in the array. This problem arises in a number of
applications.

For example, in air-traffic control, you may want to monitor planes that come
too close together, since this may indicate a possible collision.

Recall the following formula for distance between two points p and q.
|PQ| = sqrt((Px-Qx)^2+ (Py-Qy)^2)
*/

#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

// https://www.geeksforgeeks.org/closest-pair-of-points-using-divide-and-conquer-algorithm/
float distance(const vector<int> &left, const vector<int> &right) {
  return sqrtf(static_cast<float>((left[0] - right[0]) * (left[0] - right[0]) +
                                  (left[1] - right[1]) * (left[1] - right[1])));
}

float bruteForce(const vector<vector<int>> &pts, int start, int end) {
  float d = FLT_MAX;
  for (int i = start; i < end - 1; i++) {
    float di = distance(pts[i], pts[i + 1]);
    if (di < d)
      d = di;
  }
  return d;
}

float stripClosest(const vector<vector<int>> &pts, vector<int> &indices,
                  int target, float d) {
  int i = target;
  while (--i >= 0 && pts[target][0] - pts[i][0] < d) {
    indices.emplace_back(i);
  }
  i = target;
  int n = pts.size();
  while (++i < n && pts[i][0] - pts[target][0] < d) {
    indices.emplace_back(i);
  }
  sort(indices.begin(), indices.end(),
       [&pts](int i, int j) { return pts[i][1] < pts[j][1]; });

  float min = d;
  // Pick all points one by one and try the next points till the difference
  // between y coordinates is smaller than d.
  for (int i = 0, m = indices.size(); i < m - 1; i++) {
    // This is a proven fact that this loop runs at most 6 times
    for (int j = i + 1; j < m && pts[j][1] - pts[i][1] < min; j++) {
      float dj = distance(pts[i], pts[j]);
      if (dj < min) {
        min = dj;
      }
    }
  }
  return min;
}

float closestPair(const vector<vector<int>> &pts, int start, int end) {
  if (end - start <= 3) {
    return bruteForce(pts, start, end);
  }
  int mid = start + (end - start) / 2;
  float d1 = closestPair(pts, start, mid), d2 = closestPair(pts, mid, end);
  float d = min(d1, d2);
  vector<int> indices;
  return min(d, stripClosest(pts, indices, mid, d));
}

float closestPair(const vector<vector<int>> &pts) {
  auto cpy = pts;
  sort(cpy.begin(), cpy.end());
  return closestPair(cpy, 0, cpy.size());
}

int main() {
  cout << closestPair({{2, 3}, {12, 30}, {40, 50}, {5, 1}, {12, 10}, {3, 4}})
       << endl;
  return 0;
}