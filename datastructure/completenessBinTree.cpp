/*
Given a binary tree, determine if it is a complete binary tree.

Definition of a complete binary tree from Wikipedia:
In a complete binary tree every level, except possibly the last, is completely filled, and all nodes in the last level are as far left as possible. It can have between 1 and 2h nodes inclusive at the last level h.

Example 1:
     1
  2     3  
4   5 6

Input: [1,2,3,4,5,6]
Output: true
Explanation: Every level before the last is full (ie. levels with node-values {1} and {2, 3}), and all nodes in the last level ({4, 5, 6}) are as far left as possible.

Example 2:
     1
   2   3
 4  5    7

Input: [1,2,3,4,5,null,7]
Output: false
Explanation: The node with value 7 isn't as far left as possible.
 
Note:

The tree will have between 1 and 100 nodes.
*/
#include <stdio.h>
struct TreeNode{
  TreeNode* left, *right;
  int val;
  TreeNode(int v): val(v), left(NULL), right(NULL) {}
};

bool doCheck(TreeNode* root, bool& flag) {
  if (root == NULL)
    return true;
  if (root->left == NULL)
    return root->right == NULL;
  else if (flag)
    return false;
  else if (root->right == NULL)
    flag = true;
  return doCheck(root->left, flag) && doCheck(root->right, flag);
}

bool checkCompleteness(TreeNode* root) {
  bool flag = false;
  return doCheck(root, flag);
}

int main() {
  TreeNode t[7] = {1,2,3,4,5,6,7};
  t[0].left = &t[1];
  t[0].right = &t[2];
  t[1].left = &t[3];
  t[1].right = &t[4];
  //t[2].left = &t[5];
  t[2].right = &t[6];
  if (checkCompleteness(t))
    printf("It is a complete binary tree.");
  else
    printf("It is not a complete binary tree.");
  getchar();
  return 0;
}