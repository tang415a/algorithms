/*
You are given an m x n matrix of characters box representing a side-view of a
box. Each cell of the box is one of the following:

A stone '#'
A stationary obstacle '*'
Empty '.'
The box is rotated 90 degrees clockwise, causing some of the stones to fall due
to gravity. Each stone falls down until it lands on an obstacle, another stone,
or the bottom of the box. Gravity does not affect the obstacles' positions, and
the inertia from the box's rotation does not affect the stones' horizontal
positions.

It is guaranteed that each stone in box rests on an obstacle, another stone, or
the bottom of the box.

Return an n x m matrix representing the box after the rotation described above.



Example 1:



Input: box = [["#",".","#"]]
Output: [["."],
         ["#"],
         ["#"]]
Example 2:



Input: box = [["#",".","*","."],
              ["#","#","*","."]]
Output: [["#","."],
         ["#","#"],
         ["*","*"],
         [".","."]]
Example 3:



Input: box = [["#","#","*",".","*","."],
              ["#","#","#","*",".","."],
              ["#","#","#",".","#","."]]
Output: [[".","#","#"],
         [".","#","#"],
         ["#","#","*"],
         ["#","*","."],
         ["#",".","*"],
         ["#",".","."]]


Constraints:

m == box.length
n == box[i].length
1 <= m, n <= 500
box[i][j] is either '#', '*', or '.'.
*/

#include <iostream>
#include <vector>

using namespace std;
vector<vector<char>> rotateTheBox(const vector<vector<char>> &box) {
  int n = box.size(), m = box[0].size();
  vector<vector<char>> store(m, vector<char>(n, '.'));
  for (int i = n - 1; i >= 0; i--) {
    int x = m - 1, y = m - 1;
    while (x >= 0) {
      if (box[i][x] == '*') {
        y = x;
        store[y--][n - 1 - i] = '*';
      } else if (box[i][x] == '#') {
        store[y--][n - 1 - i] = '#';
      }
      x--;
    }
  }
  return store;
}

int main() {
  {
    auto vec = rotateTheBox({{'#', '.', '#'}});
    for (auto &l : vec) {
      for (char c : l) {
        cout << c << " ";
      }
      cout << endl;
    }
  }
  cout << "=============" << endl;
  {
    vector<vector<char>> box = {{'#', '.', '*', '.'}, {'#', '#', '*', '.'}};
    auto vec = rotateTheBox(box);
    for (auto &l : vec) {
      for (char c : l) {
        cout << c << " ";
      }
      cout << endl;
    }
  }
  cout << "=============" << endl;
  {
    auto vec = rotateTheBox({{'#', '#', '*', '.', '*', '.'},
                             {'#', '#', '#', '*', '.', '.'},
                             {'#', '#', '#', '.', '#', '.'}});
    for (auto &l : vec) {
      for (char c : l) {
        cout << c << " ";
      }
      cout << endl;
    }
  }
  return 0;
}