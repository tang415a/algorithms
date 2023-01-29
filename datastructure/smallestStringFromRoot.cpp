/*
Given the root of a binary tree, each node has a value from 0 to 25 representing the letters 'a' to 'z': a value of 0 represents 'a', a value of 1 represents 'b', and so on.

Find the lexicographically smallest string that starts at a leaf of this tree and ends at the root.

(As a reminder, any shorter prefix of a string is lexicographically smaller: for example, "ab" is lexicographically smaller than "aba".  A leaf of a node is a node that has no children.)

Example 1:
        a
    b       c
  d  e    d  e
Input: [0,1,2,3,4,3,4]
Output: "dba"

Example 2:
        z
    b       d
  b   d   a   c
Input: [25,1,3,1,3,0,2]
Output: "adz"

Example 3:
        c
    c       b
      b   a
    a
Input: [2,2,1,null,1,0,null,0]
Output: "abc"

Note:

The number of nodes in the given tree will be between 1 and 8500.
Each node in the tree will have a value between 0 and 25.
*/

#include <string>
#include <vector>
#include <algorithm>
using namespace std;
/**
 * Definition for a binary tree node.
 */
struct TreeNode {
  int val;
  TreeNode *left;
  TreeNode *right;
  TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

void smallestFromLeafHelper(TreeNode* root, string str, string& res) {
  str.insert(0, 1, char(root->val + 'a'));
  
  if (root->left == NULL && root->right == NULL) {
    res = min(res, str);
    return;
  }
  if (root->left)
    smallestFromLeafHelper(root->left, str, res);
  if (root->right)
    smallestFromLeafHelper(root->right, str, res);
}

string smallestFromLeaf(TreeNode* root) {
  if (root == NULL)
    return "";
  string str = "", res = "{"; // 'z' + 1
  smallestFromLeafHelper(root, str, res);
  return res;
}

int main() {
  //     c
  // c       b
  //   b   a
  // a
  // TreeNode n[6] = {2, 2, 1, 1, 0, 0};
  // n[0].left = n + 1;
  // n[0].right = n + 2;
  // n[1].right = n + 3;
  // n[2].left = n + 4;
  // n[3].left = n + 5;

  //        z
  //   b       d
  // b   d   a   c
  // TreeNode n[7] = {25, 1, 3, 1, 3, 0, 2};
  // n[0].left = n + 1;
  // n[0].right = n + 2;
  // n[1].left = n + 3;
  // n[1].right = n + 4;
  // n[2].left = n + 5;
  // n[2].right = n + 6;

  //         a
  //   b       c
  // d  e    d  e
  TreeNode n[7] = {0,1,2,3,4,3,4};
  n[0].left = n + 1;
  n[0].right = n + 2;
  n[1].left = n + 3;
  n[1].right = n + 4;
  n[2].left = n + 5;
  n[2].right = n + 6;

  auto str = smallestFromLeaf(n);
  printf(str.c_str());
  return 0;
}