/*
Given a set of points, a Convex hull is the smallest convex polygon containing
all the given points.

Example 1:
Input : points[] = {{0, 3}, {1, 1}, {2, 2}, {4, 4},
                    {0, 0}, {1, 2}, {3, 1}, {3, 3}};
Output :  The points in convex hull are:
          (0, 0) (0, 3) (3, 1) (4, 4)

Example 2:
Input : points[] = {{0, 3}, {1, 1}}
Output : Not Possible
There must be at least three points to form a hull.

Example 3:
Input  : points[] = {{0, 0}, {0, 4}, {-4, 0}, {5, 0},
                     {0, -6}, {1, 0}};
Output : (-4, 0), (5, 0), (0, -6), (0, 4)
*/

#include <algorithm>
#include <iostream>
#include <set>
#include <vector>

using namespace std;

/*
https://www.geeksforgeeks.org/quickhull-algorithm-convex-hull/
Following are the steps for finding the convex hull of the points.
1. Find the point with minimum x-coordinate lets say, min_x and similarly the
point with maximum x-coordinate, max_x.
2. Make a line joining these two points, say L. This line will divide the whole
set into two parts. Take both the parts one by one and proceed further.
3. For a part, find the point P with maximum distance from the line L. P forms a
triangle with the points min_x, max_x.

It is clear that the points residing inside this triangle can never be the part
of convex hull.

4. The above step divides the problem into two sub-problems (solved
recursively). Now the line joining the points P and min_x and the line joining
the points P and max_x are new lines and the points residing outside the
triangle is the set of points. Repeat point no. 3 till there no point left with
the line. Add the end points of this point to the convex hull.
*/

float distance(const vector<int> &left, const vector<int> &right) {
  return sqrtf(static_cast<float>((left[0] - right[0]) * (left[0] - right[0]) +
                                  (left[1] - right[1]) * (left[1] - right[1])));
}

float perpendicularDistance(const vector<int> &left, const vector<int> &right,
                            const vector<int> &pt) {
  float dx1 = right[0] - left[0], dx2 = pt[0] - left[0];
  float dy1 = right[1] - left[1], dy2 = pt[1] - left[1];
  float crossProduct = dx1 * dy2 - dy1 * dx2;
  return crossProduct / distance(left, right);
}

bool orient(const vector<int> &left, const vector<int> &right,
            const vector<int> &pt) {
  float dx1 = right[0] - left[0], dx2 = pt[0] - left[0];
  float dy1 = right[1] - left[1], dy2 = pt[1] - left[1];
  return dx1 * dy2 - dy1 * dx2 > 0;
}

bool insideTriangle(const vector<int> &a, const vector<int> &b,
                    const vector<int> &c, const vector<int> &p) {
  return orient(a, b, p) && orient(b, c, p) && orient(c, a, p);
}

void hull(vector<int> &h, const vector<vector<int>> &pts, int min, int max,
          const set<int> &in) {
  if (in.size() == 1) {
    for (int i : in) {
      h.emplace_back(i);
    }
    return;
  }

  float top = 0, bottom = 0;
  int topPt = -1, bottomPt = -1;
  set<int> topSet, bottomSet;
  for (auto iter = in.begin(); iter != in.end(); iter++) {
    float d = perpendicularDistance(pts[min], pts[max], pts[*iter]);
    if (d > top) {
      top = d;
      topPt = *iter;
    } else if (d < bottom) {
      bottom = d;
      bottomPt = *iter;
    }
    if (d > 0) {
      topSet.insert(*iter);
    } else if (d < 0) {
      bottomSet.insert(*iter);
    }
  }

  auto iter = topSet.begin();
  while (iter != topSet.end()) {
    if (*iter == topPt || insideTriangle(pts[min], pts[max], pts[topPt], pts[*iter])) {
      iter = topSet.erase(iter);
    } else {
      iter++;
    }
  }

  iter = bottomSet.begin();
  while (iter != bottomSet.end()) {
    if (*iter == bottomPt || insideTriangle(pts[min], pts[bottomPt], pts[max], pts[*iter])) {
      iter = bottomSet.erase(iter);
    } else {
      iter++;
    }
  }

  if (topPt >= 0) {
    h.emplace_back(topPt);
    hull(h, pts, min, topPt, topSet);
    hull(h, pts, topPt, max, topSet);
  }

  if (bottomPt >= 0) {
    h.emplace_back(bottomPt);
    hull(h, pts, min, bottomPt, bottomSet);
    hull(h, pts, bottomPt, max, bottomSet);
  }
}

void hull(vector<int> &h, vector<vector<int>> &pts) {
  int n = pts.size();
  if (n < 3)
    return;
  sort(pts.begin(), pts.end());
  set<int> s;
  for (int i = 1; i < n - 1; i++) {
    s.insert(i);
  }
  h.emplace_back(0);
  h.emplace_back(n - 1);
  hull(h, pts, 0, n - 1, s);
}

// helper function
void print(const vector<int> &h, const vector<vector<int>> &pts) {
  for (int i : h) {
    cout << "(" << pts[i][0] << "," << pts[i][1] << ") ";
  }
}

int main() {
  vector<vector<int>> pts = {{0, 3}, {1, 1}, {2, 2}, {4, 4},
                             {0, 0}, {1, 2}, {3, 1}, {3, 3}};
  vector<int> h;
  hull(h, pts);
  print(h, pts);
  cout << endl;

  h.clear();
  pts = {{0, 3}, {1, 1}};
  hull(h, pts);
  print(h, pts);
  cout << endl;

  h.clear();
  pts = {{0, 0}, {0, 4}, {-4, 0}, {5, 0}, {0, -6}, {1, 0}};
  hull(h, pts);
  print(h, pts);
  cout << endl;
  return 0;
}