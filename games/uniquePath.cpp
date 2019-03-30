/*
On a 2-dimensional grid, there are 4 types of squares:

1 represents the starting square.  There is exactly one starting square.
2 represents the ending square.  There is exactly one ending square.
0 represents empty squares we can walk over.
-1 represents obstacles that we cannot walk over.
Return the number of 4-directional walks from the starting square to the ending square, that walk over every non-obstacle square exactly once.

Example 1:

Input: [[1,0,0,0],[0,0,0,0],[0,0,2,-1]]
Output: 2
Explanation: We have the following two paths: 
1. (0,0),(0,1),(0,2),(0,3),(1,3),(1,2),(1,1),(1,0),(2,0),(2,1),(2,2)
2. (0,0),(1,0),(2,0),(2,1),(1,1),(0,1),(0,2),(0,3),(1,3),(1,2),(2,2)

Example 2:

Input: [[1,0,0,0],[0,0,0,0],[0,0,0,2]]
Output: 4
Explanation: We have the following four paths: 
1. (0,0),(0,1),(0,2),(0,3),(1,3),(1,2),(1,1),(1,0),(2,0),(2,1),(2,2),(2,3)
2. (0,0),(0,1),(1,1),(1,0),(2,0),(2,1),(2,2),(1,2),(0,2),(0,3),(1,3),(2,3)
3. (0,0),(1,0),(2,0),(2,1),(2,2),(1,2),(1,1),(0,1),(0,2),(0,3),(1,3),(2,3)
4. (0,0),(1,0),(2,0),(2,1),(1,1),(0,1),(0,2),(0,3),(1,3),(1,2),(2,2),(2,3)

Example 3:

Input: [[0,1],[2,0]]
Output: 0
Explanation: 
There is no path that walks over every empty square exactly once.
Note that the starting and ending square can be anywhere in the grid. 

Note:

1 <= grid.length * grid[0].length <= 20
*/

#include <vector>
using namespace std;

void findStartPos(const vector<vector<int>>& grid, int& r, int& c) {
  for(int i = 0; i < grid.size(); i++) {
    for(int j = 0; j < grid[i].size(); j++) {
      if(grid[i][j] == 1){
        r = i;
        c = j;
        return;
      }
    }
  }
  printf("ERROR: there is no start pos.");
}

bool walkOver(const vector<vector<int>>& grid) {
  for(auto& r: grid) {
    for(auto& v: r) {
      if(v == 0)
        return false;
    }
  }
  return true;
}

int findPath(vector<vector<int>>& grid, int r, int c, int rDelta, int cDelta) {
  int res = 0;
  int r1 = r + rDelta;
  if (r1 < grid.size() && r1 >= 0) {
    int c1 = c + cDelta;
    if (c1 < grid[r1].size() && c1 >= 0) {
      if (grid[r1][c1] == 0 || grid[r1][c1] == 1) {
        int o = grid[r1][c1];
        grid[r1][c1] = 3;
        res += findPath(grid, r1, c1, 1, 0);
        res += findPath(grid, r1, c1, -1, 0);
        res += findPath(grid, r1, c1, 0, 1);
        res += findPath(grid, r1, c1, 0, -1);
        grid[r1][c1] = o;
      }
      else if(grid[r1][c1] == 2 && walkOver(grid)) {
        res = 1;
      }
    }
  }
  return res;
}

int uniquePaths(vector<vector<int>>& grid) {
  int r, c;
  findStartPos(grid, r, c);
  return findPath(grid, r, c, 0, 0);
}

int main() {
  vector<vector<int>> grid = {{0,1},{2,0}};
  printf("%d ", uniquePaths(grid));
  getchar();
  return 0;
}