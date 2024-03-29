/*
Given the root of a binary tree with N nodes, each node in the tree has node.val
coins, and there are N coins total.

In one move, we may choose two adjacent nodes and move one coin from one node to
another.  (The move may be from parent to child, or from child to parent.)

Return the number of moves required to make every node have exactly one coin.

Example 1:
Input: [3,0,0]
Output: 2
Explanation: From the root of the tree, we move one coin to its left child, and
one coin to its right child.

Example 2:
Input: [0,3,0]
Output: 3
Explanation: From the left child of the root, we move two coins to the root
[taking two moves].  Then, we move one coin from the root of the tree to the
right child.

Example 3:
Input: [1,0,2]
Output: 2

Example 4:
Input: [1,0,0,null,3]
Output: 4

Note:
1<= N <= 100
0 <= node.val <= N
*/

#include <stdio.h>

struct TreeNode {
  int val;
  TreeNode *left, *right;
  TreeNode(int v) : val(v), left(NULL), right(NULL) {}
};

int abs(int v) { return v >= 0 ? v : -v; }

int distributeCoins(TreeNode *root, int &cnt) {
  cnt = 0;
  if (root == NULL)
    return 0;
  int cnt1, cnt2;
  int r1 = distributeCoins(root->left, cnt1),
      r2 = distributeCoins(root->right, cnt2);
  int cnt0 = root->val - 1;
  cnt = cnt1 + cnt2 + cnt0;
  return abs(cnt1) + abs(cnt2) + r1 + r2;
}

int main() {
  TreeNode n[4] = {1, 0, 0, 3};
  n[0].left = n + 1;
  n[0].right = n + 2;
  n[1].right = n + 3;
  int cnt;
  int res = distributeCoins(n, cnt);
  printf("%d", res);
  return 0;
}