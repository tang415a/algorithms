/*
Given a non-empty 2D array grid of 0's and 1's, an island is a group of 1's
(representing land) connected 4-directionally (horizontal or vertical.) You may
assume all four edges of the grid are surrounded by water.

Find the maximum area of an island in the given 2D array. (If there is no
island, the maximum area is 0.)

Example 1:
[[0,0,1,0,0,0,0,1,0,0,0,0,0],
 [0,0,0,0,0,0,0,1,1,1,0,0,0],
 [0,1,1,0,1,0,0,0,0,0,0,0,0],
 [0,1,0,0,1,1,0,0,1,0,1,0,0],
 [0,1,0,0,1,1,0,0,1,1,1,0,0],
 [0,0,0,0,0,0,0,0,0,0,1,0,0],
 [0,0,0,0,0,0,0,1,1,1,0,0,0],
 [0,0,0,0,0,0,0,1,1,0,0,0,0]]
Given the above grid, return 6. Note the answer is not 11, because the island
must be connected 4-directionally.

Example 2:
[[0,0,0,0,0,0,0,0]]
Given the above grid, return 0.
Note: The length of each dimension in the given grid does not exceed 50.
*/

#include <stdio.h>
#include <vector>
using namespace std;

int maxAreaFromPos(vector<vector<int>> &grid, int i, int j, int rows,
                   int cols) {
  if (grid[i][j] != 1)
    return 0;
  grid[i][j] = 2;
  int area = 1;
  if (i > 0)
    area += maxAreaFromPos(grid, i - 1, j, rows, cols);
  if (j > 0)
    area += maxAreaFromPos(grid, i, j - 1, rows, cols);
  if (i < rows - 1)
    area += maxAreaFromPos(grid, i + 1, j, rows, cols);
  if (j < cols - 1)
    area += maxAreaFromPos(grid, i, j + 1, rows, cols);
  return area;
}

int maxAreaOfIsland(vector<vector<int>> &grid) {
  int rows = grid.size();
  if (rows <= 0)
    return 0;
  int cols = grid[0].size(), max = 0;
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      int m = maxAreaFromPos(grid, i, j, rows, cols);
      if (max < m)
        max = m;
    }
  }
  return max;
}

int main() {
  vector<vector<int>> grid = {{0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0},
                              {0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0},
                              {0, 1, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0},
                              {0, 1, 0, 0, 1, 1, 0, 0, 1, 0, 1, 0, 0},
                              {0, 1, 0, 0, 1, 1, 0, 0, 1, 1, 1, 0, 0},
                              {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0},
                              {0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0},
                              {0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0}};

  printf("%d\n", maxAreaOfIsland(grid));

  grid = {{0, 0, 0, 0, 0, 0, 0, 0}};
  printf("%d\n", maxAreaOfIsland(grid));

  return 0;
}