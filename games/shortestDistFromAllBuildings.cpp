/*
You want to build a house on an empty land which reaches all buildings in the
shortest amount of distance. You can only move up, down, left and right. You are
given a 2D grid of values 0, 1 or 2, where:

Each 0 marks an empty land which you can pass by freely.

Each 1 marks a building which you cannot pass through.

Each 2 marks an obstacle which you cannot pass through.

For example, given three buildings at (0,0), (0,4), (2,2), and an obstacle at
(0,2):

1 - 0 - 2 - 0 - 1
|   |   |   |   |
0 - 0 - 0 - 0 - 0
|   |   |   |   |
0 - 0 - 1 - 0 - 0
The point (1,2) is an ideal empty land to build a house, as the total travel
distance of 3+3+1=7 is minimal. So return 7.

Note: There will be at least one building. If it is not possible to build such
house according to the above rules, return -1.
*/

#include <iostream>
#include <queue>
#include <vector>

using namespace std;

// thoughts:
// The question requires BFS to solve, classic, generally need queue.
// * breadth-first search from building locations
// * establishment of distance field and count field
// * iteration of the distance field and count field to get the min
int shortestDistance(const vector<vector<int>> &grid) {
  int res = INT_MAX, buildingCnt = 0, m = grid.size(), n = grid[0].size();
  // the distance field and building count field
  vector<vector<int>> dist(m, vector<int>(n, 0)), cnt = dist;
  // directions
  vector<vector<int>> dirs{{0, -1}, {-1, 0}, {0, 1}, {1, 0}};
  for (int i = 0; i < m; ++i) {
    for (int j = 0; j < n; ++j) {
      if (grid[i][j] == 1) {
        ++buildingCnt;
        // pair is faster than vector
        queue<pair<int, int>> q;
        q.push({i, j});
        vector<vector<bool>> visited(m, vector<bool>(n, false));
        int level = 1;
        while (!q.empty()) {
          int size = q.size();
          for (int s = 0; s < size; ++s) {
            int a = q.front().first, b = q.front().second;
            q.pop();
            for (int k = 0; k < dirs.size(); ++k) {
              int x = a + dirs[k][0], y = b + dirs[k][1];
              // check if (x, y) is in the range, grid[x][y] is empty and the
              // grid is not visited before
              if (x >= 0 && x < m && y >= 0 && y < n && grid[x][y] == 0 &&
                  !visited[x][y]) {
                dist[x][y] += level;
                ++cnt[x][y];
                visited[x][y] = true;
                q.push({x, y});
              }
            }
          }
          ++level;
        }
      }
    }
  }
  for (int i = 0; i < m; ++i) {
    for (int j = 0; j < n; ++j) {
      // check if it is empty and all the buildings can be visited from here
      if (grid[i][j] == 0 && cnt[i][j] == buildingCnt) {
        res = min(res, dist[i][j]);
      }
    }
  }
  return res == INT_MAX ? -1 : res;
}

int main() {
  cout << shortestDistance({{1, 0, 2, 0, 1}, {0, 0, 0, 0, 0}, {0, 0, 1, 0, 0}})
       << endl;
  return 0;
}