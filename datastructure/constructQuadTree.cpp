/*
Given a n * n matrix grid of 0's and 1's only. We want to represent the grid
with a Quad-Tree.

Return the root of the Quad-Tree representing the grid.

Notice that you can assign the value of a node to True or False when isLeaf is
False, and both are accepted in the answer.

A Quad-Tree is a tree data structure in which each internal node has exactly
four children. Besides, each node has two attributes:

val: True if the node represents a grid of 1's or False if the node represents a
grid of 0's. isLeaf: True if the node is leaf node on the tree or False if the
node has the four children.

class Node {
    public boolean val;
    public boolean isLeaf;
    public Node topLeft;
    public Node topRight;
    public Node bottomLeft;
    public Node bottomRight;
}

We can construct a Quad-Tree from a two-dimensional area using the following
steps:

If the current grid has the same value (i.e all 1's or all 0's) set isLeaf True
and set val to the value of the grid and set the four children to Null and stop.
If the current grid has different values, set isLeaf to False and set val to any
value and divide the current grid into four sub-grids as shown in the photo.
Recurse for each of the children with the proper sub-grid.

If you want to know more about the Quad-Tree, you can refer to the wiki.

Quad-Tree format:

The output represents the serialized format of a Quad-Tree using level order
traversal, where null signifies a path terminator where no node exists below.

It is very similar to the serialization of the binary tree. The only difference
is that the node is represented as a list [isLeaf, val].

If the value of isLeaf or val is True we represent it as 1 in the list [isLeaf,
val] and if the value of isLeaf or val is False we represent it as 0.

Example 1:

Input: grid = [[0,1],[1,0]]
Output: [[0,1],[1,0],[1,1],[1,1],[1,0]]
Explanation: The explanation of this example is shown below:
Notice that 0 represnts False and 1 represents True in the photo representing
the Quad-Tree.

Example 2:

Input: grid =
[[1,1,1,1,0,0,0,0],[1,1,1,1,0,0,0,0],[1,1,1,1,1,1,1,1],[1,1,1,1,1,1,1,1],[1,1,1,1,0,0,0,0],[1,1,1,1,0,0,0,0],[1,1,1,1,0,0,0,0],[1,1,1,1,0,0,0,0]]

Output:
[[0,1],[1,1],[0,1],[1,1],[1,0],null,null,null,null,[1,0],[1,0],[1,1],[1,1]]
Explanation: All values in the grid are not the same. We divide the grid into
four sub-grids. The topLeft, bottomLeft and bottomRight each has the same value.
The topRight have different values so we divide it into 4 sub-grids where each
has the same value. Explanation is shown in the photo below:

Constraints:

n == grid.length == grid[i].length
n == 2x where 0 <= x <= 6
*/
#include <iostream>
#include <vector>

using namespace std;

// Definition for a QuadTree node.
class Node {
public:
  bool val;
  bool isLeaf;
  Node *topLeft;
  Node *topRight;
  Node *bottomLeft;
  Node *bottomRight;

  Node() {
    val = false;
    isLeaf = false;
    topLeft = NULL;
    topRight = NULL;
    bottomLeft = NULL;
    bottomRight = NULL;
  }

  Node(bool _val, bool _isLeaf) {
    val = _val;
    isLeaf = _isLeaf;
    topLeft = NULL;
    topRight = NULL;
    bottomLeft = NULL;
    bottomRight = NULL;
  }

  Node(bool _val, bool _isLeaf, Node *_topLeft, Node *_topRight,
       Node *_bottomLeft, Node *_bottomRight) {
    val = _val;
    isLeaf = _isLeaf;
    topLeft = _topLeft;
    topRight = _topRight;
    bottomLeft = _bottomLeft;
    bottomRight = _bottomRight;
  }
};

void clear(Node *p) {
  if (p == NULL)
    return;
  if (!p->isLeaf) {
    if (p->topLeft)
      clear(p->topLeft);
    if (p->topRight)
      clear(p->topRight);
    if (p->bottomLeft)
      clear(p->bottomLeft);
    if (p->bottomRight)
      clear(p->bottomRight);
  }
  delete p;
}

Node *construct(const vector<vector<int>> &grid, int x, int y, int l) {
  if (l == 1) {
    return new Node(grid[x][y], true);
  }
  l /= 2;
  Node *topLeft = construct(grid, x, y, l);
  Node *topRight = construct(grid, x, y + l, l);
  Node *bottomLeft = construct(grid, x + l, y, l);
  Node *bottomRight = construct(grid, x + l, y + l, l);
  if (topLeft->isLeaf && topRight->isLeaf && bottomLeft->isLeaf &&
      bottomRight->isLeaf && topLeft->val == topRight->val &&
      topLeft->val == bottomLeft->val && topLeft->val == bottomRight->val) {
    int val = topLeft->val;
    clear(topLeft);
    clear(topRight);
    clear(bottomLeft);
    clear(bottomRight);
    return new Node(val, true);
  }
  return new Node(1, false, topLeft, topRight, bottomLeft, bottomRight);
}

Node *construct(const vector<vector<int>> &grid) {
  int n = grid.size();
  return construct(grid, 0, 0, n);
}

// helper function
bool hasChild(Node *p) { return p != NULL && !p->isLeaf; }
void print(Node *p) {
  if (p == NULL) {
    cout << "[null]";
    return;
  }
  cout << "[";
  vector<Node *> v = {p};
  for (int k = 0, n = v.size(); k < v.size(); k++) {
    if (v[k] == NULL) {
      cout << "null,"; // the last element in the array cannot be null
      continue;
    }
    cout << "[" << v[k]->isLeaf << "," << v[k]->val << "]";
    if (k != v.size() - 1)
      cout << ",";
    if (k < n) { // n is the last branch node so far
      v.emplace_back(v[k]->topLeft);
      if (hasChild(v.back()))
        n = v.size();
      v.emplace_back(v[k]->topRight);
      if (hasChild(v.back()))
        n = v.size();
      v.emplace_back(v[k]->bottomLeft);
      if (hasChild(v.back()))
        n = v.size();
      v.emplace_back(v[k]->bottomRight);
      if (hasChild(v.back()))
        n = v.size();
    }
  }
  cout << "]";
}

int main() {
  Node *p = construct({{0, 1}, {1, 0}});
  print(p);
  clear(p);
  cout << endl;
  p = construct({{1, 1, 1, 1, 0, 0, 0, 0},
                 {1, 1, 1, 1, 0, 0, 0, 0},
                 {1, 1, 1, 1, 1, 1, 1, 1},
                 {1, 1, 1, 1, 1, 1, 1, 1},
                 {1, 1, 1, 1, 0, 0, 0, 0},
                 {1, 1, 1, 1, 0, 0, 0, 0},
                 {1, 1, 1, 1, 0, 0, 0, 0},
                 {1, 1, 1, 1, 0, 0, 0, 0}});
  print(p);
  clear(p);
  return 0;
}