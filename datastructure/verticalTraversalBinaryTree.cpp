/*
Given a binary tree, return the vertical order traversal of its nodes values.

For each node at position (X, Y), its left and right children respectively will be at positions (X-1, Y-1) and (X+1, Y-1).

Running a vertical line from X = -infinity to X = +infinity, whenever the vertical line touches some nodes, we report the values of the nodes in order from top to bottom (decreasing Y coordinates).

If two nodes have the same position, then the value of the node that is reported first is the value that is smaller.

Return an list of non-empty reports in order of X coordinate.  Every report will have a list of values of nodes.

Example 1:
Input: [3,9,20,null,null,15,7]
Output: [[9],[3,15],[20],[7]]

Explanation: 
Without loss of generality, we can assume the root node is at position (0, 0):
Then, the node with value 9 occurs at position (-1, -1);
The nodes with values 3 and 15 occur at positions (0, 0) and (0, -2);
The node with value 20 occurs at position (1, -1);
The node with value 7 occurs at position (2, -2).

Example 2:
Input: [1,2,3,4,5,6,7]
Output: [[4],[2],[1,5,6],[3],[7]]

Explanation: 
The node with value 5 and the node with value 6 have the same position according to the given scheme.
However, in the report "[1,5,6]", the node value of 5 comes first since 5 is smaller than 6.
Note:

The tree will have between 1 and 1000 nodes.
Each node’s value will be between 0 and 1000.
*/

#include <stdio.h>
#include <vector>
using namespace std;

struct TreeNode{
  TreeNode* left, *right;
  int val;
  TreeNode(int v): val(v), left(NULL), right(NULL) {}
};

void doTraversal(TreeNode* root, vector<vector<int>>& positives, vector<vector<int>>& negatives, int val) {
  if (root == NULL)
    return;
  
  if (val >= 0) {
    if (positives.size() < val + 1)
      positives.resize(val + 1);
    positives[val].push_back(root->val);
  }
  else {
    if (negatives.size() < -val)
      negatives.resize(-val);
    negatives[-val - 1].push_back(root->val);
  }

  doTraversal(root->left, positives, negatives, val - 1);
  doTraversal(root->right, positives, negatives, val + 1);
}

vector<vector<int>> verticalTraversalBinaryTree(TreeNode* treeNode) {
  if (treeNode == NULL)
    return {};
  vector<vector<int>> positives, negatives, res;
  doTraversal(treeNode, positives, negatives, 0);
  for(int i = negatives.size() - 1; i >= 0; i--) {
    if (negatives[i].size() > 0)
      res.push_back(negatives[i]);
  }
  for (auto& iter: positives) {
    if (iter.size() > 0)
      res.push_back(iter);
  }
  return res;
}

int main() {
  TreeNode nodes[7] = { 1, 2, 3, 4, 5, 6, 7 };
  nodes[0].left = nodes + 1;
  nodes[0].right = nodes + 2;
  nodes[1].left = nodes + 3;
  nodes[1].right = nodes + 4;
  nodes[2].left = nodes + 5;
  nodes[2].right = nodes + 6;
  auto r = verticalTraversalBinaryTree(nodes);

  int siz = r.size();
  printf("[");
  for (int i = 0; i < siz; i++) {
    printf("[");
    int s = r[i].size();
    for(int j = 0; j < s; j++)
      j == s - 1 ? printf("%d", r[i][j]) : printf("%d,", r[i][j]);
    i == siz - 1 ? printf("]") : printf("],");
  }
  printf("]");
  getchar();
  return 0;
}