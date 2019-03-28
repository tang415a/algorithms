// Given a binary tree with N nodes, each node has a different value from {1, ..., N}.

// A node in this binary tree can be flipped by swapping the left child and the right child of that node.

// Consider the sequence of N values reported by a preorder traversal starting from the root.  Call such a sequence of N values the voyage of the tree.

// (Recall that a preorder traversal of a node means we report the current node's value, then preorder-traverse the left child, then preorder-traverse the right child.)

// Our goal is to flip the least number of nodes in the tree so that the voyage of the tree matches the voyage we are given.

// If we can do so, then return a list of the values of all nodes flipped.  You may return the answer in any order.

// If we cannot do so, then return the list [-1].

// example 1
//    1
// 2
// Input: root = [1,2], voyage = [2,1]
// Output: [-1]

// example 2
//     1
//  2     3
// Input: root = [1,2,3], voyage = [1,3,2]
// Output: [1]

// exmaple 3
//     1
// 2      3
// Input: root = [1,2,3], voyage = [1,2,3]
// Output: []
// Note:
//  1 <= N <= 100

#include <vector>
using namespace std;

/**
 * Definition for a binary tree node.
 * 
 */
struct TreeNode {
  int val;
  TreeNode *left;
  TreeNode *right;
  TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

int doFlip(TreeNode*left, TreeNode*right, const vector<int>& voyage, int &st) {
  TreeNode *first = NULL, *second = NULL; 
  int r = 0, tmp;
  if(left && left->val == voyage[st]) {
    first = left;
    second = right;
  }
  else if(right && right->val == voyage[st]){
    first = right;
    second = left;
    if (left)
      r = 1;
  }
  if (first == NULL) {
    return -1;
  }
  if (first->left || first->right) {
    tmp = doFlip(first->left, first->right, voyage, ++st);
    if (tmp == -1)
      return -1;
    r += tmp;
  }
  if (second) {
    tmp = doFlip(second, NULL, voyage, ++st);
    if (tmp == -1)
      return -1;
    r += tmp;
  }
  return r;
}
vector<int> flipMatchVoyage(TreeNode* root, const vector<int>& voyage) {
  if (voyage.empty()) {
    if (root == NULL)
      return {0};
    return {-1};
  }
  int st = 0;
  int r = doFlip(root, NULL, voyage, st);
  if (st < voyage.size() - 1)
    return {-1};
  return {r};
}

int main() {
  TreeNode n1(1), n2(2), n3(3), n4(4);
  n1.left = &n2;
  n2.right = &n3;
  n1.right = &n4;
  auto res = flipMatchVoyage(&n1, {1,4, 2,3});
  printf("%d", res[0]);
  getchar();
  return 0;
}